#ifndef ZDMA_H
#define ZDMA_H

#include "ZDma_define.h"

class ZDMAClass {
	public:
		ZDMAClass(void);
		ZunoError_t								toMemoryPeripheral(ZunoZDmaUser_t *userLp, ZDMA_PeripheralSignal_t peripheralSignal, void *dst, void *src,
												size_t len, ZDma_DataSize_t size);
};

extern ZDMAClass ZDMA;

#endif // ZDMA_H