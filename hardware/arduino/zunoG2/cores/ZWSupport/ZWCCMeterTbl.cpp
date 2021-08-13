#include "Arduino.h"
#include "time.h"
#include "ZWCCMeterTbl.h"
#include "Custom_timestamp.h" 

uint8_t zunoMeterTblId(byte channel, uint8_t *meterIdCharacter) __attribute__ ((weak));
uint8_t zunoMeterTblId(byte channel, uint8_t *meterIdCharacter) {
	uint32_t							number;

	number = rand();
	ultoa(number, (char *)meterIdCharacter, 0xA);
	return (strlen((char *)meterIdCharacter));
	(void)channel;
}

const ZunoMeterTblCapability_t *zunoMeterTblCapability(byte channel) __attribute__ ((weak));
const ZunoMeterTblCapability_t *zunoMeterTblCapability(byte channel) {
	static const ZunoMeterTblCapability_t				capability = {0,0,0};

	return (&capability);
	(void)channel;
}

time_t zunoMeterTblHistoryTimeFind(time_t stop_time) __attribute__ ((weak));
time_t zunoMeterTblHistoryTimeFind(time_t stop_time) {
	return (stop_time);
}

time_t zunoMeterTblHistoryFindNext(time_t stop_time) __attribute__ ((weak));
time_t zunoMeterTblHistoryFindNext(time_t stop_time) {
	return (0);
	(void)stop_time;
}

void zunoMeterTblHistoryGetValue(byte channel, time_t time, size_t dataset, ZunoMeterTblHistoryValue_t *lp) __attribute__ ((weak));
void zunoMeterTblHistoryGetValue(byte channel, time_t time, size_t dataset, ZunoMeterTblHistoryValue_t *lp) {

	lp->precision = ZUNO_METER_TBL_PRECISION_ZERO_DECIMALS;
	lp->scale = ZUNO_METER_TBL_MONITOR_SCALE_GAS_WATER_METER3;
	lp->value = 100;
	(void)channel;
	(void)time;
	(void)dataset;
}

time_t zunoMeterTblHistoryCurrentGetValue(byte channel, size_t dataset, ZunoMeterTblHistoryValue_t *lp) __attribute__ ((weak));
time_t zunoMeterTblHistoryCurrentGetValue(byte channel, size_t dataset, ZunoMeterTblHistoryValue_t *lp) {
	lp->precision = ZUNO_METER_TBL_PRECISION_ZERO_DECIMALS;
	lp->scale = ZUNO_METER_TBL_MONITOR_SCALE_GAS_WATER_METER3;
	lp->value = 100;
	return (ZUNO_SKETCH_BUILD_TS);
	(void)channel;
	(void)dataset;
}

static int _supported_get(void) {
	ZwMeterTblSupportedFrame_t				*report;

	report = (ZwMeterTblSupportedFrame_t *)&CMD_REPLY_CC;
	// report->cmdClass = COMMAND_CLASS_METER_TBL_MONITOR; //set in - fillOutgoingPacket
	// report->cmd = METER_TBL_STATUS_SUPPORTED_REPORT; //set in - fillOutgoingPacket
	report->supportedOperatingStatus1 = 0;
	report->supportedOperatingStatus2 = 0;
	report->supportedOperatingStatus3 = 0;
	report->statusEventLogDepth = 0;
	CMD_REPLY_LEN = sizeof(ZwMeterTblSupportedFrame_t);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _point_adm_no_get(void) {
	ZwMeterTblPointAdmNoReportFrame_t				*report;

	report = (ZwMeterTblPointAdmNoReportFrame_t *)&CMD_REPLY_CC;
	// report->cmdClass = COMMAND_CLASS_METER_TBL_MONITOR; //set in - fillOutgoingPacket
	// report->cmd = METER_TBL_TABLE_POINT_ADM_NO_REPORT; //set in - fillOutgoingPacket
	report->properties1 = 0;//v2++ If the Meter Table Point Adm, Number has not been set using the Meter Table Configuration Command Class, this field MUST be set to 0x00 and the Meter Point Adm. Numbers Character field MUST be omitted. 
	CMD_REPLY_LEN = sizeof(ZwMeterTblPointAdmNoReportFrame_t);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _id_get(size_t channel) {
	ZwMeterTblTableIdReportFrame_t					*report;
	size_t											len;

	report = (ZwMeterTblTableIdReportFrame_t *)&CMD_REPLY_CC;
	// report->cmdClass = COMMAND_CLASS_METER_TBL_MONITOR; //set in - fillOutgoingPacket
	// report->cmd = METER_TBL_TABLE_ID_REPORT; //set in - fillOutgoingPacket
	len = zunoMeterTblId(channel, &report->meterIdCharacter[0]);
	report->properties1 = len;
	CMD_REPLY_LEN = sizeof(ZwMeterTblTableIdReportFrame_t) + len;
	return (ZUNO_COMMAND_ANSWERED);
}

static int _capability_get(size_t channel) {
	ZwMeterTblReportFrame_t						*report;
	const ZunoMeterTblCapability_t				*capability;

	capability = zunoMeterTblCapability(channel);
	report = (ZwMeterTblReportFrame_t *)&CMD_REPLY_CC;
	// report->cmdClass = COMMAND_CLASS_METER_TBL_MONITOR; //set in - fillOutgoingPacket
	// report->cmd = METER_TBL_REPORT; //set in - fillOutgoingPacket
	report->properties1 = ZUNO_CFG_CHANNEL(channel).sub_type;
	report->properties2 = ZUNO_CFG_CHANNEL(channel).params[0];
	memcpy(&report->datasetSupported, &capability->datasetSupported, sizeof(report->datasetSupported));
	memcpy(&report->datasetHistorySupported, &capability->datasetHistorySupported, sizeof(report->datasetHistorySupported));
	_zme_memcpy((byte *)&report->dataHistorySupported, (byte *)&capability->dataHistorySupported, sizeof(report->dataHistorySupported));
	CMD_REPLY_LEN = sizeof(ZwMeterTblReportFrame_t);
	return (ZUNO_COMMAND_ANSWERED);
}

static uint8_t _bitCount (uint32_t n) {
	n -= (n >> 1) & 0x55555555;
	n = ((n >> 2) & 0x33333333 ) + (n & 0x33333333);
	n = ((((n >> 4) + n) & 0x0F0F0F0F) * 0x01010101) >> 24;
	return ((uint8_t)n);
}

static int _current_data_get(size_t channel, ZwMeterTblCurrentDataGetFrame_t *packed) {
	ZwMeterTblCurrentDataReportFrame_t		*report;
	size_t									dataset;
	size_t									reportsToFollow;
	size_t									shift;
	ZunoMeterTblHistoryValue_t				out;
	size_t									tempos;
	time_t									current_time;

	report = (ZwMeterTblCurrentDataReportFrame_t *)&CMD_REPLY_CC;
	// report->cmdClass = COMMAND_CLASS_METER_TBL_MONITOR; //set in - fillOutgoingPacket
	// report->cmd = METER_TBL_CURRENT_DATA_REPORT; //set in - fillOutgoingPacket
	report->properties1 = ZUNO_CFG_CHANNEL(channel).sub_type >> METER_TBL_REPORT_PROPERTIES1_RATE_TYPE_SHIFT;
	CMD_REPLY_LEN = sizeof(ZwMeterTblCurrentDataReportFrame_t);
	memcpy(&dataset, &packed->datasetRequested[0], sizeof(packed->datasetRequested));
	reportsToFollow = _bitCount(dataset);
	shift = 0;
	while (reportsToFollow-- != 0) {
		report->reportsToFollow = reportsToFollow;
		while ((dataset & 0x1) == 0) {
			dataset = dataset >> 1;
			shift++;
		}
		tempos = (1 << shift);
		memcpy(&report->dataset[0], &tempos, sizeof(report->dataset));
		current_time = zunoMeterTblHistoryCurrentGetValue(channel, tempos, &out);
		zuno_CCTimerParametrsSet(&report->time, current_time);
		report->properties2 = (out.precision << 0x5) | out.scale;
		_zme_memcpy((byte *)&report->currentValue[0], (byte *)&out.value, sizeof(report->currentValue));
		zunoSendZWPackage(&g_outgoing_main_packet);
	}
	return (ZUNO_COMMAND_PROCESSED);
}

static int _historical_data_get(size_t channel, ZwMeterTblHistoricalDataGet_t *packed) {
	ZwMeterTblHistoricalDataReport_t		*report;
	time_t									start_time;
	time_t									stop_time;
	time_t									next_time;
	size_t									dataset;
	size_t									maximumReports;
	size_t									reportsToFollow;
	size_t									shift;
	ZunoMeterTblHistoryValue_t				out;
	size_t									tempos;

	zuno_CCTimerParametrsGet(&packed->start_time, &start_time);
	zuno_CCTimerParametrsGet(&packed->stop_time, &stop_time);
	stop_time = zunoMeterTblHistoryTimeFind(stop_time);
	if (stop_time < start_time)
		return (ZUNO_COMMAND_PROCESSED);
	memcpy(&dataset, &packed->historicalDatasetRequested[0], sizeof(packed->historicalDatasetRequested));
	report = (ZwMeterTblHistoricalDataReport_t *)&CMD_REPLY_CC;
	// report->cmdClass = COMMAND_CLASS_METER_TBL_MONITOR; //set in - fillOutgoingPacket
	// report->cmd = METER_TBL_HISTORICAL_DATA_REPORT; //set in - fillOutgoingPacket
	report->properties1 = ZUNO_CFG_CHANNEL(channel).sub_type >> METER_TBL_REPORT_PROPERTIES1_RATE_TYPE_SHIFT;
	CMD_REPLY_LEN = sizeof(ZwMeterTblHistoricalDataReport_t);
	maximumReports = packed->maximumReports;
	while (maximumReports-- != 0) {
		zuno_CCTimerParametrsSet(&report->time, stop_time);
		next_time = zunoMeterTblHistoryFindNext(stop_time);
		if (next_time < start_time)
			maximumReports = 0;
		reportsToFollow = _bitCount(dataset);
		shift = 0;
		while (reportsToFollow-- != 0) {
			report->reportsToFollow = (maximumReports != 0) ? 0xFF : reportsToFollow;
			while ((dataset & 0x1) == 0) {
				dataset = dataset >> 1;
				shift++;
			}
			tempos = (1 << shift);
			memcpy(&report->dataset[0], &tempos, sizeof(report->dataset));
			zunoMeterTblHistoryGetValue(channel, stop_time, tempos, &out);
			report->properties2 = (out.precision << 0x5) | out.scale;
			_zme_memcpy((byte *)&report->historicalValue[0], (byte *)&out.value, sizeof(report->historicalValue));
			zunoSendZWPackage(&g_outgoing_main_packet);
			stop_time = next_time;
		}
	}
	return (ZUNO_COMMAND_PROCESSED);
}

int zuno_CCMeterTblMonitorHandler(byte channel, ZUNOCommandPacket_t *cmd) {
	int								rs;

	switch (ZW_CMD) {
		case METER_TBL_STATUS_SUPPORTED_GET:
			rs = _supported_get();
			break ;
		case METER_TBL_TABLE_POINT_ADM_NO_GET:
			rs = _point_adm_no_get();
			break ;
		case METER_TBL_TABLE_ID_GET:
			rs = _id_get(channel);
			break ;
		case METER_TBL_TABLE_CAPABILITY_GET:
			rs = _capability_get(channel);
			break ;
		case METER_TBL_CURRENT_DATA_GET:
			rs = _current_data_get(channel, (ZwMeterTblCurrentDataGetFrame_t *)cmd->cmd);
			break ;
		case METER_TBL_HISTORICAL_DATA_GET:
			rs = _historical_data_get(channel, (ZwMeterTblHistoricalDataGet_t *)cmd->cmd);
			break ;
		default:
			rs = ZUNO_UNKNOWN_CMD;
			break ;
	}
	return (rs);
	(void)channel;
}