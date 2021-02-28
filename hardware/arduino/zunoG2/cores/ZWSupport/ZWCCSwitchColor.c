#include "ZWCCSwitchColor.h"
#include "ZWCCTimer.h"
#include "./includes/ZWCCSwitchColor_private.h"

static int _supported_report(uint8_t channel) {//Processed to get the value of the color components
	ZwSwitchColorSupportedReporFrame_t		*lp;

	lp = (ZwSwitchColorSupportedReporFrame_t *)&CMD_REPLY_CC;
	lp->cmdClass = COMMAND_CLASS_SWITCH_COLOR;
	lp->cmd = SWITCH_COLOR_SUPPORTED_REPORT;
	lp->colorComponentMask1 = ZUNO_CFG_CHANNEL(channel).sub_type;//It contains a bitmask of colors
	lp->colorComponentMask2 = 0;
	CMD_REPLY_LEN = sizeof(ZwSwitchColorSupportedReporFrame_t);
	return (ZUNO_COMMAND_ANSWERED);
}

static void	_set_color(uint8_t channel, ZUNOCommandPacket_t *cmd) {
	uint8_t						*lp;
	uint8_t						i;

	lp = (uint8_t *)cmd->cmd;
	i = ((ZwSwitchColorSetFrame_t *)lp)->properties1 & 0x1F;//Color Component Count (5 bits)
	lp = (uint8_t *)&((ZwSwitchColorSetFrame_t *)lp)->variantgroup[0];
	while (i-- != 0) {
		zuno_universalSetter2P(channel, ((VgSwitchColorSetVg_t *)lp)->colorComponentId, ((VgSwitchColorSetVg_t *)lp)->value);
		lp = lp + sizeof(VgSwitchColorSetVg_t);
	}
}

static volatile ZunoTimerColorChannel_t	*_find(uint8_t channel, uint8_t colorComponentId) {// Trying to find a free structure for writing
	volatile ZunoTimerColorChannel_t				*lp_b;
	volatile ZunoTimerColorChannel_t				*lp_e;

	lp_b = &g_zuno_timer.s_color[0];
	lp_e = &g_zuno_timer.s_color[ZUNO_TIMER_COLOR_MAX_SUPPORT_CHANNAL];

	channel++;
	while (lp_b < lp_e) {// First look for matches
		if (lp_b->channel == channel && lp_b->colorComponentId == colorComponentId)
			return (lp_b);
		lp_b++;
	}
	lp_b = &g_zuno_timer.s_color[0];
	while (lp_b < lp_e) {// Then look for an unoccupied structure
		if ((lp_b->b_mode & ZUNO_TIMER_COLOR_ON) == 0)
			return (lp_b);
		lp_b++;
	}
	return (0);// So everything is busy
}

static void _start_level(uint8_t channel, ZUNOCommandPacket_t *cmd) {// Prepare the structure for dimming
	ZwSwitchColorStartLevelChange_FRAME_u			*pk;
	volatile ZunoTimerColorChannel_t					*lp;
	uint8_t												current_level;
	uint8_t												b_mode;

	pk = (ZwSwitchColorStartLevelChange_FRAME_u *)cmd->cmd;
	if ((pk->v2.properties1 & (1 << 5)) == 0) {// If the level from which you want to start dimming has come, make it current
		current_level = pk->v2.startLevel;
		zuno_universalSetter2P(channel, pk->v2.colorComponentId, current_level);
		zunoSendReport(channel + 1);
	}
	else// Otherwise, get the current
		current_level = zuno_universalGetter2P(channel, pk->v2.colorComponentId);
	if ((pk->v2.properties1 & (1 << 6)) == 0) {// Dimming to up
		if (ZUNO_TIMER_COLOR_MAX_VALUE - current_level == 0)// Check it may not need to dim
			return ;
		b_mode = ZUNO_TIMER_COLOR_INC | ZUNO_TIMER_COLOR_ON;
	} else {// Dimming to down
		if (current_level == ZUNO_TIMER_COLOR_MIN_VALUE)// Check it may not need to dim
			return ;
		b_mode = ZUNO_TIMER_COLOR_DEC | ZUNO_TIMER_COLOR_ON;
	}
	noInterrupts();
	if ((lp =_find(channel, pk->v2.colorComponentId)) != 0) {// Trying to find a free structure
		lp->step = ZUNO_TIMER_COLOR_DEFAULT_DURATION * 1000 / (ZUNO_TIMER_COLOR_MAX_VALUE * 10);
		lp->current_level = current_level;
		lp->ticks = g_zuno_timer.ticks;
		lp->b_mode |= b_mode;
		lp->channel = channel + 1;
		lp->colorComponentId = pk->v2.colorComponentId;
	}
	interrupts();
}

static void _remove_switch_multilevel(volatile ZunoTimerColorChannel_t *lp_b) {
	lp_b->b_mode = 0;
	lp_b->channel = 0;
}

static void _stop_level(uint8_t channel, uint8_t colorComponentId) {// Stop Dimming
	volatile ZunoTimerColorChannel_t				*lp_b;
	volatile ZunoTimerColorChannel_t				*lp_e;

	channel++;
	lp_b = &g_zuno_timer.s_color[0];
	lp_e = &g_zuno_timer.s_color[ZUNO_TIMER_COLOR_MAX_SUPPORT_CHANNAL];
	noInterrupts();
	while (lp_b < lp_e) {
		if (lp_b->channel == channel && lp_b->colorComponentId == colorComponentId) {
			_remove_switch_multilevel(lp_b);
			break ;
		}
		lp_b++;
	}
	interrupts();
}


int zuno_CCSwitchColorHandler(uint8_t channel, ZUNOCommandPacket_t *cmd) {
	int				rs;
	rs = ZUNO_UNKNOWN_CMD;
	switch(ZW_CMD)
	{
		case SWITCH_COLOR_SUPPORTED_GET:
			rs =_supported_report(channel);
			break ;
		case SWITCH_COLOR_GET:
			rs = zuno_CCSwitchColorReport(channel, cmd);
			break ;
		case SWITCH_COLOR_SET:
			_set_color(channel, cmd);
			zunoSendReport(channel + 1);
			rs = ZUNO_COMMAND_PROCESSED;
			break ;
		case SWITCH_COLOR_START_LEVEL_CHANGE:
			_start_level(channel, cmd);
			rs = ZUNO_COMMAND_PROCESSED;
			break ;
		case SWITCH_COLOR_STOP_LEVEL_CHANGE:
			_stop_level(channel, ((ZwSwitchColorStopLevelChange_t *)cmd->cmd)->colorComponentId);
			rs = ZUNO_COMMAND_PROCESSED;
			break ;
	}
	return (rs);
}


int zuno_CCSwitchColorReport(uint8_t channel, ZUNOCommandPacket_t *cmd) {
	ZwSwitchColorReportFrame_t			*lp;
	uint8_t								colorComponentId;
	uint8_t								mask;
	
	if (cmd != NULL) {
		mask = 1 << (((ZwSwitchColorGetFrame_t *)cmd->cmd)->colorComponentId);
	} else {
		mask = ZUNO_CFG_CHANNEL(channel).sub_type;//It contains a bitmask of colors
	}
	lp = (ZwSwitchColorReportFrame_t *)&CMD_REPLY_CC;
	lp->v2.cmdClass = COMMAND_CLASS_SWITCH_COLOR;
	lp->v2.cmd = SWITCH_COLOR_REPORT;
	CMD_REPLY_LEN = sizeof(lp->v2);
	colorComponentId = 0;
	while (mask != 0) {//We will pass through all the colors and send a report for each
		if ((mask & 0x01) != 0) {
			lp->v2.colorComponentId = colorComponentId;

			lp->v2.value = zuno_universalGetter2P(channel, colorComponentId);
			zunoSendZWPackage(&g_outgoing_packet);
		}
		colorComponentId++;
		mask >>=  1;
	}
	return (ZUNO_COMMAND_PROCESSED);
}

void zuno_CCSwitchColorTimer(uint32_t ticks) { // We dim in the timer if there is a need
	volatile ZunoTimerColorChannel_t				*lp_b;
	volatile ZunoTimerColorChannel_t				*lp_e;
	uint8_t											current_level;

	lp_b = &g_zuno_timer.s_color[0];
	lp_e = &g_zuno_timer.s_color[ZUNO_TIMER_COLOR_MAX_SUPPORT_CHANNAL];
	noInterrupts();
	while (lp_b < lp_e) {
		if ((lp_b->b_mode & ZUNO_TIMER_COLOR_ON) != 0) {
			if (ticks >= lp_b->ticks + lp_b->step || lp_b->ticks >= lp_b->step + ticks) {// Check if overflow has occurred lp_b->ticks >= lp_b->step + ticks
				lp_b->ticks = ticks;
				current_level = (lp_b->current_level += (lp_b->b_mode & ZUNO_TIMER_COLOR_INC) != 0 ? 1 : -1);// Depending on the flag, increase or decrease
				zuno_universalSetter2P(lp_b->channel - 1, lp_b->colorComponentId, current_level);
				zunoSendReport(lp_b->channel);
				if (current_level == ZUNO_TIMER_COLOR_MAX_VALUE || current_level == ZUNO_TIMER_COLOR_MIN_VALUE)
					_remove_switch_multilevel(lp_b);// When you have reached the goal of dimming - stop
			}
		}
		lp_b++;
	}
	interrupts();
}