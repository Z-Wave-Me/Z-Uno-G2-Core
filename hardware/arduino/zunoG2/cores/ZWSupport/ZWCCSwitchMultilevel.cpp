#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCTimer.h"
#include "ZWCCSwitchMultilevel.h"

static void _start_level(size_t channel, ZUNOCommandPacket_t *cmd) {// Prepare the structure for dimming
	ZwSwitchMultilevelStartLevelChangeFrame_t			*pk;
	ZunoTimerBasic_t									*lp;
	uint32_t											step;
	uint8_t												current_level;
	uint8_t												b_mode;

	pk = (ZwSwitchMultilevelStartLevelChangeFrame_t *)cmd->cmd;
	if ((pk->v1.properties1 & (1 << 5)) == 0) {// If the level from which you want to start dimming has come, make it current
		if ((current_level = pk->v1.startLevel) > ZUNO_TIMER_SWITCH_MAX_VALUE)
			current_level = ZUNO_TIMER_SWITCH_MAX_VALUE;
		if (current_level != 0x0)
			ZUNO_CFG_CHANNEL(channel).params[0] = current_level;
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
		b_mode = ZUNO_TIMER_SWITCH_INC;
	} else {// Dimming to down
		if (current_level == ZUNO_TIMER_SWITCH_MIN_VALUE)// Check it may not need to dim
			return ;
		if (step == 0) {// If the step turned out to be zero - immediately set the desired level
			zunoSendReport(channel + 1);
			return (zuno_universalSetter1P(channel, ZUNO_TIMER_SWITCH_MIN_VALUE));
		}
		b_mode = ZUNO_TIMER_SWITCH_DEC;
	}
	zunoEnterCritical();
	if ((lp = zuno_CCTimerBasicFind(channel)) != 0x0) {
		lp->step = step / ZUNO_TIMER_SWITCH_MAX_VALUE;
		lp->ticksEnd = g_zuno_timer.ticks + step;
		lp->currentValue = current_level;
		lp->targetValue = (b_mode & ZUNO_TIMER_SWITCH_INC) != 0 ? ZUNO_TIMER_SWITCH_MAX_VALUE : ZUNO_TIMER_SWITCH_MIN_VALUE;
		lp->ticks = g_zuno_timer.ticks;
		lp->bMode = b_mode;
		lp->channel = channel + 1;
	}
	zunoExitCritical();
}

int zuno_CCSwitchMultilevelReport(byte channel, bool reply) {
	SwitchMultilevelReportFrame_t			*report;
	size_t									currentValue;
	size_t									targetValue;
	size_t									duration;
	ZunoTimerBasic_t						*lp;

	currentValue = zuno_universalGetter1P(channel);
	if(currentValue > ZUNO_TIMER_SWITCH_MAX_VALUE)
		currentValue = ZUNO_TIMER_SWITCH_MAX_VALUE;
	if(reply){
		report = (SwitchMultilevelReportFrame_t *)&CMD_REPLY_CC;
		CMD_REPLY_LEN = sizeof(report->v4);
	} else {
		report = (SwitchMultilevelReportFrame_t *)&CMD_REPORT_CC;
		CMD_REPORT_LEN = sizeof(report->v4);
	}
	zunoEnterCritical();
	if ((lp = zuno_CCTimerBasicFind(channel)) != 0x0 && lp->channel != 0x0) {
		targetValue = lp->targetValue;
		duration = zuno_CCTimerTable8(lp->ticksEnd - g_zuno_timer.ticks);
	}
	else {
		targetValue = currentValue;
		duration = 0x0;
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
	ZunoTimerBasic_t				*lp;
	size_t							currentValue;

	if ((value = cmd->v4.value) > ZUNO_TIMER_SWITCH_MAX_VALUE && value < 0xFF)
		return (ZUNO_COMMAND_BLOCKED);
	if (value == 0xFF) {
		if ((tempos = ZUNO_CFG_CHANNEL(channel).params[0]) != 0)
			value = tempos;
		else
			value = ZUNO_TIMER_SWITCH_MAX_VALUE;
	}
	if (value != 0x0)
		ZUNO_CFG_CHANNEL(channel).params[0] = value;
	currentValue = zuno_universalGetter1P(channel) ? 0xFF : 0x00;
	if(currentValue > ZUNO_TIMER_SWITCH_MAX_VALUE)
		currentValue = ZUNO_TIMER_SWITCH_MAX_VALUE;
	if (currentValue != value) {
		switch (len) {
			case sizeof(cmd->v4):
				if ((duration = zuno_CCTimerTicksTable7(cmd->v4.dimmingDuration)) == 0x0)
					break ;
				zunoEnterCritical();
				if ((lp = zuno_CCTimerBasicFind(channel)) == 0x0) {
					zunoExitCritical();
					break ;
				}
				if (value > currentValue) {
					lp->step = duration / (value - currentValue);
					lp->bMode = ZUNO_TIMER_SWITCH_INC;
				}
				else {
					lp->step = duration / (currentValue - value);
					lp->bMode = ZUNO_TIMER_SWITCH_DEC;
				}
				lp->currentValue = currentValue;
				lp->channel = channel + 0x1;
				lp->ticksEnd = g_zuno_timer.ticks + duration;
				lp->ticks = g_zuno_timer.ticks;
				lp->targetValue = value;
				zunoExitCritical();
				return (ZUNO_COMMAND_PROCESSED);
				break ;
			default:
				break ;
		}
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
	ZunoTimerBasic_t				*lp;

	zunoEnterCritical();
	if ((lp = zuno_CCTimerBasicFind(channel)) != 0x0)
		lp->channel = 0x0;
	zunoExitCritical();
	return (ZUNO_COMMAND_PROCESSED);
}

int zuno_CCSwitchMultilevelHandler(byte channel, ZUNOCommandPacket_t *cmd) {
	int									rs;

	switch(ZW_CMD) {
		case SWITCH_MULTILEVEL_GET:
			_zunoMarkChannelRequested(channel);
			rs = zuno_CCSwitchMultilevelReport(channel, true);
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

void zuno_CCSwitchMultilevelTimer(size_t ticks, ZunoTimerBasic_t *lp) {
	size_t									channel;
	size_t									value;
	size_t									tempos;

	channel = lp->channel;
	if (lp->step == 0) {
		if (ticks < lp->ticks)
			return ;
		value = lp->targetValue;
		lp->channel = 0x0;
	}
	else if ((tempos = lp->ticks + lp->step) > ticks)
		return ;
	else {
		lp->ticks = tempos;
		value = (lp->currentValue += (lp->bMode & ZUNO_TIMER_SWITCH_INC) != 0 ? 1 : -1);// Depending on the flag, increase or decrease
		if (value == ZUNO_TIMER_SWITCH_MAX_VALUE || value == ZUNO_TIMER_SWITCH_MIN_VALUE)
			lp->channel = 0x0;
	}
	zuno_universalSetter1P(channel - 1, value);
	zunoSendReport(channel);
}
