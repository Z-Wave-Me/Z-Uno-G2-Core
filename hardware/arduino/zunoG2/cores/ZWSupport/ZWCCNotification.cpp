#include "ZWCCNotification.h"
#include "ZWSupport.h"

static const byte NOTIFICATION_MAPPER[] = {
	0,0,
	NOTIFICATION_TYPE_BURGLAR_ALARM, NOTIFICATION_EVENT_INTRUSION_UL,   // SENSOR_BINARY_REPORT_TYPE_GENERAL_PURPOSE       
	NOTIFICATION_TYPE_SMOKE_ALARM,   NOTIFICATION_EVENT_SMOKE_UL,       // SENSOR_BINARY_REPORT_TYPE_SMOKE                 
	NOTIFICATION_TYPE_CO_ALARM,      NOTIFICATION_EVENT_CO_UL,          // SENSOR_BINARY_REPORT_TYPE_CO                  
	NOTIFICATION_TYPE_CO2_ALARM,     NOTIFICATION_EVENT_CO2_UL,         // SENSOR_BINARY_REPORT_TYPE_CO2                     
	NOTIFICATION_TYPE_HEAT_ALARM,    NOTIFICATION_EVENT_OVERHEAT_UL,    // SENSOR_BINARY_REPORT_TYPE_HEAT                  
	NOTIFICATION_TYPE_WATER_ALARM,   NOTIFICATION_EVENT_WATER_LEAK_UL,  // SENSOR_BINARY_REPORT_TYPE_WATER                 
	NOTIFICATION_TYPE_HEAT_ALARM,    NOTIFICATION_EVENT_UNDERHEAT_UL,   // SENSOR_BINARY_REPORT_TYPE_FREEZE                 
	NOTIFICATION_TYPE_BURGLAR_ALARM, NOTIFICATION_EVENT_TAMPER_REMOVED, // SENSOR_BINARY_REPORT_TYPE_TAMPER              
	NOTIFICATION_TYPE_BURGLAR_ALARM,        NOTIFICATION_EVENT_INTRUSION_UL,       // SENSOR_BINARY_REPORT_TYPE_AUX                    
	NOTIFICATION_TYPE_ACCESS_CONTROL_ALARM, NOTIFICATION_EVENT_WINDOW_DOOR_OPENED, // SENSOR_BINARY_REPORT_TYPE_DOOR_WINDOW         
	NOTIFICATION_TYPE_BURGLAR_ALARM,        NOTIFICATION_EVENT_INTRUSION_UL,       // SENSOR_BINARY_REPORT_TYPE_TILT                   
	NOTIFICATION_TYPE_BURGLAR_ALARM,        NOTIFICATION_EVENT_MOTION_DETECTION_UL,// SENSOR_BINARY_REPORT_TYPE_MOTION              
	NOTIFICATION_TYPE_BURGLAR_ALARM,        NOTIFICATION_EVENT_GLASS_BREAK_UL ,     // SENSOR_BINARY_REPORT_TYPE_GLASSBREAK         
	NOTIFICATION_TYPE_HOME_HEALTH,          0x02,
	NOTIFICATION_TYPE_SIREN,                0x02,
	NOTIFICATION_TYPE_WATER_VALVE,          0x02,
	NOTIFICATION_TYPE_WEATHER_ALAR,         0x02,
	NOTIFICATION_TYPE_IRRIGATION,           0x02,
	NOTIFICATION_TYPE_GAS_ALARM,            NOTIFICATION_EVENT_GAS_COMBUSTIBLE,
	NOTIFICATION_TYPE_GAS_ALARM,            NOTIFICATION_EVENT_GAS_TOXIC
};

int zuno_CCNotificationReport(byte channel, ZUNOCommandPacket_t *cmd){
	uint32_t							eeprom_mask;
	size_t								index;
	size_t								notificationType;
	size_t								mevent;
	ZwNotificationReportFrame_t			*report;
	ZwNotificationGetFrame_t			*cmd_get;

	zunoEEPROMRead(EEPROM_NOTIFICATION_ADDR, EEPROM_NOTIFICATION_SIZE, (byte*)&eeprom_mask);// Load report mask from EEPROM
	if(cmd == NULL){// If it's unsolicited report we have to check if it was turned on by user
		if((eeprom_mask & (1UL << channel)) == 0)// Unsolicited => doesn't have incoming package
			return (ZUNO_COMMAND_BLOCKED); // User don't want this report => don't send it
		report = (ZwNotificationReportFrame_t *)&CMD_REPORT_CC;
		CMD_REPORT_LEN = NOTIFICATION_REPORT_LEN; 
	} else {
		report = (ZwNotificationReportFrame_t *)&CMD_REPLY_CC;
		CMD_REPLY_LEN = NOTIFICATION_REPORT_LEN; 
	}
	memset(report, 0, sizeof(report->byte1));// Initially till the report data with zeros
	index = (ZUNO_CFG_CHANNEL(channel).sub_type) << 1;
	if(cmd != NULL) {
		cmd_get = (ZwNotificationGetFrame_t*)cmd->cmd;
		if(cmd->len >= 4 && (notificationType = cmd_get->notificationType) != NOTIFICATION_MAPPER[index] && (notificationType != 0xFF))
			return (ZUNO_COMMAND_BLOCKED);// We don't support this request
		if(cmd_get->v1AlarmType == 0xFF)// Fix the "wildcard" param
			report->byte1.mevent = 0xFE;
	}
	report->byte1.cmdClass = COMMAND_CLASS_NOTIFICATION;
	report->byte1.cmd = NOTIFICATION_REPORT;
	
	if(report->byte1.mevent != 0xFE) {
		report->byte1.notificationStatus = (eeprom_mask & (1UL << channel)) ? NOTIFICATION_ON_VALUE : NOTIFICATION_OFF_VALUE;
		report->byte1.notificationType = NOTIFICATION_MAPPER[index];
		if(zuno_universalGetter1P(channel))
			mevent = NOTIFICATION_MAPPER[index + 1];
		else if (NOTIFICATION_MAPPER[index + 1] == NOTIFICATION_EVENT_WINDOW_DOOR_OPENED)// For window/door sensor we have special values => process this case
			mevent = NOTIFICATION_EVENT_WINDOW_DOOR_CLOSED;
		else {
			mevent = NOTIFICATION_OFF_VALUE;
			report->byte1.properties1 = 1;
			report->byte1.eventParameter1 = NOTIFICATION_MAPPER[index + 1];
		}
		report->byte1.mevent = mevent;
	}
	return (ZUNO_COMMAND_ANSWERED);
}

static int _set(size_t channel, ZwNotificationSetFrame_t *cmd) {
	uint32_t					eeprom_mask;
	size_t						notificationStatus;

	if(cmd->notificationType != NOTIFICATION_MAPPER[(ZUNO_CFG_CHANNEL(channel).sub_type) << 1])
		return (ZUNO_COMMAND_BLOCKED);
	notificationStatus = cmd->notificationStatus;
	if((notificationStatus != NOTIFICATION_OFF_VALUE) && (notificationStatus != NOTIFICATION_ON_VALUE))
		return (ZUNO_COMMAND_BLOCKED);
	zunoEEPROMRead(EEPROM_NOTIFICATION_ADDR, EEPROM_NOTIFICATION_SIZE, (byte*)&eeprom_mask);
	if(notificationStatus)
		eeprom_mask |= 1UL << channel;
	else
		eeprom_mask &= ~(1UL << channel);
	zunoEEPROMWrite(EEPROM_NOTIFICATION_ADDR, EEPROM_NOTIFICATION_SIZE, (byte*)&eeprom_mask);
	return (ZUNO_COMMAND_PROCESSED);
}

static int _supported_get(size_t channel) {
	ZwNotificationSupportedReportFrame_t		*report;

	report = (ZwNotificationSupportedReportFrame_t *)&CMD_REPLY_CC;
	// report->cmdClass = COMMAND_CLASS_NOTIFICATION; set in - fillOutgoingPacket
	// report->cmd = NOTIFICATION_SUPPORTED_REPORT; set in - fillOutgoingPacket
	report->properties1 = ((NOTIFICATION_TYPE_MAX >> 3) + 1);
	CMD_REPLY_LEN = sizeof(ZwNotificationSupportedReportFrame_t) + ((NOTIFICATION_TYPE_MAX >> 3) + 1);
	memset(&report->bitMask[0], 0x0, ((NOTIFICATION_TYPE_MAX >> 3) + 1));
	zunoSetupBitMask(&report->bitMask[0], NOTIFICATION_MAPPER[(ZUNO_CFG_CHANNEL(channel).sub_type) << 1], ((NOTIFICATION_TYPE_MAX >> 3) + 1));
	return (ZUNO_COMMAND_ANSWERED);
}

static int _supported_get_even(size_t channel, ZwEventSupportedGetFrame_t *cmd) {
	ZwEventSupportedReportFrame_t						*report;
	size_t												index;
	size_t												notificationType;

	report = (ZwEventSupportedReportFrame_t *)&CMD_REPLY_CC;
	// report->cmdClass = COMMAND_CLASS_NOTIFICATION; set in - fillOutgoingPacket
	// report->cmd = EVENT_SUPPORTED_REPORT; set in - fillOutgoingPacket
	index = (ZUNO_CFG_CHANNEL(channel).sub_type) << 1;
	if((notificationType = cmd->notificationType) != NOTIFICATION_MAPPER[index] && notificationType != 0xFF)
		return (ZUNO_COMMAND_BLOCKED);// We don't support this request
	report->notificationType = notificationType;
	report->properties1 = ((NOTIFICATION_EVENT_MAX >> 3) + 1);
	CMD_REPLY_LEN = sizeof(ZwEventSupportedReportFrame_t) + ((NOTIFICATION_EVENT_MAX >> 3) + 1);
	memset(&report->bitMask[0], 0x0, ((NOTIFICATION_EVENT_MAX >> 3) + 1));
	zunoSetupBitMask(&report->bitMask[0], NOTIFICATION_MAPPER[index +1 ], ((NOTIFICATION_EVENT_MAX >> 3) + 1));
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCNotificationHandler(byte channel, ZUNOCommandPacket_t *cmd){
	int										rs;

	switch(ZW_CMD) {
		case NOTIFICATION_GET:
			_zunoMarkChannelRequested(channel);
			rs = zuno_CCNotificationReport(channel, cmd);	
			break ;
		case NOTIFICATION_SET:
			rs = _set(channel, (ZwNotificationSetFrame_t *)cmd->cmd);
			break ;
		case NOTIFICATION_SUPPORTED_GET:
			rs = _supported_get(channel);
			break;
		case EVENT_SUPPORTED_GET:
			rs = _supported_get_even(channel, (ZwEventSupportedGetFrame_t *)cmd->cmd);
			break;
		default:
			rs = ZUNO_UNKNOWN_CMD;
			break ;
	}
	return (rs);
}
