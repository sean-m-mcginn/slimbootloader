/** @file

  Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/


#ifndef __FSPSUPD_H__
#define __FSPSUPD_H__

#include <FspUpd.h>

#pragma pack(1)


/** Fsp S Configuration
**/
typedef struct {

/** Offset 0x0020 - ActiveProcessorCores
  Number of active cores. 0:Disable(Default), 1:Enable.
**/
  UINT8                       ActiveProcessorCores;

/** Offset 0x0021 - Disable Core1
  Disable/Enable Core1. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       DisableCore1;

/** Offset 0x0022 - Disable Core2
  Disable/Enable Core2. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       DisableCore2;

/** Offset 0x0023 - Disable Core3
  Disable/Enable Core3. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       DisableCore3;

/** Offset 0x0024 - VMX Enable
  Enable or Disable VMX. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       VmxEnable;

/** Offset 0x0025 - Memory region allocation for Processor Trace
  Memory region allocation for Processor Trace, allowed range is from 4K (0x0) to
  128MB (0xF); <b>0xFF: Disable. 0xFF:Disable(Default)
**/
  UINT8                       ProcTraceMemSize;

/** Offset 0x0026 - Enable Processor Trace
  Enable or Disable Processor Trace feature.  0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       ProcTraceEnable;

/** Offset 0x0027 - Eist
  Enable or Disable Intel SpeedStep Technology. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       Eist;

/** Offset 0x0028 - Boot PState
  Boot PState with HFM or LFM. 0:HFM(Default), 1:LFM.
**/
  UINT8                       BootPState;

/** Offset 0x0029 - CPU power states (C-states)
  Enable or Disable CPU power states (C-states). 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       EnableCx;

/** Offset 0x002A - Enhanced C-states
  Enable or Disable Enhanced C-states. 0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       C1e;

/** Offset 0x002B - Bi-Directional PROCHOT#
  Enable or Disable Bi-Directional PROCHOT#. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       BiProcHot;

/** Offset 0x002C - Max Pkg Cstate
  Max Pkg Cstate. 0:PkgC0C1, 1:PkgC2, 2:PkgC3(Default), 3:PkgC6, 4:PkgC7, 5:PkgC7s,
  6:PkgC8, 7:PkgC9, 8:PkgC10, 9:PkgCMax, 254:PkgCpuDefault, 255:PkgAuto.
**/
  UINT8                       PkgCStateLimit;

/** Offset 0x002D - C-State auto-demotion
  C-State Auto Demotion. 0:Disable(Default) C1 and C3 Auto-demotion, 1:Enable C3/C6/C7
  Auto-demotion to C1, 2:Enable C6/C7 Auto-demotion to C3, 3:Enable C6/C7 Auto-demotion
  to C1 and C3.
**/
  UINT8                       CStateAutoDemotion;

/** Offset 0x002E - C-State un-demotion
  C-State un-demotion. 0:Disable(Default) C1 and C3 Un-demotion, 1:Enable C1 Un-demotion,
  2:Enable C3 Un-demotion, 3:Enable C1 and C3 Un-demotion.
**/
  UINT8                       CStateUnDemotion;

/** Offset 0x002F - Max Core C-State
  Max Core C-State. 0:Unlimited, 1:C1, 2:C3, 3:C6, 4:C7, 5:C8, 6:C9, 7:C10, 8:CCx(Default).
**/
  UINT8                       MaxCoreCState;

/** Offset 0x0030 - Package C-State Demotion
  Enable or Disable Package Cstate Demotion. 0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       PkgCStateDemotion;

/** Offset 0x0031 - Package C-State Un-demotion
  Enable or Disable Package Cstate UnDemotion. 0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       PkgCStateUnDemotion;

/** Offset 0x0032 - Turbo Mode
  Enable or Disable long duration Turbo Mode. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       TurboMode;

/** Offset 0x0033 - SC HDA Verb Table Entry Number
  Number of Entries in Verb Table. 0(Default).
**/
  UINT8                       HdaVerbTableEntryNum;

/** Offset 0x0034 - SC HDA Verb Table Pointer
  Pointer to Array of pointers to Verb Table. 0x00000000(Default).
**/
  UINT32                      HdaVerbTablePtr;

/** Offset 0x0038 - Enable/Disable P2SB device hidden.
  Enable/Disable P2SB device hidden. 0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       P2sbUnhide;

/** Offset 0x0039 - IPU Enable/Disable
  Enable/Disable IPU Device. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       IpuEn;

/** Offset 0x003A - IMGU ACPI mode selection
  0:Auto, 1:IGFX Child device(Default), 2:ACPI device.
  0:Disable, 1:IGFX Child device, 2:ACPI device
**/
  UINT8                       IpuAcpiMode;

/** Offset 0x003B - Enable ForceWake
  Enable/disable ForceWake Models. 0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       ForceWake;

/** Offset 0x003C - GttMmAdr
  GttMmAdr structure for initialization. 0xBF000000(Default).
**/
  UINT32                      GttMmAdr;

/** Offset 0x0040 - GmAdr
  GmAdr structure for initialization. 0xA0000000(Default).
**/
  UINT32                      GmAdr;

/** Offset 0x0044 - Enable PavpLock
  Enable/disable PavpLock. 0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       PavpLock;

/** Offset 0x0045 - Enable GraphicsFreqModify
  Enable/disable GraphicsFreqModify. 0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       GraphicsFreqModify;

/** Offset 0x0046 - Enable GraphicsFreqReq
  Enable/disable GraphicsFreqReq. 0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       GraphicsFreqReq;

/** Offset 0x0047 - Enable GraphicsVideoFreq
  Enable/disable GraphicsVideoFreq. 0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       GraphicsVideoFreq;

/** Offset 0x0048 - Enable PmLock
  Enable/disable PmLock. 0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       PmLock;

/** Offset 0x0049 - Enable DopClockGating
  Enable/disable DopClockGating. 0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       DopClockGating;

/** Offset 0x004A - Enable UnsolicitedAttackOverride
  Enable/disable UnsolicitedAttackOverride. 0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       UnsolicitedAttackOverride;

/** Offset 0x004B - Enable WOPCMSupport
  Enable/disable WOPCMSupport. 0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       WOPCMSupport;

/** Offset 0x004C - Enable WOPCMSize
  Enable/disable WOPCMSize. 0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       WOPCMSize;

/** Offset 0x004D - Enable PowerGating
  Enable/disable PowerGating. 0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       PowerGating;

/** Offset 0x004E - Enable UnitLevelClockGating
  Enable/disable UnitLevelClockGating. 0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       UnitLevelClockGating;

/** Offset 0x004F - Enable FastBoot
  Enable/disable FastBoot. 0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       FastBoot;

/** Offset 0x0050 - Enable DynSR
  Enable/disable DynSR. 0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       DynSR;

/** Offset 0x0051 - Enable SaIpuEnable
  Enable/disable SaIpuEnable. 0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       SaIpuEnable;

/** Offset 0x0052 - GT PM Support
  Enable/Disable GT power management support. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       PmSupport;

/** Offset 0x0053 - RC6(Render Standby)
  Enable/Disable render standby support. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       EnableRenderStandby;

/** Offset 0x0054 - BMP Logo Data Size
  BMP logo data buffer size. 0x00000000(Default).
**/
  UINT32                      LogoSize;

/** Offset 0x0058 - BMP Logo Data Pointer
  BMP logo data pointer to a BMP format buffer. 0x00000000(Default).
**/
  UINT32                      LogoPtr;

/** Offset 0x005C - Graphics Configuration Data Pointer
  Graphics configuration data used for initialization. 0x00000000(Default).
**/
  UINT32                      GraphicsConfigPtr;

/** Offset 0x0060 - PAVP Enable
  Enable/Disable Protected Audio Visual Path (PAVP). 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       PavpEnable;

/** Offset 0x0061 - PAVP PR3
  Enable/Disable PAVP PR3 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       PavpPr3;

/** Offset 0x0062 - CdClock Frequency selection
  0:144MHz, 1:288MHz, 2:384MHz, 3:576MHz, 4:624MHz(Default).
  0: 144 MHz, 1: 288 MHz, 2: 384 MHz, 3: 576 MHz, 4: 624 MHz
**/
  UINT8                       CdClock;

/** Offset 0x0063 - Enable/Disable PeiGraphicsPeimInit
  Enable/Disable PeiGraphicsPeimInit 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       PeiGraphicsPeimInit;

/** Offset 0x0064 - Write Protection Support
  Enable/disable Write Protection. 0:Disable, 1:Enable(Default).
**/
  UINT8                       WriteProtectionEnable[5];

/** Offset 0x0069 - Read Protection Support
  Enable/disable Read Protection. 0:Disable, 1:Enable(Default).
**/
  UINT8                       ReadProtectionEnable[5];

/** Offset 0x006E - Protected Range Limitation
  The address of the upper limit of protection, 0x0FFFh(Default).
**/
  UINT16                      ProtectedRangeLimit[5];

/** Offset 0x0078 - Protected Range Base
  The base address of the upper limit of protection. 0x0000(Default).
**/
  UINT16                      ProtectedRangeBase[5];

/** Offset 0x0082 - Enable SC Gaussian Mixture Models
  Enable/disable SC Gaussian Mixture Models. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       Gmm;

/** Offset 0x0083 - GMM Clock Gating - PGCB Clock Trunk
  Enable/disable PGCB Clock Trunk. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       ClkGatingPgcbClkTrunk;

/** Offset 0x0084 - GMM Clock Gating  - Sideband
  Enable/disable Sideband. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       ClkGatingSb;

/** Offset 0x0085 - GMM Clock Gating  - Sideband
  Enable/disable Sideband. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       ClkGatingSbClkTrunk;

/** Offset 0x0086 - GMM Clock Gating  - Sideband Clock Partition
  Enable/disable Sideband Clock Partition. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       ClkGatingSbClkPartition;

/** Offset 0x0087 - GMM Clock Gating  - Core
  Enable/disable Core. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       ClkGatingCore;

/** Offset 0x0088 - GMM Clock Gating  - DMA
  Enable/disable DMA. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       ClkGatingDma;

/** Offset 0x0089 - GMM Clock Gating  - Register Access
  Enable/disable Register Access. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       ClkGatingRegAccess;

/** Offset 0x008A - GMM Clock Gating  - Host
  Enable/disable Host. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       ClkGatingHost;

/** Offset 0x008B - GMM Clock Gating  - Partition
  Enable/disable Partition. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       ClkGatingPartition;

/** Offset 0x008C - Clock Gating  - Trunk
  Enable/disable Trunk. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       ClkGatingTrunk;

/** Offset 0x008D - HD Audio Support
  Enable/disable HDA Audio Feature. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       HdaEnable;

/** Offset 0x008E - HD Audio DSP Support
  Enable/disable HDA Audio DSP Feature. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       DspEnable;

/** Offset 0x008F - Azalia wake-on-ring
  Enable/disable Azalia wake-on-ring. 0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       Pme;

/** Offset 0x0090 - HD-Audio I/O Buffer Ownership
  Set HD-Audio I/O Buffer Ownership. 0:HD-Audio link owns all the I/O buffers(Default)
  0:HD-Audio link owns all the I/O buffers, 1:HD-Audio link owns 4 I/O buffers and
  I2S port owns 4 I/O buffers, 3:I2S port owns all the I/O buffers
**/
  UINT8                       HdAudioIoBufferOwnership;

/** Offset 0x0091 - HD-Audio I/O Buffer Voltage
  HD-Audio I/O Buffer Voltage Mode Selectiton . 0:3.3V(Default), 1:1.8V.
  0: 3.3V, 1: 1.8V
**/
  UINT8                       HdAudioIoBufferVoltage;

/** Offset 0x0092 - HD-Audio Virtual Channel Type
  HD-Audio Virtual Channel Type Selectiton. 0:VC0(Default), 1:VC1.
  0: VC0, 1: VC1
**/
  UINT8                       HdAudioVcType;

/** Offset 0x0093 - HD-Audio Link Frequency
  HD-Audio Virtual Channel Type Selectiton. 0:6MHz(Default), 1:12MHz, 2:24MHz, 3:48MHz,
  4:96MHz, 5:Invalid.
  0: 6MHz, 1: 12MHz, 2: 24MHz, 3: 48MHz, 4: 96MHz, 5: Invalid
**/
  UINT8                       HdAudioLinkFrequency;

/** Offset 0x0094 - HD-Audio iDisp-Link Frequency
  HD-Audio iDisp-Link Frequency Selectiton. 0:6MHz(Default), 1:12MHz, 2:24MHz, 3:48MHz,
  4:96MHz, 5:Invalid.
  0: 6MHz, 1: 12MHz, 2: 24MHz, 3: 48MHz, 4: 96MHz, 5: Invalid
**/
  UINT8                       HdAudioIDispLinkFrequency;

/** Offset 0x0095 - HD-Audio iDisp-Link T-Mode
  HD-Audio iDisp-Link T-Mode Selectiton. 0:2T(Default), 1:1T.
  0: 2T, 1: 1T
**/
  UINT8                       HdAudioIDispLinkTmode;

/** Offset 0x0096 - HD-Audio Disp DMIC
  HD-Audio Disp DMIC Selectiton. 0:Disable, 1:2ch array(Default), 2:4ch array.
  0: Disable, 1: 2ch array, 2: 4ch array
**/
  UINT8                       DspEndpointDmic;

/** Offset 0x0097 - HD-Audio Bluetooth
  Enable/Disable HD-Audio bluetooth. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       DspEndpointBluetooth;

/** Offset 0x0098 - HD-Audio I2S SHK
  Enable/Disable HD-Audio I2S SHK. 0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       DspEndpointI2sSkp;

/** Offset 0x0099 - HD-Audio I2S HP
  Enable/Disable HD-Audio I2S HP. 0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       DspEndpointI2sHp;

/** Offset 0x009A - HD-Audio Controller Power Gating
  Enable/Disable HD-Audio Controller Power Gating. This option is deprecated.
  $EN_DIS
**/
  UINT8                       AudioCtlPwrGate;

/** Offset 0x009B - HD-Audio ADSP Power Gating
  Enable/Disable HD-Audio ADSP Power Gating. This option is deprecated.
  $EN_DIS
**/
  UINT8                       AudioDspPwrGate;

/** Offset 0x009C - HD-Audio CSME Memory Transfers
  Enable/Disable HD-Audio CSME Memory Transfers. 0:VC0(Default), 1:VC2.
  0: VC0, 1: VC2
**/
  UINT8                       Mmt;

/** Offset 0x009D - HD-Audio Host Memory Transfers
  Enable/Disable HD-Audio Host Memory Transfers. 0:VC0(Default), 1:VC2.
  0: VC0, 1: VC2
**/
  UINT8                       Hmt;

/** Offset 0x009E - HD-Audio Power Gating
  Enable/Disable HD-Audio BIOS Configuration Lock Down. 0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       HDAudioPwrGate;

/** Offset 0x009F - HD-Audio Clock Gatingn
  Enable/Disable HD-Audio Clock Gating. 0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       HDAudioClkGate;

/** Offset 0x00A0 - Bitmask of DSP Feature
  Set Bitmask of HD-Audio DSP Feature. 0x00000000(Default).
  [BIT0] - WoV, [BIT1] - BT Sideband, [BIT2] - Codec VAD, [BIT5] - BT Intel HFP, [BIT6]
  - BT Intel A2DP, [BIT7] - DSP based speech pre-processing disabled, [BIT8] - 0:
  Intel WoV, 1: Windows Voice Activation
**/
  UINT32                      DspFeatureMask;

/** Offset 0x00A4 - Bitmask of supported DSP Post-Processing Modules
  Set HD-Audio Bitmask of supported DSP Post-Processing Modules. 0x00000000(Default).
  [BIT0] - WoV, [BIT1] - BT Sideband, [BIT2] - Codec VAD, [BIT5] - BT Intel HFP, [BIT6]
  - BT Intel A2DP, [BIT7] - DSP based speech pre-processing disabled, [BIT8] - 0:
  Intel WoV, 1: Windows Voice Activation
**/
  UINT32                      DspPpModuleMask;

/** Offset 0x00A8 - HD-Audio BIOS Configuration Lock Down
  Enable/Disable HD-Audio BIOS Configuration Lock Down. 0:Disable(Default), 1:Enable.
  This option is deprecated
  $EN_DIS
**/
  UINT8                       BiosCfgLockDown;

/** Offset 0x00A9 - Enable High Precision Timer
  Enable/Disable Hpet. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       Hpet;

/** Offset 0x00AA - Hpet Valid BDF Value
  Enable/Disable Hpet Valid BDF Value. 0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       HpetBdfValid;

/** Offset 0x00AB - Bus Number of Hpet
  Completer ID of Bus Number of Hpet. Default = 0xFA(Default).
**/
  UINT8                       HpetBusNumber;

/** Offset 0x00AC - Device Number of Hpet
  Completer ID of Device Number of Hpet. 0x1F(Default).
**/
  UINT8                       HpetDeviceNumber;

/** Offset 0x00AD - Function Number of Hpet
  Completer ID of Function Number of Hpet. 0x00(Default).
**/
  UINT8                       HpetFunctionNumber;

/** Offset 0x00AE - IoApic Valid BDF Value
  Enable/Disable IoApic Valid BDF Value. 0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       IoApicBdfValid;

/** Offset 0x00AF - Bus Number of IoApic
  Completer ID of Bus Number of IoApic. 0xFA(Default).
**/
  UINT8                       IoApicBusNumber;

/** Offset 0x00B0 - Device Number of IoApic
  Completer ID of Device Number of IoApic. 0x0F(Default).
**/
  UINT8                       IoApicDeviceNumber;

/** Offset 0x00B1 - Function Number of IoApic
  Completer ID of Function Number of IoApic. 0x00(Default).
**/
  UINT8                       IoApicFunctionNumber;

/** Offset 0x00B2 - IOAPIC Entry 24-119
  Enable/Disable IOAPIC Entry 24-119. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       IoApicEntry24_119;

/** Offset 0x00B3 - IO APIC ID
  This member determines IOAPIC ID. 0x01(Default).
**/
  UINT8                       IoApicId;

/** Offset 0x00B4 - IoApic Range
  Define address bits 19:12 for the IOxAPIC range. 0x00(Default).
**/
  UINT8                       IoApicRangeSelect;

/** Offset 0x00B5 - ISH Controller
  Enable/Disable ISH Controller. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       IshEnable;

/** Offset 0x00B6 - BIOS Interface Lock Down
  Enable/Disable BIOS Interface Lock Down bit to prevent writes to the Backup Control
  Register. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       BiosInterface;

/** Offset 0x00B7 - Bios LockDown Enable
  Enable the BIOS Lock Enable (BLE) feature and set EISS bit. 0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       BiosLock;

/** Offset 0x00B8 - SPI EISS Status
  Enable/Disable InSMM.STS (EISS) in SPI. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       SpiEiss;

/** Offset 0x00B9 - BiosLock SWSMI Number
  This member describes the SwSmi value for Bios Lock. 0xA9(Default).
**/
  UINT8                       BiosLockSwSmiNumber;

/** Offset 0x00BA - LPSS IOSF PMCTL S0ix Enable
  Enable/Disable LPSS IOSF Bridge PMCTL Register S0ix Bits. 0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       LPSS_S0ixEnable;

/** Offset 0x00BB
**/
  UINT8                       UnusedUpdSpace0[1];

/** Offset 0x00BC - LPSS I2C Clock Gating Configuration
  Enable/Disable LPSS I2C Clock Gating. 0:Disable, 1:Enable(Default).
**/
  UINT8                       I2cClkGateCfg[8];

/** Offset 0x00C4 - PSS HSUART Clock Gating Configuration
  Enable/Disable LPSS HSUART Clock Gating. 0:Disable, 1:Enable(Default).
**/
  UINT8                       HsuartClkGateCfg[4];

/** Offset 0x00C8 - LPSS SPI Clock Gating Configuration
  Enable/Disable LPSS SPI Clock Gating. 0:Disable, 1:Enable(Default).
**/
  UINT8                       SpiClkGateCfg[3];

/** Offset 0x00CB - I2C Device 0
  Enable/Disable I2C Device 0. 0:Disabled, 1:PCI Mode(Default), 2:ACPI Mode.
  0: Disabled, 1: PCI Mode, 2: ACPI Mode
**/
  UINT8                       I2c0Enable;

/** Offset 0x00CC - I2C Device 1
  Enable/Disable I2C Device 1. 0:Disabled, 1:PCI Mode(Default), 2:ACPI Mode.
  0: Disabled, 1: PCI Mode, 2: ACPI Mode
**/
  UINT8                       I2c1Enable;

/** Offset 0x00CD - I2C Device 2
  Enable/Disable I2C Device 2. 0:Disabled, 1:PCI Mode(Default), 2:ACPI Mode.
  0: Disabled, 1: PCI Mode, 2: ACPI Mode
**/
  UINT8                       I2c2Enable;

/** Offset 0x00CE - I2C Device 3
  Enable/Disable I2C Device 3. 0:Disabled, 1:PCI Mode(Default), 2:ACPI Mode.
  0: Disabled, 1: PCI Mode, 2: ACPI Mode
**/
  UINT8                       I2c3Enable;

/** Offset 0x00CF - I2C Device 4
  Enable/Disable I2C Device 4. 0:Disabled, 1:PCI Mode(Default), 2:ACPI Mode.
  0: Disabled, 1: PCI Mode, 2: ACPI Mode
**/
  UINT8                       I2c4Enable;

/** Offset 0x00D0 - I2C Device 5
  Enable/Disable I2C Device 5. 0:Disabled, 1:PCI Mode(Default), 2:ACPI Mode.
  0: Disabled, 1: PCI Mode, 2: ACPI Mode
**/
  UINT8                       I2c5Enable;

/** Offset 0x00D1 - I2C Device 6
  Enable/Disable I2C Device 6. 0:Disabled, 1:PCI Mode(Default), 2:ACPI Mode.
  0: Disabled, 1: PCI Mode, 2: ACPI Mode
**/
  UINT8                       I2c6Enable;

/** Offset 0x00D2 - I2C Device 7
  Enable/Disable I2C Device 7. 0:Disabled, 1:PCI Mode(Default), 2:ACPI Mode.
  0: Disabled, 1: PCI Mode, 2: ACPI Mode
**/
  UINT8                       I2c7Enable;

/** Offset 0x00D3 - UART Device 0
  Enable/Disable UART Device 0. 0:Disabled, 1:PCI Mode(Default), 2:ACPI Mode.
  0: Disabled, 1: PCI Mode, 2: ACPI Mode
**/
  UINT8                       Hsuart0Enable;

/** Offset 0x00D4 - UART Device 1
  Enable/Disable UART Device 1. 0:Disabled, 1:PCI Mode(Default), 2:ACPI Mode.
  0: Disabled, 1: PCI Mode, 2: ACPI Mode
**/
  UINT8                       Hsuart1Enable;

/** Offset 0x00D5 - UART Device 2
  Enable/Disable UART Device 2. 0:Disabled, 1:PCI Mode(Default), 2:ACPI Mode.
  0: Disabled, 1: PCI Mode, 2: ACPI Mode
**/
  UINT8                       Hsuart2Enable;

/** Offset 0x00D6 - UART Device 3
  Enable/Disable UART Device 3. 0:Disabled, 1:PCI Mode(Default), 2:ACPI Mode.
  0: Disabled, 1: PCI Mode, 2: ACPI Mode
**/
  UINT8                       Hsuart3Enable;

/** Offset 0x00D7 - SPI UART Device 0
  Enable/Disable SPI Device 0. 0:Disabled, 1:PCI Mode(Default), 2:ACPI Mode.
  0: Disabled, 1: PCI Mode, 2: ACPI Mode
**/
  UINT8                       Spi0Enable;

/** Offset 0x00D8 - SPI UART Device 1
  Enable/Disable SPI Device 1. 0:Disabled, 1:PCI Mode(Default), 2:ACPI Mode.
  0: Disabled, 1: PCI Mode, 2: ACPI Mode
**/
  UINT8                       Spi1Enable;

/** Offset 0x00D9 - SPI UART Device 2
  Enable/Disable SPI Device 2. 0:Disabled, 1:PCI Mode(Default), 2:ACPI Mode.
  0: Disabled, 1: PCI Mode, 2: ACPI Mode
**/
  UINT8                       Spi2Enable;

/** Offset 0x00DA - OS Debug Feature
  Enable/Disable OS Debug Feature. 0:Disable(Default), 1: Enable.
  $EN_DIS
**/
  UINT8                       OsDbgEnable;

/** Offset 0x00DB - DCI Feature
  Enable/Disable DCI Feature. 0:Disable(Default), 1: Enable.
  $EN_DIS
**/
  UINT8                       DciEn;

/** Offset 0x00DC - UART Debug Base Address
  UART Debug Base Address. 0x00000000(Default).
**/
  UINT32                      Uart2KernelDebugBaseAddress;

/** Offset 0x00E0 - Enable PCIE Clock Gating
  Enable/disable PCIE Clock Gating. 0:Enable, 1:Disable(Default).
  0:Enable, 1:Disable
**/
  UINT8                       PcieClockGatingDisabled;

/** Offset 0x00E1 - Enable PCIE Root Port 8xh Decode
  Enable/disable PCIE Root Port 8xh Decode. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       PcieRootPort8xhDecode;

/** Offset 0x00E2 - PCIE 8xh Decode Port Index
  PCIE 8xh Decode Port Index. 0x00(Default).
**/
  UINT8                       Pcie8xhDecodePortIndex;

/** Offset 0x00E3 - Enable PCIE Root Port Peer Memory Write
  Enable/disable PCIE root port peer memory write. 0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       PcieRootPortPeerMemoryWriteEnable;

/** Offset 0x00E4 - PCIE SWSMI Number
  This member describes the SwSmi value for override PCIe ASPM table. 0xAA(Default).
**/
  UINT8                       PcieAspmSwSmiNumber;

/** Offset 0x00E5
**/
  UINT8                       UnusedUpdSpace1[1];

/** Offset 0x00E6 - PCI Express Root Port
  Control the PCI Express Root Port . 0:Disable, 1:Enable(Default).
**/
  UINT8                       PcieRootPortEn[6];

/** Offset 0x00EC - Hide PCIE Root Port Configuration Space
  Enable/disable Hide PCIE Root Port Configuration Space. 0:Disable(Default), 1:Enable.
**/
  UINT8                       PcieRpHide[6];

/** Offset 0x00F2 - PCIE Root Port Slot Implement
  Enable/disable PCIE Root Port Slot Implement. 0:Disable, 1:Enable(Default).
**/
  UINT8                       PcieRpSlotImplemented[6];

/** Offset 0x00F8 - Hot Plug
  PCI Express Hot Plug Enable/Disable. 0:Disable, 1:Enable(Default).
**/
  UINT8                       PcieRpHotPlug[6];

/** Offset 0x00FE - PCIE PM SCI
  Enable/Disable PCI Express PME SCI. 0:Disable(Default), 1:Enable.
**/
  UINT8                       PcieRpPmSci[6];

/** Offset 0x0104 - PCIE Root Port Extended Sync
  Enable/Disable PCIE Root Port Extended Sync. 0:Disable, 1:Enable(Default).
**/
  UINT8                       PcieRpExtSync[6];

/** Offset 0x010A - Transmitter Half Swing
  Transmitter Half Swing Enable/Disable. 0:Disable, 1:Enable(Default).
**/
  UINT8                       PcieRpTransmitterHalfSwing[6];

/** Offset 0x0110 - ACS
  Enable/Disable Access Control Services Extended Capability. 0:Disable, 1:Enable(Default).
**/
  UINT8                       PcieRpAcsEnabled[6];

/** Offset 0x0116 - Clock Request Support
  Enable/Disable CLKREQ# Support. 0:Disable, 1:Enable(Default).
**/
  UINT8                       PcieRpClkReqSupported[6];

/** Offset 0x011C - Configure CLKREQ Number
  Configure Root Port CLKREQ Number if CLKREQ is supported. Default=0x04, 0x05, 0x00,
  0x01, 0x02, 0x03.
**/
  UINT8                       PcieRpClkReqNumber[6];

/** Offset 0x0122 - CLKREQ# Detection
  Enable/Disable CLKREQ# Detection Probe. 0: Disable(Default), 1: Enable.
**/
  UINT8                       PcieRpClkReqDetect[6];

/** Offset 0x0128 - Advanced Error Reporting
  Enable/Disable Advanced Error Reporting. 0: Disable(Default), 1: Enable.
**/
  UINT8                       AdvancedErrorReporting[6];

/** Offset 0x012E - PME Interrupt
  Enable/Disable PME Interrupt. 0: Disable(Default), 1: Enable.
**/
  UINT8                       PmeInterrupt[6];

/** Offset 0x0134 -   URR
  PCI Express Unsupported Request Reporting Enable/Disable. 0:Disable(Default), 1:Enable.
**/
  UINT8                       UnsupportedRequestReport[6];

/** Offset 0x013A -   FER
  PCI Express Device Fatal Error Reporting Enable/Disable. 0:Disable(Default), 1:Enable.
**/
  UINT8                       FatalErrorReport[6];

/** Offset 0x0140 -   NFER
  PCI Express Device Non-Fatal Error Reporting Enable/Disable. 0:Disable(Default), 1:Enable.
**/
  UINT8                       NoFatalErrorReport[6];

/** Offset 0x0146 -   CER
  PCI Express Device Correctable Error Reporting Enable/Disable. 0:Disable(Default), 1:Enable.
**/
  UINT8                       CorrectableErrorReport[6];

/** Offset 0x014C -   SEFE
  Root PCI Express System Error on Fatal Error Enable/Disable. 0:Disable(Default), 1:Enable.
**/
  UINT8                       SystemErrorOnFatalError[6];

/** Offset 0x0152 -   SENFE
  Root PCI Express System Error on Non-Fatal Error Enable/Disable. 0:Disable(Default), 1:Enable.
**/
  UINT8                       SystemErrorOnNonFatalError[6];

/** Offset 0x0158 -   SECE
  Root PCI Express System Error on Correctable Error Enable/Disable. 0:Disable(Default), 1:Enable.
**/
  UINT8                       SystemErrorOnCorrectableError[6];

/** Offset 0x015E - PCIe Speed
  Configure PCIe Speed. 0:Auto(Default), 1:Gen1, 2:Gen2, 3:Gen3.
**/
  UINT8                       PcieRpSpeed[6];

/** Offset 0x0164 - Physical Slot Number
  Physical Slot Number for PCIE Root Port. Default=0x00, 0x01, 0x02, 0x03, 0x04, 0x05.
**/
  UINT8                       PhysicalSlotNumber[6];

/** Offset 0x016A - CTO
  Enable/Disable PCI Express Completion Timer TO . 0:Disable(Default), 1:Enable.
**/
  UINT8                       PcieRpCompletionTimeout[6];

/** Offset 0x0170 - PTM Support
  Enable/Disable PTM Support. 0:Disable(Default), 1:Enable.
**/
  UINT8                       PtmEnable[6];

/** Offset 0x0176 - ASPM
  PCI Express Active State Power Management settings. 0:Disable, 1:L0s, 2:L1, 3:L0sL1,
  4:Auto(Default).
**/
  UINT8                       PcieRpAspm[6];

/** Offset 0x017C - L1 Substates
  PCI Express L1 Substates settings. 0:Disable, 1:L1.1, 2:L1.2, 3:L1.1 & L1.2(Default).
**/
  UINT8                       PcieRpL1Substates[6];

/** Offset 0x0182 - PCH PCIe LTR
  PCH PCIE Latency Reporting Enable/Disable. 0:Disable, 1:Enable(Default).
**/
  UINT8                       PcieRpLtrEnable[6];

/** Offset 0x0188 - PCIE LTR Lock
  PCIE LTR Configuration Lock. 0:Disable(Default), 1:Enable.
**/
  UINT8                       PcieRpLtrConfigLock[6];

/** Offset 0x018E - PME_B0_S5 Disable bit
  PME_B0_S5_DIS bit in the General PM Configuration B (GEN_PMCON_B) register. 0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       PmeB0S5Dis;

/** Offset 0x018F - PCI Clock Run
  This member describes whether or not the PCI ClockRun feature of SC should be enabled.
  0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       PciClockRun;

/** Offset 0x0190 - Enable/Disable Timer 8254 Clock Setting
  Enable/Disable Timer 8254 Clock. 0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       Timer8254ClkSetting;

/** Offset 0x0191 - Chipset SATA
  Enables or Disables the Chipset SATA Controller. The Chipset SATA controller supports
  the 2 black internal SATA ports (up to 3Gb/s supported per port). 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       EnableSata;

/** Offset 0x0192 - SATA Mode Selection
  Determines how SATA controller(s) operate. 0:AHCI(Default), 1:RAID.
  0:AHCI, 1:RAID
**/
  UINT8                       SataMode;

/** Offset 0x0193 - Aggressive LPM Support
  Enable PCH to aggressively enter link power state.  0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       SataSalpSupport;

/** Offset 0x0194 - SATA Power Optimization
  Enable SATA Power Optimizer on SC side.  0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       SataPwrOptEnable;

/** Offset 0x0195 - eSATA Speed Limit
  Enable/Disable eSATA Speed Limit.  0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       eSATASpeedLimit;

/** Offset 0x0196 - SATA Speed Limit
  SATA Speed Limit. 0h:ScSataSpeed(Default), 1h:1.5Gb/s(Gen 1), 2h:3Gb/s(Gen 2), 3h:6Gb/s(Gen 3).
  0:Default, 1: 1.5 Gb/s (Gen 1), 2: 3 Gb/s(Gen 2), 3: 6 Gb/s (Gen 1)
**/
  UINT8                       SpeedLimit;

/** Offset 0x0197
**/
  UINT8                       UnusedUpdSpace2[1];

/** Offset 0x0198 - SATA Port
  Enable or Disable SATA Port.  0:Disable, 1:Enable(Default).
**/
  UINT8                       SataPortsEnable[2];

/** Offset 0x019A - SATA Port DevSlp
  Enable/Disable SATA Port  DevSlp. Board rework for LP needed before enable.  0:Disable(Default), 1:Enable.
**/
  UINT8                       SataPortsDevSlp[2];

/** Offset 0x019C - SATA Port HotPlug
  Enable/Disable SATA Port Hotplug . 0:Disable(Default), 1:Enable.
**/
  UINT8                       SataPortsHotPlug[2];

/** Offset 0x019E - Mechanical Presence Switch
  Controls reporting if this port has an Mechanical Presence Switch.\n
  Note:Requires hardware support.  0:Disable, 1:Enable(Default).
**/
  UINT8                       SataPortsInterlockSw[2];

/** Offset 0x01A0 - External SATA Ports
  Enable/Disable External SATA Ports. 0:Disable(Default), 1:Enable.
**/
  UINT8                       SataPortsExternal[2];

/** Offset 0x01A2 - Spin Up Device
  Enable/Disable device spin up at boot on selected Sata Ports. 0:Disable(Default), 1:Enable.
**/
  UINT8                       SataPortsSpinUp[2];

/** Offset 0x01A4 - SATA Solid State
  Identify the SATA port is connected to Solid State Drive or Hard Disk Drive.  0:Hard
  Disk Drive(Default), 1:Solid State Drive.
**/
  UINT8                       SataPortsSolidStateDrive[2];

/** Offset 0x01A6 -   DITO Configuration
  Enable/Disable DITO Configuration.  0:Disable(Default), 1:Enable.
**/
  UINT8                       SataPortsEnableDitoConfig[2];

/** Offset 0x01A8 - DM Value
  DM Value.  0:Minimum, 0x0F:Maximum(Default).
**/
  UINT8                       SataPortsDmVal[2];

/** Offset 0x01AA
**/
  UINT8                       UnusedUpdSpace3[2];

/** Offset 0x01AC - DITO Value
  DEVSLP Idle Timeout Value. 0:Minimum, 0x03FF:Maximum, 0x0271(Default).
**/
  UINT16                      SataPortsDitoVal[2];

/** Offset 0x01B0 - Subsystem Vendor ID
  Subsystem Vendor ID. 0x8086(Default).
**/
  UINT16                      SubSystemVendorId;

/** Offset 0x01B2 - Subsystem ID
  Subsystem ID. 0x7270(Default).
**/
  UINT16                      SubSystemId;

/** Offset 0x01B4 - CRIDSettings
  PMC CRID setting. 0:Disable(Default), 1:CRID_1, 2:CRID_2, 3:CRID_3.
**/
  UINT8                       CRIDSettings;

/** Offset 0x01B5 - ResetSelect
  ResetSelect. 0x6:warm reset(Default), 0xE:cold reset.
**/
  UINT8                       ResetSelect;

/** Offset 0x01B6 - SD Card Support (D27:F0)
  Enable/Disable SD Card Support. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       SdcardEnabled;

/** Offset 0x01B7 - SeMMC Support (D28:F0)
  Enable/Disable eMMC Support. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       eMMCEnabled;

/** Offset 0x01B8 - eMMC Max Speed
  Select the eMMC max Speed allowed. 0:HS400(Default), 1:HS200, 2:DDR50.
  0:HS400, 1: HS200, 2:DDR50
**/
  UINT8                       eMMCHostMaxSpeed;

/** Offset 0x01B9 - UFS Support (D29:F0)
  Enable/Disable SDIO Support. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       UfsEnabled;

/** Offset 0x01BA - SDIO Support (D30:F0)
  Enable/Disable SDIO Support. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       SdioEnabled;

/** Offset 0x01BB - GPP Lock Feature
  Enable/Disable GPP lock. 0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       GppLock;

/** Offset 0x01BC - Serial IRQ
  Enable/Disable Serial IRQ. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       SirqEnable;

/** Offset 0x01BD - Serial IRQ Mode
  Serial IRQ Mode Selection. 0:Quiet mode(Default), 1:Continuous mode.
  $EN_DIS
**/
  UINT8                       SirqMode;

/** Offset 0x01BE - Start Frame Pulse Width
  Start Frame Pulse Width Value. 0:ScSfpw4Clk(Default), 1: ScSfpw6Clk, 2:ScSfpw8Clk.
  0:ScSfpw4Clk, 1:ScSfpw6Clk, 2:ScSfpw8Clk
**/
  UINT8                       StartFramePulse;

/** Offset 0x01BF - Enable SMBus
  Enable/disable SMBus controller. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       SmbusEnable;

/** Offset 0x01C0 - SMBus ARP Support
  Enable/disable SMBus ARP Support. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       ArpEnable;

/** Offset 0x01C1
**/
  UINT8                       UnusedUpdSpace4;

/** Offset 0x01C2 - SMBus Table Elements
  The number of elements in the Reserved SMBus Address Table. 0x0080(Default).
**/
  UINT16                      NumRsvdSmbusAddresses;

/** Offset 0x01C4 - Reserved SMBus Address Table
  Array of addresses reserved for non-ARP-capable SMBus devices. 0x00(Default).
**/
  UINT8                       RsvdSmbusAddressTable[128];

/** Offset 0x0244 - XHCI Disable Compliance Mode
  Options to disable XHCI Link Compliance Mode. Default is FALSE to not disable Compliance
  Mode. Set TRUE to disable Compliance Mode. 0:FALSE(Default), 1:True.
  $EN_DIS
**/
  UINT8                       DisableComplianceMode;

/** Offset 0x0245 - USB Per-Port Control
  Control each of the USB ports enable/disable. 0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       UsbPerPortCtl;

/** Offset 0x0246 - xHCI Mode
  Mode of operation of xHCI controller. 0:Disable, 1:Enable, 2:Auto(Default)
  0:Disable, 1:Enable, 2:Auto
**/
  UINT8                       Usb30Mode;

/** Offset 0x0247
**/
  UINT8                       UnusedUpdSpace5[1];

/** Offset 0x0248 - Enable USB2 ports
  Enable/disable per USB2 ports. One byte for each port, byte0 for port0, byte1 for
  port1, and so on. 0x01(Default).
**/
  UINT8                       PortUsb20Enable[8];

/** Offset 0x0250 - USB20 Over Current Pin
  Over Current Pin number of USB 2.0 Port. 0x00(Default).
**/
  UINT8                       PortUs20bOverCurrentPin[8];

/** Offset 0x0258 - XDCI Support
  Enable/Disable XDCI. 0:Disable, 1:PCI_Mode(Default), 2:ACPI_mode.
  0:Disable, 1:PCI_Mode, 2:ACPI_mode
**/
  UINT8                       UsbOtg;

/** Offset 0x0259 - Enable XHCI HSIC Support
  Enable/Disable USB HSIC1. 0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       HsicSupportEnable;

/** Offset 0x025A - Enable USB3 ports
  Enable/disable per USB3 ports. One byte for each port, byte0 for port0, byte1 for
  port1, and so on. 0x01(Default).
**/
  UINT8                       PortUsb30Enable[6];

/** Offset 0x0260 - USB20 Over Current Pin
  Over Current Pin number of USB 3.0 Port. 0x01(Default).
**/
  UINT8                       PortUs30bOverCurrentPin[6];

/** Offset 0x0266 - Enable XHCI SSIC Support
  Enable/disable XHCI SSIC ports. One byte for each port, byte0 for port0, byte1 for
  port1. 0x00(Default).
**/
  UINT8                       SsicPortEnable[2];

/** Offset 0x0268 - SSIC Dlane PowerGating
  Enable/Disable SSIC Data lane Power Gating. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT16                      DlanePwrGating;

/** Offset 0x026A - VT-d
  Enable/Disable VT-d. 0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       VtdEnable;

/** Offset 0x026B - SMI Lock bit
  Enable/Disable SMI_LOCK bit to prevent writes to the Global SMI Enable bit. 0:Disable,
  1:Enable(Default).
  $EN_DIS
**/
  UINT8                       LockDownGlobalSmi;

/** Offset 0x026C - HDAudio Delay Timer
  The delay timer after Azalia reset. 0x012C(Default).
**/
  UINT16                      ResetWaitTimer;

/** Offset 0x026E - RTC Lock Bits
  Enable/Disable RTC Lock Bits. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       RtcLock;

/** Offset 0x026F - SATA Test Mode Selection
  Enable/Disable SATA Test Mode. 0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT8                       SataTestMode;

/** Offset 0x0270 - XHCI SSIC RATE
  Set XHCI SSIC1 Rate to A Series or B Series. 1:A Series(Default), 2:B Series.
**/
  UINT8                       SsicRate[2];

/** Offset 0x0272 - SMBus Dynamic Power Gating
  Enable/Disable SMBus dynamic power gating. 0:Disable(Default), 1:Enable.
  $EN_DIS
**/
  UINT16                      DynamicPowerGating;

/** Offset 0x0274 - Max Snoop Latency
  Latency Tolerance Reporting Max Snoop Latency. 0x0000(Default).
**/
  UINT16                      PcieRpLtrMaxSnoopLatency[6];

/** Offset 0x0280 -   Snoop Latency Override
  Snoop Latency Override for PCH PCIE. \n
  Disabled:Disable override.\n
  Manual:Manually enter override values.\n
  Auto:Maintain default BIOS flow. 0:Disable, 1:Enable, 2:Auto(Default).
**/
  UINT8                       PcieRpSnoopLatencyOverrideMode[6];

/** Offset 0x0286
**/
  UINT8                       UnusedUpdSpace6[2];

/** Offset 0x0288 -   Snoop Latency Value
  LTR Snoop Latency value of PCH PCIE. 0:Minimum, 0x03FF:Maximum, 0x003C(Default).
**/
  UINT16                      PcieRpSnoopLatencyOverrideValue[6];

/** Offset 0x0294 -   Snoop Latency Multiplier
  LTR Snoop Latency Multiplier of PCH PCIE. 0:1ns, 1:32ns, 2:1024ns(Default), 3:32768ns,
  4:1048576ns, 5:33554432ns.
**/
  UINT8                       PcieRpSnoopLatencyOverrideMultiplier[6];

/** Offset 0x029A - Skip Multi-Processor Initialization
  When this is skipped, boot loader must initialize processors before SilicionInit
  API. 0: Initialize(Default), <b>1: Skip
  $EN_DIS
**/
  UINT8                       SkipMpInit;

/** Offset 0x029B - DCI Auto Detect
  Deprecated: Enable/disable DCI AUTO mode. Enabled(Default).
  $EN_DIS
**/
  UINT8                       DciAutoDetect;

/** Offset 0x029C - Max Non-Snoop Latency
  Latency Tolerance Reporting, Max Non-Snoop Latency. 0x0000(Default).
**/
  UINT16                      PcieRpLtrMaxNonSnoopLatency[6];

/** Offset 0x02A8 -   Non Snoop Latency Override
  Non Snoop Latency Override for PCH PCIE. \n
  Disabled:Disable override.\n
  Manual:Manually enter override values.\n
  Auto: Maintain default BIOS flow. 0:Disable, 1:Enable, 2:Auto(Default).
**/
  UINT8                       PcieRpNonSnoopLatencyOverrideMode[6];

/** Offset 0x02AE - Halt and Lock TCO Timer
  Halt and Lock the TCO Timer (Watchdog).
  0:No, 1:Yes (default)
**/
  UINT8                       TcoTimerHaltLock;

/** Offset 0x02AF - Power Button Override Period
  specifies how long will PMC wait before initiating a global reset. 000b-4s(default),
  001b-6s, 010b-8s, 011b-10s, 100b-12s, 101b-14s.)
  0x0:4s, 0x1:6s, 0x2:8s, 0x3:10s, 0x4:12s, 0x5:14s
**/
  UINT8                       PwrBtnOverridePeriod;

/** Offset 0x02B0 -   Non Snoop Latency Value
  LTR Non Snoop Latency value of PCH PCIE. 0:Minimum, 0x03FF:Maximum, 0x003C(Default).
**/
  UINT16                      PcieRpNonSnoopLatencyOverrideValue[6];

/** Offset 0x02BC -   Non Snoop Latency Multiplier
  LTR Non Snoop Latency Multiplier of PCH PCIE. 0:1ns, 1:32ns, 2:1024ns(Default),
  3:32768ns, 4:1048576ns, 5:33554432ns.
**/
  UINT8                       PcieRpNonSnoopLatencyOverrideMultiplier[6];

/** Offset 0x02C2 - PCIE Root Port Slot Power Limit Scale
  Specifies scale used for slot power limit value. 0x00(Default).
**/
  UINT8                       PcieRpSlotPowerLimitScale[6];

/** Offset 0x02C8 - PCIE Root Port Slot Power Limit Value
  Specifies upper limit on power supplie by slot. 0x00(Default).
**/
  UINT8                       PcieRpSlotPowerLimitValue[6];

/** Offset 0x02CE - Power Button Native Mode Disable
  Disable power button native mode, when 1, this will result in the PMC logic constantly
  seeing the power button as de-asserted. 0 (default))
  $EN_DIS
**/
  UINT8                       DisableNativePowerButton;

/** Offset 0x02CF - Power Button Debounce Mode
  Enable interrupt when PWRBTN# is asserted. 0:Disabled, 1:Enabled(default)
  $EN_DIS
**/
  UINT8                       PowerButterDebounceMode;

/** Offset 0x02D0 - SDIO_TX_CMD_DLL_CNTL
  SDIO_TX_CMD_DLL_CNTL. 0x505(Default).
**/
  UINT32                      SdioTxCmdCntl;

/** Offset 0x02D4 - SDIO_TX_DATA_DLL_CNTL1
  SDIO_TX_DATA_DLL_CNTL1. 0xE(Default).
**/
  UINT32                      SdioTxDataCntl1;

/** Offset 0x02D8 - SDIO_TX_DATA_DLL_CNTL2
  SDIO_TX_DATA_DLL_CNTL2. 0x22272828(Default).
**/
  UINT32                      SdioTxDataCntl2;

/** Offset 0x02DC - SDIO_RX_CMD_DATA_DLL_CNTL1
  SDIO_RX_CMD_DATA_DLL_CNTL1. 0x16161616(Default).
**/
  UINT32                      SdioRxCmdDataCntl1;

/** Offset 0x02E0 - SDIO_RX_CMD_DATA_DLL_CNTL2
  SDIO_RX_CMD_DATA_DLL_CNTL2. 0x10000(Default).
**/
  UINT32                      SdioRxCmdDataCntl2;

/** Offset 0x02E4 - SDCARD_TX_CMD_DLL_CNTL
  SDCARD_TX_CMD_DLL_CNTL. 0x505(Default).
**/
  UINT32                      SdcardTxCmdCntl;

/** Offset 0x02E8 - SDCARD_TX_DATA_DLL_CNTL1
  SDCARD_TX_DATA_DLL_CNTL1. 0xA13(Default).
**/
  UINT32                      SdcardTxDataCntl1;

/** Offset 0x02EC - SDCARD_TX_DATA_DLL_CNTL2
  SDCARD_TX_DATA_DLL_CNTL2. 0x24242828(Default).
**/
  UINT32                      SdcardTxDataCntl2;

/** Offset 0x02F0 - SDCARD_RX_CMD_DATA_DLL_CNTL1
  SDCARD_RX_CMD_DATA_DLL_CNTL1. 0x73A3637(Default).
**/
  UINT32                      SdcardRxCmdDataCntl1;

/** Offset 0x02F4 - SDCARD_RX_STROBE_DLL_CNTL
  SDCARD_RX_STROBE_DLL_CNTL. 0x0(Default).
**/
  UINT32                      SdcardRxStrobeCntl;

/** Offset 0x02F8 - SDCARD_RX_CMD_DATA_DLL_CNTL2
  SDCARD_RX_CMD_DATA_DLL_CNTL2. 0x10000(Default).
**/
  UINT32                      SdcardRxCmdDataCntl2;

/** Offset 0x02FC - EMMC_TX_CMD_DLL_CNTL
  EMMC_TX_CMD_DLL_CNTL. 0x505(Default).
**/
  UINT32                      EmmcTxCmdCntl;

/** Offset 0x0300 - EMMC_TX_DATA_DLL_CNTL1
  EMMC_TX_DATA_DLL_CNTL1. 0xC11(Default).
**/
  UINT32                      EmmcTxDataCntl1;

/** Offset 0x0304 - EMMC_TX_DATA_DLL_CNTL2
  EMMC_TX_DATA_DLL_CNTL2. 0x1C2A2927(Default).
**/
  UINT32                      EmmcTxDataCntl2;

/** Offset 0x0308 - EMMC_RX_CMD_DATA_DLL_CNTL1
  EMMC_RX_CMD_DATA_DLL_CNTL1. 0x000D162F(Default).
**/
  UINT32                      EmmcRxCmdDataCntl1;

/** Offset 0x030C - EMMC_RX_STROBE_DLL_CNTL
  EMMC_RX_STROBE_DLL_CNTL. 0x0a0a(Default).
**/
  UINT32                      EmmcRxStrobeCntl;

/** Offset 0x0310 - EMMC_RX_CMD_DATA_DLL_CNTL2
  EMMC_RX_CMD_DATA_DLL_CNTL2. 0x1003b(Default).
**/
  UINT32                      EmmcRxCmdDataCntl2;

/** Offset 0x0314 - EMMC_MASTER_DLL_CNTL
  EMMC_MASTER_DLL_CNTL. 0x001(Default).
**/
  UINT32                      EmmcMasterSwCntl;

/** Offset 0x0318 - PCIe Selectable De-emphasis
  When the Link is operating at 5.0 GT/s speed, this bit selects the level of de-emphasis
  for an Upstream component. 1b:-3.5 dB 0b:-6 dB. 0:Disable, 1:Enable(Default).
**/
  UINT8                       PcieRpSelectableDeemphasis[6];

/** Offset 0x031E - Monitor Mwait Enable
  Enable/Disable Monitor Mwait. For Windows* OS, this should be Enabled. For Linux
  based OS, this should be Disabled. 0:Disable, 1:Enable(Default).
  $EN_DIS
**/
  UINT8                       MonitorMwaitEnable;

/** Offset 0x031F - Universal Audio Architecture compliance for DSP enabled system
  0: Not-UAA Compliant (Intel SST driver supported only), 1: UAA Compliant (HDA Inbox
  driver or SST driver supported).
  $EN_DIS
**/
  UINT8                       HdAudioDspUaaCompliance;

/** Offset 0x0320 - IRQ Interrupt Polarity Control
  Set IRQ Interrupt Polarity Control to ITSS.IPC[0]~IPC[3]. 0:Active High, 1:Active Low
**/
  UINT32                      IPC[4];

/** Offset 0x0330 - Disable ModPHY dynamic power gate
  Disable ModPHY dynamic power gate for the specific SATA port.
**/
  UINT8                       SataPortsDisableDynamicPg[2];

/** Offset 0x0332 - Init CPU during S3 resume
  0: Do not initialize CPU during S3 resume. 1: Initialize CPU during S3 resume.
  $EN_DIS
**/
  UINT8                       InitS3Cpu;

/** Offset 0x0333 - Skip P-unit Initialization
  When this is skipped, boot loader must initialize P-unit before SilicionInit API.
  0: Initialize(Default), 1: Skip
  $EN_DIS
**/
  UINT8                       SkipPunitInit;

/** Offset 0x0334
**/
  UINT8                       UnusedUpdSpace7[4];

/** Offset 0x0338 - PerPort Half Bit Pre-emphasis
  PerPort Half Bit Pre-emphasis. Value of register USB2_PER_PORT_PPX [14]
**/
  UINT8                       PortUsb20PerPortTxPeHalf[8];

/** Offset 0x0340 - PerPort HS Pre-emphasis Bias
  PerPort HS Pre-emphasis Bias. Value of register USB2_PER_PORT_PPX [13:11]
**/
  UINT8                       PortUsb20PerPortPeTxiSet[8];

/** Offset 0x0348 - PerPort HS Transmitter Bias
  PerPort HS Transmitter Bias. Value of register USB2_PER_PORT_PPX [10:8]
**/
  UINT8                       PortUsb20PerPortTxiSet[8];

/** Offset 0x0350 - Select the skew direction for HS transition
  Select the skew direction for HS transition. Value of register USB2_PER_PORT_2_PPX [25]
**/
  UINT8                       PortUsb20HsSkewSel[8];

/** Offset 0x0358 - Per Port HS Transmitter Emphasis
  Per Port HS Transmitter Emphasis. Value of register USB2_PER_PORT_2_PPX [24:23]
**/
  UINT8                       PortUsb20IUsbTxEmphasisEn[8];

/** Offset 0x0360 - PerPort HS Receiver Bias
  PerPort HS Receiver Bias. Value of register  USB2_PER_PORT_2_PPX [19:17]
**/
  UINT8                       PortUsb20PerPortRXISet[8];

/** Offset 0x0368 - Delay/skew's strength control for HS driver
  Delay/skew's strength control for HS driver. Value of register USB2_PER_PORT_2_PPX [1:0]
**/
  UINT8                       PortUsb20HsNpreDrvSel[8];

/** Offset 0x0370
**/
  UINT8                       ReservedFspsUpd[16];
} FSP_S_CONFIG;

/** Fsp S UPD Configuration
**/
typedef struct {

/** Offset 0x0000
**/
  FSP_UPD_HEADER              FspUpdHeader;

/** Offset 0x0020
**/
  FSP_S_CONFIG                FspsConfig;

/** Offset 0x0380
**/
  UINT8                       UnusedUpdSpace8[46];

/** Offset 0x03AE
**/
  UINT16                      UpdTerminator;
} FSPS_UPD;

#pragma pack()

#endif
