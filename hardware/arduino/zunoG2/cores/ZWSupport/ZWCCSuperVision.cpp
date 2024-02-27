#include "Arduino.h"
#include "ZWSupport.h"
#include "Debug.h"
#include "ZWCCSuperVision.h"
#include "ZWCCTimer.h"
#include "ZWCCAssociation.h"
#include "ZWCCConfiguration.h"


uint8_t _previously_receive_session_id = 0xFF;
zuno_cc_supervision_data_t __cc_supervision = {0xFF, 0x00, false, 0x00};

#ifdef LOGGING_DBG
void zuno_dbgdumpZWPacakge(ZUNOCommandPacket_t * cmd);
#endif

bool __zuno_CCSupervisionReportSendTest(uint8_t duration) {
	if (duration != 0x0 && (__cc_supervision.properties1 & SUPERVISION_REPORT_PROPERTIES1_MORE_STATUS_UPDATES_BIT_MASK) != 0x0)
		return (true);
	return (false);
}

static uint8_t __zuno_CCSupervisionReportSend(uint8_t process_result, uint8_t duration, ZunoTimerBasic_t *timer, ZUNOCommandPacketReport_t *frame_report){
	ZwCSuperVisionReportFrame_t	* report = (ZwCSuperVisionReportFrame_t *)frame_report->packet.cmd;
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
		case ZUNO_COMMAND_BLOCKED_WORKING:
			process_result = SUPERVISION_REPORT_WORKING;
			break;
		case ZUNO_COMMAND_BLOCKED_NO_SUPPORT:
		default:
			process_result = SUPERVISION_REPORT_NO_SUPPORT;
			break;
	}
	report->cmdClass = COMMAND_CLASS_SUPERVISION;
	report->cmd = SUPERVISION_REPORT;
	report->status = process_result;
	report->duration = duration;
	if (__zuno_CCSupervisionReportSendTest(duration) == true) {
		report->properties1 = report->properties1 | SUPERVISION_REPORT_PROPERTIES1_MORE_STATUS_UPDATES_BIT_MASK;
		if (timer != 0x0)
			timer->bMode = timer->bMode | ZUNO_TIMER_SWITCH_SUPERVISION;
	}
	frame_report->packet.len = sizeof(ZwCSuperVisionReportFrame_t);
	__cc_supervision._unpacked = false;
	zunoSendZWPackage(&frame_report->packet);
	return (ZUNO_COMMAND_PROCESSED);
}



int zuno_CCAssociationHandler(ZUNOCommandPacket_t *cmd);
static void __unpackSV(ZUNOCommandPacket_t *cmd, ZwCSuperVisionGetFrame_t *frame){
	cmd->len -= 4;
	__cc_supervision._unpacked = true;
	__cc_supervision._node_id = cmd->src_node;
	__cc_supervision.properties1 = frame->properties1;
	#ifdef LOGGING_DBG
	LOGGING_UART.print(millis());
	LOGGING_UART.print("SV UNPACK:  "); 
	zuno_dbgdumpZWPacakge(cmd);
	#endif
}
node_id_t zunoGetSupervisionHost(){
	if(!__cc_supervision._unpacked)
		return 0;
	return __cc_supervision._node_id;
}
uint8_t zuno_CCSupervisionUnpack(uint8_t process_result, ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	ZwCSuperVisionGetFrame_t								*frame;
	uint8_t													id;

	// Always answer to supervision as we were asked (the same security scheme)
	frame_report->packet.zw_rx_secure_opts = cmd->zw_rx_secure_opts;

	frame = (ZwCSuperVisionGetFrame_t *)cmd->cmd;
	if((frame->cmdClass != COMMAND_CLASS_SUPERVISION) || (frame->cmd != SUPERVISION_GET))
		return (process_result);
    __cc_supervision._unpacked = false;
	#ifdef SUPERVISION_HIGHEST_S2_ONLY
	#pragma message "Higher Supervision level only"
	if (cmd->zw_rx_secure_opts != zunoSecurityStatus()) {
			return ZUNO_COMMAND_BLOCKED;
	}
	#endif
	id = (frame->properties1 & SUPERVISION_GET_PROPERTIES1_SESSION_ID_MASK);
	
	if (id == __cc_supervision._prev_id)
		return (ZUNO_COMMAND_PROCESSED);
	__cc_supervision._prev_id = id;
	if (_zunoTransposeSecurityLevel(cmd->zw_rx_secure_opts) < _zunoTransposeSecurityLevel(zunoSecurityStatus())) {
		return __zuno_CCSupervisionReportSend(ZUNO_COMMAND_BLOCKED_NO_SUPPORT, 0, NULL, frame_report);
	}
	cmd->cmd += 4;
	switch (ZW_CMD_CLASS) {
		case COMMAND_CLASS_POWERLEVEL:
			break;
		case COMMAND_CLASS_ASSOCIATION:
		case COMMAND_CLASS_MULTI_CHANNEL_ASSOCIATION:
			if(cmd->dst_zw_channel == 0)
				return ZUNO_UNKNOWN_CMD;
			//if (ZW_CMD == ASSOCIATION_SET || ZW_CMD == ASSOCIATION_REMOVE) //&& zuno_CCAssociationHandler(cmd) == ZUNO_UNKNOWN_CMD)
			//	break ;
			__unpackSV(cmd, frame);
			return (ZUNO_COMMAND_UNPACKED);
		default:
			__unpackSV(cmd, frame);
			return (ZUNO_COMMAND_UNPACKED);
			break ;
	}
	cmd->cmd -= 4;
	return (ZUNO_UNKNOWN_CMD);
}

uint8_t zuno_CCSupervisionReport(uint8_t process_result, uint8_t duration, ZunoTimerBasic_t *timer, ZUNOCommandPacketReport_t *frame_report){
	if(!__cc_supervision._unpacked)
		return process_result;
	return __zuno_CCSupervisionReportSend(process_result, duration, timer,frame_report);
}

int zuno_CCSupervisionApp(int result, ZUNOCommandPacketReport_t *frame_report) {
	ZwApplicationRejectedRequestFrame_t						*report;

	if (zuno_CCSupervisionReport(result, 0x0, 0x0, frame_report) != result)
		return (ZUNO_COMMAND_PROCESSED);
	report = (ZwApplicationRejectedRequestFrame_t *)frame_report->packet.cmd;
	report->cmdClass = COMMAND_CLASS_APPLICATION_STATUS;
	report->cmd = APPLICATION_REJECTED_REQUEST;
	report->status = 0x0;
	frame_report->packet.len = sizeof(ZwApplicationRejectedRequestFrame_t);
	zunoSendZWPackage(&frame_report->packet);
	return (ZUNO_COMMAND_PROCESSED);
}