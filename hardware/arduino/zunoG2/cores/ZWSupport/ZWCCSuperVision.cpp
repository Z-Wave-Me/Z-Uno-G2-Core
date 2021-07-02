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
	__cc_supervision._unpacked = false;
	if((ZW_CMD_CLASS != COMMAND_CLASS_SUPERVISION) || (ZW_CMD != SUPERVISION_GET))
		return ZUNO_UNKNOWN_CMD;

	ZwCSuperVisionGetFrame_t * frame = (ZwCSuperVisionGetFrame_t *)cmd->cmd;
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
	report->status = (process_result == ZUNO_COMMAND_PROCESSED) ? SUPERVISION_REPORT_SUCCESS : SUPERVISION_REPORT_NO_SUPPORT;
	report->duration = 0x0;
	CMD_REPLY_LEN = sizeof(ZwCSuperVisionReportFrame_t);
	__cc_supervision._unpacked = false;
	return ZUNO_COMMAND_ANSWERED;
}