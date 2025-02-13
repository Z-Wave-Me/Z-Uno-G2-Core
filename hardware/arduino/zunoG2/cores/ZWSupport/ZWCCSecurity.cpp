#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCSecurity.h"

uint8_t *zuno_AddCommonClass(uint8_t *b);

static uint8_t *_reportGeneral(uint8_t *commandClass, uint8_t endpoint) {
	const _ZUNOChannelCCS_t *cc_types;
	size_t i;
	size_t channel;

	commandClass = zuno_AddCommonClass(commandClass);
	if (endpoint != 0 && (channel = zuno_findChannelByZWChannelIndexChannel(endpoint)) != UNKNOWN_CHANNEL) {
		if ((cc_types = _zunoGetCCTypes((_ZunoChannelNumber_t)ZUNO_CFG_CHANNEL(channel).type)) != NULL)
		{
			i = 0;
			while (i < cc_types->num_ccs) {
				commandClass++[0] = cc_types->ccs[i].cc;
				i++;
			}
		}
	}
	return (commandClass);
}

static int _report2(uint8_t endpoint, ZUNOCommandPacketReport_t *frame_report) {
	ZwSecurity2CommandsSupportedFrame_t					*report;
	uint8_t												*commandClass;

	report = (ZwSecurity2CommandsSupportedFrame_t *)frame_report->info.packet.cmd;
	// report->cmdClass = COMMAND_CLASS_SECURITY_2; set in - fillOutgoingPacket
	// report->cmd = SECURITY_2_COMMANDS_SUPPORTED_REPORT; set in - fillOutgoingPacket
	commandClass = _reportGeneral(&report->commandClass[0], endpoint);
	frame_report->info.packet.len = sizeof(ZwSecurity2CommandsSupportedFrame_t) + (commandClass - &report->commandClass[0]);
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCSecurity2(const ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	int								rs;

	if(g_zuno_sys->enclusion_state != INCLUSION_STATE_INCLUDED_SECURE)
		return ZUNO_COMMAND_BLOCKED;
	switch (ZW_CMD) {
		case SECURITY_2_COMMANDS_SUPPORTED_GET:
			rs = _report2(cmd->dst_zw_channel, frame_report);
			break ;
		default:
			rs = ZUNO_UNKNOWN_CMD;
			break ;
	}
	return (rs);
}

static int _report(size_t channel, ZUNOCommandPacketReport_t *frame_report) {
	ZwSecurityCommandsSupportedFrame_t					*report;
	uint8_t												*commandClass;

	report = (ZwSecurityCommandsSupportedFrame_t *)frame_report->info.packet.cmd;
	// report->cmdClass = COMMAND_CLASS_SECURITY; set in - fillOutgoingPacket
	// report->cmd = SECURITY_COMMANDS_SUPPORTED_REPORT; set in - fillOutgoingPacket
	report->reportsToFollow = 0x0;
	commandClass = _reportGeneral(&report->commandClassSupport[0], channel);
	frame_report->info.packet.len = sizeof(ZwSecurityCommandsSupportedFrame_t) + (commandClass - &report->commandClassSupport[0]);
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCSecurity(const ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	int								rs;

	if(g_zuno_sys->enclusion_state != INCLUSION_STATE_INCLUDED_SECURE)
		return ZUNO_COMMAND_BLOCKED;
	switch (ZW_CMD) {
		case SECURITY_COMMANDS_SUPPORTED_GET:
			rs = _report(cmd->dst_zw_channel, frame_report);
			break ;
		default:
			rs = ZUNO_UNKNOWN_CMD;
			break ;
	}
	return (rs);
}