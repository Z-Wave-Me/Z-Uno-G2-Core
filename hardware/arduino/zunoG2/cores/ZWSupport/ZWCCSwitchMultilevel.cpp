#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCTimer.h"
#include "ZWCCSwitchMultilevel.h"
#include "ZWCCBasic.h"
#include "ZWCCSuperVision.h"
#include "LinkedList.h"

#define SWITCH_MULTILEVEL_TIMER_SWITCH_INC					(0x1 << 0x0)//Indicates what should be up
#define SWITCH_MULTILEVEL_TIMER_SWITCH_DEC					(0x1 << 0x1)//Indicates what should be down
#define SWITCH_MULTILEVEL_TIMER_SWITCH_SUPERVISION			(0x1 << 0x2)

bool __zuno_CCSupervisionReportSendTest(uint8_t duration);
uint64_t rtcc_micros(void);

typedef struct					ZWCCSwitchMultilevelTimerList_s
{
	uint64_t					ticksEnd;
	uint32_t					step;
	uint8_t						channel;
	uint8_t						bMode;//Stores modes
	uint8_t						targetValue;
	uint8_t						currentValue;//Current Dimming Level
}								ZWCCSwitchMultilevelTimerList_t;

static ZNLinkedList_t *_switch_multilevel_timer = NULL;

static ZWCCSwitchMultilevelTimerList_t *_get_list_old(uint8_t channel) {
	const ZNLinkedList_t								*linked_list;
	ZWCCSwitchMultilevelTimerList_t						*parameter_list;

	linked_list = _switch_multilevel_timer;
	while (linked_list != NULL) {
		parameter_list = (ZWCCSwitchMultilevelTimerList_t *)linked_list->data;
		if (parameter_list->channel == channel)
			return (parameter_list);
		linked_list = linked_list->next;
	}
	return (NULL);
}

static ZWCCSwitchMultilevelTimerList_t *_get_list_new_change(uint8_t channel) {
	ZWCCSwitchMultilevelTimerList_t						*parameter_list;

	if ((parameter_list = _get_list_old(channel)) != NULL)
		return (parameter_list);
	if ((parameter_list = (ZWCCSwitchMultilevelTimerList_t *)malloc(sizeof(parameter_list[0x0]))) == NULL)
		return (NULL);
	if (znllPushBack(&_switch_multilevel_timer, parameter_list) == false) {
		free(parameter_list);
		return (NULL);
	}
	parameter_list->channel = channel;
	g_sleep_data.latch++;
	return (parameter_list);
}

static void _stop_timer_remove(ZWCCSwitchMultilevelTimerList_t *parameter_list) {
	znllRemoveP(&_switch_multilevel_timer, parameter_list);
	free(parameter_list);
	g_sleep_data.latch--;
}

static void _stop_timer(uint8_t channel) {
	const ZNLinkedList_t								*linked_list;
	ZWCCSwitchMultilevelTimerList_t						*parameter_list;

	zunoEnterCritical();
	linked_list = _switch_multilevel_timer;
	while (linked_list != NULL) {
		parameter_list = (ZWCCSwitchMultilevelTimerList_t *)linked_list->data;
		if (parameter_list->channel == channel) {
			_stop_timer_remove(parameter_list);
			break ;
		}
		linked_list = linked_list->next;
	}
	zunoExitCritical();
}

void __zuno_CCSwitchMultilevelTimerStop(uint8_t channel) {
	_stop_timer(channel);
}

void __zuno_CCSwitchMultilevelGetValues(uint8_t channel, uint8_t *current_value, uint8_t *duration_table_8, uint8_t *target_value) {
	ZWCCSwitchMultilevelTimerList_t						*parameter_list;
	uint64_t											ticks;
	size_t												duration;
	uint8_t												currentValue;

	currentValue = ZWCC_BASIC_GETTER_1P(channel);
	if(currentValue > ZUNO_TIMER_SWITCH_MAX_VALUE)
		currentValue = ZUNO_TIMER_SWITCH_MAX_VALUE;
	current_value[0x0] = currentValue;
	zunoEnterCritical();
	if ((parameter_list = _get_list_old(channel)) != NULL) {
		target_value[0x0] = parameter_list->targetValue;
		ticks = rtcc_micros() / 1000;
		if (parameter_list->ticksEnd > ticks)
			duration = parameter_list->ticksEnd - ticks;
		else
			duration = 0x0;
		duration_table_8[0x0] = zuno_CCTimerTable8(duration);
	}
	else {
		target_value[0x0] = currentValue;
		duration_table_8[0x0] = 0x0;
	}
	zunoExitCritical();
}

void zunoSwitchColorSaveSet(uint8_t channel, void *value);
uint8_t zunoSwitchColorSaveGet(uint8_t channel);

void __zunoWindowCoveringSet(uint8_t channel, uint8_t value);
uint8_t __zunoWindowCoveringGet(uint8_t channel);

void zuno_SwitchMultilevelUniversalSetter1P(byte zuno_ch, uint8_t value) {
    uint8_t type = ZUNO_CFG_CHANNEL(zuno_ch).type;

    switch (type) {
        #ifdef WITH_CC_WINDOW_COVERING
        case ZUNO_WINDOW_COVERING_CHANNEL_NUMBER:
            __zunoWindowCoveringSet(zuno_ch, value);
            break;
        #endif
        // #ifdef WITH_CC_SWITCH_COLOR
        // case ZUNO_SWITCH_COLOR_CHANNEL_NUMBER:
        //     zunoSwitchColorSaveSet(zuno_ch, &value);
        //     break;
        // #endif
        default:
            zuno_universalSetter1P(zuno_ch, value);
            break ;
    }
}

uint8_t zuno_SwitchMultilevelUniversalGetter1P(byte zuno_ch) {
	uint8_t								value;

	uint8_t type = ZUNO_CFG_CHANNEL(zuno_ch).type;
	switch (type) {
		#ifdef WITH_CC_WINDOW_COVERING
		case ZUNO_WINDOW_COVERING_CHANNEL_NUMBER:
			value = __zunoWindowCoveringGet(zuno_ch);
			break;
		#endif
		// #ifdef WITH_CC_SWITCH_COLOR
		// case ZUNO_SWITCH_COLOR_CHANNEL_NUMBER:
		// 	value = zunoSwitchColorSaveGet(zuno_ch);
		// 	break;
		// #endif
		default:
			value = zuno_universalGetter1P(zuno_ch);
			break ;
	}
	return (value);
}

static void _start_level(uint8_t channel, ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report) {// Prepare the structure for dimming
	ZwSwitchMultilevelStartLevelChangeFrame_t			*pk;
	uint32_t											step;
	uint8_t												current_level;
	uint8_t												targetValue;
	uint8_t												b_mode;
	uint8_t												duration;
	ZWCCSwitchMultilevelTimerList_t						*parameter;

	pk = (ZwSwitchMultilevelStartLevelChangeFrame_t *)cmd->cmd;
	if ((pk->v1.properties1 & (1 << 5)) == 0) {// If the level from which you want to start dimming has come, make it current
		if ((current_level = pk->v1.startLevel) > ZUNO_TIMER_SWITCH_MAX_VALUE)
			current_level = ZUNO_TIMER_SWITCH_MAX_VALUE;
		if (current_level != 0x0)
			zunoBasicSaveSet(channel, &current_level);
		ZWCC_BASIC_SETTER_1P(channel, current_level);
		zunoSendReport(channel + 1);
	} else {// Otherwise, get the current
		if ((current_level = ZWCC_BASIC_GETTER_1P(channel)) > ZUNO_TIMER_SWITCH_MAX_VALUE)
			current_level = ZUNO_TIMER_SWITCH_MAX_VALUE;
	}
	if (cmd->len == sizeof(ZwSwitchMultilevelStartLevelChangeV1Frame_t)) {
		step = ZUNO_TIMER_SWITCH_DEFAULT_DURATION * (1000);// Depending on the version, set the default step to increase or from the command we will
		duration = ZUNO_TIMER_SWITCH_DEFAULT_DURATION;
	}
	else {
		duration = pk->v2.dimmingDuration;
		step = zuno_CCTimerTicksTable7(pk->v2.dimmingDuration);
	}
	if ((pk->v1.properties1 & (1 << 6)) == 0) {// Dimming to up
		if (ZUNO_TIMER_SWITCH_MAX_VALUE - current_level == 0)// Check it may not need to dim
			return ;
		if (step == 0) {// If the step turned out to be zero - immediately set the desired level
			zunoSendReport(channel + 1);
			return (ZWCC_BASIC_SETTER_1P(channel, ZUNO_TIMER_SWITCH_MAX_VALUE));
		}
		b_mode = SWITCH_MULTILEVEL_TIMER_SWITCH_INC;
		targetValue = ZUNO_TIMER_SWITCH_MAX_VALUE;
	} else {// Dimming to down
		if (current_level == ZUNO_TIMER_SWITCH_MIN_VALUE)// Check it may not need to dim
			return ;
		if (step == 0) {// If the step turned out to be zero - immediately set the desired level
			zunoSendReport(channel + 1);
			return (ZWCC_BASIC_SETTER_1P(channel, ZUNO_TIMER_SWITCH_MIN_VALUE));
		}
		targetValue = ZUNO_TIMER_SWITCH_MIN_VALUE;
		b_mode = SWITCH_MULTILEVEL_TIMER_SWITCH_DEC;
	}
	if (targetValue == current_level)
		return ;
	step = step / (ZUNO_TIMER_SWITCH_MAX_VALUE + 0x1);
	zunoEnterCritical();
	if ((parameter = _get_list_new_change(channel)) != NULL) {
		parameter->step = step;
		if (b_mode == SWITCH_MULTILEVEL_TIMER_SWITCH_INC)
			step = step * (targetValue - current_level);
		else
			step = step * (current_level - targetValue);
		parameter->ticksEnd = (rtcc_micros() / 1000) + step;
		parameter->currentValue = current_level;
		parameter->targetValue = targetValue;
		if (__zuno_CCSupervisionReportSendTest(duration) == true)
			b_mode = b_mode | SWITCH_MULTILEVEL_TIMER_SWITCH_SUPERVISION;
		parameter->bMode = b_mode;
	}
	zunoExitCritical();
	zuno_CCSupervisionReport(ZUNO_COMMAND_BLOCKED_WORKING, duration, NULL, frame_report);
}

int zuno_CCSwitchMultilevelReport(byte channel, ZUNOCommandPacket_t *packet) {
	SwitchMultilevelReportFrame_t			*report;

	report = (SwitchMultilevelReportFrame_t *)&packet->cmd[0x0];
	__zuno_CCSwitchMultilevelGetValues(channel, &report->v4.currentValue, &report->v4.duration, &report->v4.targetValue);
	report->v4.cmdClass = COMMAND_CLASS_SWITCH_MULTILEVEL;
	report->v4.cmd = SWITCH_MULTILEVEL_REPORT;
	packet->len = sizeof(report->v4);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _set(SwitchMultilevelSetFrame_t *cmd, uint8_t len, uint8_t channel, ZUNOCommandPacketReport_t *frame_report) {
	uint32_t						step;
	size_t							duration;
	uint8_t							value;
	uint8_t							val_basic;
	uint8_t							currentValue;
	uint8_t							b_mode;
	ZWCCSwitchMultilevelTimerList_t	*parameter;

	if ((value = cmd->v4.value) > ZUNO_TIMER_SWITCH_MAX_VALUE && value < 0xFF)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	if (value == 0xFF) {
		if ((val_basic = zunoBasicSaveGet(channel)) != 0)
			value = val_basic;
		else
			value = ZUNO_TIMER_SWITCH_MAX_VALUE;
	}
	if (value != 0x0)
		zunoBasicSaveSet(channel, &value);
	currentValue = ZWCC_BASIC_GETTER_1P(channel) ? 0xFF : 0x00;
	if(currentValue > ZUNO_TIMER_SWITCH_MAX_VALUE)
		currentValue = ZUNO_TIMER_SWITCH_MAX_VALUE;
	if (currentValue != value) {
		switch (len) {
			case sizeof(cmd->v4):
				if ((duration = zuno_CCTimerTicksTable7(cmd->v4.dimmingDuration)) == 0x0) {
					_stop_timer(channel);
					break ;
				}
				zunoEnterCritical();
				if ((parameter = _get_list_new_change(channel)) == NULL) {
					zunoExitCritical();
					break ;
				}
				if (value > currentValue) {
					step = duration / (value - currentValue);
					b_mode = SWITCH_MULTILEVEL_TIMER_SWITCH_INC;
				}
				else {
					step = duration / (currentValue - value);
					b_mode = SWITCH_MULTILEVEL_TIMER_SWITCH_DEC;
				}
				if (__zuno_CCSupervisionReportSendTest(cmd->v4.dimmingDuration) == true)
					b_mode = b_mode | SWITCH_MULTILEVEL_TIMER_SWITCH_SUPERVISION;
				parameter->bMode = b_mode;
				parameter->step = step;
				parameter->currentValue = currentValue;
				parameter->ticksEnd = (rtcc_micros() / 1000) + (duration);
				parameter->targetValue = value;
				zunoExitCritical();
				zuno_CCSupervisionReport(ZUNO_COMMAND_BLOCKED_WORKING, cmd->v4.dimmingDuration, NULL, frame_report);
				return (ZUNO_COMMAND_PROCESSED);
				break ;
			default:
				_stop_timer(channel);
				break ;
		}
	}
	else
		_stop_timer(channel);
	ZWCC_BASIC_SETTER_1P(channel, value);
	zunoSendReport(channel + 1);
	return (ZUNO_COMMAND_PROCESSED);
}

static int _supported(ZUNOCommandPacketReport_t *frame_report) {
	ZwSwitchMultilevelSupportedReportFrame_t		*report;

	report = (ZwSwitchMultilevelSupportedReportFrame_t *)frame_report->packet.cmd;
	report->cmdClass = COMMAND_CLASS_SWITCH_MULTILEVEL;
	report->cmd = SWITCH_MULTILEVEL_SUPPORTED_REPORT;
	report->properties1 = 0x2;/* A supporting device MUST implement the Primary Switch type. The Primary Switch Type SHOULD be 0x02 (Up/Down).The Primary Switch Type MUST NOT be 0x00 (Undefined). */
	report->properties2 = 0x0;
	frame_report->packet.len = sizeof(ZwSwitchMultilevelSupportedReportFrame_t);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _stop_level(uint8_t channel) {// Stop Dimming
	_stop_timer(channel);
	return (ZUNO_COMMAND_PROCESSED);
}
__attribute__((weak)) void zcustom_SWLStartStopHandler(uint8_t channel, bool start, bool up, uint8_t * cmd) {
    (void) channel;
	(void) start;
	(void) up;
	(void) cmd;
}
int zuno_CCSwitchMultilevelHandler(byte channel, ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	int									rs;

	switch(ZW_CMD) {
		case SWITCH_MULTILEVEL_GET:
			_zunoMarkChannelRequested(channel);
			rs = zuno_CCSwitchMultilevelReport(channel, &frame_report->packet);
			break;
		case SWITCH_MULTILEVEL_SET:
			rs = _set((SwitchMultilevelSetFrame_t *)cmd->cmd, cmd->len, channel, frame_report);
			break ;
		case SWITCH_MULTILEVEL_START_LEVEL_CHANGE:
			{
				ZwSwitchMultilevelStartLevelChangeFrame_t * pk = (ZwSwitchMultilevelStartLevelChangeFrame_t *)cmd->cmd;
				zcustom_SWLStartStopHandler(channel, 
											  true, 
											  (pk->v1.properties1 & (1 << 6)) == 0, 
											  (uint8_t*) cmd);
			}
			_start_level(channel, cmd, frame_report);
			rs = ZUNO_COMMAND_PROCESSED;
			break ;
		case SWITCH_MULTILEVEL_STOP_LEVEL_CHANGE:
			zcustom_SWLStartStopHandler(channel, 
										  false, 
										  false, 
										  (uint8_t*) cmd);
			
			rs = _stop_level(channel);
			break ;
		case SWITCH_MULTILEVEL_SUPPORTED_GET:
			rs = _supported(frame_report);
			break ;
		default:
			rs = ZUNO_COMMAND_BLOCKED_NO_SUPPORT;
			break ;
	}
	return rs;
}

static void _zuno_CCSwitchMultilevelTimer(ZUNOCommandPacketReport_t *frame_report, ZWCCSwitchMultilevelTimerList_t *parameter_list) {
	uint64_t								ticks;
	uint8_t									value;
	uint8_t									new_value;

	ticks = rtcc_micros() / 1000;
	if (ticks >= parameter_list->ticksEnd) {
		new_value = parameter_list->targetValue;
	}
	else {
		value = ((parameter_list->ticksEnd - ticks) / parameter_list->step);
		if ((parameter_list->bMode & SWITCH_MULTILEVEL_TIMER_SWITCH_INC) != 0x0)
			new_value = parameter_list->targetValue - value;
		else
			new_value = parameter_list->targetValue + value;
	}
	if (new_value == parameter_list->currentValue)
		return ;
	parameter_list->currentValue = new_value;
	ZWCC_BASIC_SETTER_1P(parameter_list->channel, new_value);
	zunoSendReport(parameter_list->channel + 0x1);
	if (parameter_list->currentValue != parameter_list->targetValue)
		return ;
	if ((parameter_list->bMode & SWITCH_MULTILEVEL_TIMER_SWITCH_SUPERVISION) != 0x0) {
		__cc_supervision._unpacked = true;
		fillOutgoingReportPacketAsync(frame_report, ZUNO_CFG_CHANNEL(parameter_list->channel).zw_channel);
		zuno_CCSupervisionReport(ZUNO_COMMAND_PROCESSED, 0x0, 0x0, frame_report);
	}
	_stop_timer_remove(parameter_list);
}

void __zuno_CCSwitchMultilevelTimer(ZUNOCommandPacketReport_t *frame_report) {
	const ZNLinkedList_t								*linked_list;
	ZWCCSwitchMultilevelTimerList_t						*parameter_list;

	if (_switch_multilevel_timer == NULL)
		return ;
	zunoEnterCritical();
	linked_list = _switch_multilevel_timer;
	while (linked_list != NULL) {
		parameter_list = (ZWCCSwitchMultilevelTimerList_t *)linked_list->data;
		_zuno_CCSwitchMultilevelTimer(frame_report, parameter_list);
		linked_list = linked_list->next;
	}
	zunoExitCritical();
}