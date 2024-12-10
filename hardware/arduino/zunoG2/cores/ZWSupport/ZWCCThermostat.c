#include "Arduino.h"
#include "ZWCCThermostat.h"
#if defined(WITH_CC_THERMOSTAT_MODE) || defined(WITH_CC_THERMOSTAT_SETPOINT)

static uint32_t _get_compresed_combi_value(uint8_t channel)
{
	return (ZUNO_CFG_CHANNEL(channel).params[0]);
}

static uint32_t _get_mode_support_mask(uint8_t channel)
{
	uint32_t					mask;
	uint8_t						sub_type;
	uint8_t						params1;

	sub_type = ZUNO_CFG_CHANNEL(channel).sub_type;
	mask = ((sub_type & (THERMOSTAT_FLAGS_OFF|THERMOSTAT_FLAGS_HEAT|THERMOSTAT_FLAGS_COOL)) | ((sub_type & (THERMOSTAT_FLAGS_FURNACE)) << 4));
	mask = mask | (((sub_type & (THERMOSTAT_FLAGS_DRY|THERMOSTAT_FLAGS_MOIST|THERMOSTAT_FLAGS_AUTO_CHANGEOVER)) << 0x4) | ((sub_type & (THERMOSTAT_FLAGS_FULL_POWER)) << 0x8));
	params1 = ZUNO_CFG_CHANNEL(channel).params[0x1];
	mask = mask | (((params1 << 0x8) << 0x3) & (THERMOSTAT_FLAGS_MASK_PARAM_01 << 0x3));
	return (mask);
}

static bool _get_termostat_set_point_is_valid(uint8_t channel, uint8_t componentId)
{
	uint32_t									support_mode_mask;

	support_mode_mask = _get_mode_support_mask(channel);
	if ((support_mode_mask & (0x1 << componentId)) != 0x0)
		return (true);
	return (false);
}

static uint32_t _get_termostat_set_point_support_mask_interpretation_a(uint8_t channel)
{
	uint32_t					mask;
	uint32_t					mask_a;

	mask = _get_mode_support_mask(channel);
	mask_a = (mask & ((0x1 << THERMOSTAT_MODE_FURNACE)|(0x1 << THERMOSTAT_MODE_DRY)|(0x1 << THERMOSTAT_MODE_MOIST)|(0x1 << THERMOSTAT_MODE_AUTO_CHANGEOVER)|(0x1 << THERMOSTAT_MODE_FULL_POWER)|
	(0x1 << THERMOSTAT_MODE_ENERGY_SAVE_HEATING)|(0x1 << THERMOSTAT_MODE_ENERGY_SAVE_COOLING)|(0x1 << THERMOSTAT_MODE_AWAY_COOLING)|(0x1 << THERMOSTAT_MODE_AWAY_HEATING))) >> 0x4;
	mask_a = mask_a | (mask & ((0x1 << THERMOSTAT_MODE_HEAT)|(0x1 << THERMOSTAT_MODE_COOL)));
	return (mask_a);
}

static uint32_t _get_termostat_mode_support_mask(uint8_t channel)
{
	uint32_t					mask;

	mask = _get_mode_support_mask(channel);
	if ((mask & ((0x1 << THERMOSTAT_MODE_AWAY_HEATING) | (0x1 << THERMOSTAT_MODE_AWAY_COOLING))) != 0x0)
		mask = (mask & (~((0x1 << THERMOSTAT_MODE_AWAY_HEATING) | (0x1 << THERMOSTAT_MODE_AWAY_COOLING)))) | (0x1 << THERMOSTAT_MODE_AWAY_HEATING);
	return (mask);
}

static bool _termostat_mode_is_valid(uint8_t channel, uint8_t componentId)
{
	uint32_t									support_mode_mask;

	support_mode_mask = _get_termostat_mode_support_mask(channel);
	if ((support_mode_mask & (0x1 << componentId)) != 0x0)
		return (true);
	return (false);
}

static int _supported_report_mode(uint8_t channel, ZUNOCommandPacketReport_t *frame_report) {//Processed to get the value of the thermostatmode components
	ZwThermostatModeSupportedReportFrame_t		*report;
	uint32_t									support_mode_mask;
	uint8_t										len;

	support_mode_mask = _get_termostat_mode_support_mask(channel);
	report = (ZwThermostatModeSupportedReportFrame_t *)frame_report->info.packet.cmd;
	len = ((((sizeof(support_mode_mask) * 0x8) - __builtin_clz(support_mode_mask)) >> 0x3) + 0x1);
	// lp->byte2.cmdClass = COMMAND_CLASS_THERMOSTAT_MODE; set in - fillOutgoingPacket
	// lp->byte2.cmd = THERMOSTAT_MODE_SUPPORTED_REPORT; set in - fillOutgoingPacket
	memcpy(&report->bitMask[0x0], &support_mode_mask, len);
	frame_report->info.packet.len = sizeof(report[0x0]) + len;
	return (ZUNO_COMMAND_ANSWERED);
}

static const uint8_t _termostat_mode_basic_null[] = {THERMOSTAT_MODE_OFF, THERMOSTAT_MODE_ENERGY_SAVE_HEATING, THERMOSTAT_MODE_ENERGY_SAVE_COOLING, THERMOSTAT_MODE_AWAY_HEATING};
static const uint8_t _termostat_mode_basic[] = {THERMOSTAT_MODE_HEAT, THERMOSTAT_MODE_COOL};

static int8_t _termostat_mode_basic_set(const uint8_t *array, size_t lenght, uint32_t support_mode_mask) {
	size_t					i;

	i = 0x0;
	while (i < lenght)
	{
		if ((support_mode_mask & (0x1 << array[i])) != 0x0)
			return (array[i]);
		i++;
	}
	return (-1);
}

static uint8_t __zuno_CCThermostatModeTobasicSet_any(uint32_t support_mode_mask, int8_t id_cmp, uint8_t id_default) {
	int8_t					id_find;

	id_find = 0x0;
	while (support_mode_mask != 0x0) {
		if ((support_mode_mask & 0x1) != 0x0) {
			if (id_cmp != id_find)
				return (id_find);
		}
		support_mode_mask = support_mode_mask >> 0x1;
		id_find++;
	}
	return (id_default);
}

static uint8_t __zuno_CCThermostatModeTobasicSet_null(uint32_t support_mode_mask) {
	int8_t					id_null;
	int8_t					id_ff;

	if ((id_null = _termostat_mode_basic_set(&_termostat_mode_basic_null[0x0], (sizeof(_termostat_mode_basic_null) / sizeof(_termostat_mode_basic_null[0x0])), support_mode_mask)) >= 0x0)
		return (id_null);
	id_ff = _termostat_mode_basic_set(&_termostat_mode_basic[0x0], (sizeof(_termostat_mode_basic) / sizeof(_termostat_mode_basic[0x0])), support_mode_mask);
	return (__zuno_CCThermostatModeTobasicSet_any(support_mode_mask, id_ff, _termostat_mode_basic_null[0x0]));
}

static uint8_t __zuno_CCThermostatModeTobasicSet_ff(uint32_t support_mode_mask) {
	int8_t					id_null;
	int8_t					id_ff;

	if ((id_ff = _termostat_mode_basic_set(&_termostat_mode_basic[0x0], (sizeof(_termostat_mode_basic) / sizeof(_termostat_mode_basic[0x0])), support_mode_mask)) >= 0x0)
		return (id_ff);
	id_null = __zuno_CCThermostatModeTobasicSet_null(support_mode_mask);
	return (__zuno_CCThermostatModeTobasicSet_any(support_mode_mask, id_null, _termostat_mode_basic[0x0]));
}

uint8_t __zuno_CCThermostatModeTobasicSet(uint8_t channel, uint8_t value) {
	uint32_t				support_mode_mask;

	support_mode_mask = _get_termostat_mode_support_mask(channel);
	if (value == 0x00)
		return (__zuno_CCThermostatModeTobasicSet_null(support_mode_mask));
	return (__zuno_CCThermostatModeTobasicSet_ff(support_mode_mask));
}

uint8_t __zuno_CCThermostatModeTobasicGet(size_t channel) {
	uint8_t				value;
	uint32_t			support_mode_mask;

	value = zuno_universalGetter1P(channel);
	support_mode_mask = _get_termostat_mode_support_mask(channel);
	if (__zuno_CCThermostatModeTobasicSet_null(support_mode_mask) == value)
		return (0x0);
	if (__zuno_CCThermostatModeTobasicSet_ff(support_mode_mask) == value)
		return (0xFF);
	return (0xFE);
}

static int _set_mode(size_t channel, const ZwThermostatModeSetFrame_t *cmd) {
	uint8_t										componentId;

	componentId = cmd->v2.level & THERMOSTAT_MASK_4_BIT;
	if (_termostat_mode_is_valid(channel, componentId) == false)
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
	ZwThermostatSetpointSupportedReportFrame_t		*report;
	uint32_t										support_mode_mask;
	uint8_t											len;

	support_mode_mask = _get_termostat_set_point_support_mask_interpretation_a(channel);
	report = (ZwThermostatSetpointSupportedReportFrame_t *)frame_report->info.packet.cmd;
	// lp->byte2.cmdClass = COMMAND_CLASS_THERMOSTAT_SETPOINT; set in - fillOutgoingPacket
	// lp->byte2.cmd = THERMOSTAT_SETPOINT_SUPPORTED_REPORT; set in - fillOutgoingPacket
	len = ((((sizeof(support_mode_mask) * 0x8) - __builtin_clz(support_mode_mask)) >> 0x3) + 0x1);
	memcpy(&report->bitMask[0x0], &support_mode_mask, len);
	frame_report->info.packet.len = sizeof(report[0x0]) + len;
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
	if (_get_termostat_set_point_is_valid(channel, componentId) == true) {
		report->level = componentId;
		report->level2 = THERMOSTAT_SETPOINT_PARAMETR(THERMOSTAT_SETPOINT_SIZE, THERMOSTAT_SETPOINT_SCALE(channel), THERMOSTAT_SETPOINT_PRECISION);
		out = zuno_universalGetter2P(channel, componentId);
		out = _limit_setpoint(_get_compresed_combi_value(channel), out);
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
	uint16_t									value;

	lp = (ZwThermostatSetpointSetFrame_t *)cmd->cmd;
	if (_get_termostat_set_point_is_valid(channel, (lp->byte1.level & THERMOSTAT_SETPOINT_SET_LEVEL_SETPOINT_TYPE_MASK)) == false)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	if ((lp->byte1.level2 & (THERMOSTAT_SETPOINT_SET_LEVEL2_SIZE_MASK | THERMOSTAT_SETPOINT_SET_LEVEL2_SCALE_MASK)) != (THERMOSTAT_SETPOINT_SIZE | (THERMOSTAT_SETPOINT_SCALE(channel) << THERMOSTAT_SETPOINT_SET_LEVEL2_SCALE_SHIFT)))
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	value = lp->byte2.value2 | (lp->byte2.value1 << (sizeof(value) * 8 / 2));
	value =_limit_setpoint(_get_compresed_combi_value(channel), value);
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
	_get_limits_setpoint(_get_compresed_combi_value(channel), down_limit, up_limit);
	if (_get_termostat_set_point_is_valid(channel, componentId) == true) {
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
