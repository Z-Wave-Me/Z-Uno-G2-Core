#include "ZWCCMeter.h"
#include "ZWSupport.h"
#include "Arduino.h"

#define DEBUGSERIAL Serial0
#define dbgprint(a)              \
    DEBUGSERIAL.print("[DBG] "); \
    DEBUGSERIAL.print(a)

#define dbgprintln(a) DEBUGSERIAL.println(a, HEX)

int zuno_CCMeterReport(byte channel, const ZUNOCommandPacket_t *paket) {
	ZwMeterReportFrame_t				*report;
	uint32_t							params;
	uint32_t							channel_size;
	int32_t								value;
	uint8_t								*lp;
	size_t								len;
	const ZwMeterGetFrame_t				*cmd;
	size_t								scale;
	size_t								properties1;
	size_t								type;
	uint8_t								*paket_len;

	params = ZUNO_CFG_CHANNEL(channel).params[0];
	if (paket == 0x0 || (len = paket->len) == sizeof(ZW_METER_GET_FRAME)) {
		len = sizeof(ZW_METER_GET_FRAME);
	}
	else {
		cmd = (const ZwMeterGetFrame_t *)paket->cmd;
		properties1 = cmd->v6.properties1;
		type = (properties1 & METER_GET_PROPERTIES1_RATE_TYPE_MASK) >> METER_GET_PROPERTIES1_RATE_TYPE_SHIFT;
		if (len == sizeof(ZW_METER_GET_V6_FRAME) && !(METER_GET_RATE_TYPE_IMPORT == type || type == 0x0))
			return (ZUNO_COMMAND_BLOCKED);
		scale = (properties1 & METER_GET_PROPERTIES1_SCALE_MASK) >> METER_GET_PROPERTIES1_SCALE_SHIFT;
		if (scale != 0x0 && scale != GET_SCALE(params))
			return (ZUNO_COMMAND_BLOCKED);
	}
	if (paket != 0x0) {
		paket_len = &CMD_REPLY_LEN;
		report = (ZwMeterReportFrame_t *)&CMD_REPLY_CC;
	}
	else {
		paket_len = &CMD_REPORT_LEN;
		report = (ZwMeterReportFrame_t *)&CMD_REPORT_CC;
	}
	report->v3.byte1.cmdClass = COMMAND_CLASS_METER;
	report->v3.byte1.cmd = METER_REPORT;
	report->v3.byte1.properties1 = (ZUNO_CFG_CHANNEL(channel).sub_type & METER_REPORT_PROPERTIES1_METER_TYPE_MASK) | (len == sizeof(ZW_METER_GET_FRAME) ? 0x0  : (METER_REPORT_RATE_TYPE_IMPORT << METER_REPORT_PROPERTIES1_RATE_TYPE_SHIFT) | GET_SCALE2(params));
	report->v3.byte1.properties2 = COMBINE_PARAMS(params);
	channel_size = GET_SIZE(params);
	value = zuno_universalGetter1P(channel);
	lp = &report->v3.byte1.meterValue1;
	_zme_memcpy(lp, (uint8_t *)&value, channel_size);
	lp[channel_size] = 0;//deltaTime1
	lp[channel_size + 1] = 0;//deltaTime2 if deltaTime == 0 previousMeterValue not support
	paket_len[0x0] = 0x6 + channel_size;
	return (ZUNO_COMMAND_ANSWERED);
}

static int _reset(size_t channel, const ZwMeterResetFrame_t *cmd, size_t len) {
	size_t							value;

	value = 0x0;
	switch (len) {
		case sizeof(cmd->v2):
			break ;
		default:
			_zme_memcpy((uint8_t *)&value, (uint8_t *)&cmd->v6.meterValue1, cmd->v6.properties1 >> METER_RESET_PROPERTIES1_SIZE_SHIFT);
			break ;
	}
	zuno_universalSetter1P(channel, value);
	return (ZUNO_COMMAND_PROCESSED);
}

int zuno_CCMeterHandler(byte channel, ZUNOCommandPacket_t *cmd) {
	int								rs;

	switch (ZW_CMD) {
		case METER_GET:
			_zunoMarkChannelRequested(channel);
			rs = zuno_CCMeterReport(channel, cmd);
			break ;
		case METER_SUPPORTED_GET://v6
			CMD_REPLY_DATA(0) = ZUNO_CFG_CHANNEL(channel).sub_type | (METER_SUPPORTED_REPORT_RATE_TYPE_IMPORT_ONLY << METER_SUPPORTED_REPORT_PROPERTIES1_RATE_TYPE_SHIFT);
			CMD_REPLY_DATA(1) = 1 << (ZUNO_CFG_CHANNEL(channel).params[0] & 0x07);
			CMD_REPLY_LEN = 4;
			rs = ZUNO_COMMAND_ANSWERED;
			break ;
		case METER_RESET:
			rs = _reset(channel, (const ZwMeterResetFrame_t *)cmd->cmd, cmd->len);
			break ;
		default:
			rs = ZUNO_UNKNOWN_CMD;
			break ;
	}
	return (rs);
}