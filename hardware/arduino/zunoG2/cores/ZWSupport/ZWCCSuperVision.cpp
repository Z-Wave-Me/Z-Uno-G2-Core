#include "Arduino.h"
#include "ZWSupport.h"
#include "Debug.h"
#include "ZWCCSuperVision.h"

typedef struct zuno_cc_supervision_data_s{
	uint8_t _prev_id;
	bool    _unpacked;
} zuno_cc_supervision_data_t;
uint8_t _previously_receive_session_id = 0xFF;
static zuno_cc_supervision_data_t __cc_supervision = {0xFF, false};

#ifdef LOGGING_DBG
void zuno_dbgdumpZWPacakge(ZUNOCommandPacket_t * cmd);
#endif
uint8_t zuno_CCSupervisionUnpack(ZUNOCommandPacket_t *cmd){
	ZwCSuperVisionGetFrame_t * frame = (ZwCSuperVisionGetFrame_t *)cmd->cmd;
	__cc_supervision._unpacked = false;
	if((frame->cmdClass != COMMAND_CLASS_SUPERVISION) || (frame->cmd != SUPERVISION_GET))
		return ZUNO_UNKNOWN_CMD;
	if ((cmd->zw_rx_secure_opts & 0x7) < (zunoSecurityStatus() & 0x7)) {
		
		ZwCSuperVisionReportFrame_t	* report = (ZwCSuperVisionReportFrame_t *)&CMD_REPLY_CC;
		report->properties1 = (frame->properties1 & SUPERVISION_GET_PROPERTIES1_SESSION_ID_MASK);
		report->status = SUPERVISION_REPORT_NO_SUPPORT;
		report->duration = 0x0;
		CMD_REPLY_LEN = sizeof(ZwCSuperVisionReportFrame_t);
		zunoSendZWPackage(&g_outgoing_main_packet);
		return (ZUNO_COMMAND_PROCESSED);
	}
	uint8_t				id = (frame->properties1 & SUPERVISION_GET_PROPERTIES1_SESSION_ID_MASK);
	if(id == __cc_supervision._prev_id){
		return ZUNO_COMMAND_PROCESSED;
	}
	__cc_supervision._unpacked = true;
	__cc_supervision._prev_id = id;
	cmd->cmd += 4;
	cmd->len -= 4;
	#ifdef LOGGING_DBG
	LOGGING_UART.print(millis());
	LOGGING_UART.print("SV UNPACK:  "); 
	zuno_dbgdumpZWPacakge(cmd);
	#endif
	return ZUNO_COMMAND_UNPACKED;
}
uint8_t zuno_CCSupervisionReport(uint8_t process_result){
	if(!__cc_supervision._unpacked)
		return process_result;
	ZwCSuperVisionReportFrame_t	* report = (ZwCSuperVisionReportFrame_t *)&CMD_REPLY_CC;
	report->properties1 = __cc_supervision._prev_id;
	switch (process_result) {
		case ZUNO_UNKNOWN_CMD:
		case ZUNO_COMMAND_PROCESSED:
		case ZUNO_COMMAND_ANSWERED:
			process_result = SUPERVISION_REPORT_SUCCESS;
			break;
		case ZUNO_COMMAND_BLOCKED_FAILL:
			process_result = SUPERVISION_REPORT_FAIL;
			break;
		case ZUNO_COMMAND_BLOCKED_NO_SUPPORT:
		default:
			process_result = SUPERVISION_REPORT_NO_SUPPORT;
			break;
	}
	report->status = process_result;
	report->duration = 0x0;
	CMD_REPLY_LEN = sizeof(ZwCSuperVisionReportFrame_t);
	__cc_supervision._unpacked = false;
	zunoSendZWPackage(&g_outgoing_main_packet);
	return (ZUNO_COMMAND_PROCESSED);
}