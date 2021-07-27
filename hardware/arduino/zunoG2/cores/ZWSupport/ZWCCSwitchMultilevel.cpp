#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCTimer.h"
#include "ZWCCSwitchMultilevel.h"
#include "ZWCCBasic.h"

void zuno_SwitchMultilevelUniversalSetter1P(byte zuno_ch, int32_t value) {
	switch (ZUNO_CFG_CHANNEL(zuno_ch).type) {
		#ifdef WITH_CC_SWITCH_COLOR
		case ZUNO_SWITCH_COLOR_CHANNEL_NUMBER:
			ZWCC_BASIC_SAVE_COLOR(zuno_ch) = value;
			break;
		#endif
		default:
			zuno_universalSetter1P(zuno_ch, value);
			break ;
	}
}

int32_t zuno_SwitchMultilevelUniversalGetter1P(byte zuno_ch) {
	int32_t								value;

	switch (ZUNO_CFG_CHANNEL(zuno_ch).type) {
		#ifdef WITH_CC_SWITCH_COLOR
		case ZUNO_SWITCH_COLOR_CHANNEL_NUMBER:
			value = ZWCC_BASIC_SAVE_COLOR(zuno_ch);
			break;
		#endif
		default:
			value = zuno_universalGetter1P(zuno_ch);
			break ;
	}
	return (value);
}

static void _start_level(size_t channel, ZUNOCommandPacket_t *cmd) {// Prepare the structure for dimming
	ZwSwitchMultilevelStartLevelChangeFrame_t			*pk;
	ZunoTimerBasic_t									*lp;
	uint32_t											step;
	size_t												current_level;
	size_t												targetValue;
	size_t												b_mode;

	pk = (ZwSwitchMultilevelStartLevelChangeFrame_t *)cmd->cmd;
	if ((pk->v1.properties1 & (1 << 5)) == 0) {// If the level from which you want to start dimming has come, make it current
		if ((current_level = pk->v1.startLevel) > ZUNO_TIMER_SWITCH_MAX_VALUE)
			current_level = ZUNO_TIMER_SWITCH_MAX_VALUE;
		if (current_level != 0x0)
			ZWCC_BASIC_SAVE_LAST(channel) = current_level;
		ZWCC_BASIC_SETTER_1P(channel, current_level);
		zunoSendReport(channel + 1);
	} else {// Otherwise, get the current
		if ((current_level = ZWCC_BASIC_GETTER_1P(channel)) > ZUNO_TIMER_SWITCH_MAX_VALUE)
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
			return (ZWCC_BASIC_SETTER_1P(channel, ZUNO_TIMER_SWITCH_MAX_VALUE));
		}
		b_mode = ZUNO_TIMER_SWITCH_INC;
		targetValue = ZUNO_TIMER_SWITCH_MAX_VALUE;
	} else {// Dimming to down
		if (current_level == ZUNO_TIMER_SWITCH_MIN_VALUE)// Check it may not need to dim
			return ;
		if (step == 0) {// If the step turned out to be zero - immediately set the desired level
			zunoSendReport(channel + 1);
			return (ZWCC_BASIC_SETTER_1P(channel, ZUNO_TIMER_SWITCH_MIN_VALUE));
		}
		targetValue = ZUNO_TIMER_SWITCH_MIN_VALUE;
		b_mode = ZUNO_TIMER_SWITCH_DEC;
	}
	if (targetValue == current_level)
		return ;
	zunoEnterCritical();
	if ((lp = zuno_CCTimerBasicFind(channel)) != 0x0) {
		lp->step = ZUNO_TIMER_ALING_STEP(step / ZUNO_TIMER_SWITCH_MAX_VALUE);
		lp->ticksEnd = g_zuno_timer.ticks + (step / ZUNO_SYSTIMER_PERIOD_MC);
		lp->currentValue = current_level;
		lp->targetValue = targetValue;
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

	currentValue = ZWCC_BASIC_GETTER_1P(channel);
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
	if ((lp = zuno_CCTimerBasicFind(channel)) != 0x0 && lp->channel != 0x0 && (lp->bMode & ZUNO_TIMER_SWITCH_NO_BASIC) == 0x0) {
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
	size_t							step;
	ZunoTimerBasic_t				*lp;
	size_t							currentValue;

	if ((value = cmd->v4.value) > ZUNO_TIMER_SWITCH_MAX_VALUE && value < 0xFF)
		return (ZUNO_COMMAND_BLOCKED);
	if (value == 0xFF) {
		if ((tempos = ZWCC_BASIC_SAVE_LAST(channel)) != 0)
			value = tempos;
		else
			value = ZUNO_TIMER_SWITCH_MAX_VALUE;
	}
	if (value != 0x0)
		ZWCC_BASIC_SAVE_LAST(channel) = value;
	currentValue = ZWCC_BASIC_GETTER_1P(channel) ? 0xFF : 0x00;
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
					step = duration / (value - currentValue);
					lp->bMode = ZUNO_TIMER_SWITCH_INC;
				}
				else {
					step = duration / (currentValue - value);
					lp->bMode = ZUNO_TIMER_SWITCH_DEC;
				}
				lp->step = ZUNO_TIMER_ALING_STEP(step);
				lp->currentValue = currentValue;
				lp->channel = channel + 0x1;
				lp->ticksEnd = g_zuno_timer.ticks + (duration / ZUNO_SYSTIMER_PERIOD_MC);
				lp->ticks = g_zuno_timer.ticks;
				lp->targetValue = value;
				zunoExitCritical();
				return (ZUNO_COMMAND_PROCESSED);
				break ;
			default:
				break ;
		}
	}
	ZWCC_BASIC_SETTER_1P(channel, value);
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
	size_t									step;
	size_t									tempos;

	channel = lp->channel;
	if ((step = lp->step) == 0x0) {
		if (ticks < lp->ticks)
			return ;
		value = lp->targetValue;
		lp->channel = 0x0;
	}
	else if ((tempos = lp->ticks + step) > ticks)
		return ;
	else {
		ticks = ticks - tempos;
		lp->ticks = tempos + (ticks % step);
		ticks = ticks / step + 0x1;
		value = lp->currentValue;
		if ((lp->bMode & ZUNO_TIMER_SWITCH_INC) != 0x0)
			value += ticks;
		else
			value -= ticks;
		lp->currentValue = value;
		if (value == ZUNO_TIMER_SWITCH_MAX_VALUE || value == ZUNO_TIMER_SWITCH_MIN_VALUE)
			lp->channel = 0x0;
	}
	ZWCC_BASIC_SETTER_1P(channel - 1, value);
	zunoSendReport(channel);
}
