#include "Arduino.h"
#include "CrtxGcc.h"
#include "ZDma.h"
#include "stdlib.h"


//
// Built in DMA
// ----------------------------------------------------------------------------------------------------------
typedef struct DMAxFerParam_s{
    ZDMA_PeripheralSignal_t peripheralSignal;
    void *dest;
    void *src;
    size_t len;
    ZDma_DataSize_t size;
    ZunoZDmaExt_t * lpExt;
}DMAxFerParam_t;
typedef enum{
    DMAOk,
    DMALimitChannel,
    DMAInvalidUniqId,
    DMAUniqIdInUse,
    DMAInvalidReconfig
} DMAResul_t;
/*
static inline uint8_t _isProcessing(size_t uniqId){
   return (uint8_t)(uint32_t)zunoSysCall(ZUNO_SYSFUNC_DMA_IS_PRC, 1, uniqId);
}
static inline ZunoError_t _transferReceivedCount(size_t uniqId, size_t *count){
	*count = (size_t)zunoSysCall(ZUNO_SYSFUNC_DMA_COUNT, 1, uniqId);
	ZunoError_t res = ((ssize_t)*count == -1) ? ZunoErrorOk :  ZunoErrorDmaInvalidUniqId;
	return res;
}
static void _waitTransfer(size_t uniqId) {
	if (zunoIsIOThread())
		return;
	delay(1);
	while (_isProcessing(uniqId))
		delay(1);
}
static inline ZunoError_t _transfer(size_t uniqId, ZDMA_PeripheralSignal_t peripheralSignal, void *dest, void *src, size_t len, ZDma_DataSize_t size, ZunoZDmaExt_t *lpExt){
	DMAxFerParam_t param = {.peripheralSignal = peripheralSignal, .dest=dest, .src = src, .len = len, .size = size, .lpExt = lpExt};
	DMAResul_t res =  (DMAResul_t)(uint32_t)zunoSysCall(ZUNO_SYSFUNC_DMA_XFER, 2, uniqId, &param);
	if(res == DMAOk)
		return ZunoErrorOk;
	return ZunoError_t ((uint32_t)res + (uint32_t)ZunoErrorDmaLimitChannel);
}
static inline void _stopTransfer(size_t uniqId, uint8_t bForce){
	zunoSysCall(ZUNO_SYSFUNC_DMA_STOP, 2, uniqId, bForce);
}
*/
// ----------------------------------------------------------------------------------------------------------

/*
ZDMAClass::ZDMAClass(void){
	// zunoAttachSysHandler(ZUNO_HANDLER_IRQ, ZUNO_IRQVEC_LDMA, (void *)LDMA_IRQHandler);
}
uint8_t ZDMAClass::isProcessing(size_t uniqId) {
	return(_isProcessing(uniqId));
}
ZunoError_t ZDMAClass::transferReceivedCount(size_t uniqId, size_t *count) {
	return (_transferReceivedCount(uniqId, count));
}
void ZDMAClass::stopTransfer(size_t uniqId, uint8_t bForce) {
	_stopTransfer(uniqId, bForce);
}
void ZDMAClass::waitTransfer(size_t uniqId) {
	_waitTransfer(uniqId);
}
ZunoError_t ZDMAClass::toMemoryPeripheral(size_t uniqId, ZDMA_PeripheralSignal_t peripheralSignal, void *dest, void *src, size_t len, ZDma_DataSize_t size) {
	ZunoZDmaExt_t					lpExt;

	lpExt = ZDMA_EXT_INIT_DEFAULT;
	lpExt.flags |= (ZDMA_EXT_FLAGS_REQ_BLOCK | ZDMA_EXT_FLAGS_DEST_NOT_INC);
	return (_transfer(uniqId, peripheralSignal, dest, src, len, size, &lpExt));
}
ZunoError_t ZDMAClass::toMemoryPeripheral(size_t uniqId, ZDMA_PeripheralSignal_t peripheralSignal, void *dest, void *src, size_t len, ZDma_DataSize_t size, ZunoZDmaExt_t *lpExt) {
	lpExt->flags |= (ZDMA_EXT_FLAGS_REQ_BLOCK | ZDMA_EXT_FLAGS_DEST_NOT_INC);
	return (_transfer(uniqId, peripheralSignal, dest, src, len, size, lpExt));
}
ZunoError_t ZDMAClass::toPeripheralMemory(size_t uniqId, ZDMA_PeripheralSignal_t peripheralSignal, void *dest, void *src, size_t len, ZDma_DataSize_t size) {
	ZunoZDmaExt_t					lpExt;

	lpExt = ZDMA_EXT_INIT_DEFAULT;
	lpExt.flags |= (ZDMA_EXT_FLAGS_REQ_BLOCK | ZDMA_EXT_FLAGS_SRC_NOT_INC);
	return (_transfer(uniqId, peripheralSignal, dest, src, len, size, &lpExt));
}
ZunoError_t ZDMAClass::toPeripheralMemory(size_t uniqId, ZDMA_PeripheralSignal_t peripheralSignal, void *dest, void *src, size_t len, ZDma_DataSize_t size, ZunoZDmaExt_t *lpExt) {
	lpExt->flags |= (ZDMA_EXT_FLAGS_REQ_BLOCK | ZDMA_EXT_FLAGS_SRC_NOT_INC);
	return (_transfer(uniqId, peripheralSignal, dest, src, len, size, lpExt));
}


ZDMAClass ZDMA;*/