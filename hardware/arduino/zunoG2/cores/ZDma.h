#ifndef ZDMA_H
#define ZDMA_H

#include "ZDma_define.h"
#include "Threading.h"

typedef struct							ZunoZDmaList_s
{
	uint8_t								(*f)(size_t);
	size_t								param;
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
		ZunoError_t								toMemoryPeripheral(size_t uniqId, ZDMA_PeripheralSignal_t peripheralSignal, void *dest, void *src, size_t len, ZDma_DataSize_t size);
		ZunoError_t								toMemoryPeripheral(size_t uniqId, ZDMA_PeripheralSignal_t peripheralSignal, void *dest, void *src, size_t len, ZDma_DataSize_t size, ZunoZDmaExt_t *lpExt);
		ZunoError_t								toPeripheralMemory(size_t uniqId, ZDMA_PeripheralSignal_t peripheralSignal, void *dest, void *src, size_t len, ZDma_DataSize_t size);
		ZunoError_t								toPeripheralMemory(size_t uniqId, ZDMA_PeripheralSignal_t peripheralSignal, void *dest, void *src, size_t len, ZDma_DataSize_t size, ZunoZDmaExt_t *lpExt);
		uint8_t									isProcessing(size_t uniqId);
		void									stopTransfer(size_t uniqId, uint8_t bForce);
		void									waitTransfer(size_t uniqId);
		ZunoError_t								transferReceivedCount(size_t uniqId, size_t *count);
		volatile uint8_t						bitZDmaLock;
	
	private:
		inline uint8_t							_stopTransfer(size_t uniqId, uint8_t bForce);
		inline ZunoError_t						_transferLock(size_t uniqId, ZDMA_PeripheralSignal_t peripheralSignal, void *dest, void *src, size_t len, ZDma_DataSize_t size, ZunoZDmaExt_t *lpExt);
		inline ZunoError_t						_transfer(size_t uniqId, ZDMA_PeripheralSignal_t peripheralSignal, void *dest, void *src, size_t len, ZDma_DataSize_t size, ZunoZDmaExt_t *lpExt);
		static void								_LDMA_IRQHandler(void * pdata);
		inline void								_reload(ZunoZDmaList_t *list, LDMA_Descriptor_t *transfer_desc, size_t counter, size_t chZDma, size_t chmask);
		inline ZunoError_t						_getZDma(ZunoZDmaList_t **list_out, size_t *outchZDma);
		inline void								_addList(ZunoZDmaList_t *list, uint8_t chZDma);
		inline ZunoZDmaList_t					*_findList(uint8_t chZDma);
		inline ZunoZDmaList_t					*_findListUniqId(size_t uniqId, size_t *chZDma);
		static const uint8_t					_multSize[];
		znMutex									_mutex;
		uint16_t								_listCh[DMA_CHAN_COUNT];
};

extern ZDMAClass ZDMA;

#endif // ZDMA_H