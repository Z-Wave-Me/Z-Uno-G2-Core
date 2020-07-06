#include "ZWCCConfiguration.h"
#include "./includes/ZWCCConfiguration_private.h"

#ifdef WITH_CC_CONFIGURATION
static int _configuration_get(uint8_t param) {
	ZwConfigurationReportFrame_t			*lp;
	uint32_t								value;

	if (param < CONFIGPARAM_MIN_PARAM || param > CONFIGPARAM_MAX_PARAM)// Check if this is not user data
		return (ZUNO_UNKNOWN_CMD);
	value = zunoLoadCFGParam(param);
	lp = (ZwConfigurationReportFrame_t *)&CMD_REPLY_CC;
	lp->byte4.cmdClass = COMMAND_CLASS_CONFIGURATION;
	lp->byte4.cmd = CONFIGURATION_REPORT;
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
	 for(int i=0;i<getSysHandlerCount(ZUNO_HANDLER_ZW_CFG);i++)
        ((zuno_configuartionhandler_t *)(getSysHandlerPtr(ZUNO_HANDLER_ZW_CFG, i)))(param, value);
	return (ZUNO_COMMAND_PROCESSED);
}

int zuno_CCConfigurationHandler(ZUNOCommandPacket_t *cmd) {
	int				rs;

	rs = ZUNO_UNKNOWN_CMD;
	switch(ZW_CMD) {
		case CONFIGURATION_GET:
			rs = _configuration_get(((ZwConfigurationGetFrame_t *)cmd->cmd)->parameterNumber);
			break ;
		case CONFIGURATION_SET:
			rs = _configuration_set(cmd);
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
#endif