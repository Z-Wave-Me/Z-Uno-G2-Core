#ifndef EEPROM_CONFIG_SCHEDULE_ENTRY_LOCK_H
#define EEPROM_CONFIG_SCHEDULE_ENTRY_LOCK_H

#ifdef WITH_CC_SCHEDULE_ENTRY_LOCK

#define SCHEDULE_ENTRY_LOCK_ADDR						((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.schedule_entry_lock)
#define SCHEDULE_ENTRY_LOCK_SIZE						(sizeof(((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.schedule_entry_lock))

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
	ScheduleEntryLockSaveUserId_t		user_id[SCHEDULE_ENTRY_LOCK_NUMBER];
}							ScheduleEntryLockSaveCommon_t;

#endif//WITH_CC_SCHEDULE_ENTRY_LOCK
#endif//EEPROM_CONFIG_SCHEDULE_ENTRY_LOCK_H