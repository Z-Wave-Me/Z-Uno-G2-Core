#include "ZWCCMeter.h"
#include "ZWSupport.h"

int zuno_CCMeterHandler(byte channel, ZUNOCommandPacket_t * cmd)
{
	int rs = ZUNO_UNKNOWN_CMD;
	switch(ZW_CMD)
	{
		case METER_GET:
		{
			int32_t getter_values = zuno_universalGetter1P(channel) ? 0xFF : 0x00;

			if (!(CMD_REPLY_LEN & 0x80) && (ZW_CMD_BPARAM(0) != ZUNO_CFG_CHANNEL(channel).params) & 0x07)
			{
				CMD_REPLY_LEN = 0;
				break;
			}
			uint8_t tmp_param = ZUNO_CFG_CHANNEL(channel).params[0]; // Now we are using only one of four bytes (remained bytes reserved)
			CMD_REPLY_DATA(0) = METER_RATE_IMPORT; // Rate == import
			if (ZW_CMD_BPARAM(0) & 0x04)
				CMD_REPLY_DATA(0) |= 0x80;
			
			CMD_REPLY_DATA(0) |=  ZUNO_CFG_CHANNEL(channel).sub_type & 0x1F;
			CMD_REPLY_DATA(1) = (tmp_param & 0x03) << 3;
			CMD_REPLY_DATA(1) |= (tmp_param << 2) & 0xE0;
			
			tmp_param >>= 6;
			tmp_param += 1;
			
			CMD_REPLY_DATA(1) |= tmp_param;
			
			_zme_memcpy(CMD_REPLY_DATA(2), cmd->cmd, tmp_param);

			CMD_REPLY_DATA(tmp_param + 2) = 0;
			CMD_REPLY_DATA(tmp_param + 3) = 0;
			
			CMD_REPLY_LEN = 6 + tmp_param;
			rs = ZUNO_COMMAND_ANSWERED;		
			break;
		}
		case METER_SUPPORTED_GET:
			CMD_REPLY_DATA(0) = ZUNO_CFG_CHANNEL(channel).sub_type | METER_RATE_IMPORT;
			CMD_REPLY_DATA(1) = 1 << (ZUNO_CFG_CHANNEL(channel).params[0]);
			CMD_REPLY_LEN = 4;
			rs = ZUNO_COMMAND_ANSWERED;		
			break;
	}
	return rs;
}