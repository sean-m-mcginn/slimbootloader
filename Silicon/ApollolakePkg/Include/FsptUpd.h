/** @file

  Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/


#ifndef __FSPTUPD_H__
#define __FSPTUPD_H__

#include <FspUpd.h>

#pragma pack(1)


/** Fsp T Common UPD
**/
typedef struct {

/** Offset 0x0020
**/
  UINT8                       Revision;

/** Offset 0x0021
**/
  UINT8                       Reserved[3];

/** Offset 0x0024
**/
  UINT32                      MicrocodeRegionBase;

/** Offset 0x0028
**/
  UINT32                      MicrocodeRegionLength;

/** Offset 0x002C
**/
  UINT32                      CodeRegionBase;

/** Offset 0x0030
**/
  UINT32                      CodeRegionLength;

/** Offset 0x0034
**/
  UINT8                       Reserved1[12];
} FSPT_COMMON_UPD;

/** Fsp T UPD Configuration
**/
typedef struct {

/** Offset 0x0000
**/
  FSP_UPD_HEADER              FspUpdHeader;

/** Offset 0x0020
**/
  FSPT_COMMON_UPD             FsptCommonUpd;

/** Offset 0x0040
**/
  UINT8                       ReservedFsptUpd1[16];

/** Offset 0x0050
**/
  UINT8                       UnusedUpdSpace0[6];

/** Offset 0x0056
**/
  UINT16                      UpdTerminator;
} FSPT_UPD;

#pragma pack()

#endif
