/**@file
 VER4 GPIO data for use with GPIO ASL lib

  Copyright (c) 2021, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#include <GpioAcpiDefines.h>
#include <GpioAcpiDefinesAdl.h>

#include <Register/PchRegsGpio.h>
#include <Register/PchRegsGpioVer4.h>

//
// If in GPIO_GROUP_INFO structure certain register doesn't exist
// it will have value equal to NO_REGISTER_FOR_PROPERTY
//
#define NO_REGISTER_FOR_PROPERTY 0xFFFF

//
// If in GPIO_GROUP_INFO structure certain group should not be used
// by GPIO OS driver then "Gpio base number" field should be set to below value
//
#define GPIO_OS_DRV_NOT_SUPPORTED 0xFFFF

//
// GPIO Library objects
//
Scope(\_SB)
{
  //
  // GPIO information data structure
  //

  //
  // GPIO information data structure for PCH-S
  //
  Name(GPCS, Package(){
    Package(){ // GPP_I
      PCH_GPIO_COM0,
      GPIO_VER4_PCH_S_GPIO_GPP_I_PAD_MAX,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_I_PADCFG_OFFSET,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_I_HOSTSW_OWN,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_I_PAD_OWN,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_I_GPI_GPE_STS,
      GPIO_VER4_S_DRIVER_GPP_I0
    },
    Package(){ // GPP_R
      PCH_GPIO_COM0,
      GPIO_VER4_PCH_S_GPIO_GPP_R_PAD_MAX,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_R_PADCFG_OFFSET,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_R_HOSTSW_OWN,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_R_PAD_OWN,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_R_GPI_GPE_STS,
      GPIO_VER4_S_DRIVER_GPP_R0
    },
    Package(){ // GPP_J
      PCH_GPIO_COM0,
      GPIO_VER4_PCH_S_GPIO_GPP_J_PAD_MAX,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_J_PADCFG_OFFSET,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_J_HOSTSW_OWN,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_J_PAD_OWN,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_J_GPI_GPE_STS,
      GPIO_VER4_S_DRIVER_GPP_B0
    },
    Package(){ // VGPIO
      PCH_GPIO_COM0,
      GPIO_VER4_PCH_S_GPIO_VGPIO_PAD_MAX,
      R_GPIO_VER4_PCH_S_GPIO_PCR_VGPIO_PADCFG_OFFSET,
      R_GPIO_VER4_PCH_S_GPIO_PCR_VGPIO_HOSTSW_OWN,
      R_GPIO_VER4_PCH_S_GPIO_PCR_VGPIO_PAD_OWN,
      R_GPIO_VER4_PCH_S_GPIO_PCR_VGPIO_GPI_GPE_STS,
      GPIO_VER4_S_DRIVER_VGPIO0
    },
    Package(){ // VGPIO_0
      PCH_GPIO_COM0,
      GPIO_VER4_PCH_S_GPIO_VGPIO_0_PAD_MAX,
      R_GPIO_VER4_PCH_S_GPIO_PCR_VGPIO_0_PADCFG_OFFSET,
      R_GPIO_VER4_PCH_S_GPIO_PCR_VGPIO_0_HOSTSW_OWN,
      R_GPIO_VER4_PCH_S_GPIO_PCR_VGPIO_0_PAD_OWN,
      R_GPIO_VER4_PCH_S_GPIO_PCR_VGPIO_0_GPI_GPE_STS,
      GPIO_VER4_S_DRIVER_VGPIO_0_0
    },
    Package(){ // GPP_B
      PCH_GPIO_COM1,
      GPIO_VER4_PCH_S_GPIO_GPP_B_PAD_MAX,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_B_PADCFG_OFFSET,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_B_HOSTSW_OWN,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_B_PAD_OWN,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_B_GPI_GPE_STS,
      GPIO_VER4_S_DRIVER_GPP_B0
    },
    Package(){ // GPP_G
      PCH_GPIO_COM1,
      GPIO_VER4_PCH_S_GPIO_GPP_G_PAD_MAX,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_G_PADCFG_OFFSET,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_G_HOSTSW_OWN,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_G_PAD_OWN,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_G_GPI_GPE_STS,
      GPIO_VER4_S_DRIVER_GPP_G0
    },
    Package(){ // GPP_H
      PCH_GPIO_COM1,
      GPIO_VER4_PCH_S_GPIO_GPP_H_PAD_MAX,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_H_PADCFG_OFFSET,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_H_HOSTSW_OWN,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_H_PAD_OWN,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_H_GPI_GPE_STS,
      GPIO_VER4_S_DRIVER_GPP_H0
    },
    Package(){ // GPD
      PCH_GPIO_COM2,
      GPIO_VER4_PCH_S_GPIO_GPD_PAD_MAX,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPD_PADCFG_OFFSET,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPD_HOSTSW_OWN,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPD_PAD_OWN,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPD_GPI_GPE_STS,
      0 // TBD
    },
    Package(){ // SPI
      PCH_GPIO_COM3,
      GPIO_VER4_PCH_S_GPIO_SPI_PAD_MAX,
      R_GPIO_VER4_PCH_S_GPIO_PCR_SPI_PADCFG_OFFSET,
      R_GPIO_VER4_PCH_S_GPIO_PCR_SPI_HOSTSW_OWN,
      R_GPIO_VER4_PCH_S_GPIO_PCR_SPI_PAD_OWN,
      R_GPIO_VER4_PCH_S_GPIO_PCR_SPI_GPI_GPE_STS,
      0 // TBD
    },
    Package(){ // GPP_A
      PCH_GPIO_COM3,
      GPIO_VER4_PCH_S_GPIO_GPP_A_PAD_MAX,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_A_PADCFG_OFFSET,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_A_HOSTSW_OWN,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_A_PAD_OWN,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_A_GPI_GPE_STS,
      GPIO_VER4_S_DRIVER_GPP_A0
    },
    Package(){ // GPP_C
      PCH_GPIO_COM3,
      GPIO_VER4_PCH_S_GPIO_GPP_C_PAD_MAX,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_C_PADCFG_OFFSET,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_C_HOSTSW_OWN,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_C_PAD_OWN,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_C_GPI_GPE_STS,
      GPIO_VER4_S_DRIVER_GPP_C0
    },
    Package(){ // VGPIO_3
      PCH_GPIO_COM3,
      GPIO_VER4_PCH_S_GPIO_VGPIO_3_PAD_MAX,
      R_GPIO_VER4_PCH_S_GPIO_PCR_VGPIO_3_PADCFG_OFFSET,
      R_GPIO_VER4_PCH_S_GPIO_PCR_VGPIO_3_HOSTSW_OWN,
      R_GPIO_VER4_PCH_S_GPIO_PCR_VGPIO_3_PAD_OWN,
      R_GPIO_VER4_PCH_S_GPIO_PCR_VGPIO_3_GPI_GPE_STS,
      GPIO_VER4_S_DRIVER_VGPIO30
    },
    Package(){ // GPP_S
      PCH_GPIO_COM4,
      GPIO_VER4_PCH_S_GPIO_GPP_S_PAD_MAX,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_S_PADCFG_OFFSET,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_S_HOSTSW_OWN,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_S_PAD_OWN,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_S_GPI_GPE_STS,
      GPIO_VER4_S_DRIVER_GPP_S0
    },
    Package(){ // GPP_E
      PCH_GPIO_COM4,
      GPIO_VER4_PCH_S_GPIO_GPP_E_PAD_MAX,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_E_PADCFG_OFFSET,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_E_HOSTSW_OWN,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_E_PAD_OWN,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_E_GPI_GPE_STS,
      GPIO_VER4_S_DRIVER_GPP_E0
    },
    Package(){ // GPP_K
      PCH_GPIO_COM4,
      GPIO_VER4_PCH_S_GPIO_GPP_K_PAD_MAX,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_K_PADCFG_OFFSET,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_K_HOSTSW_OWN,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_K_PAD_OWN,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_K_GPI_GPE_STS,
      GPIO_VER4_S_DRIVER_GPP_K0
    },
    Package(){ // GPP_F
      PCH_GPIO_COM4,
      GPIO_VER4_PCH_S_GPIO_GPP_F_PAD_MAX,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_F_PADCFG_OFFSET,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_F_HOSTSW_OWN,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_F_PAD_OWN,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_F_GPI_GPE_STS,
      GPIO_VER4_S_DRIVER_GPP_F0
    },
    Package(){ // GPP_D
      PCH_GPIO_COM5,
      GPIO_VER4_PCH_S_GPIO_GPP_D_PAD_MAX,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_D_PADCFG_OFFSET,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_D_HOSTSW_OWN,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_D_PAD_OWN,
      R_GPIO_VER4_PCH_S_GPIO_PCR_GPP_D_GPI_GPE_STS,
      GPIO_VER4_S_DRIVER_GPP_D0
    }
  })

  //
  // Object for storing RX Level/Edge Configuration for all pads.
  // One fields contains data for one pad.
  //   00b = Level
  //   01b = Edge (RxInv=0 for rising edge; 1 for falling edge)
  //   10b = Disabled
  //   11b = Either rising edge or falling edge
  //
  // Each row has data for one group. Buffer size needs
  // to equal to number of pads
  Name(RXEV, Package(){
    Buffer(GPIO_VER4_PCH_S_GPIO_GPP_I_PAD_MAX){},   // PCH-S: GPP_I
    Buffer(GPIO_VER4_PCH_S_GPIO_GPP_R_PAD_MAX){},   // PCH-S: GPP_R
    Buffer(GPIO_VER4_PCH_S_GPIO_GPP_J_PAD_MAX){},   // PCH-S: GPP_J
    Buffer(GPIO_VER4_PCH_S_GPIO_VGPIO_PAD_MAX){},   // PCH-S: VGPIO
    Buffer(GPIO_VER4_PCH_S_GPIO_VGPIO_0_PAD_MAX){}, // PCH-S: VGPIO0
    Buffer(GPIO_VER4_PCH_S_GPIO_GPP_B_PAD_MAX){},   // PCH-S: GPP_B
    Buffer(GPIO_VER4_PCH_S_GPIO_GPP_G_PAD_MAX){},   // PCH-S: GPP_G
    Buffer(GPIO_VER4_PCH_S_GPIO_GPP_H_PAD_MAX){},   // PCH-S: GPP_H
    Buffer(GPIO_VER4_PCH_S_GPIO_GPD_PAD_MAX){},     // PCH-S: GPD
    Buffer(GPIO_VER4_PCH_S_GPIO_SPI_PAD_MAX){},     // PCH-S: SPI
    Buffer(GPIO_VER4_PCH_S_GPIO_GPP_A_PAD_MAX){},   // PCH-S: GPP_A
    Buffer(GPIO_VER4_PCH_S_GPIO_GPP_C_PAD_MAX){},   // PCH-S: GPP_C
    Buffer(GPIO_VER4_PCH_S_GPIO_VGPIO_3_PAD_MAX){}, // PCH-S: VGPIO3
    Buffer(GPIO_VER4_PCH_S_GPIO_GPP_S_PAD_MAX){},   // PCH-S: GPP_S
    Buffer(GPIO_VER4_PCH_S_GPIO_GPP_E_PAD_MAX){},   // PCH-S: GPP_E
    Buffer(GPIO_VER4_PCH_S_GPIO_GPP_K_PAD_MAX){},   // PCH-S: GPP_K
    Buffer(GPIO_VER4_PCH_S_GPIO_GPP_F_PAD_MAX){},   // PCH-S: GPP_F
    Buffer(GPIO_VER4_PCH_S_GPIO_GPP_D_PAD_MAX){}    // PCH-S: GPP_D
  })
}
