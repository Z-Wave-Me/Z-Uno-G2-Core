#include "ZWCCConfiguration.h"
#include "./includes/ZWCCConfiguration_private.h"


static int _configuration_get(uint8_t param) {
	ZwConfigurationReportFrame_t			*lp;
	CONFIGPARAM_MAX_SIZE					value;

	value = zunoLoadCFGParam(param);
	lp = (ZwConfigurationReportFrame_t *)&CMD_REPLY_CC;
	lp->byte2.cmdClass = COMMAND_CLASS_CONFIGURATION;
	lp->byte2.cmd = CONFIGURATION_REPORT;
	lp->byte2.parameterNumber = param;
	lp->byte2.level = sizeof(CONFIGPARAM_MAX_SIZE);
	lp->byte2.configurationValue1 = (uint8_t)(value >> 8);
	lp->byte2.configurationValue2 = (uint8_t)(value);
	CMD_REPLY_LEN = sizeof(lp->byte2);
	return (ZUNO_COMMAND_ANSWERED);
}

static void _configuration_set(uint8_t channel, ZUNOCommandPacket_t *cmd) {
	ZwConfigurationSetFrame_t			*lp;
	uint8_t								size;
	uint32_t							value;

	lp = (ZwConfigurationSetFrame_t *)cmd->cmd;
	if (((size = lp->byte1.level) & 0x80) != 0)
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
			value = 0;
			break;
	}
	zuno_universalSetter2P(channel, lp->byte1.parameterNumber, (CONFIGPARAM_MAX_SIZE)value);
}


int zuno_CCConfigurationHandler(uint8_t channel, ZUNOCommandPacket_t *cmd) {
	int				rs;

	rs = ZUNO_UNKNOWN_CMD;
	switch(ZW_CMD) {
		case CONFIGURATION_GET:
			rs = _configuration_get(((ZwConfigurationGetFrame_t *)cmd->cmd)->parameterNumber);
			break ;
		case CONFIGURATION_SET:
			_configuration_set(channel, cmd);
			rs = ZUNO_COMMAND_PROCESSED;
			break ;
	}
	return (rs);
}


CONFIGPARAM_MAX_SIZE zunoLoadCFGParam(uint8_t param)
{
	CONFIGPARAM_MAX_SIZE		out;
	if (param < CONFIGPARAM_MIN_PARAM || param > CONFIGPARAM_MAX_PARAM)
		return (0);
	zunoEEPROMRead(CONFIGPARAM_EEPROM_ADDR(param), sizeof(CONFIGPARAM_MAX_SIZE), (byte*)&out);
	return (out);
}

void zunoSaveCFGParam(uint8_t param, CONFIGPARAM_MAX_SIZE value)
{
	if (param < CONFIGPARAM_MIN_PARAM || param > CONFIGPARAM_MAX_PARAM)
		return ;
	zunoEEPROMWrite(CONFIGPARAM_EEPROM_ADDR(param), sizeof(CONFIGPARAM_MAX_SIZE), (byte*)&value);
}