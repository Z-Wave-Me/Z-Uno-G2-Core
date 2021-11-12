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

#include "ZUNO_AutoChannels.h"

enum {
	HADLER_ARGTYPE_1UB,
	HADLER_ARGTYPE_2UB,
	HADLER_ARGTYPE_4UB,
	HADLER_ARGTYPE_1SB = HADLER_ARGTYPE_1UB | 0x08,
	HADLER_ARGTYPE_2SB = HADLER_ARGTYPE_2UB | 0x08,
	HADLER_ARGTYPE_4SB = HADLER_ARGTYPE_4UB | 0x08
};
#define HANDLER_DESCRIPTOR_TYPE_MASK     0x0F
#define HANDLER_DESCRIPTOR_LEN_SHIFT     0x04
#define HANDLER_DESCRIPTOR_LEN_MASK      0x03
#define HANDLER_DESCRIPTOR_SIGNED_BIT    0x80

typedef struct ZUnoChannelDtaHandler_s{
	void * p_handler;     
					   // |    7   | 6 |  5    |   4 | 3 |2|1|0|
	byte   descriptor; // | SIGNED | - | 2^NUM_BYTES |  TYPE   |
}ZUnoChannelDtaHandler_t;

ZUnoChannelDtaHandler_t g_zuno_channelhandlers_map[ZUNO_MAX_MULTI_CHANNEL_NUMBER];
ZUNOCommandPacket_t g_outgoing_main_packet;
ZUNOCommandPacket_t g_outgoing_report_packet;
uint8_t             g_outgoing_main_data[MAX_ZW_PACKAGE];
uint8_t             g_outgoing_report_data[MAX_ZW_PACKAGE];
// Report data
//-------------------------------------------------------------------------------------------------


typedef struct ZUNOChannelsData_s{
	uint32_t update_map;
	uint32_t request_map;
	uint32_t report_map;
	uint32_t sys_reports;
	uint32_t sys_requests;
	uint32_t last_report_time[ZUNO_MAX_MULTI_CHANNEL_NUMBER];
}ZUNOChannelsData_t;
ZUNOChannelsData_t g_channels_data;

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
void ZWCCSetup(){
	memset(&g_channels_data, 0, sizeof(g_channels_data));
	#ifdef WITH_CC_BATTERY
	zuno_CCBattery_OnSetup();
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
		case ZUNO_FLOWSTOP_CHANNEL_NUMBER:
		case ZUNO_SIREN_CHANNEL_NUMBER:
			if(cmd_class == COMMAND_CLASS_SWITCH_BINARY)
				return true;
			if(cmd_class == COMMAND_CLASS_BASIC)
				return true;
			break;
		case ZUNO_SWITCH_MULTILEVEL_CHANNEL_NUMBER:
		case ZUNO_BLINDS_CHANNEL_NUMBER:
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
		case ZUNO_DOORLOCK_CHANNEL_NUMBER:
			if(cmd_class == COMMAND_CLASS_DOOR_LOCK)
				return true;
			break;

		case ZUNO_THERMOSTAT_CHANNEL_NUMBER:
			if(cmd_class == COMMAND_CLASS_THERMOSTAT_MODE)
				return true;
			if(cmd_class == COMMAND_CLASS_THERMOSTAT_SETPOINT)
				return true;
			break;
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
byte zuno_findTargetChannel(ZUNOCommandPacket_t * cmd) {
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

bool fillOutgoingRawPacket(ZUNOCommandPacket_t * p, uint8_t * d, uint8_t ch, uint8_t flags, uint8_t dst){
	bool res = true;
	memset(p, 0, sizeof(ZUNOCommandPacket_t));
	memset(d, 0, MAX_ZW_PACKAGE);
	p->cmd = d + MAX_ZWTRANSPORT_ENCAP; // Greetings from ZAF creators
	p->flags 	= flags;
	p->dst_node	= dst; 
	p->src_node  = zunoNID();
	p->src_zw_channel  = ZUNO_CFG_CHANNEL(ch).zw_channel; //& ~(ZWAVE_CHANNEL_MAPPED_BIT);
	p->zw_rx_opts = ZWAVE_PLUS_TX_OPTIONS;
	p->zw_rx_secure_opts = 0xFF; // Ask system to detect the security level automatically
								 // In most cases it uses highest avaliable level
	return res;
}
void fillOutgoingPacket(ZUNOCommandPacket_t * cmd) {
	
	fillOutgoingRawPacket(&g_outgoing_main_packet, g_outgoing_main_data, 0, 0, cmd->src_node);
	g_outgoing_main_packet.cmd[0] = cmd->cmd[0];  // the same command class
	g_outgoing_main_packet.cmd[1] = cmd->cmd[1]+1; // in most cases report = get+1
	// Reply as we were asked
	g_outgoing_main_packet.src_zw_channel    = cmd->dst_zw_channel;
	g_outgoing_main_packet.dst_zw_channel    = cmd->src_zw_channel;

}
void fillOutgoingReportPacket(uint8_t ch) {
	fillOutgoingRawPacket(&g_outgoing_report_packet, 
						  g_outgoing_report_data,
						 ch, ZUNO_PACKETFLAGS_GROUP, ZUNO_LIFELINE_GRP);
}
#ifdef LOGGING_UART
void zuno_dbgdumpZWPacakge(ZUNOCommandPacket_t * cmd){
	
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
	LOGGING_UART.print(" OPTS:");
	LOGGING_UART.print(cmd->zw_rx_opts, HEX);
	LOGGING_UART.print(" DATA:");
	LOGGING_UART.dumpPrint(cmd->cmd, cmd->len);
	LOGGING_UART.println("");
}
#endif

uint8_t *zuno_AddCommonClass(uint8_t *b) {
	b++[0] = COMMAND_CLASS_ZWAVEPLUS_INFO;
	b++[0] = COMMAND_CLASS_ASSOCIATION;
	b++[0] = COMMAND_CLASS_MULTI_CHANNEL_ASSOCIATION;
	b++[0] = COMMAND_CLASS_ASSOCIATION_GRP_INFO;
	b++[0] = COMMAND_CLASS_SUPERVISION;
	return (b);
}

// Non multiinstance classes like CCConfiguration/AGI/Association and etc we have to dispatch here...
static uint8_t _multiinstance(ZUNOCommandPacket_t *cmd, int *out) {
	int result = ZUNO_UNKNOWN_CMD;

	switch(ZW_CMD_CLASS) {
			case COMMAND_CLASS_SECURITY:
				result = zuno_CCSecurity(cmd);
				break ;
			case COMMAND_CLASS_SECURITY_2:
				result = zuno_CCSecurity2(cmd);
				break ;
			case COMMAND_CLASS_CONFIGURATION:
				result = zuno_CCConfigurationHandler(cmd);
				break ;
			case COMMAND_CLASS_ASSOCIATION:
				result = zuno_CCAssociationHandler(cmd);
				break ;
			case COMMAND_CLASS_MULTI_CHANNEL_ASSOCIATION:
				result = zuno_CCMultiAssociationHandler(cmd);
				break ;
			case COMMAND_CLASS_ZWAVEPLUS_INFO:
				result = zuno_CCZWavePlusInfoHandler(cmd);
				break ;
			case COMMAND_CLASS_ASSOCIATION_GRP_INFO:
				result = zuno_CCAssociationGprInfoHandler(cmd);
				break ;
			#ifdef WITH_CC_TIME_PARAMETERS
			case COMMAND_CLASS_TIME_PARAMETERS:
				result = zuno_CCTimerParametrsHandler(cmd);
				break ;
			#endif
			#ifdef WITH_CC_BATTERY
			case COMMAND_CLASS_BATTERY:
				result = zuno_CCBattery(cmd);
				break;
			#endif
			#ifdef WITH_CC_WAKEUP
			case COMMAND_CLASS_WAKE_UP:
				result = zuno_CCWakeupHandler(cmd);
				break;
			#endif
			default:
				return (true);
	}
	*out = result;
	return (false);
}

static size_t _testMultiBroadcast(size_t zw_rx_opts, size_t cmdClass, size_t cmd) {
	if ((zw_rx_opts & RECEIVE_STATUS_TYPE_MULTI) == 0)//test multicast
		return (true);
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
		case COMMAND_CLASS_CONFIGURATION:
			if (cmd == CONFIGURATION_BULK_SET)
				return (true);
			if (cmd == CONFIGURATION_SET)
				return (true);
			if (cmd == CONFIGURATION_DEFAULT_RESET)
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

// Main command handler for incoming z-wave commands
int zuno_CommandHandler(ZUNOCommandPacket_t *cmd) {
	int result = ZUNO_UNKNOWN_CMD;
	
	#ifdef LOGGING_DBG
	LOGGING_UART.print(millis());
	LOGGING_UART.print("INCOMING  "); 
	zuno_dbgdumpZWPacakge(cmd);
	#endif
	#if defined(WITH_CC_WAKEUP) || defined(WITH_CC_BATTERY)
	zunoKickSleepTimeout(ZUNO_SLEEP_RX_TIMEOUT);
    //g_wup_sended_notify = true;
 	//zuno_CCWakeup_OnAnyRx();
	#endif
	if ((cmd->zw_rx_opts & RECEIVE_STATUS_TYPE_BROAD) != 0)//test broadcast
		return (ZUNO_COMMAND_BLOCKED);
	// prepare packet for report
	fillOutgoingPacket(cmd);
	// If we have multichannel support enabled.
	// Pass the data through it first
	#ifdef WITH_CC_MULTICHANNEL
	if(ZW_CMD_CLASS == COMMAND_CLASS_MULTI_CHANNEL){
		result = zuno_CCMultichannel(cmd);
		if(result == ZUNO_COMMAND_BLOCKED){
			return result;
		}
		if(result == ZUNO_COMMAND_UNPACKED){
			#ifdef LOGGING_DBG
			LOGGING_UART.print(millis());
			LOGGING_UART.print("UNPACKED:  "); 
			zuno_dbgdumpZWPacakge(cmd);
			#endif
			fillOutgoingPacket(cmd);
			if (ZW_CMD_CLASS == COMMAND_CLASS_VERSION) {
				return (zuno_CCVersionHandler(cmd));
			}
		}
	}
	#endif
	result = zuno_CCSupervisionUnpack(result, cmd);
	if(result == ZUNO_UNKNOWN_CMD || result == ZUNO_COMMAND_UNPACKED) {
		if (_testMultiBroadcast(cmd->zw_rx_opts, ZW_CMD_CLASS, ZW_CMD) == false)
			return (ZUNO_COMMAND_BLOCKED);
		#if ZUNO_ASSEMBLY_TYPE == ZUNO_UNO
		zunoReportHandler(cmd);
		#endif
		// Check if command fits to any existing channel
		if(_multiinstance(cmd, &result) == true) {
			byte zuno_ch = zuno_findTargetChannel(cmd);
			if(zuno_ch == UNKNOWN_CHANNEL){
				#ifdef LOGGING_DBG
				LOGGING_UART.println("**** Can't find channel for last cmd!"); 
				#endif
				return (zuno_CCSupervisionReport(result, 0x0)); // Command doesn't fit => forward it to firmware CommandHandler
			}
			#ifdef LOGGING_DBG
			LOGGING_UART.print("CHANNEL WAS  FOUND:"); 
			LOGGING_UART.println(zuno_ch);
			#endif
			switch(ZW_CMD_CLASS) {
				#ifdef WITH_CC_BASIC
				case COMMAND_CLASS_BASIC:
					result = zuno_CCBasicHandler(zuno_ch, cmd);
					break;
				#endif
				#ifdef WITH_CC_SWITCH_BINARY
				case COMMAND_CLASS_SWITCH_BINARY:
					result = zuno_CCSwitchBinaryHandler(zuno_ch, cmd);
					break;
				#endif
				#ifdef WITH_CC_NOTIFICATION
				case COMMAND_CLASS_NOTIFICATION:
					result = zuno_CCNotificationHandler(zuno_ch, cmd);
					break;
				#endif
				#ifdef WITH_CC_SWITCH_MULTILEVEL
				case COMMAND_CLASS_SWITCH_MULTILEVEL:
					result = zuno_CCSwitchMultilevelHandler(zuno_ch, cmd);
					break;
				#endif
				#ifdef WITH_CC_METER
				case COMMAND_CLASS_METER:
					result = zuno_CCMeterHandler(zuno_ch, cmd);
					break;
				#endif
				#ifdef WITH_CC_METER_TBL_MONITOR
				case COMMAND_CLASS_METER_TBL_MONITOR:
					result = zuno_CCMeterTblMonitorHandler(zuno_ch, cmd);
					break;
				#endif
				#ifdef WITH_CC_DOORLOCK
				case COMMAND_CLASS_DOOR_LOCK:
					result = zuno_CCDoorLockHandler(zuno_ch, cmd);
					break;
				#endif
				#ifdef WITH_CC_SENSOR_MULTILEVEL
				case COMMAND_CLASS_SENSOR_MULTILEVEL:
					result = zuno_CCSensorMultilevelHandler(zuno_ch, cmd);
					break ;
				#endif
				#ifdef WITH_CC_SWITCH_COLOR
				case COMMAND_CLASS_SWITCH_COLOR:
					result = zuno_CCSwitchColorHandler(zuno_ch, cmd);
					break;
				#endif
				#ifdef WITH_CC_THERMOSTAT_MODE
				case COMMAND_CLASS_THERMOSTAT_MODE:
					result = zuno_CCThermostatModeHandler(zuno_ch, cmd);
					break;
				#endif
				#ifdef WITH_CC_THERMOSTAT_SETPOINT
				case COMMAND_CLASS_THERMOSTAT_SETPOINT:
					result = zuno_CCThermostatSetPointHandler(zuno_ch, cmd);
					break;
				#endif
			}
		}
	}
	result = zuno_CCSupervisionReport(result, 0x0);
	// Do we have any report to send?
	if(result == ZUNO_COMMAND_ANSWERED){
		zunoSendZWPackage(&g_outgoing_main_packet);
	}
	return result;
}

// Universal staff for CC support
int32_t zuno_callGetter(byte val_type, byte ch, void * handler){
	if(handler == 0)
		return 0;
	switch(val_type){
		case HADLER_ARGTYPE_1UB:
		case HADLER_ARGTYPE_1SB:
			if(ch != UNKNOWN_CHANNEL)
				return ((zuno_multigetter1ub_t*)handler)(ch);
			return ((zuno_singlegetter1ub_t*)handler)();
		case HADLER_ARGTYPE_2UB:
		case HADLER_ARGTYPE_2SB:
			if(ch != UNKNOWN_CHANNEL)
				return ((zuno_multigetter2ub_t*)handler)(ch);
			return ((zuno_singlegetter2ub_t*)handler)();
		case HADLER_ARGTYPE_4UB:
		case HADLER_ARGTYPE_4SB:
			if(ch != UNKNOWN_CHANNEL)
				return ((zuno_multigetter4ub_t*)handler)(ch);
			return ((zuno_singlegetter4ub_t*)handler)();
	}
	return (0);
}
void zuno_callSetter(byte val_type, byte ch, void * handler, int32_t value) {
	if(handler == 0)
		return;
	switch(val_type){
		case HADLER_ARGTYPE_1UB:
		case HADLER_ARGTYPE_1SB: {
				uint8_t v =  value & 0xFF;
				if(ch != UNKNOWN_CHANNEL)
				{
					((zuno_multisetter1ub_t*)handler)(ch, v);
					 break;
				}
				((zuno_singlesetter1ub_t*)handler)(v);
			}
			break;
		case HADLER_ARGTYPE_2UB:
		case HADLER_ARGTYPE_2SB:{
				uint16_t v =  value & 0xFFFF;
				if(ch != UNKNOWN_CHANNEL){
					((zuno_multisetter2ub_t*)handler)(ch, v);
					break;
				}
				((zuno_singlesetter2ub_t*)handler)(v);
			}
			break;
		case HADLER_ARGTYPE_4UB:
		case HADLER_ARGTYPE_4SB:
			if(ch != UNKNOWN_CHANNEL)
			{
				((zuno_multisetter4ub_t*)handler)(ch, value);
				break;
			}
			((zuno_singlesetter4ub_t*)handler)(value);
			break;
	}
}
int zuno_getMappedValue(byte val_type, byte ch, void * handler){
	switch(val_type){
		case HADLER_ARGTYPE_1UB:
		case HADLER_ARGTYPE_1SB:
			if(ch != UNKNOWN_CHANNEL)
				return ((uint8_t*)handler)[ch];
			return *((uint8_t*)handler);
		case HADLER_ARGTYPE_2UB:
		case HADLER_ARGTYPE_2SB:
			if(ch != UNKNOWN_CHANNEL)
				return ((uint16_t*)handler)[ch];
			return *((uint16_t*)handler);
		case HADLER_ARGTYPE_4UB:
		case HADLER_ARGTYPE_4SB:
			if(ch != UNKNOWN_CHANNEL)
				return ((uint32_t*)handler)[ch];
			return *((uint32_t*)handler);
	}
	return (0);
}

void zuno_setMappedValue(byte val_type, byte ch, void * handler, int32_t value){
	switch(val_type){
		case HADLER_ARGTYPE_1UB:
		case HADLER_ARGTYPE_1SB:
			if(ch != UNKNOWN_CHANNEL)
			{
				((uint8_t*)handler)[ch] = value & 0xFF;
				break;
			}
			*((uint8_t*)handler) = value & 0xFF;
			break;
		case HADLER_ARGTYPE_2UB:
		case HADLER_ARGTYPE_2SB:
			if(ch != UNKNOWN_CHANNEL)
			{
				((uint16_t*)handler)[ch] = value & 0xFFFF;
				break;
			}
			*((uint16_t*)handler) = value & 0xFFFF;
			break;
		case HADLER_ARGTYPE_4UB:
		case HADLER_ARGTYPE_4SB:
			if(ch != UNKNOWN_CHANNEL)
			{
				((uint32_t*)handler)[ch] = value;
				break;
			}
			*((uint32_t*)handler) = value;
			break;
	}
}
int32_t zuno_universalGetter1P(byte zuno_ch) {
	if(zuno_ch>ZUNO_CFG_CHANNEL_COUNT)
		return 0;
	if(g_zuno_channelhandlers_map[zuno_ch].p_handler == NULL)
		return 0;
	byte type = g_zuno_channelhandlers_map[zuno_ch].descriptor & HANDLER_DESCRIPTOR_TYPE_MASK;
	byte val_type = (g_zuno_channelhandlers_map[zuno_ch].descriptor >> HANDLER_DESCRIPTOR_LEN_SHIFT);
	switch(type){
		case CHANNEL_HANDLER_EMPTY:
			return 0;
		case CHANNEL_HANDLER_SINGLE_GETTER:
			return zuno_callGetter(val_type, UNKNOWN_CHANNEL, g_zuno_channelhandlers_map[zuno_ch].p_handler);
		case CHANNEL_HANDLER_SINGLE_GETTERSETTER:
		{
			zuno_handler_single_gettersetter_t * p_gs = (zuno_handler_single_gettersetter_t *) g_zuno_channelhandlers_map[zuno_ch].p_handler;
			return zuno_callGetter(val_type, UNKNOWN_CHANNEL, p_gs->getter);
		}
		case CHANNEL_HANDLER_SINGLE_VALUEMAPPER:
			return zuno_getMappedValue(val_type, UNKNOWN_CHANNEL, g_zuno_channelhandlers_map[zuno_ch].p_handler);
		case CHANNEL_HANDLER_MULTI_GETTER:{
			zuno_handler_multi_getter_t * p_mg = (zuno_handler_multi_getter_t *) g_zuno_channelhandlers_map[zuno_ch].p_handler;
			return zuno_callGetter(val_type, zuno_ch-p_mg->offset, p_mg->getter);
		}
		case CHANNEL_HANDLER_MULTI_GETTERSETTER:
		{
			zuno_handler_multi_gettersetter_t * p_mgs = (zuno_handler_multi_gettersetter_t *) g_zuno_channelhandlers_map[zuno_ch].p_handler;
			return zuno_callGetter(val_type, zuno_ch-p_mgs->offset, p_mgs->getter);
		}
		case CHANNEL_HANDLER_MULTI_MAPPER:{
			zuno_handler_multi_getter_t * p_mw = (zuno_handler_multi_getter_t *) g_zuno_channelhandlers_map[zuno_ch].p_handler;
			return zuno_getMappedValue(val_type, zuno_ch - p_mw->offset, p_mw->getter);
		}
		case CHANNEL_HANDLER_SINGLE_THERMOSTAT:
		{
			zuno_handler_single_thermostat_t *p_gs = (zuno_handler_single_thermostat_t *) g_zuno_channelhandlers_map[zuno_ch].p_handler;
			return zuno_callGetter(val_type, UNKNOWN_CHANNEL, p_gs->getter1);
		}
		case CHANNEL_HANDLER_MULTI_THERMOSTAT:
		{
			zuno_handler_multi_thermostat_t *p_mgs = (zuno_handler_multi_thermostat_t *) g_zuno_channelhandlers_map[zuno_ch].p_handler;
			return zuno_callGetter(val_type, zuno_ch-p_mgs->offset, p_mgs->getter1);
		}
	}
	return 0;
}

void zuno_universalSetter1P(byte zuno_ch, int32_t value) {
	if(zuno_ch > ZUNO_CFG_CHANNEL_COUNT)
		return;
	byte type = g_zuno_channelhandlers_map[zuno_ch].descriptor & HANDLER_DESCRIPTOR_TYPE_MASK;
	byte val_type = (g_zuno_channelhandlers_map[zuno_ch].descriptor >> HANDLER_DESCRIPTOR_LEN_SHIFT);
	switch(type) {
		case CHANNEL_HANDLER_SINGLE_GETTERSETTER: {
				zuno_handler_single_gettersetter_t * p_gs = (zuno_handler_single_gettersetter_t *) g_zuno_channelhandlers_map[zuno_ch].p_handler;
				zuno_callSetter(val_type, UNKNOWN_CHANNEL, p_gs->setter, value);
			}
			break;
		case CHANNEL_HANDLER_SINGLE_VALUEMAPPER:
			zuno_setMappedValue(val_type, UNKNOWN_CHANNEL, g_zuno_channelhandlers_map[zuno_ch].p_handler, value);
			break;
		case CHANNEL_HANDLER_MULTI_GETTERSETTER: {
				zuno_handler_multi_gettersetter_t * p_mgs = (zuno_handler_multi_gettersetter_t *) g_zuno_channelhandlers_map[zuno_ch].p_handler;
				zuno_callSetter(val_type, zuno_ch-p_mgs->offset, p_mgs->setter, value);
			}
			break;
		case CHANNEL_HANDLER_MULTI_MAPPER: {
				zuno_handler_multi_getter_t * p_mw = (zuno_handler_multi_getter_t *) g_zuno_channelhandlers_map[zuno_ch].p_handler;
				zuno_setMappedValue(val_type, zuno_ch - p_mw->offset, p_mw->getter, value);
			}
			break;
		case CHANNEL_HANDLER_SINGLE_THERMOSTAT: {
				zuno_handler_single_thermostat_t *p_gs = (zuno_handler_single_thermostat_t *) g_zuno_channelhandlers_map[zuno_ch].p_handler;
				zuno_callSetter(val_type, UNKNOWN_CHANNEL, p_gs->setter1, value);
			}
			break;
		case CHANNEL_HANDLER_MULTI_THERMOSTAT: {
				zuno_handler_multi_thermostat_t * p_mgs = (zuno_handler_multi_thermostat_t *) g_zuno_channelhandlers_map[zuno_ch].p_handler;
				zuno_callSetter(val_type, zuno_ch-p_mgs->offset, p_mgs->setter1, value);
			}
			break;
	}
}

static uint32_t _callGetter2P(byte val_type, byte ch, void * handler, uint32_t value){
	if (handler == 0)
		return (0);
	
	switch(val_type) {
		case HADLER_ARGTYPE_1UB:
		case HADLER_ARGTYPE_1SB:
			if(ch != UNKNOWN_CHANNEL)
				return (((zuno_multigetter1ub_2p_t *)handler)(ch, value));
			else
				return (((zuno_singlegetter1ub_2p_t *)handler)(value));
			break;
		case HADLER_ARGTYPE_2UB:
		case HADLER_ARGTYPE_2SB:
			if(ch != UNKNOWN_CHANNEL)
				return (((zuno_multigetter2ub_2p_t *)handler)(ch, value));
			else
				return (((zuno_singlegetter2ub_2p_t *)handler)(value));
			break;
		case HADLER_ARGTYPE_4UB:
		case HADLER_ARGTYPE_4SB:
			if(ch != UNKNOWN_CHANNEL)
				return (((zuno_multigetter4ub_2p_t *)handler)(ch, value));
			else
				return (((zuno_singlegetter4ub_2p_t *)handler)(value));
			break;
		default:
			return (0);
	}
	
}


uint32_t zuno_universalGetter2P(byte zuno_ch, uint32_t value) {
	void							*lp;
	uint8_t							type;
	uint8_t							val_type;

	if (zuno_ch > ZUNO_CFG_CHANNEL_COUNT)
		return (0);
	lp = &g_zuno_channelhandlers_map[zuno_ch];
	type = ((ZUnoChannelDtaHandler_t *)lp)->descriptor & HANDLER_DESCRIPTOR_TYPE_MASK;
	val_type = (((ZUnoChannelDtaHandler_t *)lp)->descriptor >> HANDLER_DESCRIPTOR_LEN_SHIFT);
	lp = ((ZUnoChannelDtaHandler_t *)lp)->p_handler;
	switch(type) {
		case CHANNEL_HANDLER_SINGLE_GETTERSETTER_2P:
			return _callGetter2P(val_type, UNKNOWN_CHANNEL, ((zuno_handler_single_gettersetter_t *)lp)->getter, value);
		case CHANNEL_HANDLER_MULTI_GETTERSETTER_2P:
			return _callGetter2P(val_type, zuno_ch - ((zuno_handler_multi_gettersetter_t *)lp)->offset, ((zuno_handler_multi_gettersetter_t *)lp)->getter, value);
		case CHANNEL_HANDLER_SINGLE_THERMOSTAT:
			return _callGetter2P(HADLER_ARGTYPE_2UB, UNKNOWN_CHANNEL, ((zuno_handler_single_thermostat_t *)lp)->getter2, value);
		case CHANNEL_HANDLER_MULTI_THERMOSTAT:
			return _callGetter2P(HADLER_ARGTYPE_2UB, zuno_ch - ((zuno_handler_multi_thermostat_t *)lp)->offset, ((zuno_handler_multi_thermostat_t *)lp)->getter2, value);
	}
	return 0;
}

static void _callSetter2P(byte val_type, byte ch, void *handler, uint32_t value, uint32_t value_add) {
	if (handler == 0)
		return ;
	
	switch(val_type) {
		case HADLER_ARGTYPE_1UB:
		case HADLER_ARGTYPE_1SB:
			value = value & 0xFF;
			value_add = value_add & 0xFF;
			if(ch != UNKNOWN_CHANNEL)
				((zuno_multisetter1ub_2p_t *)handler)(ch, value, value_add);
			else
				((zuno_singlesetter1ub_2p_t *)handler)(value, value_add);
			break;
		case HADLER_ARGTYPE_2UB:
		case HADLER_ARGTYPE_2SB:
			value = value & 0xFFFF;
			value_add = value_add & 0xFFFF;
			if(ch != UNKNOWN_CHANNEL)
				((zuno_multisetter2ub_2p_t *)handler)(ch, value, value_add);
			else
				((zuno_singlesetter2ub_2p_t *)handler)(value, value_add);
			break;
		case HADLER_ARGTYPE_4UB:
		case HADLER_ARGTYPE_4SB:
			if(ch != UNKNOWN_CHANNEL)
				((zuno_multisetter4ub_2p_t *)handler)(ch, value, value_add);
			else
				((zuno_singlesetter4ub_2p_t *)handler)(value, value_add);
			break;
		default:
			return ;
	}
	
}

void zuno_universalSetter2P(byte zuno_ch, uint32_t value, uint32_t value_add) {
	void							*lp;
	uint8_t							type;
	uint8_t							val_type;

	if(zuno_ch > ZUNO_CFG_CHANNEL_COUNT)
		return;
	lp = &g_zuno_channelhandlers_map[zuno_ch];
	type = ((ZUnoChannelDtaHandler_t *)lp)->descriptor & HANDLER_DESCRIPTOR_TYPE_MASK;
	val_type = (((ZUnoChannelDtaHandler_t *)lp)->descriptor >> HANDLER_DESCRIPTOR_LEN_SHIFT);
	lp = ((ZUnoChannelDtaHandler_t *)lp)->p_handler;
	switch(type) {
		case CHANNEL_HANDLER_SINGLE_GETTERSETTER_2P:
			_callSetter2P(val_type, UNKNOWN_CHANNEL, ((zuno_handler_single_gettersetter_t *)lp)->setter, value, value_add);
			break;
		case CHANNEL_HANDLER_MULTI_GETTERSETTER_2P:
			_callSetter2P(val_type, zuno_ch - ((zuno_handler_multi_gettersetter_t *)lp)->offset, ((zuno_handler_multi_gettersetter_t *)lp)->setter, value, value_add);
			break;
		case CHANNEL_HANDLER_SINGLE_THERMOSTAT:
			_callSetter2P(HADLER_ARGTYPE_2UB, UNKNOWN_CHANNEL, ((zuno_handler_single_thermostat_t *)lp)->setter2, value, value_add);
			break;
		case CHANNEL_HANDLER_MULTI_THERMOSTAT:
			_callSetter2P(HADLER_ARGTYPE_2UB, zuno_ch - ((zuno_handler_multi_thermostat_t *)lp)->offset, ((zuno_handler_multi_thermostat_t *)lp)->setter2, value, value_add);
			break;
	}
}


// Channels fill routines
bool zunoStartDeviceConfiguration() {
	if(zunoInNetwork())
		return false;
	memset(g_zuno_sys->zwave_cfg, 0, sizeof(ZUNODeviceConfiguation_t));
	g_zuno_sys->flags = DEFAULT_CONFIG_FLAGS;
	g_zuno_sys->zwave_cfg->security_keys = SECURITY_KEY_S2_UNAUTHENTICATED_BIT | SECURITY_KEY_S0_BIT;
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
static void initCCSData() {
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
// Adds user-defined command class support to main end-point NIF and Secure NIF. Be careful with that! 
bool zunoAddBaseCCS(byte ccs, byte version){
	if(ZUNO_CFG_BASE_CCS_NUM >= ZUNO_MAX_CUSTOM_CCS)
		return false;
	ZUNO_CFG_BASECCS(ZUNO_CFG_BASE_CCS_NUM).cc = ccs;
	ZUNO_CFG_BASECCS(ZUNO_CFG_BASE_CCS_NUM).version = version;
	ZUNO_CFG_BASE_CCS_NUM++;
	return true;
}
byte zunoAddChannel(byte type, byte subtype, byte options) {
	#ifdef LOGGING_DBG
	// dbgCCTypes();
	#endif
	initCCSData();
	// Do we have space for the new channel?
	if(ZUNO_CFG_CHANNEL_COUNT >= ZUNO_MAX_MULTI_CHANNEL_NUMBER)
		return UNKNOWN_CHANNEL;
	// 
	byte type_index = zuno_findChannelType(type, ZUNO_CFG_TYPES, ZUNO_CFG_TYPE_COUNT);
	// We have to add new type to device
	if(type_index == UNKNOWN_CHANNEL) {
		// Do we have space for the new CC type?
		if(ZUNO_CFG_TYPE_COUNT >= ZUNO_MAX_CCTYPES)
			return UNKNOWN_CHANNEL;
		// Fill the type structure from predefined array.
		// type index starts from 1, so we have to decrement it
		int const_type_index =  zuno_findChannelType(type, (ZUNOChannelCCS_t*)ZUNO_CC_TYPES, getMaxChannelTypes());
		if(const_type_index == UNKNOWN_CHANNEL){
			#ifdef LOGGING_DBG
			LOGGING_UART.print("***ERROR: Can't find CCTYPE for:");
			LOGGING_UART.println(type, HEX);
			#endif
			return UNKNOWN_CHANNEL;
		}
		memcpy(&ZUNO_CFG_TYPE(ZUNO_CFG_TYPE_COUNT), &ZUNO_CC_TYPES[const_type_index], sizeof(ZUNOChannelCCS_t));
		ZUNO_CFG_TYPE_COUNT++;
	}
	byte ch_i = ZUNO_CFG_CHANNEL_COUNT;
	if(ch_i == 0){
		g_zuno_sys->zwave_cfg->device_generic_type      =   ZUNO_DEV_TYPES[type-1].gen_type;
		g_zuno_sys->zwave_cfg->device_specific_type     =   ZUNO_DEV_TYPES[type-1].spec_type;
		g_zuno_sys->zwave_cfg->device_icon              =   ZUNO_DEV_TYPES[type-1].icon;
		g_zuno_sys->zwave_cfg->device_app_icon          =   ZUNO_DEV_TYPES[type-1].app_icon;
	}
	// Create new channel
	ZUNO_CFG_CHANNEL(ch_i).type         =   type;
	ZUNO_CFG_CHANNEL(ch_i).sub_type     =   subtype;
	ZUNO_CFG_CHANNEL(ch_i).params[0]    =   options;
	ZUNO_CFG_CHANNEL_COUNT++;
	return ch_i;
}

void zunoAppendChannelHandler(byte ch, byte value_size, byte type, void * handler) {
	g_zuno_channelhandlers_map[ch].descriptor = (((value_size >> 1)&HANDLER_DESCRIPTOR_LEN_MASK) << HANDLER_DESCRIPTOR_LEN_SHIFT) | (type & HANDLER_DESCRIPTOR_TYPE_MASK);
	g_zuno_channelhandlers_map[ch].p_handler = handler;
}
ZUNOChannel_t * zuno_findChannelByZWChannel(byte zw_ch) {
	for(int i=0;i<ZUNO_CFG_CHANNEL_COUNT;i++){
		byte naked_channel = ZUNO_CFG_CHANNEL(i).zw_channel & (~ZWAVE_CHANNEL_MAPPED_BIT);
		if(naked_channel == zw_ch)
			return &(ZUNO_CFG_CHANNEL(i));
	}
	return NULL;
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
				if(g_zuno_sys->cfg_flags & ZUNO_CFGFILE_FLAG_DBG){ // Set param #1 (DBG) first
					// We can dynamically modify report interval using parameter #11 for test pusposes
					dtime = g_zuno_sys->cfg_mlinterval;
					dtime *= 100; // We use seconds for param #11, so we have to convert it to sytem timer intervals 
				}
				bool can_send = (ch_time == 0) || ((ticks -  ch_time) > dtime);
				if(can_send){
					#ifdef LOGGING_DBG
					LOGGING_UART.print("Time check ok. channel:");
					LOGGING_UART.print(ch);
					LOGGING_UART.print(" last time:");
					LOGGING_UART.print(ch_time);
					LOGGING_UART.print(" current time:");
					LOGGING_UART.print(ticks);
					#endif
					
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
void zunoSendReportHandler(uint32_t ticks) {
	// Check if device is included to network
	if(zunoNID() == 0)
        return; // it doesn't => go away
	#ifdef WITH_CC_BATTERY
	if(__zunoDispatchPendingBatteryReport()){
		zunoSendBatteryReportHandler();
		return;
	}
	#endif
	#ifdef WITH_CC_WAKEUP
	// Send WUP Notification report only if there are no channel reports & user is ready to sleep 
	if(!zunoIsSleepLocked()){
		uint32_t sys_reports = __getSyncVar(&g_channels_data.sys_reports);
		uint32_t usr_reports = __getSyncVar(&g_channels_data.report_map);
		if((usr_reports == 0) && 
	    	((sys_reports & (~(1 << SYSREPORT_MAP_WAKEUP_BIT))) == 0)){
				if(__zunoDispatchPendingWUPReport()){
					zuno_sendWUP_NotificationReport();
					return;
			}
		}
	}
	// If Wakeup Notification has been sent and controller haven't unblocked wakeup => we don't send anything else unsolicited
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
			continue;
		}
		#ifdef LOGGING_DBG
		LOGGING_UART.print("REPORT CH:");
		LOGGING_UART.print(ch);
		LOGGING_UART.print(" TYPE:");
		LOGGING_UART.println(ZUNO_CFG_CHANNEL(ch).type);
		#endif
		fillOutgoingReportPacket(ch);
		__setSyncVar(&(g_channels_data.last_report_time[ch]), ticks);
		rs = ZUNO_UNKNOWN_CMD;
		switch(ZUNO_CFG_CHANNEL(ch).type) {
			#ifdef WITH_CC_SWITCH_BINARY
			case ZUNO_SWITCH_BINARY_CHANNEL_NUMBER:
				rs = zuno_CCSwitchBinaryReport(ch, false);
				break;
			#endif
			#ifdef WITH_CC_SWITCH_MULTILEVEL
			case ZUNO_SWITCH_MULTILEVEL_CHANNEL_NUMBER:
				rs = zuno_CCSwitchMultilevelReport(ch, false);
				break;
			#endif
			#ifdef WITH_CC_SWITCH_COLOR
			case ZUNO_SWITCH_COLOR_CHANNEL_NUMBER:
				rs = zuno_CCSwitchColorReport(ch, NULL);
				break;
			#endif
			#ifdef WITH_CC_DOORLOCK
			case ZUNO_DOORLOCK_CHANNEL_NUMBER:
				rs = zuno_CCDoorLockReport(ch, false);
				break;
			#endif
			#ifdef WITH_CC_NOTIFICATION
			case ZUNO_SENSOR_BINARY_CHANNEL_NUMBER:
				rs = zuno_CCNotificationReport(ch, NULL);
				break;
			#endif
			#ifdef WITH_CC_SENSOR_MULTILEVEL
			case ZUNO_SENSOR_MULTILEVEL_CHANNEL_NUMBER:
				rs = zuno_CCSensorMultilevelReport(ch, false);
				break;
			#endif
			#ifdef WITH_CC_METER
			case ZUNO_METER_CHANNEL_NUMBER:
				rs = zuno_CCMeterReport(ch, NULL);
				break;
			#endif
			#if defined(WITH_CC_THERMOSTAT_MODE) || defined(WITH_CC_THERMOSTAT_SETPOINT)
			case ZUNO_THERMOSTAT_CHANNEL_NUMBER:
				rs = zuno_CCThermostatReport(ch);
				break;
			#endif
			default:
				break;
		}
		if(rs == ZUNO_COMMAND_ANSWERED){
			zunoSendZWPackage(&g_outgoing_report_packet);
		}
		if(rs == ZUNO_COMMAND_ANSWERED || rs == ZUNO_COMMAND_PROCESSED){
			__clearSyncMapChannel(&g_channels_data.report_map, ch);
			break; // Only one report per 1 pass
		}
	}
}

void zunoSendReport(byte ch){
	if((ch < 1) || (ch > (ZUNO_CFG_CHANNEL_COUNT)))
		return;
	ch--;
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
	if(zunoNID() == 0) { // We are out of network - don't send anything
		#ifdef LOGGING_DBG
		LOGGING_UART.print(millis());
		LOGGING_UART.println(" Package was dropped! NodeID==0");
		#endif
		return;
		
	}
	#if defined(WITH_CC_WAKEUP) || defined(WITH_CC_BATTERY)
	zunoKickSleepTimeout(ZUNO_SLEEP_TX_TIMEOUT);
	#endif
    #ifdef LOGGING_DBG
	LOGGING_UART.print("\n >>> (");
	LOGGING_UART.print(millis());
	LOGGING_UART.print(") OUTGOING PACKAGE: ");
	zuno_dbgdumpZWPacakge(pkg);
	#endif
	// DBG
	//g_outgoing_packet.src_zw_channel    = 0;
	//g_outgoing_packet.dst_zw_channel    = 0;
	// If the channel "mapped to" main channel => report twice
	byte last_ch = pkg->src_zw_channel;
    if(pkg->src_zw_channel & ZWAVE_CHANNEL_MAPPED_BIT){
		pkg->src_zw_channel = 0;
		zunoSysCall(ZUNO_SYSFUNC_SENDPACKET, 1, pkg);
		pkg->src_zw_channel = last_ch & ~(ZWAVE_CHANNEL_MAPPED_BIT);
	}
    zunoSysCall(ZUNO_SYSFUNC_SENDPACKET, 1, pkg); // DBG
	pkg->src_zw_channel = last_ch; // Bring it back!
}	
