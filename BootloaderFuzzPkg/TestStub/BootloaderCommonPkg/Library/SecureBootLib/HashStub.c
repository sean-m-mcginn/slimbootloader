/** @file
  This library is hashing lib.

Copyright (c) 2013 - 2018, Intel Corporation. All rights reserved. <BR>
SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Library/CryptoLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>

VOID    *mSha256Buffer;
UINTN   mSha256BufferSize;
VOID    *mSha384Buffer;
UINTN   mSha384BufferSize;
VOID    *mSm3Buffer;
UINTN   mSm3BufferSize;

/**
  Computes the SHA-256 message digest of a input data buffer.

  This function performs the SHA-256 message digest of a given data buffer, and places
  the digest value into the specified memory.

  @param[in]   Data        Pointer to the buffer containing the data to be hashed.
  @param[in]   Length      Length of Data buffer in bytes.
  @param[out]  Digest      Pointer to a buffer that receives the SHA-256 digest
                           value (32 bytes).

  @retval                  A pointer to SHA-256 digest value
**/
UINT8 *
EFIAPI
Sha256 (
  IN  CONST UINT8          *Data,
  IN        UINT32          Length,
  OUT       UINT8          *Digest
  )
{
  CopyMem (Digest, mSha256Buffer, mSha256BufferSize);
  return mSha256Buffer;
}

/**
  Computes the SHA-384 message digest of a input data buffer.

  This function performs the SHA-384 message digest of a given data buffer, and places
  the digest value into the specified memory.

  @param[in]   Data        Pointer to the buffer containing the data to be hashed.
  @param[in]   Length      Length of Data buffer in bytes.
  @param[out]  Digest      Pointer to a buffer that receives the SHA-384 digest
                           value (32 bytes).

  @retval                  A pointer to SHA-384 digest value
**/
UINT8 *
EFIAPI
Sha384 (
  IN  CONST UINT8          *Data,
  IN        UINT32          Length,
  OUT       UINT8          *Digest
  )
{
  CopyMem (Digest, mSha384Buffer, mSha384BufferSize);
  return mSha384Buffer;
}

/**
  Computes the SM-3 message digest of a input data buffer.

  This function performs the SM-3 message digest of a given data buffer, and places
  the digest value into the specified memory.

  @param[in]   Data        Pointer to the buffer containing the data to be hashed.
  @param[in]   Length      Length of Data buffer in bytes.
  @param[out]  Digest      Pointer to a buffer that receives the SM-3 digest
                           value (32 bytes).

  @retval                  A pointer to SM-3 digest value
**/
UINT8 *
EFIAPI
Sm3 (
  IN  CONST UINT8          *Data,
  IN        UINT32          Length,
  OUT       UINT8          *Digest
  )
{
  CopyMem (Digest, mSm3Buffer, mSm3BufferSize);
  return mSm3Buffer;
}

EFI_STATUS
EFIAPI
Sha256ResponseInitialize (
  IN  VOID                   *Buffer,
  IN  UINTN                  BufferSize
  )
{
  mSha256Buffer = Buffer;
  mSha256BufferSize = BufferSize;
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Sha384ResponseInitialize (
  IN  VOID                   *Buffer,
  IN  UINTN                  BufferSize
  )
{
  mSha384Buffer = Buffer;
  mSha384BufferSize = BufferSize;
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Sm3ResponseInitialize (
  IN  VOID                   *Buffer,
  IN  UINTN                  BufferSize
  )
{
  mSm3Buffer = Buffer;
  mSm3BufferSize = BufferSize;
  return EFI_SUCCESS;
}
