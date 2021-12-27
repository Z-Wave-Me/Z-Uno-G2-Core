#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCTimerParametrs.h"
#include "time.h"
#include "zwaveme_libft.h"
#include "errno.h"
#include "string.h"

size_t zuno_CCTimerParametrsGet(const ZwTimerParametrs_t *packet, time_t *timeUnix) {
	struct tm					timeinfo;
	int							tm_year;

	tm_year = ((packet->year1 << 8) | packet->year2) - 1900;
	timeinfo.tm_year = tm_year;
	timeinfo.tm_mon = packet->month - 1;
	timeinfo.tm_mday = packet->day;
	timeinfo.tm_hour = packet->hourUtc;
	timeinfo.tm_min = packet->minuteUtc;
	timeinfo.tm_sec = packet->secondUtc;
	timeUnix[0x0] = mktime(&timeinfo);
	if (timeinfo.tm_sec != packet->secondUtc || timeinfo.tm_min != packet->minuteUtc || timeinfo.tm_hour != packet->hourUtc || timeinfo.tm_mday != packet->day || timeinfo.tm_mon != packet->month - 1 || timeinfo.tm_year != tm_year)
		return (false);
	return (true);
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

static int _set(ZwTimerParametrsSetFrame_t *packet) {
	time_t						timeUnix;

	if (zuno_CCTimerParametrsGet(&packet->time, &timeUnix) == false)
		return (ZUNO_COMMAND_BLOCKED);
	zunoSetTimeStamp(timeUnix);
	zunoSysHandlerCall(ZUNO_HANDLER_NOTIFICATON_TIME_STAMP, 0x0);
	return (ZUNO_COMMAND_PROCESSED);
}

static int _report(void) {
	ZwTimerParametrsReportFrame_t			*report;
	time_t									time;

	report = (ZwTimerParametrsReportFrame_t *)&CMD_REPLY_CC;
	// report->cmdClass = COMMAND_CLASS_TIME_PARAMETERS; //set in - fillOutgoingPacket
	// report->cmd = TIME_PARAMETERS_REPORT; //set in - fillOutgoingPacket
	time = zunoGetTimeStamp();
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