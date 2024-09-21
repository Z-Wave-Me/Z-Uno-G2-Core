#include "Arduino.h"
#include "ZWCCThermostat.h"
#if defined(WITH_CC_THERMOSTAT_MODE) || defined(WITH_CC_THERMOSTAT_SETPOINT)
static int _supported_report_mode(uint8_t channel, ZUNOCommandPacketReport_t *frame_report) {//Processed to get the value of the thermostatmode components
	ZwThermostatModeSupportedReportFrame_t		*lp;
	uint8_t										sub_type;

	lp = (ZwThermostatModeSupportedReportFrame_t *)frame_report->info.packet.cmd;
	sub_type = ZUNO_CFG_CHANNEL(channel).sub_type;//It contains a bitmask of thermostat
	// lp->byte2.cmdClass = COMMAND_CLASS_THERMOSTAT_MODE; set in - fillOutgoingPacket
	// lp->byte2.cmd = THERMOSTAT_MODE_SUPPORTED_REPORT; set in - fillOutgoingPacket
	lp->byte2.bitMask1 = (sub_type & 0x07) | ((sub_type & 0x08) << 4);
	sub_type >>= 4;
	lp->byte2.bitMask2 = (sub_type & 0x07) | ((sub_type & 0x08) << 4);
	frame_report->info.packet.len = sizeof(lp->byte2);
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

size_t zuno_CCThermostatModeTobasic(size_t channel, size_t value) {
	if (value == 0x0)
		return (0x0);
	value = THERMOSTAT_MODE_HEAT;
	while (value <= THERMOSTAT_MODE_FULL_POWER) {
		if (_bitTestComponentId(channel, value) == true)
			return (value);
		value++;
	}
	return (0x0);
}

static int _set_mode(size_t channel, const ZwThermostatModeSetFrame_t *cmd) {
	size_t										componentId;

	componentId = cmd->v2.level & THERMOSTAT_MASK_4_BIT;
	if (_bitTestComponentId(channel, componentId) == false)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	zuno_universalSetter1P(channel, componentId);
	zunoSendReport(channel + 1);
	return (ZUNO_COMMAND_PROCESSED);
}

static int _report_mode(uint8_t channel, ZUNOCommandPacket_t *packet) {
	ZwThermostatModeReportFrame_t			*report;

	report = (ZwThermostatModeReportFrame_t *)&packet->packet.cmd[0x0];
	report->v2.cmdClass = COMMAND_CLASS_THERMOSTAT_MODE;
	report->v2.cmd = THERMOSTAT_MODE_REPORT;
	report->v2.level = zuno_universalGetter1P(channel) & THERMOSTAT_MASK_4_BIT;//Mode (4 bits)
	packet->packet.len = sizeof(report->v2);
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCThermostatModeHandler(uint8_t channel, const ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	int				rs;

	switch(ZW_CMD) {
		case THERMOSTAT_MODE_SET:
			rs = _set_mode(channel, (const ZwThermostatModeSetFrame_t *)cmd->cmd);
			break ;
		case THERMOSTAT_MODE_GET:
			_zunoMarkChannelRequested(channel);
			rs = _report_mode(channel, &frame_report->info);
			break ;
		case THERMOSTAT_MODE_SUPPORTED_GET:
			rs = _supported_report_mode(channel, frame_report);
			break ;
		default:
			rs = ZUNO_COMMAND_BLOCKED_NO_SUPPORT;
			break ;
	}
	return (rs);
}

static int _supported_report_setpoint(uint8_t channel, ZUNOCommandPacketReport_t *frame_report) {//Processed to get the value of the thermostatmode components
	ZwThermostatSetpointSupportedReportFrame_t		*lp;
	uint8_t											sub_type;

	lp = (ZwThermostatSetpointSupportedReportFrame_t *)frame_report->info.packet.cmd;
	sub_type = ZUNO_CFG_CHANNEL(channel).sub_type;//It contains a bitmask of thermostat
	// lp->byte2.cmdClass = COMMAND_CLASS_THERMOSTAT_SETPOINT; set in - fillOutgoingPacket
	// lp->byte2.cmd = THERMOSTAT_SETPOINT_SUPPORTED_REPORT; set in - fillOutgoingPacket
	lp->byte2.bitMask1 = sub_type & 0x7E;
	lp->byte2.bitMask2 = (sub_type >> 7) << 3;//This field MUST be encoded according to Table 142, interpretation A:
	frame_report->info.packet.len = sizeof(lp->byte2);
	return (ZUNO_COMMAND_ANSWERED);
}

static void _get_limits_setpoint(uint8_t compressed_value, int16_t & down_limit, int16_t &	up_limit){
	if (((compressed_value & THERMOSTAT_RANGE_NEG) != 0) && 
		((compressed_value & THERMOSTAT_RANGE_POS) != 0)) {
		up_limit = 10 * THERMOSTAT_SETPOINT_RATIO;
		down_limit = -10 * THERMOSTAT_SETPOINT_RATIO;
	} else if ((compressed_value & THERMOSTAT_RANGE_NEG) != 0 ) {
		up_limit = 0;
		down_limit = -10 * THERMOSTAT_SETPOINT_RATIO;
	} else {
		up_limit = 10 * THERMOSTAT_SETPOINT_RATIO;
		down_limit = 0;
	}
	down_limit *= (compressed_value & THERMOSTAT_LIMITS_MASK);
	up_limit *= (compressed_value & THERMOSTAT_LIMITS_MASK);

}
static uint16_t _limit_setpoint(uint8_t b_test, uint16_t value) {
	int16_t					up_limit;
	int16_t					down_limit;
	_get_limits_setpoint(b_test, down_limit, up_limit);
	if ((int16_t)value > up_limit)
		value = (uint16_t)up_limit;
	if ((int16_t)value < down_limit)
		value = (uint16_t)down_limit;
	return (value);
}

static int  _setpoint_get(size_t channel, const ZwThermostatSetpointGetFrame_t *cmd, ZUNOCommandPacket_t *packet) {
	ZwThermostatSetpointReportFrame_t			*report;
	size_t										componentId;
	uint16_t									out;
	size_t										count;
	
	if (cmd != NULL)
		componentId = cmd->level;
	else
		componentId = zuno_universalGetter1P(channel);
	report = (ZwThermostatSetpointReportFrame_t *)&packet->packet.cmd[0x0];
	componentId = componentId & THERMOSTAT_MASK_4_BIT;//Setpoint Type (4 bits)
	report->cmdClass = COMMAND_CLASS_THERMOSTAT_SETPOINT;
	report->cmd = THERMOSTAT_SETPOINT_REPORT;
	if (_bitTestComponentId(channel, componentId) == true) {
		report->level = componentId;
		report->level2 = THERMOSTAT_SETPOINT_PARAMETR(THERMOSTAT_SETPOINT_SIZE, THERMOSTAT_SETPOINT_SCALE(channel), THERMOSTAT_SETPOINT_PRECISION);
		out = zuno_universalGetter2P(channel, componentId);
		out = _limit_setpoint(ZUNO_CFG_CHANNEL(channel).params[0], out);
		report->value[0x0] = (uint8_t)(out >> (sizeof(out) * 8 / 2));
		report->value[0x1] = (uint8_t)(out & 0xFF);
		count = THERMOSTAT_SETPOINT_SIZE;
	}
	else {
		report->level = 0x0;
		report->level2 = 0x1;//THERMOSTAT_SETPOINT_PARAMETR(THERMOSTAT_SETPOINT_SIZE, THERMOSTAT_CELSIUS, THERMOSTAT_SETPOINT_PRECISION);
		report->value[0x0] = 0x0;
		count = 0x1;
	}
	packet->packet.len = sizeof(report[0x0]) + count;
	return (ZUNO_COMMAND_ANSWERED);
}

static int _set_setpoint(uint8_t channel, const ZUNOCommandCmd_t *cmd) {
	ZwThermostatSetpointSetFrame_t				*lp;
	size_t										sub_type;
	uint16_t									value;

	lp = (ZwThermostatSetpointSetFrame_t *)cmd->cmd;
	sub_type = ZUNO_CFG_CHANNEL(channel).sub_type;//It contains a bitmask of thermostat
	sub_type = (sub_type & 0x7E) | ((sub_type >> 7) << 3);//This field MUST be encoded according to Table 142, interpretation A:
	if ((sub_type & (0x1 << (lp->byte1.level & THERMOSTAT_SETPOINT_SET_LEVEL_SETPOINT_TYPE_MASK))) == 0x0)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	if ((lp->byte1.level2 & (THERMOSTAT_SETPOINT_SET_LEVEL2_SIZE_MASK | THERMOSTAT_SETPOINT_SET_LEVEL2_SCALE_MASK)) != (THERMOSTAT_SETPOINT_SIZE | (THERMOSTAT_SETPOINT_SCALE(channel) << THERMOSTAT_SETPOINT_SET_LEVEL2_SCALE_SHIFT)))
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	value = lp->byte2.value2 | (lp->byte2.value1 << (sizeof(value) * 8 / 2));
	value =_limit_setpoint(ZUNO_CFG_CHANNEL(channel).params[0], value);
	zuno_universalSetter2P(channel, lp->byte2.level & THERMOSTAT_MASK_4_BIT, value);
	return (ZUNO_COMMAND_PROCESSED);
}

static int _setpoint_capabilities_get(size_t channel, const ZwThermostatSetpointCapabilitiesGetFrame_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	ZwThermostatSetpointCapabilitiesReportFrame_t		*report;
	size_t												componentId;
	uint8_t												*data;
	size_t												count;

	report = (ZwThermostatSetpointCapabilitiesReportFrame_t *)frame_report->info.packet.cmd;
	// report->cmdClass = COMMAND_CLASS_THERMOSTAT_SETPOINT; set in - fillOutgoingPacket
	// report->cmd = THERMOSTAT_SETPOINT_CAPABILITIES_REPORT; set in - fillOutgoingPacket
	componentId = cmd->properties1 & THERMOSTAT_MASK_4_BIT;
	data = &report->data[0x0];
	int16_t					up_limit;
	int16_t					down_limit;
	_get_limits_setpoint(ZUNO_CFG_CHANNEL(channel).params[0], down_limit, up_limit);
	if (_bitTestComponentId(channel, componentId) == true) {
		report->properties1 = componentId;
		data[0] = THERMOSTAT_SETPOINT_PARAMETR(THERMOSTAT_SETPOINT_SIZE, THERMOSTAT_SETPOINT_SCALE(channel), THERMOSTAT_SETPOINT_PRECISION);
		data[1] = down_limit >> 8;
		data[2] = down_limit & 0xFF;
		data[3] = THERMOSTAT_SETPOINT_PARAMETR(THERMOSTAT_SETPOINT_SIZE, THERMOSTAT_SETPOINT_SCALE(channel), THERMOSTAT_SETPOINT_PRECISION);
		data[4] = up_limit >> 8;
		data[5] = up_limit & 0xFF;
		count = 0x2 + THERMOSTAT_SETPOINT_SIZE * 0x2;
	}
	else {
		report->properties1 = 0;
		data[0] = 1;
		data[1] = 0;
		data[2] = 1;
		data[3] = 0;
		count = 4;
	}
	frame_report->info.packet.len = sizeof(ZwThermostatSetpointCapabilitiesReportFrame_t) + count;
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCThermostatSetPointHandler(uint8_t channel, const ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	int				rs;

	switch(ZW_CMD) {
		case THERMOSTAT_SETPOINT_SET:
			rs = _set_setpoint(channel, cmd);
			zunoSendReport(channel + 1);
			break ;
		case THERMOSTAT_SETPOINT_GET:
			_zunoMarkChannelRequested(channel);
			rs = _setpoint_get(channel, (const ZwThermostatSetpointGetFrame_t *)cmd->cmd, &frame_report->info);
			break ;
		case THERMOSTAT_SETPOINT_SUPPORTED_GET:
			rs = _supported_report_setpoint(channel, frame_report);
			break ;
		case THERMOSTAT_SETPOINT_CAPABILITIES_GET:
			rs = _setpoint_capabilities_get(channel, (const ZwThermostatSetpointCapabilitiesGetFrame_t *)cmd->cmd, frame_report);
			break ;
		default:
			rs = ZUNO_COMMAND_BLOCKED_NO_SUPPORT;
			break ;
	}
	return (rs);
}


int zuno_CCThermostatReport(byte channel, ZUNOCommandPacket_t *packet) {
	int				rs;

	#ifdef WITH_CC_THERMOSTAT_MODE
	rs = _report_mode(channel, packet);
	#endif
	#ifdef WITH_CC_THERMOSTAT_SETPOINT
	rs = _setpoint_get(channel, NULL, packet);
	#endif
	return (rs);
}
#endif
