#include "Arduino.h"
#include "ZWCCWindowCovering.h"
#include "ZWCCSwitchMultilevel.h"
#include "ZWCCSuperVision.h"
#include "LinkedList.h"

#define WINDOW_COVERING_TIMER_SWITCH_INC					(0x1 << 0x0)//Indicates what should be up
#define WINDOW_COVERING_TIMER_SWITCH_DEC					(0x1 << 0x1)//Indicates what should be down
#define WINDOW_COVERING_TIMER_SWITCH_SUPERVISION			(0x1 << 0x2)

bool __zuno_CCSupervisionReportSendTest(uint8_t duration);
uint64_t rtcc_micros(void);

typedef struct					ZWCCWindowCoveringTimerList_s
{
	uint64_t					ticksEnd;
	uint32_t					step;
	uint8_t						channel;
	uint8_t						bMode;//Stores modes
	uint8_t						targetValue;
	uint8_t						currentValue;//Current Dimming Level
	uint8_t						parameterId;
}								ZWCCWindowCoveringTimerList_t;

static ZNLinkedList_t *_window_covering_timer = NULL;

static ZWCCWindowCoveringTimerList_t *_get_list_old(uint8_t channel, uint8_t parameterId) {
	const ZNLinkedList_t								*linked_list;
	ZWCCWindowCoveringTimerList_t						*parameter_list;

	linked_list = _window_covering_timer;
	while (linked_list != NULL) {
		parameter_list = (ZWCCWindowCoveringTimerList_t *)linked_list->data;
		if (parameter_list->channel == channel && parameter_list->parameterId == parameterId)
			return (parameter_list);
		linked_list = linked_list->next;
	}
	return (NULL);
}

static ZWCCWindowCoveringTimerList_t *_get_list_new_change(uint8_t channel, uint8_t parameterId) {
	ZWCCWindowCoveringTimerList_t						*parameter_list;

	if ((parameter_list = _get_list_old(channel, parameterId)) != NULL)
		return (parameter_list);
	if ((parameter_list = (ZWCCWindowCoveringTimerList_t *)malloc(sizeof(parameter_list[0x0]))) == NULL)
		return (NULL);
	if (znllPushBack(&_window_covering_timer, parameter_list) == false) {
		free(parameter_list);
		return (NULL);
	}
	parameter_list->channel = channel;
	g_sleep_data.latch++;
	return (parameter_list);
}

static void _stop_timer_remove(ZWCCWindowCoveringTimerList_t *parameter_list) {
	znllRemoveP(&_window_covering_timer, parameter_list);
	free(parameter_list);
	g_sleep_data.latch--;
}

static bool _stop_timer(uint8_t channel, uint8_t parameterId) {
	const ZNLinkedList_t								*linked_list;
	ZWCCWindowCoveringTimerList_t						*parameter_list;
	bool												b_free;

	zunoEnterCritical();
	b_free = false;
	linked_list = _window_covering_timer;
	while (linked_list != NULL) {
		parameter_list = (ZWCCWindowCoveringTimerList_t *)linked_list->data;
		if (parameter_list->channel == channel && parameter_list->parameterId == parameterId) {
			_stop_timer_remove(parameter_list);
			b_free = true;
			break ;
		}
		linked_list = linked_list->next;
	}
	zunoExitCritical();
	return (b_free);
}

void __zuno_CCWindowCoveringTimerStop(uint8_t channel) {
	const ZNLinkedList_t								*linked_list;
	ZWCCWindowCoveringTimerList_t						*parameter_list;
	bool												b_free;

	zunoEnterCritical();
	b_free = false;
	linked_list = _window_covering_timer;
	while (linked_list != NULL) {
		parameter_list = (ZWCCWindowCoveringTimerList_t *)linked_list->data;
		if (parameter_list->channel == channel) {
			_stop_timer_remove(parameter_list);
			b_free = true;
		}
		linked_list = linked_list->next;
	}
	zunoExitCritical();
	if (b_free == true)
		return ;
	__zuno_CCSwitchMultilevelTimerStop(channel);
}

static bool _get_values(uint8_t channel, uint8_t parameterId, uint8_t *current_value, uint8_t *duration_table_8, uint8_t *target_value) {
	ZWCCWindowCoveringTimerList_t						*parameter_list;
	uint64_t											ticks;
	size_t												duration;
	uint8_t												currentValue;
	bool												b_find;

	currentValue = zuno_universalGetter2P(channel, parameterId);
	if(currentValue > 0x63)
		currentValue = 0x63;
	current_value[0x0] = currentValue;
	zunoEnterCritical();
	if ((parameter_list = _get_list_old(channel, parameterId)) != NULL) {
		target_value[0x0] = parameter_list->targetValue;
		ticks = rtcc_micros() / 1000;
		if (parameter_list->ticksEnd > ticks)
			duration = parameter_list->ticksEnd - ticks;
		else
			duration = 0x0;
		duration_table_8[0x0] = zuno_CCTimerTable8(duration);
		b_find = true;
	}
	else {
		target_value[0x0] = currentValue;
		duration_table_8[0x0] = 0x0;
		b_find = false;

	}
	zunoExitCritical();
	return (b_find);
}

static uint32_t _get_parameter_mask(uint8_t channel) {
	uint32_t								mask;

	memcpy(&mask, &ZUNO_CFG_CHANNEL(channel).params[0x0], sizeof(mask));
	if ((mask & 0x55555555) != 0x0)
		return (mask & (0x55555555 & WINDOW_COVERING_PARAMETER_ID_MASK));
	return (mask & (0xAAAAAAAA & WINDOW_COVERING_PARAMETER_ID_MASK));
	// return (mask);
}

static int _supported_report(uint8_t channel, ZUNOCommandPacketReport_t *frame_report) {
	ZW_WINDOW_COVERING_SUPPORTED_REPORT_1BYTE_FRAME					*report;
	uint32_t														mask;

	report = (ZW_WINDOW_COVERING_SUPPORTED_REPORT_1BYTE_FRAME *)frame_report->packet.cmd;
	// report->cmdClass = COMMAND_CLASS_WINDOW_COVERING; set in - fillOutgoingPacket
	// report->cmd = WINDOW_COVERING_SUPPORTED_REPORT; set in - fillOutgoingPacket
	mask = _get_parameter_mask(channel);
	memcpy(&report->parameterMask[0x0], &mask, sizeof(mask));
	report->properties1 = sizeof(mask);
	frame_report->packet.len = sizeof(report[0x0]) + sizeof(mask);
	return (ZUNO_COMMAND_ANSWERED);
}

static bool _set_test(uint32_t mask, const VG_WINDOW_COVERING_SET_VG *vg) {
	uint8_t														parameterId;
	uint8_t														value;

	parameterId = vg->parameterId;
	if ((mask & (0x1 << parameterId)) == 0x0)
		return (false);
	value = vg->value;
	if (value > 0x63)
		return (false);
	return (true);
}

static void _set_duration_0(uint8_t channel, const VG_WINDOW_COVERING_SET_VG *vg, uint8_t count) {
	uint8_t														i;

	zunoEnterCritical();
	i = 0x0;
	while (i < count) {
		_stop_timer(channel, vg[i].parameterId);
		i++;
	}
	zunoExitCritical();
	i = 0x0;
	while (i < count) {
		zuno_universalSetter2P(channel, vg[i].parameterId, vg[i].value);
		i++;
	}
}

static int _set(uint8_t channel, const ZW_WINDOW_COVERING_SET_1BYTE_FRAME *paket, ZUNOCommandPacketReport_t *frame_report) {
	const VG_WINDOW_COVERING_SET_VG								*vg;
	uint32_t													mask;
	uint8_t														count;
	uint8_t														i;
	size_t														duration;
	const uint8_t												*tmp;
	uint8_t														parameterId;
	size_t														step;
	uint8_t														b_mode;
	uint8_t														currentValue;
	uint8_t														targetValue;
	uint8_t														duration_encode;
	ZWCCWindowCoveringTimerList_t								*parameter_list;

	mask = _get_parameter_mask(channel);
	count = paket->properties1 & WINDOW_COVERING_SET_PROPERTIES1_PARAMETER_COUNT_MASK;
	vg = &paket->variantgroup1[0x0];
	i = 0x0;
	while (i < count) {
		if (_set_test(mask, &vg[i]) == false)
			return (ZUNO_COMMAND_BLOCKED_FAILL);
		i++;
	}
	i = 0x0;
	vg = &paket->variantgroup1[0x0];
	tmp = (const uint8_t *)(vg + count);
	duration_encode = tmp[0x0];
	duration = zuno_CCTimerTicksTable7(duration_encode);
	if (duration == 0x0) {
		_set_duration_0(channel, vg, count);
		zunoSendReport(channel + 1);
		return (ZUNO_COMMAND_PROCESSED);
	}
	while (i < count) {
		parameterId = vg[i].parameterId;
		targetValue = vg[i].value;
		currentValue = zuno_universalGetter2P(channel, parameterId);
		if (currentValue != targetValue ) {
			if (targetValue > currentValue) {
				step = duration / (targetValue - currentValue);
				b_mode = WINDOW_COVERING_TIMER_SWITCH_INC;
			}
			else {
				step = duration / (currentValue - targetValue);
				b_mode = WINDOW_COVERING_TIMER_SWITCH_DEC;
			}
			if (step == 0x0) {
				zuno_universalSetter2P(channel, parameterId, targetValue);
				continue ;
			}
			zunoEnterCritical();
			if ((parameter_list = _get_list_new_change(channel, parameterId)) != NULL) {
				parameter_list->channel = channel;
				parameter_list->parameterId = parameterId;
				parameter_list->bMode = b_mode;
				parameter_list->currentValue = currentValue;
				parameter_list->targetValue = targetValue;
				parameter_list->step = step;
				parameter_list->ticksEnd = (rtcc_micros() / 1000) + duration;
			}
			zunoExitCritical();
			zuno_CCSupervisionReport(ZUNO_COMMAND_PROCESSED, 0, 0, frame_report);
		}
		i++;
	}
	return (ZUNO_COMMAND_PROCESSED);
}

static void _get_set(uint8_t channel, ZW_WINDOW_COVERING_REPORT_FRAME *report, uint8_t parameterId) {
	report->parameterId = parameterId;
	_get_values(channel, parameterId, &report->currentValue, &report->duration, &report->targetValue);
}

static int _get(uint8_t channel, const ZW_WINDOW_COVERING_GET_FRAME *paket, ZUNOCommandPacketReport_t *frame_report) {
	uint32_t													mask;
	uint8_t														parameterId;
	ZW_WINDOW_COVERING_REPORT_FRAME								*report;

	mask = _get_parameter_mask(channel);
	parameterId = paket->parameterId;
	if ((mask & (0x1 << parameterId)) == 0x0)
		return (ZUNO_COMMAND_BLOCKED);
	report = (ZW_WINDOW_COVERING_REPORT_FRAME *)frame_report->packet.cmd;
	// report->cmdClass = COMMAND_CLASS_WINDOW_COVERING; set in - fillOutgoingPacket
	// report->cmd = WINDOW_COVERING_REPORT; set in - fillOutgoingPacket
	frame_report->packet.len = sizeof(report[0x0]);
	_get_set(channel, report, parameterId);
	return (ZUNO_COMMAND_ANSWERED);
}

static void _start_level_sdfdsfgsd(uint8_t channel, uint8_t parameterId, uint8_t duration, uint8_t targetValue, uint8_t b_mode, ZUNOCommandPacketReport_t *frame_report) {
	ZWCCWindowCoveringTimerList_t								*parameter_list;
	uint8_t														currentValue;
	size_t														step;

	step = (zuno_CCTimerTicksTable7(duration) / (0x63 + 1));
	if (step == 0x0) {
		zuno_universalSetter2P(channel, parameterId, targetValue);
		return ;
	}
	currentValue = zuno_universalGetter2P(channel, parameterId);
	zunoEnterCritical();
	if ((parameter_list = _get_list_new_change(channel, parameterId)) != NULL) {
		parameter_list->channel = channel;
		parameter_list->parameterId = parameterId;
		parameter_list->bMode = b_mode;
		parameter_list->currentValue = currentValue;
		parameter_list->targetValue = targetValue;
		parameter_list->step = step;
		if (b_mode == WINDOW_COVERING_TIMER_SWITCH_INC)
			step = step * (targetValue - currentValue);
		else
			step = step * (currentValue - targetValue);
		parameter_list->ticksEnd = (rtcc_micros() / 1000) + step;
	}
	zunoExitCritical();
	zuno_CCSupervisionReport(ZUNO_COMMAND_PROCESSED, 0, 0, frame_report);
}

static int _start_level_change(uint8_t channel, const ZW_WINDOW_COVERING_START_LEVEL_CHANGE_FRAME *paket, ZUNOCommandPacketReport_t *frame_report) {
	uint32_t													mask;
	uint8_t														parameterId;
	uint8_t														targetValue;
	uint8_t														bMode;

	mask = _get_parameter_mask(channel);
	parameterId = paket->parameterId;
	if ((mask & (0x1 << parameterId)) == 0x0)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	if ((paket->properties1 & WINDOW_COVERING_START_LEVEL_CHANGE_PROPERTIES1_UP_DOWN_BIT_MASK) == 0) {// Dimming to up
		targetValue = 0x63;
		bMode = WINDOW_COVERING_TIMER_SWITCH_INC;
	}
	else {// Dimming to down
		targetValue = 0x0;
		bMode = WINDOW_COVERING_TIMER_SWITCH_DEC;
	}
	_start_level_sdfdsfgsd(channel, parameterId, paket->duration, targetValue, bMode, frame_report);
	return (ZUNO_COMMAND_PROCESSED);
}

__WEAK void zuno_CCWindowCoveringStop(uint8_t channel, uint8_t parameterId) {
	(void)channel;
	(void)parameterId;
}

static int _stop_level_change(uint8_t channel, const ZW_WINDOW_COVERING_STOP_LEVEL_CHANGE_FRAME *paket) {
	uint8_t											parameterId;

	parameterId = paket->parameterId;
	if (_stop_timer(channel, parameterId) == true)
		zuno_CCWindowCoveringStop(channel, parameterId);
	return (ZUNO_COMMAND_PROCESSED);
}


int zuno_CCWindowCoveringHandler(uint8_t channel, ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	int				rs;

	switch(ZW_CMD) {
		case WINDOW_COVERING_SUPPORTED_GET:
			rs = _supported_report(channel, frame_report);
			break ;
		case WINDOW_COVERING_SET:
			rs = _set(channel, (const ZW_WINDOW_COVERING_SET_1BYTE_FRAME *)cmd->cmd, frame_report);
			break ;
		case WINDOW_COVERING_GET:
			_zunoMarkChannelRequested(channel);
			rs = _get(channel, (const ZW_WINDOW_COVERING_GET_FRAME *)cmd->cmd, frame_report);
			break ;
		case WINDOW_COVERING_START_LEVEL_CHANGE:
			rs = _start_level_change(channel, (const ZW_WINDOW_COVERING_START_LEVEL_CHANGE_FRAME *)cmd->cmd, frame_report);
			break ;
		case WINDOW_COVERING_STOP_LEVEL_CHANGE:
			rs = _stop_level_change(channel, (const ZW_WINDOW_COVERING_STOP_LEVEL_CHANGE_FRAME *)cmd->cmd);
			break ;
		default:
			rs = ZUNO_COMMAND_BLOCKED_NO_SUPPORT;
			break ;
	}
	return (rs);
}

int zuno_CCWindowCoveringReport(uint8_t channel, ZUNOCommandPacket_t *packet) {
	ZW_WINDOW_COVERING_REPORT_FRAME								*report;
	uint32_t													mask;
	uint8_t														parameterId;

	mask = _get_parameter_mask(channel);
	report = (ZW_WINDOW_COVERING_REPORT_FRAME *)&packet->cmd[0x0];
	packet->len = sizeof(report[0x0]);
	report->cmdClass = COMMAND_CLASS_WINDOW_COVERING;
	report->cmd = WINDOW_COVERING_REPORT;
	parameterId = 0x0;
	while (mask != 0x0) {
		if ((mask & 0x1) != 0x0) {
			_get_set(channel, report, parameterId);
			zunoSendZWPackage(packet);
		}
		mask = mask >> 0x1;
		parameterId++;
	}
	return (ZUNO_COMMAND_PROCESSED);
}

static void _zuno_CCWindowCoveringTimer(ZUNOCommandPacketReport_t *frame_report, ZWCCWindowCoveringTimerList_t *parameter_list) {
	uint64_t								ticks;
	uint8_t									value;
	uint8_t									new_value;

	ticks = rtcc_micros() / 1000;
	if (ticks >= parameter_list->ticksEnd) {
		new_value = parameter_list->targetValue;
	}
	else {
		value = ((parameter_list->ticksEnd - ticks) / parameter_list->step);
		if ((parameter_list->bMode & WINDOW_COVERING_TIMER_SWITCH_INC) != 0x0)
			new_value = parameter_list->targetValue - value;
		else
			new_value = parameter_list->targetValue + value;
	}
	if (new_value == parameter_list->currentValue)
		return ;
	parameter_list->currentValue = new_value;
	zuno_universalSetter2P(parameter_list->channel, parameter_list->parameterId, new_value);
	zunoSendReport(parameter_list->channel + 0x1);
	if (parameter_list->currentValue != parameter_list->targetValue)
		return ;
	if ((parameter_list->bMode & WINDOW_COVERING_TIMER_SWITCH_SUPERVISION) != 0x0) {
		__cc_supervision._unpacked = true;
		fillOutgoingReportPacketAsync(frame_report, ZUNO_CFG_CHANNEL(parameter_list->channel).zw_channel);
		zuno_CCSupervisionReport(ZUNO_COMMAND_PROCESSED, 0x0, 0x0, frame_report);
	}
	_stop_timer_remove(parameter_list);
}

void __zuno_CCWindowCoveringTimer(ZUNOCommandPacketReport_t *frame_report) {
	const ZNLinkedList_t								*linked_list;
	ZWCCWindowCoveringTimerList_t						*parameter_list;

	if (_window_covering_timer == NULL)
		return ;
	zunoEnterCritical();
	linked_list = _window_covering_timer;
	while (linked_list != NULL) {
		parameter_list = (ZWCCWindowCoveringTimerList_t *)linked_list->data;
		_zuno_CCWindowCoveringTimer(frame_report, parameter_list);
		linked_list = linked_list->next;
	}
	zunoExitCritical();
}

void __zunoWindowCoveringSet(uint8_t channel, uint8_t value) {
	uint32_t													mask;
	uint32_t													parameterId_mask;
	uint8_t														parameterId;
	VG_WINDOW_COVERING_SET_VG									vg;

	vg.value = value;
	mask = _get_parameter_mask(channel);
	parameterId = 0x0;
	while (mask != 0x0) {
		parameterId_mask = 0x1 << parameterId;
		if ((mask & parameterId_mask) != 0x0) {
			mask = mask ^ parameterId_mask;
			vg.parameterId = parameterId;
			_set_duration_0(channel, &vg, 0x1);
		}
		parameterId++;
	}
}

uint8_t __zunoWindowCoveringGet(uint8_t channel) {
	uint32_t													mask;
	uint8_t														parameterId;
	uint8_t														currentValue;

	mask = _get_parameter_mask(channel);
	parameterId = ZUNO_CFG_CHANNEL(channel).sub_type;
	if ((mask & (0x1 << parameterId)) == 0x0)
		return (0x0);
	currentValue = zuno_universalGetter2P(channel, parameterId);
	return (currentValue);
}

void __zuno_CCWindowCoveringGetValues(uint8_t channel, uint8_t *current_value, uint8_t *duration_table_8, uint8_t *target_value) {
	if (_get_values(channel, ZUNO_CFG_CHANNEL(channel).sub_type, current_value, duration_table_8, target_value) == true)
		return ;
	__zuno_CCSwitchMultilevelGetValues(channel, current_value, duration_table_8, target_value);
}

#include "ZWCCZWavePlusInfo.h"

#define ICON_TYPE_GENERIC_WINDOW_COVERING_NO_POSITION_ENDPOINT               0x1800   //Window Covering No Position/Endpoint  Device Type
																		   
#define ICON_TYPE_GENERIC_WINDOW_COVERING_ENDPOINT_AWARE                     0x1900   //Window Covering Endpoint Aware Device Type
																		   
#define ICON_TYPE_GENERIC_WINDOW_COVERING_POSITION_ENDPOINT_AWARE            0x1A00   //Window Covering Position/Endpoint Aware Device Type

void zuno_CCWindowCoveringGetIcon(uint8_t channel, ZwZwavePlusInfoIcon_t *icon) {
	uint32_t						mask;
	uint16_t						installerIconType;
	uint16_t						userIconType;

	mask = _get_parameter_mask(channel);
	if ((mask & 0x55555555) != 0x0) {
		installerIconType = ICON_TYPE_GENERIC_WINDOW_COVERING_ENDPOINT_AWARE;
		userIconType = ICON_TYPE_GENERIC_WINDOW_COVERING_ENDPOINT_AWARE;
	}
	else {
		installerIconType = ICON_TYPE_GENERIC_WINDOW_COVERING_POSITION_ENDPOINT_AWARE;
		userIconType = ICON_TYPE_GENERIC_WINDOW_COVERING_POSITION_ENDPOINT_AWARE;
	}
	icon->installerIconType = installerIconType;
	icon->userIconType = userIconType;
}

void zuno_CCWindowCoveringGetType(uint8_t channel, ZwZwavePlusInfoType_t *type) {
	uint32_t						mask;
	uint8_t							specificDeviceClass;

	mask = _get_parameter_mask(channel);
	if ((mask & 0x55555555) != 0x0) {
		specificDeviceClass = SPECIFIC_TYPE_CLASS_B_MOTOR_CONTROL;
	}
	else {
		specificDeviceClass = SPECIFIC_TYPE_CLASS_C_MOTOR_CONTROL;
	}
	type->genericDeviceClass = GENERIC_TYPE_SWITCH_MULTILEVEL;
	type->specificDeviceClass = specificDeviceClass;
}