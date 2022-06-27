/** @file
  Library for TCO timer.

  Copyright (c) 2022, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Library/TcoTimerLib.h>
#include <Library/BaseLib.h>
#include <Library/PciLib.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <CpuRegsAccess.h>

/**
  Program and enable TCO base address. 
**/
VOID
EFIAPI
SetupTcoBaseAddress (
  VOID
  )
{
  PciWrite32 (PCI_LIB_ADDRESS(0, 31, 4, 0x50), TCO_BASE_ADDRESS);
  PciWrite32 (PCI_LIB_ADDRESS(0, 31, 4, 0x54), BIT8);
}


/**
  Disable watch dog timer (Initialize TCO timer and halt it).
**/
VOID
EFIAPI
DisableTcoTimer (
  VOID
  )
{
  SetupTcoBaseAddress ();

  // Halt the TCO timer.
  IoOr16 (TCO_BASE_ADDRESS + 0x8, BIT11);

}

/**
  Set up watch dog timer (Initialize TCO timer and clear reboot flag).

  @param[in] Timeout    Number of 0.6s ticks to wait
**/
VOID
EFIAPI
SetupTcoTimer (
  IN UINT16 Timeout
  )
{
  SetupTcoBaseAddress ();

  // Set the TCO timer to given number of 0.6s ticks.
  IoOr16 (TCO_BASE_ADDRESS + 0x12, Timeout);

  // Reset the TCO timer.
  IoOr16 (TCO_BASE_ADDRESS, BIT0);

}

/**
  Check if TCO status indicates failure on last boot
**/
BOOLEAN
EFIAPI
WasPreviousTcoTimeout (
  VOID
  )
{
  return IoRead16 (TCO_BASE_ADDRESS + 0x6) & BIT1;
}

/**
  Clear TCO status
**/
VOID
EFIAPI
ClearTcoStatus (
  VOID
  )
{
  IoOr16 (TCO_BASE_ADDRESS + 0x6, BIT1);
}

/**
  Halt the watch dog timer (Halt the TCO timer).
**/
VOID
HaltTcoTimer (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "Halting TCO timer!\n"));
  IoOr16 (TCO_BASE_ADDRESS + 0x8, BIT11);
}