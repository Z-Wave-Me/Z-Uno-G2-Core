#include "Arduino.h"
#include "ReportHandler.h"

float zunoFixToFloat(uint8_t len, uint8_t precision, uint8_t *array) {
	uint32_t				number;
	float					out;
	size_t 					factor;

	switch (len) {
		case sizeof(uint16_t):
			number = ((array[0] << 0x8) | array[1]);
			break ;
		case sizeof(uint32_t):
			number = ((array[0] << 0x18) | (array[1] << 0x10) | (array[2] << 0x8) | array[3]);
			break ;
		default:
			number = array[0];
			break ;
	}
	factor = 0x1;
	while(precision-- != 0x0)
		factor = factor * 10;
	out = number / factor;
	return (out);
}

void zunoReportHandler(ZUNOCommandPacket_t *cmd) {
	ReportAuxData_t			report_data;
	uint8_t					cmdClass;
	uint8_t					sub_type;
	uint8_t					zwcmd;
	
	cmdClass = ZW_CMD_CLASS;
	zwcmd = ZW_CMD;
	switch(cmdClass) {
			case COMMAND_CLASS_BASIC:
				if (zwcmd != BASIC_REPORT)
					return ;
				sub_type = Basic;
				break ;
			case COMMAND_CLASS_SWITCH_BINARY:
				if (zwcmd != SWITCH_BINARY_REPORT)
					return ;
				sub_type = SwitchBinary;
				break ;
			case COMMAND_CLASS_SWITCH_MULTILEVEL:
				if (zwcmd != SWITCH_MULTILEVEL_REPORT)
					return ;
				sub_type = SwitchMultilevel;
				break ;
			case COMMAND_CLASS_SENSOR_MULTILEVEL:
				if (zwcmd != SENSOR_MULTILEVEL_REPORT)
					return ;
				sub_type = SensorMultilevel;
				break ;
			case COMMAND_CLASS_METER:
				if (zwcmd != METER_REPORT)
					return ;
				sub_type = Meter;
				break ;
			case COMMAND_CLASS_NOTIFICATION:
				if (zwcmd != NOTIFICATION_REPORT)
					return ;
				sub_type = Notification;
				break ;
			case COMMAND_CLASS_BATTERY:
				if (zwcmd != BATTERY_REPORT)
					return ;
				sub_type = Battery;
				break ;
			default:
				return ;
	}
	report_data.cmdClass = cmdClass;
	report_data.channelSource = cmd->src_zw_channel;
	report_data.nodeIdSource = cmd->src_node;
	report_data.len = cmd->len;
	report_data.rawReportData = cmd->cmd;
	zunoSysHandlerCall(ZUNO_HANDLER_REPORT, sub_type, &report_data);
}