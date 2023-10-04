/*******************************************************************************
* Copyright 2002-2020 Intel Corporation
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
//  Purpose:
//     Intel(R) Integrated Performance Primitives. Cryptography Primitives.
//     Internal Unsigned BNU misc functionality
//
//  Contents:
//     cpNLZ_BNU()
//     cpNTZ_BNU()
//
//     cpLSL_BNU()
//     cpLSR_BNU()
//
//     cpLSBit_BNU()
//     cpMSBit_BNU()
//
//     cpFromOctStr_BNU()
//     cpToOctStrS_BNU()
//
//
*/

#include "owncp.h"
#include "pcpbnumisc.h"


/*F*
//    Name: cpNLZ_BNU
//
// Purpose: Returns number of leading zeros of the BNU.
//
// Returns:
//       number of leading zeros of the BNU
//
// Parameters:
//    x         BigNum x
//
*F*/

#if !((_IPP >= _IPP_H9) || (_IPP32E >= _IPP32E_L9))
cpSize cpNLZ_BNU(BNU_CHUNK_T x)
{
   cpSize nlz = 0;
   BNU_CHUNK_T
   #if (BNU_CHUNK_BITS == BNU_CHUNK_64BIT)
   mask = cpIsZero_ct(x & 0xFFFFFFFF00000000);
   nlz += 32 & mask; x = ((x<<32) & mask) | (x & ~mask);

   mask = cpIsZero_ct(x & 0xFFFF000000000000);
   nlz += 16 & mask; x = ((x<<16) & mask) | (x & ~mask);

   mask = cpIsZero_ct(x & 0xFF00000000000000);
   nlz += 8 & mask; x = ((x << 8) & mask) | (x & ~mask);

   mask = cpIsZero_ct(x & 0xF000000000000000);
   nlz += 4 & mask; x = ((x << 4) & mask) | (x & ~mask);

   mask = cpIsZero_ct(x & 0xC000000000000000);
   nlz += 2 & mask; x = ((x << 2) & mask) | (x & ~mask);

   mask = cpIsZero_ct(x & 0x8000000000000000);
   nlz += 1 & mask; x = ((x << 1) & mask) | (x & ~mask);

   mask = cpIsZero_ct(x & 0x8000000000000000);
   nlz += 1 & mask;
#else
   mask = cpIsZero_ct(x & 0xFFFF0000);
   nlz += 16 & mask; x = ((x << 16) & mask) | (x & ~mask);

   mask = cpIsZero_ct(x & 0xFF000000);
   nlz += 8 & mask; x = ((x << 8) & mask) | (x & ~mask);

   mask = cpIsZero_ct(x & 0xF0000000);
   nlz += 4 & mask; x = ((x << 4) & mask) | (x & ~mask);

   mask = cpIsZero_ct(x & 0xC0000000);
   nlz += 2 & mask; x = ((x << 2) & mask) | (x & ~mask);

   mask = cpIsZero_ct(x & 0x80000000);
   nlz += 1 & mask; x = ((x << 1) & mask) | (x & ~mask);

   mask = cpIsZero_ct(x & 0x80000000);
   nlz += 1 & mask;
#endif
   return nlz;
}
#endif

/*F*
//    Name: cpNTZ_BNU
//
// Purpose: Returns number of trailing zeros of the BNU.
//
// Returns:
//       number of trailing zeros of the BNU
//
// Parameters:
//    x         BigNum x
//
*F*/

cpSize cpNTZ_BNU(BNU_CHUNK_T x)
{
   cpSize ntz = BNU_CHUNK_BITS;
   if(x) {
      ntz = 0;
      #if (BNU_CHUNK_BITS==BNU_CHUNK_64BIT)
      if( 0==(x & 0x00000000FFFFFFFF) ) { ntz+=32; x>>=32; }
      if( 0==(x & 0x000000000000FFFF) ) { ntz+=16; x>>=16; }
      if( 0==(x & 0x00000000000000FF) ) { ntz+= 8; x>>= 8; }
      if( 0==(x & 0x000000000000000F) ) { ntz+= 4; x>>= 4; }
      if( 0==(x & 0x0000000000000003) ) { ntz+= 2; x>>= 2; }
      if( 0==(x & 0x0000000000000001) ) { ntz++; }
      #else
      if( 0==(x & 0x0000FFFF) )         { ntz+=16; x>>=16; }
      if( 0==(x & 0x000000FF) )         { ntz+= 8; x>>= 8; }
      if( 0==(x & 0x0000000F) )         { ntz+= 4; x>>= 4; }
      if( 0==(x & 0x00000003) )         { ntz+= 2; x>>= 2; }
      if( 0==(x & 0x00000001) )         { ntz++; }
      #endif
   }
   return ntz;
}

/*F*
//    Name: cpLSR_BNU
//
// Purpose: Logical shift right (including inplace).
//
// Returns:
//       new length
//
// Parameters:
//    pA          BigNum A
//    pR          result BigNum
//    nsA         size of A
//    nBits       size of shift in bits 
*F*/

cpSize cpLSR_BNU(BNU_CHUNK_T* pR, const BNU_CHUNK_T* pA, cpSize nsA, cpSize nBits)
{
   cpSize nw = nBits/BNU_CHUNK_BITS;
   cpSize n;

   pA += nw;
   nsA -= nw;

   nBits %= BNU_CHUNK_BITS;
   if(nBits) {
      BNU_CHUNK_T hi;
      BNU_CHUNK_T lo = pA[0];

      for(n=0; n<(nsA-1); n++) {
         hi = pA[n+1];
         pR[n] = (lo>>nBits) | (hi<<(BNU_CHUNK_BITS-nBits));
         lo = hi;
      }
      pR[nsA-1] = (lo>>nBits);
   }
   else {
      for(n=0; n<nsA; n++)
         pR[n] = pA[n];
   }

   for(n=0; n<nw; n++)
      pR[nsA+n] = 0;

   return nsA+nw;
}

/*F*
//    Name: cpMSBit_BNU
//
// Purpose: Returns Most Significant Bit of the BNU.
//
// Returns:
//       Most Significant Bit of the BNU
//
// Parameters:
//    pA          BigNum A
//    nsA         size of A
//
// Note:
//    if BNU==0, -1 will return
*F*/
int cpMSBit_BNU(const BNU_CHUNK_T* pA, cpSize nsA)
{
   int msb;
   FIX_BNU(pA, nsA);
   msb  = nsA*BNU_CHUNK_BITS - cpNLZ_BNU(pA[nsA-1]) -1;
   return msb;
}

/*F*
//    Name: cpFromOctStr_BNU
//
// Purpose: Convert Oct String into BNU representation.
//
// Returns:                 
//          size of BNU in BNU_CHUNK_T chunks
//
// Parameters:
//    pStr        pointer to the source octet string
//    strLen      octet string length
//    pA          pointer to the target BN
//
*F*/
cpSize cpFromOctStr_BNU(BNU_CHUNK_T* pA, const Ipp8u* pStr, cpSize strLen)
{
   int nsA =0;

   /* start from the end of string */
   for(; strLen>=(int)sizeof(BNU_CHUNK_T); nsA++,strLen-=(int)(sizeof(BNU_CHUNK_T))) {
      /* pack sizeof(BNU_CHUNK_T) bytes into single BNU_CHUNK_T value*/
      *pA++ =
         #if (BNU_CHUNK_BITS==BNU_CHUNK_64BIT)
         +( (BNU_CHUNK_T)pStr[strLen-8]<<(8*7) )
         +( (BNU_CHUNK_T)pStr[strLen-7]<<(8*6) )
         +( (BNU_CHUNK_T)pStr[strLen-6]<<(8*5) )
         +( (BNU_CHUNK_T)pStr[strLen-5]<<(8*4) )
         #endif
         +( (BNU_CHUNK_T)pStr[strLen-4]<<(8*3) )
         +( (BNU_CHUNK_T)pStr[strLen-3]<<(8*2) )
         +( (BNU_CHUNK_T)pStr[strLen-2]<<(8*1) )
         +  (BNU_CHUNK_T)pStr[strLen-1];
   }

   /* convert the beginning of the string */
   if(strLen) {
      BNU_CHUNK_T x = 0;
      for(x=0; strLen>0; strLen--) {
         BNU_CHUNK_T d = *pStr++;
         x = (x<<8) + d;
       }
       *pA++ = x;
       nsA++;
   }

   return nsA;
}

/*
// Convert BNU into HexString representation
//
// Returns length of the string or 0 if no success
*/
cpSize cpToOctStr_BNU(Ipp8u* pStr, cpSize strLen, const BNU_CHUNK_T* pA, cpSize nsA)
{
   FIX_BNU(pA, nsA);
   {
      cpSize bnuBitSize = BITSIZE_BNU(pA, nsA);
      if(bnuBitSize <= strLen*BYTESIZE) {
         int cnvLen = 0;
         BNU_CHUNK_T x = pA[nsA-1];

         ZEXPAND_BNU(pStr, 0, strLen);
         pStr += strLen - BITS2WORD8_SIZE(bnuBitSize);

         if(x) {
            //int nb;
            cpSize nb;
            for(nb=cpNLZ_BNU(x)/BYTESIZE; nb<(cpSize)(sizeof(BNU_CHUNK_T)); cnvLen++, nb++)
               *pStr++ = EBYTE(x, (Ipp32s)sizeof(BNU_CHUNK_T)-1-nb);

            for(--nsA; nsA>0; cnvLen+=(Ipp32s)sizeof(BNU_CHUNK_T), nsA--) {
               x = pA[nsA-1];
               #if (BNU_CHUNK_BITS==BNU_CHUNK_64BIT)
               *pStr++ = EBYTE(x,7);
               *pStr++ = EBYTE(x,6);
               *pStr++ = EBYTE(x,5);
               *pStr++ = EBYTE(x,4);
               #endif
               *pStr++ = EBYTE(x,3);
               *pStr++ = EBYTE(x,2);
               *pStr++ = EBYTE(x,1);
               *pStr++ = EBYTE(x,0);
            }
         }
         IPP_UNREFERENCED_PARAMETER(cnvLen);

         return strLen;
      }
      else
         return 0;
   }
}
