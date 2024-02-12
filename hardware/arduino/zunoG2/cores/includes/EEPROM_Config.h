#ifndef EEPROM_CONFIG_H
#define EEPROM_CONFIG_H

#include "Arduino.h"

#define EEPROM_SKETH_ADDR								0x0
#define EEPROM_SKETH_SIZE								0xE00

#ifdef WITH_CC_USER_CREDENTIAL
#define USER_CREDENTIAL_ADDR							((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential)
#define USER_CREDENTIAL_SIZE							(sizeof(((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential))
#endif

#ifdef WITH_CC_SCHEDULE_ENTRY_LOCK
#define SCHEDULE_ENTRY_LOCK_ADDR						((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.schedule_entry_lock)
#define SCHEDULE_ENTRY_LOCK_SIZE						(sizeof(((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.schedule_entry_lock))
#endif

#define EEPROM_USER_CODE_ADDR							((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.user_code[0x0])
#define EEPROM_USER_CODE_SIZE							(sizeof(((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.user_code))

#define EEPROM_NOTIFICATION_ADDR						((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->notification[0x0])
#define EEPROM_NOTIFICATION_SIZE						4
#define EEPROM_WAKEUP_ADDR								((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->wakeup[0x0])
#define EEPROM_WAKEUP_SIZE								4

#ifdef WITH_CC_BASIC
#define EEPROM_BASIC_SAVE_ADDR							((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->basic[0x0])
#define EEPROM_BASIC_SAVE_SIZE							(1 * ZUNO_MAX_MULTI_CHANNEL_NUMBER)
#endif
#if defined(WITH_CC_SWITCH_COLOR)
#define EEPROM_SWITCH_COLOR_SAVE_ADDR					((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->switch_color[0x0])
#define EEPROM_SWITCH_COLOR_SAVE_SIZE					(1 * ZUNO_MAX_MULTI_CHANNEL_NUMBER)
#endif
#if defined(WITH_CC_SOUND_SWITCH)
#define EEPROM_SWITCH_SOUND_SAVE_ADDR					((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->switch_sound[0x0])
#define EEPROM_SWITCH_SOUND_SAVE_SIZE					(3 * ZUNO_MAX_MULTI_CHANNEL_NUMBER)
#endif
#if defined(WITH_CC_CENTRAL_SCENE)
#define EEPROM_CENTRAL_SCENE_SAVE_ADDR					((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->central_scene[0x0])
#define EEPROM_CENTRAL_SCENE_SAVE_SIZE					(1)
#endif

#define EEPROM_USER_CHANNELS_EEPROM_ADDR				((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->zuno_zw_cfg)
#define EEPROM_USER_CHANNELS_EEPROM_SIZE				sizeof(g_zuno_zw_cfg)

// All last
#define EEPROM_CONFIGURATION_ADDR						((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->config_param)
#ifdef CONFIGPARAMETERS_MAX_COUNT
	#define EEPROM_CONFIGURATION_SIZE					(CONFIGPARAMETERS_MAX_COUNT * 0x4)
#else
	#define EEPROM_CONFIGURATION_SIZE					(0x20 * 0x4)
#endif

#define EEPROM_MAX_SIZE									0x1300

#ifdef WITH_CC_SCHEDULE_ENTRY_LOCK
#ifndef SCHEDULE_ENTRY_LOCK_NUMBER
#define SCHEDULE_ENTRY_LOCK_NUMBER											35
#endif

#ifndef SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_WEEK_DAY
#define SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_WEEK_DAY							0x2
#endif

#ifndef SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_YEAR_DAY
#define SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_YEAR_DAY							0x2
#endif

#ifndef SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_DAILY_REPEATING
#define SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_DAILY_REPEATING						0x2
#endif


typedef struct				ScheduleEntryLockSaveUserIdentifierYearDay_s
{
	uint8_t					startYear;
	uint8_t					startMonth;
	uint8_t					startDay;
	uint8_t					startHour;
	uint8_t					startMinute;
	uint8_t					stopYear;
	uint8_t					stopMonth;
	uint8_t					stopDay;
	uint8_t					stopHour;
	uint8_t					stopMinute;
}							ScheduleEntryLockSaveUserIdentifierYearDay_t;

typedef struct				ScheduleEntryLockSaveUserIdentifierWeekDay_s
{
	uint8_t					dayOfWeek;
	uint8_t					startHour;
	uint8_t					startMinute;
	uint8_t					stopHour;
	uint8_t					stopMinute;
}							ScheduleEntryLockSaveUserIdentifierWeekDay_t;

typedef struct				ScheduleEntryLockSaveUserIdentifierDayilyRepeating_s
{
	uint8_t					weekDayBitmask;
	uint8_t					startHour;
	uint8_t					startMinute;
	uint8_t					durationHour;
	uint8_t					durationMinute;
}							ScheduleEntryLockSaveUserIdentifierDayilyRepeating_t;

typedef struct				ScheduleEntryLockSaveUserIdentifierWeekDayMask_s
{
	uint8_t					crc16[0x2];//lsb - Msb
	uint8_t					mask[(((SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_WEEK_DAY + 0x7) & (0x0 - 0x8)) / 0x8)];
}							ScheduleEntryLockSaveUserIdentifierWeekDayMask_t;

typedef struct				ScheduleEntryLockSaveUserIdentifierYearDayMask_s
{
	uint8_t					crc16[0x2];//lsb - Msb
	uint8_t					mask[(((SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_YEAR_DAY + 0x7) & (0x0 - 0x8)) / 0x8)];
}							ScheduleEntryLockSaveUserIdentifierYearDayMask_t;

typedef struct				ScheduleEntryLockSaveUserIdentifierDayilyRepeatingMask_s
{
	uint8_t					crc16[0x2];//lsb - Msb
	uint8_t					mask[(((SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_DAILY_REPEATING + 0x7) & (0x0 - 0x8)) / 0x8)];
}							ScheduleEntryLockSaveUserIdentifierDayilyRepeatingMask_t;

typedef struct				ScheduleEntryLockSaveUserId_s
{
	ScheduleEntryLockSaveUserIdentifierWeekDayMask_t			week_day_mask;
	ScheduleEntryLockSaveUserIdentifierYearDayMask_t			year_day_mask;
	ScheduleEntryLockSaveUserIdentifierDayilyRepeatingMask_t	dayily_repeating_mask;
	ScheduleEntryLockSaveUserIdentifierWeekDay_t			week_day[SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_WEEK_DAY];
	ScheduleEntryLockSaveUserIdentifierYearDay_t			year_day[SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_YEAR_DAY];
	ScheduleEntryLockSaveUserIdentifierDayilyRepeating_t	dayily_repeating[SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_DAILY_REPEATING];
}							ScheduleEntryLockSaveUserId_t;


#define SCHEDULE_ENTRY_LOCK_NUMBER_MASK_LENGHT						0x2

typedef struct				ScheduleEntryLockSaveMask_s
{
	uint8_t					crc16[0x2];//lsb - Msb
	uint8_t					mask[SCHEDULE_ENTRY_LOCK_NUMBER_MASK_LENGHT];
}							ScheduleEntryLockSaveMask_t;

typedef struct						ScheduleEntryLockSaveTimeOffsetInfo_s
{
	uint8_t							level;/* masked byte */
	uint8_t							minuteTzo;/**/
	uint8_t							level2;/* masked byte */
}									ScheduleEntryLockSaveTimeOffsetInfo_t;

typedef struct						ScheduleEntryLockSaveTimeOffset_s
{
	uint8_t							crc16[0x2];//lsb - Msb
	ScheduleEntryLockSaveTimeOffsetInfo_t	info;
}									ScheduleEntryLockSaveTimeOffset_t;

typedef struct				ScheduleEntryLockSaveCommon_s
{
	ScheduleEntryLockSaveTimeOffset_t	time_offset;
	ScheduleEntryLockSaveMask_t			user_id_mask[((((SCHEDULE_ENTRY_LOCK_NUMBER + ((SCHEDULE_ENTRY_LOCK_NUMBER_MASK_LENGHT * 0x8) - 0x1)) & (0x0 - (SCHEDULE_ENTRY_LOCK_NUMBER_MASK_LENGHT * 0x8))) / (SCHEDULE_ENTRY_LOCK_NUMBER_MASK_LENGHT * 0x8)))];
	ScheduleEntryLockSaveUserId_t		user_id[SCHEDULE_ENTRY_LOCK_NUMBER];
}							ScheduleEntryLockSaveCommon_t;

#endif//WITH_CC_SCHEDULE_ENTRY_LOCK

#include "EEPROM_ConfigUserCode.h"
#include "EEPROM_ConfigUserCredential.h"

typedef struct									ZwEepromSkethCommonInfo_s
{
	#ifdef WITH_CC_USER_CREDENTIAL
	UserCredentialSaveCommon_t					user_credential;
	#endif
	#if !defined(WITH_CC_USER_CREDENTIAL) && defined(WITH_CC_USER_CODE)
	UserCodeSaveCommon_t						user_code;
	#endif
	#ifdef WITH_CC_SCHEDULE_ENTRY_LOCK
	ScheduleEntryLockSaveCommon_t				schedule_entry_lock;
	#endif
}												ZwEepromSkethCommonInfo_t;

typedef struct									ZwEepromSkethCommon_s
{
	uint8_t										user_code[EEPROM_SKETH_SIZE - sizeof(ZwEepromSkethCommonInfo_t)];
	ZwEepromSkethCommonInfo_t					info;
}												ZwEepromSkethCommon_t;

typedef struct									ZwEepromSkethConfigParam_s
{
	uint8_t										config_param[EEPROM_CONFIGURATION_SIZE];
} __attribute__((aligned(0x100),packed))		ZwEepromSkethConfigParam_t;

typedef struct									ZwEepromSketh_s
{
	ZwEepromSkethCommon_t						common;
	uint8_t										notification[EEPROM_NOTIFICATION_SIZE];
	uint8_t										wakeup[EEPROM_WAKEUP_SIZE];
	#if defined(WITH_CC_BASIC)
	uint8_t										basic[EEPROM_BASIC_SAVE_SIZE];
	#endif
	#if defined(WITH_CC_SWITCH_COLOR)
	uint8_t										switch_color[EEPROM_SWITCH_COLOR_SAVE_SIZE];
	#endif
	#if defined(WITH_CC_SOUND_SWITCH)
	uint8_t										switch_sound[EEPROM_SWITCH_SOUND_SAVE_SIZE];
	#endif
	#if defined(WITH_CC_CENTRAL_SCENE)
	uint8_t										central_scene[EEPROM_CENTRAL_SCENE_SAVE_SIZE];
	#endif
	ZUNOZWConfiguation_t						zuno_zw_cfg;
	ZwEepromSkethConfigParam_t					config_param;
}												ZwEepromSketh_t;


inline int zunoEEPROMWrite(word address, word size, byte * data) {return (int)zunoSysCall(ZUNO_SYSFUNC_EEPROM_IO, 4, true, address, size, data);};
inline int zunoEEPROMRead(word address, word size, byte * data) {return (int)zunoSysCall(ZUNO_SYSFUNC_EEPROM_IO, 4, false, address, size, data);};
inline int zunoEEPROMErase(void) {return (int)zunoSysCall(ZUNO_SYSFUNC_EEPROM_ERASE, 1, 0xCAFE0ACE);};

#endif//EEPROM_CONFIG_H