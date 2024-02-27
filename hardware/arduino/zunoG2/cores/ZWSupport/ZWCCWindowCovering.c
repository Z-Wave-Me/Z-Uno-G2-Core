#include "Arduino.h"
#include "ZWCCWindowCovering.h"
#include "ZWCCSwitchMultilevel.h"
#include "ZWCCSuperVision.h"

typedef struct					ZunoWindowCoveringDuration_s {
	uint8_t						targetValue;
	uint8_t						currentValue;
	uint8_t						channel;
	uint8_t						parameterId;
	struct
	{
		uint32_t				diming: 1;
		uint32_t				step: 31;
	};
	uint32_t					ticks;
}								ZunoWindowCoveringDuration_t;

static ZunoWindowCoveringDuration_t _duration[0x10];

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

static void _start_level_set(uint8_t channel, uint8_t current_level, uint8_t targetValue, uint8_t parameterId, size_t step, uint8_t diming, uint8_t duration, ZUNOCommandPacketReport_t *frame_report) {
	ZunoTimerBasic_t								*lp;
	ZunoWindowCoveringDuration_t					*lpDur_b;
	ZunoWindowCoveringDuration_t					*lpDur_e;
	size_t											tempos;

	if (step == 0x0) {
		zuno_universalSetter2P(channel, parameterId, targetValue);
		return ;
	}
	zunoEnterCritical();
	if ((lp = zuno_CCTimerBasicFind(channel)) != 0x0) {
		lpDur_b = &_duration[0x0];
		lpDur_e = &_duration[(sizeof(_duration) / sizeof(_duration[0x0]))];
		tempos = channel + 0x1;
		while (lpDur_b < lpDur_e) {
			if (lpDur_b->channel == tempos && lpDur_b->parameterId == parameterId)
				break ;
			lpDur_b++;
		}
		if (lpDur_b == lpDur_e) {
			lpDur_b = &_duration[0];
			while (lpDur_b < lpDur_e) {
				if (lpDur_b->channel == 0x0) {
					g_sleep_data.latch++;
					break ;
				}
				lpDur_b++;
			}
		}
		if (lpDur_b != lpDur_e) {
			lp->bMode = ZUNO_TIMER_SWITCH_NO_BASIC;
			lp->channel = tempos;
			lpDur_b->channel = tempos;
			lpDur_b->diming = diming;
			lpDur_b->step = step;
			lpDur_b->ticks = millis();
			lpDur_b->parameterId = parameterId;
			lpDur_b->currentValue = current_level;
			lpDur_b->targetValue = targetValue;
			zunoExitCritical();
			zuno_CCSupervisionReport(ZUNO_COMMAND_PROCESSED, 0, 0, frame_report);
			zunoEnterCritical();
		}
	}
	zunoExitCritical();
	(void)duration;
}

static void _set_duration_0(uint8_t channel, const VG_WINDOW_COVERING_SET_VG *vg, uint8_t count) {
	size_t														tempos;
	uint8_t														i;
	uint8_t														parameterId;
	ZunoWindowCoveringDuration_t								*lpDur_b;
	ZunoWindowCoveringDuration_t								*lpDur_e;

	zunoEnterCritical();
	tempos = channel + 0x1;
	i = 0x0;
	while (i < count) {
		parameterId = vg[i].parameterId;
		if ((parameterId & 0x1) != 0x0) {
			lpDur_b = &_duration[0x0];
			lpDur_e = &_duration[(sizeof(_duration) / sizeof(_duration[0x0]))];
			while (lpDur_b < lpDur_e) {
				if (lpDur_b->channel == tempos && lpDur_b->channel == parameterId) {
					lpDur_b->channel = 0x0;
					break ;
				}
				lpDur_b++;
			}
		}
		i++;
	}
	lpDur_b = &_duration[0x0];
	lpDur_e = &_duration[(sizeof(_duration) / sizeof(_duration[0x0]))];
	i = 0x0;
	while (lpDur_b < lpDur_e) {
		if (lpDur_b->channel == tempos) {
			i++;
			break ;
		}
		lpDur_b++;
	}
	if (i != 0x0)
		zuno_CCTimerBasicFindStop(channel);
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
	uint8_t														diming;
	uint8_t														currentValue;
	uint8_t														targetValue;
	uint8_t														duration_encode;

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
				diming = 0x0;
			}
			else {
				step = duration / (currentValue - targetValue);
				diming = 0x1;
			}
			_start_level_set(channel, currentValue, targetValue, parameterId, step, diming, duration_encode, frame_report);
		}
		i++;
	}
	return (ZUNO_COMMAND_PROCESSED);
}

static void _get_set(uint8_t channel, ZW_WINDOW_COVERING_REPORT_FRAME *report, uint8_t parameterId) {
	ZunoWindowCoveringDuration_t								*lpDur_b;
	ZunoWindowCoveringDuration_t								*lpDur_e;
	size_t														tempos;
	uint8_t														currentValue;
	uint8_t														targetValue;
	uint8_t														duration;

	report->parameterId = parameterId;
	zunoEnterCritical();
	lpDur_b = &_duration[0x0];
	lpDur_e = &_duration[(sizeof(_duration) / sizeof(_duration[0x0]))];
	tempos = channel + 0x1;
	while (lpDur_b < lpDur_e) {
		if (lpDur_b->channel == tempos && lpDur_b->channel == parameterId) {
			lpDur_b->channel = 0x0;
			break ;
		}
		lpDur_b++;
	}
	zunoExitCritical();
	if (lpDur_b == lpDur_e) {
		targetValue = 0x0;
		if ((parameterId & 0x1) == 0x0)
			duration = 0xFE;
		else
			duration = 0x0;
	}
	else {
		targetValue = lpDur_b->targetValue;
		currentValue = lpDur_b->currentValue;
		if (targetValue > currentValue)
			currentValue = targetValue - currentValue;
		else
			currentValue = currentValue - targetValue;
		duration = zuno_CCTimerTable8(currentValue * lpDur_b->step);
	}
	currentValue = zuno_universalGetter2P(channel, parameterId);
	if (duration == 0x0)
		targetValue = currentValue;
	report->currentValue = currentValue;
	report->targetValue = targetValue;
	report->duration = duration;
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

static int _start_level_change(uint8_t channel, const ZW_WINDOW_COVERING_START_LEVEL_CHANGE_FRAME *paket, ZUNOCommandPacketReport_t *frame_report) {
	uint32_t													mask;
	uint8_t														parameterId;
	size_t														step;
	uint8_t														currentValue;
	uint8_t														targetValue;
	uint8_t														diming;

	
	mask = _get_parameter_mask(channel);
	parameterId = paket->parameterId;
	if ((mask & (0x1 << parameterId)) == 0x0)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	currentValue = zuno_universalGetter2P(channel, parameterId);
	if ((paket->properties1 & WINDOW_COVERING_START_LEVEL_CHANGE_PROPERTIES1_UP_DOWN_BIT_MASK) == 0) {// Dimming to up
		targetValue = 0x63;
		diming = 0x0;
	}
	else {// Dimming to down
		targetValue = 0x0;
		diming = 0x1;
	}
	step = (zuno_CCTimerTicksTable7(paket->duration) / (0x63 + 1));
	_start_level_set(channel, currentValue, targetValue, parameterId, step, diming, paket->duration, frame_report);
	return (ZUNO_COMMAND_PROCESSED);
}

__WEAK void zuno_CCWindowCoveringStop(uint8_t channel, uint8_t parameterId) {
	(void)channel;
	(void)parameterId;
}

static int _stop_level_change(uint8_t channel, const ZW_WINDOW_COVERING_STOP_LEVEL_CHANGE_FRAME *paket) {
	ZunoTimerBasic_t								*lp;
	ZunoWindowCoveringDuration_t					*lpDur_b;
	ZunoWindowCoveringDuration_t					*lpDur_e;
	size_t											count;
	uint8_t											parameterId;
	bool											b_stop;

	parameterId = paket->parameterId;
	zunoEnterCritical();
	b_stop = false;
	channel++;
	if ((lp = zuno_CCTimerBasicFind(channel)) != 0x0) {
		lpDur_b = &_duration[0x0];
		lpDur_e = &_duration[(sizeof(_duration) / sizeof(_duration[0x0]))];
		count = 0x0;
		while (lpDur_b < lpDur_e) {
			if (lpDur_b->channel == channel) {
				if (lpDur_b->parameterId == parameterId) {
					lpDur_b->channel = 0x0;
					g_sleep_data.latch--;
					b_stop = true;
					break ;
				}
				else
					count++;
			}
			lpDur_b++;
		}
		if (count == 0x0) {
			while (lpDur_b < lpDur_e) {
				if (lpDur_b->channel == channel) {
					count++;
					break ;
				}
				lpDur_b++;
			}
		}
		if (count == 0x0)
			lp->channel = 0x0;
	}
	zunoExitCritical();
	if (b_stop == true)
		zuno_CCWindowCoveringStop(channel - 0x1, parameterId);
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

void zuno_CCWindowCoveringTimer(ZunoTimerBasic_t *lp, ZUNOCommandPacketReport_t *frame_report) {
	size_t									bMode;
	size_t									channel;
	ssize_t									value;
	size_t									count;
	size_t									tempos;
	size_t									step;
	ZunoWindowCoveringDuration_t			*lpDur_b;
	ZunoWindowCoveringDuration_t			*lpDur_e;
	size_t									ticks;

	if ((bMode = lp->bMode) == 0x0)
		return ;
	channel = lp->channel;
	lpDur_b = &_duration[0x0];
	lpDur_e = &_duration[(sizeof(_duration) / sizeof(_duration[0x0]))];
	count = 0x0;
	while (lpDur_b < lpDur_e) {
		if (lpDur_b->channel == channel) {
			ticks = millis();
			count++;
			step = lpDur_b->step;
			if ((tempos = lpDur_b->ticks + step) <= ticks) {
				ticks = ticks - tempos;
				lpDur_b->ticks = tempos + (ticks % step);
				ticks = ticks / step + 0x1;
				value = lpDur_b->currentValue;
				if (lpDur_b->diming == 0x0) {
					value += ticks;
					if (value >= lpDur_b->targetValue) {
						lpDur_b->channel = 0x0;
						g_sleep_data.latch--;
						count--;
					}
				}
				else {
					value -= ticks;
					if (value <= lpDur_b->targetValue) {
						lpDur_b->channel = 0x0;
						g_sleep_data.latch--;
						count--;
					}
				}
				lpDur_b->currentValue = value;
				zuno_universalSetter2P(channel - 1, lpDur_b->parameterId, value);
				zunoSendReport(channel);
			}
		}
		lpDur_b++;
	}
	if (count == 0x0) {
		lp->channel = 0x0;
		if ((lp->bMode & ZUNO_TIMER_SWITCH_SUPERVISION) != 0x0) {
			__cc_supervision._unpacked = true;
			fillOutgoingReportPacketAsync(frame_report, ZUNO_CFG_CHANNEL(channel - 1).zw_channel);
			zuno_CCSupervisionReport(ZUNO_COMMAND_PROCESSED, 0x0, 0x0, frame_report);
		}
	}
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