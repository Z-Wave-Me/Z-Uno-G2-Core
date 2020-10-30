#ifndef ZDMA_H
#define ZDMA_H

#include "ZDma_define.h"

class ZDMAClass {
	public:
		ZunoError_t								toMemoryPeripheral(size_t uniqId, ZDMA_PeripheralSignal_t peripheralSignal, void *dst, void *src, size_t len, ZDma_DataSize_t size);
		ZunoError_t								toMemoryPeripheral(size_t uniqId, ZDMA_PeripheralSignal_t peripheralSignal, void *dst, void *src, size_t len, ZDma_DataSize_t size, ZunoZDmaExt_t *lpExt);
		ZunoError_t								toPeripheralMemory(size_t uniqId, ZDMA_PeripheralSignal_t peripheralSignal, void *dst, void *src, size_t len, ZDma_DataSize_t size);
		ZunoError_t								toPeripheralMemory(size_t uniqId, ZDMA_PeripheralSignal_t peripheralSignal, void *dst, void *src, size_t len, ZDma_DataSize_t size, ZunoZDmaExt_t *lpExt);
		uint8_t									isProcessing(size_t uniqId);
		void									stopTransfer(size_t uniqId, uint8_t bForce);
		size_t									transferRemainingCount(size_t uniqId);
};

extern ZDMAClass ZDMA;

#endif // ZDMA_H