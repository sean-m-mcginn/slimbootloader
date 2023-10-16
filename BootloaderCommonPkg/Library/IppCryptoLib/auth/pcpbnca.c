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
//               Intel(R) Integrated Performance Primitives
//                   Cryptographic Primitives (ippcp)
//
//  Contents:
//     ippsBigNumGetSize()
//     ippsBigNumInit()
//
//     ippsSet_BN()
//     ippsGet_BN()
//     ippsGetSize_BN()
//     ippsExtGet_BN()
//     ippsRef_BN()
//
//     ippsCmpZero_BN()
//     ippsCmp_BN()
//
//     ippsAdd_BN()
//     ippsSub_BN()
//     ippsMul_BN()
//     ippsMAC_BN_I()
//     ippsDiv_BN()
//     ippsMod_BN()
//     ippsGcd_BN()
//     ippsModInv_BN()
//
//     cpPackBigNumCtx(), cpUnpackBigNumCtx()
//
//
*/

#include "owndefs.h"
#include "owncp.h"
#include "pcpbn.h"
#include "pcptool.h"

/*F*
//    Name: cpBN_OneRef
//
// Purpose: BN(1) and reference
//
//  Return: 
//      BigNum = 1
*F*/

/* BN(1) and reference */
IppsBigNumState* cpBN_OneRef (void)
{
   static IppsBigNumStateChunk cpChunk_BN1 = {
      {
         idCtxUnknown,
         ippBigNumPOS,
         1,1,
         &cpChunk_BN1.value,&cpChunk_BN1.temporary
      },
      1,0
   };
   BN_SET_ID(&cpChunk_BN1.bn);
   return &cpChunk_BN1.bn;
}

/*F*
//    Name: cpBN_TwoRef
//
// Purpose: BN(2) and reference
//
//  Return:
//      BigNum = 2
*F*/

IppsBigNumState* cpBN_TwoRef (void)
{
   static IppsBigNumStateChunk cpChunk_BN2 = {
      {
         idCtxUnknown,
         ippBigNumPOS,
         1,1,
         &cpChunk_BN2.value,&cpChunk_BN2.temporary
      },
      2,0
   };
   BN_SET_ID(&cpChunk_BN2.bn);
   return &cpChunk_BN2.bn;
}

/*F*
//    Name: cpBN_ThreeRef
//
// Purpose: BN(3) and reference
//
//  Return:
//      BigNum = 3
*F*/

IppsBigNumState* cpBN_ThreeRef (void)
{
   static IppsBigNumStateChunk cpChunk_BN3 = {
      {
         idCtxUnknown,
         ippBigNumPOS,
         1,1,
         &cpChunk_BN3.value,&cpChunk_BN3.temporary
      },
      3,0
   };
   BN_SET_ID(&cpChunk_BN3.bn);
   return &cpChunk_BN3.bn;
}

/*F*
//    Name: ippsBigNumGetSize
//
// Purpose: Returns size of BigNum ctx (bytes).
//
// Returns:                Reason:
//    ippStsNullPtrErr        pCtxSize == NULL
//    ippStsLengthErr         length < 1
//                            length > BITS2WORD32_SIZE(BN_MAXBITSIZE)
//    ippStsNoErr             no errors
//
// Parameters:
//    length  max BN length (32-bits segments)
//    pSize   pointer BigNum ctx size
//
*F*/
IPPFUN(IppStatus, ippsBigNumGetSize, (int length, cpSize *pCtxSize))
{
   IPP_BAD_PTR1_RET(pCtxSize);
   IPP_BADARG_RET(length<1 || length>BITS2WORD32_SIZE(BN_MAXBITSIZE), ippStsLengthErr);

   {
      /* convert length to the number of BNU_CHUNK_T */
      cpSize len = INTERNAL_BNU_LENGTH(length);

      /* reserve one BNU_CHUNK_T more for cpDiv_BNU,
         mul, mont exp operations */
      len++;

      *pCtxSize = (Ipp32s)sizeof(IppsBigNumState)
                + len*(Ipp32s)sizeof(BNU_CHUNK_T)
                + len*(Ipp32s)sizeof(BNU_CHUNK_T)
                + BN_ALIGNMENT-1;

      return ippStsNoErr;
   }
}

/*F*
//    Name: ippsBigNumInit
//
// Purpose: Init BigNum spec for future usage.
//
// Returns:                Reason:
//    ippStsNullPtrErr        pBN == NULL
//    ippStsLengthErr         length<1
//                            length > BITS2WORD32_SIZE(BN_MAXBITSIZE)
//    ippStsNoErr             no errors
//
// Parameters:
//    length    max BN length (32-bits segments)
//    pBN      BigNum ctx
//
*F*/
IPPFUN(IppStatus, ippsBigNumInit, (int length, IppsBigNumState* pBN))
{
    IPP_BADARG_RET(length<1 || length>BITS2WORD32_SIZE(BN_MAXBITSIZE), ippStsLengthErr);
    IPP_BAD_PTR1_RET(pBN);

    {
        Ipp8u* ptr = (Ipp8u*)pBN;

        /* convert length to the number of BNU_CHUNK_T */
        cpSize len = INTERNAL_BNU_LENGTH(length);

        BN_SIGN(pBN) = ippBigNumPOS;
        BN_SIZE(pBN) = 1;     /* initial valie is zero */
        BN_ROOM(pBN) = len;   /* close to what has been passed by user */

                              /* reserve one BNU_CHUNK_T more for cpDiv_BNU,
                              mul, mont exp operations */
        len++;

        ptr += sizeof(IppsBigNumState);

        /* allocate buffers */
        ptr = (Ipp8u*)(IPP_ALIGNED_PTR(ptr, BN_ALIGNMENT));
        BN_NUMBER(pBN) = (BNU_CHUNK_T*)ptr;
        ptr += len * (Ipp32s)sizeof(BNU_CHUNK_T);
        BN_BUFFER(pBN) = (BNU_CHUNK_T*)(ptr); /* use expanded length here */

                                                                           /* set BN value and buffer to zero */
        ZEXPAND_BNU(BN_NUMBER(pBN), 0, len);
        ZEXPAND_BNU(BN_BUFFER(pBN), 0, len);

        BN_SET_ID(pBN);
        return ippStsNoErr;
    }
}

/*F*
//    Name: cpPackBigNumCtx
//
// Purpose: Serialize bigNum context
//
// Parameters:
//    pBN     BigNum
//    pBuffer buffer
*F*/
void cpPackBigNumCtx(const IppsBigNumState* pBN, Ipp8u* pBuffer)
{
IppsBigNumState* pB = (IppsBigNumState*)(pBuffer);
   CopyBlock(pBN, pB, sizeof(IppsBigNumState));

   // TODO: use IPP_INT64
   cpSize dataAlignment = (cpSize)(IPP_INT_PTR(BN_NUMBER(pBN)) - IPP_INT_PTR(pBN) - (__INT64)sizeof(IppsBigNumState));

   BN_NUMBER(pB) = (BNU_CHUNK_T*)((Ipp8u*)NULL + IPP_INT_PTR(BN_NUMBER(pBN))-IPP_INT_PTR(pBN) - dataAlignment);
   BN_BUFFER(pB) = (BNU_CHUNK_T*)((Ipp8u*)NULL + IPP_INT_PTR(BN_BUFFER(pBN))-IPP_INT_PTR(pBN) - dataAlignment);

   CopyBlock(BN_NUMBER(pBN), (Ipp8u*)pB+IPP_UINT_PTR(BN_NUMBER(pB)), BN_ROOM(pBN)*(Ipp32s)sizeof(BNU_CHUNK_T));
   CopyBlock(BN_BUFFER(pBN), (Ipp8u*)pB+IPP_UINT_PTR(BN_BUFFER(pB)), BN_ROOM(pBN)*(Ipp32s)sizeof(BNU_CHUNK_T));
}

/*F*
//    Name: cpUnpackBigNumCtx
//
// Purpose: Deserialize bigNum context
//
// Parameters:
//    pBN     BigNum
//    pBuffer buffer
*F*/
void cpUnpackBigNumCtx(const Ipp8u* pBuffer, IppsBigNumState* pBN)
{
     IppsBigNumState* pB = (IppsBigNumState*)(pBuffer);
   CopyBlock(pBuffer, pBN, sizeof(IppsBigNumState));

   Ipp8u* ptr = (Ipp8u*)pBN;
   ptr += sizeof(IppsBigNumState);
   ptr = IPP_ALIGNED_PTR(ptr, BN_ALIGNMENT);
   BN_NUMBER(pBN) = (BNU_CHUNK_T*)(ptr);
   ptr += BN_ROOM(pBN)*(Ipp32s)sizeof(BNU_CHUNK_T);
   BN_BUFFER(pBN) = (BNU_CHUNK_T*)(ptr);

   cpSize bufferOffset = (cpSize)(IPP_INT_PTR(BN_BUFFER(pBN)) - IPP_INT_PTR(pBN));

   CopyBlock((Ipp8u*)pB+sizeof(IppsBigNumState), BN_NUMBER(pBN), BN_ROOM(pBN)*(Ipp32s)sizeof(BNU_CHUNK_T));
   CopyBlock((Ipp8u*)pB+bufferOffset, BN_BUFFER(pBN), BN_ROOM(pBN)*(Ipp32s)sizeof(BNU_CHUNK_T));
}


/*F*
//    Name: ippsCmpZero_BN
//
// Purpose: Compare BigNum value with zero.
//
// Returns:                Reason:
//    ippStsNullPtrErr        pBN == NULL
//                            pResult == NULL
//    ippStsContextMatchErr   !BN_VALID_ID(pBN)
//    ippStsNoErr             no errors
//
// Parameters:
//    pBN      BigNum ctx
//    pResult  result of comparison
//
*F*/
IPPFUN(IppStatus, ippsCmpZero_BN, (const IppsBigNumState* pBN, Ipp32u* pResult))
{
   IPP_BAD_PTR2_RET(pBN, pResult);

   IPP_BADARG_RET(!BN_VALID_ID(pBN), ippStsContextMatchErr);

   if(BN_SIZE(pBN)==1 && BN_NUMBER(pBN)[0]==0)
      *pResult = IS_ZERO;
   else if (BN_SIGN(pBN)==ippBigNumPOS)
      *pResult = GREATER_THAN_ZERO;
   else if (BN_SIGN(pBN)==ippBigNumNEG)
      *pResult = LESS_THAN_ZERO;

   return ippStsNoErr;
}

/*F*
//    Name: ippsCmp_BN
//
// Purpose: Compare two BigNums.
//
// Returns:                Reason:
//    ippStsNullPtrErr        pA == NULL
//                            pB == NULL
//                            pResult == NULL
//    ippStsContextMatchErr   !BN_VALID_ID(pA)
//                            !BN_VALID_ID(pB)
//    ippStsNoErr             no errors
//
// Parameters:
//    pA       BigNum ctx
//    pB       BigNum ctx
//    pResult  result of comparison
//
*F*/
IPPFUN(IppStatus, ippsCmp_BN,(const IppsBigNumState* pA, const IppsBigNumState* pB, Ipp32u *pResult))
{
   IPP_BAD_PTR3_RET(pA, pB, pResult);

   IPP_BADARG_RET(!BN_VALID_ID(pA), ippStsContextMatchErr);
   IPP_BADARG_RET(!BN_VALID_ID(pB), ippStsContextMatchErr);

   {
      BNU_CHUNK_T positiveA = cpIsEqu_ct(ippBigNumPOS, BN_SIGN(pA));
      BNU_CHUNK_T positiveB = cpIsEqu_ct(ippBigNumPOS, BN_SIGN(pB));
      BNU_CHUNK_T signMask;

      /* (ippBigNumPOS == BN_SIGN(pA)) && (ippBigNumPOS==BN_SIGN(pB))  => res = cpCmp_BNU() */
      BNU_CHUNK_T res  = (BNU_CHUNK_T)( cpCmp_BNU(BN_NUMBER(pA), BN_SIZE(pA), BN_NUMBER(pB), BN_SIZE(pB)) );

      /* (ippBigNumNEG == BN_SIGN(pA)) && (ippBigNumNEG==BN_SIGN(pB))  => invert res value */
      signMask = ~positiveA & ~positiveB;
      res = (res & ~signMask) | ((0-res) & signMask);

      /* (ippBigNumPOS == BN_SIGN(pA)) && (ippBigNumNEG==BN_SIGN(pB))  => res = 1 */
      signMask = positiveA & ~positiveB;
      res = (res & ~signMask) | ((1) & signMask);

      /* (ippBigNumNEG == BN_SIGN(pA)) && (ippBigNumPOS==BN_SIGN(pB))  => res = -1 */
      signMask = ~positiveA & positiveB;
      res = (res & ~signMask) | ((BNU_CHUNK_T)(-1) & signMask);

      // map res into IPP_IS_LT/EQ/GT
      Ipp32u cmpResult = (Ipp32u)( (cpIsEqu_ct(res, (BNU_CHUNK_T)(-1)) & IPP_IS_LT)
                                 | (cpIsEqu_ct(res, (BNU_CHUNK_T)(0))  & IPP_IS_EQ)
                                 | (cpIsEqu_ct(res, (BNU_CHUNK_T)(1))  & IPP_IS_GT) );
      *pResult = cmpResult;

      return ippStsNoErr;
   }
}

/*F*
//    Name: ippsGetSize_BN
//
// Purpose: Returns BigNum room.
//
// Returns:                Reason:
//    ippStsNullPtrErr        pBN == NULL
//                            pSize == NULL
//    ippStsContextMatchErr   !BN_VALID_ID(pBN)
//    ippStsNoErr             no errors
//
// Parameters:
//    pBN      BigNum ctx
//    pSize    max BigNum length (in Ipp32u chunks)
//
*F*/
IPPFUN(IppStatus, ippsGetSize_BN, (const IppsBigNumState* pBN, cpSize* pSize))
{
   IPP_BAD_PTR2_RET(pBN, pSize);

   IPP_BADARG_RET(!BN_VALID_ID(pBN), ippStsContextMatchErr);

   *pSize = BN_ROOM(pBN)*(Ipp32s)(sizeof(BNU_CHUNK_T)/sizeof(Ipp32u));

    return ippStsNoErr;
}


/*F*
//    Name: ippsSet_BN
//
// Purpose: Set BigNum.
//
// Returns:                Reason:
//    ippStsNullPtrErr        pBN == NULL
//                            pData == NULL
//    ippStsContextMatchErr   !BN_VALID_ID(pBN)
//    ippStsLengthErr         length < 1
//    ippStsOutOfRangeErr     length > BN_ROOM(pBN)
//    ippStsNoErr             no errors
//
// Parameters:
//    sgn      sign
//    length   data size (in Ipp32u chunks)
//    pData    source data pointer
//    pBN      BigNum ctx
//
*F*/
IPPFUN(IppStatus, ippsSet_BN, (IppsBigNumSGN sgn, int length, const Ipp32u* pData,
                               IppsBigNumState* pBN))
{
   IPP_BAD_PTR2_RET(pData, pBN);

   IPP_BADARG_RET(!BN_VALID_ID(pBN), ippStsContextMatchErr);

   IPP_BADARG_RET(length<1, ippStsLengthErr);

   /* compute real size */
   FIX_BNU32(pData, length);

   {
      cpSize len = INTERNAL_BNU_LENGTH(length);
      IPP_BADARG_RET(len > BN_ROOM(pBN), ippStsOutOfRangeErr);

      ZEXPAND_COPY_BNU((Ipp32u*)BN_NUMBER(pBN), BN_ROOM(pBN)*(int)(sizeof(BNU_CHUNK_T)/sizeof(Ipp32u)), pData, length);

      BN_SIZE(pBN) = len;

      if(length==1 && pData[0] == 0)
         sgn = ippBigNumPOS;  /* consider zero value as positive */
      BN_SIGN(pBN) = sgn;

      return ippStsNoErr;
   }
}


/*F*
//    Name: ippsGet_BN
//
// Purpose: Get BigNum.
//
// Returns:                   Reason:
//    ippStsNullPtrErr           pBN == NULL
//                               pData == NULL
//                               pSgn == NULL
//                               pLengthInBits ==NULL
//    ippStsContextMatchErr      !BN_VALID_ID(pBN)
//    ippStsNoErr                no errors
//
// Parameters:
//    pSgn            pointer to the sign
//    pLengthInBits   pointer to the data size (in Ipp32u chunks)
//    pData           pointer to the data buffer
//    pBN             BigNum ctx
//
*F*/
IPPFUN(IppStatus, ippsGet_BN, (IppsBigNumSGN* pSgn, int* pLengthInBits, Ipp32u* pData,
                               const IppsBigNumState* pBN))
{
   IPP_BAD_PTR4_RET(pSgn, pLengthInBits, pData, pBN);

   IPP_BADARG_RET(!BN_VALID_ID(pBN), ippStsContextMatchErr);

   {
      cpSize len32 = BN_SIZE(pBN)*(Ipp32s)(sizeof(BNU_CHUNK_T)/sizeof(Ipp32u));
      Ipp32u* bnData = (Ipp32u*)BN_NUMBER(pBN);

      FIX_BNU32(bnData, len32);
      COPY_BNU(pData, bnData, len32);

      *pSgn = BN_SIGN(pBN);
      *pLengthInBits = len32;

      return ippStsNoErr;
   }
}


/*F*
//    Name: ippsRef_BN
//
// Purpose: Get BigNum info.
//
// Returns:                   Reason:
//    ippStsNullPtrErr           pBN == NULL
//    ippStsContextMatchErr      !BN_VALID_ID(pBN)
//    ippStsNoErr                no errors
//
// Parameters:
//    pSgn     pointer to the sign
//    pBitSize pointer to the data size (in bits)
//    ppData   pointer to the data buffer
//    pBN      BigNum ctx
//
*F*/
IPPFUN(IppStatus, ippsRef_BN, (IppsBigNumSGN* pSgn, cpSize* pBitSize, Ipp32u** const ppData,
                               const IppsBigNumState *pBN))
{
   IPP_BAD_PTR1_RET(pBN);

   IPP_BADARG_RET(!BN_VALID_ID(pBN), ippStsContextMatchErr);

   if(pSgn)
      *pSgn = BN_SIGN(pBN);
   if(pBitSize) {
      cpSize bitLen = BITSIZE_BNU(BN_NUMBER(pBN), BN_SIZE(pBN));
      *pBitSize = bitLen? bitLen : 1;
   }

   if(ppData)
      *ppData = (Ipp32u*)BN_NUMBER(pBN);

   return ippStsNoErr;
}

/*F*
//    Name: ippsExtGet_BN
//
// Purpose: Extracts the specified combination of the sign, data
//          length, and value characteristics of the integer big
//          number from the input structure.
//
// Returns:                   Reason:
//    ippStsNullPtrErr           pBN == NULL
//    ippStsContextMatchErr      !BN_VALID_ID(pBN)
//    ippStsNoErr                no errors
//
// Parameters:
//    pSgn     pointer to the sign
//    pBitSize pointer to the data size (in bits)
//    pData    pointer to the data buffer
//    pBN      BigNum ctx
//
*F*/
IPPFUN(IppStatus, ippsExtGet_BN, (IppsBigNumSGN* pSgn, cpSize* pBitSize, Ipp32u* pData,
                               const IppsBigNumState* pBN))
{
   IPP_BAD_PTR1_RET(pBN);

   IPP_BADARG_RET(!BN_VALID_ID(pBN), ippStsContextMatchErr);

   {
      cpSize bitSize = BITSIZE_BNU(BN_NUMBER(pBN), BN_SIZE(pBN));
      if(0==bitSize)
         bitSize = 1;
      if(pData)
         COPY_BNU(pData, (Ipp32u*)BN_NUMBER(pBN), BITS2WORD32_SIZE(bitSize));
      if(pSgn)
         *pSgn = BN_SIGN(pBN);
      if(pBitSize)
         *pBitSize = bitSize;

      return ippStsNoErr;
   }
}


/*F*
//    Name: ippsAdd_BN
//
// Purpose: Add BigNums.
//
// Returns:                Reason:
//    ippStsNullPtrErr        pA  == NULL
//                            pB  == NULL
//                            pR  == NULL
//    ippStsContextMatchErr   !BN_VALID_ID(pA)
//                            !BN_VALID_ID(pB)
//                            !BN_VALID_ID(pR)
//    ippStsOutOfRangeErr     pR can not hold result
//    ippStsNoErr             no errors
//
// Parameters:
//    pA    source BigNum A
//    pB    source BigNum B
//    pR    resultant BigNum
//
*F*/
IPPFUN(IppStatus, ippsAdd_BN, (IppsBigNumState* pA, IppsBigNumState* pB, IppsBigNumState* pR))
{
     IPP_BAD_PTR3_RET(pA, pB, pR);

   IPP_BADARG_RET(!BN_VALID_ID(pA), ippStsContextMatchErr);
   IPP_BADARG_RET(!BN_VALID_ID(pB), ippStsContextMatchErr);
   IPP_BADARG_RET(!BN_VALID_ID(pR), ippStsContextMatchErr);

   {
      cpSize nsA = BN_SIZE(pA);
      cpSize nsB = BN_SIZE(pB);
      cpSize nsR = BN_ROOM(pR);
      IPP_BADARG_RET(nsR < IPP_MAX(nsA, nsB), ippStsOutOfRangeErr);

      {
         BNU_CHUNK_T* pDataR = BN_NUMBER(pR);

         IppsBigNumSGN sgnA = BN_SIGN(pA);
         IppsBigNumSGN sgnB = BN_SIGN(pB);
         BNU_CHUNK_T* pDataA = BN_NUMBER(pA);
         BNU_CHUNK_T* pDataB = BN_NUMBER(pB);

         BNU_CHUNK_T carry;

         if(sgnA==sgnB) {
            if(nsA < nsB) {
               SWAP(nsA, nsB);
               SWAP_PTR(BNU_CHUNK_T, pDataA, pDataB);
            }

            carry = cpAdd_BNU(pDataR, pDataA, pDataB, nsB);
            if(nsA>nsB)
               carry = cpInc_BNU(pDataR+nsB, pDataA+nsB, nsA-nsB, carry);
            if(carry) {
               if(nsR>nsA)
                  pDataR[nsA++] = carry;
               else
                  IPP_ERROR_RET(ippStsOutOfRangeErr);
            }
            BN_SIGN(pR) = sgnA;
         }

         else {
            int cmpRes = cpCmp_BNU(pDataA, nsA, pDataB, nsB);

            if(0==cmpRes) {
               pDataR[0] = 0;
               BN_SIZE(pR) = 1;
               BN_SIGN(pR) = ippBigNumPOS;
               return ippStsNoErr;
            }

            if(0>cmpRes) {
               SWAP(nsA, nsB);
               SWAP_PTR(BNU_CHUNK_T, pDataA, pDataB);
            }

            carry = cpSub_BNU(pDataR, pDataA, pDataB, nsB);
            if(nsA>nsB)
               cpDec_BNU(pDataR+nsB, pDataA+nsB, nsA-nsB, carry);

            BN_SIGN(pR) = cmpRes>0? sgnA : INVERSE_SIGN(sgnA);
         }

         FIX_BNU(pDataR, nsA);
         BN_SIZE(pR) = nsA;

         return ippStsNoErr;
      }
   }
}


/*F*
//    Name: ippsSub_BN
//
// Purpose: Subtract BigNums.
//
// Returns:                Reason:
//    ippStsNullPtrErr        pA  == NULL
//                            pB  == NULL
//                            pR  == NULL
//    ippStsContextMatchErr   !BN_VALID_ID(pA)
//                            !BN_VALID_ID(pB)
//                            !BN_VALID_ID(pR)
//    ippStsOutOfRangeErr     pR can not hold result
//    ippStsNoErr             no errors
//
// Parameters:
//    pA    source BigNum
//    pB    source BigNum
//    pR    resultant BigNum
//
*F*/
IPPFUN(IppStatus, ippsSub_BN, (IppsBigNumState* pA, IppsBigNumState* pB, IppsBigNumState* pR))
{
   IPP_BAD_PTR3_RET(pA, pB, pR);

   IPP_BADARG_RET(!BN_VALID_ID(pA), ippStsContextMatchErr);
   IPP_BADARG_RET(!BN_VALID_ID(pB), ippStsContextMatchErr);
   IPP_BADARG_RET(!BN_VALID_ID(pR), ippStsContextMatchErr);

   {
      cpSize nsA = BN_SIZE(pA);
      cpSize nsB = BN_SIZE(pB);
      cpSize nsR = BN_ROOM(pR);
      IPP_BADARG_RET(nsR < IPP_MAX(nsA, nsB), ippStsOutOfRangeErr);

      {
         BNU_CHUNK_T* pDataR = BN_NUMBER(pR);

         IppsBigNumSGN sgnA = BN_SIGN(pA);
         IppsBigNumSGN sgnB = BN_SIGN(pB);
         BNU_CHUNK_T* pDataA = BN_NUMBER(pA);
         BNU_CHUNK_T* pDataB = BN_NUMBER(pB);

         BNU_CHUNK_T carry;

         if(sgnA!=sgnB) {
            if(nsA < nsB) {
               SWAP(nsA, nsB);
               SWAP_PTR(BNU_CHUNK_T, pDataA, pDataB);
            }

            carry = cpAdd_BNU(pDataR, pDataA, pDataB, nsB);
            if(nsA>nsB)
               carry = cpInc_BNU(pDataR+nsB, pDataA+nsB, nsA-nsB, carry);
            if(carry) {
               if(nsR > nsA)
                  pDataR[nsA++] = carry;
               else
                  IPP_ERROR_RET(ippStsOutOfRangeErr);
            }
            BN_SIGN(pR) = sgnA;
         }

         else {
            int cmpRes= cpCmp_BNU(pDataA, nsA, pDataB, nsB);

            if(0==cmpRes) {
               ZEXPAND_BNU(pDataR,0, nsR);
               BN_SIZE(pR) = 1;
               BN_SIGN(pR) = ippBigNumPOS;
               return ippStsNoErr;
            }

            if(0>cmpRes) {
               SWAP(nsA, nsB);
               SWAP_PTR(BNU_CHUNK_T, pDataA, pDataB);
            }

            carry = cpSub_BNU(pDataR, pDataA, pDataB, nsB);
            if(nsA>nsB)
               cpDec_BNU(pDataR+nsB, pDataA+nsB, nsA-nsB, carry);

            BN_SIGN(pR) = cmpRes>0? sgnA : INVERSE_SIGN(sgnA);
         }

         FIX_BNU(pDataR, nsA);
         BN_SIZE(pR) = nsA;

         return ippStsNoErr;
      }
   }
}


/*F*
//    Name: ippsMul_BN
//
// Purpose: Multiply BigNums.
//
// Returns:                Reason:
//    ippStsNullPtrErr        pA  == NULL
//                            pB  == NULL
//                            pR  == NULL
//    ippStsContextMatchErr   !BN_VALID_ID(pA)
//                            !BN_VALID_ID(pB)
//                            !BN_VALID_ID(pR)
//    ippStsOutOfRangeErr     pR can not hold result
//    ippStsNoErr             no errors
//
// Parameters:
//    pA    source BigNum
//    pB    source BigNum
//    pR    resultant BigNum
//
*F*/
IPPFUN(IppStatus, ippsMul_BN, (IppsBigNumState* pA, IppsBigNumState* pB, IppsBigNumState* pR))
{
   IPP_BAD_PTR3_RET(pA, pB, pR);

   IPP_BADARG_RET(!BN_VALID_ID(pA), ippStsContextMatchErr);
   IPP_BADARG_RET(!BN_VALID_ID(pB), ippStsContextMatchErr);
   IPP_BADARG_RET(!BN_VALID_ID(pR), ippStsContextMatchErr);

   {
      BNU_CHUNK_T* pDataA = BN_NUMBER(pA);
      BNU_CHUNK_T* pDataB = BN_NUMBER(pB);
      BNU_CHUNK_T* pDataR = BN_NUMBER(pR);

      cpSize nsA = BN_SIZE(pA);
      cpSize nsB = BN_SIZE(pB);
      cpSize nsR = BN_ROOM(pR);

      cpSize bitSizeA = BITSIZE_BNU(pDataA, nsA);
      cpSize bitSizeB = BITSIZE_BNU(pDataB, nsB);

      /* test if multiplicant/multiplier is zero */
      if(!bitSizeA || !bitSizeB) {
         BN_SIZE(pR) = 1;
         BN_SIGN(pR) = IppsBigNumPOS;
         pDataR[0] = 0;
         return ippStsNoErr;
      }

      /* test if even low estimation of product A*B exceeded */
      IPP_BADARG_RET(nsR*BNU_CHUNK_BITS < (bitSizeA+bitSizeB-1), ippStsOutOfRangeErr);

      {
         BNU_CHUNK_T* aData = pDataA;
         BNU_CHUNK_T* bData = pDataB;

         if(pA == pR) {
            aData = BN_BUFFER(pR);
            COPY_BNU(aData, pDataA, nsA);
         }
         if((pB == pR) && (pA != pB)) {
            bData = BN_BUFFER(pR);
            COPY_BNU(bData, pDataB, nsB);
         }

         /* clear result */
         ZEXPAND_BNU(pDataR, 0, nsR+1);

         if(pA==pB)
            cpSqr_BNU_school(pDataR, aData, nsA);
         else
            cpMul_BNU_school(pDataR, aData, nsA, bData, nsB);

         nsR = (bitSizeA + bitSizeB + BNU_CHUNK_BITS - 1) /BNU_CHUNK_BITS;
         FIX_BNU(pDataR, nsR);
         IPP_BADARG_RET(nsR>BN_ROOM(pR), ippStsOutOfRangeErr);

         BN_SIZE(pR) = nsR;
         BN_SIGN(pR) = (BN_SIGN(pA)==BN_SIGN(pB)? ippBigNumPOS : ippBigNumNEG);
         return ippStsNoErr;
      }
   }
}

/*F*
//    Name: ippsMAC_BN_I
//
// Purpose: Multiply and Accumulate BigNums.
//
// Returns:                Reason:
//    ippStsNullPtrErr        pA  == NULL
//                            pB  == NULL
//                            pR  == NULL
//    ippStsContextMatchErr   !BN_VALID_ID(pA)
//                            !BN_VALID_ID(pB)
//                            !BN_VALID_ID(pR)
//    ippStsOutOfRangeErr     pR can not fit result
//    ippStsNoErr             no errors
//
// Parameters:
//    pA    source BigNum
//    pB    source BigNum
//    pR    resultant BigNum
//
*F*/
IPPFUN(IppStatus, ippsMAC_BN_I, (IppsBigNumState* pA, IppsBigNumState* pB, IppsBigNumState* pR))
{
   IPP_BAD_PTR3_RET(pA, pB, pR);

   IPP_BADARG_RET(!BN_VALID_ID(pA), ippStsContextMatchErr);
   IPP_BADARG_RET(!BN_VALID_ID(pB), ippStsContextMatchErr);
   IPP_BADARG_RET(!BN_VALID_ID(pR), ippStsContextMatchErr);

   {
      BNU_CHUNK_T* pDataA = BN_NUMBER(pA);
      BNU_CHUNK_T* pDataB = BN_NUMBER(pB);

      cpSize nsA = BN_SIZE(pA);
      cpSize nsB = BN_SIZE(pB);

      cpSize bitSizeA = BITSIZE_BNU(pDataA, nsA);
      cpSize bitSizeB = BITSIZE_BNU(pDataB, nsB);
      /* size of temporary pruduct */
      cpSize nsP = BITS_BNU_CHUNK(bitSizeA+bitSizeB);

      /* test if multiplicant/multiplier is zero */
      if(!bitSizeA || !bitSizeB) return ippStsNoErr;
      /* test if product can't fit to the result */
      IPP_BADARG_RET(BN_ROOM(pR)<nsP, ippStsOutOfRangeErr);

      {
         BNU_CHUNK_T* pDataR  = BN_NUMBER(pR);
         IppsBigNumSGN sgnR = BN_SIGN(pR);
         cpSize nsR = BN_SIZE(pR);
         cpSize room = BN_ROOM(pR);

         /* temporary product */
         BNU_CHUNK_T* pDataP = BN_BUFFER(pR);
         IppsBigNumSGN sgnP = BN_SIGN(pA)==BN_SIGN(pB)? ippBigNumPOS : ippBigNumNEG;

         /* clear the rest of R data buffer */
         ZEXPAND_BNU(pDataR, nsR, room);

         /* temporary product */
         if(pA==pB)
            cpSqr_BNU_school(pDataP, pDataA, nsA);
         else
            cpMul_BNU_school(pDataP, pDataA, nsA, pDataB, nsB);
         /* clear the rest of rpoduct */
         ZEXPAND_BNU(pDataP, nsP, room);

         if(sgnR==sgnP) {
            BNU_CHUNK_T carry = cpAdd_BNU(pDataR, pDataR, pDataP, room);
            if(carry) {
               BN_SIZE(pR) = room;
               IPP_ERROR_RET(ippStsOutOfRangeErr);
            }
         }

         else {
            BNU_CHUNK_T* pTmp = pDataR;
            int cmpRes = cpCmp_BNU(pDataR, room, pDataP, room);
            if(0>cmpRes) {
               SWAP_PTR(BNU_CHUNK_T, pTmp, pDataP);
            }
            cpSub_BNU(pDataR, pTmp, pDataP, room);

            BN_SIGN(pR) = cmpRes>0? sgnR : INVERSE_SIGN(sgnR);
         }

         FIX_BNU(pDataR, room);
         BN_SIZE(pR) = room;

         return ippStsNoErr;
      }
   }
}


/*F*
//    Name: ippsDiv_BN
//
// Purpose: Divide BigNums.
//
// Returns:                Reason:
//    ippStsNullPtrErr        pA  == NULL
//                            pB  == NULL
//                            pQ  == NULL
//                            pR  == NULL
//    ippStsContextMatchErr   !BN_VALID_ID(pA)
//                            !BN_VALID_ID(pB)
//                            !BN_VALID_ID(pQ)
//                            !BN_VALID_ID(pR)
//    ippStsDivByZeroErr      BN_SIZE(pB) == 1 && BN_NUMBER(pB)[0] == 0
//    ippStsOutOfRangeErr     pQ and/or pR can not hold result
//    ippStsNoErr             no errors
//
// Parameters:
//    pA    source BigNum
//    pB    source BigNum
//    pQ    quotient BigNum
//    pR    reminder BigNum
//
//    A = Q*B + R, 0 <= val(R) < val(B), sgn(A)==sgn(R)
//
*F*/
IPPFUN(IppStatus, ippsDiv_BN, (IppsBigNumState* pA, IppsBigNumState* pB, IppsBigNumState* pQ, IppsBigNumState* pR))
{
   IPP_BAD_PTR4_RET(pA, pB, pQ, pR);

   IPP_BADARG_RET(!BN_VALID_ID(pA), ippStsContextMatchErr);
   IPP_BADARG_RET(!BN_VALID_ID(pB), ippStsContextMatchErr);
   IPP_BADARG_RET(!BN_VALID_ID(pQ), ippStsContextMatchErr);
   IPP_BADARG_RET(!BN_VALID_ID(pR), ippStsContextMatchErr);

   IPP_BADARG_RET(BN_SIZE(pB)== 1 && BN_NUMBER(pB)[0]==0, ippStsDivByZeroErr);

   IPP_BADARG_RET(BN_ROOM(pR)<BN_SIZE(pB), ippStsOutOfRangeErr);
   IPP_BADARG_RET((int)BN_ROOM(pQ)<(int)(BN_SIZE(pA)-BN_SIZE(pB)), ippStsOutOfRangeErr);

   {
      BNU_CHUNK_T* pDataA = BN_BUFFER(pA);
      cpSize nsA = BN_SIZE(pA);
      BNU_CHUNK_T* pDataB = BN_NUMBER(pB);
      cpSize nsB = BN_SIZE(pB);
      BNU_CHUNK_T* pDataQ = BN_NUMBER(pQ);
      cpSize nsQ;
      BNU_CHUNK_T* pDataR = BN_NUMBER(pR);
      cpSize nsR;

      COPY_BNU(pDataA, BN_NUMBER(pA), nsA);
      nsR = cpDiv_BNU(pDataQ, &nsQ, pDataA, nsA, pDataB, nsB);
      COPY_BNU(pDataR, pDataA, nsR);

      BN_SIGN(pQ) = BN_SIGN(pA)==BN_SIGN(pB)? ippBigNumPOS : ippBigNumNEG;
      BN_SIZE(pQ) = nsQ;
      if(nsQ==1 && pDataQ[0]==0) BN_SIGN(pQ) = ippBigNumPOS;

      BN_SIGN(pR) = BN_SIGN(pA);
      BN_SIZE(pR) = nsR;
      if(nsR==1 && pDataR[0]==0) BN_SIGN(pR) = ippBigNumPOS;

      return ippStsNoErr;
   }
}


/*F*
//    Name: ippsMod_BN
//
// Purpose: reduction BigNum.
//
// Returns:                Reason:
//    ippStsNullPtrErr        pA  == NULL
//                            pM  == NULL
//                            pR  == NULL
//    ippStsContextMatchErr   !BN_VALID_ID(pA)
//                            !BN_VALID_ID(pM)
//                            !BN_VALID_ID(pR)
//    ippStsOutOfRangeErr     pR can not hold result
//    ippStsBadModulusErr     modulus IppsBigNumState* pM
//                             is not a positive integer
//    ippStsNoErr             no errors
//
// Parameters:
//    pA    source BigNum
//    pB    source BigNum
//    pR    reminder BigNum
//
//    A = Q*M + R, 0 <= R < B
//
*F*/
IPPFUN(IppStatus, ippsMod_BN, (IppsBigNumState* pA, IppsBigNumState* pM, IppsBigNumState* pR))
{
      IPP_BAD_PTR3_RET(pA, pM, pR);

   IPP_BADARG_RET(!BN_VALID_ID(pA), ippStsContextMatchErr);
   IPP_BADARG_RET(!BN_VALID_ID(pM), ippStsContextMatchErr);
   IPP_BADARG_RET(!BN_VALID_ID(pR), ippStsContextMatchErr);

   IPP_BADARG_RET(BN_NEGATIVE(pM), ippStsBadModulusErr);
   IPP_BADARG_RET(BN_SIZE(pM)== 1 && BN_NUMBER(pM)[0]==0, ippStsBadModulusErr);

   IPP_BADARG_RET(BN_ROOM(pR)<BN_SIZE(pM), ippStsOutOfRangeErr);

   if(cpEqu_BNU_CHUNK(BN_NUMBER(pA), BN_SIZE(pA), 0)) {
      BN_SIGN(pR) = ippBigNumPOS;
      BN_SIZE(pR) = 1;
      BN_NUMBER(pR)[0] = 0;
   }

   else {
      BNU_CHUNK_T* pDataM = BN_NUMBER(pM);
      cpSize nsM = BN_SIZE(pM);
      BNU_CHUNK_T* pBuffA = BN_BUFFER(pA);
      cpSize nsA = BN_SIZE(pA);
      BNU_CHUNK_T* pDataR = BN_NUMBER(pR);
      cpSize nsR;

      COPY_BNU(pBuffA, BN_NUMBER(pA), nsA);
      nsR = cpMod_BNU(pBuffA, nsA, pDataM, nsM);

      COPY_BNU(pDataR, pBuffA, nsR);
      BN_SIZE(pR) = nsR;
      BN_SIGN(pR) = ippBigNumPOS;

      if(BN_NEGATIVE(pA) && !(nsR==1 && pDataR[0]==0)) {
         ZEXPAND_BNU(pDataR, nsR, nsM);
         cpSub_BNU(pDataR, pDataM, pDataR, nsM);
         FIX_BNU(pDataR, nsM);
         BN_SIZE(pR) = nsM;
      }
   }

   return ippStsNoErr;
}


/*F*
//    Name: ippsGcd_BN
//
// Purpose: compute GCD value.
//
// Returns:                Reason:
//    ippStsNullPtrErr        pA  == NULL
//                            pB  == NULL
//                            pGCD  == NULL
//    ippStsContextMatchErr   !BN_VALID_ID(pA)
//                            !BN_VALID_ID(pB)
//                            !BN_VALID_ID(pGCD)
//    ippStsBadArgErr         A==B==0
//    ippStsOutOfRangeErr     pGCD can not hold result
//    ippStsNoErr             no errors
//
// Parameters:
//    pA    source BigNum
//    pB    source BigNum
//    pGCD    GCD value
//
*F*/
IPPFUN(IppStatus, ippsGcd_BN, (IppsBigNumState* pA, IppsBigNumState* pB, IppsBigNumState* pGCD))
{
   IPP_BAD_PTR3_RET(pA, pB, pGCD);

   IPP_BADARG_RET(!BN_VALID_ID(pA), ippStsContextMatchErr);
   IPP_BADARG_RET(!BN_VALID_ID(pB), ippStsContextMatchErr);
   IPP_BADARG_RET(!BN_VALID_ID(pGCD), ippStsContextMatchErr);

   IPP_BADARG_RET(BN_ROOM(pGCD) < IPP_MIN(BN_SIZE(pA), BN_SIZE(pB)), ippStsOutOfRangeErr);

   {
      IppsBigNumState* x = pA;
      IppsBigNumState* y = pB;
      IppsBigNumState* g = pGCD;

      int aIsZero = BN_SIZE(pA)==1 && BN_NUMBER(pA)[0]==0;
      int bIsZero = BN_SIZE(pB)==1 && BN_NUMBER(pB)[0]==0;

      if(aIsZero && bIsZero)
         return ippStsBadArgErr;
      if(aIsZero && !bIsZero) {
         COPY_BNU(BN_NUMBER(g), BN_NUMBER(pB), BN_SIZE(pB));
         BN_SIZE(g) = BN_SIZE(pB);
         BN_SIGN(g) = ippBigNumPOS;
         return ippStsNoErr;
      }
      if(bIsZero && !aIsZero) {
         COPY_BNU(BN_NUMBER(g), BN_NUMBER(pA), BN_SIZE(pA));
         BN_SIZE(g) = BN_SIZE(pA);
         BN_SIGN(g) = ippBigNumPOS;
         return ippStsNoErr;
      }

      /*
      // Lehmer's algorithm requres that first number must be greater than second
      // x is the first, y is the second
      */
      {
         int cmpRes = cpCmp_BNU(BN_NUMBER(x), BN_SIZE(x), BN_NUMBER(y), BN_SIZE(y));
         if(0>cmpRes)
            SWAP_PTR(IppsBigNumState, x, y);
         if(0==cmpRes) {
            COPY_BNU(BN_NUMBER(g), BN_NUMBER(x), BN_SIZE(x));
            BN_SIGN(g) = ippBigNumPOS;
            BN_SIZE(g) = BN_SIZE(x);
            return ippStsNoErr;
         }
         if(BN_SIZE(x)==1) {
            BNU_CHUNK_T gcd = cpGcd_BNU(BN_NUMBER(x)[0], BN_NUMBER(y)[0]);
            BN_NUMBER(g)[0] = gcd;
            BN_SIZE(g) = 1;
            return ippStsNoErr;
         }
      }

      {
         Ipp32u* xBuffer = (Ipp32u*)BN_BUFFER(x);
         Ipp32u* yBuffer = (Ipp32u*)BN_BUFFER(y);
         Ipp32u* gBuffer = (Ipp32u*)BN_BUFFER(g);
         Ipp32u* xData = (Ipp32u*)BN_NUMBER(x);
         Ipp32u* yData = (Ipp32u*)BN_NUMBER(y);
         Ipp32u* gData = (Ipp32u*)BN_NUMBER(g);
         cpSize nsXmax = BN_ROOM(x)*((Ipp32s)(sizeof(BNU_CHUNK_T)/sizeof(Ipp32u)));
         cpSize nsYmax = BN_ROOM(y)*((Ipp32s)(sizeof(BNU_CHUNK_T)/sizeof(Ipp32u)));
         cpSize nsGmax = BN_ROOM(g)*((Ipp32s)(sizeof(BNU_CHUNK_T)/sizeof(Ipp32u)));
         cpSize nsX = BN_SIZE(x)*((Ipp32s)(sizeof(BNU_CHUNK_T)/sizeof(Ipp32u)));
         cpSize nsY = BN_SIZE(y)*((Ipp32s)(sizeof(BNU_CHUNK_T)/sizeof(Ipp32u)));

         Ipp32u* T;
         Ipp32u* u;

         FIX_BNU32(xData, nsX);
         FIX_BNU32(yData, nsY);

         /* init buffers */
         ZEXPAND_COPY_BNU(xBuffer, nsXmax, xData, nsX);
         ZEXPAND_COPY_BNU(yBuffer, nsYmax, yData, nsY);

         T = gBuffer;
         u = gData;
         ZEXPAND_BNU(T, 0, nsGmax);
         ZEXPAND_BNU(u, 0, nsGmax);

         while(nsX > (cpSize)(sizeof(BNU_CHUNK_T)/sizeof(Ipp32u))) {
            /* xx and yy is the high-order digits of x and y (yy could be 0) */

            Ipp64u xx = (Ipp64u)(xBuffer[nsX-1]);
            Ipp64u yy = (nsY < nsX)? 0 : (Ipp64u)(yBuffer[nsY-1]);

            Ipp64s AA = 1;
            Ipp64s BB = 0;
            Ipp64s CC = 0;
            Ipp64s DD = 1;
            Ipp64s t;

            while((yy+(Ipp64u)CC)!=0 && (yy+(Ipp64u)DD)!=0) {
#ifdef _SLIMBOOT_OPT
               Ipp64u q  = DivU64x64Remainder ( xx + (Ipp64u)AA ,  yy + (Ipp64u)CC , 0);
               Ipp64u q1 = DivU64x64Remainder ( xx + (Ipp64u)BB ,  yy + (Ipp64u)DD , 0);
#else
                  Ipp64u q  = ( xx + (Ipp64u)AA ) / ( yy + (Ipp64u)CC );
                  Ipp64u q1 = ( xx + (Ipp64u)BB ) / ( yy + (Ipp64u)DD );
#endif
               if(q!=q1)
                  break;
#ifdef _SLIMBOOT_OPT
               t = AA - MultS64x64 ((Ipp64s)q , CC);
#else
                  t = AA - (Ipp64s)q*CC;
#endif
               AA = CC;
               CC = t;
#ifdef _SLIMBOOT_OPT
               t = BB - MultS64x64 ((Ipp64s)q , DD);
#else
               t = BB - (Ipp64s)q*DD;

#endif
               BB = DD;
               DD = t;
#ifdef _SLIMBOOT_OPT
               t = (Ipp64s)(xx - MultU64x64 (q , yy));
#else
               t = (Ipp64s)(xx - q*yy);
#endif
               xx = yy;
               yy = (Ipp64u)t;
            }

            if(BB == 0) {
               /* T = x mod y */
               cpSize nsT = cpMod_BNU32(xBuffer, nsX, yBuffer, nsY);
               ZEXPAND_BNU(T, 0, nsGmax);
               COPY_BNU(T, xBuffer, nsT);
               /* a = b; b = T; */
               ZEXPAND_BNU(xBuffer, 0, nsXmax);
               COPY_BNU(xBuffer, yBuffer, nsY);
               ZEXPAND_BNU(yBuffer, 0, nsYmax);
               COPY_BNU(yBuffer, T, nsY);
            }

            else {
               Ipp32u carry;
               /*
               // T = AA*x + BB*y;
               // u = CC*x + DD*y;
               // b = u; a = T;
               */
               if((AA <= 0)&&(BB>=0)) {
                  Ipp32u a1 = (Ipp32u)(-AA);
                  carry = cpMulDgt_BNU32(T, yBuffer, nsY, (Ipp32u)BB);
                  carry = cpMulDgt_BNU32(u, xBuffer, nsY, a1);
                  /* T = BB*y - AA*x; */
                  carry = cpSub_BNU32(T, T, u, nsY);
               }
               else {
                  if((AA >= 0)&&(BB<=0)) {
                     Ipp32u b1 = (Ipp32u)(-BB);
                     carry = cpMulDgt_BNU32(T, xBuffer, nsY, (Ipp32u)AA);
                     carry = cpMulDgt_BNU32(u, yBuffer, nsY, b1);
                     /* T = AA*x - BB*y; */
                     carry = cpSub_BNU32(T, T, u, nsY);
                  }
                  else {
                     /*AA*BB>=0 */
                     carry = cpMulDgt_BNU32(T, xBuffer, nsY, (Ipp32u)AA);
                     carry = cpMulDgt_BNU32(u, yBuffer, nsY, (Ipp32u)BB);
                     /* T = AA*x + BB*y; */
                     carry = cpAdd_BNU32(T, T, u, nsY);
                  }
               }

               /* Now T is reserved. We use only u for intermediate results. */
               if((CC <= 0)&&(DD>=0)){
                  Ipp32u c1 = (Ipp32u)(-CC);
                  /* u = x*CC; x = u; */
                  carry = cpMulDgt_BNU32(u, xBuffer, nsY, c1);
                  COPY_BNU(xBuffer, u, nsY);
                  /* u = y*DD; */
                  carry = cpMulDgt_BNU32(u, yBuffer, nsY, (Ipp32u)DD);
                  /* u = DD*y - CC*x; */
                  carry = cpSub_BNU32(u, u, xBuffer, nsY);
               }
               else {
                  if((CC >= 0)&&(DD<=0)){
                     Ipp32u d1 = (Ipp32u)(-DD);
                     /* u = y*DD; y = u */
                     carry = cpMulDgt_BNU32(u, yBuffer, nsY, d1);
                     COPY_BNU(yBuffer, u, nsY);
                     /* u = CC*x; */
                     carry = cpMulDgt_BNU32(u, xBuffer, nsY, (Ipp32u)CC);
                     /* u = CC*x - DD*y; */
                     carry = cpSub_BNU32(u, u, yBuffer, nsY);
                  }
                  else {
                     /*CC*DD>=0 */
                     /* y = y*DD */
                     carry = cpMulDgt_BNU32(u,  yBuffer, nsY, (Ipp32u)DD);
                     COPY_BNU(yBuffer, u, nsY);
                     /* u = x*CC */
                     carry = cpMulDgt_BNU32(u, xBuffer, nsY, (Ipp32u)CC);
                     /* u = x*CC + y*DD */
                     carry = cpAdd_BNU32(u, u, yBuffer, nsY);
                  }
               }

               IPP_UNREFERENCED_PARAMETER(carry);

               /* y = u; x = T; */
               COPY_BNU(yBuffer, u, nsY);
               COPY_BNU(xBuffer, T, nsY);
            }

            FIX_BNU32(xBuffer, nsX);
            FIX_BNU32(yBuffer, nsY);

            if (nsY > nsX) {
               SWAP_PTR(IppsBigNumState, x, y);
               SWAP(nsX, nsY);
            }

            if (nsY==1 && yBuffer[nsY-1]==0) {
               /* End evaluation */
               ZEXPAND_BNU(gData, 0, nsGmax);
               COPY_BNU(gData, xBuffer, nsX);
               BN_SIZE(g) = INTERNAL_BNU_LENGTH(nsX);
               BN_SIGN(g) = ippBigNumPOS;
               return ippStsNoErr;
            }
         }

         BN_NUMBER(g)[0] = cpGcd_BNU(((BNU_CHUNK_T*)xBuffer)[0], ((BNU_CHUNK_T*)yBuffer)[0]);
         BN_SIZE(g) = 1;
         BN_SIGN(g) = ippBigNumPOS;
         return ippStsNoErr;
      }
   }
}


/*F*
//    Name: ippsModInv_BN
//
// Purpose: Multiplicative Inversion BigNum.
//
// Returns:                Reason:
//    ippStsNullPtrErr        pA  == NULL
//                            pM  == NULL
//                            pInv  == NULL
//    ippStsContextMatchErr   !BN_VALID_ID(pA)
//                            !BN_VALID_ID(pM)
//                            !BN_VALID_ID(pInv)
//    ippStsBadArgErr         A<=0
//    ippStsBadModulusErr     M<=0
//    ippStsScaleRangeErr     A>=M
//    ippStsOutOfRangeErr     pInv can not hold result
//    ippStsNoErr             no errors
//    ippStsBadModulusErr     inversion not found
//
// Parameters:
//    pA    source (value) BigNum
//    pM    source (modulus) BigNum
//    pInv  result BigNum
//
*F*/
IPPFUN(IppStatus, ippsModInv_BN, (IppsBigNumState* pA, IppsBigNumState* pM, IppsBigNumState* pInv) )
{
   IPP_BAD_PTR3_RET(pA, pM, pInv);

   IPP_BADARG_RET(!BN_VALID_ID(pA), ippStsContextMatchErr);
   IPP_BADARG_RET(!BN_VALID_ID(pM), ippStsContextMatchErr);
   IPP_BADARG_RET(!BN_VALID_ID(pInv), ippStsContextMatchErr);

    IPP_BADARG_RET(BN_ROOM(pInv) < BN_SIZE(pM), ippStsOutOfRangeErr);
    IPP_BADARG_RET(BN_NEGATIVE(pA) || (BN_SIZE(pA)==1 && BN_NUMBER(pA)[0]==0), ippStsBadArgErr);
    IPP_BADARG_RET(BN_NEGATIVE(pM) || (BN_SIZE(pM)==1 && BN_NUMBER(pM)[0]==0), ippStsBadModulusErr);
    IPP_BADARG_RET(cpCmp_BNU(BN_NUMBER(pA), BN_SIZE(pA), BN_NUMBER(pM), BN_SIZE(pM)) >= 0, ippStsScaleRangeErr);

   {
      cpSize nsR = cpModInv_BNU(BN_NUMBER(pInv),
                                BN_NUMBER(pA), BN_SIZE(pA),
                                BN_NUMBER(pM), BN_SIZE(pM),
                                BN_BUFFER(pInv), BN_BUFFER(pA), BN_BUFFER(pM));
      if(nsR) {
         BN_SIGN(pInv) = ippBigNumPOS;
         BN_SIZE(pInv) = nsR;
         return ippStsNoErr;
      }
      else
         return ippStsBadModulusErr;
    }
}

