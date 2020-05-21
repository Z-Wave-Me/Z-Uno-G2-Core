#include "ZWCCSwitchMultilevel.h"
#include "ZWSupport.h"
#include "./includes/ZWSupportTimer.h"
#include "./includes/ZWCCSwitchMultilevelTimer.h"

static uint32_t			fn_duration(uint32_t duration)// Get the step for dimming in milliseconds
{
	if (duration == 0)
		return (0);
	if (duration == 0xFF)
		return (ZUNO_TIMER_SWITCH_DEFAULT_DURATION * 1000);// Set By Default
	if ((duration & (1 << 7)) != 0)
		duration = (duration ^ (1 << 7)) * 60;
	return (duration * 1000);
}

static volatile t_ZUNO_TIMER_SWITCH_CHANNEL	*fn_find(uint8_t channel)// Trying to find a free structure for writing
{
	volatile t_ZUNO_TIMER_SWITCH_CHANNEL				*lp_b;
	volatile t_ZUNO_TIMER_SWITCH_CHANNEL				*lp_e;

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
		if ((lp_b->b_mode & ZUNO_TIMER_SWITCH_ON) == 0)
			return (lp_b);
		lp_b++;
	}
	return (0);// So everything is busy
}

static void				fn_start_level(uint8_t channel, ZUNOCommandPacket_t *cmd)// Prepare the structure for dimming
{
	u_ZW_SWITCH_MULTILEVEL_START_LEVEL_CHANGE_FRAME		*pk;
	volatile t_ZUNO_TIMER_SWITCH_CHANNEL				*lp;
	uint32_t											step;
	uint8_t												current_level;
	uint8_t												b_mode;

	if(channel > ZUNO_CFG_CHANNEL_COUNT)// Check if the channel number is correct
		return ;
	switch (cmd->len)// We can check the unsupported version of the command
	{
		case sizeof(t_ZW_SWITCH_MULTILEVEL_START_LEVEL_CHANGE_V1_FRAME):
		case sizeof(t_ZW_SWITCH_MULTILEVEL_START_LEVEL_CHANGE_V2_FRAME):
		case sizeof(t_ZW_SWITCH_MULTILEVEL_START_LEVEL_CHANGE_V3_FRAME):
			break ;
		default:
			return ;
	}
	pk = (u_ZW_SWITCH_MULTILEVEL_START_LEVEL_CHANGE_FRAME *)cmd->cmd;
	if ((pk->v1.properties1 & (1 << 5)) == 0)
	{// If the level from which you want to start dimming has come, make it current
		if ((current_level = pk->v1.startLevel) > ZUNO_TIMER_SWITCH_MAX_VALUE)
			current_level = ZUNO_TIMER_SWITCH_MAX_VALUE;
		zuno_universalSetter1P(channel, current_level);
		zunoSendReport(channel + 1);
	}
	else
	{// Otherwise, get the current
		if ((current_level = zuno_universalGetter1P(channel)) > ZUNO_TIMER_SWITCH_MAX_VALUE)
			current_level = ZUNO_TIMER_SWITCH_MAX_VALUE;
	}
	if (cmd->len == sizeof(t_ZW_SWITCH_MULTILEVEL_START_LEVEL_CHANGE_V1_FRAME))
		step = ZUNO_TIMER_SWITCH_DEFAULT_DURATION * 1000;// Depending on the version, set the default step to increase or from the command we will
	else
		step = fn_duration(pk->v2.dimmingDuration);
	if ((pk->v1.properties1 & (1 << 6)) == 0)
	{// Dimming to up
		if (ZUNO_TIMER_SWITCH_MAX_VALUE - current_level == 0)// Check it may not need to dim
			return ;
		if (step == 0)// If the step turned out to be zero - immediately set the desired level
			return (zuno_universalSetter1P(channel, ZUNO_TIMER_SWITCH_MAX_VALUE));
		b_mode = ZUNO_TIMER_SWITCH_INC | ZUNO_TIMER_SWITCH_ON;
	}
	else
	{// Dimming to down
		if (current_level == ZUNO_TIMER_SWITCH_MIN_VALUE)// Check it may not need to dim
			return ;
		if (step == 0)// If the step turned out to be zero - immediately set the desired level
			return (zuno_universalSetter1P(channel, ZUNO_TIMER_SWITCH_MIN_VALUE));
		b_mode = ZUNO_TIMER_SWITCH_DEC | ZUNO_TIMER_SWITCH_ON;
	}
	noInterrupts();
	if ((lp = fn_find(channel)) != 0)// Trying to find a free structure
	{
		lp->step = step / (ZUNO_TIMER_SWITCH_MAX_VALUE * 10);
		lp->current_level = current_level;
		lp->ticks = g_zuno_timer.ticks;
		lp->b_mode |= b_mode;
		lp->channel = channel + 1;
	}
	interrupts();
	return ;
}

static void		fn_remove_switch_multilevel(volatile t_ZUNO_TIMER_SWITCH_CHANNEL *lp_b)
{
	lp_b->b_mode = 0;
	lp_b->channel = 0;
}

static void			fn_stop_level(uint8_t channel)// Stop Dimming
{
	volatile t_ZUNO_TIMER_SWITCH_CHANNEL				*lp_b;
	volatile t_ZUNO_TIMER_SWITCH_CHANNEL				*lp_e;

	if(channel > ZUNO_CFG_CHANNEL_COUNT)// Check if the channel number is correct
		return ;
	channel++;
	lp_b = &g_zuno_timer.s_switch[0];
	lp_e = &g_zuno_timer.s_switch[ZUNO_TIMER_SWITCH_MAX_SUPPORT_CHANNAL];
	noInterrupts();
	while (lp_b < lp_e)
	{
		if (lp_b->channel == channel)
		{
			fn_remove_switch_multilevel(lp_b);
			break ;
		}
		lp_b++;
	}
	interrupts();
	return ;
}

int		zuno_CCSwitchMultilevelReport(byte channel){
	CMD_REPLY_CC = COMMAND_CLASS_SWITCH_MULTILEVEL;
    CMD_REPLY_CMD = SWITCH_MULTILEVEL_REPORT;
	CMD_REPLY_DATA(0) = zuno_universalGetter1P(channel);
	CMD_REPLY_LEN = 3;
	return ZUNO_COMMAND_ANSWERED;
}
int		zuno_CCSwitchMultilevelHandler(byte channel, ZUNOCommandPacket_t *cmd)
{
	int rs = ZUNO_UNKNOWN_CMD;

	switch(ZW_CMD)
	{
		case SWITCH_MULTILEVEL_GET:
			rs = zuno_CCSwitchMultilevelReport(channel);
			break;
		case SWITCH_MULTILEVEL_SET:
			zuno_universalSetter1P(channel, ZW_CMD_BPARAM(0));
			rs = ZUNO_COMMAND_PROCESSED;
			break;
		case SWITCH_MULTILEVEL_START_LEVEL_CHANGE:
			fn_start_level(channel, cmd);
			rs = ZUNO_COMMAND_PROCESSED;
			break;
		case SWITCH_MULTILEVEL_STOP_LEVEL_CHANGE:
			fn_stop_level(channel);
			rs = ZUNO_COMMAND_PROCESSED;
			break;
	}
	return rs;
}

void			zuno_CCSwitchMultilevelTimer(uint32_t ticks)// We dim in the timer if there is a need
{
	volatile t_ZUNO_TIMER_SWITCH_CHANNEL				*lp_b;
	volatile t_ZUNO_TIMER_SWITCH_CHANNEL				*lp_e;

	lp_b = &g_zuno_timer.s_switch[0];
	lp_e = &g_zuno_timer.s_switch[ZUNO_TIMER_SWITCH_MAX_SUPPORT_CHANNAL];
	noInterrupts();
	while (lp_b < lp_e)
	{
		if ((lp_b->b_mode & ZUNO_TIMER_SWITCH_ON) != 0)
		{
			if (ticks >= lp_b->ticks + lp_b->step || lp_b->ticks >= lp_b->step + ticks)// Check if overflow has occurred lp_b->ticks >= lp_b->step + ticks
			{
				lp_b->ticks = ticks;
				lp_b->current_level += (lp_b->b_mode & ZUNO_TIMER_SWITCH_INC) != 0 ? 1 : -1;// Depending on the flag, increase or decrease
				zuno_universalSetter1P(lp_b->channel - 1, lp_b->current_level);
				zunoSendReport(lp_b->channel);
				if (lp_b->current_level == ZUNO_TIMER_SWITCH_MAX_VALUE || lp_b->current_level == ZUNO_TIMER_SWITCH_MIN_VALUE)
					fn_remove_switch_multilevel(lp_b);// When you have reached the goal of dimming - stop
			}
		}
		lp_b++;
	}
	interrupts();
}