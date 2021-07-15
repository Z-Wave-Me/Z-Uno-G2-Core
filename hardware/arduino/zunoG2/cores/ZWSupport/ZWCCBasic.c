#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCTimer.h"
#include "ZWCCBasic.h"

static int _basic_set(byte channel, const ZwBasicSetFrame_t *paket) {
	ZunoTimerBasic_t				*lp;
	size_t							value;

	zunoEnterCritical();
	if ((lp = zuno_CCTimerBasicFind(channel)) != 0x0 && lp->channel != 0x0)
		lp->channel = 0x0;
	zunoExitCritical();
	value = paket->value;
	switch (ZUNO_CFG_CHANNEL(channel).type) {
		#ifdef WITH_CC_SWITCH_BINARY
		case ZUNO_SWITCH_BINARY_CHANNEL_NUMBER:
			if (value > 0x63 && value < 0xFF)
				return (ZUNO_COMMAND_BLOCKED);
			value = value ? 0xFF : 0x00;// Map the value right way
			break;
		#endif
		default:
			break;
	}
	zuno_universalSetter1P(channel, value);
	zunoSendReport(channel + 1);
	return (ZUNO_COMMAND_PROCESSED);
}

static int _basic_get(byte channel) {
	ZwBasicReportV2Frame_t					*report;
	ZunoTimerBasic_t						*lp;
	size_t									currentValue;
	size_t									targetValue;
	size_t									duration;

	report = (ZwBasicReportV2Frame_t *)&CMD_REPLY_CC;
	// report->cmdClass = COMMAND_CLASS_BASIC; set in - fillOutgoingPacket
	// report->cmd = BASIC_REPORT; set in - fillOutgoingPacket
	currentValue = zuno_universalGetter1P(channel);
	switch (ZUNO_CFG_CHANNEL(channel).type) {
		#ifdef WITH_CC_SWITCH_BINARY
		case ZUNO_SWITCH_BINARY_CHANNEL_NUMBER:
			currentValue = currentValue ? 0xFF : 0x00;
			break;
		#endif
		default:
			break;
	}
	zunoEnterCritical();
	if ((lp = zuno_CCTimerBasicFind(channel)) != 0x0 && lp->channel != 0x0) {
		duration = zuno_CCTimerTable8(lp->ticksEnd - lp->ticks);
		targetValue = lp->targetValue;
	}
	else {
		targetValue = currentValue;
		duration = 0x0;
	}
	report->currentValue = currentValue;
	report->targetValue = targetValue;
	report->duration = duration;
	zunoExitCritical();
	CMD_REPLY_LEN = sizeof(ZwBasicReportV2Frame_t);
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCBasicHandler(byte channel, ZUNOCommandPacket_t * cmd) {
	int										rs;

	switch(ZW_CMD){
		case BASIC_GET:
			rs = _basic_get(channel);
			break ;
		case BASIC_SET:
			rs = _basic_set(channel, (const ZwBasicSetFrame_t *)cmd->cmd);
			break ;
		default:
			rs = ZUNO_UNKNOWN_CMD;
			break ;
	}
	return rs;
}