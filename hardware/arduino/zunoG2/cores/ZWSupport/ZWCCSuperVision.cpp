#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCSuperVision.h"

uint8_t _previously_receive_session_id = 0xFF;

static int _report(ZwCSuperVisionGetFrame_t *cmd) {
	ZwCSuperVisionReportFrame_t		*report;
	size_t							id;

	id = (cmd->properties1 & SUPERVISION_GET_PROPERTIES1_SESSION_ID_MASK);
	memcpy(cmd, &cmd->data[0], cmd->encapsulatedCommandLength);
	if (_previously_receive_session_id == id)
		return (ZUNO_COMMAND_PROCESSED);
	_previously_receive_session_id = id;
	report = (ZwCSuperVisionReportFrame_t *)&CMD_REPLY_CC;
	// report->cmdClass = COMMAND_CLASS_SUPERVISION; set in - fillOutgoingPacket
	// report->cmd = SUPERVISION_REPORT; set in - fillOutgoingPacket
	report->properties1 = id;
	report->status = SUPERVISION_REPORT_SUCCESS;
	report->duration = 0x0;
	CMD_REPLY_LEN = sizeof(ZwCSuperVisionReportFrame_t);
	return (ZUNO_COMMAND_PROCESSED);
}

int zuno_CCSuperVisionHandler(ZUNOCommandPacket_t *cmd) {
	int								rs;
 
	switch (ZW_CMD) {
		case SUPERVISION_GET:
			rs = _report((ZwCSuperVisionGetFrame_t *)cmd->cmd);
			break ;
		default:
			rs = ZUNO_UNKNOWN_CMD;
			break ;
	}
	return (rs);
}