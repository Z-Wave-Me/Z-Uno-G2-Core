#include "ZWCCSwitchMultilevel.h"
#include "ZWSupport.h"

int zuno_CCSwitchMultilevelHandler(byte channel, ZUNOCommandPacket_t * cmd){
    int rs = ZUNO_UNKNOWN_CMD;
    switch(ZW_CMD){
        case SWITCH_MULTILEVEL_GET:
            CMD_REPLY_DATA(0) = zuno_universalGetter1P(channel);
            CMD_REPLY_LEN = 3;
            rs = ZUNO_COMMAND_ANSWERED;
            break;
        case SWITCH_MULTILEVEL_SET:
            zuno_universalSetter1P(channel, ZW_CMD_BPARAM(0));
            rs = ZUNO_COMMAND_PROCESSED;
            break;
        case SWITCH_MULTILEVEL_START_LEVEL_CHANGE:
            // ---
            rs = ZUNO_COMMAND_PROCESSED;
            break;
        case SWITCH_MULTILEVEL_STOP_LEVEL_CHANGE:
            // ---
            rs = ZUNO_COMMAND_PROCESSED;
            break;
        
    }
    return rs;
}
