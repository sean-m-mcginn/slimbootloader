/** @file

Copyright (c) 2023, Intel Corporation. All rights reserved.<BR>
SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Library/Tpm2PtpStub.h>
#include <IndustryStandard/Tpm20.h>
#include <Library/BaseLib.h>
#include <Library/TpmLib/Tpm2CommandLib.h>
#include <Library/BaseMemoryLib.h>

#define TOTAL_SIZE (512 * 1024)

#pragma pack(1)

typedef struct {
  TPM2_COMMAND_HEADER       Header;
  TPMI_RH_HIERARCHY_AUTH    AuthHandle;
  UINT32                    AuthorizationSize;
  TPMS_AUTH_COMMAND         AuthSession;
  TPM2B_AUTH                NewAuth;
} TPM2_HIERARCHY_CHANGE_AUTH_COMMAND;

typedef struct {
  TPM2_RESPONSE_HEADER       Header;
  UINT32                     ParameterSize;
  TPMS_AUTH_RESPONSE         AuthSession;
} TPM2_HIERARCHY_CHANGE_AUTH_RESPONSE;

typedef struct {
  TPM2_COMMAND_HEADER       Header;
  TPMI_RH_HIERARCHY         AuthHandle;
  UINT32                    AuthorizationSize;
  TPMS_AUTH_COMMAND         AuthSession;
  TPMI_RH_HIERARCHY         Hierarchy;
  TPMI_YES_NO               State;
} TPM2_HIERARCHY_CONTROL_COMMAND;

typedef struct {
  TPM2_RESPONSE_HEADER       Header;
  UINT32                     ParameterSize;
  TPMS_AUTH_RESPONSE         AuthSession;
} TPM2_HIERARCHY_CONTROL_RESPONSE;

#pragma pack()

VOID
FixBufferChangeAuth (
  UINT8                   *TestBuffer
  )
{
  TPM2_HIERARCHY_CHANGE_AUTH_RESPONSE  *Res;

  Res = (VOID *)TestBuffer;
  Res->Header.responseCode = SwapBytes32(TPM_RC_SUCCESS);
  Res->Header.paramSize = SwapBytes32 (sizeof(TPM2_HIERARCHY_CHANGE_AUTH_RESPONSE));
}

VOID
FixBufferHierarchyControl (
  UINT8                   *TestBuffer
  )
{
  TPM2_HIERARCHY_CONTROL_RESPONSE  *Res;

  Res = (VOID *)TestBuffer;
  Res->Header.responseCode = SwapBytes32(TPM_RC_SUCCESS);
  Res->Header.paramSize = SwapBytes32 (sizeof(TPM2_HIERARCHY_CONTROL_RESPONSE));
}

VOID
TestTpm2HierarchyChangeAuth (
  VOID
  )
{
  TPM2B_AUTH            NewPlatformAuth;

  ZeroMem(&NewPlatformAuth, sizeof(NewPlatformAuth));
  NewPlatformAuth.size  = SHA384_DIGEST_SIZE;

  Tpm2HierarchyChangeAuth(TPM_RH_PLATFORM, NULL, &NewPlatformAuth);
}

VOID
TestTpm2HierarchyControl (
  VOID
  )
{
  TPMS_AUTH_COMMAND       AuthSession;
  ZeroMem(&AuthSession, sizeof(AuthSession));
  AuthSession.sessionHandle = TPM_RS_PW;

  Tpm2HierarchyControl (TPM_RH_PLATFORM, &AuthSession, TPM_RH_ENDORSEMENT, NO);
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
  FixBufferChangeAuth (TestBuffer);
  Tpm2ResponseInitialize (TestBuffer, TestBufferSize);

  TestTpm2HierarchyChangeAuth ();
}
