#ifndef ZWAVEME_TRNG_H
#define ZWAVEME_TRNG_H

#include <stddef.h>
#include "em_device.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum					TrngStatus_e
{
	TrngStatusOk,
	TrngStatusAlarn,
	TrngStatusNoise,
	TrngStatusNotDate
}								TrngStatus_t;

static inline void trngSoftReset(void) {
	uint32_t				ctrl;

	ctrl = TRNG0->CONTROL;
	ctrl |= TRNG_CONTROL_SOFTRESET;
	TRNG0->CONTROL = ctrl;
	ctrl &= ~TRNG_CONTROL_SOFTRESET;
	TRNG0->CONTROL = ctrl;
};

void trngInit(void);
size_t getRandomData(void *b, size_t len, TrngStatus_t *status);

#ifdef __cplusplus
}
#endif

#endif//ZWAVEME_TRNG_H