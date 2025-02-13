#include <math.h>
#include "ArduinoTypes.h"
#include "LLCore.h"
#include "ZUNO_Definitions.h"
#include "ZWCCMultichannel.h"
#include "ZWCCZWavePlusInfo.h"
#include "ZW_classcmd.h"

typedef struct __MultiChannelAuxData_s
{
	bool inited;
	bool identical;
	byte num_channels;
} __MultiChannelAuxData_t;

static __MultiChannelAuxData_t __multi_channel_data =
{
	.inited = false,
	.identical = false,
	.num_channels = 0,
};

static void __initMchData(void) {
	bool identical;
	size_t					num_channels;
	size_t					ch;
	size_t					i;

	if(__multi_channel_data.inited == true)
		return;
	num_channels = 0;
	identical = true;
	for(i = 0;i < ZUNO_CFG_CHANNEL_COUNT; i++){
		if (ZUNO_CFG_CHANNEL(0).type != ZUNO_CFG_CHANNEL(i).type)
			identical = false;
		ch = ZUNO_CFG_CHANNEL(i).zw_channel & ~(ZWAVE_CHANNEL_MAPPED_BIT);
		num_channels = MAX(ch, num_channels);
	}
	__multi_channel_data.inited = true;
	__multi_channel_data.identical = identical;
	__multi_channel_data.num_channels = num_channels;
}

static int _capability_get(ZW_MULTI_CHANNEL_CAPABILITY_GET_V4_FRAME *cmd, ZUNOCommandPacketReport_t *frame_report) {
	const _ZUNOChannelCCS_t *cc_types;
	ZW_MULTI_CHANNEL_CAPABILITY_REPORT_1BYTE_V4_FRAME *report;
	size_t i;
	uint8_t										channel;
	size_t										endpoint;
	uint8_t										*commandClass;
	ZwZwavePlusInfoType_t						info_type;

	endpoint = cmd->properties1 & 0x7F;
	// Get the info about selected endpoint
	if((channel = zuno_findChannelByZWChannelIndexChannel(endpoint)) == UNKNOWN_CHANNEL)// According to z-wave specification we must to ignore unsupported end points numbers - see. CC:0060.03.09.11.004 CC:0060.03.09.11.005
		return (ZUNO_COMMAND_BLOCKED);
	report = (ZW_MULTI_CHANNEL_CAPABILITY_REPORT_1BYTE_V4_FRAME *)frame_report->info.packet.cmd;
	// report->cmdClass = COMMAND_CLASS_MULTI_CHANNEL; set in - fillOutgoingPacket
	// report->cmd = MULTI_CHANNEL_CAPABILITY_REPORT; set in - fillOutgoingPacket
	report->properties1 = endpoint; // The index of selected endpoint
	__zuno_CCZWavePlusGetType(channel, &info_type);
	report->genericDeviceClass = info_type.genericDeviceClass;
	report->specificDeviceClass = info_type.specificDeviceClass;
	commandClass = &report->commandClass1;
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
		if ((cc_types = _zunoGetCCTypes((_ZunoChannelNumber_t)ZUNO_CFG_CHANNEL(channel).type)) != NULL)
		{
			i = 0;
			while (i < cc_types->num_ccs) {
				commandClass++[0] = cc_types->ccs[i].cc;
				i++;
			}
		}
	}
	frame_report->info.packet.len = (sizeof(report[0]) - sizeof(report->commandClass1)) + (commandClass - &report->commandClass1);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _point_get(ZUNOCommandPacketReport_t *frame_report) {
	ZW_MULTI_CHANNEL_END_POINT_REPORT_V4_FRAME			*report;

	// Request of endpoint's count
	report = (ZW_MULTI_CHANNEL_END_POINT_REPORT_V4_FRAME *)frame_report->info.packet.cmd;
	// report->v4.cmdClass = COMMAND_CLASS_MULTI_CHANNEL; set in - fillOutgoingPacket
	// report->v4.cmd = MULTI_CHANNEL_END_POINT_REPORT; set in - fillOutgoingPacket
	report->properties1 = 0; // No dynamic endpoints
	if (__multi_channel_data.identical == true)
		report->properties1 = report->properties1 | MULTI_CHANNEL_END_POINT_REPORT_PROPERTIES1_IDENTICAL_BIT_MASK_V4;
	report->properties2 = __multi_channel_data.num_channels;// Number of endpoints ZUno has
	report->properties3 = 0;// No aggregated end points
	frame_report->info.packet.len = sizeof(report[0]);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _find(ZW_MULTI_CHANNEL_END_POINT_FIND_V4_FRAME *cmd, ZUNOCommandPacketReport_t *frame_report) {
	ZW_MULTI_CHANNEL_END_POINT_FIND_REPORT_1BYTE_V4_FRAME *report;
	VG_MULTI_CHANNEL_END_POINT_FIND_REPORT_V4_VG *end_point;
	ZwZwavePlusInfoType_t						info_type;
	size_t										genericDeviceClass;
	size_t										specificDeviceClass;
	size_t										i;
	size_t										max;

	genericDeviceClass = cmd->genericDeviceClass;
	specificDeviceClass = cmd->specificDeviceClass;
	report = (ZW_MULTI_CHANNEL_END_POINT_FIND_REPORT_1BYTE_V4_FRAME *)frame_report->info.packet.cmd;
	// report->cmdClass = COMMAND_CLASS_MULTI_CHANNEL; set in - fillOutgoingPacket
	// report->cmd = MULTI_CHANNEL_END_POINT_FIND_REPORT; set in - fillOutgoingPacket
	report->reportsToFollow = 0;
	report->genericDeviceClass = genericDeviceClass;
	report->specificDeviceClass = specificDeviceClass;
	i = 1;
	max = ZUNO_CFG_CHANNEL_COUNT;
	end_point = &report->variantgroup1;
	if (genericDeviceClass == GENERIC_TYPE_NON_INTEROPERABLE) {
		while (i <= max)
			end_point++[0].properties1 = i++;
	}
	else if (specificDeviceClass == GENERIC_TYPE_NON_INTEROPERABLE) {
		while (i <= max) {
			__zuno_CCZWavePlusGetType(i - 1, &info_type);
			if (info_type.genericDeviceClass == genericDeviceClass)
				end_point++[0].properties1 = i;
			i++;
		}
	}
	else {
		while (i <= max) {
			__zuno_CCZWavePlusGetType(i - 1, &info_type);
			if (info_type.genericDeviceClass == genericDeviceClass && info_type.specificDeviceClass == specificDeviceClass)
				end_point++[0].properties1 = i;
			i++;
		}
	}
	if (end_point == &report->variantgroup1)
		end_point++[0].properties1 = 0x0;
	frame_report->info.packet.len = (sizeof(report[0]) - sizeof(report->variantgroup1)) + (end_point - &report->variantgroup1);
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCMultichannel(ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	int									rs;

	__initMchData();
	// We have only one channel => there is no need to expose multichannel
	if((!__multi_channel_data.num_channels)  && 
		(ZW_CMD != MULTI_CHANNEL_CMD_ENCAP_V4))
		return (ZUNO_COMMAND_BLOCKED);
	/// Mutichannel is always secure command class and availiably ONLY on the highest S2 level
	// if (_zunoTransposeSecurityLevel(cmd->zw_rx_secure_opts) < _zunoTransposeSecurityLevel(zunoSecurityStatus()))
	//	return ZUNO_COMMAND_BLOCKED; // Don't answer to it 
	switch(ZW_CMD) {
		case MULTI_CHANNEL_CAPABILITY_GET_V4:
			rs = _capability_get((ZW_MULTI_CHANNEL_CAPABILITY_GET_V4_FRAME *)cmd->cmd, frame_report);
			break;
		case MULTI_CHANNEL_CMD_ENCAP_V4:
			if(cmd->len < 3)
				return (ZUNO_COMMAND_BLOCKED);
			// Extracting the command from the parent frame; Add multichannel endpoints
			cmd->src_zw_channel = ZW_CMD_BPARAM(0);
			cmd->dst_zw_channel = ZW_CMD_BPARAM(1);
			cmd->cmd += 4;
			cmd->len -= 4;
			rs = ZUNO_COMMAND_UNPACKED;
			break;
		case MULTI_CHANNEL_END_POINT_GET_V4:
			rs = _point_get(frame_report);
			break;
		case MULTI_CHANNEL_END_POINT_FIND_V4:
			rs = _find((ZW_MULTI_CHANNEL_END_POINT_FIND_V4_FRAME*)cmd->cmd, frame_report);
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