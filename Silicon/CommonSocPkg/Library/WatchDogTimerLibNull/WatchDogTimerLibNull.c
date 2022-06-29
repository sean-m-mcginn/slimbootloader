/** @file
  Library for watch dog timer.

  Copyright (c) 2021, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/


#include <Library/WatchDogTimerLib.h>

/**
  Get Watchdog Timer address

  @retval UINT32                  Watchdog's address
**/
UINT32
WdtGetAddress (
  VOID
  )
{
  return 0;
}

/**
  Reloads WDT with new timeout value and starts it.

  @param[in] TimeoutValue         Time in seconds before WDT times out. Supported range = 1 - 1024.
  @param[in] Flags                WDT timer flag that indicate the purpose to start the WDT timer.

  @retval EFI_SUCCESS             if everything's OK
  @retval EFI_INVALID_PARAMETER   if TimeoutValue parameter is wrong
**/
EFI_STATUS
EFIAPI
WdtReloadAndStart (
  IN  UINT32  TimeoutValue,
  IN  UINT32  Flags
  )
{
  return EFI_UNSUPPORTED;
}

/**
  Disables WDT timer and cleared the specified WDT timer flag.

  @param[in] Flags                The timer flags will be cleared when disabling the WDT

**/
VOID
EFIAPI
WdtDisable (
  IN  UINT32  Flags
  )
{
}

/**
  Clear WDT flags in scratchpad

  @param[in] Flags             The scratchpad flags that would be cleared.

**/
VOID
EFIAPI
WdtClearScratchpad (
  IN  UINT32  Flags
  )
{
}

/**
  Set WDT flags in scratchpad

  @param[in] Flags             The scratchpad flags that would be set.

**/
VOID
EFIAPI
WdtSetScratchpad (
  IN  UINT32  Flags
  )
{
}

/**
  Get WDT flags in scratchpad

  @param[in] Flags             The scratchpad flags to get.
  @retval UINT32               The flags specified.
**/
UINT32
EFIAPI
WdtGetScratchpad (
  IN  UINT32  Flags
  )
{
  return 0;
}

/**
  Returns if the previous reset is triggered by timer expiration.

  @retval TRUE                    Timer time out
  @retval FALSE                   Timer no time out
**/
UINT8
EFIAPI
IsWdtTimeout (
  VOID
  )
{
  return 0;
}



/**
  Returns if specified timer flag is set.

  @param[in] Flags                The timer flags that would be checked.

  @retval TRUE                    if specified timer flags is set
  @retval FALSE                   if specified timer flags is not set
**/
UINT8
EFIAPI
IsWdtFlagsSet (
  IN  UINT32  Flags
  )
{
  return 0;
}

/**
  Returns WDT enabled/disabled status.

  @retval TRUE                    if WDT is enabled
  @retval FALSE                   if WDT is disabled
**/
UINT8
EFIAPI
IsWdtEnabled (
  VOID
  )
{
  return 0;
}

/**
  Returns WDT locked status.

  @retval TRUE                    if WDT is locked
  @retval FALSE                   if WDT is unlocked
**/
UINT8
EFIAPI
IsWdtLocked (
  VOID
  )
{
  return 0;
}

/**
  Get the number of failed boots.

  @retval UINT32              the number of boots

**/
UINT32
EFIAPI
GetFailedBootCount (
  VOID
  )
{
  return 0;
}

/**
  Increment the number of failed boots.
**/
VOID
EFIAPI
IncrementFailedBootCount (
  VOID
  )
{
}

/**
  Set the number of failed boots to 0.
**/
VOID
EFIAPI
ClearFailedBootCount (
  VOID
  )
{
}
