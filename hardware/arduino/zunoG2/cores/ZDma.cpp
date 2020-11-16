#include "Arduino.h"
#include "CrtxGcc.h"
#include "ZDma.h"
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

#define ZDMA_DESCRIPTOR(src, dest, count, req_mode, size_block, src_inc, dst_inc) \
  {                                                       \
    .xfer =                                               \
    {                                                     \
      .structType   = ldmaCtrlStructTypeXfer,             \
      .reserved0    = 0,                                  \
      .structReq    = 0,                                  \
      .xferCnt      = (count) - 1,                        \
      .byteSwap     = 0,                                  \
      .blockSize    = ldmaCtrlBlockSizeUnit1,             \
      .doneIfs      = 1,                                  \
      .reqMode      = req_mode,                           \
      .decLoopCnt   = 0,                                  \
      .ignoreSrec   = 0,                                  \
      .srcInc       = src_inc,                            \
      .size         = size_block,                         \
      .dstInc       = dst_inc,                            \
      .srcAddrMode  = ldmaCtrlSrcAddrModeAbs,             \
      .dstAddrMode  = ldmaCtrlDstAddrModeAbs,             \
      .srcAddr      = (uint32_t)(src),                    \
      .dstAddr      = (uint32_t)(dest),                   \
      .linkMode     = 0,                                  \
      .link         = 0,                                  \
      .linkAddr     = 0                                   \
    }                                                     \
  }

extern unsigned long __bss_start__;

/* Constants */
const uint8_t ZDMAClass::_multSize[] = {1, 2, 4};

/* Public Constructors */
ZDMAClass::ZDMAClass(void)
#if (ZUNO_ZERO_BSS != true || false != 0)
	: bitZDmaLock(0), _listCh{0}
#endif
{
}

uint8_t ZDMAClass::isProcessing(size_t uniqId) {
	size_t					chZDma;
	ZunoZDmaList_t			*list;

	zunoEnterCritical();
	list = this->_findListUniqId(uniqId, &chZDma);
	zunoExitCritical();
	if (list == 0)
		return (false);
	return (true);
}

ZunoError_t ZDMAClass::transferReceivedCount(size_t uniqId, size_t *count) {
	size_t					chZDma;
	ZunoZDmaList_t			*list;
	ZunoError_t				ret;

	zunoEnterCritical();
	list = this->_findListUniqId(uniqId, &chZDma);
	if (list == 0)
		ret = ZunoErrorDmaInvalidUniqId;
	else {
		count[0] = (list ->len - (LDMA_TransferRemainingCount(chZDma) + list->counter));
		ret = ZunoErrorOk;
	}
	zunoExitCritical();
	return (ret);
}

void ZDMAClass::stopTransfer(size_t uniqId, uint8_t bForce) {
	zunoEnterCritical();
	this->_stopTransfer(uniqId, bForce);
	zunoExitCritical();
}

void ZDMAClass::waitTransfer(size_t uniqId) {
	ZunoZDmaList_t			*list;
	uint8_t					chZDma;
	void					*handler;

	if (zunoIsIOThread() == true)
		return ;
	delay(1);
	while (this->isProcessing(uniqId) == true)
		delay(1);
}

ZunoError_t ZDMAClass::toMemoryPeripheral(size_t uniqId, ZDMA_PeripheralSignal_t peripheralSignal, void *dest, void *src, size_t len, ZDma_DataSize_t size) {
	ZunoZDmaExt_t					lpExt;

	lpExt = ZDMA_EXT_INIT_DEFAULT;
	lpExt.flags |= (ZDMA_EXT_FLAGS_REQ_BLOCK | ZDMA_EXT_FLAGS_DEST_NOT_INC);
	return (this->_transfer(uniqId, peripheralSignal, dest, src, len, size, &lpExt));
}

ZunoError_t ZDMAClass::toMemoryPeripheral(size_t uniqId, ZDMA_PeripheralSignal_t peripheralSignal, void *dest, void *src, size_t len, ZDma_DataSize_t size, ZunoZDmaExt_t *lpExt) {
	lpExt->flags |= (ZDMA_EXT_FLAGS_REQ_BLOCK | ZDMA_EXT_FLAGS_DEST_NOT_INC);
	return (this->_transfer(uniqId, peripheralSignal, dest, src, len, size, lpExt));
}

ZunoError_t ZDMAClass::toPeripheralMemory(size_t uniqId, ZDMA_PeripheralSignal_t peripheralSignal, void *dest, void *src, size_t len, ZDma_DataSize_t size) {
	ZunoZDmaExt_t					lpExt;

	lpExt = ZDMA_EXT_INIT_DEFAULT;
	lpExt.flags |= (ZDMA_EXT_FLAGS_REQ_BLOCK | ZDMA_EXT_FLAGS_SRC_NOT_INC);
	return (this->_transfer(uniqId, peripheralSignal, dest, src, len, size, &lpExt));
}

ZunoError_t ZDMAClass::toPeripheralMemory(size_t uniqId, ZDMA_PeripheralSignal_t peripheralSignal, void *dest, void *src, size_t len, ZDma_DataSize_t size, ZunoZDmaExt_t *lpExt) {
	lpExt->flags |= (ZDMA_EXT_FLAGS_REQ_BLOCK | ZDMA_EXT_FLAGS_SRC_NOT_INC);
	return (this->_transfer(uniqId, peripheralSignal, dest, src, len, size, lpExt));
}

/* Private Methods */
inline ZunoError_t ZDMAClass::_transfer(size_t uniqId, ZDMA_PeripheralSignal_t peripheralSignal, void *dest, void *src, size_t len, ZDma_DataSize_t size, ZunoZDmaExt_t *lpExt) {
	ZunoError_t				ret;
	ZunoZDmaList_t			*list;
	LDMA_TransferCfg_t		transfer_cfg;
	LDMA_Descriptor_t		*transfer_desc;
	size_t					loop;
	size_t					buff;
	size_t					chZDma;
	uint32_t				flags;

	if (uniqId == 0)
		return (ZunoErrorDmaInvalidUniqId);
	if (len == 0 || (loop = lpExt->loop) == 0)
		return (ZunoErrorOk);
	zunoEnterCritical();
	list = this->_findListUniqId(uniqId, &chZDma);
	flags = lpExt->flags;
	if (((flags & ZDMA_EXT_FLAGS_RECONFIG) != 0)) {
		if (list == 0) {
			zunoExitCritical();
			return (ZunoErrorDmaInvalidReconfig);
		}
		LDMA_StopTransfer(chZDma);
		zunoExitCritical();
	}
	else {
		zunoExitCritical();
		if (list != 0)
			return (ZunoErrorDmaUniqIdAlready);
		if ((ret = this->_getZDma(&list, &chZDma)) != ZunoErrorOk)
			return (ret);
		list->uniqId = uniqId;
	}
	list->f = lpExt->f;
	list->param = lpExt->param;
	list->len = len;
	list->loop = (loop == ZDMA_EXT_LOOP_INFINITY) ? loop : loop - 1;
	list->buff = ((flags & ZDMA_EXT_FLAGS_DEST_NOT_INC) != 0)? (uint32_t)src : (uint32_t)dest;
	if (len > ZDMA_MAX_XFER_COUNT) {
		list->counter = len - ZDMA_MAX_XFER_COUNT;
		len = ZDMA_MAX_XFER_COUNT;
	}
	else
		list->counter = 0;
	transfer_desc = &list->transfer_desc;
	transfer_desc[0] = ZDMA_DESCRIPTOR(src, dest, len, (((flags & ZDMA_EXT_FLAGS_REQ_BLOCK) != 0)? ldmaCtrlReqModeBlock : ldmaCtrlReqModeAll), size, (((flags & ZDMA_EXT_FLAGS_SRC_NOT_INC) != 0)? ldmaCtrlSrcIncNone : ldmaCtrlSrcIncOne), (((flags & ZDMA_EXT_FLAGS_DEST_NOT_INC) != 0)? ldmaCtrlDstIncNone : ldmaCtrlDstIncOne));
	transfer_cfg = LDMA_TRANSFER_CFG_PERIPHERAL(peripheralSignal);
	LDMA_StartTransfer(chZDma, &transfer_cfg, transfer_desc);
	return (ZunoErrorOk);
}

void ZDMAClass::_LDMA_IRQHandler(void * param) {
	LDMA_Descriptor_t	*transfer_desc;
	size_t				pending;
	size_t				chZDma;
	size_t				chmask;
	ZunoZDmaList_t		*list;
	size_t				counter;
	size_t				loop;
	uint8_t				(*f)(size_t);

	pending = (uint32_t) param;//LDMA_IntGetEnabled();
	if (pending & LDMA_IF_ERROR)/* Check for LDMA error. */
		while (true)/* Loop to enable debugger to see what has happened. */
			__NOP();/* Wait forever. */
	chZDma = 0;
	while (chZDma < DMA_CHAN_COUNT) {/* Iterate over all LDMA channels. */
		chmask = 1 << chZDma;
		if ((pending & chmask) != 0 && (ZDMA.bitZDmaLock & chmask) != 0) {
			list = ZDMA._findList(chZDma);
			if (LDMA_TransferDone(chZDma) == true) {
				transfer_desc = &list->transfer_desc;
				if ((counter = list->counter) == 0) {
					if ((loop = list->loop) == 0) {
						list->uniqId = 0;
						ZDMA.bitZDmaLock ^= chmask;
						if ((f = list->f) != 0)
							f(list->param);
					}
					else {
						list->loop = (loop == ZDMA_EXT_LOOP_INFINITY) ? loop : loop - 1;
						if (transfer_desc->xfer.srcInc != ldmaCtrlSrcIncNone)
							transfer_desc->xfer.srcAddr = list->buff;
						else if (transfer_desc->xfer.dstInc != ldmaCtrlDstIncNone)
							transfer_desc->xfer.dstAddr = list->buff;
						counter = list->len;
						ZDMA._reload(list, transfer_desc, list->len, chZDma, chmask);
					}
				}
				else {
					if (transfer_desc->xfer.srcInc != ldmaCtrlSrcIncNone)
						transfer_desc->xfer.srcAddr = transfer_desc->xfer.srcAddr + ((transfer_desc->xfer.xferCnt + 1) * ZDMA._multSize[transfer_desc->xfer.size]);
					else if (transfer_desc->xfer.dstInc != ldmaCtrlDstIncNone)
						transfer_desc->xfer.dstAddr = transfer_desc->xfer.dstAddr + ((transfer_desc->xfer.xferCnt + 1) * ZDMA._multSize[transfer_desc->xfer.size]);
					ZDMA._reload(list, transfer_desc, counter, chZDma, chmask);
				}
			}
		}
		chZDma++;
	}
}

inline void ZDMAClass::_reload(ZunoZDmaList_t *list, LDMA_Descriptor_t *transfer_desc, size_t counter, size_t chZDma, size_t chmask) {
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

inline ZunoError_t ZDMAClass::_getZDma(ZunoZDmaList_t **list_out, size_t *outchZDma) {
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
	zunoEnterCritical();
	if ((bitZDmaLock = this->bitZDmaLock) == 0xFF) {
		zunoExitCritical();
		return (ZunoErrorDmaLimitChannel);
	}
	chZDma = 0;
	while ((bitZDmaLock & 0x1) != 0) {
		chZDma++;
		bitZDmaLock = bitZDmaLock >> 1;
	}
	this->bitZDmaLock |= 1 << chZDma;
	zunoExitCritical();
	outchZDma[0] = chZDma;
	if ((list = this->_findList(chZDma)) == 0) {
		if ((list = (ZunoZDmaList_t *)malloc(sizeof(ZunoZDmaList_t))) == 0) {
			this->bitZDmaLock ^= 1 << chZDma;
			return (ZunoErrorMemory);
		}
		list->uniqId = 0;
		this->_addList(list, chZDma);
	}
	*list_out = list;
	return (ZunoErrorOk);
}

inline void ZDMAClass::_stopTransfer(size_t uniqId, uint8_t bForce) {
	ZunoZDmaList_t			*list;
	size_t					chZDma;

	if ((list = this->_findListUniqId(uniqId, &chZDma)) == 0)
		return ;
	if (bForce == false)
		list->loop = 0;
	else {
		LDMA_StopTransfer(chZDma);
		list->uniqId = 0;
		this->bitZDmaLock ^= (1 << chZDma);
	}
	return ;
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

inline ZunoZDmaList_t *ZDMAClass::_findListUniqId(size_t uniqId, size_t *chZDma) {
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