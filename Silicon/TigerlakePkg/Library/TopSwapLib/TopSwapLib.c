/** @file
  Library for Top Swap.

  Copyright (c) 2022, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Library/TopSwapLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/BootloaderCommonLib.h>
#include <Library/PcdLib.h>
#include <Library/BaseLib.h>
#include <PchAccess.h>

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
  UINTN     P2sbBase;
  UINT32    P2sbBar;
  UINT32    TopSwapReg;
  UINT32    Data32;
  BOOLEAN   P2sbIsHidden;

  //
  // Get Top swap register Bit0 in PCH Private Configuration Space.
  //
  P2sbBase   = MM_PCI_ADDRESS (0, PCI_DEVICE_NUMBER_PCH_LPC, 1, 0); // P2SB device base
  P2sbIsHidden = FALSE;

  if (MmioRead16 (P2sbBase) == 0xFFFF) {
    //
    // unhide P2SB
    //
    MmioWrite8 (P2sbBase + 0xE1, 0);
    P2sbIsHidden = TRUE;
    DEBUG ((DEBUG_INFO, "P2sb is hidden, unhide it\n"));
  }

  P2sbBar    = MmioRead32 (P2sbBase + 0x10);
  P2sbBar  &= 0xFFFFFFF0;
  if (P2sbBar != 0xFFFFFFF0) {
    DEBUG ((DEBUG_ERROR, "P2sbBar could not be unhidden!"));
    return EFI_ACCESS_DENIED;
  }

  TopSwapReg = P2sbBar | ((PID_RTC_HOST) << 16) | (UINT16)(R_RTC_PCR_BUC);
  Data32    = MmioRead32 (TopSwapReg);
  DEBUG ((DEBUG_INFO, "P2sbBar=0x%x, Data32=0x%x\n", P2sbBar, Data32));

  if (Val) {
    //
    // Set Top Swap
    //
    Data32 |= BIT0;
  } else {
    //
    // Clear Top Swap
    //
    Data32 &= ~BIT0;
  }

  MmioWrite32 (TopSwapReg, Data32);
  DEBUG ((DEBUG_INFO, "write Data32=0x%x\n", Data32));
  Data32 = MmioRead32 (TopSwapReg);

  if (P2sbIsHidden) {
    //
    // Hide P2SB
    //
    MmioWrite8 (P2sbBase + 0xE1, BIT0);
    DEBUG ((DEBUG_INFO, "Hide p2sb again.\n"));
  }

  DEBUG ((DEBUG_INFO, "Read it to ensure data is written. Data32=0x%x\n", Data32));

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

  UINTN     P2sbBase;
  UINT32    P2sbBar;
  UINT32    TopSwapReg;
  UINT32    Data32;
  BOOLEAN   P2sbIsHidden;

  //
  // Get Top swap register Bit0 in PCH Private Configuration Space.
  //
  P2sbBase   = MM_PCI_ADDRESS (0, PCI_DEVICE_NUMBER_PCH_LPC, 1, 0); // P2SB device base
  P2sbIsHidden = FALSE;

  if (MmioRead16 (P2sbBase) == 0xFFFF) {
    //
    // unhide P2SB
    //
    MmioWrite8 (P2sbBase + 0xE1, 0);
    P2sbIsHidden = TRUE;
    DEBUG ((DEBUG_INFO, "P2sb is hidden, unhide it\n"));
  }

  P2sbBar    = MmioRead32 (P2sbBase + 0x10);
  P2sbBar  &= 0xFFFFFFF0;
  if (P2sbBar != 0xFFFFFFF0) {
    DEBUG ((DEBUG_ERROR, "P2sbBar could not be unhidden!"));
    return EFI_ACCESS_DENIED;
  }

  TopSwapReg = P2sbBar | ((PID_RTC_HOST) << 16) | (UINT16)(R_RTC_PCR_BUC);
  Data32    = MmioRead32 (TopSwapReg);
  DEBUG ((DEBUG_INFO, "P2sbBar=0x%x, Data32=0x%x\n", P2sbBar, Data32));

  if (P2sbIsHidden) {
    //
    // Hide P2SB
    //
    MmioWrite8 (P2sbBase + 0xE1, BIT0);
    DEBUG ((DEBUG_INFO, "Hide p2sb again.\n"));
  }

  DEBUG ((DEBUG_INFO, "Read it to ensure data is written. Data32=0x%x\n", Data32));

  *Val = Data32 & BIT0;

  return EFI_SUCCESS;
}

