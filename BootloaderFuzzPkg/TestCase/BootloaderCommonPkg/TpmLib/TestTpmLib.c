/** @file

Copyright (c) 2023, Intel Corporation. All rights reserved.<BR>
SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Library/Tpm2DeviceLibStub.h>
#include <IndustryStandard/Tpm20.h>
#include <Library/BaseLib.h>
#include <Library/TpmLib/Tpm2CommandLib.h>

#define TOTAL_SIZE (512 * 1024)

#pragma pack(1)

typedef struct {
  TPM2_RESPONSE_HEADER      Header;
  TPMI_YES_NO               MoreData;
  TPMS_CAPABILITY_DATA      CapabilityData;
} TPM2_GET_CAPABILITY_RESPONSE;

#pragma pack()

VOID
FixBuffer (
  UINT8                   *TestBuffer
  )
{
  TPM2_GET_CAPABILITY_RESPONSE  *Res;

  Res = (VOID *)TestBuffer;
  Res->Header.responseCode = SwapBytes32(TPM_RC_SUCCESS);
  Res->Header.paramSize = SwapBytes32 (sizeof(TPM2_GET_CAPABILITY_RESPONSE));
}

VOID
TestTpm2GetCapabilitySupportedAndActivePcrs (
  VOID
  )
{
  UINT32                    TpmHashAlgorithmBitmap;
  UINT32                    ActivePcrBanks;

  Tpm2GetCapabilitySupportedAndActivePcrs (&TpmHashAlgorithmBitmap, &ActivePcrBanks);
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
EFIAPI
RunTestHarness(
  IN VOID  *TestBuffer,
  IN UINTN TestBufferSize
  )
{
  FixBuffer (TestBuffer);
  Tpm2ResponseInitialize (TestBuffer, TestBufferSize);

  TestTpm2GetCapabilitySupportedAndActivePcrs ();
}
