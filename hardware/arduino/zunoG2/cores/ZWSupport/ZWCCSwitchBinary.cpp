#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCTimer.h"
#include "ZWCCSwitchBinary.h"
#include "ZWCCSuperVision.h"
#include "LinkedList.h"

uint64_t rtcc_micros(void);

void __zuno_CCSwitchBinaryTimerStop(uint8_t channel) {
	zunoTimerTreadDimingStop(zunoTimerTreadDimingTypeSwitchBinary, channel);
}

static uint8_t _get_value(uint8_t channel) {
	uint8_t										currentValue;

	currentValue = __zuno_BasicUniversalGetter1P(channel) ? 0xFF : 0x00;
	return (currentValue);
}

void __zuno_CCSwitchBinaryGetValues(uint8_t channel, uint8_t *current_value, uint8_t *duration_table_8, uint8_t *target_value) {
	uint8_t										currentValue;

	currentValue = _get_value(channel);
	current_value[0x0] = currentValue;
	zunoTimerTreadDimingGetValues(zunoTimerTreadDimingTypeSwitchBinary, channel, currentValue, duration_table_8, target_value);
}

int zuno_CCSwitchBinaryReport(byte channel, ZUNOCommandPacket_t *packet) {
	ZwBasicBinaryReportFrame_t				*report;

	report = (ZwBasicBinaryReportFrame_t *)&packet->packet.cmd[0x0];
	__zuno_BasicUniversalGetCurrentValueDurationTargetValue(channel, &report->v2.currentValue, &report->v2.duration, &report->v2.targetValue);
	report->v2.cmdClass = COMMAND_CLASS_SWITCH_BINARY;
	report->v2.cmd = SWITCH_BINARY_REPORT;
	packet->packet.len = sizeof(report->v2);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _set(ZwSwitchBinarySetFrame_t *cmd, size_t len, size_t channel, ZUNOCommandPacketReport_t *frame_report, const ZUNOCommandCmd_t *packet, const ZUNOCommandHandlerOption_t *options) {
	uint8_t							targetValue;
	size_t							duration;
	uint8_t							currentValue;
	zunoTimerTreadDiming_t			*parameter;

	if ((targetValue = cmd->v2.targetValue) > 0x63 && targetValue < 0xFF)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	targetValue = targetValue ? 0xFF : 0x00;// Map the value right way
	currentValue =_get_value(channel);
	if (currentValue == targetValue) {
		return (ZUNO_COMMAND_PROCESSED);
	}
	__zuno_BasicUniversalTimerStop(channel);
	switch (len) {
		case sizeof(cmd->v2):
			if ((duration = (zuno_CCTimerTicksTable7(cmd->v2.duration))) == 0x0)
				break ;
			if ((parameter = zunoTimerTreadDimingCreate()) == NULL)
				return (ZUNO_COMMAND_BLOCKED_FAILL);
			if (zuno_CCSupervisionReportSyncWorking(frame_report, cmd->v2.duration) == true) {
				parameter->flag = ZUNO_TIMER_TREA_DIMING_FLAG_SUPERVISION;
				zuno_CCSupervisionAsyncProcessedSet(packet, &parameter->super_vision);
			}
			else
				parameter->flag = 0x0;
			parameter->channel = channel;
			parameter->ticks_end = (rtcc_micros() / 1000) + duration;
			parameter->target_value = targetValue;
			parameter->type = zunoTimerTreadDimingTypeSwitchBinary;
			zunoTimerTreadDimingAdd(parameter);
			return (ZUNO_COMMAND_PROCESSED);
			break ;
		default:
			break ;
	}
	__zuno_BasicUniversalSetter1P(channel, targetValue);
	zunoSendReportSet(channel, options);
	return (ZUNO_COMMAND_PROCESSED);
}

int zuno_CCSwitchBinaryHandler(byte channel, const ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report, const ZUNOCommandHandlerOption_t *options) {
	int							rs;

	switch(ZW_CMD) {
		case SWITCH_BINARY_GET:
			rs = zuno_CCSwitchBinaryReport(channel, &frame_report->info);
			_zunoMarkChannelRequested(channel);
			break;
		case SWITCH_BINARY_SET:
			rs = _set((ZwSwitchBinarySetFrame_t *)cmd->cmd, cmd->len, channel, frame_report, cmd, options);
			break;
		default:
			rs = ZUNO_COMMAND_BLOCKED_NO_SUPPORT;
			break ;
	}
	return (rs);
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