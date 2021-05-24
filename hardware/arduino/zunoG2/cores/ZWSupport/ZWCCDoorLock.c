#include "ZWCCDoorLock.h"
#include "./includes/ZWCCDoorLock_private.h"

static int _report_configuration(uint8_t channel, bool reply) {
	ZwDoorLockConfigurationReportFrame_t		*lp;
	if(reply){
		lp = (ZwDoorLockConfigurationReportFrame_t *)&CMD_REPLY_CC;
		CMD_REPLY_LEN = sizeof(lp->v3);
	} else {
		lp = (ZwDoorLockConfigurationReportFrame_t *)&CMD_REPORT_CC;
		CMD_REPORT_LEN = sizeof(lp->v3);
	}
	lp = (ZwDoorLockConfigurationReportFrame_t *)&CMD_REPLY_CC;
	lp->v3.cmdClass = COMMAND_CLASS_DOOR_LOCK;
	lp->v3.cmd = DOOR_LOCK_CONFIGURATION_REPORT;
	lp->v3.operationType = 0x1;
	lp->v3.properties1 = 0x1;
	lp->v3.lockTimeoutMinutes = 0xFE;
	lp->v3.lockTimeoutSeconds = 0xFE;
	return (ZUNO_COMMAND_ANSWERED);
	(void)channel;
}

static void _set_operation(uint8_t channel, ZUNOCommandPacket_t *cmd) {
	zuno_universalSetter1P(channel, ((ZwDoorLockOperationSet_t *)cmd->cmd)->doorLockMode);
}

int zuno_CCDoorLockHandler(uint8_t channel, ZUNOCommandPacket_t *cmd) {
	int				rs;

	rs = ZUNO_UNKNOWN_CMD;
	switch(ZW_CMD) {
		case DOOR_LOCK_CONFIGURATION_GET:
			rs = _report_configuration(channel, true);
			break ;
		case DOOR_LOCK_OPERATION_GET:
			rs = zuno_CCDoorLockReport(channel, true);
			break ;
		case DOOR_LOCK_OPERATION_SET:
			_set_operation(channel, cmd);
			zunoSendReport(channel + 1);
			rs = ZUNO_COMMAND_PROCESSED;
			break ;
	}
	return (rs);
}

int zuno_CCDoorLockReport(uint8_t channel, bool reply) {
	ZwDoorLockOperationReportFrame_t		*lp;
	uint8_t									doorLockMode;

	if(reply){
		lp = (ZwDoorLockOperationReportFrame_t *)&CMD_REPLY_CC;
		CMD_REPLY_LEN = sizeof(lp->v2);
	} else {
		lp = (ZwDoorLockOperationReportFrame_t *)&CMD_REPORT_CC;
		CMD_REPORT_LEN = sizeof(lp->v2);
	}
	doorLockMode = zuno_universalGetter1P(channel);
	lp->v2.cmdClass = COMMAND_CLASS_DOOR_LOCK;
	lp->v2.cmd = DOOR_LOCK_OPERATION_REPORT;
	lp->v2.doorLockMode = doorLockMode;
	lp->v2.properties1 = 0x1;
	lp->v2.doorCondition = (doorLockMode == 0) ? 0x0 : 0x1;
	lp->v2.lockTimeoutMinutes = 0xFE;
	lp->v2.lockTimeoutSeconds = 0xFE;
	return (ZUNO_COMMAND_ANSWERED);
}