#include "ZWCCThermostat.h"
#include "./includes/ZWCCThermostat_private.h"

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
	zuno_universalSetter1P(channel, ((ZwThermostatModeSetFrame_t *)cmd->cmd)->v2.level & THERMOSTAT_MASK_4_BIT);//Mode (4 bits)
}

static int _report_mode(uint8_t channel, bool reply) {
	ZwThermostatModeReportFrame_t			*lp;

	if(reply){
		lp = (ZwThermostatModeReportFrame_t *)&CMD_REPLY_CC;
		CMD_REPLY_LEN = sizeof(lp->v2);
	} else {
		lp = (ZwThermostatModeReportFrame_t *)&CMD_REPORT_CC;
		CMD_REPORT_LEN = sizeof(lp->v2);
	}
	
	lp->v2.cmdClass = COMMAND_CLASS_THERMOSTAT_MODE;
	lp->v2.cmd = THERMOSTAT_MODE_REPORT;
	lp->v2.level = zuno_universalGetter1P(channel) & THERMOSTAT_MASK_4_BIT;//Mode (4 bits)
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCThermostatModeHandler(uint8_t channel, ZUNOCommandPacket_t *cmd) {
	int				rs;

	rs = ZUNO_UNKNOWN_CMD;
	switch(ZW_CMD)
	{
		case THERMOSTAT_MODE_SET:
			_set_mode(channel, cmd);
			zunoSendReport(channel + 1);
			rs = ZUNO_COMMAND_PROCESSED;
			break ;
		case THERMOSTAT_MODE_GET:
			rs = _report_mode(channel, true);
			break ;
		case THERMOSTAT_MODE_SUPPORTED_GET:
			rs = _supported_report_mode(channel);
			break ;
	}
	return (rs);
}

static int _supported_report_setpoint(uint8_t channel) {//Processed to get the value of the thermostatmode components
	ZwThermostatSetpointSupportedReportFrame_t		*lp;
	uint8_t											sub_type;

	lp = (ZwThermostatSetpointSupportedReportFrame_t *)&CMD_REPLY_CC;
	sub_type = ZUNO_CFG_CHANNEL(channel).sub_type;//It contains a bitmask of thermostat
	lp->byte2.cmdClass = COMMAND_CLASS_THERMOSTAT_SETPOINT;
	lp->byte2.cmd = THERMOSTAT_SETPOINT_SUPPORTED_REPORT;
	lp->byte2.bitMask1 = sub_type & 0x7E;
	lp->byte2.bitMask2 = (sub_type >> 7) << 3;//This field MUST be encoded according to Table 142, interpretation A:
	CMD_REPLY_LEN = sizeof(lp->byte2);
	return (ZUNO_COMMAND_ANSWERED);
}


static uint16_t _limit_setpoint(uint8_t b_test, uint16_t value) {
	int16_t					up_limit;
	int16_t					down_limit;
	uint8_t					ratio;

	if ((b_test & THERMOSTAT_RANGE_NEG) != 0 && (b_test & THERMOSTAT_RANGE_POS) != 0) {
		up_limit = 10 * THERMOSTAT_SETPOINT_RATIO;
		down_limit = -10 * THERMOSTAT_SETPOINT_RATIO;
	} else if ((b_test & THERMOSTAT_RANGE_NEG) != 0 ) {
		up_limit = 0;
		down_limit = -10 * THERMOSTAT_SETPOINT_RATIO;
	} else {
		up_limit = 10 * THERMOSTAT_SETPOINT_RATIO;
		down_limit = 0;
	}
	ratio = b_test & THERMOSTAT_LIMITS_MASK;
	up_limit = up_limit * ratio;
	down_limit = down_limit * ratio;
	if ((int16_t)value > up_limit)
		value = (uint16_t)up_limit;
	if ((int16_t)value < down_limit)
		value = (uint16_t)down_limit;
	return (value);
}

static int _report_setpoint(uint8_t channel, ZUNOCommandPacket_t *cmd) {
	ZwThermostatSetpointReportFrame_t			*lp;
	uint8_t										componentId;
	uint16_t									out;
	
	if (cmd != NULL) {
		componentId = ((ZwThermostatSetpointGetFrame_t *)cmd->cmd)->level;
		lp = (ZwThermostatSetpointReportFrame_t *)&CMD_REPLY_CC;
		CMD_REPLY_LEN = sizeof(lp->byte2);

	} else {
		componentId = zuno_universalGetter1P(channel);
		lp = (ZwThermostatSetpointReportFrame_t *)&CMD_REPORT_CC;
		CMD_REPORT_LEN = sizeof(lp->byte2);
	}
	componentId = componentId & THERMOSTAT_MASK_4_BIT;//Setpoint Type (4 bits)
	lp->byte2.cmdClass = COMMAND_CLASS_THERMOSTAT_SETPOINT;
	lp->byte2.cmd = THERMOSTAT_SETPOINT_REPORT;
	lp->byte2.level = componentId;
	lp->byte2.level2 = THERMOSTAT_SETPOINT_PARAMETR(THERMOSTAT_SETPOINT_SIZE, THERMOSTAT_SETPOINT_SCALE(channel), THERMOSTAT_SETPOINT_PRECISION);
	out = zuno_universalGetter2P(channel, componentId);
	out = _limit_setpoint(ZUNO_CFG_CHANNEL(channel).params[0], out);
	lp->byte2.value1 = (uint8_t)(out >> (sizeof(out) * 8 / 2));
	lp->byte2.value2 = (uint8_t)(out & 0xFF);
	if(cmd == NULL){
		zunoSendZWPackage(&g_outgoing_report_packet);
	} else {
		zunoSendZWPackage(&g_outgoing_main_packet);
	}
	return (ZUNO_COMMAND_PROCESSED);
}

static void _set_setpoint(uint8_t channel, ZUNOCommandPacket_t *cmd) {
	ZwThermostatSetpointSetFrame_t				*lp;
	uint16_t									value;
	
	lp = (ZwThermostatSetpointSetFrame_t *)cmd->cmd;
	value = lp->byte2.value2 | (lp->byte2.value1 << (sizeof(value) * 8 / 2));
	value =_limit_setpoint(ZUNO_CFG_CHANNEL(channel).params[0], value);
	zuno_universalSetter2P(channel, lp->byte2.level & THERMOSTAT_MASK_4_BIT, value);
}

int zuno_CCThermostatSetPointHandler(uint8_t channel, ZUNOCommandPacket_t *cmd) {
	int				rs;

	rs = ZUNO_UNKNOWN_CMD;
	switch(ZW_CMD)
	{
		case THERMOSTAT_SETPOINT_SET:
			_set_setpoint(channel, cmd);
			zunoSendReport(channel + 1);
			rs = ZUNO_COMMAND_PROCESSED;
			break ;
		case THERMOSTAT_SETPOINT_GET:
			rs = _report_setpoint(channel, cmd);
			break ;
		case THERMOSTAT_SETPOINT_SUPPORTED_GET:
			rs = _supported_report_setpoint(channel);
			break ;
	}
	return (rs);
}

int zuno_CCThermostatReport(byte channel) {
	#ifdef WITH_CC_THERMOSTAT_MODE
	_report_mode(channel, false);
	#endif
	#ifdef WITH_CC_THERMOSTAT_SETPOINT
	_report_setpoint(channel, NULL);
	#endif
	return (ZUNO_COMMAND_PROCESSED);
	(void)channel;
}