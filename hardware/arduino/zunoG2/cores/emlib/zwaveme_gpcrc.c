#include <stdint.h>
#include <stddef.h>
#include "zwaveme_gpcrc.h"

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

uint8_t crc8_sapi(const void *data, size_t len) {
	const uint8_t				*b;
	const uint8_t				*e;
	uint8_t						crc8;

	b = (uint8_t *)data;
	e = &b[len];
	crc8 = 0xFF;
	while(b < e)
		crc8 ^= b++[0];
	return (crc8);
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
	return (crc32_zlibStream(0xFFFFFFFF, data, len) ^ 0xFFFFFFFF);
}

uint32_t crc32_zlibStream(uint32_t initValue, const void *data, size_t len) {
	GPCRC_Init_TypeDef					initGpcrc;

	initGpcrc.crcPoly = 0x04C11DB7;
	initGpcrc.initValue = initValue;
	initGpcrc.reverseBits = false;
	_crcCommon(data, len, &initGpcrc);
	return (GPCRC_DataRead(GPCRC));
}