#include "ZWCCMeter.h"
#include "ZWSupport.h"
#include "Arduino.h"

#define DEBUGSERIAL Serial0
#define dbgprint(a)              \
    DEBUGSERIAL.print("[DBG] "); \
    DEBUGSERIAL.print(a)

#define dbgprintln(a) DEBUGSERIAL.println(a, HEX)

int zuno_CCMeterReport(byte channel) {
	ZwMeterReportFrame_t				*report;
	uint32_t							params;
	uint32_t							channel_size;
	int32_t								value;
	uint8_t								*lp;

	report = (ZwMeterReportFrame_t *)&CMD_REPLY_CC;
	report->v3.byte1.cmdClass = COMMAND_CLASS_METER;
	report->v3.byte1.cmd = METER_REPORT;
	params = ZUNO_CFG_CHANNEL(channel).params[0];
	report->v3.byte1.properties1 = METER_RATE_IMPORT | (ZUNO_CFG_CHANNEL(channel).sub_type & 0x1F) | GET_SCALE2(params);
	report->v3.byte1.properties2 = COMBINE_PARAMS(params);
	channel_size = GET_SIZE(params);
	value = zuno_universalGetter1P(channel);
	lp = &report->v3.byte1.meterValue1;
	memcpy(lp, &value, channel_size);
	lp[channel_size] = 0;//deltaTime1
	lp[channel_size + 1] = 0;//deltaTime2 if deltaTime == 0 previousMeterValue not support
	CMD_REPLY_LEN = 6 + channel_size;
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCMeterHandler(byte channel, ZUNOCommandPacket_t *cmd)
{
    int rs = ZUNO_UNKNOWN_CMD;

    switch (ZW_CMD)
    {
        case METER_GET:
            rs = zuno_CCMeterReport(channel);
            break;

        case METER_SUPPORTED_GET:
            CMD_REPLY_DATA(0) = ZUNO_CFG_CHANNEL(channel).sub_type | METER_RATE_IMPORT;
            CMD_REPLY_DATA(1) = 1 << (ZUNO_CFG_CHANNEL(channel).params[0] & 0x07);
            CMD_REPLY_LEN = 4;

            rs = ZUNO_COMMAND_ANSWERED;
            break;

        case METER_RESET:
            zuno_universalSetter1P(channel, 0);

            rs = ZUNO_COMMAND_ANSWERED;
        }
    return rs;
}