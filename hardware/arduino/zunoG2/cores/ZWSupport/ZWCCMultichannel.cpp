#include "ZWCCMultichannel.h"
#include "ZWSupport.h"
#include "ZWCCZWavePlusInfo.h"
#include <math.h>

typedef struct	MultiChannelAuxData_s
{
	bool		inited;
	byte		num_channels;
}				MultiChannelAuxData_t;
MultiChannelAuxData_t g_mch_aux_data = {false, 0};

static void zuno_initMchData() {
	size_t					num_channels;
	size_t					ch;
	size_t					i;

	if(g_mch_aux_data.inited == true)
		return;
	num_channels = 0;
	for(i = 0;i < ZUNO_CFG_CHANNEL_COUNT; i++){
		ch = ZUNO_CFG_CHANNEL(i).zw_channel & ~(ZWAVE_CHANNEL_MAPPED_BIT);
		num_channels = MAX(ch, num_channels);
	}
	g_mch_aux_data.inited = true;
	g_mch_aux_data.num_channels = num_channels;
}

static int _capability_get(ZwMultiChannelCapabilityGetFrame_t *cmd) {
	ZUNOChannel_t								*channel;
	size_t										endpoint;
	size_t										type_index;
	ZwMultiChannelCapabilityReportFrame_t		*report;
	uint8_t										*commandClass;

	endpoint = cmd->properties1 & 0x7F;
	// Get the info about selected endpoint
	if((channel = zuno_findChannelByZWChannel(endpoint)) == NULL)// According to z-wave specification we must to ignore unsupported end points numbers - see. CC:0060.03.09.11.004 CC:0060.03.09.11.005
		return (ZUNO_COMMAND_BLOCKED);
	report = (ZwMultiChannelCapabilityReportFrame_t *)&CMD_REPLY_CC;
	report->cmdClass = COMMAND_CLASS_MULTI_CHANNEL;
	report->cmd = MULTI_CHANNEL_CAPABILITY_REPORT;
	report->properties1 = endpoint; // The index of selected endpoint
	type_index = zuno_findChannelType(channel->type, (ZUNOChannelCCS_t*)ZUNO_CC_TYPES, getMaxChannelTypes());
	report->genericDeviceClass = ZUNO_DEV_TYPES[type_index].gen_type;
	report->specificDeviceClass = ZUNO_DEV_TYPES[type_index].spec_type;
	commandClass = &report->commandClass[0];
	commandClass++[0] = COMMAND_CLASS_ZWAVEPLUS_INFO;
	commandClass++[0] = COMMAND_CLASS_ASSOCIATION;
	commandClass++[0] = COMMAND_CLASS_MULTI_CHANNEL_ASSOCIATION;
	commandClass++[0] = COMMAND_CLASS_ASSOCIATION_GRP_INFO;
	commandClass++[0] = ZUNO_CC_TYPES[type_index].ccs[0].cc;
	if( (ZUNO_CC_TYPES[type_index].num_ccs > 1) && (ZUNO_CC_TYPES[type_index].ccs[1].cc != COMMAND_CLASS_BASIC))
		commandClass++[0] = ZUNO_CC_TYPES[type_index].ccs[1].cc;
	CMD_REPLY_LEN = sizeof(ZwMultiChannelCapabilityReportFrame_t) + (commandClass - &report->commandClass[0]);
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCMultichannel(ZUNOCommandPacket_t *cmd) {
	int									rs;

	zuno_initMchData();
	// We have only one channel => there is no need to expose multichannel
	if(!g_mch_aux_data.num_channels)
		return (ZUNO_COMMAND_BLOCKED);
	switch(ZW_CMD) {
		case MULTI_CHANNEL_CAPABILITY_GET:
			rs = _capability_get((ZwMultiChannelCapabilityGetFrame_t *)cmd->cmd);
			break;
		case MULTI_CHANNEL_CMD_ENCAP:
			if(cmd->len < 3)
				return (ZUNO_COMMAND_BLOCKED);
			// Extracting the command from the parent frame; Add multichannel endpoints
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
			CMD_REPLY_LEN = 2 + 3; // 2 = CMD_CLASS + CMD, 3= DATA^^^
			rs = ZUNO_COMMAND_ANSWERED;
			break;
		case MULTI_CHANNEL_END_POINT_FIND:
			// we don't support it yet
			rs = ZUNO_COMMAND_BLOCKED;
			break;
		case MULTI_INSTANCE_GET:
			// we don't support it yet
			rs = ZUNO_COMMAND_BLOCKED;
			break ;
		default:
			rs = ZUNO_UNKNOWN_CMD;
			break ;
	}
	return rs;
}