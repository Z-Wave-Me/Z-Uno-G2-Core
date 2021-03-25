#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCTimerParametrs.h"
#include "time.h"
#include "Libft.h"
#include "errno.h"

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
	struct tm					timeinfo;

	timeinfo.tm_year = ((packet->year1 << 8) | packet->year2) - 1900;
	timeinfo.tm_mon = packet->month - 1;
	timeinfo.tm_mday = packet->day;
	timeinfo.tm_hour = packet->hourUtc;
	timeinfo.tm_min = packet->minuteUtc;
	timeinfo.tm_sec = packet->secondUtc;
	_timeUnix= mktime(&timeinfo);
	_time = millis() / 1000;
	return (ZUNO_COMMAND_PROCESSED);
}

static int _report(void) {
	ZwTimerParametrsReportFrame_t			*report;
	struct tm								timeinfo;
	size_t									tempos;
	time_t									time;

	time = _timeUnix + ((millis() / 1000) - _time);
	gmtime_r(&time, &timeinfo);
	report = (ZwTimerParametrsReportFrame_t *)&CMD_REPLY_CC;
	// report->cmdClass = COMMAND_CLASS_TIME_PARAMETERS; //set in - fillOutgoingPacket
	// report->cmd = TIME_PARAMETERS_REPORT; //set in - fillOutgoingPacket
	tempos = timeinfo.tm_year + 1900;
	report->year1 = tempos >> 8;
	report->year2 = tempos;
	report->month = timeinfo.tm_mon + 1;
	report->day = timeinfo.tm_mday;
	report->hourUtc = timeinfo.tm_hour;
	report->minuteUtc = timeinfo.tm_min;
	report->secondUtc = timeinfo.tm_sec;
	CMD_REPLY_LEN = sizeof(ZwTimerParametrsReportFrame_t);
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCTimerParametrs(ZUNOCommandPacket_t *cmd) {
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