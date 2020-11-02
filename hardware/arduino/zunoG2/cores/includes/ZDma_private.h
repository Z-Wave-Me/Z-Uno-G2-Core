#ifndef ZDMA_PRIVATE_H
#define ZDMA_PRIVATE_H

#include "ZDma_define.h"

typedef struct							ZunoZDmaList_s
{
	struct ZunoZDmaList_s				*next;
	ZunoZDmaUser_t						*userLp;
	size_t								len;
	LDMA_Descriptor_t					transfer_desc[2];
	uint8_t								chZDma;
	ZDmaMode_t							mode;
}										ZunoZDmaList_t;

class ZDMAClass {
	public:
		ZDMAClass(void);
		ZunoError_t								toMemoryPeripheral(ZunoZDmaUser_t *userLp, ZDMA_PeripheralSignal_t peripheralSignal, void *dst, void *src, size_t len, ZDma_DataSize_t size);
	
	private:
		ZunoError_t								_transfer(ZunoZDmaUser_t *userLp, ZDMA_PeripheralSignal_t peripheralSignal, void *dst, void *src, size_t len, ZDma_DataSize_t size,
												ZDmaMode_t mode, ZDmaDirection_t direction);
		size_t									_modeBasicLen(LDMA_Descriptor_t *transfer_desc, size_t len);
		static void								_LDMA_IRQHandler(void * pdata);
		inline ZunoError_t						_getZDma(ZunoZDmaList_t **list_out);
		inline void								_addList(ZunoZDmaList_t *list);
		inline ZunoZDmaList_t					*_findList(uint8_t chZDma);
		ZunoZDmaList_t							*list;
		volatile uint8_t						bitZDmaLock;
};

extern ZDMAClass ZDMA;

#endif // ZDMA_PRIVATE_H