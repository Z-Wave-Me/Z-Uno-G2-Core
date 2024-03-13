#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCTimer.h"
#include "ZWCCSwitchMultilevel.h"
#include "ZWCCBasic.h"
#include "ZWCCSuperVision.h"
#include "LinkedList.h"

uint64_t rtcc_micros(void);

void __zuno_CCSwitchMultilevelTimerStop(uint8_t channel) {
	zunoTimerTreadDimingStop(zunoTimerTreadDimingTypeSwitchMultilevel, channel);
}

void __zuno_CCSwitchMultilevelGetValues(uint8_t channel, uint8_t *current_value, uint8_t *duration_table_8, uint8_t *target_value) {
	uint8_t												currentValue;

	currentValue = __zuno_BasicUniversalGetter1P(channel);
	if(currentValue > ZUNO_TIMER_SWITCH_MAX_VALUE)
		currentValue = ZUNO_TIMER_SWITCH_MAX_VALUE;
	current_value[0x0] = currentValue;
	zunoTimerTreadDimingGetValues(zunoTimerTreadDimingTypeSwitchMultilevel, channel, currentValue, duration_table_8, target_value);
}

static int _start_level(uint8_t channel, ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report) {// Prepare the structure for dimming
	ZwSwitchMultilevelStartLevelChangeFrame_t			*pk;
	uint32_t											step;
	uint8_t												current_level;
	uint8_t												targetValue;
	uint8_t												flag;
	uint8_t												duration;
	zunoTimerTreadDiming_t								*parameter;

	pk = (ZwSwitchMultilevelStartLevelChangeFrame_t *)cmd->cmd;
	if ((pk->v1.properties1 & (1 << 5)) == 0) {// If the level from which you want to start dimming has come, make it current
		if ((current_level = pk->v1.startLevel) > ZUNO_TIMER_SWITCH_MAX_VALUE)
			current_level = ZUNO_TIMER_SWITCH_MAX_VALUE;
		if (current_level != 0x0)
			zunoBasicSaveSet(channel, &current_level);
		__zuno_BasicUniversalSetter1P(channel, current_level);
		zunoSendReport(channel + 1);
	} else {// Otherwise, get the current
		if ((current_level = __zuno_BasicUniversalGetter1P(channel)) > ZUNO_TIMER_SWITCH_MAX_VALUE)
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
			return (ZUNO_COMMAND_PROCESSED);
		if (step == 0) {// If the step turned out to be zero - immediately set the desired level
			zunoSendReport(channel + 1);
			__zuno_BasicUniversalSetter1P(channel, ZUNO_TIMER_SWITCH_MAX_VALUE);
			return (ZUNO_COMMAND_PROCESSED);
		}
		flag = ZUNO_TIMER_TREA_DIMING_FLAG_MODE_UP;
		targetValue = ZUNO_TIMER_SWITCH_MAX_VALUE;
	} else {// Dimming to down
		if (current_level == ZUNO_TIMER_SWITCH_MIN_VALUE)// Check it may not need to dim
			return (ZUNO_COMMAND_PROCESSED);
		if (step == 0) {// If the step turned out to be zero - immediately set the desired level
			zunoSendReport(channel + 1);
			__zuno_BasicUniversalSetter1P(channel, ZUNO_TIMER_SWITCH_MIN_VALUE);
			return (ZUNO_COMMAND_PROCESSED);
		}
		targetValue = ZUNO_TIMER_SWITCH_MIN_VALUE;
		flag = ZUNO_TIMER_TREA_DIMING_FLAG_MODE_DOWN;
	}
	if (targetValue == current_level)
		return (ZUNO_COMMAND_PROCESSED);
	__zuno_BasicUniversalTimerStop(channel);
	step = step / (ZUNO_TIMER_SWITCH_MAX_VALUE + 0x1);
	if ((parameter = zunoTimerTreadDimingCreate()) == NULL)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	parameter->channel = channel;
	parameter->type = zunoTimerTreadDimingTypeSwitchMultilevel;
	parameter->step = step;
	if (flag == ZUNO_TIMER_TREA_DIMING_FLAG_MODE_UP)
		step = step * (targetValue - current_level);
	else
		step = step * (current_level - targetValue);
	parameter->ticks_end = (rtcc_micros() / 1000) + step;
	parameter->current_value = current_level;
	parameter->target_value = targetValue;
	if (zuno_CCSupervisionReportSyncWorking(frame_report, duration) == true) {
		flag = flag | ZUNO_TIMER_TREA_DIMING_FLAG_SUPERVISION;
		zuno_CCSupervisionAsyncProcessedSet(cmd, &parameter->super_vision);
	}
	parameter->flag = flag;
	zunoTimerTreadDimingAdd(parameter);
	return (ZUNO_COMMAND_PROCESSED);
}

int zuno_CCSwitchMultilevelReport(byte channel, ZUNOCommandPacket_t *packet) {
	SwitchMultilevelReportFrame_t			*report;

	report = (SwitchMultilevelReportFrame_t *)&packet->cmd[0x0];
	__zuno_BasicUniversalGetCurrentValueDurationTargetValue(channel, &report->v4.currentValue, &report->v4.duration, &report->v4.targetValue);
	report->v4.cmdClass = COMMAND_CLASS_SWITCH_MULTILEVEL;
	report->v4.cmd = SWITCH_MULTILEVEL_REPORT;
	packet->len = sizeof(report->v4);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _set(SwitchMultilevelSetFrame_t *cmd, uint8_t len, uint8_t channel, ZUNOCommandPacketReport_t *frame_report, ZUNOCommandPacket_t *packet) {
	uint32_t						step;
	size_t							duration;
	uint8_t							value;
	uint8_t							val_basic;
	uint8_t							currentValue;
	zunoTimerTreadDiming_t			*parameter;

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
	currentValue = __zuno_BasicUniversalGetter1P(channel);
	if(currentValue > ZUNO_TIMER_SWITCH_MAX_VALUE)
		currentValue = ZUNO_TIMER_SWITCH_MAX_VALUE;
	if (currentValue == value) {
		return (ZUNO_COMMAND_PROCESSED);
	}
	__zuno_BasicUniversalTimerStop(channel);
	switch (len) {
		case sizeof(cmd->v4):
			if ((duration = zuno_CCTimerTicksTable7(cmd->v4.dimmingDuration)) == 0x0) {
				break ;
			}
			if ((parameter = zunoTimerTreadDimingCreate()) == NULL)
				return (ZUNO_COMMAND_BLOCKED_FAILL);
			if (zuno_CCSupervisionReportSyncWorking(frame_report, cmd->v4.dimmingDuration) == true) {
				parameter->flag = ZUNO_TIMER_TREA_DIMING_FLAG_SUPERVISION;
				zuno_CCSupervisionAsyncProcessedSet(packet, &parameter->super_vision);
			}
			else
				parameter->flag = 0x0;
			if (value > currentValue) {
				step = duration / (value - currentValue);
				parameter->flag = parameter->flag | ZUNO_TIMER_TREA_DIMING_FLAG_MODE_UP;
			}
			else {
				step = duration / (currentValue - value);
				parameter->flag = parameter->flag | ZUNO_TIMER_TREA_DIMING_FLAG_MODE_DOWN;
			}
			parameter->step = step;
			parameter->current_value = currentValue;
			parameter->ticks_end = (rtcc_micros() / 1000) + duration;
			parameter->target_value = value;
			parameter->type = zunoTimerTreadDimingTypeSwitchMultilevel;
			parameter->channel = channel;
			zunoTimerTreadDimingAdd(parameter);
			return (ZUNO_COMMAND_PROCESSED);
			break ;
		default:
			break ;
	}
	__zuno_BasicUniversalSetter1P(channel, value);
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
	__zuno_BasicUniversalTimerStop(channel);
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
			rs = _set((SwitchMultilevelSetFrame_t *)cmd->cmd, cmd->len, channel, frame_report, cmd);
			break ;
		case SWITCH_MULTILEVEL_START_LEVEL_CHANGE:
			{
				ZwSwitchMultilevelStartLevelChangeFrame_t * pk = (ZwSwitchMultilevelStartLevelChangeFrame_t *)cmd->cmd;
				zcustom_SWLStartStopHandler(channel, 
											  true, 
											  (pk->v1.properties1 & (1 << 6)) == 0, 
											  (uint8_t*) cmd);
			}
			rs = _start_level(channel, cmd, frame_report);
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

#include "ZWCCZWavePlusInfo.h"

void zuno_CCSwitchMultilevelGetIcon(ZwZwavePlusInfoIcon_t *icon) {
	uint16_t								installerIconType;
	uint16_t								userIconType;

	installerIconType = ICON_TYPE_GENERIC_LIGHT_DIMMER_SWITCH;
	userIconType = ICON_TYPE_GENERIC_LIGHT_DIMMER_SWITCH;
	icon->installerIconType = installerIconType;
	icon->userIconType = userIconType;
}

void zuno_CCSwitchMultilevelGetType(uint8_t channel, ZwZwavePlusInfoType_t *type) {
	type->genericDeviceClass = GENERIC_TYPE_SWITCH_MULTILEVEL;
	type->specificDeviceClass = ZUNO_CFG_CHANNEL(channel).sub_type;
}