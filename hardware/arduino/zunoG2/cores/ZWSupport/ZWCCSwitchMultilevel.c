#include "ZWCCSwitchMultilevel.h"
#include "ZWSupport.h"
#include "ZWCCTimer.h"

static uint32_t _duration(uint32_t duration) {// Get the step for dimming in milliseconds
	if (duration == 0)
		return (0);
	if (duration == 0xFF)
		return (ZUNO_TIMER_SWITCH_DEFAULT_DURATION * 1000);// Set By Default
	if ((duration & (1 << 7)) != 0)
		duration = (duration ^ (1 << 7)) * 60;
	return (duration * 1000);
}

static volatile ZunoTimerSwitchChannel_t	*_find(uint8_t channel) {// Trying to find a free structure for writing
	volatile ZunoTimerSwitchChannel_t				*lp_b;
	volatile ZunoTimerSwitchChannel_t				*lp_e;

	lp_b = &g_zuno_timer.s_switch[0];
	lp_e = &g_zuno_timer.s_switch[ZUNO_TIMER_SWITCH_MAX_SUPPORT_CHANNAL];

	channel++;
	while (lp_b < lp_e)// First look for matches
	{
		if (lp_b->channel == channel)
			return (lp_b);
		lp_b++;
	}
	lp_b = &g_zuno_timer.s_switch[0];
	while (lp_b < lp_e)// Then look for an unoccupied structure
	{
		if ((lp_b->b_mode & ZUNO_TIMER_SWITCH_DIMMING) == 0)
			return (lp_b);
		lp_b++;
	}
	return (0);// So everything is busy
}

static void _start_level(uint8_t channel, ZUNOCommandPacket_t *cmd) {// Prepare the structure for dimming
	ZwSwitchMultilevelStartLevelChangeFrame_t		*pk;
	volatile ZunoTimerSwitchChannel_t				*lp;
	uint32_t											step;
	uint8_t												current_level;
	uint8_t												b_mode;

	switch (cmd->len) {// We can check the unsupported version of the command
		case sizeof(ZwSwitchMultilevelStartLevelChangeV1Frame_t):
		case sizeof(ZwSwitchMultilevelStartLevelChangeV2Frame_t):
		case sizeof(ZwSwitchMultilevelStartLevelChangeV3Frame_t):
			break ;
		default:
			return ;
	}
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
		step = ZUNO_TIMER_SWITCH_DEFAULT_DURATION * 1000;// Depending on the version, set the default step to increase or from the command we will
	else
		step =_duration(pk->v2.dimmingDuration);
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
	noInterrupts();
	if ((lp =_find(channel)) != 0) {// Trying to find a free structure
		lp->step = step / (ZUNO_TIMER_SWITCH_MAX_VALUE * 10);
		lp->current_level = current_level;
		lp->ticks = g_zuno_timer.ticks;
		lp->b_mode |= b_mode;
		lp->channel = channel + 1;
	}
	interrupts();
}

static void _remove_switch_multilevel(volatile ZunoTimerSwitchChannel_t *lp_b) {
	lp_b->b_mode = 0;
	lp_b->channel = 0;
}

static void		_stop_level(uint8_t channel) {// Stop Dimming
	volatile ZunoTimerSwitchChannel_t				*lp_b;
	volatile ZunoTimerSwitchChannel_t				*lp_e;

	channel++;
	lp_b = &g_zuno_timer.s_switch[0];
	lp_e = &g_zuno_timer.s_switch[ZUNO_TIMER_SWITCH_MAX_SUPPORT_CHANNAL];
	noInterrupts();
	while (lp_b < lp_e) {
		if (lp_b->channel == channel) {
			_remove_switch_multilevel(lp_b);
			break ;
		}
		lp_b++;
	}
	interrupts();
}

int zuno_CCSwitchMultilevelReport(byte channel) {
	CMD_REPLY_CC = COMMAND_CLASS_SWITCH_MULTILEVEL;
	CMD_REPLY_CMD = SWITCH_MULTILEVEL_REPORT;
	byte val_mapper = zuno_universalGetter1P(channel);
	if(val_mapper > 99)
		val_mapper = 99;
	CMD_REPLY_DATA(0) = val_mapper;
	CMD_REPLY_LEN = 3;
	return ZUNO_COMMAND_ANSWERED;
}
int zuno_CCSwitchMultilevelHandler(byte channel, ZUNOCommandPacket_t *cmd) {
	int rs = ZUNO_UNKNOWN_CMD;
	switch(ZW_CMD) {
		case SWITCH_MULTILEVEL_GET:
			rs = zuno_CCSwitchMultilevelReport(channel);
			break;
		case SWITCH_MULTILEVEL_SET:{
				byte val_mapper = ZW_CMD_BPARAM(0);
				if(val_mapper == 0xFF)
					val_mapper = 99; // We use always 99 as the last "on" value
				if(val_mapper > 99)
					return rs;
				zuno_universalSetter1P(channel, val_mapper);
				zunoSendReport(channel + 1);
				rs = ZUNO_COMMAND_PROCESSED;
			}
			break;
		case SWITCH_MULTILEVEL_START_LEVEL_CHANGE:
			_start_level(channel, cmd);
			rs = ZUNO_COMMAND_PROCESSED;
			break;
		case SWITCH_MULTILEVEL_STOP_LEVEL_CHANGE:
			_stop_level(channel);
			rs = ZUNO_COMMAND_PROCESSED;
			break;
	}
	return rs;
}

void zuno_CCSwitchMultilevelTimer(uint32_t ticks) {// We dim in the timer if there is a need
	volatile ZunoTimerSwitchChannel_t				*lp_b;
	volatile ZunoTimerSwitchChannel_t				*lp_e;
	uint8_t												current_level;

	lp_b = &g_zuno_timer.s_switch[0];
	lp_e = &g_zuno_timer.s_switch[ZUNO_TIMER_SWITCH_MAX_SUPPORT_CHANNAL];
	noInterrupts();
	while (lp_b < lp_e) {
		if ((lp_b->b_mode & ZUNO_TIMER_SWITCH_DIMMING) != 0) {
			if (ticks >= lp_b->ticks + lp_b->step || lp_b->ticks >= lp_b->step + ticks) {// Check if overflow has occurred lp_b->ticks >= lp_b->step + ticks
				lp_b->ticks = ticks;
				current_level = (lp_b->current_level += (lp_b->b_mode & ZUNO_TIMER_SWITCH_INC) != 0 ? 1 : -1);// Depending on the flag, increase or decrease
				zuno_universalSetter1P(lp_b->channel - 1, current_level);
				zunoSendReport(lp_b->channel);
				if (current_level == ZUNO_TIMER_SWITCH_MAX_VALUE || current_level == ZUNO_TIMER_SWITCH_MIN_VALUE)
					_remove_switch_multilevel(lp_b);// When you have reached the goal of dimming - stop
			}
		}
		lp_b++;
	}
	interrupts();
}