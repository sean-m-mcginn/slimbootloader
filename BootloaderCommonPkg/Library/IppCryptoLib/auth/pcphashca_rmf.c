/*******************************************************************************
* Copyright 2016-2020 Intel Corporation
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
//     Security Hash Standard
//     Generalized Functionality
//
//  Contents:
//     ippsHashGetSize_rmf()
//     ippsHashInit_rmf()
//     ippsHashPack_rmf()
//     ippsHashUnpack_rmf()
//     ippsHashDuplicate_rmf()
//     ippsHashUpdate_rmf()
//     ippsHashGetTag_rmf()
//     ippsHashFinal_rmf()
//     ippsHashMessage_rmf()
//
*/

#include "owndefs.h"
#include "owncp.h"
#include "pcphash_rmf.h"
#include "pcptool.h"


/*F*
//    Name: ippsHashGetSize_rmf
//
// Purpose: Returns size (bytes) of IppsHashState state.
//
// Returns:                Reason:
//    ippStsNullPtrErr        pSize == NULL
//    ippStsNoErr             no errors
//
// Parameters:
//    pSize       pointer to state size
//
*F*/
IPPFUN(IppStatus, ippsHashGetSize_rmf,(int* pSize))
{
   /* test pointers */
   IPP_BAD_PTR1_RET(pSize);

   *pSize = sizeof(IppsHashState_rmf);

   return ippStsNoErr;
}

/*F*
//    Name: ippsHashInit_rmf
//
// Purpose: Init Hash state.
//
// Returns:                Reason:
//    ippStsNullPtrErr           pState == NULL
//                               pMethod == NULL
//    ippStsNoErr                no errors
//
// Parameters:
//    pState   pointer to the Hash state
//    pMethod  hash method
//
*F*/
IPPFUN(IppStatus, ippsHashInit_rmf,(IppsHashState_rmf* pState, const IppsHashMethod* pMethod))
{
   /* test ctx pointers */
   IPP_BAD_PTR2_RET(pState, pMethod);

   PadBlock(0, pState, sizeof(IppsHashState_rmf));
   HASH_METHOD(pState) = pMethod;
   HASH_SET_ID(pState, idCtxHash);
   pMethod->hashInit(HASH_VALUE(pState));
   return ippStsNoErr;
}

/*F*
//    Name: ippsHashPack_rmf
//
// Purpose: Copy initialized context to the buffer.
//
// Returns:                Reason:
//    ippStsNullPtrErr        pState == NULL
//                            pBuffer == NULL
//    ippStsContextMatchErr   pState->idCtx != idCtxHash
//    ippStsNoMemErr          bufSize < sizeof(IppsHashState_rmf)
//    ippStsNoErr             no errors
//
// Parameters:
//    pState      pointer hash state
//    pBuffer     pointer to the destination buffer
//    bufSize     size of the destination buffer
//
*F*/
IPPFUN(IppStatus, ippsHashPack_rmf,(const IppsHashState_rmf* pState, Ipp8u* pBuffer, int bufSize))
{
   /* test pointers */
   IPP_BAD_PTR2_RET(pState, pBuffer);
   IPP_BADARG_RET(!HASH_VALID_ID(pState, idCtxHash), ippStsContextMatchErr);
   /* test buffer length */
   IPP_BADARG_RET((int)(sizeof(IppsHashState_rmf))>bufSize, ippStsNoMemErr);

   CopyBlock(pState, pBuffer, sizeof(IppsHashState_rmf));
   IppsHashState_rmf* pCopy = (IppsHashState_rmf*)pBuffer;
   HASH_RESET_ID(pCopy, idCtxHash);
   return ippStsNoErr;
}

/*F*
//    Name: ippsHashUnpack_rmf
//
// Purpose: Unpack buffer content into the initialized context.
//
// Returns:                Reason:
//    ippStsNullPtrErr        pBuffer == NULL
//                            pState == NULL
//    ippStsNoErr             no errors
//
// Parameters:
//    pBuffer     pointer to the source buffer
//    pState      pointer hash state
//
*F*/
IPPFUN(IppStatus, ippsHashUnpack_rmf,(const Ipp8u* pBuffer, IppsHashState_rmf* pState))
{
   /* test pointers */
   IPP_BAD_PTR2_RET(pState, pBuffer);

   CopyBlock(pBuffer, pState, sizeof(IppsHashState_rmf));
   HASH_SET_ID(pState, idCtxHash);
   return ippStsNoErr;
}

/*F*
//    Name: ippsHashDuplicate_rmf
//
// Purpose: Clone Hash context.
//
// Returns:                Reason:
//    ippStsNullPtrErr        pSrcState == NULL
//                            pDstState == NULL
//    ippStsContextMatchErr   pSrcState->idCtx != idCtxHash
//                            pDstState->idCtx != idCtxHash
//    ippStsNoErr             no errors
//
// Parameters:
//    pSrcState  pointer to the source Hash context
//    pDstState  pointer to the target Hash context
//
// Note:
//    pDstState may to be uninitialized by ippsHashInit_rmf()
//
*F*/
IPPFUN(IppStatus, ippsHashDuplicate_rmf,(const IppsHashState_rmf* pSrcState, IppsHashState_rmf* pDstState))
{
   /* test state pointers */
   IPP_BAD_PTR2_RET(pSrcState, pDstState);
   /* test states ID */
   IPP_BADARG_RET(!HASH_VALID_ID(pSrcState,idCtxHash), ippStsContextMatchErr);

   /* copy state */
   CopyBlock(pSrcState, pDstState, sizeof(IppsHashState_rmf));
   HASH_SET_ID(pDstState, idCtxHash);

   return ippStsNoErr;
}

/*F*
//    Name: ippsHashUpdate_rmf
//
// Purpose: Updates intermediate hash value based on input stream.
//
// Returns:                   Reason:
//    ippStsNullPtrErr           pState == NULL
//    ippStsNullPtrErr           pSrc==0 but len!=0
//    ippStsContextMatchErr      pState->idCtx != idCtxHash
//    ippStsLengthErr            len <0
//    ippStsNoErr                no errors
//
// Parameters:
//    pSrc     pointer to the input stream
//    len      input stream length
//    pState   pointer to the Hash context
//
*F*/
IPPFUN(IppStatus, ippsHashUpdate_rmf,(const Ipp8u* pSrc, int len, IppsHashState_rmf* pState))
{
   /* test state pointer and ID */
   IPP_BAD_PTR1_RET(pState);
   IPP_BADARG_RET(!HASH_VALID_ID(pState, idCtxHash), ippStsContextMatchErr);

   /* test input length */
   IPP_BADARG_RET((len<0), ippStsLengthErr);
   /* test source pointer */
   IPP_BADARG_RET((len && !pSrc), ippStsNullPtrErr);

   if(len) {
      const IppsHashMethod* method = HASH_METHOD(pState);
      hashUpdateF hashFunc = method->hashUpdate;   /* processing function */
      int msgBlkSize = method->msgBlkSize;         /* messge block size */

      int procLen;

      int idx = HASH_BUFFIDX(pState);
      Ipp64u lenLo = HASH_LENLO(pState);
      Ipp64u lenHi = HASH_LENHI(pState);
      lenLo += (Ipp64u)len;
      if(lenLo < HASH_LENLO(pState)) lenHi++;

      /* if internal buffer is not empty */
      if(idx) {
         procLen = IPP_MIN(len, (msgBlkSize-idx));
         CopyBlock(pSrc, HASH_BUFF(pState)+idx, procLen);
         idx += procLen;

         /* process complete message block  */
         if(msgBlkSize==idx) {
            hashFunc(HASH_VALUE(pState), HASH_BUFF(pState), msgBlkSize);
            idx = 0;
         }

         /* update message pointer and length */
         pSrc += procLen;
         len  -= procLen;
      }

      /* process main part of the input*/
      procLen = len & ~(msgBlkSize-1);
      if(procLen) {
         hashFunc(HASH_VALUE(pState), pSrc, procLen);
         pSrc += procLen;
         len  -= procLen;
      }

      /* store the rest of input in the buffer */
      if(len) {
         CopyBlock(pSrc, HASH_BUFF(pState), len);
         idx += len;
      }

      /* update length of processed message */
      HASH_LENLO(pState) = lenLo;
      HASH_LENHI(pState) = lenHi;
      HASH_BUFFIDX(pState) = idx;
   }

   return ippStsNoErr;
}

void cpFinalize_rmf (DigestSHA512 pHash, const Ipp8u* inpBuffer, int inpLen, Ipp64u lenLo, Ipp64u lenHi, const IppsHashMethod* method)
{
   int mbs = method->msgBlkSize;    /* messge block size */
   int mrl = method->msgLenRepSize; /* processed length representation size */

   /* local buffer and it length */
   Ipp8u buffer[MBS_SHA512*2];
   int bufferLen = inpLen < (mbs-mrl)? mbs : mbs*2; 

   /* copy rest of message into internal buffer */
   CopyBlock(inpBuffer, buffer, inpLen);

   /* padd message */
   buffer[inpLen++] = 0x80;
   PadBlock(0, buffer+inpLen, bufferLen-inpLen-mrl);

   /* message length representation */
   method->msgLenRep(buffer+bufferLen-mrl, lenLo, lenHi);

   /* copmplete hash computation */
   method->hashUpdate(pHash, buffer, bufferLen);
}

/*F*
//    Name: ippsHashFinal_rmf
//
// Purpose: Complete message digesting and return digest.
//
// Returns:                   Reason:
//    ippStsNullPtrErr           pMD == NULL
//                               pState == NULL
//    ippStsContextMatchErr      pState->idCtx != idCtxHash
//    ippStsNoErr                no errors
//
// Parameters:
//    pMD     address of the output digest
//    pState  pointer to the SHS state
//
*F*/
IPPFUN(IppStatus, ippsHashFinal_rmf,(Ipp8u* pMD, IppsHashState_rmf* pState))
{
   /* test state pointer and ID */
   IPP_BAD_PTR2_RET(pMD, pState);
   IPP_BADARG_RET(!HASH_VALID_ID(pState, idCtxHash), ippStsContextMatchErr);

   {
      const IppsHashMethod* method = HASH_METHOD(pState);

      cpFinalize_rmf(HASH_VALUE(pState),
                     HASH_BUFF(pState), HASH_BUFFIDX(pState),
                     HASH_LENLO(pState), HASH_LENHI(pState),
                     method);
      /* convert hash into oct string */
      method->hashOctStr(pMD, HASH_VALUE(pState));

      /* re-init hash value */
      HASH_BUFFIDX(pState) = 0;
      HASH_LENLO(pState) = 0;
      HASH_LENHI(pState) = 0;
      method->hashInit(HASH_VALUE(pState));

      return ippStsNoErr;
   }
}

/*F*
//    Name: ippsHashGetTag_rmf
//
// Purpose: Compute digest based on current state.
//          Note, that futher digest update is possible
//
// Returns:                   Reason:
//    ippStsNullPtrErr           pTag == NULL
//                               pState == NULL
//    ippStsContextMatchErr      pState->idCtx != idCtxHash
//    ippStsLengthErr            hashSize < tagLen <1
//    ippStsNoErr                no errors
//
// Parameters:
//    pTag     address of the output digest
//    tagLen   length of digest
//    pState   pointer to the SHS state
//
*F*/
IPPFUN(IppStatus, ippsHashGetTag_rmf,(Ipp8u* pTag, int tagLen, const IppsHashState_rmf* pState))
{
   /* test state pointer and ID */
   IPP_BAD_PTR1_RET(pState);
   IPP_BADARG_RET(!HASH_VALID_ID(pState, idCtxHash), ippStsContextMatchErr);

   /* test digest pointer */
   IPP_BAD_PTR1_RET(pTag);
   IPP_BADARG_RET((tagLen <1) || HASH_METHOD(pState)->hashLen<tagLen, ippStsLengthErr);

   { /* TBD: consider implementation without copy of internal buffer content */
      DigestSHA512 hash;
      const IppsHashMethod* method = HASH_METHOD(pState);
      CopyBlock(HASH_VALUE(pState), hash, sizeof(DigestSHA512));
      cpFinalize_rmf(hash,
                  HASH_BUFF(pState), HASH_BUFFIDX(pState),
                  HASH_LENLO(pState), HASH_LENHI(pState),
                  method);
      method->hashOctStr(pTag, hash);

      return ippStsNoErr;
   }
}

/*F*
//    Name: ippsHashMessage_rmf
//
// Purpose: Hash of the whole message.
//
// Returns:                Reason:
//    ippStsNullPtrErr           pMD == NULL
//                               pMsg == NULL but len!=0
//    ippStsLengthErr            len <0
//    ippStsNoErr                no errors
//
// Parameters:
//    pMsg        pointer to the input message
//    len         input message length
//    pMD         address of the output digest
//    pMethod     hash methods
//
*F*/
IPPFUN(IppStatus, ippsHashMessage_rmf,(const Ipp8u* pMsg, int len, Ipp8u* pMD, const IppsHashMethod* pMethod))
{
   /* test method pointer */
   IPP_BAD_PTR1_RET(pMethod);
   /* test digest pointer */
   IPP_BAD_PTR1_RET(pMD);
   /* test message length */
   IPP_BADARG_RET(0>len, ippStsLengthErr);
   IPP_BADARG_RET((len && !pMsg), ippStsNullPtrErr);

   {
      /* message length in the multiple MBS and the rest */
      int msgLenBlks = len &(-pMethod->msgBlkSize);
      int msgLenRest = len - msgLenBlks;

      /* init hash */
      DigestSHA512 hash;
      pMethod->hashInit(hash);

      /* process main part of the message */
      if(msgLenBlks) {
         pMethod->hashUpdate(hash, pMsg, msgLenBlks);
         pMsg += msgLenBlks;
      }
      cpFinalize_rmf(hash,
                     pMsg, msgLenRest,
                     (Ipp64u)len, 0,
                     pMethod);

      pMethod->hashOctStr(pMD, hash);

      return ippStsNoErr;
   }
}
