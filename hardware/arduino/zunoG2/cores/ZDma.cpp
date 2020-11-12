#include "Arduino.h"
#include "Threading.h"
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

#define ZDMA_STOPTRANSEFR_WAIT			false
#define ZDMA_STOPTRANSEFR_BREAK			true

extern unsigned long  __bss_start__;
static const uint8_t _multSize[] = {1, 2, 4};

static znMutex g_mutex = znMutex();

/* Public Constructors */
ZDMAClass::ZDMAClass(void): bitZDmaLock(0), _listCh{0} {

}

uint8_t ZDMAClass::isProcessing(size_t uniqId) {
	uint8_t					chZDma;
	ZunoZDmaList_t			*list;

	g_mutex.lock();
	list = this->_findListUniqId(uniqId, &chZDma);
	g_mutex.unlock();
	if (list == 0)
		return (false);
	return (true);
}

ZunoError_t ZDMAClass::transferReceivedCount(size_t uniqId, size_t *count) {
	uint8_t					chZDma;
	ZunoZDmaList_t			*list;
	ZunoError_t				ret;

	g_mutex.lock();
	list = this->_findListUniqId(uniqId, &chZDma);
	if (list == 0)
		ret = ZunoErrorDmaInvalidUniqId;
	else {
		count[0] = (list ->len - (LDMA_TransferRemainingCount(chZDma) + list->counter));
		ret = ZunoErrorOk;
	}
	g_mutex.unlock();
	return (ret);
}

void ZDMAClass::stopTransfer(size_t uniqId, uint8_t bForce) {
	uint8_t			out;


	while (0xFF) {
		g_mutex.lock();
		out = this->_stopTransfer(uniqId, bForce);
		g_mutex.unlock();
		if (out == ZDMA_STOPTRANSEFR_BREAK)
			break ;
		delay(1);
	}
}

void ZDMAClass::waitTransfer(size_t uniqId) {
	ZunoZDmaList_t			*list;
	uint8_t					chZDma;
	void					*handler;

	handler = zunoGetCurrentThreadHandle();
	g_mutex.lock();
	if ((list = this->_findListUniqId(uniqId, &chZDma)) != 0 && list->handler == 0) {
		list->handler = handler;
		g_mutex.unlock();
		zunoSuspendThread(handler);
	}
	else
		g_mutex.unlock();
}

ZunoError_t ZDMAClass::toMemoryPeripheral(size_t uniqId, ZDMA_PeripheralSignal_t peripheralSignal, void *dst, void *src, size_t len, ZDma_DataSize_t size) {
	ZunoZDmaExt_t					lpExt;

	lpExt = ZDMA_EXT_INIT_DEFAULT;
	return (this->_transferLock(uniqId, peripheralSignal, dst, src, len, size, zdmaDirectionMemToPeripheral, &lpExt));
}

ZunoError_t ZDMAClass::toMemoryPeripheral(size_t uniqId, ZDMA_PeripheralSignal_t peripheralSignal, void *dst, void *src, size_t len, ZDma_DataSize_t size, ZunoZDmaExt_t *lpExt) {
	return (this->_transferLock(uniqId, peripheralSignal, dst, src, len, size, zdmaDirectionMemToPeripheral, lpExt));
}

ZunoError_t ZDMAClass::toPeripheralMemory(size_t uniqId, ZDMA_PeripheralSignal_t peripheralSignal, void *dst, void *src, size_t len, ZDma_DataSize_t size) {
	ZunoZDmaExt_t					lpExt;

	lpExt = ZDMA_EXT_INIT_DEFAULT;
	return (this->_transferLock(uniqId, peripheralSignal, dst, src, len, size, zdmaDirectionPeripheralToMem, &lpExt));
}

ZunoError_t ZDMAClass::toPeripheralMemory(size_t uniqId, ZDMA_PeripheralSignal_t peripheralSignal, void *dst, void *src, size_t len, ZDma_DataSize_t size, ZunoZDmaExt_t *lpExt) {
	return (this->_transferLock(uniqId, peripheralSignal, dst, src, len, size, zdmaDirectionPeripheralToMem, lpExt));
}

/* Private Methods */
inline ZunoError_t ZDMAClass::_transferLock(size_t uniqId, ZDMA_PeripheralSignal_t peripheralSignal, void *dst, void *src, size_t len, ZDma_DataSize_t size, ZDmaDirection_t direction, ZunoZDmaExt_t *lpExt) {
	ZunoError_t				ret;

	g_mutex.lock();
	ret = this->_transfer(uniqId, peripheralSignal, dst, src, len, size, direction, lpExt);
	g_mutex.unlock();
	return (ret);
}

inline ZunoError_t ZDMAClass::_transfer(size_t uniqId, ZDMA_PeripheralSignal_t peripheralSignal, void *dst, void *src, size_t len, ZDma_DataSize_t size, ZDmaDirection_t direction, ZunoZDmaExt_t *lpExt) {
	ZunoError_t				ret;
	ZunoZDmaList_t			*list;
	LDMA_TransferCfg_t		transfer_cfg;
	LDMA_Descriptor_t		*transfer_desc;
	size_t					loop;
	size_t					buff;
	uint8_t					chZDma;

	if (uniqId == 0)
		return (ZunoErrorDmaInvalidUniqId);
	if (len == 0 || (loop = lpExt->loop) == 0)
		return (ZunoErrorOk);
	list = this->_findListUniqId(uniqId, &chZDma);
	if ((lpExt->bReconfig == true)) {
		if (list == 0 || list->handler != 0)
			return (ZunoErrorDmaInvalidReconfig);
		LDMA_StopTransfer(chZDma);
	}
	else {
		if (list != 0)
			return (ZunoErrorDmaUniqIdAlready);
		if ((ret = this->_getZDma(&list, &chZDma)) != ZunoErrorOk)
			return (ret);
		list->uniqId = uniqId;
	}
	list->f = lpExt->f;
	list->param = lpExt->param;
	list->handler = 0;
	list->len = len;
	list->loop = (loop == ZDMA_EXT_LOOP_INFINITY) ? loop : loop - 1;
	transfer_desc = &list->transfer_desc;
	if (direction == zdmaDirectionMemToPeripheral) {
		transfer_desc[0] = LDMA_DESCRIPTOR_SINGLE_M2P_BYTE(0, 0, 1);
		buff = (uint32_t)(uint8_t *)src;
	}
	else {
		transfer_desc[0] = LDMA_DESCRIPTOR_SINGLE_P2M_BYTE(0, 0, 1);
		buff = (uint32_t)(uint8_t *)dst;
	}
	list->buff = buff;
	transfer_desc->xfer.dstAddr = (uint32_t)(uint8_t *)dst;
	transfer_desc->xfer.srcAddr = (uint32_t)(uint8_t *)src;
	transfer_desc->xfer.size = size;
	if (len > ZDMA_MAX_XFER_COUNT) {
		list->counter = len - ZDMA_MAX_XFER_COUNT;
		len = ZDMA_MAX_XFER_COUNT - 1;
	}
	else {
		list->counter = 0;
		len = len - 1;
	}
	transfer_desc->xfer.xferCnt = len;
	transfer_cfg = LDMA_TRANSFER_CFG_PERIPHERAL(peripheralSignal);
	LDMA_StartTransfer(chZDma, &transfer_cfg, transfer_desc);
	return (ZunoErrorOk);
}


static void _reload(ZunoZDmaList_t *list, LDMA_Descriptor_t *transfer_desc, size_t counter, size_t chZDma, size_t chmask) {
	if (counter > ZDMA_MAX_XFER_COUNT) {
		list->counter = counter - ZDMA_MAX_XFER_COUNT;
		counter = ZDMA_MAX_XFER_COUNT - 1;
	}
	else {
		list->counter = 0;
		counter = counter - 1;
	}
	transfer_desc->xfer.xferCnt = counter;
	LDMA->CH[chZDma].LINK = (uint32_t)transfer_desc & _LDMA_CH_LINK_LINKADDR_MASK;
	BUS_RegMaskedClear(&LDMA->CHDONE, chmask);// Clear the done flag.
	LDMA->LINKLOAD = chmask;// Start a transfer by loading the descriptor.
}

void ZDMAClass::_LDMA_IRQHandler(void * param) {
	LDMA_Descriptor_t	*transfer_desc;
	size_t				pending;
	size_t				chZDma;
	size_t				chmask;
	ZunoZDmaList_t		*list;
	size_t				counter;
	size_t				loop;
	volatile void		*handler;
	uint8_t				(*f)(size_t);

	g_mutex.lock();
	pending = (uint32_t) param;//LDMA_IntGetEnabled();
	if (pending & LDMA_IF_ERROR)/* Check for LDMA error. */
		while (true)/* Loop to enable debugger to see what has happened. */
			__NOP();/* Wait forever. */
	chZDma = 0;
	while (chZDma < DMA_CHAN_COUNT) {/* Iterate over all LDMA channels. */
		chmask = 1 << chZDma;
		if ((pending & chmask) != 0) {
			list = ZDMA._findList(chZDma);
			if (LDMA_TransferDone(chZDma) == true) {
				transfer_desc = &list->transfer_desc;
				if ((counter = list->counter) == 0) {
					if ((loop = list->loop) == 0) {
						list->uniqId = 0;
						ZDMA.bitZDmaLock ^= chmask;
						if ((f = list->f) != 0)
							f(list->param);
						if ((handler = list->handler) != 0) {
							list->handler = 0;
							while (zunoThreadIsRunning((void *)handler) == true)
								__NOP();
							zunoResumeThread((void *)handler);
						}
					}
					else {
						list->loop = (loop == ZDMA_EXT_LOOP_INFINITY) ? loop : loop - 1;
						if (transfer_desc->xfer.srcInc != ldmaCtrlSrcIncNone)
							transfer_desc->xfer.srcAddr = list->buff;
						else
							transfer_desc->xfer.dstAddr = list->buff;
						counter = list->len;
						_reload(list, transfer_desc, list->len, chZDma, chmask);
					}
				}
				else {
					if (transfer_desc->xfer.srcInc != ldmaCtrlSrcIncNone)
						transfer_desc->xfer.srcAddr = transfer_desc->xfer.srcAddr + ((transfer_desc->xfer.xferCnt + 1) * _multSize[transfer_desc->xfer.size]);
					else
						transfer_desc->xfer.dstAddr = transfer_desc->xfer.dstAddr + ((transfer_desc->xfer.xferCnt + 1) * _multSize[transfer_desc->xfer.size]);
					_reload(list, transfer_desc, counter, chZDma, chmask);
				}
			}
		}
		chZDma++;
	}
	g_mutex.unlock();
}

inline size_t ZDMAClass::_modeBasicLen(LDMA_Descriptor_t *transfer_desc, size_t len) {
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

inline ZunoError_t ZDMAClass::_getZDma(ZunoZDmaList_t **list_out, uint8_t *outchZDma) {
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
		return (ZunoErrorDmaLimitChannel);
	chZDma = 0;
	while ((bitZDmaLock & 0x1) != 0) {
		chZDma++;
		bitZDmaLock = bitZDmaLock >> 1;
	}
	this->bitZDmaLock |= 1 << chZDma;
	outchZDma[0] = chZDma;
	if ((list = this->_findList(chZDma)) == 0) {
		if ((list = (ZunoZDmaList_t *)malloc(sizeof(ZunoZDmaList_t))) == 0) {
			this->bitZDmaLock ^= 1 << chZDma;
			return (ZunoErrorMemory);
		}
		this->_addList(list, chZDma);
	}
	*list_out = list;
	return (ZunoErrorOk);
}

inline uint8_t ZDMAClass::_stopTransfer(size_t uniqId, uint8_t bForce) {
	ZunoZDmaList_t			*list;
	uint8_t					chZDma;
	volatile void			*handler;

	if ((list = this->_findListUniqId(uniqId, &chZDma)) == 0)
		return (ZDMA_STOPTRANSEFR_BREAK);
	if (bForce == false)
		list->loop = 0;
	else {
		if ((handler = list->handler) != 0 && zunoThreadIsRunning((void *)handler) == true)
			return (ZDMA_STOPTRANSEFR_WAIT);
		LDMA_StopTransfer(chZDma);
		list->uniqId = 0;
		this->bitZDmaLock ^= (1 << chZDma);
		if (handler != 0)
			zunoResumeThread((void *)handler);
	}
	return (ZDMA_STOPTRANSEFR_BREAK);
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

inline ZunoZDmaList_t *ZDMAClass::_findListUniqId(size_t uniqId, uint8_t *chZDma) {
	size_t					list;
	uint16_t				*b;
	uint16_t				*e;

	b = &this->_listCh[0];
	e = &b[DMA_CHAN_COUNT];
	while (b < e) {
		if ((list = b[0]) == 0) {
			b++;
			continue ;
		}
		list = list + (size_t)&__bss_start__;
		if (((ZunoZDmaList_t *)list)->uniqId == uniqId) {
			chZDma[0] = DMA_CHAN_COUNT - (e - b);
			return ((ZunoZDmaList_t *)list);
		}
		b++;
	}
	return (0);
}

/* Preinstantiate Objects */
ZDMAClass ZDMA = ZDMAClass();