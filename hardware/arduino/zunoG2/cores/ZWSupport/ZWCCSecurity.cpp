#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCSecurity.h"

uint8_t *zuno_AddCommonClass(uint8_t *b);

static int _report(size_t channel) {
	ZwSecurity2CommandsSupportedFrame_t					*report;
	uint8_t												*commandClass;
	const ZUNOChannelCCS_t								*lp;
	size_t												i;
	size_t												max;

	report = (ZwSecurity2CommandsSupportedFrame_t *)&CMD_REPLY_CC;
	report->cmdClass = COMMAND_CLASS_SECURITY_2;
	report->cmd = SECURITY_2_COMMANDS_SUPPORTED_REPORT; 
	commandClass = &report->commandClass[0];
	commandClass = zuno_AddCommonClass(commandClass);
	if (channel != 0) {
		channel--;
		i = 0;
		lp = &ZUNO_CC_TYPES[ZUNO_CFG_CHANNEL(channel).type - 1];
		max = lp->num_ccs;
		while (i < max)
				commandClass++[0] = lp->ccs[i++].cc;
	}
	CMD_REPLY_LEN = sizeof(ZwSecurity2CommandsSupportedFrame_t) + (commandClass - &report->commandClass[0]);
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCSecurity(ZUNOCommandPacket_t *cmd) {
	int								rs;

	switch (ZW_CMD) {
		case SECURITY_2_COMMANDS_SUPPORTED_GET:
			rs = _report(cmd->dst_zw_channel);
			break ;
		default:
			rs = ZUNO_UNKNOWN_CMD;
			break ;
	}
	return (rs);
}