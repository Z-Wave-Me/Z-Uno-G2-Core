#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCZWavePlusInfo.h"

void zuno_CCSoundSwitchGetIcon(ZwZwavePlusInfoIcon_t *icon);
void zuno_CCSensorMultilevelGetIcon(uint8_t channel, ZwZwavePlusInfoIcon_t *icon) ;
void zuno_CCNotificationGetIcon(uint8_t channel, ZwZwavePlusInfoIcon_t *icon);
void zuno_CCWindowCoveringGetIcon(uint8_t channel, ZwZwavePlusInfoIcon_t *icon);
void zuno_CCSwitchBinaryGetIcon(ZwZwavePlusInfoIcon_t *icon);

void __zuno_CCZWavePlusGetIcon(uint8_t channel, ZwZwavePlusInfoIcon_t *icon) {
	uint8_t								type;

	type = ZUNO_CFG_CHANNEL(channel).type;
	switch (type) {
		#if defined(WITH_CC_SOUND_SWITCH)
		case ZUNO_SOUND_SWITCH_CHANNEL_NUMBER:
			zuno_CCSoundSwitchGetIcon(icon);
			break ;
		#endif
		#if defined(WITH_CC_SENSOR_MULTILEVEL)
		case ZUNO_SENSOR_MULTILEVEL_CHANNEL_NUMBER:
			zuno_CCSensorMultilevelGetIcon(channel, icon);
			break ;
		#endif
		#if defined(WITH_CC_NOTIFICATION)
		case ZUNO_SENSOR_BINARY_CHANNEL_NUMBER:
			zuno_CCNotificationGetIcon(channel, icon);
			break ;
		#endif
		#if defined(WITH_CC_WINDOW_COVERING)
		case ZUNO_WINDOW_COVERING_CHANNEL_NUMBER:
			zuno_CCWindowCoveringGetIcon(channel, icon);
			break ;
		#endif
		#if defined(WITH_CC_SWITCH_BINARY)
		case ZUNO_SWITCH_BINARY_CHANNEL_NUMBER:
			zuno_CCSwitchBinaryGetIcon(icon);
			break ;
		#endif
		#if defined(WITH_CC_SWITCH_MULTILEVEL)
		case ZUNO_SWITCH_MULTILEVEL_CHANNEL_NUMBER:
			zuno_CCSwitchMultilevelGetIcon(icon);
			break ;
		#endif
		default:
			type--;
			icon->installerIconType = ZUNO_DEV_TYPES[type].icon;
			icon->userIconType = ZUNO_DEV_TYPES[type].app_icon;
			break ;
	}
}

void zuno_CCWindowCoveringGetType(uint8_t channel, ZwZwavePlusInfoType_t *type);
void zuno_CCSwitchBinaryGetType(uint8_t channel, ZwZwavePlusInfoType_t *type);

void __zuno_CCZWavePlusGetType(uint8_t channel, ZwZwavePlusInfoType_t *info_type) {
	uint8_t								type;

	type = ZUNO_CFG_CHANNEL(channel).type;
	switch (type) {
		#if defined(WITH_CC_WINDOW_COVERING)
		case ZUNO_WINDOW_COVERING_CHANNEL_NUMBER:
			zuno_CCWindowCoveringGetType(channel, info_type);
			break ;
		#endif
		#if defined(WITH_CC_SWITCH_BINARY)
		case ZUNO_SWITCH_BINARY_CHANNEL_NUMBER:
			zuno_CCSwitchBinaryGetType(channel, info_type);
			break ;
		#endif
		#if defined(WITH_CC_SWITCH_MULTILEVEL)
		case ZUNO_SWITCH_MULTILEVEL_CHANNEL_NUMBER:
			zuno_CCSwitchMultilevelGetType(channel, info_type);
			break ;
		#endif
		default:
			type--;
			info_type->genericDeviceClass = ZUNO_DEV_TYPES[type].gen_type;
			info_type->specificDeviceClass = ZUNO_DEV_TYPES[type].spec_type;
			break ;
	}
}

static int _report(ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	ZwZwavePlusInfoReportFrame_t		*report;
	ZwZwavePlusInfoIcon_t				icon;
	size_t								roleType;
	uint8_t								channel;
	
	#ifdef MODERN_MULTICHANNEL_S2
	if ((cmd->zw_rx_secure_opts == SECURITY_KEY_NONE) &&
	    (zunoSecurityStatus() != SECURITY_KEY_NONE) && 
		(cmd->dst_zw_channel != 0) ) {
			return ZUNO_COMMAND_BLOCKED;
	}
	#endif
	channel = zuno_findChannelByZWChannelIndexChannel(cmd->dst_zw_channel);
	if (channel == UNKNOWN_CHANNEL)
		channel = 0x0;
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
	__zuno_CCZWavePlusGetIcon(channel, &icon);
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