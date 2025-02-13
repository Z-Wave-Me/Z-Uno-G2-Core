#include "Arduino.h"
#include "ZWSupport.h"
#include "Debug.h"
#include "ZWCCSuperVision.h"
#include "ZWCCTimer.h"
#include "ZWCCAssociation.h"
#include "ZWCCConfiguration.h"

uint64_t rtcc_micros(void);
zuno_cc_supervision_data_t __cc_supervision = {
	.last_ms = 0x00,
	._node_id = 0x00,
	._prev_id = 0xFF,
	._unpacked = false,
	.properties1 = 0x00
};

#ifdef LOGGING_DBG
void zuno_dbgdumpZWPacakge(const ZUNOCommandCmd_t * cmd);
#endif

void zuno_CCSupervisionAsyncProcessedSet(const ZUNOCommandCmd_t *packet, ZwCSuperVisionReportAsyncProcessed_t *super_vision) {
	super_vision->id = __cc_supervision._prev_id;
	super_vision->dst = packet->src_node;
	super_vision->src_zw_channel = packet->dst_zw_channel;
	super_vision->dst_zw_channel = packet->src_zw_channel;
}
static void _supervision_send(ZUNOCommandPacketReport_t *frame_report, uint8_t id, bool more_status, uint8_t process_result, uint8_t duration){
	ZwCSuperVisionReportFrame_t						*report;

	switch (process_result) {
		case ZUNO_UNKNOWN_CMD:
		case ZUNO_COMMAND_PROCESSED:
		case ZUNO_COMMAND_ANSWERED:
			process_result = SUPERVISION_REPORT_SUCCESS;
			break;
		case ZUNO_COMMAND_BLOCKED_MALLOC:
		case ZUNO_COMMAND_BLOCKED_FAIL:
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
	report = (ZwCSuperVisionReportFrame_t *)frame_report->info.packet.cmd;
	if (more_status == true)
		id = id | SUPERVISION_REPORT_PROPERTIES1_MORE_STATUS_UPDATES_BIT_MASK;
	report->cmdClass = COMMAND_CLASS_SUPERVISION;
	report->cmd = SUPERVISION_REPORT;
	report->properties1 = id;
	report->status = process_result;
	report->duration = duration;
	frame_report->info.packet.len = sizeof(ZwCSuperVisionReportFrame_t);
	zunoSendZWPacketAdd(frame_report);
	return ;
}

int zuno_CCSupervisionReportSyncDefault(ZUNOCommandPacketReport_t *frame_report, uint8_t process_result) {
	if(__cc_supervision._unpacked == false)
		return (process_result);
	_supervision_send(frame_report, __cc_supervision._prev_id, false, process_result, 0x0);
	__cc_supervision._unpacked = false;
	return (ZUNO_COMMAND_PROCESSED);
}

void zuno_CCSupervisionReportSyncProcessed(ZUNOCommandPacketReport_t *frame_report) {
	if(__cc_supervision._unpacked == false)
		return ;
	_supervision_send(frame_report, __cc_supervision._prev_id, false, ZUNO_COMMAND_PROCESSED, 0x0);
	__cc_supervision._unpacked = false;
}

bool zuno_CCSupervisionReportSyncWorking(ZUNOCommandPacketReport_t *frame_report, uint8_t duration_table_8) {
	bool										more_status;
	uint8_t										process_result;

	more_status = false;
	if(__cc_supervision._unpacked == false)
		return (false);
	if (duration_table_8 == 0x0) {
		process_result = ZUNO_COMMAND_PROCESSED;
	}
	else {
		process_result = ZUNO_COMMAND_BLOCKED_WORKING;
		if ((__cc_supervision.properties1 & SUPERVISION_REPORT_PROPERTIES1_MORE_STATUS_UPDATES_BIT_MASK) != 0x0)
			more_status = true;
	}
	_supervision_send(frame_report, __cc_supervision._prev_id, more_status, process_result, duration_table_8);
	__cc_supervision._unpacked = false;
	if (more_status == false)
		return (false);
	return (true);
}

void zuno_CCSupervisionReportAsyncProcessed(ZUNOCommandPacketReport_t *frame_report, const ZwCSuperVisionReportAsyncProcessed_t *super_vision) {
	fillOutgoingRawPacket(&frame_report->info, &frame_report->data[0x0], super_vision->src_zw_channel, QUEUE_CHANNEL_SYNC, super_vision->dst);
	frame_report->info.packet.dst_zw_channel = super_vision->dst_zw_channel;
	_supervision_send(frame_report, super_vision->id, false, ZUNO_COMMAND_PROCESSED, 0x0);
}

bool __zuno_CCSupervisionReportSendTest(uint8_t duration) {
	if (duration != 0x0 && (__cc_supervision.properties1 & SUPERVISION_REPORT_PROPERTIES1_MORE_STATUS_UPDATES_BIT_MASK) != 0x0)
		return (true);
	return (false);
}

int zuno_CCAssociationHandler(ZUNOCommandCmd_t *cmd);
static void __unpackSV(ZUNOCommandCmd_t *cmd, ZwCSuperVisionGetFrame_t *frame, bool multicast){
	cmd->len -= 4;
	if (multicast == false)
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
uint8_t zuno_CCSupervisionUnpack(uint8_t process_result, ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report, bool multicast) {
	ZwCSuperVisionGetFrame_t								*frame;
	uint8_t													id;
	uint64_t												ms;

	// Always answer to supervision as we were asked (the same security scheme)
	frame_report->info.packet.zw_rx_secure_opts = cmd->zw_rx_secure_opts;

	frame = (ZwCSuperVisionGetFrame_t *)cmd->cmd;
	if((frame->cmdClass != COMMAND_CLASS_SUPERVISION) || (frame->cmd != SUPERVISION_GET))
		return (process_result);
	ms = rtcc_micros() / 1000;
	if ((__cc_supervision.last_ms + 1000000) >= ms) {
		__cc_supervision._prev_id = 0xFF;
	}
	__cc_supervision.last_ms = ms;
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
		if (multicast == false)
			__cc_supervision._unpacked = true;
		return zuno_CCSupervisionReportSyncDefault(frame_report, ZUNO_COMMAND_BLOCKED_NO_SUPPORT);
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
			__unpackSV(cmd, frame, multicast);
			return (ZUNO_COMMAND_UNPACKED);
		default:
			__unpackSV(cmd, frame, multicast);
			return (ZUNO_COMMAND_UNPACKED);
			break ;
	}
	cmd->cmd -= 4;
	return (ZUNO_UNKNOWN_CMD);
}

int zuno_CCSupervisionApp(int result, ZUNOCommandPacketReport_t *frame_report) {
	ZwApplicationRejectedRequestFrame_t						*report;

	if (zuno_CCSupervisionReportSyncDefault(frame_report, result) != result)
		return (ZUNO_COMMAND_PROCESSED);
	report = (ZwApplicationRejectedRequestFrame_t *)frame_report->info.packet.cmd;
	report->cmdClass = COMMAND_CLASS_APPLICATION_STATUS;
	report->cmd = APPLICATION_REJECTED_REQUEST;
	report->status = 0x0;
	frame_report->info.packet.len = sizeof(ZwApplicationRejectedRequestFrame_t);
	zunoSendZWPacketAdd(frame_report);
	return (ZUNO_COMMAND_PROCESSED);
}