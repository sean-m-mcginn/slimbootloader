/** @file
  Header file for TCO timer library implementation.

  Copyright (c) 2022, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/
#ifndef TCO_TIMER_LIB_H_
#define TCO_TIMER_LIB_H_

/**
  Disable watch dog timer (Initialize TCO timer and halt it).
**/
VOID
EFIAPI
DisableTcoTimer (
  VOID
  );

/**
  Set up watch dog timer (Initialize TCO timer and clear reboot flag).

  @param[in] Timeout    Number of 0.6s ticks to wait
**/
VOID
EFIAPI
SetupTcoTimer (
  IN UINT16 Timeout
  );

/**
  Check if TCO status indicates failure on last boot
**/
BOOLEAN
EFIAPI
WasPreviousTcoTimeout (
  VOID
  );

/**
  Clear TCO status
**/
VOID
EFIAPI
ClearTcoStatus (
  VOID
  );

/**
  Halt the watch dog timer (Halt the TCO timer).
**/
VOID
EFIAPI
HaltTcoTimer (
  VOID
  );

#endif
