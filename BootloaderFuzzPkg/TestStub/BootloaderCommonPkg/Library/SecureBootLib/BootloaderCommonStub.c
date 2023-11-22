/** @file
  This library is bootloader common lib.

Copyright (c) 2013 - 2018, Intel Corporation. All rights reserved. <BR>
SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/BootloaderCommonLib.h>

RETURN_STATUS   mResp;

/**
  Match a given hash with the ones in hash store.

  @param[in]  Usatge      Hash usage.
  @param[in]  HashData    Hash data pointer.
  @param[in]  HashAlg     Hash algorithm.

  @retval RETURN_SUCCESS             Found a match in hash store.
  @retval RETURN_INVALID_PARAMETER   HashData is NULL.
  @retval RETURN_NOT_FOUND           Hash data is not found.

**/
RETURN_STATUS
MatchHashInStore (
  IN       UINT32           Usage,
  IN       UINT8            HashAlg,
  IN       UINT8           *HashData
  )
{
  return mResp;
}

/**
  Dump a binary block using HEX byte format (16 bytes per line).

  @param[in]  Indent      Indent space for each line (16 bytes).
  @param[in]  Offset      Offset from the data buffer pointer.
  @param[in]  DataSize    Data buffer size.
  @param[in]  UserData    Pointer to the data buffer.

**/
VOID
DumpHex (
  IN UINTN        Indent,
  IN UINTN        Offset,
  IN UINTN        DataSize,
  IN VOID         *UserData
  )
{
  // Do nothing
}

/**
  Get the component hash data by the component type.

  @param[in]  ComponentType   Component type.
  @param[out] HashData        Hash data pointer corresponding Component type.
  @param[out] HashAlg         Hash Alg for Hash store.

  @retval RETURN_SUCCESS             Get hash data succeeded.
  @retval RETURN_UNSUPPORTED         Hash component type is not supported.
  @retval RETURN_NOT_FOUND           Hash data is not found.
  @retval RETURN_INVALID_PARAMETER   HashData is NULL.

**/
RETURN_STATUS
GetComponentHash (
  IN        UINT8            ComponentType,
  OUT CONST UINT8            **HashData,
  OUT       UINT8            *HashAlg
  )
{
  // Do nothing
}

EFI_STATUS
EFIAPI
MatchHashInStoreResponseInitialize (
  IN  RETURN_STATUS  Resp
  )
{
  mResp = Resp;
  return EFI_SUCCESS;
}
