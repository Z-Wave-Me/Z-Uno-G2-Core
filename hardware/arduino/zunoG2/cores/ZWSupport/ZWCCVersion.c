#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCBasic.h"
#include "ZWCCSwitchBinary.h"
#include "ZWCCSwitchColor.h"
#include "ZWCCThermostat.h"
#include "ZWCCSwitchMultilevel.h"
#include "ZWCCMultichannel.h"
#include "ZWCCMeter.h"
#include "ZWCCSensorMultilevel.h"
#include "ZWCCNotification.h"
#include "ZWCCDoorLock.h"
#include "ZWCCConfiguration.h"
#include "ZWCCAssociation.h"
#include "ZWCCBattery.h"
#include "ZWCCWakeup.h"
#include "ZWCCZWavePlusInfo.h"
#include "ZWCCTimer.h"
#include "ZWCCSecurity.h"
#include "ZWCCTimerParametrs.h"
#include "ZWCCMeterTbl.h"
#include "ZWCCVersion.h"
#include "Debug.h"
#include "ZWCCSuperVision.h"
#include "ZWCCUserCode.h"
#include "ZWCCEntryControl.h"
#include "ZWCCAuthentication.h"
#include "ZWCCSoundSwitch.h"
#include "ZWCCIndicator.h"
#include "ZWCCCentralScene.h"
#include "ZWCCResetLocally.h"
#include "ZWCCWindowCovering.h"
#include "ZWCCScheduleEntryLock.h"
#include "ZWCCTime.h"
#include "ZWCCUserCredential.h"

static const uint8_t zuno_CCVesrions[] = {
  COMMAND_CLASS_APPLICATION_STATUS, APPLICATION_STATUS_VERSION,
  COMMAND_CLASS_ZWAVEPLUS_INFO, ZWAVEPLUS_INFO_VERSION,
  COMMAND_CLASS_ASSOCIATION,  ASSOCIATION_VERSION,
  COMMAND_CLASS_MULTI_CHANNEL_ASSOCIATION, MULTI_CHANNEL_ASSOCIATION_VERSION,
  COMMAND_CLASS_ASSOCIATION_GRP_INFO, ASSOCIATION_GRP_INFO_VERSION,
  COMMAND_CLASS_TRANSPORT_SERVICE, TRANSPORT_SERVICE_VERSION,
  COMMAND_CLASS_VERSION, VERSION_VERSION,
  COMMAND_CLASS_MANUFACTURER_SPECIFIC,MANUFACTURER_SPECIFIC_VERSION, 
  COMMAND_CLASS_DEVICE_RESET_LOCALLY,DEVICE_RESET_LOCALLY_VERSION,
  COMMAND_CLASS_INDICATOR, INDICATOR_VERSION,
  COMMAND_CLASS_CONFIGURATION, CONFIGURATION_VERSION, 
  COMMAND_CLASS_FIRMWARE_UPDATE_MD,FIRMWARE_UPDATE_MD_VERSION, 
  COMMAND_CLASS_SUPERVISION, SUPERVISION_VERSION,
  COMMAND_CLASS_SECURITY, SECURITY_VERSION,
  COMMAND_CLASS_SECURITY_2, SECURITY_2_VERSION,
  COMMAND_CLASS_POWERLEVEL, 0x1,
  #ifndef DYNAMIC_CCS_SUPPORT
  #ifdef WITH_CC_BASIC
  COMMAND_CLASS_BASIC, BASIC_VERSION, 
  #endif
  #ifdef WITH_CC_SWITCH_BINARY
  COMMAND_CLASS_SWITCH_BINARY, SWITCH_BINARY_VERSION, 
  #endif
  #ifdef WITH_CC_SWITCH_MULTILEVEL
  COMMAND_CLASS_SWITCH_MULTILEVEL,  SWITCH_MULTILEVEL_VERSION,
  #endif
  #ifdef WITH_CC_NOTIFICATION
  COMMAND_CLASS_NOTIFICATION, NOTIFICATION_VERSION,
  #endif
  #ifdef WITH_CC_SENSOR_MULTILEVEL
  COMMAND_CLASS_SENSOR_MULTILEVEL, SENSOR_MULTILEVEL_VERSION,
  #endif
  #ifdef WITH_CC_METER
  COMMAND_CLASS_METER, METER_VERSION,
  #endif
  #ifdef WITH_CC_METER_TBL_MONITOR
  COMMAND_CLASS_METER_TBL_MONITOR, METER_TBL_MONITOR_VERSION,
  #endif
  #ifdef WITH_CC_DOORLOCK
  COMMAND_CLASS_DOOR_LOCK, DOOR_LOCK_VERSION,
  #endif
  #ifdef WITH_CC_THERMOSTAT_MODE
  COMMAND_CLASS_THERMOSTAT_MODE, THERMOSTAT_MODE_VERSION,
  #endif
  #ifdef WITH_CC_THERMOSTAT_SETPOINT
  COMMAND_CLASS_THERMOSTAT_SETPOINT, THERMOSTAT_SETPOINT_VERSION,
  #endif
  #ifdef WITH_CC_SWITCH_COLOR
  COMMAND_CLASS_SWITCH_COLOR, SWITCH_COLOR_VERSION,
  #endif
  #ifdef WITH_CC_WINDOW_COVERING
  COMMAND_CLASS_WINDOW_COVERING, WINDOW_COVERING_VERSION,
  #endif
  #ifdef WITH_CC_SOUND_SWITCH
  COMMAND_CLASS_SOUND_SWITCH, SOUND_SWITCH_VERSION,
  #endif
  #ifdef WITH_CC_WAKEUP
  COMMAND_CLASS_WAKE_UP, WAKE_UP_VERSION, 
  #endif
  #ifdef WITH_CC_BATTERY
  COMMAND_CLASS_BATTERY, BATTERY_VERSION,
  #endif
  #ifdef WITH_CC_MULTICHANNEL
  COMMAND_CLASS_MULTI_CHANNEL, MULTI_CHANNEL_VERSION,
  #endif
  #ifdef WITH_CC_CENTRAL_SCENE
  COMMAND_CLASS_CENTRAL_SCENE, CENTRAL_SCENE_VERSION,
  #endif
  #ifdef WITH_CC_SCHEDULE_ENTRY_LOCK
  COMMAND_CLASS_SCHEDULE_ENTRY_LOCK, SCHEDULE_ENTRY_LOCK_VERSION,
  #endif
  #ifdef WITH_CC_USER_CODE
  COMMAND_CLASS_USER_CODE, USER_CODE_VERSION,
  #endif
  #ifdef WITH_CC_USER_CREDENTIAL
  COMMAND_CLASS_USER_CREDENTIAL, USER_CREDENTIAL_VERSION,
  #endif
  #ifdef WITH_CC_ENTRY_CONTROL
  COMMAND_CLASS_ENTRY_CONTROL, ENTRY_CONTROL_VERSION,
  #endif
  #ifdef WITH_CC_TIME_PARAMETERS
  COMMAND_CLASS_TIME_PARAMETERS, TIME_PARAMETERS_VERSION,
  #endif
  #ifdef WITH_CC_TIME
  COMMAND_CLASS_TIME, TIME_VERSION,
  #endif
  #endif // DYNAMIC_CCS_SUPPORT
};

static uint8_t extractVersionFromCCList(uint8_t cc, uint8_t * ccs, uint8_t ccs_len){
	#if defined(WITH_CC_WAKEUP) || defined(WITH_CC_BATTERY)
	if (zunoIsSleepingMode() == false) {
		#if defined(WITH_CC_WAKEUP)
		if (cc == COMMAND_CLASS_WAKE_UP)
			return (0);
		#endif
		#if defined(WITH_CC_BATTERY)
		if (cc == COMMAND_CLASS_BATTERY)
			return (0);
		#endif
	}
	#endif
	for(int i=0;i<ccs_len;i+=2){
		if(ccs[i] == cc)
			return ccs[i+1];
	}
	return 0;
}
static int _class_get(const ZUNOCommandCmd_t *packet, ZW_VERSION_COMMAND_CLASS_GET_V3_FRAME *cmd, ZUNOCommandPacketReport_t *frame_report) {
	ZW_VERSION_COMMAND_CLASS_REPORT_V3_FRAME		*report;
	report = (ZW_VERSION_COMMAND_CLASS_REPORT_V3_FRAME *)frame_report->info.packet.cmd;
	
	report->requestedCommandClass = cmd->requestedCommandClass;
	report->commandClassVersion = 0;
	#ifdef DYNAMIC_CCS_SUPPORT
	report->commandClassVersion = dynamicCCVersion(report->requestedCommandClass);
	if(report->commandClassVersion == 0)
	#endif
	{
		report->commandClassVersion = extractVersionFromCCList(report->requestedCommandClass, (uint8_t*)zuno_CCVesrions, sizeof(zuno_CCVesrions));
	}
	frame_report->info.packet.len = sizeof(ZW_VERSION_COMMAND_CLASS_REPORT_V3_FRAME);
	zunoSendZWPackageAdd(frame_report);
	return (ZUNO_COMMAND_PROCESSED);
	(void)packet;
}
extern ZUNOCodeHeader_t g_zuno_codeheader;
int zuno_CCVersionHandler(const ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	switch(ZW_CMD){
		case VERSION_COMMAND_CLASS_GET:
			return _class_get(cmd, (ZW_VERSION_COMMAND_CLASS_GET_V3_FRAME *)cmd->cmd, frame_report);
    case VERSION_GET:{
      frame_report->info.packet.cmd[2] = VERSION_LIBRARY_TYPE_SLAVE;
      frame_report->info.packet.cmd[3] = ZWAVE_SDK_VERSION_MAJOR;
      frame_report->info.packet.cmd[4] = ZWAVE_SDK_VERSION_MINOR;
      frame_report->info.packet.cmd[5] = g_zuno_codeheader.version_major;
      frame_report->info.packet.cmd[6] = g_zuno_codeheader.version_minor;
      frame_report->info.packet.cmd[7] = g_zuno_sys->fw_static_header->hw_id & 0xFF;
      frame_report->info.packet.cmd[8] = g_zuno_codeheader.ota_firmwares_count;
      uint8_t * p_versions = frame_report->info.packet.cmd+9;
      if((g_zuno_codeheader.flags & HEADER_FLAGS_NOSKETCH_OTA) == 0){
        frame_report->info.packet.cmd[8] += 1;
        p_versions[0] = g_zuno_codeheader.sketch_version >> 8;
        p_versions[1] = g_zuno_codeheader.sketch_version & 0xFF;
        p_versions += 2;
      }
      for(int i=0;i<g_zuno_codeheader.ota_firmwares_count;i++, p_versions += 2){
        uint16_t v = g_zuno_codeheader.ota_firmwares_descriptions[i].version;
        p_versions[0] = v >> 8;
        p_versions[1] = v & 0xFF;
      }
      frame_report->info.packet.len = p_versions - frame_report->info.packet.cmd;
      zunoSendZWPackageAdd(frame_report);
      return ZUNO_COMMAND_PROCESSED;
    }
    case VERSION_CAPABILITIES_GET:
      frame_report->info.packet.cmd[2] = VERSION_CAPABILITIES_REPORT_PROPERTIES1_VERSION_BIT_MASK | VERSION_CAPABILITIES_REPORT_PROPERTIES1_COMMAND_CLASS_BIT_MASK;
      frame_report->info.packet.len = 3;
      zunoSendZWPackageAdd(frame_report);
      return ZUNO_COMMAND_PROCESSED;
		default:
			return ZUNO_UNKNOWN_CMD;
	}
	return ZUNO_UNKNOWN_CMD;
}