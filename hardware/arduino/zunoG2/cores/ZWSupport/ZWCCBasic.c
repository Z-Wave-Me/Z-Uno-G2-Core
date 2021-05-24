#include "ZWCCBasic.h"
#include "ZWSupport.h"
int zuno_CCBasicHandler(byte channel, ZUNOCommandPacket_t * cmd){
    int rs = ZUNO_UNKNOWN_CMD;
    switch(ZW_CMD){
        case BASIC_GET:
            CMD_REPLY_DATA(0) = zuno_universalGetter1P(channel);
            CMD_REPLY_LEN = 3;
            rs = ZUNO_COMMAND_ANSWERED;
            break;
        case BASIC_SET:
            zuno_universalSetter1P(channel, ZW_CMD_BPARAM(0));
            zunoSendReport(channel + 1); 
            rs = ZUNO_COMMAND_PROCESSED;
            break;
        
    }
    return rs;
}