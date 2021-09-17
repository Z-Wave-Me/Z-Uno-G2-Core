#ifndef NOTIFICATION_CC_H
#define NOTIFICATION_CC_H

#include "Arduino.h"

#define NOTIFICATION_PROPERTIES_PARAMLENGTH_MASK	0x1F

/* Notification command class commands */
#define NOTIFICATION_VERSION                                                          0x08
#define NOTIFICATION_GET                                                              0x04
#define NOTIFICATION_REPORT                                                           0x05
#define NOTIFICATION_SET                                                              0x06
#define NOTIFICATION_SUPPORTED_GET                                                    0x07
#define NOTIFICATION_SUPPORTED_REPORT                                                 0x08
#define EVENT_SUPPORTED_GET                                                           0x01
#define EVENT_SUPPORTED_REPORT                                                        0x02

/* Values used for Notification Supported Report command */
#define NOTIFICATION_SUPPORTED_REPORT_PROPERTIES1_NUMBER_OF_BIT_MASKS_MASK               0x1F
#define NOTIFICATION_SUPPORTED_REPORT_PROPERTIES1_RESERVED_MASK                          0x60
#define NOTIFICATION_SUPPORTED_REPORT_PROPERTIES1_RESERVED_SHIFT                         0x05
#define NOTIFICATION_SUPPORTED_REPORT_PROPERTIES1_V1_ALARM_BIT_MASK                      0x80

// TYPES
#define NOTIFICATION_TYPE_SMOKE_ALARM					0x01
#define NOTIFICATION_TYPE_CO_ALARM 						0x02
#define NOTIFICATION_TYPE_CO2_ALARM						0x03
#define NOTIFICATION_TYPE_HEAT_ALARM					0x04
#define NOTIFICATION_TYPE_WATER_ALARM 					0x05
#define NOTIFICATION_TYPE_ACCESS_CONTROL_ALARM			0x06
#define NOTIFICATION_TYPE_BURGLAR_ALARM					0x07
#define NOTIFICATION_TYPE_POWER_MANAGEMENT_ALARM		0x08
#define NOTIFICATION_TYPE_SYSTEM_ALARM 					0x09
#define NOTIFICATION_TYPE_EMERGENCY_ALARM				0x0a
#define NOTIFICATION_TYPE_CLOCK_ALARM					0x0b
#define NOTIFICATION_TYPE_APPLIANCE_ALARM				0x0c
#define NOTIFICATION_TYPE_HOME_HEALTH					0x0d
#define NOTIFICATION_TYPE_SIREN							0x0e
#define NOTIFICATION_TYPE_WATER_VALVE					0x0f
#define NOTIFICATION_TYPE_WEATHER_ALAR					0x10
#define NOTIFICATION_TYPE_IRRIGATION					0x11
#define NOTIFICATION_TYPE_GAS_ALARM						0x12
#define NOTIFICATION_TYPE_MAX							0x12

/*
#define NOTIFICATION_SET_HOME_HEALTH_V7                                                  0x0D
#define NOTIFICATION_SET_SIREN_V7                                                        0x0E
#define NOTIFICATION_SET_WATER_VALVE_V7                                                  0x0F
#define NOTIFICATION_SET_WEATHER_ALARM_V7                                                0x10
#define NOTIFICATION_SET_IRRIGATION_V7                                                   0x11
#define NOTIFICATION_SET_GAS_ALARM_V7                                                    0x12
*/
#define NOTIFICATION_ON_VALUE							0xff
#define NOTIFICATION_OFF_VALUE							0x00
//Notification events (UL=Unknown Location)
#define NOTIFICATION_UNKNOWN_EVENT						0xfe
//Smoke
#define NOTIFICATION_EVENT_SMOKE						0x01
#define NOTIFICATION_EVENT_SMOKE_UL						0x02
#define NOTIFICATION_EVENT_SMOKE_TEST					0x03
//CO
#define NOTIFICATION_EVENT_CO							0x01
#define NOTIFICATION_EVENT_CO_UL						0x02
#define NOTIFICATION_EVENT_CO_TEST						0x03
//CO2
#define NOTIFICATION_EVENT_CO2							0x01
#define NOTIFICATION_EVENT_CO2_UL						0x02
//HEAT
#define NOTIFICATION_EVENT_OVERHEAT						0x01
#define NOTIFICATION_EVENT_OVERHEAT_UL					0x02
#define NOTIFICATION_EVENT_TEMP_RISE					0x03
#define NOTIFICATION_EVENT_TEMP_RISE_UL					0x04
#define NOTIFICATION_EVENT_UNDERHEAT					0x05
#define NOTIFICATION_EVENT_UNDERHEAT_UL					0x06
//WATER
#define NOTIFICATION_EVENT_WATER_LEAK					0x01
#define NOTIFICATION_EVENT_WATER_LEAK_UL				0x02
#define NOTIFICATION_EVENT_WATER_LEVEL_DROP				0x03
#define NOTIFICATION_EVENT_WATER_LEVEL_DROP_UL			0x04
//ACCESS
#define NOTIFICATION_EVENT_MANUAL_LOCK					0x01
#define NOTIFICATION_EVENT_MANUAL_UNLOCK				0x02
#define NOTIFICATION_EVENT_MANUAL_NOT_FULLY_LOCKED		0x07
#define NOTIFICATION_EVENT_RF_LOCK						0x03
#define NOTIFICATION_EVENT_RF_UNLOCK					0x04
#define NOTIFICATION_EVENT_RF_NOT_FULLY_LOCKED			0x08
#define NOTIFICATION_EVENT_KEYPAD_LOCK					0x05
#define NOTIFICATION_EVENT_KEYPAD_UNLOCK				0x06
#define NOTIFICATION_EVENT_AUTO_LOCKED					0x09
#define NOTIFICATION_EVENT_AUTO_LOCK_NOT_FULLY_LOCKED	0x0a
#define NOTIFICATION_EVENT_LOCK_JAMMED					0x0b
#define NOTIFICATION_EVENT_ALL_USER_CODES_DELETED		0x0c
#define NOTIFICATION_EVENT_SINGLE_USER_CODE_DELETED		0x0d
#define NOTIFICATION_EVENT_NEW_USER_CODE_ADDED			0X0e
#define NOTIFICATION_EVENT_NEW_USER_CODE_NOT_ADDED		0x0f
#define NOTIFICATION_EVENT_KEYPAD_TEMPORARY_DISABLE		0x10
#define NOTIFICATION_EVENT_KEYPAD_BUSY					0x11
#define NOTIFICATION_EVENT_NEW_PROGRAM_CODE_ENTERED		0x12
#define NOTIFICATION_EVENT_MANUAL_CODE_EXCEEDS_LIMITS	0x13
#define NOTIFICATION_EVENT_RF_UNLOCK_INVALID_CODE		0x14
#define NOTIFICATION_EVENT_RF_LOCK_INVALID_CODE			0x15
#define NOTIFICATION_EVENT_WINDOW_DOOR_OPENED			0x16
#define NOTIFICATION_EVENT_WINDOW_DOOR_CLOSED			0x17
//BURGLAR, HOME SECURITY
#define NOTIFICATION_EVENT_INTRUSION					0x01
#define NOTIFICATION_EVENT_INTRUSION_UL					0x02
#define NOTIFICATION_EVENT_TAMPER_REMOVED				0x03
#define NOTIFICATION_EVENT_TAMPER_INVALID_CODE			0x04
#define NOTIFICATION_EVENT_GLASS_BREAK					0x05
#define NOTIFICATION_EVENT_GLASS_BREAK_UL				0x06
#define NOTIFICATION_EVENT_MOTION_DETECTION				0x07
#define NOTIFICATION_EVENT_MOTION_DETECTION_UL			0x08
#define NOTIFICATION_EVENT_TAMPER_OBJECTMOVED			0x09

//POWER MANAGEMENT
#define NOTIFICATION_EVENT_POWER_APPLIED				0x01
#define NOTIFICATION_EVENT_AC_DISCONNECTED				0x02
#define NOTIFICATION_EVENT_AC_RECONNECTED				0x03
#define NOTIFICATION_EVENT_SURGE						0x04
#define NOTIFICATION_EVENT_VOLTAGE_DROP					0x05
#define NOTIFICATION_EVENT_OVER_CURRENT					0x06
#define NOTIFICATION_EVENT_OVER_VOLTAGE					0x07
#define NOTIFICATION_EVENT_OVER_LOAD					0x08
#define NOTIFICATION_EVENT_LOAD_ERROR					0x09
#define NOTIFICATION_EVENT_REPLACE_BAT_SOON				0x0a
#define NOTIFICATION_EVENT_REPLACE_BAT_NOW				0x0b
//SYSTEM
#define NOTIFICATION_EVENT_HW_FAIL						0x01
#define NOTIFICATION_EVENT_SW_FAIL						0x02
#define NOTIFICATION_EVENT_HW_FAIL_OEM					0x03
#define NOTIFICATION_EVENT_SW_FAIL_OEM					0x04
//EMERGENCY_ALARM
#define NOTIFICATION_EVENT_CONTACT_POLICE				0x01
#define NOTIFICATION_EVENT_CONTACT_FIREMEN				0x02
#define NOTIFICATION_EVENT_CONTACT_MEDIC				0x03
//CLOCK
#define NOTIFICATION_EVENT_WAKE_UP_ALERT				0x01
#define NOTIFICATION_EVENT_TIMER_ENDED					0x02
// GAS
#define NOTIFICATION_EVENT_GAS_COMBUSTIBLE				0x02
#define NOTIFICATION_EVENT_GAS_TOXIC					0x04

#define NOTIFICATION_EVENT_MAX							0x16

/************************************************************/
/* Notification Set V8 command class structs */             
/************************************************************/
typedef struct								ZwNotificationSetFrame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									notificationType;/**/
	uint8_t									notificationStatus;/**/
}											ZwNotificationSetFrame_t;

/************************************************************/
/* Notification Supported Report  command class structs */
/************************************************************/
typedef struct								ZwNotificationSupportedReportFrame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									properties1;/* masked byte */
	uint8_t									bitMask[];
}											ZwNotificationSupportedReportFrame_t;

/************************************************************/
/* Notification Get command class structs */             
/************************************************************/
typedef struct								ZwNotificationGetFrame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									v1AlarmType;/**/
	uint8_t									notificationType;/**/
	uint8_t									mevent;/**/
}											ZwNotificationGetFrame_t;

/************************************************************/
/* Notification Report command class structs */    
/************************************************************/
typedef struct								ZwNotificationReportByte1Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									v1AlarmType;/**/
	uint8_t									v1AlarmLevel;/**/
	uint8_t									reserved;/**/
	uint8_t									notificationStatus;/**/
	uint8_t									notificationType;/**/
	uint8_t									mevent;/**/
	uint8_t									properties1;/* masked byte */
	uint8_t									eventParameter1;
	uint8_t									sequenceNumber;/**/
}											ZwNotificationReportByte1Frame_t;

typedef struct								ZwNotificationReportByte2Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									v1AlarmType;/**/
	uint8_t									v1AlarmLevel;/**/
	uint8_t									reserved;/**/
	uint8_t									notificationStatus;/**/
	uint8_t									notificationType;/**/
	uint8_t									mevent;/**/
	uint8_t									properties1;/* masked byte */
	uint8_t									eventParameter1;/* MSB */
	uint8_t									eventParameter2;/* LSB */
	uint8_t									sequenceNumber;/**/
}											ZwNotificationReportByte2Frame_t;

typedef struct								ZwNotificationReportByte3Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									v1AlarmType;/**/
	uint8_t									v1AlarmLevel;/**/
	uint8_t									reserved;/**/
	uint8_t									notificationStatus;/**/
	uint8_t									notificationType;/**/
	uint8_t									mevent;/**/
	uint8_t									properties1;/* masked byte */
	uint8_t									eventParameter1;/* MSB */
	uint8_t									eventParameter2;
	uint8_t									eventParameter3;/* LSB */
	uint8_t									sequenceNumber;/**/
}											ZwNotificationReportByte3Frame_t;

typedef struct								ZwNotificationReportByte4Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									v1AlarmType;/**/
	uint8_t									v1AlarmLevel;/**/
	uint8_t									reserved;/**/
	uint8_t									notificationStatus;/**/
	uint8_t									notificationType;/**/
	uint8_t									mevent;/**/
	uint8_t									properties1;/* masked byte */
	uint8_t									eventParameter1;/* MSB */
	uint8_t									eventParameter2;
	uint8_t									eventParameter3;
	uint8_t									eventParameter4;/* LSB */
	uint8_t									sequenceNumber;/**/
}											ZwNotificationReportByte4Frame_t;

typedef union								ZwNotificationReportFrame_u {//For more convenient support, several versions of commands
	ZwNotificationReportByte1Frame_t		byte1;
	ZwNotificationReportByte2Frame_t		byte2;
	ZwNotificationReportByte3Frame_t		byte3;
	ZwNotificationReportByte4Frame_t		byte4;
}											ZwNotificationReportFrame_t;

/************************************************************/
/* Event Supported Get command class structs */          
/************************************************************/
typedef struct								ZwEventSupportedGetFrame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									notificationType;/**/
}											ZwEventSupportedGetFrame_t;

/************************************************************/
/* Event Supported Report command class structs */ 
/************************************************************/
typedef struct								ZwEventSupportedReportFrame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									notificationType;/**/
	uint8_t									properties1;/* masked byte */
	uint8_t									bitMask[];
}											ZwEventSupportedReportFrame_t;

inline void zuno_CCNotificationInitData() {
	uint32_t eeprom_mask = 0xFFFFFFFF; 
	zunoEEPROMWrite(EEPROM_NOTIFICATION_ADDR, EEPROM_NOTIFICATION_SIZE, (byte*)&eeprom_mask);
};

int  zuno_CCNotificationReport(byte channel, ZUNOCommandPacket_t * cmd);
int  zuno_CCNotificationHandler(byte channel, ZUNOCommandPacket_t * cmd);

#endif // NOTIFICATION_CC_H
