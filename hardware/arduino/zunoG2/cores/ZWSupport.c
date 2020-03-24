#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCBasic.h"
#include "ZWCCSwitchBinary.h"
#include "ZWCCSwitchMultilevel.h"
#include "ZWCCMultichannel.h"

#define UNKNOWN_CHANNEL       0xFF 

#include "zuno_preproc/ZUNO_AutoChannels.h"

enum {
    HADLER_ARGTYPE_1UB,
    HADLER_ARGTYPE_2UB,
    HADLER_ARGTYPE_4UB,
    HADLER_ARGTYPE_1SB = HADLER_ARGTYPE_1UB | 0x08,
    HADLER_ARGTYPE_2SB = HADLER_ARGTYPE_2UB | 0x08,
    HADLER_ARGTYPE_4SB = HADLER_ARGTYPE_4UB | 0x08
};
#define HANDLER_DESCRIPTOR_TYPE_MASK     0x07
#define HANDLER_DESCRIPTOR_LEN_SHIFT     0x04
#define HANDLER_DESCRIPTOR_LEN_MASK      0x03
#define HANDLER_DESCRIPTOR_SIGNED_BIT    0x80

typedef struct ZUnoChannelDtaHandler_s{
    void * p_handler;     
                       // |    7   | 6 |  5    |   4 | 3 |2|1|0|
    byte   descriptor; // | SIGNED | - | 2^NUM_BYTES | - | TYPE|
}ZUnoChannelDtaHandler_t;
ZUnoChannelDtaHandler_t g_zuno_channelhandlers_map[ZUNO_MAX_MULTI_CHANNEL_NUMBER];
ZUNOCommandPacket_t g_outgoing_packet;
uint8_t             g_outgoing_data[MAX_ZW_PACKAGE];

bool zuno_compare_channeltypeCC(ZUNOChannel_t * channel, uint8_t * cmd_bytes){
    switch(channel->type){
        case ZUNO_SWITCH_BINARY_CHANNEL_NUMBER:
            if(cmd_bytes[0] == COMMAND_CLASS_SWITCH_BINARY)
                return true;
            if(cmd_bytes[0] == COMMAND_CLASS_BASIC)
                return true;
            break;
        case ZUNO_SWITCH_MULTILEVEL_CHANNEL_NUMBER:
             if(cmd_bytes[0] == COMMAND_CLASS_SWITCH_MULTILEVEL)
                return true;
            if(cmd_bytes[0] == COMMAND_CLASS_BASIC)
                return true;
            break;
        case ZUNO_SENSOR_MULTILEVEL_CHANNEL_NUMBER:
            if(cmd_bytes[0] == COMMAND_CLASS_SENSOR_MULTILEVEL)
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
    for(i=0;i<ZUNO_CFG_CHANNEL_COUNT;i++)
        if(compare_zw_channel(ZUNO_CFG_CHANNEL(i).zw_channel,cmd->dst_zw_channel)) //ZUNO_CFG_CHANNEL(N).zw_channel == cmd->dst_zw_channel)
            if(zuno_compare_channeltypeCC(&(ZUNO_CFG_CHANNEL(i)), cmd->cmd))
                return i;
    return UNKNOWN_CHANNEL;
}


void fillOutgoingPacket(ZUNOCommandPacket_t * cmd) {
    memset(&g_outgoing_packet, 0, sizeof(ZUNOCommandPacket_t));
    memset(g_outgoing_data, 0, MAX_ZW_PACKAGE);
    g_outgoing_packet.cmd = g_outgoing_data;
    g_outgoing_data[0] = cmd->cmd[0];  // the same command class
    g_outgoing_data[1] = cmd->cmd[1]+1; // in most cases report = get+1
    // Reply as we was asked
    g_outgoing_packet.src_node          = zunoNID();
    g_outgoing_packet.dst_node          = cmd->src_node;
    g_outgoing_packet.src_zw_channel    = cmd->dst_zw_channel;
    g_outgoing_packet.dst_zw_channel    = cmd->src_zw_channel;
    g_outgoing_packet.zw_rx_secure_opts = cmd->zw_rx_secure_opts;
    g_outgoing_packet.zw_rx_opts        = ZWAVE_PLUS_TX_OPTIONS;
}

void zuno_dbgdumpZWPacakge(ZUNOCommandPacket_t * cmd){
    #ifdef LOGGING_UART
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
    #endif
}
// Main timer for CC purposes
void zuno_CCTimer(uint32_t ticks){

}
// Main command handler for incoming z-wave commands
int zuno_CommandHandler(ZUNOCommandPacket_t * cmd) {
    int result = ZUNO_UNKNOWN_CMD;
    
    #ifdef LOGGING_DBG
    LOGGING_UART.print(millis());
    LOGGING_UART.print("INCOMING  "); 
    zuno_dbgdumpZWPacakge(cmd);
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
    if(result != ZUNO_COMMAND_ANSWERED){
        byte zuno_ch = zuno_findTargetChannel(cmd);
        if(zuno_ch == UNKNOWN_CHANNEL){
            return ZUNO_UNKNOWN_CMD; // Command doesn't fit => forward it to firmware CommandHandler
        }
        #ifdef LOGGING_DBG
        LOGGING_UART.print("CHANNEL WAS  FOUND:"); 
        LOGGING_UART.println(zuno_ch);
        #endif
        switch(ZW_CMD_CLASS){
            case COMMAND_CLASS_BASIC:
                result = zuno_CCBasicHandler(zuno_ch, cmd);
                break;
            #if ( WITH_CC_SWITCH_BINARY )
            case COMMAND_CLASS_SWITCH_BINARY:
                result = zuno_CCSwitchBinaryHandler(zuno_ch, cmd);
                break;
            #endif
            #ifdef WITH_CC_SWITCH_MULTILEVEL
            case COMMAND_CLASS_SWITCH_MULTILEVEL:
                result = zuno_CCSwitchMultilevelHandler(zuno_ch, cmd);
                break;
            #endif
        }
    }
    // Do we have any report to send?
    if(result == ZUNO_COMMAND_ANSWERED){
        #ifdef LOGGING_DBG
        LOGGING_UART.print(millis());
        LOGGING_UART.print("OUTGOING  "); 
        zuno_dbgdumpZWPacakge(&g_outgoing_packet);
        #endif
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
                    ((zuno_multisetter1ub_t*)handler)(ch, v);
                     break;
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
            if(ch != UNKNOWN_CHANNEL){
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
                ((uint8_t*)handler)[ch] = value & 0xFF;
                break;
            *((uint8_t*)handler) = value & 0xFF;
            break;
        case HADLER_ARGTYPE_2UB:
        case HADLER_ARGTYPE_2SB:
            if(ch != UNKNOWN_CHANNEL)
                ((uint16_t*)handler)[ch] = value & 0xFFFF;
                break;
            *((uint16_t*)handler) = value & 0xFFFF;
            break;
        case HADLER_ARGTYPE_4UB:
        case HADLER_ARGTYPE_4SB:
            if(ch != UNKNOWN_CHANNEL)
                ((uint32_t*)handler)[ch] = value;
                break;
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
        case CHANNEL_HANDLER_SINGLE_GETTERSETTER:{
            zuno_handler_single_gettersetter_t * p_gs = (zuno_handler_single_gettersetter_t *) g_zuno_channelhandlers_map[zuno_ch].p_handler;
            return zuno_callGetter(val_type, UNKNOWN_CHANNEL, p_gs->getter);
        }
        case CHANNEL_HANDLER_SINGLE_VALUEMAPPER:
            return zuno_getMappedValue(val_type, UNKNOWN_CHANNEL, g_zuno_channelhandlers_map[zuno_ch].p_handler);
        case CHANNEL_HANDLER_MULTI_GETTER:{
            zuno_handler_multi_getter_t * p_mg = (zuno_handler_multi_getter_t *) g_zuno_channelhandlers_map[zuno_ch].p_handler;
            return zuno_callGetter(val_type, zuno_ch-p_mg->offset, p_mg->getter);
        }
        case CHANNEL_HANDLER_MULTI_GETTERSETTER:{
            zuno_handler_multi_gettersetter_t * p_mgs = (zuno_handler_multi_gettersetter_t *) g_zuno_channelhandlers_map[zuno_ch].p_handler;
            return zuno_callGetter(val_type, zuno_ch-p_mgs->offset, p_mgs->getter);
        }
        case CHANNEL_HANDLER_MULTI_MAPPER:{
            zuno_handler_multi_getter_t * p_mw = (zuno_handler_multi_getter_t *) g_zuno_channelhandlers_map[zuno_ch].p_handler;
            return zuno_getMappedValue(val_type, zuno_ch - p_mw->offset, p_mw->getter);
        }
    }
    return 0;

} 
void zuno_universalSetter1P(byte zuno_ch, int32_t value) {
     if(zuno_ch>ZUNO_CFG_CHANNEL_COUNT)
        return;
    byte type = g_zuno_channelhandlers_map[zuno_ch].descriptor & HANDLER_DESCRIPTOR_TYPE_MASK;
    byte val_type = (g_zuno_channelhandlers_map[zuno_ch].descriptor >> HANDLER_DESCRIPTOR_LEN_SHIFT);
    switch(type){
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
    }
} 
// Channels fill routines
bool zunoStartDeviceConfiguration() {
    if(zunoInNetwork())
        return false;
    memset(g_zuno_sys->zwave_cfg, 0, sizeof(ZUNODeviceConfiguation_t));
    g_zuno_sys->zwave_cfg->security_keys = SECURITY_KEY_S2_UNAUTHENTICATED_BIT | SECURITY_KEY_S0_BIT;
    return  true;
}
byte zuno_findChannelType(byte type){
    byte i;
    for(i=0;i<ZUNO_CFG_TYPE_COUNT;i++){
        if(ZUNO_CFG_TYPE(i).type == type)
            return i;
    }
    return UNKNOWN_CHANNEL;
}
byte zunoAddChannel(byte type, byte subtype, byte options) {
    // Do we have space for the new channel?
    if(ZUNO_CFG_CHANNEL_COUNT >= ZUNO_MAX_MULTI_CHANNEL_NUMBER)
        return UNKNOWN_CHANNEL;
    byte type_index = zuno_findChannelType(type);
    // We have to add new type to device
    if(type_index == UNKNOWN_CHANNEL) {
        // Do we have space for the new CC type?
        if(ZUNO_CFG_TYPE_COUNT >= ZUNO_MAX_CCTYPES)
            return UNKNOWN_CHANNEL;
        // Fill the type structure from predefined array.
        // type index starts from 1, so we have to decrement it
        memcpy(&ZUNO_CFG_TYPE(ZUNO_CFG_TYPE_COUNT), &ZUNO_CC_TYPES[type-1], sizeof(ZUNOChannelCCS_t));
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
void zunoSetZWChannel(byte ch, byte zw_channel){
    ZUNO_CFG_CHANNEL(ch).zw_channel = zw_channel;
}
void zunoAppendChannelHandler(byte ch, byte value_size, byte type, void * handler) {
    g_zuno_channelhandlers_map[ch].descriptor = (value_size&0x03) << 4 | (type & 0x07);
    g_zuno_channelhandlers_map[ch].p_handler = handler;
}
ZUNOChannel_t * zuno_findChannelByZWChannel(byte zw_ch){
    for(int i=0;i<ZUNO_CFG_CHANNEL_COUNT;i++){
        byte naked_channel = ZUNO_CFG_CHANNEL(i).zw_channel & (~ZWAVE_CHANNEL_MAPPED_BIT);
        if(naked_channel == zw_ch)
            return &(ZUNO_CFG_CHANNEL(i));
    }
    return NULL;
}
