#include "Arduino.h"
#include "CrtxTrng.h"


typedef enum					TrngStatus_e
{
	TrngStatusOk,
	TrngStatusFaill,
	TrngStatusNoise,
}								TrngStatus_t;

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
	}
	if ((status & (TRNG_STATUS_REPCOUNTIF | TRNG_STATUS_APT64IF | TRNG_STATUS_APT4096IF | TRNG_STATUS_ALMIF)) != 0) {
		trngSoftReset(trng);
		return (TrngStatusFaill);
	}
	return (TrngStatusNoise);
}

size_t getRandomData(TRNG_TypeDef *trng, uint8_t *out, size_t len, ZunoError_t *status) {
	ZunoError_t						ret;
	size_t							available;
	size_t							out_len;
	TrngStatus_t					st;
	size_t							tempos;
	uint8_t							*tmp;

	ret = ZunoErrorOk;
	out_len = 0;
	while (len > 0) {
		available = trng->FIFOLEVEL * sizeof(trng->FIFO);
		if (available == 0) {
			ret = ZunoErrorTrngNotDate;
			break ;
		}
		if ((st = _trngCheckStatus(trng)) == TrngStatusNoise)
			continue ;
		if (st == TrngStatusFaill) {
			ret = ZunoErrorTrngFaill;
			break ;
		}
		if (len < available)
			available = len;
		tmp = out;
		out += available;
		out_len += available;
		len -= available;
		while (available >= sizeof(trng->FIFO)) {
			available -= sizeof(trng->FIFO);
			tempos = trng->FIFO;
			tmp = (uint8_t *)memcpy(tmp, &tempos, sizeof(trng->FIFO)) + sizeof(trng->FIFO);
		}
		if (available == 0)
			continue ;
		tempos = trng->FIFO;
		memcpy(tmp, &tempos, available);
	}
	status[0] = ret;
	return (out_len);
}