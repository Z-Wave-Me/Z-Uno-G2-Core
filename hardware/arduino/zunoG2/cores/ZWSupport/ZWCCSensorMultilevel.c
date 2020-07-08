#include "ZWCCSensorMultilevel.h"
#include "Arduino.h"


typedef union split_e
{
    int32_t val;
    byte buff[4];
} split_t;

int zuno_CCSensorMultilevelReport(byte channel){
    CMD_REPLY_CC = COMMAND_CLASS_SENSOR_MULTILEVEL;
    CMD_REPLY_CMD = SENSOR_MULTILEVEL_REPORT;
    CMD_REPLY_DATA(0) = ZUNO_CFG_CHANNEL(channel).sub_type;
    uint8_t channel_size = ZUNO_CFG_CHANNEL(channel).params[0];
    CMD_REPLY_DATA(1) = channel_size;            
    channel_size &= SENSOR_MULTILEVEL_PROPERTIES_SIZE_MASK;
    split_t values = { .val = zuno_universalGetter1P(channel) };
    _zme_memcpy(&CMD_REPLY_DATA(2), values.buff, channel_size);
    CMD_REPLY_LEN = channel_size + 4;
    return ZUNO_COMMAND_ANSWERED;
}
int zuno_CCSensorMultilevelHandler(byte channel, ZUNOCommandPacket_t * cmd) {
    int rs = ZUNO_UNKNOWN_CMD;
    switch (ZW_CMD) {
        case SENSOR_MULTILEVEL_SUPPORTED_GET:
            // clear reply bit mask
            memset(&CMD_REPLY_DATA(0), 0, SENSOR_MULTILEVEL_SUPPORTED_MAX_BYTE_MASK);
            // In case it's a 0 channel mapping we have to declare all the types.
            if(cmd->dst_zw_channel == 0) {
                for (byte i = 0; i < ZUNO_CFG_CHANNEL_COUNT; i++){
                    if (ZUNO_CFG_CHANNEL(i).type != ZUNO_SENSOR_MULTILEVEL_CHANNEL_NUMBER)
                        continue;
                    if ((ZUNO_CFG_CHANNEL(i).zw_channel & 0x80) || 
                        (ZUNO_CFG_CHANNEL(i).zw_channel == 0)) {
                        // bit index starts from 0
                        zunoSetupBitMask(&CMD_REPLY_DATA(0), ZUNO_CFG_CHANNEL(i).sub_type-1, SENSOR_MULTILEVEL_SUPPORTED_MAX_BYTE_MASK);
                    }
                }
            } else {
                // If we use multichannel => just one bit in one mask
                // bit index starts from 0
                zunoSetupBitMask(&CMD_REPLY_DATA(0), ZUNO_CFG_CHANNEL(channel).sub_type-1, SENSOR_MULTILEVEL_SUPPORTED_MAX_BYTE_MASK);
            }
            CMD_REPLY_LEN = SENSOR_MULTILEVEL_SUPPORTED_LEN;
            rs = ZUNO_COMMAND_ANSWERED;
            break;
        case SENSOR_MULTILEVEL_SUPPORTED_GET_SCALE:
            CMD_REPLY_CMD = SENSOR_MULTILEVEL_SUPPORTED_SCALE_REPORT;
            CMD_REPLY_DATA(0) = ZW_CMD_BPARAM(0);
            CMD_REPLY_DATA(1) = 0;
            if (ZUNO_CFG_CHANNEL(channel).sub_type == ZW_CMD_BPARAM(0))
                CMD_REPLY_DATA(1) = 1 << ((ZUNO_CFG_CHANNEL(channel).params[0] & SENSOR_MULTILEVEL_PROPERTIES_SCALE_MASK) >> SENSOR_MULTILEVEL_PROPERTIES_SCALE_SHIFT);
            CMD_REPLY_LEN = 4;
            rs = ZUNO_COMMAND_ANSWERED;
            break;
        case SENSOR_MULTILEVEL_GET:
            if ((cmd->len > 2) && (ZUNO_CFG_CHANNEL(channel).sub_type != ZW_CMD_BPARAM(0)))
                return ZUNO_UNKNOWN_CMD; // Reject unsupported type
            rs = zuno_CCSensorMultilevelReport(channel);
            break;
    }

    return rs;
}