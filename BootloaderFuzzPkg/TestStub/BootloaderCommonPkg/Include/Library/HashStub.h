/** @file

Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>
SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#ifndef _HASH_STUB_LIB_H_
#define _HASH_STUB_LIB_H_

#include <Uefi.h>

EFI_STATUS
EFIAPI
Sha256ResponseInitialize (
  IN  VOID                   *Buffer,
  IN  UINTN                  BufferSize
  );

EFI_STATUS
EFIAPI
Sha384ResponseInitialize (
  IN  VOID                   *Buffer,
  IN  UINTN                  BufferSize
  );

EFI_STATUS
EFIAPI
Sm3ResponseInitialize (
  IN  VOID                   *Buffer,
  IN  UINTN                  BufferSize
  );

#endif
