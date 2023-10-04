/*******************************************************************************
* Copyright 2017-2020 Intel Corporation
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

#if !defined(_GS_MOD_METHOD_H)
#define _GS_MOD_METHOD_H

#include "owncp.h"
#include "pcpbnuimpl.h"

typedef struct _gsModEngine gsEngine;

/* modular arith methods */
typedef BNU_CHUNK_T* (*mod_encode)(BNU_CHUNK_T* pR, const BNU_CHUNK_T* pA, gsEngine* pMA);
typedef BNU_CHUNK_T* (*mod_decode)(BNU_CHUNK_T* pR, const BNU_CHUNK_T* pA, gsEngine* pMA);
typedef BNU_CHUNK_T* (*mod_red)   (BNU_CHUNK_T* pR,       BNU_CHUNK_T* pA, gsEngine* pMA);
typedef BNU_CHUNK_T* (*mod_sqr)   (BNU_CHUNK_T* pR, const BNU_CHUNK_T* pA, gsEngine* pMA);
typedef BNU_CHUNK_T* (*mod_mul)   (BNU_CHUNK_T* pR, const BNU_CHUNK_T* pA, const BNU_CHUNK_T* pB, gsEngine* pMA);
typedef BNU_CHUNK_T* (*mod_add)   (BNU_CHUNK_T* pR, const BNU_CHUNK_T* pA, const BNU_CHUNK_T* pB, gsEngine* pMA);
typedef BNU_CHUNK_T* (*mod_sub)   (BNU_CHUNK_T* pR, const BNU_CHUNK_T* pA, const BNU_CHUNK_T* pB, gsEngine* pMA);
typedef BNU_CHUNK_T* (*mod_neg)   (BNU_CHUNK_T* pR, const BNU_CHUNK_T* pA, gsEngine* pMA);
typedef BNU_CHUNK_T* (*mod_div2)  (BNU_CHUNK_T* pR, const BNU_CHUNK_T* pA, gsEngine* pMA);
typedef BNU_CHUNK_T* (*mod_mul2)  (BNU_CHUNK_T* pR, const BNU_CHUNK_T* pA, gsEngine* pMA);
typedef BNU_CHUNK_T* (*mod_mul3)  (BNU_CHUNK_T* pR, const BNU_CHUNK_T* pA, gsEngine* pMA);

typedef struct _gsModMethod {
   mod_encode encode;
   mod_decode decode;
   mod_mul  mul;
   mod_sqr  sqr;
   mod_red  red;
   mod_add  add;
   mod_sub  sub;
   mod_neg  neg;
   mod_div2 div2;
   mod_mul2 mul2;
   mod_mul3 mul3;
} gsModMethod;

/* common available pre-defined methos */
#define      gsModArith OWNAPI(gsModArith)
gsModMethod* gsModArith(void);

/* available pre-defined methos for RSA */
#define      gsModArithRSA OWNAPI(gsModArithRSA)
gsModMethod* gsModArithRSA(void);

/* available pre-defined methos for ippsMont* */
#define      gsModArithMont OWNAPI(gsModArithMont)
gsModMethod* gsModArithMont(void);

/* available pre-defined methos for DLP * */
#define      gsModArithDLP OWNAPI(gsModArithDLP)
gsModMethod* gsModArithDLP(void);

/* available pre-defined common methos for GF over prime * */
#define      gsArithGFp OWNAPI(gsArithGFp)
gsModMethod* gsArithGFp(void);

/* ... and etc ... */

#endif /* _GS_MOD_METHOD_H */

