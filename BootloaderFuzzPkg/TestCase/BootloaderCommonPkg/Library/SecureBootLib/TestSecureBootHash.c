/** @file

Copyright (c) 2023, Intel Corporation. All rights reserved.<BR>
SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Library/HashStub.h>
#include <Library/BootloaderCommonStub.h>
#include <Library/BootloaderCommonLib.h>
#include <Library/BaseLib.h>
#include <Guid/KeyHashGuid.h>
#include <Library/BootloaderCoreLib.h>
#include <Library/SecureBootLib.h>

#define TOTAL_SIZE        (512 * 1024)
#define MAX_DIGEST_SIZE   SHA384_DIGEST_SIZE

typedef struct {
  UINT8             Data[100];
  UINT32            Length;
  HASH_COMP_USAGE   Usage;
  UINT8             HashAlg;
} DO_HASH_VERIFY_INPUTS;

#pragma pack(1)

VOID
FixBuffer (
  UINT8                   *TestBuffer
  )
{
}

VOID
TestDoHashVerify (
  DO_HASH_VERIFY_INPUTS* Input
  )
{
  UINT8 Hash[MAX_DIGEST_SIZE];
  DoHashVerify (Input->Data, Input->Length, Input->Usage, Input->HashAlg, (VOID*)Hash);
}

UINTN
EFIAPI
GetMaxBufferSize (
  VOID
  )
{
  return TOTAL_SIZE;
}

VOID
HashResponsesInitialize (
  VOID* Hash
  )
{
  Sha256ResponseInitialize ((VOID *)Hash, SHA256_DIGEST_SIZE);
  Sha384ResponseInitialize ((VOID *)Hash, SHA384_DIGEST_SIZE);
  Sm3ResponseInitialize ((VOID *)Hash, SM3_DIGEST_SIZE);
}

VOID
EFIAPI
RunTestHarness(
  IN VOID  *TestBuffer,
  IN UINTN TestBufferSize
  )
{
  DO_HASH_VERIFY_INPUTS* Input = (DO_HASH_VERIFY_INPUTS*)TestBuffer;
  UINT8 Hash[MAX_DIGEST_SIZE] = {0};

  // Set responses for all hash algorithms
  HashResponsesInitialize (Hash);

  // Set if calculated hash matches stored hash
  MatchHashInStoreResponseInitialize (RETURN_SUCCESS);

  // Run the test
  TestDoHashVerify (Input);
}
