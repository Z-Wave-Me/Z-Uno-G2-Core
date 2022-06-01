#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCTimer.h"
#include "ZWCCSwitchColor.h"
#include "ZWCCSwitchMultilevel.h"
#include "ZWCCSwitchBinary.h"

size_t zuno_CCTimerBasicFindStop(size_t channel) {
	ZunoTimerBasic_t				*lp;
	size_t							out;

	zunoEnterCritical();
	if ((lp = zuno_CCTimerBasicFind(channel)) != 0x0) {
		lp->channel = 0x0;
		out = true;
	}
	else
		out = false;
	zunoExitCritical();
	return (out);
}

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

	if ((tempos = ticks / (1000)) == 0x0 && ticks != 0x0)
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
void zuno_CCSwitchBinaryTimer(ZunoTimerBasic_t *lp, ZUNOCommandPacketReport_t *frame_report);
void zuno_CCSwitchMultilevelTimer(ZunoTimerBasic_t *lp, ZUNOCommandPacketReport_t *frame_report);
void zuno_CCSwitchColorTimer(ZunoTimerBasic_t *lp, ZUNOCommandPacketReport_t *frame_report);
void zuno_CCDoorLockTimer(ZunoTimerBasic_t *lp);
void zuno_CCSoundSwitchTimer(void);
void zuno_CCIndicatorTimer(void);
void zuno_CCCentralSceneTimer(void);

// Main timer for CC purposes
ZunoTimer_t g_zuno_timer;

#if defined(WITH_CC_SWITCH_BINARY) || defined(WITH_CC_SWITCH_MULTILEVEL) || defined(WITH_CC_SWITCH_COLOR) || defined(WITH_CC_DOORLOCK)
static void _exe(ZUNOCommandPacketReport_t *frame_report) {
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
					zuno_CCSwitchBinaryTimer(lp_b, frame_report);
					break ;
				#endif
				#ifdef WITH_CC_SWITCH_MULTILEVEL
				case ZUNO_SWITCH_MULTILEVEL_CHANNEL_NUMBER:
					zuno_CCSwitchMultilevelTimer(lp_b, frame_report);
					break ;
				#endif
				#ifdef WITH_CC_SWITCH_COLOR
				case ZUNO_SWITCH_COLOR_CHANNEL_NUMBER:
					zuno_CCSwitchColorTimer(lp_b, frame_report);
					break ;
				#endif
				#ifdef WITH_CC_DOORLOCK
				case ZUNO_DOORLOCK_CHANNEL_NUMBER:
					zuno_CCDoorLockTimer(lp_b);
					break ;
				#endif
				default:
					break ;
			}
		}
		lp_b++;
	}
}
#endif

void zuno_CCTimer(uint32_t ticks) {
	#if defined(WITH_CC_SWITCH_BINARY) || defined(WITH_CC_SWITCH_MULTILEVEL) || defined(WITH_CC_SWITCH_COLOR) || defined(WITH_CC_DOORLOCK)
	ZUNOCommandPacketReport_t frame_report;
	_exe(&frame_report);
	#endif
	#if defined(WITH_CC_SOUND_SWITCH)
	if((ticks & 0x7) == 0) // Once in ~80ms 
		zuno_CCSoundSwitchTimer();
	#endif
	if((ticks & 0x3) == 0) // Once in ~40ms 
		zuno_CCIndicatorTimer();
	#if defined(WITH_CC_CENTRAL_SCENE)
	if((ticks & 0x7) == 0) // Once in ~80ms 
		zuno_CCCentralSceneTimer();
	#endif
	if((ticks & ZUNO_REPORTTIME_DIVIDER) == 0) // Once in ~80ms - for 0x7
		zunoSendReportHandler(ticks);
}
