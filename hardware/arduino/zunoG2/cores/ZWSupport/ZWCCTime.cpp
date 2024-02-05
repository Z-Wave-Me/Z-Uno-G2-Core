#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCTime.h"

#ifdef WITH_CC_TIME

#define TIME_PERIOD_FAIL_REPEAT							(1 * 60 * 1000 * 1000)//1 minute
#define TIME_PERIOD_REPEAT								(8 * 60 * 60 * 1000 * 1000)//8 hours

typedef enum							ZwCCTimeState_e
{
	ZwCCTimeStateWaitNetwork,
	ZwCCTimeStateWait,
}										ZwCCTimeState_t;

typedef struct					ZwCCTimeDateReportInfo_s
{
	uint8_t						year1;/* MSB */
	uint8_t						year2;/* LSB */
	uint8_t						month;/**/
	uint8_t						day;/**/
}								ZwCCTimeDateReportInfo_t;

typedef struct					ZwCCTimeDateReport_s
{
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	ZwCCTimeDateReportInfo_t	info;
}								ZwCCTimeDateReport_t;

typedef struct					ZwCCTimeTimeReportInfo_s
{
	uint8_t						properties1;/* masked byte */
	uint8_t						minuteLocalTime;/**/
	uint8_t						secondLocalTime;/**/
}								ZwCCTimeTimeReportInfo_t;

typedef struct					ZwCCTimeTimeReport_s
{
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	ZwCCTimeTimeReportInfo_t	info;
}								ZwCCTimeTimeReport_t;

typedef struct					ZwCCTimeGet_s
{
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
}								ZwCCTimeGet_t;

static ZwCCTimeDateReportInfo_t _date_report_info;
static ZwCCTimeState_t _state_timer = ZwCCTimeStateWaitNetwork;
static uint64_t _new_update_time_stamp_micros = 0x0;
static uint64_t _micros_date_report = 0x0;

uint64_t rtcc_micros(void);

static void _send(uint8_t cmd) {
	ZwCCTimeGet_t											*report;
	ZUNOCommandPacketReport_t								frame;

	fillOutgoingReportPacketAsync(&frame, 0x0);
	report = (ZwCCTimeGet_t *)&frame.packet.cmd[0x0];
	report->cmdClass = COMMAND_CLASS_TIME;
	report->cmd = cmd;
	frame.packet.len = sizeof(report[0x0]);
	zunoSendZWPackage(&frame.packet);
}

static int _time_data_report(const ZwCCTimeDateReport_t *in) {
	_date_report_info = in->info;
	_micros_date_report = rtcc_micros();
	_send(TIME_GET);
	return (ZUNO_COMMAND_PROCESSED);
}

static void _lock(bool lock) {
	static bool								status = false;

	zunoEnterCritical();
	if (lock == true) {
		if (status == false) {
			status = true;
			g_sleep_data.latch++;
		}
	}
	else {
		if (status == true) {
			status = false;
			g_sleep_data.latch--;
		}
	}
	zunoExitCritical();
}

static time_t _get_time_stamp(const ZwCCTimeTimeReport_t *in) {
	time_t											timeUnix;
	struct tm										timeinfo;
	int												tm_year;
	uint64_t										micros;

	if (_micros_date_report == 0x0)
		return (0x0);
	micros = ((in->info.properties1 & TIME_REPORT_PROPERTIES1_HOUR_LOCAL_TIME_MASK) * 60);
	micros = (in->info.secondLocalTime + ((in->info.minuteLocalTime + micros) * 60)) * 1000000;
	if ((rtcc_micros() - _micros_date_report) > micros)
		return (0x0);
	tm_year = ((_date_report_info.year1 << 8) | _date_report_info.year2) - 1900;
	timeinfo.tm_year = tm_year;
	timeinfo.tm_mon = _date_report_info.month - 1;
	timeinfo.tm_mday = _date_report_info.day;
	timeinfo.tm_hour = in->info.properties1 & TIME_REPORT_PROPERTIES1_HOUR_LOCAL_TIME_MASK;
	timeinfo.tm_min = in->info.minuteLocalTime;
	timeinfo.tm_sec = in->info.secondLocalTime;
	timeUnix = mktime(&timeinfo);
	if (timeinfo.tm_sec != in->info.secondLocalTime || timeinfo.tm_min != in->info.minuteLocalTime || timeinfo.tm_hour != (in->info.properties1 & TIME_REPORT_PROPERTIES1_HOUR_LOCAL_TIME_MASK) || timeinfo.tm_mday != _date_report_info.day || timeinfo.tm_mon != _date_report_info.month - 1 || timeinfo.tm_year != tm_year)
		return (0x0);
	_lock(false);
	return (timeUnix);
}

static int _time_time_report(const ZwCCTimeTimeReport_t *in) {
	time_t											timeUnix;

	if ((timeUnix = _get_time_stamp(in)) == 0x0) {
		_micros_date_report = 0x0;
		return (ZUNO_COMMAND_BLOCKED);
	}
	_new_update_time_stamp_micros = rtcc_micros() + TIME_PERIOD_REPEAT;
	zunoSetTimeStamp(timeUnix);
	return (ZUNO_COMMAND_PROCESSED);
}

int zuno_CCTimeHandler(ZUNOCommandPacket_t *cmd) {
	int								rs;

	switch (ZW_CMD) {
		case TIME_REPORT:
			rs = _time_time_report((const ZwCCTimeTimeReport_t *)&cmd->cmd[0x0]);
			break ;
		case DATE_REPORT:
			rs = _time_data_report((const ZwCCTimeDateReport_t *)&cmd->cmd[0x0]);
			break ;
		default:
			rs = ZUNO_UNKNOWN_CMD;
			break ;
	}
	return (rs);
}

static void _zuno_CCTimeHandlerTimerStateWaitSet(void) {
	uint64_t									micros;

	if ((micros = rtcc_micros()) >= _new_update_time_stamp_micros) {
		_lock(true);
		_micros_date_report = 0x0;
		_new_update_time_stamp_micros = micros + TIME_PERIOD_FAIL_REPEAT;
		_send(DATE_GET);
	}
}

void zuno_CCTimeHandlerTimer(void) {
	switch (_state_timer) {
		case ZwCCTimeStateWaitNetwork:
			if (zunoInNetwork() == true) {
				_state_timer = ZwCCTimeStateWait;
				_zuno_CCTimeHandlerTimerStateWaitSet();
			}
			break ;
		case ZwCCTimeStateWait:
			_zuno_CCTimeHandlerTimerStateWaitSet();
			break ;
	}
}

#endif//WITH_CC_TIME