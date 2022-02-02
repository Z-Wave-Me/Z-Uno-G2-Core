#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "em_gpcrc.h"
#include "em_cmu.h"
#include "CrcClass.h"
#include "Arduino.h"
#include "Sync.h"
// #include "em_ldma.h"
// #include "LdmaClass.h"

static ZunoSync_t _SyncCrcClass = ZUNO_SYNC_INIT_DEFAULT_OPEN(SyncMasterCrcClass);
static uint8_t _CrcClassKey = true;

static void _crcSet(GPCRC_Init_TypeDef *initGpcrc) {
	static uint8_t				test = false;
	
	if (test == false) {
		CMU_ClockEnable(cmuClock_GPCRC, true);
		test = true;
	}
	initGpcrc->enable = true;
	initGpcrc->reverseByteOrder = false;
	initGpcrc->enableByteMode = false;
	GPCRC_Init(GPCRC, initGpcrc);
	GPCRC_Start(GPCRC);
}

static void _crcCommon(const void *data, size_t len, GPCRC_Init_TypeDef *initGpcrc) {
	const uint8_t					*e;
	const uint8_t					*b;
	const uint32_t					*tmp;

	if (zunoSyncLockWrite(&_SyncCrcClass, SyncMasterCrcClass, &_CrcClassKey) != ZunoErrorOk)
		return ;
	initGpcrc->autoInit = false;
	_crcSet(initGpcrc);
	b = (uint8_t *)data;
	e = b + len;
	if (len >= (sizeof(uint32_t) * 0x2 - 0x1)) {//Проверяем рационально по байту или может по слову лучше
		while (((uint32_t)b & 0x3) != 0x0)//Выравниваем адрес под  слово используемое в системе в arm x86 - выравниваем под 4 байт
			GPCRC_InputU8(GPCRC, b++[0x0]);
		tmp = (const uint32_t *)b;
		b = (const uint8_t *)((uint32_t)e & (0x0 - sizeof(uint32_t)));
		while (tmp < (const uint32_t *)b)
			GPCRC_InputU32(GPCRC, tmp++[0x0]);
	}
	while (b < e)//Если остались не добитые байты добьем
		GPCRC_InputU8(GPCRC, b++[0]);
	zunoSyncReleseWrite(&_SyncCrcClass, SyncMasterCrcClass, &_CrcClassKey);
}

// static void _crcCommonDma(const void *data, size_t len, GPCRC_Init_TypeDef *initGpcrc) {
// 	const uint8_t						*b;
// 	const uint8_t						*e;
// 	ssize_t								channel;
// 	LdmaClassTransferSingle_t			array;

// 	channel = 0;
// 	initGpcrc->autoInit = true;
// 	_crcSet(initGpcrc);
// 	b = (const uint8_t *)data;
// 	e = b + len;
// 	if (len >= (sizeof(uint32_t) * 3 - 1)) {//Проверяем рационально по байту или может по слову лучше
// 		while (((size_t)b & (sizeof(uint32_t) - 1)) != 0)//Выравниваем адрес под  слово используемое в системе в arm x86 - выравниваем под 4 байт
// 			GPCRC_InputU8(GPCRC, b++[0]);
// 		len = (e - b) / sizeof(uint32_t);
// 		channel = LdmaClass::transferSingle(b, (void *)&GPCRC->INPUTDATA, len, LdmaClassSignal_NONE, ldmaCtrlSizeWord, ldmaCtrlSrcIncOne, ldmaCtrlDstIncNone, &array);
// 		// delay(len / 0x1800);//Считаем что 0x1800 считает за 1 ms
// 		while (LdmaClass::transferDone(channel) == false)
// 			__NOP();
// 		b = b + (len * sizeof(uint32_t));
// 	}
// 	while (b < e)//Если остались не добитые байты добьем
// 		GPCRC_InputU8(GPCRC, b++[0]);
// }


/* Public Methods */
uint8_t CrcClass::crc8_sapi(uint8_t initValue, const void *data, size_t len) {
	const uint8_t				*b;
	const uint8_t				*e;
	uint8_t						crc8;

	b = (uint8_t *)data;
	e = &b[len];
	crc8 = initValue;
	while(b < e)
		crc8 ^= b++[0];
	return (crc8);
}


/* Private Methods */
uint32_t CrcClass::_crc_RefInFalse_RefOutFalse(uint32_t crcPoly, uint32_t initValue, const void *data, size_t len) {
	GPCRC_Init_TypeDef					initGpcrc;

	initGpcrc.crcPoly = crcPoly;
	initGpcrc.initValue = initValue;
	initGpcrc.reverseBits = true;
	_crcCommon(data, len, &initGpcrc);
	return (GPCRC_DataReadBitReversed(GPCRC));
}

uint32_t CrcClass::_crc_RefInTrue_RefOutTrue(uint32_t crcPoly, uint32_t initValue, const void *data, size_t len) {
	GPCRC_Init_TypeDef					initGpcrc;

	initGpcrc.crcPoly = crcPoly;
	initGpcrc.initValue = initValue;
	initGpcrc.reverseBits = false;
	_crcCommon(data, len, &initGpcrc);
	return (GPCRC_DataRead(GPCRC));
}


// uint32_t CrcClass::_dma_crc_RefInFalse_RefOutFalse(uint32_t crcPoly, uint32_t initValue, const void *data, size_t len) {
// 	GPCRC_Init_TypeDef					initGpcrc;

// 	initGpcrc.crcPoly = crcPoly;
// 	initGpcrc.initValue = initValue;
// 	initGpcrc.reverseBits = true;
// 	_crcCommonDma(data, len, &initGpcrc);
// 	return (GPCRC_DataReadBitReversed(GPCRC));
// }

// uint32_t CrcClass::_dma_crc_RefInTrue_RefOutTrue(uint32_t crcPoly, uint32_t initValue, const void *data, size_t len) {
// 	GPCRC_Init_TypeDef					initGpcrc;

// 	initGpcrc.crcPoly = crcPoly;
// 	initGpcrc.initValue = initValue;
// 	initGpcrc.reverseBits = false;
// 	_crcCommonDma(data, len, &initGpcrc);
// 	return (GPCRC_DataRead(GPCRC));
// }