#include "ZWCCSwitchBinary.h"
#include "ZWSupport.h"

int zuno_CCSwitchBinaryReport(byte channel){
    CMD_REPLY_CC = COMMAND_CLASS_SWITCH_BINARY;
    CMD_REPLY_CMD = SWITCH_BINARY_REPORT;
    CMD_REPLY_DATA(0) = zuno_universalGetter1P(channel) ? 0xFF : 0x00;
    CMD_REPLY_LEN = 3;
    return ZUNO_COMMAND_ANSWERED;
}
int zuno_CCSwitchBinaryHandler(byte channel, ZUNOCommandPacket_t * cmd){
    int rs = ZUNO_UNKNOWN_CMD;
    switch(ZW_CMD){
        case SWITCH_BINARY_GET:
            rs = zuno_CCSwitchBinaryReport(channel);
            break;
        case SWITCH_BINARY_SET:
            zuno_universalSetter1P(channel, ZW_CMD_BPARAM(0));
            rs = ZUNO_COMMAND_PROCESSED;
            break;
        
    }
    return rs;
}
