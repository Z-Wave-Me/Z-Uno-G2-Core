#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCTimerParametrs.h"
#include "time.h"
#include "Libft.h"
#include "errno.h"

time_t zuno_CCTimerParametrsGet(const ZwTimerParametrs_t *packet) {
	struct tm					timeinfo;

	timeinfo.tm_year = ((packet->year1 << 8) | packet->year2) - 1900;
	timeinfo.tm_mon = packet->month - 1;
	timeinfo.tm_mday = packet->day;
	timeinfo.tm_hour = packet->hourUtc;
	timeinfo.tm_min = packet->minuteUtc;
	timeinfo.tm_sec = packet->secondUtc;
	return (mktime(&timeinfo));
}

void zuno_CCTimerParametrsSet(ZwTimerParametrs_t *packet, time_t time) {
	struct tm								timeinfo;
	size_t									tempos;
	gmtime_r(&time, &timeinfo);
	tempos = timeinfo.tm_year + 1900;
	packet->year1 = tempos >> 8;
	packet->year2 = tempos;
	packet->month = timeinfo.tm_mon + 1;
	packet->day = timeinfo.tm_mday;
	packet->hourUtc = timeinfo.tm_hour;
	packet->minuteUtc = timeinfo.tm_min;
	packet->secondUtc = timeinfo.tm_sec;
}

// extern unsigned long __etext;
// extern unsigned long __data_start__;
// extern unsigned long __data_end__;
// extern unsigned long __bss_start__;
// extern unsigned long __bss_end__;
// extern unsigned long __HeapBase;
// extern unsigned long __HeapLimit;

// extern "C" void *_sbrk(intptr_t delta) {
// 	static uint8_t		*heap_end = 0;
// 	uint8_t				*prev_heap_end;

// 	if (heap_end == 0)
// 		heap_end = (uint8_t *)&__HeapBase;
// 	prev_heap_end = heap_end;
// 	delta = ((delta + (sizeof(size_t) - 1)) & (0 - sizeof(size_t)));
// 	if (heap_end + delta > (uint8_t *)&__HeapLimit) {
// 		errno = ENOMEM;
// 		return (void *) -1;
// 	}
// 	heap_end = heap_end + delta;
// 	return (prev_heap_end);
// }

static time_t _timeUnix = 0;
static uint32_t _time = 0;

static int _set(ZwTimerParametrsSetFrame_t *packet) {
	_timeUnix= zuno_CCTimerParametrsGet(&packet->time);
	_time = millis() / 1000;
	return (ZUNO_COMMAND_PROCESSED);
}

static int _report(void) {
	ZwTimerParametrsReportFrame_t			*report;
	time_t									time;

	report = (ZwTimerParametrsReportFrame_t *)&CMD_REPLY_CC;
	// report->cmdClass = COMMAND_CLASS_TIME_PARAMETERS; //set in - fillOutgoingPacket
	// report->cmd = TIME_PARAMETERS_REPORT; //set in - fillOutgoingPacket
	time = _timeUnix + ((millis() / 1000) - _time);
	zuno_CCTimerParametrsSet(&report->time, time);
	CMD_REPLY_LEN = sizeof(ZwTimerParametrsReportFrame_t);
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCTimerParametrsHandler(ZUNOCommandPacket_t *cmd) {
	int								rs;

	switch (ZW_CMD) {
		case TIME_PARAMETERS_SET:
			rs = _set((ZwTimerParametrsSetFrame_t *)cmd->cmd);
			break ;
		case TIME_PARAMETERS_GET:
			rs = _report();
			break ;
		default:
			rs = ZUNO_UNKNOWN_CMD;
			break ;
	}
	return (rs);
}