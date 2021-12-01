#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCZWavePlusInfo.h"


static int _report(ZUNOCommandPacket_t *cmd) {
	ZwZwavePlusInfoReportFrame_t		*report;
	size_t								installerIconType;
	size_t								userIconType;
	size_t								roleType;

	ZUNOChannel_t * ch_data =  zuno_findChannelByZWChannel(zw_channel);
	uint8_t type_index = ch_data->type -1;
	report = (ZwZwavePlusInfoReportFrame_t *)&CMD_REPLY_CC;
	report->v2.cmdClass = COMMAND_CLASS_ZWAVEPLUS_INFO;
	report->v2.cmd = ZWAVEPLUS_INFO_REPORT;
	report->v2.zWaveVersion = ZWAVEPLUS_INFO_VERSION;
	switch (g_zuno_sys->zwave_cfg->flags & DEVICE_CONFIGURATION_FLAGS_MASK_SLEEP) {
		case DEVICE_CONFIGURATION_FLAGS_SLEEP:
			roleType = ZWAVEPLUS_INFO_REPORT_ROLE_TYPE_SLAVE_SLEEPING_REPORTING;
			break ;
		case DEVICE_CONFIGURATION_FLAGS_FLIRS:
			roleType = ZWAVEPLUS_INFO_REPORT_ROLE_TYPE_SLAVE_SLEEPING_LISTENING;
			break ;
		default:
			roleType = ZWAVEPLUS_INFO_REPORT_ROLE_TYPE_SLAVE_ALWAYS_ON;
			break ;
	}
	report->v2.roleType = roleType;
	report->v2.nodeType = ZWAVEPLUS_INFO_REPORT_NODE_TYPE_ZWAVEPLUS_NODE;
	installerIconType = ZUNO_DEV_TYPES[type_index].icon;
	userIconType = ZUNO_DEV_TYPES[type_index].app_icon;
	report->v2.installerIconType1 = installerIconType >> 8;
	report->v2.installerIconType2 = installerIconType & 0xFF;
	report->v2.userIconType1 = userIconType >> 8;
	report->v2.userIconType2 = userIconType & 0xFF;
	CMD_REPLY_LEN = sizeof(report->v2);
	// Use security policy as we were asked. It fixes some controllers S2 problems...
	g_outgoing_main_packet.zw_rx_secure_opts = cmd->zw_rx_secure_opts;
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCZWavePlusInfoHandler(ZUNOCommandPacket_t *cmd) {
	int								rs;
 
	switch (ZW_CMD) {
		case ZWAVEPLUS_INFO_GET:
			rs = _report(cmd);
			break ;
		default:
			rs = ZUNO_UNKNOWN_CMD;
			break ;
	}
	return (rs);
}