/***************************************************************************//**
 * @file
 * @brief ZGM13_GPCRC register and bit field definitions
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
#ifndef CRTX_GPCRC_H
#define CRTX_GPCRC_H

#include "ZGecko.h"

/***************************************************************************//**
 * @addtogroup Parts
 * @{
 ******************************************************************************/
/***************************************************************************//**
 * @defgroup ZGM13_GPCRC GPCRC
 * @{
 * @brief ZGM13_GPCRC Register Declaration
 ******************************************************************************/
/** GPCRC Register Declaration */
typedef struct {
  __IOM uint32_t CTRL;           /**< Control Register  */
  __IOM uint32_t CMD;            /**< Command Register  */
  __IOM uint32_t INIT;           /**< CRC Init Value  */
  __IOM uint32_t POLY;           /**< CRC Polynomial Value  */
  __IOM uint32_t INPUTDATA;      /**< Input 32-bit Data Register  */
  __IOM uint32_t INPUTDATAHWORD; /**< Input 16-bit Data Register  */
  __IOM uint32_t INPUTDATABYTE;  /**< Input 8-bit Data Register  */
  __IM uint32_t  DATA;           /**< CRC Data Register  */
  __IM uint32_t  DATAREV;        /**< CRC Data Reverse Register  */
  __IM uint32_t  DATABYTEREV;    /**< CRC Data Byte Reverse Register  */
} GPCRC_TypeDef;                 /** @} */

/***************************************************************************//**
 * @addtogroup ZGM13_GPCRC
 * @{
 * @defgroup ZGM13_GPCRC_BitFields  GPCRC Bit Fields
 * @{
 ******************************************************************************/

/* Bit fields for GPCRC CTRL */
#define _GPCRC_CTRL_RESETVALUE                          0x00000000UL                             /**< Default value for GPCRC_CTRL */
#define _GPCRC_CTRL_MASK                                0x00002711UL                             /**< Mask for GPCRC_CTRL */
#define GPCRC_CTRL_EN                                   (0x1UL << 0)                             /**< CRC Functionality Enable */
#define _GPCRC_CTRL_EN_SHIFT                            0                                        /**< Shift value for GPCRC_EN */
#define _GPCRC_CTRL_EN_MASK                             0x1UL                                    /**< Bit mask for GPCRC_EN */
#define _GPCRC_CTRL_EN_DEFAULT                          0x00000000UL                             /**< Mode DEFAULT for GPCRC_CTRL */
#define _GPCRC_CTRL_EN_DISABLE                          0x00000000UL                             /**< Mode DISABLE for GPCRC_CTRL */
#define _GPCRC_CTRL_EN_ENABLE                           0x00000001UL                             /**< Mode ENABLE for GPCRC_CTRL */
#define GPCRC_CTRL_EN_DEFAULT                           (_GPCRC_CTRL_EN_DEFAULT << 0)            /**< Shifted mode DEFAULT for GPCRC_CTRL */
#define GPCRC_CTRL_EN_DISABLE                           (_GPCRC_CTRL_EN_DISABLE << 0)            /**< Shifted mode DISABLE for GPCRC_CTRL */
#define GPCRC_CTRL_EN_ENABLE                            (_GPCRC_CTRL_EN_ENABLE << 0)             /**< Shifted mode ENABLE for GPCRC_CTRL */
#define GPCRC_CTRL_POLYSEL                              (0x1UL << 4)                             /**< Polynomial Select */
#define _GPCRC_CTRL_POLYSEL_SHIFT                       4                                        /**< Shift value for GPCRC_POLYSEL */
#define _GPCRC_CTRL_POLYSEL_MASK                        0x10UL                                   /**< Bit mask for GPCRC_POLYSEL */
#define _GPCRC_CTRL_POLYSEL_DEFAULT                     0x00000000UL                             /**< Mode DEFAULT for GPCRC_CTRL */
#define _GPCRC_CTRL_POLYSEL_CRC32                       0x00000000UL                             /**< Mode CRC32 for GPCRC_CTRL */
#define _GPCRC_CTRL_POLYSEL_16                          0x00000001UL                             /**< Mode 16 for GPCRC_CTRL */
#define GPCRC_CTRL_POLYSEL_DEFAULT                      (_GPCRC_CTRL_POLYSEL_DEFAULT << 4)       /**< Shifted mode DEFAULT for GPCRC_CTRL */
#define GPCRC_CTRL_POLYSEL_CRC32                        (_GPCRC_CTRL_POLYSEL_CRC32 << 4)         /**< Shifted mode CRC32 for GPCRC_CTRL */
#define GPCRC_CTRL_POLYSEL_16                           (_GPCRC_CTRL_POLYSEL_16 << 4)            /**< Shifted mode 16 for GPCRC_CTRL */
#define GPCRC_CTRL_BYTEMODE                             (0x1UL << 8)                             /**< Byte Mode Enable */
#define _GPCRC_CTRL_BYTEMODE_SHIFT                      8                                        /**< Shift value for GPCRC_BYTEMODE */
#define _GPCRC_CTRL_BYTEMODE_MASK                       0x100UL                                  /**< Bit mask for GPCRC_BYTEMODE */
#define _GPCRC_CTRL_BYTEMODE_DEFAULT                    0x00000000UL                             /**< Mode DEFAULT for GPCRC_CTRL */
#define GPCRC_CTRL_BYTEMODE_DEFAULT                     (_GPCRC_CTRL_BYTEMODE_DEFAULT << 8)      /**< Shifted mode DEFAULT for GPCRC_CTRL */
#define GPCRC_CTRL_BITREVERSE                           (0x1UL << 9)                             /**< Byte-level Bit Reverse Enable */
#define _GPCRC_CTRL_BITREVERSE_SHIFT                    9                                        /**< Shift value for GPCRC_BITREVERSE */
#define _GPCRC_CTRL_BITREVERSE_MASK                     0x200UL                                  /**< Bit mask for GPCRC_BITREVERSE */
#define _GPCRC_CTRL_BITREVERSE_DEFAULT                  0x00000000UL                             /**< Mode DEFAULT for GPCRC_CTRL */
#define _GPCRC_CTRL_BITREVERSE_NORMAL                   0x00000000UL                             /**< Mode NORMAL for GPCRC_CTRL */
#define _GPCRC_CTRL_BITREVERSE_REVERSED                 0x00000001UL                             /**< Mode REVERSED for GPCRC_CTRL */
#define GPCRC_CTRL_BITREVERSE_DEFAULT                   (_GPCRC_CTRL_BITREVERSE_DEFAULT << 9)    /**< Shifted mode DEFAULT for GPCRC_CTRL */
#define GPCRC_CTRL_BITREVERSE_NORMAL                    (_GPCRC_CTRL_BITREVERSE_NORMAL << 9)     /**< Shifted mode NORMAL for GPCRC_CTRL */
#define GPCRC_CTRL_BITREVERSE_REVERSED                  (_GPCRC_CTRL_BITREVERSE_REVERSED << 9)   /**< Shifted mode REVERSED for GPCRC_CTRL */
#define GPCRC_CTRL_BYTEREVERSE                          (0x1UL << 10)                            /**< Byte Reverse Mode */
#define _GPCRC_CTRL_BYTEREVERSE_SHIFT                   10                                       /**< Shift value for GPCRC_BYTEREVERSE */
#define _GPCRC_CTRL_BYTEREVERSE_MASK                    0x400UL                                  /**< Bit mask for GPCRC_BYTEREVERSE */
#define _GPCRC_CTRL_BYTEREVERSE_DEFAULT                 0x00000000UL                             /**< Mode DEFAULT for GPCRC_CTRL */
#define _GPCRC_CTRL_BYTEREVERSE_NORMAL                  0x00000000UL                             /**< Mode NORMAL for GPCRC_CTRL */
#define _GPCRC_CTRL_BYTEREVERSE_REVERSED                0x00000001UL                             /**< Mode REVERSED for GPCRC_CTRL */
#define GPCRC_CTRL_BYTEREVERSE_DEFAULT                  (_GPCRC_CTRL_BYTEREVERSE_DEFAULT << 10)  /**< Shifted mode DEFAULT for GPCRC_CTRL */
#define GPCRC_CTRL_BYTEREVERSE_NORMAL                   (_GPCRC_CTRL_BYTEREVERSE_NORMAL << 10)   /**< Shifted mode NORMAL for GPCRC_CTRL */
#define GPCRC_CTRL_BYTEREVERSE_REVERSED                 (_GPCRC_CTRL_BYTEREVERSE_REVERSED << 10) /**< Shifted mode REVERSED for GPCRC_CTRL */
#define GPCRC_CTRL_AUTOINIT                             (0x1UL << 13)                            /**< Auto Init Enable */
#define _GPCRC_CTRL_AUTOINIT_SHIFT                      13                                       /**< Shift value for GPCRC_AUTOINIT */
#define _GPCRC_CTRL_AUTOINIT_MASK                       0x2000UL                                 /**< Bit mask for GPCRC_AUTOINIT */
#define _GPCRC_CTRL_AUTOINIT_DEFAULT                    0x00000000UL                             /**< Mode DEFAULT for GPCRC_CTRL */
#define GPCRC_CTRL_AUTOINIT_DEFAULT                     (_GPCRC_CTRL_AUTOINIT_DEFAULT << 13)     /**< Shifted mode DEFAULT for GPCRC_CTRL */

/* Bit fields for GPCRC CMD */
#define _GPCRC_CMD_RESETVALUE                           0x00000000UL                   /**< Default value for GPCRC_CMD */
#define _GPCRC_CMD_MASK                                 0x00000001UL                   /**< Mask for GPCRC_CMD */
#define GPCRC_CMD_INIT                                  (0x1UL << 0)                   /**< Initialization Enable */
#define _GPCRC_CMD_INIT_SHIFT                           0                              /**< Shift value for GPCRC_INIT */
#define _GPCRC_CMD_INIT_MASK                            0x1UL                          /**< Bit mask for GPCRC_INIT */
#define _GPCRC_CMD_INIT_DEFAULT                         0x00000000UL                   /**< Mode DEFAULT for GPCRC_CMD */
#define GPCRC_CMD_INIT_DEFAULT                          (_GPCRC_CMD_INIT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPCRC_CMD */

/* Bit fields for GPCRC INIT */
#define _GPCRC_INIT_RESETVALUE                          0x00000000UL                    /**< Default value for GPCRC_INIT */
#define _GPCRC_INIT_MASK                                0xFFFFFFFFUL                    /**< Mask for GPCRC_INIT */
#define _GPCRC_INIT_INIT_SHIFT                          0                               /**< Shift value for GPCRC_INIT */
#define _GPCRC_INIT_INIT_MASK                           0xFFFFFFFFUL                    /**< Bit mask for GPCRC_INIT */
#define _GPCRC_INIT_INIT_DEFAULT                        0x00000000UL                    /**< Mode DEFAULT for GPCRC_INIT */
#define GPCRC_INIT_INIT_DEFAULT                         (_GPCRC_INIT_INIT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPCRC_INIT */

/* Bit fields for GPCRC POLY */
#define _GPCRC_POLY_RESETVALUE                          0x00000000UL                    /**< Default value for GPCRC_POLY */
#define _GPCRC_POLY_MASK                                0x0000FFFFUL                    /**< Mask for GPCRC_POLY */
#define _GPCRC_POLY_POLY_SHIFT                          0                               /**< Shift value for GPCRC_POLY */
#define _GPCRC_POLY_POLY_MASK                           0xFFFFUL                        /**< Bit mask for GPCRC_POLY */
#define _GPCRC_POLY_POLY_DEFAULT                        0x00000000UL                    /**< Mode DEFAULT for GPCRC_POLY */
#define GPCRC_POLY_POLY_DEFAULT                         (_GPCRC_POLY_POLY_DEFAULT << 0) /**< Shifted mode DEFAULT for GPCRC_POLY */

/* Bit fields for GPCRC INPUTDATA */
#define _GPCRC_INPUTDATA_RESETVALUE                     0x00000000UL                              /**< Default value for GPCRC_INPUTDATA */
#define _GPCRC_INPUTDATA_MASK                           0xFFFFFFFFUL                              /**< Mask for GPCRC_INPUTDATA */
#define _GPCRC_INPUTDATA_INPUTDATA_SHIFT                0                                         /**< Shift value for GPCRC_INPUTDATA */
#define _GPCRC_INPUTDATA_INPUTDATA_MASK                 0xFFFFFFFFUL                              /**< Bit mask for GPCRC_INPUTDATA */
#define _GPCRC_INPUTDATA_INPUTDATA_DEFAULT              0x00000000UL                              /**< Mode DEFAULT for GPCRC_INPUTDATA */
#define GPCRC_INPUTDATA_INPUTDATA_DEFAULT               (_GPCRC_INPUTDATA_INPUTDATA_DEFAULT << 0) /**< Shifted mode DEFAULT for GPCRC_INPUTDATA */

/* Bit fields for GPCRC INPUTDATAHWORD */
#define _GPCRC_INPUTDATAHWORD_RESETVALUE                0x00000000UL                                        /**< Default value for GPCRC_INPUTDATAHWORD */
#define _GPCRC_INPUTDATAHWORD_MASK                      0x0000FFFFUL                                        /**< Mask for GPCRC_INPUTDATAHWORD */
#define _GPCRC_INPUTDATAHWORD_INPUTDATAHWORD_SHIFT      0                                                   /**< Shift value for GPCRC_INPUTDATAHWORD */
#define _GPCRC_INPUTDATAHWORD_INPUTDATAHWORD_MASK       0xFFFFUL                                            /**< Bit mask for GPCRC_INPUTDATAHWORD */
#define _GPCRC_INPUTDATAHWORD_INPUTDATAHWORD_DEFAULT    0x00000000UL                                        /**< Mode DEFAULT for GPCRC_INPUTDATAHWORD */
#define GPCRC_INPUTDATAHWORD_INPUTDATAHWORD_DEFAULT     (_GPCRC_INPUTDATAHWORD_INPUTDATAHWORD_DEFAULT << 0) /**< Shifted mode DEFAULT for GPCRC_INPUTDATAHWORD */

/* Bit fields for GPCRC INPUTDATABYTE */
#define _GPCRC_INPUTDATABYTE_RESETVALUE                 0x00000000UL                                      /**< Default value for GPCRC_INPUTDATABYTE */
#define _GPCRC_INPUTDATABYTE_MASK                       0x000000FFUL                                      /**< Mask for GPCRC_INPUTDATABYTE */
#define _GPCRC_INPUTDATABYTE_INPUTDATABYTE_SHIFT        0                                                 /**< Shift value for GPCRC_INPUTDATABYTE */
#define _GPCRC_INPUTDATABYTE_INPUTDATABYTE_MASK         0xFFUL                                            /**< Bit mask for GPCRC_INPUTDATABYTE */
#define _GPCRC_INPUTDATABYTE_INPUTDATABYTE_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for GPCRC_INPUTDATABYTE */
#define GPCRC_INPUTDATABYTE_INPUTDATABYTE_DEFAULT       (_GPCRC_INPUTDATABYTE_INPUTDATABYTE_DEFAULT << 0) /**< Shifted mode DEFAULT for GPCRC_INPUTDATABYTE */

/* Bit fields for GPCRC DATA */
#define _GPCRC_DATA_RESETVALUE                          0x00000000UL                    /**< Default value for GPCRC_DATA */
#define _GPCRC_DATA_MASK                                0xFFFFFFFFUL                    /**< Mask for GPCRC_DATA */
#define _GPCRC_DATA_DATA_SHIFT                          0                               /**< Shift value for GPCRC_DATA */
#define _GPCRC_DATA_DATA_MASK                           0xFFFFFFFFUL                    /**< Bit mask for GPCRC_DATA */
#define _GPCRC_DATA_DATA_DEFAULT                        0x00000000UL                    /**< Mode DEFAULT for GPCRC_DATA */
#define GPCRC_DATA_DATA_DEFAULT                         (_GPCRC_DATA_DATA_DEFAULT << 0) /**< Shifted mode DEFAULT for GPCRC_DATA */

/* Bit fields for GPCRC DATAREV */
#define _GPCRC_DATAREV_RESETVALUE                       0x00000000UL                          /**< Default value for GPCRC_DATAREV */
#define _GPCRC_DATAREV_MASK                             0xFFFFFFFFUL                          /**< Mask for GPCRC_DATAREV */
#define _GPCRC_DATAREV_DATAREV_SHIFT                    0                                     /**< Shift value for GPCRC_DATAREV */
#define _GPCRC_DATAREV_DATAREV_MASK                     0xFFFFFFFFUL                          /**< Bit mask for GPCRC_DATAREV */
#define _GPCRC_DATAREV_DATAREV_DEFAULT                  0x00000000UL                          /**< Mode DEFAULT for GPCRC_DATAREV */
#define GPCRC_DATAREV_DATAREV_DEFAULT                   (_GPCRC_DATAREV_DATAREV_DEFAULT << 0) /**< Shifted mode DEFAULT for GPCRC_DATAREV */

/* Bit fields for GPCRC DATABYTEREV */
#define _GPCRC_DATABYTEREV_RESETVALUE                   0x00000000UL                                  /**< Default value for GPCRC_DATABYTEREV */
#define _GPCRC_DATABYTEREV_MASK                         0xFFFFFFFFUL                                  /**< Mask for GPCRC_DATABYTEREV */
#define _GPCRC_DATABYTEREV_DATABYTEREV_SHIFT            0                                             /**< Shift value for GPCRC_DATABYTEREV */
#define _GPCRC_DATABYTEREV_DATABYTEREV_MASK             0xFFFFFFFFUL                                  /**< Bit mask for GPCRC_DATABYTEREV */
#define _GPCRC_DATABYTEREV_DATABYTEREV_DEFAULT          0x00000000UL                                  /**< Mode DEFAULT for GPCRC_DATABYTEREV */
#define GPCRC_DATABYTEREV_DATABYTEREV_DEFAULT           (_GPCRC_DATABYTEREV_DATABYTEREV_DEFAULT << 0) /**< Shifted mode DEFAULT for GPCRC_DATABYTEREV */

/***************************************************************************//**
 * @addtogroup GPCRC
 * @brief General Purpose Cyclic Redundancy Check (GPCRC) API.
 *
 * @details
 * The GPCRC API functions provide full support for the GPCRC peripheral.
 *
 * The GPCRC module is a peripheral that implements a Cyclic Redundancy Check
 * (CRC) function. It supports a fixed 32-bit polynomial and a user
 * configurable 16-bit polynomial. The fixed 32-bit polynomial is the commonly
 * used IEEE 802.3 polynomial 0x04C11DB7.
 *
 * When using a 16-bit polynomial it is up to the user to choose a polynomial
 * that fits the application. Commonly used 16-bit polynomials are 0x1021
 * (CCITT-16), 0x3D65 (IEC16-MBus), and 0x8005 (ZigBee, 802.15.4, and USB).
 * See this link for other polynomials:
 * https://en.wikipedia.org/wiki/Cyclic_redundancy_check
 *
 * Before a CRC calculation can begin it is important to call the
 * @ref GPCRC_Start function. This function will reset CRC calculation
 * by copying the configured initialization value over to the CRC data register.
 *
 * There are two ways of sending input data to the GPCRC. Either write
 * the input data into the input data register using input functions
 * @ref GPCRC_InputU32, @ref GPCRC_InputU16 and @ref GPCRC_InputU8, or the
 * user can configure @ref LDMA to transfer data directly to one of the GPCRC
 * input data registers.
 *
 * <b> Examples of GPCRC usage: </b>
 *
 * A CRC-32 Calculation:
 *
 * @include em_gpcrc_crc32.c
 *
 * A CRC-16 Calculation:
 *
 * @include em_gpcrc_crc16.c
 *
 * A CRC-CCITT calculation:
 *
 * @include em_gpcrc_ccit.c
 *
 * @{
 ******************************************************************************/

/*******************************************************************************
 *******************************   STRUCTS   ***********************************
 ******************************************************************************/

/** CRC initialization structure. */
typedef struct {
  /**
   * CRC polynomial value. GPCRC supports either a fixed 32-bit polynomial
   * or a user configurable 16 bit polynomial. The fixed 32-bit polynomial
   * is the one used in IEEE 802.3, which has the value 0x04C11DB7. To use the
   * 32-bit fixed polynomial, just assign 0x04C11DB7 to the crcPoly field.
   * To use a 16-bit polynomial, assign a value to crcPoly where the upper 16
   * bits are zero.
   *
   * The polynomial should be written in normal bit order. For instance,
   * to use the CRC-16 polynomial X^16 + X^15 + X^2 + 1, first convert
   * it to hex representation and remove the highest order term
   * of the polynomial. This would give us 0x8005 as the value to write into
   * crcPoly.
   */
  uint32_t                   crcPoly;

  /**
   * CRC initialization value. This value is assigned to the GPCRC_INIT register.
   * The initValue is loaded into the data register when calling the
   * @ref GPCRC_Start function or when one of the data registers are read
   * while @ref autoInit is enabled.
   */
  uint32_t                   initValue;

  /**
   * Reverse byte order. This has an effect when sending a 32-bit word or
   * 16-bit half word input to the CRC calculation. When set to true, the input
   * bytes are reversed before entering the CRC calculation. When set to
   * false, the input bytes stay in the same order.
   */
  bool                       reverseByteOrder;

  /**
   * Reverse bits within each input byte. This setting enables or disables byte
   * level bit reversal. When byte-level bit reversal is enabled, then each byte
   * of input data will be reversed before entering CRC calculation.
   */
  bool                       reverseBits;

  /**
   * Enable/disable byte mode. When byte mode is enabled, then all input
   * is treated as single byte input even though the input is a 32-bit word
   * or a 16-bit half word. Only the least significant byte of the data-word
   * will be used for CRC calculation for all writes.
   */
  bool                       enableByteMode;

  /**
   * Enable automatic initialization by re-seeding the CRC result based on
   * the init value after reading one of the CRC data registers.
   */
  bool                       autoInit;

  /** Enable/disable GPCRC when initialization is completed. */
  bool                       enable;
} GPCRC_Init_TypeDef;

/** Default configuration for GPCRC_Init_TypeDef structure. */
#define GPCRC_INIT_DEFAULT                                                    \
  {                                                                           \
    0x04C11DB7UL,        /* CRC32 Polynomial value. */                        \
    0x00000000UL,        /* Initialization value. */                          \
    false,               /* Byte order is normal. */                          \
    false,               /* Bit order is not reversed on output. */           \
    false,               /* Disable byte mode. */                             \
    false,               /* Disable automatic initialization on data read. */ \
    true,                /* Enable GPCRC. */                                  \
  }

/*******************************************************************************
 ******************************   PROTOTYPES   *********************************
 ******************************************************************************/

void GPCRC_Init(GPCRC_TypeDef * gpcrc, const GPCRC_Init_TypeDef * init);
void GPCRC_Reset(GPCRC_TypeDef * gpcrc);

/***************************************************************************//**
 * @brief
 *   Enable/disable GPCRC.
 *
 * @param[in] gpcrc
 *   Pointer to GPCRC peripheral register block.
 *
 * @param[in] enable
 *   True to enable GPCRC, false to disable.
 ******************************************************************************/
__STATIC_INLINE void GPCRC_Enable(GPCRC_TypeDef * gpcrc, bool enable)
{
#if defined(GPCRC_EN_EN)
  BUS_RegBitWrite(&gpcrc->EN, _GPCRC_EN_EN_SHIFT, enable);
#else
  BUS_RegBitWrite(&gpcrc->CTRL, _GPCRC_CTRL_EN_SHIFT, enable);
#endif
}

/***************************************************************************//**
 * @brief
 *   Issues a command to initialize CRC calculation.
 *
 * @details
 *   Issues the command INIT in GPCRC_CMD that initializes
 *   CRC calculation by writing the initial values to the DATA register.
 *
 * @param[in] gpcrc
 *   Pointer to GPCRC peripheral register block.
 ******************************************************************************/
__STATIC_INLINE void GPCRC_Start(GPCRC_TypeDef * gpcrc)
{
  gpcrc->CMD = GPCRC_CMD_INIT;
}

/***************************************************************************//**
 * @brief
 *   Set the initialization value of the CRC.
 *
 * @param [in] initValue
 *   Value to use to initialize a CRC calculation. This value is moved into
 *   the data register when calling @ref GPCRC_Start
 *
 * @param[in] gpcrc
 *   Pointer to GPCRC peripheral register block.
 ******************************************************************************/
__STATIC_INLINE void GPCRC_InitValueSet(GPCRC_TypeDef * gpcrc, uint32_t initValue)
{
  gpcrc->INIT = initValue;
}

/***************************************************************************//**
 * @brief
 *   Writes a 32-bit value to the input data register of the CRC.
 *
 * @details
 *   Use this function to write a 32-bit input data to the CRC. CRC
 *   calculation is based on the provided input data using the configured
 *   CRC polynomial.
 *
 * @param[in] gpcrc
 *   Pointer to GPCRC peripheral register block.
 *
 * @param[in] data
 *   Data to be written to the input data register.
 ******************************************************************************/
__STATIC_INLINE void GPCRC_InputU32(GPCRC_TypeDef * gpcrc, uint32_t data)
{
  gpcrc->INPUTDATA = data;
}

/***************************************************************************//**
 * @brief
 *   Writes a 16-bit value to the input data register of the CRC.
 *
 * @details
 *   Use this function to write a 16 bit input data to the CRC. CRC
 *   calculation is based on the provided input data using the configured
 *   CRC polynomial.
 *
 * @param[in] gpcrc
 *   Pointer to GPCRC peripheral register block.
 *
 * @param[in] data
 *   Data to be written to the input data register.
 ******************************************************************************/
__STATIC_INLINE void GPCRC_InputU16(GPCRC_TypeDef * gpcrc, uint16_t data)
{
  gpcrc->INPUTDATAHWORD = data;
}

/***************************************************************************//**
 * @brief
 *   Writes an 8-bit value to the input data register of the CRC.
 *
 * @details
 *   Use this function to write an 8-bit input data to the CRC. CRC
 *   calculation is based on the provided input data using the configured
 *   CRC polynomial.
 *
 * @param[in] gpcrc
 *   Pointer to GPCRC peripheral register block.
 *
 * @param[in] data
 *   Data to be written to the input data register.
 ******************************************************************************/
__STATIC_INLINE void GPCRC_InputU8(GPCRC_TypeDef * gpcrc, uint8_t data)
{
  gpcrc->INPUTDATABYTE = data;
}

/***************************************************************************//**
 * @brief
 *   Reads the data register of the CRC.
 *
 * @details
 *   Use this function to read the calculated CRC value.
 *
 * @param[in] gpcrc
 *   Pointer to GPCRC peripheral register block.
 *
 * @return
 *   Content of the CRC data register.
 ******************************************************************************/
__STATIC_INLINE uint32_t GPCRC_DataRead(GPCRC_TypeDef * gpcrc)
{
  return gpcrc->DATA;
}

/***************************************************************************//**
 * @brief
 *   Reads the data register of the CRC bit reversed.
 *
 * @details
 *   Use this function to read the calculated CRC value bit reversed. When
 *   using a 32-bit polynomial, bits [31:0] are reversed, when using a
 *   16-bit polynomial, bits [15:0] are reversed.
 *
 * @param[in] gpcrc
 *   Pointer to GPCRC peripheral register block.
 *
 * @return
 *   Content of the CRC data register bit reversed.
 ******************************************************************************/
__STATIC_INLINE uint32_t GPCRC_DataReadBitReversed(GPCRC_TypeDef * gpcrc)
{
  return gpcrc->DATAREV;
}

/***************************************************************************//**
 * @brief
 *   Reads the data register of the CRC byte reversed.
 *
 * @details
 *   Use this function to read the calculated CRC value byte reversed.
 *
 * @param[in] gpcrc
 *   Pointer to GPCRC peripheral register block.
 *
 * @return
 *   Content of the CRC data register byte reversed.
 ******************************************************************************/
__STATIC_INLINE uint32_t GPCRC_DataReadByteReversed(GPCRC_TypeDef * gpcrc)
{
  return gpcrc->DATABYTEREV;
}

#endif//CRTX_GPCRC_H