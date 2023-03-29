#ifndef LDMA_CLASS_H
#define LDMA_CLASS_H

#include "em_ldma.h"
void *zunoSysCall(uint8_t ct, uint8_t n, ...);


#define LDMACLASS_MAX_XFER_COUNT (((_LDMA_CH_CTRL_XFERCNT_MASK >> _LDMA_CH_CTRL_XFERCNT_SHIFT) + 1))

typedef enum								LdmaClassStatus_e
{
	LdmaClassStatusOk = 0,
	LdmaClassStatusNotChannel,
	LdmaClassStatusFalled
}											LdmaClassStatus_t;

typedef struct								LdmaClassReceivedCyclical_s
{
	size_t									count_read;
	LDMA_Descriptor_t						descLink[1];
}											LdmaClassReceivedCyclical_t;

typedef struct								LdmaClassTransferSingle_s
{
	LDMA_Descriptor_t						descLink[2];
}											LdmaClassTransferSingle_t;

typedef struct								LdmaClassTransferI2cRequestFromMaster_s
{
	uint32_t								ctrl;
	LDMA_Descriptor_t						descLink[0x6];
	LDMA_Descriptor_t						descLinkAdd[0x4];
}											LdmaClassTransferI2cRequestFromMaster_t;

typedef struct								LdmaClassTransferCyclical_s
{
	LdmaClassReceivedCyclical_t				array;
}											LdmaClassTransferCyclical_t;

typedef union								LdmaClassChannel_u
{
	ssize_t									channel;
	struct
	{
		ssize_t								channel_1: 0x4;
		ssize_t								channel_2: 0x4;
	};
	
}											LdmaClassChannel_t;


class LdmaClass {
	public:
		LdmaClass(void) {};
		static size_t								ldmaGetDst(ssize_t channel) {return ((ssize_t)zunoSysCall(ZUNO_SYSFUNC_DMA_GETDST, 0x1, channel));};
		static size_t								ldmaGetSrc(ssize_t channel) {return ((ssize_t)zunoSysCall(ZUNO_SYSFUNC_DMA_GETSRC, 0x1, channel));};
		static size_t								receivedAvailable(ssize_t channel);
		static ssize_t								receivedReadPeek(ssize_t channel, uint8_t bBool);
		static ssize_t								receivedCyclical(const void *src, void *dst, size_t len, LDMA_PeripheralSignal_t signal, LDMA_CtrlSize_t size, LdmaClassReceivedCyclical_t *array);
		static ssize_t								transferCyclical(const void *src, void *dst, size_t len, LDMA_PeripheralSignal_t signal, LDMA_CtrlSize_t size, LdmaClassTransferCyclical_t *array);
		static ssize_t								transferSingle(const void *src, void *dst, size_t len, LDMA_PeripheralSignal_t signal, LDMA_CtrlSize_t size, LDMA_CtrlSrcInc_t srcInc, LDMA_CtrlDstInc_t dstInc, LdmaClassTransferSingle_t *array);
		static size_t								transferDone(ssize_t channel);
		static void									transferStop(ssize_t channel);
		// static void									transferStop(LdmaClassChannel_t channel);
		static void									i2cFixReceived(ssize_t channel);
		static ssize_t								i2cRequestFrom(I2C_TypeDef *i2c, void *dst, size_t len, LDMA_PeripheralSignal_t signal, LdmaClassTransferI2cRequestFromMaster_t *array);
};

#endif//LDMA_CLASS_H