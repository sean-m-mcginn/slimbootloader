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
  Program/enable TCO base address and halt TCO timer
**/
VOID
EFIAPI
InitTcoTimer (
  VOID
  )
{
  // Program TCO base address
  PciWrite32 (PCI_LIB_ADDRESS(0, 31, 4, 0x50), TCO_BASE_ADDRESS);

  // Enable TCO base address
  PciWrite32 (PCI_LIB_ADDRESS(0, 31, 4, 0x54), BIT8);

  HaltTcoTimer ();
}

/**
  Set the TCO timeout and start countdown

  @param[in] Timeout    Number of 0.6s ticks to wait
**/
VOID
EFIAPI
StartTcoTimer (
  IN UINT16 Timeout
  )
{

  // Set the TCO timer to given number of 0.6s ticks
  IoOr16 (TCO_BASE_ADDRESS + 0x12, Timeout);

  // Un-halt the TCO timer
  IoAnd16 (TCO_BASE_ADDRESS + 0x8, (UINT16)~BIT11);

  // Re-start the TCO timer with full timeout
  IoOr16 (TCO_BASE_ADDRESS, BIT0);
}

/**
  Check if TCO status indicates failure on last boot

  @return TRUE if last boot failed
  @return FALSE if last boot succeeded
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
  Halt the TCO timer
**/
VOID
EFIAPI
HaltTcoTimer (
  VOID
  )
{
  IoOr16 (TCO_BASE_ADDRESS + 0x8, BIT11);
}
