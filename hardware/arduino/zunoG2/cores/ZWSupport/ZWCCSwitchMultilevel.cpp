#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCTimer.h"
#include "ZWCCSwitchMultilevel.h"

#define ZUNO_TIMER_SWITCH_MULTILEVEL_MAX_CHANNEL					0x3//How many channels at the same time support for dimming

typedef struct					ZunoTimerSwitchMultilevel_s
{
	ZunoTimerDimmingStart_t		start;
	uint8_t						targetValue;
	uint8_t						current_level;//Current Dimming Level
	uint32_t					ticks;//The number of milliseconds since starting the current program divided by 10 - Saved while changing current level
	uint32_t					step;//How many milliseconds divided by 10 to wait until the next change in the current dimming level
}								ZunoTimerSwitchMultilevel_t;

static ZunoTimerSwitchMultilevel_t _switchMultiLevel[ZUNO_TIMER_SWITCH_MULTILEVEL_MAX_CHANNEL];

static void _start_level(size_t channel, ZUNOCommandPacket_t *cmd) {// Prepare the structure for dimming
	ZwSwitchMultilevelStartLevelChangeFrame_t			*pk;
	ZunoTimerSwitchMultilevel_t							*lpV4;
	uint32_t											step;
	uint8_t												current_level;
	uint8_t												b_mode;

	pk = (ZwSwitchMultilevelStartLevelChangeFrame_t *)cmd->cmd;
	if ((pk->v1.properties1 & (1 << 5)) == 0) {// If the level from which you want to start dimming has come, make it current
		if ((current_level = pk->v1.startLevel) > ZUNO_TIMER_SWITCH_MAX_VALUE)
			current_level = ZUNO_TIMER_SWITCH_MAX_VALUE;
		zuno_universalSetter1P(channel, current_level);
		zunoSendReport(channel + 1);
	} else {// Otherwise, get the current
		if ((current_level = zuno_universalGetter1P(channel)) > ZUNO_TIMER_SWITCH_MAX_VALUE)
			current_level = ZUNO_TIMER_SWITCH_MAX_VALUE;
	}
	if (cmd->len == sizeof(ZwSwitchMultilevelStartLevelChangeV1Frame_t))
		step = ZUNO_TIMER_SWITCH_DEFAULT_DURATION * (1000 / ZUNO_SYSTIMER_PERIOD_MC);// Depending on the version, set the default step to increase or from the command we will
	else
		step =zuno_CCTimerTicksTable7(pk->v2.dimmingDuration);
	if ((pk->v1.properties1 & (1 << 6)) == 0) {// Dimming to up
		if (ZUNO_TIMER_SWITCH_MAX_VALUE - current_level == 0)// Check it may not need to dim
			return ;
		if (step == 0) {// If the step turned out to be zero - immediately set the desired level
			zunoSendReport(channel + 1);
			return (zuno_universalSetter1P(channel, ZUNO_TIMER_SWITCH_MAX_VALUE));
		}
		b_mode = ZUNO_TIMER_SWITCH_INC | ZUNO_TIMER_SWITCH_DIMMING;
	} else {// Dimming to down
		if (current_level == ZUNO_TIMER_SWITCH_MIN_VALUE)// Check it may not need to dim
			return ;
		if (step == 0) {// If the step turned out to be zero - immediately set the desired level
			zunoSendReport(channel + 1);
			return (zuno_universalSetter1P(channel, ZUNO_TIMER_SWITCH_MIN_VALUE));
		}
		b_mode = ZUNO_TIMER_SWITCH_DEC | ZUNO_TIMER_SWITCH_DIMMING;
	}
	zunoEnterCritical();
	if ((lpV4 = (ZunoTimerSwitchMultilevel_t *)zuno_CCTimerFind(channel, &_switchMultiLevel[0], &_switchMultiLevel[ZUNO_TIMER_SWITCH_MULTILEVEL_MAX_CHANNEL], sizeof(ZunoTimerSwitchMultilevel_t))) != 0) {// Trying to find a free structure
		lpV4->step = step / ZUNO_TIMER_SWITCH_MAX_VALUE;
		lpV4->current_level = current_level;
		lpV4->targetValue = (b_mode & ZUNO_TIMER_SWITCH_INC) != 0 ? ZUNO_TIMER_SWITCH_MAX_VALUE : ZUNO_TIMER_SWITCH_MIN_VALUE;
		lpV4->ticks = g_zuno_timer.ticks;
		lpV4->start.bMode = b_mode;
		lpV4->start.channel = channel + 1;
	}
	zunoExitCritical();
}

int zuno_CCSwitchMultilevelReport(byte channel, bool reply) {
	SwitchMultilevelReportFrame_t			*report;
	size_t									currentValue;
	size_t									targetValue;
	size_t									duration;
	ZunoTimerSwitchMultilevel_t				*lpV4;

	currentValue = zuno_universalGetter1P(channel);
	if(currentValue > 99)
		currentValue = 99;
	if (currentValue != 0)
		ZUNO_CFG_CHANNEL(channel).params[0] = currentValue;
	if(reply){
		report = (SwitchMultilevelReportFrame_t *)&CMD_REPLY_CC;
		CMD_REPLY_LEN = sizeof(report->v4);
	} else {
		report = (SwitchMultilevelReportFrame_t *)&CMD_REPORT_CC;
		CMD_REPORT_LEN = sizeof(report->v4);
	}
	zunoEnterCritical();
	lpV4 = (ZunoTimerSwitchMultilevel_t *)zuno_CCTimerFind(channel, &_switchMultiLevel[0], &_switchMultiLevel[ZUNO_TIMER_SWITCH_MULTILEVEL_MAX_CHANNEL], sizeof(ZunoTimerSwitchMultilevel_t));
	if (lpV4 == 0 || lpV4->start.channel == 0) {
		targetValue = currentValue;
		duration = 0;
	}
	else {
		targetValue = lpV4->targetValue;
		duration = zuno_CCTimerTable8(lpV4->ticks - g_zuno_timer.ticks);
	}
	zunoExitCritical();
	
	report->v4.cmdClass = COMMAND_CLASS_SWITCH_MULTILEVEL;
	report->v4.cmd = SWITCH_MULTILEVEL_REPORT;
	report->v4.currentValue = currentValue;
	report->v4.targetValue = targetValue;
	report->v4.duration = duration;
	
	return (ZUNO_COMMAND_ANSWERED);
}

static int _set(SwitchMultilevelSetFrame_t *cmd, size_t len, size_t channel) {
	size_t							value;
	size_t							tempos;
	size_t							duration;
	ZunoTimerSwitchMultilevel_t		*lpV4;

	if ((value = cmd->v4.value) == 0xFF) {
		if ((tempos = ZUNO_CFG_CHANNEL(channel).params[0]) != 0)
			value = tempos;
		else
			value = 99;
	}
	if (value > 99)
		return (ZUNO_COMMAND_BLOCKED);
	switch (len ) {
		case sizeof(cmd->v4):
			if ((duration = zuno_CCTimerTicksTable7(cmd->v4.dimmingDuration)) == 0)
				break ;
			zunoEnterCritical();
			if ((lpV4 = (ZunoTimerSwitchMultilevel_t *)zuno_CCTimerFind(channel, &_switchMultiLevel[0], &_switchMultiLevel[ZUNO_TIMER_SWITCH_MULTILEVEL_MAX_CHANNEL], sizeof(ZunoTimerSwitchMultilevel_t))) == 0) {
				zunoExitCritical();
				break ;
			}
			lpV4->start.channel = channel + 1;
			lpV4->start.bMode = ZUNO_TIMER_SWITCH_DIMMING;
			lpV4->ticks = g_zuno_timer.ticks + duration;
			lpV4->targetValue = value;
			lpV4->step = 0;
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

static int _supported(void) {
	ZwSwitchMultilevelSupportedReportFrame_t		*report;

	report = (ZwSwitchMultilevelSupportedReportFrame_t *)&CMD_REPLY_CC;
	report->cmdClass = COMMAND_CLASS_SWITCH_MULTILEVEL;
	report->cmd = SWITCH_MULTILEVEL_SUPPORTED_REPORT;
	report->properties1 = 0x2;/* A supporting device MUST implement the Primary Switch type. The Primary Switch Type SHOULD be 0x02 (Up/Down).The Primary Switch Type MUST NOT be 0x00 (Undefined). */
	report->properties2 = 0x0;
	CMD_REPLY_LEN = sizeof(ZwSwitchMultilevelSupportedReportFrame_t);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _stop_level(uint8_t channel) {// Stop Dimming
	ZunoTimerSwitchMultilevel_t				*lpV4;

	zunoEnterCritical();
	lpV4 = (ZunoTimerSwitchMultilevel_t *)zuno_CCTimerFind(channel, &_switchMultiLevel[0], &_switchMultiLevel[ZUNO_TIMER_SWITCH_MULTILEVEL_MAX_CHANNEL], sizeof(ZunoTimerSwitchMultilevel_t));
	if (lpV4 != 0 && lpV4->step != 0)
		lpV4->start.bMode = lpV4->start.bMode ^ ZUNO_TIMER_SWITCH_DIMMING;
	zunoExitCritical();
	return (ZUNO_COMMAND_PROCESSED);
}

int zuno_CCSwitchMultilevelHandler(byte channel, ZUNOCommandPacket_t *cmd) {
	int									rs;

	switch(ZW_CMD) {
		case SWITCH_MULTILEVEL_GET:
			rs = zuno_CCSwitchMultilevelReport(channel, true);
			_zunoMarkChannelRequested(channel);
			break;
		case SWITCH_MULTILEVEL_SET:
			rs = _set((SwitchMultilevelSetFrame_t *)cmd->cmd, cmd->len, channel);
			break ;
		case SWITCH_MULTILEVEL_START_LEVEL_CHANGE:
			_start_level(channel, cmd);
			rs = ZUNO_COMMAND_PROCESSED;
			break ;
		case SWITCH_MULTILEVEL_STOP_LEVEL_CHANGE:
			rs = _stop_level(channel);
			break ;
		case SWITCH_MULTILEVEL_SUPPORTED_GET:
			rs = _supported();
			break ;
		default:
			rs = ZUNO_UNKNOWN_CMD;
			break ;
	}
	return rs;
}

static void _zuno_CCSwitchMultilevelTimer(size_t ticks, ZunoTimerSwitchMultilevel_t *lpV4) {
	size_t									channel;
	size_t									tempos;
	size_t									value;

	channel = lpV4->start.channel;
	if (lpV4->step == 0) {
		if (ticks < lpV4->ticks)
			return ;
		value = lpV4->targetValue;
		lpV4->start.bMode = lpV4->start.bMode ^ ZUNO_TIMER_SWITCH_DIMMING;
	}
	else if ((tempos = lpV4->ticks + lpV4->step) > ticks)
		return ;
	else {
		lpV4->ticks = tempos;
		value = (lpV4->current_level += (lpV4->start.bMode & ZUNO_TIMER_SWITCH_INC) != 0 ? 1 : -1);// Depending on the flag, increase or decrease
		if (value == ZUNO_TIMER_SWITCH_MAX_VALUE || value == ZUNO_TIMER_SWITCH_MIN_VALUE)
			lpV4->start.bMode = lpV4->start.bMode ^ ZUNO_TIMER_SWITCH_DIMMING;
	}
	zuno_universalSetter1P(channel - 1, value);
	zunoSendReport(channel);
}

void zuno_CCSwitchMultilevelTimer(size_t ticks) {
	ZunoTimerSwitchMultilevel_t				*lp_b;
	ZunoTimerSwitchMultilevel_t				*lp_e;

	lp_b = &_switchMultiLevel[0];
	lp_e = &_switchMultiLevel[ZUNO_TIMER_SWITCH_MULTILEVEL_MAX_CHANNEL];
	while (lp_b < lp_e) {
		if ((lp_b->start.bMode & ZUNO_TIMER_SWITCH_DIMMING) != 0)
			_zuno_CCSwitchMultilevelTimer(ticks, lp_b);
		lp_b++;
	}
}