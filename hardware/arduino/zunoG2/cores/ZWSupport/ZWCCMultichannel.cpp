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



static int _capability_get(ZwMultiChannelCapabilityGetFrame_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	uint8_t										channel;
	size_t										endpoint;
	size_t										type_index;
	ZwMultiChannelCapabilityReportFrame_t		*report;
	uint8_t										*commandClass;
	ZwZwavePlusInfoType_t						info_type;

	endpoint = cmd->properties1 & 0x7F;
	// Get the info about selected endpoint
	if((channel = zuno_findChannelByZWChannelIndexChannel(endpoint)) == UNKNOWN_CHANNEL)// According to z-wave specification we must to ignore unsupported end points numbers - see. CC:0060.03.09.11.004 CC:0060.03.09.11.005
		return (ZUNO_COMMAND_BLOCKED);
	report = (ZwMultiChannelCapabilityReportFrame_t *)frame_report->info.packet.cmd;
	// report->cmdClass = COMMAND_CLASS_MULTI_CHANNEL; set in - fillOutgoingPacket
	// report->cmd = MULTI_CHANNEL_CAPABILITY_REPORT; set in - fillOutgoingPacket
	report->properties1 = endpoint; // The index of selected endpoint
	__zuno_CCZWavePlusGetType(channel, &info_type);
	report->genericDeviceClass = info_type.genericDeviceClass;
	report->specificDeviceClass = info_type.specificDeviceClass;
	commandClass = &report->commandClass[0];
	commandClass = zuno_AddCommonClassMinimal(commandClass);
	#ifdef MODERN_MULTICHANNEL_S2
	if(g_zuno_sys->enclusion_state != INCLUSION_STATE_INCLUDED_SECURE){
		commandClass = zuno_AddCommonClass(commandClass);
	}
	#else
	commandClass = zuno_AddCommonClass(commandClass);
	#endif
	#ifndef MODERN_MULTICHANNEL_S2_ALWAYS
	if(g_zuno_sys->enclusion_state == INCLUSION_STATE_INCLUDED_SECURE)
	#endif
	{
		commandClass++[0] =  COMMAND_CLASS_SECURITY;
		commandClass++[0] =  COMMAND_CLASS_SECURITY_2;
	}
	#ifdef MODERN_MULTICHANNEL_S2
	// CTT test S2_SupportedCCRequirement_Rev02
	// CC:0060.03.00.21.00E
	if(g_zuno_sys->enclusion_state != INCLUSION_STATE_INCLUDED_SECURE) 
	#endif
	{
		type_index = zuno_findChannelType(ZUNO_CFG_CHANNEL(channel).type, (ZUNOChannelCCS_t*)ZUNO_CC_TYPES, getMaxChannelTypes());
		commandClass++[0] = ZUNO_CC_TYPES[type_index].ccs[0].cc;
		if( (ZUNO_CC_TYPES[type_index].num_ccs > 1) && (ZUNO_CC_TYPES[type_index].ccs[1].cc != COMMAND_CLASS_BASIC))
			commandClass++[0] = ZUNO_CC_TYPES[type_index].ccs[1].cc;
	}
	frame_report->info.packet.len = sizeof(ZwMultiChannelCapabilityReportFrame_t) + (commandClass - &report->commandClass[0]);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _point_get(ZUNOCommandPacketReport_t *frame_report) {
	ZwMultiChannelEndPointReportFrame_t			*report;

	// Request of endpoint's count
	report = (ZwMultiChannelEndPointReportFrame_t *)frame_report->info.packet.cmd;
	// report->v4.cmdClass = COMMAND_CLASS_MULTI_CHANNEL; set in - fillOutgoingPacket
	// report->v4.cmd = MULTI_CHANNEL_END_POINT_REPORT; set in - fillOutgoingPacket
	report->v4.properties1 = 0; // No dynamic/identical endpoints
	report->v4.properties2 = g_mch_aux_data.num_channels;// Number of endpoints ZUno has
	report->v4.properties3 = 0;// No aggregated end points
	frame_report->info.packet.len = sizeof(report->v4);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _find(ZwMultiChannelEndPointFindFrame_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	ZwZwavePlusInfoType_t						info_type;
	ZwMultiChannelEndPointFindReportFrame_t		*report;
	size_t										genericDeviceClass;
	size_t										specificDeviceClass;
	uint8_t										*end_point;
	size_t										i;
	size_t										max;

	genericDeviceClass = cmd->genericDeviceClass;
	specificDeviceClass = cmd->specificDeviceClass;
	report = (ZwMultiChannelEndPointFindReportFrame_t *)frame_report->info.packet.cmd;
	// report->cmdClass = COMMAND_CLASS_MULTI_CHANNEL; set in - fillOutgoingPacket
	// report->cmd = MULTI_CHANNEL_END_POINT_FIND_REPORT; set in - fillOutgoingPacket
	report->reportsToFollow = 0;
	report->genericDeviceClass = genericDeviceClass;
	report->specificDeviceClass = specificDeviceClass;
	i = 1;
	max = ZUNO_CFG_CHANNEL_COUNT;
	end_point = &report->variantgroup[0];
	if (genericDeviceClass == GENERIC_TYPE_NON_INTEROPERABLE) {
		while (i <= max)
			end_point++[0] = i++;
	}
	else if (specificDeviceClass == GENERIC_TYPE_NON_INTEROPERABLE) {
		while (i <= max) {
			__zuno_CCZWavePlusGetType(i - 1, &info_type);
			if (info_type.genericDeviceClass == genericDeviceClass)
				end_point++[0] = i;
			i++;
		}
	}
	else {
		while (i <= max) {
			__zuno_CCZWavePlusGetType(i - 1, &info_type);
			if (info_type.genericDeviceClass == genericDeviceClass && info_type.specificDeviceClass == specificDeviceClass)
				end_point++[0] = i;
			i++;
		}
	}
	if (end_point == &report->variantgroup[0])
		end_point++[0] = 0x0;
	frame_report->info.packet.len = sizeof(ZwMultiChannelEndPointFindReportFrame_t) + (end_point - &report->variantgroup[0]);
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCMultichannel(ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	int									rs;

	zuno_initMchData();
	// We have only one channel => there is no need to expose multichannel
	if((!g_mch_aux_data.num_channels)  && 
		(ZW_CMD != MULTI_CHANNEL_CMD_ENCAP))
		return (ZUNO_COMMAND_BLOCKED);
	/// Mutichannel is always secure command class and availiably ONLY on the highest S2 level
	// if (_zunoTransposeSecurityLevel(cmd->zw_rx_secure_opts) < _zunoTransposeSecurityLevel(zunoSecurityStatus()))
	//	return ZUNO_COMMAND_BLOCKED; // Don't answer to it 
	switch(ZW_CMD) {
		case MULTI_CHANNEL_CAPABILITY_GET:
			rs = _capability_get((ZwMultiChannelCapabilityGetFrame_t *)cmd->cmd, frame_report);
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
			rs = _point_get(frame_report);
			break;
		case MULTI_CHANNEL_END_POINT_FIND:
			rs = _find((ZwMultiChannelEndPointFindFrame_t*)cmd->cmd, frame_report);
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