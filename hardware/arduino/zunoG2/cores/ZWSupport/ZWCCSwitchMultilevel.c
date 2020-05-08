#include "ZWCCSwitchMultilevel.h"
#include "ZWSupport.h"
#include "./includes/ZWSupportTimer.h"
#include "./includes/ZWCCSwitchMultilevelTimer.h"

static uint32_t			fn_duration(uint32_t duration)
{
	if (duration == 0)
		return (0);
	if (duration == 0xFF)
		return (ZUNO_TIMER_SWITCH_DEFAULT_DURATION * 1000);
	if ((duration & (1 << 7)) != 0)
		duration = (duration ^ (1 << 7)) * 60;
	return (duration * 1000);
}

static volatile t_ZUNO_TIMER_SWITCH_CHANNEL	*fn_find(uint8_t channel)
{
	volatile t_ZUNO_TIMER_SWITCH_CHANNEL				*lp_b;
	volatile t_ZUNO_TIMER_SWITCH_CHANNEL				*lp_e;

	lp_b = &g_zuno_timer.s_switch[0];
	lp_e = &g_zuno_timer.s_switch[ZUNO_TIMER_SWITCH_MAX_SUPPORT_CHANNAL];

	channel++;
	while (lp_b < lp_e)
	{
		if (lp_b->channel == channel)
			return (lp_b);
		lp_b++;
	}
	lp_b = &g_zuno_timer.s_switch[0];
	while (lp_b < lp_e)
	{
		if ((lp_b->b_mode & ZUNO_TIMER_SWITCH_ON) == 0)
			return (lp_b);
		lp_b++;
	}
	lp_b = &g_zuno_timer.s_switch[0];
	while (lp_b < lp_e)
	{
		if ((lp_b->b_mode & ZUNO_TIMER_SWITCH_ONLY_DEC) != 0)
			return (lp_b);
		lp_b++;
	}
	return (0);
}

static void				fn_set_level(uint8_t channel, ZUNOCommandPacket_t *cmd)
{
	u_ZW_SWITCH_MULTILEVEL_SET_FRAME					*pk;
	volatile t_ZUNO_TIMER_SWITCH_CHANNEL				*lp;
	uint8_t												duration_dec;

	if(channel > ZUNO_CFG_CHANNEL_COUNT)
		return ;//Проверяем верный номкер канала и есть ли на этом канале обработчик
	pk = (u_ZW_SWITCH_MULTILEVEL_SET_FRAME *)cmd->cmd;
	switch (cmd->len)
	{
		case sizeof(t_ZW_SWITCH_MULTILEVEL_SET_V1_FRAME):
			duration_dec = ZUNO_TIMER_SWITCH_DEFAULT_DURATION;
			break ;
		case sizeof(t_ZW_SWITCH_MULTILEVEL_SET_V2_FRAME):
			duration_dec = pk->v2.dimmingDuration;
			break ;
		default:
			return ;//Проверим может не поддерживаемый версия команды
	}
	noInterrupts();
	if ((lp = fn_find(channel)) != 0)
	{
		lp->duration_dec = duration_dec;
		lp->channel = channel + 1;
		lp->b_mode = ZUNO_TIMER_SWITCH_ONLY_DEC;
	}
	interrupts();
	return ;
}

static void				fn_start_level(uint8_t channel, ZUNOCommandPacket_t *cmd)
{
	u_ZW_SWITCH_MULTILEVEL_START_LEVEL_CHANGE_FRAME		*pk;
	volatile t_ZUNO_TIMER_SWITCH_CHANNEL				*lp;
	uint32_t											step;
	uint8_t												current_level;
	uint8_t												b_mode;

	if(channel > ZUNO_CFG_CHANNEL_COUNT)
		return ;//Проверяем верный номкер канала и есть ли на этом канале обработчик
	switch (cmd->len)
	{
		case sizeof(t_ZW_SWITCH_MULTILEVEL_START_LEVEL_CHANGE_V1_FRAME):
		case sizeof(t_ZW_SWITCH_MULTILEVEL_START_LEVEL_CHANGE_V2_FRAME):
		case sizeof(t_ZW_SWITCH_MULTILEVEL_START_LEVEL_CHANGE_V3_FRAME):
			break ;
		default:
			return ;//Проверим может не поддерживаемый версия команды
	}
	pk = (u_ZW_SWITCH_MULTILEVEL_START_LEVEL_CHANGE_FRAME *)cmd->cmd;
	if ((pk->v1.properties1 & (1 << 5)) == 0)
	{
		if ((current_level = pk->v1.startLevel) > ZUNO_TIMER_SWITCH_MAX_VALUE)
			current_level = ZUNO_TIMER_SWITCH_MAX_VALUE;
		zuno_universalSetter1P(channel, current_level);
	}
	else
	{
		if ((current_level = zuno_universalGetter1P(channel)) > ZUNO_TIMER_SWITCH_MAX_VALUE)
			current_level = ZUNO_TIMER_SWITCH_MAX_VALUE;
	}
	if ((pk->v1.properties1 & (1 << 6)) == 0)
	{
		if (ZUNO_TIMER_SWITCH_MAX_VALUE - current_level == 0)
			return ;
		if (cmd->len == sizeof(t_ZW_SWITCH_MULTILEVEL_START_LEVEL_CHANGE_V1_FRAME))
			step = ZUNO_TIMER_SWITCH_DEFAULT_DURATION * 1000;
		else
			step = fn_duration(pk->v2.dimmingDuration);
		if (step == 0)
			return (zuno_universalSetter1P(channel, ZUNO_TIMER_SWITCH_MAX_VALUE));
		b_mode = ZUNO_TIMER_SWITCH_INC | ZUNO_TIMER_SWITCH_ON;
	}
	else
	{
		if (current_level == ZUNO_TIMER_SWITCH_MIN_VALUE)
			return ;
		noInterrupts();
		if ((lp = fn_find(channel)) != 0 && lp->b_mode != 0)
			step = fn_duration(lp->duration_dec);
		else
			step = ZUNO_TIMER_SWITCH_DEFAULT_DURATION * 1000;
		interrupts();
		if (step == 0)
			return (zuno_universalSetter1P(channel, ZUNO_TIMER_SWITCH_MIN_VALUE));
		b_mode = ZUNO_TIMER_SWITCH_DEC | ZUNO_TIMER_SWITCH_ON;
	}
	noInterrupts();
	if ((lp = fn_find(channel)) != 0)
	{
		lp->step = step / (ZUNO_TIMER_SWITCH_MAX_VALUE * 10);
		lp->current_level = current_level;
		lp->ticks = g_zuno_timer.ticks;
		lp->b_mode = b_mode;
		lp->channel = channel + 1;
	}
	interrupts();
	return ;
}

static void		fn_remove_switch_multilevel(uint8_t channel)
{
	uint8_t				i;

	channel++;
	i = 0;
	while (i < ZUNO_TIMER_SWITCH_MAX_SUPPORT_CHANNAL)
	{
		if (g_zuno_timer.s_switch[i].channel == channel)
		{
			g_zuno_timer.s_switch[i].b_mode = 0;
			g_zuno_timer.s_switch[i].channel = 0;
			return ;
		}
		i++;
	}
}

static void			fn_stop_level(uint8_t channel)
{
	if(channel > ZUNO_CFG_CHANNEL_COUNT)
		return ;
	noInterrupts();
	fn_remove_switch_multilevel(channel);
	interrupts();
	return ;
}

int					zuno_CCSwitchMultilevelHandler(byte channel, ZUNOCommandPacket_t *cmd)
{
	int rs = ZUNO_UNKNOWN_CMD;

	switch(ZW_CMD)
	{
		case SWITCH_MULTILEVEL_GET:
			CMD_REPLY_DATA(0) = zuno_universalGetter1P(channel);
			CMD_REPLY_LEN = 3;
			rs = ZUNO_COMMAND_ANSWERED;
			break;
		case SWITCH_MULTILEVEL_SET:
			zuno_universalSetter1P(channel, ZW_CMD_BPARAM(0));
			fn_set_level(channel, cmd);
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

void			zuno_CCSwitchMultilevelTimer(uint32_t ticks)
{
	volatile t_ZUNO_TIMER_SWITCH_CHANNEL				*lp_b;
	volatile t_ZUNO_TIMER_SWITCH_CHANNEL				*lp_e;

	lp_b = &g_zuno_timer.s_switch[0];
	lp_e = &g_zuno_timer.s_switch[ZUNO_TIMER_SWITCH_MAX_SUPPORT_CHANNAL];
	while (lp_b < lp_e)
	{
		if ((lp_b->b_mode & ZUNO_TIMER_SWITCH_ON) != 0)
		{
			if (ticks >= lp_b->ticks + lp_b->step || lp_b->ticks >= lp_b->step + ticks)
			{
				lp_b->ticks = ticks;
				lp_b->current_level += (lp_b->b_mode & ZUNO_TIMER_SWITCH_INC) != 0 ? 1 : -1;
				zuno_universalSetter1P(lp_b->channel - 1, lp_b->current_level);
				if (lp_b->current_level == ZUNO_TIMER_SWITCH_MAX_VALUE || lp_b->current_level == ZUNO_TIMER_SWITCH_MIN_VALUE)
					fn_remove_switch_multilevel(lp_b->channel - 1);
			}
		}
		lp_b++;
	}
}