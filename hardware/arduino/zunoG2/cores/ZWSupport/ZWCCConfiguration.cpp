#include "Arduino.h"
#include "ZWCCConfiguration.h"
#include "ZWCCSuperVision.h"

typedef uint32_t CONFIGPARAM_MAX_SIZE;

#define CONFIGPARAM_MIN_PARAM			0x40
#define CONFIGPARAM_MAX_PARAM			0x60
#define CONFIGPARAM_EEPROM_ADDR(param)	(((param - CONFIGPARAM_MIN_PARAM) * sizeof(CONFIGPARAM_MAX_SIZE)) + EEPROM_CONFIGURATION_ADDR)

#define CONFIGPARAM_STANDART_NAME			"Eeprom parameter "

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

// System side parameters information
const ZunoCFGParameter_t SYSCFGPARAM1 =
{
	.name = "Debug mode",
	.info = "Enables Z-Uno debug mode",
	.minValue = 0x0,
	.maxValue = 0x1,
	.defaultValue = 0x0,
	.size = ZUNO_CFG_PARAMETER_SIZE_8BIT,
	.format = ZUNO_CFG_PARAMETER_FORMAT_UNSIGNED,
	.readOnly = false,
	.altering = false
}; 
const ZunoCFGParameter_t SYSCFGPARAM2 =
{
	.name = "ActivityLED",
	.info = "Turns on/off activity led of Z-Uno",
	.minValue = 0x0,
	.maxValue = 0x1,
	.defaultValue = 0x1,
	.size = ZUNO_CFG_PARAMETER_SIZE_8BIT,
	.format = ZUNO_CFG_PARAMETER_FORMAT_UNSIGNED,
	.readOnly = false,
	.altering = false
}; 
const ZunoCFGParameter_t SYSCFGPARAM7 =
{
	.name = "Security",
	.info = "Turns on/off security mode",
	.minValue = 0x0,
	.maxValue = 0x1,
	.defaultValue = 0x1,
	.size = ZUNO_CFG_PARAMETER_SIZE_8BIT,
	.format = ZUNO_CFG_PARAMETER_FORMAT_UNSIGNED,
	.readOnly = false,
	.altering = false
}; 
const ZunoCFGParameter_t SYSCFGPARAM8 =
{
	.name = "RFLogging",
	.info = "Turns on/off exception logging via radio channel.",
	.minValue = 0x0,
	.maxValue = 0x1,
	.defaultValue = 0x1,
	.size = ZUNO_CFG_PARAMETER_SIZE_8BIT,
	.format = ZUNO_CFG_PARAMETER_FORMAT_UNSIGNED,
	.readOnly = false,
	.altering = false
}; 
const ZunoCFGParameter_t SYSCFGPARAM9 =
{
	.name = "RFFrequency",
	.info = "Changes Z-Wave region of Z-Uno",
	.minValue = 0x0,
	.maxValue = 0xFFFF,
	.defaultValue = 0x00FF,
	.size = ZUNO_CFG_PARAMETER_SIZE_16BIT,
	.format = ZUNO_CFG_PARAMETER_FORMAT_UNSIGNED,
	.readOnly = false,
	.altering = false
}; 
const ZunoCFGParameter_t SYSCFGPARAM11 =
{
	.name = "MultilevelReportInterval",
	.info = "Changes minimal report interval of SensorMultilevel/Meter. It's ONLY for tests, enable debug first.",
	.minValue = 0x0,
	.maxValue = 255,
	.defaultValue = 0x1,
	.size = ZUNO_CFG_PARAMETER_SIZE_8BIT,
	.format = ZUNO_CFG_PARAMETER_FORMAT_UNSIGNED,
	.readOnly = false,
	.altering = false
}; 
const ZunoCFGParameter_t SYSCFGPARAM20 =
{
	.name = "OTAConfirmation",
	.info = "Accepts firmware update process. If sketch has pin-code for upgrade you have to apply it here.",
	.minValue = 0x0,
	.maxValue = 0x7FFFFFFF,
	.defaultValue = 0x0,
	.size = ZUNO_CFG_PARAMETER_SIZE_32BIT,
	.format = ZUNO_CFG_PARAMETER_FORMAT_UNSIGNED,
	.readOnly = false,
	.altering = false
}; 
const ZunoCFGParameter_t *zunoCFGParameterProxy(size_t param){

	switch(param){
		case 1:
			return &SYSCFGPARAM1;
		case 2:
			return &SYSCFGPARAM2;
		case 7:
			return &SYSCFGPARAM7;
		case 8:
			return &SYSCFGPARAM8;
		case 9:
			return &SYSCFGPARAM9;
		case 11:
			return &SYSCFGPARAM11;
		case 20:
			return &SYSCFGPARAM20;
	}

	// Return user-defined callback result for user-defined parameters
	return  zunoCFGParameter(param);
}
static int _configuration_get(uint8_t param) {
	ZwConfigurationReportFrame_t			*lp;
	uint32_t								value;
	const ZunoCFGParameter_t				*cfg;

	if (param < CONFIGPARAM_MIN_PARAM)
		return (ZUNO_UNKNOWN_CMD); // Forward this parameter to main firmware
	if ((cfg = zunoCFGParameter(param)) == ZUNO_CFG_PARAMETER_UNKNOWN) {
		param = CONFIGPARAM_MIN_PARAM;
		while (param <= CONFIGPARAM_MAX_PARAM) {
			if ((cfg = zunoCFGParameter(param)) != ZUNO_CFG_PARAMETER_UNKNOWN)
				break ;
			param++;
		}
		if (param > CONFIGPARAM_MAX_PARAM)
			return (ZUNO_COMMAND_BLOCKED_FAILL);
	}
	value = zunoLoadCFGParam(param);
	lp = (ZwConfigurationReportFrame_t *)&CMD_REPLY_CC;
	// lp->byte4.cmdClass = COMMAND_CLASS_CONFIGURATION; set in -  fillOutgoingPacket
	// lp->byte4.cmd = CONFIGURATION_REPORT; set in - fillOutgoingPacket
	lp->byte4.parameterNumber = param;
	lp->byte4.level = cfg->size;
	switch (cfg->size){
		case 2:
			CMD_REPLY_LEN = sizeof(lp->byte2);
			lp->byte2.configurationValue1 = (uint8_t)(value >> 8);
			lp->byte2.configurationValue2 = (uint8_t)(value);
			break;
		case 1:
			CMD_REPLY_LEN = sizeof(lp->byte1);
			lp->byte1.configurationValue1 = (uint8_t)(value);
			break ;
		default:
			CMD_REPLY_LEN = sizeof(lp->byte4);
			lp->byte4.configurationValue1 = (uint8_t)(value >> 24);
			lp->byte4.configurationValue2 = (uint8_t)(value >> 16);
			lp->byte4.configurationValue3 = (uint8_t)(value >> 8);
			lp->byte4.configurationValue4 = (uint8_t)(value);
			break ;
	}
	return (ZUNO_COMMAND_ANSWERED);
}

static int _configuration_set(ZUNOCommandPacket_t *cmd) {
	ZwConfigurationSetFrame_t			*lp;
	uint8_t								level;
	uint8_t								param;
	uint32_t							value;
	const ZunoCFGParameter_t			*cfg;

	lp = (ZwConfigurationSetFrame_t *)cmd->cmd;
	param = lp->byte1.parameterNumber;
	if (param < CONFIGPARAM_MIN_PARAM)
		return ZUNO_UNKNOWN_CMD; // Forward this parameter to main firmware
	if (param > CONFIGPARAM_MAX_PARAM)// Check if this is not user data
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	if ((cfg = zunoCFGParameter(param)) == ZUNO_CFG_PARAMETER_UNKNOWN)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	level = lp->byte1.level;
	if ((level & CONFIGURATION_SET_LEVEL_DEFAULT_BIT_MASK) != 0)// Check whether you want to restore the default value
		value = (uint32_t)cfg->defaultValue;
	else {
		level = (level & CONFIGURATION_SET_LEVEL_SIZE_MASK);
		if (level != cfg->size)
			return (ZUNO_COMMAND_BLOCKED_FAILL);
		switch (level) {
			case 2:
				value = lp->byte4.configurationValue1 << 8;
				value = value | lp->byte4.configurationValue2;
				if (cfg->format == ZUNO_CFG_PARAMETER_FORMAT_SIGNED)
					value = (int16_t)value;
				break;
			case 1:
				value = lp->byte4.configurationValue1;
				if (cfg->format == ZUNO_CFG_PARAMETER_FORMAT_SIGNED)
					value = (int8_t)value;
				break ;
			default:
				value = lp->byte4.configurationValue1 << 24;
				value = value | (lp->byte4.configurationValue2 << 16);
				value = value | (lp->byte4.configurationValue3 << 8);
				value = value | lp->byte4.configurationValue4;
				break ;
		}
		if (cfg->format == ZUNO_CFG_PARAMETER_FORMAT_SIGNED) {
			if ((ssize_t)value < cfg->minValue || (ssize_t)value > cfg->maxValue)
				return (ZUNO_COMMAND_BLOCKED_FAILL);
		}
		else if (value < (size_t)cfg->minValue || value > (size_t)cfg->maxValue)
			return (ZUNO_COMMAND_BLOCKED_FAILL);
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
	if ((cfg = zunoCFGParameterProxy(parameter)) == ZUNO_CFG_PARAMETER_UNKNOWN) {
		properties1 = 0;
		end = (ZwConfigurationPropertiesPeportByte4FrameV4End_t *)&report->v4.byte4.minValue1;
	}
	else {
		size = cfg->size;
		_zme_memcpy(&report->v4.byte4.minValue1, (uint8_t *)&cfg->minValue, size);
		_zme_memcpy(&report->v4.byte4.maxValue1, (uint8_t *)&cfg->maxValue, size);
		_zme_memcpy(&report->v4.byte4.defaultValue1, (uint8_t *)&cfg->defaultValue, size);
		properties1 = ((uint8_t *)((uint8_t *)&cfg->defaultValue + sizeof(cfg->defaultValue)))[0];
		end = (ZwConfigurationPropertiesPeportByte4FrameV4End_t *)((size_t)&report->v4.byte4.minValue1 + size * 3);
	}
	report->v4.byte4.properties1 = properties1;
	if (parameter < CONFIGPARAM_MIN_PARAM)
		parameter = CONFIGPARAM_MIN_PARAM;
	else
		parameter++;
	if (zunoCFGParameterProxy(parameter) == ZUNO_CFG_PARAMETER_UNKNOWN)
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
	if ((cfg = zunoCFGParameterProxy(parameter)) == ZUNO_CFG_PARAMETER_UNKNOWN)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
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

int zuno_CCConfigurationHandler(ZUNOCommandPacket_t *cmd) {
	int				rs;

	switch(ZW_CMD) {
		case CONFIGURATION_DEFAULT_RESET:
			rs = _configuration_default_reset();
			break ;
		case CONFIGURATION_BULK_SET:
		case CONFIGURATION_BULK_GET:
			rs = zuno_CCSupervisionApp(ZUNO_COMMAND_BLOCKED_NO_SUPPORT);
			break ;
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
			rs = ZUNO_COMMAND_BLOCKED_NO_SUPPORT;
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
