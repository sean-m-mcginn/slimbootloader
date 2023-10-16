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
//     RSA Functions
//
//  Contents:
//     ippsRSA_GetBufferSizePublicKey()
//     ippsRSA_GetBufferSizePrivateKey()
//     ippsRSA_Encrypt()
//     ippsRSA_Decrypt()
//
//
*/

#include "owncp.h"
#include "pcpbn.h"
#include "pcpngrsa.h"
#include "pcpngrsamontstuff.h"


/* get default method based on CPU's features */
static gsMethod_RSA* getDefaultMethod_RSA_public(int modulusBitSize)
{
    gsMethod_RSA* m;

#if(_IPP32E>=_IPP32E_K0) && defined(_RSA_AVX512)
    m = IsFeatureEnabled(ippCPUID_AVX512IFMA) ? gsMethod_RSA_avx512_public() : gsMethod_RSA_avx2_public();
#elif(_IPP32E>=_IPP32E_L9) && defined(_RSA_AVX2)
    m = gsMethod_RSA_avx2_public();
#elif(_IPP>=_IPP_W7) && defined(_RSA_SSE2)
    m = gsMethod_RSA_sse2_public();
#else
    m = gsMethod_RSA_gpr_public();
#endif

    if (!(m->loModulusBisize <= modulusBitSize && modulusBitSize <= m->hiModulusBisize))
        m = gsMethod_RSA_gpr_public();
    return m;
}

static gsMethod_RSA* getDefaultMethod_RSA_private(int modulusBitSize)
{
    gsMethod_RSA* m;

#if(_IPP32E>=_IPP32E_K0) && defined(_RSA_AVX512)
    m = IsFeatureEnabled(ippCPUID_AVX512IFMA) ? gsMethod_RSA_avx512_private() : gsMethod_RSA_avx2_private();

#elif(_IPP32E>=_IPP32E_L9) && defined(_RSA_AVX2)
    m = IsFeatureEnabled(ippCPUID_ADCOX) ? gsMethod_RSA_gpr_private() : gsMethod_RSA_avx2_private();

#elif(_IPP>=_IPP_W7) && defined(_RSA_SSE2)
    m = gsMethod_RSA_sse2_private();

#else
    m = gsMethod_RSA_gpr_private();
#endif

    if (!(m->loModulusBisize <= modulusBitSize && modulusBitSize <= m->hiModulusBisize))
        m = gsMethod_RSA_gpr_private();
    return m;
}

static gsMethod_RSA* getDualExpMethod_RSA_private(int bitSizeDP, int bitSizeDQ)
{
    /* Dual exp kernels assume same bitsizes of private exponents */
    if ((bitSizeDP != bitSizeDQ) || (bitSizeDP == 0))
        return NULL;

#if(_IPP32E>=_IPP32E_L9) && defined(_RSA_AVX2)
    gsMethod_RSA* m = NULL;
    m = gsMethod_RSA_avx512_crt_private(bitSizeDP);
    if (m && m->dualExpFun)
        return m;
#endif

    return NULL;
}

/*F*
// Name: ippsRSA_GetBufferSizePublicKey
//
// Purpose: Returns size of temporary buffer (in bytes) for public key operation
//
// Returns:                   Reason:
//    ippStsNullPtrErr           NULL == pKey
//                               NULL == pBufferSize
//
//    ippStsContextMatchErr     !RSA_PUB_KEY_VALID_ID()
//
//    ippStsIncompleteContextErr no ippsRSA_SetPublicKey() call
//
//    ippStsNoErr                no error
//
// Parameters:
//    pBufferSize pointer to size of temporary buffer
//    pKey        pointer to the key context
*F*/
IPPFUN(IppStatus, ippsRSA_GetBufferSizePublicKey,(int* pBufferSize, const IppsRSAPublicKeyState* pKey))
{
   IPP_BAD_PTR1_RET(pKey);
   IPP_BADARG_RET(!RSA_PUB_KEY_VALID_ID(pKey), ippStsContextMatchErr);
   IPP_BADARG_RET(!RSA_PUB_KEY_IS_SET(pKey), ippStsIncompleteContextErr);

   IPP_BAD_PTR1_RET(pBufferSize);

   {
      cpSize bitSizeN = RSA_PUB_KEY_BITSIZE_N(pKey);
      cpSize nsN = BITS_BNU_CHUNK(bitSizeN);

      gsMethod_RSA* m = getDefaultMethod_RSA_public(bitSizeN);

      cpSize bufferNum = ((nsN+1)*2)*2          /* (1)2 BN for RSA (enc)/sign schemes */
                        + 1;                    /* BNU_CHUNK_T alignment */
      bufferNum += m->bufferNumFunc(bitSizeN);  /* RSA public key operation */

      *pBufferSize = bufferNum*(Ipp32s)sizeof(BNU_CHUNK_T);

      return ippStsNoErr;
   }
}

/*F*
// Name: ippsRSA_GetBufferSizePrivateKey
//
// Purpose: Returns size of temporary buffer (in bytes) for private key operation
//
// Returns:                   Reason:
//    ippStsNullPtrErr           NULL == pKey
//                               NULL == pBufferSize
//
//    ippStsContextMatchErr     !RSA_PRV_KEY_VALID_ID()
//
//    ippStsIncompleteContextErr (type1) private key is not set up
//
//    ippStsNoErr                no error
//
// Parameters:
//    pBufferSize pointer to size of temporary buffer
//    pKey        pointer to the key context
*F*/
IPPFUN(IppStatus, ippsRSA_GetBufferSizePrivateKey,(int* pBufferSize, const IppsRSAPrivateKeyState* pKey))
{
   IPP_BAD_PTR1_RET(pKey);
   IPP_BADARG_RET(!RSA_PRV_KEY_VALID_ID(pKey), ippStsContextMatchErr);
   IPP_BADARG_RET(RSA_PRV_KEY1_VALID_ID(pKey) && !RSA_PRV_KEY_IS_SET(pKey), ippStsIncompleteContextErr);

   IPP_BAD_PTR1_RET(pBufferSize);

   {
      cpSize modulusBits = (RSA_PRV_KEY1_VALID_ID(pKey))? RSA_PRV_KEY_BITSIZE_N(pKey) :
                                                  IPP_MAX(RSA_PRV_KEY_BITSIZE_P(pKey), RSA_PRV_KEY_BITSIZE_Q(pKey));
      gsMethod_RSA* m = getDualExpMethod_RSA_private(RSA_PRV_KEY_BITSIZE_P(pKey), RSA_PRV_KEY_BITSIZE_Q(pKey));
      if (NULL == m)
         m = getDefaultMethod_RSA_private(modulusBits);

      cpSize bitSizeN = (RSA_PRV_KEY1_VALID_ID(pKey))? modulusBits : modulusBits*2;
      cpSize nsN = BITS_BNU_CHUNK(bitSizeN);

      cpSize bn_scheme = (nsN+1)*2;    /* BN for RSA schemes */
      cpSize bn3_gen = (RSA_PRV_KEY2_VALID_ID(pKey))? (nsN+1)*2*3 : 0; /* 3 BN for generation/validation */

      cpSize bufferNum = bn_scheme*2               /* (1)2 BN for RSA (enc)/sign schemes */
                       + 1;                        /* BNU_CHUNK_T alignment */
      bufferNum += m->bufferNumFunc(modulusBits);  /* RSA private key operation */

      bufferNum = IPP_MAX(bufferNum, bn3_gen); /* generation/validation resource overlaps RSA resource  */

      *pBufferSize = bufferNum*(Ipp32s)sizeof(BNU_CHUNK_T);

      #if defined(_USE_WINDOW_EXP_)
      /* pre-computed table should be CACHE_LINE aligned*/
      *pBufferSize += CACHE_LINE_SIZE;
      #endif

      return ippStsNoErr;
   }
}


void gsRSApub_cipher (IppsBigNumState* pY, const IppsBigNumState* pX, const IppsRSAPublicKeyState* pKey, BNU_CHUNK_T* pBuffer)
{
   gsMethod_RSA* m = getDefaultMethod_RSA_public(RSA_PRV_KEY_BITSIZE_N(pKey));

   BNU_CHUNK_T* dataY = BN_NUMBER(pY);
   cpSize nsY = m->expFun(dataY,
                          BN_NUMBER(pX), BN_SIZE(pX),
                          RSA_PUB_KEY_E(pKey), RSA_PUB_KEY_BITSIZE_E(pKey),
                          RSA_PUB_KEY_NMONT(pKey),
                          pBuffer);
   FIX_BNU(dataY, nsY);
   BN_SIZE(pY) = nsY;
   BN_SIGN(pY) = ippBigNumPOS;
}

/*F*
// Name: ippsRSA_Encrypt
//
// Purpose: Performs RSA Encryprion
//
// Returns:                   Reason:
//    ippStsNullPtrErr           NULL == pKey
//                               NULL == pPtxt
//                               NULL == pCtxt
//                               NULL == pBuffer
//
//    ippStsContextMatchErr     !RSA_PUB_KEY_VALID_ID()
//                              !BN_VALID_ID(pPtxt)
//                              !BN_VALID_ID(pCtxt)
//
//    ippStsIncompleteContextErr public key is not setup
//
//    ippStsOutOfRangeErr        pPtxt >= modulus
//                               pPtxt <0
//
//    ippStsSizeErr              BN_ROOM(pCtxt) is not enough
//
//    ippStsNoErr                no error
//
// Parameters:
//    pPtxt          pointer to the plaintext
//    pCtxt          pointer to the ciphertext
//    pKey           pointer to the key context
//    pScratchBuffer pointer to the temporary buffer
*F*/
IPPFUN(IppStatus, ippsRSA_Encrypt,(const IppsBigNumState* pPtxt,
                                         IppsBigNumState* pCtxt,
                                   const IppsRSAPublicKeyState* pKey,
                                         Ipp8u* pBuffer))
{
   IPP_BAD_PTR2_RET(pKey, pBuffer);
   IPP_BADARG_RET(!RSA_PUB_KEY_VALID_ID(pKey), ippStsContextMatchErr);
   IPP_BADARG_RET(!RSA_PUB_KEY_IS_SET(pKey), ippStsIncompleteContextErr);

   IPP_BAD_PTR1_RET(pPtxt);
   IPP_BADARG_RET(!BN_VALID_ID(pPtxt), ippStsContextMatchErr);
   IPP_BADARG_RET(BN_NEGATIVE(pPtxt), ippStsOutOfRangeErr);
   IPP_BADARG_RET(0 <= cpCmp_BNU(BN_NUMBER(pPtxt), BN_SIZE(pPtxt),
                                 MOD_MODULUS(RSA_PUB_KEY_NMONT(pKey)), MOD_LEN(RSA_PUB_KEY_NMONT(pKey))), ippStsOutOfRangeErr);

   IPP_BAD_PTR1_RET(pCtxt);
   IPP_BADARG_RET(!BN_VALID_ID(pCtxt), ippStsContextMatchErr);
   IPP_BADARG_RET(BN_ROOM(pCtxt) < BITS_BNU_CHUNK(RSA_PUB_KEY_BITSIZE_N(pKey)), ippStsSizeErr);

   {
      BNU_CHUNK_T* pScratchBuffer = (BNU_CHUNK_T*)(IPP_ALIGNED_PTR(pBuffer, (int)sizeof(BNU_CHUNK_T)) );
      gsRSApub_cipher(pCtxt, pPtxt, pKey, pScratchBuffer);
      return ippStsNoErr;
   }
}

void gsRSAprv_cipher (IppsBigNumState* pY, const IppsBigNumState* pX, const IppsRSAPrivateKeyState* pKey, BNU_CHUNK_T* pBuffer)
{
   gsMethod_RSA* m = getDefaultMethod_RSA_private(RSA_PRV_KEY_BITSIZE_N(pKey));

   BNU_CHUNK_T* dataY = BN_NUMBER(pY);
   cpSize nsY = m->expFun(dataY,
                          BN_NUMBER(pX), BN_SIZE(pX),
                          RSA_PRV_KEY_D(pKey), RSA_PRV_KEY_BITSIZE_N(pKey),
                          RSA_PRV_KEY_NMONT(pKey),
                          pBuffer);
   FIX_BNU(dataY, nsY);
   BN_SIZE(pY) = nsY;
   BN_SIGN(pY) = ippBigNumPOS;
}

/* CTE version of CRT based RSA decrypt */
void gsRSAprv_cipher_crt (IppsBigNumState* pY, const IppsBigNumState* pX, const IppsRSAPrivateKeyState* pKey, BNU_CHUNK_T* pBuffer)
{
   const BNU_CHUNK_T* dataX = BN_NUMBER(pX);
   cpSize nsX = BN_SIZE(pX);

   BNU_CHUNK_T* dataY = BN_NUMBER(pY);

   BNU_CHUNK_T* dataXp = BN_NUMBER(pY);
   BNU_CHUNK_T* dataXq = BN_BUFFER(pY);

   /* P- and Q- montgometry engines */
   gsModEngine* pMontP = RSA_PRV_KEY_PMONT(pKey);
   gsModEngine* pMontQ = RSA_PRV_KEY_QMONT(pKey);
   cpSize nsP = MOD_LEN(pMontP);
   cpSize nsQ = MOD_LEN(pMontQ);
   cpSize bitSizeP = RSA_PRV_KEY_BITSIZE_P(pKey);
   cpSize bitSizeQ = RSA_PRV_KEY_BITSIZE_Q(pKey);
   cpSize bitSizeDP = bitSizeP; //BITSIZE_BNU(RSA_PRV_KEY_DP(pKey), nsP); /* bitsize of dP exp */
   cpSize bitSizeDQ = bitSizeQ; //BITSIZE_BNU(RSA_PRV_KEY_DQ(pKey), nsQ); /* bitsize of dQ exp */

   /* Prefer dual exponentiation method if available */
   gsMethod_RSA* m = getDualExpMethod_RSA_private(bitSizeDP, bitSizeDQ);
   if (m) {
      ZEXPAND_COPY_BNU(pBuffer, nsQ+nsQ, dataX, nsX);
      MOD_METHOD(pMontQ)->red(dataXq, pBuffer, pMontQ);
      MOD_METHOD(pMontQ)->mul(dataXq, dataXq, MOD_MNT_R2(pMontQ), pMontQ);

      ZEXPAND_COPY_BNU(pBuffer, nsP+nsP, dataX, nsX);
      MOD_METHOD(pMontP)->red(dataXp, pBuffer, pMontP);
      MOD_METHOD(pMontP)->mul(dataXp, dataXp, MOD_MNT_R2(pMontP), pMontP);

      BNU_CHUNK_T* pDataX[2] = {0};
      pDataX[0] = dataXq;
      pDataX[1] = dataXp;

      cpSize pSize[2] = {0};
      pSize[0] = nsQ;
      pSize[1] = nsP;

      BNU_CHUNK_T* pPrvExp[2] = {0};
      pPrvExp[0] = RSA_PRV_KEY_DQ(pKey);
      pPrvExp[1] = RSA_PRV_KEY_DP(pKey);

      gsModEngine* pMont[2] = {0};
      pMont[0] = pMontQ;
      pMont[1] = pMontP;

      m->dualExpFun(pDataX, (const BNU_CHUNK_T**)pDataX, pSize, (const BNU_CHUNK_T**)pPrvExp, pMont, pBuffer);
   } else {
      /* compute xq = x^dQ mod Q */
      if (bitSizeP== bitSizeQ) { /* believe it's enough conditions for correct Mont application */
         ZEXPAND_COPY_BNU(pBuffer, nsQ+nsQ, dataX, nsX);
         MOD_METHOD(pMontQ)->red(dataXq, pBuffer, pMontQ);
         MOD_METHOD(pMontQ)->mul(dataXq, dataXq, MOD_MNT_R2(pMontQ), pMontQ);
      }
      else {
         COPY_BNU(dataXq, dataX, nsX);
         cpMod_BNU(dataXq, nsX, MOD_MODULUS(pMontQ), nsQ);
      }

      m = getDefaultMethod_RSA_private(bitSizeDQ);
      m->expFun(dataXq, dataXq, nsQ, RSA_PRV_KEY_DQ(pKey), bitSizeDQ, pMontQ, pBuffer);

      /* compute xp = x^dP mod P */
      if (bitSizeP== bitSizeQ) { /* believe it's enough conditions for correct Mont application */
         ZEXPAND_COPY_BNU(pBuffer, nsP+nsP, dataX, nsX);
         MOD_METHOD(pMontP)->red(dataXp, pBuffer, pMontP);
         MOD_METHOD(pMontP)->mul(dataXp, dataXp, MOD_MNT_R2(pMontP), pMontP);
      }
      else {
         COPY_BNU(dataXp, dataX, nsX);
         cpMod_BNU(dataXp, nsX, MOD_MODULUS(pMontP), nsP);
      }

      m = getDefaultMethod_RSA_private(bitSizeDP);
      m->expFun(dataXp, dataXp, nsP, RSA_PRV_KEY_DP(pKey), bitSizeDP, pMontP, pBuffer);
   }

   /*
   // recombination
   */
   /* xq = xq mod P
      must be sure that xq in the same residue domain as xp
      because of following (xp-xq) mod P operation
   */
   if (bitSizeP == bitSizeQ) { /* believe it's enough conditions for correct Mont application */
      ZEXPAND_COPY_BNU(pBuffer, nsP+nsP, dataXq, nsQ);
      //MOD_METHOD(pMontP)->red(pBuffer, pBuffer, pMontP);
      //MOD_METHOD(pMontP)->mul(pBuffer, pBuffer, MOD_MNT_R2(pMontP), pMontP);
      MOD_METHOD(pMontP)->sub(pBuffer, pBuffer, MOD_MODULUS(pMontP), pMontP);
      /* xp = (xp - xq) mod P */
      MOD_METHOD(pMontP)->sub(dataXp, dataXp, pBuffer, pMontP);
   }
   else {
      COPY_BNU(pBuffer, dataXq, nsQ);
      {
         cpSize nsQP = cpMod_BNU(pBuffer, nsQ, MOD_MODULUS(pMontP), nsP);
         BNU_CHUNK_T cf = cpSub_BNU(dataXp, dataXp, pBuffer, nsQP);
         if(nsP-nsQP)
            cf = cpDec_BNU(dataXp+nsQP, dataXp + nsQP, (nsP-nsQP), cf);
         if (cf)
            cpAdd_BNU(dataXp, dataXp, MOD_MODULUS(pMontP), nsP);
      }
   }

   /* xp = xp*qInv mod P */
   /* convert invQ into Montgomery domain */
   MOD_METHOD(pMontP)->encode(pBuffer, RSA_PRV_KEY_INVQ(pKey), (gsModEngine*)pMontP);
   /* and multiply xp *= mont(invQ) mod P */
   MOD_METHOD(pMontP)->mul(dataXp, dataXp, pBuffer, pMontP);

   /* Y = xq + xp*Q */
   cpMul_BNU_school(pBuffer, dataXp, nsP, MOD_MODULUS(pMontQ), nsQ);
   {
      BNU_CHUNK_T cf = cpAdd_BNU(dataY, pBuffer, dataXq, nsQ);
      cpInc_BNU(dataY + nsQ, pBuffer + nsQ, nsP, cf);
   }

   nsX = nsP + nsQ;
   FIX_BNU(dataY, nsX);
   BN_SIZE(pY) = nsX;
   BN_SIGN(pY) = ippBigNumPOS;
}

/*F*
// Name: ippsRSA_Decrypt
//
// Purpose: Performs RSA Decryprion
//
// Returns:                   Reason:
//    ippStsNullPtrErr           NULL == pKey
//                               NULL == pCtxt
//                               NULL == pPtxt
//                               NULL == pBuffer
//
//    ippStsContextMatchErr     !RSA_PUB_KEY_VALID_ID()
//                              !BN_VALID_ID(pCtxt)
//                              !BN_VALID_ID(pPtxt)
//
//    ippStsIncompleteContextErr private key is not set up
//
//    ippStsOutOfRangeErr        pCtxt >= modulus
//                               pCtxt <0
//
//    ippStsSizeErr              BN_ROOM(pPtxt) is not enough
//
//    ippStsNoErr                no error
//
// Parameters:
//    pCtxt          pointer to the ciphertext
//    pPtxt          pointer to the plaintext
//    pKey           pointer to the key context
//    pScratchBuffer pointer to the temporary buffer
*F*/
IPPFUN(IppStatus, ippsRSA_Decrypt,(const IppsBigNumState* pCtxt,
                                         IppsBigNumState* pPtxt,
                                   const IppsRSAPrivateKeyState* pKey,
                                         Ipp8u* pBuffer))
{
   IPP_BAD_PTR2_RET(pKey, pBuffer);
   IPP_BADARG_RET(!RSA_PRV_KEY_VALID_ID(pKey), ippStsContextMatchErr);
   IPP_BADARG_RET(!RSA_PRV_KEY_IS_SET(pKey), ippStsIncompleteContextErr);

   IPP_BAD_PTR1_RET(pCtxt);
   IPP_BADARG_RET(!BN_VALID_ID(pCtxt), ippStsContextMatchErr);
   IPP_BADARG_RET(BN_NEGATIVE(pCtxt), ippStsOutOfRangeErr);
   IPP_BADARG_RET(0 <= cpCmp_BNU(BN_NUMBER(pCtxt), BN_SIZE(pCtxt),
                                 MOD_MODULUS(RSA_PRV_KEY_NMONT(pKey)), MOD_LEN(RSA_PRV_KEY_NMONT(pKey))), ippStsOutOfRangeErr);

   IPP_BAD_PTR1_RET(pPtxt);
   IPP_BADARG_RET(!BN_VALID_ID(pPtxt), ippStsContextMatchErr);
   IPP_BADARG_RET(BN_ROOM(pPtxt) < BITS_BNU_CHUNK(RSA_PRV_KEY_BITSIZE_N(pKey)), ippStsSizeErr);

   {
      BNU_CHUNK_T* pScratchBuffer = (BNU_CHUNK_T*)( IPP_ALIGNED_PTR(pBuffer, (int)sizeof(BNU_CHUNK_T)) );

      if(RSA_PRV_KEY1_VALID_ID(pKey))
         gsRSAprv_cipher(pPtxt, pCtxt, pKey, pScratchBuffer);
      else
         gsRSAprv_cipher_crt(pPtxt, pCtxt, pKey, pScratchBuffer);

      return ippStsNoErr;
   }
}
