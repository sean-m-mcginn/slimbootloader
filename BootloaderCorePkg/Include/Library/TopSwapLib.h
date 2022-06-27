/** @file
  Library for Top Swap.

  Copyright (c) 2022, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#ifndef _TOP_SWAP_LIB_H_
#define _TOP_SWAP_LIB_H_

#include <Uefi/UefiBaseType.h>

/**
  TODO: this
**/
EFI_STATUS
EFIAPI
SetTopSwap (
  IN BOOLEAN Val
  );


/**
  TODO: this
**/  
EFI_STATUS
EFIAPI
GetTopSwap (
  OUT BOOLEAN *Val
  );

#endif

