/** @file
  This library is TPM2 DTPM device lib.
  Choosing this library means platform uses and only uses DTPM device as TPM2 engine.

Copyright (c) 2013 - 2018, Intel Corporation. All rights reserved. <BR>
SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/TpmLib.h>

VOID    *mTpm2TestBuffer;
UINTN   mTpm2TestBufferSize;

/**
  This service enables the sending of commands to the TPM2.

  @param[in]      InputParameterBlockSize  Size of the TPM2 input parameter block.
  @param[in]      InputParameterBlock      Pointer to the TPM2 input parameter block.
  @param[in,out]  OutputParameterBlockSize Size of the TPM2 output parameter block.
  @param[in]      OutputParameterBlock     Pointer to the TPM2 output parameter block.

  @retval EFI_SUCCESS            The command byte stream was successfully sent to the device and a response was successfully received.
  @retval EFI_DEVICE_ERROR       The command was not successfully sent to the device or a response was not successfully received from the device.
  @retval EFI_BUFFER_TOO_SMALL   The output parameter block is too small.
**/
EFI_STATUS
EFIAPI
Tpm2SubmitCommand (
  IN UINT32            InputParameterBlockSize,
  IN UINT8             *InputParameterBlock,
  IN OUT UINT32        *OutputParameterBlockSize,
  IN UINT8             *OutputParameterBlock
  )
{
  if (*OutputParameterBlockSize > mTpm2TestBufferSize) {
    *OutputParameterBlockSize = (UINT32)mTpm2TestBufferSize;
  }
  CopyMem (OutputParameterBlock, mTpm2TestBuffer, *OutputParameterBlockSize);
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
Tpm2ResponseInitialize (
  IN  VOID                   *Buffer,
  IN  UINTN                  BufferSize
  )
{
  mTpm2TestBuffer = Buffer;
  mTpm2TestBufferSize = BufferSize;
  return EFI_SUCCESS;
}
