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
#include "./includes/ZWSupportTimer.h"

#define UNKNOWN_CHANNEL       0xFF 

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
ZUNOCommandPacket_t g_outgoing_packet;

uint8_t             g_outgoing_data[MAX_ZW_PACKAGE];

// Report data
//-------------------------------------------------------------------------------------------------
typedef struct ZUnoReportDta_s{
	uint32_t channels_mask;
	uint32_t last_report_time[ZUNO_MAX_MULTI_CHANNEL_NUMBER];
}ZUnoReportDta_t;
volatile ZUnoReportDta_t g_report_data;
//-------------------------------------------------------------------------------------------------
void ZWCCSetup(){
	#ifdef WITH_CC_BATTERY
	zuno_CCBattery_OnSetup();
	#endif
	#ifdef WITH_CC_WAKEUP
	zuno_CCWakeup_OnSetup();
	#endif
}
bool zuno_compare_channeltypeCC(ZUNOChannel_t *channel, uint8_t *cmd_bytes) {
	uint8_t	cmd_class;

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
			if(cmd_class != COMMAND_CLASS_SENSOR_MULTILEVEL)
				return false;
			if(cmd_bytes[1] == SENSOR_MULTILEVEL_SUPPORTED_GET)
				return true;
			if(cmd_bytes[2] == channel->sub_type)
				return true;
			break;
		case ZUNO_SWITCH_COLOR_CHANNEL_NUMBER:
			if(cmd_class == COMMAND_CLASS_SWITCH_COLOR)
				return true;
			break;
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
			if(cmd_bytes[0] == COMMAND_CLASS_METER)
				return true;
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
	for(i=0;i<ZUNO_CFG_CHANNEL_COUNT;i++){
		if(compare_zw_channel(ZUNO_CFG_CHANNEL(i).zw_channel,cmd->dst_zw_channel)) //ZUNO_CFG_CHANNEL(N).zw_channel == cmd->dst_zw_channel)
			if(zuno_compare_channeltypeCC(&(ZUNO_CFG_CHANNEL(i)), cmd->cmd))
				return i;
		
	}
	return UNKNOWN_CHANNEL;
}


void fillOutgoingPacket(ZUNOCommandPacket_t * cmd) {
	memset(&g_outgoing_packet, 0, sizeof(ZUNOCommandPacket_t));
	memset(g_outgoing_data, 0, MAX_ZW_PACKAGE);
	g_outgoing_packet.cmd = g_outgoing_data + MAX_ZWTRANSPORT_ENCAP; // Greetings from ZAF creators
	g_outgoing_packet.cmd[0] = cmd->cmd[0];  // the same command class
	g_outgoing_packet.cmd[1] = cmd->cmd[1]+1; // in most cases report = get+1
	// Reply as we were asked
	g_outgoing_packet.src_node          = zunoNID();
	g_outgoing_packet.dst_node          = cmd->src_node;
	g_outgoing_packet.src_zw_channel    = cmd->dst_zw_channel;
	g_outgoing_packet.dst_zw_channel    = cmd->src_zw_channel;
	g_outgoing_packet.zw_rx_secure_opts = cmd->zw_rx_secure_opts;
	g_outgoing_packet.zw_rx_opts        = ZWAVE_PLUS_TX_OPTIONS;
}
void fillOutgoingReportPacket(uint8_t ch) {
	memset(&g_outgoing_packet, 0, sizeof(ZUNOCommandPacket_t));
	memset(g_outgoing_data, 0, MAX_ZW_PACKAGE);
	g_outgoing_packet.cmd = g_outgoing_data + MAX_ZWTRANSPORT_ENCAP; // Greetings from ZAF creators
	g_outgoing_packet.flags 	= ZUNO_PACKETFLAGS_GROUP;
	g_outgoing_packet.dst_node	= ZUNO_LIFELINE_GRP; 
	g_outgoing_packet.src_node  = zunoNID();
	g_outgoing_packet.src_zw_channel  = ZUNO_CFG_CHANNEL(ch).zw_channel; //& ~(ZWAVE_CHANNEL_MAPPED_BIT);
	g_outgoing_packet.zw_rx_opts = ZWAVE_PLUS_TX_OPTIONS;

	// ZUNO_CFG_CHANNEL(ch)
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

// Non multiinstance classes like CCConfiguration/AGI/Association and etc we have to dispatch here...
static uint8_t _multiinstance(ZUNOCommandPacket_t *cmd, int *out) {
	int result = ZUNO_UNKNOWN_CMD;

	switch(ZW_CMD_CLASS) {
			case COMMAND_CLASS_CONFIGURATION:
				#ifdef WITH_CC_CONFIGURATION
				result = zuno_CCConfigurationHandler(cmd);
				#endif
				break ;
			case COMMAND_CLASS_ASSOCIATION:
				result = zuno_CCAssociationHandler(cmd);
				break ;
			case COMMAND_CLASS_MULTI_CHANNEL_ASSOCIATION:
				result = zuno_CCMultiAssociationHandler(cmd);
				break ;
			case COMMAND_CLASS_ASSOCIATION_GRP_INFO:
				result = zuno_CCAssociationGprInfoHandler(cmd);
				break ;
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

// Main command handler for incoming z-wave commands
int zuno_CommandHandler(ZUNOCommandPacket_t * cmd) {
	int result = ZUNO_UNKNOWN_CMD;
	
	#ifdef LOGGING_DBG
	LOGGING_UART.print(millis());
	LOGGING_UART.print("INCOMING  "); 
	zuno_dbgdumpZWPacakge(cmd);
	#pragma message "LOGGING ON"
	#endif
	#ifdef WITH_CC_WAKEUP
 	zuno_CCWakeup_OnAnyRx();
	#endif
	// prepare packet for report
	fillOutgoingPacket(cmd);
	// If we have multichannel support enabled.
	// Pass the data through it first
	#ifdef WITH_CC_MULTICHANNEL
	if(ZW_CMD_CLASS == COMMAND_CLASS_MULTICHANNEL){
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
		}
	}
	#endif
	// Check if command fits to any existing channel
	if((result != ZUNO_COMMAND_ANSWERED) && (result != ZUNO_COMMAND_PROCESSED) && _multiinstance(cmd, &result) == true){
		byte zuno_ch = zuno_findTargetChannel(cmd);
		if(zuno_ch == UNKNOWN_CHANNEL){
			#ifdef LOGGING_DBG
			LOGGING_UART.println("**** Can't find channel for last cmd!"); 
			#endif
			return ZUNO_UNKNOWN_CMD; // Command doesn't fit => forward it to firmware CommandHandler
		}
		#ifdef LOGGING_DBG
		LOGGING_UART.print("CHANNEL WAS  FOUND:"); 
		LOGGING_UART.println(zuno_ch);
		#endif
		switch(ZW_CMD_CLASS){
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
			#ifdef WITH_CC_DOORLOCK
			case COMMAND_CLASS_DOOR_LOCK:
				result = zuno_CCDoorLockHandler(zuno_ch, cmd);
				break;
			#endif
			#ifdef WITH_CC_SENSORMULTILEVEL
			case COMMAND_CLASS_SENSOR_MULTILEVEL:
				result = zuno_CCSensorMultilevelHandler(zuno_ch, cmd);
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
	// Do we have any report to send?
	if(result == ZUNO_COMMAND_ANSWERED){
		zunoSendZWPackage(&g_outgoing_packet);
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
			((zuno_singlesetter2ub_t*)handler)(value);
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
	for(int i=0;i<(sizeof(ZUNO_CC_TYPES)/sizeof(ZUNOChannelCCS_t));i++){
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
void zunoSetS2Keys(byte keys){
	g_zuno_sys->zwave_cfg->security_keys = keys;
}
void zunoSetSleepingMode(byte mode){
	g_zuno_sys->zwave_cfg->flags &= ~(DEVICE_CONFIGURATION_FLAGS_MASK_SLEEP);
	g_zuno_sys->zwave_cfg->flags |= (mode & DEVICE_CONFIGURATION_FLAGS_MASK_SLEEP);
}
void zunoSetZWChannel(byte ch, byte zw_channel) {
	ZUNO_CFG_CHANNEL(ch).zw_channel = zw_channel;
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

// Main timer for CC purposes
volatile ZunoTimer_t g_zuno_timer;
	
static bool aux_check_last_reporttime(uint8_t ch, uint32_t ticks)
{	
	#if defined(WITH_CC_SENSOR_MULTILEVEL) || defined(WITH_CC_METER)
	if((ZUNO_CFG_CHANNEL(ch).type == ZUNO_SENSOR_MULTILEVEL_CHANNEL_NUMBER) || 
		(ZUNO_CFG_CHANNEL(ch).type == ZUNO_METER_CHANNEL_NUMBER))
		return (ticks -  g_report_data.last_report_time[ch]) > 3000UL; // We can't send too frequent for these CCs
	#endif
	return true;
}

void zunoSendReportHandler(uint32_t ticks) {
	if(g_report_data.channels_mask == 0)
		return;
	int rs = ZUNO_UNKNOWN_CMD;
	for(uint8_t ch = 0; ch < ZUNO_MAX_MULTI_CHANNEL_NUMBER; ch++) {
		if((g_report_data.channels_mask & (1UL << ch)) == 0)
			continue;
		if(!aux_check_last_reporttime(ch, ticks))
			continue;
		#ifdef LOGGING_DBG
		LOGGING_UART.print("REPORT CH:");
		LOGGING_UART.println(ch);
		#endif
		fillOutgoingReportPacket(ch);
		rs = ZUNO_UNKNOWN_CMD;	
		switch(ZUNO_CFG_CHANNEL(ch).type)
		{
			#ifdef WITH_CC_SWITCH_BINARY
			case ZUNO_SWITCH_BINARY_CHANNEL_NUMBER:
				rs = zuno_CCSwitchBinaryReport(ch);
				break;
			#endif
			#ifdef WITH_CC_SWITCH_MULTILEVEL
			case ZUNO_SWITCH_MULTILEVEL_CHANNEL_NUMBER:
				rs = zuno_CCSwitchMultilevelReport(ch);
				break;
			#endif
			#ifdef WITH_CC_SWITCH_COLOR
			case ZUNO_SWITCH_COLOR_CHANNEL_NUMBER:
				rs = zuno_CCSwitchColorReport(ch, NULL);
				break;
			#endif
			#ifdef WITH_CC_DOORLOCK
			case ZUNO_DOORLOCK_CHANNEL_NUMBER:
				rs = zuno_CCDoorLockReport(ch);
				break;
			#endif
			#ifdef WITH_CC_NOTIFICATION
			case ZUNO_SENSOR_BINARY_CHANNEL_NUMBER:
				rs = zuno_CCNotificationReport(ch, NULL);
				break;
			#endif
			#ifdef WITH_CC_SENSOR_MULTILEVEL
			case ZUNO_SENSOR_MULTILEVEL_CHANNEL_NUMBER:
				rs = zuno_CCSensorMultilevelReport(ch);
				break;
			#endif
			#ifdef WITH_CC_METER
			case ZUNO_METER_CHANNEL_NUMBER:
				rs = zuno_CCMeterReport(ch);
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
			zunoSendZWPackage(&g_outgoing_packet);
		}
		if(rs == ZUNO_COMMAND_ANSWERED || rs == ZUNO_COMMAND_PROCESSED){
			g_report_data.channels_mask &= ~(1UL<<ch); // remove channel bit from pending report bitmap
			break; // Only one report per 1 pass
		}
	}
}
void zuno_CCTimer(uint32_t ticks) {
	g_zuno_timer.ticks = ticks;
	#ifdef WITH_CC_SWITCH_MULTILEVEL
	zuno_CCSwitchMultilevelTimer(ticks);
	#endif
	#ifdef WITH_CC_SWITCH_COLOR
	zuno_CCSwitchColorTimer(ticks);
	#endif
	if((ticks & 0x1F) == 0) // Once in ~320ms 
		zunoSendReportHandler(ticks);
}

void zunoSendReport(byte ch){
	if((ch < 1) || (ch > (ZUNO_CFG_CHANNEL_COUNT)))
		return;
	ch--;
	g_report_data.channels_mask |= (1 << ch);
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
		LOGGING_UART.print(" Package was dropped! NodeID==0");
		#endif
		return;
		
	}
	#ifdef WITH_CC_WAKEUP
	zuno_CCWakeup_OnAnyRx();
	#endif
    #ifdef LOGGING_DBG
	LOGGING_UART.print(millis());
	LOGGING_UART.print(" OUTGOING PACAKAGE");
	zuno_dbgdumpZWPacakge(&g_outgoing_packet);
	#endif
	// DBG
	//g_outgoing_packet.src_zw_channel    = 0;
	//g_outgoing_packet.dst_zw_channel    = 0;
	// If the channel "mapped to" main channel => report twice
	byte last_ch = pkg->src_zw_channel;
    if(pkg->src_zw_channel & ZWAVE_CHANNEL_MAPPED_BIT){
		pkg->src_zw_channel = 0;
		zunoSysCall(ZUNO_FUNC_SENDPACKET, 1, pkg);
		pkg->src_zw_channel = last_ch & ~(ZWAVE_CHANNEL_MAPPED_BIT);
	}
    zunoSysCall(ZUNO_FUNC_SENDPACKET, 1, pkg); // DBG
	pkg->src_zw_channel = last_ch; // Bring it back!
}	
