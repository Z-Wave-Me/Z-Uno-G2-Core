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

static int _secyrity(uint8_t sec) {
	int				ret;

	switch (sec) {
		case SECURITY_KEY_NONE:
			ret = -2;
			break;
		case SECURITY_KEY_S0:
			ret = -1;
			break;
		default:
			ret = sec;
			break;
	}
	return (ret);
}

int zuno_CCAssociationHandler(ZUNOCommandPacket_t *cmd);

uint8_t zuno_CCSupervisionUnpack(uint8_t process_result, ZUNOCommandPacket_t *cmd){
	ZwCSuperVisionGetFrame_t								*frame;
	uint8_t													id;

	frame = (ZwCSuperVisionGetFrame_t *)cmd->cmd;
	if((frame->cmdClass != COMMAND_CLASS_SUPERVISION) || (frame->cmd != SUPERVISION_GET))
		return (process_result);
	id = (frame->properties1 & SUPERVISION_GET_PROPERTIES1_SESSION_ID_MASK);
	__cc_supervision._unpacked = false;
	if (id == __cc_supervision._prev_id)
		return (ZUNO_COMMAND_PROCESSED);
	__cc_supervision._prev_id = id;
	if (_secyrity(cmd->zw_rx_secure_opts) < _secyrity(zunoSecurityStatus())) {
		ZwCSuperVisionReportFrame_t	* report = (ZwCSuperVisionReportFrame_t *)&CMD_REPLY_CC;
		report->properties1 = id;
		report->status = SUPERVISION_REPORT_NO_SUPPORT;
		report->duration = 0x0;
		CMD_REPLY_LEN = sizeof(ZwCSuperVisionReportFrame_t);
		g_outgoing_main_packet.zw_rx_secure_opts = cmd->zw_rx_secure_opts;
		zunoSendZWPackage(&g_outgoing_main_packet);
		return (ZUNO_COMMAND_PROCESSED);
	}
	cmd->cmd += 4;
	switch (ZW_CMD_CLASS) {
		case COMMAND_CLASS_POWERLEVEL:
			break ;
		case COMMAND_CLASS_ASSOCIATION:
		case COMMAND_CLASS_MULTI_CHANNEL_ASSOCIATION:
			if ((ZW_CMD == 0x1 || ZW_CMD == 0x4) && zuno_CCAssociationHandler(cmd) == ZUNO_UNKNOWN_CMD)
				break ;
			cmd->len -= 4;
			__cc_supervision._unpacked = true;
			#ifdef LOGGING_DBG
			LOGGING_UART.print(millis());
			LOGGING_UART.print("SV UNPACK:  "); 
			zuno_dbgdumpZWPacakge(cmd);
			#endif
			return (ZUNO_COMMAND_UNPACKED);
			break ;
		default:
			cmd->len -= 4;
			__cc_supervision._unpacked = true;
			#ifdef LOGGING_DBG
			LOGGING_UART.print(millis());
			LOGGING_UART.print("SV UNPACK:  "); 
			zuno_dbgdumpZWPacakge(cmd);
			#endif
			return (ZUNO_COMMAND_UNPACKED);
			break ;
	}
	cmd->cmd -= 0x4;
	return (ZUNO_UNKNOWN_CMD);
}

uint8_t zuno_CCSupervisionReport(uint8_t process_result, ZUNOCommandPacket_t *cmd){
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
	g_outgoing_main_packet.zw_rx_secure_opts = cmd->zw_rx_secure_opts;
	zunoSendZWPackage(&g_outgoing_main_packet);
	return (ZUNO_COMMAND_PROCESSED);
}