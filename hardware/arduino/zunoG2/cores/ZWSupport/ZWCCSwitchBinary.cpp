#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCTimer.h"
#include "ZWCCSwitchBinary.h"
#include "ZWCCSuperVision.h"

int zuno_CCSwitchBinaryReport(byte channel, ZUNOCommandPacket_t *packet) {
	ZwBasicBinaryReportFrame_t				*report;
	size_t									currentValue;
	size_t									targetValue;
	size_t									duration;
	ZunoTimerBasic_t						*lp;

	currentValue = zuno_universalGetter1P(channel) ? 0xFF : 0x00;
	zunoEnterCritical();
	if ((lp = zuno_CCTimerBasicFind(channel)) != 0x0 && lp->channel != 0x0) {
		duration = millis();
		if (lp->ticksEnd > duration)
			duration = lp->ticksEnd - duration;
		else
			duration = 0x0;
		duration = zuno_CCTimerTable8(duration);
		targetValue = lp->targetValue;
	}
	else {
		targetValue = currentValue;
		duration = 0x0;
	}
	zunoExitCritical();
	report = (ZwBasicBinaryReportFrame_t *)&packet->cmd[0x0];
	report->v2.cmdClass = COMMAND_CLASS_SWITCH_BINARY;
	report->v2.cmd = SWITCH_BINARY_REPORT;
	report->v2.currentValue = currentValue;
	report->v2.targetValue = targetValue;
	report->v2.duration = duration;
	packet->len = sizeof(report->v2);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _set(ZwSwitchBinarySetFrame_t *cmd, size_t len, size_t channel) {
	size_t							value;
	size_t							duration;
	ZunoTimerBasic_t				*lp;
	size_t							currentValue;

	if ((value = cmd->v2.targetValue) > 0x63 && value < 0xFF)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	value = value ? 0xFF : 0x00;// Map the value right way
	currentValue = zuno_universalGetter1P(channel) ? 0xFF : 0x00;
	if (currentValue != value) {
		switch (len) {
			case sizeof(cmd->v2):
				if ((duration = (zuno_CCTimerTicksTable7(cmd->v2.duration))) == 0x0) {
					zuno_CCTimerBasicFindStop(channel);
					break ;
				}
				zunoEnterCritical();
				if ((lp = zuno_CCTimerBasicFind(channel)) == 0x0) {
					zunoExitCritical();
					break ;
				}
				lp->bMode = 0x0;
				lp->channel = channel + 0x1;
				lp->ticksEnd = millis() + duration;
				lp->targetValue = value;
				zunoExitCritical();
				zuno_CCSupervisionReport(ZUNO_COMMAND_BLOCKED_WORKING, cmd->v2.duration, lp);
				return (ZUNO_COMMAND_PROCESSED);
				break ;
			default:
				break ;
		}
	}
	else
		zuno_CCTimerBasicFindStop(channel);
	zuno_universalSetter1P(channel, value);
	zunoSendReport(channel + 0x1);
	return (ZUNO_COMMAND_PROCESSED);
}

int zuno_CCSwitchBinaryHandler(byte channel, ZUNOCommandPacket_t *cmd){
	int							rs;

	switch(ZW_CMD) {
		case SWITCH_BINARY_GET:
			rs = zuno_CCSwitchBinaryReport(channel, &g_outgoing_main_packet);
			_zunoMarkChannelRequested(channel);
			break;
		case SWITCH_BINARY_SET:
			rs = _set((ZwSwitchBinarySetFrame_t *)cmd->cmd, cmd->len, channel);
			break;
		default:
			rs = ZUNO_COMMAND_BLOCKED_NO_SUPPORT;
			break ;
	}
	return (rs);
}

void zuno_CCSwitchBinaryTimer(ZunoTimerBasic_t *lp) {
	size_t									channel;
	size_t									ticks;

	ticks = millis();
	if (ticks < lp->ticksEnd)
		return ;
	channel = lp->channel;
	zuno_universalSetter1P(channel - 1, lp->targetValue);
	zunoSendReport(channel);
	lp->channel = 0x0;
	if (lp->bMode == ZUNO_TIMER_SWITCH_SUPERVISION) {
		__cc_supervision._unpacked = true;
		zuno_CCSupervisionReport(ZUNO_COMMAND_PROCESSED, 0x0, 0x0);
	}
}