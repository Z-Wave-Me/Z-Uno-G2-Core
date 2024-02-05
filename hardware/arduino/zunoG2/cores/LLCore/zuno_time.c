#include "Arduino.h"
#include "zuno_time.h"
#include "em_rtcc.h"
#include "em_burtc.h"

#define ZUNO_TIME_DELAY_MICROSECONDS_MIN				2000
#define ZUNO_TIME_DELAY_MICROSECONDS_MAX				4000

// MULTI_CHIP
#if defined(RTCC_COUNT) && (RTCC_COUNT == 1)
uint64_t rtcc_micros(void) {
	uint32_t			tic1;
	uint32_t			tic2;
	uint32_t			overflow;
	uint64_t			out;

	tic1 = RTCC_CounterGet();
	overflow = RTCC->RET[0x1F].REG;// overflow = RTCC->RET[0x1F].REG;
	tic2 = RTCC_CounterGet();
	if (tic2 < tic1) {
		tic1 = tic2;
		overflow++;
	}
	out = overflow;
	out = (out << 0x20) | tic1;
	out = (out * 1000000) >> 0xF;//DIV1 - 32768 - freq
	return (out);
}

time_t zunoGetTimeStamp(void) {
	return (RTCC->RET[0x1E].REG + (rtcc_micros() / 1000000));
}

void zunoSetTimeStamp(time_t timeUnix) {
	RTCC->RET[0x1E].REG = timeUnix - (rtcc_micros() / 1000000);
}
#endif//#if defined(RTCC_COUNT) && (RTCC_COUNT == 1)
#if defined(BURTC_PRESENT)
uint64_t rtcc_micros(void) {
	uint32_t			tic1;
	uint32_t			tic2;
	uint32_t			overflow;
	uint64_t			out;

	tic1 = BURTC_CounterGet();
	overflow = BURAM->RET[0x1F].REG;// overflow = RTCC->RET[0x1F].REG;
	tic2 = BURTC_CounterGet();
	if (tic2 < tic1) {
		tic1 = tic2;
		overflow++;
	}
	out = overflow;
	out = (out << 0x20) | tic1;
	out = (out * 1000000) >> 0xF;//DIV1 - 32768 - freq
	return (out);
}

time_t zunoGetTimeStamp(void) {
	return (BURAM->RET[0x1E].REG + (rtcc_micros() / 1000000));
}

void zunoSetTimeStamp(time_t timeUnix) {
	BURAM->RET[0x1E].REG = timeUnix - (rtcc_micros() / 1000000);
}
#endif//#if defined(BURTC_PRESENT)

dword millis(void){
	return (dword)(rtcc_micros() / 1000);
}
// JUST A STUB...
dword micros(void){
	return (dword)(rtcc_micros());
}

static void _udelay(dword tdelay){
	while(tdelay--){
		asm("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop");
		asm("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop");
		asm("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop");
		asm("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop");
	}
}


void delayMicroseconds(dword tdelay) {
	uint64_t					us_required;
	uint64_t					us_current;

	if (tdelay <= ZUNO_TIME_DELAY_MICROSECONDS_MAX)
		return (_udelay(tdelay));
	us_required = rtcc_micros() + tdelay;
	delay((tdelay - ZUNO_TIME_DELAY_MICROSECONDS_MIN) / 1000);
	us_current = rtcc_micros();
	if (us_current >= us_required)
		return ;
	_udelay(us_required - us_current);
}
