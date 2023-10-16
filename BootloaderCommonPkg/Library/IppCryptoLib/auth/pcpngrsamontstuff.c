/*******************************************************************************
* Copyright 2018-2020 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/*
//
//  Purpose:
//     Cryptography Primitive.
//     RSA Internal Functions
//
//
//
*/

#include "owndefs.h"
#include "owncp.h"
#include "pcpngrsa.h"
#include "pcpngrsamontstuff.h"


/*
// Montgomery engine preparation (GetSize/init/Set)
*/
void rsaMontExpGetSize (int maxLen32, int* pSize)
{
    int size = 0;
    int maxBitSize = maxLen32 << 5;
    gsModEngineGetSize(maxBitSize, MOD_ENGINE_RSA_POOL_SIZE, &size);

    *pSize = size;
}


/*
// "fast" binary montgomery exponentiation
//
// scratch buffer structure:
//    dataT[nsM]     copy of base (in case of inplace operation)
//    product[nsM*2]
*/
cpSize gsMontExpBin_BNU (BNU_CHUNK_T* dataY, const BNU_CHUNK_T* dataX, cpSize nsX, const BNU_CHUNK_T* dataE, cpSize bitsizeE, gsModEngine* pMont, BNU_CHUNK_T* pBuffer)
{
    cpSize nsM = MOD_LEN(pMont);
    cpSize nsE = BITS_BNU_CHUNK(bitsizeE);

    /*
    // test for special cases:
    //    x^0 = 1
    //    0^e = 0
    */
    if (cpEqu_BNU_CHUNK(dataE, nsE, 0)) {
        COPY_BNU(dataY, MOD_MNT_R(pMont), nsM);
    }
    else if (cpEqu_BNU_CHUNK(dataX, nsX, 0)) {
        ZEXPAND_BNU(dataY, 0, nsM);
    }

    /* general case */
    else {
        /* allocate buffers */
        BNU_CHUNK_T* dataT = pBuffer;

        /* copy and expand base to the modulus length */
        ZEXPAND_COPY_BNU(dataT, nsM, dataX, nsX);
        /* copy */
        COPY_BNU(dataY, dataT, nsM);

        FIX_BNU(dataE, nsE);

        /* execute most significant part pE */
        {
            BNU_CHUNK_T eValue = dataE[nsE - 1];
            int n = cpNLZ_BNU(eValue) + 1;

            eValue <<= n;
            for (; n<BNU_CHUNK_BITS; n++, eValue <<= 1) {
                /* squaring R = R*R mod Modulus */
                MOD_METHOD(pMont)->sqr(dataY, dataY, pMont);
                /* and multiply R = R*X mod Modulus */
                if (eValue & ((BNU_CHUNK_T)1 << (BNU_CHUNK_BITS - 1)))
                    MOD_METHOD(pMont)->mul(dataY, dataY, dataT, pMont);
            }

            /* execute rest bits of E */
            for (--nsE; nsE>0; nsE--) {
                eValue = dataE[nsE - 1];

                for (n = 0; n<BNU_CHUNK_BITS; n++, eValue <<= 1) {
                    /* squaring: R = R*R mod Modulus */
                    MOD_METHOD(pMont)->sqr(dataY, dataY, pMont);

                    if (eValue & ((BNU_CHUNK_T)1 << (BNU_CHUNK_BITS - 1)))
                        MOD_METHOD(pMont)->mul(dataY, dataY, dataT, pMont);
                }
            }
        }
    }

    return nsM;
}

/*
// "safe" binary montgomery exponentiation
//
// scratch buffer structure:
//    sscm[nsM]
//    dataT[nsM]
//    product[nsM*2]
*/
cpSize gsMontExpBin_BNU_sscm (BNU_CHUNK_T* dataY, const BNU_CHUNK_T* dataX, cpSize nsX, const BNU_CHUNK_T* dataE, cpSize bitsizeE, gsModEngine* pMont, BNU_CHUNK_T* pBuffer)
{

    cpSize nsM = MOD_LEN(pMont);
    cpSize nsE = BITS_BNU_CHUNK(bitsizeE);

    /*
    // test for special cases:
    //    x^0 = 1
    //    0^e = 0
    */
    if (cpEqu_BNU_CHUNK(dataE, nsE, 0)) {
        COPY_BNU(dataY, MOD_MNT_R(pMont), nsM);
    }
    else if (cpEqu_BNU_CHUNK(dataX, nsX, 0)) {
        ZEXPAND_BNU(dataY, 0, nsM);
    }

    /* general case */
    else {

      /* allocate buffers */
      BNU_CHUNK_T* dataT = pBuffer;
      BNU_CHUNK_T* sscmB = dataT + nsM;

      /* mont(1) */
      BNU_CHUNK_T* pR = MOD_MNT_R(pMont);

      /* copy and expand base to the modulus length */
       ZEXPAND_COPY_BNU(dataT, nsM, dataX, nsX);
       /* init result */
       COPY_BNU(dataY, MOD_MNT_R(pMont), nsM);

      /* execute bits of E */
      for (; nsE>0; nsE--) {
         BNU_CHUNK_T eValue = dataE[nsE-1];

         int n;
         for(n=BNU_CHUNK_BITS; n>0; n--) {
            /* sscmB = ( msb(eValue) )? X : mont(1) */
            BNU_CHUNK_T mask = cpIsMsb_ct(eValue);
            eValue <<= 1;
            cpMaskedCopyBNU_ct(sscmB, mask, dataT, pR, nsM);

            /* squaring Y = Y^2 */
            MOD_METHOD(pMont)->sqr(dataY, dataY, pMont);
            /* and multiplication: Y = Y * sscmB */
            MOD_METHOD(pMont)->mul(dataY, dataY, sscmB, pMont);
         }
      }
   }

   return nsM;
}


#if defined(_USE_WINDOW_EXP_)
//#define GS_DEBUG  // test buffer alignment
#if defined(GS_DEBUG)
#include <stdio.h>
#endif
/*
// "safe" fixed-size window montgomery exponentiation
//
// - input/output are in Montgomery Domain
// - possible inplace mode
//
// scratch buffer structure:
//    precomuted table of multipliers[(1<<w)*nsM]
//    RR[nsM]   tmp result if inplace operation
//    TT[nsM]  unscrmbled table entry
//    EE[nsM+1] power expasin
*/
cpSize gsMontExpWin_BNU_sscm (BNU_CHUNK_T* dataY, const BNU_CHUNK_T* dataX, cpSize nsX, const BNU_CHUNK_T* dataExp, cpSize bitsizeE, gsModEngine* pMont, BNU_CHUNK_T* pBuffer)
{
   cpSize nsM = MOD_LEN(pMont);
   cpSize nsE = BITS_BNU_CHUNK(bitsizeE);

   /*
   // test for special cases:
   //    x^0 = 1
   //    0^e = 0
   */
   if( cpEqu_BNU_CHUNK(dataExp, nsE, 0) ) {
      COPY_BNU(dataY, MOD_MNT_R(pMont), nsM);
   }
   else if( cpEqu_BNU_CHUNK(dataX, nsX, 0) ) {
      ZEXPAND_BNU(dataY, 0, nsM);
   }

   /* general case */
   else {
      cpSize winSize = gsMontExp_WinSize(bitsizeE);
      cpSize nPrecomute= 1<<winSize;
      BNU_CHUNK_T mask = (BNU_CHUNK_T)(nPrecomute -1);
      int n;

      BNU_CHUNK_T* pTable = (BNU_CHUNK_T*)(IPP_ALIGNED_PTR((pBuffer), CACHE_LINE_SIZE));
      BNU_CHUNK_T* dataTT = pTable + gsGetScrambleBufferSize(nsM, winSize);
      BNU_CHUNK_T* dataRR = dataTT + nsM;
      BNU_CHUNK_T* dataEE = dataRR;

      /* copy and expand base to the modulus length */
      ZEXPAND_COPY_BNU(dataTT, nsM, dataX, nsX);

      /* initialize recource */
      gsScramblePut(pTable, 0, MOD_MNT_R(pMont), nsM, winSize);
      COPY_BNU(dataRR, dataTT, nsM);
      gsScramblePut(pTable, 1, dataTT, nsM, winSize);
      for(n=2; n<nPrecomute; n++) {
         MOD_METHOD( pMont )->mul(dataTT, dataTT, dataRR, pMont);
         gsScramblePut(pTable, n, dataTT, nsM, winSize);
      }

      /* expand exponent*/
      ZEXPAND_COPY_BNU(dataEE, nsM+1, dataExp, nsE);
      bitsizeE = ((bitsizeE+winSize-1)/winSize) *winSize;

      /* exponentiation */
      {
         /* position of the 1-st (left) window */
         int eBit = bitsizeE-winSize;

         /* extract 1-st window value */
         Ipp32u eChunk = *((Ipp32u*)((Ipp16u*)dataEE + eBit/BITSIZE(Ipp16u)));
         int shift = eBit & 0xF;
         Ipp32u winVal = (eChunk>>shift) &mask;

         /* initialize result */
         gsScrambleGet_sscm(dataY, nsM, pTable, (int)winVal, winSize);

         for(eBit-=winSize; eBit>=0; eBit-=winSize) {
            /* do square window times */
            for(n=0,winVal=0; n<winSize; n++) {
               MOD_METHOD( pMont )->sqr(dataY, dataY, pMont);
            }

            /* extract next window value */
            eChunk = *((Ipp32u*)((Ipp16u*)dataEE + eBit/BITSIZE(Ipp16u)));
            shift = eBit & 0xF;
            winVal = (eChunk>>shift) &mask;

            /* exptact precomputed value and muptiply */
            gsScrambleGet_sscm(dataTT, nsM, pTable, (int)winVal, winSize);

            MOD_METHOD( pMont )->mul(dataY, dataY, dataTT, pMont);
         }
      }
   }

   return nsM;
}
#endif

cpSize gsMontExpWinBuffer (int modulusBits)
{
   cpSize w = gsMontExp_WinSize(modulusBits);
   cpSize nsM = BITS_BNU_CHUNK(modulusBits);

   cpSize bufferNum = CACHE_LINE_SIZE/((Ipp32s)sizeof(BNU_CHUNK_T))
                    + gsGetScrambleBufferSize(nsM, w) /* pre-computed table */
                    + nsM                             /* tmp unscrambled table entry */
                    + nsM;                            /* zero expanded exponent | "masked" multipler (X|1) */
   return bufferNum;
}

/*
// "safe" fixed-size window exponentiation
// - input/output are in Regular Domain
// - possible inplace mode
*/
cpSize gsModExpWin_BNU_sscm (BNU_CHUNK_T* dataY, const BNU_CHUNK_T* dataX, cpSize nsX, const BNU_CHUNK_T* dataExp, cpSize bitsizeE, gsModEngine* pMont, BNU_CHUNK_T* pBuffer)
{
   cpSize nsM = MOD_LEN(pMont);

   /* copy and expand base to the modulus length */
   ZEXPAND_COPY_BNU(dataY, nsM, dataX, nsX);

   /* convert base to Montgomery domain */
   MOD_METHOD(pMont)->encode(dataY, dataY, pMont);

   /* exponentiation */
   gsMontExpWin_BNU_sscm(dataY, dataY, nsM, dataExp, bitsizeE, pMont, pBuffer);

   /* convert result back to regular domain */
   MOD_METHOD(pMont)->decode(dataY, dataY, pMont);

   return nsM;
}

/*
// definition of RSA exponentiation (PX/GPR based)
*/

gsMethod_RSA* gsMethod_RSA_gpr_private (void)
{
   static gsMethod_RSA m = {
      MIN_RSA_SIZE, MAX_RSA_SIZE,   /* RSA range */

      /* private key exponentiation: private, window, gpr */
      gsMontExpWinBuffer,
      #if !defined(_USE_WINDOW_EXP_)
      gsModExpBin_BNU_sscm
      #else
      gsModExpWin_BNU_sscm
      #endif
      , NULL
   };
   return &m;
}

cpSize gsMontExpBinBuffer (int modulusBits)
{
   cpSize nsM = BITS_BNU_CHUNK(modulusBits);
   cpSize bufferNum = nsM;
   return bufferNum;
}

/*
// "fast" binary montgomery exponentiation
//
// - input/output are in Regular Domain
// - possible inplace mode
//
// scratch buffer structure:
//    dataT[nsM]     copy of base (in case of inplace operation)
*/
cpSize gsModExpBin_BNU (BNU_CHUNK_T* dataY, const BNU_CHUNK_T* dataX, cpSize nsX, const BNU_CHUNK_T* dataE, cpSize bitsizeE, gsModEngine* pMont, BNU_CHUNK_T* pBuffer)
{
   cpSize nsM = MOD_LEN(pMont);
   
   /* copy and expand base to the modulus length */
   ZEXPAND_COPY_BNU(dataY, nsM, dataX, nsX);
   /* convert base to Montgomery domain */
   MOD_METHOD(pMont)->encode(dataY, dataY, pMont);

   /* exponentiation */
   gsMontExpBin_BNU(dataY, dataY, nsM, dataE, bitsizeE, pMont, pBuffer);

   /* convert result back to regular domain */
   MOD_METHOD(pMont)->decode(dataY, dataY, pMont);

   return nsM;
}

gsMethod_RSA* gsMethod_RSA_gpr_public (void)
{
   static gsMethod_RSA m = {
      MIN_RSA_SIZE, MAX_RSA_SIZE,   /* RSA range */

      /* public key exponentiation: public, binary, gpr */
      gsMontExpBinBuffer,
      gsModExpBin_BNU,
      NULL
   };
   return &m;
}

int gsGetScrambleBufferSize (int modulusLen, int w)
{
   /* size of resource to store 2^w values of modulusLen*sizeof(BNU_CHUNK_T) each */
   int size = (1<<w) * modulusLen * (Ipp32s)sizeof(BNU_CHUNK_T);
   /* padd it up to CACHE_LINE_SIZE */
   size += (CACHE_LINE_SIZE - (size % CACHE_LINE_SIZE)) %CACHE_LINE_SIZE;
   return size/(Ipp32s)sizeof(BNU_CHUNK_T);
}

void gsScramblePut (BNU_CHUNK_T* tbl, int idx, const BNU_CHUNK_T* val, int vLen, int w)
{
   int width = 1 << w;
   int i, j;
   for(i=0, j=idx; i<vLen; i++, j+= width) {
      tbl[j] = val[i];
   }
}

void gsScrambleGet (BNU_CHUNK_T* val, int vLen, const BNU_CHUNK_T* tbl, int idx, int w)
{
   int width = 1 << w;
   int i, j;
   for(i=0, j=idx; i<vLen; i++, j+= width) {
      val[i] = tbl[j];
   }
}

void gsScrambleGet_sscm (BNU_CHUNK_T* val, int vLen, const BNU_CHUNK_T* tbl, int idx, int w)
{
   BNU_CHUNK_T mask[1<<MAX_W];

   int width = 1 << w;

   int n, i;
   switch (w) {
   case 6:
      for(n=0; n<(1<<6); n++)
         mask[n] = cpIsEqu_ct((BNU_CHUNK_T)n, (BNU_CHUNK_T)idx);
      break;
   case 5:
      for(n=0; n<(1<<5); n++)
         mask[n] = cpIsEqu_ct((BNU_CHUNK_T)n, (BNU_CHUNK_T)idx);
      break;
   case 4:
      for(n=0; n<(1<<4); n++)
         mask[n] = cpIsEqu_ct((BNU_CHUNK_T)n, (BNU_CHUNK_T)idx);
      break;
   case 3:
      for(n=0; n<(1<<3); n++)
         mask[n] = cpIsEqu_ct((BNU_CHUNK_T)n, (BNU_CHUNK_T)idx);
      break;
   case 2:
      for(n=0; n<(1<<2); n++)
         mask[n] = cpIsEqu_ct((BNU_CHUNK_T)n, (BNU_CHUNK_T)idx);
      break;
   default:
      mask[0] = cpIsEqu_ct(0, (BNU_CHUNK_T)idx);
      mask[1] = cpIsEqu_ct(1, (BNU_CHUNK_T)idx);
      break;
   }

   for(i=0; i<vLen; i++, tbl += width) {
      BNU_CHUNK_T acc = 0;

      switch (w) {
      case 6:
         for(n=0; n<(1<<6); n++)
            acc |= tbl[n] & mask[n];
         break;
      case 5:
         for(n=0; n<(1<<5); n++)
            acc |= tbl[n] & mask[n];
         break;
      case 4:
         for(n=0; n<(1<<4); n++)
            acc |= tbl[n] & mask[n];
         break;
      case 3:
         for(n=0; n<(1<<3); n++)
            acc |= tbl[n] & mask[n];
         break;
      case 2:
         for(n=0; n<(1<<2); n++)
            acc |= tbl[n] & mask[n];
         break;
      default:
         acc |= tbl[0] & mask[0];
         acc |= tbl[1] & mask[1];
         break;
      }

      val[i] = acc;
   }
}