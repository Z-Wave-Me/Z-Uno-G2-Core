#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCTimer.h"
#include "ZWCCSwitchColor.h"
#include "ZWCCSwitchMultilevel.h"
#include "ZWCCSwitchBinary.h"

ZunoTimerBasic_t *zuno_CCTimerBasicFind(size_t channel) {
	ZunoTimerBasic_t				*lp_b;
	ZunoTimerBasic_t				*lp_e;

	lp_b = &g_zuno_timer.s_basic[0];
	lp_e = &g_zuno_timer.s_basic[(sizeof(g_zuno_timer.s_basic) / sizeof(ZunoTimerBasic_t))];
	channel++;
	while (lp_b < lp_e) {
		if (lp_b->channel == channel)
			return (lp_b);
		lp_b++;
	}
	lp_b = &g_zuno_timer.s_basic[0];
	while (lp_b < lp_e) {
		if (lp_b->channel == 0x0)
			return (lp_b);
		lp_b++;
	}
	return (0x0);
}

uint8_t zuno_CCTimerTable8(size_t ticks) {
	size_t				tempos;

	if ((tempos = ticks / (1000 / ZUNO_SYSTIMER_PERIOD_MC)) == 0x0 && ticks != 0x0)
		return (0x1);
	ticks = tempos;
	if (ticks <= 0x7F)
		return (ticks);
	ticks = ticks / 60;
	ticks = ticks | (1 << 7);
	return (ticks);
}

size_t zuno_CCTimerTicksTable7(size_t duration) {// Get the step for dimming in ms
	if (duration == 0)
		return (0);
	if (duration == 0xFF)
		return (ZUNO_TIMER_SWITCH_DEFAULT_DURATION * (1000));// Set By Default
	if ((duration & (1 << 7)) != 0)
		duration = ((duration + 0x1) ^ (1 << 7)) * 60;
	return (duration * (1000));
}

void zunoSendReportHandler(uint32_t ticks);
void zuno_CCSwitchBinaryTimer(size_t ticks, ZunoTimerBasic_t *lp);
void zuno_CCSwitchMultilevelTimer(size_t ticks, ZunoTimerBasic_t *lp);
void zuno_CCSwitchColorTimer(size_t ticks, ZunoTimerBasic_t *lp);
void zuno_CCDoorLockTimer(size_t ticks, ZunoTimerBasic_t *lp);

// Main timer for CC purposes
ZunoTimer_t g_zuno_timer;

void _exe(uint32_t ticks) {
	ZunoTimerBasic_t				*lp_b;
	ZunoTimerBasic_t				*lp_e;
	size_t							channel;

	lp_b = &g_zuno_timer.s_basic[0];
	lp_e = &g_zuno_timer.s_basic[(sizeof(g_zuno_timer.s_basic) / sizeof(ZunoTimerBasic_t))];
	while (lp_b < lp_e) {
		if ((channel = lp_b->channel) != 0x0) {
			switch (ZUNO_CFG_CHANNEL(channel - 1).type) {
				#ifdef WITH_CC_SWITCH_BINARY
				case ZUNO_SWITCH_BINARY_CHANNEL_NUMBER:
					zuno_CCSwitchBinaryTimer(ticks, lp_b);
					break ;
				#endif
				#ifdef WITH_CC_SWITCH_MULTILEVEL
				case ZUNO_SWITCH_MULTILEVEL_CHANNEL_NUMBER:
					zuno_CCSwitchMultilevelTimer(ticks, lp_b);
					break ;
				#endif
				#ifdef WITH_CC_SWITCH_COLOR
				case ZUNO_SWITCH_COLOR_CHANNEL_NUMBER:
					zuno_CCSwitchColorTimer(ticks, lp_b);
					break ;
				#endif
				#ifdef WITH_CC_DOORLOCK
				case ZUNO_DOORLOCK_CHANNEL_NUMBER:
					zuno_CCDoorLockTimer(ticks, lp_b);
					break ;
				#endif
				default:
					break ;
			}
		}
		lp_b++;
	}
	(void)ticks;
}

void zuno_CCTimer(uint32_t ticks) {
	g_zuno_timer.ticks = ticks;
	#if defined(WITH_CC_SWITCH_BINARY) || defined(WITH_CC_SWITCH_MULTILEVEL) || defined(WITH_CC_SWITCH_COLOR)
	_exe(ticks);
	#endif
	if((ticks & 0x1F) == 0) // Once in ~320ms 
		zunoSendReportHandler(ticks);
}
