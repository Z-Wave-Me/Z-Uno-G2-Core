#include "Arduino.h"
#include "ZWCCConfiguration.h"

typedef uint32_t CONFIGPARAM_MAX_SIZE;

#define CONFIGPARAM_MIN_PARAM			0x40
#define CONFIGPARAM_MAX_PARAM			0x60
#define CONFIGPARAM_EEPROM_ADDR(param)	(((param - CONFIGPARAM_MIN_PARAM) * sizeof(CONFIGPARAM_MAX_SIZE)) + EEPROM_CONFIGURATION_ADDR)

#define CONFIGPARAM_STANDART_NAME			"Eeprom parameter "

static const ZunoCFGParameter_t _param =
{
	.name = 0,
	.info = 0,
	.minValue = -2147483648,
	.maxValue = 2147483647,
	.defaultValue = -1,
	.format = ZunoCFGParameterFormatSigned,
	.size = ZunoCFGParameterSize32bit
};

typedef enum				ZunoCFGTypeHandler_e
{
	ZunoCFGTypeHandlerInfo,
	ZunoCFGTypeHandlerName
}							ZunoCFGTypeHandler_t;

const ZunoCFGParameter_t *zunoCFGParameter(size_t param) __attribute__ ((weak));
const ZunoCFGParameter_t *zunoCFGParameter(size_t param) {
	(void)param;
	return (ZUNO_CFG_PARAMETER_UNKNOWN);
}

static int _configuration_get(uint8_t param) {
	ZwConfigurationReportFrame_t			*lp;
	uint32_t								value;

	if (param < CONFIGPARAM_MIN_PARAM || param > CONFIGPARAM_MAX_PARAM)// Check if this is not user data
		return (ZUNO_UNKNOWN_CMD);
	value = zunoLoadCFGParam(param);
	lp = (ZwConfigurationReportFrame_t *)&CMD_REPLY_CC;
	// lp->byte4.cmdClass = COMMAND_CLASS_CONFIGURATION; set in -  fillOutgoingPacket
	// lp->byte4.cmd = CONFIGURATION_REPORT; set in - fillOutgoingPacket
	lp->byte4.parameterNumber = param;
	lp->byte4.level = sizeof(uint32_t);
	lp->byte4.configurationValue1 = (uint8_t)(value >> 24);
	lp->byte4.configurationValue2 = (uint8_t)(value >> 16);
	lp->byte4.configurationValue3 = (uint8_t)(value >> 8);
	lp->byte4.configurationValue4 = (uint8_t)(value);
	CMD_REPLY_LEN = sizeof(lp->byte4);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _configuration_set(ZUNOCommandPacket_t *cmd) {
	ZwConfigurationSetFrame_t			*lp;
	uint8_t								size;
	uint8_t								param;
	uint32_t							value;
	const ZunoCFGParameter_t			*cfg;

	lp = (ZwConfigurationSetFrame_t *)cmd->cmd;
	param = lp->byte1.parameterNumber;
	if (param < CONFIGPARAM_MIN_PARAM || param > CONFIGPARAM_MAX_PARAM)// Check if this is not user data
		return (ZUNO_UNKNOWN_CMD);
	if (((size = lp->byte1.level) & CONFIGURATION_SET_LEVEL_DEFAULT_BIT_MASK) != 0){// Check whether you want to restore the default value
		if ((cfg = zunoCFGParameter(param)) == ZUNO_CFG_PARAMETER_UNKNOWN)
			value = (uint32_t)-1;
		else
			value = (uint32_t)cfg->defaultValue;
	}
	else {
		value = lp->byte4.configurationValue1 << 24;
		value = value | (lp->byte4.configurationValue2 << 16);
		value = value | (lp->byte4.configurationValue3 << 8);
		value = value | lp->byte4.configurationValue4;
	}
	size = size & 0x7;
	switch (size) {
		case 2:
			value = value & 0xFFFF;
			break;
		case 1:
			value = value & 0xFF;
			break ;
		default:
			break ;
	}
	zunoSaveCFGParam(param, (CONFIGPARAM_MAX_SIZE)value);
	zunoSysHandlerCall(ZUNO_HANDLER_ZW_CFG, 0, param, value);
	return (ZUNO_COMMAND_PROCESSED);
}

static int _configuration_properties_get(ZwConfigurationPropertiesGetFrame_t *cmd) {
	size_t												parameter;
	ZwConfigurationPropertiesPeportFrame_t				*report;
	size_t												parameterNumber1;
	size_t												parameterNumber2;
	size_t												properties1;
	size_t												size;
	ZwConfigurationPropertiesPeportByte4FrameV4End_t	*end;
	const ZunoCFGParameter_t							*cfg;

	report = (ZwConfigurationPropertiesPeportFrame_t *)&CMD_REPLY_CC;
	// report->v4.byte4.cmdClass = COMMAND_CLASS_CONFIGURATION; set in - fillOutgoingPacket
	// report->v4.byte4.cmd = CONFIGURATION_PROPERTIES_REPORT; set in - fillOutgoingPacket
	parameterNumber1 = cmd->parameterNumber1;
	parameterNumber2 = cmd->parameterNumber2;
	report->v4.byte4.parameterNumber1 = parameterNumber1;
	report->v4.byte4.parameterNumber2 = parameterNumber2;
	parameter = (parameterNumber1 << 8) | parameterNumber2;
	if ((cfg = zunoCFGParameter(parameter)) == ZUNO_CFG_PARAMETER_UNKNOWN) {
		properties1 = 0;
		end = (ZwConfigurationPropertiesPeportByte4FrameV4End_t *)&report->v4.byte4.minValue1;
	}
	else {
		if (cfg == ZUNO_CFG_PARAMETER_DEFAULT)
			cfg = &_param;
		size = cfg->size;
		_zme_memcpy(&report->v4.byte4.minValue1, (uint8_t *)&cfg->minValue, size);
		_zme_memcpy(&report->v4.byte4.maxValue1, (uint8_t *)&cfg->maxValue, size);
		_zme_memcpy(&report->v4.byte4.defaultValue1, (uint8_t *)&cfg->defaultValue, size);
		properties1 = (cfg->format << CONFIGURATION_PROPERTIES_REPORT_PROPERTIES1_FORMAT_SHIFT) | size;
		end = (ZwConfigurationPropertiesPeportByte4FrameV4End_t *)((size_t)&report->v4.byte4.minValue1 + size * 3);
	}
	report->v4.byte4.properties1 = properties1;
	if (parameter < CONFIGPARAM_MIN_PARAM)
		parameter = CONFIGPARAM_MIN_PARAM;
	else
		parameter++;
	if (zunoCFGParameter(parameter) == ZUNO_CFG_PARAMETER_UNKNOWN)
		parameter = 0;
	end->nextParameterNumber1 = 0;
	end->nextParameterNumber2 = parameter;
	end->properties2 = CONFIGURATION_PROPERTIES_REPORT_PROPERTIES2_NO_BULK_SUPPORT_BIT_MASK;
	CMD_REPLY_LEN = sizeof(ZwConfigurationPropertiesPeportByte4FrameV4End_t) + ((size_t)end - (size_t)report);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _configuration_name_get(ZwConfigurationNameGetFrame_t *cmd, ZunoCFGTypeHandler_t type) {
	size_t												parameter;
	ZwConfigurationNameReportFrame_t					*report;
	size_t												parameterNumber1;
	size_t												parameterNumber2;
	size_t												len;
	const char											*str;
	const ZunoCFGParameter_t							*cfg;

	report = (ZwConfigurationNameReportFrame_t *)&CMD_REPLY_CC;
	// report->cmdClass = COMMAND_CLASS_CONFIGURATION; set in - fillOutgoingPacket
	// report->cmd = CONFIGURATION_NAME_REPORT; set in - fillOutgoingPacket
	parameterNumber1 = cmd->parameterNumber1;
	parameterNumber2 = cmd->parameterNumber2;
	report->parameterNumber1 = parameterNumber1;
	report->parameterNumber2 = parameterNumber2;
	parameter = (parameterNumber1 << 8) | parameterNumber2;
	if ((cfg = zunoCFGParameter(parameter)) == ZUNO_CFG_PARAMETER_UNKNOWN)
		len = sizeof(ZwConfigurationNameReportFrame_t);
	else if (cfg == ZUNO_CFG_PARAMETER_DEFAULT) {
		report->name[(sizeof(CONFIGPARAM_STANDART_NAME) - 1)] = parameter / 10 + 0x30;
		report->name[(sizeof(CONFIGPARAM_STANDART_NAME) - 1) + 1] = parameter % 10 + 0x30;
		memcpy(&report->name[0], CONFIGPARAM_STANDART_NAME, sizeof(CONFIGPARAM_STANDART_NAME) - 1);
		len = sizeof(CONFIGPARAM_STANDART_NAME) - 1 + sizeof(ZwConfigurationNameReportFrame_t) + 2;//+2 fot numbers
	}
	else {
		report->reportsToFollow = 1;
		str = (type == ZunoCFGTypeHandlerInfo) ? cfg->info : cfg->name;
		len = strlen(str);
		while (len > (ZUNO_COMMAND_PACKET_CMD_LEN_MAX_OUT - sizeof(ZwConfigurationNameReportFrame_t))) {
			len = len - (ZUNO_COMMAND_PACKET_CMD_LEN_MAX_OUT - sizeof(ZwConfigurationNameReportFrame_t));
			memcpy(&report->name[0], str, (ZUNO_COMMAND_PACKET_CMD_LEN_MAX_OUT - sizeof(ZwConfigurationNameReportFrame_t)));
			str = str + (ZUNO_COMMAND_PACKET_CMD_LEN_MAX_OUT - sizeof(ZwConfigurationNameReportFrame_t));
			CMD_REPLY_LEN = ZUNO_COMMAND_PACKET_CMD_LEN_MAX_OUT;
			zunoSendZWPackage(&g_outgoing_main_packet);
		}
		memcpy(&report->name[0], str, len);
		len = len + sizeof(ZwConfigurationNameReportFrame_t);
	}
	report->reportsToFollow = 0;
	CMD_REPLY_LEN = len;
	return (ZUNO_COMMAND_ANSWERED);
}

static int _configuration_info_get(ZwConfigurationInfoGetFrame_t *cmd) {
	CMD_REPLY_CMD = CONFIGURATION_INFO_REPORT;
	return (_configuration_name_get((ZwConfigurationNameGetFrame_t *)cmd, ZunoCFGTypeHandlerInfo));
}

static int _configuration_default_reset(void) {
	size_t												param;
	const ZunoCFGParameter_t							*cfg;
	uint32_t											value;

	param = CONFIGPARAM_MIN_PARAM;
	while (param <= CONFIGPARAM_MAX_PARAM)
	{
		if ((cfg = zunoCFGParameter(param)) != ZUNO_CFG_PARAMETER_UNKNOWN) {
			value = (uint32_t)cfg->defaultValue;
			zunoSaveCFGParam(param, value);
		}
		param++;
	}
	return (ZUNO_COMMAND_PROCESSED);
}

// static int _configuration_builk_get(const ZwConfigurationBuilkGetFrame_t *paket) {
// 	size_t										parameterOffset;
// 	size_t										param;
// 	size_t										numberOfParameters;
// 	ZwConfigurationBuilkReportFrame_t			*lp;
// 	const ZunoCFGParameter_t					*cfg;
// 	uint32_t									value;
// 	size_t										properties1;

// 	parameterOffset = paket->parameterOffset1 << 0x8 | paket->parameterOffset2;
// 	param = CONFIGPARAM_MIN_PARAM + parameterOffset;
// 	if (param < CONFIGPARAM_MIN_PARAM || param > CONFIGPARAM_MAX_PARAM)// Check if this is not user data
// 		return (ZUNO_UNKNOWN_CMD);
// 	numberOfParameters = paket->numberOfParameters;
// 	lp = (ZwConfigurationBuilkReportFrame_t *)&CMD_REPLY_CC;
// 	// lp->cmdClass = COMMAND_CLASS_CONFIGURATION; set in -  fillOutgoingPacket
// 	// lp->cmd = CONFIGURATION_BULK_REPORT; set in - fillOutgoingPacket
// 	lp->numberOfParameters = 0x1;
// 	while (numberOfParameters-- != 0x0)
// 	{
// 		if ((cfg = zunoCFGParameter(param)) == ZUNO_CFG_PARAMETER_UNKNOWN)
// 			cfg = &_param;
// 		lp->parameterOffset1 = parameterOffset >> 0x8;
// 		lp->parameterOffset2 = parameterOffset;
// 		lp->reportsToFollow = numberOfParameters;
// 		value = zunoLoadCFGParam(param);
// 		properties1 = cfg->size;
// 		CMD_REPLY_LEN = sizeof(ZwConfigurationBuilkReportFrame_t) + properties1;
// 		_zme_memcpy(&lp->parameter[0], (uint8_t *)&value, properties1);
// 		if ((uint32_t)cfg->defaultValue == value)
// 			properties1 = properties1 | CONFIGURATION_SET_LEVEL_DEFAULT_BIT_MASK;
// 		lp->properties1 = properties1;
// 		param++;
// 		parameterOffset++;

// 		zunoSendZWPackage(&g_outgoing_main_packet);
// 	}
// 	return (ZUNO_COMMAND_PROCESSED);
// }

int zuno_CCConfigurationHandler(ZUNOCommandPacket_t *cmd) {
	int				rs;

	switch(ZW_CMD) {
		case CONFIGURATION_DEFAULT_RESET:
			rs = _configuration_default_reset();
			break ;
		// case CONFIGURATION_BULK_GET:
		// 	rs = _configuration_builk_get((const ZwConfigurationBuilkGetFrame_t *)cmd->cmd);
		// 	break ;
		case CONFIGURATION_GET:
			rs = _configuration_get(((ZwConfigurationGetFrame_t *)cmd->cmd)->parameterNumber);
			break ;
		case CONFIGURATION_SET:
			rs = _configuration_set(cmd);
			break ;
		case CONFIGURATION_PROPERTIES_GET:
			rs = _configuration_properties_get((ZwConfigurationPropertiesGetFrame_t *)cmd->cmd);
			break ;
		case CONFIGURATION_NAME_GET:
			rs = _configuration_name_get((ZwConfigurationNameGetFrame_t *)cmd->cmd, ZunoCFGTypeHandlerName);
			break ;
		case CONFIGURATION_INFO_GET:
			rs = _configuration_info_get((ZwConfigurationInfoGetFrame_t *)cmd->cmd);
			break ;
		default:
			rs = ZUNO_UNKNOWN_CMD;
			break ;
	}
	return (rs);
}


CONFIGPARAM_MAX_SIZE zunoLoadCFGParam(uint8_t param)
{
	CONFIGPARAM_MAX_SIZE		out;
	if (param < CONFIGPARAM_MIN_PARAM || param > CONFIGPARAM_MAX_PARAM)// Check if this is not user data
		return (0);
	zunoEEPROMRead(CONFIGPARAM_EEPROM_ADDR(param), sizeof(CONFIGPARAM_MAX_SIZE), (uint8_t *)&out);
	return (out);
}

void zunoSaveCFGParam(uint8_t param, CONFIGPARAM_MAX_SIZE value)
{
	if (param < CONFIGPARAM_MIN_PARAM || param > CONFIGPARAM_MAX_PARAM)// Check if this is not user data
		return ;
	zunoEEPROMWrite(CONFIGPARAM_EEPROM_ADDR(param), sizeof(CONFIGPARAM_MAX_SIZE), (uint8_t *)&value);
}
