/** @file
  Library for Top Swap.

  Copyright (c) 2022, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Library/TopSwapLib.h>
#include <Library/BaseLib.h>

/**
  Set the top swap bit in the appropriate register.

  @param[in] Val    The value to set the TS bit.

  @retval EFI_SUCCESS             if TS bit set sucessfully.
  @retval Others                  if an error occured when setting TS bit.
**/
EFI_STATUS
EFIAPI
SetTopSwapBit (
  IN BOOLEAN Val
  )
{
  return EFI_SUCCESS;
}

/**
  Get the top swap bit from the appropriate register.

  @param[out] Val    The current value of the TS bit.

  @retval EFI_SUCCESS             if TS bit retrieved successfully.
  @retval Others                  if an error occured when getting TS bit.
**/  
EFI_STATUS
EFIAPI
GetTopSwapBit (
  OUT BOOLEAN *Val
  )
{
  Val = NULL;
  return EFI_SUCCESS;
}

