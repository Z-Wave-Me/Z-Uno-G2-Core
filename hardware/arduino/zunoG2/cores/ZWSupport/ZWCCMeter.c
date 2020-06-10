#include "ZWCCMeter.h"
#include "ZWSupport.h"
#include "Arduino.h"

#define DEBUGSERIAL Serial0
#define dbgprint(a)   DEBUGSERIAL.print("[DBG] "); DEBUGSERIAL.print(a)
#define dbgprintln(a) DEBUGSERIAL.println(a, HEX)

typedef union split_e
{
    int32_t val;
    byte buff[4];

} split_t;

int zuno_CCMeterHandler(byte channel, ZUNOCommandPacket_t * cmd)
{
	int rs = ZUNO_UNKNOWN_CMD;
	switch(ZW_CMD)
	{
		case METER_GET:
		{
			ZW_CMD_BPARAM(0) >>=3;
			ZW_CMD_BPARAM(0) &= 0x07;
			if ((ZW_CMD_BPARAM(0)) != ((ZUNO_CFG_CHANNEL(channel).params[0]) & 0x07))
			{
				CMD_REPLY_LEN = 0;
				break;
			}

			uint8_t channel_size = ZUNO_CFG_CHANNEL(channel).params[0]; // Now we are using only one of four bytes (remained bytes are reserved)

			CMD_REPLY_DATA(0) = METER_RATE_IMPORT;

			if (ZW_CMD_BPARAM(0) & 0x04)
				CMD_REPLY_DATA(0) |= 0x80;

			CMD_REPLY_DATA(0) |=  ZUNO_CFG_CHANNEL(channel).sub_type & 0x1F;
			CMD_REPLY_DATA(1) = (channel_size & 0x03) << 3;
			CMD_REPLY_DATA(1) |= (channel_size << 2) & 0xE0;

			channel_size >>= 6;
			channel_size += 1;
			
			CMD_REPLY_DATA(1) |= channel_size;

			split_t values = { .val = zuno_universalGetter1P(channel) };

			_zme_memcpy(&CMD_REPLY_DATA(2), values.buff, channel_size);


			CMD_REPLY_DATA(channel_size + 2) = 0;
			CMD_REPLY_DATA(channel_size + 3) = 0;

			CMD_REPLY_LEN = 6 + channel_size;
	
			rs = ZUNO_COMMAND_ANSWERED;
			break;
		}

		case METER_SUPPORTED_GET:
			CMD_REPLY_DATA(0) = ZUNO_CFG_CHANNEL(channel).sub_type | METER_RATE_IMPORT;
			CMD_REPLY_DATA(1) = 1 << (ZUNO_CFG_CHANNEL(channel).params[0] & 0x07);
			CMD_REPLY_LEN = 4;

			rs = ZUNO_COMMAND_ANSWERED;		
			break;
		
		case METER_RESET:
			zuno_universalSetter1P(channel, 0);
			
			rs = ZUNO_COMMAND_ANSWERED;
	}
	return rs;
}