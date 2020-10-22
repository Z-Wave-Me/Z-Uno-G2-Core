#include "Arduino.h"
#include "ZDma_private.h"
#include "stdlib.h"

// if ( ZDMA_IRQ_PRIORITY > 7 ) {
// return ZunoErrorDma;
// }
/// DMADRV DMA interrupt priority configuration option.
/// Set DMA interrupt priority. Range is 0..7, 0 is highest priority.
#if (__NVIC_PRIO_BITS == 2)
	#define ZDMA_IRQ_PRIORITY			3
#else
	#define ZDMA_IRQ_PRIORITY			4
#endif

/// DMADRV DMA channel priority configuration option.
/// Set DMA channel priority. Range 0..EMDRV_DMADRV_DMA_CH_COUNT.
/// On LDMA, this will configure channel 0 to CH_PRIORITY - 1 as fixed priority,
/// and CH_PRIORITY to CH_COUNT as round-robin.
/// On DMA, this will have no impact, since high priority is unuseable with
/// peripherals.
#define ZDMA_CH_PRIORITY				0

/// Maximum length of one DMA transfer.
#define ZDMA_MAX_XFER_COUNT ((size_t)((_LDMA_CH_CTRL_XFERCNT_MASK >> _LDMA_CH_CTRL_XFERCNT_SHIFT) + 1))

#if DMA_CHAN_COUNT > 8
	#error "Error DMA_CHAN_COUNT big too - bitZDma"
#endif

extern unsigned long  __bss_start__;
static const uint8_t _multSize[] = {1, 2, 4};

/* Public Constructors */
ZDMAClass::ZDMAClass(void): bitZDmaLock(0) {
	memset(&this->_listCh[0], 0, sizeof(this->_listCh));
}

uint8_t ZDMAClass::isProcessing(size_t uniqId) {
	if (this->_findListUniqId(uniqId) == 0)
		return (false);
	return (true);
}

void ZDMAClass::stopTransfer(size_t uniqId, uint8_t bForce) {
	ZunoZDmaList_t			*list;
	uint8_t					chZDma;

	if ((list = this->_findListUniqId(uniqId)) == 0)
		return ;
	if (bForce == false) {
		list->loop = 0;
		return ;
	}
	chZDma = list->chZDma;
	LDMA_StopTransfer(chZDma);
	list->uniqId = 0;
	this->bitZDmaLock ^= (1 << chZDma);
}

ZunoError_t ZDMAClass::toMemoryPeripheral(size_t uniqId, ZDMA_PeripheralSignal_t peripheralSignal, void *dst, void *src, size_t len, ZDma_DataSize_t size) {
	ZunoZDmaExt_t					lpExt;

	lpExt = ZDMA_EXT_INIT_DEFAULT;
	return (this->_transfer(uniqId, peripheralSignal, dst, src, len, size, zdmaDirectionMemToPeripheral, &lpExt));
}

ZunoError_t ZDMAClass::toMemoryPeripheral(size_t uniqId, ZDMA_PeripheralSignal_t peripheralSignal, void *dst, void *src, size_t len, ZDma_DataSize_t size, ZunoZDmaExt_t *lpExt) {
	return (this->_transfer(uniqId, peripheralSignal, dst, src, len, size, zdmaDirectionMemToPeripheral, lpExt));
}

ZunoError_t ZDMAClass::toPeripheralMemory(size_t uniqId, ZDMA_PeripheralSignal_t peripheralSignal, void *dst, void *src, size_t len, ZDma_DataSize_t size) {
	ZunoZDmaExt_t					lpExt;

	lpExt = ZDMA_EXT_INIT_DEFAULT;
	return (this->_transfer(uniqId, peripheralSignal, dst, src, len, size, zdmaDirectionPeripheralToMem, &lpExt));
}

/* Private Methods */
ZunoError_t ZDMAClass::_transfer(size_t uniqId, ZDMA_PeripheralSignal_t peripheralSignal, void *dst, void *src, size_t len, ZDma_DataSize_t size, ZDmaDirection_t direction, ZunoZDmaExt_t *lpExt) {
	ZunoError_t				ret;
	ZunoZDmaList_t			*list;
	LDMA_TransferCfg_t		transfer_cfg;
	LDMA_Descriptor_t		*transfer_desc;
	size_t					loop;

	if (len == 0)
		return (ZunoErrorOk);
	if (uniqId == 0 || (loop = lpExt->loop) == 0)
		return (ZunoErrorDma);
	if ((ret = this->_getZDma(&list)) != ZunoErrorOk)
		return (ret);
	list->uniqId = uniqId;
	list->srcLen = len;
	list->srcAddr = (uint32_t)(uint8_t *)src;
	list->loop = (loop == ZDMA_EXT_LOOP_INFINITY) ? loop : loop - 1;
	transfer_desc = &list->transfer_desc[0];
	if (direction == zdmaDirectionMemToPeripheral)
		transfer_desc[0] = LDMA_DESCRIPTOR_SINGLE_M2P_BYTE(0, 0, 1);
	else
		transfer_desc[0] = LDMA_DESCRIPTOR_SINGLE_P2M_BYTE(0, 0, 1);
	transfer_desc->xfer.dstAddr = (uint32_t)(uint8_t *)dst;
	transfer_desc->xfer.srcAddr = (uint32_t)(uint8_t *)src;
	transfer_desc->xfer.size = size;
	if (len > ZDMA_MAX_XFER_COUNT) {
		transfer_desc->xfer.linkMode = ldmaLinkModeRel;
		transfer_desc->xfer.link = true;
		transfer_desc->xfer.linkAddr = 4;
		transfer_desc[1] = transfer_desc[0];
		transfer_desc[1].xfer.linkAddr = -4;
		list->counter = this->_modeBasicLen(transfer_desc, len);
	}
	else {
		list->counter = 0;
		transfer_desc->xfer.xferCnt = len - 1;
	}
	transfer_cfg = LDMA_TRANSFER_CFG_PERIPHERAL(peripheralSignal);
	LDMA_StartTransfer(list->chZDma, &transfer_cfg, transfer_desc);
	return (ZunoErrorOk);
}

void ZDMAClass::_LDMA_IRQHandler(void) {
	LDMA_Descriptor_t	*transfer_desc;
	size_t				pending;
	size_t				chZDma;
	size_t				chmask;
	ZunoZDmaList_t		*list;
	size_t				counter;
	size_t				loop;

	pending = LDMA_IntGetEnabled();
	if (pending & LDMA_IF_ERROR)/* Check for LDMA error. */
		while (true)/* Loop to enable debugger to see what has happened. */
			__NOP();/* Wait forever. */
	chZDma = 0;
	while (chZDma < DMA_CHAN_COUNT) {/* Iterate over all LDMA channels. */
		chmask = 1 << chZDma;
		
		if ((pending & chmask) != 0) {
			list = ZDMA._findList(chZDma);
			transfer_desc = &list->transfer_desc[0];
			if ((counter = list->counter) == 0) {
  				if (LDMA_TransferDone(chZDma) == true) {
					if ((loop = list->loop) == 0) {
						list->uniqId = 0;
						ZDMA.bitZDmaLock ^= chmask;
					}
					else {
						list->loop = (loop == ZDMA_EXT_LOOP_INFINITY) ? loop : loop - 1;
						transfer_desc[0].xfer.srcAddr = list->srcAddr;
						if ((counter = list->srcLen) > ZDMA_MAX_XFER_COUNT) {
							transfer_desc[0].xfer.link = true;
							list->counter = ZDMA._modeBasicLen(transfer_desc, counter);
						}
						else
							transfer_desc->xfer.xferCnt = counter - 1;
						LDMA->CH[chZDma].LINK = (uint32_t)transfer_desc & _LDMA_CH_LINK_LINKADDR_MASK;
						BUS_RegMaskedClear(&LDMA->CHDONE, chmask);// Clear the done flag. 
						LDMA->LINKLOAD = chmask;// Start a transfer by loading the descriptor.
					}
				}
			}
			else if (counter <= ZDMA_MAX_XFER_COUNT) {
				transfer_desc[0].xfer.srcAddr = transfer_desc[1].xfer.srcAddr + ((transfer_desc[1].xfer.xferCnt + 1) * _multSize[transfer_desc[1].xfer.size]);
				transfer_desc[0].xfer.xferCnt = counter - 1;
				transfer_desc[0].xfer.link = false;
				list->counter = 0;
			}
			else {
				transfer_desc[0].xfer.srcAddr = transfer_desc[1].xfer.srcAddr + ((transfer_desc[1].xfer.xferCnt + 1) * _multSize[transfer_desc[1].xfer.size]);
				list->counter = ZDMA._modeBasicLen(transfer_desc, counter);
			}
			LDMA_IntClear(chmask);
		}
		chZDma++;
	}
}

size_t ZDMAClass::_modeBasicLen(LDMA_Descriptor_t *transfer_desc, size_t len) {
	size_t					tempos;

	len--;
	if (len >= (ZDMA_MAX_XFER_COUNT * 2))
		tempos = ZDMA_MAX_XFER_COUNT;
	else
		tempos = len / 2;
	len = len - tempos * 2 + 1;
	transfer_desc[0].xfer.xferCnt = tempos - 1;
	transfer_desc[1].xfer.xferCnt = tempos - 1;
	transfer_desc[1].xfer.srcAddr = transfer_desc[0].xfer.srcAddr + (tempos * _multSize[transfer_desc[0].xfer.size]);
	return (len);
}

inline ZunoError_t ZDMAClass::_getZDma(ZunoZDmaList_t **list_out) {
	LDMA_Init_t				ldmaInit;
	ZunoError_t				ret;
	size_t					bitZDmaLock;
	uint8_t					chZDma;
	ZunoZDmaList_t			*list;
	
	if (g_bit_field.bZDMAInit == false) {
		if ((ret = zunoAttachSysHandler(ZUNO_HANDLER_IRQ, ZUNO_IRQVEC_LDMA, (void *)this->_LDMA_IRQHandler)) != ZunoErrorOk)
			return (ret);
		g_bit_field.bZDMAInit = true;
		ldmaInit = LDMA_INIT_DEFAULT;
		ldmaInit.ldmaInitCtrlNumFixed = ZDMA_CH_PRIORITY;
		ldmaInit.ldmaInitIrqPriority = ZDMA_IRQ_PRIORITY;
		LDMA_Init(&ldmaInit);
	}
	if ((bitZDmaLock = this->bitZDmaLock) == 0xFF) 
		return (ZunoErrorDma);
	chZDma = 0;
	while ((bitZDmaLock & 0x1) != 0) {
		chZDma++;
		bitZDmaLock = bitZDmaLock >> 1;
	}
	this->bitZDmaLock |= 1 << chZDma;
	if ((list = this->_findList(chZDma)) == 0) {
		if ((list = (ZunoZDmaList_t *)malloc(sizeof(ZunoZDmaList_t))) == 0) {
			this->bitZDmaLock ^= 1 << chZDma;
			return (ZunoErrorMemory);
		}
		list->chZDma = chZDma;
		this->_addList(list, chZDma);
	}
	*list_out = list;
	return (ZunoErrorOk);
}

inline void ZDMAClass::_addList(ZunoZDmaList_t *list, uint8_t chZDma) {
	this->_listCh[chZDma] = (uint16_t)((size_t)list - (size_t)&__bss_start__);
}

inline ZunoZDmaList_t *ZDMAClass::_findList(uint8_t chZDma) {
	size_t					out;

	if ((out = this->_listCh[chZDma]) == 0)
		return (0);
	return ((ZunoZDmaList_t *)(out + (size_t)&__bss_start__));
}

ZunoZDmaList_t *ZDMAClass::_findListUniqId(size_t uniqId) {
	size_t					list;
	uint16_t				*b;
	uint16_t				*e;

	b = &this->_listCh[0];
	e = &b[DMA_CHAN_COUNT];
	while (b < e) {
		if ((list = b++[0]) == 0)
			continue ;
		list = list + (size_t)&__bss_start__;
		if (((ZunoZDmaList_t *)list)->uniqId == uniqId)
			return ((ZunoZDmaList_t *)list);
	}
	return (0);
}

/* Preinstantiate Objects */
ZDMAClass ZDMA = ZDMAClass();