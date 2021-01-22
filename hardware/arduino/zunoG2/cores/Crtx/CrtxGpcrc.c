/***************************************************************************//**
 * @file
 * @brief General Purpose Cyclic Redundancy Check (GPCRC) API.
 * @version 5.8.1
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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
#include "Arduino.h"
#include "CrtxGcc.h"
#include "CrtxGpcrc.h"

/***************************************************************************//**
 * @addtogroup emlib
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup GPCRC
 * @{
 ******************************************************************************/

/*******************************************************************************
 ***************************   GLOBAL FUNCTIONS   ******************************
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *   Initialize the General Purpose Cyclic Redundancy Check (GPCRC) module.
 *
 * @details
 *   Use this function to configure the operational parameters of the GPCRC,
 *   such as the polynomial to use and how the input should be preprocessed
 *   before entering the CRC calculation.
 *
 * @note
 *   This function will not copy the initialization value to the data register
 *   to prepare for a new CRC calculation. Either call
 *   @ref GPCRC_Start before each calculation or by use the
 *   autoInit functionality.
 *
 * @param[in] gpcrc
 *   A pointer to the GPCRC peripheral register block.
 *
 * @param[in] init
 *   A pointer to the initialization structure used to configure the GPCRC.
 ******************************************************************************/
void GPCRC_Init(GPCRC_TypeDef * gpcrc, const GPCRC_Init_TypeDef * init)
{
  uint32_t polySelect;
  uint32_t revPoly = 0;

  if (init->crcPoly == 0x04C11DB7) {
    polySelect = GPCRC_CTRL_POLYSEL_CRC32;
  } else {
    // If not using the fixed CRC-32 polynomial, use 16-bit.
    // EFM_ASSERT((init->crcPoly & 0xFFFF0000) == 0);
#if defined(GPCRC_CTRL_POLYSEL_CRC16)
    polySelect = GPCRC_CTRL_POLYSEL_CRC16;
#else
    polySelect = GPCRC_CTRL_POLYSEL_16;
#endif
    revPoly = SL_RBIT16(init->crcPoly);
  }

#if defined(GPCRC_EN_EN)
  if (init->enable) {
    gpcrc->EN_SET = GPCRC_EN_EN;
  } else {
    gpcrc->EN_CLR = GPCRC_EN_EN;
  }

  gpcrc->CTRL = (((uint32_t)init->autoInit << _GPCRC_CTRL_AUTOINIT_SHIFT)
                 | ((uint32_t)init->reverseByteOrder << _GPCRC_CTRL_BYTEREVERSE_SHIFT)
                 | ((uint32_t)init->reverseBits << _GPCRC_CTRL_BITREVERSE_SHIFT)
                 | ((uint32_t)init->enableByteMode << _GPCRC_CTRL_BYTEMODE_SHIFT)
                 | polySelect);
#else
  gpcrc->CTRL = (((uint32_t)init->autoInit << _GPCRC_CTRL_AUTOINIT_SHIFT)
                 | ((uint32_t)init->reverseByteOrder << _GPCRC_CTRL_BYTEREVERSE_SHIFT)
                 | ((uint32_t)init->reverseBits << _GPCRC_CTRL_BITREVERSE_SHIFT)
                 | ((uint32_t)init->enableByteMode << _GPCRC_CTRL_BYTEMODE_SHIFT)
                 | polySelect
                 | ((uint32_t)init->enable << _GPCRC_CTRL_EN_SHIFT));
#endif

#if defined(GPCRC_CTRL_POLYSEL_CRC16)
  if (polySelect == GPCRC_CTRL_POLYSEL_CRC16) {
#else
  if (polySelect == GPCRC_CTRL_POLYSEL_16) {
#endif
    // Set the CRC polynomial value.
    gpcrc->POLY = revPoly & _GPCRC_POLY_POLY_MASK;
  }

  // Load the CRC initialization value to GPCRC_INIT.
  gpcrc->INIT = init->initValue;
}

/***************************************************************************//**
 * @brief
 *   Reset GPCRC registers to the hardware reset state.
 *
 * @note
 *   The data registers are not reset by this function.
 *
 * @param[in] gpcrc
 *   A pointer to the GPCRC peripheral register block.
 ******************************************************************************/
void GPCRC_Reset(GPCRC_TypeDef * gpcrc)
{
  gpcrc->CTRL = _GPCRC_CTRL_RESETVALUE;
  gpcrc->POLY = _GPCRC_POLY_RESETVALUE;
  gpcrc->INIT = _GPCRC_INIT_RESETVALUE;
}

static void _crcCount(GPCRC_TypeDef *gpcrc, const uint8_t *b, size_t len) {
	const uint8_t					*e;
	const uint32_t					*tmp;
	
	e = b + len;
	if (len >= 4 * 2 - 1) {//Проверяем рационально по байту или может по слову лучше
		while (((size_t)b & 3) != 0)//Выравниваем адрес под  слово используемое в системе в arm x86 - выравниваем под 4 байт
			GPCRC_InputU8(gpcrc, b++[0]);
		tmp = (const uint32_t *)b;
		b = (const uint8_t *)((size_t)e & (0 - 4));
		while (tmp < (const uint32_t *)b)
			GPCRC_InputU32(gpcrc, tmp++[0]);
	}
	while (b < e)//Если остались не добитые байты добьем
		GPCRC_InputU8(gpcrc, b++[0]);
}

static void _crcCommon(const void *data, size_t len, GPCRC_Init_TypeDef *initGpcrc) {
	initGpcrc->autoInit = false;
	initGpcrc->enable = true;
	initGpcrc->reverseByteOrder = false;
	initGpcrc->enableByteMode = false;
	GPCRC_Init(GPCRC, initGpcrc);
	GPCRC_Start(GPCRC);
	_crcCount(GPCRC, (const uint8_t *)data, len);
}

uint16_t crc16_ccitt(const void *data, size_t len) {
	GPCRC_Init_TypeDef					initGpcrc;

	initGpcrc.crcPoly = 0x1021;
	initGpcrc.initValue = 0xFFFF;
	initGpcrc.reverseBits = true;
	_crcCommon(data, len, &initGpcrc);
	return (GPCRC_DataReadBitReversed(GPCRC));
}

uint16_t crc16_bypass(const void *data,size_t len) {
	GPCRC_Init_TypeDef					initGpcrc;

	initGpcrc.crcPoly = 0x8005;
	initGpcrc.initValue = 0x0000;
	initGpcrc.reverseBits = true;
	_crcCommon(data, len, &initGpcrc);
	return (GPCRC_DataReadBitReversed(GPCRC));
}

uint16_t crc16_xmodem(const void *data,size_t len) {
	GPCRC_Init_TypeDef					initGpcrc;

	initGpcrc.crcPoly = 0x1021;
	initGpcrc.initValue = 0x0000;
	initGpcrc.reverseBits = true;
	_crcCommon(data, len, &initGpcrc);
	return (GPCRC_DataReadBitReversed(GPCRC));
}

uint16_t crc16_teledisk(const void *data,size_t len) {
	GPCRC_Init_TypeDef					initGpcrc;

	initGpcrc.crcPoly = 0xA097;
	initGpcrc.initValue = 0x0000;
	initGpcrc.reverseBits = true;
	_crcCommon(data, len, &initGpcrc);
	return (GPCRC_DataReadBitReversed(GPCRC));
}

uint16_t crc16_augccitt(const void *data,size_t len) {
	GPCRC_Init_TypeDef					initGpcrc;

	initGpcrc.crcPoly = 0x1021;
	initGpcrc.initValue = 0xF0B8;//reverse 0x1D0F
	initGpcrc.reverseBits = true;
	_crcCommon(data, len, &initGpcrc);
	return (GPCRC_DataReadBitReversed(GPCRC));
}

uint16_t crc16_cdma2000(const void *data,size_t len) {
	GPCRC_Init_TypeDef					initGpcrc;

	initGpcrc.crcPoly = 0xC867;
	initGpcrc.initValue = 0xFFFF;
	initGpcrc.reverseBits = true;
	_crcCommon(data, len, &initGpcrc);
	return (GPCRC_DataReadBitReversed(GPCRC));
}

uint16_t crc16_dds110(const void *data,size_t len) {
	GPCRC_Init_TypeDef					initGpcrc;

	initGpcrc.crcPoly = 0x8005;
	initGpcrc.initValue = 0xB001;//reverse 0x800d
	initGpcrc.reverseBits = true;
	_crcCommon(data, len, &initGpcrc);
	return (GPCRC_DataReadBitReversed(GPCRC));
}

uint16_t crc16_dect_x(const void *data,size_t len) {
	GPCRC_Init_TypeDef					initGpcrc;

	initGpcrc.crcPoly = 0x0589;
	initGpcrc.initValue = 0x0000;
	initGpcrc.reverseBits = true;
	_crcCommon(data, len, &initGpcrc);
	return (GPCRC_DataReadBitReversed(GPCRC));
}

uint16_t crc16_dect_r(const void *data,size_t len) {
	GPCRC_Init_TypeDef					initGpcrc;

	initGpcrc.crcPoly = 0x0589;
	initGpcrc.initValue = 0x0000;
	initGpcrc.reverseBits = true;
	_crcCommon(data, len, &initGpcrc);
	return (GPCRC_DataReadBitReversed(GPCRC) ^ 0x1);
}

uint16_t crc16_en13757(const void *data,size_t len) {
	GPCRC_Init_TypeDef					initGpcrc;

	initGpcrc.crcPoly = 0x3D65;
	initGpcrc.initValue = 0x0000;
	initGpcrc.reverseBits = true;
	_crcCommon(data, len, &initGpcrc);
	return (GPCRC_DataReadBitReversed(GPCRC) ^ 0xFFFF);
}

uint16_t crc16_t10dif(const void *data,size_t len) {
	GPCRC_Init_TypeDef					initGpcrc;

	initGpcrc.crcPoly = 0x8BB7;
	initGpcrc.initValue = 0x0000;
	initGpcrc.reverseBits = true;
	_crcCommon(data, len, &initGpcrc);
	return (GPCRC_DataReadBitReversed(GPCRC));
}

uint16_t crc16_modbus(const void *data,size_t len) {
	GPCRC_Init_TypeDef					initGpcrc;

	initGpcrc.crcPoly = 0x8005;
	initGpcrc.initValue = 0xFFFF;
	initGpcrc.reverseBits = false;
	_crcCommon(data, len, &initGpcrc);
	return (GPCRC_DataRead(GPCRC));
}

uint32_t crc32_posix(const void *data,size_t len) {
	GPCRC_Init_TypeDef					initGpcrc;

	initGpcrc.crcPoly = 0x04C11DB7;
	initGpcrc.initValue = 0x0000;
	initGpcrc.reverseBits = true;
	_crcCommon(data, len, &initGpcrc);
	return (GPCRC_DataReadBitReversed(GPCRC) ^ 0xFFFFFFFF);
}

uint32_t crc32_mpeg2(const void *data,size_t len) {
	GPCRC_Init_TypeDef					initGpcrc;

	initGpcrc.crcPoly = 0x04C11DB7;
	initGpcrc.initValue = 0xFFFFFFFF;
	initGpcrc.reverseBits = true;
	_crcCommon(data, len, &initGpcrc);
	return (GPCRC_DataReadBitReversed(GPCRC));
}

uint32_t crc32_jamcrc(const void *data,size_t len) {
	GPCRC_Init_TypeDef					initGpcrc;

	initGpcrc.crcPoly = 0x04C11DB7;
	initGpcrc.initValue = 0xFFFFFFFF;
	initGpcrc.reverseBits = false;
	_crcCommon(data, len, &initGpcrc);
	return (GPCRC_DataRead(GPCRC));
}

uint32_t crc32_bzip2(const void *data,size_t len) {
	GPCRC_Init_TypeDef					initGpcrc;

	initGpcrc.crcPoly = 0x04C11DB7;
	initGpcrc.initValue = 0xFFFFFFFF;
	initGpcrc.reverseBits = true;
	_crcCommon(data, len, &initGpcrc);
	return (GPCRC_DataReadBitReversed(GPCRC) ^ 0xFFFFFFFF);
}

uint32_t crc32_zlib(const void *data,size_t len) {
	GPCRC_Init_TypeDef					initGpcrc;

	initGpcrc.crcPoly = 0x04C11DB7;
	initGpcrc.initValue = 0xFFFFFFFF;
	initGpcrc.reverseBits = false;
	_crcCommon(data, len, &initGpcrc);
	return (GPCRC_DataRead(GPCRC) ^ 0xFFFFFFFF);
}

void crc_common(const void *data, size_t len, GPCRC_Init_TypeDef *initGpcrc) {
	_crcCommon(data, len, initGpcrc);
}