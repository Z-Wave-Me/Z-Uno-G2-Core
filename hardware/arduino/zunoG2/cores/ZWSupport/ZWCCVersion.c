#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCVersion.h"

byte zuno_findTargetChannel(ZUNOCommandPacket_t * cmd);

static int _class_get(ZUNOCommandPacket_t *packet, ZW_VERSION_COMMAND_CLASS_GET_V3_FRAME *cmd, ZUNOCommandPacketReport_t *frame_report) {
	ZW_VERSION_COMMAND_CLASS_REPORT_V3_FRAME		*report;
	
	if((zuno_findTargetChannel(packet)) != UNKNOWN_CHANNEL)
		return (ZUNO_UNKNOWN_CMD);
	report = (ZW_VERSION_COMMAND_CLASS_REPORT_V3_FRAME *)frame_report->packet.cmd;
	// report->cmdClass = COMMAND_CLASS_VERSION; set in - fillOutgoingPacket
	// report->cmd = VERSION_COMMAND_CLASS_REPORT; set in - fillOutgoingPacket
	report->requestedCommandClass = cmd->requestedCommandClass;
	report->commandClassVersion = 0x0;
	frame_report->packet.len = sizeof(ZW_VERSION_COMMAND_CLASS_REPORT_V3_FRAME);
	zunoSendZWPackage(&frame_report->packet);
	return (ZUNO_COMMAND_PROCESSED);
}

int zuno_CCVersionHandler(ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	int										rs;

	switch(ZW_CMD){
		case VERSION_COMMAND_CLASS_GET:
			rs = _class_get(cmd, (ZW_VERSION_COMMAND_CLASS_GET_V3_FRAME *)cmd->cmd, frame_report);
			break ;
		default:
			rs = ZUNO_UNKNOWN_CMD;
			break ;
	}
	return (rs);
}