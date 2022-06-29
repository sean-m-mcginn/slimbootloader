/** @file
  Library for TCO timer.

  Copyright (c) 2022, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Library/TcoTimerLib.h>

/**
  Program/enable TCO base address and halt TCO timer.
**/
VOID
EFIAPI
DisableTcoTimer (
  VOID
  )
{
}

/**
  Program/enable TCO base address, set the TCO timeout, and restart the TCO timer.

  @param[in] Timeout    Number of 0.6s ticks to wait
**/
VOID
EFIAPI
SetupTcoTimer (
  IN UINT16 Timeout
  )
{
}

/**
  Check if TCO status indicates failure on last boot.

  @return TRUE if last boot failed.
  @return FALSE if last boot succeeded.
**/
BOOLEAN
EFIAPI
WasPreviousTcoTimeout (
  VOID
  )
{
  return FALSE;
}

/**
  Clear TCO status.
**/
VOID
EFIAPI
ClearTcoStatus (
  VOID
  )
{
}

/**
  Halt the TCO timer.
**/
VOID
EFIAPI
HaltTcoTimer (
  VOID
  )
{
}
