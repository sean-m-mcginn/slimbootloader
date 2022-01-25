//
// Automatically generated by GenNvs ver 2.4.6
// Please DO NOT modify !!!
//

/** @file

  Copyright (c) 2021, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

  //
  // Define CPU NVS Area operation region.
  //


  OperationRegion(PNVS,SystemMemory,0xFFFF0000,0xAA55)
  Field(PNVS,AnyAcc,Lock,Preserve)
  {  Offset(0),      PGRV, 8,  // Offset(0),     CPU GlobalNvs Revision
  Offset(1),      CFGD, 32, // Offset(1),     PPM Flags Values
  Offset(6),                // Offset(5) : Offset(5), Reserved bytes
  Offset(6),      ACRT, 8,  // Offset(6),     Auto Critical Trip Point
  Offset(7),      APSV, 8,  // Offset(7),     Auto Passive Trip Point
  Offset(8),      AAC0, 8,  // Offset(8),     Auto Active Trip Point
  Offset(9),      CPID, 32, // Offset(9),     CPUID
  Offset(13),     CPPC, 8,  // Offset(13),    Boot Mode vlues for _PPC
  Offset(14),     CLVL, 8,  // Offset(14),    ConfigTdp Number Of Levels
  Offset(15),     CBMI, 8,  // Offset(15),    CTDP Boot Mode Index
  Offset(16),     PL10, 16, // Offset(16),    CTDP Level 0 Power Limit1
  Offset(18),     PL11, 16, // Offset(18),    CTDP Level 1 Power Limit1
  Offset(20),     PL12, 16, // Offset(20),    CTDP Level 2 Power Limit1
  Offset(22),     PL20, 16, // Offset(22),    CTDP Level 0 Power Limit2
  Offset(24),     PL21, 16, // Offset(24),    CTDP Level 1 Power Limit2
  Offset(26),     PL22, 16, // Offset(26),    CTDP Level 2 Power Limit2
  Offset(28),     PLW0, 8,  // Offset(28),    CTDP Level 0 Power Limit1 Time Window
  Offset(29),     PLW1, 8,  // Offset(29),    CTDP Level 1 Power Limit1 Time Window
  Offset(30),     PLW2, 8,  // Offset(30),    CTDP Level 2 Power Limit1 Time Window
  Offset(31),     CTC0, 8,  // Offset(31),    CTDP Level 0 CTC
  Offset(32),     CTC1, 8,  // Offset(32),    CTDP Level 1 CTC
  Offset(33),     CTC2, 8,  // Offset(33),    CTDP Level 2 CTC
  Offset(34),     TAR0, 8,  // Offset(34),    CTDP Level 0 TAR
  Offset(35),     TAR1, 8,  // Offset(35),    CTDP Level 1 TAR
  Offset(36),     TAR2, 8,  // Offset(36),    CTDP Level 2 TAR
  Offset(37),     PPC0, 8,  // Offset(37),    CTDP Level 0 PPC
  Offset(38),     PPC1, 8,  // Offset(38),    CTDP Level 1 PPC
  Offset(39),     PPC2, 8,  // Offset(39),    CTDP Level 2 PPC
  Offset(41),               // Offset(40) : Offset(40), Reserved bytes
  Offset(41),     C6MW, 8,  // Offset(41),    Mwait Hint value for C6
  Offset(42),     C7MW, 8,  // Offset(42),    Mwait Hint value for C7/C7s
  Offset(43),     CDMW, 8,  // Offset(43),    Mwait Hint value for C7/C8/C9/C10
  Offset(46),               // Offset(44) : Offset(45), Reserved bytes
  Offset(46),     C6LT, 16, // Offset(46),    Latency Value for C6
  Offset(48),     C7LT, 16, // Offset(48),    Latency Value for C7/C7S
  Offset(50),     CDLT, 16, // Offset(50),    Latency Value for C8/C9/C10
  Offset(52),     CDLV, 16, // Offset(52),    IO LVL value for C8/C9/C10
  Offset(54),     CDPW, 16, // Offset(54),    Power value for C8/C9/C10
  Offset(56),     MPMF, 8,  // Offset(56),    MiscPowerManagementFlags
  Offset(57),     HWPV, 8,  // Offset(57),    HWP Version
  Offset(85),               // Offset(58) : Offset(84), Reserved bytes
  Offset(85),     LMPS, 8,  // Offset(85),    Max ratio of the slowest core.
  Offset(86),     ITBM, 8,  // Offset(86),    Enable/Disable Intel Turbo Boost Max Technology 3.0.
  Offset(87),     OBIN, 8,  // Offset(87),    Indicates bins of Oc support. MSR 194h FLEX_RATIO Bits (19:17)
  Offset(88),     TXTE, 8,  // Offset(88),    Indicates whether TXT is enabled or not based on MSR 0x3A
  Offset(89),     HWPE, 8,  // Offset(89),    HWP Enable
  Offset(90),     HTRO, 8,  // Offset(90),    Indicates whether Hetero is supported by SoC
  Offset(91),     CM00, 8,  // Offset(91),    Indicates the number of cores in a module and module ID of Processor 0. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(92),     CM01, 8,  // Offset(92),    Indicates the number of cores in a module and module ID of Processor 1. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(93),     CM02, 8,  // Offset(93),    Indicates the number of cores in a module and module ID of Processor 2. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(94),     CM03, 8,  // Offset(94),    Indicates the number of cores in a module and module ID of Processor 3. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(95),     CM04, 8,  // Offset(95),    Indicates the number of cores in a module and module ID of Processor 4. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(96),     CM05, 8,  // Offset(96),    Indicates the number of cores in a module and module ID of Processor 5. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(97),     CM06, 8,  // Offset(97),    Indicates the number of cores in a module and module ID of Processor 6. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(98),     CM07, 8,  // Offset(98),    Indicates the number of cores in a module and module ID of Processor 7. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(99),     CM08, 8,  // Offset(99),    Indicates the number of cores in a module and module ID of Processor 8. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(100),    CM09, 8,  // Offset(100),   Indicates the number of cores in a module and module ID of Processor 9. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(101),    CM10, 8,  // Offset(101),   Indicates the number of cores in a module and module ID of Processor 10. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(102),    CM11, 8,  // Offset(102),   Indicates the number of cores in a module and module ID of Processor 11. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(103),    CM12, 8,  // Offset(103),   Indicates the number of cores in a module and module ID of Processor 12. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(104),    CM13, 8,  // Offset(104),   Indicates the number of cores in a module and module ID of Processor 13. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(105),    CM14, 8,  // Offset(105),   Indicates the number of cores in a module and module ID of Processor 14. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(106),    CM15, 8,  // Offset(106),   Indicates the number of cores in a module and module ID of Processor 15. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(107),    CM16, 8,  // Offset(107),   Indicates the number of cores in a module and module ID of Processor 16. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(108),    CM17, 8,  // Offset(108),   Indicates the number of cores in a module and module ID of Processor 17. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(109),    CM18, 8,  // Offset(109),   Indicates the number of cores in a module and module ID of Processor 18. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(110),    CM19, 8,  // Offset(110),   Indicates the number of cores in a module and module ID of Processor 19. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(111),    CM20, 8,  // Offset(111),   Indicates the number of cores in a module and module ID of Processor 20. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(112),    CM21, 8,  // Offset(112),   Indicates the number of cores in a module and module ID of Processor 21. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(113),    CM22, 8,  // Offset(113),   Indicates the number of cores in a module and module ID of Processor 22. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(114),    CM23, 8,  // Offset(114),   Indicates the number of cores in a module and module ID of Processor 23. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(115),    CM24, 8,  // Offset(115),   Indicates the number of cores in a module and module ID of Processor 24. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(116),    CM25, 8,  // Offset(116),   Indicates the number of cores in a module and module ID of Processor 25. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(117),    CM26, 8,  // Offset(117),   Indicates the number of cores in a module and module ID of Processor 26. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(118),    CM27, 8,  // Offset(118),   Indicates the number of cores in a module and module ID of Processor 27. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(119),    CM28, 8,  // Offset(119),   Indicates the number of cores in a module and module ID of Processor 28. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(120),    CM29, 8,  // Offset(120),   Indicates the number of cores in a module and module ID of Processor 29. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(121),    CM30, 8,  // Offset(121),   Indicates the number of cores in a module and module ID of Processor 30. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(122),    CM31, 8,  // Offset(122),   Indicates the number of cores in a module and module ID of Processor 31. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(123),    CM32, 8,  // Offset(123),   Indicates the number of cores in a module and module ID of Processor 32. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(124),    CM33, 8,  // Offset(124),   Indicates the number of cores in a module and module ID of Processor 33. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(125),    CM34, 8,  // Offset(125),   Indicates the number of cores in a module and module ID of Processor 34. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(126),    CM35, 8,  // Offset(126),   Indicates the number of cores in a module and module ID of Processor 35. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(127),    CM36, 8,  // Offset(127),   Indicates the number of cores in a module and module ID of Processor 36. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(128),    CM37, 8,  // Offset(128),   Indicates the number of cores in a module and module ID of Processor 37. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(129),    CM38, 8,  // Offset(129),   Indicates the number of cores in a module and module ID of Processor 38. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(130),    CM39, 8,  // Offset(130),   Indicates the number of cores in a module and module ID of Processor 39. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(131),    CM40, 8,  // Offset(131),   Indicates the number of cores in a module and module ID of Processor 40. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(132),    CM41, 8,  // Offset(132),   Indicates the number of cores in a module and module ID of Processor 41. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(133),    CM42, 8,  // Offset(133),   Indicates the number of cores in a module and module ID of Processor 42. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(134),    CM43, 8,  // Offset(134),   Indicates the number of cores in a module and module ID of Processor 43. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(135),    CM44, 8,  // Offset(135),   Indicates the number of cores in a module and module ID of Processor 44. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(136),    CM45, 8,  // Offset(136),   Indicates the number of cores in a module and module ID of Processor 45. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(137),    CM46, 8,  // Offset(137),   Indicates the number of cores in a module and module ID of Processor 46. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(138),    CM47, 8,  // Offset(138),   Indicates the number of cores in a module and module ID of Processor 47. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(139),    CM48, 8,  // Offset(139),   Indicates the number of cores in a module and module ID of Processor 48. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(140),    CM49, 8,  // Offset(140),   Indicates the number of cores in a module and module ID of Processor 49. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(141),    CM50, 8,  // Offset(141),   Indicates the number of cores in a module and module ID of Processor 50. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(142),    CM51, 8,  // Offset(142),   Indicates the number of cores in a module and module ID of Processor 51. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(143),    CM52, 8,  // Offset(143),   Indicates the number of cores in a module and module ID of Processor 52. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(144),    CM53, 8,  // Offset(144),   Indicates the number of cores in a module and module ID of Processor 53. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(145),    CM54, 8,  // Offset(145),   Indicates the number of cores in a module and module ID of Processor 54. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(146),    CM55, 8,  // Offset(146),   Indicates the number of cores in a module and module ID of Processor 55. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(147),    CM56, 8,  // Offset(147),   Indicates the number of cores in a module and module ID of Processor 56. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(148),    CM57, 8,  // Offset(148),   Indicates the number of cores in a module and module ID of Processor 57. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(149),    CM58, 8,  // Offset(149),   Indicates the number of cores in a module and module ID of Processor 58. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(150),    CM59, 8,  // Offset(150),   Indicates the number of cores in a module and module ID of Processor 59. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(151),    CM60, 8,  // Offset(151),   Indicates the number of cores in a module and module ID of Processor 60. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(152),    CM61, 8,  // Offset(152),   Indicates the number of cores in a module and module ID of Processor 61. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(153),    CM62, 8,  // Offset(153),   Indicates the number of cores in a module and module ID of Processor 62. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(154),    CM63, 8,  // Offset(154),   Indicates the number of cores in a module and module ID of Processor 63. 07:4 - Number of cores in a module. 3:0 - ModuleID
  Offset(155),    CORE, 32, // Offset(155),   Each bit indicates the core type
  Offset(159),    SFSC, 16, // Offset(159),   Indicates the Scaling Factor for Small Core
  Offset(161),    SFBC, 16, // Offset(161),   Indicates the Scaling Factor for Big Core
  Offset(163),    NMFQ, 16, // Offset(163),   Nominal Frequency
  Offset(165),    INFS, 8,  // Offset(165),   Indicates if Nominal Frequency is supported
  }
