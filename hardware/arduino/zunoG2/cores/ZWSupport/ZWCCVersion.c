#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCVersion.h"

byte zuno_findTargetChannel(ZUNOCommandPacket_t * cmd);

static int _class_get(ZUNOCommandPacket_t *packet, ZW_VERSION_COMMAND_CLASS_GET_V3_FRAME *cmd) {
	ZW_VERSION_COMMAND_CLASS_REPORT_V3_FRAME		*report;
	
	if((zuno_findTargetChannel(packet)) != UNKNOWN_CHANNEL)
		return (ZUNO_UNKNOWN_CMD);
	report = (ZW_VERSION_COMMAND_CLASS_REPORT_V3_FRAME *)&CMD_REPLY_CC;
	// report->cmdClass = COMMAND_CLASS_VERSION; set in - fillOutgoingPacket
	// report->cmd = VERSION_COMMAND_CLASS_REPORT; set in - fillOutgoingPacket
	report->requestedCommandClass = cmd->requestedCommandClass;
	report->commandClassVersion = 0x0;
	CMD_REPLY_LEN = sizeof(ZW_VERSION_COMMAND_CLASS_REPORT_V3_FRAME);
	zunoSendZWPackage(&g_outgoing_main_packet);
	return (ZUNO_COMMAND_PROCESSED);
}

int zuno_CCVersionHandler(ZUNOCommandPacket_t *cmd) {
	int										rs;

	switch(ZW_CMD){
		case VERSION_COMMAND_CLASS_GET:
			rs = _class_get(cmd, (ZW_VERSION_COMMAND_CLASS_GET_V3_FRAME *)cmd->cmd);
			break ;
		default:
			rs = ZUNO_UNKNOWN_CMD;
			break ;
	}
	return (rs);
}