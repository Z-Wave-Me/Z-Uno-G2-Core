#ifndef CRTX_CMU_H
#define CRTX_CMU_H

#include "Arduino.h"

/***************************************************************************//**
 * @file
 * @brief ZGM13_CMU register and bit field definitions
 * @version 5.8.1
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

// #if defined(__ICCARM__)
// #pragma system_include       /* Treat file as system include file. */
// #elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
// #pragma clang system_header  /* Treat file as system include file. */
// #endif

/***************************************************************************//**
 * @addtogroup Parts
 * @{
 ******************************************************************************/
/***************************************************************************//**
 * @defgroup ZGM13_CMU CMU
 * @{
 * @brief ZGM13_CMU Register Declaration
 ******************************************************************************/
/** CMU Register Declaration */
typedef struct {
  __IOM uint32_t CTRL;                /**< CMU Control Register  */

  uint32_t       RESERVED0[3U];       /**< Reserved for future use **/
  __IOM uint32_t HFRCOCTRL;           /**< HFRCO Control Register  */

  uint32_t       RESERVED1[1U];       /**< Reserved for future use **/
  __IOM uint32_t AUXHFRCOCTRL;        /**< AUXHFRCO Control Register  */

  uint32_t       RESERVED2[1U];       /**< Reserved for future use **/
  __IOM uint32_t LFRCOCTRL;           /**< LFRCO Control Register  */
  __IOM uint32_t HFXOCTRL;            /**< HFXO Control Register  */

  uint32_t       RESERVED3[1U];       /**< Reserved for future use **/
  __IOM uint32_t HFXOSTARTUPCTRL;     /**< HFXO Startup Control  */
  __IOM uint32_t HFXOSTEADYSTATECTRL; /**< HFXO Steady State Control  */
  __IOM uint32_t HFXOTIMEOUTCTRL;     /**< HFXO Timeout Control  */
  __IOM uint32_t LFXOCTRL;            /**< LFXO Control Register  */

  uint32_t       RESERVED4[1U];       /**< Reserved for future use **/
  __IOM uint32_t DPLLCTRL;            /**< DPLL Control Register  */
  __IOM uint32_t DPLLCTRL1;           /**< DPLL Control Register  */
  uint32_t       RESERVED5[2U];       /**< Reserved for future use **/
  __IOM uint32_t CALCTRL;             /**< Calibration Control Register  */
  __IOM uint32_t CALCNT;              /**< Calibration Counter Register  */
  uint32_t       RESERVED6[2U];       /**< Reserved for future use **/
  __IOM uint32_t OSCENCMD;            /**< Oscillator Enable/Disable Command Register  */
  __IOM uint32_t CMD;                 /**< Command Register  */
  uint32_t       RESERVED7[2U];       /**< Reserved for future use **/
  __IOM uint32_t DBGCLKSEL;           /**< Debug Trace Clock Select  */
  __IOM uint32_t HFCLKSEL;            /**< High Frequency Clock Select Command Register  */
  uint32_t       RESERVED8[2U];       /**< Reserved for future use **/
  __IOM uint32_t LFACLKSEL;           /**< Low Frequency A Clock Select Register  */
  __IOM uint32_t LFBCLKSEL;           /**< Low Frequency B Clock Select Register  */
  __IOM uint32_t LFECLKSEL;           /**< Low Frequency E Clock Select Register  */

  uint32_t       RESERVED9[1U];       /**< Reserved for future use **/
  __IM uint32_t  STATUS;              /**< Status Register  */
  __IM uint32_t  HFCLKSTATUS;         /**< HFCLK Status Register  */
  uint32_t       RESERVED10[1U];      /**< Reserved for future use **/
  __IM uint32_t  HFXOTRIMSTATUS;      /**< HFXO Trim Status  */
  __IM uint32_t  IF;                  /**< Interrupt Flag Register  */
  __IOM uint32_t IFS;                 /**< Interrupt Flag Set Register  */
  __IOM uint32_t IFC;                 /**< Interrupt Flag Clear Register  */
  __IOM uint32_t IEN;                 /**< Interrupt Enable Register  */
  __IOM uint32_t HFBUSCLKEN0;         /**< High Frequency Bus Clock Enable Register 0  */

  uint32_t       RESERVED11[3U];      /**< Reserved for future use **/
  __IOM uint32_t HFPERCLKEN0;         /**< High Frequency Peripheral Clock Enable Register 0  */

  uint32_t       RESERVED12[7U];      /**< Reserved for future use **/
  __IOM uint32_t LFACLKEN0;           /**< Low Frequency a Clock Enable Register 0  (Async Reg)  */
  uint32_t       RESERVED13[1U];      /**< Reserved for future use **/
  __IOM uint32_t LFBCLKEN0;           /**< Low Frequency B Clock Enable Register 0 (Async Reg)  */

  uint32_t       RESERVED14[1U];      /**< Reserved for future use **/
  __IOM uint32_t LFECLKEN0;           /**< Low Frequency E Clock Enable Register 0 (Async Reg)  */
  uint32_t       RESERVED15[3U];      /**< Reserved for future use **/
  __IOM uint32_t HFPRESC;             /**< High Frequency Clock Prescaler Register  */

  uint32_t       RESERVED16[1U];      /**< Reserved for future use **/
  __IOM uint32_t HFCOREPRESC;         /**< High Frequency Core Clock Prescaler Register  */
  __IOM uint32_t HFPERPRESC;          /**< High Frequency Peripheral Clock Prescaler Register  */

  uint32_t       RESERVED17[1U];      /**< Reserved for future use **/
  __IOM uint32_t HFEXPPRESC;          /**< High Frequency Export Clock Prescaler Register  */

  uint32_t       RESERVED18[2U];      /**< Reserved for future use **/
  __IOM uint32_t LFAPRESC0;           /**< Low Frequency a Prescaler Register 0 (Async Reg)  */
  uint32_t       RESERVED19[1U];      /**< Reserved for future use **/
  __IOM uint32_t LFBPRESC0;           /**< Low Frequency B Prescaler Register 0  (Async Reg)  */
  uint32_t       RESERVED20[1U];      /**< Reserved for future use **/
  __IOM uint32_t LFEPRESC0;           /**< Low Frequency E Prescaler Register 0  (Async Reg)  */

  uint32_t       RESERVED21[3U];      /**< Reserved for future use **/
  __IM uint32_t  SYNCBUSY;            /**< Synchronization Busy Register  */
  __IOM uint32_t FREEZE;              /**< Freeze Register  */
  uint32_t       RESERVED22[2U];      /**< Reserved for future use **/
  __IOM uint32_t PCNTCTRL;            /**< PCNT Control Register  */

  uint32_t       RESERVED23[2U];      /**< Reserved for future use **/
  __IOM uint32_t ADCCTRL;             /**< ADC Control Register  */

  uint32_t       RESERVED24[4U];      /**< Reserved for future use **/
  __IOM uint32_t ROUTEPEN;            /**< I/O Routing Pin Enable Register  */
  __IOM uint32_t ROUTELOC0;           /**< I/O Routing Location Register  */
  __IOM uint32_t ROUTELOC1;           /**< I/O Routing Location Register  */
  uint32_t       RESERVED25[1U];      /**< Reserved for future use **/
  __IOM uint32_t LOCK;                /**< Configuration Lock Register  */
  __IOM uint32_t HFRCOSS;             /**< HFRCO Spread Spectrum Register  */
} CMU_TypeDef;                        /** @} */

/***************************************************************************//**
 * @addtogroup ZGM13_CMU
 * @{
 * @defgroup ZGM13_CMU_BitFields  CMU Bit Fields
 * @{
 ******************************************************************************/

/* Bit fields for CMU CTRL */
#define _CMU_CTRL_RESETVALUE                              0x00300000UL                          /**< Default value for CMU_CTRL */
#define _CMU_CTRL_MASK                                    0x001103FFUL                          /**< Mask for CMU_CTRL */
#define _CMU_CTRL_CLKOUTSEL0_SHIFT                        0                                     /**< Shift value for CMU_CLKOUTSEL0 */
#define _CMU_CTRL_CLKOUTSEL0_MASK                         0x1FUL                                /**< Bit mask for CMU_CLKOUTSEL0 */
#define _CMU_CTRL_CLKOUTSEL0_DEFAULT                      0x00000000UL                          /**< Mode DEFAULT for CMU_CTRL */
#define _CMU_CTRL_CLKOUTSEL0_DISABLED                     0x00000000UL                          /**< Mode DISABLED for CMU_CTRL */
#define _CMU_CTRL_CLKOUTSEL0_ULFRCO                       0x00000001UL                          /**< Mode ULFRCO for CMU_CTRL */
#define _CMU_CTRL_CLKOUTSEL0_LFRCO                        0x00000002UL                          /**< Mode LFRCO for CMU_CTRL */
#define _CMU_CTRL_CLKOUTSEL0_LFXO                         0x00000003UL                          /**< Mode LFXO for CMU_CTRL */
#define _CMU_CTRL_CLKOUTSEL0_HFXO                         0x00000006UL                          /**< Mode HFXO for CMU_CTRL */
#define _CMU_CTRL_CLKOUTSEL0_HFEXPCLK                     0x00000007UL                          /**< Mode HFEXPCLK for CMU_CTRL */
#define _CMU_CTRL_CLKOUTSEL0_ULFRCOQ                      0x00000009UL                          /**< Mode ULFRCOQ for CMU_CTRL */
#define _CMU_CTRL_CLKOUTSEL0_LFRCOQ                       0x0000000AUL                          /**< Mode LFRCOQ for CMU_CTRL */
#define _CMU_CTRL_CLKOUTSEL0_LFXOQ                        0x0000000BUL                          /**< Mode LFXOQ for CMU_CTRL */
#define _CMU_CTRL_CLKOUTSEL0_HFRCOQ                       0x0000000CUL                          /**< Mode HFRCOQ for CMU_CTRL */
#define _CMU_CTRL_CLKOUTSEL0_AUXHFRCOQ                    0x0000000DUL                          /**< Mode AUXHFRCOQ for CMU_CTRL */
#define _CMU_CTRL_CLKOUTSEL0_HFXOQ                        0x0000000EUL                          /**< Mode HFXOQ for CMU_CTRL */
#define _CMU_CTRL_CLKOUTSEL0_HFSRCCLK                     0x0000000FUL                          /**< Mode HFSRCCLK for CMU_CTRL */
#define CMU_CTRL_CLKOUTSEL0_DEFAULT                       (_CMU_CTRL_CLKOUTSEL0_DEFAULT << 0)   /**< Shifted mode DEFAULT for CMU_CTRL */
#define CMU_CTRL_CLKOUTSEL0_DISABLED                      (_CMU_CTRL_CLKOUTSEL0_DISABLED << 0)  /**< Shifted mode DISABLED for CMU_CTRL */
#define CMU_CTRL_CLKOUTSEL0_ULFRCO                        (_CMU_CTRL_CLKOUTSEL0_ULFRCO << 0)    /**< Shifted mode ULFRCO for CMU_CTRL */
#define CMU_CTRL_CLKOUTSEL0_LFRCO                         (_CMU_CTRL_CLKOUTSEL0_LFRCO << 0)     /**< Shifted mode LFRCO for CMU_CTRL */
#define CMU_CTRL_CLKOUTSEL0_LFXO                          (_CMU_CTRL_CLKOUTSEL0_LFXO << 0)      /**< Shifted mode LFXO for CMU_CTRL */
#define CMU_CTRL_CLKOUTSEL0_HFXO                          (_CMU_CTRL_CLKOUTSEL0_HFXO << 0)      /**< Shifted mode HFXO for CMU_CTRL */
#define CMU_CTRL_CLKOUTSEL0_HFEXPCLK                      (_CMU_CTRL_CLKOUTSEL0_HFEXPCLK << 0)  /**< Shifted mode HFEXPCLK for CMU_CTRL */
#define CMU_CTRL_CLKOUTSEL0_ULFRCOQ                       (_CMU_CTRL_CLKOUTSEL0_ULFRCOQ << 0)   /**< Shifted mode ULFRCOQ for CMU_CTRL */
#define CMU_CTRL_CLKOUTSEL0_LFRCOQ                        (_CMU_CTRL_CLKOUTSEL0_LFRCOQ << 0)    /**< Shifted mode LFRCOQ for CMU_CTRL */
#define CMU_CTRL_CLKOUTSEL0_LFXOQ                         (_CMU_CTRL_CLKOUTSEL0_LFXOQ << 0)     /**< Shifted mode LFXOQ for CMU_CTRL */
#define CMU_CTRL_CLKOUTSEL0_HFRCOQ                        (_CMU_CTRL_CLKOUTSEL0_HFRCOQ << 0)    /**< Shifted mode HFRCOQ for CMU_CTRL */
#define CMU_CTRL_CLKOUTSEL0_AUXHFRCOQ                     (_CMU_CTRL_CLKOUTSEL0_AUXHFRCOQ << 0) /**< Shifted mode AUXHFRCOQ for CMU_CTRL */
#define CMU_CTRL_CLKOUTSEL0_HFXOQ                         (_CMU_CTRL_CLKOUTSEL0_HFXOQ << 0)     /**< Shifted mode HFXOQ for CMU_CTRL */
#define CMU_CTRL_CLKOUTSEL0_HFSRCCLK                      (_CMU_CTRL_CLKOUTSEL0_HFSRCCLK << 0)  /**< Shifted mode HFSRCCLK for CMU_CTRL */
#define _CMU_CTRL_CLKOUTSEL1_SHIFT                        5                                     /**< Shift value for CMU_CLKOUTSEL1 */
#define _CMU_CTRL_CLKOUTSEL1_MASK                         0x3E0UL                               /**< Bit mask for CMU_CLKOUTSEL1 */
#define _CMU_CTRL_CLKOUTSEL1_DEFAULT                      0x00000000UL                          /**< Mode DEFAULT for CMU_CTRL */
#define _CMU_CTRL_CLKOUTSEL1_DISABLED                     0x00000000UL                          /**< Mode DISABLED for CMU_CTRL */
#define _CMU_CTRL_CLKOUTSEL1_ULFRCO                       0x00000001UL                          /**< Mode ULFRCO for CMU_CTRL */
#define _CMU_CTRL_CLKOUTSEL1_LFRCO                        0x00000002UL                          /**< Mode LFRCO for CMU_CTRL */
#define _CMU_CTRL_CLKOUTSEL1_LFXO                         0x00000003UL                          /**< Mode LFXO for CMU_CTRL */
#define _CMU_CTRL_CLKOUTSEL1_HFXO                         0x00000006UL                          /**< Mode HFXO for CMU_CTRL */
#define _CMU_CTRL_CLKOUTSEL1_HFEXPCLK                     0x00000007UL                          /**< Mode HFEXPCLK for CMU_CTRL */
#define _CMU_CTRL_CLKOUTSEL1_ULFRCOQ                      0x00000009UL                          /**< Mode ULFRCOQ for CMU_CTRL */
#define _CMU_CTRL_CLKOUTSEL1_LFRCOQ                       0x0000000AUL                          /**< Mode LFRCOQ for CMU_CTRL */
#define _CMU_CTRL_CLKOUTSEL1_LFXOQ                        0x0000000BUL                          /**< Mode LFXOQ for CMU_CTRL */
#define _CMU_CTRL_CLKOUTSEL1_HFRCOQ                       0x0000000CUL                          /**< Mode HFRCOQ for CMU_CTRL */
#define _CMU_CTRL_CLKOUTSEL1_AUXHFRCOQ                    0x0000000DUL                          /**< Mode AUXHFRCOQ for CMU_CTRL */
#define _CMU_CTRL_CLKOUTSEL1_HFXOQ                        0x0000000EUL                          /**< Mode HFXOQ for CMU_CTRL */
#define _CMU_CTRL_CLKOUTSEL1_HFSRCCLK                     0x0000000FUL                          /**< Mode HFSRCCLK for CMU_CTRL */
#define CMU_CTRL_CLKOUTSEL1_DEFAULT                       (_CMU_CTRL_CLKOUTSEL1_DEFAULT << 5)   /**< Shifted mode DEFAULT for CMU_CTRL */
#define CMU_CTRL_CLKOUTSEL1_DISABLED                      (_CMU_CTRL_CLKOUTSEL1_DISABLED << 5)  /**< Shifted mode DISABLED for CMU_CTRL */
#define CMU_CTRL_CLKOUTSEL1_ULFRCO                        (_CMU_CTRL_CLKOUTSEL1_ULFRCO << 5)    /**< Shifted mode ULFRCO for CMU_CTRL */
#define CMU_CTRL_CLKOUTSEL1_LFRCO                         (_CMU_CTRL_CLKOUTSEL1_LFRCO << 5)     /**< Shifted mode LFRCO for CMU_CTRL */
#define CMU_CTRL_CLKOUTSEL1_LFXO                          (_CMU_CTRL_CLKOUTSEL1_LFXO << 5)      /**< Shifted mode LFXO for CMU_CTRL */
#define CMU_CTRL_CLKOUTSEL1_HFXO                          (_CMU_CTRL_CLKOUTSEL1_HFXO << 5)      /**< Shifted mode HFXO for CMU_CTRL */
#define CMU_CTRL_CLKOUTSEL1_HFEXPCLK                      (_CMU_CTRL_CLKOUTSEL1_HFEXPCLK << 5)  /**< Shifted mode HFEXPCLK for CMU_CTRL */
#define CMU_CTRL_CLKOUTSEL1_ULFRCOQ                       (_CMU_CTRL_CLKOUTSEL1_ULFRCOQ << 5)   /**< Shifted mode ULFRCOQ for CMU_CTRL */
#define CMU_CTRL_CLKOUTSEL1_LFRCOQ                        (_CMU_CTRL_CLKOUTSEL1_LFRCOQ << 5)    /**< Shifted mode LFRCOQ for CMU_CTRL */
#define CMU_CTRL_CLKOUTSEL1_LFXOQ                         (_CMU_CTRL_CLKOUTSEL1_LFXOQ << 5)     /**< Shifted mode LFXOQ for CMU_CTRL */
#define CMU_CTRL_CLKOUTSEL1_HFRCOQ                        (_CMU_CTRL_CLKOUTSEL1_HFRCOQ << 5)    /**< Shifted mode HFRCOQ for CMU_CTRL */
#define CMU_CTRL_CLKOUTSEL1_AUXHFRCOQ                     (_CMU_CTRL_CLKOUTSEL1_AUXHFRCOQ << 5) /**< Shifted mode AUXHFRCOQ for CMU_CTRL */
#define CMU_CTRL_CLKOUTSEL1_HFXOQ                         (_CMU_CTRL_CLKOUTSEL1_HFXOQ << 5)     /**< Shifted mode HFXOQ for CMU_CTRL */
#define CMU_CTRL_CLKOUTSEL1_HFSRCCLK                      (_CMU_CTRL_CLKOUTSEL1_HFSRCCLK << 5)  /**< Shifted mode HFSRCCLK for CMU_CTRL */
#define CMU_CTRL_WSHFLE                                   (0x1UL << 16)                         /**< Wait State for High-Frequency LE Interface */
#define _CMU_CTRL_WSHFLE_SHIFT                            16                                    /**< Shift value for CMU_WSHFLE */
#define _CMU_CTRL_WSHFLE_MASK                             0x10000UL                             /**< Bit mask for CMU_WSHFLE */
#define _CMU_CTRL_WSHFLE_DEFAULT                          0x00000000UL                          /**< Mode DEFAULT for CMU_CTRL */
#define CMU_CTRL_WSHFLE_DEFAULT                           (_CMU_CTRL_WSHFLE_DEFAULT << 16)      /**< Shifted mode DEFAULT for CMU_CTRL */
#define CMU_CTRL_HFPERCLKEN                               (0x1UL << 20)                         /**< HFPERCLK Enable */
#define _CMU_CTRL_HFPERCLKEN_SHIFT                        20                                    /**< Shift value for CMU_HFPERCLKEN */
#define _CMU_CTRL_HFPERCLKEN_MASK                         0x100000UL                            /**< Bit mask for CMU_HFPERCLKEN */
#define _CMU_CTRL_HFPERCLKEN_DEFAULT                      0x00000001UL                          /**< Mode DEFAULT for CMU_CTRL */
#define CMU_CTRL_HFPERCLKEN_DEFAULT                       (_CMU_CTRL_HFPERCLKEN_DEFAULT << 20)  /**< Shifted mode DEFAULT for CMU_CTRL */

/* Bit fields for CMU HFRCOCTRL */
#define _CMU_HFRCOCTRL_RESETVALUE                         0xB1481F7FUL                                /**< Default value for CMU_HFRCOCTRL */
#define _CMU_HFRCOCTRL_MASK                               0xFFFF3F7FUL                                /**< Mask for CMU_HFRCOCTRL */
#define _CMU_HFRCOCTRL_TUNING_SHIFT                       0                                           /**< Shift value for CMU_TUNING */
#define _CMU_HFRCOCTRL_TUNING_MASK                        0x7FUL                                      /**< Bit mask for CMU_TUNING */
#define _CMU_HFRCOCTRL_TUNING_DEFAULT                     0x0000007FUL                                /**< Mode DEFAULT for CMU_HFRCOCTRL */
#define CMU_HFRCOCTRL_TUNING_DEFAULT                      (_CMU_HFRCOCTRL_TUNING_DEFAULT << 0)        /**< Shifted mode DEFAULT for CMU_HFRCOCTRL */
#define _CMU_HFRCOCTRL_FINETUNING_SHIFT                   8                                           /**< Shift value for CMU_FINETUNING */
#define _CMU_HFRCOCTRL_FINETUNING_MASK                    0x3F00UL                                    /**< Bit mask for CMU_FINETUNING */
#define _CMU_HFRCOCTRL_FINETUNING_DEFAULT                 0x0000001FUL                                /**< Mode DEFAULT for CMU_HFRCOCTRL */
#define CMU_HFRCOCTRL_FINETUNING_DEFAULT                  (_CMU_HFRCOCTRL_FINETUNING_DEFAULT << 8)    /**< Shifted mode DEFAULT for CMU_HFRCOCTRL */
#define _CMU_HFRCOCTRL_FREQRANGE_SHIFT                    16                                          /**< Shift value for CMU_FREQRANGE */
#define _CMU_HFRCOCTRL_FREQRANGE_MASK                     0x1F0000UL                                  /**< Bit mask for CMU_FREQRANGE */
#define _CMU_HFRCOCTRL_FREQRANGE_DEFAULT                  0x00000008UL                                /**< Mode DEFAULT for CMU_HFRCOCTRL */
#define CMU_HFRCOCTRL_FREQRANGE_DEFAULT                   (_CMU_HFRCOCTRL_FREQRANGE_DEFAULT << 16)    /**< Shifted mode DEFAULT for CMU_HFRCOCTRL */
#define _CMU_HFRCOCTRL_CMPBIAS_SHIFT                      21                                          /**< Shift value for CMU_CMPBIAS */
#define _CMU_HFRCOCTRL_CMPBIAS_MASK                       0xE00000UL                                  /**< Bit mask for CMU_CMPBIAS */
#define _CMU_HFRCOCTRL_CMPBIAS_DEFAULT                    0x00000002UL                                /**< Mode DEFAULT for CMU_HFRCOCTRL */
#define CMU_HFRCOCTRL_CMPBIAS_DEFAULT                     (_CMU_HFRCOCTRL_CMPBIAS_DEFAULT << 21)      /**< Shifted mode DEFAULT for CMU_HFRCOCTRL */
#define CMU_HFRCOCTRL_LDOHP                               (0x1UL << 24)                               /**< HFRCO LDO High Power Mode */
#define _CMU_HFRCOCTRL_LDOHP_SHIFT                        24                                          /**< Shift value for CMU_LDOHP */
#define _CMU_HFRCOCTRL_LDOHP_MASK                         0x1000000UL                                 /**< Bit mask for CMU_LDOHP */
#define _CMU_HFRCOCTRL_LDOHP_DEFAULT                      0x00000001UL                                /**< Mode DEFAULT for CMU_HFRCOCTRL */
#define CMU_HFRCOCTRL_LDOHP_DEFAULT                       (_CMU_HFRCOCTRL_LDOHP_DEFAULT << 24)        /**< Shifted mode DEFAULT for CMU_HFRCOCTRL */
#define _CMU_HFRCOCTRL_CLKDIV_SHIFT                       25                                          /**< Shift value for CMU_CLKDIV */
#define _CMU_HFRCOCTRL_CLKDIV_MASK                        0x6000000UL                                 /**< Bit mask for CMU_CLKDIV */
#define _CMU_HFRCOCTRL_CLKDIV_DEFAULT                     0x00000000UL                                /**< Mode DEFAULT for CMU_HFRCOCTRL */
#define _CMU_HFRCOCTRL_CLKDIV_DIV1                        0x00000000UL                                /**< Mode DIV1 for CMU_HFRCOCTRL */
#define _CMU_HFRCOCTRL_CLKDIV_DIV2                        0x00000001UL                                /**< Mode DIV2 for CMU_HFRCOCTRL */
#define _CMU_HFRCOCTRL_CLKDIV_DIV4                        0x00000002UL                                /**< Mode DIV4 for CMU_HFRCOCTRL */
#define CMU_HFRCOCTRL_CLKDIV_DEFAULT                      (_CMU_HFRCOCTRL_CLKDIV_DEFAULT << 25)       /**< Shifted mode DEFAULT for CMU_HFRCOCTRL */
#define CMU_HFRCOCTRL_CLKDIV_DIV1                         (_CMU_HFRCOCTRL_CLKDIV_DIV1 << 25)          /**< Shifted mode DIV1 for CMU_HFRCOCTRL */
#define CMU_HFRCOCTRL_CLKDIV_DIV2                         (_CMU_HFRCOCTRL_CLKDIV_DIV2 << 25)          /**< Shifted mode DIV2 for CMU_HFRCOCTRL */
#define CMU_HFRCOCTRL_CLKDIV_DIV4                         (_CMU_HFRCOCTRL_CLKDIV_DIV4 << 25)          /**< Shifted mode DIV4 for CMU_HFRCOCTRL */
#define CMU_HFRCOCTRL_FINETUNINGEN                        (0x1UL << 27)                               /**< Enable Reference for Fine Tuning */
#define _CMU_HFRCOCTRL_FINETUNINGEN_SHIFT                 27                                          /**< Shift value for CMU_FINETUNINGEN */
#define _CMU_HFRCOCTRL_FINETUNINGEN_MASK                  0x8000000UL                                 /**< Bit mask for CMU_FINETUNINGEN */
#define _CMU_HFRCOCTRL_FINETUNINGEN_DEFAULT               0x00000000UL                                /**< Mode DEFAULT for CMU_HFRCOCTRL */
#define CMU_HFRCOCTRL_FINETUNINGEN_DEFAULT                (_CMU_HFRCOCTRL_FINETUNINGEN_DEFAULT << 27) /**< Shifted mode DEFAULT for CMU_HFRCOCTRL */
#define _CMU_HFRCOCTRL_VREFTC_SHIFT                       28                                          /**< Shift value for CMU_VREFTC */
#define _CMU_HFRCOCTRL_VREFTC_MASK                        0xF0000000UL                                /**< Bit mask for CMU_VREFTC */
#define _CMU_HFRCOCTRL_VREFTC_DEFAULT                     0x0000000BUL                                /**< Mode DEFAULT for CMU_HFRCOCTRL */
#define CMU_HFRCOCTRL_VREFTC_DEFAULT                      (_CMU_HFRCOCTRL_VREFTC_DEFAULT << 28)       /**< Shifted mode DEFAULT for CMU_HFRCOCTRL */

/* Bit fields for CMU AUXHFRCOCTRL */
#define _CMU_AUXHFRCOCTRL_RESETVALUE                      0xB1481F7FUL                                   /**< Default value for CMU_AUXHFRCOCTRL */
#define _CMU_AUXHFRCOCTRL_MASK                            0xFFFF3F7FUL                                   /**< Mask for CMU_AUXHFRCOCTRL */
#define _CMU_AUXHFRCOCTRL_TUNING_SHIFT                    0                                              /**< Shift value for CMU_TUNING */
#define _CMU_AUXHFRCOCTRL_TUNING_MASK                     0x7FUL                                         /**< Bit mask for CMU_TUNING */
#define _CMU_AUXHFRCOCTRL_TUNING_DEFAULT                  0x0000007FUL                                   /**< Mode DEFAULT for CMU_AUXHFRCOCTRL */
#define CMU_AUXHFRCOCTRL_TUNING_DEFAULT                   (_CMU_AUXHFRCOCTRL_TUNING_DEFAULT << 0)        /**< Shifted mode DEFAULT for CMU_AUXHFRCOCTRL */
#define _CMU_AUXHFRCOCTRL_FINETUNING_SHIFT                8                                              /**< Shift value for CMU_FINETUNING */
#define _CMU_AUXHFRCOCTRL_FINETUNING_MASK                 0x3F00UL                                       /**< Bit mask for CMU_FINETUNING */
#define _CMU_AUXHFRCOCTRL_FINETUNING_DEFAULT              0x0000001FUL                                   /**< Mode DEFAULT for CMU_AUXHFRCOCTRL */
#define CMU_AUXHFRCOCTRL_FINETUNING_DEFAULT               (_CMU_AUXHFRCOCTRL_FINETUNING_DEFAULT << 8)    /**< Shifted mode DEFAULT for CMU_AUXHFRCOCTRL */
#define _CMU_AUXHFRCOCTRL_FREQRANGE_SHIFT                 16                                             /**< Shift value for CMU_FREQRANGE */
#define _CMU_AUXHFRCOCTRL_FREQRANGE_MASK                  0x1F0000UL                                     /**< Bit mask for CMU_FREQRANGE */
#define _CMU_AUXHFRCOCTRL_FREQRANGE_DEFAULT               0x00000008UL                                   /**< Mode DEFAULT for CMU_AUXHFRCOCTRL */
#define CMU_AUXHFRCOCTRL_FREQRANGE_DEFAULT                (_CMU_AUXHFRCOCTRL_FREQRANGE_DEFAULT << 16)    /**< Shifted mode DEFAULT for CMU_AUXHFRCOCTRL */
#define _CMU_AUXHFRCOCTRL_CMPBIAS_SHIFT                   21                                             /**< Shift value for CMU_CMPBIAS */
#define _CMU_AUXHFRCOCTRL_CMPBIAS_MASK                    0xE00000UL                                     /**< Bit mask for CMU_CMPBIAS */
#define _CMU_AUXHFRCOCTRL_CMPBIAS_DEFAULT                 0x00000002UL                                   /**< Mode DEFAULT for CMU_AUXHFRCOCTRL */
#define CMU_AUXHFRCOCTRL_CMPBIAS_DEFAULT                  (_CMU_AUXHFRCOCTRL_CMPBIAS_DEFAULT << 21)      /**< Shifted mode DEFAULT for CMU_AUXHFRCOCTRL */
#define CMU_AUXHFRCOCTRL_LDOHP                            (0x1UL << 24)                                  /**< AUXHFRCO LDO High Power Mode */
#define _CMU_AUXHFRCOCTRL_LDOHP_SHIFT                     24                                             /**< Shift value for CMU_LDOHP */
#define _CMU_AUXHFRCOCTRL_LDOHP_MASK                      0x1000000UL                                    /**< Bit mask for CMU_LDOHP */
#define _CMU_AUXHFRCOCTRL_LDOHP_DEFAULT                   0x00000001UL                                   /**< Mode DEFAULT for CMU_AUXHFRCOCTRL */
#define CMU_AUXHFRCOCTRL_LDOHP_DEFAULT                    (_CMU_AUXHFRCOCTRL_LDOHP_DEFAULT << 24)        /**< Shifted mode DEFAULT for CMU_AUXHFRCOCTRL */
#define _CMU_AUXHFRCOCTRL_CLKDIV_SHIFT                    25                                             /**< Shift value for CMU_CLKDIV */
#define _CMU_AUXHFRCOCTRL_CLKDIV_MASK                     0x6000000UL                                    /**< Bit mask for CMU_CLKDIV */
#define _CMU_AUXHFRCOCTRL_CLKDIV_DEFAULT                  0x00000000UL                                   /**< Mode DEFAULT for CMU_AUXHFRCOCTRL */
#define _CMU_AUXHFRCOCTRL_CLKDIV_DIV1                     0x00000000UL                                   /**< Mode DIV1 for CMU_AUXHFRCOCTRL */
#define _CMU_AUXHFRCOCTRL_CLKDIV_DIV2                     0x00000001UL                                   /**< Mode DIV2 for CMU_AUXHFRCOCTRL */
#define _CMU_AUXHFRCOCTRL_CLKDIV_DIV4                     0x00000002UL                                   /**< Mode DIV4 for CMU_AUXHFRCOCTRL */
#define CMU_AUXHFRCOCTRL_CLKDIV_DEFAULT                   (_CMU_AUXHFRCOCTRL_CLKDIV_DEFAULT << 25)       /**< Shifted mode DEFAULT for CMU_AUXHFRCOCTRL */
#define CMU_AUXHFRCOCTRL_CLKDIV_DIV1                      (_CMU_AUXHFRCOCTRL_CLKDIV_DIV1 << 25)          /**< Shifted mode DIV1 for CMU_AUXHFRCOCTRL */
#define CMU_AUXHFRCOCTRL_CLKDIV_DIV2                      (_CMU_AUXHFRCOCTRL_CLKDIV_DIV2 << 25)          /**< Shifted mode DIV2 for CMU_AUXHFRCOCTRL */
#define CMU_AUXHFRCOCTRL_CLKDIV_DIV4                      (_CMU_AUXHFRCOCTRL_CLKDIV_DIV4 << 25)          /**< Shifted mode DIV4 for CMU_AUXHFRCOCTRL */
#define CMU_AUXHFRCOCTRL_FINETUNINGEN                     (0x1UL << 27)                                  /**< Enable Reference for Fine Tuning */
#define _CMU_AUXHFRCOCTRL_FINETUNINGEN_SHIFT              27                                             /**< Shift value for CMU_FINETUNINGEN */
#define _CMU_AUXHFRCOCTRL_FINETUNINGEN_MASK               0x8000000UL                                    /**< Bit mask for CMU_FINETUNINGEN */
#define _CMU_AUXHFRCOCTRL_FINETUNINGEN_DEFAULT            0x00000000UL                                   /**< Mode DEFAULT for CMU_AUXHFRCOCTRL */
#define CMU_AUXHFRCOCTRL_FINETUNINGEN_DEFAULT             (_CMU_AUXHFRCOCTRL_FINETUNINGEN_DEFAULT << 27) /**< Shifted mode DEFAULT for CMU_AUXHFRCOCTRL */
#define _CMU_AUXHFRCOCTRL_VREFTC_SHIFT                    28                                             /**< Shift value for CMU_VREFTC */
#define _CMU_AUXHFRCOCTRL_VREFTC_MASK                     0xF0000000UL                                   /**< Bit mask for CMU_VREFTC */
#define _CMU_AUXHFRCOCTRL_VREFTC_DEFAULT                  0x0000000BUL                                   /**< Mode DEFAULT for CMU_AUXHFRCOCTRL */
#define CMU_AUXHFRCOCTRL_VREFTC_DEFAULT                   (_CMU_AUXHFRCOCTRL_VREFTC_DEFAULT << 28)       /**< Shifted mode DEFAULT for CMU_AUXHFRCOCTRL */

/* Bit fields for CMU LFRCOCTRL */
#define _CMU_LFRCOCTRL_RESETVALUE                         0x81060100UL                                /**< Default value for CMU_LFRCOCTRL */
#define _CMU_LFRCOCTRL_MASK                               0xF33701FFUL                                /**< Mask for CMU_LFRCOCTRL */
#define _CMU_LFRCOCTRL_TUNING_SHIFT                       0                                           /**< Shift value for CMU_TUNING */
#define _CMU_LFRCOCTRL_TUNING_MASK                        0x1FFUL                                     /**< Bit mask for CMU_TUNING */
#define _CMU_LFRCOCTRL_TUNING_DEFAULT                     0x00000100UL                                /**< Mode DEFAULT for CMU_LFRCOCTRL */
#define CMU_LFRCOCTRL_TUNING_DEFAULT                      (_CMU_LFRCOCTRL_TUNING_DEFAULT << 0)        /**< Shifted mode DEFAULT for CMU_LFRCOCTRL */
#define CMU_LFRCOCTRL_ENVREF                              (0x1UL << 16)                               /**< Enable Duty Cycling of Vref */
#define _CMU_LFRCOCTRL_ENVREF_SHIFT                       16                                          /**< Shift value for CMU_ENVREF */
#define _CMU_LFRCOCTRL_ENVREF_MASK                        0x10000UL                                   /**< Bit mask for CMU_ENVREF */
#define _CMU_LFRCOCTRL_ENVREF_DEFAULT                     0x00000000UL                                /**< Mode DEFAULT for CMU_LFRCOCTRL */
#define CMU_LFRCOCTRL_ENVREF_DEFAULT                      (_CMU_LFRCOCTRL_ENVREF_DEFAULT << 16)       /**< Shifted mode DEFAULT for CMU_LFRCOCTRL */
#define CMU_LFRCOCTRL_ENCHOP                              (0x1UL << 17)                               /**< Enable Comparator Chopping */
#define _CMU_LFRCOCTRL_ENCHOP_SHIFT                       17                                          /**< Shift value for CMU_ENCHOP */
#define _CMU_LFRCOCTRL_ENCHOP_MASK                        0x20000UL                                   /**< Bit mask for CMU_ENCHOP */
#define _CMU_LFRCOCTRL_ENCHOP_DEFAULT                     0x00000001UL                                /**< Mode DEFAULT for CMU_LFRCOCTRL */
#define CMU_LFRCOCTRL_ENCHOP_DEFAULT                      (_CMU_LFRCOCTRL_ENCHOP_DEFAULT << 17)       /**< Shifted mode DEFAULT for CMU_LFRCOCTRL */
#define CMU_LFRCOCTRL_ENDEM                               (0x1UL << 18)                               /**< Enable Dynamic Element Matching */
#define _CMU_LFRCOCTRL_ENDEM_SHIFT                        18                                          /**< Shift value for CMU_ENDEM */
#define _CMU_LFRCOCTRL_ENDEM_MASK                         0x40000UL                                   /**< Bit mask for CMU_ENDEM */
#define _CMU_LFRCOCTRL_ENDEM_DEFAULT                      0x00000001UL                                /**< Mode DEFAULT for CMU_LFRCOCTRL */
#define CMU_LFRCOCTRL_ENDEM_DEFAULT                       (_CMU_LFRCOCTRL_ENDEM_DEFAULT << 18)        /**< Shifted mode DEFAULT for CMU_LFRCOCTRL */
#define _CMU_LFRCOCTRL_VREFUPDATE_SHIFT                   20                                          /**< Shift value for CMU_VREFUPDATE */
#define _CMU_LFRCOCTRL_VREFUPDATE_MASK                    0x300000UL                                  /**< Bit mask for CMU_VREFUPDATE */
#define _CMU_LFRCOCTRL_VREFUPDATE_DEFAULT                 0x00000000UL                                /**< Mode DEFAULT for CMU_LFRCOCTRL */
#define _CMU_LFRCOCTRL_VREFUPDATE_32CYCLES                0x00000000UL                                /**< Mode 32CYCLES for CMU_LFRCOCTRL */
#define _CMU_LFRCOCTRL_VREFUPDATE_64CYCLES                0x00000001UL                                /**< Mode 64CYCLES for CMU_LFRCOCTRL */
#define _CMU_LFRCOCTRL_VREFUPDATE_128CYCLES               0x00000002UL                                /**< Mode 128CYCLES for CMU_LFRCOCTRL */
#define _CMU_LFRCOCTRL_VREFUPDATE_256CYCLES               0x00000003UL                                /**< Mode 256CYCLES for CMU_LFRCOCTRL */
#define CMU_LFRCOCTRL_VREFUPDATE_DEFAULT                  (_CMU_LFRCOCTRL_VREFUPDATE_DEFAULT << 20)   /**< Shifted mode DEFAULT for CMU_LFRCOCTRL */
#define CMU_LFRCOCTRL_VREFUPDATE_32CYCLES                 (_CMU_LFRCOCTRL_VREFUPDATE_32CYCLES << 20)  /**< Shifted mode 32CYCLES for CMU_LFRCOCTRL */
#define CMU_LFRCOCTRL_VREFUPDATE_64CYCLES                 (_CMU_LFRCOCTRL_VREFUPDATE_64CYCLES << 20)  /**< Shifted mode 64CYCLES for CMU_LFRCOCTRL */
#define CMU_LFRCOCTRL_VREFUPDATE_128CYCLES                (_CMU_LFRCOCTRL_VREFUPDATE_128CYCLES << 20) /**< Shifted mode 128CYCLES for CMU_LFRCOCTRL */
#define CMU_LFRCOCTRL_VREFUPDATE_256CYCLES                (_CMU_LFRCOCTRL_VREFUPDATE_256CYCLES << 20) /**< Shifted mode 256CYCLES for CMU_LFRCOCTRL */
#define _CMU_LFRCOCTRL_TIMEOUT_SHIFT                      24                                          /**< Shift value for CMU_TIMEOUT */
#define _CMU_LFRCOCTRL_TIMEOUT_MASK                       0x3000000UL                                 /**< Bit mask for CMU_TIMEOUT */
#define _CMU_LFRCOCTRL_TIMEOUT_2CYCLES                    0x00000000UL                                /**< Mode 2CYCLES for CMU_LFRCOCTRL */
#define _CMU_LFRCOCTRL_TIMEOUT_DEFAULT                    0x00000001UL                                /**< Mode DEFAULT for CMU_LFRCOCTRL */
#define _CMU_LFRCOCTRL_TIMEOUT_16CYCLES                   0x00000001UL                                /**< Mode 16CYCLES for CMU_LFRCOCTRL */
#define _CMU_LFRCOCTRL_TIMEOUT_32CYCLES                   0x00000002UL                                /**< Mode 32CYCLES for CMU_LFRCOCTRL */
#define CMU_LFRCOCTRL_TIMEOUT_2CYCLES                     (_CMU_LFRCOCTRL_TIMEOUT_2CYCLES << 24)      /**< Shifted mode 2CYCLES for CMU_LFRCOCTRL */
#define CMU_LFRCOCTRL_TIMEOUT_DEFAULT                     (_CMU_LFRCOCTRL_TIMEOUT_DEFAULT << 24)      /**< Shifted mode DEFAULT for CMU_LFRCOCTRL */
#define CMU_LFRCOCTRL_TIMEOUT_16CYCLES                    (_CMU_LFRCOCTRL_TIMEOUT_16CYCLES << 24)     /**< Shifted mode 16CYCLES for CMU_LFRCOCTRL */
#define CMU_LFRCOCTRL_TIMEOUT_32CYCLES                    (_CMU_LFRCOCTRL_TIMEOUT_32CYCLES << 24)     /**< Shifted mode 32CYCLES for CMU_LFRCOCTRL */
#define _CMU_LFRCOCTRL_GMCCURTUNE_SHIFT                   28                                          /**< Shift value for CMU_GMCCURTUNE */
#define _CMU_LFRCOCTRL_GMCCURTUNE_MASK                    0xF0000000UL                                /**< Bit mask for CMU_GMCCURTUNE */
#define _CMU_LFRCOCTRL_GMCCURTUNE_DEFAULT                 0x00000008UL                                /**< Mode DEFAULT for CMU_LFRCOCTRL */
#define CMU_LFRCOCTRL_GMCCURTUNE_DEFAULT                  (_CMU_LFRCOCTRL_GMCCURTUNE_DEFAULT << 28)   /**< Shifted mode DEFAULT for CMU_LFRCOCTRL */

/* Bit fields for CMU HFXOCTRL */
#define _CMU_HFXOCTRL_RESETVALUE                          0x00000000UL                                     /**< Default value for CMU_HFXOCTRL */
#define _CMU_HFXOCTRL_MASK                                0x37000731UL                                     /**< Mask for CMU_HFXOCTRL */
#define CMU_HFXOCTRL_MODE                                 (0x1UL << 0)                                     /**< HFXO Mode */
#define _CMU_HFXOCTRL_MODE_SHIFT                          0                                                /**< Shift value for CMU_MODE */
#define _CMU_HFXOCTRL_MODE_MASK                           0x1UL                                            /**< Bit mask for CMU_MODE */
#define _CMU_HFXOCTRL_MODE_DEFAULT                        0x00000000UL                                     /**< Mode DEFAULT for CMU_HFXOCTRL */
#define _CMU_HFXOCTRL_MODE_XTAL                           0x00000000UL                                     /**< Mode XTAL for CMU_HFXOCTRL */
#define _CMU_HFXOCTRL_MODE_EXTCLK                         0x00000001UL                                     /**< Mode EXTCLK for CMU_HFXOCTRL */
#define CMU_HFXOCTRL_MODE_DEFAULT                         (_CMU_HFXOCTRL_MODE_DEFAULT << 0)                /**< Shifted mode DEFAULT for CMU_HFXOCTRL */
#define CMU_HFXOCTRL_MODE_XTAL                            (_CMU_HFXOCTRL_MODE_XTAL << 0)                   /**< Shifted mode XTAL for CMU_HFXOCTRL */
#define CMU_HFXOCTRL_MODE_EXTCLK                          (_CMU_HFXOCTRL_MODE_EXTCLK << 0)                 /**< Shifted mode EXTCLK for CMU_HFXOCTRL */
#define _CMU_HFXOCTRL_PEAKDETSHUNTOPTMODE_SHIFT           4                                                /**< Shift value for CMU_PEAKDETSHUNTOPTMODE */
#define _CMU_HFXOCTRL_PEAKDETSHUNTOPTMODE_MASK            0x30UL                                           /**< Bit mask for CMU_PEAKDETSHUNTOPTMODE */
#define _CMU_HFXOCTRL_PEAKDETSHUNTOPTMODE_DEFAULT         0x00000000UL                                     /**< Mode DEFAULT for CMU_HFXOCTRL */
#define _CMU_HFXOCTRL_PEAKDETSHUNTOPTMODE_AUTOCMD         0x00000000UL                                     /**< Mode AUTOCMD for CMU_HFXOCTRL */
#define _CMU_HFXOCTRL_PEAKDETSHUNTOPTMODE_CMD             0x00000001UL                                     /**< Mode CMD for CMU_HFXOCTRL */
#define _CMU_HFXOCTRL_PEAKDETSHUNTOPTMODE_MANUAL          0x00000002UL                                     /**< Mode MANUAL for CMU_HFXOCTRL */
#define CMU_HFXOCTRL_PEAKDETSHUNTOPTMODE_DEFAULT          (_CMU_HFXOCTRL_PEAKDETSHUNTOPTMODE_DEFAULT << 4) /**< Shifted mode DEFAULT for CMU_HFXOCTRL */
#define CMU_HFXOCTRL_PEAKDETSHUNTOPTMODE_AUTOCMD          (_CMU_HFXOCTRL_PEAKDETSHUNTOPTMODE_AUTOCMD << 4) /**< Shifted mode AUTOCMD for CMU_HFXOCTRL */
#define CMU_HFXOCTRL_PEAKDETSHUNTOPTMODE_CMD              (_CMU_HFXOCTRL_PEAKDETSHUNTOPTMODE_CMD << 4)     /**< Shifted mode CMD for CMU_HFXOCTRL */
#define CMU_HFXOCTRL_PEAKDETSHUNTOPTMODE_MANUAL           (_CMU_HFXOCTRL_PEAKDETSHUNTOPTMODE_MANUAL << 4)  /**< Shifted mode MANUAL for CMU_HFXOCTRL */
#define CMU_HFXOCTRL_LOWPOWER                             (0x1UL << 8)                                     /**< Low Power Mode Control */
#define _CMU_HFXOCTRL_LOWPOWER_SHIFT                      8                                                /**< Shift value for CMU_LOWPOWER */
#define _CMU_HFXOCTRL_LOWPOWER_MASK                       0x100UL                                          /**< Bit mask for CMU_LOWPOWER */
#define _CMU_HFXOCTRL_LOWPOWER_DEFAULT                    0x00000000UL                                     /**< Mode DEFAULT for CMU_HFXOCTRL */
#define CMU_HFXOCTRL_LOWPOWER_DEFAULT                     (_CMU_HFXOCTRL_LOWPOWER_DEFAULT << 8)            /**< Shifted mode DEFAULT for CMU_HFXOCTRL */
#define CMU_HFXOCTRL_XTI2GND                              (0x1UL << 9)                                     /**< Clamp HFXTAL_N Pin to Ground When HFXO Oscillator is Off */
#define _CMU_HFXOCTRL_XTI2GND_SHIFT                       9                                                /**< Shift value for CMU_XTI2GND */
#define _CMU_HFXOCTRL_XTI2GND_MASK                        0x200UL                                          /**< Bit mask for CMU_XTI2GND */
#define _CMU_HFXOCTRL_XTI2GND_DEFAULT                     0x00000000UL                                     /**< Mode DEFAULT for CMU_HFXOCTRL */
#define CMU_HFXOCTRL_XTI2GND_DEFAULT                      (_CMU_HFXOCTRL_XTI2GND_DEFAULT << 9)             /**< Shifted mode DEFAULT for CMU_HFXOCTRL */
#define CMU_HFXOCTRL_XTO2GND                              (0x1UL << 10)                                    /**< Clamp HFXTAL_P Pin to Ground When HFXO Oscillator is Off */
#define _CMU_HFXOCTRL_XTO2GND_SHIFT                       10                                               /**< Shift value for CMU_XTO2GND */
#define _CMU_HFXOCTRL_XTO2GND_MASK                        0x400UL                                          /**< Bit mask for CMU_XTO2GND */
#define _CMU_HFXOCTRL_XTO2GND_DEFAULT                     0x00000000UL                                     /**< Mode DEFAULT for CMU_HFXOCTRL */
#define CMU_HFXOCTRL_XTO2GND_DEFAULT                      (_CMU_HFXOCTRL_XTO2GND_DEFAULT << 10)            /**< Shifted mode DEFAULT for CMU_HFXOCTRL */
#define _CMU_HFXOCTRL_LFTIMEOUT_SHIFT                     24                                               /**< Shift value for CMU_LFTIMEOUT */
#define _CMU_HFXOCTRL_LFTIMEOUT_MASK                      0x7000000UL                                      /**< Bit mask for CMU_LFTIMEOUT */
#define _CMU_HFXOCTRL_LFTIMEOUT_DEFAULT                   0x00000000UL                                     /**< Mode DEFAULT for CMU_HFXOCTRL */
#define _CMU_HFXOCTRL_LFTIMEOUT_0CYCLES                   0x00000000UL                                     /**< Mode 0CYCLES for CMU_HFXOCTRL */
#define _CMU_HFXOCTRL_LFTIMEOUT_2CYCLES                   0x00000001UL                                     /**< Mode 2CYCLES for CMU_HFXOCTRL */
#define _CMU_HFXOCTRL_LFTIMEOUT_4CYCLES                   0x00000002UL                                     /**< Mode 4CYCLES for CMU_HFXOCTRL */
#define _CMU_HFXOCTRL_LFTIMEOUT_16CYCLES                  0x00000003UL                                     /**< Mode 16CYCLES for CMU_HFXOCTRL */
#define _CMU_HFXOCTRL_LFTIMEOUT_32CYCLES                  0x00000004UL                                     /**< Mode 32CYCLES for CMU_HFXOCTRL */
#define _CMU_HFXOCTRL_LFTIMEOUT_64CYCLES                  0x00000005UL                                     /**< Mode 64CYCLES for CMU_HFXOCTRL */
#define _CMU_HFXOCTRL_LFTIMEOUT_1KCYCLES                  0x00000006UL                                     /**< Mode 1KCYCLES for CMU_HFXOCTRL */
#define _CMU_HFXOCTRL_LFTIMEOUT_4KCYCLES                  0x00000007UL                                     /**< Mode 4KCYCLES for CMU_HFXOCTRL */
#define CMU_HFXOCTRL_LFTIMEOUT_DEFAULT                    (_CMU_HFXOCTRL_LFTIMEOUT_DEFAULT << 24)          /**< Shifted mode DEFAULT for CMU_HFXOCTRL */
#define CMU_HFXOCTRL_LFTIMEOUT_0CYCLES                    (_CMU_HFXOCTRL_LFTIMEOUT_0CYCLES << 24)          /**< Shifted mode 0CYCLES for CMU_HFXOCTRL */
#define CMU_HFXOCTRL_LFTIMEOUT_2CYCLES                    (_CMU_HFXOCTRL_LFTIMEOUT_2CYCLES << 24)          /**< Shifted mode 2CYCLES for CMU_HFXOCTRL */
#define CMU_HFXOCTRL_LFTIMEOUT_4CYCLES                    (_CMU_HFXOCTRL_LFTIMEOUT_4CYCLES << 24)          /**< Shifted mode 4CYCLES for CMU_HFXOCTRL */
#define CMU_HFXOCTRL_LFTIMEOUT_16CYCLES                   (_CMU_HFXOCTRL_LFTIMEOUT_16CYCLES << 24)         /**< Shifted mode 16CYCLES for CMU_HFXOCTRL */
#define CMU_HFXOCTRL_LFTIMEOUT_32CYCLES                   (_CMU_HFXOCTRL_LFTIMEOUT_32CYCLES << 24)         /**< Shifted mode 32CYCLES for CMU_HFXOCTRL */
#define CMU_HFXOCTRL_LFTIMEOUT_64CYCLES                   (_CMU_HFXOCTRL_LFTIMEOUT_64CYCLES << 24)         /**< Shifted mode 64CYCLES for CMU_HFXOCTRL */
#define CMU_HFXOCTRL_LFTIMEOUT_1KCYCLES                   (_CMU_HFXOCTRL_LFTIMEOUT_1KCYCLES << 24)         /**< Shifted mode 1KCYCLES for CMU_HFXOCTRL */
#define CMU_HFXOCTRL_LFTIMEOUT_4KCYCLES                   (_CMU_HFXOCTRL_LFTIMEOUT_4KCYCLES << 24)         /**< Shifted mode 4KCYCLES for CMU_HFXOCTRL */
#define CMU_HFXOCTRL_AUTOSTARTEM0EM1                      (0x1UL << 28)                                    /**< Automatically Start of HFXO Upon EM0/EM1 Entry From EM2/EM3 */
#define _CMU_HFXOCTRL_AUTOSTARTEM0EM1_SHIFT               28                                               /**< Shift value for CMU_AUTOSTARTEM0EM1 */
#define _CMU_HFXOCTRL_AUTOSTARTEM0EM1_MASK                0x10000000UL                                     /**< Bit mask for CMU_AUTOSTARTEM0EM1 */
#define _CMU_HFXOCTRL_AUTOSTARTEM0EM1_DEFAULT             0x00000000UL                                     /**< Mode DEFAULT for CMU_HFXOCTRL */
#define CMU_HFXOCTRL_AUTOSTARTEM0EM1_DEFAULT              (_CMU_HFXOCTRL_AUTOSTARTEM0EM1_DEFAULT << 28)    /**< Shifted mode DEFAULT for CMU_HFXOCTRL */
#define CMU_HFXOCTRL_AUTOSTARTSELEM0EM1                   (0x1UL << 29)                                    /**< Automatically Start and Select of HFXO Upon EM0/EM1 Entry From EM2/EM3 */
#define _CMU_HFXOCTRL_AUTOSTARTSELEM0EM1_SHIFT            29                                               /**< Shift value for CMU_AUTOSTARTSELEM0EM1 */
#define _CMU_HFXOCTRL_AUTOSTARTSELEM0EM1_MASK             0x20000000UL                                     /**< Bit mask for CMU_AUTOSTARTSELEM0EM1 */
#define _CMU_HFXOCTRL_AUTOSTARTSELEM0EM1_DEFAULT          0x00000000UL                                     /**< Mode DEFAULT for CMU_HFXOCTRL */
#define CMU_HFXOCTRL_AUTOSTARTSELEM0EM1_DEFAULT           (_CMU_HFXOCTRL_AUTOSTARTSELEM0EM1_DEFAULT << 29) /**< Shifted mode DEFAULT for CMU_HFXOCTRL */

/* Bit fields for CMU HFXOSTARTUPCTRL */
#define _CMU_HFXOSTARTUPCTRL_RESETVALUE                   0x00050020UL                                     /**< Default value for CMU_HFXOSTARTUPCTRL */
#define _CMU_HFXOSTARTUPCTRL_MASK                         0x000FF87FUL                                     /**< Mask for CMU_HFXOSTARTUPCTRL */
#define _CMU_HFXOSTARTUPCTRL_IBTRIMXOCORE_SHIFT           0                                                /**< Shift value for CMU_IBTRIMXOCORE */
#define _CMU_HFXOSTARTUPCTRL_IBTRIMXOCORE_MASK            0x7FUL                                           /**< Bit mask for CMU_IBTRIMXOCORE */
#define _CMU_HFXOSTARTUPCTRL_IBTRIMXOCORE_DEFAULT         0x00000020UL                                     /**< Mode DEFAULT for CMU_HFXOSTARTUPCTRL */
#define CMU_HFXOSTARTUPCTRL_IBTRIMXOCORE_DEFAULT          (_CMU_HFXOSTARTUPCTRL_IBTRIMXOCORE_DEFAULT << 0) /**< Shifted mode DEFAULT for CMU_HFXOSTARTUPCTRL */
#define _CMU_HFXOSTARTUPCTRL_CTUNE_SHIFT                  11                                               /**< Shift value for CMU_CTUNE */
#define _CMU_HFXOSTARTUPCTRL_CTUNE_MASK                   0xFF800UL                                        /**< Bit mask for CMU_CTUNE */
#define _CMU_HFXOSTARTUPCTRL_CTUNE_DEFAULT                0x000000A0UL                                     /**< Mode DEFAULT for CMU_HFXOSTARTUPCTRL */
#define CMU_HFXOSTARTUPCTRL_CTUNE_DEFAULT                 (_CMU_HFXOSTARTUPCTRL_CTUNE_DEFAULT << 11)       /**< Shifted mode DEFAULT for CMU_HFXOSTARTUPCTRL */

/* Bit fields for CMU HFXOSTEADYSTATECTRL */
#define _CMU_HFXOSTEADYSTATECTRL_RESETVALUE               0xA30B4507UL                                         /**< Default value for CMU_HFXOSTEADYSTATECTRL */
#define _CMU_HFXOSTEADYSTATECTRL_MASK                     0xF70FFFFFUL                                         /**< Mask for CMU_HFXOSTEADYSTATECTRL */
#define _CMU_HFXOSTEADYSTATECTRL_IBTRIMXOCORE_SHIFT       0                                                    /**< Shift value for CMU_IBTRIMXOCORE */
#define _CMU_HFXOSTEADYSTATECTRL_IBTRIMXOCORE_MASK        0x7FUL                                               /**< Bit mask for CMU_IBTRIMXOCORE */
#define _CMU_HFXOSTEADYSTATECTRL_IBTRIMXOCORE_DEFAULT     0x00000007UL                                         /**< Mode DEFAULT for CMU_HFXOSTEADYSTATECTRL */
#define CMU_HFXOSTEADYSTATECTRL_IBTRIMXOCORE_DEFAULT      (_CMU_HFXOSTEADYSTATECTRL_IBTRIMXOCORE_DEFAULT << 0) /**< Shifted mode DEFAULT for CMU_HFXOSTEADYSTATECTRL */
#define _CMU_HFXOSTEADYSTATECTRL_REGISH_SHIFT             7                                                    /**< Shift value for CMU_REGISH */
#define _CMU_HFXOSTEADYSTATECTRL_REGISH_MASK              0x780UL                                              /**< Bit mask for CMU_REGISH */
#define _CMU_HFXOSTEADYSTATECTRL_REGISH_DEFAULT           0x0000000AUL                                         /**< Mode DEFAULT for CMU_HFXOSTEADYSTATECTRL */
#define CMU_HFXOSTEADYSTATECTRL_REGISH_DEFAULT            (_CMU_HFXOSTEADYSTATECTRL_REGISH_DEFAULT << 7)       /**< Shifted mode DEFAULT for CMU_HFXOSTEADYSTATECTRL */
#define _CMU_HFXOSTEADYSTATECTRL_CTUNE_SHIFT              11                                                   /**< Shift value for CMU_CTUNE */
#define _CMU_HFXOSTEADYSTATECTRL_CTUNE_MASK               0xFF800UL                                            /**< Bit mask for CMU_CTUNE */
#define _CMU_HFXOSTEADYSTATECTRL_CTUNE_DEFAULT            0x00000168UL                                         /**< Mode DEFAULT for CMU_HFXOSTEADYSTATECTRL */
#define CMU_HFXOSTEADYSTATECTRL_CTUNE_DEFAULT             (_CMU_HFXOSTEADYSTATECTRL_CTUNE_DEFAULT << 11)       /**< Shifted mode DEFAULT for CMU_HFXOSTEADYSTATECTRL */
#define _CMU_HFXOSTEADYSTATECTRL_REGSELILOW_SHIFT         24                                                   /**< Shift value for CMU_REGSELILOW */
#define _CMU_HFXOSTEADYSTATECTRL_REGSELILOW_MASK          0x3000000UL                                          /**< Bit mask for CMU_REGSELILOW */
#define _CMU_HFXOSTEADYSTATECTRL_REGSELILOW_DEFAULT       0x00000003UL                                         /**< Mode DEFAULT for CMU_HFXOSTEADYSTATECTRL */
#define CMU_HFXOSTEADYSTATECTRL_REGSELILOW_DEFAULT        (_CMU_HFXOSTEADYSTATECTRL_REGSELILOW_DEFAULT << 24)  /**< Shifted mode DEFAULT for CMU_HFXOSTEADYSTATECTRL */
#define CMU_HFXOSTEADYSTATECTRL_PEAKDETEN                 (0x1UL << 26)                                        /**< Enables Oscillator Peak Detectors */
#define _CMU_HFXOSTEADYSTATECTRL_PEAKDETEN_SHIFT          26                                                   /**< Shift value for CMU_PEAKDETEN */
#define _CMU_HFXOSTEADYSTATECTRL_PEAKDETEN_MASK           0x4000000UL                                          /**< Bit mask for CMU_PEAKDETEN */
#define _CMU_HFXOSTEADYSTATECTRL_PEAKDETEN_DEFAULT        0x00000000UL                                         /**< Mode DEFAULT for CMU_HFXOSTEADYSTATECTRL */
#define CMU_HFXOSTEADYSTATECTRL_PEAKDETEN_DEFAULT         (_CMU_HFXOSTEADYSTATECTRL_PEAKDETEN_DEFAULT << 26)   /**< Shifted mode DEFAULT for CMU_HFXOSTEADYSTATECTRL */
#define _CMU_HFXOSTEADYSTATECTRL_REGISHUPPER_SHIFT        28                                                   /**< Shift value for CMU_REGISHUPPER */
#define _CMU_HFXOSTEADYSTATECTRL_REGISHUPPER_MASK         0xF0000000UL                                         /**< Bit mask for CMU_REGISHUPPER */
#define _CMU_HFXOSTEADYSTATECTRL_REGISHUPPER_DEFAULT      0x0000000AUL                                         /**< Mode DEFAULT for CMU_HFXOSTEADYSTATECTRL */
#define CMU_HFXOSTEADYSTATECTRL_REGISHUPPER_DEFAULT       (_CMU_HFXOSTEADYSTATECTRL_REGISHUPPER_DEFAULT << 28) /**< Shifted mode DEFAULT for CMU_HFXOSTEADYSTATECTRL */

/* Bit fields for CMU HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_RESETVALUE                   0x0002A067UL                                           /**< Default value for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_MASK                         0x000FF0FFUL                                           /**< Mask for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_SHIFT         0                                                      /**< Shift value for CMU_STARTUPTIMEOUT */
#define _CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_MASK          0xFUL                                                  /**< Bit mask for CMU_STARTUPTIMEOUT */
#define _CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_2CYCLES       0x00000000UL                                           /**< Mode 2CYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_4CYCLES       0x00000001UL                                           /**< Mode 4CYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_16CYCLES      0x00000002UL                                           /**< Mode 16CYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_32CYCLES      0x00000003UL                                           /**< Mode 32CYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_256CYCLES     0x00000004UL                                           /**< Mode 256CYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_1KCYCLES      0x00000005UL                                           /**< Mode 1KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_2KCYCLES      0x00000006UL                                           /**< Mode 2KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_DEFAULT       0x00000007UL                                           /**< Mode DEFAULT for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_4KCYCLES      0x00000007UL                                           /**< Mode 4KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_8KCYCLES      0x00000008UL                                           /**< Mode 8KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_16KCYCLES     0x00000009UL                                           /**< Mode 16KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_32KCYCLES     0x0000000AUL                                           /**< Mode 32KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_2CYCLES        (_CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_2CYCLES << 0)     /**< Shifted mode 2CYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_4CYCLES        (_CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_4CYCLES << 0)     /**< Shifted mode 4CYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_16CYCLES       (_CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_16CYCLES << 0)    /**< Shifted mode 16CYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_32CYCLES       (_CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_32CYCLES << 0)    /**< Shifted mode 32CYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_256CYCLES      (_CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_256CYCLES << 0)   /**< Shifted mode 256CYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_1KCYCLES       (_CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_1KCYCLES << 0)    /**< Shifted mode 1KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_2KCYCLES       (_CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_2KCYCLES << 0)    /**< Shifted mode 2KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_DEFAULT        (_CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_DEFAULT << 0)     /**< Shifted mode DEFAULT for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_4KCYCLES       (_CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_4KCYCLES << 0)    /**< Shifted mode 4KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_8KCYCLES       (_CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_8KCYCLES << 0)    /**< Shifted mode 8KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_16KCYCLES      (_CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_16KCYCLES << 0)   /**< Shifted mode 16KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_32KCYCLES      (_CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_32KCYCLES << 0)   /**< Shifted mode 32KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_SHIFT          4                                                      /**< Shift value for CMU_STEADYTIMEOUT */
#define _CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_MASK           0xF0UL                                                 /**< Bit mask for CMU_STEADYTIMEOUT */
#define _CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_2CYCLES        0x00000000UL                                           /**< Mode 2CYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_4CYCLES        0x00000001UL                                           /**< Mode 4CYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_16CYCLES       0x00000002UL                                           /**< Mode 16CYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_32CYCLES       0x00000003UL                                           /**< Mode 32CYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_256CYCLES      0x00000004UL                                           /**< Mode 256CYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_1KCYCLES       0x00000005UL                                           /**< Mode 1KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_DEFAULT        0x00000006UL                                           /**< Mode DEFAULT for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_2KCYCLES       0x00000006UL                                           /**< Mode 2KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_4KCYCLES       0x00000007UL                                           /**< Mode 4KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_8KCYCLES       0x00000008UL                                           /**< Mode 8KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_16KCYCLES      0x00000009UL                                           /**< Mode 16KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_32KCYCLES      0x0000000AUL                                           /**< Mode 32KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_2CYCLES         (_CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_2CYCLES << 4)      /**< Shifted mode 2CYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_4CYCLES         (_CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_4CYCLES << 4)      /**< Shifted mode 4CYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_16CYCLES        (_CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_16CYCLES << 4)     /**< Shifted mode 16CYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_32CYCLES        (_CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_32CYCLES << 4)     /**< Shifted mode 32CYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_256CYCLES       (_CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_256CYCLES << 4)    /**< Shifted mode 256CYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_1KCYCLES        (_CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_1KCYCLES << 4)     /**< Shifted mode 1KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_DEFAULT         (_CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_DEFAULT << 4)      /**< Shifted mode DEFAULT for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_2KCYCLES        (_CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_2KCYCLES << 4)     /**< Shifted mode 2KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_4KCYCLES        (_CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_4KCYCLES << 4)     /**< Shifted mode 4KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_8KCYCLES        (_CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_8KCYCLES << 4)     /**< Shifted mode 8KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_16KCYCLES       (_CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_16KCYCLES << 4)    /**< Shifted mode 16KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_32KCYCLES       (_CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_32KCYCLES << 4)    /**< Shifted mode 32KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_SHIFT         12                                                     /**< Shift value for CMU_PEAKDETTIMEOUT */
#define _CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_MASK          0xF000UL                                               /**< Bit mask for CMU_PEAKDETTIMEOUT */
#define _CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_2CYCLES       0x00000000UL                                           /**< Mode 2CYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_4CYCLES       0x00000001UL                                           /**< Mode 4CYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_16CYCLES      0x00000002UL                                           /**< Mode 16CYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_32CYCLES      0x00000003UL                                           /**< Mode 32CYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_256CYCLES     0x00000004UL                                           /**< Mode 256CYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_1KCYCLES      0x00000005UL                                           /**< Mode 1KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_2KCYCLES      0x00000006UL                                           /**< Mode 2KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_4KCYCLES      0x00000007UL                                           /**< Mode 4KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_8KCYCLES      0x00000008UL                                           /**< Mode 8KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_16KCYCLES     0x00000009UL                                           /**< Mode 16KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_DEFAULT       0x0000000AUL                                           /**< Mode DEFAULT for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_32KCYCLES     0x0000000AUL                                           /**< Mode 32KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_2CYCLES        (_CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_2CYCLES << 12)    /**< Shifted mode 2CYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_4CYCLES        (_CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_4CYCLES << 12)    /**< Shifted mode 4CYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_16CYCLES       (_CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_16CYCLES << 12)   /**< Shifted mode 16CYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_32CYCLES       (_CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_32CYCLES << 12)   /**< Shifted mode 32CYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_256CYCLES      (_CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_256CYCLES << 12)  /**< Shifted mode 256CYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_1KCYCLES       (_CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_1KCYCLES << 12)   /**< Shifted mode 1KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_2KCYCLES       (_CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_2KCYCLES << 12)   /**< Shifted mode 2KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_4KCYCLES       (_CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_4KCYCLES << 12)   /**< Shifted mode 4KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_8KCYCLES       (_CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_8KCYCLES << 12)   /**< Shifted mode 8KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_16KCYCLES      (_CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_16KCYCLES << 12)  /**< Shifted mode 16KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_DEFAULT        (_CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_DEFAULT << 12)    /**< Shifted mode DEFAULT for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_32KCYCLES      (_CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_32KCYCLES << 12)  /**< Shifted mode 32KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_SHIFT        16                                                     /**< Shift value for CMU_SHUNTOPTTIMEOUT */
#define _CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_MASK         0xF0000UL                                              /**< Bit mask for CMU_SHUNTOPTTIMEOUT */
#define _CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_2CYCLES      0x00000000UL                                           /**< Mode 2CYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_4CYCLES      0x00000001UL                                           /**< Mode 4CYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_DEFAULT      0x00000002UL                                           /**< Mode DEFAULT for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_16CYCLES     0x00000002UL                                           /**< Mode 16CYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_32CYCLES     0x00000003UL                                           /**< Mode 32CYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_256CYCLES    0x00000004UL                                           /**< Mode 256CYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_1KCYCLES     0x00000005UL                                           /**< Mode 1KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_2KCYCLES     0x00000006UL                                           /**< Mode 2KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_4KCYCLES     0x00000007UL                                           /**< Mode 4KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_8KCYCLES     0x00000008UL                                           /**< Mode 8KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_16KCYCLES    0x00000009UL                                           /**< Mode 16KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define _CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_32KCYCLES    0x0000000AUL                                           /**< Mode 32KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_2CYCLES       (_CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_2CYCLES << 16)   /**< Shifted mode 2CYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_4CYCLES       (_CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_4CYCLES << 16)   /**< Shifted mode 4CYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_DEFAULT       (_CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_DEFAULT << 16)   /**< Shifted mode DEFAULT for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_16CYCLES      (_CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_16CYCLES << 16)  /**< Shifted mode 16CYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_32CYCLES      (_CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_32CYCLES << 16)  /**< Shifted mode 32CYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_256CYCLES     (_CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_256CYCLES << 16) /**< Shifted mode 256CYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_1KCYCLES      (_CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_1KCYCLES << 16)  /**< Shifted mode 1KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_2KCYCLES      (_CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_2KCYCLES << 16)  /**< Shifted mode 2KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_4KCYCLES      (_CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_4KCYCLES << 16)  /**< Shifted mode 4KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_8KCYCLES      (_CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_8KCYCLES << 16)  /**< Shifted mode 8KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_16KCYCLES     (_CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_16KCYCLES << 16) /**< Shifted mode 16KCYCLES for CMU_HFXOTIMEOUTCTRL */
#define CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_32KCYCLES     (_CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_32KCYCLES << 16) /**< Shifted mode 32KCYCLES for CMU_HFXOTIMEOUTCTRL */

/* Bit fields for CMU LFXOCTRL */
#define _CMU_LFXOCTRL_RESETVALUE                          0x07009000UL                            /**< Default value for CMU_LFXOCTRL */
#define _CMU_LFXOCTRL_MASK                                0x0713DB7FUL                            /**< Mask for CMU_LFXOCTRL */
#define _CMU_LFXOCTRL_TUNING_SHIFT                        0                                       /**< Shift value for CMU_TUNING */
#define _CMU_LFXOCTRL_TUNING_MASK                         0x7FUL                                  /**< Bit mask for CMU_TUNING */
#define _CMU_LFXOCTRL_TUNING_DEFAULT                      0x00000000UL                            /**< Mode DEFAULT for CMU_LFXOCTRL */
#define CMU_LFXOCTRL_TUNING_DEFAULT                       (_CMU_LFXOCTRL_TUNING_DEFAULT << 0)     /**< Shifted mode DEFAULT for CMU_LFXOCTRL */
#define _CMU_LFXOCTRL_MODE_SHIFT                          8                                       /**< Shift value for CMU_MODE */
#define _CMU_LFXOCTRL_MODE_MASK                           0x300UL                                 /**< Bit mask for CMU_MODE */
#define _CMU_LFXOCTRL_MODE_DEFAULT                        0x00000000UL                            /**< Mode DEFAULT for CMU_LFXOCTRL */
#define _CMU_LFXOCTRL_MODE_XTAL                           0x00000000UL                            /**< Mode XTAL for CMU_LFXOCTRL */
#define _CMU_LFXOCTRL_MODE_BUFEXTCLK                      0x00000001UL                            /**< Mode BUFEXTCLK for CMU_LFXOCTRL */
#define _CMU_LFXOCTRL_MODE_DIGEXTCLK                      0x00000002UL                            /**< Mode DIGEXTCLK for CMU_LFXOCTRL */
#define CMU_LFXOCTRL_MODE_DEFAULT                         (_CMU_LFXOCTRL_MODE_DEFAULT << 8)       /**< Shifted mode DEFAULT for CMU_LFXOCTRL */
#define CMU_LFXOCTRL_MODE_XTAL                            (_CMU_LFXOCTRL_MODE_XTAL << 8)          /**< Shifted mode XTAL for CMU_LFXOCTRL */
#define CMU_LFXOCTRL_MODE_BUFEXTCLK                       (_CMU_LFXOCTRL_MODE_BUFEXTCLK << 8)     /**< Shifted mode BUFEXTCLK for CMU_LFXOCTRL */
#define CMU_LFXOCTRL_MODE_DIGEXTCLK                       (_CMU_LFXOCTRL_MODE_DIGEXTCLK << 8)     /**< Shifted mode DIGEXTCLK for CMU_LFXOCTRL */
#define _CMU_LFXOCTRL_GAIN_SHIFT                          11                                      /**< Shift value for CMU_GAIN */
#define _CMU_LFXOCTRL_GAIN_MASK                           0x1800UL                                /**< Bit mask for CMU_GAIN */
#define _CMU_LFXOCTRL_GAIN_DEFAULT                        0x00000002UL                            /**< Mode DEFAULT for CMU_LFXOCTRL */
#define CMU_LFXOCTRL_GAIN_DEFAULT                         (_CMU_LFXOCTRL_GAIN_DEFAULT << 11)      /**< Shifted mode DEFAULT for CMU_LFXOCTRL */
#define CMU_LFXOCTRL_HIGHAMPL                             (0x1UL << 14)                           /**< LFXO High XTAL Oscillation Amplitude Enable */
#define _CMU_LFXOCTRL_HIGHAMPL_SHIFT                      14                                      /**< Shift value for CMU_HIGHAMPL */
#define _CMU_LFXOCTRL_HIGHAMPL_MASK                       0x4000UL                                /**< Bit mask for CMU_HIGHAMPL */
#define _CMU_LFXOCTRL_HIGHAMPL_DEFAULT                    0x00000000UL                            /**< Mode DEFAULT for CMU_LFXOCTRL */
#define CMU_LFXOCTRL_HIGHAMPL_DEFAULT                     (_CMU_LFXOCTRL_HIGHAMPL_DEFAULT << 14)  /**< Shifted mode DEFAULT for CMU_LFXOCTRL */
#define CMU_LFXOCTRL_AGC                                  (0x1UL << 15)                           /**< LFXO AGC Enable */
#define _CMU_LFXOCTRL_AGC_SHIFT                           15                                      /**< Shift value for CMU_AGC */
#define _CMU_LFXOCTRL_AGC_MASK                            0x8000UL                                /**< Bit mask for CMU_AGC */
#define _CMU_LFXOCTRL_AGC_DEFAULT                         0x00000001UL                            /**< Mode DEFAULT for CMU_LFXOCTRL */
#define CMU_LFXOCTRL_AGC_DEFAULT                          (_CMU_LFXOCTRL_AGC_DEFAULT << 15)       /**< Shifted mode DEFAULT for CMU_LFXOCTRL */
#define _CMU_LFXOCTRL_CUR_SHIFT                           16                                      /**< Shift value for CMU_CUR */
#define _CMU_LFXOCTRL_CUR_MASK                            0x30000UL                               /**< Bit mask for CMU_CUR */
#define _CMU_LFXOCTRL_CUR_DEFAULT                         0x00000000UL                            /**< Mode DEFAULT for CMU_LFXOCTRL */
#define CMU_LFXOCTRL_CUR_DEFAULT                          (_CMU_LFXOCTRL_CUR_DEFAULT << 16)       /**< Shifted mode DEFAULT for CMU_LFXOCTRL */
#define CMU_LFXOCTRL_BUFCUR                               (0x1UL << 20)                           /**< LFXO Buffer Bias Current */
#define _CMU_LFXOCTRL_BUFCUR_SHIFT                        20                                      /**< Shift value for CMU_BUFCUR */
#define _CMU_LFXOCTRL_BUFCUR_MASK                         0x100000UL                              /**< Bit mask for CMU_BUFCUR */
#define _CMU_LFXOCTRL_BUFCUR_DEFAULT                      0x00000000UL                            /**< Mode DEFAULT for CMU_LFXOCTRL */
#define CMU_LFXOCTRL_BUFCUR_DEFAULT                       (_CMU_LFXOCTRL_BUFCUR_DEFAULT << 20)    /**< Shifted mode DEFAULT for CMU_LFXOCTRL */
#define _CMU_LFXOCTRL_TIMEOUT_SHIFT                       24                                      /**< Shift value for CMU_TIMEOUT */
#define _CMU_LFXOCTRL_TIMEOUT_MASK                        0x7000000UL                             /**< Bit mask for CMU_TIMEOUT */
#define _CMU_LFXOCTRL_TIMEOUT_2CYCLES                     0x00000000UL                            /**< Mode 2CYCLES for CMU_LFXOCTRL */
#define _CMU_LFXOCTRL_TIMEOUT_256CYCLES                   0x00000001UL                            /**< Mode 256CYCLES for CMU_LFXOCTRL */
#define _CMU_LFXOCTRL_TIMEOUT_1KCYCLES                    0x00000002UL                            /**< Mode 1KCYCLES for CMU_LFXOCTRL */
#define _CMU_LFXOCTRL_TIMEOUT_2KCYCLES                    0x00000003UL                            /**< Mode 2KCYCLES for CMU_LFXOCTRL */
#define _CMU_LFXOCTRL_TIMEOUT_4KCYCLES                    0x00000004UL                            /**< Mode 4KCYCLES for CMU_LFXOCTRL */
#define _CMU_LFXOCTRL_TIMEOUT_8KCYCLES                    0x00000005UL                            /**< Mode 8KCYCLES for CMU_LFXOCTRL */
#define _CMU_LFXOCTRL_TIMEOUT_16KCYCLES                   0x00000006UL                            /**< Mode 16KCYCLES for CMU_LFXOCTRL */
#define _CMU_LFXOCTRL_TIMEOUT_DEFAULT                     0x00000007UL                            /**< Mode DEFAULT for CMU_LFXOCTRL */
#define _CMU_LFXOCTRL_TIMEOUT_32KCYCLES                   0x00000007UL                            /**< Mode 32KCYCLES for CMU_LFXOCTRL */
#define CMU_LFXOCTRL_TIMEOUT_2CYCLES                      (_CMU_LFXOCTRL_TIMEOUT_2CYCLES << 24)   /**< Shifted mode 2CYCLES for CMU_LFXOCTRL */
#define CMU_LFXOCTRL_TIMEOUT_256CYCLES                    (_CMU_LFXOCTRL_TIMEOUT_256CYCLES << 24) /**< Shifted mode 256CYCLES for CMU_LFXOCTRL */
#define CMU_LFXOCTRL_TIMEOUT_1KCYCLES                     (_CMU_LFXOCTRL_TIMEOUT_1KCYCLES << 24)  /**< Shifted mode 1KCYCLES for CMU_LFXOCTRL */
#define CMU_LFXOCTRL_TIMEOUT_2KCYCLES                     (_CMU_LFXOCTRL_TIMEOUT_2KCYCLES << 24)  /**< Shifted mode 2KCYCLES for CMU_LFXOCTRL */
#define CMU_LFXOCTRL_TIMEOUT_4KCYCLES                     (_CMU_LFXOCTRL_TIMEOUT_4KCYCLES << 24)  /**< Shifted mode 4KCYCLES for CMU_LFXOCTRL */
#define CMU_LFXOCTRL_TIMEOUT_8KCYCLES                     (_CMU_LFXOCTRL_TIMEOUT_8KCYCLES << 24)  /**< Shifted mode 8KCYCLES for CMU_LFXOCTRL */
#define CMU_LFXOCTRL_TIMEOUT_16KCYCLES                    (_CMU_LFXOCTRL_TIMEOUT_16KCYCLES << 24) /**< Shifted mode 16KCYCLES for CMU_LFXOCTRL */
#define CMU_LFXOCTRL_TIMEOUT_DEFAULT                      (_CMU_LFXOCTRL_TIMEOUT_DEFAULT << 24)   /**< Shifted mode DEFAULT for CMU_LFXOCTRL */
#define CMU_LFXOCTRL_TIMEOUT_32KCYCLES                    (_CMU_LFXOCTRL_TIMEOUT_32KCYCLES << 24) /**< Shifted mode 32KCYCLES for CMU_LFXOCTRL */

/* Bit fields for CMU DPLLCTRL */
#define _CMU_DPLLCTRL_RESETVALUE                          0x00000000UL                             /**< Default value for CMU_DPLLCTRL */
#define _CMU_DPLLCTRL_MASK                                0x0000001FUL                             /**< Mask for CMU_DPLLCTRL */
#define CMU_DPLLCTRL_MODE                                 (0x1UL << 0)                             /**< Operating Mode Control */
#define _CMU_DPLLCTRL_MODE_SHIFT                          0                                        /**< Shift value for CMU_MODE */
#define _CMU_DPLLCTRL_MODE_MASK                           0x1UL                                    /**< Bit mask for CMU_MODE */
#define _CMU_DPLLCTRL_MODE_DEFAULT                        0x00000000UL                             /**< Mode DEFAULT for CMU_DPLLCTRL */
#define _CMU_DPLLCTRL_MODE_FREQLL                         0x00000000UL                             /**< Mode FREQLL for CMU_DPLLCTRL */
#define _CMU_DPLLCTRL_MODE_PHASELL                        0x00000001UL                             /**< Mode PHASELL for CMU_DPLLCTRL */
#define CMU_DPLLCTRL_MODE_DEFAULT                         (_CMU_DPLLCTRL_MODE_DEFAULT << 0)        /**< Shifted mode DEFAULT for CMU_DPLLCTRL */
#define CMU_DPLLCTRL_MODE_FREQLL                          (_CMU_DPLLCTRL_MODE_FREQLL << 0)         /**< Shifted mode FREQLL for CMU_DPLLCTRL */
#define CMU_DPLLCTRL_MODE_PHASELL                         (_CMU_DPLLCTRL_MODE_PHASELL << 0)        /**< Shifted mode PHASELL for CMU_DPLLCTRL */
#define CMU_DPLLCTRL_EDGESEL                              (0x1UL << 1)                             /**< Reference Edge Select */
#define _CMU_DPLLCTRL_EDGESEL_SHIFT                       1                                        /**< Shift value for CMU_EDGESEL */
#define _CMU_DPLLCTRL_EDGESEL_MASK                        0x2UL                                    /**< Bit mask for CMU_EDGESEL */
#define _CMU_DPLLCTRL_EDGESEL_DEFAULT                     0x00000000UL                             /**< Mode DEFAULT for CMU_DPLLCTRL */
#define _CMU_DPLLCTRL_EDGESEL_FALL                        0x00000000UL                             /**< Mode FALL for CMU_DPLLCTRL */
#define _CMU_DPLLCTRL_EDGESEL_RISE                        0x00000001UL                             /**< Mode RISE for CMU_DPLLCTRL */
#define CMU_DPLLCTRL_EDGESEL_DEFAULT                      (_CMU_DPLLCTRL_EDGESEL_DEFAULT << 1)     /**< Shifted mode DEFAULT for CMU_DPLLCTRL */
#define CMU_DPLLCTRL_EDGESEL_FALL                         (_CMU_DPLLCTRL_EDGESEL_FALL << 1)        /**< Shifted mode FALL for CMU_DPLLCTRL */
#define CMU_DPLLCTRL_EDGESEL_RISE                         (_CMU_DPLLCTRL_EDGESEL_RISE << 1)        /**< Shifted mode RISE for CMU_DPLLCTRL */
#define CMU_DPLLCTRL_AUTORECOVER                          (0x1UL << 2)                             /**< Automatic Recovery Ctrl */
#define _CMU_DPLLCTRL_AUTORECOVER_SHIFT                   2                                        /**< Shift value for CMU_AUTORECOVER */
#define _CMU_DPLLCTRL_AUTORECOVER_MASK                    0x4UL                                    /**< Bit mask for CMU_AUTORECOVER */
#define _CMU_DPLLCTRL_AUTORECOVER_DEFAULT                 0x00000000UL                             /**< Mode DEFAULT for CMU_DPLLCTRL */
#define CMU_DPLLCTRL_AUTORECOVER_DEFAULT                  (_CMU_DPLLCTRL_AUTORECOVER_DEFAULT << 2) /**< Shifted mode DEFAULT for CMU_DPLLCTRL */
#define _CMU_DPLLCTRL_REFSEL_SHIFT                        3                                        /**< Shift value for CMU_REFSEL */
#define _CMU_DPLLCTRL_REFSEL_MASK                         0x18UL                                   /**< Bit mask for CMU_REFSEL */
#define _CMU_DPLLCTRL_REFSEL_DEFAULT                      0x00000000UL                             /**< Mode DEFAULT for CMU_DPLLCTRL */
#define _CMU_DPLLCTRL_REFSEL_HFXO                         0x00000000UL                             /**< Mode HFXO for CMU_DPLLCTRL */
#define _CMU_DPLLCTRL_REFSEL_LFXO                         0x00000001UL                             /**< Mode LFXO for CMU_DPLLCTRL */
#define _CMU_DPLLCTRL_REFSEL_CLKIN0                       0x00000003UL                             /**< Mode CLKIN0 for CMU_DPLLCTRL */
#define CMU_DPLLCTRL_REFSEL_DEFAULT                       (_CMU_DPLLCTRL_REFSEL_DEFAULT << 3)      /**< Shifted mode DEFAULT for CMU_DPLLCTRL */
#define CMU_DPLLCTRL_REFSEL_HFXO                          (_CMU_DPLLCTRL_REFSEL_HFXO << 3)         /**< Shifted mode HFXO for CMU_DPLLCTRL */
#define CMU_DPLLCTRL_REFSEL_LFXO                          (_CMU_DPLLCTRL_REFSEL_LFXO << 3)         /**< Shifted mode LFXO for CMU_DPLLCTRL */
#define CMU_DPLLCTRL_REFSEL_CLKIN0                        (_CMU_DPLLCTRL_REFSEL_CLKIN0 << 3)       /**< Shifted mode CLKIN0 for CMU_DPLLCTRL */

/* Bit fields for CMU DPLLCTRL1 */
#define _CMU_DPLLCTRL1_RESETVALUE                         0x00000000UL                     /**< Default value for CMU_DPLLCTRL1 */
#define _CMU_DPLLCTRL1_MASK                               0x0FFF0FFFUL                     /**< Mask for CMU_DPLLCTRL1 */
#define _CMU_DPLLCTRL1_M_SHIFT                            0                                /**< Shift value for CMU_M */
#define _CMU_DPLLCTRL1_M_MASK                             0xFFFUL                          /**< Bit mask for CMU_M */
#define _CMU_DPLLCTRL1_M_DEFAULT                          0x00000000UL                     /**< Mode DEFAULT for CMU_DPLLCTRL1 */
#define CMU_DPLLCTRL1_M_DEFAULT                           (_CMU_DPLLCTRL1_M_DEFAULT << 0)  /**< Shifted mode DEFAULT for CMU_DPLLCTRL1 */
#define _CMU_DPLLCTRL1_N_SHIFT                            16                               /**< Shift value for CMU_N */
#define _CMU_DPLLCTRL1_N_MASK                             0xFFF0000UL                      /**< Bit mask for CMU_N */
#define _CMU_DPLLCTRL1_N_DEFAULT                          0x00000000UL                     /**< Mode DEFAULT for CMU_DPLLCTRL1 */
#define CMU_DPLLCTRL1_N_DEFAULT                           (_CMU_DPLLCTRL1_N_DEFAULT << 16) /**< Shifted mode DEFAULT for CMU_DPLLCTRL1 */

/* Bit fields for CMU CALCTRL */
#define _CMU_CALCTRL_RESETVALUE                           0x00000000UL                            /**< Default value for CMU_CALCTRL */
#define _CMU_CALCTRL_MASK                                 0x0F0F01FFUL                            /**< Mask for CMU_CALCTRL */
#define _CMU_CALCTRL_UPSEL_SHIFT                          0                                       /**< Shift value for CMU_UPSEL */
#define _CMU_CALCTRL_UPSEL_MASK                           0xFUL                                   /**< Bit mask for CMU_UPSEL */
#define _CMU_CALCTRL_UPSEL_DEFAULT                        0x00000000UL                            /**< Mode DEFAULT for CMU_CALCTRL */
#define _CMU_CALCTRL_UPSEL_HFXO                           0x00000000UL                            /**< Mode HFXO for CMU_CALCTRL */
#define _CMU_CALCTRL_UPSEL_LFXO                           0x00000001UL                            /**< Mode LFXO for CMU_CALCTRL */
#define _CMU_CALCTRL_UPSEL_HFRCO                          0x00000002UL                            /**< Mode HFRCO for CMU_CALCTRL */
#define _CMU_CALCTRL_UPSEL_LFRCO                          0x00000003UL                            /**< Mode LFRCO for CMU_CALCTRL */
#define _CMU_CALCTRL_UPSEL_AUXHFRCO                       0x00000004UL                            /**< Mode AUXHFRCO for CMU_CALCTRL */
#define _CMU_CALCTRL_UPSEL_PRS                            0x00000005UL                            /**< Mode PRS for CMU_CALCTRL */
#define CMU_CALCTRL_UPSEL_DEFAULT                         (_CMU_CALCTRL_UPSEL_DEFAULT << 0)       /**< Shifted mode DEFAULT for CMU_CALCTRL */
#define CMU_CALCTRL_UPSEL_HFXO                            (_CMU_CALCTRL_UPSEL_HFXO << 0)          /**< Shifted mode HFXO for CMU_CALCTRL */
#define CMU_CALCTRL_UPSEL_LFXO                            (_CMU_CALCTRL_UPSEL_LFXO << 0)          /**< Shifted mode LFXO for CMU_CALCTRL */
#define CMU_CALCTRL_UPSEL_HFRCO                           (_CMU_CALCTRL_UPSEL_HFRCO << 0)         /**< Shifted mode HFRCO for CMU_CALCTRL */
#define CMU_CALCTRL_UPSEL_LFRCO                           (_CMU_CALCTRL_UPSEL_LFRCO << 0)         /**< Shifted mode LFRCO for CMU_CALCTRL */
#define CMU_CALCTRL_UPSEL_AUXHFRCO                        (_CMU_CALCTRL_UPSEL_AUXHFRCO << 0)      /**< Shifted mode AUXHFRCO for CMU_CALCTRL */
#define CMU_CALCTRL_UPSEL_PRS                             (_CMU_CALCTRL_UPSEL_PRS << 0)           /**< Shifted mode PRS for CMU_CALCTRL */
#define _CMU_CALCTRL_DOWNSEL_SHIFT                        4                                       /**< Shift value for CMU_DOWNSEL */
#define _CMU_CALCTRL_DOWNSEL_MASK                         0xF0UL                                  /**< Bit mask for CMU_DOWNSEL */
#define _CMU_CALCTRL_DOWNSEL_DEFAULT                      0x00000000UL                            /**< Mode DEFAULT for CMU_CALCTRL */
#define _CMU_CALCTRL_DOWNSEL_HFCLK                        0x00000000UL                            /**< Mode HFCLK for CMU_CALCTRL */
#define _CMU_CALCTRL_DOWNSEL_HFXO                         0x00000001UL                            /**< Mode HFXO for CMU_CALCTRL */
#define _CMU_CALCTRL_DOWNSEL_LFXO                         0x00000002UL                            /**< Mode LFXO for CMU_CALCTRL */
#define _CMU_CALCTRL_DOWNSEL_HFRCO                        0x00000003UL                            /**< Mode HFRCO for CMU_CALCTRL */
#define _CMU_CALCTRL_DOWNSEL_LFRCO                        0x00000004UL                            /**< Mode LFRCO for CMU_CALCTRL */
#define _CMU_CALCTRL_DOWNSEL_AUXHFRCO                     0x00000005UL                            /**< Mode AUXHFRCO for CMU_CALCTRL */
#define _CMU_CALCTRL_DOWNSEL_PRS                          0x00000006UL                            /**< Mode PRS for CMU_CALCTRL */
#define CMU_CALCTRL_DOWNSEL_DEFAULT                       (_CMU_CALCTRL_DOWNSEL_DEFAULT << 4)     /**< Shifted mode DEFAULT for CMU_CALCTRL */
#define CMU_CALCTRL_DOWNSEL_HFCLK                         (_CMU_CALCTRL_DOWNSEL_HFCLK << 4)       /**< Shifted mode HFCLK for CMU_CALCTRL */
#define CMU_CALCTRL_DOWNSEL_HFXO                          (_CMU_CALCTRL_DOWNSEL_HFXO << 4)        /**< Shifted mode HFXO for CMU_CALCTRL */
#define CMU_CALCTRL_DOWNSEL_LFXO                          (_CMU_CALCTRL_DOWNSEL_LFXO << 4)        /**< Shifted mode LFXO for CMU_CALCTRL */
#define CMU_CALCTRL_DOWNSEL_HFRCO                         (_CMU_CALCTRL_DOWNSEL_HFRCO << 4)       /**< Shifted mode HFRCO for CMU_CALCTRL */
#define CMU_CALCTRL_DOWNSEL_LFRCO                         (_CMU_CALCTRL_DOWNSEL_LFRCO << 4)       /**< Shifted mode LFRCO for CMU_CALCTRL */
#define CMU_CALCTRL_DOWNSEL_AUXHFRCO                      (_CMU_CALCTRL_DOWNSEL_AUXHFRCO << 4)    /**< Shifted mode AUXHFRCO for CMU_CALCTRL */
#define CMU_CALCTRL_DOWNSEL_PRS                           (_CMU_CALCTRL_DOWNSEL_PRS << 4)         /**< Shifted mode PRS for CMU_CALCTRL */
#define CMU_CALCTRL_CONT                                  (0x1UL << 8)                            /**< Continuous Calibration */
#define _CMU_CALCTRL_CONT_SHIFT                           8                                       /**< Shift value for CMU_CONT */
#define _CMU_CALCTRL_CONT_MASK                            0x100UL                                 /**< Bit mask for CMU_CONT */
#define _CMU_CALCTRL_CONT_DEFAULT                         0x00000000UL                            /**< Mode DEFAULT for CMU_CALCTRL */
#define CMU_CALCTRL_CONT_DEFAULT                          (_CMU_CALCTRL_CONT_DEFAULT << 8)        /**< Shifted mode DEFAULT for CMU_CALCTRL */
#define _CMU_CALCTRL_PRSUPSEL_SHIFT                       16                                      /**< Shift value for CMU_PRSUPSEL */
#define _CMU_CALCTRL_PRSUPSEL_MASK                        0xF0000UL                               /**< Bit mask for CMU_PRSUPSEL */
#define _CMU_CALCTRL_PRSUPSEL_DEFAULT                     0x00000000UL                            /**< Mode DEFAULT for CMU_CALCTRL */
#define _CMU_CALCTRL_PRSUPSEL_PRSCH0                      0x00000000UL                            /**< Mode PRSCH0 for CMU_CALCTRL */
#define _CMU_CALCTRL_PRSUPSEL_PRSCH1                      0x00000001UL                            /**< Mode PRSCH1 for CMU_CALCTRL */
#define _CMU_CALCTRL_PRSUPSEL_PRSCH2                      0x00000002UL                            /**< Mode PRSCH2 for CMU_CALCTRL */
#define _CMU_CALCTRL_PRSUPSEL_PRSCH3                      0x00000003UL                            /**< Mode PRSCH3 for CMU_CALCTRL */
#define _CMU_CALCTRL_PRSUPSEL_PRSCH4                      0x00000004UL                            /**< Mode PRSCH4 for CMU_CALCTRL */
#define _CMU_CALCTRL_PRSUPSEL_PRSCH5                      0x00000005UL                            /**< Mode PRSCH5 for CMU_CALCTRL */
#define _CMU_CALCTRL_PRSUPSEL_PRSCH6                      0x00000006UL                            /**< Mode PRSCH6 for CMU_CALCTRL */
#define _CMU_CALCTRL_PRSUPSEL_PRSCH7                      0x00000007UL                            /**< Mode PRSCH7 for CMU_CALCTRL */
#define _CMU_CALCTRL_PRSUPSEL_PRSCH8                      0x00000008UL                            /**< Mode PRSCH8 for CMU_CALCTRL */
#define _CMU_CALCTRL_PRSUPSEL_PRSCH9                      0x00000009UL                            /**< Mode PRSCH9 for CMU_CALCTRL */
#define _CMU_CALCTRL_PRSUPSEL_PRSCH10                     0x0000000AUL                            /**< Mode PRSCH10 for CMU_CALCTRL */
#define _CMU_CALCTRL_PRSUPSEL_PRSCH11                     0x0000000BUL                            /**< Mode PRSCH11 for CMU_CALCTRL */
#define CMU_CALCTRL_PRSUPSEL_DEFAULT                      (_CMU_CALCTRL_PRSUPSEL_DEFAULT << 16)   /**< Shifted mode DEFAULT for CMU_CALCTRL */
#define CMU_CALCTRL_PRSUPSEL_PRSCH0                       (_CMU_CALCTRL_PRSUPSEL_PRSCH0 << 16)    /**< Shifted mode PRSCH0 for CMU_CALCTRL */
#define CMU_CALCTRL_PRSUPSEL_PRSCH1                       (_CMU_CALCTRL_PRSUPSEL_PRSCH1 << 16)    /**< Shifted mode PRSCH1 for CMU_CALCTRL */
#define CMU_CALCTRL_PRSUPSEL_PRSCH2                       (_CMU_CALCTRL_PRSUPSEL_PRSCH2 << 16)    /**< Shifted mode PRSCH2 for CMU_CALCTRL */
#define CMU_CALCTRL_PRSUPSEL_PRSCH3                       (_CMU_CALCTRL_PRSUPSEL_PRSCH3 << 16)    /**< Shifted mode PRSCH3 for CMU_CALCTRL */
#define CMU_CALCTRL_PRSUPSEL_PRSCH4                       (_CMU_CALCTRL_PRSUPSEL_PRSCH4 << 16)    /**< Shifted mode PRSCH4 for CMU_CALCTRL */
#define CMU_CALCTRL_PRSUPSEL_PRSCH5                       (_CMU_CALCTRL_PRSUPSEL_PRSCH5 << 16)    /**< Shifted mode PRSCH5 for CMU_CALCTRL */
#define CMU_CALCTRL_PRSUPSEL_PRSCH6                       (_CMU_CALCTRL_PRSUPSEL_PRSCH6 << 16)    /**< Shifted mode PRSCH6 for CMU_CALCTRL */
#define CMU_CALCTRL_PRSUPSEL_PRSCH7                       (_CMU_CALCTRL_PRSUPSEL_PRSCH7 << 16)    /**< Shifted mode PRSCH7 for CMU_CALCTRL */
#define CMU_CALCTRL_PRSUPSEL_PRSCH8                       (_CMU_CALCTRL_PRSUPSEL_PRSCH8 << 16)    /**< Shifted mode PRSCH8 for CMU_CALCTRL */
#define CMU_CALCTRL_PRSUPSEL_PRSCH9                       (_CMU_CALCTRL_PRSUPSEL_PRSCH9 << 16)    /**< Shifted mode PRSCH9 for CMU_CALCTRL */
#define CMU_CALCTRL_PRSUPSEL_PRSCH10                      (_CMU_CALCTRL_PRSUPSEL_PRSCH10 << 16)   /**< Shifted mode PRSCH10 for CMU_CALCTRL */
#define CMU_CALCTRL_PRSUPSEL_PRSCH11                      (_CMU_CALCTRL_PRSUPSEL_PRSCH11 << 16)   /**< Shifted mode PRSCH11 for CMU_CALCTRL */
#define _CMU_CALCTRL_PRSDOWNSEL_SHIFT                     24                                      /**< Shift value for CMU_PRSDOWNSEL */
#define _CMU_CALCTRL_PRSDOWNSEL_MASK                      0xF000000UL                             /**< Bit mask for CMU_PRSDOWNSEL */
#define _CMU_CALCTRL_PRSDOWNSEL_DEFAULT                   0x00000000UL                            /**< Mode DEFAULT for CMU_CALCTRL */
#define _CMU_CALCTRL_PRSDOWNSEL_PRSCH0                    0x00000000UL                            /**< Mode PRSCH0 for CMU_CALCTRL */
#define _CMU_CALCTRL_PRSDOWNSEL_PRSCH1                    0x00000001UL                            /**< Mode PRSCH1 for CMU_CALCTRL */
#define _CMU_CALCTRL_PRSDOWNSEL_PRSCH2                    0x00000002UL                            /**< Mode PRSCH2 for CMU_CALCTRL */
#define _CMU_CALCTRL_PRSDOWNSEL_PRSCH3                    0x00000003UL                            /**< Mode PRSCH3 for CMU_CALCTRL */
#define _CMU_CALCTRL_PRSDOWNSEL_PRSCH4                    0x00000004UL                            /**< Mode PRSCH4 for CMU_CALCTRL */
#define _CMU_CALCTRL_PRSDOWNSEL_PRSCH5                    0x00000005UL                            /**< Mode PRSCH5 for CMU_CALCTRL */
#define _CMU_CALCTRL_PRSDOWNSEL_PRSCH6                    0x00000006UL                            /**< Mode PRSCH6 for CMU_CALCTRL */
#define _CMU_CALCTRL_PRSDOWNSEL_PRSCH7                    0x00000007UL                            /**< Mode PRSCH7 for CMU_CALCTRL */
#define _CMU_CALCTRL_PRSDOWNSEL_PRSCH8                    0x00000008UL                            /**< Mode PRSCH8 for CMU_CALCTRL */
#define _CMU_CALCTRL_PRSDOWNSEL_PRSCH9                    0x00000009UL                            /**< Mode PRSCH9 for CMU_CALCTRL */
#define _CMU_CALCTRL_PRSDOWNSEL_PRSCH10                   0x0000000AUL                            /**< Mode PRSCH10 for CMU_CALCTRL */
#define _CMU_CALCTRL_PRSDOWNSEL_PRSCH11                   0x0000000BUL                            /**< Mode PRSCH11 for CMU_CALCTRL */
#define CMU_CALCTRL_PRSDOWNSEL_DEFAULT                    (_CMU_CALCTRL_PRSDOWNSEL_DEFAULT << 24) /**< Shifted mode DEFAULT for CMU_CALCTRL */
#define CMU_CALCTRL_PRSDOWNSEL_PRSCH0                     (_CMU_CALCTRL_PRSDOWNSEL_PRSCH0 << 24)  /**< Shifted mode PRSCH0 for CMU_CALCTRL */
#define CMU_CALCTRL_PRSDOWNSEL_PRSCH1                     (_CMU_CALCTRL_PRSDOWNSEL_PRSCH1 << 24)  /**< Shifted mode PRSCH1 for CMU_CALCTRL */
#define CMU_CALCTRL_PRSDOWNSEL_PRSCH2                     (_CMU_CALCTRL_PRSDOWNSEL_PRSCH2 << 24)  /**< Shifted mode PRSCH2 for CMU_CALCTRL */
#define CMU_CALCTRL_PRSDOWNSEL_PRSCH3                     (_CMU_CALCTRL_PRSDOWNSEL_PRSCH3 << 24)  /**< Shifted mode PRSCH3 for CMU_CALCTRL */
#define CMU_CALCTRL_PRSDOWNSEL_PRSCH4                     (_CMU_CALCTRL_PRSDOWNSEL_PRSCH4 << 24)  /**< Shifted mode PRSCH4 for CMU_CALCTRL */
#define CMU_CALCTRL_PRSDOWNSEL_PRSCH5                     (_CMU_CALCTRL_PRSDOWNSEL_PRSCH5 << 24)  /**< Shifted mode PRSCH5 for CMU_CALCTRL */
#define CMU_CALCTRL_PRSDOWNSEL_PRSCH6                     (_CMU_CALCTRL_PRSDOWNSEL_PRSCH6 << 24)  /**< Shifted mode PRSCH6 for CMU_CALCTRL */
#define CMU_CALCTRL_PRSDOWNSEL_PRSCH7                     (_CMU_CALCTRL_PRSDOWNSEL_PRSCH7 << 24)  /**< Shifted mode PRSCH7 for CMU_CALCTRL */
#define CMU_CALCTRL_PRSDOWNSEL_PRSCH8                     (_CMU_CALCTRL_PRSDOWNSEL_PRSCH8 << 24)  /**< Shifted mode PRSCH8 for CMU_CALCTRL */
#define CMU_CALCTRL_PRSDOWNSEL_PRSCH9                     (_CMU_CALCTRL_PRSDOWNSEL_PRSCH9 << 24)  /**< Shifted mode PRSCH9 for CMU_CALCTRL */
#define CMU_CALCTRL_PRSDOWNSEL_PRSCH10                    (_CMU_CALCTRL_PRSDOWNSEL_PRSCH10 << 24) /**< Shifted mode PRSCH10 for CMU_CALCTRL */
#define CMU_CALCTRL_PRSDOWNSEL_PRSCH11                    (_CMU_CALCTRL_PRSDOWNSEL_PRSCH11 << 24) /**< Shifted mode PRSCH11 for CMU_CALCTRL */

/* Bit fields for CMU CALCNT */
#define _CMU_CALCNT_RESETVALUE                            0x00000000UL                      /**< Default value for CMU_CALCNT */
#define _CMU_CALCNT_MASK                                  0x000FFFFFUL                      /**< Mask for CMU_CALCNT */
#define _CMU_CALCNT_CALCNT_SHIFT                          0                                 /**< Shift value for CMU_CALCNT */
#define _CMU_CALCNT_CALCNT_MASK                           0xFFFFFUL                         /**< Bit mask for CMU_CALCNT */
#define _CMU_CALCNT_CALCNT_DEFAULT                        0x00000000UL                      /**< Mode DEFAULT for CMU_CALCNT */
#define CMU_CALCNT_CALCNT_DEFAULT                         (_CMU_CALCNT_CALCNT_DEFAULT << 0) /**< Shifted mode DEFAULT for CMU_CALCNT */

/* Bit fields for CMU OSCENCMD */
#define _CMU_OSCENCMD_RESETVALUE                          0x00000000UL                             /**< Default value for CMU_OSCENCMD */
#define _CMU_OSCENCMD_MASK                                0x000033FFUL                             /**< Mask for CMU_OSCENCMD */
#define CMU_OSCENCMD_HFRCOEN                              (0x1UL << 0)                             /**< HFRCO Enable */
#define _CMU_OSCENCMD_HFRCOEN_SHIFT                       0                                        /**< Shift value for CMU_HFRCOEN */
#define _CMU_OSCENCMD_HFRCOEN_MASK                        0x1UL                                    /**< Bit mask for CMU_HFRCOEN */
#define _CMU_OSCENCMD_HFRCOEN_DEFAULT                     0x00000000UL                             /**< Mode DEFAULT for CMU_OSCENCMD */
#define CMU_OSCENCMD_HFRCOEN_DEFAULT                      (_CMU_OSCENCMD_HFRCOEN_DEFAULT << 0)     /**< Shifted mode DEFAULT for CMU_OSCENCMD */
#define CMU_OSCENCMD_HFRCODIS                             (0x1UL << 1)                             /**< HFRCO Disable */
#define _CMU_OSCENCMD_HFRCODIS_SHIFT                      1                                        /**< Shift value for CMU_HFRCODIS */
#define _CMU_OSCENCMD_HFRCODIS_MASK                       0x2UL                                    /**< Bit mask for CMU_HFRCODIS */
#define _CMU_OSCENCMD_HFRCODIS_DEFAULT                    0x00000000UL                             /**< Mode DEFAULT for CMU_OSCENCMD */
#define CMU_OSCENCMD_HFRCODIS_DEFAULT                     (_CMU_OSCENCMD_HFRCODIS_DEFAULT << 1)    /**< Shifted mode DEFAULT for CMU_OSCENCMD */
#define CMU_OSCENCMD_HFXOEN                               (0x1UL << 2)                             /**< HFXO Enable */
#define _CMU_OSCENCMD_HFXOEN_SHIFT                        2                                        /**< Shift value for CMU_HFXOEN */
#define _CMU_OSCENCMD_HFXOEN_MASK                         0x4UL                                    /**< Bit mask for CMU_HFXOEN */
#define _CMU_OSCENCMD_HFXOEN_DEFAULT                      0x00000000UL                             /**< Mode DEFAULT for CMU_OSCENCMD */
#define CMU_OSCENCMD_HFXOEN_DEFAULT                       (_CMU_OSCENCMD_HFXOEN_DEFAULT << 2)      /**< Shifted mode DEFAULT for CMU_OSCENCMD */
#define CMU_OSCENCMD_HFXODIS                              (0x1UL << 3)                             /**< HFXO Disable */
#define _CMU_OSCENCMD_HFXODIS_SHIFT                       3                                        /**< Shift value for CMU_HFXODIS */
#define _CMU_OSCENCMD_HFXODIS_MASK                        0x8UL                                    /**< Bit mask for CMU_HFXODIS */
#define _CMU_OSCENCMD_HFXODIS_DEFAULT                     0x00000000UL                             /**< Mode DEFAULT for CMU_OSCENCMD */
#define CMU_OSCENCMD_HFXODIS_DEFAULT                      (_CMU_OSCENCMD_HFXODIS_DEFAULT << 3)     /**< Shifted mode DEFAULT for CMU_OSCENCMD */
#define CMU_OSCENCMD_AUXHFRCOEN                           (0x1UL << 4)                             /**< AUXHFRCO Enable */
#define _CMU_OSCENCMD_AUXHFRCOEN_SHIFT                    4                                        /**< Shift value for CMU_AUXHFRCOEN */
#define _CMU_OSCENCMD_AUXHFRCOEN_MASK                     0x10UL                                   /**< Bit mask for CMU_AUXHFRCOEN */
#define _CMU_OSCENCMD_AUXHFRCOEN_DEFAULT                  0x00000000UL                             /**< Mode DEFAULT for CMU_OSCENCMD */
#define CMU_OSCENCMD_AUXHFRCOEN_DEFAULT                   (_CMU_OSCENCMD_AUXHFRCOEN_DEFAULT << 4)  /**< Shifted mode DEFAULT for CMU_OSCENCMD */
#define CMU_OSCENCMD_AUXHFRCODIS                          (0x1UL << 5)                             /**< AUXHFRCO Disable */
#define _CMU_OSCENCMD_AUXHFRCODIS_SHIFT                   5                                        /**< Shift value for CMU_AUXHFRCODIS */
#define _CMU_OSCENCMD_AUXHFRCODIS_MASK                    0x20UL                                   /**< Bit mask for CMU_AUXHFRCODIS */
#define _CMU_OSCENCMD_AUXHFRCODIS_DEFAULT                 0x00000000UL                             /**< Mode DEFAULT for CMU_OSCENCMD */
#define CMU_OSCENCMD_AUXHFRCODIS_DEFAULT                  (_CMU_OSCENCMD_AUXHFRCODIS_DEFAULT << 5) /**< Shifted mode DEFAULT for CMU_OSCENCMD */
#define CMU_OSCENCMD_LFRCOEN                              (0x1UL << 6)                             /**< LFRCO Enable */
#define _CMU_OSCENCMD_LFRCOEN_SHIFT                       6                                        /**< Shift value for CMU_LFRCOEN */
#define _CMU_OSCENCMD_LFRCOEN_MASK                        0x40UL                                   /**< Bit mask for CMU_LFRCOEN */
#define _CMU_OSCENCMD_LFRCOEN_DEFAULT                     0x00000000UL                             /**< Mode DEFAULT for CMU_OSCENCMD */
#define CMU_OSCENCMD_LFRCOEN_DEFAULT                      (_CMU_OSCENCMD_LFRCOEN_DEFAULT << 6)     /**< Shifted mode DEFAULT for CMU_OSCENCMD */
#define CMU_OSCENCMD_LFRCODIS                             (0x1UL << 7)                             /**< LFRCO Disable */
#define _CMU_OSCENCMD_LFRCODIS_SHIFT                      7                                        /**< Shift value for CMU_LFRCODIS */
#define _CMU_OSCENCMD_LFRCODIS_MASK                       0x80UL                                   /**< Bit mask for CMU_LFRCODIS */
#define _CMU_OSCENCMD_LFRCODIS_DEFAULT                    0x00000000UL                             /**< Mode DEFAULT for CMU_OSCENCMD */
#define CMU_OSCENCMD_LFRCODIS_DEFAULT                     (_CMU_OSCENCMD_LFRCODIS_DEFAULT << 7)    /**< Shifted mode DEFAULT for CMU_OSCENCMD */
#define CMU_OSCENCMD_LFXOEN                               (0x1UL << 8)                             /**< LFXO Enable */
#define _CMU_OSCENCMD_LFXOEN_SHIFT                        8                                        /**< Shift value for CMU_LFXOEN */
#define _CMU_OSCENCMD_LFXOEN_MASK                         0x100UL                                  /**< Bit mask for CMU_LFXOEN */
#define _CMU_OSCENCMD_LFXOEN_DEFAULT                      0x00000000UL                             /**< Mode DEFAULT for CMU_OSCENCMD */
#define CMU_OSCENCMD_LFXOEN_DEFAULT                       (_CMU_OSCENCMD_LFXOEN_DEFAULT << 8)      /**< Shifted mode DEFAULT for CMU_OSCENCMD */
#define CMU_OSCENCMD_LFXODIS                              (0x1UL << 9)                             /**< LFXO Disable */
#define _CMU_OSCENCMD_LFXODIS_SHIFT                       9                                        /**< Shift value for CMU_LFXODIS */
#define _CMU_OSCENCMD_LFXODIS_MASK                        0x200UL                                  /**< Bit mask for CMU_LFXODIS */
#define _CMU_OSCENCMD_LFXODIS_DEFAULT                     0x00000000UL                             /**< Mode DEFAULT for CMU_OSCENCMD */
#define CMU_OSCENCMD_LFXODIS_DEFAULT                      (_CMU_OSCENCMD_LFXODIS_DEFAULT << 9)     /**< Shifted mode DEFAULT for CMU_OSCENCMD */
#define CMU_OSCENCMD_DPLLEN                               (0x1UL << 12)                            /**< DPLL Enable */
#define _CMU_OSCENCMD_DPLLEN_SHIFT                        12                                       /**< Shift value for CMU_DPLLEN */
#define _CMU_OSCENCMD_DPLLEN_MASK                         0x1000UL                                 /**< Bit mask for CMU_DPLLEN */
#define _CMU_OSCENCMD_DPLLEN_DEFAULT                      0x00000000UL                             /**< Mode DEFAULT for CMU_OSCENCMD */
#define CMU_OSCENCMD_DPLLEN_DEFAULT                       (_CMU_OSCENCMD_DPLLEN_DEFAULT << 12)     /**< Shifted mode DEFAULT for CMU_OSCENCMD */
#define CMU_OSCENCMD_DPLLDIS                              (0x1UL << 13)                            /**< DPLL Disable */
#define _CMU_OSCENCMD_DPLLDIS_SHIFT                       13                                       /**< Shift value for CMU_DPLLDIS */
#define _CMU_OSCENCMD_DPLLDIS_MASK                        0x2000UL                                 /**< Bit mask for CMU_DPLLDIS */
#define _CMU_OSCENCMD_DPLLDIS_DEFAULT                     0x00000000UL                             /**< Mode DEFAULT for CMU_OSCENCMD */
#define CMU_OSCENCMD_DPLLDIS_DEFAULT                      (_CMU_OSCENCMD_DPLLDIS_DEFAULT << 13)    /**< Shifted mode DEFAULT for CMU_OSCENCMD */

/* Bit fields for CMU CMD */
#define _CMU_CMD_RESETVALUE                               0x00000000UL                              /**< Default value for CMU_CMD */
#define _CMU_CMD_MASK                                     0x00000033UL                              /**< Mask for CMU_CMD */
#define CMU_CMD_CALSTART                                  (0x1UL << 0)                              /**< Calibration Start */
#define _CMU_CMD_CALSTART_SHIFT                           0                                         /**< Shift value for CMU_CALSTART */
#define _CMU_CMD_CALSTART_MASK                            0x1UL                                     /**< Bit mask for CMU_CALSTART */
#define _CMU_CMD_CALSTART_DEFAULT                         0x00000000UL                              /**< Mode DEFAULT for CMU_CMD */
#define CMU_CMD_CALSTART_DEFAULT                          (_CMU_CMD_CALSTART_DEFAULT << 0)          /**< Shifted mode DEFAULT for CMU_CMD */
#define CMU_CMD_CALSTOP                                   (0x1UL << 1)                              /**< Calibration Stop */
#define _CMU_CMD_CALSTOP_SHIFT                            1                                         /**< Shift value for CMU_CALSTOP */
#define _CMU_CMD_CALSTOP_MASK                             0x2UL                                     /**< Bit mask for CMU_CALSTOP */
#define _CMU_CMD_CALSTOP_DEFAULT                          0x00000000UL                              /**< Mode DEFAULT for CMU_CMD */
#define CMU_CMD_CALSTOP_DEFAULT                           (_CMU_CMD_CALSTOP_DEFAULT << 1)           /**< Shifted mode DEFAULT for CMU_CMD */
#define CMU_CMD_HFXOPEAKDETSTART                          (0x1UL << 4)                              /**< HFXO Peak Detection Start */
#define _CMU_CMD_HFXOPEAKDETSTART_SHIFT                   4                                         /**< Shift value for CMU_HFXOPEAKDETSTART */
#define _CMU_CMD_HFXOPEAKDETSTART_MASK                    0x10UL                                    /**< Bit mask for CMU_HFXOPEAKDETSTART */
#define _CMU_CMD_HFXOPEAKDETSTART_DEFAULT                 0x00000000UL                              /**< Mode DEFAULT for CMU_CMD */
#define CMU_CMD_HFXOPEAKDETSTART_DEFAULT                  (_CMU_CMD_HFXOPEAKDETSTART_DEFAULT << 4)  /**< Shifted mode DEFAULT for CMU_CMD */
#define CMU_CMD_HFXOSHUNTOPTSTART                         (0x1UL << 5)                              /**< HFXO Shunt Current Optimization Start */
#define _CMU_CMD_HFXOSHUNTOPTSTART_SHIFT                  5                                         /**< Shift value for CMU_HFXOSHUNTOPTSTART */
#define _CMU_CMD_HFXOSHUNTOPTSTART_MASK                   0x20UL                                    /**< Bit mask for CMU_HFXOSHUNTOPTSTART */
#define _CMU_CMD_HFXOSHUNTOPTSTART_DEFAULT                0x00000000UL                              /**< Mode DEFAULT for CMU_CMD */
#define CMU_CMD_HFXOSHUNTOPTSTART_DEFAULT                 (_CMU_CMD_HFXOSHUNTOPTSTART_DEFAULT << 5) /**< Shifted mode DEFAULT for CMU_CMD */

/* Bit fields for CMU DBGCLKSEL */
#define _CMU_DBGCLKSEL_RESETVALUE                         0x00000000UL                       /**< Default value for CMU_DBGCLKSEL */
#define _CMU_DBGCLKSEL_MASK                               0x00000001UL                       /**< Mask for CMU_DBGCLKSEL */
#define _CMU_DBGCLKSEL_DBG_SHIFT                          0                                  /**< Shift value for CMU_DBG */
#define _CMU_DBGCLKSEL_DBG_MASK                           0x1UL                              /**< Bit mask for CMU_DBG */
#define _CMU_DBGCLKSEL_DBG_DEFAULT                        0x00000000UL                       /**< Mode DEFAULT for CMU_DBGCLKSEL */
#define _CMU_DBGCLKSEL_DBG_AUXHFRCO                       0x00000000UL                       /**< Mode AUXHFRCO for CMU_DBGCLKSEL */
#define _CMU_DBGCLKSEL_DBG_HFCLK                          0x00000001UL                       /**< Mode HFCLK for CMU_DBGCLKSEL */
#define CMU_DBGCLKSEL_DBG_DEFAULT                         (_CMU_DBGCLKSEL_DBG_DEFAULT << 0)  /**< Shifted mode DEFAULT for CMU_DBGCLKSEL */
#define CMU_DBGCLKSEL_DBG_AUXHFRCO                        (_CMU_DBGCLKSEL_DBG_AUXHFRCO << 0) /**< Shifted mode AUXHFRCO for CMU_DBGCLKSEL */
#define CMU_DBGCLKSEL_DBG_HFCLK                           (_CMU_DBGCLKSEL_DBG_HFCLK << 0)    /**< Shifted mode HFCLK for CMU_DBGCLKSEL */

/* Bit fields for CMU HFCLKSEL */
#define _CMU_HFCLKSEL_RESETVALUE                          0x00000000UL                      /**< Default value for CMU_HFCLKSEL */
#define _CMU_HFCLKSEL_MASK                                0x00000007UL                      /**< Mask for CMU_HFCLKSEL */
#define _CMU_HFCLKSEL_HF_SHIFT                            0                                 /**< Shift value for CMU_HF */
#define _CMU_HFCLKSEL_HF_MASK                             0x7UL                             /**< Bit mask for CMU_HF */
#define _CMU_HFCLKSEL_HF_DEFAULT                          0x00000000UL                      /**< Mode DEFAULT for CMU_HFCLKSEL */
#define _CMU_HFCLKSEL_HF_HFRCO                            0x00000001UL                      /**< Mode HFRCO for CMU_HFCLKSEL */
#define _CMU_HFCLKSEL_HF_HFXO                             0x00000002UL                      /**< Mode HFXO for CMU_HFCLKSEL */
#define _CMU_HFCLKSEL_HF_LFRCO                            0x00000003UL                      /**< Mode LFRCO for CMU_HFCLKSEL */
#define _CMU_HFCLKSEL_HF_LFXO                             0x00000004UL                      /**< Mode LFXO for CMU_HFCLKSEL */
#define _CMU_HFCLKSEL_HF_HFRCODIV2                        0x00000005UL                      /**< Mode HFRCODIV2 for CMU_HFCLKSEL */
#define _CMU_HFCLKSEL_HF_CLKIN0                           0x00000007UL                      /**< Mode CLKIN0 for CMU_HFCLKSEL */
#define CMU_HFCLKSEL_HF_DEFAULT                           (_CMU_HFCLKSEL_HF_DEFAULT << 0)   /**< Shifted mode DEFAULT for CMU_HFCLKSEL */
#define CMU_HFCLKSEL_HF_HFRCO                             (_CMU_HFCLKSEL_HF_HFRCO << 0)     /**< Shifted mode HFRCO for CMU_HFCLKSEL */
#define CMU_HFCLKSEL_HF_HFXO                              (_CMU_HFCLKSEL_HF_HFXO << 0)      /**< Shifted mode HFXO for CMU_HFCLKSEL */
#define CMU_HFCLKSEL_HF_LFRCO                             (_CMU_HFCLKSEL_HF_LFRCO << 0)     /**< Shifted mode LFRCO for CMU_HFCLKSEL */
#define CMU_HFCLKSEL_HF_LFXO                              (_CMU_HFCLKSEL_HF_LFXO << 0)      /**< Shifted mode LFXO for CMU_HFCLKSEL */
#define CMU_HFCLKSEL_HF_HFRCODIV2                         (_CMU_HFCLKSEL_HF_HFRCODIV2 << 0) /**< Shifted mode HFRCODIV2 for CMU_HFCLKSEL */
#define CMU_HFCLKSEL_HF_CLKIN0                            (_CMU_HFCLKSEL_HF_CLKIN0 << 0)    /**< Shifted mode CLKIN0 for CMU_HFCLKSEL */

/* Bit fields for CMU LFACLKSEL */
#define _CMU_LFACLKSEL_RESETVALUE                         0x00000000UL                       /**< Default value for CMU_LFACLKSEL */
#define _CMU_LFACLKSEL_MASK                               0x00000007UL                       /**< Mask for CMU_LFACLKSEL */
#define _CMU_LFACLKSEL_LFA_SHIFT                          0                                  /**< Shift value for CMU_LFA */
#define _CMU_LFACLKSEL_LFA_MASK                           0x7UL                              /**< Bit mask for CMU_LFA */
#define _CMU_LFACLKSEL_LFA_DEFAULT                        0x00000000UL                       /**< Mode DEFAULT for CMU_LFACLKSEL */
#define _CMU_LFACLKSEL_LFA_DISABLED                       0x00000000UL                       /**< Mode DISABLED for CMU_LFACLKSEL */
#define _CMU_LFACLKSEL_LFA_LFRCO                          0x00000001UL                       /**< Mode LFRCO for CMU_LFACLKSEL */
#define _CMU_LFACLKSEL_LFA_LFXO                           0x00000002UL                       /**< Mode LFXO for CMU_LFACLKSEL */
#define _CMU_LFACLKSEL_LFA_ULFRCO                         0x00000004UL                       /**< Mode ULFRCO for CMU_LFACLKSEL */
#define CMU_LFACLKSEL_LFA_DEFAULT                         (_CMU_LFACLKSEL_LFA_DEFAULT << 0)  /**< Shifted mode DEFAULT for CMU_LFACLKSEL */
#define CMU_LFACLKSEL_LFA_DISABLED                        (_CMU_LFACLKSEL_LFA_DISABLED << 0) /**< Shifted mode DISABLED for CMU_LFACLKSEL */
#define CMU_LFACLKSEL_LFA_LFRCO                           (_CMU_LFACLKSEL_LFA_LFRCO << 0)    /**< Shifted mode LFRCO for CMU_LFACLKSEL */
#define CMU_LFACLKSEL_LFA_LFXO                            (_CMU_LFACLKSEL_LFA_LFXO << 0)     /**< Shifted mode LFXO for CMU_LFACLKSEL */
#define CMU_LFACLKSEL_LFA_ULFRCO                          (_CMU_LFACLKSEL_LFA_ULFRCO << 0)   /**< Shifted mode ULFRCO for CMU_LFACLKSEL */

/* Bit fields for CMU LFBCLKSEL */
#define _CMU_LFBCLKSEL_RESETVALUE                         0x00000000UL                       /**< Default value for CMU_LFBCLKSEL */
#define _CMU_LFBCLKSEL_MASK                               0x00000007UL                       /**< Mask for CMU_LFBCLKSEL */
#define _CMU_LFBCLKSEL_LFB_SHIFT                          0                                  /**< Shift value for CMU_LFB */
#define _CMU_LFBCLKSEL_LFB_MASK                           0x7UL                              /**< Bit mask for CMU_LFB */
#define _CMU_LFBCLKSEL_LFB_DEFAULT                        0x00000000UL                       /**< Mode DEFAULT for CMU_LFBCLKSEL */
#define _CMU_LFBCLKSEL_LFB_DISABLED                       0x00000000UL                       /**< Mode DISABLED for CMU_LFBCLKSEL */
#define _CMU_LFBCLKSEL_LFB_LFRCO                          0x00000001UL                       /**< Mode LFRCO for CMU_LFBCLKSEL */
#define _CMU_LFBCLKSEL_LFB_LFXO                           0x00000002UL                       /**< Mode LFXO for CMU_LFBCLKSEL */
#define _CMU_LFBCLKSEL_LFB_HFCLKLE                        0x00000003UL                       /**< Mode HFCLKLE for CMU_LFBCLKSEL */
#define _CMU_LFBCLKSEL_LFB_ULFRCO                         0x00000004UL                       /**< Mode ULFRCO for CMU_LFBCLKSEL */
#define CMU_LFBCLKSEL_LFB_DEFAULT                         (_CMU_LFBCLKSEL_LFB_DEFAULT << 0)  /**< Shifted mode DEFAULT for CMU_LFBCLKSEL */
#define CMU_LFBCLKSEL_LFB_DISABLED                        (_CMU_LFBCLKSEL_LFB_DISABLED << 0) /**< Shifted mode DISABLED for CMU_LFBCLKSEL */
#define CMU_LFBCLKSEL_LFB_LFRCO                           (_CMU_LFBCLKSEL_LFB_LFRCO << 0)    /**< Shifted mode LFRCO for CMU_LFBCLKSEL */
#define CMU_LFBCLKSEL_LFB_LFXO                            (_CMU_LFBCLKSEL_LFB_LFXO << 0)     /**< Shifted mode LFXO for CMU_LFBCLKSEL */
#define CMU_LFBCLKSEL_LFB_HFCLKLE                         (_CMU_LFBCLKSEL_LFB_HFCLKLE << 0)  /**< Shifted mode HFCLKLE for CMU_LFBCLKSEL */
#define CMU_LFBCLKSEL_LFB_ULFRCO                          (_CMU_LFBCLKSEL_LFB_ULFRCO << 0)   /**< Shifted mode ULFRCO for CMU_LFBCLKSEL */

/* Bit fields for CMU LFECLKSEL */
#define _CMU_LFECLKSEL_RESETVALUE                         0x00000000UL                       /**< Default value for CMU_LFECLKSEL */
#define _CMU_LFECLKSEL_MASK                               0x00000007UL                       /**< Mask for CMU_LFECLKSEL */
#define _CMU_LFECLKSEL_LFE_SHIFT                          0                                  /**< Shift value for CMU_LFE */
#define _CMU_LFECLKSEL_LFE_MASK                           0x7UL                              /**< Bit mask for CMU_LFE */
#define _CMU_LFECLKSEL_LFE_DEFAULT                        0x00000000UL                       /**< Mode DEFAULT for CMU_LFECLKSEL */
#define _CMU_LFECLKSEL_LFE_DISABLED                       0x00000000UL                       /**< Mode DISABLED for CMU_LFECLKSEL */
#define _CMU_LFECLKSEL_LFE_LFRCO                          0x00000001UL                       /**< Mode LFRCO for CMU_LFECLKSEL */
#define _CMU_LFECLKSEL_LFE_LFXO                           0x00000002UL                       /**< Mode LFXO for CMU_LFECLKSEL */
#define _CMU_LFECLKSEL_LFE_ULFRCO                         0x00000004UL                       /**< Mode ULFRCO for CMU_LFECLKSEL */
#define CMU_LFECLKSEL_LFE_DEFAULT                         (_CMU_LFECLKSEL_LFE_DEFAULT << 0)  /**< Shifted mode DEFAULT for CMU_LFECLKSEL */
#define CMU_LFECLKSEL_LFE_DISABLED                        (_CMU_LFECLKSEL_LFE_DISABLED << 0) /**< Shifted mode DISABLED for CMU_LFECLKSEL */
#define CMU_LFECLKSEL_LFE_LFRCO                           (_CMU_LFECLKSEL_LFE_LFRCO << 0)    /**< Shifted mode LFRCO for CMU_LFECLKSEL */
#define CMU_LFECLKSEL_LFE_LFXO                            (_CMU_LFECLKSEL_LFE_LFXO << 0)     /**< Shifted mode LFXO for CMU_LFECLKSEL */
#define CMU_LFECLKSEL_LFE_ULFRCO                          (_CMU_LFECLKSEL_LFE_ULFRCO << 0)   /**< Shifted mode ULFRCO for CMU_LFECLKSEL */

/* Bit fields for CMU STATUS */
#define _CMU_STATUS_RESETVALUE                            0x00010003UL                                /**< Default value for CMU_STATUS */
#define _CMU_STATUS_MASK                                  0x3FE133FFUL                                /**< Mask for CMU_STATUS */
#define CMU_STATUS_HFRCOENS                               (0x1UL << 0)                                /**< HFRCO Enable Status */
#define _CMU_STATUS_HFRCOENS_SHIFT                        0                                           /**< Shift value for CMU_HFRCOENS */
#define _CMU_STATUS_HFRCOENS_MASK                         0x1UL                                       /**< Bit mask for CMU_HFRCOENS */
#define _CMU_STATUS_HFRCOENS_DEFAULT                      0x00000001UL                                /**< Mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_HFRCOENS_DEFAULT                       (_CMU_STATUS_HFRCOENS_DEFAULT << 0)         /**< Shifted mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_HFRCORDY                               (0x1UL << 1)                                /**< HFRCO Ready */
#define _CMU_STATUS_HFRCORDY_SHIFT                        1                                           /**< Shift value for CMU_HFRCORDY */
#define _CMU_STATUS_HFRCORDY_MASK                         0x2UL                                       /**< Bit mask for CMU_HFRCORDY */
#define _CMU_STATUS_HFRCORDY_DEFAULT                      0x00000001UL                                /**< Mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_HFRCORDY_DEFAULT                       (_CMU_STATUS_HFRCORDY_DEFAULT << 1)         /**< Shifted mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_HFXOENS                                (0x1UL << 2)                                /**< HFXO Enable Status */
#define _CMU_STATUS_HFXOENS_SHIFT                         2                                           /**< Shift value for CMU_HFXOENS */
#define _CMU_STATUS_HFXOENS_MASK                          0x4UL                                       /**< Bit mask for CMU_HFXOENS */
#define _CMU_STATUS_HFXOENS_DEFAULT                       0x00000000UL                                /**< Mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_HFXOENS_DEFAULT                        (_CMU_STATUS_HFXOENS_DEFAULT << 2)          /**< Shifted mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_HFXORDY                                (0x1UL << 3)                                /**< HFXO Ready */
#define _CMU_STATUS_HFXORDY_SHIFT                         3                                           /**< Shift value for CMU_HFXORDY */
#define _CMU_STATUS_HFXORDY_MASK                          0x8UL                                       /**< Bit mask for CMU_HFXORDY */
#define _CMU_STATUS_HFXORDY_DEFAULT                       0x00000000UL                                /**< Mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_HFXORDY_DEFAULT                        (_CMU_STATUS_HFXORDY_DEFAULT << 3)          /**< Shifted mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_AUXHFRCOENS                            (0x1UL << 4)                                /**< AUXHFRCO Enable Status */
#define _CMU_STATUS_AUXHFRCOENS_SHIFT                     4                                           /**< Shift value for CMU_AUXHFRCOENS */
#define _CMU_STATUS_AUXHFRCOENS_MASK                      0x10UL                                      /**< Bit mask for CMU_AUXHFRCOENS */
#define _CMU_STATUS_AUXHFRCOENS_DEFAULT                   0x00000000UL                                /**< Mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_AUXHFRCOENS_DEFAULT                    (_CMU_STATUS_AUXHFRCOENS_DEFAULT << 4)      /**< Shifted mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_AUXHFRCORDY                            (0x1UL << 5)                                /**< AUXHFRCO Ready */
#define _CMU_STATUS_AUXHFRCORDY_SHIFT                     5                                           /**< Shift value for CMU_AUXHFRCORDY */
#define _CMU_STATUS_AUXHFRCORDY_MASK                      0x20UL                                      /**< Bit mask for CMU_AUXHFRCORDY */
#define _CMU_STATUS_AUXHFRCORDY_DEFAULT                   0x00000000UL                                /**< Mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_AUXHFRCORDY_DEFAULT                    (_CMU_STATUS_AUXHFRCORDY_DEFAULT << 5)      /**< Shifted mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_LFRCOENS                               (0x1UL << 6)                                /**< LFRCO Enable Status */
#define _CMU_STATUS_LFRCOENS_SHIFT                        6                                           /**< Shift value for CMU_LFRCOENS */
#define _CMU_STATUS_LFRCOENS_MASK                         0x40UL                                      /**< Bit mask for CMU_LFRCOENS */
#define _CMU_STATUS_LFRCOENS_DEFAULT                      0x00000000UL                                /**< Mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_LFRCOENS_DEFAULT                       (_CMU_STATUS_LFRCOENS_DEFAULT << 6)         /**< Shifted mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_LFRCORDY                               (0x1UL << 7)                                /**< LFRCO Ready */
#define _CMU_STATUS_LFRCORDY_SHIFT                        7                                           /**< Shift value for CMU_LFRCORDY */
#define _CMU_STATUS_LFRCORDY_MASK                         0x80UL                                      /**< Bit mask for CMU_LFRCORDY */
#define _CMU_STATUS_LFRCORDY_DEFAULT                      0x00000000UL                                /**< Mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_LFRCORDY_DEFAULT                       (_CMU_STATUS_LFRCORDY_DEFAULT << 7)         /**< Shifted mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_LFXOENS                                (0x1UL << 8)                                /**< LFXO Enable Status */
#define _CMU_STATUS_LFXOENS_SHIFT                         8                                           /**< Shift value for CMU_LFXOENS */
#define _CMU_STATUS_LFXOENS_MASK                          0x100UL                                     /**< Bit mask for CMU_LFXOENS */
#define _CMU_STATUS_LFXOENS_DEFAULT                       0x00000000UL                                /**< Mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_LFXOENS_DEFAULT                        (_CMU_STATUS_LFXOENS_DEFAULT << 8)          /**< Shifted mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_LFXORDY                                (0x1UL << 9)                                /**< LFXO Ready */
#define _CMU_STATUS_LFXORDY_SHIFT                         9                                           /**< Shift value for CMU_LFXORDY */
#define _CMU_STATUS_LFXORDY_MASK                          0x200UL                                     /**< Bit mask for CMU_LFXORDY */
#define _CMU_STATUS_LFXORDY_DEFAULT                       0x00000000UL                                /**< Mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_LFXORDY_DEFAULT                        (_CMU_STATUS_LFXORDY_DEFAULT << 9)          /**< Shifted mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_DPLLENS                                (0x1UL << 12)                               /**< DPLL Enable Status */
#define _CMU_STATUS_DPLLENS_SHIFT                         12                                          /**< Shift value for CMU_DPLLENS */
#define _CMU_STATUS_DPLLENS_MASK                          0x1000UL                                    /**< Bit mask for CMU_DPLLENS */
#define _CMU_STATUS_DPLLENS_DEFAULT                       0x00000000UL                                /**< Mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_DPLLENS_DEFAULT                        (_CMU_STATUS_DPLLENS_DEFAULT << 12)         /**< Shifted mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_DPLLRDY                                (0x1UL << 13)                               /**< DPLL Ready */
#define _CMU_STATUS_DPLLRDY_SHIFT                         13                                          /**< Shift value for CMU_DPLLRDY */
#define _CMU_STATUS_DPLLRDY_MASK                          0x2000UL                                    /**< Bit mask for CMU_DPLLRDY */
#define _CMU_STATUS_DPLLRDY_DEFAULT                       0x00000000UL                                /**< Mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_DPLLRDY_DEFAULT                        (_CMU_STATUS_DPLLRDY_DEFAULT << 13)         /**< Shifted mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_CALRDY                                 (0x1UL << 16)                               /**< Calibration Ready */
#define _CMU_STATUS_CALRDY_SHIFT                          16                                          /**< Shift value for CMU_CALRDY */
#define _CMU_STATUS_CALRDY_MASK                           0x10000UL                                   /**< Bit mask for CMU_CALRDY */
#define _CMU_STATUS_CALRDY_DEFAULT                        0x00000001UL                                /**< Mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_CALRDY_DEFAULT                         (_CMU_STATUS_CALRDY_DEFAULT << 16)          /**< Shifted mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_HFXOREQ                                (0x1UL << 21)                               /**< HFXO is Required By Hardware */
#define _CMU_STATUS_HFXOREQ_SHIFT                         21                                          /**< Shift value for CMU_HFXOREQ */
#define _CMU_STATUS_HFXOREQ_MASK                          0x200000UL                                  /**< Bit mask for CMU_HFXOREQ */
#define _CMU_STATUS_HFXOREQ_DEFAULT                       0x00000000UL                                /**< Mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_HFXOREQ_DEFAULT                        (_CMU_STATUS_HFXOREQ_DEFAULT << 21)         /**< Shifted mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_HFXOPEAKDETRDY                         (0x1UL << 22)                               /**< HFXO Peak Detection Ready */
#define _CMU_STATUS_HFXOPEAKDETRDY_SHIFT                  22                                          /**< Shift value for CMU_HFXOPEAKDETRDY */
#define _CMU_STATUS_HFXOPEAKDETRDY_MASK                   0x400000UL                                  /**< Bit mask for CMU_HFXOPEAKDETRDY */
#define _CMU_STATUS_HFXOPEAKDETRDY_DEFAULT                0x00000000UL                                /**< Mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_HFXOPEAKDETRDY_DEFAULT                 (_CMU_STATUS_HFXOPEAKDETRDY_DEFAULT << 22)  /**< Shifted mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_HFXOSHUNTOPTRDY                        (0x1UL << 23)                               /**< HFXO Shunt Current Optimization Ready */
#define _CMU_STATUS_HFXOSHUNTOPTRDY_SHIFT                 23                                          /**< Shift value for CMU_HFXOSHUNTOPTRDY */
#define _CMU_STATUS_HFXOSHUNTOPTRDY_MASK                  0x800000UL                                  /**< Bit mask for CMU_HFXOSHUNTOPTRDY */
#define _CMU_STATUS_HFXOSHUNTOPTRDY_DEFAULT               0x00000000UL                                /**< Mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_HFXOSHUNTOPTRDY_DEFAULT                (_CMU_STATUS_HFXOSHUNTOPTRDY_DEFAULT << 23) /**< Shifted mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_HFXOAMPHIGH                            (0x1UL << 24)                               /**< HFXO Oscillation Amplitude is Too High */
#define _CMU_STATUS_HFXOAMPHIGH_SHIFT                     24                                          /**< Shift value for CMU_HFXOAMPHIGH */
#define _CMU_STATUS_HFXOAMPHIGH_MASK                      0x1000000UL                                 /**< Bit mask for CMU_HFXOAMPHIGH */
#define _CMU_STATUS_HFXOAMPHIGH_DEFAULT                   0x00000000UL                                /**< Mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_HFXOAMPHIGH_DEFAULT                    (_CMU_STATUS_HFXOAMPHIGH_DEFAULT << 24)     /**< Shifted mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_HFXOAMPLOW                             (0x1UL << 25)                               /**< HFXO Amplitude Tuning Value Too Low */
#define _CMU_STATUS_HFXOAMPLOW_SHIFT                      25                                          /**< Shift value for CMU_HFXOAMPLOW */
#define _CMU_STATUS_HFXOAMPLOW_MASK                       0x2000000UL                                 /**< Bit mask for CMU_HFXOAMPLOW */
#define _CMU_STATUS_HFXOAMPLOW_DEFAULT                    0x00000000UL                                /**< Mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_HFXOAMPLOW_DEFAULT                     (_CMU_STATUS_HFXOAMPLOW_DEFAULT << 25)      /**< Shifted mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_HFXOREGILOW                            (0x1UL << 26)                               /**< HFXO Regulator Shunt Current Too Low */
#define _CMU_STATUS_HFXOREGILOW_SHIFT                     26                                          /**< Shift value for CMU_HFXOREGILOW */
#define _CMU_STATUS_HFXOREGILOW_MASK                      0x4000000UL                                 /**< Bit mask for CMU_HFXOREGILOW */
#define _CMU_STATUS_HFXOREGILOW_DEFAULT                   0x00000000UL                                /**< Mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_HFXOREGILOW_DEFAULT                    (_CMU_STATUS_HFXOREGILOW_DEFAULT << 26)     /**< Shifted mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_LFXOPHASE                              (0x1UL << 27)                               /**< LFXO Clock Phase */
#define _CMU_STATUS_LFXOPHASE_SHIFT                       27                                          /**< Shift value for CMU_LFXOPHASE */
#define _CMU_STATUS_LFXOPHASE_MASK                        0x8000000UL                                 /**< Bit mask for CMU_LFXOPHASE */
#define _CMU_STATUS_LFXOPHASE_DEFAULT                     0x00000000UL                                /**< Mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_LFXOPHASE_DEFAULT                      (_CMU_STATUS_LFXOPHASE_DEFAULT << 27)       /**< Shifted mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_LFRCOPHASE                             (0x1UL << 28)                               /**< LFRCO Clock Phase */
#define _CMU_STATUS_LFRCOPHASE_SHIFT                      28                                          /**< Shift value for CMU_LFRCOPHASE */
#define _CMU_STATUS_LFRCOPHASE_MASK                       0x10000000UL                                /**< Bit mask for CMU_LFRCOPHASE */
#define _CMU_STATUS_LFRCOPHASE_DEFAULT                    0x00000000UL                                /**< Mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_LFRCOPHASE_DEFAULT                     (_CMU_STATUS_LFRCOPHASE_DEFAULT << 28)      /**< Shifted mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_ULFRCOPHASE                            (0x1UL << 29)                               /**< ULFRCO Clock Phase */
#define _CMU_STATUS_ULFRCOPHASE_SHIFT                     29                                          /**< Shift value for CMU_ULFRCOPHASE */
#define _CMU_STATUS_ULFRCOPHASE_MASK                      0x20000000UL                                /**< Bit mask for CMU_ULFRCOPHASE */
#define _CMU_STATUS_ULFRCOPHASE_DEFAULT                   0x00000000UL                                /**< Mode DEFAULT for CMU_STATUS */
#define CMU_STATUS_ULFRCOPHASE_DEFAULT                    (_CMU_STATUS_ULFRCOPHASE_DEFAULT << 29)     /**< Shifted mode DEFAULT for CMU_STATUS */

/* Bit fields for CMU HFCLKSTATUS */
#define _CMU_HFCLKSTATUS_RESETVALUE                       0x00000001UL                               /**< Default value for CMU_HFCLKSTATUS */
#define _CMU_HFCLKSTATUS_MASK                             0x00000007UL                               /**< Mask for CMU_HFCLKSTATUS */
#define _CMU_HFCLKSTATUS_SELECTED_SHIFT                   0                                          /**< Shift value for CMU_SELECTED */
#define _CMU_HFCLKSTATUS_SELECTED_MASK                    0x7UL                                      /**< Bit mask for CMU_SELECTED */
#define _CMU_HFCLKSTATUS_SELECTED_DEFAULT                 0x00000001UL                               /**< Mode DEFAULT for CMU_HFCLKSTATUS */
#define _CMU_HFCLKSTATUS_SELECTED_HFRCO                   0x00000001UL                               /**< Mode HFRCO for CMU_HFCLKSTATUS */
#define _CMU_HFCLKSTATUS_SELECTED_HFXO                    0x00000002UL                               /**< Mode HFXO for CMU_HFCLKSTATUS */
#define _CMU_HFCLKSTATUS_SELECTED_LFRCO                   0x00000003UL                               /**< Mode LFRCO for CMU_HFCLKSTATUS */
#define _CMU_HFCLKSTATUS_SELECTED_LFXO                    0x00000004UL                               /**< Mode LFXO for CMU_HFCLKSTATUS */
#define _CMU_HFCLKSTATUS_SELECTED_HFRCODIV2               0x00000005UL                               /**< Mode HFRCODIV2 for CMU_HFCLKSTATUS */
#define _CMU_HFCLKSTATUS_SELECTED_CLKIN0                  0x00000007UL                               /**< Mode CLKIN0 for CMU_HFCLKSTATUS */
#define CMU_HFCLKSTATUS_SELECTED_DEFAULT                  (_CMU_HFCLKSTATUS_SELECTED_DEFAULT << 0)   /**< Shifted mode DEFAULT for CMU_HFCLKSTATUS */
#define CMU_HFCLKSTATUS_SELECTED_HFRCO                    (_CMU_HFCLKSTATUS_SELECTED_HFRCO << 0)     /**< Shifted mode HFRCO for CMU_HFCLKSTATUS */
#define CMU_HFCLKSTATUS_SELECTED_HFXO                     (_CMU_HFCLKSTATUS_SELECTED_HFXO << 0)      /**< Shifted mode HFXO for CMU_HFCLKSTATUS */
#define CMU_HFCLKSTATUS_SELECTED_LFRCO                    (_CMU_HFCLKSTATUS_SELECTED_LFRCO << 0)     /**< Shifted mode LFRCO for CMU_HFCLKSTATUS */
#define CMU_HFCLKSTATUS_SELECTED_LFXO                     (_CMU_HFCLKSTATUS_SELECTED_LFXO << 0)      /**< Shifted mode LFXO for CMU_HFCLKSTATUS */
#define CMU_HFCLKSTATUS_SELECTED_HFRCODIV2                (_CMU_HFCLKSTATUS_SELECTED_HFRCODIV2 << 0) /**< Shifted mode HFRCODIV2 for CMU_HFCLKSTATUS */
#define CMU_HFCLKSTATUS_SELECTED_CLKIN0                   (_CMU_HFCLKSTATUS_SELECTED_CLKIN0 << 0)    /**< Shifted mode CLKIN0 for CMU_HFCLKSTATUS */

/* Bit fields for CMU HFXOTRIMSTATUS */
#define _CMU_HFXOTRIMSTATUS_RESETVALUE                    0x00000500UL                                    /**< Default value for CMU_HFXOTRIMSTATUS */
#define _CMU_HFXOTRIMSTATUS_MASK                          0x000007FFUL                                    /**< Mask for CMU_HFXOTRIMSTATUS */
#define _CMU_HFXOTRIMSTATUS_IBTRIMXOCORE_SHIFT            0                                               /**< Shift value for CMU_IBTRIMXOCORE */
#define _CMU_HFXOTRIMSTATUS_IBTRIMXOCORE_MASK             0x7FUL                                          /**< Bit mask for CMU_IBTRIMXOCORE */
#define _CMU_HFXOTRIMSTATUS_IBTRIMXOCORE_DEFAULT          0x00000000UL                                    /**< Mode DEFAULT for CMU_HFXOTRIMSTATUS */
#define CMU_HFXOTRIMSTATUS_IBTRIMXOCORE_DEFAULT           (_CMU_HFXOTRIMSTATUS_IBTRIMXOCORE_DEFAULT << 0) /**< Shifted mode DEFAULT for CMU_HFXOTRIMSTATUS */
#define _CMU_HFXOTRIMSTATUS_REGISH_SHIFT                  7                                               /**< Shift value for CMU_REGISH */
#define _CMU_HFXOTRIMSTATUS_REGISH_MASK                   0x780UL                                         /**< Bit mask for CMU_REGISH */
#define _CMU_HFXOTRIMSTATUS_REGISH_DEFAULT                0x0000000AUL                                    /**< Mode DEFAULT for CMU_HFXOTRIMSTATUS */
#define CMU_HFXOTRIMSTATUS_REGISH_DEFAULT                 (_CMU_HFXOTRIMSTATUS_REGISH_DEFAULT << 7)       /**< Shifted mode DEFAULT for CMU_HFXOTRIMSTATUS */

/* Bit fields for CMU IF */
#define _CMU_IF_RESETVALUE                                0x00000001UL                             /**< Default value for CMU_IF */
#define _CMU_IF_MASK                                      0xB803FF7FUL                             /**< Mask for CMU_IF */
#define CMU_IF_HFRCORDY                                   (0x1UL << 0)                             /**< HFRCO Ready Interrupt Flag */
#define _CMU_IF_HFRCORDY_SHIFT                            0                                        /**< Shift value for CMU_HFRCORDY */
#define _CMU_IF_HFRCORDY_MASK                             0x1UL                                    /**< Bit mask for CMU_HFRCORDY */
#define _CMU_IF_HFRCORDY_DEFAULT                          0x00000001UL                             /**< Mode DEFAULT for CMU_IF */
#define CMU_IF_HFRCORDY_DEFAULT                           (_CMU_IF_HFRCORDY_DEFAULT << 0)          /**< Shifted mode DEFAULT for CMU_IF */
#define CMU_IF_HFXORDY                                    (0x1UL << 1)                             /**< HFXO Ready Interrupt Flag */
#define _CMU_IF_HFXORDY_SHIFT                             1                                        /**< Shift value for CMU_HFXORDY */
#define _CMU_IF_HFXORDY_MASK                              0x2UL                                    /**< Bit mask for CMU_HFXORDY */
#define _CMU_IF_HFXORDY_DEFAULT                           0x00000000UL                             /**< Mode DEFAULT for CMU_IF */
#define CMU_IF_HFXORDY_DEFAULT                            (_CMU_IF_HFXORDY_DEFAULT << 1)           /**< Shifted mode DEFAULT for CMU_IF */
#define CMU_IF_LFRCORDY                                   (0x1UL << 2)                             /**< LFRCO Ready Interrupt Flag */
#define _CMU_IF_LFRCORDY_SHIFT                            2                                        /**< Shift value for CMU_LFRCORDY */
#define _CMU_IF_LFRCORDY_MASK                             0x4UL                                    /**< Bit mask for CMU_LFRCORDY */
#define _CMU_IF_LFRCORDY_DEFAULT                          0x00000000UL                             /**< Mode DEFAULT for CMU_IF */
#define CMU_IF_LFRCORDY_DEFAULT                           (_CMU_IF_LFRCORDY_DEFAULT << 2)          /**< Shifted mode DEFAULT for CMU_IF */
#define CMU_IF_LFXORDY                                    (0x1UL << 3)                             /**< LFXO Ready Interrupt Flag */
#define _CMU_IF_LFXORDY_SHIFT                             3                                        /**< Shift value for CMU_LFXORDY */
#define _CMU_IF_LFXORDY_MASK                              0x8UL                                    /**< Bit mask for CMU_LFXORDY */
#define _CMU_IF_LFXORDY_DEFAULT                           0x00000000UL                             /**< Mode DEFAULT for CMU_IF */
#define CMU_IF_LFXORDY_DEFAULT                            (_CMU_IF_LFXORDY_DEFAULT << 3)           /**< Shifted mode DEFAULT for CMU_IF */
#define CMU_IF_AUXHFRCORDY                                (0x1UL << 4)                             /**< AUXHFRCO Ready Interrupt Flag */
#define _CMU_IF_AUXHFRCORDY_SHIFT                         4                                        /**< Shift value for CMU_AUXHFRCORDY */
#define _CMU_IF_AUXHFRCORDY_MASK                          0x10UL                                   /**< Bit mask for CMU_AUXHFRCORDY */
#define _CMU_IF_AUXHFRCORDY_DEFAULT                       0x00000000UL                             /**< Mode DEFAULT for CMU_IF */
#define CMU_IF_AUXHFRCORDY_DEFAULT                        (_CMU_IF_AUXHFRCORDY_DEFAULT << 4)       /**< Shifted mode DEFAULT for CMU_IF */
#define CMU_IF_CALRDY                                     (0x1UL << 5)                             /**< Calibration Ready Interrupt Flag */
#define _CMU_IF_CALRDY_SHIFT                              5                                        /**< Shift value for CMU_CALRDY */
#define _CMU_IF_CALRDY_MASK                               0x20UL                                   /**< Bit mask for CMU_CALRDY */
#define _CMU_IF_CALRDY_DEFAULT                            0x00000000UL                             /**< Mode DEFAULT for CMU_IF */
#define CMU_IF_CALRDY_DEFAULT                             (_CMU_IF_CALRDY_DEFAULT << 5)            /**< Shifted mode DEFAULT for CMU_IF */
#define CMU_IF_CALOF                                      (0x1UL << 6)                             /**< Calibration Overflow Interrupt Flag */
#define _CMU_IF_CALOF_SHIFT                               6                                        /**< Shift value for CMU_CALOF */
#define _CMU_IF_CALOF_MASK                                0x40UL                                   /**< Bit mask for CMU_CALOF */
#define _CMU_IF_CALOF_DEFAULT                             0x00000000UL                             /**< Mode DEFAULT for CMU_IF */
#define CMU_IF_CALOF_DEFAULT                              (_CMU_IF_CALOF_DEFAULT << 6)             /**< Shifted mode DEFAULT for CMU_IF */
#define CMU_IF_HFXODISERR                                 (0x1UL << 8)                             /**< HFXO Disable Error Interrupt Flag */
#define _CMU_IF_HFXODISERR_SHIFT                          8                                        /**< Shift value for CMU_HFXODISERR */
#define _CMU_IF_HFXODISERR_MASK                           0x100UL                                  /**< Bit mask for CMU_HFXODISERR */
#define _CMU_IF_HFXODISERR_DEFAULT                        0x00000000UL                             /**< Mode DEFAULT for CMU_IF */
#define CMU_IF_HFXODISERR_DEFAULT                         (_CMU_IF_HFXODISERR_DEFAULT << 8)        /**< Shifted mode DEFAULT for CMU_IF */
#define CMU_IF_HFXOAUTOSW                                 (0x1UL << 9)                             /**< HFXO Automatic Switch Interrupt Flag */
#define _CMU_IF_HFXOAUTOSW_SHIFT                          9                                        /**< Shift value for CMU_HFXOAUTOSW */
#define _CMU_IF_HFXOAUTOSW_MASK                           0x200UL                                  /**< Bit mask for CMU_HFXOAUTOSW */
#define _CMU_IF_HFXOAUTOSW_DEFAULT                        0x00000000UL                             /**< Mode DEFAULT for CMU_IF */
#define CMU_IF_HFXOAUTOSW_DEFAULT                         (_CMU_IF_HFXOAUTOSW_DEFAULT << 9)        /**< Shifted mode DEFAULT for CMU_IF */
#define CMU_IF_HFXOPEAKDETERR                             (0x1UL << 10)                            /**< HFXO Automatic Peak Detection Error Interrupt Flag */
#define _CMU_IF_HFXOPEAKDETERR_SHIFT                      10                                       /**< Shift value for CMU_HFXOPEAKDETERR */
#define _CMU_IF_HFXOPEAKDETERR_MASK                       0x400UL                                  /**< Bit mask for CMU_HFXOPEAKDETERR */
#define _CMU_IF_HFXOPEAKDETERR_DEFAULT                    0x00000000UL                             /**< Mode DEFAULT for CMU_IF */
#define CMU_IF_HFXOPEAKDETERR_DEFAULT                     (_CMU_IF_HFXOPEAKDETERR_DEFAULT << 10)   /**< Shifted mode DEFAULT for CMU_IF */
#define CMU_IF_HFXOPEAKDETRDY                             (0x1UL << 11)                            /**< HFXO Automatic Peak Detection Ready Interrupt Flag */
#define _CMU_IF_HFXOPEAKDETRDY_SHIFT                      11                                       /**< Shift value for CMU_HFXOPEAKDETRDY */
#define _CMU_IF_HFXOPEAKDETRDY_MASK                       0x800UL                                  /**< Bit mask for CMU_HFXOPEAKDETRDY */
#define _CMU_IF_HFXOPEAKDETRDY_DEFAULT                    0x00000000UL                             /**< Mode DEFAULT for CMU_IF */
#define CMU_IF_HFXOPEAKDETRDY_DEFAULT                     (_CMU_IF_HFXOPEAKDETRDY_DEFAULT << 11)   /**< Shifted mode DEFAULT for CMU_IF */
#define CMU_IF_HFXOSHUNTOPTRDY                            (0x1UL << 12)                            /**< HFXO Automatic Shunt Current Optimization Ready Interrupt Flag */
#define _CMU_IF_HFXOSHUNTOPTRDY_SHIFT                     12                                       /**< Shift value for CMU_HFXOSHUNTOPTRDY */
#define _CMU_IF_HFXOSHUNTOPTRDY_MASK                      0x1000UL                                 /**< Bit mask for CMU_HFXOSHUNTOPTRDY */
#define _CMU_IF_HFXOSHUNTOPTRDY_DEFAULT                   0x00000000UL                             /**< Mode DEFAULT for CMU_IF */
#define CMU_IF_HFXOSHUNTOPTRDY_DEFAULT                    (_CMU_IF_HFXOSHUNTOPTRDY_DEFAULT << 12)  /**< Shifted mode DEFAULT for CMU_IF */
#define CMU_IF_HFRCODIS                                   (0x1UL << 13)                            /**< HFRCO Disable Interrupt Flag */
#define _CMU_IF_HFRCODIS_SHIFT                            13                                       /**< Shift value for CMU_HFRCODIS */
#define _CMU_IF_HFRCODIS_MASK                             0x2000UL                                 /**< Bit mask for CMU_HFRCODIS */
#define _CMU_IF_HFRCODIS_DEFAULT                          0x00000000UL                             /**< Mode DEFAULT for CMU_IF */
#define CMU_IF_HFRCODIS_DEFAULT                           (_CMU_IF_HFRCODIS_DEFAULT << 13)         /**< Shifted mode DEFAULT for CMU_IF */
#define CMU_IF_LFTIMEOUTERR                               (0x1UL << 14)                            /**< Low Frequency Timeout Error Interrupt Flag */
#define _CMU_IF_LFTIMEOUTERR_SHIFT                        14                                       /**< Shift value for CMU_LFTIMEOUTERR */
#define _CMU_IF_LFTIMEOUTERR_MASK                         0x4000UL                                 /**< Bit mask for CMU_LFTIMEOUTERR */
#define _CMU_IF_LFTIMEOUTERR_DEFAULT                      0x00000000UL                             /**< Mode DEFAULT for CMU_IF */
#define CMU_IF_LFTIMEOUTERR_DEFAULT                       (_CMU_IF_LFTIMEOUTERR_DEFAULT << 14)     /**< Shifted mode DEFAULT for CMU_IF */
#define CMU_IF_DPLLRDY                                    (0x1UL << 15)                            /**< DPLL Lock Interrupt Flag */
#define _CMU_IF_DPLLRDY_SHIFT                             15                                       /**< Shift value for CMU_DPLLRDY */
#define _CMU_IF_DPLLRDY_MASK                              0x8000UL                                 /**< Bit mask for CMU_DPLLRDY */
#define _CMU_IF_DPLLRDY_DEFAULT                           0x00000000UL                             /**< Mode DEFAULT for CMU_IF */
#define CMU_IF_DPLLRDY_DEFAULT                            (_CMU_IF_DPLLRDY_DEFAULT << 15)          /**< Shifted mode DEFAULT for CMU_IF */
#define CMU_IF_DPLLLOCKFAILLOW                            (0x1UL << 16)                            /**< DPLL Lock Failure Low Interrupt Flag */
#define _CMU_IF_DPLLLOCKFAILLOW_SHIFT                     16                                       /**< Shift value for CMU_DPLLLOCKFAILLOW */
#define _CMU_IF_DPLLLOCKFAILLOW_MASK                      0x10000UL                                /**< Bit mask for CMU_DPLLLOCKFAILLOW */
#define _CMU_IF_DPLLLOCKFAILLOW_DEFAULT                   0x00000000UL                             /**< Mode DEFAULT for CMU_IF */
#define CMU_IF_DPLLLOCKFAILLOW_DEFAULT                    (_CMU_IF_DPLLLOCKFAILLOW_DEFAULT << 16)  /**< Shifted mode DEFAULT for CMU_IF */
#define CMU_IF_DPLLLOCKFAILHIGH                           (0x1UL << 17)                            /**< DPLL Lock Failure Low Interrupt Flag */
#define _CMU_IF_DPLLLOCKFAILHIGH_SHIFT                    17                                       /**< Shift value for CMU_DPLLLOCKFAILHIGH */
#define _CMU_IF_DPLLLOCKFAILHIGH_MASK                     0x20000UL                                /**< Bit mask for CMU_DPLLLOCKFAILHIGH */
#define _CMU_IF_DPLLLOCKFAILHIGH_DEFAULT                  0x00000000UL                             /**< Mode DEFAULT for CMU_IF */
#define CMU_IF_DPLLLOCKFAILHIGH_DEFAULT                   (_CMU_IF_DPLLLOCKFAILHIGH_DEFAULT << 17) /**< Shifted mode DEFAULT for CMU_IF */
#define CMU_IF_LFXOEDGE                                   (0x1UL << 27)                            /**< LFXO Clock Edge Detected Interrupt Flag */
#define _CMU_IF_LFXOEDGE_SHIFT                            27                                       /**< Shift value for CMU_LFXOEDGE */
#define _CMU_IF_LFXOEDGE_MASK                             0x8000000UL                              /**< Bit mask for CMU_LFXOEDGE */
#define _CMU_IF_LFXOEDGE_DEFAULT                          0x00000000UL                             /**< Mode DEFAULT for CMU_IF */
#define CMU_IF_LFXOEDGE_DEFAULT                           (_CMU_IF_LFXOEDGE_DEFAULT << 27)         /**< Shifted mode DEFAULT for CMU_IF */
#define CMU_IF_LFRCOEDGE                                  (0x1UL << 28)                            /**< LFRCO Clock Edge Detected Interrupt Flag */
#define _CMU_IF_LFRCOEDGE_SHIFT                           28                                       /**< Shift value for CMU_LFRCOEDGE */
#define _CMU_IF_LFRCOEDGE_MASK                            0x10000000UL                             /**< Bit mask for CMU_LFRCOEDGE */
#define _CMU_IF_LFRCOEDGE_DEFAULT                         0x00000000UL                             /**< Mode DEFAULT for CMU_IF */
#define CMU_IF_LFRCOEDGE_DEFAULT                          (_CMU_IF_LFRCOEDGE_DEFAULT << 28)        /**< Shifted mode DEFAULT for CMU_IF */
#define CMU_IF_ULFRCOEDGE                                 (0x1UL << 29)                            /**< ULFRCO Clock Edge Detected Interrupt Flag */
#define _CMU_IF_ULFRCOEDGE_SHIFT                          29                                       /**< Shift value for CMU_ULFRCOEDGE */
#define _CMU_IF_ULFRCOEDGE_MASK                           0x20000000UL                             /**< Bit mask for CMU_ULFRCOEDGE */
#define _CMU_IF_ULFRCOEDGE_DEFAULT                        0x00000000UL                             /**< Mode DEFAULT for CMU_IF */
#define CMU_IF_ULFRCOEDGE_DEFAULT                         (_CMU_IF_ULFRCOEDGE_DEFAULT << 29)       /**< Shifted mode DEFAULT for CMU_IF */
#define CMU_IF_CMUERR                                     (0x1UL << 31)                            /**< CMU Error Interrupt Flag */
#define _CMU_IF_CMUERR_SHIFT                              31                                       /**< Shift value for CMU_CMUERR */
#define _CMU_IF_CMUERR_MASK                               0x80000000UL                             /**< Bit mask for CMU_CMUERR */
#define _CMU_IF_CMUERR_DEFAULT                            0x00000000UL                             /**< Mode DEFAULT for CMU_IF */
#define CMU_IF_CMUERR_DEFAULT                             (_CMU_IF_CMUERR_DEFAULT << 31)           /**< Shifted mode DEFAULT for CMU_IF */

/* Bit fields for CMU IFS */
#define _CMU_IFS_RESETVALUE                               0x00000000UL                              /**< Default value for CMU_IFS */
#define _CMU_IFS_MASK                                     0xB803FF7FUL                              /**< Mask for CMU_IFS */
#define CMU_IFS_HFRCORDY                                  (0x1UL << 0)                              /**< Set HFRCORDY Interrupt Flag */
#define _CMU_IFS_HFRCORDY_SHIFT                           0                                         /**< Shift value for CMU_HFRCORDY */
#define _CMU_IFS_HFRCORDY_MASK                            0x1UL                                     /**< Bit mask for CMU_HFRCORDY */
#define _CMU_IFS_HFRCORDY_DEFAULT                         0x00000000UL                              /**< Mode DEFAULT for CMU_IFS */
#define CMU_IFS_HFRCORDY_DEFAULT                          (_CMU_IFS_HFRCORDY_DEFAULT << 0)          /**< Shifted mode DEFAULT for CMU_IFS */
#define CMU_IFS_HFXORDY                                   (0x1UL << 1)                              /**< Set HFXORDY Interrupt Flag */
#define _CMU_IFS_HFXORDY_SHIFT                            1                                         /**< Shift value for CMU_HFXORDY */
#define _CMU_IFS_HFXORDY_MASK                             0x2UL                                     /**< Bit mask for CMU_HFXORDY */
#define _CMU_IFS_HFXORDY_DEFAULT                          0x00000000UL                              /**< Mode DEFAULT for CMU_IFS */
#define CMU_IFS_HFXORDY_DEFAULT                           (_CMU_IFS_HFXORDY_DEFAULT << 1)           /**< Shifted mode DEFAULT for CMU_IFS */
#define CMU_IFS_LFRCORDY                                  (0x1UL << 2)                              /**< Set LFRCORDY Interrupt Flag */
#define _CMU_IFS_LFRCORDY_SHIFT                           2                                         /**< Shift value for CMU_LFRCORDY */
#define _CMU_IFS_LFRCORDY_MASK                            0x4UL                                     /**< Bit mask for CMU_LFRCORDY */
#define _CMU_IFS_LFRCORDY_DEFAULT                         0x00000000UL                              /**< Mode DEFAULT for CMU_IFS */
#define CMU_IFS_LFRCORDY_DEFAULT                          (_CMU_IFS_LFRCORDY_DEFAULT << 2)          /**< Shifted mode DEFAULT for CMU_IFS */
#define CMU_IFS_LFXORDY                                   (0x1UL << 3)                              /**< Set LFXORDY Interrupt Flag */
#define _CMU_IFS_LFXORDY_SHIFT                            3                                         /**< Shift value for CMU_LFXORDY */
#define _CMU_IFS_LFXORDY_MASK                             0x8UL                                     /**< Bit mask for CMU_LFXORDY */
#define _CMU_IFS_LFXORDY_DEFAULT                          0x00000000UL                              /**< Mode DEFAULT for CMU_IFS */
#define CMU_IFS_LFXORDY_DEFAULT                           (_CMU_IFS_LFXORDY_DEFAULT << 3)           /**< Shifted mode DEFAULT for CMU_IFS */
#define CMU_IFS_AUXHFRCORDY                               (0x1UL << 4)                              /**< Set AUXHFRCORDY Interrupt Flag */
#define _CMU_IFS_AUXHFRCORDY_SHIFT                        4                                         /**< Shift value for CMU_AUXHFRCORDY */
#define _CMU_IFS_AUXHFRCORDY_MASK                         0x10UL                                    /**< Bit mask for CMU_AUXHFRCORDY */
#define _CMU_IFS_AUXHFRCORDY_DEFAULT                      0x00000000UL                              /**< Mode DEFAULT for CMU_IFS */
#define CMU_IFS_AUXHFRCORDY_DEFAULT                       (_CMU_IFS_AUXHFRCORDY_DEFAULT << 4)       /**< Shifted mode DEFAULT for CMU_IFS */
#define CMU_IFS_CALRDY                                    (0x1UL << 5)                              /**< Set CALRDY Interrupt Flag */
#define _CMU_IFS_CALRDY_SHIFT                             5                                         /**< Shift value for CMU_CALRDY */
#define _CMU_IFS_CALRDY_MASK                              0x20UL                                    /**< Bit mask for CMU_CALRDY */
#define _CMU_IFS_CALRDY_DEFAULT                           0x00000000UL                              /**< Mode DEFAULT for CMU_IFS */
#define CMU_IFS_CALRDY_DEFAULT                            (_CMU_IFS_CALRDY_DEFAULT << 5)            /**< Shifted mode DEFAULT for CMU_IFS */
#define CMU_IFS_CALOF                                     (0x1UL << 6)                              /**< Set CALOF Interrupt Flag */
#define _CMU_IFS_CALOF_SHIFT                              6                                         /**< Shift value for CMU_CALOF */
#define _CMU_IFS_CALOF_MASK                               0x40UL                                    /**< Bit mask for CMU_CALOF */
#define _CMU_IFS_CALOF_DEFAULT                            0x00000000UL                              /**< Mode DEFAULT for CMU_IFS */
#define CMU_IFS_CALOF_DEFAULT                             (_CMU_IFS_CALOF_DEFAULT << 6)             /**< Shifted mode DEFAULT for CMU_IFS */
#define CMU_IFS_HFXODISERR                                (0x1UL << 8)                              /**< Set HFXODISERR Interrupt Flag */
#define _CMU_IFS_HFXODISERR_SHIFT                         8                                         /**< Shift value for CMU_HFXODISERR */
#define _CMU_IFS_HFXODISERR_MASK                          0x100UL                                   /**< Bit mask for CMU_HFXODISERR */
#define _CMU_IFS_HFXODISERR_DEFAULT                       0x00000000UL                              /**< Mode DEFAULT for CMU_IFS */
#define CMU_IFS_HFXODISERR_DEFAULT                        (_CMU_IFS_HFXODISERR_DEFAULT << 8)        /**< Shifted mode DEFAULT for CMU_IFS */
#define CMU_IFS_HFXOAUTOSW                                (0x1UL << 9)                              /**< Set HFXOAUTOSW Interrupt Flag */
#define _CMU_IFS_HFXOAUTOSW_SHIFT                         9                                         /**< Shift value for CMU_HFXOAUTOSW */
#define _CMU_IFS_HFXOAUTOSW_MASK                          0x200UL                                   /**< Bit mask for CMU_HFXOAUTOSW */
#define _CMU_IFS_HFXOAUTOSW_DEFAULT                       0x00000000UL                              /**< Mode DEFAULT for CMU_IFS */
#define CMU_IFS_HFXOAUTOSW_DEFAULT                        (_CMU_IFS_HFXOAUTOSW_DEFAULT << 9)        /**< Shifted mode DEFAULT for CMU_IFS */
#define CMU_IFS_HFXOPEAKDETERR                            (0x1UL << 10)                             /**< Set HFXOPEAKDETERR Interrupt Flag */
#define _CMU_IFS_HFXOPEAKDETERR_SHIFT                     10                                        /**< Shift value for CMU_HFXOPEAKDETERR */
#define _CMU_IFS_HFXOPEAKDETERR_MASK                      0x400UL                                   /**< Bit mask for CMU_HFXOPEAKDETERR */
#define _CMU_IFS_HFXOPEAKDETERR_DEFAULT                   0x00000000UL                              /**< Mode DEFAULT for CMU_IFS */
#define CMU_IFS_HFXOPEAKDETERR_DEFAULT                    (_CMU_IFS_HFXOPEAKDETERR_DEFAULT << 10)   /**< Shifted mode DEFAULT for CMU_IFS */
#define CMU_IFS_HFXOPEAKDETRDY                            (0x1UL << 11)                             /**< Set HFXOPEAKDETRDY Interrupt Flag */
#define _CMU_IFS_HFXOPEAKDETRDY_SHIFT                     11                                        /**< Shift value for CMU_HFXOPEAKDETRDY */
#define _CMU_IFS_HFXOPEAKDETRDY_MASK                      0x800UL                                   /**< Bit mask for CMU_HFXOPEAKDETRDY */
#define _CMU_IFS_HFXOPEAKDETRDY_DEFAULT                   0x00000000UL                              /**< Mode DEFAULT for CMU_IFS */
#define CMU_IFS_HFXOPEAKDETRDY_DEFAULT                    (_CMU_IFS_HFXOPEAKDETRDY_DEFAULT << 11)   /**< Shifted mode DEFAULT for CMU_IFS */
#define CMU_IFS_HFXOSHUNTOPTRDY                           (0x1UL << 12)                             /**< Set HFXOSHUNTOPTRDY Interrupt Flag */
#define _CMU_IFS_HFXOSHUNTOPTRDY_SHIFT                    12                                        /**< Shift value for CMU_HFXOSHUNTOPTRDY */
#define _CMU_IFS_HFXOSHUNTOPTRDY_MASK                     0x1000UL                                  /**< Bit mask for CMU_HFXOSHUNTOPTRDY */
#define _CMU_IFS_HFXOSHUNTOPTRDY_DEFAULT                  0x00000000UL                              /**< Mode DEFAULT for CMU_IFS */
#define CMU_IFS_HFXOSHUNTOPTRDY_DEFAULT                   (_CMU_IFS_HFXOSHUNTOPTRDY_DEFAULT << 12)  /**< Shifted mode DEFAULT for CMU_IFS */
#define CMU_IFS_HFRCODIS                                  (0x1UL << 13)                             /**< Set HFRCODIS Interrupt Flag */
#define _CMU_IFS_HFRCODIS_SHIFT                           13                                        /**< Shift value for CMU_HFRCODIS */
#define _CMU_IFS_HFRCODIS_MASK                            0x2000UL                                  /**< Bit mask for CMU_HFRCODIS */
#define _CMU_IFS_HFRCODIS_DEFAULT                         0x00000000UL                              /**< Mode DEFAULT for CMU_IFS */
#define CMU_IFS_HFRCODIS_DEFAULT                          (_CMU_IFS_HFRCODIS_DEFAULT << 13)         /**< Shifted mode DEFAULT for CMU_IFS */
#define CMU_IFS_LFTIMEOUTERR                              (0x1UL << 14)                             /**< Set LFTIMEOUTERR Interrupt Flag */
#define _CMU_IFS_LFTIMEOUTERR_SHIFT                       14                                        /**< Shift value for CMU_LFTIMEOUTERR */
#define _CMU_IFS_LFTIMEOUTERR_MASK                        0x4000UL                                  /**< Bit mask for CMU_LFTIMEOUTERR */
#define _CMU_IFS_LFTIMEOUTERR_DEFAULT                     0x00000000UL                              /**< Mode DEFAULT for CMU_IFS */
#define CMU_IFS_LFTIMEOUTERR_DEFAULT                      (_CMU_IFS_LFTIMEOUTERR_DEFAULT << 14)     /**< Shifted mode DEFAULT for CMU_IFS */
#define CMU_IFS_DPLLRDY                                   (0x1UL << 15)                             /**< Set DPLLRDY Interrupt Flag */
#define _CMU_IFS_DPLLRDY_SHIFT                            15                                        /**< Shift value for CMU_DPLLRDY */
#define _CMU_IFS_DPLLRDY_MASK                             0x8000UL                                  /**< Bit mask for CMU_DPLLRDY */
#define _CMU_IFS_DPLLRDY_DEFAULT                          0x00000000UL                              /**< Mode DEFAULT for CMU_IFS */
#define CMU_IFS_DPLLRDY_DEFAULT                           (_CMU_IFS_DPLLRDY_DEFAULT << 15)          /**< Shifted mode DEFAULT for CMU_IFS */
#define CMU_IFS_DPLLLOCKFAILLOW                           (0x1UL << 16)                             /**< Set DPLLLOCKFAILLOW Interrupt Flag */
#define _CMU_IFS_DPLLLOCKFAILLOW_SHIFT                    16                                        /**< Shift value for CMU_DPLLLOCKFAILLOW */
#define _CMU_IFS_DPLLLOCKFAILLOW_MASK                     0x10000UL                                 /**< Bit mask for CMU_DPLLLOCKFAILLOW */
#define _CMU_IFS_DPLLLOCKFAILLOW_DEFAULT                  0x00000000UL                              /**< Mode DEFAULT for CMU_IFS */
#define CMU_IFS_DPLLLOCKFAILLOW_DEFAULT                   (_CMU_IFS_DPLLLOCKFAILLOW_DEFAULT << 16)  /**< Shifted mode DEFAULT for CMU_IFS */
#define CMU_IFS_DPLLLOCKFAILHIGH                          (0x1UL << 17)                             /**< Set DPLLLOCKFAILHIGH Interrupt Flag */
#define _CMU_IFS_DPLLLOCKFAILHIGH_SHIFT                   17                                        /**< Shift value for CMU_DPLLLOCKFAILHIGH */
#define _CMU_IFS_DPLLLOCKFAILHIGH_MASK                    0x20000UL                                 /**< Bit mask for CMU_DPLLLOCKFAILHIGH */
#define _CMU_IFS_DPLLLOCKFAILHIGH_DEFAULT                 0x00000000UL                              /**< Mode DEFAULT for CMU_IFS */
#define CMU_IFS_DPLLLOCKFAILHIGH_DEFAULT                  (_CMU_IFS_DPLLLOCKFAILHIGH_DEFAULT << 17) /**< Shifted mode DEFAULT for CMU_IFS */
#define CMU_IFS_LFXOEDGE                                  (0x1UL << 27)                             /**< Set LFXOEDGE Interrupt Flag */
#define _CMU_IFS_LFXOEDGE_SHIFT                           27                                        /**< Shift value for CMU_LFXOEDGE */
#define _CMU_IFS_LFXOEDGE_MASK                            0x8000000UL                               /**< Bit mask for CMU_LFXOEDGE */
#define _CMU_IFS_LFXOEDGE_DEFAULT                         0x00000000UL                              /**< Mode DEFAULT for CMU_IFS */
#define CMU_IFS_LFXOEDGE_DEFAULT                          (_CMU_IFS_LFXOEDGE_DEFAULT << 27)         /**< Shifted mode DEFAULT for CMU_IFS */
#define CMU_IFS_LFRCOEDGE                                 (0x1UL << 28)                             /**< Set LFRCOEDGE Interrupt Flag */
#define _CMU_IFS_LFRCOEDGE_SHIFT                          28                                        /**< Shift value for CMU_LFRCOEDGE */
#define _CMU_IFS_LFRCOEDGE_MASK                           0x10000000UL                              /**< Bit mask for CMU_LFRCOEDGE */
#define _CMU_IFS_LFRCOEDGE_DEFAULT                        0x00000000UL                              /**< Mode DEFAULT for CMU_IFS */
#define CMU_IFS_LFRCOEDGE_DEFAULT                         (_CMU_IFS_LFRCOEDGE_DEFAULT << 28)        /**< Shifted mode DEFAULT for CMU_IFS */
#define CMU_IFS_ULFRCOEDGE                                (0x1UL << 29)                             /**< Set ULFRCOEDGE Interrupt Flag */
#define _CMU_IFS_ULFRCOEDGE_SHIFT                         29                                        /**< Shift value for CMU_ULFRCOEDGE */
#define _CMU_IFS_ULFRCOEDGE_MASK                          0x20000000UL                              /**< Bit mask for CMU_ULFRCOEDGE */
#define _CMU_IFS_ULFRCOEDGE_DEFAULT                       0x00000000UL                              /**< Mode DEFAULT for CMU_IFS */
#define CMU_IFS_ULFRCOEDGE_DEFAULT                        (_CMU_IFS_ULFRCOEDGE_DEFAULT << 29)       /**< Shifted mode DEFAULT for CMU_IFS */
#define CMU_IFS_CMUERR                                    (0x1UL << 31)                             /**< Set CMUERR Interrupt Flag */
#define _CMU_IFS_CMUERR_SHIFT                             31                                        /**< Shift value for CMU_CMUERR */
#define _CMU_IFS_CMUERR_MASK                              0x80000000UL                              /**< Bit mask for CMU_CMUERR */
#define _CMU_IFS_CMUERR_DEFAULT                           0x00000000UL                              /**< Mode DEFAULT for CMU_IFS */
#define CMU_IFS_CMUERR_DEFAULT                            (_CMU_IFS_CMUERR_DEFAULT << 31)           /**< Shifted mode DEFAULT for CMU_IFS */

/* Bit fields for CMU IFC */
#define _CMU_IFC_RESETVALUE                               0x00000000UL                              /**< Default value for CMU_IFC */
#define _CMU_IFC_MASK                                     0xB803FF7FUL                              /**< Mask for CMU_IFC */
#define CMU_IFC_HFRCORDY                                  (0x1UL << 0)                              /**< Clear HFRCORDY Interrupt Flag */
#define _CMU_IFC_HFRCORDY_SHIFT                           0                                         /**< Shift value for CMU_HFRCORDY */
#define _CMU_IFC_HFRCORDY_MASK                            0x1UL                                     /**< Bit mask for CMU_HFRCORDY */
#define _CMU_IFC_HFRCORDY_DEFAULT                         0x00000000UL                              /**< Mode DEFAULT for CMU_IFC */
#define CMU_IFC_HFRCORDY_DEFAULT                          (_CMU_IFC_HFRCORDY_DEFAULT << 0)          /**< Shifted mode DEFAULT for CMU_IFC */
#define CMU_IFC_HFXORDY                                   (0x1UL << 1)                              /**< Clear HFXORDY Interrupt Flag */
#define _CMU_IFC_HFXORDY_SHIFT                            1                                         /**< Shift value for CMU_HFXORDY */
#define _CMU_IFC_HFXORDY_MASK                             0x2UL                                     /**< Bit mask for CMU_HFXORDY */
#define _CMU_IFC_HFXORDY_DEFAULT                          0x00000000UL                              /**< Mode DEFAULT for CMU_IFC */
#define CMU_IFC_HFXORDY_DEFAULT                           (_CMU_IFC_HFXORDY_DEFAULT << 1)           /**< Shifted mode DEFAULT for CMU_IFC */
#define CMU_IFC_LFRCORDY                                  (0x1UL << 2)                              /**< Clear LFRCORDY Interrupt Flag */
#define _CMU_IFC_LFRCORDY_SHIFT                           2                                         /**< Shift value for CMU_LFRCORDY */
#define _CMU_IFC_LFRCORDY_MASK                            0x4UL                                     /**< Bit mask for CMU_LFRCORDY */
#define _CMU_IFC_LFRCORDY_DEFAULT                         0x00000000UL                              /**< Mode DEFAULT for CMU_IFC */
#define CMU_IFC_LFRCORDY_DEFAULT                          (_CMU_IFC_LFRCORDY_DEFAULT << 2)          /**< Shifted mode DEFAULT for CMU_IFC */
#define CMU_IFC_LFXORDY                                   (0x1UL << 3)                              /**< Clear LFXORDY Interrupt Flag */
#define _CMU_IFC_LFXORDY_SHIFT                            3                                         /**< Shift value for CMU_LFXORDY */
#define _CMU_IFC_LFXORDY_MASK                             0x8UL                                     /**< Bit mask for CMU_LFXORDY */
#define _CMU_IFC_LFXORDY_DEFAULT                          0x00000000UL                              /**< Mode DEFAULT for CMU_IFC */
#define CMU_IFC_LFXORDY_DEFAULT                           (_CMU_IFC_LFXORDY_DEFAULT << 3)           /**< Shifted mode DEFAULT for CMU_IFC */
#define CMU_IFC_AUXHFRCORDY                               (0x1UL << 4)                              /**< Clear AUXHFRCORDY Interrupt Flag */
#define _CMU_IFC_AUXHFRCORDY_SHIFT                        4                                         /**< Shift value for CMU_AUXHFRCORDY */
#define _CMU_IFC_AUXHFRCORDY_MASK                         0x10UL                                    /**< Bit mask for CMU_AUXHFRCORDY */
#define _CMU_IFC_AUXHFRCORDY_DEFAULT                      0x00000000UL                              /**< Mode DEFAULT for CMU_IFC */
#define CMU_IFC_AUXHFRCORDY_DEFAULT                       (_CMU_IFC_AUXHFRCORDY_DEFAULT << 4)       /**< Shifted mode DEFAULT for CMU_IFC */
#define CMU_IFC_CALRDY                                    (0x1UL << 5)                              /**< Clear CALRDY Interrupt Flag */
#define _CMU_IFC_CALRDY_SHIFT                             5                                         /**< Shift value for CMU_CALRDY */
#define _CMU_IFC_CALRDY_MASK                              0x20UL                                    /**< Bit mask for CMU_CALRDY */
#define _CMU_IFC_CALRDY_DEFAULT                           0x00000000UL                              /**< Mode DEFAULT for CMU_IFC */
#define CMU_IFC_CALRDY_DEFAULT                            (_CMU_IFC_CALRDY_DEFAULT << 5)            /**< Shifted mode DEFAULT for CMU_IFC */
#define CMU_IFC_CALOF                                     (0x1UL << 6)                              /**< Clear CALOF Interrupt Flag */
#define _CMU_IFC_CALOF_SHIFT                              6                                         /**< Shift value for CMU_CALOF */
#define _CMU_IFC_CALOF_MASK                               0x40UL                                    /**< Bit mask for CMU_CALOF */
#define _CMU_IFC_CALOF_DEFAULT                            0x00000000UL                              /**< Mode DEFAULT for CMU_IFC */
#define CMU_IFC_CALOF_DEFAULT                             (_CMU_IFC_CALOF_DEFAULT << 6)             /**< Shifted mode DEFAULT for CMU_IFC */
#define CMU_IFC_HFXODISERR                                (0x1UL << 8)                              /**< Clear HFXODISERR Interrupt Flag */
#define _CMU_IFC_HFXODISERR_SHIFT                         8                                         /**< Shift value for CMU_HFXODISERR */
#define _CMU_IFC_HFXODISERR_MASK                          0x100UL                                   /**< Bit mask for CMU_HFXODISERR */
#define _CMU_IFC_HFXODISERR_DEFAULT                       0x00000000UL                              /**< Mode DEFAULT for CMU_IFC */
#define CMU_IFC_HFXODISERR_DEFAULT                        (_CMU_IFC_HFXODISERR_DEFAULT << 8)        /**< Shifted mode DEFAULT for CMU_IFC */
#define CMU_IFC_HFXOAUTOSW                                (0x1UL << 9)                              /**< Clear HFXOAUTOSW Interrupt Flag */
#define _CMU_IFC_HFXOAUTOSW_SHIFT                         9                                         /**< Shift value for CMU_HFXOAUTOSW */
#define _CMU_IFC_HFXOAUTOSW_MASK                          0x200UL                                   /**< Bit mask for CMU_HFXOAUTOSW */
#define _CMU_IFC_HFXOAUTOSW_DEFAULT                       0x00000000UL                              /**< Mode DEFAULT for CMU_IFC */
#define CMU_IFC_HFXOAUTOSW_DEFAULT                        (_CMU_IFC_HFXOAUTOSW_DEFAULT << 9)        /**< Shifted mode DEFAULT for CMU_IFC */
#define CMU_IFC_HFXOPEAKDETERR                            (0x1UL << 10)                             /**< Clear HFXOPEAKDETERR Interrupt Flag */
#define _CMU_IFC_HFXOPEAKDETERR_SHIFT                     10                                        /**< Shift value for CMU_HFXOPEAKDETERR */
#define _CMU_IFC_HFXOPEAKDETERR_MASK                      0x400UL                                   /**< Bit mask for CMU_HFXOPEAKDETERR */
#define _CMU_IFC_HFXOPEAKDETERR_DEFAULT                   0x00000000UL                              /**< Mode DEFAULT for CMU_IFC */
#define CMU_IFC_HFXOPEAKDETERR_DEFAULT                    (_CMU_IFC_HFXOPEAKDETERR_DEFAULT << 10)   /**< Shifted mode DEFAULT for CMU_IFC */
#define CMU_IFC_HFXOPEAKDETRDY                            (0x1UL << 11)                             /**< Clear HFXOPEAKDETRDY Interrupt Flag */
#define _CMU_IFC_HFXOPEAKDETRDY_SHIFT                     11                                        /**< Shift value for CMU_HFXOPEAKDETRDY */
#define _CMU_IFC_HFXOPEAKDETRDY_MASK                      0x800UL                                   /**< Bit mask for CMU_HFXOPEAKDETRDY */
#define _CMU_IFC_HFXOPEAKDETRDY_DEFAULT                   0x00000000UL                              /**< Mode DEFAULT for CMU_IFC */
#define CMU_IFC_HFXOPEAKDETRDY_DEFAULT                    (_CMU_IFC_HFXOPEAKDETRDY_DEFAULT << 11)   /**< Shifted mode DEFAULT for CMU_IFC */
#define CMU_IFC_HFXOSHUNTOPTRDY                           (0x1UL << 12)                             /**< Clear HFXOSHUNTOPTRDY Interrupt Flag */
#define _CMU_IFC_HFXOSHUNTOPTRDY_SHIFT                    12                                        /**< Shift value for CMU_HFXOSHUNTOPTRDY */
#define _CMU_IFC_HFXOSHUNTOPTRDY_MASK                     0x1000UL                                  /**< Bit mask for CMU_HFXOSHUNTOPTRDY */
#define _CMU_IFC_HFXOSHUNTOPTRDY_DEFAULT                  0x00000000UL                              /**< Mode DEFAULT for CMU_IFC */
#define CMU_IFC_HFXOSHUNTOPTRDY_DEFAULT                   (_CMU_IFC_HFXOSHUNTOPTRDY_DEFAULT << 12)  /**< Shifted mode DEFAULT for CMU_IFC */
#define CMU_IFC_HFRCODIS                                  (0x1UL << 13)                             /**< Clear HFRCODIS Interrupt Flag */
#define _CMU_IFC_HFRCODIS_SHIFT                           13                                        /**< Shift value for CMU_HFRCODIS */
#define _CMU_IFC_HFRCODIS_MASK                            0x2000UL                                  /**< Bit mask for CMU_HFRCODIS */
#define _CMU_IFC_HFRCODIS_DEFAULT                         0x00000000UL                              /**< Mode DEFAULT for CMU_IFC */
#define CMU_IFC_HFRCODIS_DEFAULT                          (_CMU_IFC_HFRCODIS_DEFAULT << 13)         /**< Shifted mode DEFAULT for CMU_IFC */
#define CMU_IFC_LFTIMEOUTERR                              (0x1UL << 14)                             /**< Clear LFTIMEOUTERR Interrupt Flag */
#define _CMU_IFC_LFTIMEOUTERR_SHIFT                       14                                        /**< Shift value for CMU_LFTIMEOUTERR */
#define _CMU_IFC_LFTIMEOUTERR_MASK                        0x4000UL                                  /**< Bit mask for CMU_LFTIMEOUTERR */
#define _CMU_IFC_LFTIMEOUTERR_DEFAULT                     0x00000000UL                              /**< Mode DEFAULT for CMU_IFC */
#define CMU_IFC_LFTIMEOUTERR_DEFAULT                      (_CMU_IFC_LFTIMEOUTERR_DEFAULT << 14)     /**< Shifted mode DEFAULT for CMU_IFC */
#define CMU_IFC_DPLLRDY                                   (0x1UL << 15)                             /**< Clear DPLLRDY Interrupt Flag */
#define _CMU_IFC_DPLLRDY_SHIFT                            15                                        /**< Shift value for CMU_DPLLRDY */
#define _CMU_IFC_DPLLRDY_MASK                             0x8000UL                                  /**< Bit mask for CMU_DPLLRDY */
#define _CMU_IFC_DPLLRDY_DEFAULT                          0x00000000UL                              /**< Mode DEFAULT for CMU_IFC */
#define CMU_IFC_DPLLRDY_DEFAULT                           (_CMU_IFC_DPLLRDY_DEFAULT << 15)          /**< Shifted mode DEFAULT for CMU_IFC */
#define CMU_IFC_DPLLLOCKFAILLOW                           (0x1UL << 16)                             /**< Clear DPLLLOCKFAILLOW Interrupt Flag */
#define _CMU_IFC_DPLLLOCKFAILLOW_SHIFT                    16                                        /**< Shift value for CMU_DPLLLOCKFAILLOW */
#define _CMU_IFC_DPLLLOCKFAILLOW_MASK                     0x10000UL                                 /**< Bit mask for CMU_DPLLLOCKFAILLOW */
#define _CMU_IFC_DPLLLOCKFAILLOW_DEFAULT                  0x00000000UL                              /**< Mode DEFAULT for CMU_IFC */
#define CMU_IFC_DPLLLOCKFAILLOW_DEFAULT                   (_CMU_IFC_DPLLLOCKFAILLOW_DEFAULT << 16)  /**< Shifted mode DEFAULT for CMU_IFC */
#define CMU_IFC_DPLLLOCKFAILHIGH                          (0x1UL << 17)                             /**< Clear DPLLLOCKFAILHIGH Interrupt Flag */
#define _CMU_IFC_DPLLLOCKFAILHIGH_SHIFT                   17                                        /**< Shift value for CMU_DPLLLOCKFAILHIGH */
#define _CMU_IFC_DPLLLOCKFAILHIGH_MASK                    0x20000UL                                 /**< Bit mask for CMU_DPLLLOCKFAILHIGH */
#define _CMU_IFC_DPLLLOCKFAILHIGH_DEFAULT                 0x00000000UL                              /**< Mode DEFAULT for CMU_IFC */
#define CMU_IFC_DPLLLOCKFAILHIGH_DEFAULT                  (_CMU_IFC_DPLLLOCKFAILHIGH_DEFAULT << 17) /**< Shifted mode DEFAULT for CMU_IFC */
#define CMU_IFC_LFXOEDGE                                  (0x1UL << 27)                             /**< Clear LFXOEDGE Interrupt Flag */
#define _CMU_IFC_LFXOEDGE_SHIFT                           27                                        /**< Shift value for CMU_LFXOEDGE */
#define _CMU_IFC_LFXOEDGE_MASK                            0x8000000UL                               /**< Bit mask for CMU_LFXOEDGE */
#define _CMU_IFC_LFXOEDGE_DEFAULT                         0x00000000UL                              /**< Mode DEFAULT for CMU_IFC */
#define CMU_IFC_LFXOEDGE_DEFAULT                          (_CMU_IFC_LFXOEDGE_DEFAULT << 27)         /**< Shifted mode DEFAULT for CMU_IFC */
#define CMU_IFC_LFRCOEDGE                                 (0x1UL << 28)                             /**< Clear LFRCOEDGE Interrupt Flag */
#define _CMU_IFC_LFRCOEDGE_SHIFT                          28                                        /**< Shift value for CMU_LFRCOEDGE */
#define _CMU_IFC_LFRCOEDGE_MASK                           0x10000000UL                              /**< Bit mask for CMU_LFRCOEDGE */
#define _CMU_IFC_LFRCOEDGE_DEFAULT                        0x00000000UL                              /**< Mode DEFAULT for CMU_IFC */
#define CMU_IFC_LFRCOEDGE_DEFAULT                         (_CMU_IFC_LFRCOEDGE_DEFAULT << 28)        /**< Shifted mode DEFAULT for CMU_IFC */
#define CMU_IFC_ULFRCOEDGE                                (0x1UL << 29)                             /**< Clear ULFRCOEDGE Interrupt Flag */
#define _CMU_IFC_ULFRCOEDGE_SHIFT                         29                                        /**< Shift value for CMU_ULFRCOEDGE */
#define _CMU_IFC_ULFRCOEDGE_MASK                          0x20000000UL                              /**< Bit mask for CMU_ULFRCOEDGE */
#define _CMU_IFC_ULFRCOEDGE_DEFAULT                       0x00000000UL                              /**< Mode DEFAULT for CMU_IFC */
#define CMU_IFC_ULFRCOEDGE_DEFAULT                        (_CMU_IFC_ULFRCOEDGE_DEFAULT << 29)       /**< Shifted mode DEFAULT for CMU_IFC */
#define CMU_IFC_CMUERR                                    (0x1UL << 31)                             /**< Clear CMUERR Interrupt Flag */
#define _CMU_IFC_CMUERR_SHIFT                             31                                        /**< Shift value for CMU_CMUERR */
#define _CMU_IFC_CMUERR_MASK                              0x80000000UL                              /**< Bit mask for CMU_CMUERR */
#define _CMU_IFC_CMUERR_DEFAULT                           0x00000000UL                              /**< Mode DEFAULT for CMU_IFC */
#define CMU_IFC_CMUERR_DEFAULT                            (_CMU_IFC_CMUERR_DEFAULT << 31)           /**< Shifted mode DEFAULT for CMU_IFC */

/* Bit fields for CMU IEN */
#define _CMU_IEN_RESETVALUE                               0x00000000UL                              /**< Default value for CMU_IEN */
#define _CMU_IEN_MASK                                     0xB803FF7FUL                              /**< Mask for CMU_IEN */
#define CMU_IEN_HFRCORDY                                  (0x1UL << 0)                              /**< HFRCORDY Interrupt Enable */
#define _CMU_IEN_HFRCORDY_SHIFT                           0                                         /**< Shift value for CMU_HFRCORDY */
#define _CMU_IEN_HFRCORDY_MASK                            0x1UL                                     /**< Bit mask for CMU_HFRCORDY */
#define _CMU_IEN_HFRCORDY_DEFAULT                         0x00000000UL                              /**< Mode DEFAULT for CMU_IEN */
#define CMU_IEN_HFRCORDY_DEFAULT                          (_CMU_IEN_HFRCORDY_DEFAULT << 0)          /**< Shifted mode DEFAULT for CMU_IEN */
#define CMU_IEN_HFXORDY                                   (0x1UL << 1)                              /**< HFXORDY Interrupt Enable */
#define _CMU_IEN_HFXORDY_SHIFT                            1                                         /**< Shift value for CMU_HFXORDY */
#define _CMU_IEN_HFXORDY_MASK                             0x2UL                                     /**< Bit mask for CMU_HFXORDY */
#define _CMU_IEN_HFXORDY_DEFAULT                          0x00000000UL                              /**< Mode DEFAULT for CMU_IEN */
#define CMU_IEN_HFXORDY_DEFAULT                           (_CMU_IEN_HFXORDY_DEFAULT << 1)           /**< Shifted mode DEFAULT for CMU_IEN */
#define CMU_IEN_LFRCORDY                                  (0x1UL << 2)                              /**< LFRCORDY Interrupt Enable */
#define _CMU_IEN_LFRCORDY_SHIFT                           2                                         /**< Shift value for CMU_LFRCORDY */
#define _CMU_IEN_LFRCORDY_MASK                            0x4UL                                     /**< Bit mask for CMU_LFRCORDY */
#define _CMU_IEN_LFRCORDY_DEFAULT                         0x00000000UL                              /**< Mode DEFAULT for CMU_IEN */
#define CMU_IEN_LFRCORDY_DEFAULT                          (_CMU_IEN_LFRCORDY_DEFAULT << 2)          /**< Shifted mode DEFAULT for CMU_IEN */
#define CMU_IEN_LFXORDY                                   (0x1UL << 3)                              /**< LFXORDY Interrupt Enable */
#define _CMU_IEN_LFXORDY_SHIFT                            3                                         /**< Shift value for CMU_LFXORDY */
#define _CMU_IEN_LFXORDY_MASK                             0x8UL                                     /**< Bit mask for CMU_LFXORDY */
#define _CMU_IEN_LFXORDY_DEFAULT                          0x00000000UL                              /**< Mode DEFAULT for CMU_IEN */
#define CMU_IEN_LFXORDY_DEFAULT                           (_CMU_IEN_LFXORDY_DEFAULT << 3)           /**< Shifted mode DEFAULT for CMU_IEN */
#define CMU_IEN_AUXHFRCORDY                               (0x1UL << 4)                              /**< AUXHFRCORDY Interrupt Enable */
#define _CMU_IEN_AUXHFRCORDY_SHIFT                        4                                         /**< Shift value for CMU_AUXHFRCORDY */
#define _CMU_IEN_AUXHFRCORDY_MASK                         0x10UL                                    /**< Bit mask for CMU_AUXHFRCORDY */
#define _CMU_IEN_AUXHFRCORDY_DEFAULT                      0x00000000UL                              /**< Mode DEFAULT for CMU_IEN */
#define CMU_IEN_AUXHFRCORDY_DEFAULT                       (_CMU_IEN_AUXHFRCORDY_DEFAULT << 4)       /**< Shifted mode DEFAULT for CMU_IEN */
#define CMU_IEN_CALRDY                                    (0x1UL << 5)                              /**< CALRDY Interrupt Enable */
#define _CMU_IEN_CALRDY_SHIFT                             5                                         /**< Shift value for CMU_CALRDY */
#define _CMU_IEN_CALRDY_MASK                              0x20UL                                    /**< Bit mask for CMU_CALRDY */
#define _CMU_IEN_CALRDY_DEFAULT                           0x00000000UL                              /**< Mode DEFAULT for CMU_IEN */
#define CMU_IEN_CALRDY_DEFAULT                            (_CMU_IEN_CALRDY_DEFAULT << 5)            /**< Shifted mode DEFAULT for CMU_IEN */
#define CMU_IEN_CALOF                                     (0x1UL << 6)                              /**< CALOF Interrupt Enable */
#define _CMU_IEN_CALOF_SHIFT                              6                                         /**< Shift value for CMU_CALOF */
#define _CMU_IEN_CALOF_MASK                               0x40UL                                    /**< Bit mask for CMU_CALOF */
#define _CMU_IEN_CALOF_DEFAULT                            0x00000000UL                              /**< Mode DEFAULT for CMU_IEN */
#define CMU_IEN_CALOF_DEFAULT                             (_CMU_IEN_CALOF_DEFAULT << 6)             /**< Shifted mode DEFAULT for CMU_IEN */
#define CMU_IEN_HFXODISERR                                (0x1UL << 8)                              /**< HFXODISERR Interrupt Enable */
#define _CMU_IEN_HFXODISERR_SHIFT                         8                                         /**< Shift value for CMU_HFXODISERR */
#define _CMU_IEN_HFXODISERR_MASK                          0x100UL                                   /**< Bit mask for CMU_HFXODISERR */
#define _CMU_IEN_HFXODISERR_DEFAULT                       0x00000000UL                              /**< Mode DEFAULT for CMU_IEN */
#define CMU_IEN_HFXODISERR_DEFAULT                        (_CMU_IEN_HFXODISERR_DEFAULT << 8)        /**< Shifted mode DEFAULT for CMU_IEN */
#define CMU_IEN_HFXOAUTOSW                                (0x1UL << 9)                              /**< HFXOAUTOSW Interrupt Enable */
#define _CMU_IEN_HFXOAUTOSW_SHIFT                         9                                         /**< Shift value for CMU_HFXOAUTOSW */
#define _CMU_IEN_HFXOAUTOSW_MASK                          0x200UL                                   /**< Bit mask for CMU_HFXOAUTOSW */
#define _CMU_IEN_HFXOAUTOSW_DEFAULT                       0x00000000UL                              /**< Mode DEFAULT for CMU_IEN */
#define CMU_IEN_HFXOAUTOSW_DEFAULT                        (_CMU_IEN_HFXOAUTOSW_DEFAULT << 9)        /**< Shifted mode DEFAULT for CMU_IEN */
#define CMU_IEN_HFXOPEAKDETERR                            (0x1UL << 10)                             /**< HFXOPEAKDETERR Interrupt Enable */
#define _CMU_IEN_HFXOPEAKDETERR_SHIFT                     10                                        /**< Shift value for CMU_HFXOPEAKDETERR */
#define _CMU_IEN_HFXOPEAKDETERR_MASK                      0x400UL                                   /**< Bit mask for CMU_HFXOPEAKDETERR */
#define _CMU_IEN_HFXOPEAKDETERR_DEFAULT                   0x00000000UL                              /**< Mode DEFAULT for CMU_IEN */
#define CMU_IEN_HFXOPEAKDETERR_DEFAULT                    (_CMU_IEN_HFXOPEAKDETERR_DEFAULT << 10)   /**< Shifted mode DEFAULT for CMU_IEN */
#define CMU_IEN_HFXOPEAKDETRDY                            (0x1UL << 11)                             /**< HFXOPEAKDETRDY Interrupt Enable */
#define _CMU_IEN_HFXOPEAKDETRDY_SHIFT                     11                                        /**< Shift value for CMU_HFXOPEAKDETRDY */
#define _CMU_IEN_HFXOPEAKDETRDY_MASK                      0x800UL                                   /**< Bit mask for CMU_HFXOPEAKDETRDY */
#define _CMU_IEN_HFXOPEAKDETRDY_DEFAULT                   0x00000000UL                              /**< Mode DEFAULT for CMU_IEN */
#define CMU_IEN_HFXOPEAKDETRDY_DEFAULT                    (_CMU_IEN_HFXOPEAKDETRDY_DEFAULT << 11)   /**< Shifted mode DEFAULT for CMU_IEN */
#define CMU_IEN_HFXOSHUNTOPTRDY                           (0x1UL << 12)                             /**< HFXOSHUNTOPTRDY Interrupt Enable */
#define _CMU_IEN_HFXOSHUNTOPTRDY_SHIFT                    12                                        /**< Shift value for CMU_HFXOSHUNTOPTRDY */
#define _CMU_IEN_HFXOSHUNTOPTRDY_MASK                     0x1000UL                                  /**< Bit mask for CMU_HFXOSHUNTOPTRDY */
#define _CMU_IEN_HFXOSHUNTOPTRDY_DEFAULT                  0x00000000UL                              /**< Mode DEFAULT for CMU_IEN */
#define CMU_IEN_HFXOSHUNTOPTRDY_DEFAULT                   (_CMU_IEN_HFXOSHUNTOPTRDY_DEFAULT << 12)  /**< Shifted mode DEFAULT for CMU_IEN */
#define CMU_IEN_HFRCODIS                                  (0x1UL << 13)                             /**< HFRCODIS Interrupt Enable */
#define _CMU_IEN_HFRCODIS_SHIFT                           13                                        /**< Shift value for CMU_HFRCODIS */
#define _CMU_IEN_HFRCODIS_MASK                            0x2000UL                                  /**< Bit mask for CMU_HFRCODIS */
#define _CMU_IEN_HFRCODIS_DEFAULT                         0x00000000UL                              /**< Mode DEFAULT for CMU_IEN */
#define CMU_IEN_HFRCODIS_DEFAULT                          (_CMU_IEN_HFRCODIS_DEFAULT << 13)         /**< Shifted mode DEFAULT for CMU_IEN */
#define CMU_IEN_LFTIMEOUTERR                              (0x1UL << 14)                             /**< LFTIMEOUTERR Interrupt Enable */
#define _CMU_IEN_LFTIMEOUTERR_SHIFT                       14                                        /**< Shift value for CMU_LFTIMEOUTERR */
#define _CMU_IEN_LFTIMEOUTERR_MASK                        0x4000UL                                  /**< Bit mask for CMU_LFTIMEOUTERR */
#define _CMU_IEN_LFTIMEOUTERR_DEFAULT                     0x00000000UL                              /**< Mode DEFAULT for CMU_IEN */
#define CMU_IEN_LFTIMEOUTERR_DEFAULT                      (_CMU_IEN_LFTIMEOUTERR_DEFAULT << 14)     /**< Shifted mode DEFAULT for CMU_IEN */
#define CMU_IEN_DPLLRDY                                   (0x1UL << 15)                             /**< DPLLRDY Interrupt Enable */
#define _CMU_IEN_DPLLRDY_SHIFT                            15                                        /**< Shift value for CMU_DPLLRDY */
#define _CMU_IEN_DPLLRDY_MASK                             0x8000UL                                  /**< Bit mask for CMU_DPLLRDY */
#define _CMU_IEN_DPLLRDY_DEFAULT                          0x00000000UL                              /**< Mode DEFAULT for CMU_IEN */
#define CMU_IEN_DPLLRDY_DEFAULT                           (_CMU_IEN_DPLLRDY_DEFAULT << 15)          /**< Shifted mode DEFAULT for CMU_IEN */
#define CMU_IEN_DPLLLOCKFAILLOW                           (0x1UL << 16)                             /**< DPLLLOCKFAILLOW Interrupt Enable */
#define _CMU_IEN_DPLLLOCKFAILLOW_SHIFT                    16                                        /**< Shift value for CMU_DPLLLOCKFAILLOW */
#define _CMU_IEN_DPLLLOCKFAILLOW_MASK                     0x10000UL                                 /**< Bit mask for CMU_DPLLLOCKFAILLOW */
#define _CMU_IEN_DPLLLOCKFAILLOW_DEFAULT                  0x00000000UL                              /**< Mode DEFAULT for CMU_IEN */
#define CMU_IEN_DPLLLOCKFAILLOW_DEFAULT                   (_CMU_IEN_DPLLLOCKFAILLOW_DEFAULT << 16)  /**< Shifted mode DEFAULT for CMU_IEN */
#define CMU_IEN_DPLLLOCKFAILHIGH                          (0x1UL << 17)                             /**< DPLLLOCKFAILHIGH Interrupt Enable */
#define _CMU_IEN_DPLLLOCKFAILHIGH_SHIFT                   17                                        /**< Shift value for CMU_DPLLLOCKFAILHIGH */
#define _CMU_IEN_DPLLLOCKFAILHIGH_MASK                    0x20000UL                                 /**< Bit mask for CMU_DPLLLOCKFAILHIGH */
#define _CMU_IEN_DPLLLOCKFAILHIGH_DEFAULT                 0x00000000UL                              /**< Mode DEFAULT for CMU_IEN */
#define CMU_IEN_DPLLLOCKFAILHIGH_DEFAULT                  (_CMU_IEN_DPLLLOCKFAILHIGH_DEFAULT << 17) /**< Shifted mode DEFAULT for CMU_IEN */
#define CMU_IEN_LFXOEDGE                                  (0x1UL << 27)                             /**< LFXOEDGE Interrupt Enable */
#define _CMU_IEN_LFXOEDGE_SHIFT                           27                                        /**< Shift value for CMU_LFXOEDGE */
#define _CMU_IEN_LFXOEDGE_MASK                            0x8000000UL                               /**< Bit mask for CMU_LFXOEDGE */
#define _CMU_IEN_LFXOEDGE_DEFAULT                         0x00000000UL                              /**< Mode DEFAULT for CMU_IEN */
#define CMU_IEN_LFXOEDGE_DEFAULT                          (_CMU_IEN_LFXOEDGE_DEFAULT << 27)         /**< Shifted mode DEFAULT for CMU_IEN */
#define CMU_IEN_LFRCOEDGE                                 (0x1UL << 28)                             /**< LFRCOEDGE Interrupt Enable */
#define _CMU_IEN_LFRCOEDGE_SHIFT                          28                                        /**< Shift value for CMU_LFRCOEDGE */
#define _CMU_IEN_LFRCOEDGE_MASK                           0x10000000UL                              /**< Bit mask for CMU_LFRCOEDGE */
#define _CMU_IEN_LFRCOEDGE_DEFAULT                        0x00000000UL                              /**< Mode DEFAULT for CMU_IEN */
#define CMU_IEN_LFRCOEDGE_DEFAULT                         (_CMU_IEN_LFRCOEDGE_DEFAULT << 28)        /**< Shifted mode DEFAULT for CMU_IEN */
#define CMU_IEN_ULFRCOEDGE                                (0x1UL << 29)                             /**< ULFRCOEDGE Interrupt Enable */
#define _CMU_IEN_ULFRCOEDGE_SHIFT                         29                                        /**< Shift value for CMU_ULFRCOEDGE */
#define _CMU_IEN_ULFRCOEDGE_MASK                          0x20000000UL                              /**< Bit mask for CMU_ULFRCOEDGE */
#define _CMU_IEN_ULFRCOEDGE_DEFAULT                       0x00000000UL                              /**< Mode DEFAULT for CMU_IEN */
#define CMU_IEN_ULFRCOEDGE_DEFAULT                        (_CMU_IEN_ULFRCOEDGE_DEFAULT << 29)       /**< Shifted mode DEFAULT for CMU_IEN */
#define CMU_IEN_CMUERR                                    (0x1UL << 31)                             /**< CMUERR Interrupt Enable */
#define _CMU_IEN_CMUERR_SHIFT                             31                                        /**< Shift value for CMU_CMUERR */
#define _CMU_IEN_CMUERR_MASK                              0x80000000UL                              /**< Bit mask for CMU_CMUERR */
#define _CMU_IEN_CMUERR_DEFAULT                           0x00000000UL                              /**< Mode DEFAULT for CMU_IEN */
#define CMU_IEN_CMUERR_DEFAULT                            (_CMU_IEN_CMUERR_DEFAULT << 31)           /**< Shifted mode DEFAULT for CMU_IEN */

/* Bit fields for CMU HFBUSCLKEN0 */
#define _CMU_HFBUSCLKEN0_RESETVALUE                       0x00000000UL                            /**< Default value for CMU_HFBUSCLKEN0 */
#define _CMU_HFBUSCLKEN0_MASK                             0x0000007FUL                            /**< Mask for CMU_HFBUSCLKEN0 */
#define CMU_HFBUSCLKEN0_CRYPTO0                           (0x1UL << 0)                            /**< Advanced Encryption Standard Accelerator 0 Clock Enable */
#define CMU_HFBUSCLKEN0_CRYPTO                            CMU_HFBUSCLKEN0_CRYPTO0                 /**< Alias for CRYPTO0 */
#define _CMU_HFBUSCLKEN0_CRYPTO0_SHIFT                    0                                       /**< Shift value for CMU_CRYPTO0 */
#define _CMU_HFBUSCLKEN0_CRYPTO0_MASK                     0x1UL                                   /**< Bit mask for CMU_CRYPTO0 */
#define _CMU_HFBUSCLKEN0_CRYPTO_SHIFT                     _CMU_HFBUSCLKEN0_CRYPTO0_SHIFT          /**< Alias for CMU_CRYPTO0 */
#define _CMU_HFBUSCLKEN0_CRYPTO_MASK                      _CMU_HFBUSCLKEN0_CRYPTO0_MASK           /**< Alias for CMU_CRYPTO0 */
#define _CMU_HFBUSCLKEN0_CRYPTO0_DEFAULT                  0x00000000UL                            /**< Mode DEFAULT for CMU_HFBUSCLKEN0 */
#define _CMU_HFBUSCLKEN0_CRYPTO_DEFAULT                   _CMU_HFBUSCLKEN0_CRYPTO0_DEFAULT        /**< Alias for CRYPTO0 mode DEFAULT */
#define CMU_HFBUSCLKEN0_CRYPTO0_DEFAULT                   (_CMU_HFBUSCLKEN0_CRYPTO0_DEFAULT << 0) /**< Shifted mode DEFAULT for CMU_HFBUSCLKEN0 */
#define  CMU_HFBUSCLKEN0_CRYPTO_DEFAULT                   CMU_HFBUSCLKEN0_CRYPTO0_DEFAULT         /**< Alias for CRYPTO0 mode DEFAULT*/
#define CMU_HFBUSCLKEN0_CRYPTO1                           (0x1UL << 1)                            /**< Advanced Encryption Standard Accelerator 1 Clock Enable */
#define _CMU_HFBUSCLKEN0_CRYPTO1_SHIFT                    1                                       /**< Shift value for CMU_CRYPTO1 */
#define _CMU_HFBUSCLKEN0_CRYPTO1_MASK                     0x2UL                                   /**< Bit mask for CMU_CRYPTO1 */
#define _CMU_HFBUSCLKEN0_CRYPTO1_DEFAULT                  0x00000000UL                            /**< Mode DEFAULT for CMU_HFBUSCLKEN0 */
#define CMU_HFBUSCLKEN0_CRYPTO1_DEFAULT                   (_CMU_HFBUSCLKEN0_CRYPTO1_DEFAULT << 1) /**< Shifted mode DEFAULT for CMU_HFBUSCLKEN0 */
#define CMU_HFBUSCLKEN0_LE                                (0x1UL << 2)                            /**< Low Energy Peripheral Interface Clock Enable */
#define _CMU_HFBUSCLKEN0_LE_SHIFT                         2                                       /**< Shift value for CMU_LE */
#define _CMU_HFBUSCLKEN0_LE_MASK                          0x4UL                                   /**< Bit mask for CMU_LE */
#define _CMU_HFBUSCLKEN0_LE_DEFAULT                       0x00000000UL                            /**< Mode DEFAULT for CMU_HFBUSCLKEN0 */
#define CMU_HFBUSCLKEN0_LE_DEFAULT                        (_CMU_HFBUSCLKEN0_LE_DEFAULT << 2)      /**< Shifted mode DEFAULT for CMU_HFBUSCLKEN0 */
#define CMU_HFBUSCLKEN0_GPIO                              (0x1UL << 3)                            /**< General purpose Input/Output Clock Enable */
#define _CMU_HFBUSCLKEN0_GPIO_SHIFT                       3                                       /**< Shift value for CMU_GPIO */
#define _CMU_HFBUSCLKEN0_GPIO_MASK                        0x8UL                                   /**< Bit mask for CMU_GPIO */
#define _CMU_HFBUSCLKEN0_GPIO_DEFAULT                     0x00000000UL                            /**< Mode DEFAULT for CMU_HFBUSCLKEN0 */
#define CMU_HFBUSCLKEN0_GPIO_DEFAULT                      (_CMU_HFBUSCLKEN0_GPIO_DEFAULT << 3)    /**< Shifted mode DEFAULT for CMU_HFBUSCLKEN0 */
#define CMU_HFBUSCLKEN0_PRS                               (0x1UL << 4)                            /**< Peripheral Reflex System Clock Enable */
#define _CMU_HFBUSCLKEN0_PRS_SHIFT                        4                                       /**< Shift value for CMU_PRS */
#define _CMU_HFBUSCLKEN0_PRS_MASK                         0x10UL                                  /**< Bit mask for CMU_PRS */
#define _CMU_HFBUSCLKEN0_PRS_DEFAULT                      0x00000000UL                            /**< Mode DEFAULT for CMU_HFBUSCLKEN0 */
#define CMU_HFBUSCLKEN0_PRS_DEFAULT                       (_CMU_HFBUSCLKEN0_PRS_DEFAULT << 4)     /**< Shifted mode DEFAULT for CMU_HFBUSCLKEN0 */
#define CMU_HFBUSCLKEN0_LDMA                              (0x1UL << 5)                            /**< Linked Direct Memory Access Controller Clock Enable */
#define _CMU_HFBUSCLKEN0_LDMA_SHIFT                       5                                       /**< Shift value for CMU_LDMA */
#define _CMU_HFBUSCLKEN0_LDMA_MASK                        0x20UL                                  /**< Bit mask for CMU_LDMA */
#define _CMU_HFBUSCLKEN0_LDMA_DEFAULT                     0x00000000UL                            /**< Mode DEFAULT for CMU_HFBUSCLKEN0 */
#define CMU_HFBUSCLKEN0_LDMA_DEFAULT                      (_CMU_HFBUSCLKEN0_LDMA_DEFAULT << 5)    /**< Shifted mode DEFAULT for CMU_HFBUSCLKEN0 */
#define CMU_HFBUSCLKEN0_GPCRC                             (0x1UL << 6)                            /**< General Purpose CRC Clock Enable */
#define _CMU_HFBUSCLKEN0_GPCRC_SHIFT                      6                                       /**< Shift value for CMU_GPCRC */
#define _CMU_HFBUSCLKEN0_GPCRC_MASK                       0x40UL                                  /**< Bit mask for CMU_GPCRC */
#define _CMU_HFBUSCLKEN0_GPCRC_DEFAULT                    0x00000000UL                            /**< Mode DEFAULT for CMU_HFBUSCLKEN0 */
#define CMU_HFBUSCLKEN0_GPCRC_DEFAULT                     (_CMU_HFBUSCLKEN0_GPCRC_DEFAULT << 6)   /**< Shifted mode DEFAULT for CMU_HFBUSCLKEN0 */

/* Bit fields for CMU HFPERCLKEN0 */
#define _CMU_HFPERCLKEN0_RESETVALUE                       0x00000000UL                               /**< Default value for CMU_HFPERCLKEN0 */
#define _CMU_HFPERCLKEN0_MASK                             0x0000FFFFUL                               /**< Mask for CMU_HFPERCLKEN0 */
#define CMU_HFPERCLKEN0_TIMER0                            (0x1UL << 0)                               /**< Timer 0 Clock Enable */
#define _CMU_HFPERCLKEN0_TIMER0_SHIFT                     0                                          /**< Shift value for CMU_TIMER0 */
#define _CMU_HFPERCLKEN0_TIMER0_MASK                      0x1UL                                      /**< Bit mask for CMU_TIMER0 */
#define _CMU_HFPERCLKEN0_TIMER0_DEFAULT                   0x00000000UL                               /**< Mode DEFAULT for CMU_HFPERCLKEN0 */
#define CMU_HFPERCLKEN0_TIMER0_DEFAULT                    (_CMU_HFPERCLKEN0_TIMER0_DEFAULT << 0)     /**< Shifted mode DEFAULT for CMU_HFPERCLKEN0 */
#define CMU_HFPERCLKEN0_TIMER1                            (0x1UL << 1)                               /**< Timer 1 Clock Enable */
#define _CMU_HFPERCLKEN0_TIMER1_SHIFT                     1                                          /**< Shift value for CMU_TIMER1 */
#define _CMU_HFPERCLKEN0_TIMER1_MASK                      0x2UL                                      /**< Bit mask for CMU_TIMER1 */
#define _CMU_HFPERCLKEN0_TIMER1_DEFAULT                   0x00000000UL                               /**< Mode DEFAULT for CMU_HFPERCLKEN0 */
#define CMU_HFPERCLKEN0_TIMER1_DEFAULT                    (_CMU_HFPERCLKEN0_TIMER1_DEFAULT << 1)     /**< Shifted mode DEFAULT for CMU_HFPERCLKEN0 */
#define CMU_HFPERCLKEN0_WTIMER0                           (0x1UL << 2)                               /**< Wide Timer 0 Clock Enable */
#define _CMU_HFPERCLKEN0_WTIMER0_SHIFT                    2                                          /**< Shift value for CMU_WTIMER0 */
#define _CMU_HFPERCLKEN0_WTIMER0_MASK                     0x4UL                                      /**< Bit mask for CMU_WTIMER0 */
#define _CMU_HFPERCLKEN0_WTIMER0_DEFAULT                  0x00000000UL                               /**< Mode DEFAULT for CMU_HFPERCLKEN0 */
#define CMU_HFPERCLKEN0_WTIMER0_DEFAULT                   (_CMU_HFPERCLKEN0_WTIMER0_DEFAULT << 2)    /**< Shifted mode DEFAULT for CMU_HFPERCLKEN0 */
#define CMU_HFPERCLKEN0_USART0                            (0x1UL << 3)                               /**< Universal Synchronous/Asynchronous Receiver/Transmitter 0 Clock Enable */
#define _CMU_HFPERCLKEN0_USART0_SHIFT                     3                                          /**< Shift value for CMU_USART0 */
#define _CMU_HFPERCLKEN0_USART0_MASK                      0x8UL                                      /**< Bit mask for CMU_USART0 */
#define _CMU_HFPERCLKEN0_USART0_DEFAULT                   0x00000000UL                               /**< Mode DEFAULT for CMU_HFPERCLKEN0 */
#define CMU_HFPERCLKEN0_USART0_DEFAULT                    (_CMU_HFPERCLKEN0_USART0_DEFAULT << 3)     /**< Shifted mode DEFAULT for CMU_HFPERCLKEN0 */
#define CMU_HFPERCLKEN0_USART1                            (0x1UL << 4)                               /**< Universal Synchronous/Asynchronous Receiver/Transmitter 1 Clock Enable */
#define _CMU_HFPERCLKEN0_USART1_SHIFT                     4                                          /**< Shift value for CMU_USART1 */
#define _CMU_HFPERCLKEN0_USART1_MASK                      0x10UL                                     /**< Bit mask for CMU_USART1 */
#define _CMU_HFPERCLKEN0_USART1_DEFAULT                   0x00000000UL                               /**< Mode DEFAULT for CMU_HFPERCLKEN0 */
#define CMU_HFPERCLKEN0_USART1_DEFAULT                    (_CMU_HFPERCLKEN0_USART1_DEFAULT << 4)     /**< Shifted mode DEFAULT for CMU_HFPERCLKEN0 */
#define CMU_HFPERCLKEN0_USART2                            (0x1UL << 5)                               /**< Universal Synchronous/Asynchronous Receiver/Transmitter 2 Clock Enable */
#define _CMU_HFPERCLKEN0_USART2_SHIFT                     5                                          /**< Shift value for CMU_USART2 */
#define _CMU_HFPERCLKEN0_USART2_MASK                      0x20UL                                     /**< Bit mask for CMU_USART2 */
#define _CMU_HFPERCLKEN0_USART2_DEFAULT                   0x00000000UL                               /**< Mode DEFAULT for CMU_HFPERCLKEN0 */
#define CMU_HFPERCLKEN0_USART2_DEFAULT                    (_CMU_HFPERCLKEN0_USART2_DEFAULT << 5)     /**< Shifted mode DEFAULT for CMU_HFPERCLKEN0 */
#define CMU_HFPERCLKEN0_I2C0                              (0x1UL << 6)                               /**< I2C 0 Clock Enable */
#define _CMU_HFPERCLKEN0_I2C0_SHIFT                       6                                          /**< Shift value for CMU_I2C0 */
#define _CMU_HFPERCLKEN0_I2C0_MASK                        0x40UL                                     /**< Bit mask for CMU_I2C0 */
#define _CMU_HFPERCLKEN0_I2C0_DEFAULT                     0x00000000UL                               /**< Mode DEFAULT for CMU_HFPERCLKEN0 */
#define CMU_HFPERCLKEN0_I2C0_DEFAULT                      (_CMU_HFPERCLKEN0_I2C0_DEFAULT << 6)       /**< Shifted mode DEFAULT for CMU_HFPERCLKEN0 */
#define CMU_HFPERCLKEN0_I2C1                              (0x1UL << 7)                               /**< I2C 1 Clock Enable */
#define _CMU_HFPERCLKEN0_I2C1_SHIFT                       7                                          /**< Shift value for CMU_I2C1 */
#define _CMU_HFPERCLKEN0_I2C1_MASK                        0x80UL                                     /**< Bit mask for CMU_I2C1 */
#define _CMU_HFPERCLKEN0_I2C1_DEFAULT                     0x00000000UL                               /**< Mode DEFAULT for CMU_HFPERCLKEN0 */
#define CMU_HFPERCLKEN0_I2C1_DEFAULT                      (_CMU_HFPERCLKEN0_I2C1_DEFAULT << 7)       /**< Shifted mode DEFAULT for CMU_HFPERCLKEN0 */
#define CMU_HFPERCLKEN0_ACMP0                             (0x1UL << 8)                               /**< Analog Comparator 0 Clock Enable */
#define _CMU_HFPERCLKEN0_ACMP0_SHIFT                      8                                          /**< Shift value for CMU_ACMP0 */
#define _CMU_HFPERCLKEN0_ACMP0_MASK                       0x100UL                                    /**< Bit mask for CMU_ACMP0 */
#define _CMU_HFPERCLKEN0_ACMP0_DEFAULT                    0x00000000UL                               /**< Mode DEFAULT for CMU_HFPERCLKEN0 */
#define CMU_HFPERCLKEN0_ACMP0_DEFAULT                     (_CMU_HFPERCLKEN0_ACMP0_DEFAULT << 8)      /**< Shifted mode DEFAULT for CMU_HFPERCLKEN0 */
#define CMU_HFPERCLKEN0_ACMP1                             (0x1UL << 9)                               /**< Analog Comparator 1 Clock Enable */
#define _CMU_HFPERCLKEN0_ACMP1_SHIFT                      9                                          /**< Shift value for CMU_ACMP1 */
#define _CMU_HFPERCLKEN0_ACMP1_MASK                       0x200UL                                    /**< Bit mask for CMU_ACMP1 */
#define _CMU_HFPERCLKEN0_ACMP1_DEFAULT                    0x00000000UL                               /**< Mode DEFAULT for CMU_HFPERCLKEN0 */
#define CMU_HFPERCLKEN0_ACMP1_DEFAULT                     (_CMU_HFPERCLKEN0_ACMP1_DEFAULT << 9)      /**< Shifted mode DEFAULT for CMU_HFPERCLKEN0 */
#define CMU_HFPERCLKEN0_CRYOTIMER                         (0x1UL << 10)                              /**< CRYOTIMER Clock Enable */
#define _CMU_HFPERCLKEN0_CRYOTIMER_SHIFT                  10                                         /**< Shift value for CMU_CRYOTIMER */
#define _CMU_HFPERCLKEN0_CRYOTIMER_MASK                   0x400UL                                    /**< Bit mask for CMU_CRYOTIMER */
#define _CMU_HFPERCLKEN0_CRYOTIMER_DEFAULT                0x00000000UL                               /**< Mode DEFAULT for CMU_HFPERCLKEN0 */
#define CMU_HFPERCLKEN0_CRYOTIMER_DEFAULT                 (_CMU_HFPERCLKEN0_CRYOTIMER_DEFAULT << 10) /**< Shifted mode DEFAULT for CMU_HFPERCLKEN0 */
#define CMU_HFPERCLKEN0_ADC0                              (0x1UL << 11)                              /**< Analog to Digital Converter 0 Clock Enable */
#define _CMU_HFPERCLKEN0_ADC0_SHIFT                       11                                         /**< Shift value for CMU_ADC0 */
#define _CMU_HFPERCLKEN0_ADC0_MASK                        0x800UL                                    /**< Bit mask for CMU_ADC0 */
#define _CMU_HFPERCLKEN0_ADC0_DEFAULT                     0x00000000UL                               /**< Mode DEFAULT for CMU_HFPERCLKEN0 */
#define CMU_HFPERCLKEN0_ADC0_DEFAULT                      (_CMU_HFPERCLKEN0_ADC0_DEFAULT << 11)      /**< Shifted mode DEFAULT for CMU_HFPERCLKEN0 */
#define CMU_HFPERCLKEN0_VDAC0                             (0x1UL << 12)                              /**< Digital to Analog Converter 0 Clock Enable */
#define _CMU_HFPERCLKEN0_VDAC0_SHIFT                      12                                         /**< Shift value for CMU_VDAC0 */
#define _CMU_HFPERCLKEN0_VDAC0_MASK                       0x1000UL                                   /**< Bit mask for CMU_VDAC0 */
#define _CMU_HFPERCLKEN0_VDAC0_DEFAULT                    0x00000000UL                               /**< Mode DEFAULT for CMU_HFPERCLKEN0 */
#define CMU_HFPERCLKEN0_VDAC0_DEFAULT                     (_CMU_HFPERCLKEN0_VDAC0_DEFAULT << 12)     /**< Shifted mode DEFAULT for CMU_HFPERCLKEN0 */
#define CMU_HFPERCLKEN0_CSEN                              (0x1UL << 13)                              /**< Capacitive touch sense module Clock Enable */
#define _CMU_HFPERCLKEN0_CSEN_SHIFT                       13                                         /**< Shift value for CMU_CSEN */
#define _CMU_HFPERCLKEN0_CSEN_MASK                        0x2000UL                                   /**< Bit mask for CMU_CSEN */
#define _CMU_HFPERCLKEN0_CSEN_DEFAULT                     0x00000000UL                               /**< Mode DEFAULT for CMU_HFPERCLKEN0 */
#define CMU_HFPERCLKEN0_CSEN_DEFAULT                      (_CMU_HFPERCLKEN0_CSEN_DEFAULT << 13)      /**< Shifted mode DEFAULT for CMU_HFPERCLKEN0 */
#define CMU_HFPERCLKEN0_IDAC0                             (0x1UL << 14)                              /**< Current Digital to Analog Converter 0 Clock Enable */
#define _CMU_HFPERCLKEN0_IDAC0_SHIFT                      14                                         /**< Shift value for CMU_IDAC0 */
#define _CMU_HFPERCLKEN0_IDAC0_MASK                       0x4000UL                                   /**< Bit mask for CMU_IDAC0 */
#define _CMU_HFPERCLKEN0_IDAC0_DEFAULT                    0x00000000UL                               /**< Mode DEFAULT for CMU_HFPERCLKEN0 */
#define CMU_HFPERCLKEN0_IDAC0_DEFAULT                     (_CMU_HFPERCLKEN0_IDAC0_DEFAULT << 14)     /**< Shifted mode DEFAULT for CMU_HFPERCLKEN0 */
#define CMU_HFPERCLKEN0_TRNG0                             (0x1UL << 15)                              /**< True Random Number Generator 0 Clock Enable */
#define _CMU_HFPERCLKEN0_TRNG0_SHIFT                      15                                         /**< Shift value for CMU_TRNG0 */
#define _CMU_HFPERCLKEN0_TRNG0_MASK                       0x8000UL                                   /**< Bit mask for CMU_TRNG0 */
#define _CMU_HFPERCLKEN0_TRNG0_DEFAULT                    0x00000000UL                               /**< Mode DEFAULT for CMU_HFPERCLKEN0 */
#define CMU_HFPERCLKEN0_TRNG0_DEFAULT                     (_CMU_HFPERCLKEN0_TRNG0_DEFAULT << 15)     /**< Shifted mode DEFAULT for CMU_HFPERCLKEN0 */

/* Bit fields for CMU LFACLKEN0 */
#define _CMU_LFACLKEN0_RESETVALUE                         0x00000000UL                           /**< Default value for CMU_LFACLKEN0 */
#define _CMU_LFACLKEN0_MASK                               0x00000003UL                           /**< Mask for CMU_LFACLKEN0 */
#define CMU_LFACLKEN0_LETIMER0                            (0x1UL << 0)                           /**< Low Energy Timer 0 Clock Enable */
#define _CMU_LFACLKEN0_LETIMER0_SHIFT                     0                                      /**< Shift value for CMU_LETIMER0 */
#define _CMU_LFACLKEN0_LETIMER0_MASK                      0x1UL                                  /**< Bit mask for CMU_LETIMER0 */
#define _CMU_LFACLKEN0_LETIMER0_DEFAULT                   0x00000000UL                           /**< Mode DEFAULT for CMU_LFACLKEN0 */
#define CMU_LFACLKEN0_LETIMER0_DEFAULT                    (_CMU_LFACLKEN0_LETIMER0_DEFAULT << 0) /**< Shifted mode DEFAULT for CMU_LFACLKEN0 */
#define CMU_LFACLKEN0_LESENSE                             (0x1UL << 1)                           /**< Low Energy Sensor Interface Clock Enable */
#define _CMU_LFACLKEN0_LESENSE_SHIFT                      1                                      /**< Shift value for CMU_LESENSE */
#define _CMU_LFACLKEN0_LESENSE_MASK                       0x2UL                                  /**< Bit mask for CMU_LESENSE */
#define _CMU_LFACLKEN0_LESENSE_DEFAULT                    0x00000000UL                           /**< Mode DEFAULT for CMU_LFACLKEN0 */
#define CMU_LFACLKEN0_LESENSE_DEFAULT                     (_CMU_LFACLKEN0_LESENSE_DEFAULT << 1)  /**< Shifted mode DEFAULT for CMU_LFACLKEN0 */

/* Bit fields for CMU LFBCLKEN0 */
#define _CMU_LFBCLKEN0_RESETVALUE                         0x00000000UL                          /**< Default value for CMU_LFBCLKEN0 */
#define _CMU_LFBCLKEN0_MASK                               0x00000007UL                          /**< Mask for CMU_LFBCLKEN0 */
#define CMU_LFBCLKEN0_SYSTICK                             (0x1UL << 0)                          /**<  Clock Enable */
#define _CMU_LFBCLKEN0_SYSTICK_SHIFT                      0                                     /**< Shift value for CMU_SYSTICK */
#define _CMU_LFBCLKEN0_SYSTICK_MASK                       0x1UL                                 /**< Bit mask for CMU_SYSTICK */
#define _CMU_LFBCLKEN0_SYSTICK_DEFAULT                    0x00000000UL                          /**< Mode DEFAULT for CMU_LFBCLKEN0 */
#define CMU_LFBCLKEN0_SYSTICK_DEFAULT                     (_CMU_LFBCLKEN0_SYSTICK_DEFAULT << 0) /**< Shifted mode DEFAULT for CMU_LFBCLKEN0 */
#define CMU_LFBCLKEN0_LEUART0                             (0x1UL << 1)                          /**< Low Energy UART 0 Clock Enable */
#define _CMU_LFBCLKEN0_LEUART0_SHIFT                      1                                     /**< Shift value for CMU_LEUART0 */
#define _CMU_LFBCLKEN0_LEUART0_MASK                       0x2UL                                 /**< Bit mask for CMU_LEUART0 */
#define _CMU_LFBCLKEN0_LEUART0_DEFAULT                    0x00000000UL                          /**< Mode DEFAULT for CMU_LFBCLKEN0 */
#define CMU_LFBCLKEN0_LEUART0_DEFAULT                     (_CMU_LFBCLKEN0_LEUART0_DEFAULT << 1) /**< Shifted mode DEFAULT for CMU_LFBCLKEN0 */
#define CMU_LFBCLKEN0_CSEN                                (0x1UL << 2)                          /**< Capacitive touch sense module Clock Enable */
#define _CMU_LFBCLKEN0_CSEN_SHIFT                         2                                     /**< Shift value for CMU_CSEN */
#define _CMU_LFBCLKEN0_CSEN_MASK                          0x4UL                                 /**< Bit mask for CMU_CSEN */
#define _CMU_LFBCLKEN0_CSEN_DEFAULT                       0x00000000UL                          /**< Mode DEFAULT for CMU_LFBCLKEN0 */
#define CMU_LFBCLKEN0_CSEN_DEFAULT                        (_CMU_LFBCLKEN0_CSEN_DEFAULT << 2)    /**< Shifted mode DEFAULT for CMU_LFBCLKEN0 */

/* Bit fields for CMU LFECLKEN0 */
#define _CMU_LFECLKEN0_RESETVALUE                         0x00000000UL                       /**< Default value for CMU_LFECLKEN0 */
#define _CMU_LFECLKEN0_MASK                               0x00000001UL                       /**< Mask for CMU_LFECLKEN0 */
#define CMU_LFECLKEN0_RTCC                                (0x1UL << 0)                       /**< Real-Time Counter and Calendar Clock Enable */
#define _CMU_LFECLKEN0_RTCC_SHIFT                         0                                  /**< Shift value for CMU_RTCC */
#define _CMU_LFECLKEN0_RTCC_MASK                          0x1UL                              /**< Bit mask for CMU_RTCC */
#define _CMU_LFECLKEN0_RTCC_DEFAULT                       0x00000000UL                       /**< Mode DEFAULT for CMU_LFECLKEN0 */
#define CMU_LFECLKEN0_RTCC_DEFAULT                        (_CMU_LFECLKEN0_RTCC_DEFAULT << 0) /**< Shifted mode DEFAULT for CMU_LFECLKEN0 */

/* Bit fields for CMU HFPRESC */
#define _CMU_HFPRESC_RESETVALUE                           0x00000000UL                              /**< Default value for CMU_HFPRESC */
#define _CMU_HFPRESC_MASK                                 0x01001F00UL                              /**< Mask for CMU_HFPRESC */
#define _CMU_HFPRESC_PRESC_SHIFT                          8                                         /**< Shift value for CMU_PRESC */
#define _CMU_HFPRESC_PRESC_MASK                           0x1F00UL                                  /**< Bit mask for CMU_PRESC */
#define _CMU_HFPRESC_PRESC_DEFAULT                        0x00000000UL                              /**< Mode DEFAULT for CMU_HFPRESC */
#define _CMU_HFPRESC_PRESC_NODIVISION                     0x00000000UL                              /**< Mode NODIVISION for CMU_HFPRESC */
#define CMU_HFPRESC_PRESC_DEFAULT                         (_CMU_HFPRESC_PRESC_DEFAULT << 8)         /**< Shifted mode DEFAULT for CMU_HFPRESC */
#define CMU_HFPRESC_PRESC_NODIVISION                      (_CMU_HFPRESC_PRESC_NODIVISION << 8)      /**< Shifted mode NODIVISION for CMU_HFPRESC */
#define _CMU_HFPRESC_HFCLKLEPRESC_SHIFT                   24                                        /**< Shift value for CMU_HFCLKLEPRESC */
#define _CMU_HFPRESC_HFCLKLEPRESC_MASK                    0x1000000UL                               /**< Bit mask for CMU_HFCLKLEPRESC */
#define _CMU_HFPRESC_HFCLKLEPRESC_DEFAULT                 0x00000000UL                              /**< Mode DEFAULT for CMU_HFPRESC */
#define _CMU_HFPRESC_HFCLKLEPRESC_DIV2                    0x00000000UL                              /**< Mode DIV2 for CMU_HFPRESC */
#define _CMU_HFPRESC_HFCLKLEPRESC_DIV4                    0x00000001UL                              /**< Mode DIV4 for CMU_HFPRESC */
#define CMU_HFPRESC_HFCLKLEPRESC_DEFAULT                  (_CMU_HFPRESC_HFCLKLEPRESC_DEFAULT << 24) /**< Shifted mode DEFAULT for CMU_HFPRESC */
#define CMU_HFPRESC_HFCLKLEPRESC_DIV2                     (_CMU_HFPRESC_HFCLKLEPRESC_DIV2 << 24)    /**< Shifted mode DIV2 for CMU_HFPRESC */
#define CMU_HFPRESC_HFCLKLEPRESC_DIV4                     (_CMU_HFPRESC_HFCLKLEPRESC_DIV4 << 24)    /**< Shifted mode DIV4 for CMU_HFPRESC */

/* Bit fields for CMU HFCOREPRESC */
#define _CMU_HFCOREPRESC_RESETVALUE                       0x00000000UL                             /**< Default value for CMU_HFCOREPRESC */
#define _CMU_HFCOREPRESC_MASK                             0x0001FF00UL                             /**< Mask for CMU_HFCOREPRESC */
#define _CMU_HFCOREPRESC_PRESC_SHIFT                      8                                        /**< Shift value for CMU_PRESC */
#define _CMU_HFCOREPRESC_PRESC_MASK                       0x1FF00UL                                /**< Bit mask for CMU_PRESC */
#define _CMU_HFCOREPRESC_PRESC_DEFAULT                    0x00000000UL                             /**< Mode DEFAULT for CMU_HFCOREPRESC */
#define _CMU_HFCOREPRESC_PRESC_NODIVISION                 0x00000000UL                             /**< Mode NODIVISION for CMU_HFCOREPRESC */
#define CMU_HFCOREPRESC_PRESC_DEFAULT                     (_CMU_HFCOREPRESC_PRESC_DEFAULT << 8)    /**< Shifted mode DEFAULT for CMU_HFCOREPRESC */
#define CMU_HFCOREPRESC_PRESC_NODIVISION                  (_CMU_HFCOREPRESC_PRESC_NODIVISION << 8) /**< Shifted mode NODIVISION for CMU_HFCOREPRESC */

/* Bit fields for CMU HFPERPRESC */
#define _CMU_HFPERPRESC_RESETVALUE                        0x00000000UL                            /**< Default value for CMU_HFPERPRESC */
#define _CMU_HFPERPRESC_MASK                              0x0001FF00UL                            /**< Mask for CMU_HFPERPRESC */
#define _CMU_HFPERPRESC_PRESC_SHIFT                       8                                       /**< Shift value for CMU_PRESC */
#define _CMU_HFPERPRESC_PRESC_MASK                        0x1FF00UL                               /**< Bit mask for CMU_PRESC */
#define _CMU_HFPERPRESC_PRESC_DEFAULT                     0x00000000UL                            /**< Mode DEFAULT for CMU_HFPERPRESC */
#define _CMU_HFPERPRESC_PRESC_NODIVISION                  0x00000000UL                            /**< Mode NODIVISION for CMU_HFPERPRESC */
#define CMU_HFPERPRESC_PRESC_DEFAULT                      (_CMU_HFPERPRESC_PRESC_DEFAULT << 8)    /**< Shifted mode DEFAULT for CMU_HFPERPRESC */
#define CMU_HFPERPRESC_PRESC_NODIVISION                   (_CMU_HFPERPRESC_PRESC_NODIVISION << 8) /**< Shifted mode NODIVISION for CMU_HFPERPRESC */

/* Bit fields for CMU HFEXPPRESC */
#define _CMU_HFEXPPRESC_RESETVALUE                        0x00000000UL                            /**< Default value for CMU_HFEXPPRESC */
#define _CMU_HFEXPPRESC_MASK                              0x00001F00UL                            /**< Mask for CMU_HFEXPPRESC */
#define _CMU_HFEXPPRESC_PRESC_SHIFT                       8                                       /**< Shift value for CMU_PRESC */
#define _CMU_HFEXPPRESC_PRESC_MASK                        0x1F00UL                                /**< Bit mask for CMU_PRESC */
#define _CMU_HFEXPPRESC_PRESC_DEFAULT                     0x00000000UL                            /**< Mode DEFAULT for CMU_HFEXPPRESC */
#define _CMU_HFEXPPRESC_PRESC_NODIVISION                  0x00000000UL                            /**< Mode NODIVISION for CMU_HFEXPPRESC */
#define CMU_HFEXPPRESC_PRESC_DEFAULT                      (_CMU_HFEXPPRESC_PRESC_DEFAULT << 8)    /**< Shifted mode DEFAULT for CMU_HFEXPPRESC */
#define CMU_HFEXPPRESC_PRESC_NODIVISION                   (_CMU_HFEXPPRESC_PRESC_NODIVISION << 8) /**< Shifted mode NODIVISION for CMU_HFEXPPRESC */

/* Bit fields for CMU LFAPRESC0 */
#define _CMU_LFAPRESC0_RESETVALUE                         0x00000000UL                            /**< Default value for CMU_LFAPRESC0 */
#define _CMU_LFAPRESC0_MASK                               0x0000003FUL                            /**< Mask for CMU_LFAPRESC0 */
#define _CMU_LFAPRESC0_LETIMER0_SHIFT                     0                                       /**< Shift value for CMU_LETIMER0 */
#define _CMU_LFAPRESC0_LETIMER0_MASK                      0xFUL                                   /**< Bit mask for CMU_LETIMER0 */
#define _CMU_LFAPRESC0_LETIMER0_DIV1                      0x00000000UL                            /**< Mode DIV1 for CMU_LFAPRESC0 */
#define _CMU_LFAPRESC0_LETIMER0_DIV2                      0x00000001UL                            /**< Mode DIV2 for CMU_LFAPRESC0 */
#define _CMU_LFAPRESC0_LETIMER0_DIV4                      0x00000002UL                            /**< Mode DIV4 for CMU_LFAPRESC0 */
#define _CMU_LFAPRESC0_LETIMER0_DIV8                      0x00000003UL                            /**< Mode DIV8 for CMU_LFAPRESC0 */
#define _CMU_LFAPRESC0_LETIMER0_DIV16                     0x00000004UL                            /**< Mode DIV16 for CMU_LFAPRESC0 */
#define _CMU_LFAPRESC0_LETIMER0_DIV32                     0x00000005UL                            /**< Mode DIV32 for CMU_LFAPRESC0 */
#define _CMU_LFAPRESC0_LETIMER0_DIV64                     0x00000006UL                            /**< Mode DIV64 for CMU_LFAPRESC0 */
#define _CMU_LFAPRESC0_LETIMER0_DIV128                    0x00000007UL                            /**< Mode DIV128 for CMU_LFAPRESC0 */
#define _CMU_LFAPRESC0_LETIMER0_DIV256                    0x00000008UL                            /**< Mode DIV256 for CMU_LFAPRESC0 */
#define _CMU_LFAPRESC0_LETIMER0_DIV512                    0x00000009UL                            /**< Mode DIV512 for CMU_LFAPRESC0 */
#define _CMU_LFAPRESC0_LETIMER0_DIV1024                   0x0000000AUL                            /**< Mode DIV1024 for CMU_LFAPRESC0 */
#define _CMU_LFAPRESC0_LETIMER0_DIV2048                   0x0000000BUL                            /**< Mode DIV2048 for CMU_LFAPRESC0 */
#define _CMU_LFAPRESC0_LETIMER0_DIV4096                   0x0000000CUL                            /**< Mode DIV4096 for CMU_LFAPRESC0 */
#define _CMU_LFAPRESC0_LETIMER0_DIV8192                   0x0000000DUL                            /**< Mode DIV8192 for CMU_LFAPRESC0 */
#define _CMU_LFAPRESC0_LETIMER0_DIV16384                  0x0000000EUL                            /**< Mode DIV16384 for CMU_LFAPRESC0 */
#define _CMU_LFAPRESC0_LETIMER0_DIV32768                  0x0000000FUL                            /**< Mode DIV32768 for CMU_LFAPRESC0 */
#define CMU_LFAPRESC0_LETIMER0_DIV1                       (_CMU_LFAPRESC0_LETIMER0_DIV1 << 0)     /**< Shifted mode DIV1 for CMU_LFAPRESC0 */
#define CMU_LFAPRESC0_LETIMER0_DIV2                       (_CMU_LFAPRESC0_LETIMER0_DIV2 << 0)     /**< Shifted mode DIV2 for CMU_LFAPRESC0 */
#define CMU_LFAPRESC0_LETIMER0_DIV4                       (_CMU_LFAPRESC0_LETIMER0_DIV4 << 0)     /**< Shifted mode DIV4 for CMU_LFAPRESC0 */
#define CMU_LFAPRESC0_LETIMER0_DIV8                       (_CMU_LFAPRESC0_LETIMER0_DIV8 << 0)     /**< Shifted mode DIV8 for CMU_LFAPRESC0 */
#define CMU_LFAPRESC0_LETIMER0_DIV16                      (_CMU_LFAPRESC0_LETIMER0_DIV16 << 0)    /**< Shifted mode DIV16 for CMU_LFAPRESC0 */
#define CMU_LFAPRESC0_LETIMER0_DIV32                      (_CMU_LFAPRESC0_LETIMER0_DIV32 << 0)    /**< Shifted mode DIV32 for CMU_LFAPRESC0 */
#define CMU_LFAPRESC0_LETIMER0_DIV64                      (_CMU_LFAPRESC0_LETIMER0_DIV64 << 0)    /**< Shifted mode DIV64 for CMU_LFAPRESC0 */
#define CMU_LFAPRESC0_LETIMER0_DIV128                     (_CMU_LFAPRESC0_LETIMER0_DIV128 << 0)   /**< Shifted mode DIV128 for CMU_LFAPRESC0 */
#define CMU_LFAPRESC0_LETIMER0_DIV256                     (_CMU_LFAPRESC0_LETIMER0_DIV256 << 0)   /**< Shifted mode DIV256 for CMU_LFAPRESC0 */
#define CMU_LFAPRESC0_LETIMER0_DIV512                     (_CMU_LFAPRESC0_LETIMER0_DIV512 << 0)   /**< Shifted mode DIV512 for CMU_LFAPRESC0 */
#define CMU_LFAPRESC0_LETIMER0_DIV1024                    (_CMU_LFAPRESC0_LETIMER0_DIV1024 << 0)  /**< Shifted mode DIV1024 for CMU_LFAPRESC0 */
#define CMU_LFAPRESC0_LETIMER0_DIV2048                    (_CMU_LFAPRESC0_LETIMER0_DIV2048 << 0)  /**< Shifted mode DIV2048 for CMU_LFAPRESC0 */
#define CMU_LFAPRESC0_LETIMER0_DIV4096                    (_CMU_LFAPRESC0_LETIMER0_DIV4096 << 0)  /**< Shifted mode DIV4096 for CMU_LFAPRESC0 */
#define CMU_LFAPRESC0_LETIMER0_DIV8192                    (_CMU_LFAPRESC0_LETIMER0_DIV8192 << 0)  /**< Shifted mode DIV8192 for CMU_LFAPRESC0 */
#define CMU_LFAPRESC0_LETIMER0_DIV16384                   (_CMU_LFAPRESC0_LETIMER0_DIV16384 << 0) /**< Shifted mode DIV16384 for CMU_LFAPRESC0 */
#define CMU_LFAPRESC0_LETIMER0_DIV32768                   (_CMU_LFAPRESC0_LETIMER0_DIV32768 << 0) /**< Shifted mode DIV32768 for CMU_LFAPRESC0 */
#define _CMU_LFAPRESC0_LESENSE_SHIFT                      4                                       /**< Shift value for CMU_LESENSE */
#define _CMU_LFAPRESC0_LESENSE_MASK                       0x30UL                                  /**< Bit mask for CMU_LESENSE */
#define _CMU_LFAPRESC0_LESENSE_DIV1                       0x00000000UL                            /**< Mode DIV1 for CMU_LFAPRESC0 */
#define _CMU_LFAPRESC0_LESENSE_DIV2                       0x00000001UL                            /**< Mode DIV2 for CMU_LFAPRESC0 */
#define _CMU_LFAPRESC0_LESENSE_DIV4                       0x00000002UL                            /**< Mode DIV4 for CMU_LFAPRESC0 */
#define _CMU_LFAPRESC0_LESENSE_DIV8                       0x00000003UL                            /**< Mode DIV8 for CMU_LFAPRESC0 */
#define CMU_LFAPRESC0_LESENSE_DIV1                        (_CMU_LFAPRESC0_LESENSE_DIV1 << 4)      /**< Shifted mode DIV1 for CMU_LFAPRESC0 */
#define CMU_LFAPRESC0_LESENSE_DIV2                        (_CMU_LFAPRESC0_LESENSE_DIV2 << 4)      /**< Shifted mode DIV2 for CMU_LFAPRESC0 */
#define CMU_LFAPRESC0_LESENSE_DIV4                        (_CMU_LFAPRESC0_LESENSE_DIV4 << 4)      /**< Shifted mode DIV4 for CMU_LFAPRESC0 */
#define CMU_LFAPRESC0_LESENSE_DIV8                        (_CMU_LFAPRESC0_LESENSE_DIV8 << 4)      /**< Shifted mode DIV8 for CMU_LFAPRESC0 */

/* Bit fields for CMU LFBPRESC0 */
#define _CMU_LFBPRESC0_RESETVALUE                         0x00000000UL                       /**< Default value for CMU_LFBPRESC0 */
#define _CMU_LFBPRESC0_MASK                               0x0000033FUL                       /**< Mask for CMU_LFBPRESC0 */
#define _CMU_LFBPRESC0_SYSTICK_SHIFT                      0                                  /**< Shift value for CMU_SYSTICK */
#define _CMU_LFBPRESC0_SYSTICK_MASK                       0xFUL                              /**< Bit mask for CMU_SYSTICK */
#define _CMU_LFBPRESC0_SYSTICK_DIV1                       0x00000000UL                       /**< Mode DIV1 for CMU_LFBPRESC0 */
#define CMU_LFBPRESC0_SYSTICK_DIV1                        (_CMU_LFBPRESC0_SYSTICK_DIV1 << 0) /**< Shifted mode DIV1 for CMU_LFBPRESC0 */
#define _CMU_LFBPRESC0_LEUART0_SHIFT                      4                                  /**< Shift value for CMU_LEUART0 */
#define _CMU_LFBPRESC0_LEUART0_MASK                       0x30UL                             /**< Bit mask for CMU_LEUART0 */
#define _CMU_LFBPRESC0_LEUART0_DIV1                       0x00000000UL                       /**< Mode DIV1 for CMU_LFBPRESC0 */
#define _CMU_LFBPRESC0_LEUART0_DIV2                       0x00000001UL                       /**< Mode DIV2 for CMU_LFBPRESC0 */
#define _CMU_LFBPRESC0_LEUART0_DIV4                       0x00000002UL                       /**< Mode DIV4 for CMU_LFBPRESC0 */
#define _CMU_LFBPRESC0_LEUART0_DIV8                       0x00000003UL                       /**< Mode DIV8 for CMU_LFBPRESC0 */
#define CMU_LFBPRESC0_LEUART0_DIV1                        (_CMU_LFBPRESC0_LEUART0_DIV1 << 4) /**< Shifted mode DIV1 for CMU_LFBPRESC0 */
#define CMU_LFBPRESC0_LEUART0_DIV2                        (_CMU_LFBPRESC0_LEUART0_DIV2 << 4) /**< Shifted mode DIV2 for CMU_LFBPRESC0 */
#define CMU_LFBPRESC0_LEUART0_DIV4                        (_CMU_LFBPRESC0_LEUART0_DIV4 << 4) /**< Shifted mode DIV4 for CMU_LFBPRESC0 */
#define CMU_LFBPRESC0_LEUART0_DIV8                        (_CMU_LFBPRESC0_LEUART0_DIV8 << 4) /**< Shifted mode DIV8 for CMU_LFBPRESC0 */
#define _CMU_LFBPRESC0_CSEN_SHIFT                         8                                  /**< Shift value for CMU_CSEN */
#define _CMU_LFBPRESC0_CSEN_MASK                          0x300UL                            /**< Bit mask for CMU_CSEN */
#define _CMU_LFBPRESC0_CSEN_DIV16                         0x00000000UL                       /**< Mode DIV16 for CMU_LFBPRESC0 */
#define _CMU_LFBPRESC0_CSEN_DIV32                         0x00000001UL                       /**< Mode DIV32 for CMU_LFBPRESC0 */
#define _CMU_LFBPRESC0_CSEN_DIV64                         0x00000002UL                       /**< Mode DIV64 for CMU_LFBPRESC0 */
#define _CMU_LFBPRESC0_CSEN_DIV128                        0x00000003UL                       /**< Mode DIV128 for CMU_LFBPRESC0 */
#define CMU_LFBPRESC0_CSEN_DIV16                          (_CMU_LFBPRESC0_CSEN_DIV16 << 8)   /**< Shifted mode DIV16 for CMU_LFBPRESC0 */
#define CMU_LFBPRESC0_CSEN_DIV32                          (_CMU_LFBPRESC0_CSEN_DIV32 << 8)   /**< Shifted mode DIV32 for CMU_LFBPRESC0 */
#define CMU_LFBPRESC0_CSEN_DIV64                          (_CMU_LFBPRESC0_CSEN_DIV64 << 8)   /**< Shifted mode DIV64 for CMU_LFBPRESC0 */
#define CMU_LFBPRESC0_CSEN_DIV128                         (_CMU_LFBPRESC0_CSEN_DIV128 << 8)  /**< Shifted mode DIV128 for CMU_LFBPRESC0 */

/* Bit fields for CMU LFEPRESC0 */
#define _CMU_LFEPRESC0_RESETVALUE                         0x00000000UL                    /**< Default value for CMU_LFEPRESC0 */
#define _CMU_LFEPRESC0_MASK                               0x00000003UL                    /**< Mask for CMU_LFEPRESC0 */
#define _CMU_LFEPRESC0_RTCC_SHIFT                         0                               /**< Shift value for CMU_RTCC */
#define _CMU_LFEPRESC0_RTCC_MASK                          0x3UL                           /**< Bit mask for CMU_RTCC */
#define _CMU_LFEPRESC0_RTCC_DIV1                          0x00000000UL                    /**< Mode DIV1 for CMU_LFEPRESC0 */
#define _CMU_LFEPRESC0_RTCC_DIV2                          0x00000001UL                    /**< Mode DIV2 for CMU_LFEPRESC0 */
#define _CMU_LFEPRESC0_RTCC_DIV4                          0x00000002UL                    /**< Mode DIV4 for CMU_LFEPRESC0 */
#define CMU_LFEPRESC0_RTCC_DIV1                           (_CMU_LFEPRESC0_RTCC_DIV1 << 0) /**< Shifted mode DIV1 for CMU_LFEPRESC0 */
#define CMU_LFEPRESC0_RTCC_DIV2                           (_CMU_LFEPRESC0_RTCC_DIV2 << 0) /**< Shifted mode DIV2 for CMU_LFEPRESC0 */
#define CMU_LFEPRESC0_RTCC_DIV4                           (_CMU_LFEPRESC0_RTCC_DIV4 << 0) /**< Shifted mode DIV4 for CMU_LFEPRESC0 */

/* Bit fields for CMU SYNCBUSY */
#define _CMU_SYNCBUSY_RESETVALUE                          0x00000000UL                               /**< Default value for CMU_SYNCBUSY */
#define _CMU_SYNCBUSY_MASK                                0x3F050055UL                               /**< Mask for CMU_SYNCBUSY */
#define CMU_SYNCBUSY_LFACLKEN0                            (0x1UL << 0)                               /**< Low Frequency a Clock Enable 0 Busy */
#define _CMU_SYNCBUSY_LFACLKEN0_SHIFT                     0                                          /**< Shift value for CMU_LFACLKEN0 */
#define _CMU_SYNCBUSY_LFACLKEN0_MASK                      0x1UL                                      /**< Bit mask for CMU_LFACLKEN0 */
#define _CMU_SYNCBUSY_LFACLKEN0_DEFAULT                   0x00000000UL                               /**< Mode DEFAULT for CMU_SYNCBUSY */
#define CMU_SYNCBUSY_LFACLKEN0_DEFAULT                    (_CMU_SYNCBUSY_LFACLKEN0_DEFAULT << 0)     /**< Shifted mode DEFAULT for CMU_SYNCBUSY */
#define CMU_SYNCBUSY_LFAPRESC0                            (0x1UL << 2)                               /**< Low Frequency a Prescaler 0 Busy */
#define _CMU_SYNCBUSY_LFAPRESC0_SHIFT                     2                                          /**< Shift value for CMU_LFAPRESC0 */
#define _CMU_SYNCBUSY_LFAPRESC0_MASK                      0x4UL                                      /**< Bit mask for CMU_LFAPRESC0 */
#define _CMU_SYNCBUSY_LFAPRESC0_DEFAULT                   0x00000000UL                               /**< Mode DEFAULT for CMU_SYNCBUSY */
#define CMU_SYNCBUSY_LFAPRESC0_DEFAULT                    (_CMU_SYNCBUSY_LFAPRESC0_DEFAULT << 2)     /**< Shifted mode DEFAULT for CMU_SYNCBUSY */
#define CMU_SYNCBUSY_LFBCLKEN0                            (0x1UL << 4)                               /**< Low Frequency B Clock Enable 0 Busy */
#define _CMU_SYNCBUSY_LFBCLKEN0_SHIFT                     4                                          /**< Shift value for CMU_LFBCLKEN0 */
#define _CMU_SYNCBUSY_LFBCLKEN0_MASK                      0x10UL                                     /**< Bit mask for CMU_LFBCLKEN0 */
#define _CMU_SYNCBUSY_LFBCLKEN0_DEFAULT                   0x00000000UL                               /**< Mode DEFAULT for CMU_SYNCBUSY */
#define CMU_SYNCBUSY_LFBCLKEN0_DEFAULT                    (_CMU_SYNCBUSY_LFBCLKEN0_DEFAULT << 4)     /**< Shifted mode DEFAULT for CMU_SYNCBUSY */
#define CMU_SYNCBUSY_LFBPRESC0                            (0x1UL << 6)                               /**< Low Frequency B Prescaler 0 Busy */
#define _CMU_SYNCBUSY_LFBPRESC0_SHIFT                     6                                          /**< Shift value for CMU_LFBPRESC0 */
#define _CMU_SYNCBUSY_LFBPRESC0_MASK                      0x40UL                                     /**< Bit mask for CMU_LFBPRESC0 */
#define _CMU_SYNCBUSY_LFBPRESC0_DEFAULT                   0x00000000UL                               /**< Mode DEFAULT for CMU_SYNCBUSY */
#define CMU_SYNCBUSY_LFBPRESC0_DEFAULT                    (_CMU_SYNCBUSY_LFBPRESC0_DEFAULT << 6)     /**< Shifted mode DEFAULT for CMU_SYNCBUSY */
#define CMU_SYNCBUSY_LFECLKEN0                            (0x1UL << 16)                              /**< Low Frequency E Clock Enable 0 Busy */
#define _CMU_SYNCBUSY_LFECLKEN0_SHIFT                     16                                         /**< Shift value for CMU_LFECLKEN0 */
#define _CMU_SYNCBUSY_LFECLKEN0_MASK                      0x10000UL                                  /**< Bit mask for CMU_LFECLKEN0 */
#define _CMU_SYNCBUSY_LFECLKEN0_DEFAULT                   0x00000000UL                               /**< Mode DEFAULT for CMU_SYNCBUSY */
#define CMU_SYNCBUSY_LFECLKEN0_DEFAULT                    (_CMU_SYNCBUSY_LFECLKEN0_DEFAULT << 16)    /**< Shifted mode DEFAULT for CMU_SYNCBUSY */
#define CMU_SYNCBUSY_LFEPRESC0                            (0x1UL << 18)                              /**< Low Frequency E Prescaler 0 Busy */
#define _CMU_SYNCBUSY_LFEPRESC0_SHIFT                     18                                         /**< Shift value for CMU_LFEPRESC0 */
#define _CMU_SYNCBUSY_LFEPRESC0_MASK                      0x40000UL                                  /**< Bit mask for CMU_LFEPRESC0 */
#define _CMU_SYNCBUSY_LFEPRESC0_DEFAULT                   0x00000000UL                               /**< Mode DEFAULT for CMU_SYNCBUSY */
#define CMU_SYNCBUSY_LFEPRESC0_DEFAULT                    (_CMU_SYNCBUSY_LFEPRESC0_DEFAULT << 18)    /**< Shifted mode DEFAULT for CMU_SYNCBUSY */
#define CMU_SYNCBUSY_HFRCOBSY                             (0x1UL << 24)                              /**< HFRCO Busy */
#define _CMU_SYNCBUSY_HFRCOBSY_SHIFT                      24                                         /**< Shift value for CMU_HFRCOBSY */
#define _CMU_SYNCBUSY_HFRCOBSY_MASK                       0x1000000UL                                /**< Bit mask for CMU_HFRCOBSY */
#define _CMU_SYNCBUSY_HFRCOBSY_DEFAULT                    0x00000000UL                               /**< Mode DEFAULT for CMU_SYNCBUSY */
#define CMU_SYNCBUSY_HFRCOBSY_DEFAULT                     (_CMU_SYNCBUSY_HFRCOBSY_DEFAULT << 24)     /**< Shifted mode DEFAULT for CMU_SYNCBUSY */
#define CMU_SYNCBUSY_AUXHFRCOBSY                          (0x1UL << 25)                              /**< AUXHFRCO Busy */
#define _CMU_SYNCBUSY_AUXHFRCOBSY_SHIFT                   25                                         /**< Shift value for CMU_AUXHFRCOBSY */
#define _CMU_SYNCBUSY_AUXHFRCOBSY_MASK                    0x2000000UL                                /**< Bit mask for CMU_AUXHFRCOBSY */
#define _CMU_SYNCBUSY_AUXHFRCOBSY_DEFAULT                 0x00000000UL                               /**< Mode DEFAULT for CMU_SYNCBUSY */
#define CMU_SYNCBUSY_AUXHFRCOBSY_DEFAULT                  (_CMU_SYNCBUSY_AUXHFRCOBSY_DEFAULT << 25)  /**< Shifted mode DEFAULT for CMU_SYNCBUSY */
#define CMU_SYNCBUSY_LFRCOBSY                             (0x1UL << 26)                              /**< LFRCO Busy */
#define _CMU_SYNCBUSY_LFRCOBSY_SHIFT                      26                                         /**< Shift value for CMU_LFRCOBSY */
#define _CMU_SYNCBUSY_LFRCOBSY_MASK                       0x4000000UL                                /**< Bit mask for CMU_LFRCOBSY */
#define _CMU_SYNCBUSY_LFRCOBSY_DEFAULT                    0x00000000UL                               /**< Mode DEFAULT for CMU_SYNCBUSY */
#define CMU_SYNCBUSY_LFRCOBSY_DEFAULT                     (_CMU_SYNCBUSY_LFRCOBSY_DEFAULT << 26)     /**< Shifted mode DEFAULT for CMU_SYNCBUSY */
#define CMU_SYNCBUSY_LFRCOVREFBSY                         (0x1UL << 27)                              /**< LFRCO VREF Busy */
#define _CMU_SYNCBUSY_LFRCOVREFBSY_SHIFT                  27                                         /**< Shift value for CMU_LFRCOVREFBSY */
#define _CMU_SYNCBUSY_LFRCOVREFBSY_MASK                   0x8000000UL                                /**< Bit mask for CMU_LFRCOVREFBSY */
#define _CMU_SYNCBUSY_LFRCOVREFBSY_DEFAULT                0x00000000UL                               /**< Mode DEFAULT for CMU_SYNCBUSY */
#define CMU_SYNCBUSY_LFRCOVREFBSY_DEFAULT                 (_CMU_SYNCBUSY_LFRCOVREFBSY_DEFAULT << 27) /**< Shifted mode DEFAULT for CMU_SYNCBUSY */
#define CMU_SYNCBUSY_HFXOBSY                              (0x1UL << 28)                              /**< HFXO Busy */
#define _CMU_SYNCBUSY_HFXOBSY_SHIFT                       28                                         /**< Shift value for CMU_HFXOBSY */
#define _CMU_SYNCBUSY_HFXOBSY_MASK                        0x10000000UL                               /**< Bit mask for CMU_HFXOBSY */
#define _CMU_SYNCBUSY_HFXOBSY_DEFAULT                     0x00000000UL                               /**< Mode DEFAULT for CMU_SYNCBUSY */
#define CMU_SYNCBUSY_HFXOBSY_DEFAULT                      (_CMU_SYNCBUSY_HFXOBSY_DEFAULT << 28)      /**< Shifted mode DEFAULT for CMU_SYNCBUSY */
#define CMU_SYNCBUSY_LFXOBSY                              (0x1UL << 29)                              /**< LFXO Busy */
#define _CMU_SYNCBUSY_LFXOBSY_SHIFT                       29                                         /**< Shift value for CMU_LFXOBSY */
#define _CMU_SYNCBUSY_LFXOBSY_MASK                        0x20000000UL                               /**< Bit mask for CMU_LFXOBSY */
#define _CMU_SYNCBUSY_LFXOBSY_DEFAULT                     0x00000000UL                               /**< Mode DEFAULT for CMU_SYNCBUSY */
#define CMU_SYNCBUSY_LFXOBSY_DEFAULT                      (_CMU_SYNCBUSY_LFXOBSY_DEFAULT << 29)      /**< Shifted mode DEFAULT for CMU_SYNCBUSY */

/* Bit fields for CMU FREEZE */
#define _CMU_FREEZE_RESETVALUE                            0x00000000UL                         /**< Default value for CMU_FREEZE */
#define _CMU_FREEZE_MASK                                  0x00000001UL                         /**< Mask for CMU_FREEZE */
#define CMU_FREEZE_REGFREEZE                              (0x1UL << 0)                         /**< Register Update Freeze */
#define _CMU_FREEZE_REGFREEZE_SHIFT                       0                                    /**< Shift value for CMU_REGFREEZE */
#define _CMU_FREEZE_REGFREEZE_MASK                        0x1UL                                /**< Bit mask for CMU_REGFREEZE */
#define _CMU_FREEZE_REGFREEZE_DEFAULT                     0x00000000UL                         /**< Mode DEFAULT for CMU_FREEZE */
#define _CMU_FREEZE_REGFREEZE_UPDATE                      0x00000000UL                         /**< Mode UPDATE for CMU_FREEZE */
#define _CMU_FREEZE_REGFREEZE_FREEZE                      0x00000001UL                         /**< Mode FREEZE for CMU_FREEZE */
#define CMU_FREEZE_REGFREEZE_DEFAULT                      (_CMU_FREEZE_REGFREEZE_DEFAULT << 0) /**< Shifted mode DEFAULT for CMU_FREEZE */
#define CMU_FREEZE_REGFREEZE_UPDATE                       (_CMU_FREEZE_REGFREEZE_UPDATE << 0)  /**< Shifted mode UPDATE for CMU_FREEZE */
#define CMU_FREEZE_REGFREEZE_FREEZE                       (_CMU_FREEZE_REGFREEZE_FREEZE << 0)  /**< Shifted mode FREEZE for CMU_FREEZE */

/* Bit fields for CMU PCNTCTRL */
#define _CMU_PCNTCTRL_RESETVALUE                          0x00000000UL                             /**< Default value for CMU_PCNTCTRL */
#define _CMU_PCNTCTRL_MASK                                0x00000003UL                             /**< Mask for CMU_PCNTCTRL */
#define CMU_PCNTCTRL_PCNT0CLKEN                           (0x1UL << 0)                             /**< PCNT0 Clock Enable */
#define _CMU_PCNTCTRL_PCNT0CLKEN_SHIFT                    0                                        /**< Shift value for CMU_PCNT0CLKEN */
#define _CMU_PCNTCTRL_PCNT0CLKEN_MASK                     0x1UL                                    /**< Bit mask for CMU_PCNT0CLKEN */
#define _CMU_PCNTCTRL_PCNT0CLKEN_DEFAULT                  0x00000000UL                             /**< Mode DEFAULT for CMU_PCNTCTRL */
#define CMU_PCNTCTRL_PCNT0CLKEN_DEFAULT                   (_CMU_PCNTCTRL_PCNT0CLKEN_DEFAULT << 0)  /**< Shifted mode DEFAULT for CMU_PCNTCTRL */
#define CMU_PCNTCTRL_PCNT0CLKSEL                          (0x1UL << 1)                             /**< PCNT0 Clock Select */
#define _CMU_PCNTCTRL_PCNT0CLKSEL_SHIFT                   1                                        /**< Shift value for CMU_PCNT0CLKSEL */
#define _CMU_PCNTCTRL_PCNT0CLKSEL_MASK                    0x2UL                                    /**< Bit mask for CMU_PCNT0CLKSEL */
#define _CMU_PCNTCTRL_PCNT0CLKSEL_DEFAULT                 0x00000000UL                             /**< Mode DEFAULT for CMU_PCNTCTRL */
#define _CMU_PCNTCTRL_PCNT0CLKSEL_LFACLK                  0x00000000UL                             /**< Mode LFACLK for CMU_PCNTCTRL */
#define _CMU_PCNTCTRL_PCNT0CLKSEL_PCNT0S0                 0x00000001UL                             /**< Mode PCNT0S0 for CMU_PCNTCTRL */
#define CMU_PCNTCTRL_PCNT0CLKSEL_DEFAULT                  (_CMU_PCNTCTRL_PCNT0CLKSEL_DEFAULT << 1) /**< Shifted mode DEFAULT for CMU_PCNTCTRL */
#define CMU_PCNTCTRL_PCNT0CLKSEL_LFACLK                   (_CMU_PCNTCTRL_PCNT0CLKSEL_LFACLK << 1)  /**< Shifted mode LFACLK for CMU_PCNTCTRL */
#define CMU_PCNTCTRL_PCNT0CLKSEL_PCNT0S0                  (_CMU_PCNTCTRL_PCNT0CLKSEL_PCNT0S0 << 1) /**< Shifted mode PCNT0S0 for CMU_PCNTCTRL */

/* Bit fields for CMU ADCCTRL */
#define _CMU_ADCCTRL_RESETVALUE                           0x00000000UL                            /**< Default value for CMU_ADCCTRL */
#define _CMU_ADCCTRL_MASK                                 0x00000130UL                            /**< Mask for CMU_ADCCTRL */
#define _CMU_ADCCTRL_ADC0CLKSEL_SHIFT                     4                                       /**< Shift value for CMU_ADC0CLKSEL */
#define _CMU_ADCCTRL_ADC0CLKSEL_MASK                      0x30UL                                  /**< Bit mask for CMU_ADC0CLKSEL */
#define _CMU_ADCCTRL_ADC0CLKSEL_DEFAULT                   0x00000000UL                            /**< Mode DEFAULT for CMU_ADCCTRL */
#define _CMU_ADCCTRL_ADC0CLKSEL_DISABLED                  0x00000000UL                            /**< Mode DISABLED for CMU_ADCCTRL */
#define _CMU_ADCCTRL_ADC0CLKSEL_AUXHFRCO                  0x00000001UL                            /**< Mode AUXHFRCO for CMU_ADCCTRL */
#define _CMU_ADCCTRL_ADC0CLKSEL_HFXO                      0x00000002UL                            /**< Mode HFXO for CMU_ADCCTRL */
#define _CMU_ADCCTRL_ADC0CLKSEL_HFSRCCLK                  0x00000003UL                            /**< Mode HFSRCCLK for CMU_ADCCTRL */
#define CMU_ADCCTRL_ADC0CLKSEL_DEFAULT                    (_CMU_ADCCTRL_ADC0CLKSEL_DEFAULT << 4)  /**< Shifted mode DEFAULT for CMU_ADCCTRL */
#define CMU_ADCCTRL_ADC0CLKSEL_DISABLED                   (_CMU_ADCCTRL_ADC0CLKSEL_DISABLED << 4) /**< Shifted mode DISABLED for CMU_ADCCTRL */
#define CMU_ADCCTRL_ADC0CLKSEL_AUXHFRCO                   (_CMU_ADCCTRL_ADC0CLKSEL_AUXHFRCO << 4) /**< Shifted mode AUXHFRCO for CMU_ADCCTRL */
#define CMU_ADCCTRL_ADC0CLKSEL_HFXO                       (_CMU_ADCCTRL_ADC0CLKSEL_HFXO << 4)     /**< Shifted mode HFXO for CMU_ADCCTRL */
#define CMU_ADCCTRL_ADC0CLKSEL_HFSRCCLK                   (_CMU_ADCCTRL_ADC0CLKSEL_HFSRCCLK << 4) /**< Shifted mode HFSRCCLK for CMU_ADCCTRL */
#define CMU_ADCCTRL_ADC0CLKINV                            (0x1UL << 8)                            /**< Invert Clock Selected By ADC0CLKSEL */
#define _CMU_ADCCTRL_ADC0CLKINV_SHIFT                     8                                       /**< Shift value for CMU_ADC0CLKINV */
#define _CMU_ADCCTRL_ADC0CLKINV_MASK                      0x100UL                                 /**< Bit mask for CMU_ADC0CLKINV */
#define _CMU_ADCCTRL_ADC0CLKINV_DEFAULT                   0x00000000UL                            /**< Mode DEFAULT for CMU_ADCCTRL */
#define CMU_ADCCTRL_ADC0CLKINV_DEFAULT                    (_CMU_ADCCTRL_ADC0CLKINV_DEFAULT << 8)  /**< Shifted mode DEFAULT for CMU_ADCCTRL */

/* Bit fields for CMU ROUTEPEN */
#define _CMU_ROUTEPEN_RESETVALUE                          0x00000000UL                            /**< Default value for CMU_ROUTEPEN */
#define _CMU_ROUTEPEN_MASK                                0x10000003UL                            /**< Mask for CMU_ROUTEPEN */
#define CMU_ROUTEPEN_CLKOUT0PEN                           (0x1UL << 0)                            /**< CLKOUT0 Pin Enable */
#define _CMU_ROUTEPEN_CLKOUT0PEN_SHIFT                    0                                       /**< Shift value for CMU_CLKOUT0PEN */
#define _CMU_ROUTEPEN_CLKOUT0PEN_MASK                     0x1UL                                   /**< Bit mask for CMU_CLKOUT0PEN */
#define _CMU_ROUTEPEN_CLKOUT0PEN_DEFAULT                  0x00000000UL                            /**< Mode DEFAULT for CMU_ROUTEPEN */
#define CMU_ROUTEPEN_CLKOUT0PEN_DEFAULT                   (_CMU_ROUTEPEN_CLKOUT0PEN_DEFAULT << 0) /**< Shifted mode DEFAULT for CMU_ROUTEPEN */
#define CMU_ROUTEPEN_CLKOUT1PEN                           (0x1UL << 1)                            /**< CLKOUT1 Pin Enable */
#define _CMU_ROUTEPEN_CLKOUT1PEN_SHIFT                    1                                       /**< Shift value for CMU_CLKOUT1PEN */
#define _CMU_ROUTEPEN_CLKOUT1PEN_MASK                     0x2UL                                   /**< Bit mask for CMU_CLKOUT1PEN */
#define _CMU_ROUTEPEN_CLKOUT1PEN_DEFAULT                  0x00000000UL                            /**< Mode DEFAULT for CMU_ROUTEPEN */
#define CMU_ROUTEPEN_CLKOUT1PEN_DEFAULT                   (_CMU_ROUTEPEN_CLKOUT1PEN_DEFAULT << 1) /**< Shifted mode DEFAULT for CMU_ROUTEPEN */
#define CMU_ROUTEPEN_CLKIN0PEN                            (0x1UL << 28)                           /**< CLKIN0 Pin Enable */
#define _CMU_ROUTEPEN_CLKIN0PEN_SHIFT                     28                                      /**< Shift value for CMU_CLKIN0PEN */
#define _CMU_ROUTEPEN_CLKIN0PEN_MASK                      0x10000000UL                            /**< Bit mask for CMU_CLKIN0PEN */
#define _CMU_ROUTEPEN_CLKIN0PEN_DEFAULT                   0x00000000UL                            /**< Mode DEFAULT for CMU_ROUTEPEN */
#define CMU_ROUTEPEN_CLKIN0PEN_DEFAULT                    (_CMU_ROUTEPEN_CLKIN0PEN_DEFAULT << 28) /**< Shifted mode DEFAULT for CMU_ROUTEPEN */

/* Bit fields for CMU ROUTELOC0 */
#define _CMU_ROUTELOC0_RESETVALUE                         0x00000000UL                             /**< Default value for CMU_ROUTELOC0 */
#define _CMU_ROUTELOC0_MASK                               0x00000707UL                             /**< Mask for CMU_ROUTELOC0 */
#define _CMU_ROUTELOC0_CLKOUT0LOC_SHIFT                   0                                        /**< Shift value for CMU_CLKOUT0LOC */
#define _CMU_ROUTELOC0_CLKOUT0LOC_MASK                    0x7UL                                    /**< Bit mask for CMU_CLKOUT0LOC */
#define _CMU_ROUTELOC0_CLKOUT0LOC_LOC0                    0x00000000UL                             /**< Mode LOC0 for CMU_ROUTELOC0 */
#define _CMU_ROUTELOC0_CLKOUT0LOC_DEFAULT                 0x00000000UL                             /**< Mode DEFAULT for CMU_ROUTELOC0 */
#define _CMU_ROUTELOC0_CLKOUT0LOC_LOC1                    0x00000001UL                             /**< Mode LOC1 for CMU_ROUTELOC0 */
#define _CMU_ROUTELOC0_CLKOUT0LOC_LOC2                    0x00000002UL                             /**< Mode LOC2 for CMU_ROUTELOC0 */
#define _CMU_ROUTELOC0_CLKOUT0LOC_LOC3                    0x00000003UL                             /**< Mode LOC3 for CMU_ROUTELOC0 */
#define _CMU_ROUTELOC0_CLKOUT0LOC_LOC4                    0x00000004UL                             /**< Mode LOC4 for CMU_ROUTELOC0 */
#define _CMU_ROUTELOC0_CLKOUT0LOC_LOC5                    0x00000005UL                             /**< Mode LOC5 for CMU_ROUTELOC0 */
#define _CMU_ROUTELOC0_CLKOUT0LOC_LOC6                    0x00000006UL                             /**< Mode LOC6 for CMU_ROUTELOC0 */
#define _CMU_ROUTELOC0_CLKOUT0LOC_LOC7                    0x00000007UL                             /**< Mode LOC7 for CMU_ROUTELOC0 */
#define CMU_ROUTELOC0_CLKOUT0LOC_LOC0                     (_CMU_ROUTELOC0_CLKOUT0LOC_LOC0 << 0)    /**< Shifted mode LOC0 for CMU_ROUTELOC0 */
#define CMU_ROUTELOC0_CLKOUT0LOC_DEFAULT                  (_CMU_ROUTELOC0_CLKOUT0LOC_DEFAULT << 0) /**< Shifted mode DEFAULT for CMU_ROUTELOC0 */
#define CMU_ROUTELOC0_CLKOUT0LOC_LOC1                     (_CMU_ROUTELOC0_CLKOUT0LOC_LOC1 << 0)    /**< Shifted mode LOC1 for CMU_ROUTELOC0 */
#define CMU_ROUTELOC0_CLKOUT0LOC_LOC2                     (_CMU_ROUTELOC0_CLKOUT0LOC_LOC2 << 0)    /**< Shifted mode LOC2 for CMU_ROUTELOC0 */
#define CMU_ROUTELOC0_CLKOUT0LOC_LOC3                     (_CMU_ROUTELOC0_CLKOUT0LOC_LOC3 << 0)    /**< Shifted mode LOC3 for CMU_ROUTELOC0 */
#define CMU_ROUTELOC0_CLKOUT0LOC_LOC4                     (_CMU_ROUTELOC0_CLKOUT0LOC_LOC4 << 0)    /**< Shifted mode LOC4 for CMU_ROUTELOC0 */
#define CMU_ROUTELOC0_CLKOUT0LOC_LOC5                     (_CMU_ROUTELOC0_CLKOUT0LOC_LOC5 << 0)    /**< Shifted mode LOC5 for CMU_ROUTELOC0 */
#define CMU_ROUTELOC0_CLKOUT0LOC_LOC6                     (_CMU_ROUTELOC0_CLKOUT0LOC_LOC6 << 0)    /**< Shifted mode LOC6 for CMU_ROUTELOC0 */
#define CMU_ROUTELOC0_CLKOUT0LOC_LOC7                     (_CMU_ROUTELOC0_CLKOUT0LOC_LOC7 << 0)    /**< Shifted mode LOC7 for CMU_ROUTELOC0 */
#define _CMU_ROUTELOC0_CLKOUT1LOC_SHIFT                   8                                        /**< Shift value for CMU_CLKOUT1LOC */
#define _CMU_ROUTELOC0_CLKOUT1LOC_MASK                    0x700UL                                  /**< Bit mask for CMU_CLKOUT1LOC */
#define _CMU_ROUTELOC0_CLKOUT1LOC_LOC0                    0x00000000UL                             /**< Mode LOC0 for CMU_ROUTELOC0 */
#define _CMU_ROUTELOC0_CLKOUT1LOC_DEFAULT                 0x00000000UL                             /**< Mode DEFAULT for CMU_ROUTELOC0 */
#define _CMU_ROUTELOC0_CLKOUT1LOC_LOC1                    0x00000001UL                             /**< Mode LOC1 for CMU_ROUTELOC0 */
#define _CMU_ROUTELOC0_CLKOUT1LOC_LOC2                    0x00000002UL                             /**< Mode LOC2 for CMU_ROUTELOC0 */
#define _CMU_ROUTELOC0_CLKOUT1LOC_LOC3                    0x00000003UL                             /**< Mode LOC3 for CMU_ROUTELOC0 */
#define _CMU_ROUTELOC0_CLKOUT1LOC_LOC4                    0x00000004UL                             /**< Mode LOC4 for CMU_ROUTELOC0 */
#define _CMU_ROUTELOC0_CLKOUT1LOC_LOC5                    0x00000005UL                             /**< Mode LOC5 for CMU_ROUTELOC0 */
#define _CMU_ROUTELOC0_CLKOUT1LOC_LOC6                    0x00000006UL                             /**< Mode LOC6 for CMU_ROUTELOC0 */
#define _CMU_ROUTELOC0_CLKOUT1LOC_LOC7                    0x00000007UL                             /**< Mode LOC7 for CMU_ROUTELOC0 */
#define CMU_ROUTELOC0_CLKOUT1LOC_LOC0                     (_CMU_ROUTELOC0_CLKOUT1LOC_LOC0 << 8)    /**< Shifted mode LOC0 for CMU_ROUTELOC0 */
#define CMU_ROUTELOC0_CLKOUT1LOC_DEFAULT                  (_CMU_ROUTELOC0_CLKOUT1LOC_DEFAULT << 8) /**< Shifted mode DEFAULT for CMU_ROUTELOC0 */
#define CMU_ROUTELOC0_CLKOUT1LOC_LOC1                     (_CMU_ROUTELOC0_CLKOUT1LOC_LOC1 << 8)    /**< Shifted mode LOC1 for CMU_ROUTELOC0 */
#define CMU_ROUTELOC0_CLKOUT1LOC_LOC2                     (_CMU_ROUTELOC0_CLKOUT1LOC_LOC2 << 8)    /**< Shifted mode LOC2 for CMU_ROUTELOC0 */
#define CMU_ROUTELOC0_CLKOUT1LOC_LOC3                     (_CMU_ROUTELOC0_CLKOUT1LOC_LOC3 << 8)    /**< Shifted mode LOC3 for CMU_ROUTELOC0 */
#define CMU_ROUTELOC0_CLKOUT1LOC_LOC4                     (_CMU_ROUTELOC0_CLKOUT1LOC_LOC4 << 8)    /**< Shifted mode LOC4 for CMU_ROUTELOC0 */
#define CMU_ROUTELOC0_CLKOUT1LOC_LOC5                     (_CMU_ROUTELOC0_CLKOUT1LOC_LOC5 << 8)    /**< Shifted mode LOC5 for CMU_ROUTELOC0 */
#define CMU_ROUTELOC0_CLKOUT1LOC_LOC6                     (_CMU_ROUTELOC0_CLKOUT1LOC_LOC6 << 8)    /**< Shifted mode LOC6 for CMU_ROUTELOC0 */
#define CMU_ROUTELOC0_CLKOUT1LOC_LOC7                     (_CMU_ROUTELOC0_CLKOUT1LOC_LOC7 << 8)    /**< Shifted mode LOC7 for CMU_ROUTELOC0 */

/* Bit fields for CMU ROUTELOC1 */
#define _CMU_ROUTELOC1_RESETVALUE                         0x00000000UL                            /**< Default value for CMU_ROUTELOC1 */
#define _CMU_ROUTELOC1_MASK                               0x00000007UL                            /**< Mask for CMU_ROUTELOC1 */
#define _CMU_ROUTELOC1_CLKIN0LOC_SHIFT                    0                                       /**< Shift value for CMU_CLKIN0LOC */
#define _CMU_ROUTELOC1_CLKIN0LOC_MASK                     0x7UL                                   /**< Bit mask for CMU_CLKIN0LOC */
#define _CMU_ROUTELOC1_CLKIN0LOC_LOC0                     0x00000000UL                            /**< Mode LOC0 for CMU_ROUTELOC1 */
#define _CMU_ROUTELOC1_CLKIN0LOC_DEFAULT                  0x00000000UL                            /**< Mode DEFAULT for CMU_ROUTELOC1 */
#define _CMU_ROUTELOC1_CLKIN0LOC_LOC1                     0x00000001UL                            /**< Mode LOC1 for CMU_ROUTELOC1 */
#define _CMU_ROUTELOC1_CLKIN0LOC_LOC2                     0x00000002UL                            /**< Mode LOC2 for CMU_ROUTELOC1 */
#define _CMU_ROUTELOC1_CLKIN0LOC_LOC3                     0x00000003UL                            /**< Mode LOC3 for CMU_ROUTELOC1 */
#define _CMU_ROUTELOC1_CLKIN0LOC_LOC4                     0x00000004UL                            /**< Mode LOC4 for CMU_ROUTELOC1 */
#define CMU_ROUTELOC1_CLKIN0LOC_LOC0                      (_CMU_ROUTELOC1_CLKIN0LOC_LOC0 << 0)    /**< Shifted mode LOC0 for CMU_ROUTELOC1 */
#define CMU_ROUTELOC1_CLKIN0LOC_DEFAULT                   (_CMU_ROUTELOC1_CLKIN0LOC_DEFAULT << 0) /**< Shifted mode DEFAULT for CMU_ROUTELOC1 */
#define CMU_ROUTELOC1_CLKIN0LOC_LOC1                      (_CMU_ROUTELOC1_CLKIN0LOC_LOC1 << 0)    /**< Shifted mode LOC1 for CMU_ROUTELOC1 */
#define CMU_ROUTELOC1_CLKIN0LOC_LOC2                      (_CMU_ROUTELOC1_CLKIN0LOC_LOC2 << 0)    /**< Shifted mode LOC2 for CMU_ROUTELOC1 */
#define CMU_ROUTELOC1_CLKIN0LOC_LOC3                      (_CMU_ROUTELOC1_CLKIN0LOC_LOC3 << 0)    /**< Shifted mode LOC3 for CMU_ROUTELOC1 */
#define CMU_ROUTELOC1_CLKIN0LOC_LOC4                      (_CMU_ROUTELOC1_CLKIN0LOC_LOC4 << 0)    /**< Shifted mode LOC4 for CMU_ROUTELOC1 */

/* Bit fields for CMU LOCK */
#define _CMU_LOCK_RESETVALUE                              0x00000000UL                      /**< Default value for CMU_LOCK */
#define _CMU_LOCK_MASK                                    0x0000FFFFUL                      /**< Mask for CMU_LOCK */
#define _CMU_LOCK_LOCKKEY_SHIFT                           0                                 /**< Shift value for CMU_LOCKKEY */
#define _CMU_LOCK_LOCKKEY_MASK                            0xFFFFUL                          /**< Bit mask for CMU_LOCKKEY */
#define _CMU_LOCK_LOCKKEY_DEFAULT                         0x00000000UL                      /**< Mode DEFAULT for CMU_LOCK */
#define _CMU_LOCK_LOCKKEY_LOCK                            0x00000000UL                      /**< Mode LOCK for CMU_LOCK */
#define _CMU_LOCK_LOCKKEY_UNLOCKED                        0x00000000UL                      /**< Mode UNLOCKED for CMU_LOCK */
#define _CMU_LOCK_LOCKKEY_LOCKED                          0x00000001UL                      /**< Mode LOCKED for CMU_LOCK */
#define _CMU_LOCK_LOCKKEY_UNLOCK                          0x0000580EUL                      /**< Mode UNLOCK for CMU_LOCK */
#define CMU_LOCK_LOCKKEY_DEFAULT                          (_CMU_LOCK_LOCKKEY_DEFAULT << 0)  /**< Shifted mode DEFAULT for CMU_LOCK */
#define CMU_LOCK_LOCKKEY_LOCK                             (_CMU_LOCK_LOCKKEY_LOCK << 0)     /**< Shifted mode LOCK for CMU_LOCK */
#define CMU_LOCK_LOCKKEY_UNLOCKED                         (_CMU_LOCK_LOCKKEY_UNLOCKED << 0) /**< Shifted mode UNLOCKED for CMU_LOCK */
#define CMU_LOCK_LOCKKEY_LOCKED                           (_CMU_LOCK_LOCKKEY_LOCKED << 0)   /**< Shifted mode LOCKED for CMU_LOCK */
#define CMU_LOCK_LOCKKEY_UNLOCK                           (_CMU_LOCK_LOCKKEY_UNLOCK << 0)   /**< Shifted mode UNLOCK for CMU_LOCK */

/* Bit fields for CMU HFRCOSS */
#define _CMU_HFRCOSS_RESETVALUE                           0x00000000UL                      /**< Default value for CMU_HFRCOSS */
#define _CMU_HFRCOSS_MASK                                 0x00001F07UL                      /**< Mask for CMU_HFRCOSS */
#define _CMU_HFRCOSS_SSAMP_SHIFT                          0                                 /**< Shift value for CMU_SSAMP */
#define _CMU_HFRCOSS_SSAMP_MASK                           0x7UL                             /**< Bit mask for CMU_SSAMP */
#define _CMU_HFRCOSS_SSAMP_DEFAULT                        0x00000000UL                      /**< Mode DEFAULT for CMU_HFRCOSS */
#define CMU_HFRCOSS_SSAMP_DEFAULT                         (_CMU_HFRCOSS_SSAMP_DEFAULT << 0) /**< Shifted mode DEFAULT for CMU_HFRCOSS */
#define _CMU_HFRCOSS_SSINV_SHIFT                          8                                 /**< Shift value for CMU_SSINV */
#define _CMU_HFRCOSS_SSINV_MASK                           0x1F00UL                          /**< Bit mask for CMU_SSINV */
#define _CMU_HFRCOSS_SSINV_DEFAULT                        0x00000000UL                      /**< Mode DEFAULT for CMU_HFRCOSS */
#define CMU_HFRCOSS_SSINV_DEFAULT                         (_CMU_HFRCOSS_SSINV_DEFAULT << 8) /**< Shifted mode DEFAULT for CMU_HFRCOSS */


/* Select register IDs for internal use. */
#define CMU_NOSEL_REG              0
#define CMU_HFCLKSEL_REG           1
#define CMU_LFACLKSEL_REG          2
#define CMU_LFBCLKSEL_REG          3
#define CMU_LFCCLKSEL_REG          4
#define CMU_LFECLKSEL_REG          5
#define CMU_DBGCLKSEL_REG          6
#define CMU_USBCCLKSEL_REG         7
#define CMU_ADC0ASYNCSEL_REG       8
#define CMU_ADC1ASYNCSEL_REG       9
#define CMU_SDIOREFSEL_REG        10
#define CMU_QSPI0REFSEL_REG       11
#define CMU_USBRCLKSEL_REG        12
#define CMU_PDMREFSEL_REG         13

#define CMU_SEL_REG_POS            0U
#define CMU_SEL_REG_MASK           0xfU

/* Divisor/prescaler register IDs for internal use. */
#define CMU_NODIV_REG              0
#define CMU_NOPRESC_REG            0
#define CMU_HFPRESC_REG            1
#define CMU_HFCLKDIV_REG           1
#define CMU_HFEXPPRESC_REG         2
#define CMU_HFCLKLEPRESC_REG       3
#define CMU_HFPERPRESC_REG         4
#define CMU_HFPERCLKDIV_REG        4
#define CMU_HFPERPRESCB_REG        5
#define CMU_HFPERPRESCC_REG        6
#define CMU_HFCOREPRESC_REG        7
#define CMU_HFCORECLKDIV_REG       7
#define CMU_LFAPRESC0_REG          8
#define CMU_LFBPRESC0_REG          9
#define CMU_LFEPRESC0_REG         10
#define CMU_ADCASYNCDIV_REG       11
#define CMU_HFBUSPRESC_REG        12

#define CMU_PRESC_REG_POS          4U
#define CMU_DIV_REG_POS            CMU_PRESC_REG_POS
#define CMU_PRESC_REG_MASK         0xfU
#define CMU_DIV_REG_MASK           CMU_PRESC_REG_MASK

/* Enable register IDs for internal use. */
#define CMU_NO_EN_REG              0
#define CMU_CTRL_EN_REG            1
#define CMU_HFPERCLKDIV_EN_REG     1
#define CMU_HFPERCLKEN0_EN_REG     2
#define CMU_HFCORECLKEN0_EN_REG    3
#define CMU_PDMREF_EN_REG          4
#define CMU_HFBUSCLKEN0_EN_REG     5
#define CMU_LFACLKEN0_EN_REG       6
#define CMU_LFBCLKEN0_EN_REG       7
#define CMU_LFCCLKEN0_EN_REG       8
#define CMU_LFECLKEN0_EN_REG       9
#define CMU_PCNT_EN_REG            10
#define CMU_SDIOREF_EN_REG         11
#define CMU_QSPI0REF_EN_REG        12
#define CMU_QSPI1REF_EN_REG        13
#define CMU_HFPERCLKEN1_EN_REG     14
#define CMU_USBRCLK_EN_REG         15

#define CMU_EN_REG_POS             8U
#define CMU_EN_REG_MASK            0xfU

/* Enable register bit positions, for internal use. */
#define CMU_EN_BIT_POS             12U
#define CMU_EN_BIT_MASK            0x1fU

/* Clock branch bitfield positions, for internal use. */
#define CMU_HF_CLK_BRANCH          0
#define CMU_HFCORE_CLK_BRANCH      1
#define CMU_HFPER_CLK_BRANCH       2
#define CMU_HFPERB_CLK_BRANCH      3
#define CMU_HFPERC_CLK_BRANCH      4
#define CMU_HFBUS_CLK_BRANCH       5
#define CMU_HFEXP_CLK_BRANCH       6
#define CMU_DBG_CLK_BRANCH         7
#define CMU_AUX_CLK_BRANCH         8
#define CMU_RTC_CLK_BRANCH         9
#define CMU_RTCC_CLK_BRANCH        10
#define CMU_LETIMER0_CLK_BRANCH    11
#define CMU_LETIMER1_CLK_BRANCH    12
#define CMU_LEUART0_CLK_BRANCH     13
#define CMU_LEUART1_CLK_BRANCH     14
#define CMU_LFA_CLK_BRANCH         15
#define CMU_LFB_CLK_BRANCH         16
#define CMU_LFC_CLK_BRANCH         17
#define CMU_LFE_CLK_BRANCH         18
#define CMU_USBC_CLK_BRANCH        19
#define CMU_USBLE_CLK_BRANCH       20
#define CMU_LCDPRE_CLK_BRANCH      21
#define CMU_LCD_CLK_BRANCH         22
#define CMU_LESENSE_CLK_BRANCH     23
#define CMU_CSEN_LF_CLK_BRANCH     24
#define CMU_ADC0ASYNC_CLK_BRANCH   25
#define CMU_ADC1ASYNC_CLK_BRANCH   26
#define CMU_SDIOREF_CLK_BRANCH     27
#define CMU_QSPI0REF_CLK_BRANCH    28
#define CMU_USBR_CLK_BRANCH        29
#define CMU_PDMREF_CLK_BRANCH      30
#define CMU_HFLE_CLK_BRANCH        31

#define CMU_CLK_BRANCH_POS         17U
#define CMU_CLK_BRANCH_MASK        0x1fU

#if defined(_EMU_CMD_EM01VSCALE0_MASK)
/* Maximum clock frequency for VSCALE voltages. */
#define CMU_VSCALEEM01_LOWPOWER_VOLTAGE_CLOCK_MAX     20000000UL
#endif

/* Macros for VSCALE for use with the CMU_UpdateWaitStates(freq, vscale) API.
 * NOTE: The values must align with the values in EMU_VScaleEM01_TypeDef for
 * Series1 parts (highest VSCALE voltage = lowest numerical value). */
#define VSCALE_EM01_LOW_POWER           2
#define VSCALE_EM01_HIGH_PERFORMANCE    0

#if defined(USB_PRESENT) && defined(_CMU_HFCORECLKEN0_USBC_MASK)
#define USBC_CLOCK_PRESENT
#endif
#if defined(USB_PRESENT) && defined(_CMU_USBCTRL_MASK)
#define USBR_CLOCK_PRESENT
#endif
#if defined(CMU_OSCENCMD_PLFRCOEN)
#define PLFRCO_PRESENT
#endif

/** @endcond */

/*******************************************************************************
 ********************************   ENUMS   ************************************
 ******************************************************************************/

/** Clock divisors. These values are valid for prescalers. */
#define cmuClkDiv_1     1     /**< Divide clock by 1. */
#define cmuClkDiv_2     2     /**< Divide clock by 2. */
#define cmuClkDiv_4     4     /**< Divide clock by 4. */
#define cmuClkDiv_8     8     /**< Divide clock by 8. */
#define cmuClkDiv_16    16    /**< Divide clock by 16. */
#define cmuClkDiv_32    32    /**< Divide clock by 32. */
#define cmuClkDiv_64    64    /**< Divide clock by 64. */
#define cmuClkDiv_128   128   /**< Divide clock by 128. */
#define cmuClkDiv_256   256   /**< Divide clock by 256. */
#define cmuClkDiv_512   512   /**< Divide clock by 512. */
#define cmuClkDiv_1024  1024  /**< Divide clock by 1024. */
#define cmuClkDiv_2048  2048  /**< Divide clock by 2048. */
#define cmuClkDiv_4096  4096  /**< Divide clock by 4096. */
#define cmuClkDiv_8192  8192  /**< Divide clock by 8192. */
#define cmuClkDiv_16384 16384 /**< Divide clock by 16384. */
#define cmuClkDiv_32768 32768 /**< Divide clock by 32768. */

/** Clock divider configuration */
typedef uint32_t CMU_ClkDiv_TypeDef;

#if defined(_SILICON_LABS_32B_SERIES_1)
/** Clockprescaler configuration */
typedef uint32_t CMU_ClkPresc_TypeDef;
#endif

#if defined(_CMU_HFRCOCTRL_BAND_MASK)
/** High-frequency system RCO bands */
typedef enum {
  cmuHFRCOBand_1MHz  = _CMU_HFRCOCTRL_BAND_1MHZ,      /**< 1 MHz HFRCO band  */
  cmuHFRCOBand_7MHz  = _CMU_HFRCOCTRL_BAND_7MHZ,      /**< 7 MHz HFRCO band  */
  cmuHFRCOBand_11MHz = _CMU_HFRCOCTRL_BAND_11MHZ,     /**< 11 MHz HFRCO band */
  cmuHFRCOBand_14MHz = _CMU_HFRCOCTRL_BAND_14MHZ,     /**< 14 MHz HFRCO band */
  cmuHFRCOBand_21MHz = _CMU_HFRCOCTRL_BAND_21MHZ,     /**< 21 MHz HFRCO band */
#if defined(CMU_HFRCOCTRL_BAND_28MHZ)
  cmuHFRCOBand_28MHz = _CMU_HFRCOCTRL_BAND_28MHZ,     /**< 28 MHz HFRCO band */
#endif
} CMU_HFRCOBand_TypeDef;
#endif /* _CMU_HFRCOCTRL_BAND_MASK */

#if defined(_CMU_AUXHFRCOCTRL_BAND_MASK)
/** AUX high-frequency RCO bands */
typedef enum {
  cmuAUXHFRCOBand_1MHz  = _CMU_AUXHFRCOCTRL_BAND_1MHZ,  /**< 1 MHz RC band  */
  cmuAUXHFRCOBand_7MHz  = _CMU_AUXHFRCOCTRL_BAND_7MHZ,  /**< 7 MHz RC band  */
  cmuAUXHFRCOBand_11MHz = _CMU_AUXHFRCOCTRL_BAND_11MHZ, /**< 11 MHz RC band */
  cmuAUXHFRCOBand_14MHz = _CMU_AUXHFRCOCTRL_BAND_14MHZ, /**< 14 MHz RC band */
  cmuAUXHFRCOBand_21MHz = _CMU_AUXHFRCOCTRL_BAND_21MHZ, /**< 21 MHz RC band */
#if defined(CMU_AUXHFRCOCTRL_BAND_28MHZ)
  cmuAUXHFRCOBand_28MHz = _CMU_AUXHFRCOCTRL_BAND_28MHZ, /**< 28 MHz RC band */
#endif
} CMU_AUXHFRCOBand_TypeDef;
#endif

#if defined(_CMU_USHFRCOCONF_BAND_MASK)
/** Universal serial high-frequency RC bands */
typedef enum {
  /** 24 MHz RC band. */
  cmuUSHFRCOBand_24MHz = _CMU_USHFRCOCONF_BAND_24MHZ,
  /** 48 MHz RC band. */
  cmuUSHFRCOBand_48MHz = _CMU_USHFRCOCONF_BAND_48MHZ,
} CMU_USHFRCOBand_TypeDef;
#endif

#if defined(_CMU_USHFRCOCTRL_FREQRANGE_MASK)
/** High-USHFRCO bands */
typedef enum {
  cmuUSHFRCOFreq_16M0Hz           = 16000000U,            /**< 16 MHz RC band  */
  cmuUSHFRCOFreq_32M0Hz           = 32000000U,            /**< 32 MHz RC band  */
  cmuUSHFRCOFreq_48M0Hz           = 48000000U,            /**< 48 MHz RC band  */
  cmuUSHFRCOFreq_50M0Hz           = 50000000U,            /**< 50 MHz RC band  */
  cmuUSHFRCOFreq_UserDefined      = 0,
} CMU_USHFRCOFreq_TypeDef;
#define CMU_USHFRCO_MIN           cmuUSHFRCOFreq_16M0Hz
#define CMU_USHFRCO_MAX           cmuUSHFRCOFreq_50M0Hz
#endif

#if defined(_CMU_HFRCOCTRL_FREQRANGE_MASK)
/** High-frequency system RCO bands */
typedef enum {
  cmuHFRCOFreq_1M0Hz            = 1000000U,             /**< 1 MHz RC band   */
  cmuHFRCOFreq_2M0Hz            = 2000000U,             /**< 2 MHz RC band   */
  cmuHFRCOFreq_4M0Hz            = 4000000U,             /**< 4 MHz RC band   */
  cmuHFRCOFreq_7M0Hz            = 7000000U,             /**< 7 MHz RC band   */
  cmuHFRCOFreq_13M0Hz           = 13000000U,            /**< 13 MHz RC band  */
  cmuHFRCOFreq_16M0Hz           = 16000000U,            /**< 16 MHz RC band  */
  cmuHFRCOFreq_19M0Hz           = 19000000U,            /**< 19 MHz RC band  */
  cmuHFRCOFreq_26M0Hz           = 26000000U,            /**< 26 MHz RC band  */
  cmuHFRCOFreq_32M0Hz           = 32000000U,            /**< 32 MHz RC band  */
  cmuHFRCOFreq_38M0Hz           = 38000000U,            /**< 38 MHz RC band  */
#if defined(_DEVINFO_HFRCOCAL13_MASK)
  cmuHFRCOFreq_48M0Hz           = 48000000U,            /**< 48 MHz RC band  */
#endif
#if defined(_DEVINFO_HFRCOCAL14_MASK)
  cmuHFRCOFreq_56M0Hz           = 56000000U,            /**< 56 MHz RC band  */
#endif
#if defined(_DEVINFO_HFRCOCAL15_MASK)
  cmuHFRCOFreq_64M0Hz           = 64000000U,            /**< 64 MHz RC band  */
#endif
#if defined(_DEVINFO_HFRCOCAL16_MASK)
  cmuHFRCOFreq_72M0Hz           = 72000000U,            /**< 72 MHz RC band  */
#endif
  cmuHFRCOFreq_UserDefined      = 0,
} CMU_HFRCOFreq_TypeDef;
#define CMU_HFRCO_MIN           cmuHFRCOFreq_1M0Hz
#if defined(_DEVINFO_HFRCOCAL16_MASK)
#define CMU_HFRCO_MAX           cmuHFRCOFreq_72M0Hz
#elif defined(_DEVINFO_HFRCOCAL15_MASK)
#define CMU_HFRCO_MAX           cmuHFRCOFreq_64M0Hz
#elif defined(_DEVINFO_HFRCOCAL14_MASK)
#define CMU_HFRCO_MAX           cmuHFRCOFreq_56M0Hz
#elif defined(_DEVINFO_HFRCOCAL13_MASK)
#define CMU_HFRCO_MAX           cmuHFRCOFreq_48M0Hz
#else
#define CMU_HFRCO_MAX           cmuHFRCOFreq_38M0Hz
#endif
#endif

#if defined(_CMU_AUXHFRCOCTRL_FREQRANGE_MASK)
/** AUX high-frequency RCO bands */
typedef enum {
  cmuAUXHFRCOFreq_1M0Hz         = 1000000U,             /**< 1 MHz RC band   */
  cmuAUXHFRCOFreq_2M0Hz         = 2000000U,             /**< 2 MHz RC band   */
  cmuAUXHFRCOFreq_4M0Hz         = 4000000U,             /**< 4 MHz RC band   */
  cmuAUXHFRCOFreq_7M0Hz         = 7000000U,             /**< 7 MHz RC band   */
  cmuAUXHFRCOFreq_13M0Hz        = 13000000U,            /**< 13 MHz RC band  */
  cmuAUXHFRCOFreq_16M0Hz        = 16000000U,            /**< 16 MHz RC band  */
  cmuAUXHFRCOFreq_19M0Hz        = 19000000U,            /**< 19 MHz RC band  */
  cmuAUXHFRCOFreq_26M0Hz        = 26000000U,            /**< 26 MHz RC band  */
  cmuAUXHFRCOFreq_32M0Hz        = 32000000U,            /**< 32 MHz RC band  */
  cmuAUXHFRCOFreq_38M0Hz        = 38000000U,            /**< 38 MHz RC band  */
#if defined(_DEVINFO_AUXHFRCOCAL13_MASK)
  cmuAUXHFRCOFreq_48M0Hz        = 48000000U,            /**< 48 MHz RC band  */
#endif
#if defined(_DEVINFO_AUXHFRCOCAL14_MASK)
  cmuAUXHFRCOFreq_50M0Hz        = 50000000U,            /**< 50 MHz RC band  */
#endif
  cmuAUXHFRCOFreq_UserDefined   = 0,
} CMU_AUXHFRCOFreq_TypeDef;
#define CMU_AUXHFRCO_MIN        cmuAUXHFRCOFreq_1M0Hz
#if defined(_DEVINFO_AUXHFRCOCAL14_MASK)
#define CMU_AUXHFRCO_MAX        cmuAUXHFRCOFreq_50M0Hz
#elif defined(_DEVINFO_AUXHFRCOCAL13_MASK)
#define CMU_AUXHFRCO_MAX        cmuAUXHFRCOFreq_48M0Hz
#else
#define CMU_AUXHFRCO_MAX        cmuAUXHFRCOFreq_38M0Hz
#endif
#endif

#if ZUNO_ASSEMBLY_TYPE == ZUNO_UNO
typedef  enum{
	cmuClock_HFPER = CMU_CLOCK_TYPE_HFPER,
	cmuClock_ADC0 = CMU_CLOCK_TYPE_ADC0,
	cmuClock_TIMER0 = CMU_CLOCK_TYPE_TIMER0,
	cmuClock_TIMER1 = CMU_CLOCK_TYPE_TIMER1,
	cmuClock_I2C0 = CMU_CLOCK_TYPE_I2C0,
	cmuClock_I2C1 = CMU_CLOCK_TYPE_I2C1,
	cmuClock_USART0 = CMU_CLOCK_TYPE_USART0,
	cmuClock_USART1 = CMU_CLOCK_TYPE_USART1,
	cmuClock_USART2 = CMU_CLOCK_TYPE_USART2,
	cmuClock_GPIO = CMU_CLOCK_TYPE_GPIO,
	cmuClock_CSEN_HF = CMU_CLOCK_TYPE_CSEN_HF,
	cmuClock_CSEN_LF = CMU_CLOCK_TYPE_CSEN_LF, 
	cmuClock_WTIMER0 = CMU_CLOCK_TYPE_WTIMER0,
	cmuClock_LDMA  = CMU_CLOCK_TYPE_LDMA,
	cmuClock_CRYPTO = CMU_CLOCK_TYPE_CRYPTO,
	cmuClock_GPCRC = CMU_CLOCK_TYPE_CRC,
	cmuClock_TRNG0 = CMU_CLOCK_TYPE_RND,
	cmuClock_HFLE = CMU_CLOCK_TYPE_HFLE,
	cmuClock_LEUART0 = CMU_CLOCK_TYPE_LEUART0


  } CMU_Clock_TypeDef;
#elif ZUNO_ASSEMBLY_TYPE == ZUNO_RASBERI || ZUNO_ASSEMBLY_TYPE == ZUNO_BOOTLOADER
/** Clock points in CMU. See CMU overview in the reference manual. */
typedef enum {
  /*******************/
  /* HF clock branch */
  /*******************/

  /** High-frequency clock */
#if defined(_CMU_CTRL_HFCLKDIV_MASK) \
  || defined(_CMU_HFPRESC_MASK)
  cmuClock_HF = (CMU_HFCLKDIV_REG << CMU_DIV_REG_POS)
                | (CMU_HFCLKSEL_REG << CMU_SEL_REG_POS)
                | (CMU_NO_EN_REG << CMU_EN_REG_POS)
                | (0 << CMU_EN_BIT_POS)
                | (CMU_HF_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#else
  cmuClock_HF = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                | (CMU_HFCLKSEL_REG << CMU_SEL_REG_POS)
                | (CMU_NO_EN_REG << CMU_EN_REG_POS)
                | (0 << CMU_EN_BIT_POS)
                | (CMU_HF_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

  /** Debug clock */
  cmuClock_DBG = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                 | (CMU_DBGCLKSEL_REG << CMU_SEL_REG_POS)
                 | (CMU_NO_EN_REG << CMU_EN_REG_POS)
                 | (0 << CMU_EN_BIT_POS)
                 | (CMU_DBG_CLK_BRANCH << CMU_CLK_BRANCH_POS),

  /** AUX clock */
  cmuClock_AUX = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                 | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                 | (CMU_NO_EN_REG << CMU_EN_REG_POS)
                 | (0 << CMU_EN_BIT_POS)
                 | (CMU_AUX_CLK_BRANCH << CMU_CLK_BRANCH_POS),

#if defined(_CMU_HFEXPPRESC_MASK)
  /**********************/
  /* HF export sub-branch */
  /**********************/

  /** Export clock */
  cmuClock_EXPORT = (CMU_HFEXPPRESC_REG << CMU_PRESC_REG_POS)
                    | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                    | (CMU_NO_EN_REG << CMU_EN_REG_POS)
                    | (0 << CMU_EN_BIT_POS)
                    | (CMU_HFEXP_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(_CMU_HFBUSCLKEN0_MASK)
/**********************************/
/* HF bus clock sub-branch */
/**********************************/

  /** High-frequency bus clock */
#if defined(_CMU_HFBUSPRESC_MASK)
  cmuClock_BUS = (CMU_HFBUSPRESC_REG << CMU_PRESC_REG_POS)
                 | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                 | (CMU_NO_EN_REG << CMU_EN_REG_POS)
                 | (0 << CMU_EN_BIT_POS)
                 | (CMU_HFBUS_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#else
  cmuClock_BUS = (CMU_NOPRESC_REG << CMU_PRESC_REG_POS)
                 | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                 | (CMU_NO_EN_REG << CMU_EN_REG_POS)
                 | (0 << CMU_EN_BIT_POS)
                 | (CMU_HFBUS_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFBUSCLKEN0_CRYPTO)
  /** Cryptography accelerator clock */
  cmuClock_CRYPTO = (CMU_NOPRESC_REG << CMU_PRESC_REG_POS)
                    | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                    | (CMU_HFBUSCLKEN0_EN_REG << CMU_EN_REG_POS)
                    | (_CMU_HFBUSCLKEN0_CRYPTO_SHIFT << CMU_EN_BIT_POS)
                    | (CMU_HFBUS_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFBUSCLKEN0_CRYPTO0)
  /** Cryptography accelerator 0 clock */
  cmuClock_CRYPTO0 = (CMU_NOPRESC_REG << CMU_PRESC_REG_POS)
                     | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                     | (CMU_HFBUSCLKEN0_EN_REG << CMU_EN_REG_POS)
                     | (_CMU_HFBUSCLKEN0_CRYPTO0_SHIFT << CMU_EN_BIT_POS)
                     | (CMU_HFBUS_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFBUSCLKEN0_CRYPTO1)
  /** Cryptography accelerator 1 clock */
  cmuClock_CRYPTO1 = (CMU_NOPRESC_REG << CMU_PRESC_REG_POS)
                     | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                     | (CMU_HFBUSCLKEN0_EN_REG << CMU_EN_REG_POS)
                     | (_CMU_HFBUSCLKEN0_CRYPTO1_SHIFT << CMU_EN_BIT_POS)
                     | (CMU_HFBUS_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFBUSCLKEN0_LDMA)
  /** Direct-memory access controller clock */
  cmuClock_LDMA = (CMU_NOPRESC_REG << CMU_PRESC_REG_POS)
                  | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                  | (CMU_HFBUSCLKEN0_EN_REG << CMU_EN_REG_POS)
                  | (_CMU_HFBUSCLKEN0_LDMA_SHIFT << CMU_EN_BIT_POS)
                  | (CMU_HFBUS_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFBUSCLKEN0_QSPI0)
  /** Quad SPI clock */
  cmuClock_QSPI0 = (CMU_NOPRESC_REG << CMU_PRESC_REG_POS)
                   | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                   | (CMU_HFBUSCLKEN0_EN_REG << CMU_EN_REG_POS)
                   | (_CMU_HFBUSCLKEN0_QSPI0_SHIFT << CMU_EN_BIT_POS)
                   | (CMU_HFBUS_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFBUSCLKEN0_GPCRC)
  /** General-purpose cyclic redundancy checksum clock */
  cmuClock_GPCRC = (CMU_NOPRESC_REG << CMU_PRESC_REG_POS)
                   | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                   | (CMU_HFBUSCLKEN0_EN_REG << CMU_EN_REG_POS)
                   | (_CMU_HFBUSCLKEN0_GPCRC_SHIFT << CMU_EN_BIT_POS)
                   | (CMU_HFBUS_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFBUSCLKEN0_GPIO)
  /** General-purpose input/output clock */
  cmuClock_GPIO = (CMU_NOPRESC_REG << CMU_PRESC_REG_POS)
                  | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                  | (CMU_HFBUSCLKEN0_EN_REG << CMU_EN_REG_POS)
                  | (_CMU_HFBUSCLKEN0_GPIO_SHIFT << CMU_EN_BIT_POS)
                  | (CMU_HFBUS_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

  /** Low-energy clock divided down from HFBUSCLK */
  cmuClock_HFLE = (CMU_NOPRESC_REG << CMU_PRESC_REG_POS)
                  | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                  | (CMU_HFBUSCLKEN0_EN_REG << CMU_EN_REG_POS)
                  | (_CMU_HFBUSCLKEN0_LE_SHIFT << CMU_EN_BIT_POS)
                  | (CMU_HFBUS_CLK_BRANCH << CMU_CLK_BRANCH_POS),

#if defined(CMU_HFBUSCLKEN0_PRS)
  /** Peripheral reflex system clock */
  cmuClock_PRS = (CMU_NOPRESC_REG << CMU_PRESC_REG_POS)
                 | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                 | (CMU_HFBUSCLKEN0_EN_REG << CMU_EN_REG_POS)
                 | (_CMU_HFBUSCLKEN0_PRS_SHIFT << CMU_EN_BIT_POS)
                 | (CMU_HFBUS_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif
#endif

  /**********************************/
  /* HF peripheral clock sub-branch */
  /**********************************/

  /** High-frequency peripheral clock */
#if defined(_CMU_HFPRESC_MASK)
  cmuClock_HFPER = (CMU_HFPERPRESC_REG << CMU_PRESC_REG_POS)
                   | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                   | (CMU_CTRL_EN_REG << CMU_EN_REG_POS)
                   | (_CMU_CTRL_HFPERCLKEN_SHIFT << CMU_EN_BIT_POS)
                   | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#else
  cmuClock_HFPER = (CMU_HFPERCLKDIV_REG << CMU_DIV_REG_POS)
                   | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                   | (CMU_HFPERCLKDIV_EN_REG << CMU_EN_REG_POS)
                   | (_CMU_HFPERCLKDIV_HFPERCLKEN_SHIFT << CMU_EN_BIT_POS)
                   | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(_CMU_HFPERPRESCB_MASK)
  /** Branch B figh-frequency peripheral clock */
  cmuClock_HFPERB = (CMU_HFPERPRESCB_REG << CMU_PRESC_REG_POS)
                    | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                    | (CMU_CTRL_EN_REG << CMU_EN_REG_POS)
                    | (_CMU_CTRL_HFPERCLKEN_SHIFT << CMU_EN_BIT_POS)
                    | (CMU_HFPERB_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(_CMU_HFPERPRESCC_MASK)
  /** Branch C figh-frequency peripheral clock */
  cmuClock_HFPERC = (CMU_HFPERPRESCC_REG << CMU_PRESC_REG_POS)
                    | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                    | (CMU_CTRL_EN_REG << CMU_EN_REG_POS)
                    | (_CMU_CTRL_HFPERCLKEN_SHIFT << CMU_EN_BIT_POS)
                    | (CMU_HFPERC_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFPERCLKEN0_PDM)
  /** PDM clock */
  cmuClock_PDM = (CMU_NOPRESC_REG << CMU_PRESC_REG_POS)
                 | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                 | (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS)
                 | (_CMU_HFPERCLKEN0_PDM_SHIFT << CMU_EN_BIT_POS)
                 | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFPERCLKEN0_USART0)
  /** Universal sync/async receiver/transmitter 0 clock */
  cmuClock_USART0 = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                    | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                    | (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS)
                    | (_CMU_HFPERCLKEN0_USART0_SHIFT << CMU_EN_BIT_POS)
                    | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFPERCLKEN0_USARTRF0)
  /** Universal sync/async receiver/transmitter 0 clock */
  cmuClock_USARTRF0 = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                      | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                      | (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS)
                      | (_CMU_HFPERCLKEN0_USARTRF0_SHIFT << CMU_EN_BIT_POS)
                      | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFPERCLKEN0_USARTRF1)
  /** Universal sync/async receiver/transmitter 0 clock */
  cmuClock_USARTRF1 = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                      | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                      | (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS)
                      | (_CMU_HFPERCLKEN0_USARTRF1_SHIFT << CMU_EN_BIT_POS)
                      | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFPERCLKEN0_USART1)
  /** Universal sync/async receiver/transmitter 1 clock */
  cmuClock_USART1 = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                    | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                    | (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS)
                    | (_CMU_HFPERCLKEN0_USART1_SHIFT << CMU_EN_BIT_POS)
                    | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFPERCLKEN0_USART2)
  /** Universal sync/async receiver/transmitter 2 clock */
  cmuClock_USART2 = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                    | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                    | (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS)
                    | (_CMU_HFPERCLKEN0_USART2_SHIFT << CMU_EN_BIT_POS)
  #if defined(_CMU_HFPERPRESCB_MASK)
                    | (CMU_HFPERB_CLK_BRANCH << CMU_CLK_BRANCH_POS),
  #else
                    | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
  #endif
#endif

#if defined(CMU_HFPERCLKEN0_USART3)
  /** Universal sync/async receiver/transmitter 3 clock */
  cmuClock_USART3 = (CMU_NOPRESC_REG << CMU_PRESC_REG_POS)
                    | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                    | (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS)
                    | (_CMU_HFPERCLKEN0_USART3_SHIFT << CMU_EN_BIT_POS)
                    | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFPERCLKEN0_USART4)
  /** Universal sync/async receiver/transmitter 4 clock */
  cmuClock_USART4 = (CMU_NOPRESC_REG << CMU_PRESC_REG_POS)
                    | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                    | (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS)
                    | (_CMU_HFPERCLKEN0_USART4_SHIFT << CMU_EN_BIT_POS)
                    | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFPERCLKEN0_USART5)
  /** Universal sync/async receiver/transmitter 5 clock */
  cmuClock_USART5 = (CMU_NOPRESC_REG << CMU_PRESC_REG_POS)
                    | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                    | (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS)
                    | (_CMU_HFPERCLKEN0_USART5_SHIFT << CMU_EN_BIT_POS)
                    | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFPERCLKEN0_UART0)
  /** Universal async receiver/transmitter 0 clock */
  cmuClock_UART0 = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                   | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                   | (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS)
                   | (_CMU_HFPERCLKEN0_UART0_SHIFT << CMU_EN_BIT_POS)
                   | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#elif defined(_CMU_HFPERCLKEN1_UART0_MASK)
  /** Universal async receiver/transmitter 0 clock */
  cmuClock_UART0 = (CMU_NOPRESC_REG << CMU_PRESC_REG_POS)
                   | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                   | (CMU_HFPERCLKEN1_EN_REG << CMU_EN_REG_POS)
                   | (_CMU_HFPERCLKEN1_UART0_SHIFT << CMU_EN_BIT_POS)
                   | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFPERCLKEN0_UART1)
  /** Universal async receiver/transmitter 1 clock */
  cmuClock_UART1 = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                   | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                   | (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS)
                   | (_CMU_HFPERCLKEN0_UART1_SHIFT << CMU_EN_BIT_POS)
                   | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#elif defined(_CMU_HFPERCLKEN1_UART1_MASK)
  /** Universal async receiver/transmitter 1 clock */
  cmuClock_UART1 = (CMU_NOPRESC_REG << CMU_PRESC_REG_POS)
                   | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                   | (CMU_HFPERCLKEN1_EN_REG << CMU_EN_REG_POS)
                   | (_CMU_HFPERCLKEN1_UART1_SHIFT << CMU_EN_BIT_POS)
                   | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFPERCLKEN0_TIMER0)
  /** Timer 0 clock */
  cmuClock_TIMER0 = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                    | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                    | (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS)
                    | (_CMU_HFPERCLKEN0_TIMER0_SHIFT << CMU_EN_BIT_POS)
  #if defined(_CMU_HFPERPRESCB_MASK)
                    | (CMU_HFPERB_CLK_BRANCH << CMU_CLK_BRANCH_POS),
  #else
                    | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
  #endif
#endif

#if defined(CMU_HFPERCLKEN0_TIMER1)
  /** Timer 1 clock */
  cmuClock_TIMER1 = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                    | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                    | (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS)
                    | (_CMU_HFPERCLKEN0_TIMER1_SHIFT << CMU_EN_BIT_POS)
                    | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFPERCLKEN0_TIMER2)
  /** Timer 2 clock */
  cmuClock_TIMER2 = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                    | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                    | (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS)
                    | (_CMU_HFPERCLKEN0_TIMER2_SHIFT << CMU_EN_BIT_POS)
                    | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFPERCLKEN0_TIMER3)
  /** Timer 3 clock */
  cmuClock_TIMER3 = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                    | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                    | (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS)
                    | (_CMU_HFPERCLKEN0_TIMER3_SHIFT << CMU_EN_BIT_POS)
                    | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFPERCLKEN0_TIMER4)
  /** Timer 4 clock */
  cmuClock_TIMER4 = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                    | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                    | (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS)
                    | (_CMU_HFPERCLKEN0_TIMER4_SHIFT << CMU_EN_BIT_POS)
                    | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFPERCLKEN0_TIMER5)
  /** Timer 5 clock */
  cmuClock_TIMER5 = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                    | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                    | (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS)
                    | (_CMU_HFPERCLKEN0_TIMER5_SHIFT << CMU_EN_BIT_POS)
                    | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFPERCLKEN0_TIMER6)
  /** Timer 6 clock */
  cmuClock_TIMER6 = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                    | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                    | (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS)
                    | (_CMU_HFPERCLKEN0_TIMER6_SHIFT << CMU_EN_BIT_POS)
                    | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFPERCLKEN0_WTIMER0)
  /** Wide-timer 0 clock */
  cmuClock_WTIMER0 = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                     | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                     | (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS)
                     | (_CMU_HFPERCLKEN0_WTIMER0_SHIFT << CMU_EN_BIT_POS)
                     | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#elif defined(CMU_HFPERCLKEN1_WTIMER0)
  /** Wide-timer 0 clock */
  cmuClock_WTIMER0 = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                     | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                     | (CMU_HFPERCLKEN1_EN_REG << CMU_EN_REG_POS)
                     | (_CMU_HFPERCLKEN1_WTIMER0_SHIFT << CMU_EN_BIT_POS)
                     | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFPERCLKEN0_WTIMER1)
  /** Wide-timer 1 clock */
  cmuClock_WTIMER1 = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                     | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                     | (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS)
                     | (_CMU_HFPERCLKEN0_WTIMER1_SHIFT << CMU_EN_BIT_POS)
                     | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#elif defined(CMU_HFPERCLKEN1_WTIMER1)
  /** Wide-timer 1 clock */
  cmuClock_WTIMER1 = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                     | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                     | (CMU_HFPERCLKEN1_EN_REG << CMU_EN_REG_POS)
                     | (_CMU_HFPERCLKEN1_WTIMER1_SHIFT << CMU_EN_BIT_POS)
                     | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFPERCLKEN1_WTIMER2)
  /** Wide-timer 2 clock */
  cmuClock_WTIMER2 = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                     | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                     | (CMU_HFPERCLKEN1_EN_REG << CMU_EN_REG_POS)
                     | (_CMU_HFPERCLKEN1_WTIMER2_SHIFT << CMU_EN_BIT_POS)
                     | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFPERCLKEN1_WTIMER3)
  /** Wide-timer 3 clock */
  cmuClock_WTIMER3 = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                     | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                     | (CMU_HFPERCLKEN1_EN_REG << CMU_EN_REG_POS)
                     | (_CMU_HFPERCLKEN1_WTIMER3_SHIFT << CMU_EN_BIT_POS)
                     | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFPERCLKEN0_CRYOTIMER)
  /** CRYOtimer clock */
  cmuClock_CRYOTIMER = (CMU_NOPRESC_REG << CMU_PRESC_REG_POS)
                       | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                       | (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS)
                       | (_CMU_HFPERCLKEN0_CRYOTIMER_SHIFT << CMU_EN_BIT_POS)
  #if defined(_CMU_HFPERPRESCC_MASK)
                       | (CMU_HFPERC_CLK_BRANCH << CMU_CLK_BRANCH_POS),
  #else
                       | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
  #endif
#endif

#if defined(CMU_HFPERCLKEN0_ACMP0)
  /** Analog comparator 0 clock */
  cmuClock_ACMP0 = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                   | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                   | (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS)
                   | (_CMU_HFPERCLKEN0_ACMP0_SHIFT << CMU_EN_BIT_POS)
  #if defined(_CMU_HFPERPRESCC_MASK)
                   | (CMU_HFPERC_CLK_BRANCH << CMU_CLK_BRANCH_POS),
  #else
                   | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
  #endif
#endif

#if defined(CMU_HFPERCLKEN0_ACMP1)
  /** Analog comparator 1 clock */
  cmuClock_ACMP1 = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                   | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                   | (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS)
                   | (_CMU_HFPERCLKEN0_ACMP1_SHIFT << CMU_EN_BIT_POS)
  #if defined(_CMU_HFPERPRESCC_MASK)
                   | (CMU_HFPERC_CLK_BRANCH << CMU_CLK_BRANCH_POS),
  #else
                   | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
  #endif
#endif

#if defined(CMU_HFPERCLKEN0_ACMP2)
  /** Analog comparator 2 clock */
  cmuClock_ACMP2 = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                   | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                   | (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS)
                   | (_CMU_HFPERCLKEN0_ACMP2_SHIFT << CMU_EN_BIT_POS)
                   | (CMU_HFPERC_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFPERCLKEN0_ACMP3)
  /** Analog comparator 3 clock */
  cmuClock_ACMP3 = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                   | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                   | (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS)
                   | (_CMU_HFPERCLKEN0_ACMP3_SHIFT << CMU_EN_BIT_POS)
                   | (CMU_HFPERC_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFPERCLKEN0_PRS)
  /** Peripheral-reflex system clock */
  cmuClock_PRS = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                 | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                 | (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS)
                 | (_CMU_HFPERCLKEN0_PRS_SHIFT << CMU_EN_BIT_POS)
                 | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFPERCLKEN0_DAC0)
  /** Digital-to-analog converter 0 clock */
  cmuClock_DAC0 = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                  | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                  | (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS)
                  | (_CMU_HFPERCLKEN0_DAC0_SHIFT << CMU_EN_BIT_POS)
                  | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFPERCLKEN0_VDAC0)
  /** Voltage digital-to-analog converter 0 clock */
  cmuClock_VDAC0 = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                   | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                   | (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS)
                   | (_CMU_HFPERCLKEN0_VDAC0_SHIFT << CMU_EN_BIT_POS)
                   | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#elif defined(CMU_HFPERCLKEN1_VDAC0)
  /** Voltage digital-to-analog converter 0 clock */
  cmuClock_VDAC0 = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                   | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                   | (CMU_HFPERCLKEN1_EN_REG << CMU_EN_REG_POS)
                   | (_CMU_HFPERCLKEN1_VDAC0_SHIFT << CMU_EN_BIT_POS)
  #if defined(_CMU_HFPERPRESCC_MASK)
                   | (CMU_HFPERC_CLK_BRANCH << CMU_CLK_BRANCH_POS),
  #else
                   | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
  #endif
#endif

#if defined(CMU_HFPERCLKEN0_IDAC0)
  /** Current digital-to-analog converter 0 clock */
  cmuClock_IDAC0 = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                   | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                   | (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS)
                   | (_CMU_HFPERCLKEN0_IDAC0_SHIFT << CMU_EN_BIT_POS)
  #if defined(_CMU_HFPERPRESCC_MASK)
                   | (CMU_HFPERC_CLK_BRANCH << CMU_CLK_BRANCH_POS),
  #else
                   | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
  #endif
#endif

#if defined(CMU_HFPERCLKEN0_GPIO)
  /** General-purpose input/output clock */
  cmuClock_GPIO = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                  | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                  | (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS)
                  | (_CMU_HFPERCLKEN0_GPIO_SHIFT << CMU_EN_BIT_POS)
                  | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFPERCLKEN0_VCMP)
  /** Voltage comparator clock */
  cmuClock_VCMP = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                  | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                  | (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS)
                  | (_CMU_HFPERCLKEN0_VCMP_SHIFT << CMU_EN_BIT_POS)
                  | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFPERCLKEN0_ADC0)
  /** Analog-to-digital converter 0 clock */
  cmuClock_ADC0 = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                  | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                  | (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS)
                  | (_CMU_HFPERCLKEN0_ADC0_SHIFT << CMU_EN_BIT_POS)
  #if defined(_CMU_HFPERPRESCC_MASK)
                  | (CMU_HFPERC_CLK_BRANCH << CMU_CLK_BRANCH_POS),
  #else
                  | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
  #endif
#endif

#if defined(CMU_HFPERCLKEN0_ADC1)
  /** Analog-to-digital converter 1 clock */
  cmuClock_ADC1 = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                  | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                  | (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS)
                  | (_CMU_HFPERCLKEN0_ADC1_SHIFT << CMU_EN_BIT_POS)
                  | (CMU_HFPERC_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFPERCLKEN0_I2C0)
  /** I2C 0 clock */
  cmuClock_I2C0 = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                  | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                  | (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS)
                  | (_CMU_HFPERCLKEN0_I2C0_SHIFT << CMU_EN_BIT_POS)
  #if defined(_CMU_HFPERPRESCC_MASK)
                  | (CMU_HFPERC_CLK_BRANCH << CMU_CLK_BRANCH_POS),
  #else
                  | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
  #endif
#endif

#if defined(CMU_HFPERCLKEN0_I2C1)
  /** I2C 1 clock */
  cmuClock_I2C1 = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                  | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                  | (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS)
                  | (_CMU_HFPERCLKEN0_I2C1_SHIFT << CMU_EN_BIT_POS)
  #if defined(_CMU_HFPERPRESCC_MASK)
                  | (CMU_HFPERC_CLK_BRANCH << CMU_CLK_BRANCH_POS),
  #else
                  | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
  #endif
#endif

#if defined(CMU_HFPERCLKEN0_I2C2)
  /** I2C 2 clock */
  cmuClock_I2C2 = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                  | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                  | (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS)
                  | (_CMU_HFPERCLKEN0_I2C2_SHIFT << CMU_EN_BIT_POS)
                  | (CMU_HFPERC_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFPERCLKEN0_CSEN)
  /** Capacitive Sense HF clock */
  cmuClock_CSEN_HF = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                     | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                     | (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS)
                     | (_CMU_HFPERCLKEN0_CSEN_SHIFT << CMU_EN_BIT_POS)
                     | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#elif defined(CMU_HFPERCLKEN1_CSEN)
  /** Capacitive Sense HF clock */
  cmuClock_CSEN_HF = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                     | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                     | (CMU_HFPERCLKEN1_EN_REG << CMU_EN_REG_POS)
                     | (_CMU_HFPERCLKEN1_CSEN_SHIFT << CMU_EN_BIT_POS)
                     | (CMU_HFPERC_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFPERCLKEN0_TRNG0)
  /** True random number generator clock */
  cmuClock_TRNG0 = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                   | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                   | (CMU_HFPERCLKEN0_EN_REG << CMU_EN_REG_POS)
                   | (_CMU_HFPERCLKEN0_TRNG0_SHIFT << CMU_EN_BIT_POS)
                   | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(_CMU_HFPERCLKEN1_CAN0_MASK)
  /** Controller Area Network 0 clock */
  cmuClock_CAN0 = (CMU_NOPRESC_REG << CMU_PRESC_REG_POS)
                  | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                  | (CMU_HFPERCLKEN1_EN_REG << CMU_EN_REG_POS)
                  | (_CMU_HFPERCLKEN1_CAN0_SHIFT << CMU_EN_BIT_POS)
                  | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(_CMU_HFPERCLKEN1_CAN1_MASK)
  /** Controller Area Network 1 clock. */
  cmuClock_CAN1 = (CMU_NOPRESC_REG << CMU_PRESC_REG_POS)
                  | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                  | (CMU_HFPERCLKEN1_EN_REG << CMU_EN_REG_POS)
                  | (_CMU_HFPERCLKEN1_CAN1_SHIFT << CMU_EN_BIT_POS)
                  | (CMU_HFPER_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

  /**********************/
  /* HF core sub-branch */
  /**********************/

  /** Core clock */
  cmuClock_CORE = (CMU_HFCORECLKDIV_REG << CMU_DIV_REG_POS)
                  | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                  | (CMU_NO_EN_REG << CMU_EN_REG_POS)
                  | (0 << CMU_EN_BIT_POS)
                  | (CMU_HFCORE_CLK_BRANCH << CMU_CLK_BRANCH_POS),

#if defined(CMU_HFCORECLKEN0_AES)
  /** Advanced encryption standard accelerator clock */
  cmuClock_AES = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                 | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                 | (CMU_HFCORECLKEN0_EN_REG << CMU_EN_REG_POS)
                 | (_CMU_HFCORECLKEN0_AES_SHIFT << CMU_EN_BIT_POS)
                 | (CMU_HFCORE_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFCORECLKEN0_DMA)
  /** Direct memory access controller clock */
  cmuClock_DMA = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                 | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                 | (CMU_HFCORECLKEN0_EN_REG << CMU_EN_REG_POS)
                 | (_CMU_HFCORECLKEN0_DMA_SHIFT << CMU_EN_BIT_POS)
                 | (CMU_HFCORE_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFCORECLKEN0_LE)
  /** Low-energy clock divided down from HFCORECLK */
  cmuClock_HFLE = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                  | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                  | (CMU_HFCORECLKEN0_EN_REG << CMU_EN_REG_POS)
                  | (_CMU_HFCORECLKEN0_LE_SHIFT << CMU_EN_BIT_POS)
                  | (CMU_HFCORE_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFCORECLKEN0_EBI)
  /** External bus interface clock */
  cmuClock_EBI = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                 | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                 | (CMU_HFCORECLKEN0_EN_REG << CMU_EN_REG_POS)
                 | (_CMU_HFCORECLKEN0_EBI_SHIFT << CMU_EN_BIT_POS)
                 | (CMU_HFCORE_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#elif defined(_CMU_HFBUSCLKEN0_EBI_MASK)
  /** External bus interface clock */
  cmuClock_EBI = (CMU_NOPRESC_REG << CMU_PRESC_REG_POS)
                 | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                 | (CMU_HFBUSCLKEN0_EN_REG << CMU_EN_REG_POS)
                 | (_CMU_HFBUSCLKEN0_EBI_SHIFT << CMU_EN_BIT_POS)
                 | (CMU_HFCORE_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(_CMU_HFBUSCLKEN0_ETH_MASK)
  /** Ethernet clock */
  cmuClock_ETH = (CMU_NOPRESC_REG << CMU_PRESC_REG_POS)
                 | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                 | (CMU_HFBUSCLKEN0_EN_REG << CMU_EN_REG_POS)
                 | (_CMU_HFBUSCLKEN0_ETH_SHIFT << CMU_EN_BIT_POS)
                 | (CMU_HFCORE_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(_CMU_HFBUSCLKEN0_SDIO_MASK)
  /** SDIO clock */
  cmuClock_SDIO = (CMU_NOPRESC_REG << CMU_PRESC_REG_POS)
                  | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                  | (CMU_HFBUSCLKEN0_EN_REG << CMU_EN_REG_POS)
                  | (_CMU_HFBUSCLKEN0_SDIO_SHIFT << CMU_EN_BIT_POS)
                  | (CMU_HFCORE_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(USBC_CLOCK_PRESENT)
  /** USB Core clock */
  cmuClock_USBC = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                  | (CMU_USBCCLKSEL_REG << CMU_SEL_REG_POS)
                  | (CMU_HFCORECLKEN0_EN_REG << CMU_EN_REG_POS)
                  | (_CMU_HFCORECLKEN0_USBC_SHIFT << CMU_EN_BIT_POS)
                  | (CMU_USBC_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif
#if defined (USBR_CLOCK_PRESENT)
  /** USB Rate clock */
  cmuClock_USBR = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                  | (CMU_USBRCLKSEL_REG << CMU_SEL_REG_POS)
                  | (CMU_USBRCLK_EN_REG << CMU_EN_REG_POS)
                  | (_CMU_USBCTRL_USBCLKEN_SHIFT << CMU_EN_BIT_POS)
                  | (CMU_USBR_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_HFCORECLKEN0_USB)
  /** USB clock */
  cmuClock_USB = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                 | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                 | (CMU_HFCORECLKEN0_EN_REG << CMU_EN_REG_POS)
                 | (_CMU_HFCORECLKEN0_USB_SHIFT << CMU_EN_BIT_POS)
                 | (CMU_HFCORE_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#elif defined(CMU_HFBUSCLKEN0_USB)
  /** USB clock */
  cmuClock_USB = (CMU_NOPRESC_REG << CMU_PRESC_REG_POS)
                 | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                 | (CMU_HFBUSCLKEN0_EN_REG << CMU_EN_REG_POS)
                 | (_CMU_HFBUSCLKEN0_USB_SHIFT << CMU_EN_BIT_POS)
                 | (CMU_HFCORE_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

  /***************/
  /* LF A branch */
  /***************/

  /** Low-frequency A clock */
  cmuClock_LFA = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                 | (CMU_LFACLKSEL_REG << CMU_SEL_REG_POS)
                 | (CMU_NO_EN_REG << CMU_EN_REG_POS)
                 | (0 << CMU_EN_BIT_POS)
                 | (CMU_LFA_CLK_BRANCH << CMU_CLK_BRANCH_POS),

#if defined(CMU_LFACLKEN0_RTC)
  /** Real time counter clock */
  cmuClock_RTC = (CMU_LFAPRESC0_REG << CMU_DIV_REG_POS)
                 | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                 | (CMU_LFACLKEN0_EN_REG << CMU_EN_REG_POS)
                 | (_CMU_LFACLKEN0_RTC_SHIFT << CMU_EN_BIT_POS)
                 | (CMU_RTC_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_LFACLKEN0_LETIMER0)
  /** Low-energy timer 0 clock */
  cmuClock_LETIMER0 = (CMU_LFAPRESC0_REG << CMU_DIV_REG_POS)
                      | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                      | (CMU_LFACLKEN0_EN_REG << CMU_EN_REG_POS)
                      | (_CMU_LFACLKEN0_LETIMER0_SHIFT << CMU_EN_BIT_POS)
                      | (CMU_LETIMER0_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_LFACLKEN0_LETIMER1)
  /** Low-energy timer 1 clock */
  cmuClock_LETIMER1 = (CMU_LFAPRESC0_REG << CMU_DIV_REG_POS)
                      | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                      | (CMU_LFACLKEN0_EN_REG << CMU_EN_REG_POS)
                      | (_CMU_LFACLKEN0_LETIMER1_SHIFT << CMU_EN_BIT_POS)
                      | (CMU_LETIMER1_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_LFACLKEN0_LCD)
  /** Liquid crystal display, pre FDIV clock */
  cmuClock_LCDpre = (CMU_LFAPRESC0_REG << CMU_DIV_REG_POS)
                    | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                    | (CMU_NO_EN_REG << CMU_EN_REG_POS)
                    | (0 << CMU_EN_BIT_POS)
                    | (CMU_LCDPRE_CLK_BRANCH << CMU_CLK_BRANCH_POS),

  /** Liquid crystal display clock. Note that FDIV prescaler
   * must be set by special API. */
  cmuClock_LCD = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                 | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                 | (CMU_LFACLKEN0_EN_REG << CMU_EN_REG_POS)
                 | (_CMU_LFACLKEN0_LCD_SHIFT << CMU_EN_BIT_POS)
                 | (CMU_LCD_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_PCNTCTRL_PCNT0CLKEN)
  /** Pulse counter 0 clock */
  cmuClock_PCNT0 = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                   | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                   | (CMU_PCNT_EN_REG << CMU_EN_REG_POS)
                   | (_CMU_PCNTCTRL_PCNT0CLKEN_SHIFT << CMU_EN_BIT_POS)
                   | (CMU_LFA_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_PCNTCTRL_PCNT1CLKEN)
  /** Pulse counter 1 clock */
  cmuClock_PCNT1 = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                   | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                   | (CMU_PCNT_EN_REG << CMU_EN_REG_POS)
                   | (_CMU_PCNTCTRL_PCNT1CLKEN_SHIFT << CMU_EN_BIT_POS)
                   | (CMU_LFA_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_PCNTCTRL_PCNT2CLKEN)
  /** Pulse counter 2 clock */
  cmuClock_PCNT2 = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                   | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                   | (CMU_PCNT_EN_REG << CMU_EN_REG_POS)
                   | (_CMU_PCNTCTRL_PCNT2CLKEN_SHIFT << CMU_EN_BIT_POS)
                   | (CMU_LFA_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif
#if defined(CMU_LFACLKEN0_LESENSE)
  /** LESENSE clock */
  cmuClock_LESENSE = (CMU_LFAPRESC0_REG << CMU_DIV_REG_POS)
                     | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                     | (CMU_LFACLKEN0_EN_REG << CMU_EN_REG_POS)
                     | (_CMU_LFACLKEN0_LESENSE_SHIFT << CMU_EN_BIT_POS)
                     | (CMU_LESENSE_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

  /***************/
  /* LF B branch */
  /***************/

  /** Low-frequency B clock */
  cmuClock_LFB = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                 | (CMU_LFBCLKSEL_REG << CMU_SEL_REG_POS)
                 | (CMU_NO_EN_REG << CMU_EN_REG_POS)
                 | (0 << CMU_EN_BIT_POS)
                 | (CMU_LFB_CLK_BRANCH << CMU_CLK_BRANCH_POS),

#if defined(CMU_LFBCLKEN0_LEUART0)
  /** Low-energy universal asynchronous receiver/transmitter 0 clock */
  cmuClock_LEUART0 = (CMU_LFBPRESC0_REG << CMU_DIV_REG_POS)
                     | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                     | (CMU_LFBCLKEN0_EN_REG << CMU_EN_REG_POS)
                     | (_CMU_LFBCLKEN0_LEUART0_SHIFT << CMU_EN_BIT_POS)
                     | (CMU_LEUART0_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_LFBCLKEN0_CSEN)
  /** Capacitive Sense LF clock */
  cmuClock_CSEN_LF = (CMU_LFBPRESC0_REG << CMU_DIV_REG_POS)
                     | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                     | (CMU_LFBCLKEN0_EN_REG << CMU_EN_REG_POS)
                     | (_CMU_LFBCLKEN0_CSEN_SHIFT << CMU_EN_BIT_POS)
                     | (CMU_CSEN_LF_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_LFBCLKEN0_LEUART1)
  /** Low-energy universal asynchronous receiver/transmitter 1 clock */
  cmuClock_LEUART1 = (CMU_LFBPRESC0_REG << CMU_DIV_REG_POS)
                     | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                     | (CMU_LFBCLKEN0_EN_REG << CMU_EN_REG_POS)
                     | (_CMU_LFBCLKEN0_LEUART1_SHIFT << CMU_EN_BIT_POS)
                     | (CMU_LEUART1_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(CMU_LFBCLKEN0_SYSTICK)
  /** Cortex SYSTICK LF clock */
  cmuClock_SYSTICK = (CMU_LFBPRESC0_REG << CMU_DIV_REG_POS)
                     | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                     | (CMU_LFBCLKEN0_EN_REG << CMU_EN_REG_POS)
                     | (_CMU_LFBCLKEN0_SYSTICK_SHIFT << CMU_EN_BIT_POS)
                     | (CMU_LEUART0_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(_CMU_LFCCLKEN0_MASK)
  /***************/
  /* LF C branch */
  /***************/

  /** Low-frequency C clock */
  cmuClock_LFC = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                 | (CMU_LFCCLKSEL_REG << CMU_SEL_REG_POS)
                 | (CMU_NO_EN_REG << CMU_EN_REG_POS)
                 | (0 << CMU_EN_BIT_POS)
                 | (CMU_LFC_CLK_BRANCH << CMU_CLK_BRANCH_POS),

#if defined(CMU_LFCCLKEN0_USBLE)
  /** USB LE clock */
  cmuClock_USBLE = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                   | (CMU_LFCCLKSEL_REG << CMU_SEL_REG_POS)
                   | (CMU_LFCCLKEN0_EN_REG << CMU_EN_REG_POS)
                   | (_CMU_LFCCLKEN0_USBLE_SHIFT << CMU_EN_BIT_POS)
                   | (CMU_USBLE_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#elif defined(CMU_LFCCLKEN0_USB)
  /** USB LE clock */
  cmuClock_USBLE = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                   | (CMU_LFCCLKSEL_REG << CMU_SEL_REG_POS)
                   | (CMU_LFCCLKEN0_EN_REG << CMU_EN_REG_POS)
                   | (_CMU_LFCCLKEN0_USB_SHIFT << CMU_EN_BIT_POS)
                   | (CMU_USBLE_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif
#endif

#if defined(_CMU_LFECLKEN0_MASK)
  /***************/
  /* LF E branch */
  /***************/

  /** Low-frequency E clock */
  cmuClock_LFE = (CMU_NOPRESC_REG << CMU_PRESC_REG_POS)
                 | (CMU_LFECLKSEL_REG << CMU_SEL_REG_POS)
                 | (CMU_NO_EN_REG << CMU_EN_REG_POS)
                 | (0 << CMU_EN_BIT_POS)
                 | (CMU_LFE_CLK_BRANCH << CMU_CLK_BRANCH_POS),

  /** Real-time counter and calendar clock */
#if defined (CMU_LFECLKEN0_RTCC)
  cmuClock_RTCC = (CMU_LFEPRESC0_REG << CMU_PRESC_REG_POS)
                  | (CMU_NOSEL_REG << CMU_SEL_REG_POS)
                  | (CMU_LFECLKEN0_EN_REG << CMU_EN_REG_POS)
                  | (_CMU_LFECLKEN0_RTCC_SHIFT << CMU_EN_BIT_POS)
                  | (CMU_RTCC_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif
#endif

  /**********************************/
  /* Asynchronous peripheral clocks */
  /**********************************/

#if defined(_CMU_ADCCTRL_ADC0CLKSEL_MASK)
  /** ADC0 asynchronous clock */
  cmuClock_ADC0ASYNC = (CMU_ADCASYNCDIV_REG << CMU_DIV_REG_POS)
                       | (CMU_ADC0ASYNCSEL_REG << CMU_SEL_REG_POS)
                       | (CMU_NO_EN_REG << CMU_EN_REG_POS)
                       | (0 << CMU_EN_BIT_POS)
                       | (CMU_ADC0ASYNC_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(_CMU_ADCCTRL_ADC1CLKSEL_MASK)
  /** ADC1 asynchronous clock */
  cmuClock_ADC1ASYNC = (CMU_ADCASYNCDIV_REG << CMU_DIV_REG_POS)
                       | (CMU_ADC1ASYNCSEL_REG << CMU_SEL_REG_POS)
                       | (CMU_NO_EN_REG << CMU_EN_REG_POS)
                       | (0 << CMU_EN_BIT_POS)
                       | (CMU_ADC1ASYNC_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(_CMU_SDIOCTRL_SDIOCLKDIS_MASK)
  /** SDIO reference clock */
  cmuClock_SDIOREF = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                     | (CMU_SDIOREFSEL_REG << CMU_SEL_REG_POS)
                     | (CMU_SDIOREF_EN_REG << CMU_EN_REG_POS)
                     | (_CMU_SDIOCTRL_SDIOCLKDIS_SHIFT << CMU_EN_BIT_POS)
                     | (CMU_SDIOREF_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(_CMU_QSPICTRL_QSPI0CLKDIS_MASK)
  /** QSPI0 reference clock */
  cmuClock_QSPI0REF = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                      | (CMU_QSPI0REFSEL_REG << CMU_SEL_REG_POS)
                      | (CMU_QSPI0REF_EN_REG << CMU_EN_REG_POS)
                      | (_CMU_QSPICTRL_QSPI0CLKDIS_SHIFT << CMU_EN_BIT_POS)
                      | (CMU_QSPI0REF_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif

#if defined(_CMU_PDMCTRL_PDMCLKEN_MASK)
  /** PDM reference clock */
  cmuClock_PDMREF = (CMU_NODIV_REG << CMU_DIV_REG_POS)
                    | (CMU_PDMREFSEL_REG << CMU_SEL_REG_POS)
                    | (CMU_PDMREF_EN_REG << CMU_EN_REG_POS)
                    | (_CMU_PDMCTRL_PDMCLKEN_SHIFT << CMU_EN_BIT_POS)
                    | (CMU_PDMREF_CLK_BRANCH << CMU_CLK_BRANCH_POS),
#endif
} CMU_Clock_TypeDef;
#else
	#error Set ZUNO_ASSEMBLY_TYPE
#endif

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */
/* Deprecated CMU_Clock_TypeDef member */
#define cmuClock_CORELE cmuClock_HFLE
/** @endcond */

/** Oscillator types. */
typedef enum {
  cmuOsc_LFXO,     /**< Low-frequency crystal oscillator. */
  cmuOsc_LFRCO,    /**< Low-frequency RC oscillator. */
  cmuOsc_HFXO,     /**< High-frequency crystal oscillator. */
  cmuOsc_HFRCO,    /**< High-frequency RC oscillator. */
  cmuOsc_AUXHFRCO, /**< Auxiliary high-frequency RC oscillator. */
#if defined(_CMU_STATUS_USHFRCOENS_MASK)
  cmuOsc_USHFRCO,  /**< Universal serial high-frequency RC oscillator */
#endif
#if defined(CMU_LFCLKSEL_LFAE_ULFRCO) || defined(CMU_LFACLKSEL_LFA_ULFRCO)
  cmuOsc_ULFRCO,   /**< Ultra low-frequency RC oscillator. */
#endif
#if defined(CMU_HFCLKSTATUS_SELECTED_CLKIN0)
  cmuOsc_CLKIN0,   /**< External oscillator. */
#endif
#if defined(PLFRCO_PRESENT)
  cmuOsc_PLFRCO,   /**< Precision Low Frequency Oscillator. */
#endif
} CMU_Osc_TypeDef;

/** Oscillator modes. */
typedef enum {
  cmuOscMode_Crystal,   /**< Crystal oscillator. */
  cmuOscMode_AcCoupled, /**< AC-coupled buffer. */
  cmuOscMode_External,  /**< External digital clock. */
} CMU_OscMode_TypeDef;

/** Selectable clock sources. */
typedef enum {
  cmuSelect_Error,                      /**< Usage error. */
  cmuSelect_Disabled,                   /**< Clock selector disabled. */
  cmuSelect_LFXO,                       /**< Low-frequency crystal oscillator. */
  cmuSelect_LFRCO,                      /**< Low-frequency RC oscillator. */
  cmuSelect_HFXO,                       /**< High-frequency crystal oscillator. */
  cmuSelect_HFRCO,                      /**< High-frequency RC oscillator. */
  cmuSelect_HFCLKLE,                    /**< High-frequency LE clock divided by 2 or 4. */
  cmuSelect_AUXHFRCO,                   /**< Auxilliary clock source can be used for debug clock. */
  cmuSelect_HFSRCCLK,                   /**< High-frequency source clock. */
  cmuSelect_HFCLK,                      /**< Divided HFCLK on Giant for debug clock, undivided on
                                             Tiny Gecko and for USBC (not used on Gecko). */
#if defined(CMU_STATUS_USHFRCOENS)
  cmuSelect_USHFRCO,                    /**< Universal serial high-frequency RC oscillator. */
#endif
#if defined(CMU_CMD_HFCLKSEL_USHFRCODIV2)
  cmuSelect_USHFRCODIV2,                /**< Universal serial high-frequency RC oscillator / 2. */
#endif
#if defined(CMU_HFXOCTRL_HFXOX2EN)
  cmuSelect_HFXOX2,                     /**< High-frequency crystal oscillator x 2. */
#endif
#if defined(CMU_LFCLKSEL_LFAE_ULFRCO) || defined(CMU_LFACLKSEL_LFA_ULFRCO)
  cmuSelect_ULFRCO,                     /**< Ultra low-frequency RC oscillator. */
#endif
#if defined(CMU_HFCLKSTATUS_SELECTED_HFRCODIV2)
  cmuSelect_HFRCODIV2,                 /**< High-frequency RC oscillator divided by 2. */
#endif
#if defined(CMU_HFCLKSTATUS_SELECTED_CLKIN0)
  cmuSelect_CLKIN0,                    /**< External clock input. */
#endif
#if defined(PLFRCO_PRESENT)
  cmuSelect_PLFRCO,                    /**< Precision Low Frequency Oscillator. */
#endif
} CMU_Select_TypeDef;

#if defined(CMU_HFCORECLKEN0_LE)
/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */
/* Deprecated CMU_Select_TypeDef member */
#define cmuSelect_CORELEDIV2    cmuSelect_HFCLKLE
/** @endcond */
#endif

#if defined(_CMU_HFXOCTRL_PEAKDETSHUNTOPTMODE_MASK) || defined(_CMU_HFXOCTRL_PEAKDETMODE_MASK)
/** HFXO tuning modes */
typedef enum {
  cmuHFXOTuningMode_Auto               = 0,
  cmuHFXOTuningMode_PeakDetectCommand  = CMU_CMD_HFXOPEAKDETSTART,   /**< Run peak detect optimization only. */
#if defined(CMU_CMD_HFXOSHUNTOPTSTART)
  cmuHFXOTuningMode_ShuntCommand       = CMU_CMD_HFXOSHUNTOPTSTART,  /**< Run shunt current optimization only. */
  cmuHFXOTuningMode_PeakShuntCommand   = CMU_CMD_HFXOPEAKDETSTART    /**< Run peak and shunt current optimization. */
                                         | CMU_CMD_HFXOSHUNTOPTSTART,
#endif
} CMU_HFXOTuningMode_TypeDef;
#endif

#if defined(_CMU_CTRL_LFXOBOOST_MASK)
/** LFXO Boost values. */
typedef enum {
  cmuLfxoBoost70         = 0x0,
  cmuLfxoBoost100        = 0x2,
#if defined(_EMU_AUXCTRL_REDLFXOBOOST_MASK)
  cmuLfxoBoost70Reduced  = 0x1,
  cmuLfxoBoost100Reduced = 0x3,
#endif
} CMU_LFXOBoost_TypeDef;
#endif

#if defined(CMU_OSCENCMD_DPLLEN)
/** DPLL reference clock selector. */
typedef enum {
  cmuDPLLClkSel_Hfxo   = _CMU_DPLLCTRL_REFSEL_HFXO,   /**< HFXO is DPLL reference clock. */
  cmuDPLLClkSel_Lfxo   = _CMU_DPLLCTRL_REFSEL_LFXO,   /**< LFXO is DPLL reference clock. */
  cmuDPLLClkSel_Clkin0 = _CMU_DPLLCTRL_REFSEL_CLKIN0  /**< CLKIN0 is DPLL reference clock. */
} CMU_DPLLClkSel_TypeDef;

/** DPLL reference clock edge detect selector. */
typedef enum {
  cmuDPLLEdgeSel_Fall = _CMU_DPLLCTRL_EDGESEL_FALL,   /**< Detect falling edge of reference clock. */
  cmuDPLLEdgeSel_Rise = _CMU_DPLLCTRL_EDGESEL_RISE    /**< Detect rising edge of reference clock. */
} CMU_DPLLEdgeSel_TypeDef;

/** DPLL lock mode selector. */
typedef enum {
  cmuDPLLLockMode_Freq  = _CMU_DPLLCTRL_MODE_FREQLL,  /**< Frequency lock mode. */
  cmuDPLLLockMode_Phase = _CMU_DPLLCTRL_MODE_PHASELL  /**< Phase lock mode. */
} CMU_DPLLLockMode_TypeDef;
#endif // CMU_OSCENCMD_DPLLEN

/*******************************************************************************
 *******************************   STRUCTS   ***********************************
 ******************************************************************************/

/** LFXO initialization structure. Initialization values should be obtained from a configuration tool,
    app note, or xtal data sheet.  */
typedef struct {
#if defined(_CMU_LFXOCTRL_MASK)
  uint8_t ctune;                        /**< CTUNE (load capacitance) value */
  uint8_t gain;                         /**< Gain/max startup margin */
#else
  CMU_LFXOBoost_TypeDef boost;          /**< LFXO boost */
#endif
  uint8_t timeout;                      /**< Startup delay */
  CMU_OscMode_TypeDef mode;             /**< Oscillator mode */
} CMU_LFXOInit_TypeDef;

#if defined(_CMU_LFXOCTRL_MASK)
/** Default LFXO initialization values for platform 2 devices, which contain a
 *  separate LFXOCTRL register. */
#define CMU_LFXOINIT_DEFAULT                                                  \
  {                                                                           \
    _CMU_LFXOCTRL_TUNING_DEFAULT,   /* Default CTUNE value, 0 */              \
    _CMU_LFXOCTRL_GAIN_DEFAULT,     /* Default gain, 2 */                     \
    _CMU_LFXOCTRL_TIMEOUT_DEFAULT,  /* Default start-up delay, 32 K cycles */ \
    cmuOscMode_Crystal,             /* Crystal oscillator */                  \
  }
#define CMU_LFXOINIT_EXTERNAL_CLOCK                                             \
  {                                                                             \
    0,                              /* No CTUNE value needed */                 \
    0,                              /* No LFXO startup gain */                  \
    _CMU_LFXOCTRL_TIMEOUT_2CYCLES,  /* Minimal lfxo start-up delay, 2 cycles */ \
    cmuOscMode_External,            /* External digital clock */                \
  }
#else
/** Default LFXO initialization values for platform 1 devices. */
#define CMU_LFXOINIT_DEFAULT       \
  {                                \
    cmuLfxoBoost70,                \
    _CMU_CTRL_LFXOTIMEOUT_DEFAULT, \
    cmuOscMode_Crystal,            \
  }
#define CMU_LFXOINIT_EXTERNAL_CLOCK \
  {                                 \
    cmuLfxoBoost70,                 \
    _CMU_CTRL_LFXOTIMEOUT_8CYCLES,  \
    cmuOscMode_External,            \
  }
#endif

/** HFXO initialization structure. Initialization values should be obtained from a configuration tool,
    app note, or xtal data sheet.  */
typedef struct {
#if defined(_SILICON_LABS_32B_SERIES_1) && (_SILICON_LABS_GECKO_INTERNAL_SDID >= 100)
  uint16_t ctuneStartup;                /**< Startup phase CTUNE (load capacitance) value */
  uint16_t ctuneSteadyState;            /**< Steady-state phase CTUNE (load capacitance) value */
  uint16_t xoCoreBiasTrimStartup;       /**< Startup XO core bias current trim */
  uint16_t xoCoreBiasTrimSteadyState;   /**< Steady-state XO core bias current trim */
  uint8_t timeoutPeakDetect;            /**< Timeout - peak detection */
  uint8_t timeoutSteady;                /**< Timeout - steady-state */
  uint8_t timeoutStartup;               /**< Timeout - startup */
#elif defined(_CMU_HFXOCTRL_MASK)
  bool lowPowerMode;                    /**< Enable low-power mode */
  bool autoStartEm01;                   /**< @deprecated Use @ref CMU_HFXOAutostartEnable instead. */
  bool autoSelEm01;                     /**< @deprecated Use @ref CMU_HFXOAutostartEnable instead. */
  bool autoStartSelOnRacWakeup;         /**< @deprecated Use @ref CMU_HFXOAutostartEnable instead. */
  uint16_t ctuneStartup;                /**< Startup phase CTUNE (load capacitance) value */
  uint16_t ctuneSteadyState;            /**< Steady-state phase CTUNE (load capacitance) value */
  uint8_t regIshSteadyState;            /**< Shunt steady-state current */
  uint8_t xoCoreBiasTrimStartup;        /**< Startup XO core bias current trim */
  uint8_t xoCoreBiasTrimSteadyState;    /**< Steady-state XO core bias current trim */
  uint8_t thresholdPeakDetect;          /**< Peak detection threshold */
  uint8_t timeoutShuntOptimization;     /**< Timeout - shunt optimization */
  uint8_t timeoutPeakDetect;            /**< Timeout - peak detection */
  uint8_t timeoutSteady;                /**< Timeout - steady-state */
  uint8_t timeoutStartup;               /**< Timeout - startup */
#else
  uint8_t boost;                        /**< HFXO Boost, 0=50% 1=70%, 2=80%, 3=100% */
  uint8_t timeout;                      /**< Startup delay */
  bool glitchDetector;                  /**< Enable/disable glitch detector */
#endif
  CMU_OscMode_TypeDef mode;             /**< Oscillator mode */
} CMU_HFXOInit_TypeDef;

#if defined(_SILICON_LABS_32B_SERIES_1) && (_SILICON_LABS_GECKO_INTERNAL_SDID >= 100)
#define CMU_HFXOINIT_DEFAULT                       \
  {                                                \
    _CMU_HFXOSTARTUPCTRL_CTUNE_DEFAULT,            \
    _CMU_HFXOSTEADYSTATECTRL_CTUNE_DEFAULT,        \
    _CMU_HFXOSTARTUPCTRL_IBTRIMXOCORE_DEFAULT,     \
    _CMU_HFXOSTEADYSTATECTRL_IBTRIMXOCORE_DEFAULT, \
    _CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_DEFAULT,   \
    _CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_DEFAULT,    \
    _CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_DEFAULT,   \
    cmuOscMode_Crystal,                            \
  }
#define CMU_HFXOINIT_EXTERNAL_CLOCK                \
  {                                                \
    _CMU_HFXOSTARTUPCTRL_CTUNE_DEFAULT,            \
    _CMU_HFXOSTEADYSTATECTRL_CTUNE_DEFAULT,        \
    _CMU_HFXOSTARTUPCTRL_IBTRIMXOCORE_DEFAULT,     \
    _CMU_HFXOSTEADYSTATECTRL_IBTRIMXOCORE_DEFAULT, \
    _CMU_HFXOTIMEOUTCTRL_PEAKDETTIMEOUT_DEFAULT,   \
    _CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_DEFAULT,    \
    _CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_DEFAULT,   \
    cmuOscMode_External,                           \
  }
#elif defined(_CMU_HFXOCTRL_MASK)
/**
 * Default HFXO initialization values for Platform 2 devices, which contain a
 * separate HFXOCTRL register.
 */
#if defined(_EFR_DEVICE)
#define CMU_HFXOINIT_DEFAULT                                        \
  {                                                                 \
    false,      /* Low-noise mode for EFR32 */                      \
    false,      /* @deprecated no longer in use */                  \
    false,      /* @deprecated no longer in use */                  \
    false,      /* @deprecated no longer in use */                  \
    _CMU_HFXOSTARTUPCTRL_CTUNE_DEFAULT,                             \
    _CMU_HFXOSTEADYSTATECTRL_CTUNE_DEFAULT,                         \
    0xA,        /* Default Shunt steady-state current */            \
    0x20,       /* Matching errata fix in @ref CHIP_Init() */       \
    0x7,        /* Recommended steady-state XO core bias current */ \
    0x6,        /* Recommended peak detection threshold */          \
    0x2,        /* Recommended shunt optimization timeout */        \
    0xA,        /* Recommended peak detection timeout  */           \
    0x4,        /* Recommended steady timeout */                    \
    _CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_DEFAULT,                    \
    cmuOscMode_Crystal,                                             \
  }
#else /* EFM32 device */
#define CMU_HFXOINIT_DEFAULT                                         \
  {                                                                  \
    true,       /* Low-power mode for EFM32 */                       \
    false,      /* @deprecated no longer in use */                   \
    false,      /* @deprecated no longer in use */                   \
    false,      /* @deprecated no longer in use */                   \
    _CMU_HFXOSTARTUPCTRL_CTUNE_DEFAULT,                              \
    _CMU_HFXOSTEADYSTATECTRL_CTUNE_DEFAULT,                          \
    0xA,        /* Default shunt steady-state current */             \
    0x20,       /* Matching errata fix in @ref CHIP_Init() */        \
    0x7,        /* Recommended steady-state osc core bias current */ \
    0x6,        /* Recommended peak detection threshold */           \
    0x2,        /* Recommended shunt optimization timeout */         \
    0xA,        /* Recommended peak detection timeout  */            \
    0x4,        /* Recommended steady timeout */                     \
    _CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_DEFAULT,                     \
    cmuOscMode_Crystal,                                              \
  }
#endif /* _EFR_DEVICE */
#define CMU_HFXOINIT_EXTERNAL_CLOCK                                            \
  {                                                                            \
    true,       /* Low-power mode */                                           \
    false,      /* @deprecated no longer in use */                             \
    false,      /* @deprecated no longer in use */                             \
    false,      /* @deprecated no longer in use */                             \
    0,          /* Startup CTUNE=0 recommended for external clock */           \
    0,          /* Steady  CTUNE=0 recommended for external clock */           \
    0xA,        /* Default shunt steady-state current */                       \
    0,          /* Startup IBTRIMXOCORE=0 recommended for external clock */    \
    0,          /* Steady  IBTRIMXOCORE=0 recommended for external clock */    \
    0x6,        /* Recommended peak detection threshold */                     \
    0x2,        /* Recommended shunt optimization timeout */                   \
    0x0,        /* Peak-detect not recommended for external clock usage */     \
    _CMU_HFXOTIMEOUTCTRL_STEADYTIMEOUT_2CYCLES, /* Minimal steady timeout */   \
    _CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_2CYCLES, /* Minimal startup timeout */ \
    cmuOscMode_External,                                                       \
  }
#else /* _CMU_HFXOCTRL_MASK */
/**
 * Default HFXO initialization values for Platform 1 devices.
 */
#define CMU_HFXOINIT_DEFAULT                                   \
  {                                                            \
    _CMU_CTRL_HFXOBOOST_DEFAULT, /* 100% HFXO boost */         \
    _CMU_CTRL_HFXOTIMEOUT_DEFAULT, /* 16 K startup delay */    \
    false,                       /* Disable glitch detector */ \
    cmuOscMode_Crystal,          /* Crystal oscillator */      \
  }
#define CMU_HFXOINIT_EXTERNAL_CLOCK                                      \
  {                                                                      \
    0,                           /* Minimal HFXO boost, 50% */           \
    _CMU_CTRL_HFXOTIMEOUT_8CYCLES, /* Minimal startup delay, 8 cycles */ \
    false,                       /* Disable glitch detector */           \
    cmuOscMode_External,         /* External digital clock */            \
  }
#endif /* _CMU_HFXOCTRL_MASK */

#if defined(CMU_OSCENCMD_DPLLEN)
/** DPLL initialization structure. Frequency will be Fref*(N+1)/(M+1). */
typedef struct {
  uint32_t  frequency;                  /**< PLL frequency value, max 40 MHz. */
  uint16_t  n;                          /**< Factor N. 300 <= N <= 4095       */
  uint16_t  m;                          /**< Factor M. M <= 4095              */
  uint8_t   ssInterval;                 /**< Spread spectrum update interval. */
  uint8_t   ssAmplitude;                /**< Spread spectrum amplitude.       */
  CMU_DPLLClkSel_TypeDef    refClk;     /**< Reference clock selector.        */
  CMU_DPLLEdgeSel_TypeDef   edgeSel;    /**< Reference clock edge detect selector. */
  CMU_DPLLLockMode_TypeDef  lockMode;   /**< DPLL lock mode selector.         */
  bool      autoRecover;                /**< Enable automatic lock recovery.  */
} CMU_DPLLInit_TypeDef;

/**
 * DPLL initialization values for 39,998,805 Hz using LFXO as reference
 * clock, M=2 and N=3661.
 */
#define CMU_DPLL_LFXO_TO_40MHZ                                             \
  {                                                                        \
    39998805,                     /* Target frequency.                  */ \
    3661,                         /* Factor N.                          */ \
    2,                            /* Factor M.                          */ \
    0,                            /* No spread spectrum clocking.       */ \
    0,                            /* No spread spectrum clocking.       */ \
    cmuDPLLClkSel_Lfxo,           /* Select LFXO as reference clock.    */ \
    cmuDPLLEdgeSel_Fall,          /* Select falling edge of ref clock.  */ \
    cmuDPLLLockMode_Freq,         /* Use frequency lock mode.           */ \
    true                          /* Enable automatic lock recovery.    */ \
  }
#endif // CMU_OSCENCMD_DPLLEN

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/
#if ZUNO_ASSEMBLY_TYPE == ZUNO_UNO
  #define CMU_ClockFreqGet(C) ((uint32_t)zunoSysCall(ZUNO_SYSFUNC_GECKOEXT_CMUCLOCK, 2, CMU_CLOCK_SUBFUNC_GETFREQ, C))
  #define CMU_ClockEnable(C, E) zunoSysCall(ZUNO_SYSFUNC_GECKOEXT_CMUCLOCK, 3, CMU_CLOCK_SUBFUNC_ENABLE, C, E)
#elif ZUNO_ASSEMBLY_TYPE == ZUNO_RASBERI || ZUNO_ASSEMBLY_TYPE == ZUNO_BOOTLOADER

#if defined(_CMU_AUXHFRCOCTRL_BAND_MASK)
CMU_AUXHFRCOBand_TypeDef  CMU_AUXHFRCOBandGet(void);
void                      CMU_AUXHFRCOBandSet(CMU_AUXHFRCOBand_TypeDef band);

#elif defined(_CMU_AUXHFRCOCTRL_FREQRANGE_MASK)
CMU_AUXHFRCOFreq_TypeDef  CMU_AUXHFRCOBandGet(void);
void                      CMU_AUXHFRCOBandSet(CMU_AUXHFRCOFreq_TypeDef setFreq);
#endif

uint32_t              CMU_Calibrate(uint32_t HFCycles, CMU_Osc_TypeDef reference);

#if defined(_CMU_CALCTRL_UPSEL_MASK) && defined(_CMU_CALCTRL_DOWNSEL_MASK)
void                  CMU_CalibrateConfig(uint32_t downCycles, CMU_Osc_TypeDef downSel,
                                          CMU_Osc_TypeDef upSel);
#endif

uint32_t              CMU_CalibrateCountGet(void);
void                  CMU_ClockEnable(CMU_Clock_TypeDef clock, uint8_t enable);
CMU_ClkDiv_TypeDef    CMU_ClockDivGet(CMU_Clock_TypeDef clock);
void                  CMU_ClockDivSet(CMU_Clock_TypeDef clock, CMU_ClkDiv_TypeDef div);
uint32_t              CMU_ClockFreqGet(CMU_Clock_TypeDef clock);

#if defined(_SILICON_LABS_32B_SERIES_1)
void                  CMU_ClockPrescSet(CMU_Clock_TypeDef clock, CMU_ClkPresc_TypeDef presc);
uint32_t              CMU_ClockPrescGet(CMU_Clock_TypeDef clock);
#endif

void                  CMU_ClockSelectSet(CMU_Clock_TypeDef clock, CMU_Select_TypeDef ref);
CMU_Select_TypeDef    CMU_ClockSelectGet(CMU_Clock_TypeDef clock);

#if defined(CMU_OSCENCMD_DPLLEN)
bool                  CMU_DPLLLock(const CMU_DPLLInit_TypeDef *init);
#endif
void                  CMU_FreezeEnable(bool enable);

#if defined(_CMU_HFRCOCTRL_BAND_MASK)
CMU_HFRCOBand_TypeDef CMU_HFRCOBandGet(void);
void                  CMU_HFRCOBandSet(CMU_HFRCOBand_TypeDef band);

#elif defined(_CMU_HFRCOCTRL_FREQRANGE_MASK)
CMU_HFRCOFreq_TypeDef CMU_HFRCOBandGet(void);
void                  CMU_HFRCOBandSet(CMU_HFRCOFreq_TypeDef setFreq);
#endif

#if defined(_CMU_HFRCOCTRL_SUDELAY_MASK)
uint32_t              CMU_HFRCOStartupDelayGet(void);
void                  CMU_HFRCOStartupDelaySet(uint32_t delay);
#endif

#if defined(_CMU_USHFRCOCTRL_FREQRANGE_MASK)
CMU_USHFRCOFreq_TypeDef CMU_USHFRCOBandGet(void);
void                    CMU_USHFRCOBandSet(CMU_USHFRCOFreq_TypeDef setFreq);
uint32_t                CMU_USHFRCOFreqGet(void);
#endif

#if defined(_CMU_HFXOCTRL_AUTOSTARTEM0EM1_MASK)
void                  CMU_HFXOAutostartEnable(uint32_t userSel,
                                              bool enEM0EM1Start,
                                              bool enEM0EM1StartSel);
#endif

void                  CMU_HFXOInit(const CMU_HFXOInit_TypeDef *hfxoInit);

uint32_t              CMU_LCDClkFDIVGet(void);
void                  CMU_LCDClkFDIVSet(uint32_t div);
void                  CMU_LFXOInit(const CMU_LFXOInit_TypeDef *lfxoInit);

void                  CMU_OscillatorEnable(CMU_Osc_TypeDef osc, bool enable, bool wait);
uint32_t              CMU_OscillatorTuningGet(CMU_Osc_TypeDef osc);
void                  CMU_OscillatorTuningSet(CMU_Osc_TypeDef osc, uint32_t val);

#if defined(_CMU_HFXOCTRL_PEAKDETSHUNTOPTMODE_MASK) || defined(_CMU_HFXOCTRL_PEAKDETMODE_MASK)
bool CMU_OscillatorTuningWait(CMU_Osc_TypeDef osc, CMU_HFXOTuningMode_TypeDef mode);
bool CMU_OscillatorTuningOptimize(CMU_Osc_TypeDef osc,
                                  CMU_HFXOTuningMode_TypeDef mode,
                                  bool wait);
#endif

#if (_SILICON_LABS_32B_SERIES < 2)
bool                  CMU_PCNTClockExternalGet(unsigned int instance);
void                  CMU_PCNTClockExternalSet(unsigned int instance, bool external);
#endif

#if defined(_CMU_USHFRCOCONF_BAND_MASK)
CMU_USHFRCOBand_TypeDef   CMU_USHFRCOBandGet(void);
void                      CMU_USHFRCOBandSet(CMU_USHFRCOBand_TypeDef band);
uint32_t                  CMU_USHFRCOFreqGet(void);
#endif
void                  CMU_UpdateWaitStates(uint32_t freq, int vscale);

#if defined(CMU_CALCTRL_CONT)
/***************************************************************************//**
 * @brief
 *   Configure continuous calibration mode.
 * @param[in] enable
 *   If true, enables continuous calibration, if false disables continuous
 *   calibration.
 ******************************************************************************/
__STATIC_INLINE void CMU_CalibrateCont(bool enable)
{
  BUS_RegBitWrite(&CMU->CALCTRL, _CMU_CALCTRL_CONT_SHIFT, (uint32_t)enable);
}
#endif

/***************************************************************************//**
 * @brief
 *   Start calibration.
 * @note
 *   This call is usually invoked after @ref CMU_CalibrateConfig() and possibly
 *   @ref CMU_CalibrateCont().
 ******************************************************************************/
__STATIC_INLINE void CMU_CalibrateStart(void)
{
  CMU->CMD = CMU_CMD_CALSTART;
}

#if defined(CMU_CMD_CALSTOP)
/***************************************************************************//**
 * @brief
 *   Stop the calibration counters.
 ******************************************************************************/
__STATIC_INLINE void CMU_CalibrateStop(void)
{
  CMU->CMD = CMU_CMD_CALSTOP;
}
#endif

/***************************************************************************//**
 * @brief
 *   Convert dividend to logarithmic value. It only works for even
 *   numbers equal to 2^n.
 *
 * @param[in] div
 *   An unscaled dividend.
 *
 * @return
 *   Logarithm of 2, as used by fixed prescalers.
 ******************************************************************************/
__STATIC_INLINE uint32_t CMU_DivToLog2(CMU_ClkDiv_TypeDef div)
{
  uint32_t log2;

  /* Fixed 2^n prescalers take argument of 32768 or less. */
//   EFM_ASSERT((div > 0U) && (div <= 32768U));

  /* Count leading zeroes and "reverse" result */
  log2 = 31UL - __CLZ(div);

  return log2;
}

#if defined(CMU_OSCENCMD_DPLLEN)
/***************************************************************************//**
 * @brief
 *   Unlock DPLL.
 * @note
 *   HFRCO is not turned off.
 ******************************************************************************/
__STATIC_INLINE void CMU_DPLLUnlock(void)
{
  CMU->OSCENCMD  = CMU_OSCENCMD_DPLLDIS;
}
#endif

/***************************************************************************//**
 * @brief
 *   Clear one or more pending CMU interrupts.
 *
 * @param[in] flags
 *   CMU interrupt sources to clear.
 ******************************************************************************/
__STATIC_INLINE void CMU_IntClear(uint32_t flags)
{
  CMU->IFC = flags;
}

/***************************************************************************//**
 * @brief
 *   Disable one or more CMU interrupts.
 *
 * @param[in] flags
 *   CMU interrupt sources to disable.
 ******************************************************************************/
__STATIC_INLINE void CMU_IntDisable(uint32_t flags)
{
  CMU->IEN &= ~flags;
}

/***************************************************************************//**
 * @brief
 *   Enable one or more CMU interrupts.
 *
 * @note
 *   Depending on use case, a pending interrupt may already be set prior to
 *   enabling the interrupt. Consider using @ref CMU_IntClear() prior to enabling
 *   if the pending interrupt should be ignored.
 *
 * @param[in] flags
 *   CMU interrupt sources to enable.
 ******************************************************************************/
__STATIC_INLINE void CMU_IntEnable(uint32_t flags)
{
  CMU->IEN |= flags;
}

/***************************************************************************//**
 * @brief
 *   Get pending CMU interrupts.
 *
 * @return
 *   CMU interrupt sources pending.
 ******************************************************************************/
__STATIC_INLINE uint32_t CMU_IntGet(void)
{
  return CMU->IF;
}

/***************************************************************************//**
 * @brief
 *   Get enabled and pending CMU interrupt flags.
 *
 * @details
 *   Useful for handling more interrupt sources in the same interrupt handler.
 *
 * @note
 *   This function does not clear event bits.
 *
 * @return
 *   Pending and enabled CMU interrupt sources.
 *   The return value is the bitwise AND of
 *   - the enabled interrupt sources in CMU_IEN and
 *   - the pending interrupt flags CMU_IF
 ******************************************************************************/
__STATIC_INLINE uint32_t CMU_IntGetEnabled(void)
{
  uint32_t ien;

  ien = CMU->IEN;
  return CMU->IF & ien;
}

/**************************************************************************//**
 * @brief
 *   Set one or more pending CMU interrupts.
 *
 * @param[in] flags
 *   CMU interrupt sources to set to pending.
 *****************************************************************************/
__STATIC_INLINE void CMU_IntSet(uint32_t flags)
{
  CMU->IFS = flags;
}

/***************************************************************************//**
 * @brief
 *   Lock the CMU to protect some of its registers against unintended
 *   modification.
 *
 * @details
 *   See the reference manual for CMU registers that will be
 *   locked.
 *
 * @note
 *   If locking the CMU registers, they must be unlocked prior to using any
 *   CMU API functions modifying CMU registers protected by the lock.
 ******************************************************************************/
__STATIC_INLINE void CMU_Lock(void)
{
  CMU->LOCK = CMU_LOCK_LOCKKEY_LOCK;
}

/***************************************************************************//**
 * @brief
 *   Convert logarithm of 2 prescaler to division factor.
 * @deprecated
 *   Deprecated and marked for removal in a later release. It will be replaced
 *   by SL_Log2ToDiv.
 * @param[in] log2
 *   Logarithm of 2, as used by fixed prescalers.
 *
 * @return
 *   Dividend.
 ******************************************************************************/
__STATIC_INLINE uint32_t CMU_Log2ToDiv(uint32_t log2)
{
  return SL_Log2ToDiv(log2);
}

/***************************************************************************//**
 * @brief
 *   Unlock the CMU so that writing to locked registers again is possible.
 ******************************************************************************/
__STATIC_INLINE void CMU_Unlock(void)
{
  CMU->LOCK = CMU_LOCK_LOCKKEY_UNLOCK;
}

#if defined(_CMU_HFRCOCTRL_FREQRANGE_MASK)
/***************************************************************************//**
 * @brief
 *   Get the current HFRCO frequency.
 *
 * @deprecated
 *   A deprecated function. New code should use @ref CMU_HFRCOBandGet().
 *
 * @return
 *   HFRCO frequency.
 ******************************************************************************/
__STATIC_INLINE CMU_HFRCOFreq_TypeDef CMU_HFRCOFreqGet(void)
{
  return CMU_HFRCOBandGet();
}

/***************************************************************************//**
 * @brief
 *   Set HFRCO calibration for the selected target frequency.
 *
 * @deprecated
 *   A deprecated function. New code should use @ref CMU_HFRCOBandSet().
 *
 * @param[in] setFreq
 *   HFRCO frequency to set.
 ******************************************************************************/
__STATIC_INLINE void CMU_HFRCOFreqSet(CMU_HFRCOFreq_TypeDef setFreq)
{
  CMU_HFRCOBandSet(setFreq);
}
#endif

#if defined(_CMU_AUXHFRCOCTRL_FREQRANGE_MASK)
/***************************************************************************//**
 * @brief
 *   Get the current AUXHFRCO frequency.
 *
 * @deprecated
 *   A deprecated function. New code should use @ref CMU_AUXHFRCOBandGet().
 *
 * @return
 *   AUXHFRCO frequency.
 ******************************************************************************/
__STATIC_INLINE CMU_AUXHFRCOFreq_TypeDef CMU_AUXHFRCOFreqGet(void)
{
  return CMU_AUXHFRCOBandGet();
}

/***************************************************************************//**
 * @brief
 *   Set AUXHFRCO calibration for the selected target frequency.
 *
 * @deprecated
 *   A deprecated function. New code should use @ref CMU_AUXHFRCOBandSet().
 *
 * @param[in] setFreq
 *   AUXHFRCO frequency to set.
 ******************************************************************************/
__STATIC_INLINE void CMU_AUXHFRCOFreqSet(CMU_AUXHFRCOFreq_TypeDef setFreq)
{
  CMU_AUXHFRCOBandSet(setFreq);
}
#endif

#if !defined(_SILICON_LABS_32B_SERIES_0)
/***************************************************************************//**
 * @brief
 *   Convert prescaler dividend to a logarithmic value. It only works for even
 *   numbers equal to 2^n.
 *
 * @param[in] presc
 *   An unscaled dividend (dividend = presc + 1).
 *
 * @return
 *   Logarithm of 2, as used by fixed 2^n prescalers.
 ******************************************************************************/
__STATIC_INLINE uint32_t CMU_PrescToLog2(uint32_t presc)
{
  uint32_t log2;

  /* Integer prescalers take argument less than 32768. */
//   EFM_ASSERT(presc < 32768U);

  /* Count leading zeroes and "reverse" result. */
  log2 = 31UL - __CLZ(presc + (uint32_t) 1);

  /* Check that prescaler is a 2^n number. */
//   EFM_ASSERT(presc == (SL_Log2ToDiv(log2) - 1U));

  return log2;
}
#endif // !defined(_SILICON_LABS_32B_SERIES_0)

uint32_t SystemCoreClockGet(void);

/***************************************************************************//**
 * @brief
 *   Update CMSIS SystemCoreClock variable.
 *
 * @details
 *   CMSIS defines a global variable SystemCoreClock that shall hold the
 *   core frequency in Hz. If the core frequency is dynamically changed, the
 *   variable must be kept updated in order to be CMSIS compliant.
 *
 *   Notice that only if changing the core clock frequency through the EFR CMU
 *   API, this variable will be kept updated. This function is only provided
 *   for CMSIS compliance and if a user modifies the the core clock outside
 *   the CMU API.
 ******************************************************************************/
__STATIC_INLINE void SystemCoreClockUpdate(void)
{
  (void)SystemCoreClockGet();
}

uint32_t SystemMaxCoreClockGet(void);

void SystemInit(void);
uint32_t SystemHFClockGet(void);

uint32_t SystemHFXOClockGet(void);
void SystemHFXOClockSet(uint32_t freq);

uint32_t SystemLFRCOClockGet(void);
uint32_t SystemULFRCOClockGet(void);

uint32_t SystemLFXOClockGet(void);
void SystemLFXOClockSet(uint32_t freq);

extern uint32_t SystemCoreClock;        /**< System Clock Frequency (Core Clock) */
extern uint32_t SystemHfrcoFreq;        /**< System HFRCO frequency */

#else
	#error Set ZUNO_ASSEMBLY_TYPE
#endif

#endif // CRTX_CMU_H