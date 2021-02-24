#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCZWavePlusInfo.h"

static int _report(void) {
	ZwZwavePlusInfoReportFrame_t		*report;
	size_t								installerIconType;
	size_t								userIconType;

	report = (ZwZwavePlusInfoReportFrame_t *)&CMD_REPLY_CC;
	report->v2.cmdClass = COMMAND_CLASS_ZWAVEPLUS_INFO;
	report->v2.cmd = ZWAVEPLUS_INFO_REPORT;
	report->v2.zWaveVersion = ZWAVEPLUS_INFO_VERSION;
	report->v2.roleType = ZWAVEPLUS_INFO_REPORT_ROLE_TYPE_SLAVE_ALWAYS_ON;
	report->v2.nodeType = ZWAVEPLUS_INFO_REPORT_NODE_TYPE_ZWAVEPLUS_NODE;
	installerIconType = ICON_TYPE_GENERIC_ON_OFF_POWER_SWITCH;
	userIconType = ICON_TYPE_GENERIC_ON_OFF_POWER_SWITCH;
	report->v2.installerIconType1 = installerIconType >> 8;
	report->v2.installerIconType2 = installerIconType & 0xFF;
	report->v2.userIconType1 = userIconType >> 8;
	report->v2.userIconType2 = userIconType & 0xFF;
	CMD_REPLY_LEN = sizeof(report->v2);
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCZWavePlusInfoHandler(ZUNOCommandPacket_t *cmd) {
	int								rs;

	switch (ZW_CMD) {
		case ZWAVEPLUS_INFO_GET:
			rs = _report();
			break ;
		default:
			rs = ZUNO_UNKNOWN_CMD;
			break ;
	}
	return (rs);
}