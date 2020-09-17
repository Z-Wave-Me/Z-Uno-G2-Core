#include "Arduino.h"
#include "ReportHandler.h"


void zunoReportHandler(ZUNOCommandPacket_t *cmd) {
	ReportAuxDataAdd_t		report_data;
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
	report_data.main.cmdClass = cmdClass;
	report_data.main.channelSource = cmd->src_zw_channel;
	report_data.main.nodeIdSource = cmd->src_node;
	report_data.main.rawReportData = cmd->cmd;
	zunoSysHandlerCall(ZUNO_HANDLER_REPORT, sub_type, &report_data);
}