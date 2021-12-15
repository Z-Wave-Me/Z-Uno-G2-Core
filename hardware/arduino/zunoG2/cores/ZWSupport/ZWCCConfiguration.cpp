#include "Arduino.h"
#include "ZWCCConfiguration.h"
#include "ZWCCSuperVision.h"

typedef uint32_t zunoCfgParamValue_t; // CONFIGPARAM_MAX_SIZE;

#define CONFIGPARAM_EEPROM_ADDR(param)	(((param - CONFIGPARAM_MIN_PARAM) * sizeof(zunoCfgParamValue_t)) + EEPROM_CONFIGURATION_ADDR)

#define CONFIGPARAM_STANDART_NAME			"Eeprom parameter "

typedef enum				ZunoCFGTypeHandler_e
{
	ZunoCFGTypeHandlerInfo,
	ZunoCFGTypeHandlerName
}							ZunoCFGTypeHandler_t;

const ZunoCFGParameter_t *zunoCFGParameter(size_t param) __attribute__ ((weak));
// DEFAULT metada for configuration parameters
const ZunoCFGParameter_t CFGPARAM_DEFAULT =
{
	.name = "Parameter NN",
	.info = "Custom configuration parameter",
	.minValue = 0x0,
	.maxValue = 0x7FFFFFFF,
	.defaultValue = 0x7FFFFFFF,
	.size = ZUNO_CFG_PARAMETER_SIZE_32BIT,
	.format = ZUNO_CFG_PARAMETER_FORMAT_UNSIGNED,
	.readOnly = false,
	.altering = false,
	.advanced = false
}; 
// Default method for zuno configuration parameter's metadata
const ZunoCFGParameter_t *zunoCFGParameter(size_t param) {
	static ZunoCFGParameter_t param_data;
	memcpy(&param_data, &CFGPARAM_DEFAULT, sizeof(ZunoCFGParameter_t));
	if(param > CONFIGPARAM_MAX_PARAM)
		return (ZUNO_CFG_PARAMETER_UNKNOWN);
	char* p_nn  = strstr(param_data.name, "NN");
	p_nn[0] = '0' + (param / 10) % 10;
	p_nn[1] = '0' + (param % 10);
	return (const ZunoCFGParameter_t *)&param_data;
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
	.altering = false,
	.advanced = true
}; 
const ZunoCFGParameter_t SYSCFGPARAM2 =
{
	.name = "ActivityLED",
	.info = "Turns on/off activity led",
	.minValue = 0x0,
	.maxValue = 0x1,
	.defaultValue = 0x1,
	.size = ZUNO_CFG_PARAMETER_SIZE_8BIT,
	.format = ZUNO_CFG_PARAMETER_FORMAT_UNSIGNED,
	.readOnly = false,
	.altering = false,
	.advanced = true
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
	.altering = false,
	.advanced = true
}; 
const ZunoCFGParameter_t SYSCFGPARAM8 =
{
	.name = "RFLogging",
	.info = "Turns on/off exception logging.",
	.minValue = 0x0,
	.maxValue = 0x1,
	.defaultValue = 0x1,
	.size = ZUNO_CFG_PARAMETER_SIZE_8BIT,
	.format = ZUNO_CFG_PARAMETER_FORMAT_UNSIGNED,
	.readOnly = false,
	.altering = false,
	.advanced = true
}; 
const ZunoCFGParameter_t SYSCFGPARAM9 =
{
	.name = "RFFrequency",
	.info = "Changes Z-Wave region of Z-Uno",
	.minValue = 0x00FF,
	.maxValue = 0x9F6,
	.defaultValue = 0x00FF,
	.size = ZUNO_CFG_PARAMETER_SIZE_16BIT,
	.format = ZUNO_CFG_PARAMETER_FORMAT_UNSIGNED,
	.readOnly = false,
	.altering = false,
	.advanced = true
}; 
const ZunoCFGParameter_t SYSCFGPARAM11 =
{
	.name = "MultilevelReportInterval",
	.info = "Minimal report interval.",
	.minValue = 0x0,
	.maxValue = 255,
	.defaultValue = 30,
	.size = ZUNO_CFG_PARAMETER_SIZE_8BIT,
	.format = ZUNO_CFG_PARAMETER_FORMAT_UNSIGNED,
	.readOnly = false,
	.altering = false,
	.advanced = true
}; 
const ZunoCFGParameter_t SYSCFGPARAM20 =
{
	.name = "OTAConfirmation",
	.info = "Accepts firmware update process.",
	.minValue = 0x0,
	.maxValue = 0x7FFFFFFF,
	.defaultValue = 0x0,
	.size = ZUNO_CFG_PARAMETER_SIZE_32BIT,
	.format = ZUNO_CFG_PARAMETER_FORMAT_UNSIGNED,
	.readOnly = false,
	.altering = false,
	.advanced = true
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

uint8_t checkConfigurationParameterSVSet(uint8_t * cmd){
	const ZunoCFGParameter_t				*cfg;

	uint16_t param = cmd[2];
	uint8_t options =  cmd[3];
	uint8_t size = options & CONFIGURATION_SET_LEVEL_SIZE_MASK;
	if(param > CONFIGPARAM_MAX_PARAM)
		return PARAM_SV_UNKNOWN_PARAM;
	cfg = zunoCFGParameterProxy(param);
	if(cfg == ZUNO_CFG_PARAMETER_UNKNOWN)
		return PARAM_SV_UNKNOWN_PARAM;
	
	if((options & CONFIGURATION_SET_LEVEL_DEFAULT_BIT_MASK) == 0){
		uint32_t new_value = _zunoSetterValue2Cortex(cmd+4, size);
		if(cfg->size  != size)
			return PARAM_SV_WRONG_PARAM_SIZE;
		if (cfg->format == ZUNO_CFG_PARAMETER_FORMAT_SIGNED) {
			if ((ssize_t)new_value < cfg->minValue || (ssize_t)new_value > cfg->maxValue)
				return PARAM_SV_WRONG_VALUE;
		}else if (new_value < (size_t)cfg->minValue || new_value > (size_t)cfg->maxValue)
				return PARAM_SV_WRONG_VALUE;
	}
	return (param < CONFIGPARAM_MIN_PARAM) ? PARAM_SV_SYSTEM_OK : PARAM_SV_USER_OK;
}
static int _configuration_get(ZwConfigurationGetFrame_t *cmd) {
	ZwConfigurationReportFrame_t			*lp;
	uint32_t								value;
	const ZunoCFGParameter_t				*cfg;
	size_t									param;

	param = cmd->parameterNumber;
	if ((cfg = zunoCFGParameterProxy(param)) == ZUNO_CFG_PARAMETER_UNKNOWN) {
		// User asks about unknown parameter, lets return the first existed parameter
		for(param = CONFIGPARAM_MIN_PARAM; param <= CONFIGPARAM_MAX_PARAM; param++){
			if ((cfg = zunoCFGParameterProxy(param)) != ZUNO_CFG_PARAMETER_UNKNOWN)
				break;
		}
		if (param > CONFIGPARAM_MAX_PARAM)
			return (ZUNO_COMMAND_BLOCKED_FAILL); // There are no user-side parameters 
	}
	if (param < CONFIGPARAM_MIN_PARAM)
		return (ZUNO_UNKNOWN_CMD); // Forward this parameter to main firmware
	value = zunoLoadCFGParam(param);
	lp = (ZwConfigurationReportFrame_t *)&CMD_REPLY_CC;
	// lp->byte4.cmdClass = COMMAND_CLASS_CONFIGURATION; set in -  fillOutgoingPacket
	// lp->byte4.cmd = CONFIGURATION_REPORT; set in - fillOutgoingPacket
	lp->byte4.parameterNumber = param;
	lp->byte4.level = cfg->size;
	_zme_memcpy(&lp->byte1.configurationValue1, (uint8_t*)&value, cfg->size);
	CMD_REPLY_LEN = sizeof(lp->byte1) - 1 + cfg->size;
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
		return (ZUNO_UNKNOWN_CMD); // Forward this parameter to main firmware
	if (param > CONFIGPARAM_MAX_PARAM)// Check if this is not user data
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	if ((cfg = zunoCFGParameterProxy(param)) == ZUNO_CFG_PARAMETER_UNKNOWN)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	if (cfg->readOnly == true)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	
	level = lp->byte1.level;
	if ((level & CONFIGURATION_SET_LEVEL_DEFAULT_BIT_MASK) != 0){// Check whether you want to restore the default value
		value = (uint32_t)cfg->defaultValue;
	} else {
		level = (level & CONFIGURATION_SET_LEVEL_SIZE_MASK);
		if (level != cfg->size)
			return (ZUNO_COMMAND_BLOCKED_FAILL);
		value = _zunoSetterValue2Cortex(&lp->byte4.configurationValue1, level);
		if (cfg->format == ZUNO_CFG_PARAMETER_FORMAT_SIGNED) {
			if ((ssize_t)value < cfg->minValue || (ssize_t)value > cfg->maxValue)
				return (ZUNO_COMMAND_BLOCKED_FAILL);
		}
		else if (value < (size_t)cfg->minValue || value > (size_t)cfg->maxValue)
			return (ZUNO_COMMAND_BLOCKED_FAILL);
	}
	zunoSaveCFGParam(param, (zunoCfgParamValue_t)value);
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
		end->properties2 = CONFIGURATION_PROPERTIES_REPORT_PROPERTIES2_NO_BULK_SUPPORT_BIT_MASK;
	}
	else {
		size = cfg->size;
		_zme_memcpy(&report->v4.byte4.minValue1, (uint8_t *)&cfg->minValue, size);
		_zme_memcpy(&report->v4.byte4.minValue1 + size, (uint8_t *)&cfg->maxValue, size);
		_zme_memcpy(&report->v4.byte4.minValue1 + size *2, (uint8_t *)&cfg->defaultValue, size);
		properties1 = ((uint8_t *)((uint8_t *)&cfg->defaultValue + sizeof(cfg->defaultValue)))[0];
		end = (ZwConfigurationPropertiesPeportByte4FrameV4End_t *)((size_t)&report->v4.byte4.minValue1 + size * 3);
		end->properties2 = CONFIGURATION_PROPERTIES_REPORT_PROPERTIES2_NO_BULK_SUPPORT_BIT_MASK;
		if(cfg->advanced)
			 end->properties2 |= CONFIGURATION_PROPERTIES_REPORT_PROPERTIES2_ADVANCED_BIT_MASK;
	}
	report->v4.byte4.properties1 = properties1;
	parameter++;
	for(; parameter <= CONFIGPARAM_MAX_PARAM; parameter++){
		if ((cfg = zunoCFGParameterProxy(parameter)) != ZUNO_CFG_PARAMETER_UNKNOWN)
			break;
	}
	if (parameter > CONFIGPARAM_MAX_PARAM)
		parameter = 0;
	end->nextParameterNumber1 = 0;
	end->nextParameterNumber2 = parameter;
	
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
	if ((cfg = zunoCFGParameterProxy(parameter)) == ZUNO_CFG_PARAMETER_UNKNOWN){
		zuno_CCSupervisionApp(ZUNO_COMMAND_BLOCKED_NO_SUPPORT);
		report->name[0] = 0;
		len = 1 + sizeof(ZwConfigurationNameReportFrame_t);
	} else {
		//report->reportsToFollow = 0;
		str = (type == ZunoCFGTypeHandlerInfo) ? cfg->info : cfg->name;
		len = strlen(str);
		if(len > (ZUNO_COMMAND_PACKET_CMD_LEN_MAX_OUT - sizeof(ZwConfigurationNameReportFrame_t)))
			len = (ZUNO_COMMAND_PACKET_CMD_LEN_MAX_OUT - sizeof(ZwConfigurationNameReportFrame_t));
		/*
		while (len > (ZUNO_COMMAND_PACKET_CMD_LEN_MAX_OUT - sizeof(ZwConfigurationNameReportFrame_t))) {
			len = len - (ZUNO_COMMAND_PACKET_CMD_LEN_MAX_OUT - sizeof(ZwConfigurationNameReportFrame_t));
			memcpy(&report->name[0], str, (ZUNO_COMMAND_PACKET_CMD_LEN_MAX_OUT - sizeof(ZwConfigurationNameReportFrame_t)));
			str = str + (ZUNO_COMMAND_PACKET_CMD_LEN_MAX_OUT - sizeof(ZwConfigurationNameReportFrame_t));
			CMD_REPLY_LEN = ZUNO_COMMAND_PACKET_CMD_LEN_MAX_OUT;
			zunoSendZWPackage(&g_outgoing_main_packet);
		}*/
		memcpy(report->name, str, len);
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
	const ZunoCFGParameter_t							*cfg;
	for(int i=CONFIGPARAM_MIN_PARAM; i<=CONFIGPARAM_MAX_PARAM; i++){
		cfg = zunoCFGParameter(i);
		if (cfg != ZUNO_CFG_PARAMETER_UNKNOWN)
			zunoSaveCFGParam(i, cfg->defaultValue);
	}
	return (ZUNO_UNKNOWN_CMD); // forward reset to main firmware
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
			rs = _configuration_get((ZwConfigurationGetFrame_t *)cmd->cmd);
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


zunoCfgParamValue_t zunoLoadCFGParam(uint8_t param)
{
	zunoCfgParamValue_t		out;
	if (param < CONFIGPARAM_MIN_PARAM || param > CONFIGPARAM_MAX_PARAM)// Check if this is not user data
		return (0);
	zunoEEPROMRead(CONFIGPARAM_EEPROM_ADDR(param), sizeof(zunoCfgParamValue_t), (uint8_t *)&out);
	return (out);
}

void zunoSaveCFGParam(uint8_t param, zunoCfgParamValue_t value)
{
	if (param < CONFIGPARAM_MIN_PARAM || param > CONFIGPARAM_MAX_PARAM)// Check if this is not user data
		return ;
	zunoEEPROMWrite(CONFIGPARAM_EEPROM_ADDR(param), sizeof(zunoCfgParamValue_t), (uint8_t *)&value);
}

void zuno_CCConfiguration_OnDefault(){
	const ZunoCFGParameter_t							*cfg;
	for(int i=CONFIGPARAM_MIN_PARAM; i<=CONFIGPARAM_MAX_PARAM; i++){
		cfg = zunoCFGParameter(i);
		if (cfg != ZUNO_CFG_PARAMETER_UNKNOWN){
			#ifndef OLDSTYLE_CONFIG_DEFAULT
			// For most cases it just checks that configuration parameters are in right domain 
			int32_t current_value = zunoLoadCFGParam(i);
			if((current_value < cfg->minValue) || (current_value > cfg->maxValue))
			#endif
				zunoSaveCFGParam(i, cfg->defaultValue);
		}
	}
}