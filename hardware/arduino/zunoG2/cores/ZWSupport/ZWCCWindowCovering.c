#include "Arduino.h"
#include "ZWCCWindowCovering.h"
#include "ZWCCSwitchMultilevel.h"
#include "ZWCCSuperVision.h"
#include "LinkedList.h"
#include "ZWCCTimer.h"
uint64_t rtcc_micros(void);

static uint8_t _zunoWindowCoveringGet(uint8_t channel, uint8_t parameterId) {
	uint8_t														currentValue;

	currentValue = zuno_universalGetter2P(channel, parameterId);
	if (currentValue > 0x63)
		currentValue = 0x63;
	return (currentValue);
}

__WEAK void zuno_CCWindowCoveringStop(uint8_t channel, uint8_t parameterId) {
	(void)channel;
	(void)parameterId;
}

static uint8_t _get_default_parameter_id(uint8_t channel) {
	return (ZUNO_CFG_CHANNEL(channel).sub_type);
}

static void _timer_stop(uint8_t channel, uint8_t parameterId) {
	zunoTimerTreadDimingStop(zunoTimerTreadDimingTypeWindowsCovering, channel, &parameterId, 0x1);
	__zuno_CCSwitchMultilevelTimerStop(channel);
}

static bool _get_values(uint8_t channel, uint8_t parameterId, uint8_t *current_value, uint8_t *duration_table_8, uint8_t *target_value) {
	uint8_t												currentValue;

	currentValue = _zunoWindowCoveringGet(channel, parameterId);
	current_value[0x0] = currentValue;
	return (zunoTimerTreadDimingGetValues(zunoTimerTreadDimingTypeWindowsCovering, channel, currentValue, duration_table_8, target_value, &parameterId, 0x1));
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

	report = (ZW_WINDOW_COVERING_SUPPORTED_REPORT_1BYTE_FRAME *)frame_report->info.packet.cmd;
	// report->cmdClass = COMMAND_CLASS_WINDOW_COVERING; set in - fillOutgoingPacket
	// report->cmd = WINDOW_COVERING_SUPPORTED_REPORT; set in - fillOutgoingPacket
	mask = _get_parameter_mask(channel);
	memcpy(&report->parameterMask[0x0], &mask, sizeof(mask));
	report->properties1 = sizeof(mask);
	frame_report->info.packet.len = sizeof(report[0x0]) + sizeof(mask);
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

static void _set_duration_0(ZUNOCommandPacketReport_t *frame_report, const ZUNOCommandHandlerOption_t *options, uint8_t channel, const VG_WINDOW_COVERING_SET_VG *vg, uint8_t count, uint32_t mask) {
	uint8_t														i;
	ZwWindowCoveringReport_t									info;

	i = 0x0;
	while (i < count) {
		if (_set_test(mask, &vg[i]) == true) {
			_timer_stop(channel, vg[i].parameterId);
			__zunoWindowCoveringSet(channel, vg[i].parameterId, vg[i].value);
			info.parameterId = vg[i].parameterId;
			zunoSendReportSet(channel, frame_report, options, &info);
		}
		i++;
	}
}

static int _set(ZUNOCommandPacketReport_t *frame_report, uint8_t channel, const ZW_WINDOW_COVERING_SET_1BYTE_FRAME *paket, const ZUNOCommandHandlerOption_t *options) {
	const VG_WINDOW_COVERING_SET_VG								*vg;
	int															result;
	uint32_t													mask;
	uint8_t														count;
	uint8_t														i;
	size_t														duration;
	const uint8_t												*tmp;
	uint8_t														parameterId;
	size_t														step;
	uint8_t														flag;
	uint8_t														currentValue;
	uint8_t														targetValue;
	uint8_t														duration_encode;
	zunoTimerTreadDiming_t										*parameter;

	mask = _get_parameter_mask(channel);
	count = paket->properties1 & WINDOW_COVERING_SET_PROPERTIES1_PARAMETER_COUNT_MASK;
	vg = &paket->variantgroup1[0x0];
	i = 0x0;
	result = ZUNO_COMMAND_PROCESSED;
	while (i < count) {
		if (_set_test(mask, &vg[i]) == false)
			result = ZUNO_COMMAND_BLOCKED_FAIL;
		i++;
	}
	i = 0x0;
	vg = &paket->variantgroup1[0x0];
	tmp = (const uint8_t *)(vg + count);
	duration_encode = tmp[0x0];
	duration = zuno_CCTimerTicksTable7(duration_encode);
	if (duration == 0x0) {
		zuno_CCSupervisionReportSyncDefault(frame_report, result);
		_set_duration_0(frame_report, options, channel, vg, count, mask);
		return (result);
	}
	while (i < count) {
		if (_set_test(mask, &vg[i]) == false) {
			i++;
			continue ;
		}
		parameterId = vg[i].parameterId;
		targetValue = vg[i].value;
		_timer_stop(channel, parameterId);
		currentValue = _zunoWindowCoveringGet(channel, parameterId);
		if (currentValue != targetValue ) {
			if (targetValue > currentValue) {
				step = duration / (targetValue - currentValue);
				flag = ZUNO_TIMER_TREA_DIMING_FLAG_MODE_UP;
			}
			else {
				step = duration / (currentValue - targetValue);
				flag = ZUNO_TIMER_TREA_DIMING_FLAG_MODE_DOWN;
			}
			if (step == 0x0) {
				__zunoWindowCoveringSet(channel, parameterId, targetValue);
				continue ;
			}
			if ((parameter = zunoTimerTreadDimingCreate()) == NULL)
				return (ZUNO_COMMAND_BLOCKED_FAIL);
			parameter->type = zunoTimerTreadDimingTypeWindowsCovering;
			parameter->channel = channel;
			parameter->flag = flag;
			parameter->parameterId = parameterId;
			parameter->current_value = currentValue;
			parameter->target_value = targetValue;
			parameter->step = step;
			parameter->ticks_end = (rtcc_micros() / 1000) + duration;
			zunoTimerTreadDimingAdd(parameter, options);
		}
		i++;
	}
	return (result);
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
	report = (ZW_WINDOW_COVERING_REPORT_FRAME *)frame_report->info.packet.cmd;
	// report->cmdClass = COMMAND_CLASS_WINDOW_COVERING; set in - fillOutgoingPacket
	// report->cmd = WINDOW_COVERING_REPORT; set in - fillOutgoingPacket
	frame_report->info.packet.len = sizeof(report[0x0]);
	_get_set(channel, report, parameterId);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _start_level_sdfdsfgsd(uint8_t channel, uint8_t parameterId, uint8_t duration, uint8_t targetValue, uint8_t flag, const ZUNOCommandHandlerOption_t *options) {
	uint8_t														currentValue;
	size_t														step;
	zunoTimerTreadDiming_t										*parameter;

	_timer_stop(channel, parameterId);
	step = (zuno_CCTimerTicksTable7(duration) / (0x63 + 1));
	if (step == 0x0) {
		__zunoWindowCoveringSet(channel, parameterId, targetValue);
		return (ZUNO_COMMAND_PROCESSED);
	}
	currentValue = _zunoWindowCoveringGet(channel, parameterId);
	if ((parameter = zunoTimerTreadDimingCreate()) == NULL)
		return (ZUNO_COMMAND_BLOCKED_FAIL);
	parameter->type = zunoTimerTreadDimingTypeWindowsCovering;
	parameter->channel = channel;
	parameter->parameterId = parameterId;
	parameter->flag = flag;
	parameter->current_value = currentValue;
	parameter->target_value = targetValue;
	parameter->step = step;
	if (flag == ZUNO_TIMER_TREA_DIMING_FLAG_MODE_UP)
		step = step * (targetValue - currentValue);
	else
		step = step * (currentValue - targetValue);
	parameter->ticks_end = (rtcc_micros() / 1000) + step;
	zunoTimerTreadDimingAdd(parameter, options);
	return (ZUNO_COMMAND_PROCESSED);
}

static int _start_level_change(uint8_t channel, const ZW_WINDOW_COVERING_START_LEVEL_CHANGE_FRAME *paket, const ZUNOCommandHandlerOption_t *options) {
	uint32_t													mask;
	uint8_t														parameterId;
	uint8_t														targetValue;
	uint8_t														flag;

	mask = _get_parameter_mask(channel);
	parameterId = paket->parameterId;
	if ((mask & (0x1 << parameterId)) == 0x0)
		return (ZUNO_COMMAND_BLOCKED_FAIL);
	if ((paket->properties1 & WINDOW_COVERING_START_LEVEL_CHANGE_PROPERTIES1_UP_DOWN_BIT_MASK) == 0) {// Dimming to up
		targetValue = 0x63;
		flag = ZUNO_TIMER_TREA_DIMING_FLAG_MODE_UP;
	}
	else {// Dimming to down
		targetValue = 0x0;
		flag = ZUNO_TIMER_TREA_DIMING_FLAG_MODE_DOWN;
	}
	return (_start_level_sdfdsfgsd(channel, parameterId, paket->duration, targetValue, flag, options));
}

static int _stop_level_change(uint8_t channel, const ZW_WINDOW_COVERING_STOP_LEVEL_CHANGE_FRAME *paket) {
	_timer_stop(channel, paket->parameterId);
	zuno_CCWindowCoveringStop(channel, paket->parameterId);
	return (ZUNO_COMMAND_PROCESSED);
}


int zuno_CCWindowCoveringHandler(uint8_t channel, const ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report, const ZUNOCommandHandlerOption_t *options) {
	int				rs;

	switch(ZW_CMD) {
		case WINDOW_COVERING_SUPPORTED_GET:
			rs = _supported_report(channel, frame_report);
			break ;
		case WINDOW_COVERING_SET:
			rs = _set(frame_report, channel, (const ZW_WINDOW_COVERING_SET_1BYTE_FRAME *)cmd->cmd, options);
			break ;
		case WINDOW_COVERING_GET:
			_zunoMarkChannelRequested(channel);
			rs = _get(channel, (const ZW_WINDOW_COVERING_GET_FRAME *)cmd->cmd, frame_report);
			break ;
		case WINDOW_COVERING_START_LEVEL_CHANGE:
			rs = _start_level_change(channel, (const ZW_WINDOW_COVERING_START_LEVEL_CHANGE_FRAME *)cmd->cmd, options);
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

int zuno_CCWindowCoveringReport(uint8_t channel, ZUNOCommandPacket_t *packet, const ZwWindowCoveringReport_t *info) {
	ZW_WINDOW_COVERING_REPORT_FRAME								*report;
	uint32_t													mask;
	uint8_t														parameterId;

	mask = _get_parameter_mask(channel);
	report = (ZW_WINDOW_COVERING_REPORT_FRAME *)&packet->packet.cmd[0x0];
	packet->packet.len = sizeof(report[0x0]);
	report->cmdClass = COMMAND_CLASS_WINDOW_COVERING;
	report->cmd = WINDOW_COVERING_REPORT;
	if (info == NULL) {
		parameterId = 0x0;
		while (mask != 0x0) {
			if ((mask & 0x1) != 0x0) {
				_get_set(channel, report, parameterId);
				zunoSendZWPacket(packet);
			}
			mask = mask >> 0x1;
			parameterId++;
		}
	}
	else {
		_get_set(channel, report, info->parameterId);
		zunoSendZWPacket(packet);
		if (info->parameterId != _get_default_parameter_id(channel))
			return (ZUNO_COMMAND_PROCESSED);
	}
	return (zuno_CCSwitchMultilevelReport(channel, packet));
}

void __zunoWindowCoveringSet(uint8_t channel, uint8_t parameterId, uint8_t value) {
	zuno_universalSetter2P(channel, parameterId, value);
}

void __zunoWindowCoveringBasicSet(uint8_t channel, uint8_t value) {
	uint32_t													mask;
	uint32_t													parameterId_mask;
	uint8_t														parameterId;

	mask = _get_parameter_mask(channel);
	parameterId = 0x0;
	while (mask != 0x0) {
		parameterId_mask = 0x1 << parameterId;
		if ((mask & parameterId_mask) != 0x0) {
			mask = mask ^ parameterId_mask;
			__zunoWindowCoveringSet(channel, parameterId, value);
		}
		parameterId++;
	}
}

uint8_t __zunoWindowCoveringBasicGet(uint8_t channel) {
	uint32_t													mask;
	uint8_t														parameterId;
	uint8_t														currentValue;

	mask = _get_parameter_mask(channel);
	parameterId = _get_default_parameter_id(channel);
	if ((mask & (0x1 << parameterId)) == 0x0)
		return (0x0);
	currentValue = _zunoWindowCoveringGet(channel, parameterId);
	return (currentValue);
}

void __zuno_CCWindowCoveringGetValues(uint8_t channel, uint8_t *current_value, uint8_t *duration_table_8, uint8_t *target_value) {
	if (_get_values(channel, _get_default_parameter_id(channel), current_value, duration_table_8, target_value) == true)
		return ;
	__zuno_CCSwitchMultilevelGetValues(channel, current_value, duration_table_8, target_value);
}

void __zuno_CCWindowCoveringDimingStop(uint8_t channel) {
	uint32_t													mask;
	uint32_t													parameterId_mask;
	uint8_t														parameterId;

	mask = _get_parameter_mask(channel);
	parameterId = 0x0;
	while (mask != 0x0) {
		parameterId_mask = 0x1 << parameterId;
		if ((mask & parameterId_mask) != 0x0) {
			mask = mask ^ parameterId_mask;
			zuno_CCWindowCoveringStop(channel, parameterId);
		}
		parameterId++;
	}
}

void __zuno_CCWindowCoveringTimerStop(uint8_t channel) {
	uint32_t													mask;
	uint32_t													parameterId_mask;
	uint8_t														parameterId;

	mask = _get_parameter_mask(channel);
	parameterId = 0x0;
	while (mask != 0x0) {
		parameterId_mask = 0x1 << parameterId;
		if ((mask & parameterId_mask) != 0x0) {
			mask = mask ^ parameterId_mask;
			_timer_stop(channel, parameterId);
		}
		parameterId++;
	}
	__zuno_CCSwitchMultilevelTimerStop(channel);
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