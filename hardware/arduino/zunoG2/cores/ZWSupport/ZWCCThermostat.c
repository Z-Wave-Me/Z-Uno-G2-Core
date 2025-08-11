#include "ArduinoTypes.h"
#include "LLCore.h"
#include "ZUNO_Definitions.h"
#include "zuno_channel_handlers.h"
#include "ZWCCThermostat.h"
#include "ZW_classcmd.h"

#if defined(WITH_CC_THERMOSTAT_FAN_MODE)
static uint32_t __get_fan_mode_mask(uint8_t channel) {
	uint32_t value;

	memcpy(&value, &ZUNO_CFG_CHANNEL(channel).params[0], sizeof(value));
	return ((value & THERMOSTAT_FAN_MODE_MASK) >> THERMOSTAT_FAN_MODE_SHIFT);
}
#endif

#if defined(WITH_CC_THERMOSTAT_MODE) || defined(WITH_CC_THERMOSTAT_SETPOINT) || defined(WITH_CC_THERMOSTAT_OPERATING_STATE) || defined(WITH_CC_THERMOSTAT_FAN_MODE) || defined(WITH_CC_THERMOSTAT_FAN_STATE)
void _zme_memcpy(byte * dst, byte * src, byte count);
typedef struct							ZwThermostatSetpointCapabilitiesReportFrame_s
{
	uint8_t								cmdClass;/* The command class */
	uint8_t								cmd;/* The command */
	uint8_t								properties1;/* masked byte */
	uint8_t								data[];
}										ZwThermostatSetpointCapabilitiesReportFrame_t;

typedef struct __ZwThermostatSetpointLimit_s
{
	int32_t down_limit;
	int32_t up_limit;
	uint8_t size;
	uint8_t precision;
} __ZwThermostatSetpointLimit_t;

# define THERMOSTAT_MASK_4_BIT					0xF//Mode (4 bits)
# define THERMOSTAT_CELSIUS						0x0
# define THERMOSTAT_FAHRENHEIT					0x1

# define THERMOSTAT_SETPOINT_PARAMETR(size, scale, precision)		size | ((scale) << THERMOSTAT_SETPOINT_REPORT_LEVEL2_SCALE_SHIFT) | ((precision) << THERMOSTAT_SETPOINT_REPORT_LEVEL2_PRECISION_SHIFT)

static uint32_t _get_compresed_combi_value(uint8_t channel)
{
	return (ZUNO_CFG_CHANNEL(channel).params[0]);
}

static uint32_t __get_scale(uint8_t channel) {
	return (((ZUNO_CFG_CHANNEL(channel).params[0] & THERMOSTAT_UNITS_FAHRENHEIT) != 0 ? THERMOSTAT_FAHRENHEIT : THERMOSTAT_CELSIUS));
}

static uint8_t __get_size(uint8_t channel) {
	uint32_t value;
	uint8_t out;

	memcpy(&value, &ZUNO_CFG_CHANNEL(channel).params[0], sizeof(value));
	switch ((value & THERMOSTAT_SIZE_MASK) >> THERMOSTAT_SIZE_SHIFT) {
		case (THERMOSTAT_SIZE_ONE_BYTE >> THERMOSTAT_SIZE_SHIFT):
			out = 1;
			break;
		case (THERMOSTAT_SIZE_FOUR_BYTES >> THERMOSTAT_SIZE_SHIFT):
			out = 4;
			break;
		default:
			out = 2;
			break;
	}
	return (out);
}

static uint8_t __get_precision(uint8_t channel) {
	uint32_t value;
	uint8_t out;

	memcpy(&value, &ZUNO_CFG_CHANNEL(channel).params[0], sizeof(value));
	switch ((value & THERMOSTAT_PRECISION_MASK) >> THERMOSTAT_PRECISION_SHIFT) {
		case (THERMOSTAT_PRECISION_ZERO_DECIMALS >> THERMOSTAT_PRECISION_SHIFT):
			out = 0;
			break;
		case (THERMOSTAT_PRECISION_TWO_DECIMALS >> THERMOSTAT_PRECISION_SHIFT):
			out = 2;
			break;
		case (THERMOSTAT_PRECISION_THREE_DECIMALS >> THERMOSTAT_PRECISION_SHIFT):
			out = 3;
			break;
		case (THERMOSTAT_PRECISION_FOUR_DECIMALS >> THERMOSTAT_PRECISION_SHIFT):
			out = 4;
			break;
		case (THERMOSTAT_PRECISION_FIVE_DECIMALS >> THERMOSTAT_PRECISION_SHIFT):
			out = 5;
			break;
		case (THERMOSTAT_PRECISION_SIX_DECIMALS >> THERMOSTAT_PRECISION_SHIFT):
			out = 6;
			break;
		case (THERMOSTAT_PRECISION_SEVEN_DECIMALS >> THERMOSTAT_PRECISION_SHIFT):
			out = 7;
			break;
		default:
			out = 1;
			break;
	}
	return (out);
}

static uint32_t __calculation_multi(uint8_t precision) {
	uint32_t multi;

	multi = 1;
	while (precision-- != 0) {
		multi = multi * 10;
	}
	return (multi);
}

static void __get_setpoint_limit(uint8_t channel, __ZwThermostatSetpointLimit_t *limit) {
	uint32_t compressed_value;
	uint32_t multi;
	int32_t down_limit;
	int32_t up_limit;
	uint8_t precision;

	compressed_value = _get_compresed_combi_value(channel);
	precision = __get_precision(channel);
	limit->precision = precision;
	limit->size = __get_size(channel);
	multi = __calculation_multi(precision);
	if (((compressed_value & THERMOSTAT_RANGE_NEG) != 0) && ((compressed_value & THERMOSTAT_RANGE_POS) != 0)) {
		up_limit = 10 * multi;
		down_limit = -10 * multi;
	}
	else if ((compressed_value & THERMOSTAT_RANGE_NEG) != 0 ) {
		up_limit = 0;
		down_limit = -10 * multi;
	}
	else {
		up_limit = 10 * multi;
		down_limit = 0;
	}
	down_limit *= (compressed_value & THERMOSTAT_LIMITS_MASK);
	up_limit *= (compressed_value & THERMOSTAT_LIMITS_MASK);
	limit->down_limit = down_limit;
	limit->up_limit = up_limit;
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
	ZW_THERMOSTAT_MODE_SUPPORTED_REPORT_1BYTE_V3_FRAME *report;
	uint32_t									support_mode_mask;
	uint8_t										len;

	support_mode_mask = _get_termostat_mode_support_mask(channel);
	report = (ZW_THERMOSTAT_MODE_SUPPORTED_REPORT_1BYTE_V3_FRAME *)frame_report->info.packet.cmd;
	len = ((((sizeof(support_mode_mask) * 0x8) - __builtin_clz(support_mode_mask)) >> 0x3) + 0x1);
	// lp->byte2.cmdClass = COMMAND_CLASS_THERMOSTAT_MODE; set in - fillOutgoingPacket
	// lp->byte2.cmd = THERMOSTAT_MODE_SUPPORTED_REPORT; set in - fillOutgoingPacket
	memcpy(&report->bitMask1, &support_mode_mask, len);
	frame_report->info.packet.len = (sizeof(report[0x0]) - sizeof(report->bitMask1)) + len;
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

static int _set_mode(size_t channel, const ZW_THERMOSTAT_MODE_SET_V2_FRAME *cmd) {
	uint8_t										componentId;

	componentId = cmd->level & THERMOSTAT_MASK_4_BIT;
	if (_termostat_mode_is_valid(channel, componentId) == false)
		return (ZUNO_COMMAND_BLOCKED_FAIL);
	zuno_universalSetter1P(channel, componentId);
	zunoSendReport(channel + 1);
	return (ZUNO_COMMAND_PROCESSED);
}

static int _report_mode(uint8_t channel, ZUNOCommandPacket_t *packet) {
	ZW_THERMOSTAT_MODE_REPORT_V2_FRAME *report;

	report = (ZW_THERMOSTAT_MODE_REPORT_V2_FRAME *)&packet->packet.cmd[0x0];
	report->cmdClass = COMMAND_CLASS_THERMOSTAT_MODE;
	report->cmd = THERMOSTAT_MODE_REPORT;
	report->level = zuno_universalGetter1P(channel) & THERMOSTAT_MASK_4_BIT;//Mode (4 bits)
	packet->packet.len = sizeof(report[0]);
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCThermostatModeHandler(uint8_t channel, const ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	int				rs;

	switch(ZW_CMD) {
		case THERMOSTAT_MODE_SET:
			rs = _set_mode(channel, (const ZW_THERMOSTAT_MODE_SET_V2_FRAME *)cmd->cmd);
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
	ZW_THERMOSTAT_SETPOINT_SUPPORTED_REPORT_1BYTE_V3_FRAME *report;
	uint32_t										support_mode_mask;
	uint8_t											len;

	support_mode_mask = _get_termostat_set_point_support_mask_interpretation_a(channel);
	report = (ZW_THERMOSTAT_SETPOINT_SUPPORTED_REPORT_1BYTE_V3_FRAME *)frame_report->info.packet.cmd;
	// lp->byte2.cmdClass = COMMAND_CLASS_THERMOSTAT_SETPOINT; set in - fillOutgoingPacket
	// lp->byte2.cmd = THERMOSTAT_SETPOINT_SUPPORTED_REPORT; set in - fillOutgoingPacket
	len = ((((sizeof(support_mode_mask) * 0x8) - __builtin_clz(support_mode_mask)) >> 0x3) + 0x1);
	memcpy(&report->bitMask1, &support_mode_mask, len);
	frame_report->info.packet.len = (sizeof(report[0x0]) - sizeof(report->bitMask1))+ len;
	return (ZUNO_COMMAND_ANSWERED);
}

static int _setpoint_get(size_t channel, const ZW_THERMOSTAT_SETPOINT_GET_V3_FRAME *cmd, ZUNOCommandPacket_t *packet) {
	ZW_THERMOSTAT_SETPOINT_REPORT_1BYTE_V3_FRAME *report;
	__ZwThermostatSetpointLimit_t limit;
	size_t componentId;
	uint32_t out;
	size_t i;
	
	if (cmd != NULL)
		componentId = cmd->level;
	else
		componentId = zuno_universalGetter1P(channel);
	report = (ZW_THERMOSTAT_SETPOINT_REPORT_1BYTE_V3_FRAME *)&packet->packet.cmd[0x0];
	componentId = componentId & THERMOSTAT_SETPOINT_GET_LEVEL_SETPOINT_TYPE_MASK;//Setpoint Type (4 bits)
	report->cmdClass = COMMAND_CLASS_THERMOSTAT_SETPOINT;
	report->cmd = THERMOSTAT_SETPOINT_REPORT;
	if (_get_termostat_set_point_is_valid(channel, componentId) == true) {
		report->level = componentId;
		__get_setpoint_limit(channel, &limit);
		i = 0;
		report->level2 = THERMOSTAT_SETPOINT_PARAMETR(limit.size, __get_scale(channel), limit.precision);
		out = zuno_universalGetter2P(channel, componentId);
		_zme_memcpy(&report->value1, (byte *)&out, limit.size);
		i = limit.size - 1;
	}
	else {
		report->level = 0x0;
		report->level2 = 0x1;
		report->value1 = 0x0;
		i = 0;
	}
	packet->packet.len = (sizeof(report[0x0])) + i;
	return (ZUNO_COMMAND_ANSWERED);
}

static int _set_setpoint(uint8_t channel, const ZW_THERMOSTAT_SETPOINT_SET_4BYTE_V3_FRAME *cmd) {
	__ZwThermostatSetpointLimit_t limit;
	int32_t value;
	uint32_t multi;
	uint8_t size;
	uint8_t precision;
	uint8_t scale;
	int rs; // to allow returning SUPERVISION_FAIL even on a successful conversion - the spec says that if the Set is not exactly in th correct format, we MAY handle the command but MUST return SUPERVISION_FAIL

	if (_get_termostat_set_point_is_valid(channel, (cmd->level & THERMOSTAT_SETPOINT_SET_LEVEL_SETPOINT_TYPE_MASK)) == false)
		return (ZUNO_COMMAND_BLOCKED_FAIL);
	__get_setpoint_limit(channel, &limit);
	size = (cmd->level2 & THERMOSTAT_SETPOINT_SET_LEVEL2_SIZE_MASK);
	if (size > sizeof(value))
		return (ZUNO_COMMAND_BLOCKED_FAIL);
	if (size != limit.size)
		rs = ZUNO_COMMAND_BLOCKED_FAIL;
	else
		rs = ZUNO_COMMAND_PROCESSED;
	value = 0;
	_zme_memcpy((byte *)&value, (byte *)&cmd->value1, size);
	if ((_get_compresed_combi_value(channel) & THERMOSTAT_RANGE_NEG) != 0) {
		if (size == 1) {
			if ((value & 0x80) != 0)
				value = (int8_t)value;
		}
		else if (size == 2) {
			if ((value & 0x8000) != 0)
				value = (int16_t)value;
		}
	}
	if ((precision = ((cmd->level2 & THERMOSTAT_SETPOINT_SET_LEVEL2_PRECISION_MASK) >> THERMOSTAT_SETPOINT_SET_LEVEL2_PRECISION_SHIFT)) > limit.precision)
	{
		multi = __calculation_multi(precision - limit.precision);
		value = value / multi;
	}
	else
	{
		multi = __calculation_multi(limit.precision - precision);
		value = value * multi;
	}
	if (precision != limit.precision)
		rs = ZUNO_COMMAND_BLOCKED_FAIL;
	if ((scale = ((cmd->level2 & THERMOSTAT_SETPOINT_SET_LEVEL2_SCALE_MASK) >> THERMOSTAT_SETPOINT_SET_LEVEL2_SCALE_SHIFT)) != __get_scale(channel)) {
		rs = ZUNO_COMMAND_BLOCKED_FAIL;
		multi = (32 * __calculation_multi(limit.precision));
		if (scale == THERMOSTAT_FAHRENHEIT)
			value = ((value - multi) * 5 / 9);
		else
			value = value * 9 / 5 + multi;
	}
	if (value > limit.up_limit)
		return (ZUNO_COMMAND_BLOCKED_FAIL);
	if (value < limit.down_limit)
		return (ZUNO_COMMAND_BLOCKED_FAIL);
	zuno_universalSetter2P(channel, cmd->level & THERMOSTAT_SETPOINT_SET_LEVEL_SETPOINT_TYPE_MASK, value);
	return (rs);
}

static int _setpoint_capabilities_get(size_t channel, const ZW_THERMOSTAT_SETPOINT_CAPABILITIES_GET_V3_FRAME *cmd, ZUNOCommandPacketReport_t *frame_report) {
	ZwThermostatSetpointCapabilitiesReportFrame_t *report;
	__ZwThermostatSetpointLimit_t limit;
	uint8_t properties2;
	size_t i;

	report = (ZwThermostatSetpointCapabilitiesReportFrame_t *)frame_report->info.packet.cmd;
	// report->cmdClass = COMMAND_CLASS_THERMOSTAT_SETPOINT; set in - fillOutgoingPacket
	// report->cmd = THERMOSTAT_SETPOINT_CAPABILITIES_REPORT; set in - fillOutgoingPacket
	report->properties1 = cmd->properties1 & THERMOSTAT_SETPOINT_GET_LEVEL_SETPOINT_TYPE_MASK_V3;
	if (_get_termostat_set_point_is_valid(channel, report->properties1) == true) {
		__get_setpoint_limit(channel, &limit);
		properties2 = THERMOSTAT_SETPOINT_PARAMETR(limit.size, __get_scale(channel), limit.precision);
		i = 0;
		report->data[i++] = properties2;
		_zme_memcpy(&report->data[i], (byte *)&limit.down_limit, limit.size);
		i = i + limit.size;
		report->data[i++] = properties2;
		_zme_memcpy(&report->data[i], (byte *)&limit.up_limit, limit.size);
		i = i + limit.size;
	}
	else {
		report->properties1 = 0;
		report->data[0] = 1;
		report->data[1] = 0;
		report->data[2] = 1;
		report->data[3] = 0;
		i = 4;
	}
	frame_report->info.packet.len = sizeof(ZwThermostatSetpointCapabilitiesReportFrame_t) + i;
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCThermostatSetPointHandler(uint8_t channel, const ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	int				rs;

	switch(ZW_CMD) {
		case THERMOSTAT_SETPOINT_SET:
			rs = _set_setpoint(channel, (const ZW_THERMOSTAT_SETPOINT_SET_4BYTE_V3_FRAME *)cmd->cmd);
			zunoSendReport(channel + 1);
			break ;
		case THERMOSTAT_SETPOINT_GET:
			_zunoMarkChannelRequested(channel);
			rs = _setpoint_get(channel, (const ZW_THERMOSTAT_SETPOINT_GET_V3_FRAME *)cmd->cmd, &frame_report->info);
			break ;
		case THERMOSTAT_SETPOINT_SUPPORTED_GET:
			rs = _supported_report_setpoint(channel, frame_report);
			break ;
		case THERMOSTAT_SETPOINT_CAPABILITIES_GET_V3:
			rs = _setpoint_capabilities_get(channel, (const ZW_THERMOSTAT_SETPOINT_CAPABILITIES_GET_V3_FRAME *)cmd->cmd, frame_report);
			break ;
		default:
			rs = ZUNO_COMMAND_BLOCKED_NO_SUPPORT;
			break ;
	}
	return (rs);
}
#endif

#if defined(WITH_CC_THERMOSTAT_MODE)
ssize_t zuno_CCThermostatModeAssociationGroupCommand(_ZwAssociationGroupCommand_t *gpr_info, size_t gpr_info_max) {
	if (gpr_info_max < 1)
		return (-1);
	gpr_info[0].cmdClass = COMMAND_CLASS_THERMOSTAT_MODE;
	gpr_info[0].cmd = THERMOSTAT_MODE_REPORT;
	return (1);
}

bool zuno_CCThermostatModeIsBlockMultiBroadcast(size_t cmd) {
	if (cmd == THERMOSTAT_MODE_SET)
		return (false);
	return (true);
}

#endif // WITH_CC_THERMOSTAT_MODE

#if defined(WITH_CC_THERMOSTAT_SETPOINT)
ssize_t zuno_CCThermostatSetPointAssociationGroupCommand(_ZwAssociationGroupCommand_t *gpr_info, size_t gpr_info_max) {
	if (gpr_info_max < 1)
		return (-1);
	gpr_info[0].cmdClass = COMMAND_CLASS_THERMOSTAT_SETPOINT;
	gpr_info[0].cmd = THERMOSTAT_SETPOINT_REPORT;
	return (1);
}

bool zuno_CCThermostatSetPointIsBlockMultiBroadcast(size_t cmd) {
	if (cmd == THERMOSTAT_SETPOINT_SET)
		return (false);
	return (true);
}
#endif // WITH_CC_THERMOSTAT_SETPOINT


#if defined(WITH_CC_THERMOSTAT_OPERATING_STATE)

__WEAK uint8_t zuno_CCThermostatOperationState(uint8_t channel) {
	return (THERMOSTAT_OPERATING_STATE_IDLE);
	(void)channel;
}

static int _operating_state_report(uint8_t channel, ZUNOCommandPacket_t *packet) {
	ZW_THERMOSTAT_OPERATING_STATE_REPORT_V2_FRAME *report;

	report = (ZW_THERMOSTAT_OPERATING_STATE_REPORT_V2_FRAME *)&packet->packet.cmd[0x0];
	report->cmdClass = COMMAND_CLASS_THERMOSTAT_OPERATING_STATE;
	report->cmd = THERMOSTAT_OPERATING_STATE_REPORT;
	report->properties1 = zuno_CCThermostatOperationState(channel);
	packet->packet.len = (sizeof(report[0]));
	return (ZUNO_COMMAND_ANSWERED);
}


static int _operating_state_logging_supported_report(ZUNOCommandPacketReport_t *frame_report) {
	ZW_THERMOSTAT_OPERATING_LOGGING_SUPPORTED_REPORT_1BYTE_V2_FRAME *report;

	report = (ZW_THERMOSTAT_OPERATING_LOGGING_SUPPORTED_REPORT_1BYTE_V2_FRAME *)frame_report->info.packet.cmd;
	// report->cmdClass = COMMAND_CLASS_THERMOSTAT_OPERATING_STATE; set in - fillOutgoingPacket
	report->cmd = THERMOSTAT_OPERATING_LOGGING_SUPPORTED_REPORT_V2;
	report->bitMask1 = 0;
	frame_report->info.packet.len = (sizeof(report[0]));
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCThermostatOperationStateHandler(uint8_t channel, const ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	int				rs;

	switch(ZW_CMD) {
		case THERMOSTAT_OPERATING_STATE_GET:
			rs = _operating_state_report(channel, &frame_report->info);
			break ;
		case THERMOSTAT_OPERATING_STATE_LOGGING_SUPPORTED_GET_V2:
			rs = _operating_state_logging_supported_report(frame_report);
			break ;
		default:
			rs = ZUNO_COMMAND_BLOCKED_NO_SUPPORT;
			break ;
	}
	return (rs);
	(void)cmd;
}

ssize_t zuno_CCThermostatOperationStateAssociationGroupCommand(_ZwAssociationGroupCommand_t *gpr_info, size_t gpr_info_max) {
	if (gpr_info_max < 1)
		return (-1);
	gpr_info[0].cmdClass = COMMAND_CLASS_THERMOSTAT_OPERATING_STATE;
	gpr_info[0].cmd = THERMOSTAT_OPERATING_STATE_REPORT;
	return (1);
}

bool zuno_CCThermostatOperationStateIsBlockMultiBroadcast(size_t cmd) {
	return (true);
	(void)cmd;
}
#endif // WITH_CC_THERMOSTAT_OPERATING_STATE

#if defined(WITH_CC_THERMOSTAT_FAN_MODE)

__WEAK uint8_t zuno_CCThermostatFanModeGet(uint8_t channel) {
	return (THERMOSTAT_FAN_MODE_AUTO_LOW);
	(void)channel;
}

__WEAK bool zuno_CCThermostatFanModeIsOff(uint8_t channel) {
	return (false);
	(void)channel;
}

__WEAK void zuno_CCThermostatFanModeSet(uint8_t channel, uint8_t mode, bool off) {
	(void)channel;
	(void)mode;
	(void)off;
}

static int __fan_mode_get(uint8_t channel, ZUNOCommandPacket_t *packet) {
	ZW_THERMOSTAT_FAN_MODE_REPORT_V5_FRAME *report;

	report = (ZW_THERMOSTAT_FAN_MODE_REPORT_V5_FRAME *)&packet->packet.cmd[0x0];
	report->cmdClass = COMMAND_CLASS_THERMOSTAT_FAN_MODE;
	report->cmd = THERMOSTAT_FAN_MODE_REPORT;
	report->properties1 = zuno_CCThermostatFanModeGet(channel);
	if (zuno_CCThermostatFanModeIsOff(channel) == true)
		report->properties1 = report->properties1 | THERMOSTAT_FAN_MODE_REPORT_PROPERTIES1_OFF_BIT_MASK_V4;
	packet->packet.len = (sizeof(report[0]));
	return (ZUNO_COMMAND_ANSWERED);
}

static int __fan_mode_set(size_t channel, const ZW_THERMOSTAT_FAN_MODE_SET_V5_FRAME *cmd) {
	uint8_t										fan_mode;

	fan_mode = cmd->properties1 & THERMOSTAT_FAN_MODE_REPORT_PROPERTIES1_FAN_MODE_MASK_V5;
	if ((__get_fan_mode_mask(channel) & (1 << fan_mode)) == 0)
		return (ZUNO_COMMAND_BLOCKED_FAIL);
	zuno_CCThermostatFanModeSet(channel, fan_mode, ((cmd->properties1 & THERMOSTAT_FAN_MODE_REPORT_PROPERTIES1_OFF_BIT_MASK_V5) != 0)? true:false);
	zunoSendReport(channel + 1);
	return (ZUNO_COMMAND_PROCESSED);
}

static int __fan_mode_supported_get(uint8_t channel, ZUNOCommandPacketReport_t *frame_report) {
	ZW_THERMOSTAT_FAN_MODE_SUPPORTED_REPORT_1BYTE_V5_FRAME *report;
	uint32_t										support_mode_mask;
	uint8_t											len;

	support_mode_mask = __get_fan_mode_mask(channel);
	report = (ZW_THERMOSTAT_FAN_MODE_SUPPORTED_REPORT_1BYTE_V5_FRAME *)frame_report->info.packet.cmd;
	// lp->byte2.cmdClass = COMMAND_CLASS_THERMOSTAT_FAN_MODE; set in - fillOutgoingPacket
	// lp->byte2.cmd = THERMOSTAT_FAN_MODE_SUPPORTED_REPORT; set in - fillOutgoingPacket
	len = ((((sizeof(support_mode_mask) * 0x8) - __builtin_clz(support_mode_mask)) >> 0x3) + 0x1);
	memcpy(&report->bitMask1, &support_mode_mask, len);
	frame_report->info.packet.len = (sizeof(report[0x0]) - sizeof(report->bitMask1))+ len;
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCThermostatFanModeHandler(uint8_t channel, const ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	int				rs;

	switch(ZW_CMD) {
		case THERMOSTAT_FAN_MODE_GET_V5:
			rs = __fan_mode_get(channel, &frame_report->info);
			break ;
		case THERMOSTAT_FAN_MODE_SET_V5:
			rs = __fan_mode_set(channel, (const ZW_THERMOSTAT_FAN_MODE_SET_V5_FRAME *)cmd->cmd);
			break ;
		case THERMOSTAT_FAN_MODE_SUPPORTED_GET:
			rs = __fan_mode_supported_get(channel, frame_report);
			break ;
		default:
			rs = ZUNO_COMMAND_BLOCKED_NO_SUPPORT;
			break ;
	}
	return (rs);
}

bool zuno_CCThermostatFanModeIsBlockMultiBroadcast(size_t cmd) {
	if (cmd == THERMOSTAT_FAN_MODE_GET)
		return (true);
	if (cmd == THERMOSTAT_FAN_MODE_SUPPORTED_GET)
		return (true);
	return (false);
}

ssize_t zuno_CCThermostatFanModeAssociationGroupCommand(_ZwAssociationGroupCommand_t *gpr_info, size_t gpr_info_max)
{
	if (gpr_info_max < 1)
		return (-1);
	gpr_info[0].cmdClass = COMMAND_CLASS_THERMOSTAT_FAN_MODE;
	gpr_info[0].cmd = THERMOSTAT_FAN_MODE_REPORT;
	return (1);
}

#endif// WITH_CC_THERMOSTAT_FAN_MODE

#if defined(WITH_CC_THERMOSTAT_FAN_STATE)

__WEAK uint8_t zuno_CCThermostatFanState(uint8_t channel) {
	return (THERMOSTAT_FAN_STATE_IDLE);
	(void)channel;
}

static int __fan_state_get(uint8_t channel, ZUNOCommandPacket_t *packet) {
	ZW_THERMOSTAT_FAN_STATE_REPORT_V2_FRAME *report;

	report = (ZW_THERMOSTAT_FAN_STATE_REPORT_V2_FRAME *)&packet->packet.cmd[0x0];
	report->cmdClass = COMMAND_CLASS_THERMOSTAT_FAN_STATE;
	report->cmd = THERMOSTAT_FAN_STATE_REPORT_V2;
	report->level = zuno_CCThermostatFanState(channel);
	packet->packet.len = (sizeof(report[0]));
	return (ZUNO_COMMAND_ANSWERED);
}


int zuno_CCThermostatFanStateHandler(uint8_t channel, const ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	int				rs;

	switch(ZW_CMD) {
		case THERMOSTAT_FAN_STATE_GET_V2:
			rs = __fan_state_get(channel, &frame_report->info);
			break ;
		default:
			rs = ZUNO_COMMAND_BLOCKED_NO_SUPPORT;
			break ;
	}
	return (rs);
	(void)cmd;
}

ssize_t zuno_CCThermostatFanStateAssociationGroupCommand(_ZwAssociationGroupCommand_t *gpr_info, size_t gpr_info_max) {
	if (gpr_info_max < 1)
		return (-1);
	gpr_info[0].cmdClass = COMMAND_CLASS_THERMOSTAT_FAN_STATE;
	gpr_info[0].cmd = THERMOSTAT_FAN_STATE_REPORT_V2;
	return (1);
}

bool zuno_CCThermostatFanStateIsBlockMultiBroadcast(size_t cmd) {
	return (true);
	(void)cmd;
}

#endif// WITH_CC_THERMOSTAT_FAN_STATE

#if defined(WITH_CC_THERMOSTAT_MODE) || defined(WITH_CC_THERMOSTAT_SETPOINT) || defined(WITH_CC_THERMOSTAT_OPERATING_STATE) || defined(WITH_CC_THERMOSTAT_FAN_MODE) || defined(WITH_CC_THERMOSTAT_FAN_STATE)
bool zuno_CCThermostatCompareChanneltypeCC(size_t cmdClass) {
	if(cmdClass == COMMAND_CLASS_BASIC)
		return (true);
#if defined(WITH_CC_THERMOSTAT_MODE)
	if(cmdClass == COMMAND_CLASS_THERMOSTAT_MODE)
		return (true);
#endif
#if defined(WITH_CC_THERMOSTAT_SETPOINT)
	if(cmdClass == COMMAND_CLASS_THERMOSTAT_SETPOINT)
		return (true);
#endif
#if defined(WITH_CC_THERMOSTAT_OPERATING_STATE)
	if(cmdClass == COMMAND_CLASS_THERMOSTAT_OPERATING_STATE)
		return (true);
#endif
#if defined(WITH_CC_THERMOSTAT_FAN_MODE)
	if(cmdClass == COMMAND_CLASS_THERMOSTAT_FAN_MODE)
		return (true);
#endif
#if defined(WITH_CC_THERMOSTAT_FAN_STATE)
	if(cmdClass == COMMAND_CLASS_THERMOSTAT_FAN_STATE)
		return (true);
#endif
	return (false);
}

int zuno_CCThermostatReport(byte channel, ZUNOCommandPacket_t *packet) {
	int				rs;

	#ifdef WITH_CC_THERMOSTAT_MODE
	rs = _report_mode(channel, packet);
	if (rs == ZUNO_COMMAND_ANSWERED) {
		zunoSendZWPacket(packet);
	}
	#endif
	#ifdef WITH_CC_THERMOSTAT_OPERATING_STATE
	rs = _operating_state_report(channel, packet);
	if (rs == ZUNO_COMMAND_ANSWERED) {
		zunoSendZWPacket(packet);
	}
	#endif
	#ifdef WITH_CC_THERMOSTAT_FAN_MODE
	rs = __fan_mode_get(channel, packet);
	if (rs == ZUNO_COMMAND_ANSWERED) {
		zunoSendZWPacket(packet);
	}
	#endif
	#ifdef WITH_CC_THERMOSTAT_FAN_STATE
	rs = __fan_state_get(channel, packet);
	if (rs == ZUNO_COMMAND_ANSWERED) {
		zunoSendZWPacket(packet);
	}
	#endif
	#ifdef WITH_CC_THERMOSTAT_SETPOINT
	rs = _setpoint_get(channel, NULL, packet);
	if (rs == ZUNO_COMMAND_ANSWERED) {
		zunoSendZWPacket(packet);
	}
	#endif
	return (ZUNO_COMMAND_PROCESSED);
}

#endif// defined(WITH_CC_THERMOSTAT_MODE) || defined(WITH_CC_THERMOSTAT_SETPOINT) || defined(WITH_CC_THERMOSTAT_OPERATING_STATE) || defined(WITH_CC_THERMOSTAT_FAN_MODE) || defined(WITH_CC_THERMOSTAT_FAN_STATE)