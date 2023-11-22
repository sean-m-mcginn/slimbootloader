/** @file

Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>
SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#ifndef _BOOTLOADER_COMMON_STUB_LIB_H_
#define _BOOTLOADER_COMMON_STUB_LIB_H_

#include <Uefi.h>

EFI_STATUS
EFIAPI
MatchHashInStoreResponseInitialize (
  IN  RETURN_STATUS  Resp
  );

#endif
