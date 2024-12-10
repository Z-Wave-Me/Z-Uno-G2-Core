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
#include "ZWCCManufacturerSpecific.h"
#include "ZWCCScheduleEntryLock.h"
#include "CommandQueue.h"
#include "ZUNO_AutoChannels.h"
#include "CrcClass.h"
#include "ZWCCTime.h"
#include "ZWCCUserCredential.h"

#define DYNAMIC_CCS_SUPPORT 1
CrcClass mCrc; 

static const uint8_t FREQ_TBL_CONV[][2] = { {ZME_FREQ_EU, REGION_EU},
		 	 	 	 	 	 	 	 	 	{ZME_FREQ_RU, REGION_RU},
											{ZME_FREQ_IN, REGION_IN},
											{ZME_FREQ_US, REGION_US},
											{ZME_FREQ_ANZ, REGION_ANZ},
											{ZME_FREQ_HK, REGION_HK},
											{ZME_FREQ_CN, REGION_CN},
											{ZME_FREQ_JP, REGION_JP},
											{ZME_FREQ_KR, REGION_KR},
											{ZME_FREQ_IL, REGION_IL},
                      						{ZME_FREQ_MY, REGION_KR},
                      						{ZME_FREQ_LR_US, REGION_US_LR}};


// -----------------------------------------------------------------
// STATIC NIF
// -----------------------------------------------------------------
static const uint8_t zuno_cmdClassListNSIS_Def[] =
{
  COMMAND_CLASS_ZWAVEPLUS_INFO,
  COMMAND_CLASS_TRANSPORT_SERVICE,
  COMMAND_CLASS_SECURITY,
  COMMAND_CLASS_SECURITY_2,
  COMMAND_CLASS_SUPERVISION,
  COMMAND_CLASS_APPLICATION_STATUS
};
static const uint8_t zuno_cmdClassListSec_Def[] =
{
  COMMAND_CLASS_VERSION,
  COMMAND_CLASS_ASSOCIATION,
  COMMAND_CLASS_MULTI_CHANNEL_ASSOCIATION,
  COMMAND_CLASS_ASSOCIATION_GRP_INFO,
  COMMAND_CLASS_MANUFACTURER_SPECIFIC,
  COMMAND_CLASS_DEVICE_RESET_LOCALLY,
  COMMAND_CLASS_INDICATOR,
  COMMAND_CLASS_POWERLEVEL,
  COMMAND_CLASS_CONFIGURATION,
  COMMAND_CLASS_FIRMWARE_UPDATE_MD,
  #ifdef WITH_CC_CENTRAL_SCENE
  COMMAND_CLASS_CENTRAL_SCENE,
  #endif
  #ifdef WITH_CC_SCHEDULE_ENTRY_LOCK
  COMMAND_CLASS_SCHEDULE_ENTRY_LOCK,
  #endif
  #ifdef WITH_CC_USER_CODE
  COMMAND_CLASS_USER_CODE,
  #endif
  #ifdef WITH_CC_USER_CREDENTIAL
  COMMAND_CLASS_USER_CREDENTIAL,
  #endif
  #ifdef WITH_CC_ENTRY_CONTROL
  COMMAND_CLASS_ENTRY_CONTROL,
  #endif
  #ifdef WITH_CC_TIME_PARAMETERS
  COMMAND_CLASS_TIME_PARAMETERS,
  #endif
};
static const uint8_t zuno_cmdClassListNSNI_Def[] =
{
  COMMAND_CLASS_ZWAVEPLUS_INFO,
  COMMAND_CLASS_ASSOCIATION,
  COMMAND_CLASS_MULTI_CHANNEL_ASSOCIATION,
  COMMAND_CLASS_ASSOCIATION_GRP_INFO,
  COMMAND_CLASS_TRANSPORT_SERVICE,
  COMMAND_CLASS_VERSION,
  COMMAND_CLASS_MANUFACTURER_SPECIFIC,
  COMMAND_CLASS_DEVICE_RESET_LOCALLY,
  COMMAND_CLASS_INDICATOR,
  COMMAND_CLASS_POWERLEVEL,
  COMMAND_CLASS_SUPERVISION,
  COMMAND_CLASS_CONFIGURATION,
  COMMAND_CLASS_FIRMWARE_UPDATE_MD,
  COMMAND_CLASS_APPLICATION_STATUS,
  #ifdef WITH_CC_CENTRAL_SCENE
  COMMAND_CLASS_CENTRAL_SCENE,
  #endif
  #ifdef WITH_CC_SCHEDULE_ENTRY_LOCK
  COMMAND_CLASS_SCHEDULE_ENTRY_LOCK,
  #endif
  #ifdef WITH_CC_USER_CODE
  COMMAND_CLASS_USER_CODE,
  #endif
  #ifdef WITH_CC_USER_CREDENTIAL
  COMMAND_CLASS_USER_CREDENTIAL,
  #endif
  #ifdef WITH_CC_ENTRY_CONTROL
  COMMAND_CLASS_ENTRY_CONTROL,
  #endif
  #ifdef WITH_CC_TIME_PARAMETERS
  COMMAND_CLASS_TIME_PARAMETERS,
  #endif
};

typedef struct ZUNOChannelsData_s{
	uint32_t update_map;
	uint32_t request_map;
	uint32_t report_map;
	uint32_t sys_reports;
	uint32_t sys_requests;
	uint32_t last_report_time[ZUNO_MAX_MULTI_CHANNEL_NUMBER];
	node_id_t  sync_nodes[ZUNO_MAX_MULTI_CHANNEL_NUMBER]; // Supervision sync nodes
}ZUNOChannelsData_t;
ZUNOChannelsData_t g_channels_data;
typedef struct ZUnoRcvContext_s {
	bool 	bMulticast;
	bool    bBroadcast;
	node_id_t source_node_id;
}ZUnoRcvContext_t;
ZUnoRcvContext_t g_rcv_context;

ZUNOZWConfiguation_t g_zuno_zw_cfg;

inline void __setSyncVar16(node_id_t * var, node_id_t val){
	zunoEnterCritical();
	*var = val;
	zunoExitCritical();
}
inline void __setSyncVar(uint32_t * var, uint32_t val){
	zunoEnterCritical();
	*var = val;
	zunoExitCritical();
}
inline uint32_t __getSyncVar(uint32_t * var){
	uint32_t res = 0;
	zunoEnterCritical();
	res = *var;
	zunoExitCritical();
	return res;
}
inline node_id_t __getSyncVar16(node_id_t * var){
	node_id_t res = 0;
	zunoEnterCritical();
	res = *var;
	zunoExitCritical();
	return res;
}
inline void __setSyncMapChannel(uint32_t * map, uint8_t ch){
	zunoEnterCritical();
	*map |= (1UL << ch);
	zunoExitCritical();
}
inline void __clearSyncMapChannel(uint32_t * map, uint8_t ch){
	zunoEnterCritical();
	*map &= ~(1UL << ch);
	zunoExitCritical();
}
inline bool __isSyncMapChannel(uint32_t * map, uint8_t ch){
	uint32_t res = 0;
	zunoEnterCritical();
	res = *map;
	zunoExitCritical();
	return (res & (1UL << ch)) != 0;
}
inline bool __isSyncMapChannelAndClear(uint32_t * map, uint8_t ch){
	bool res = false;
	zunoEnterCritical();
	res =  (*map & (1UL << ch)) != 0;
	*map &= ~(1UL << ch);
	zunoExitCritical();
	return res;
}
//-------------------------------------------------------------------------------------------------
void _zunoLoadUserChannels();
void ZWCCSetup(){
	memset(&g_channels_data, 0, sizeof(g_channels_data));
	_zunoLoadUserChannels();
	#ifdef WITH_CC_BATTERY
	#ifndef NO_SYS_AUTO_BATTERY_REPORT
	zuno_CCBattery_OnSetup();
	#endif
	#endif
	#ifdef WITH_CC_WAKEUP
	zuno_CCWakeup_OnSetup();
	#endif
}
bool zuno_compare_channeltypeCC(ZUNOChannel_t *channel, uint8_t *cmd_bytes) {
	size_t				cmd_class;

	cmd_class = cmd_bytes[0];
	switch(channel->type) {
		case ZUNO_SWITCH_BINARY_CHANNEL_NUMBER:
			if(cmd_class == COMMAND_CLASS_SWITCH_BINARY)
				return true;
			if(cmd_class == COMMAND_CLASS_BASIC)
				return true;
			break;
		case ZUNO_SWITCH_MULTILEVEL_CHANNEL_NUMBER:
			if(cmd_class == COMMAND_CLASS_SWITCH_MULTILEVEL)
				return true;
			if(cmd_class == COMMAND_CLASS_BASIC)
				return true;
			break;
		case ZUNO_SENSOR_MULTILEVEL_CHANNEL_NUMBER:
			if(cmd_class == COMMAND_CLASS_SENSOR_MULTILEVEL)
				return (true);
			break;
		#ifdef WITH_CC_SWITCH_COLOR
		case ZUNO_SWITCH_COLOR_CHANNEL_NUMBER:
			if(cmd_class == COMMAND_CLASS_SWITCH_COLOR)
				return true;
			if(cmd_class == COMMAND_CLASS_SWITCH_MULTILEVEL)
				return true;
			if(cmd_class == COMMAND_CLASS_BASIC)
				return true;
			break;
		#endif
		#ifdef WITH_CC_WINDOW_COVERING
		case ZUNO_WINDOW_COVERING_CHANNEL_NUMBER:
			if(cmd_class == COMMAND_CLASS_WINDOW_COVERING)
				return true;
			if(cmd_class == COMMAND_CLASS_SWITCH_MULTILEVEL)
				return true;
			if(cmd_class == COMMAND_CLASS_BASIC)
				return true;
			break;
		#endif
		#ifdef WITH_CC_SOUND_SWITCH
		case ZUNO_SOUND_SWITCH_CHANNEL_NUMBER:
			if(cmd_class == COMMAND_CLASS_SOUND_SWITCH)
				return true;
			if(cmd_class == COMMAND_CLASS_BASIC)
				return true;
			break;
		#endif
		#ifdef WITH_CC_DOORLOCK
		case ZUNO_DOORLOCK_CHANNEL_NUMBER:
			if(cmd_class == COMMAND_CLASS_DOOR_LOCK)
				return true;
			if(cmd_class == COMMAND_CLASS_BASIC)
				return true;
			break;
		#endif
		#if defined(WITH_CC_THERMOSTAT_MODE) || defined(WITH_CC_THERMOSTAT_SETPOINT)
		case ZUNO_THERMOSTAT_CHANNEL_NUMBER:
			if(cmd_class == COMMAND_CLASS_THERMOSTAT_MODE)
				return true;
			if(cmd_class == COMMAND_CLASS_THERMOSTAT_SETPOINT)
				return true;
			if(cmd_class == COMMAND_CLASS_BASIC)
				return true;
			break;
		#endif
		case ZUNO_SENSOR_BINARY_CHANNEL_NUMBER:
			if(cmd_class == COMMAND_CLASS_NOTIFICATION)
				return true;
			break;
		case ZUNO_METER_CHANNEL_NUMBER:
			if(cmd_class == COMMAND_CLASS_METER)
				return true;
			#ifdef WITH_CC_METER_TBL_MONITOR
			if(cmd_class == COMMAND_CLASS_METER_TBL_MONITOR)
				return true;
			#endif
			break;
	}
	return false;
}

bool compare_zw_channel(byte ch, byte targ) {
	if((targ == 0) && (ch & ZWAVE_CHANNEL_MAPPED_BIT))
		return true;
	ch &= ~(ZWAVE_CHANNEL_MAPPED_BIT);
	if(targ == ch)
		return true;
	return false;
}
byte zuno_findTargetChannel(ZUNOCommandCmd_t * cmd) {
	byte i;
	#ifdef LOGGING_DBG
	LOGGING_UART.print("N_CH=");
	LOGGING_UART.println(ZUNO_CFG_CHANNEL_COUNT);
	#endif
	for(i=0;i<ZUNO_CFG_CHANNEL_COUNT;i++){
		if(compare_zw_channel(ZUNO_CFG_CHANNEL(i).zw_channel,cmd->dst_zw_channel)) //ZUNO_CFG_CHANNEL(N).zw_channel == cmd->dst_zw_channel)
			if(zuno_compare_channeltypeCC(&(ZUNO_CFG_CHANNEL(i)), cmd->cmd))
				return i;
		
	}
	return UNKNOWN_CHANNEL;
}

bool fillOutgoingRawPacket(ZUNOCommandPacket_t *info, uint8_t * d, uint8_t ch, uint8_t flags, node_id_t dst){
	ZUNOCommandCmd_t					*p;

	info->report.valid = false;
	p = &info->packet;
	bool res = true;
	memset(p, 0, sizeof(p[0x0]));
	memset(d, 0, MAX_ZW_PACKAGE);
	p->cmd = d + MAX_ZWTRANSPORT_ENCAP; // Greetings from ZAF creators
	p->flags 	= flags;
	p->dst_node	= dst; 
	p->src_node  = zunoNID();
	p->src_zw_channel  = ch; // (ZUNO_CFG_CHANNEL(ch).zw_channel) & ~(ZWAVE_CHANNEL_MAPPED_BIT);
	p->zw_rx_opts = ZWAVE_PLUS_TX_OPTIONS;
	p->zw_rx_secure_opts = 0xFF; // Ask system to detect the security level automatically
								 // In most cases it uses highest avaliable level
	return res;
}
static void _fillOutgoingPacket(const ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	
	fillOutgoingRawPacket(&frame_report->info, &frame_report->data[0x0], 0, QUEUE_CHANNEL_SYNC, cmd->src_node);
	frame_report->info.packet.cmd[0] = cmd->cmd[0];  // the same command class
	frame_report->info.packet.cmd[1] = cmd->cmd[1]+1; // in most cases report = get+1
	// Reply as we were asked
	frame_report->info.packet.src_zw_channel    = cmd->dst_zw_channel;
	frame_report->info.packet.dst_zw_channel    = cmd->src_zw_channel;

}

void fillOutgoingReportPacketAsync(ZUNOCommandPacketReport_t *frame, size_t ch) {
	fillOutgoingRawPacket(&frame->info, frame->data, ch, ZUNO_PACKETFLAGS_GROUP | QUEUE_CHANNEL_LLREPORT, ZUNO_LIFELINE_GRP);
}

#ifdef LOGGING_UART
void zuno_dbgdumpZWPacakge(const ZUNOCommandCmd_t * cmd){
	
	LOGGING_UART.print(" SRC_ID:");
	LOGGING_UART.print(cmd->src_node);
	LOGGING_UART.print(".");
	LOGGING_UART.print(cmd->src_zw_channel);
	LOGGING_UART.print(" DST_ID:");
	LOGGING_UART.print(cmd->dst_node);
	LOGGING_UART.print(".");
	LOGGING_UART.print(cmd->dst_zw_channel);
	LOGGING_UART.print(" KEY:");
	LOGGING_UART.print(cmd->zw_rx_secure_opts, HEX);
	LOGGING_UART.print(" OPT:");
	LOGGING_UART.print(cmd->zw_rx_opts, HEX);
	LOGGING_UART.print(" FL:");
	LOGGING_UART.print(cmd->flags, HEX);
	LOGGING_UART.print(" DATA:");
	LOGGING_UART.dumpPrint(cmd->cmd, cmd->len);
	LOGGING_UART.println("");
}
#endif

uint8_t *zuno_AddCommonClassMinimal(uint8_t *b) {
	#ifdef MODERN_MULTICHANNEL_S2
	b++[0] = COMMAND_CLASS_ZWAVEPLUS_INFO;
	b++[0] = COMMAND_CLASS_SUPERVISION;
	#endif
	return (b);
}
uint8_t *zuno_AddCommonClass(uint8_t *b) {
	#ifndef MODERN_MULTICHANNEL_S2
	b++[0] = COMMAND_CLASS_ZWAVEPLUS_INFO;
	b++[0] = COMMAND_CLASS_SUPERVISION;
	#endif
	b++[0] = COMMAND_CLASS_ASSOCIATION;
	b++[0] = COMMAND_CLASS_MULTI_CHANNEL_ASSOCIATION;
	b++[0] = COMMAND_CLASS_ASSOCIATION_GRP_INFO;
	return (b);
}

// Non multiinstance classes like CCConfiguration/AGI/Association and etc we have to dispatch here...
static uint8_t _multiinstance(const ZUNOCommandCmd_t *cmd, int *out, ZUNOCommandPacketReport_t *frame_report, const ZUNOCommandHandlerOption_t *options) {
	int result = ZUNO_UNKNOWN_CMD;

	switch(ZW_CMD_CLASS) {
			case COMMAND_CLASS_SECURITY:
				result = zuno_CCSecurity(cmd, frame_report);
				break ;
			case COMMAND_CLASS_SECURITY_2:
				result = zuno_CCSecurity2(cmd, frame_report);
				break ;
			case COMMAND_CLASS_CONFIGURATION:
				result = zuno_CCConfigurationHandler(cmd, frame_report);
				break ;
			case COMMAND_CLASS_INDICATOR:
				result = zuno_CCIndicatorHandler(cmd, frame_report, options);
				break ;
			case COMMAND_CLASS_ASSOCIATION:
				result = zuno_CCAssociationHandler(cmd, frame_report);
				break ;
			case COMMAND_CLASS_MULTI_CHANNEL_ASSOCIATION:
				result = zuno_CCMultiAssociationHandler(cmd, frame_report);
				break ;
			case COMMAND_CLASS_ZWAVEPLUS_INFO:
				result = zuno_CCZWavePlusInfoHandler(cmd, frame_report);
				break ;
			case COMMAND_CLASS_ASSOCIATION_GRP_INFO:
				result = zuno_CCAssociationGprInfoHandler(cmd, frame_report);
				break ;
			#ifdef WITH_CC_CENTRAL_SCENE
			case COMMAND_CLASS_CENTRAL_SCENE:
				result = zuno_CCCentralSceneHandler(cmd, frame_report);
				break;
			#endif
			#ifdef WITH_CC_SCHEDULE_ENTRY_LOCK
			case COMMAND_CLASS_SCHEDULE_ENTRY_LOCK:
				result = zuno_CCScheduleEntryLockHandler(cmd, frame_report);
				break;
			#endif
			#ifdef WITH_CC_TIME_PARAMETERS
			case COMMAND_CLASS_TIME_PARAMETERS:
				result = zuno_CCTimerParametrsHandler(cmd, frame_report);
				break ;
			#endif
			#ifdef WITH_CC_TIME
			case COMMAND_CLASS_TIME:
				result = zuno_CCTimeHandler(cmd);
				break ;
			#endif
			#ifdef WITH_CC_AUTHENTICATION
			case COMMAND_CLASS_AUTHENTICATION:
				result = zuno_CCAuthenticationHandler(cmd, frame_report);
				break ;
			#endif
			#ifdef WITH_CC_ENTRY_CONTROL
			case COMMAND_CLASS_ENTRY_CONTROL:
				result = zuno_CCEntryControlHandler(cmd, frame_report);
				break ;
			#endif
			#ifdef WITH_CC_USER_CODE
			case COMMAND_CLASS_USER_CODE:
				result = zuno_CCUserCodeHandler(cmd, frame_report);
				break ;
			#endif
			#ifdef WITH_CC_USER_CREDENTIAL
			case COMMAND_CLASS_USER_CREDENTIAL:
				result = zuno_CCUserCredentialHandler(cmd, frame_report);
				break ;
			#endif
			#ifdef WITH_CC_BATTERY
			case COMMAND_CLASS_BATTERY:
				result = zuno_CCBattery(cmd, frame_report);
				break;
			#endif
			#ifdef WITH_CC_WAKEUP
			case COMMAND_CLASS_WAKE_UP:
				result = zuno_CCWakeupHandler(cmd, frame_report);
				break;
			#endif
			default:
				return (true);
	}
	*out = result;
	return (false);
	(void)frame_report;
}

static size_t _isBlockMultiBroadcast(size_t zw_rx_opts, size_t cmdClass, size_t cmd) {
	if ((zw_rx_opts & RECEIVE_STATUS_TYPE_MULTI) == 0)//test multicast
		return (false);
	switch (cmdClass) {
		#ifdef WITH_CC_BASIC
		case COMMAND_CLASS_BASIC:
			if (cmd == BASIC_GET)
				return (false);
			return (true);
			break ;
		#endif
		#ifdef WITH_CC_SWITCH_BINARY
		case COMMAND_CLASS_SWITCH_BINARY:
			if (cmd == SWITCH_BINARY_GET)
				return (false);
			return (true);
			break ;
		#endif
		#ifdef WITH_CC_SWITCH_MULTILEVEL
		case COMMAND_CLASS_SWITCH_MULTILEVEL:
			if (cmd == SWITCH_MULTILEVEL_SUPPORTED_GET)
				return (false);
			if (cmd == SWITCH_MULTILEVEL_GET)
				return (false);
			return (true);
			break ;
		#endif
		case COMMAND_CLASS_SCENE_ACTIVATION:
			return (true);
			break ;
		#ifdef WITH_CC_METER
		case COMMAND_CLASS_METER:
			if (cmd == METER_SUPPORTED_GET)
				return (false);
			if (cmd == METER_GET)
				return (false);
			return (true);
			break ;
		#endif
		#ifdef WITH_CC_METER_TBL_MONITOR
		case COMMAND_CLASS_METER_TBL_MONITOR:
			return (false);
			break ;
		#endif
		#ifdef WITH_CC_SWITCH_COLOR
		case COMMAND_CLASS_SWITCH_COLOR:
			if (cmd == SWITCH_COLOR_GET)
				return (false);
			if (cmd == SWITCH_COLOR_SUPPORTED_GET)
				return (false);
			return (true);
			break ;
		#endif
		#ifdef WITH_CC_WINDOW_COVERING
		case COMMAND_CLASS_WINDOW_COVERING:
			if (cmd == WINDOW_COVERING_SUPPORTED_GET)
				return (false);
			if (cmd == WINDOW_COVERING_GET)
				return (false);
			return (true);
			break ;
		#endif
		#ifdef WITH_CC_SOUND_SWITCH
		case COMMAND_CLASS_SOUND_SWITCH:
			if (cmd == SOUND_SWITCH_CONFIGURATION_SET)
				return (true);
			if (cmd == SOUND_SWITCH_TONE_PLAY_SET)
				return (true);
			return (false);
			break ;
		#endif
		#ifdef WITH_CC_CENTRAL_SCENE
		case COMMAND_CLASS_CENTRAL_SCENE:
			if (cmd == CENTRAL_SCENE_CONFIGURATION_SET)
				return (true);;
			return (false);
			break ;
		#endif
		#ifdef WITH_CC_THERMOSTAT_MODE
		case COMMAND_CLASS_THERMOSTAT_MODE:
			if (cmd == THERMOSTAT_MODE_SUPPORTED_GET)
				return (false);
			if (cmd == THERMOSTAT_MODE_GET)
				return (false);
			return (true);
			break ;
		#endif
		#ifdef WITH_CC_THERMOSTAT_SETPOINT
		case COMMAND_CLASS_THERMOSTAT_SETPOINT:
			if (cmd == THERMOSTAT_SETPOINT_SET)
				return (true);
			return (false);
			break ;
		#endif
		#ifdef WITH_CC_DOORLOCK
		case COMMAND_CLASS_DOOR_LOCK:
			if (cmd == DOOR_LOCK_CONFIGURATION_SET)
				return (true);
			if (cmd == DOOR_LOCK_CONFIGURATION_SET)
				return (true);
			return (false);
			break ;
		#endif
		#ifdef WITH_CC_TIME_PARAMETERS
		case COMMAND_CLASS_TIME_PARAMETERS:
			if (cmd == TIME_PARAMETERS_GET)
				return (false);
			return (true);
			break ;
		#endif
		#ifdef WITH_CC_AUTHENTICATION
		case COMMAND_CLASS_AUTHENTICATION:
			if (cmd == AUTHENTICATION_DATA_SET)
				return (true);
			if (cmd == AUTHENTICATION_TECHNOLOGIES_COMBINATION_SET)
				return (true);
			return (false);
			break ;
		#endif
		#ifdef WITH_CC_ENTRY_CONTROL
		case COMMAND_CLASS_ENTRY_CONTROL:
			if (cmd == ENTRY_CONTROL_CONFIGURATION_SET)
				return (true);
			return (false);
			break ;
		#endif
		#ifdef WITH_CC_USER_CODE
		case COMMAND_CLASS_USER_CODE:
			if (cmd == MASTER_CODE_GET_V2)
				return (false);
			if (cmd == USER_CODE_CHECKSUM_GET_V2)
				return (false);
			if (cmd == USER_CODE_KEYPAD_MODE_GET_V2)
				return (false);
			if (cmd == EXTENDED_USER_CODE_GET_V2)
				return (false);
			if (cmd == USER_CODE_GET_V2)
				return (false);
			if (cmd == USER_CODE_CAPABILITIES_GET_V2)
				return (false);
			if (cmd == USERS_NUMBER_GET_V2)
				return (false);
			return (true);
			break ;
		#endif
		#ifdef WITH_CC_USER_CREDENTIAL
		case COMMAND_CLASS_USER_CREDENTIAL:
			if (cmd == USER_CREDENTIAL_CAPABILITIES_USER_GET)
				return (false);
			if (cmd == USER_CREDENTIAL_CAPABILITIES_CREDENTIAL_GET)
				return (false);
			if (cmd == USER_CREDENTIAL_USER_GET)
				return (false);
			if (cmd == USER_CREDENTIAL_CREDENTIAL_GET)
				return (false);
			if (cmd == USER_CREDENTIAL_ALL_USERS_CHECKSUM_GET)
				return (false);
			if (cmd == USER_CREDENTIAL_USER_CHECKSUM_GET)
				return (false);
			if (cmd == USER_CREDENTIAL_TYPE_CHECKSUM_GET)
				return (false);
			return (true);
			break ;
		#endif
		case COMMAND_CLASS_CONFIGURATION:
			if (cmd == CONFIGURATION_BULK_SET)
				return (true);
			if (cmd == CONFIGURATION_SET)
				return (true);
			if (cmd == CONFIGURATION_DEFAULT_RESET)
				return (true);
			return (false);
			break ;
		case COMMAND_CLASS_INDICATOR:
			if (cmd == INDICATOR_SET_V4)
				return (true);
			return (false);
			break ;
		#ifdef WITH_CC_NOTIFICATION
		case COMMAND_CLASS_NOTIFICATION:
			if (cmd == NOTIFICATION_SET)
				return (true);
			return (false);
			break ;
		#endif
		case COMMAND_CLASS_SECURITY:
			if (cmd == SECURITY_COMMANDS_SUPPORTED_GET)
				return (false);
			if (cmd == SECURITY_NONCE_GET)
				return (false);
			if (cmd == SECURITY_SCHEME_GET)
				return (false);
			return (true);
			break ;
		case COMMAND_CLASS_SECURITY_2:
			if (cmd == SECURITY_2_COMMANDS_SUPPORTED_GET)
				return (false);
			if (cmd == SECURITY_2_NETWORK_KEY_GET)
				return (false);
			if (cmd == KEX_GET)
				return (false);
			if (cmd == SECURITY_2_NONCE_GET)
				return (false);
			return (true);
			break ;
		default:
			return (false);
			break ;
	}
	return (false);
}

static bool _zmeIsS2LevelGreater(uint8_t l1, uint8_t l2){
    if(l1 == SECURITY_KEY_S0){
        if(l2 == SECURITY_KEY_NONE)
          return true;
        return false;
    }
    if(l2 == SECURITY_KEY_S0){
        if(l1 == SECURITY_KEY_NONE)
          return false;
        return true;
    }
    return l1 > l2;
}

static bool _isCCinList(uint8_t cc, uint8_t * cmds, uint8_t count){
    for(int i=0;i<count;i++){
      if(cmds[i] == cc)
        return true;
    }
    return false;

}
static int _appendCC(uint8_t * cc_list, uint8_t &cc_list_sz, uint8_t cc, uint8_t max_sz){
  int i;
  if(_isCCinList(cc, cc_list, cc_list_sz))
	return cc_list_sz;
  if(cc_list_sz >= max_sz){
	// Error HANDLING
    return cc_list_sz;
  }
  cc_list[cc_list_sz++] = cc;
  return cc_list_sz;
  (void)i;
}

uint8_t dynamicCCVersion(uint8_t cc){
	#ifdef WITH_CC_MULTICHANNEL
	if((cc == COMMAND_CLASS_MULTI_CHANNEL) && (ZUNO_CFG_CHANNEL_COUNT > 1))
		return MULTI_CHANNEL_VERSION;
	#endif
	// Loop over all user-defined channels
	for(int i=0;i<ZUNO_CFG_CHANNEL_COUNT;i++){
		uint8_t type = ZUNO_CFG_CHANNEL(i).type-1;
		uint8_t f = ZUNO_CC_TYPES[type].flags;
		for(int j=0;j<ZUNO_CC_TYPES[type].num_ccs;j++){
			uint8_t c = ZUNO_CC_TYPES[type].ccs[j].cc;
			if((cc == COMMAND_CLASS_BASIC) && (f&CHANNEL_TYPE_FLAGS_BASIC_MAPPER)){
				return BASIC_VERSION;
			}
			if(c == cc){
				return ZUNO_CC_TYPES[type].ccs[j].version;
			}
		}
	}
	return 0;
}

#if defined(WITH_CC_WAKEUP) || defined(WITH_CC_BATTERY) || defined(WITH_CC_MULTICHANNEL)
static void _zunoAddBaseCCS(byte ccs) {
	_appendCC(g_zuno_sys->zw_protocol_data->CCLstNSNI, g_zuno_sys->zw_protocol_data->CCLstNSNI_cnt, ccs, MAX_CMDCLASES_NSNI);
	_appendCC(g_zuno_sys->zw_protocol_data->CCLstSec, g_zuno_sys->zw_protocol_data->CCLstSec_cnt, ccs, MAX_CMDCLASES_SECURED);
}
#endif

void _fillZWaveData(uint8_t secure_param){
	ZwZwavePlusInfoIcon_t						icon;
	ZwZwavePlusInfoType_t						info_type;

	// Fill base CCs into NIF
	memcpy(g_zuno_sys->zw_protocol_data->CCLstNSIS, zuno_cmdClassListNSIS_Def, sizeof(zuno_cmdClassListNSIS_Def));
	g_zuno_sys->zw_protocol_data->CCLstNSIS_cnt = sizeof(zuno_cmdClassListNSIS_Def);
	memcpy(g_zuno_sys->zw_protocol_data->CCLstNSNI, zuno_cmdClassListNSNI_Def, sizeof(zuno_cmdClassListNSNI_Def));
	g_zuno_sys->zw_protocol_data->CCLstNSNI_cnt = sizeof(zuno_cmdClassListNSNI_Def);
	memcpy(g_zuno_sys->zw_protocol_data->CCLstSec, zuno_cmdClassListSec_Def, sizeof(zuno_cmdClassListSec_Def));
	g_zuno_sys->zw_protocol_data->CCLstSec_cnt = sizeof(zuno_cmdClassListSec_Def);
	#ifdef LOGGING_DBG
	LOGGING_UART.print("_fillZWaveData NIF:");
	LOGGING_UART.dumpPrint(g_zuno_sys->zw_protocol_data->CCLstSec, g_zuno_sys->zw_protocol_data->CCLstSec_cnt);
	#endif
	if((g_zuno_sys->p_config->secure_mode) && 
	   (secure_param != ZUNO_SECUREPARAM_OFF)){
			_appendCC(g_zuno_sys->zw_protocol_data->CCLstNSNI, g_zuno_sys->zw_protocol_data->CCLstNSNI_cnt, COMMAND_CLASS_SECURITY, MAX_CMDCLASES_NSNI);
			_appendCC(g_zuno_sys->zw_protocol_data->CCLstNSNI, g_zuno_sys->zw_protocol_data->CCLstNSNI_cnt, COMMAND_CLASS_SECURITY_2, MAX_CMDCLASES_NSNI);
	   }
	#ifdef WITH_CC_MULTICHANNEL
	// Add MULTICHANNEL CC only if we need it
	if(ZUNO_CFG_CHANNEL_COUNT > 1){
		_zunoAddBaseCCS(COMMAND_CLASS_MULTI_CHANNEL);
	}
	#endif
	// Loop over all user-defined channels
	for(int i=0;i<ZUNO_CFG_CHANNEL_COUNT;i++){
		uint8_t type = ZUNO_CFG_CHANNEL(i).type-1;
		uint8_t f = ZUNO_CC_TYPES[type].flags;
		if( (ZUNO_CFG_CHANNEL(i).zw_channel != 0) && 
			((ZUNO_CFG_CHANNEL(i).zw_channel & ZWAVE_CHANNEL_MAPPED_BIT) == 0))
			continue;
		for(int j=0;j<ZUNO_CC_TYPES[type].num_ccs;j++){
			uint8_t cc = ZUNO_CC_TYPES[type].ccs[j].cc;
			if(f & CHANNEL_TYPE_FLAGS_UNSECURE_AVALIABLE)
				_appendCC(g_zuno_sys->zw_protocol_data->CCLstNSNI, g_zuno_sys->zw_protocol_data->CCLstNSNI_cnt, cc, MAX_CMDCLASES_NSNI);
			_appendCC(g_zuno_sys->zw_protocol_data->CCLstSec, g_zuno_sys->zw_protocol_data->CCLstSec_cnt,cc, MAX_CMDCLASES_SECURED);
		}
	}
	if(ZUNO_CFG_CHANNEL_COUNT == 0){
		// It's just a control device, only associations
		g_zuno_sys->zw_protocol_data->generic_type = GENERIC_TYPE_GENERIC_CONTROLLER;
		g_zuno_sys->zw_protocol_data->specific_type = SPECIFIC_TYPE_REMOTE_CONTROL_SIMPLE;
		g_zuno_sys->zw_protocol_data->device_icon = ICON_TYPE_GENERIC_REMOTE_CONTROL_SIMPLE;
	} else {
		__zuno_CCZWavePlusGetIcon(0x0, &icon);
		__zuno_CCZWavePlusGetType(0x0, &info_type);
		g_zuno_sys->zw_protocol_data->generic_type = info_type.genericDeviceClass;
		g_zuno_sys->zw_protocol_data->specific_type = info_type.specificDeviceClass;
		g_zuno_sys->zw_protocol_data->device_icon = icon.installerIconType;
	}
	#if defined(WITH_CC_WAKEUP) || defined(WITH_CC_BATTERY)
	switch (zunoGetSleepingMode()) {
		case DEVICE_CONFIGURATION_FLAGS_SLEEP:
			g_zuno_sys->zw_protocol_data->option_mask = APPLICATION_NODEINFO_NOT_LISTENING;
			#if defined(WITH_CC_WAKEUP)
			_zunoAddBaseCCS(COMMAND_CLASS_WAKE_UP);
			#endif
			#if defined(WITH_CC_BATTERY)
			_zunoAddBaseCCS(COMMAND_CLASS_BATTERY);
			#endif
			break ;
		case DEVICE_CONFIGURATION_FLAGS_FLIRS:
			g_zuno_sys->zw_protocol_data->option_mask = APPLICATION_FREQ_LISTENING_MODE_1000ms;
			#if defined(WITH_CC_BATTERY)
			_zunoAddBaseCCS(COMMAND_CLASS_BATTERY);
			#endif
			break ;
		default:
			g_zuno_sys->zw_protocol_data->option_mask = APPLICATION_NODEINFO_LISTENING;
			break ;
	}
	#else
	g_zuno_sys->zw_protocol_data->option_mask = APPLICATION_NODEINFO_LISTENING;
	#endif
	// Reflection of association count 
	g_zuno_sys->zw_protocol_data->association_count = g_zuno_zw_cfg.num_associations;
}
uint16_t _calcCfg16Crc(){
	uint16_t crc16_pos = offsetof(ZUNOZWConfiguation_t, crc16);
	uint16_t crc16 = mCrc.crc16_a(&g_zuno_zw_cfg, crc16_pos);
	return crc16;
}
void _resetUserChannels(){
	memset(&g_zuno_zw_cfg, 0xFF, sizeof(g_zuno_zw_cfg));
	g_zuno_zw_cfg.num_channels = 0;
	g_zuno_zw_cfg.num_associations = 0;
	
}
void _zunoLoadUserChannels(){
	zunoEEPROMRead(EEPROM_USER_CHANNELS_EEPROM_ADDR, EEPROM_USER_CHANNELS_EEPROM_SIZE, (byte*)&g_zuno_zw_cfg);
	uint16_t crc16 = _calcCfg16Crc();
	#if defined(LOGGING_DBG) && defined(DEBUG_CHANNEL_DATA)
	LOGGING_UART.print("CRC16:");
	LOGGING_UART.println(crc16, HEX);
	LOGGING_UART.print("--- LOAD CHANNELS ---");
	LOGGING_UART.dumpPrint(&g_zuno_zw_cfg, sizeof(g_zuno_zw_cfg));
	#endif
	if(crc16 != g_zuno_zw_cfg.crc16){
		#ifdef LOGGING_DBG
		LOGGING_UART.println("*** Wrong channels CRC!. Clear data.");
		#endif
		//memset(&g_zuno_zw_cfg, 0xFF, sizeof(g_zuno_zw_cfg));
		_resetUserChannels();
	}
}
void _zunoSaveUserChannels(){
	g_zuno_zw_cfg.crc16 = _calcCfg16Crc();
	
	#if defined(LOGGING_DBG) && defined(DEBUG_CHANNEL_DATA)
	LOGGING_UART.print("--- SAVE CHANNELS ---");
	LOGGING_UART.dumpPrint(&g_zuno_zw_cfg, sizeof(g_zuno_zw_cfg));
	LOGGING_UART.print("CRC16:");
	LOGGING_UART.println(g_zuno_zw_cfg.crc16, HEX);
	#endif
	zunoEEPROMWrite(EEPROM_USER_CHANNELS_EEPROM_ADDR, EEPROM_USER_CHANNELS_EEPROM_SIZE, (byte*)&g_zuno_zw_cfg);
}

bool __zunoAssociationS2Access(void);
void zunoCommitCfg(){
	uint8_t										req_s2_keys;

	req_s2_keys = 0x0;
	#if defined(WITH_CC_DOORLOCK)
	#ifdef LOGGING_DBG
	if ((g_zuno_sys->zw_protocol_data->req_s2_keys & SKETCH_FLAG_S2_ACCESS_BIT) == 0x0) {
		LOGGING_UART.print(DEBUG_MESSAGE_WARNING":");
		LOGGING_UART.print("DOOR LOCK auto set 'SKETCH_FLAG_S2_ACCESS_BIT'\n");
	}
	#endif
	req_s2_keys = req_s2_keys | SKETCH_FLAG_S2_ACCESS_BIT;
	#endif
	if (__zunoAssociationS2Access() == true) {
	#ifdef LOGGING_DBG
	if ((g_zuno_sys->zw_protocol_data->req_s2_keys & SKETCH_FLAG_S2_ACCESS_BIT) == 0x0) {
		LOGGING_UART.print(DEBUG_MESSAGE_WARNING":");
		LOGGING_UART.print("ASSOCIATION DOOR LOCK auto set 'SKETCH_FLAG_S2_ACCESS_BIT'\n");
	}
	#endif
		req_s2_keys = req_s2_keys | SKETCH_FLAG_S2_ACCESS_BIT;
	}
	g_zuno_sys->zw_protocol_data->req_s2_keys = g_zuno_sys->zw_protocol_data->req_s2_keys | req_s2_keys;
	_zunoSaveUserChannels();
	_fillZWaveData(ZUNO_SECUREPARAM_UNDEFINED);
	#if defined(WITH_CC_DOORLOCK)
	__zunoDoorLockSaveInit();
	#endif
	#if defined(WITH_CC_BASIC)
	zunoBasicSaveInit();
	#endif
	#if defined(WITH_CC_SOUND_SWITCH)
	zunoSoundSwitchSaveInit();
	#endif
	#if defined(WITH_CC_CENTRAL_SCENE)
	void zunoCentralSceneSaveInit(void);
	zunoCentralSceneSaveInit();
	#endif
    zunoSysCall(ZUNO_SYSFUNC_COMMIT_ZWAVEDATA, 0);
}
static bool _zunoS2PkgFilter(const ZUNOCommandCmd_t *cmd){
	uint8_t								s2level;
	uint8_t								rx_s2level;

	s2level = zunoSecurityStatus();
	if(s2level == SECURITY_KEY_NONE)// Node was included without security - we not need to filter anything
		return (false);
	rx_s2level = cmd->zw_rx_secure_opts;
	if(((s2level > SECURITY_KEY_S0) && (rx_s2level == SECURITY_KEY_S0)) || 
		((s2level == SECURITY_KEY_S0) && (rx_s2level == 0)))
		if(ZW_CMD_CLASS == COMMAND_CLASS_MANUFACTURER_SPECIFIC)// Backward compatibility
			return (false);
	if(s2level == rx_s2level)// Highest avaliable S2-level for this node => pass it
		return (false);
	if (_zmeIsS2LevelGreater(s2level, rx_s2level)) // Request level lower than node level - check nonsecure NIF 
	{
		uint8_t cc = ZW_CMD_CLASS;
		
		// Special case for multichannel
		/*
		if(ZUNO_CFG_CHANNEL_COUNT > 1){
			// Multichannel is included 
			if((cc == COMMAND_CLASS_MULTI_CHANNEL)){
				 if(ZW_CMD != MULTI_CHANNEL_CMD_ENCAP){
					return false; // Metadata is avaliable
				 }
				 //cc = cmd->cmd[4];
			} 

		}*/
		if (_isCCinList(cc, (uint8_t*)zuno_cmdClassListNSIS_Def, sizeof(zuno_cmdClassListNSIS_Def)))
			return (false);
	}
	#ifdef LOGGING_DBG
	LOGGING_UART.print(millis());
	LOGGING_UART.println("*** S2 Filtered!"); 
	#endif
	return (true);
}

// Main command handler for incoming z-wave commands
int __zuno_CommandHandler_Out(int rs){
	g_rcv_context.source_node_id = 0;
	return rs;
}

int zuno_CommandHandler(ZUNOCommandCmd_t *cmd) {
	ZUNOCommandPacketReport_t							frame_report;
	ZUNOCommandHandlerOption_t							options;
	int													result;
	bool												supervision;
	bool												multi;

	#if defined(WITH_CC_BATTERY) || defined(WITH_CC_WAKEUP)
	zunoSleepUpdateSendRadioCmd();
	#endif
	// delay(10); // TST!
	#ifdef LOGGING_DBG
	LOGGING_UART.print(millis());
	LOGGING_UART.print("INCOMING  "); 
	zuno_dbgdumpZWPacakge(cmd);
	#endif
	ZWQIncomingStat(cmd);
	if (_zunoS2PkgFilter(cmd))
		return (ZUNO_COMMAND_BLOCKED);
	zunoReportHandler(cmd);
	result = ZUNO_UNKNOWN_CMD;
	g_rcv_context.bMulticast = (cmd->zw_rx_opts & RECEIVE_STATUS_TYPE_MULTI) != 0;
	g_rcv_context.bBroadcast = (cmd->zw_rx_opts & RECEIVE_STATUS_TYPE_BROAD) != 0;
	g_rcv_context.source_node_id = cmd->src_node;

	#if defined(WITH_CC_WAKEUP) || defined(WITH_CC_BATTERY)
	zunoKickSleepTimeout(ZUNO_SLEEP_RX_TIMEOUT);
    //g_wup_sended_notify = true;
 	//zuno_CCWakeup_OnAnyRx();
	#endif
	if ((cmd->zw_rx_opts & RECEIVE_STATUS_TYPE_BROAD) != 0)//test broadcast
		return __zuno_CommandHandler_Out(ZUNO_COMMAND_BLOCKED);
	
	// prepare packet for report
	_fillOutgoingPacket(cmd, &frame_report);
	// If we have multichannel support enabled.
	// Pass the data through it first
	multi = false;
	#ifdef WITH_CC_MULTICHANNEL
	if(ZW_CMD_CLASS == COMMAND_CLASS_MULTI_CHANNEL){
		result = zuno_CCMultichannel(cmd, &frame_report);
		if(result == ZUNO_COMMAND_BLOCKED){
			#ifdef LOGGING_DBG
			LOGGING_UART.println("*** MULTICHANNEL WAS BLOCKED"); 
			#endif
			return __zuno_CommandHandler_Out(result);
		}
		if(result == ZUNO_COMMAND_UNPACKED){
			#ifdef LOGGING_DBG
			LOGGING_UART.print(millis());
			LOGGING_UART.print("UNPACKED:  "); 
			zuno_dbgdumpZWPacakge(cmd);
			#endif
			_fillOutgoingPacket(cmd,  &frame_report);
			multi = true;
		}
	}
	#endif
	if(ZW_CMD_CLASS == COMMAND_CLASS_MANUFACTURER_SPECIFIC) {
		return __zuno_CommandHandler_Out(zuno_CCManufacturerSpecificHandler(cmd, &frame_report));
	} else if (ZW_CMD_CLASS == COMMAND_CLASS_VERSION) {
		return __zuno_CommandHandler_Out(zuno_CCVersionHandler(cmd, &frame_report));
	}
	result = zuno_CCSupervisionUnpack(result, cmd, &frame_report);
	if(result == ZUNO_UNKNOWN_CMD || result == ZUNO_COMMAND_UNPACKED) {
		if (result == ZUNO_COMMAND_UNPACKED)
			supervision = true;
		else
			supervision = false;
		if (_isBlockMultiBroadcast(cmd->zw_rx_opts, ZW_CMD_CLASS, ZW_CMD) == true)
			return __zuno_CommandHandler_Out(ZUNO_COMMAND_BLOCKED);
		options = ZUNO_COMMAND_HANDLER_OPTIONS(cmd->src_node, multi, supervision, ZW_CMD_CLASS);
		// Check if command fits to any existing channel
		if(_multiinstance(cmd, &result, &frame_report, &options) == true) {
			byte zuno_ch = zuno_findTargetChannel(cmd);
			if(zuno_ch == UNKNOWN_CHANNEL){
				#ifdef LOGGING_DBG
				LOGGING_UART.println("**** Can't find channel for last cmd!"); 
				#endif
				return __zuno_CommandHandler_Out(zuno_CCSupervisionReportSyncDefault(&frame_report, result)); // Command doesn't fit => forward it to firmware CommandHandler
			}
			#ifdef LOGGING_DBG
			LOGGING_UART.print("CHANNEL WAS  FOUND:"); 
			LOGGING_UART.println(zuno_ch);
			#endif
			switch(ZW_CMD_CLASS) {
				#ifdef WITH_CC_BASIC
				case COMMAND_CLASS_BASIC:
					result = zuno_CCBasicHandler(zuno_ch, cmd, &frame_report, &options);
					break;
				#endif
				#ifdef WITH_CC_SWITCH_BINARY
				case COMMAND_CLASS_SWITCH_BINARY:
					result = zuno_CCSwitchBinaryHandler(zuno_ch, cmd, &frame_report, &options);
					break;
				#endif
				#ifdef WITH_CC_NOTIFICATION
				case COMMAND_CLASS_NOTIFICATION:
					result = zuno_CCNotificationHandler(zuno_ch, cmd, &frame_report);
					break;
				#endif
				#ifdef WITH_CC_SWITCH_MULTILEVEL
				case COMMAND_CLASS_SWITCH_MULTILEVEL:
					result = zuno_CCSwitchMultilevelHandler(zuno_ch, cmd, &frame_report, &options);
					break;
				#endif
				#ifdef WITH_CC_METER
				case COMMAND_CLASS_METER:
					result = zuno_CCMeterHandler(zuno_ch, cmd, &frame_report);
					break;
				#endif
				#ifdef WITH_CC_METER_TBL_MONITOR
				case COMMAND_CLASS_METER_TBL_MONITOR:
					result = zuno_CCMeterTblMonitorHandler(zuno_ch, cmd, &frame_report);
					break;
				#endif
				#ifdef WITH_CC_DOORLOCK
				case COMMAND_CLASS_DOOR_LOCK:
					result = zuno_CCDoorLockHandler(zuno_ch, cmd, &frame_report);
					break;
				#endif
				#ifdef WITH_CC_SENSOR_MULTILEVEL
				case COMMAND_CLASS_SENSOR_MULTILEVEL:
					result = zuno_CCSensorMultilevelHandler(zuno_ch, cmd, &frame_report);
					break ;
				#endif
				#ifdef WITH_CC_SWITCH_COLOR
				case COMMAND_CLASS_SWITCH_COLOR:
					result = zuno_CCSwitchColorHandler(zuno_ch, cmd, &frame_report, &options);
					break;
				#endif
				#ifdef WITH_CC_WINDOW_COVERING
				case COMMAND_CLASS_WINDOW_COVERING:
					result = zuno_CCWindowCoveringHandler(zuno_ch, cmd, &frame_report, &options);
					break;
				#endif
				#ifdef WITH_CC_SOUND_SWITCH
				case COMMAND_CLASS_SOUND_SWITCH:
					result = zuno_CCSoundSwitchHandler(zuno_ch, cmd, &frame_report, &options);
					break;
				#endif
				#ifdef WITH_CC_THERMOSTAT_MODE
				case COMMAND_CLASS_THERMOSTAT_MODE:
					result = zuno_CCThermostatModeHandler(zuno_ch, cmd, &frame_report);
					break;
				#endif
				#ifdef WITH_CC_THERMOSTAT_SETPOINT
				case COMMAND_CLASS_THERMOSTAT_SETPOINT:
					result = zuno_CCThermostatSetPointHandler(zuno_ch, cmd, &frame_report);
					break;
				#endif
			}
		}
	}
	result = zuno_CCSupervisionReportSyncDefault(&frame_report, result);
	// Do we have any report to send?
	if(result == ZUNO_COMMAND_ANSWERED){
		zunoSendZWPackageAdd(&frame_report);
	}
	return __zuno_CommandHandler_Out(result);
}

__WEAK uint8_t __zunoGetS2AccessManual(void) {
	return ((SECURITY_KEY_S2_UNAUTHENTICATED_BIT | SECURITY_KEY_S2_AUTHENTICATED_BIT | SECURITY_KEY_S0_BIT));
}

__WEAK void __zunoAssociationSetupManual(void) {
}

// Channels fill routines
bool zunoStartDeviceConfiguration() {
	if(zunoInNetwork() && !zunoIsDbgModeOn())
		return false;
	// System-side protocol data
	//memset(g_zuno_sys->zw_protocol_data, 0xFF, sizeof(ZUNOZWaveProtocolData_t));
	g_zuno_sys->zw_protocol_data->association_count = 0;
	g_zuno_sys->zw_protocol_data->CCLstNSIS_cnt = 0;
	g_zuno_sys->zw_protocol_data->CCLstNSNI_cnt = 0;
	g_zuno_sys->zw_protocol_data->CCLstSec_cnt = 0;
	g_zuno_sys->zw_protocol_data->flags = DEFAULT_CONFIG_FLAGS;
	g_zuno_sys->zw_protocol_data->product_id = DEFAULT_PRODUCT_ID;
	g_zuno_sys->zw_protocol_data->req_s2_keys = __zunoGetS2AccessManual();
	// User-side data
	_resetUserChannels();
	//memset(&g_zuno_zw_cfg, 0, sizeof(g_zuno_zw_cfg));
	if (ZUNO_CFG_ASSOCIATION_COUNT == 0x0)
		__zunoAssociationSetupManual();
	return  true;
}
byte getMaxChannelTypes() {
	return sizeof(ZUNO_CC_TYPES)/sizeof(ZUNOChannelCCS_t);
}
byte zuno_findChannelType(byte type, ZUNOChannelCCS_t* types, byte count) {
	byte i;
	for(i=0;i<count;i++){
		if(types[i].type == type)
			return i;
	}
	return UNKNOWN_CHANNEL;
}
#ifdef LOGGING_DBG
void dbgDumpCCType(ZUNOChannelCCS_t * cc_type){
	LOGGING_UART.print("CC TYPE:");
	LOGGING_UART.print(cc_type->type, HEX);
	LOGGING_UART.print(" FLAGS:");
	LOGGING_UART.print(cc_type->flags, HEX);
	LOGGING_UART.print(" CCS[");
	LOGGING_UART.print(cc_type->num_ccs);
	LOGGING_UART.print(" ]=");
	for (int j = 0; j < cc_type->num_ccs; j++)
	{
		LOGGING_UART.print("{ cc:");
		LOGGING_UART.print(cc_type->ccs[j].cc, HEX);
		LOGGING_UART.print(" v:");
		LOGGING_UART.print(cc_type->ccs[j].version, HEX);
		LOGGING_UART.print("} ");
	}
	LOGGING_UART.println("");
}
void dbgCCTypes() {
	static bool fist_run = true;
	if(!fist_run)
		return;
	fist_run = false;	
	delay(2000);
	LOGGING_UART.println("STATIC TYPES:\n-------------------------");
	for(size_t i=0;i<(sizeof(ZUNO_CC_TYPES)/sizeof(ZUNOChannelCCS_t));i++){
		dbgDumpCCType((ZUNOChannelCCS_t*)&ZUNO_CC_TYPES[i]);
	}
	LOGGING_UART.println("\n-------------------------");
}
#endif
// 
void initCCSDataDefault() {
	static bool inited = false;
	if(inited)
		return;
	#ifdef WITH_CC_NOTIFICATION
	zuno_CCNotificationInitData();
	#endif
	#ifdef WITH_CC_WAKEUP
	zuno_CCWakeup_OnDefault();
	#endif
}
// Now you need to use defined. Example WITH_CC_CENTRAL_SCENE for CENTRAL_SCENE
bool zunoAddBaseCCS(byte ccs, byte version){
	return true;
	(void)ccs;
	(void)version;
}
byte zunoAddChannel(byte type, byte subtype, uint32_t options) {
	// Do we have space for the new channel?
	if(ZUNO_CFG_CHANNEL_COUNT >= ZUNO_MAX_MULTI_CHANNEL_NUMBER){
		#ifdef LOGGING_DBG
		LOGGING_UART.println("(!) CHANNELS OVERFLOW");
		#endif
		return UNKNOWN_CHANNEL;
	}
	// Create new channel
	uint8_t ch_i = ZUNO_CFG_CHANNEL_COUNT;
	ZUNO_CFG_CHANNEL(ch_i).type         =   type;
	ZUNO_CFG_CHANNEL(ch_i).sub_type     =   subtype;
	ZUNO_CFG_CHANNEL(ch_i).params[0]    =   options & 0xFF;
	ZUNO_CFG_CHANNEL(ch_i).params[1]    =   (options >> 8)  & 0xFF;
	ZUNO_CFG_CHANNEL(ch_i).params[2]    =   (options >> 16)  & 0xFF;
	ZUNO_CFG_CHANNEL(ch_i).params[3]    =   (options >> 24)  & 0xFF;
	ZUNO_CFG_CHANNEL_COUNT++;
	return ch_i;
}

uint8_t zuno_findChannelByZWChannelIndexChannel(byte endpoint) {
	for(int i=0;i<ZUNO_CFG_CHANNEL_COUNT;i++){
		if(endpoint == 0) {
			if(ZUNO_CFG_CHANNEL(i).zw_channel & ZWAVE_CHANNEL_MAPPED_BIT)
				return ((i));
		} else {
			uint8_t naked_channel = ZUNO_CFG_CHANNEL(i).zw_channel & (~ZWAVE_CHANNEL_MAPPED_BIT);
			if(naked_channel == endpoint)
				return ((i));
		}
		
	}
	return ((UNKNOWN_CHANNEL));
}

static bool aux_check_last_reporttime(uint8_t ch, uint32_t ticks) {

	#if defined(WITH_CC_SENSOR_MULTILEVEL) || defined(WITH_CC_METER) || defined(WITH_CC_METER_TBL_MONITOR)
	switch (ZUNO_CFG_CHANNEL(ch).type) {
		#ifdef WITH_CC_SENSOR_MULTILEVEL
		case ZUNO_SENSOR_MULTILEVEL_CHANNEL_NUMBER:
		#endif
		#ifdef WITH_CC_METER
		case ZUNO_METER_CHANNEL_NUMBER:
		#endif
			{
				uint32_t ch_time  = __getSyncVar(&(g_channels_data.last_report_time[ch]));
				uint32_t dtime = NEXT_ML_REPORTDELAY; // Z-Wave specification requires 30second silence interval between SensorMultilevel/Meter reports 
				if(g_zuno_sys->p_config->flags & ZUNO_CFGFILE_FLAG_DBG){ // Set param #1 (DBG) first
					// We can dynamically modify report interval using parameter #11 for test pusposes
					dtime = g_zuno_sys->p_config->ml_interval;
					dtime *= 100; // We use seconds for param #11, so we have to convert it to sytem timer intervals 
				}
				bool can_send = (ch_time == 0) || ((ticks -  ch_time) > dtime);
				if(can_send){
					/*
					#ifdef LOGGING_DBG
					LOGGING_UART.print("Time check ok. channel:");
					LOGGING_UART.print(ch);
					LOGGING_UART.print(" last time:");
					LOGGING_UART.print(ch_time);
					LOGGING_UART.print(" current time:");
					LOGGING_UART.print(ticks);
					#endif*/
					
				}
				return can_send; // We can't send too frequent for these CCs
			}
			break ;
		default:
			break ;
	}
	#endif
	(void)ch;
	(void)ticks;
	return true;
}

bool _zunoHasPendingReports(){
	if (zunoInNetwork() == false)
		return (false);
	if(__getSyncVar(&g_channels_data.sys_reports) != 0)
		return true;
	if(__getSyncVar(&g_channels_data.report_map) != 0)
		return true;	
	return (false);
}


bool zunoIsChannelUpdated(uint8_t ch){
	if(ch < 1)
		ch = 1;
	ch -= 1;
	return __isSyncMapChannelAndClear(&g_channels_data.update_map, ch);
}
bool zunoIsChannelRequested(uint8_t ch){
	return __isSyncMapChannelAndClear(&g_channels_data.request_map, ch);
}
bool zunoIsBatteryRequested(){
	return __isSyncMapChannelAndClear(&g_channels_data.sys_requests, SYSREQUEST_MAP_BATTERY_BIT);
}
void _zunoMarkChannelRequested(uint8_t ch){
	__setSyncMapChannel(&g_channels_data.request_map, ch);
}
void _zunoMarkChannelUpdated(uint8_t ch){
	__setSyncMapChannel(&g_channels_data.update_map, ch);
}
void _zunoMarkSystemClassRequested(uint8_t systembit){
	__setSyncMapChannel(&g_channels_data.sys_requests, systembit);
}
bool __zunoDispatchPendingBatteryReport(){
	return __isSyncMapChannelAndClear(&g_channels_data.sys_reports, SYSREPORT_MAP_BATTERY_BIT);
}
bool __zunoDispatchPendingWUPReport(){
	return __isSyncMapChannelAndClear(&g_channels_data.sys_reports, SYSREPORT_MAP_WAKEUP_BIT);
}
void zunoSendBatteryReport() {
	__setSyncMapChannel(&g_channels_data.sys_reports, SYSREPORT_MAP_BATTERY_BIT);
}
void zunoSendWakeUpNotification(){
	__setSyncMapChannel(&g_channels_data.sys_reports, SYSREPORT_MAP_WAKEUP_BIT);
}
bool _zunoIsWUPLocked();
bool zunoIsIclusionLatchClosed();

void zunoSendReportSet(byte channel, ZUNOCommandPacketReport_t *frame_report, const ZUNOCommandHandlerOption_t *options, const void *add) {
	int													rs;
	uint8_t												outside;
	uint8_t												ch;

	switch (options->cmd_class) {
		case COMMAND_CLASS_INDICATOR:
			outside = true;
			break ;
		default:
			outside = false;
			break ;
	}
	if (outside == false)
		ch = ZUNO_CFG_CHANNEL(channel).zw_channel;
	else
		ch = 0x0;
	fillOutgoingReportPacketAsync(frame_report, ch);
	frame_report->info.report.option = options[0x0];
	frame_report->info.report.outside = outside;
	frame_report->info.report.valid = true;
	if (outside == false) {
		switch(ZUNO_CFG_CHANNEL(channel).type) {
			#ifdef WITH_CC_SWITCH_BINARY
			case ZUNO_SWITCH_BINARY_CHANNEL_NUMBER:
				rs = zuno_CCSwitchBinaryReport(channel, &frame_report->info);
				break ;
			#endif
			#ifdef WITH_CC_SWITCH_MULTILEVEL
			case ZUNO_SWITCH_MULTILEVEL_CHANNEL_NUMBER:
				rs = zuno_CCSwitchMultilevelReport(channel, &frame_report->info);
				break ;
			#endif
			#ifdef WITH_CC_WINDOW_COVERING
			case ZUNO_WINDOW_COVERING_CHANNEL_NUMBER:
				rs = zuno_CCWindowCoveringReport(channel, &frame_report->info, (const ZwWindowCoveringReport_t *)add);
				break ;
			#endif
			#ifdef WITH_CC_SOUND_SWITCH
			case ZUNO_SOUND_SWITCH_CHANNEL_NUMBER:
				rs = zuno_CCSoundSwitchReport(channel, &frame_report->info);
				break;
			#endif
			default:
				rs = ZUNO_COMMAND_PROCESSED;
				break ;
		}
	}
	else {
		switch (options->cmd_class) {
			case COMMAND_CLASS_INDICATOR:
				rs = zuno_CCIndicatorReport(&frame_report->info, (const ZwIndicatorReport_t *)add);
				break ;
			default:
				rs = ZUNO_COMMAND_PROCESSED;
				break ;
		}
	}
	if (rs != ZUNO_COMMAND_ANSWERED)
		return ;
	zunoSendZWPackageAdd(frame_report);
}

void zunoSendReportHandler(uint32_t ticks, ZUNOCommandPacketReport_t *frame_report) {

	if(zunoCheckSystemQueueStatus(QUEUE_CHANNEL_LLREPORT)){
		#ifdef LOGGING_DBG
		//LOGGING_UART.println("Report queue is busy.");
		#endif
		return;
	}

	// Check if device is included to network
	if(zunoNID() == 0)
        return; // it doesn't => go away
	
	#ifdef WITH_CC_BATTERY
	if (zunoIsSleepingMode() == true) {
		if(__zunoDispatchPendingBatteryReport())
			zunoSendBatteryReportHandler();
	}
	#endif
	#ifdef WITH_CC_WAKEUP
	// Send WUP Notification report only if there are no channel reports & user is ready to sleep 
	if(zunoIsSleepingMode() == true && !zunoIsSleepLocked()){
		uint32_t sys_reports = __getSyncVar(&g_channels_data.sys_reports);
		uint32_t usr_reports = __getSyncVar(&g_channels_data.report_map);
		// #ifdef LOGGING_DBG
		// LOGGING_UART.print("CCWUP U:");
    	// LOGGING_UART.print(usr_reports);
		// LOGGING_UART.print(" S:");
    	// LOGGING_UART.println(sys_reports);
		// #endif
		if((usr_reports == 0) && 
	    	((sys_reports & (~(1 << SYSREPORT_MAP_WAKEUP_BIT))) == 0)){
				if(__zunoDispatchPendingWUPReport()){
					if(!zunoIsIclusionLatchClosed()) // If inclusion process started there is no need to send WUPNotification
						zuno_sendWUP_NotificationReport();
					return;
			}
		}
	}
	// If Wakeup Notification was sent and controller haven't unblocked wakeup => we don't send anything else unsolicited
	// All the traffic is from the controller side only!
	if(_zunoIsWUPLocked()){
		return;
	}
	#endif
	//
	int rs = ZUNO_UNKNOWN_CMD;
	for(uint8_t ch = 0; ch < ZUNO_MAX_MULTI_CHANNEL_NUMBER; ch++) {
		if(__getSyncVar(&g_channels_data.report_map) == 0)
			break;
		if(!__isSyncMapChannel(&g_channels_data.report_map, ch))
			continue;
		if(!aux_check_last_reporttime(ch, ticks)){
			#ifdef LOGGING_DBG
			//LOGGING_UART.print("Report timeout for channel: ");
			//LOGGING_UART.println(ch);
			#endif
			#ifdef WITH_CC_BATTERY
			if(zunoIsSleepingMode() == true){
				__clearSyncMapChannel(&g_channels_data.report_map, ch);
			}
			#endif
			continue;
		}
		#ifdef LOGGING_DBG
		LOGGING_UART.print("REPORT CH:");
		LOGGING_UART.print(ch);
		LOGGING_UART.print(" TYPE:");
		LOGGING_UART.println(ZUNO_CFG_CHANNEL(ch).type);
		#endif
		fillOutgoingReportPacketAsync(frame_report, ZUNO_CFG_CHANNEL(ch).zw_channel);
		__setSyncVar(&(g_channels_data.last_report_time[ch]), ticks);
		rs = ZUNO_UNKNOWN_CMD;
		
		switch(ZUNO_CFG_CHANNEL(ch).type) {
			#ifdef WITH_CC_SWITCH_BINARY
			case ZUNO_SWITCH_BINARY_CHANNEL_NUMBER:
				rs = zuno_CCSwitchBinaryReport(ch, &frame_report->info);
				break;
			#endif
			#ifdef WITH_CC_SWITCH_MULTILEVEL
			case ZUNO_SWITCH_MULTILEVEL_CHANNEL_NUMBER:
				rs = zuno_CCSwitchMultilevelReport(ch, &frame_report->info);
				break;
			#endif
			#ifdef WITH_CC_SWITCH_COLOR
			case ZUNO_SWITCH_COLOR_CHANNEL_NUMBER:
				rs = zuno_CCSwitchColorReport(ch,  &frame_report->info);
				break;
			#endif
			#ifdef WITH_CC_WINDOW_COVERING
			case ZUNO_WINDOW_COVERING_CHANNEL_NUMBER:
				rs = zuno_CCWindowCoveringReport(ch, &frame_report->info, NULL);
				break;
			#endif
			#ifdef WITH_CC_SOUND_SWITCH
			case ZUNO_SOUND_SWITCH_CHANNEL_NUMBER:
				rs = zuno_CCSoundSwitchReport(ch, &frame_report->info);
				break;
			#endif
			#ifdef WITH_CC_DOORLOCK
			case ZUNO_DOORLOCK_CHANNEL_NUMBER:
				rs = zuno_CCDoorLockReport(ch, &frame_report->info);
				break;
			#endif
			#ifdef WITH_CC_NOTIFICATION
			case ZUNO_SENSOR_BINARY_CHANNEL_NUMBER:
				rs = __zuno_CCNotificationReport(ch, NULL, &frame_report->info);
				break;
			#endif
			#ifdef WITH_CC_SENSOR_MULTILEVEL
			case ZUNO_SENSOR_MULTILEVEL_CHANNEL_NUMBER:
				rs = zuno_CCSensorMultilevelReport(ch, &frame_report->info);
				break;
			#endif
			#ifdef WITH_CC_METER
			case ZUNO_METER_CHANNEL_NUMBER:
				rs = zuno_CCMeterReport(ch, NULL, &frame_report->info);
				break;
			#endif
			#if defined(WITH_CC_THERMOSTAT_MODE) || defined(WITH_CC_THERMOSTAT_SETPOINT)
			case ZUNO_THERMOSTAT_CHANNEL_NUMBER:
				rs = zuno_CCThermostatReport(ch, &frame_report->info);
				break;
			#endif
			default:
				break;
		}

		if(rs == ZUNO_COMMAND_ANSWERED || rs == ZUNO_COMMAND_PROCESSED){
			__clearSyncMapChannel(&g_channels_data.report_map, ch);
		}
		if(rs == ZUNO_COMMAND_ANSWERED){
			node_id_t					node;
			node = __getSyncVar16(&g_channels_data.sync_nodes[ch]);
			memcpy(&frame_report->info.packet.aux_data[0], &node, sizeof(node));
			zunoSendZWPackageAdd(frame_report);
			return; // Only one report along one call
		}
		
	}
}
void zunoSendReport(byte ch){
	if((ch < 1) || (ch > (ZUNO_CFG_CHANNEL_COUNT)))
		return;
	
	ch--;
	// Supervision context
	node_id_t node_id = zunoGetSupervisionHost();
	// If it's Multicast do not report value to sender
	if((g_rcv_context.source_node_id != 0) && (g_rcv_context.bMulticast || g_rcv_context.bBroadcast)){
		return; // Do not report to any node!!!
		//node_id = g_rcv_context.source_node_id;
	}
	// We have to store supervision context if we have it
	// Z-Wave protocol requires to exclude supervision host's node when device is reporting
	__setSyncVar16(&g_channels_data.sync_nodes[ch], node_id);
	// Set needed bit field of report
	__setSyncMapChannel(&g_channels_data.report_map, ch);
}
void zunoSetupBitMask(byte * arr, byte b, byte max_sz){
	byte byte_index = b >> 3;
	byte bit_index = b & 0x07;
	if(byte_index >= max_sz)
		return;
	arr[byte_index] |= 1 << bit_index;
}

void zunoSendZWPackage(ZUNOCommandPacket_t * pkg){
	ZWQPushPackage(pkg);
}

void zunoSendZWPackageAdd(ZUNOCommandPacketReport_t *frame) {
	zunoSendZWPackage(&frame->info);
}

uint32_t _zunoSetterValue2Cortex(uint8_t * packet, uint8_t sz){
	uint32_t res = 0;
	while(sz){
		res <<= 8;
		res |= *packet;
		packet++;
		sz--;
	}
	return  res;
}
int _zunoTransposeSecurityLevel(uint8_t sec) {
	switch (sec) {
		case SECURITY_KEY_NONE:
			return -2;
		case SECURITY_KEY_S0:
			return  -1;
		default:
			return sec;
	}
	return sec;
}
static uint8_t DEPRECATED_RF_EVENTS[] = {
											ZUNO_SYS_EVENT_START, 
											ZUNO_SYS_EVENT_GOSLEEP,
											ZUNO_SYS_EVENT_QUICKWAKEUP,
											ZUNO_SYS_EVENT_STAY_AWAKE,
											ZUNO_SYS_EVENT_EEPROMRESET,
											ZUNO_SYS_EVENT_LEARNSTARTED,
											ZUNO_SYS_EVENT_SLEEP_MODEEXC,
											ZUNO_SYS_EVENT_QUEUE_OVERLOAD,
											ZUNO_SYS_EVENT_INVALID_TX_REQUEST

										}; 

void zunoSendTestPackage(uint8_t * data, uint8_t len, uint8_t dst_node_id){
	ZUNOCommandPacketReport_t			frame;
	fillOutgoingRawPacket(&frame.info, frame.data, 0, ZUNO_PACKETFLAGS_TEST | QUEUE_CHANNEL_CONTROL, dst_node_id);
	//frame.packet.flags |= ZUNO_PACKETFLAGS_TEST
    frame.info.packet.cmd[0] = COMMAND_CLASS_MANUFACTURER_SPECIFIC;
    frame.info.packet.cmd[1] = MANUFACTURER_SPECIFIC_LOGGER_REPORT;
	frame.info.packet.len = 2 + len;
	frame.info.packet.zw_rx_secure_opts = 0;
	memcpy(&frame.info.packet.cmd[2], (uint8_t*)data, len);
	zunoSendZWPackageAdd(&frame);
}
void zunoRFLogger(ZUNOSysEvent_t * ev){
	int i;
	ZUNOCommandPacketReport_t			frame;
	if((g_zuno_sys->p_config->flags & ZUNO_CFGFILE_FLAG_RFLOG) == 0)
		return; // RF logging switched off
	if(zunoNID() == 0)
        return; // Z-Uno is not in network
	// Filter some events to avoid deadlocks
	for(i=0;i<(int)sizeof(DEPRECATED_RF_EVENTS);i++)
		if(ev->event == DEPRECATED_RF_EVENTS[i])
			return;
	fillOutgoingReportPacketAsync(&frame, 0);
    frame.info.packet.cmd[0] = COMMAND_CLASS_MANUFACTURER_SPECIFIC;
    frame.info.packet.cmd[1] = MANUFACTURER_SPECIFIC_LOGGER_REPORT;
	frame.info.packet.len = 2 + 13;
    uint8_t * p_data  = &frame.info.packet.cmd[2];
    uint32_t systime_data  = millis();
    p_data++;
	_zme_memcpy(p_data, (uint8_t*)&systime_data, sizeof(systime_data));
	p_data += sizeof(systime_data);
    *p_data = ev->event;
	p_data++;
	_zme_memcpy(p_data, (uint8_t*)&ev->params[0], sizeof(ev->params[0]));
	p_data += sizeof(ev->params[0]);
	_zme_memcpy(p_data, (uint8_t*)&ev->params[1], sizeof(ev->params[1]));
	zunoSendZWPackageAdd(&frame);
}
uint8_t zunoZMEFrequency2Region(uint8_t freqi){
  return zmeMapDict((uint8_t*)FREQ_TBL_CONV, sizeof(FREQ_TBL_CONV), freqi, false);
}
uint8_t zunoRegion2ZMEFrequency(uint8_t freqi){
  return zmeMapDict((uint8_t*)FREQ_TBL_CONV, sizeof(FREQ_TBL_CONV), freqi, true);
}