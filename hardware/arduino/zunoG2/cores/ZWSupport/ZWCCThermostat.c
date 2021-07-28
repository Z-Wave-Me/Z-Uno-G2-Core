#include "Arduino.h"
#include "ZWCCThermostat.h"

static int _supported_report_mode(uint8_t channel) {//Processed to get the value of the thermostatmode components
	ZwThermostatModeSupportedReportFrame_t		*lp;
	uint8_t										sub_type;

	lp = (ZwThermostatModeSupportedReportFrame_t *)&CMD_REPLY_CC;
	sub_type = ZUNO_CFG_CHANNEL(channel).sub_type;//It contains a bitmask of thermostat
	// lp->byte2.cmdClass = COMMAND_CLASS_THERMOSTAT_MODE; set in - fillOutgoingPacket
	// lp->byte2.cmd = THERMOSTAT_MODE_SUPPORTED_REPORT; set in - fillOutgoingPacket
	lp->byte2.bitMask1 = (sub_type & 0x07) | ((sub_type & 0x08) << 4);
	sub_type >>= 4;
	lp->byte2.bitMask2 = (sub_type & 0x07) | ((sub_type & 0x08) << 4);
	CMD_REPLY_LEN = sizeof(lp->byte2);
	return (ZUNO_COMMAND_ANSWERED);
}

static size_t _bitTestComponentId(size_t channel, size_t componentId) {
	size_t							offset;

	switch (componentId) {
		case THERMOSTAT_MODE_OFF:
			offset = THERMOSTAT_FLAGS_OFF;
			break ;
		case THERMOSTAT_MODE_HEAT:
			offset = THERMOSTAT_FLAGS_HEAT;
			break ;
		case THERMOSTAT_MODE_COOL:
			offset = THERMOSTAT_FLAGS_COOL;
			break ;
		case THERMOSTAT_MODE_FURNACE:
			offset = THERMOSTAT_FLAGS_FURNACE;
			break ;
		case THERMOSTAT_MODE_DRY:
			offset = THERMOSTAT_FLAGS_DRY;
			break ;
		case THERMOSTAT_MODE_MOIST:
			offset = THERMOSTAT_FLAGS_MOIST;
			break ;
		case THERMOSTAT_MODE_AUTO_CHANGEOVER:
			offset = THERMOSTAT_FLAGS_AUTO_CHANGEOVER;
			break ;
		#if THERMOSTAT_MODE_AUTO_CHANGEOVER != THERMOSTAT_MODE_AUTO
		case THERMOSTAT_MODE_AUTO:
			offset = THERMOSTAT_FLAGS_AUTO;
			break ;
		#endif
		case THERMOSTAT_MODE_FULL_POWER:
			offset = THERMOSTAT_FLAGS_FULL_POWER;
			break ;
		default:
			return (false);
			break ;
	}
	if ((ZUNO_CFG_CHANNEL(channel).sub_type & offset) != 0x0)
		return (true);
	return (false);
}

static int _set_mode(size_t channel, const ZwThermostatModeSetFrame_t *cmd) {
	size_t										componentId;

	componentId = cmd->v2.level & THERMOSTAT_MASK_4_BIT;
	if (_bitTestComponentId(channel, componentId) == false)
		return (ZUNO_COMMAND_BLOCKED);
	zuno_universalSetter1P(channel, componentId);
	zunoSendReport(channel + 1);
	return (ZUNO_COMMAND_PROCESSED);
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

	switch(ZW_CMD) {
		case THERMOSTAT_MODE_SET:
			rs = _set_mode(channel, (const ZwThermostatModeSetFrame_t *)cmd->cmd);
			break ;
		case THERMOSTAT_MODE_GET:
			_zunoMarkChannelRequested(channel);
			rs = _report_mode(channel, true);
			break ;
		case THERMOSTAT_MODE_SUPPORTED_GET:
			rs = _supported_report_mode(channel);
			break ;
		default:
			rs = ZUNO_UNKNOWN_CMD;
			break ;
	}
	return (rs);
}

static int _supported_report_setpoint(uint8_t channel) {//Processed to get the value of the thermostatmode components
	ZwThermostatSetpointSupportedReportFrame_t		*lp;
	uint8_t											sub_type;

	lp = (ZwThermostatSetpointSupportedReportFrame_t *)&CMD_REPLY_CC;
	sub_type = ZUNO_CFG_CHANNEL(channel).sub_type;//It contains a bitmask of thermostat
	// lp->byte2.cmdClass = COMMAND_CLASS_THERMOSTAT_SETPOINT; set in - fillOutgoingPacket
	// lp->byte2.cmd = THERMOSTAT_SETPOINT_SUPPORTED_REPORT; set in - fillOutgoingPacket
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

static int  _setpoint_get(size_t channel, const ZwThermostatSetpointGetFrame_t *cmd) {
	ZwThermostatSetpointReportFrame_t			*lp;
	size_t										componentId;
	uint16_t									out;
	size_t										count;
	
	if (cmd != NULL) {
		componentId = cmd->level;
		lp = (ZwThermostatSetpointReportFrame_t *)&CMD_REPLY_CC;
	} else {
		componentId = zuno_universalGetter1P(channel);
		lp = (ZwThermostatSetpointReportFrame_t *)&CMD_REPORT_CC;
		
	}
	componentId = componentId & THERMOSTAT_MASK_4_BIT;//Setpoint Type (4 bits)
	lp->cmdClass = COMMAND_CLASS_THERMOSTAT_SETPOINT;
	lp->cmd = THERMOSTAT_SETPOINT_REPORT;
	if (_bitTestComponentId(channel, componentId) == true) {
		lp->level = componentId;
		lp->level2 = THERMOSTAT_SETPOINT_PARAMETR(THERMOSTAT_SETPOINT_SIZE, THERMOSTAT_SETPOINT_SCALE(channel), THERMOSTAT_SETPOINT_PRECISION);
		out = zuno_universalGetter2P(channel, componentId);
		out = _limit_setpoint(ZUNO_CFG_CHANNEL(channel).params[0], out);
		lp->value[0x0] = (uint8_t)(out >> (sizeof(out) * 8 / 2));
		lp->value[0x1] = (uint8_t)(out & 0xFF);
		count = THERMOSTAT_SETPOINT_SIZE;
	}
	else {
		lp->level = 0x0;
		lp->level2 = 0x1;//THERMOSTAT_SETPOINT_PARAMETR(THERMOSTAT_SETPOINT_SIZE, THERMOSTAT_CELSIUS, THERMOSTAT_SETPOINT_PRECISION);
		lp->value[0x0] = 0x0;
		count = 0x1;
	}
	if(cmd == NULL){
		CMD_REPORT_LEN = sizeof(ZwThermostatSetpointReportFrame_t) + count;
		zunoSendZWPackage(&g_outgoing_report_packet);
	} else {
		CMD_REPLY_LEN = sizeof(ZwThermostatSetpointReportFrame_t) + count;
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

static int _setpoint_capabilities_get(size_t channel, const ZwThermostatSetpointCapabilitiesGetFrame_t *cmd) {
	ZwThermostatSetpointCapabilitiesReportFrame_t		*report;
	size_t												componentId;
	uint8_t												*data;
	size_t												count;

	report = (ZwThermostatSetpointCapabilitiesReportFrame_t *)&CMD_REPLY_CC;
	// report->cmdClass = COMMAND_CLASS_THERMOSTAT_SETPOINT; set in - fillOutgoingPacket
	// report->cmd = THERMOSTAT_SETPOINT_CAPABILITIES_REPORT; set in - fillOutgoingPacket
	componentId = cmd->properties1 & THERMOSTAT_MASK_4_BIT;
	data = &report->data[0x0];
	if (_bitTestComponentId(channel, componentId) == true) {
		report->properties1 = componentId;
		data[0x0] = THERMOSTAT_SETPOINT_PARAMETR(THERMOSTAT_SETPOINT_SIZE, THERMOSTAT_SETPOINT_SCALE(channel), THERMOSTAT_SETPOINT_PRECISION);
		data[0x1] = 0x0;
		data[0x2] = 0x0;
		data[0x3] = THERMOSTAT_SETPOINT_PARAMETR(THERMOSTAT_SETPOINT_SIZE, THERMOSTAT_SETPOINT_SCALE(channel), THERMOSTAT_SETPOINT_PRECISION);
		data[0x4] = 0xFF;
		data[0x5] = 0xFF;
		count = 0x2 + THERMOSTAT_SETPOINT_SIZE * 0x2;
	}
	else {
		report->properties1 = 0x0;
		data[0x0] = 0x1;
		data[0x1] = 0x0;
		data[0x2] = 0x1;
		data[0x3] = 0x0;
		count = 0x4;
	}
	CMD_REPLY_LEN = sizeof(ZwThermostatSetpointCapabilitiesReportFrame_t) + count;
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCThermostatSetPointHandler(uint8_t channel, ZUNOCommandPacket_t *cmd) {
	int				rs;

	switch(ZW_CMD) {
		case THERMOSTAT_SETPOINT_SET:
			_set_setpoint(channel, cmd);
			zunoSendReport(channel + 1);
			rs = ZUNO_COMMAND_PROCESSED;
			break ;
		case THERMOSTAT_SETPOINT_GET:
			_zunoMarkChannelRequested(channel);
			rs = _setpoint_get(channel, (const ZwThermostatSetpointGetFrame_t *)cmd->cmd);
			break ;
		case THERMOSTAT_SETPOINT_SUPPORTED_GET:
			rs = _supported_report_setpoint(channel);
			break ;
		case THERMOSTAT_SETPOINT_CAPABILITIES_GET:
			rs = _setpoint_capabilities_get(channel, (const ZwThermostatSetpointCapabilitiesGetFrame_t *)cmd->cmd);
			break ;
		default:
			rs = ZUNO_UNKNOWN_CMD;
			break ;
	}
	return (rs);
}

int zuno_CCThermostatReport(byte channel) {
	#ifdef WITH_CC_THERMOSTAT_MODE
	_report_mode(channel, false);
	#endif
	#ifdef WITH_CC_THERMOSTAT_SETPOINT
	 _setpoint_get(channel, NULL);
	#endif
	return (ZUNO_COMMAND_PROCESSED);
	(void)channel;
}