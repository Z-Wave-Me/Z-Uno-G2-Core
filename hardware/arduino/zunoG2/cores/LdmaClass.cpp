#include "Arduino.h"
#include "LdmaClass.h"

/* Public Methods */
void LdmaClass::transferStop(ssize_t channel) {
	zunoSysCall(ZUNO_SYSFUNC_DMA_XFER_STOP, 0x1, channel);
}

// void LdmaClass::transferStop(LdmaClassChannel_t channel) {
// }

size_t LdmaClass::transferDone(ssize_t channel) {
	return ((size_t)zunoSysCall(ZUNO_SYSFUNC_DMA_XFER_DONE, 0x1, channel));
}

ssize_t LdmaClass::transferSingle(const void *src, void *dst, size_t len, LdmaClassSignal_t signal, LDMA_CtrlSize_t size, LDMA_CtrlSrcInc_t srcInc, LDMA_CtrlDstInc_t dstInc, LdmaClassTransferSingle_t *array) {
	return ((ssize_t)zunoSysCall(ZUNO_SYSFUNC_DMA_XFER_SINGLE, 0x8, src, dst, len, signal, size, srcInc, dstInc, array));
}

ssize_t LdmaClass::receivedCyclical(const void *src, void *dst, size_t len, LdmaClassSignal_t signal, LDMA_CtrlSize_t size, LdmaClassReceivedCyclical_t *array) {
	return ((ssize_t)zunoSysCall(ZUNO_SYSFUNC_DMA_CYCLIC, 0x6, src, dst, len, signal, size, array));
}

size_t LdmaClass::receivedAvailable(ssize_t channel) {
	return ((size_t)zunoSysCall(ZUNO_SYSFUNC_DMA_AVAILABLE, 0x1, channel));
}

ssize_t LdmaClass::receivedReadPeek(ssize_t channel, uint8_t bBool) {
	return ((ssize_t)zunoSysCall(ZUNO_SYSFUNC_DMA_READ, 0x2, channel, bBool));
}

void LdmaClass::i2cFixReceived(ssize_t channel) {
	zunoSysCall(ZUNO_SYSFUNC_DMA_I2C_RCV, 0x1, channel);
}

ssize_t LdmaClass::i2cRequestFrom(I2C_TypeDef *i2c, void *dst, size_t len, LdmaClassSignal_t signal, LdmaClassTransferI2cRequestFromMaster_t *array) {
	return ((ssize_t)zunoSysCall(ZUNO_SYSFUNC_DMA_I2C_REQUEST, 0x5, i2c, dst, len, signal, array));
}