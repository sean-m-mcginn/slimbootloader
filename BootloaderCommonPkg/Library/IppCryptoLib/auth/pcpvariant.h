/** @file

  Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/
/* 
//               Intel(R) Integrated Performance Primitives
//                   Cryptographic Primitives (ippcp)
// 
//   Purpose:
//     Define ippCP variant
// 
// 
*/

#if !defined(_CP_VARIANT_H)
#define _CP_VARIANT_H

/*
// set _AES_NI_ENABLING_
*/
#if defined _IPP_AES_NI_
   #if (_IPP_AES_NI_ == 0)
      #define _AES_NI_ENABLING_  _FEATURE_OFF_
   #elif  (_IPP_AES_NI_ == 1)
      #define _AES_NI_ENABLING_  _FEATURE_ON_
   #else
      #error Define _IPP_AES_NI_=0 or 1 or omit _IPP_AES_NI_ at all
   #endif
#else
   #if (_IPP>=_IPP_P8) || (_IPP32E>=_IPP32E_Y8)
      #define _AES_NI_ENABLING_  _FEATURE_TICKTOCK_
   #else
      #define _AES_NI_ENABLING_  _FEATURE_OFF_
   #endif
#endif

/*
// select AES safe implementation
*/
#define _ALG_AES_SAFE_COMPACT_SBOX_ (1)
#define _ALG_AES_SAFE_COMPOSITE_GF_ (2)

#if (_AES_NI_ENABLING_==_FEATURE_ON_)
   #define _ALG_AES_SAFE_   _FEATURE_OFF_
#else
   #if (_IPP>=_IPP_V8) || (_IPP32E>=_IPP32E_U8)
      #define _ALG_AES_SAFE_   _ALG_AES_SAFE_COMPOSITE_GF_
   #else
      #define _ALG_AES_SAFE_   _ALG_AES_SAFE_COMPACT_SBOX_
   #endif
#endif


/*
// set/reset _SHA_NI_ENABLING_
*/
#if (_IPP>=_IPP_P8) || (_IPP32E>=_IPP32E_Y8)
   #if !defined(_SHA_NI_ENABLING_)
      #define _SHA_NI_ENABLING_  _FEATURE_TICKTOCK_
   #endif
#else
   #undef  _SHA_NI_ENABLING_
   #define _SHA_NI_ENABLING_  _FEATURE_OFF_
#endif //lavin test

/*
// set/reset _ADCOX_NI_ENABLING_
*/
#if (_IPP32E>=_IPP32E_L9)
   #if !defined(_ADCOX_NI_ENABLING_)
      #define _ADCOX_NI_ENABLING_  _FEATURE_TICKTOCK_
   #endif
#else
   #undef  _ADCOX_NI_ENABLING_
   #define _ADCOX_NI_ENABLING_  _FEATURE_OFF_
#endif

/*
// IPP supports several hash algorithms by default:
//    SHA-1
//    SHA-256
//    SHA-224  (or SHA256/224 by the FIPS180-4 classification)
//    SHA-512
//    SHA-384  (or SHA512/384 by the FIPS180-4 classification)
//    MD5
//    SM3
//
// By default all hash algorithms are included in IPP Crypto.
//
// If one need excludes code of particular hash, just define
// suitable _DISABLE_ALG_XXX, where XXX name of the hash algorithm
//
*/
#if !defined(_DISABLE_ALG_SHA1_)
#define _ENABLE_ALG_SHA1_          /* SHA1        on  */
#else
#  undef  _ENABLE_ALG_SHA1_        /* SHA1        off */
#endif

#if !defined(_DISABLE_ALG_SHA256_)
#  define _ENABLE_ALG_SHA256_      /* SHA256      on  */
#else
#  undef  _ENABLE_ALG_SHA256_      /* SHA256      off */
#endif

#if !defined(_DISABLE_ALG_SHA224_)
#  define _ENABLE_ALG_SHA224_      /* SHA224      on  */
#else
#  undef  _ENABLE_ALG_SHA224_      /* SHA224      off */
#endif

#if !defined(_DISABLE_ALG_SHA512_)
#  define _ENABLE_ALG_SHA512_      /* SHA512      on  */
#else
#  undef  _ENABLE_ALG_SHA512_      /* SHA512      off */
#endif

#if !defined(_DISABLE_ALG_SHA384_)
#  define _ENABLE_ALG_SHA384_      /* SHA384      on  */
#else
#  undef  _ENABLE_ALG_SHA384_      /* SHA384      off */
#endif

#if !defined(_DISABLE_ALG_SHA512_224_)
#  define _ENABLE_ALG_SHA512_224_  /* SHA512/224  on  */
#else
#  undef  _ENABLE_ALG_SHA512_224_  /* SHA512/224  off */
#endif

#if !defined(_DISABLE_ALG_SHA512_256_)
#  define _ENABLE_ALG_SHA512_256_  /* SHA512/256  on  */
#else
#  undef  _ENABLE_ALG_SHA512_256_  /* SHA512/256  off */
#endif

#if !defined(_DISABLE_ALG_MD5_)
#  define _ENABLE_ALG_MD5_         /* MD5         on  */
#else
#  undef  _ENABLE_ALG_MD5_         /* MD5         off */
#endif

#if !defined(_DISABLE_ALG_SM3_)
#  define _ENABLE_ALG_SM3_         /* SM3         on  */
#else
#  undef  _ENABLE_ALG_SM3_         /* SM3         off */
#endif

/*
// SHA1 plays especial role in IPP. Thus IPP random generator
// and therefore prime number generator are based on SHA1.
// So, do no exclude SHA1 from the active list of hash algorithms
*/
#if defined(_DISABLE_ALG_SHA1_)
#undef _DISABLE_ALG_SHA1_
#endif

/*
// Because of performane reason hash algorithms are implemented in form
// of unroller cycle and therefore these implementations are big enough.
// IPP supports "compact" implementation of some basic hash algorithms:
//    SHA-1
//    SHA-256
//    SHA-512
//    SM3
//
// Define any
//    _ALG_SHA1_COMPACT_
//    _ALG_SHA256_COMPACT_
//    _ALG_SHA512_COMPACT_
//    _ALG_SM3_COMPACT_
//
// to select "compact" implementation of particular hash algorithm.
// IPP does not define "compact" implementation by default.
//
// Don't know what performance degradation leads "compact"
// in comparison with default IPP implementation.
//
// Note: the definition like _ALG_XXX_COMPACT_ has effect
// if and only if IPP instance is _PX or _MX
*/
//#define _ALG_SHA1_COMPACT_
//#define _ALG_SHA256_COMPACT_
//#define _ALG_SHA512_COMPACT_
//#define _ALG_SM3_COMPACT_
//#undef _ALG_SHA1_COMPACT_
//#undef _ALG_SHA256_COMPACT_
//#undef _ALG_SHA512_COMPACT_
//#undef _ALG_SM3_COMPACT_


/*
// BN arithmetic:
//    - do/don't use special implementation of sqr instead of usual multication
//    - do/don't use Karatsuba multiplication alg
*/
#define _USE_SQR_          /*     use implementaton of sqr */
#define xUSE_KARATSUBA_    /* not use Karatsuba method for multiplication */
#if !defined(_DISABLE_WINDOW_EXP_)
   #define _USE_WINDOW_EXP_   /*     use fixed window exponentiation */
#endif

/*
// RSA:
//    - do/don't use Ernie's style mitigation of CBA
//    - do/don't use Gres's  style mitigation of CBA
//    - do/don't use Foldinf technique for RSA-1204 implementation
*/
#define xUSE_ERNIE_CBA_MITIGATION_  /* not use (Ernie) mitigation of CBA */
#define _USE_GRES_CBA_MITIGATION_   /*     use (Gres)  mitigation of CBA */
#define xUSE_FOLD_MONT512_          /*     use foding technique in RSA-1024 case */

#if (_IPP>=_IPP_W7)
#define _RSA_SSE2
#define _RSA_SSE2_PUBLIC_BIN_
#define _xRSA_SSE2_PUBLIC_WIN_
#endif

#if (_IPP32E>=_IPP32E_L9)
#define _RSA_AVX2
#define _xRSA_AVX2_PUBLIC_BIN_
#define _xRSA_AVX2_PUBLIC_WIN_
#endif

#if (_IPP32E>=_IPP32E_K0)
#define _RSA_AVX512
#define _RSA_AVX512_PUBLIC_BIN_
#define _xRSA_AVX512_PUBLIC_WIN_
#endif

/*
// IPP supports different implementation of NIST's (standard) EC over GF(0):
//    P-128 (IppECCPStd128r1, IppECCPStd128r2)
//    P-192 (IppECCPStd192r1)
//    P-224 (IppECCPStd224r1)
//    P-256 (IppECCPStd256r1)
//    P-384 (IppECCPStd384r1)
//    P-521 (IppECCPStd521r1)
//
// If one need replace the particular implementation by abritrary one
// assign _ECP_IMP_ARBIRTRARY_ to suitable symbol
//
// _ECP_IMPL_ARBIRTRARY_   means that implementtaion does not use any curve specific,
//                         provide the same (single) code for any type curve
//
// _ECP_IMPL_SPECIFIC_     means that implementation uses specific modular reduction
//                         based on prime structure;
//                         most of NIST's cures (p128, p192, p224, p256, p384, p521) are uses
//                         such kind of reduction procedure;
//                         in contrast with _ECP_IMPL_ARBIRTRARY_ and _ECP_IMPL_MFM_
//                         this type of implementation uses point representation in REGULAR residual
//                         (not Montgometry!!) domain
//
// _ECP_IMPL_MFM_          means that implementation uses "Montgomary Friendly Modulus" (primes);
//                         p256 and sm2 are using such kind of optimization
*/
#define _ECP_IMPL_NONE_        0
#define _ECP_IMPL_ARBIRTRARY_  1
#define _ECP_IMPL_SPECIFIC_    2
#define _ECP_IMPL_MFM_         3

#if !defined(_ECP_112R1_)
#if !defined(_DISABLE_ECP_112R1_)
#  define _ECP_112R1_    _ECP_IMPL_ARBIRTRARY_
#else
#  define _ECP_112R1_    _ECP_IMPL_NONE_
#endif
#endif

#if !defined(_ECP_112R2_)
#if !defined(_DISABLE_ECP_112R2_)
#  define _ECP_112R2_    _ECP_IMPL_ARBIRTRARY_
#else
#  define _ECP_112R2_    _ECP_IMPL_NONE_
#endif
#endif

#if !defined(_ECP_160R1_)
#if !defined(_DISABLE_ECP_160R1_)
#  define _ECP_160R1_    _ECP_IMPL_ARBIRTRARY_
#else
#  define _ECP_160R1_    _ECP_IMPL_NONE_
#endif
#endif

#if !defined(_ECP_160R2_)
#if !defined(_DISABLE_ECP_160R2_)
#  define _ECP_160R2_    _ECP_IMPL_ARBIRTRARY_
#else
#  define _ECP_160R2_    _ECP_IMPL_NONE_
#endif
#endif

#if !defined(_ECP_128R1_)
#if !defined(_DISABLE_ECP_128R1_)
#  define _ECP_128R1_    _ECP_IMPL_SPECIFIC_
#else
#  define _ECP_128R1_    _ECP_IMPL_NONE_
#endif
#endif

#if !defined(_ECP_128R2_)
#if !defined(_DISABLE_ECP_128R2_)
#  define _ECP_128R2_    _ECP_IMPL_SPECIFIC_
#else
#  define _ECP_128R2_    _ECP_IMPL_NONE_
#endif
#endif

#if !defined(_ECP_192_)
#if !defined(_DISABLE_ECP_192_)
#  if (_IPP32E >= _IPP32E_M7) || (_IPP >= _IPP_P8)
#     define _ECP_192_    _ECP_IMPL_MFM_
#  else
#     define _ECP_192_    _ECP_IMPL_SPECIFIC_
#  endif
#else
#  define _ECP_192_    _ECP_IMPL_NONE_
#endif
#endif

#if !defined(_ECP_224_)
#if !defined(_DISABLE_ECP_224_)
#  if (_IPP32E >= _IPP32E_M7) || (_IPP >= _IPP_P8)
#     define _ECP_224_    _ECP_IMPL_MFM_
#  else
#     define _ECP_224_    _ECP_IMPL_SPECIFIC_
#  endif
#else
#  define _ECP_224_    _ECP_IMPL_NONE_
#endif
#endif

#if !defined(_ECP_256_)
#if !defined(_DISABLE_ECP_256_)
#  if (_IPP32E >= _IPP32E_M7) || (_IPP >= _IPP_P8)
#     define _ECP_256_    _ECP_IMPL_MFM_
#  else
#     define _ECP_256_    _ECP_IMPL_SPECIFIC_
#  endif
#else
#  define _ECP_256_    _ECP_IMPL_NONE_
#endif
#endif

#if !defined(_ECP_384_)
#if !defined(_DISABLE_ECP_384_)
#  if (_IPP32E >= _IPP32E_M7) || (_IPP >= _IPP_P8)
#     define _ECP_384_    _ECP_IMPL_MFM_
#  else
#     define _ECP_384_    _ECP_IMPL_SPECIFIC_
#  endif
#else
#  define _ECP_384_    _ECP_IMPL_NONE_
#endif
#endif

#if !defined(_ECP_521_)
#if !defined(_DISABLE_ECP_521_)
#  if (_IPP32E >= _IPP32E_M7) || (_IPP >= _IPP_P8)
#     define _ECP_521_    _ECP_IMPL_MFM_
#  else
#     define _ECP_521_    _ECP_IMPL_SPECIFIC_
#  endif
#else
#  define _ECP_521_    _ECP_IMPL_NONE_
#endif
#endif

#if !defined(_ECP_SM2_)
#if !defined(_DISABLE_ECP_SM2_)
#  if (_IPP32E >= _IPP32E_M7) || (_IPP >= _IPP_P8)
#     define _ECP_SM2_    _ECP_IMPL_MFM_
#  else
#     define _ECP_SM2_    _ECP_IMPL_SPECIFIC_
#  endif
#else
#  define _ECP_SM2_    _ECP_IMPL_NONE_
#endif
#endif

#if !defined(_ECP_BN_)
#if !defined(_DISABLE_ECP_BN_)
#  define _ECP_BN_    _ECP_IMPL_ARBIRTRARY_
#else
#  define _ECP_BN_    _ECP_IMPL_NONE_
#endif
#endif

#if !defined(_DISABLE_ECP_GENERAL_)
#  define _ECP_GENERAL_ _ECP_IMPL_ARBIRTRARY_
#else
#  define _ECP_GENERAL_ _ECP_IMPL_NONE_
#endif

//#define _ECP_128_    _ECP_IMPL_SPECIFIC_
//#define _ECP_192_    _ECP_IMPL_SPECIFIC_
//#define _ECP_224_    _ECP_IMPL_SPECIFIC_
//#define _ECP_256_    _ECP_IMPL_SPECIFIC_
//#define _ECP_384_    _ECP_IMPL_SPECIFIC_
//#define _ECP_521_    _ECP_IMPL_SPECIFIC_
//#define _ECP_SM2_    _ECP_IMPL_SPECIFIC_

//#if (_IPP32E >= _IPP32E_M7)
//#undef  _ECP_192_
//#undef  _ECP_224_
//#undef  _ECP_256_
//#undef  _ECP_384_
//#undef  _ECP_521_
//#undef  _ECP_SM2_

//#define _ECP_192_    _ECP_IMPL_MFM_
//#define _ECP_224_    _ECP_IMPL_MFM_
//#define _ECP_256_    _ECP_IMPL_MFM_
//#define _ECP_384_    _ECP_IMPL_MFM_
//#define _ECP_521_    _ECP_IMPL_MFM_
//#define _ECP_SM2_    _ECP_IMPL_MFM_
//#endif


/*
// EC over GF(p):
//    - do/don't use mitigation of CBA
*/
#define _USE_ECCP_SSCM_             /*     use SSCM ECCP */


#if defined ( _OPENMP )
#define DEFAULT_CPU_NUM    (8)

#define     BF_MIN_BLK_PER_THREAD (32)
#define     TF_MIN_BLK_PER_THREAD (16)

#define    DES_MIN_BLK_PER_THREAD (32)
#define   TDES_MIN_BLK_PER_THREAD (16)

#define  RC5_64_MIN_BLK_PER_THREAD (16)
#define RC5_128_MIN_BLK_PER_THREAD (32)

#define RIJ128_MIN_BLK_PER_THREAD (32)
#define RIJ192_MIN_BLK_PER_THREAD (16)
#define RIJ256_MIN_BLK_PER_THREAD (16)

#define AESNI128_MIN_BLK_PER_THREAD (256)
#endif

#endif /* _CP_VARIANT_H */
