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

/* Public Constructors */
ZDMAClass::ZDMAClass(void): bitZDmaLock(0), list(0) {

}

ZunoError_t ZDMAClass::toMemoryPeripheral(ZunoZDmaUser_t *userLp, ZDMA_PeripheralSignal_t peripheralSignal, void *dst, void *src,
size_t len, ZDma_DataSize_t size) {
	return (this->_transfer(userLp, peripheralSignal, dst, src, len, size, zdmaModeBasic, zdmaDirectionMemToPeripheral));
}

/* Private Methods */
ZunoError_t ZDMAClass::_transfer(ZunoZDmaUser_t *userLp, ZDMA_PeripheralSignal_t peripheralSignal, void *dst, void *src, size_t len, ZDma_DataSize_t size, ZDmaMode_t mode,
						ZDmaDirection_t direction) {
	ZunoError_t				ret;
	ZunoZDmaList_t			*list;
	LDMA_TransferCfg_t		transfer_cfg;
	LDMA_Descriptor_t		*transfer_desc;
	uint8_t					chZDma;

	if (len == 0)
		return (ZunoErrorOk);
	if ((ret = this->_getZDma(&list)) != ZunoErrorOk)
		return (ret);
	list->mode = mode;
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
		list->len = this->_modeBasicLen(transfer_desc, len);
	}
	else {
		list->len = 0;
		transfer_desc->xfer.xferCnt = len - 1;
	}
	list->userLp = userLp;
	chZDma = list->chZDma;
	userLp->bProcessing = true;
	transfer_cfg = LDMA_TRANSFER_CFG_PERIPHERAL(peripheralSignal);
	LDMA_StartTransfer(chZDma, &transfer_cfg, transfer_desc);
	return (ZunoErrorOk);
}

void ZDMAClass::_LDMA_IRQHandler(void) {
	LDMA_Descriptor_t	*transfer_desc;
	size_t				pending;
	size_t				chZDma;
	size_t				chmask;
	ZunoZDmaList_t		*list;
	size_t				len;

	pending = LDMA_IntGetEnabled();
	if (pending & LDMA_IF_ERROR)/* Check for LDMA error. */
		while (true)/* Loop to enable debugger to see what has happened. */
			__NOP();/* Wait forever. */
	chZDma = 0;
	while (chZDma < DMA_CHAN_COUNT) {/* Iterate over all LDMA channels. */
		chmask = 1 << chZDma;
		if ((pending & chmask) != 0) {
			list = ZDMA._findList(chZDma);
			len = list->len;
			if (len == 0) {
				if (LDMA_TransferDone(chZDma) == true) {
					list->userLp->bProcessing = false;
					list->userLp = 0;
					ZDMA.bitZDmaLock ^= chmask;
				}
			}
			else if (len <= ZDMA_MAX_XFER_COUNT) {
				transfer_desc = &list->transfer_desc[0];
				transfer_desc[0].xfer.srcAddr = transfer_desc[1].xfer.srcAddr + transfer_desc[1].xfer.xferCnt + 1;
				transfer_desc[0].xfer.xferCnt = len - 1;
				transfer_desc[0].xfer.link = false;
				list->len = 0;
			}
			else {
				transfer_desc = &list->transfer_desc[0];
				transfer_desc[0].xfer.srcAddr = transfer_desc[1].xfer.srcAddr + transfer_desc[1].xfer.xferCnt + 1;
				list->len = ZDMA._modeBasicLen(transfer_desc, len);
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
	transfer_desc[1].xfer.srcAddr = transfer_desc[0].xfer.srcAddr + tempos;
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
	noInterrupts();
	chZDma = 0;
	while ((bitZDmaLock & 0x1) != 0) {
		chZDma++;
		bitZDmaLock = bitZDmaLock >> 1;
	}
	this->bitZDmaLock |= 1 << chZDma;
	interrupts();
	if ((list = this->_findList(chZDma)) == 0) {
		if ((list = (ZunoZDmaList_t *)malloc(sizeof(ZunoZDmaList_t))) == 0) {
			this->bitZDmaLock ^= 1 << chZDma;
			return (ZunoErrorMemory);
		}
		list->next = 0;
		list->chZDma = chZDma;
		this->_addList(list);
	}
	*list_out = list;
	return (ZunoErrorOk);
}

inline void ZDMAClass::_addList(ZunoZDmaList_t *list) {
	ZunoZDmaList_t			*list_next;
	ZunoZDmaList_t			*list_tmp;

	noInterrupts();
	if ((list_next = this->list) != 0) {
		while ((list_tmp = list_next->next) != 0)
			list_next = list_tmp;
		list_next->next = list;
	}
	else
		this->list = list;
	interrupts();
}

inline ZunoZDmaList_t *ZDMAClass::_findList(uint8_t chZDma) {
	ZunoZDmaList_t			*list;

	list = this->list;
	while (list != 0) {
		if (list->chZDma == chZDma)
			break ;
		list = list->next;
	}
	return (list);
}

/* Preinstantiate Objects */
ZDMAClass ZDMA = ZDMAClass();