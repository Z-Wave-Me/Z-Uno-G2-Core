#include "ZWCCSwitchThermostat.h"
#include "./includes/ZWCCSwitchThermostat_private.h"

static int _supported_report_mode(uint8_t channel) {//Processed to get the value of the thermostatmode components
	ZwThermostatModeSupportedReportFrame_t		*lp;
	uint8_t										sub_type;

	lp = (ZwThermostatModeSupportedReportFrame_t *)&CMD_REPLY_CC;
	sub_type = ZUNO_CFG_CHANNEL(channel).sub_type;//It contains a bitmask of thermostat
	lp->byte2.cmdClass = COMMAND_CLASS_THERMOSTAT_MODE;
	lp->byte2.cmd = THERMOSTAT_MODE_SUPPORTED_REPORT;
	lp->byte2.bitMask1 = (sub_type & 0x07) | ((sub_type & 0x08) << 4);
	sub_type >>= 4;
	lp->byte2.bitMask2 = (sub_type & 0x07) | ((sub_type & 0x08) << 4);
	CMD_REPLY_LEN = sizeof(lp->byte2);
	return (ZUNO_COMMAND_ANSWERED);
}

static void _set_mode(uint8_t channel, ZUNOCommandPacket_t *cmd) {

	zuno_universalSetter1P(channel, ((ZwThermostatModeSetFrame_t *)cmd->cmd)->v2.level & THERMOSTAT_MASK);//Mode (5 bits)
}

static int _report_mode(uint8_t channel)
{
	ZwThermostatModeReportFrame_t			*lp;

	lp = (ZwThermostatModeReportFrame_t *)&CMD_REPLY_CC;
	lp->v2.cmdClass = COMMAND_CLASS_THERMOSTAT_MODE;
	lp->v2.cmd = THERMOSTAT_MODE_REPORT;
	lp->v2.level = zuno_universalGetter1P(channel) & THERMOSTAT_MASK;//Mode (5 bits)
	CMD_REPLY_LEN = sizeof(lp->v2);
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCSwitchThermostatModeHandler(uint8_t channel, ZUNOCommandPacket_t *cmd)
{
	int				rs;

	rs = ZUNO_UNKNOWN_CMD;
	switch(ZW_CMD)
	{
		case THERMOSTAT_MODE_SET:
			_set_mode(channel, cmd);
			rs = ZUNO_COMMAND_PROCESSED;
			break ;
		case THERMOSTAT_MODE_GET:
			rs = _report_mode(channel);
			break ;
		case THERMOSTAT_MODE_SUPPORTED_GET:
			rs = _supported_report_mode(channel);
			break ;
	}
	return (rs);
}

static int _supported_report_setpoint(uint8_t channel) {//Processed to get the value of the thermostatmode components
	ZwThermostatSetpointSupportedReportFrame_t		*lp;
	uint8_t										sub_type;

	lp = (ZwThermostatSetpointSupportedReportFrame_t *)&CMD_REPLY_CC;
	sub_type = ZUNO_CFG_CHANNEL(channel).sub_type;//It contains a bitmask of thermostat
	lp->byte2.cmdClass = COMMAND_CLASS_THERMOSTAT_SETPOINT;
	lp->byte2.cmd = THERMOSTAT_SETPOINT_SUPPORTED_REPORT;
	lp->byte2.bitMask1 = (sub_type & 0x07) | ((sub_type & 0x08) << 4);
	sub_type >>= 4;
	lp->byte2.bitMask2 = (sub_type & 0x07) | ((sub_type & 0x08) << 4);
	CMD_REPLY_LEN = sizeof(lp->byte2);
	return (ZUNO_COMMAND_ANSWERED);
}


static int _report_setpoint(uint8_t channel)
{
	ZwThermostatSetpointReportFrame_t			*lp;

	lp = (ZwThermostatSetpointReportFrame_t *)&CMD_REPLY_CC;
	lp->byte2.cmdClass = COMMAND_CLASS_THERMOSTAT_SETPOINT;
	lp->byte2.cmd = THERMOSTAT_SETPOINT_REPORT;

	CMD_REPLY_LEN = sizeof(lp->byte2);
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCSwitchThermostatSetPointHandler(uint8_t channel, ZUNOCommandPacket_t *cmd)
{
	int				rs;

	rs = ZUNO_UNKNOWN_CMD;
	switch(ZW_CMD)
	{
		case THERMOSTAT_SETPOINT_SET:
			//_set_mode(channel, cmd);
			//rs = ZUNO_COMMAND_PROCESSED;
			break ;
		case THERMOSTAT_SETPOINT_GET:
			rs = _report_setpoint(channel);
			break ;
		case THERMOSTAT_SETPOINT_SUPPORTED_GET:
			rs = _supported_report_setpoint(channel);
			break ;
	}
	return (rs);
}