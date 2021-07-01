#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCTimer.h"
#include "ZWCCSwitchBinary.h"

#define ZUNO_TIMER_SWITCH_BINARY_MAX_CHANNAL	0x3//How many channels at the same time support for dimming

typedef struct					ZunoTimerDimmingSwitchBinary_s
{
	ZunoTimerDimmingStart_t		start;
	uint8_t						targetValue;
	uint32_t					ticksEnd;
}								ZunoTimerDimmingSwitchBinary_t;

static ZunoTimerDimmingSwitchBinary_t _switchBinary[ZUNO_TIMER_SWITCH_BINARY_MAX_CHANNAL];

int zuno_CCSwitchBinaryReport(byte channel, bool reply) {
	ZwBasicBinaryReportFrame_t				*report;
	size_t									currentValue;
	size_t									targetValue;
	size_t									duration;
	ZunoTimerDimmingSwitchBinary_t			*lpV2;

	if(reply){
		CMD_REPLY_LEN = sizeof(report->v2);
		report = (ZwBasicBinaryReportFrame_t *)&CMD_REPLY_CC;
	} else {
		CMD_REPORT_LEN = sizeof(report->v2);
		report = (ZwBasicBinaryReportFrame_t *)&CMD_REPORT_CC;
	}	
	currentValue = zuno_universalGetter1P(channel) ? 0xFF : 0x00;
	zunoEnterCritical();
	lpV2 = (ZunoTimerDimmingSwitchBinary_t *)zuno_CCTimerFind(channel, &_switchBinary[0], &_switchBinary[ZUNO_TIMER_SWITCH_BINARY_MAX_CHANNAL], sizeof(ZunoTimerDimmingSwitchBinary_t));
	if (lpV2 == 0 || lpV2->start.channel == 0) {
		targetValue = currentValue;
		duration = 0;
	}
	else {
		targetValue = lpV2->targetValue;
		duration = zuno_CCTimerTable8(lpV2->ticksEnd - g_zuno_timer.ticks);
	}
	zunoExitCritical();
	report->v2.cmdClass = COMMAND_CLASS_SWITCH_BINARY;
	report->v2.cmd = SWITCH_BINARY_REPORT;
	report->v2.currentValue = currentValue;
	report->v2.targetValue = targetValue;
	report->v2.duration = duration;
	CMD_REPLY_LEN = sizeof(report->v2);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _set(ZwSwitchBinarySetFrame_t *cmd, size_t len, size_t channel) {
	size_t							value;
	size_t							duration;
	ZunoTimerDimmingSwitchBinary_t	*lpV2;

	value = cmd->v2.targetValue ? 0xFF : 0x00;// Map the value right way
	switch (len) {
		case sizeof(cmd->v2):
			if ((duration = zuno_CCTimerTicksTable7(cmd->v2.duration)) == 0)
				break ;
			zunoEnterCritical();
			if ((lpV2 = (ZunoTimerDimmingSwitchBinary_t *)zuno_CCTimerFind(channel, &_switchBinary[0], &_switchBinary[ZUNO_TIMER_SWITCH_BINARY_MAX_CHANNAL], sizeof(ZunoTimerDimmingSwitchBinary_t))) == 0) {
				zunoExitCritical();
				break ;
			}
			lpV2->start.channel = channel + 1;
			lpV2->start.bMode = ZUNO_TIMER_SWITCH_DIMMING;
			lpV2->ticksEnd = g_zuno_timer.ticks + duration;
			lpV2->targetValue = value;
			zunoExitCritical();
			return (ZUNO_COMMAND_PROCESSED);
			break ;
		default:
			break ;
	}
	zuno_universalSetter1P(channel, value);
	zunoSendReport(channel + 1);
	return (ZUNO_COMMAND_PROCESSED);
}

int zuno_CCSwitchBinaryHandler(byte channel, ZUNOCommandPacket_t *cmd){
	int							rs;

	switch(ZW_CMD) {
		case SWITCH_BINARY_GET:
			rs = zuno_CCSwitchBinaryReport(channel, true);
			_zunoMarkChannelRequested(channel);
			break;
		case SWITCH_BINARY_SET:
			rs = _set((ZwSwitchBinarySetFrame_t *)cmd->cmd, cmd->len, channel);
			break;
		default:
			rs = ZUNO_UNKNOWN_CMD;
			break ;
	}
	return (rs);
}

static void _zuno_CCSwitchBinaryTimer(size_t ticks, ZunoTimerDimmingSwitchBinary_t *lpV2) {
	size_t									channel;

	if (ticks < lpV2->ticksEnd)
		return ;
	channel = lpV2->start.channel;
	zuno_universalSetter1P(channel - 1, lpV2->targetValue);
	zunoSendReport(channel);
	lpV2->start.bMode = lpV2->start.bMode ^ ZUNO_TIMER_SWITCH_DIMMING;
}

void zuno_CCSwitchBinaryTimer(size_t ticks) {
	ZunoTimerDimmingSwitchBinary_t				*lp_b;
	ZunoTimerDimmingSwitchBinary_t				*lp_e;

	lp_b = &_switchBinary[0];
	lp_e = &_switchBinary[ZUNO_TIMER_SWITCH_BINARY_MAX_CHANNAL];
	while (lp_b < lp_e) {
		if ((lp_b->start.bMode & ZUNO_TIMER_SWITCH_DIMMING) != 0)
			_zuno_CCSwitchBinaryTimer(ticks, lp_b);
		lp_b++;
	}
}