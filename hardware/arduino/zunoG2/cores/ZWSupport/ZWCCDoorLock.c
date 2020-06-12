#include "ZWCCDoorLock.h"
#include "./includes/ZWCCDoorLock_private.h"

static int _report_configuration(uint8_t channel) {
	ZwDoorLockConfigurationReportFrame_t		*lp;

	lp = (ZwDoorLockConfigurationReportFrame_t *)&CMD_REPLY_CC;
	lp->v3.cmdClass = COMMAND_CLASS_DOOR_LOCK;
	lp->v3.cmd = DOOR_LOCK_CONFIGURATION_REPORT;
	lp->v3.operationType = 0x1;
	lp->v3.properties1 = 0x1;
	lp->v3.lockTimeoutMinutes = 0xFE;
	lp->v3.lockTimeoutSeconds = 0xFE;
	CMD_REPLY_LEN = sizeof(lp->v3);
	return (ZUNO_COMMAND_ANSWERED);
}

static void _set_operation(uint8_t channel, ZUNOCommandPacket_t *cmd) {
	zuno_universalSetter1P(channel, ((ZwDoorLockOperationSet_t *)cmd)->doorLockMode);
}

int zuno_CCDoorLockHandler(uint8_t channel, ZUNOCommandPacket_t *cmd) {
	int				rs;

	rs = ZUNO_UNKNOWN_CMD;
	switch(ZW_CMD) {
		case DOOR_LOCK_CONFIGURATION_GET:
			rs = _report_configuration(channel);
			break ;
		case DOOR_LOCK_OPERATION_GET:
			rs = zuno_CCDoorLockReport(channel);
			break ;
		case DOOR_LOCK_OPERATION_SET:
			_set_operation(channel, cmd);
			zunoSendReport(channel + 1);
			rs = ZUNO_COMMAND_PROCESSED;
			break ;
	}
	return (rs);
}

int zuno_CCDoorLockReport(uint8_t channel) {
	ZwDoorLockOperationReportFrame_t		*lp;
	uint8_t									doorLockMode;

	lp = (ZwDoorLockOperationReportFrame_t *)&CMD_REPLY_CC;
	doorLockMode = zuno_universalGetter1P(channel);
	lp->v2.cmdClass = COMMAND_CLASS_DOOR_LOCK;
	lp->v2.cmd = DOOR_LOCK_OPERATION_REPORT;
	lp->v2.doorLockMode = doorLockMode;
	lp->v2.properties1 = 0x1;
	lp->v2.doorCondition = (doorLockMode == 0) ? 0x0 : 0x1;
	lp->v2.lockTimeoutMinutes = 0xFE;
	lp->v2.lockTimeoutSeconds = 0xFE;
	CMD_REPLY_LEN = sizeof(lp->v2);
	return (ZUNO_COMMAND_ANSWERED);
}