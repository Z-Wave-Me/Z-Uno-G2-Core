#include "ZWCCNotification.h"
#include "ZWSupport.h"
#include "Arduino.h"
#include "Debug.h"
#include "ZWCCSuperVision.h"

static const byte NOTIFICATION_MAPPER[] = {
	0, 0,
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
	NOTIFICATION_TYPE_GAS_ALARM,            NOTIFICATION_EVENT_GAS_TOXIC,
	NOTIFICATION_TYPE_SYSTEM_ALARM,         NOTIFICATION_EVENT_HW_FAIL,
	NOTIFICATION_TYPE_SYSTEM_ALARM,         NOTIFICATION_EVENT_HW_FAIL_OEM,
	NOTIFICATION_TYPE_BURGLAR_ALARM,		NOTIFICATION_EVENT_TAMPER_OBJECTMOVED
};

static uint8_t _get_sensor_index(uint8_t channel) {
	return (ZUNO_CFG_CHANNEL(channel).sub_type);
}

int zuno_CCNotificationReport(byte channel, ZUNOCommandPacket_t *cmd, ZUNOCommandPacket_t *packet){
	uint32_t							eeprom_mask;
	size_t								index;
	size_t								notificationType;
	size_t								mevent;
	ZwNotificationReportFrame_t			*report;
	ZwNotificationGetFrame_t			*cmd_get = NULL;

	zunoEEPROMRead(EEPROM_NOTIFICATION_ADDR, EEPROM_NOTIFICATION_SIZE, (byte*)&eeprom_mask);// Load report mask from EEPROM
	if(cmd == NULL){
		// If it's unsolicited report we have to check if it was turned on by user
		if((eeprom_mask & (1UL << channel)) == 0)// Unsolicited => doesn't have incoming package
			return (ZUNO_COMMAND_BLOCKED); // User don't want this report => don't send it
	}
	report = (ZwNotificationReportFrame_t *)&packet->cmd[0x0];
	packet->len = sizeof(report->byte1) - 2;//don't include sequenceNumber & parameter value by default
	memset(report, 0, sizeof(report->byte1));// Initially till the report data with zeros
	index = (_get_sensor_index(channel)) << 1;
	if(cmd != NULL) {
		cmd_get = (ZwNotificationGetFrame_t*)cmd->cmd;
		if(cmd->len >= 4 && (notificationType = cmd_get->notificationType) != NOTIFICATION_MAPPER[index] && (notificationType != 0xFF))
			return (ZUNO_COMMAND_BLOCKED);// We don't support this request
		if(cmd_get->v1AlarmType == 0xFF)// Fix the "wildcard" param
			report->byte1.mevent = 0xFE;
	}
	mevent = 0x0;
	report->byte1.cmdClass = COMMAND_CLASS_NOTIFICATION;
	report->byte1.cmd = NOTIFICATION_REPORT;
	if(report->byte1.mevent != 0xFE) {
		report->byte1.notificationStatus = (eeprom_mask & (1UL << channel)) ? NOTIFICATION_ON_VALUE : NOTIFICATION_OFF_VALUE;
		report->byte1.notificationType = NOTIFICATION_MAPPER[index];
		uint32_t val = zuno_universalGetter1P(channel);
		uint8_t  param = val  & 0xFF;

		#ifdef LOGGING_DBG
		LOGGING_UART.print("*** Notification V:");
		LOGGING_UART.print(val, HEX);
		LOGGING_UART.print(" T:");
		LOGGING_UART.println(param, HEX);
		#endif
		// For window/door sensor we have special values => process this case
		if (NOTIFICATION_MAPPER[index + 1] == NOTIFICATION_EVENT_WINDOW_DOOR_OPENED){
			if(cmd_get != NULL) {
				// It's not an unsolicited report
				// check what they do want to known...
				if(cmd->len >= 5){
				  if(cmd_get->mevent == NOTIFICATION_EVENT_WINDOW_DOOR_OPENED){
					  mevent = param ? NOTIFICATION_EVENT_WINDOW_DOOR_OPENED : 0;
				  } else if (cmd_get->mevent == NOTIFICATION_EVENT_WINDOW_DOOR_CLOSED) {
					  mevent = param ? 0: NOTIFICATION_EVENT_WINDOW_DOOR_CLOSED;
				  } else if(cmd_get->mevent != 0) {
					  mevent = 0xFE;
				  }
				}
			} else {
				
				mevent = param ?  NOTIFICATION_EVENT_WINDOW_DOOR_OPENED : NOTIFICATION_EVENT_WINDOW_DOOR_CLOSED;
			}
		} else {
			if(param){
				if(param == NOTIFICATION_EVENT_PARAM_ADD){
					report->byte1.properties1 = 1;
					report->byte1.eventParameter1 = (val >> 8) & 0xFF;
					// Add parameter length to whole packet lenth
					packet->len = packet->len + 0x1;
				}
				mevent = NOTIFICATION_MAPPER[index + 1];
			} else {
				mevent = NOTIFICATION_OFF_VALUE;
			}
			if (cmd != NULL && cmd->len >= 5) {
				cmd_get = (ZwNotificationGetFrame_t*)cmd->cmd;
				if (cmd_get->mevent != NOTIFICATION_MAPPER[index + 1]){
					if(cmd_get->mevent != 0)
						mevent = 0xFE;
				}
			}
		}
		report->byte1.mevent = mevent;
	}
	return (ZUNO_COMMAND_ANSWERED);
}

static int _set(size_t channel, ZwNotificationSetFrame_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	uint32_t					eeprom_mask;
	size_t						notificationStatus;

	if(cmd->notificationType != NOTIFICATION_MAPPER[(_get_sensor_index(channel)) << 1])
		return (zuno_CCSupervisionApp(ZUNO_COMMAND_BLOCKED_FAILL, frame_report));
	notificationStatus = cmd->notificationStatus;
	if((notificationStatus != NOTIFICATION_OFF_VALUE) && (notificationStatus != NOTIFICATION_ON_VALUE))
		return (zuno_CCSupervisionApp(ZUNO_COMMAND_BLOCKED_FAILL, frame_report));
	zunoEEPROMRead(EEPROM_NOTIFICATION_ADDR, EEPROM_NOTIFICATION_SIZE, (byte*)&eeprom_mask);
	if(notificationStatus)
		eeprom_mask |= 1UL << channel;
	else
		eeprom_mask &= ~(1UL << channel);
	zunoEEPROMWrite(EEPROM_NOTIFICATION_ADDR, EEPROM_NOTIFICATION_SIZE, (byte*)&eeprom_mask);
	return (ZUNO_COMMAND_PROCESSED);
}

static int _supported_get(size_t channel, ZUNOCommandPacketReport_t *frame_report) {
	ZwNotificationSupportedReportFrame_t		*report;

	report = (ZwNotificationSupportedReportFrame_t *)frame_report->packet.cmd;
	// report->cmdClass = COMMAND_CLASS_NOTIFICATION; set in - fillOutgoingPacket
	// report->cmd = NOTIFICATION_SUPPORTED_REPORT; set in - fillOutgoingPacket
	report->properties1 = ((NOTIFICATION_TYPE_MAX >> 3) + 1);
	frame_report->packet.len = sizeof(ZwNotificationSupportedReportFrame_t) + report->properties1;
	memset(&report->bitMask[0], 0x0, ((NOTIFICATION_TYPE_MAX >> 3) + 1));
	zunoSetupBitMask(&report->bitMask[0], NOTIFICATION_MAPPER[(_get_sensor_index(channel)) << 1], report->properties1);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _supported_get_even(size_t channel, ZwEventSupportedGetFrame_t *cmd,ZUNOCommandPacketReport_t *frame_report) {
	ZwEventSupportedReportFrame_t						*report;
	size_t												index;
	size_t												notificationType;
	size_t												sz;

	report = (ZwEventSupportedReportFrame_t *)frame_report->packet.cmd;
	// report->cmdClass = COMMAND_CLASS_NOTIFICATION; set in - fillOutgoingPacket
	// report->cmd = EVENT_SUPPORTED_REPORT; set in - fillOutgoingPacket
	index = (_get_sensor_index(channel)) << 1;
	notificationType = cmd->notificationType;
	report->notificationType = notificationType;
	if(notificationType != NOTIFICATION_MAPPER[index] || notificationType == 0xFF) {
		report->properties1 = 0x0;
		frame_report->packet.len = sizeof(ZwEventSupportedReportFrame_t);
		return (ZUNO_COMMAND_ANSWERED);// We don't support this request
	}
	sz = ((NOTIFICATION_EVENT_MAX >> 3) + 1);
	report->properties1 = sz;
	frame_report->packet.len = sizeof(ZwEventSupportedReportFrame_t) + sz;
	memset(&report->bitMask[0], 0x0, sz);
	zunoSetupBitMask(&report->bitMask[0], NOTIFICATION_MAPPER[index +1 ], sz);
	if(notificationType == NOTIFICATION_TYPE_ACCESS_CONTROL_ALARM){
		// In this case we have to add another one event
		// For window/door sensor we have special values => process this case
		zunoSetupBitMask(&report->bitMask[0], NOTIFICATION_EVENT_WINDOW_DOOR_CLOSED, sz);
	}
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCNotificationHandler(byte channel, ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report){
	int										rs;

	switch(ZW_CMD) {
		case NOTIFICATION_GET:
			_zunoMarkChannelRequested(channel);
			rs = zuno_CCNotificationReport(channel, cmd, &frame_report->packet);
			break ;
		case NOTIFICATION_SET:
			rs = _set(channel, (ZwNotificationSetFrame_t *)cmd->cmd, frame_report);
			break ;
		case NOTIFICATION_SUPPORTED_GET:
			rs = _supported_get(channel, frame_report);
			break;
		case EVENT_SUPPORTED_GET:
			rs = _supported_get_even(channel, (ZwEventSupportedGetFrame_t *)cmd->cmd, frame_report);
			break;
		default:
			rs = ZUNO_COMMAND_BLOCKED_NO_SUPPORT;
			break ;
	}
	return (rs);
}


#define ICON_TYPE_GENERIC_SENSOR_NOTIFICATION                                0x0C00   //Sensor Notification Device Type
#define ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_SMOKE_ALARM                   0x0C01   //Sensor Notification Device Type (Notification type Smoke Alarm)
#define ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_CO_ALARM                      0x0C02   //Sensor Notification Device Type (Notification type CO Alarm)
#define ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_CO2_ALARM                     0x0C03   //Sensor Notification Device Type (Notification type CO2 Alarm)
#define ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_HEAT_ALARM                    0x0C04   //Sensor Notification Device Type (Notification type Heat Alarm)
#define ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_WATER_ALARM                   0x0C05   //Sensor Notification Device Type (Notification type Water Alarm)
#define ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_ACCESS_CONTROL                0x0C06   //Sensor Notification Device Type (Notification type Access Control)
#define ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_HOME_SECURITY                 0x0C07   //Sensor Notification Device Type (Notification type Home Security)
#define ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_POWER_MANAGEMENT              0x0C08   //Sensor Notification Device Type (Notification type Power Management)
#define ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_SYSTEM                        0x0C09   //Sensor Notification Device Type (Notification type System)
#define ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_EMERGENCY_ALARM               0x0C0A   //Sensor Notification Device Type (Notification type Emergency Alarm)
#define ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_CLOCK                         0x0C0B   //Sensor Notification Device Type (Notification type Clock)
#define ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_APPLIANCE                     0x0C0C
#define ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_HOME_HEALTH                   0x0C0D
#define ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_SIREN                         0x0C0E
#define ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_WATER_VALVE                   0x0C0F
#define ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_WEATHER_ALARM                 0x0C10
#define ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_IRRIGATION                    0x0C11
#define ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_GAS_ALARM                     0x0C12

#define ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_LAST                          ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_GAS_ALARM

#include "ZWCCZWavePlusInfo.h"


void zuno_CCNotificationGetIcon(uint8_t channel, ZwZwavePlusInfoIcon_t *icon) {
	uint8_t							notificationType;
	uint16_t						icon_type;

	notificationType = NOTIFICATION_MAPPER[_get_sensor_index(channel) << 0x1];
	icon_type = ICON_TYPE_GENERIC_SENSOR_NOTIFICATION;
	if (notificationType <= (ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_LAST - ICON_TYPE_GENERIC_SENSOR_NOTIFICATION))
		icon_type = icon_type + notificationType;
	icon->installerIconType = icon_type;
	icon->userIconType = icon_type;
}

#include "ZWCCAssociation.h"

void zuno_CCNotificationGetProfile(uint8_t channel, ZwAssociationInfoOut_t *agi) {
	agi->profile1 = COMMAND_CLASS_NOTIFICATION;
	agi->profile2 = NOTIFICATION_MAPPER[_get_sensor_index(channel) << 0x1];
}
