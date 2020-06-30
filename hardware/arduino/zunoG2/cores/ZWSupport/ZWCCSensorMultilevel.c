#include "ZWCCSensorMultilevel.h"
#include "Arduino.h"

typedef union split_e
{
    int32_t val;
    byte buff[4];

} split_t;

int zuno_CCSensorMultilevelReport(byte channel)
{
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

int zuno_CCSensorMultilevelHandler(byte channel, ZUNOCommandPacket_t * cmd)
{
    int rs = ZUNO_UNKNOWN_CMD;

    switch (ZW_CMD)
    {
        case SENSOR_MULTILEVEL_SUPPORTED_GET:

            memset(&CMD_REPLY_DATA(2), 0, 6);

            if (ZUNO_CFG_CHANNEL(channel).params[0] != 0)
                CMD_REPLY_DATA(((ZUNO_CFG_CHANNEL(channel).sub_type - 1) >> 3)) = 1 << ((ZUNO_CFG_CHANNEL(channel).sub_type - 1) & 0x07);

            for (byte i = 0; i < ZUNO_CFG_CHANNEL_COUNT; i++){
                if (ZUNO_CFG_CHANNEL(i).type != ZUNO_SENSOR_MULTILEVEL_CHANNEL_NUMBER)
                    continue;

                if (ZUNO_CFG_CHANNEL(i).zw_channel & 0x80 || ZUNO_CFG_CHANNEL(i).zw_channel == 0) 
                {
                    CMD_REPLY_DATA(((ZUNO_CFG_CHANNEL(i).sub_type - 1) >> 3)) |= (1 << (ZUNO_CFG_CHANNEL(i).sub_type - 1) & 0x07);
                }
            }

            CMD_REPLY_LEN = 8;

            rs = ZUNO_COMMAND_ANSWERED;
            break;

        case SENSOR_MULTILEVEL_SUPPORTED_GET_SCALE:
            CMD_REPLY_DATA(-1) = 0x06;
            CMD_REPLY_DATA(0) = ZW_CMD_BPARAM(0);
            CMD_REPLY_DATA(1) = 0;

            if (ZUNO_CFG_CHANNEL(channel).sub_type == ZW_CMD_BPARAM(0))
                CMD_REPLY_DATA(1) = 1 << ((ZUNO_CFG_CHANNEL(channel).params[0] & SENSOR_MULTILEVEL_PROPERTIES_SCALE_MASK) >> SENSOR_MULTILEVEL_PROPERTIES_SCALE_SHIFT);
            
            CMD_REPLY_LEN = 4;

            rs = ZUNO_COMMAND_ANSWERED;
            break;

        case SENSOR_MULTILEVEL_GET:
            rs = zuno_CCSensorMultilevelReport(channel);
            break;
    }

    return rs;
}