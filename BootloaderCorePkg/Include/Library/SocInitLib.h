/** @file

  Copyright (c) 2016, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#ifndef _SOC_INIT_LIB_H_

/**
  Enables the execution by writing to the MSR.
**/
VOID
EFIAPI
EnableCodeExecution (
  VOID
  );


/**
  Disable watch dog timer (Initialize TCO timer and halt it).
**/
VOID
EFIAPI
DisableWatchDogTimer (
  VOID
  );

/**
  Set up watch dog timer (Initialize TCO timer and clear reboot flag).
**/
VOID
EFIAPI
SetupWatchDogTimer (
  VOID
  );

/**
  Halt the watch dog timer (Halt the TCO timer).
**/
VOID
HaltWatchDogTimer (
  VOID
  );

/**
  Check if TCO status indicates failure on last boot
**/
BOOLEAN
EFIAPI
WasPreviousBootFailure (
  VOID
  );

/**
  Clear TCO status
**/
VOID
EFIAPI
ClearBootStatus (
  VOID
  );

/**
  Get size of global nvs area.

  @param[in] none

  @retval    UINT32     Size of global nvs area.

**/
UINT32
EFIAPI
GetAcpiGnvsSize (
  VOID
  );

/**
 Update GPIO address and length to global NVS data.

 @param [in] GnvsIn Pointer to Global NVS data.
 **/
VOID
EFIAPI
SocUpdateAcpiGnvs (
  IN VOID  *Gnvs
  );

/**
  Update reset reason.
**/
VOID
EFIAPI
UpdateResetReason (
  VOID
  );

/**
 Update memory map related info using SOC registers.

 **/
VOID
EFIAPI
UpdateMemoryInfo (
  VOID
);

#endif
