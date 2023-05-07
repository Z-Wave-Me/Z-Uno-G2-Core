#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "zgm130s037hgn1.h"
#include "em_cmu.h"
#include "zwaveme_trng.h"

void trngInit(void) {
	CMU_ClockEnable(cmuClock_TRNG0, true);
	trngSoftReset();// Apply software reset 
	TRNG0->CONTROL = TRNG_CONTROL_ENABLE | TRNG_CONTROL_REPCOUNTIEN | TRNG_CONTROL_APT64IEN | TRNG_CONTROL_APT4096IEN | TRNG_CONTROL_PREIEN | TRNG_CONTROL_ALMIEN;
};

static TrngStatus_t _trngCheckStatus(TRNG_TypeDef *trng) {
	uint32_t							status ;

	status = trng->STATUS;
	if ((status & (TRNG_STATUS_PREIF | TRNG_STATUS_REPCOUNTIF | TRNG_STATUS_APT64IF | TRNG_STATUS_APT4096IF | TRNG_STATUS_ALMIF)) == 0)
		return (TrngStatusOk);
	if (status & TRNG_STATUS_PREIF) {//On a preliminary noise alarm we clear the FIFO and clear * the alarm. The preliminary noise alarm is not critical.
		status &= ~TRNG_STATUS_PREIF;
		trng->STATUS = status;
		while (trng->FIFOLEVEL != 0)// Empty FIFO
			trng->FIFO;
		return (TrngStatusNoise);
	}
	trngSoftReset();
	if ((status & (TRNG_STATUS_REPCOUNTIF | TRNG_STATUS_APT64IF | TRNG_STATUS_APT4096IF | TRNG_STATUS_ALMIF)) != 0)
		return (TrngStatusAlarn);
	return (TrngStatusOk);
}

// size_t getRandomData(void *b, size_t len, TrngStatus_t *status) __attribute__((optimize(0)));
size_t getRandomData(void *b, size_t len, TrngStatus_t *status) {
	TrngStatus_t					ret;
	size_t							available;
	size_t							save_len;
	size_t							tempos;
	TRNG_TypeDef					*trng;
	size_t							i;
	uint8_t							*out;

	out = (uint8_t *)b;
	trng = TRNG0;
	ret = TrngStatusOk;
	save_len = len;
	while (len != 0) {
		i = 0;
		while (trng->FIFOLEVEL == 0 && i < 1000)
			i++;
		if (i == 1000) {
			ret = TrngStatusNotDate;
			break ;
		}
		if ((ret = _trngCheckStatus(trng)) != TrngStatusOk)
			break ;
		if ((available = trng->FIFOLEVEL * sizeof(trng->FIFO)) > len)
			available = len;
		len = len - available;
		while (available >= sizeof(trng->FIFO)) {
			available -= sizeof(trng->FIFO);
			tempos = trng->FIFO;
			out = memcpy(out, &tempos, sizeof(trng->FIFO));
			out = out + sizeof(trng->FIFO);
		}
		if (available == 0)
			continue ;
		tempos = trng->FIFO;
		memcpy(out, &tempos, available);
		break ;
	}
	status[0] = ret;
	return (save_len - len);
}