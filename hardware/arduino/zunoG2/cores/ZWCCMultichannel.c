#include "ZWCCMultichannel.h"
#include "ZWSupport.h"
#include <math.h>
//#if WITH_CC_MULTICHANNEL

typedef struct MultiChannelAuxData_s{
    bool inited;
    byte num_channels;
}MultiChannelAuxData_t;
MultiChannelAuxData_t g_mch_aux_data = {false, 0};
static void zuno___initMchData(){
    if(g_mch_aux_data.inited)
        return;
    g_mch_aux_data.num_channels = 0;
    for(int i=0;i<ZUNO_CFG_CHANNEL_COUNT; i++){
        byte ch = ZUNO_CFG_CHANNEL(i).zw_channel & ~(ZWAVE_CHANNEL_MAPPED_BIT);
        g_mch_aux_data.num_channels = MAX(ch, g_mch_aux_data.num_channels);
    }
    g_mch_aux_data.inited = true;
}
// ZUNO_CC_TYPES
// ZUNO_DEV_TYPES
int zuno_CCMultichannel(ZUNOCommandPacket_t * cmd){
    int rs = ZUNO_UNKNOWN_CMD;
    zuno___initMchData();
    // We have only one channel => there is no need to expose multichannel
    if(!g_mch_aux_data.num_channels)
        return ZUNO_COMMAND_BLOCKED;
    switch(ZW_CMD){
        case MULTI_CHANNEL_CAPABILITY_GET:{
                // Get the info about selected endpoint
                ZUNOChannel_t * channel =  zuno_findChannelByZWChannel(ZW_CMD_BPARAM(0));
                if(channel == NULL){
                    // According to z-wave specification we must to ignore unsupported end points numbers
                    // see. CC:0060.03.09.11.004 CC:0060.03.09.11.005
                    return ZUNO_COMMAND_BLOCKED;
                }
                byte type_index = channel->type - 1;
                CMD_REPLY_DATA(0) = ZW_CMD_BPARAM(0); // The index of selected endpoint
                CMD_REPLY_DATA(1) = ZUNO_DEV_TYPES[type_index].gen_type;
                CMD_REPLY_DATA(2) = ZUNO_DEV_TYPES[type_index].spec_type;
                CMD_REPLY_DATA(3) = ZUNO_CC_TYPES[type_index].ccs[0].cc;
                if( (ZUNO_CC_TYPES[type_index].num_ccs > 1) && 
                    (ZUNO_CC_TYPES[type_index].ccs[1].cc != COMMAND_CLASS_BASIC)) {
                    CMD_REPLY_DATA(4) = ZUNO_CC_TYPES[type_index].ccs[1].cc;
                    CMD_REPLY_LEN = 2+5; // 2 = CMD_CLASS + CMD, 3= DATA^^^
                } else {
                    CMD_REPLY_LEN = 2+4; // 2 = CMD_CLASS + CMD, 3= DATA^^^
                }
                rs = ZUNO_COMMAND_ANSWERED;
            }
            break;
        case MULTI_CHANNEL_CMD_ENCAP:
            if(cmd->len < 3){
                return ZUNO_COMMAND_BLOCKED;;
            }
            // Extracting the command from the parent frame
            // Add multichannel endpoints
            cmd->src_zw_channel = ZW_CMD_BPARAM(0);
            cmd->dst_zw_channel = ZW_CMD_BPARAM(1);
            cmd->cmd += 4;
            cmd->len -= 4;
            rs = ZUNO_COMMAND_UNPACKED;
            break;
        case MULTI_CHANNEL_END_POINT_GET:
            // Request of endpoint's count
            CMD_REPLY_DATA(0) = 0; // No dynamic/identical endpoints
            CMD_REPLY_DATA(1) = g_mch_aux_data.num_channels;  // Number of endpoints ZUno has
            CMD_REPLY_DATA(2) = 0; // No aggregated end points
            CMD_REPLY_LEN = 2+3; // 2 = CMD_CLASS + CMD, 3= DATA^^^
            rs = ZUNO_COMMAND_ANSWERED;
            break;
        case MULTI_CHANNEL_END_POINT_FIND:
             // we don't support it yet
            return ZUNO_COMMAND_BLOCKED;
            break;
        case MULTI_INSTANCE_GET:
            // we don't support it yet
            return ZUNO_COMMAND_BLOCKED;
            break;
    }
    return rs;
}