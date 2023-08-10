#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCZWavePlusInfo.h"


void zuno_CCSoundSwitchGetIcon(ZwZwavePlusInfoOut_t *icon);

static void _get_info(uint8_t type, ZwZwavePlusInfoOut_t *icon) {
	switch (type) {
		#if defined(WITH_CC_SOUND_SWITCH)
		case ZUNO_SOUND_SWITCH_CHANNEL_NUMBER:
			zuno_CCSoundSwitchGetIcon(icon);
			break ;
		#endif
		default:
			type--;
			icon->installerIconType = ZUNO_DEV_TYPES[type].icon;
			icon->userIconType = ZUNO_DEV_TYPES[type].app_icon;
			break ;
	}
}

static int _report(ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	ZwZwavePlusInfoReportFrame_t		*report;
	ZwZwavePlusInfoOut_t				icon;
	size_t								roleType;

	
	#ifdef MODERN_MULTICHANNEL_S2
	if ((cmd->zw_rx_secure_opts == SECURITY_KEY_NONE) &&
	    (zunoSecurityStatus() != SECURITY_KEY_NONE) && 
		(cmd->dst_zw_channel != 0) ) {
			return ZUNO_COMMAND_BLOCKED;
	}
	#endif
	ZUNOChannel_t * ch_data =  zuno_findChannelByZWChannel(cmd->dst_zw_channel);
	report = (ZwZwavePlusInfoReportFrame_t *)frame_report->packet.cmd;
	report->v2.cmdClass = COMMAND_CLASS_ZWAVEPLUS_INFO;
	report->v2.cmd = ZWAVEPLUS_INFO_REPORT;
	report->v2.zWaveVersion = ZWAVEPLUS_INFO_VERSION;
	switch (zunoGetSleepingMode() & DEVICE_CONFIGURATION_FLAGS_MASK_SLEEP) {
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
	_get_info(ch_data->type, &icon);
	report->v2.installerIconType1 = icon.installerIconType >> 8;
	report->v2.installerIconType2 = icon.installerIconType & 0xFF;
	report->v2.userIconType1 = icon.userIconType >> 8;
	report->v2.userIconType2 = icon.userIconType & 0xFF;
	frame_report->packet.len = sizeof(report->v2);
	// Use security policy as we were asked. It fixes some controllers S2 problems...
	frame_report->packet.zw_rx_secure_opts = cmd->zw_rx_secure_opts;
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCZWavePlusInfoHandler(ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	int								rs;
 
	switch (ZW_CMD) {
		case ZWAVEPLUS_INFO_GET:
			rs = _report(cmd, frame_report);
			break ;
		default:
			rs = ZUNO_UNKNOWN_CMD;
			break ;
	}
	return (rs);
}