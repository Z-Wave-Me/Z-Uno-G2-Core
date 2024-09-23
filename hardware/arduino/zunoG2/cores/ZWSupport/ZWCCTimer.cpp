#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCTimer.h"
#include "ZWCCSwitchColor.h"
#include "ZWCCSwitchMultilevel.h"
#include "ZWCCSwitchBinary.h"
#include "ZWCCResetLocally.h"
#include "CommandQueue.h"
#include "Debug.h"

#if defined(WITH_CC_SWITCH_BINARY) || defined(WITH_CC_SWITCH_MULTILEVEL) || defined(WITH_CC_WINDOW_COVERING) || defined(WITH_CC_SOUND_SWITCH)
uint64_t rtcc_micros(void);

static zunoTimerTreadDiming_t *_diming = NULL;

static zunoTimerTreadDiming_t *_zunoTimerTreadFind(zunoTimerTreadDimingType_t type, uint8_t channel, zunoTimerTreadDiming_t **prev, const void *data, uint8_t length) {
	zunoTimerTreadDiming_t						*root;
	zunoTimerTreadDiming_t						*list_prev;

	root = _diming;
	list_prev = NULL;
	while (root != NULL) {
		if (root->type == type && root->channel == channel) {
			if (length == 0x0 || data == NULL)
				break ;
			else if (memcmp(data, &root->data, length) == 0x0)
				break ;
		}
		list_prev = root;
		root = root->next;
	}
	prev[0x0] = list_prev;
	return (root);
}

zunoTimerTreadDiming_t *zunoTimerTreadDimingCreate(void) {
	zunoTimerTreadDiming_t			*list;

	if ((list = (zunoTimerTreadDiming_t *)malloc(sizeof(list[0x0]))) == NULL)
		return (NULL);
	#ifdef LOGGING_DBG
	LOGGING_UART.print("TIMER TREAD DIMING CREATE: ");
	LOGGING_UART.println((uint32_t)list);
	#endif
	return (list);
}

void zunoTimerTreadDimingAdd(zunoTimerTreadDiming_t *list, const ZUNOCommandHandlerOption_t *options) {
	zunoEnterCritical();
	list->options = options[0x0];
	list->next = _diming;
	_diming = list;
	g_sleep_data.latch++;
	zunoExitCritical();
}

static void _free_list(zunoTimerTreadDiming_t *list) {
	g_sleep_data.latch--;
	#ifdef LOGGING_DBG
	LOGGING_UART.print("TIMER TREAD DIMING DELETE: ");
	LOGGING_UART.println((uint32_t)list);
	#endif
	free(list);
}

void zunoTimerTreadDimingStop(zunoTimerTreadDimingType_t type, uint8_t channel, const void *data, uint8_t length) {
	zunoTimerTreadDiming_t						*list;
	zunoTimerTreadDiming_t						*prev;

	zunoEnterCritical();
	if ((list = _zunoTimerTreadFind(type, channel, &prev, data, length)) != NULL) {
		if(prev != NULL)
			prev->next = list->next;
		else
			_diming = list->next;
		_free_list(list);
	}
	zunoExitCritical();
}

void zunoTimerTreadDimingStop(zunoTimerTreadDimingType_t type, uint8_t channel) {
	zunoTimerTreadDimingStop(type, channel, NULL, 0x0);
}

bool zunoTimerTreadDimingGetInfo(zunoTimerTreadDimingType_t type, uint8_t channel, zunoTimerTreadDiming_t *list, const void *data, uint8_t length) {
	zunoTimerTreadDiming_t						*out;
	zunoTimerTreadDiming_t						*prev;

	zunoEnterCritical();
	if ((out = _zunoTimerTreadFind(type, channel, &prev, data, length)) != NULL)
		list[0x0] = out[0x0];
	zunoExitCritical();
	if (out == NULL)
		return (false);
	return (true);
}

bool zunoTimerTreadDimingGetInfo(zunoTimerTreadDimingType_t type, uint8_t channel, zunoTimerTreadDiming_t *list) {
	return (zunoTimerTreadDimingGetInfo(type, channel, list, NULL, 0x0));
}

bool zunoTimerTreadDimingGetValues(zunoTimerTreadDimingType_t type, uint8_t channel, uint8_t current_value, uint8_t *duration_table_8, uint8_t *target_value, const void *data, uint8_t length) {
	zunoTimerTreadDiming_t						list;
	uint64_t									ticks;
	size_t										duration;
	bool										out;

	out = zunoTimerTreadDimingGetInfo(type, channel, &list, data, length);
	if (out == true) {
		target_value[0x0] = list.target_value;
		ticks = rtcc_micros() / 1000;
		if (list.ticks_end > ticks)
			duration = list.ticks_end - ticks;
		else
			duration = 0x0;
		duration_table_8[0x0] = zuno_CCTimerTable8(duration);
	}
	else {
		target_value[0x0] = current_value;
		duration_table_8[0x0] = 0x0;
	}
	return (out);
}

bool zunoTimerTreadDimingGetValues(zunoTimerTreadDimingType_t type, uint8_t channel, uint8_t current_value, uint8_t *duration_table_8, uint8_t *target_value) {
	return (zunoTimerTreadDimingGetValues(type, channel, current_value, duration_table_8, target_value, NULL, 0x0));
}

static bool _zunoTimerTreadDimingLoop_set(zunoTimerTreadDiming_t *list, uint8_t new_value) {
	switch (list->type) {
		#ifdef WITH_CC_WINDOW_COVERING
		case zunoTimerTreadDimingTypeWindowsCovering:
			__zunoWindowCoveringSet(list->channel, list->parameterId, new_value);
			break ;
		#endif
		#ifdef WITH_CC_SOUND_SWITCH
		case zunoTimerTreadDimingTypeSoundSwitch:
			__zunoSoundSwitchStop(list->channel, new_value);
			break ;
		#endif
		default:
			__zuno_BasicUniversalSetter1P(list->channel, new_value);
			break ;
	}
	return (true);
}

static bool _zunoTimerTreadDimingLoop(zunoTimerTreadDiming_t *list) {
	uint64_t								ticks;
	uint8_t									new_value;
	uint8_t									value;

	ticks = rtcc_micros() / 1000;
	if (ticks >= list->ticks_end)
		return (_zunoTimerTreadDimingLoop_set(list, list->target_value));
	if ((list->flag & (ZUNO_TIMER_TREA_DIMING_FLAG_MODE_UP | ZUNO_TIMER_TREA_DIMING_FLAG_MODE_DOWN)) != 0x0) {
		value = ((list->ticks_end - ticks) / list->step);
		if ((list->flag & ZUNO_TIMER_TREA_DIMING_FLAG_MODE_UP) != 0x0)
			new_value = list->target_value - value;
		else
			new_value = list->target_value + value;
		if (new_value == list->current_value)
			return (false);
		list->current_value = new_value;
		_zunoTimerTreadDimingLoop_set(list, new_value);
		if (list->current_value != list->target_value)
			return (false);
		return (true);
	}
	return (false);
}

void zunoTimerTreadDimingLoopReportSet(ZUNOCommandPacketReport_t *frame_report, const zunoTimerTreadDiming_t *list) {
	if ((list->flag & ZUNO_TIMER_TREA_DIMING_FLAG_SUPERVISION) != 0x0)
		zuno_CCSupervisionReportAsyncProcessed(frame_report, &list->super_vision);
	zunoSendReportSet(list->channel, &list->options);
}

void zunoTimerTreadDimingLoop(ZUNOCommandPacketReport_t *frame_report) {
	zunoTimerTreadDiming_t					*list;
	zunoTimerTreadDiming_t					list_tmp;
	zunoTimerTreadDiming_t					*list_array[0x10];
	zunoTimerTreadDiming_t					*prev;
	size_t									i;
	size_t									i_max;

	if (_diming == NULL)
		return ;
	zunoEnterCritical();
	prev = NULL;
	list = _diming;
	i_max = 0x0;
	while (list != NULL && i_max < (sizeof(list_array) / sizeof(list_array[0x0]))) {
		if (_zunoTimerTreadDimingLoop(list) == true) {
			list_array[i_max] = list;
			i_max++;
			if (prev == NULL) {
				list = list->next;
				_diming = list;
				continue ;
			}
			prev->next = list->next;
			list = list->next;
			continue ;
		}
		prev = list;
		list = list->next;
	}
	zunoExitCritical();
	i = 0x0;
	while (i < i_max) {
		list = list_array[i];
		i++;
		zunoEnterCritical();
		list_tmp = list[0x0];
		_free_list(list);
		zunoExitCritical();
		zunoTimerTreadDimingLoopReportSet(frame_report, &list_tmp);
	}
}
#endif

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

	if (ticks == 0x0)
		return (0x0);
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
void zuno_CCSwitchColorTimer(ZunoTimerBasic_t *lp, ZUNOCommandPacketReport_t *frame_report);
void zuno_CCDoorLockTimer(ZunoTimerBasic_t *lp);
void zuno_CCIndicatorTimer(void);
void zuno_CCCentralSceneTimer(void);
void zuno_CCTimeHandlerTimer(void);

// Main timer for CC purposes
ZunoTimer_t g_zuno_timer;

#if defined(WITH_CC_SWITCH_COLOR) || defined(WITH_CC_DOORLOCK)
static void _exe(ZUNOCommandPacketReport_t *frame_report) {
	ZunoTimerBasic_t				*lp_b;
	ZunoTimerBasic_t				*lp_e;
	size_t							channel;

	lp_b = &g_zuno_timer.s_basic[0];
	lp_e = &g_zuno_timer.s_basic[(sizeof(g_zuno_timer.s_basic) / sizeof(ZunoTimerBasic_t))];
	while (lp_b < lp_e) {
		if ((channel = lp_b->channel) != 0x0) {
			switch (ZUNO_CFG_CHANNEL(channel - 1).type) {
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
	(void)frame_report;
}
#endif

void zuno_CCTimer(uint32_t ticks) {
	#if defined(WITH_CC_SWITCH_BINARY) || defined(WITH_CC_SWITCH_MULTILEVEL) || defined(WITH_CC_WINDOW_COVERING) || defined(WITH_CC_SOUND_SWITCH) || defined(WITH_CC_SWITCH_COLOR) || defined(WITH_CC_DOORLOCK)
	ZUNOCommandPacketReport_t						frame_report;
	#endif

	#if defined(WITH_CC_SWITCH_BINARY) || defined(WITH_CC_SWITCH_MULTILEVEL) || defined(WITH_CC_WINDOW_COVERING) || defined(WITH_CC_SOUND_SWITCH)
	if((ticks & 0x7) == 0) { // Once in ~80ms 
		zunoTimerTreadDimingLoop(&frame_report);
	}
	#endif

	#if defined(WITH_CC_SWITCH_COLOR) || defined(WITH_CC_DOORLOCK)
	_exe(&frame_report);
	#endif
	if((ticks & 0x3) == 0) {// Once in ~40ms 
		zuno_CCIndicatorTimer();
	}
	#if defined(WITH_CC_TIME) || defined(WITH_CC_CENTRAL_SCENE)
	if((ticks & 0x7) == 0) { // Once in ~80ms 
		#if defined(WITH_CC_CENTRAL_SCENE) 
		zuno_CCCentralSceneTimer();
		#endif
		#if defined(WITH_CC_TIME)
		zuno_CCTimeHandlerTimer();
		#endif
	}
	#endif
	if((ticks & ZUNO_REPORTTIME_DIVIDER) == 0){// Once in ~80ms - for 0x7
		zunoSendReportHandler(ticks);
	}
	ZWQProcess();
	RSTLocallyTick();
}
