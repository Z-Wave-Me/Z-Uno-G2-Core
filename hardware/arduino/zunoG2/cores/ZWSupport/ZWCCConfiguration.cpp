#include "Arduino.h"
#include "ZWCCConfiguration.h"
#include "ZWCCSuperVision.h"
#include "SysService.h"

#define CONFIGPARAM_MIN_PARAM				0x40
#define CONFIGPARAM_PARAM_COUNT_DEFAULT		(EEPROM_CONFIGURATION_SIZE / 0x4)
#define CONFIGPARAM_MAX_PARAM_DEFAULT		(CONFIGPARAM_MIN_PARAM + CONFIGPARAM_PARAM_COUNT_DEFAULT)

#ifdef CONFIGPARAMETERS_MAX_COUNT
	#define CONFIGPARAM_MAX_PARAM			(CONFIGPARAM_MIN_PARAM + CONFIGPARAMETERS_MAX_COUNT)
#else
	#define CONFIGPARAM_MAX_PARAM			CONFIGPARAM_MAX_PARAM_DEFAULT
#endif

#define CONFIGPARAM_EEPROM_ADDR(param)		(((param - CONFIGPARAM_MIN_PARAM) * sizeof(int32_t)) + EEPROM_CONFIGURATION_ADDR)
#define CONFIGPARAM_EEPROM_ADDR_ADD(param)	(((param - CONFIGPARAM_MAX_PARAM_DEFAULT) * sizeof(int32_t)) + EEPROM_USER_CODE_ADDR)

#define CONFIGPARAM_STANDART_NAME			"Eeprom parameter "

enum{
	ZUNO_SYSCFGPARAM_DBG = 1,
	ZUNO_SYSCFGPARAM_ACTIVITY_LED = 2,
	ZUNO_SYSCFGPARAM_SECURITY = 7,
	ZUNO_SYSCFGPARAM_LOGGING = 8,
	ZUNO_SYSCFGPARAM_FREQUENCY = 9,
	ZUNO_SYSCFGPARAM_REPORT_TIME = 11,
	ZUNO_SYSCFGPARAM_OTA_CONFIRM_PIN = 20
};
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
	.maxValue = -1,
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
	static char               alternative_name[32];
	memcpy(&param_data, &CFGPARAM_DEFAULT, sizeof(ZunoCFGParameter_t));
	strcpy(alternative_name, param_data.name);
	param_data.name = alternative_name;
	if((param >= CONFIGPARAM_MAX_PARAM) || 
		(param < CONFIGPARAM_MIN_PARAM))
		return (ZUNO_CFG_PARAMETER_UNKNOWN);
	char* p_nn  = strstr(param_data.name, "NN");
	if(p_nn == NULL)
		return (const ZunoCFGParameter_t *)&param_data;
	p_nn[0] = '0' + (param / 10) % 10;
	p_nn[1] = '0' + (param % 10);
	return (const ZunoCFGParameter_t *)&param_data;
}

// System side parameters information
const ZunoCFGParameter_t SYSCFGPARAM1 =
{
	.name = "Debug mode",
	.info = "Enables Z-Uno debug mode.",
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
	.name = "Activity LED",
	.info = "Turns on/off activity led.",
	.minValue = 0x0,
	.maxValue = 0x1,
	.defaultValue = 0x1,
	.size = ZUNO_CFG_PARAMETER_SIZE_8BIT,
	.format = ZUNO_CFG_PARAMETER_FORMAT_UNSIGNED,
	.readOnly = false,
	.altering = false,
	.advanced = true
};
#ifdef SECURITY_CONFIG_PARAM
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
	.altering = true,
	.advanced = true
};
#endif
const ZunoCFGParameter_t SYSCFGPARAM8 =
{
	.name = "RF logging",
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
#if defined(SKETCH_FLAGS) and (SKETCH_FLAGS == HEADER_FLAGS_REBOOT_CFG)
#pragma message "parameter 9 DEBUG version"
const ZunoCFGParameter_t SYSCFGPARAM9 =
{
	.name = "Radio frequency",
	.info = "Changes Z-Wave region of Z-Uno.",
	.minValue = 0,
	.maxValue = 0x11EE,
	.defaultValue = 0x00FF,
	.size = ZUNO_CFG_PARAMETER_SIZE_16BIT,
	.format = ZUNO_CFG_PARAMETER_FORMAT_UNSIGNED,
	.readOnly = false,
	.altering = false,
	.advanced = true
};
#else
const ZunoCFGParameter_t SYSCFGPARAM9 =
{
	.name = "Radio frequency",
	.info = "Changes Z-Wave region of Z-Uno.",
	.minValue = 0x00FF,
	.maxValue = 0x11EE,
	.defaultValue = 0x00FF,
	.size = ZUNO_CFG_PARAMETER_SIZE_16BIT,
	.format = ZUNO_CFG_PARAMETER_FORMAT_UNSIGNED,
	.readOnly = false,
	.altering = false,
	.advanced = true
};
#endif
const ZunoCFGParameter_t SYSCFGPARAM11 =
{
	.name = "Multilevel report interval",
	.info = "Minimal report interval. Debugging mode is required.",
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
	.name = "OTA confirmation",
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
		case ZUNO_SYSCFGPARAM_DBG:
			return &SYSCFGPARAM1;
		case ZUNO_SYSCFGPARAM_ACTIVITY_LED:
			return &SYSCFGPARAM2;
		#ifdef SECURITY_CONFIG_PARAM
		case ZUNO_SYSCFGPARAM_SECURITY:
			return &SYSCFGPARAM7;
		#endif
		case ZUNO_SYSCFGPARAM_LOGGING:
			return &SYSCFGPARAM8;
		// case ZUNO_SYSCFGPARAM_FREQUENCY:
		// 	return &SYSCFGPARAM9;
		case ZUNO_SYSCFGPARAM_REPORT_TIME:
			return &SYSCFGPARAM11;
		// case ZUNO_SYSCFGPARAM_OTA_CONFIRM_PIN:
		// 	return &SYSCFGPARAM20;
	}

	// Return user-defined callback result for user-defined parameters
	return  zunoCFGParameter(param);
}

static void _zunoSaveCFGParam(uint8_t param, ssize_t value, bool bUser);

uint8_t checkConfigurationParameterSVSet(uint8_t * cmd){
	const ZunoCFGParameter_t				*cfg;

	uint16_t param = cmd[2];
	uint8_t options =  cmd[3];
	uint8_t size = options & CONFIGURATION_SET_LEVEL_SIZE_MASK;
	if(param >= CONFIGPARAM_MAX_PARAM)
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

uint32_t g_ota_pin;
static void _loadSysParam(size_t param, uint32_t & value){
	switch(param){
		    case ZUNO_SYSCFGPARAM_DBG:
                    value = g_zuno_sys->p_config->flags & ZUNO_CFGFILE_FLAG_DBG ? 1 : 0;
                    break;
            case ZUNO_SYSCFGPARAM_ACTIVITY_LED:
                    value = g_zuno_sys->p_config->flags & ZUNO_CFGFILE_FLAG_LED_OFF? 1 : 0;
                    break;
            case ZUNO_SYSCFGPARAM_LOGGING:
                    value = g_zuno_sys->p_config->flags & ZUNO_CFGFILE_FLAG_RFLOG ? 1 : 0;
                    break;
            case ZUNO_SYSCFGPARAM_SECURITY:
                    value = g_zuno_sys->p_config->secure_mode;
                    break;
            case ZUNO_SYSCFGPARAM_FREQUENCY:{
                      // Encode region index 
                      uint8_t freq_i = zunoRegion2ZMEFrequency(g_zuno_sys->p_config->ifreq_deffered);
                      value = freq_i;
                      value <<= 8;
                      value |= freq_i ^ 0xFF;
                    }
                    break;
            case ZUNO_SYSCFGPARAM_REPORT_TIME:
                    value = g_zuno_sys->p_config->ml_interval;
                    break;
            case ZUNO_SYSCFGPARAM_OTA_CONFIRM_PIN:
                    if((g_zuno_codeheader.flags & HEADER_FLAGS_REBOOT_CFG) != 0){
                      value =  g_zuno_sys->fw_update_accepted ? 1 : 0; 
                    } else {
                      value = g_ota_pin;
                    }
               		break;
	}
}
void _saveFlag8b(uint8_t & bits, uint8_t f, bool on_off){
	if(on_off){
		bits |= f; 
	} else {
		bits &= ~f;
	}
}
static void _saveSysParam(size_t param, uint32_t  value){
	bool update = false;
	bool reboot = false;
	switch(param){
		    case ZUNO_SYSCFGPARAM_DBG:
					_saveFlag8b(g_zuno_sys->p_config->flags, ZUNO_CFGFILE_FLAG_DBG, value != 0);
					update = true;
					break;
            case ZUNO_SYSCFGPARAM_ACTIVITY_LED:
					_saveFlag8b(g_zuno_sys->p_config->flags, ZUNO_CFGFILE_FLAG_LED_OFF, value != 0);
					#ifndef NO_SYS_SVC
					SysReconfigLeds();
					#endif
					update = true;
                	break;
            case ZUNO_SYSCFGPARAM_LOGGING:
                    _saveFlag8b(g_zuno_sys->p_config->flags, ZUNO_CFGFILE_FLAG_RFLOG, value != 0);
					update = true;
                    break;
            case ZUNO_SYSCFGPARAM_SECURITY:
                    g_zuno_sys->p_config->secure_mode = value;
					update = true;
                    break;
            case ZUNO_SYSCFGPARAM_FREQUENCY:{
                      // Encode region index 
					  uint8_t freq_i = value >> 8;
                      if(value == 0){
						reboot = true;
					  } else if (value == 256){
						// Apply deferred frequency right now!
						g_zuno_sys->p_config->ifreq = g_zuno_sys->p_config->ifreq_deffered;
						g_zuno_sys->p_config->b_sketch_valid = 0x0F;
						update = true;
						reboot = true;
					  } else if ((freq_i ^ 0xFF) == (value & 0xFF)){
						// Setup DEFFERED frequency code. It will be active only after exclusion
                        g_zuno_sys->p_config->ifreq_deffered = zunoZMEFrequency2Region(freq_i);
						update = true;
					  }
                    }
                    break;
            case ZUNO_SYSCFGPARAM_REPORT_TIME:
                    g_zuno_sys->p_config->ml_interval = value;
					update = true;
                    break;
            case ZUNO_SYSCFGPARAM_OTA_CONFIRM_PIN:
					g_zuno_sys->fw_update_accepted = (value == g_zuno_codeheader.ota_pincode); 
                    if((g_zuno_codeheader.flags & HEADER_FLAGS_REBOOT_CFG) == 0){
                      g_ota_pin = value;
                    }
               		break;
	}
	if(update){
		zunoUpdateSysConfig(true, false);
	}
	if(reboot && (g_zuno_codeheader.flags & HEADER_FLAGS_REBOOT_CFG)){
		zunoReboot(false);
	}
}
static int _configuration_get(ZwConfigurationGetFrame_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	ZwConfigurationReportFrame_t			*lp;
	uint32_t								value;
	const ZunoCFGParameter_t				*cfg;
	size_t									param;

	param = cmd->parameterNumber;
	if ((cfg = zunoCFGParameterProxy(param)) == ZUNO_CFG_PARAMETER_UNKNOWN) {
		// User asks about unknown parameter, lets return the first existed parameter
		for(param = CONFIGPARAM_MIN_PARAM; param < CONFIGPARAM_MAX_PARAM; param++){
			if ((cfg = zunoCFGParameterProxy(param)) != ZUNO_CFG_PARAMETER_UNKNOWN)
				break;
		}
		if (param >= CONFIGPARAM_MAX_PARAM)
			return (ZUNO_COMMAND_BLOCKED_FAILL); // There are no user-side parameters 
	}
	if (param < CONFIGPARAM_MIN_PARAM){
		_loadSysParam(param, value); 
	} else {
		value = zunoLoadCFGParam(param);
	}
	lp = (ZwConfigurationReportFrame_t *)frame_report->packet.cmd;
	// lp->byte4.cmdClass = COMMAND_CLASS_CONFIGURATION; set in -  fillOutgoingPacket
	// lp->byte4.cmd = CONFIGURATION_REPORT; set in - fillOutgoingPacket
	lp->byte4.parameterNumber = param;
	lp->byte4.level = cfg->size;
	_zme_memcpy(&lp->byte1.configurationValue1, (uint8_t*)&value, cfg->size);
	frame_report->packet.len = sizeof(lp->byte1) - 1 + cfg->size;
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
	if (param >= CONFIGPARAM_MAX_PARAM)// Check if this is not user data
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
	if (param < CONFIGPARAM_MIN_PARAM){
		_saveSysParam(param, value);
	} else {
		_zunoSaveCFGParam(param, (int32_t)value, false);
	}
	return (ZUNO_COMMAND_PROCESSED);
}

static int _configuration_properties_get(ZwConfigurationPropertiesGetFrame_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	size_t												parameter;
	ZwConfigurationPropertiesPeportFrame_t				*report;
	size_t												parameterNumber1;
	size_t												parameterNumber2;
	size_t												properties1;
	size_t												size;
	ZwConfigurationPropertiesPeportByte4FrameV4End_t	*end;
	const ZunoCFGParameter_t							*cfg;

	report = (ZwConfigurationPropertiesPeportFrame_t *)frame_report->packet.cmd;
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
	for(; parameter < CONFIGPARAM_MAX_PARAM; parameter++){
		if ((cfg = zunoCFGParameterProxy(parameter)) != ZUNO_CFG_PARAMETER_UNKNOWN)
			break;
	}
	if (parameter >= CONFIGPARAM_MAX_PARAM)
		parameter = 0;
	end->nextParameterNumber1 = 0;
	end->nextParameterNumber2 = parameter;
	
	frame_report->packet.len = sizeof(ZwConfigurationPropertiesPeportByte4FrameV4End_t) + ((size_t)end - (size_t)report);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _configuration_name_get(ZwConfigurationNameGetFrame_t *cmd, ZunoCFGTypeHandler_t type, ZUNOCommandPacketReport_t *frame_report) {
	size_t												parameter;
	ZwConfigurationNameReportFrame_t					*report;
	size_t												parameterNumber1;
	size_t												parameterNumber2;
	size_t												len;
	const char											*str;
	const ZunoCFGParameter_t							*cfg;

	report = (ZwConfigurationNameReportFrame_t *)frame_report->packet.cmd;
	// report->cmdClass = COMMAND_CLASS_CONFIGURATION; set in - fillOutgoingPacket
	// report->cmd = CONFIGURATION_NAME_REPORT; set in - fillOutgoingPacket
	parameterNumber1 = cmd->parameterNumber1;
	parameterNumber2 = cmd->parameterNumber2;
	report->parameterNumber1 = parameterNumber1;
	report->parameterNumber2 = parameterNumber2;
	parameter = (parameterNumber1 << 8) | parameterNumber2;
	if ((cfg = zunoCFGParameterProxy(parameter)) == ZUNO_CFG_PARAMETER_UNKNOWN){
		zuno_CCSupervisionApp(ZUNO_COMMAND_BLOCKED_NO_SUPPORT, frame_report);
		report->name[0] = 0;
		len = 1 + sizeof(ZwConfigurationNameReportFrame_t);
	} else {
		frame_report->packet.len = (ZUNO_COMMAND_PACKET_CMD_LEN_MAX_OUT);
		report->reportsToFollow = 0x1;
		str = (type == ZunoCFGTypeHandlerInfo) ? cfg->info : cfg->name;
		len = strlen(str);
		while (len > (ZUNO_COMMAND_PACKET_CMD_LEN_MAX_OUT - sizeof(ZwConfigurationNameReportFrame_t))) {
			len = len - (ZUNO_COMMAND_PACKET_CMD_LEN_MAX_OUT - sizeof(ZwConfigurationNameReportFrame_t));
			memcpy(&report->name[0], str, (ZUNO_COMMAND_PACKET_CMD_LEN_MAX_OUT - sizeof(ZwConfigurationNameReportFrame_t)));
			str = str + (ZUNO_COMMAND_PACKET_CMD_LEN_MAX_OUT - sizeof(ZwConfigurationNameReportFrame_t));
			zunoSendZWPackage(&frame_report->packet);
		}
		memcpy(report->name, str, len);
		len = len + sizeof(ZwConfigurationNameReportFrame_t);
	}
	report->reportsToFollow = 0x0;
	frame_report->packet.len = len;
	return (ZUNO_COMMAND_ANSWERED);
}

static int _configuration_info_get(ZwConfigurationInfoGetFrame_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	frame_report->packet.cmd[0x1] = CONFIGURATION_INFO_REPORT;
	return (_configuration_name_get((ZwConfigurationNameGetFrame_t *)cmd, ZunoCFGTypeHandlerInfo, frame_report));
}

static int _configuration_default_reset(void) {
	const ZunoCFGParameter_t							*cfg;

	for(int i=0x0; i< CONFIGPARAM_MAX_PARAM; i++){
		cfg = zunoCFGParameter(i);
		if (cfg != ZUNO_CFG_PARAMETER_UNKNOWN) {
			if (i < CONFIGPARAM_MIN_PARAM)
				_saveSysParam(i, cfg->defaultValue);
			else
				_zunoSaveCFGParam(i, cfg->defaultValue, false);
		}
	}
	return (ZUNO_COMMAND_PROCESSED); // forward reset to main firmware
}
int zuno_CCConfigurationHandler(ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	int				rs;

	switch(ZW_CMD) {
		case CONFIGURATION_DEFAULT_RESET:
			rs = _configuration_default_reset();
			break ;
		case CONFIGURATION_BULK_SET:
		case CONFIGURATION_BULK_GET:
			rs = zuno_CCSupervisionApp(ZUNO_COMMAND_BLOCKED_NO_SUPPORT, frame_report);
			break ;
		case CONFIGURATION_GET:
			rs = _configuration_get((ZwConfigurationGetFrame_t *)cmd->cmd, frame_report);
			break ;
		case CONFIGURATION_SET:
			rs = _configuration_set(cmd);
			break ;
		case CONFIGURATION_PROPERTIES_GET:
			rs = _configuration_properties_get((ZwConfigurationPropertiesGetFrame_t *)cmd->cmd, frame_report);
			break ;
		case CONFIGURATION_NAME_GET:
			rs = _configuration_name_get((ZwConfigurationNameGetFrame_t *)cmd->cmd, ZunoCFGTypeHandlerName, frame_report);
			break ;
		case CONFIGURATION_INFO_GET:
			rs = _configuration_info_get((ZwConfigurationInfoGetFrame_t *)cmd->cmd, frame_report);
			break ;
		default:
			rs = ZUNO_COMMAND_BLOCKED_NO_SUPPORT;
			break ;
	}
	return (rs);
}


ssize_t zunoLoadCFGParam(uint8_t param) {
	const ZunoCFGParameter_t							*cfg;
	int32_t												out;
	ssize_t												minValue;
	ssize_t												maxValue;
	uint32_t											addr;

	if (param < CONFIGPARAM_MIN_PARAM || param >= CONFIGPARAM_MAX_PARAM)// Check if this is not user data
		return (0);
	#if CONFIGPARAM_MAX_PARAM > CONFIGPARAM_MAX_PARAM_DEFAULT
		if (param >= CONFIGPARAM_MAX_PARAM_DEFAULT)
			addr = CONFIGPARAM_EEPROM_ADDR_ADD(param);
		else
			addr = CONFIGPARAM_EEPROM_ADDR(param);
	#else
		addr = CONFIGPARAM_EEPROM_ADDR(param);
	#endif
	zunoEEPROMRead(addr, sizeof(out), (uint8_t *)&out);
	if ((cfg = zunoCFGParameter(param)) == ZUNO_CFG_PARAMETER_UNKNOWN)
		return (out);
	minValue = cfg->minValue;
	maxValue= cfg->maxValue;
	if (cfg->format == ZUNO_CFG_PARAMETER_FORMAT_UNSIGNED) {
		if ((uint32_t)out < (uint32_t)minValue || (uint32_t)out > (uint32_t)maxValue)
			out = cfg->defaultValue;
	}
	else if ((int32_t)out < (int32_t)minValue || (int32_t)out > (int32_t)maxValue)
		out = cfg->defaultValue;
	return (out);
}

static void _zunoSaveCFGParam(uint8_t param, ssize_t value, bool bUser) {
	const ZunoCFGParameter_t							*cfg;
	int32_t												result;
	size_t												size;
	uint32_t											addr;

	if (param < CONFIGPARAM_MIN_PARAM || param >= CONFIGPARAM_MAX_PARAM)// Check if this is not user data
		return ;
	if ((cfg = zunoCFGParameter(param)) != ZUNO_CFG_PARAMETER_UNKNOWN) {
		if (cfg->readOnly == true)
			return ;
		size = cfg->size;
		if (cfg->format == ZUNO_CFG_PARAMETER_FORMAT_UNSIGNED) {
			switch (size) {
				case ZUNO_CFG_PARAMETER_SIZE_8BIT:
					result = (uint8_t)value;
					break ;
				case ZUNO_CFG_PARAMETER_SIZE_16BIT:
					result = (uint16_t)value;
					break ;
				case ZUNO_CFG_PARAMETER_SIZE_32BIT:
				default:
					result = (uint32_t)value;
					break ;
			}
		}
		else {
			switch (size) {
				case ZUNO_CFG_PARAMETER_SIZE_8BIT:
					result = (int8_t)value;
					break ;
				case ZUNO_CFG_PARAMETER_SIZE_16BIT:
					result = (int16_t)value;
					break ;
				case ZUNO_CFG_PARAMETER_SIZE_32BIT:
				default:
					result = (int32_t)value;
					break ;
			}
		}
	}
	else
		result = value;
	if (bUser == false)
		zunoSysHandlerCall(ZUNO_HANDLER_ZW_CFG, 0, param, value);
	#if CONFIGPARAM_MAX_PARAM > CONFIGPARAM_MAX_PARAM_DEFAULT
		if (param >= CONFIGPARAM_MAX_PARAM_DEFAULT)
			addr = CONFIGPARAM_EEPROM_ADDR_ADD(param);
		else
			addr = CONFIGPARAM_EEPROM_ADDR(param);
	#else
		addr = CONFIGPARAM_EEPROM_ADDR(param);
	#endif
	zunoEEPROMWrite(addr, sizeof(result), (uint8_t *)&result);
}

void zunoSaveCFGParam(uint8_t param, ssize_t value) {
	return (_zunoSaveCFGParam(param, value, true));
}