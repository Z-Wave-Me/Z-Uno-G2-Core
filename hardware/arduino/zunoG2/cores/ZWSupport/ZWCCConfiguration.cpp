#include "Arduino.h"
#include "ZWCCConfiguration.h"

typedef uint32_t CONFIGPARAM_MAX_SIZE;

#define CONFIGPARAM_MIN_PARAM			0x40
#define CONFIGPARAM_MAX_PARAM			0x60
#define CONFIGPARAM_EEPROM_ADDR(param)	(((param - CONFIGPARAM_MIN_PARAM) * sizeof(CONFIGPARAM_MAX_SIZE)) + 0x204)

#define CONFIGPARAM_STANDART_NAME			"Eeprom parameter "

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

	lp = (ZwConfigurationSetFrame_t *)cmd->cmd;
	param = lp->byte1.parameterNumber;
	if (param < CONFIGPARAM_MIN_PARAM || param > CONFIGPARAM_MAX_PARAM)// Check if this is not user data
		return (ZUNO_UNKNOWN_CMD);
	if (((size = lp->byte1.level) & 0x80) != 0)// Check whether you want to restore the default value
		size = 0;
	else
		size = size & 0x7;
	switch (size) {
		case 4:
			value = lp->byte4.configurationValue1 << 24;
			value = value | (lp->byte4.configurationValue2 << 16);
			value = value | (lp->byte4.configurationValue3 << 8);
			value = value | lp->byte4.configurationValue4;
			break;
		case 2:
			value = lp->byte2.configurationValue1 << 8;
			value = value | lp->byte2.configurationValue2;
			break;
		case 1:
			value = lp->byte1.configurationValue1;
			break;
		default:
			value = -1;
			break;
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
	ZwConfigurationPropertiesPeportByte4FrameV4End_t	*end;

	report = (ZwConfigurationPropertiesPeportFrame_t *)&CMD_REPLY_CC;
	// report->v4.byte4.cmdClass = COMMAND_CLASS_CONFIGURATION; set in - fillOutgoingPacket
	// report->v4.byte4.cmd = CONFIGURATION_PROPERTIES_REPORT; set in - fillOutgoingPacket
	parameterNumber1 = cmd->parameterNumber1;
	parameterNumber2 = cmd->parameterNumber2;
	report->v4.byte4.parameterNumber1 = parameterNumber1;
	report->v4.byte4.parameterNumber2 = parameterNumber2;
	parameter = (parameterNumber1 << 8) | parameterNumber2;
	if (parameter < CONFIGPARAM_MIN_PARAM || parameter > CONFIGPARAM_MAX_PARAM) {
		parameter = CONFIGPARAM_MIN_PARAM;
		properties1 = 0;
	}
	else {
		if (parameter == CONFIGPARAM_MAX_PARAM)
			parameter = 0;
		else
			parameter++;
		properties1 = (CONFIGURATION_PROPERTIES_REPORT_FORMAT_SIGNED_INTEGER << CONFIGURATION_PROPERTIES_REPORT_PROPERTIES1_FORMAT_SHIFT) | 4;
	}
	report->v4.byte4.properties1 = properties1;
	if (properties1 != 0) {
		report->v4.byte4.minValue1 = 0x80;
		report->v4.byte4.minValue2 = 0x0;
		report->v4.byte4.minValue3 = 0x0;
		report->v4.byte4.minValue4 = 0x0;
		report->v4.byte4.maxValue1 = 0x7F;
		report->v4.byte4.maxValue2 = 0xFF;
		report->v4.byte4.maxValue3 = 0xFF;
		report->v4.byte4.maxValue4 = 0xFF;
		report->v4.byte4.defaultValue1 = 0xFF;
		report->v4.byte4.defaultValue2 = 0xFF;
		report->v4.byte4.defaultValue3 = 0xFF;
		report->v4.byte4.defaultValue4 = 0xFF;
		end = &report->v4.byte4.end;
	}
	else
		end = (ZwConfigurationPropertiesPeportByte4FrameV4End_t *)&report->v4.byte4.minValue1;
	end->nextParameterNumber1 = 0;
	end->nextParameterNumber2 = parameter;
	end->properties2 = CONFIGURATION_PROPERTIES_REPORT_PROPERTIES2_NO_BULK_SUPPORT_BIT_MASK;
	CMD_REPLY_LEN = sizeof(ZwConfigurationPropertiesPeportByte4FrameV4End_t) + ((size_t)end - (size_t)report);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _configuration_name_get(ZwConfigurationNameGetFrame_t *cmd) {
	size_t												parameter;
	ZwConfigurationNameReportFrame_t					*report;
	size_t												parameterNumber1;
	size_t												parameterNumber2;
	size_t												len;

	report = (ZwConfigurationNameReportFrame_t *)&CMD_REPLY_CC;
	// report->cmdClass = COMMAND_CLASS_CONFIGURATION; set in - fillOutgoingPacket
	// report->cmd = CONFIGURATION_NAME_REPORT; set in - fillOutgoingPacket
	parameterNumber1 = cmd->parameterNumber1;
	parameterNumber2 = cmd->parameterNumber2;
	report->parameterNumber1 = parameterNumber1;
	report->parameterNumber2 = parameterNumber2;
	parameter = (parameterNumber1 << 8) | parameterNumber2;
	if (parameter < CONFIGPARAM_MIN_PARAM || parameter > CONFIGPARAM_MAX_PARAM)
		len = sizeof(ZwConfigurationNameReportFrame_t);
	else {
		report->name[(sizeof(CONFIGPARAM_STANDART_NAME) - 1)] = parameter / 10 + 0x30;
		report->name[(sizeof(CONFIGPARAM_STANDART_NAME) - 1) + 1] = parameter % 10 + 0x30;
		memcpy(&report->name[0], CONFIGPARAM_STANDART_NAME, sizeof(CONFIGPARAM_STANDART_NAME) - 1);
		len = sizeof(CONFIGPARAM_STANDART_NAME) - 1 + sizeof(ZwConfigurationNameReportFrame_t) + 2;//+2 fot numbers
	}
	report->reportsToFollow = 0;
	CMD_REPLY_LEN = len;
	return (ZUNO_COMMAND_ANSWERED);
}

static int _configuration_info_get(ZwConfigurationInfoGetFrame_t *cmd) {
	CMD_REPLY_CMD = CONFIGURATION_INFO_REPORT;
	return (_configuration_name_get((ZwConfigurationNameGetFrame_t *)cmd));
}

int zuno_CCConfigurationHandler(ZUNOCommandPacket_t *cmd) {
	int				rs;

	switch(ZW_CMD) {
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
			rs = _configuration_name_get((ZwConfigurationNameGetFrame_t *)cmd->cmd);
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
