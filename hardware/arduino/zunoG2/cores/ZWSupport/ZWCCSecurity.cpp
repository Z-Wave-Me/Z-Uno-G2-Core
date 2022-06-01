#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCSecurity.h"

uint8_t *zuno_AddCommonClass(uint8_t *b);

static uint8_t *_reportGeneral(uint8_t *commandClass, size_t channel) {
	size_t												i;
	size_t												max;
	size_t												clss;
	const ZUNOChannelCCS_t								*lp;

	commandClass = zuno_AddCommonClass(commandClass);
	if (channel != 0) {
		ZUNOChannel_t * zuno_ch = zuno_findChannelByZWChannel(channel);
		//channel--;
		i = 0;
		lp = &ZUNO_CC_TYPES[zuno_ch->type - 1];
		max = lp->num_ccs;
		while (i < max)
			if ((clss = lp->ccs[i++].cc) != COMMAND_CLASS_BASIC)
				commandClass++[0] = clss;
	}
	return (commandClass);
}

static int _report2(size_t channel, ZUNOCommandPacketReport_t *frame_report) {
	ZwSecurity2CommandsSupportedFrame_t					*report;
	uint8_t												*commandClass;

	report = (ZwSecurity2CommandsSupportedFrame_t *)frame_report->packet.cmd;
	// report->cmdClass = COMMAND_CLASS_SECURITY_2; set in - fillOutgoingPacket
	// report->cmd = SECURITY_2_COMMANDS_SUPPORTED_REPORT; set in - fillOutgoingPacket
	commandClass = _reportGeneral(&report->commandClass[0], channel);
	frame_report->packet.len = sizeof(ZwSecurity2CommandsSupportedFrame_t) + (commandClass - &report->commandClass[0]);
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCSecurity2(ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
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

	report = (ZwSecurityCommandsSupportedFrame_t *)frame_report->packet.cmd;
	// report->cmdClass = COMMAND_CLASS_SECURITY; set in - fillOutgoingPacket
	// report->cmd = SECURITY_COMMANDS_SUPPORTED_REPORT; set in - fillOutgoingPacket
	report->reportsToFollow = 0x0;
	commandClass = _reportGeneral(&report->commandClassSupport[0], channel);
	frame_report->packet.len = sizeof(ZwSecurityCommandsSupportedFrame_t) + (commandClass - &report->commandClassSupport[0]);
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCSecurity(ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
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