#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCTimer.h"
#include "ZWCCSwitchBinary.h"
#include "ZWCCSuperVision.h"
#include "LinkedList.h"

#define SWITCH_BINARY_TIMER_SWITCH_SUPERVISION			(0x1 << 0x2)

bool __zuno_CCSupervisionReportSendTest(uint8_t duration);
uint64_t rtcc_micros(void);

typedef struct						ZWCCSwitchBinaryTimerListCmp_s
{
	uint8_t							channel;
}									ZWCCSwitchBinaryTimerListCmp_t;

typedef struct						ZWCCSwitchBinaryTimerList_s
{
	uint64_t						ticksEnd;
	node_id_t						dst;
	uint8_t							src_zw_channel;
	uint8_t							dst_zw_channel;
	ZWCCSwitchBinaryTimerListCmp_t	cmp;
	uint8_t							bMode;
	uint8_t							targetValue;
	uint8_t							currentValue;
}									ZWCCSwitchBinaryTimerList_t;

static ZNLinkedList_t *_switch_binary_timer = NULL;

static ZWCCSwitchBinaryTimerList_t *_get_list_old(uint8_t channel) {
	const ZNLinkedList_t							*linked_list;
	ZWCCSwitchBinaryTimerList_t						*parameter_list;

	linked_list = _switch_binary_timer;
	while (linked_list != NULL) {
		parameter_list = (ZWCCSwitchBinaryTimerList_t *)linked_list->data;
		if (parameter_list->cmp.channel == channel)
			return (parameter_list);
		linked_list = linked_list->next;
	}
	return (NULL);
}

static ZWCCSwitchBinaryTimerList_t *_get_list_new_change(uint8_t channel) {
	ZWCCSwitchBinaryTimerList_t						*parameter_list;

	if ((parameter_list = _get_list_old(channel)) != NULL)
		return (parameter_list);
	if ((parameter_list = (ZWCCSwitchBinaryTimerList_t *)malloc(sizeof(parameter_list[0x0]))) == NULL)
		return (NULL);
	if (znllPushBack(&_switch_binary_timer, parameter_list) == false) {
		free(parameter_list);
		return (NULL);
	}
	parameter_list->cmp.channel = channel;
	g_sleep_data.latch++;
	return (parameter_list);
}

static void _stop_timer_remove(ZWCCSwitchBinaryTimerList_t *parameter_list) {
	znllRemoveP(&_switch_binary_timer, parameter_list);
	free(parameter_list);
	g_sleep_data.latch--;
}

void __zuno_CCSwitchBinaryTimerStop(uint8_t channel) {
	const ZNLinkedList_t							*linked_list;
	ZWCCSwitchBinaryTimerList_t						*parameter_list;

	zunoEnterCritical();
	linked_list = _switch_binary_timer;
	while (linked_list != NULL) {
		parameter_list = (ZWCCSwitchBinaryTimerList_t *)linked_list->data;
		if (parameter_list->cmp.channel == channel) {
			_stop_timer_remove(parameter_list);
			break ;
		}
		linked_list = linked_list->next;
	}
	zunoExitCritical();
}

void __zuno_CCSwitchBinaryGetValues(uint8_t channel, uint8_t *current_value, uint8_t *duration_table_8, uint8_t *target_value) {
	ZWCCSwitchBinaryTimerList_t					*parameter_list;
	uint64_t									ticks;
	size_t										duration;
	uint8_t										currentValue;

	currentValue = __zuno_BasicUniversalGetter1P(channel) ? 0xFF : 0x00;
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

int zuno_CCSwitchBinaryReport(byte channel, ZUNOCommandPacket_t *packet) {
	ZwBasicBinaryReportFrame_t				*report;

	report = (ZwBasicBinaryReportFrame_t *)&packet->cmd[0x0];
	__zuno_BasicUniversalGetCurrentValueDurationTargetValue(channel, &report->v2.currentValue, &report->v2.duration, &report->v2.targetValue);
	report->v2.cmdClass = COMMAND_CLASS_SWITCH_BINARY;
	report->v2.cmd = SWITCH_BINARY_REPORT;
	packet->len = sizeof(report->v2);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _set(ZwSwitchBinarySetFrame_t *cmd, size_t len, size_t channel, ZUNOCommandPacketReport_t *frame_report, ZUNOCommandPacket_t *packet) {
	size_t							value;
	size_t							duration;
	size_t							currentValue;
	ZWCCSwitchBinaryTimerList_t		*parameter;

	if ((value = cmd->v2.targetValue) > 0x63 && value < 0xFF)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	value = value ? 0xFF : 0x00;// Map the value right way
	currentValue = __zuno_BasicUniversalGetter1P(channel) ? 0xFF : 0x00;
	if (currentValue != value) {
		switch (len) {
			case sizeof(cmd->v2):
				if ((duration = (zuno_CCTimerTicksTable7(cmd->v2.duration))) == 0x0) {
					__zuno_BasicUniversalTimerStop(channel);
					break ;
				}
				zunoEnterCritical();
				if ((parameter = _get_list_new_change(channel)) == NULL) {
					zunoExitCritical();
					break ;
				}
				if (__zuno_CCSupervisionReportSendTest(cmd->v2.duration) == true)
					parameter->bMode = SWITCH_BINARY_TIMER_SWITCH_SUPERVISION;
				else
					parameter->bMode = 0x0;
				parameter->dst = packet->src_node;
				parameter->src_zw_channel = packet->dst_zw_channel;
				parameter->dst_zw_channel = packet->src_zw_channel;
				parameter->cmp.channel = channel;
				parameter->ticksEnd = (rtcc_micros() / 1000) + duration;
				parameter->targetValue = value;
				zunoExitCritical();
				zuno_CCSupervisionReport(ZUNO_COMMAND_BLOCKED_WORKING, cmd->v2.duration, NULL, frame_report);
				return (ZUNO_COMMAND_PROCESSED);
				break ;
			default:
				break ;
		}
	}
	else
		__zuno_BasicUniversalTimerStop(channel);
	__zuno_BasicUniversalSetter1P(channel, value);
	zunoSendReport(channel + 0x1);
	return (ZUNO_COMMAND_PROCESSED);
}

int zuno_CCSwitchBinaryHandler(byte channel, ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report){
	int							rs;

	switch(ZW_CMD) {
		case SWITCH_BINARY_GET:
			rs = zuno_CCSwitchBinaryReport(channel, &frame_report->packet);
			_zunoMarkChannelRequested(channel);
			break;
		case SWITCH_BINARY_SET:
			rs = _set((ZwSwitchBinarySetFrame_t *)cmd->cmd, cmd->len, channel, frame_report, cmd);
			break;
		default:
			rs = ZUNO_COMMAND_BLOCKED_NO_SUPPORT;
			break ;
	}
	return (rs);
}

static void _zuno_CCSwitchBinaryTimer(ZUNOCommandPacketReport_t *frame_report, ZWCCSwitchBinaryTimerList_t *parameter_list) {
	uint64_t								ticks;

	ticks = rtcc_micros() / 1000;
	if (ticks < parameter_list->ticksEnd)
		return ;
	__zuno_BasicUniversalSetter1P(parameter_list->cmp.channel, parameter_list->targetValue);
	if (parameter_list->bMode == SWITCH_BINARY_TIMER_SWITCH_SUPERVISION) {
		zuno_CCSupervisionReportAsyncProcessed(frame_report, parameter_list->dst, parameter_list->src_zw_channel, parameter_list->dst_zw_channel);
	}
	zunoSendReport(parameter_list->cmp.channel + 0x1);
	_stop_timer_remove(parameter_list);
}

void __zuno_CCSwitchBinaryTimer(ZUNOCommandPacketReport_t *frame_report) {
	const ZNLinkedList_t							*linked_list;
	ZWCCSwitchBinaryTimerList_t						*parameter_list;

	if (_switch_binary_timer == NULL)
		return ;
	zunoEnterCritical();
	linked_list = _switch_binary_timer;
	while (linked_list != NULL) {
		parameter_list = (ZWCCSwitchBinaryTimerList_t *)linked_list->data;
		_zuno_CCSwitchBinaryTimer(frame_report, parameter_list);
		linked_list = linked_list->next;
	}
	zunoExitCritical();
}

#include "ZWCCZWavePlusInfo.h"

#define ICON_TYPE_GENERIC_ON_OFF_POWER_SWITCH                                0x0700   //On/Off Power Switch  Device Type
#define ICON_TYPE_SPECIFIC_ON_OFF_POWER_SWITCH_PLUGIN	                     0x0701	  //Relay device, implemented as a plugin device
#define ICON_TYPE_SPECIFIC_ON_OFF_POWER_SWITCH_WALL_OUTLET	                 0x0702	  //Relay device, implemented as a wall outlet
#define ICON_TYPE_SPECIFIC_ON_OFF_POWER_SWITCH_CEILING_OUTLET	             0x0703	  //Relay device, implemented as a ceiling outlet
#define ICON_TYPE_SPECIFIC_ON_OFF_POWER_SWITCH_WALL_LAMP	                 0x0704	  //Relay device, implemented as a wall mounted lamp
#define ICON_TYPE_SPECIFIC_ON_OFF_POWER_SWITCH_LAMP_POST_HIGH	             0x0705	  //Relay device, implemented as a ceiling outlet
#define ICON_TYPE_SPECIFIC_ON_OFF_POWER_SWITCH_LAMP_POST_LOW	             0x0706	  //Relay device, implemented as a ceiling outlet

void zuno_CCSwitchBinaryGetIcon(ZwZwavePlusInfoIcon_t *icon) {
	uint16_t								installerIconType;
	uint16_t								userIconType;

	installerIconType = ICON_TYPE_GENERIC_ON_OFF_POWER_SWITCH;
	userIconType = ICON_TYPE_GENERIC_ON_OFF_POWER_SWITCH;
	icon->installerIconType = installerIconType;
	icon->userIconType = userIconType;
}

void zuno_CCSwitchBinaryGetType(uint8_t channel, ZwZwavePlusInfoType_t *type) {
	type->genericDeviceClass = GENERIC_TYPE_SWITCH_BINARY;
	type->specificDeviceClass = ZUNO_CFG_CHANNEL(channel).sub_type;
}