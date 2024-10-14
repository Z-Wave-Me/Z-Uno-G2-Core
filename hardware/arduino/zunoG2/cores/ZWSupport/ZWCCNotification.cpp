#include "ZWCCNotification.h"
#include "ZWSupport.h"
#include "Arduino.h"
#include "Debug.h"
#include "ZWCCSuperVision.h"

typedef struct 						ZwNotificationTableSimle_s
{
	uint8_t							type;
	uint8_t							event;
}									ZwNotificationTableSimle_t;

static const ZwNotificationTableSimle_t NOTIFICATION_MAPPER[] = {
	{.type = 0, .event = 0},
	{.type = NOTIFICATION_TYPE_BURGLAR_ALARM, .event = NOTIFICATION_EVENT_INTRUSION_UL},   // SENSOR_BINARY_REPORT_TYPE_GENERAL_PURPOSE       
	{.type = NOTIFICATION_TYPE_SMOKE_ALARM,   .event = NOTIFICATION_EVENT_SMOKE_UL},       // SENSOR_BINARY_REPORT_TYPE_SMOKE                 
	{.type = NOTIFICATION_TYPE_CO_ALARM,      .event = NOTIFICATION_EVENT_CO_UL},          // SENSOR_BINARY_REPORT_TYPE_CO                  
	{.type = NOTIFICATION_TYPE_CO2_ALARM,     .event = NOTIFICATION_EVENT_CO2_UL},         // SENSOR_BINARY_REPORT_TYPE_CO2                     
	{.type = NOTIFICATION_TYPE_HEAT_ALARM,    .event = NOTIFICATION_EVENT_OVERHEAT_UL},    // SENSOR_BINARY_REPORT_TYPE_HEAT                  
	{.type = NOTIFICATION_TYPE_WATER_ALARM,   .event = NOTIFICATION_EVENT_WATER_LEAK_UL},  // SENSOR_BINARY_REPORT_TYPE_WATER                 
	{.type = NOTIFICATION_TYPE_HEAT_ALARM,    .event = NOTIFICATION_EVENT_UNDERHEAT_UL},   // SENSOR_BINARY_REPORT_TYPE_FREEZE                 
	{.type = NOTIFICATION_TYPE_BURGLAR_ALARM, .event = NOTIFICATION_EVENT_TAMPER_REMOVED}, // SENSOR_BINARY_REPORT_TYPE_TAMPER              
	{.type = NOTIFICATION_TYPE_BURGLAR_ALARM,        .event = NOTIFICATION_EVENT_INTRUSION_UL},       // SENSOR_BINARY_REPORT_TYPE_AUX                    
	{.type = NOTIFICATION_TYPE_ACCESS_CONTROL_ALARM, .event = NOTIFICATION_EVENT_WINDOW_DOOR_OPENED}, // SENSOR_BINARY_REPORT_TYPE_DOOR_WINDOW         
	{.type = NOTIFICATION_TYPE_BURGLAR_ALARM,        .event = NOTIFICATION_EVENT_INTRUSION_UL},       // SENSOR_BINARY_REPORT_TYPE_TILT                   
	{.type = NOTIFICATION_TYPE_BURGLAR_ALARM,        .event = NOTIFICATION_EVENT_MOTION_DETECTION_UL},// SENSOR_BINARY_REPORT_TYPE_MOTION              
	{.type = NOTIFICATION_TYPE_BURGLAR_ALARM,        .event = NOTIFICATION_EVENT_GLASS_BREAK_UL},     // SENSOR_BINARY_REPORT_TYPE_GLASSBREAK         
	{.type = NOTIFICATION_TYPE_HOME_HEALTH,          .event = 0x02},
	{.type = NOTIFICATION_TYPE_SIREN,                .event = 0x02},
	{.type = NOTIFICATION_TYPE_WATER_VALVE,          .event = 0x02},
	{.type = NOTIFICATION_TYPE_WEATHER_ALAR,         .event = 0x02},
	{.type = NOTIFICATION_TYPE_IRRIGATION,           .event = 0x02},
	{.type = NOTIFICATION_TYPE_GAS_ALARM,            .event = NOTIFICATION_EVENT_GAS_COMBUSTIBLE},
	{.type = NOTIFICATION_TYPE_GAS_ALARM,            .event = NOTIFICATION_EVENT_GAS_TOXIC},
	{.type = NOTIFICATION_TYPE_SYSTEM_ALARM,         .event = NOTIFICATION_EVENT_HW_FAIL},
	{.type = NOTIFICATION_TYPE_SYSTEM_ALARM,         .event = NOTIFICATION_EVENT_HW_FAIL_OEM},
	{.type = NOTIFICATION_TYPE_BURGLAR_ALARM,		.event = NOTIFICATION_EVENT_TAMPER_OBJECTMOVED}
};

typedef struct 						ZwNotificationInfo_s
{
	uint8_t							type;
	uint8_t							event;
	bool							extend;
	uint32_t						mask;
}									ZwNotificationInfo_t;


static bool _get_info(uint8_t channel, ZwNotificationInfo_t *info) {
	size_t								sub_type;
	uint32_t							mask;

	memset(info, 0x0, sizeof(info[0x0]));
	sub_type = ZUNO_CFG_CHANNEL(channel).sub_type;
	if ((sub_type & ZUNO_NOTIFICATION_TYPE_FLAG) != 0x0) {
		memcpy(&mask, &ZUNO_CFG_CHANNEL(channel).params[0x0], sizeof(mask));
		switch (sub_type) {
			case ZUNO_NOTIFICATION_POWER_MANAGEMENT:
				mask = mask & ZUNO_NOTIFICATION_POWER_MANAGEMENT_EVENT_ALL_MASK;
				break ;
			default:
				mask = 0x0;
				break ;
		}
		if (mask == 0x0)
			return (false);
		info->type = sub_type ^ ZUNO_NOTIFICATION_TYPE_FLAG;
		info->extend = true;
		info->mask = mask;
		return (true);
	}
	if (sub_type >= (sizeof(NOTIFICATION_MAPPER) / sizeof(NOTIFICATION_MAPPER[0x0])))
		return (false);
	info->type = NOTIFICATION_MAPPER[sub_type].type;
	info->event = NOTIFICATION_MAPPER[sub_type].event;
	return (true);
}

bool zuno_CCNotificationReport(uint8_t channel, uint8_t event, uint8_t state) {
	ZwNotificationInfo_t				info;
	ZUNOCommandPacketReport_t			frame;
	ZwNotificationReportFrame_t			*report;
	uint32_t							eeprom_mask;

	if (channel == 0x0)
		return (false);
	channel--;
	if (channel > ZUNO_CFG_CHANNEL_COUNT)
		return (false);
	if (ZUNO_CFG_CHANNEL(channel).type != ZUNO_SENSOR_BINARY_CHANNEL_NUMBER)
		return (false);
	zunoEEPROMRead(EEPROM_NOTIFICATION_ADDR, EEPROM_NOTIFICATION_SIZE, (byte*)&eeprom_mask);// Load report mask from EEPROM
	if((eeprom_mask & (1UL << channel)) == 0)// Unsolicited => doesn't have incoming package
		return (false); // User don't want this report => don't send it
	if (_get_info(channel, &info) == false)
		return (false);
	if (event != 0x0)
		if (info.extend == true)
			if (event >= (sizeof(info.mask) * 8) || (info.mask & (0x1 << event)) == 0x0)
				return (false);
	fillOutgoingReportPacketAsync(&frame, ZUNO_CFG_CHANNEL(channel).zw_channel);
	report = (ZwNotificationReportFrame_t *)&frame.info.packet.cmd[0x0];
	report->byte1.cmdClass = COMMAND_CLASS_NOTIFICATION;
	report->byte1.cmd = NOTIFICATION_REPORT;
	report->byte1.v1AlarmType = 0x0;
	report->byte1.v1AlarmLevel = 0x0;
	report->byte1.reserved = 0x0;
	report->byte1.notificationStatus = NOTIFICATION_ON_VALUE;
	report->byte1.notificationType = info.type;
	if (event != 0x0 && state == NOTIFICATION_OFF_VALUE) {
		report->byte1.properties1 = 0x1;
		report->byte1.mevent = 0x0;
		report->byte1.eventParameter1 = event;
	}
	else {
		report->byte1.mevent = event;
		report->byte1.properties1 = 0x0;
	}
	frame.info.packet.len = sizeof(report->byte1) - 2 + report->byte1.properties1;//don't include sequenceNumber & parameter value by default
	zunoSendZWPackage(&frame.info);
	return (true);
}

int __zuno_CCNotificationReport(byte channel, const ZUNOCommandCmd_t *cmd, ZUNOCommandPacket_t *packet){
	uint32_t							eeprom_mask;
	ZwNotificationInfo_t				info;
	size_t								notificationType;
	size_t								mevent;
	uint32_t							val;
	ZwNotificationReportFrame_t			*report;
	ZwNotificationGetFrame_t			*cmd_get = NULL;

	zunoEEPROMRead(EEPROM_NOTIFICATION_ADDR, EEPROM_NOTIFICATION_SIZE, (byte*)&eeprom_mask);// Load report mask from EEPROM
	if(cmd == NULL){
		// If it's unsolicited report we have to check if it was turned on by user
		if((eeprom_mask & (1UL << channel)) == 0)// Unsolicited => doesn't have incoming package
			return (ZUNO_COMMAND_BLOCKED); // User don't want this report => don't send it
	}
	report = (ZwNotificationReportFrame_t *)&packet->packet.cmd[0x0];
	packet->packet.len = sizeof(report->byte1) - 2;//don't include sequenceNumber & parameter value by default
	memset(report, 0, sizeof(report->byte1));// Initially till the report data with zeros
	_get_info(channel, &info);
	if (info.extend == true) {
		if (cmd == NULL)
			return (ZUNO_COMMAND_BLOCKED);
		if (cmd->len < 0x5)
			return (ZUNO_COMMAND_BLOCKED);
		cmd_get = (ZwNotificationGetFrame_t*)cmd->cmd;
		mevent = cmd_get->mevent;
		if (mevent >= (sizeof(info.mask) * 8) || (info.mask & (0x1 << mevent)) == 0x0)
			mevent = ~mevent;
		info.event = mevent;
	}
	if(cmd != NULL) {
		cmd_get = (ZwNotificationGetFrame_t*)cmd->cmd;
		if(cmd->len >= 4 && (notificationType = cmd_get->notificationType) != info.type && (notificationType != 0xFF))
			return (ZUNO_COMMAND_BLOCKED);// We don't support this request
		if(cmd_get->v1AlarmType == 0xFF)// Fix the "wildcard" param
			report->byte1.mevent = 0xFE;
	}
	mevent = 0x0;
	report->byte1.cmdClass = COMMAND_CLASS_NOTIFICATION;
	report->byte1.cmd = NOTIFICATION_REPORT;
	if(report->byte1.mevent != 0xFE) {
		report->byte1.notificationStatus = (eeprom_mask & (1UL << channel)) ? NOTIFICATION_ON_VALUE : NOTIFICATION_OFF_VALUE;
		report->byte1.notificationType = info.type;
		if (info.extend == false)
			val = zuno_universalGetter1P(channel);
		else
			val = zuno_universalGetter2P(channel, info.event);
		uint8_t  param = val  & 0xFF;

		#ifdef LOGGING_DBG
		LOGGING_UART.print("*** Notification V:");
		LOGGING_UART.print(val, HEX);
		LOGGING_UART.print(" T:");
		LOGGING_UART.println(param, HEX);
		#endif
		// For window/door sensor we have special values => process this case
		if (info.event == NOTIFICATION_EVENT_WINDOW_DOOR_OPENED){
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
					packet->packet.len = packet->packet.len + 0x1;
				}
				mevent = info.event;
			} else {
				mevent = NOTIFICATION_OFF_VALUE;
			}
			if (cmd != NULL && cmd->len >= 5) {
				cmd_get = (ZwNotificationGetFrame_t*)cmd->cmd;
				if (cmd_get->mevent != info.event){
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
	ZwNotificationInfo_t		info;

	_get_info(channel, &info);
	if(cmd->notificationType != info.type)
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
	ZwNotificationInfo_t						info;

	_get_info(channel, &info);
	report = (ZwNotificationSupportedReportFrame_t *)frame_report->info.packet.cmd;
	// report->cmdClass = COMMAND_CLASS_NOTIFICATION; set in - fillOutgoingPacket
	// report->cmd = NOTIFICATION_SUPPORTED_REPORT; set in - fillOutgoingPacket
	report->properties1 = ((NOTIFICATION_TYPE_MAX >> 3) + 1);
	frame_report->info.packet.len = sizeof(ZwNotificationSupportedReportFrame_t) + report->properties1;
	memset(&report->bitMask[0], 0x0, ((NOTIFICATION_TYPE_MAX >> 3) + 1));
	zunoSetupBitMask(&report->bitMask[0], info.type, report->properties1);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _supported_get_even(size_t channel, ZwEventSupportedGetFrame_t *cmd,ZUNOCommandPacketReport_t *frame_report) {
	ZwEventSupportedReportFrame_t						*report;
	size_t												notificationType;
	size_t												sz;
	ZwNotificationInfo_t								info;

	_get_info(channel, &info);
	report = (ZwEventSupportedReportFrame_t *)frame_report->info.packet.cmd;
	// report->cmdClass = COMMAND_CLASS_NOTIFICATION; set in - fillOutgoingPacket
	// report->cmd = EVENT_SUPPORTED_REPORT; set in - fillOutgoingPacket
	notificationType = cmd->notificationType;
	report->notificationType = notificationType;
	if(notificationType != info.type || notificationType == 0xFF) {
		report->properties1 = 0x0;
		frame_report->info.packet.len = sizeof(ZwEventSupportedReportFrame_t);
		return (ZUNO_COMMAND_ANSWERED);// We don't support this request
	}
	sz = sizeof(info.mask);
	report->properties1 = sz;
	frame_report->info.packet.len = sizeof(ZwEventSupportedReportFrame_t) + sz;
	memset(&report->bitMask[0], 0x0, sz);
	if (info.extend == true)
		memcpy(&report->bitMask[0], &info.mask, sz);
	else {
		zunoSetupBitMask(&report->bitMask[0], info.event, sz);
		if(notificationType == NOTIFICATION_TYPE_ACCESS_CONTROL_ALARM){
			// In this case we have to add another one event
			// For window/door sensor we have special values => process this case
			zunoSetupBitMask(&report->bitMask[0], NOTIFICATION_EVENT_WINDOW_DOOR_CLOSED, sz);
		}
	}
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCNotificationHandler(byte channel, const ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report){
	int										rs;

	switch(ZW_CMD) {
		case NOTIFICATION_GET:
			_zunoMarkChannelRequested(channel);
			rs = __zuno_CCNotificationReport(channel, cmd, &frame_report->info);
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
	ZwNotificationInfo_t			info;

	_get_info(channel, &info);
	notificationType = info.type;
	icon_type = ICON_TYPE_GENERIC_SENSOR_NOTIFICATION;
	if (notificationType <= (ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_LAST - ICON_TYPE_GENERIC_SENSOR_NOTIFICATION))
		icon_type = icon_type + notificationType;
	icon->installerIconType = icon_type;
	icon->userIconType = icon_type;
}

#include "ZWCCAssociation.h"

void zuno_CCNotificationGetProfile(uint8_t channel, ZwAssociationInfoOut_t *agi) {
	ZwNotificationInfo_t			info;

	_get_info(channel, &info);
	agi->profile1 = COMMAND_CLASS_NOTIFICATION;
	agi->profile2 = info.type;
}
