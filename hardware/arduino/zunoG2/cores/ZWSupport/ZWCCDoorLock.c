#include "Arduino.h"
#include "ZWCCTimer.h"
#include "ZWCCDoorLock.h"

#ifdef WITH_CC_DOORLOCK
typedef union							ZwDoorLockProperties_u
{
	uint8_t								properties;
	struct
	{
		uint8_t							InsideDoorHandlesMode: 0x2;
		uint8_t							OutsideDoorHandlesMode: 0x2;
	};
}										ZwDoorLockProperties_t;

typedef union							ZwDoorLockPropertiesSave_u
{
	uint8_t								properties_save;
	struct
	{
		uint8_t							InsideDoorHandlesMode: 0x2;
		uint8_t							OutsideDoorHandlesMode: 0x2;
		uint8_t							operationType: 0x4;
	};
}										ZwDoorLockPropertiesSave_t;

#define DOOR_LOCK_GET_PROPERTIES(channel, struct)					struct.properties = ZUNO_CFG_CHANNEL(channel).params[0x0]

#define DOOR_LOCK_GET_PROPERTIES_SAVE(channel, struct)				struct.properties_save = ZUNO_CFG_CHANNEL(channel).params[0x1]
#define DOOR_LOCK_SET_PROPERTIES_SAVE(channel, struct)				ZUNO_CFG_CHANNEL(channel).params[0x1] = struct.properties_save
#define DOOR_LOCK_TIMEOUT_MINUTES_SAVE(channel)						ZUNO_CFG_CHANNEL(channel).params[0x2]
#define DOOR_LOCK_TIMEOUT_SECONDS_SAVE(channel)						ZUNO_CFG_CHANNEL(channel).params[0x3]


static int _report_configuration(uint8_t channel, ZUNOCommandPacketReport_t *frame_report) {
	ZwDoorLockConfigurationReportFrame_t		*lp;
	ZwDoorLockPropertiesSave_t					properties_save;

	lp = (ZwDoorLockConfigurationReportFrame_t *)frame_report->packet.cmd;
	// lp->v4.cmdClass = COMMAND_CLASS_DOOR_LOCK; set in - fillOutgoingPacket
	// lp->v4.cmd = DOOR_LOCK_CONFIGURATION_REPORT; set in - fillOutgoingPacket
	DOOR_LOCK_GET_PROPERTIES_SAVE(channel, properties_save);
	if ((lp->v4.operationType = properties_save.operationType) == DOOR_LOCK_CONFIGURATION_SET_CONSTANT_OPERATION_V4)
		zuno_CCTimerBasicFindStop(channel);
	lp->v4.properties1 = properties_save.InsideDoorHandlesMode | (properties_save.OutsideDoorHandlesMode << DOOR_LOCK_CONFIGURATION_SET_PROPERTIES1_OUTSIDE_DOOR_HANDLES_STATE_SHIFT_V4);
	lp->v4.lockTimeoutMinutes = DOOR_LOCK_TIMEOUT_MINUTES_SAVE(channel);
	lp->v4.lockTimeoutSeconds = DOOR_LOCK_TIMEOUT_SECONDS_SAVE(channel);
	lp->v4.holdAndReleaseTime1 = 0x0;
	lp->v4.holdAndReleaseTime2 = 0x0;
	lp->v4.autoRelockTime1 = 0x0;
	lp->v4.autoRelockTime2 = 0x0;
	frame_report->packet.len = sizeof(lp->v4);
	return (ZUNO_COMMAND_ANSWERED);
	(void)channel;
}

static int _set_operation(size_t channel, const ZwDoorLockOperationSet_t *cmd) {
	ZwDoorLockPropertiesSave_t					properties_save;
	size_t										doorLockMode;
	size_t										duration;
	size_t										lockTimeoutMinutes;
	size_t										lockTimeoutSeconds;
	ZunoTimerBasic_t							*lp;

	DOOR_LOCK_GET_PROPERTIES_SAVE(channel, properties_save);
	doorLockMode = cmd->doorLockMode;
	switch (properties_save.operationType) {
		case DOOR_LOCK_CONFIGURATION_SET_CONSTANT_OPERATION_V4:
			switch (doorLockMode) {
				case DOOR_LOCK_OPERATION_REPORT_DOOR_UNSECURED_V4:
				case DOOR_LOCK_OPERATION_REPORT_DOOR_SECURED_V4:
				case DOOR_LOCK_OPERATION_REPORT_DOOR_UNSECURED_FOR_INSIDE_DOOR_HANDLES_V4:
				case DOOR_LOCK_OPERATION_REPORT_DOOR_UNSECURED_FOR_OUTSIDE_DOOR_HANDLES_V4:
					break ;
				default:
					return (ZUNO_COMMAND_BLOCKED);
					break ;
			}
			break ;
		case DOOR_LOCK_CONFIGURATION_SET_TIMED_OPERATION_V4:
			lockTimeoutMinutes = DOOR_LOCK_TIMEOUT_MINUTES_SAVE(channel);
			lockTimeoutSeconds = DOOR_LOCK_TIMEOUT_SECONDS_SAVE(channel);
			if (lockTimeoutMinutes != DOOR_LOCK_OPERATION_REPORT_UNKNOWN_DURATION_V4 && lockTimeoutSeconds != DOOR_LOCK_OPERATION_REPORT_UNKNOWN_DURATION_V4) {
				switch (doorLockMode) {
					case DOOR_LOCK_OPERATION_REPORT_DOOR_UNSECURED_WITH_TIMEOUT_V4:
					case DOOR_LOCK_OPERATION_REPORT_DOOR_UNSECURED_FOR_INSIDE_DOOR_HANDLES_WITH_TIMEOUT_V4:
					case DOOR_LOCK_OPERATION_REPORT_DOOR_UNSECURED_FOR_OUTSIDE_DOOR_HANDLES_WITH_TIMEOUT_V4:
						if ((duration = (lockTimeoutMinutes * 60 + lockTimeoutSeconds) * (1000)) == 0x0) {
							doorLockMode = DOOR_LOCK_OPERATION_REPORT_DOOR_SECURED_V4;
							zuno_CCTimerBasicFindStop(channel);
							break ;
						}
						zunoEnterCritical();
						if ((lp = zuno_CCTimerBasicFind(channel)) != 0x0) {
							lp->channel = channel + 0x1;
							lp->ticksEnd = millis() + duration;
						}
						zunoExitCritical();
						break ;
					default:
						zuno_CCTimerBasicFindStop(channel);
						break ;
				}
			}
			else
				zuno_CCTimerBasicFindStop(channel);
			break ;
		default:
			return (ZUNO_COMMAND_BLOCKED);
			break ;
	}
	zuno_universalSetter1P(channel, doorLockMode);
	zunoSendReport(channel + 0x1);
	return (ZUNO_COMMAND_PROCESSED);
}


static uint8_t *_capabilities_get_set_mode(size_t channel, uint8_t *report) {
	report++[0] = DOOR_LOCK_OPERATION_REPORT_DOOR_UNSECURED_V4;
	report++[0] = DOOR_LOCK_OPERATION_REPORT_DOOR_SECURED_V4;
	report++[0] = DOOR_LOCK_OPERATION_REPORT_DOOR_UNSECURED_WITH_TIMEOUT_V4;
	report++[0] = DOOR_LOCK_OPERATION_REPORT_DOOR_UNSECURED_FOR_INSIDE_DOOR_HANDLES_V4;
	report++[0] = DOOR_LOCK_OPERATION_REPORT_DOOR_UNSECURED_FOR_INSIDE_DOOR_HANDLES_WITH_TIMEOUT_V4;
	report++[0] = DOOR_LOCK_OPERATION_REPORT_DOOR_UNSECURED_FOR_OUTSIDE_DOOR_HANDLES_V4;
	report++[0] = DOOR_LOCK_OPERATION_REPORT_DOOR_UNSECURED_FOR_OUTSIDE_DOOR_HANDLES_WITH_TIMEOUT_V4;
	return (report);
	(void)channel;
}

static uint8_t *_capabilities_get_set_operation(size_t channel, uint8_t *report) {
	report++[0] = (0x1 << DOOR_LOCK_CONFIGURATION_SET_CONSTANT_OPERATION_V4) | (0x1 << DOOR_LOCK_CONFIGURATION_SET_TIMED_OPERATION_V4);
	return (report);
	(void)channel;
}

static int _capabilities_get(size_t channel, ZUNOCommandPacketReport_t *frame_report) {
	uint8_t					*report;
	uint8_t					*properties1;
	uint8_t					*supportedDoorLockModeListLength;
	size_t					tempos;
	ZwDoorLockProperties_t	properties;

	report = frame_report->packet.cmd + 0x2;//cmdClass + cmd// COMMAND_CLASS_DOOR_LOCK DOOR_LOCK_CAPABILITIES_REPORT ; set in - fillOutgoingPacket
	properties1 = report;
	report = _capabilities_get_set_operation(channel, report + 0x1);
	tempos = report - properties1 - 0x1;
	properties1[0] = tempos;
	supportedDoorLockModeListLength = report;
	report = _capabilities_get_set_mode(channel, report + 0x1);
	tempos = report - supportedDoorLockModeListLength - 0x1;
	supportedDoorLockModeListLength[0] = tempos;
	DOOR_LOCK_GET_PROPERTIES(channel, properties);
	report++[0] = properties.InsideDoorHandlesMode | (properties.OutsideDoorHandlesMode << DOOR_LOCK_CONFIGURATION_SET_PROPERTIES1_OUTSIDE_DOOR_HANDLES_STATE_SHIFT_V4);//properties2
	report++[0] = 0x0;//supportedDoorComponents//Supported Door components (8 bits)
	report++[0] = 0x0;//properties3//ARS (Auto-Relock support) (1 bit)//HRS (Hold and release support) (1 bit)//TAS (Twist assist support) (1 bit)//BTBS (Block-to-block support) (1 bit)
	frame_report->packet.len = report - frame_report->packet.cmd;
	return (ZUNO_COMMAND_ANSWERED);

}

static int _configuration_set(size_t channel, const ZwDoorLockConfigurationSetFrame_t *cmd, size_t len) {
	size_t								properties1;
	size_t								lockTimeoutMinutes;
	size_t								lockTimeoutSeconds;
	ZwDoorLockPropertiesSave_t			properties_save;
	size_t								operationType;

	switch (len) {
		case sizeof(cmd->v4):
			if (cmd->v4.autoRelockTime2 != 0x0 || cmd->v4.autoRelockTime1 != 0x0 || cmd->v4.properties2 != 0x0 || cmd->v4.holdAndReleaseTime1 != 0x0 || cmd->v4.holdAndReleaseTime2 != 0x0 )
				return (ZUNO_COMMAND_BLOCKED_FAILL);
			break ;
		default:
			break ;
	}
	operationType = cmd->v3.operationType;
	lockTimeoutMinutes = cmd->v3.lockTimeoutMinutes;
	lockTimeoutSeconds = cmd->v3.lockTimeoutSeconds;
	switch (operationType) {
		case DOOR_LOCK_CONFIGURATION_REPORT_CONSTANT_OPERATION_V4:
			if (lockTimeoutMinutes != 0xFE || lockTimeoutSeconds != 0xFE)
				return (ZUNO_COMMAND_BLOCKED_FAILL);
			break ;
		case DOOR_LOCK_CONFIGURATION_REPORT_TIMED_OPERATION_V4:
			if (lockTimeoutMinutes == 0xFE && lockTimeoutSeconds == 0xFE)
				break ;
			if (lockTimeoutMinutes > 0xFD || lockTimeoutSeconds > 0x3B)
				return (ZUNO_COMMAND_BLOCKED_FAILL);
			break ;
	}
	properties1 = cmd->v3.properties1;
	properties_save.operationType = operationType;
	properties_save.InsideDoorHandlesMode = properties1;
	properties_save.OutsideDoorHandlesMode = properties1 >> DOOR_LOCK_CONFIGURATION_SET_PROPERTIES1_OUTSIDE_DOOR_HANDLES_STATE_SHIFT_V4;
	DOOR_LOCK_SET_PROPERTIES_SAVE(channel, properties_save);
	DOOR_LOCK_TIMEOUT_MINUTES_SAVE(channel) = lockTimeoutMinutes;
	DOOR_LOCK_TIMEOUT_SECONDS_SAVE(channel) = lockTimeoutSeconds;
	return (ZUNO_COMMAND_PROCESSED);
}

int zuno_CCDoorLockHandler(uint8_t channel, ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	int											rs;
	ZwDoorLockPropertiesSave_t					properties_save;
	ZwDoorLockProperties_t						properties;

	DOOR_LOCK_GET_PROPERTIES_SAVE(channel, properties_save);
	if (properties_save.properties_save == 0x0) {
		DOOR_LOCK_GET_PROPERTIES(channel, properties);
		properties_save.properties_save = properties.properties;
		properties_save.operationType = DOOR_LOCK_CONFIGURATION_SET_CONSTANT_OPERATION_V4;
		DOOR_LOCK_SET_PROPERTIES_SAVE(channel, properties_save);
		DOOR_LOCK_TIMEOUT_MINUTES_SAVE(channel) = DOOR_LOCK_OPERATION_REPORT_UNKNOWN_DURATION_V4;
		DOOR_LOCK_TIMEOUT_SECONDS_SAVE(channel) = DOOR_LOCK_OPERATION_REPORT_UNKNOWN_DURATION_V4;
	}
	switch(ZW_CMD) {
		case DOOR_LOCK_CONFIGURATION_SET:
			rs = _configuration_set(channel, (const ZwDoorLockConfigurationSetFrame_t *)cmd->cmd, cmd->len);
			break ;
		case DOOR_LOCK_CONFIGURATION_GET:
			rs = _report_configuration(channel, frame_report);
			break ;
		case DOOR_LOCK_OPERATION_GET:
			rs = zuno_CCDoorLockReport(channel, &frame_report->packet);
			_zunoMarkChannelRequested(channel);
			break ;
		case DOOR_LOCK_OPERATION_SET:
			rs = _set_operation(channel, (const ZwDoorLockOperationSet_t *)cmd->cmd);
			break ;
		case DOOR_LOCK_CAPABILITIES_GET:
			rs = _capabilities_get(channel, frame_report);
			break ;
		default:
			rs = ZUNO_COMMAND_BLOCKED_NO_SUPPORT;
			break ;
	}
	return (rs);
}

int zuno_CCDoorLockReport(uint8_t channel, ZUNOCommandPacket_t *packet) {
	ZwDoorLockOperationReportFrame_t		*report;
	size_t									doorLockMode;
	size_t									ticks;
	size_t									tempos;
	size_t									lockTimeoutMinutes;
	size_t									lockTimeoutSeconds;
	ZwDoorLockPropertiesSave_t				properties_save;
	ZunoTimerBasic_t						*lp;

	doorLockMode = zuno_universalGetter1P(channel);
	zunoEnterCritical();
	DOOR_LOCK_GET_PROPERTIES_SAVE(channel, properties_save);
	if (properties_save.operationType == DOOR_LOCK_CONFIGURATION_SET_TIMED_OPERATION_V4 && (lp = zuno_CCTimerBasicFind(channel)) != 0x0 && lp->channel != 0x0) {
		ticks = millis();
		if (lp->ticksEnd > ticks)
			ticks = lp->ticksEnd - ticks;
		else
			ticks = 0x0;
		tempos = ticks / 1000;
		lockTimeoutMinutes = tempos / 60;
		lockTimeoutSeconds = tempos % 60;
		if (lockTimeoutSeconds == 0x0 && lockTimeoutMinutes == 0x0 && ticks != 0)
			lockTimeoutSeconds++;
	}
	else {
		lockTimeoutMinutes = DOOR_LOCK_OPERATION_REPORT_UNKNOWN_DURATION_V4;
		lockTimeoutSeconds = DOOR_LOCK_OPERATION_REPORT_UNKNOWN_DURATION_V4;
	}
	zunoExitCritical();
	report = (ZwDoorLockOperationReportFrame_t *)&packet->cmd[0x0];
	report->v4.cmdClass = COMMAND_CLASS_DOOR_LOCK;
	report->v4.cmd = DOOR_LOCK_OPERATION_REPORT;
	report->v4.currentDoorLockMode = doorLockMode;
	report->v4.properties1 = properties_save.InsideDoorHandlesMode | (properties_save.OutsideDoorHandlesMode << DOOR_LOCK_CONFIGURATION_SET_PROPERTIES1_OUTSIDE_DOOR_HANDLES_STATE_SHIFT_V4);;
	report->v4.doorCondition = 0x0;
	report->v4.lockTimeoutMinutes = lockTimeoutMinutes;
	report->v4.lockTimeoutSeconds = lockTimeoutSeconds;
	report->v4.targetDoorLockMode = doorLockMode;
	report->v4.duration = 0x0;
	packet->len = sizeof(report->v4);
	return (ZUNO_COMMAND_ANSWERED);
}

void zuno_CCDoorLockTimer(ZunoTimerBasic_t *lp) {
	size_t									channel;
	size_t									ticks;

	ticks = millis();
	if (ticks < lp->ticksEnd)
		return ;
	channel = lp->channel;
	zuno_universalSetter1P(channel - 1, DOOR_LOCK_OPERATION_REPORT_DOOR_SECURED_V4);
	zunoSendReport(channel);
	lp->channel = 0x0;
}
#endif // WITH_CC_DOORLOCK