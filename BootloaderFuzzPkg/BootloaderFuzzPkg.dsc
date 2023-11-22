## @file BootloaderFuzzPkg.dsc
# 
# Copyright (c) 2023, Intel Corporation. All rights reserved.<BR>
# SPDX-License-Identifier: BSD-2-Clause-Patent
#
##

[Defines]
  PLATFORM_NAME                  = BootloaderFuzzPkg
  PLATFORM_GUID                  = 9497CEE4-EEEB-4B38-B0EF-03E01920F040
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  OUTPUT_DIRECTORY               = Build/BootloaderFuzzPkg
  SUPPORTED_ARCHITECTURES        = IA32|X64
  BUILD_TARGETS                  = DEBUG|RELEASE|NOOPT
  SKUID_IDENTIFIER               = DEFAULT

[LibraryClasses]
  PcdLib|BootloaderCommonPkg/Library/PcdLib/PcdLib.inf
  RegisterFilterLib|MdePkg/Library/RegisterFilterLibNull/RegisterFilterLibNull.inf
  BaseLib|MdePkg/Library/BaseLib/BaseLib.inf
  IoLib|MdePkg/Library/BaseIoLibIntrinsic/BaseIoLibIntrinsic.inf
  PciLib|MdePkg/Library/BasePciLibPciExpress/BasePciLibPciExpress.inf
  PciCf8Lib|MdePkg/Library/BasePciCf8Lib/BasePciCf8Lib.inf
  PciExpressLib|MdePkg/Library/BasePciExpressLib/BasePciExpressLib.inf
  PciSegmentLib|MdePkg/Library/BasePciSegmentLibPci/BasePciSegmentLibPci.inf
  DebugPrintErrorLevelLib|BootloaderCorePkg/Library/DebugPrintErrorLevelLib/DebugPrintErrorLevelLib.inf
  PrintLib|MdePkg/Library/BasePrintLib/BasePrintLib.inf
  BaseMemoryLib|MdePkg/Library/BaseMemoryLibSse2/BaseMemoryLibSse2.inf
  SynchronizationLib|MdePkg/Library/BaseSynchronizationLib/BaseSynchronizationLib.inf
  TimeStampLib|BootloaderCommonPkg/Library/TimeStampLib/TimeStampLib.inf
  ExtraBaseLib|BootloaderCommonPkg/Library/ExtraBaseLib/ExtraBaseLib.inf
  ModuleEntryLib|BootloaderCommonPkg/Library/ModuleEntryLib/ModuleEntryLib.inf
  LzmaDecompressLib|BootloaderCommonPkg/Library/LzmaCustomDecompressLib/LzmaCustomDecompressLib.inf
  Lz4CompressLib|BootloaderCommonPkg/Library/Lz4CompressLib/Lz4CompressLib.inf
  DecompressLib|BootloaderCommonPkg/Library/DecompressLib/DecompressLib.inf
  RleCompressLib|BootloaderCommonPkg/Library/RleCompressLib/RleCompressLib.inf
  FspSupportLib|BootloaderCorePkg/Library/FspSupportLib/FspSupportLib.inf
  BootloaderLib|BootloaderCorePkg/Library/BootloaderLib/BootloaderLib.inf
  BootloaderCoreLib|BootloaderCorePkg/Library/BootloaderCoreLib/BootloaderCoreLib.inf
  PciEnumerationLib|BootloaderCorePkg/Library/PciEnumerationLib/PciEnumerationLib.inf
  AcpiInitLib|BootloaderCorePkg/Library/AcpiInitLib/AcpiInitLib.inf
  SmbiosInitLib|BootloaderCorePkg/Library/SmbiosInitLib/SmbiosInitLib.inf
  LitePeCoffLib|BootloaderCommonPkg/Library/LitePeCoffLib/LitePeCoffLib.inf
  HobLib|BootloaderCommonPkg/Library/HobLib/HobLib.inf
  HobBuildLib|BootloaderCorePkg/Library/HobBuildLib/HobBuildLib.inf
  LiteFvLib|BootloaderCommonPkg/Library/LiteFvLib/LiteFvLib.inf
  LoaderPerformanceLib|BootloaderCommonPkg/Library/LoaderPerformanceLib/LoaderPerformanceLib.inf
  MemoryAllocationLib|UefiHostTestPkg/Library/MemoryAllocationLibHost/MemoryAllocationLibHost.inf
  MpInitLib|BootloaderCorePkg/Library/MpInitLib/MpInitLib.inf
  StageLib|BootloaderCorePkg/Library/StageLib/StageLib.inf
  LocalApicLib|BootloaderCommonPkg/Library/BaseXApicX2ApicLib/BaseXApicX2ApicLib.inf
  SecureBootLib|BootloaderCommonPkg/Library/SecureBootLib/SecureBootLib.inf
  TpmLib|BootloaderCommonPkg/Library/TpmLib/TpmLib.inf
  ConfigDataLib|BootloaderCommonPkg/Library/ConfigDataLib/ConfigDataLib.inf
  MmcAccessLib|BootloaderCommonPkg/Library/MmcAccessLib/MmcAccessLib.inf
  GraphicsLib|BootloaderCommonPkg/Library/GraphicsLib/GraphicsLib.inf
  Crc32Lib|BootloaderCommonPkg/Library/Crc32Lib/Crc32Lib.inf
  VariableLib|BootloaderCommonPkg/Library/LiteVariableLib/LiteVariableLib.inf
  DebugDataLib|BootloaderCorePkg/Library/DebugDataLib/DebugDataLib.inf
  CpuExceptionLib|BootloaderCorePkg/Library/CpuExceptionLib/CpuExceptionLib.inf
  FileSystemLib|BootloaderCommonPkg/Library/FileSystemLib/FileSystemLib.inf
  FatLib|BootloaderCommonPkg/Library/FatLib/FatLib.inf
  PartitionLib|BootloaderCommonPkg/Library/PartitionLib/PartitionLib.inf
  Ext23Lib|BootloaderCommonPkg/Library/Ext23Lib/Ext23Lib.inf
  ShellLib|BootloaderCommonPkg/Library/ShellLib/ShellLib.inf
  SpiBlockIoLib|BootloaderCommonPkg/Library/SpiBlockIoLib/SpiBlockIoLib.inf
  UfsBlockIoLib|BootloaderCommonPkg/Library/UfsBlockIoLib/UfsBlockIoLib.inf
  MmcAccessLib|BootloaderCommonPkg/Library/MmcAccessLib/MmcAccessLib.inf
  MmcTuningLib|BootloaderCommonPkg/Library/MmcTuningLib/MmcTuningLib.inf
  RpmbLib|BootloaderCommonPkg/Library/RpmbLib/RpmbLib.inf
  NvmExpressLib|BootloaderCommonPkg/Library/NvmExpressLib/NvmExpressLib.inf
  MemoryDeviceBlockIoLib|BootloaderCommonPkg/Library/MemoryDeviceBlockIoLib/MemoryDeviceBlockIoLib.inf
  AhciLib|BootloaderCommonPkg/Library/AhciLib/AhciLib.inf
  UsbInitLib|BootloaderCommonPkg/Library/UsbInitLib/UsbInitLib.inf
  UsbKbLib|BootloaderCommonPkg/Library/UsbKbLib/UsbKbLib.inf
  UsbHostCtrlLib|BootloaderCommonPkg/Library/XhciLib/XhciLib.inf
  UsbBusLib|BootloaderCommonPkg/Library/UsbBusLib/UsbBusLib.inf
  UsbBlockIoLib|BootloaderCommonPkg/Library/UsbBlockIoLib/UsbBlockIoLib.inf
  IasImageLib|BootloaderCommonPkg/Library/IasImageLib/IasImageLib.inf
  MultibootLib|BootloaderCommonPkg/Library/MultibootLib/MultibootLib.inf
  MediaAccessLib|BootloaderCommonPkg/Library/MediaAccessLib/MediaAccessLib.inf
  ResetSystemLib|BootloaderCommonPkg/Library/ResetSystemLib/ResetSystemLib.inf
  BootOptionLib|BootloaderCommonPkg/Library/BootOptionLib/BootOptionLib.inf
  RngLib|MdePkg/Library/BaseRngLib/BaseRngLib.inf
  SeedListInfoLib|BootloaderCommonPkg/Library/SeedListInfoLib/SeedListInfoLib.inf
  CryptoLib|BootloaderCommonPkg/Library/IppCryptoLib/IppCryptoLib.inf
  ShellExtensionLib|BootloaderCommonPkg/Library/ShellExtensionLibNull/ShellExtensionLibNull.inf
  DebugLogBufferLib|BootloaderCommonPkg/Library/DebugLogBufferLib/DebugLogBufferLib.inf
  DebugLib|UefiHostTestPkg/Library/DebugLibHost/DebugLibHost.inf
  ConsoleInLib|BootloaderCommonPkg/Library/ConsoleInLib/ConsoleInLib.inf
  ConsoleOutLib|BootloaderCommonPkg/Library/ConsoleOutLib/ConsoleOutLib.inf
  ContainerLib|BootloaderCommonPkg/Library/ContainerLib/ContainerLib.inf
  LinuxLib|BootloaderCommonPkg/Library/LinuxLib/LinuxLib.inf
  UefiVariableLib|BootloaderCommonPkg/Library/UefiVariableLib/UefiVariableLib.inf
  SerialPortLib|MdePkg/Library/BaseSerialPortLibNull/BaseSerialPortLibNull.inf
  SortLib|BootloaderCommonPkg/Library/SortLib/SortLib.inf
  IoMmuLib|BootloaderCommonPkg/Library/IoMmuLib/IoMmuLib.inf
  MtrrLib|BootloaderCommonPkg/Library/MtrrLib/MtrrLib.inf
  StringSupportLib|BootloaderCommonPkg/Library/StringSupportLib/StringSupportLib.inf
  ThunkLib|BootloaderCommonPkg/Library/ThunkLib/ThunkLib.inf
  UniversalPayloadLib|BootloaderCommonPkg/Library/UniversalPayloadLib/UniversalPayloadLib.inf
  DebugAgentLib|BootloaderCommonPkg/Library/DebugAgentLib/DebugAgentLibNull.inf
  ElfLib|BootloaderCommonPkg/Library/ElfLib/ElfLib.inf
  S3SaveRestoreLib|BootloaderCorePkg/Library/S3SaveRestoreLib/S3SaveRestoreLib.inf
  BoardSupportLib|Platform/CommonBoardPkg/Library/BoardSupportLib/BoardSupportLib.inf
  PagingLib|BootloaderCommonPkg/Library/PagingLib/PagingLib.inf
  TimerLib|BootloaderCommonPkg/Library/AcpiTimerLib/AcpiTimerLib.inf
  DebugPortLib|BootloaderCommonPkg/Library/DebugPortLib/DebugPortLibNull.inf
  CrashLogLib|Silicon/CommonSocPkg/Library/CrashLogLibNull/CrashLogLibNull.inf
  FusaConfigLib|Silicon/CommonSocPkg/Library/FusaConfigLibNull/FusaConfigLibNull.inf
  ToolChainHarnessLib|UefiHostFuzzTestPkg/Library/ToolChainHarnessLib/ToolChainHarnessLib.inf
  BaseMemoryLib|UefiHostTestPkg/Library/BaseMemoryLibHost/BaseMemoryLibHost.inf
  Tpm2PtpStub|BootloaderFuzzPkg/TestStub/BootloaderCommonPkg/Library/TpmLib/Tpm2PtpStub.inf
  HashStub|BootloaderFuzzPkg/TestStub/BootloaderCommonPkg/Library/SecureBootLib/HashStub.inf
  BootloaderCommonStub|BootloaderFuzzPkg/TestStub/BootloaderCommonPkg/Library/SecureBootLib/BootloaderCommonStub.inf

[LibraryClasses.common.USER_DEFINED]

[Components]
  BootloaderFuzzPkg/TestCase/BootloaderCommonPkg/Library/TpmLib/TestTpm2Capability.inf
  BootloaderFuzzPkg/TestCase/BootloaderCommonPkg/Library/TpmLib/TestTpm2Hierarchy.inf
  BootloaderFuzzPkg/TestCase/BootloaderCommonPkg/Library/SecureBootLib/TestSecureBootHash.inf

[PcdsDynamicDefault]

[PcdsFixedAtBuild]

!include UefiHostFuzzTestPkg/UefiHostFuzzTestBuildOption.dsc
