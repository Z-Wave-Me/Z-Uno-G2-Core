#ifndef ZDMA_PRIVATE_H
#define ZDMA_PRIVATE_H

#include "ZDma_define.h"

typedef enum {
	zdmaDirectionMemToPeripheral,
	zdmaDirectionPeripheralToMem
} ZDmaDirection_t;

typedef struct							ZunoZDmaList_s
{
	size_t								uniqId;//Unique number for external access
	size_t								counter;//counter how much data still needs to be sent
	size_t								loop;
	size_t								buff;
	size_t								len;
	LDMA_Descriptor_t					transfer_desc;
}										ZunoZDmaList_t;

class ZDMAClass {
	public:
		ZDMAClass(void);
		ZunoError_t								toMemoryPeripheral(size_t uniqId, ZDMA_PeripheralSignal_t peripheralSignal, void *dst, void *src, size_t len, ZDma_DataSize_t size);
		ZunoError_t								toMemoryPeripheral(size_t uniqId, ZDMA_PeripheralSignal_t peripheralSignal, void *dst, void *src, size_t len, ZDma_DataSize_t size, ZunoZDmaExt_t *lpExt);
		ZunoError_t								toPeripheralMemory(size_t uniqId, ZDMA_PeripheralSignal_t peripheralSignal, void *dst, void *src, size_t len, ZDma_DataSize_t size);
		ZunoError_t								toPeripheralMemory(size_t uniqId, ZDMA_PeripheralSignal_t peripheralSignal, void *dst, void *src, size_t len, ZDma_DataSize_t size, ZunoZDmaExt_t *lpExt);
		uint8_t									isProcessing(size_t uniqId);
		void									stopTransfer(size_t uniqId, uint8_t bForce);
		size_t									transferRemainingCount(size_t uniqId);
	
	private:
		ZunoError_t								_transfer(size_t uniqId, ZDMA_PeripheralSignal_t peripheralSignal, void *dst, void *src, size_t len, ZDma_DataSize_t size, ZDmaDirection_t direction, ZunoZDmaExt_t *lpExt);
		size_t									_modeBasicLen(LDMA_Descriptor_t *transfer_desc, size_t len);
		static void								_LDMA_IRQHandler(void * pdata);
		inline ZunoError_t						_getZDma(ZunoZDmaList_t **list_out, uint8_t *outchZDma);
		inline void								_addList(ZunoZDmaList_t *list, uint8_t chZDma);
		inline ZunoZDmaList_t					*_findList(uint8_t chZDma);
		ZunoZDmaList_t							*_findListUniqId(size_t uniqId, uint8_t *chZDma);
		uint16_t								_listCh[DMA_CHAN_COUNT];
		volatile uint8_t						bitZDmaLock;
};

extern ZDMAClass ZDMA;

#endif // ZDMA_PRIVATE_H