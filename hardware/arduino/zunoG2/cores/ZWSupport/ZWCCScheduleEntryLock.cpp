#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCScheduleEntryLock.h"
#include "CrcClass.h"

#if defined(WITH_CC_SCHEDULE_ENTRY_LOCK)

static_assert(SCHEDULE_ENTRY_LOCK_NUMBER != 0x0, "SCHEDULE_ENTRY_LOCK_NUMBER - minimum one!!!");

static_assert(SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_WEEK_DAY <= 0xFF, "SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_WEEK_DAY - overflow!!!");
static_assert(SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_YEAR_DAY <= 0xFF, "SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_YEAR_DAY - overflow!!!");
static_assert(SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_DAILY_REPEATING <= 0xFF, "SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_DAILY_REPEATING - overflow!!!");

static_assert(SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_WEEK_DAY > 0x0 || SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_YEAR_DAY > 0x0 || SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_DAILY_REPEATING > 0x0, "SCHEDULE_ENTRY_LOCK - minimum one slot!!!");

#define SCHEDULE_ENTRY_LOCK_ADDR_TIME_OFFSET		(SCHEDULE_ENTRY_LOCK_ADDR)
#define SCHEDULE_ENTRY_LOCK_ADDR_COMMON				(SCHEDULE_ENTRY_LOCK_ADDR_TIME_OFFSET + sizeof(ScheduleEntryLockSaveTimeOffset_t))

typedef struct _ZW_SCHEDULE_ENTRY_TYPE_SUPPORTED_REPORT_V3_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   numberOfSlotsWeekDay;         /**/
    uint8_t   numberOfSlotsYearDay;         /**/
    uint8_t   numberOfSlotsDailyRepeating;  /**/
} ZW_SCHEDULE_ENTRY_TYPE_SUPPORTED_REPORT_V3_FRAME;

typedef struct					ScheduleEntryLockV3SlotInfoPre_s
{
	uint8_t						userIdentifier;/**/
	uint8_t						scheduleSlotId;/**/
}								ScheduleEntryLockV3SlotInfoPre_t;

typedef struct					ScheduleEntryLockV3GetSlotInfo_s
{
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	ScheduleEntryLockV3SlotInfoPre_t	pre;
}								ScheduleEntryLockV3GetSlotInfo_t;

typedef struct					ScheduleEntryLockV3GetSlotInfoReport_s
{
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	ScheduleEntryLockV3SlotInfoPre_t	pre;
	uint8_t						data[];
}								ScheduleEntryLockV3GetSlotInfoReport_t;

typedef struct					ScheduleEntryLockV4SlotInfoPre_s
{
	uint8_t						userIdentifier[0x2];/*MSB - LSB*/
	uint8_t						scheduleSlotId;/**/
}								ScheduleEntryLockV4SlotInfoPre_t;

typedef struct					ScheduleEntryLockV4GetSlotInfo_s
{
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	ScheduleEntryLockV4SlotInfoPre_t	pre;
}								ScheduleEntryLockV4GetSlotInfo_t;

typedef struct					ScheduleEntryLockV4GetSlotInfoReport_s
{
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	ScheduleEntryLockV4SlotInfoPre_t	pre;
	uint8_t						data[];
}								ScheduleEntryLockV4GetSlotInfoReport_t;

static int _schedule_entry_type_supported_report(ZUNOCommandPacketReport_t *frame_report) {
	ZW_SCHEDULE_ENTRY_TYPE_SUPPORTED_REPORT_V3_FRAME				*report;

	report = (ZW_SCHEDULE_ENTRY_TYPE_SUPPORTED_REPORT_V3_FRAME *)frame_report->packet.cmd;
	// report->cmdClass = COMMAND_CLASS_SCHEDULE_ENTRY_LOCK; set in - fillOutgoingPacket
	// report->cmd = SCHEDULE_ENTRY_TYPE_SUPPORTED_REPORT; set in - fillOutgoingPacket
	report->numberOfSlotsWeekDay = SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_WEEK_DAY;
	report->numberOfSlotsYearDay = SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_YEAR_DAY;
	report->numberOfSlotsDailyRepeating = SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_DAILY_REPEATING;
	frame_report->packet.len = sizeof(report[0x0]);
	return (ZUNO_COMMAND_ANSWERED);
}

static uint16_t _schedule_entry_lock_test_common_slot_info_v3(const ScheduleEntryLockV3SlotInfoPre_t *pre, uint8_t slot_id_max) {
	uint16_t									userIdentifier;
	uint8_t										scheduleSlotId;

	if ((userIdentifier = pre->userIdentifier) > SCHEDULE_ENTRY_LOCK_NUMBER)
		return (0x0);
	if ((scheduleSlotId = pre->scheduleSlotId) > slot_id_max || scheduleSlotId == 0x0)
		return (0x0);
	return (userIdentifier);
}

static uint16_t _schedule_entry_lock_test_common_slot_info_v4(const ScheduleEntryLockV4SlotInfoPre_t *pre, uint8_t slot_id_max) {
	uint16_t									userIdentifier;
	uint8_t										scheduleSlotId;

	if ((userIdentifier = ((pre->userIdentifier[0x0] << 0x8) | pre->userIdentifier[0x1])) > SCHEDULE_ENTRY_LOCK_NUMBER)
		return (0x0);
	if ((scheduleSlotId = pre->scheduleSlotId) > slot_id_max || scheduleSlotId == 0x0)
		return (0x0);
	return (userIdentifier);
}

static uint16_t _schedule_entry_lock_test_get_slot_info_v3(const ScheduleEntryLockV3GetSlotInfo_t *in, ScheduleEntryLockV3GetSlotInfoReport_t *report, uint8_t slot_id_max) {
	uint16_t									userIdentifier;

	if ((userIdentifier = _schedule_entry_lock_test_common_slot_info_v3(&in->pre, slot_id_max)) == 0x0)
		return (0x0);
	report->pre = in->pre;
	return (userIdentifier);
}

static uint16_t _schedule_entry_lock_test_get_slot_info_v4(const ScheduleEntryLockV4GetSlotInfo_t *in, ScheduleEntryLockV4GetSlotInfoReport_t *report, uint8_t slot_id_max) {
	uint16_t									userIdentifier;

	if ((userIdentifier = _schedule_entry_lock_test_common_slot_info_v4(&in->pre, slot_id_max)) == 0x0)
		return (0x0);
	report->pre = in->pre;
	return (userIdentifier);
}

static void _schedule_entry_lock_week_day_get(uint16_t userIdentifier, uint8_t scheduleSlotId, ScheduleEntryLockSaveUserIdentifierWeekDay_t *report_week_day) {
	const ScheduleEntryLockSaveUserId_t							*user_id;
	ScheduleEntryLockSaveUserIdentifierWeekDayMask_t			week_day_mask;
	uint32_t													addr;
	size_t														offset;
	uint16_t													crc16;

	userIdentifier--;
	offset = userIdentifier / (SCHEDULE_ENTRY_LOCK_NUMBER_MASK_LENGHT * 0x8);
	addr = (SCHEDULE_ENTRY_LOCK_ADDR_COMMON) + (offset * sizeof(ScheduleEntryLockSaveMask_t)) + (offset * ((SCHEDULE_ENTRY_LOCK_NUMBER_MASK_LENGHT * 0x8) * sizeof(ScheduleEntryLockSaveUserId_t)));
	user_id = (const ScheduleEntryLockSaveUserId_t *)(addr + sizeof(ScheduleEntryLockSaveMask_t));
	addr = (uint32_t)&user_id[userIdentifier % (SCHEDULE_ENTRY_LOCK_NUMBER_MASK_LENGHT * 0x8)].week_day_mask;
	zunoEEPROMRead(addr, sizeof(week_day_mask), (byte *)&week_day_mask);
	crc16 = CrcClass::crc16_ccitt_aug(&week_day_mask.mask[0x0], sizeof(week_day_mask.mask));
	scheduleSlotId--;
	if (memcmp(&crc16, &week_day_mask.crc16[0x0], sizeof(crc16)) != 0x0 || (week_day_mask.mask[scheduleSlotId / 0x8] & (0x1 << (scheduleSlotId % 8))) == 0x0) {
		memset(report_week_day, 0xFF, sizeof(report_week_day[0x0]));
		return ;
	}
	addr = (uint32_t)&user_id[userIdentifier % (SCHEDULE_ENTRY_LOCK_NUMBER_MASK_LENGHT * 0x8)].week_day[scheduleSlotId];
	zunoEEPROMRead(addr, sizeof(report_week_day[0x0]), (byte *)report_week_day);
}

static int _schedule_entry_lock_week_day_report(const ScheduleEntryLockV3GetSlotInfo_t *in, ZUNOCommandPacketReport_t *frame_report) {
	uint16_t														userIdentifier;
	ScheduleEntryLockV3GetSlotInfoReport_t							*report;
	ScheduleEntryLockSaveUserIdentifierWeekDay_t					*report_week_day;

	report = (ScheduleEntryLockV3GetSlotInfoReport_t *)frame_report->packet.cmd;
	if ((userIdentifier = _schedule_entry_lock_test_get_slot_info_v3(in, report, SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_WEEK_DAY)) == 0x0)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	// report->cmdClass = COMMAND_CLASS_SCHEDULE_ENTRY_LOCK; set in - fillOutgoingPacket
	// report->cmd = SCHEDULE_ENTRY_LOCK_WEEK_DAY_REPORT; set in - fillOutgoingPacket
	report_week_day = (ScheduleEntryLockSaveUserIdentifierWeekDay_t *)&report->data[0x0];
	_schedule_entry_lock_week_day_get(userIdentifier, in->pre.scheduleSlotId, report_week_day);
	frame_report->packet.len = sizeof(report[0x0]) + sizeof(report_week_day[0x0]);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _extended_schedule_entry_lock_week_day_report(const ScheduleEntryLockV4GetSlotInfo_t *in, ZUNOCommandPacketReport_t *frame_report) {
	uint16_t														userIdentifier;
	ScheduleEntryLockV4GetSlotInfoReport_t							*report;
	ScheduleEntryLockSaveUserIdentifierWeekDay_t					*report_week_day;

	report = (ScheduleEntryLockV4GetSlotInfoReport_t *)frame_report->packet.cmd;
	if ((userIdentifier = _schedule_entry_lock_test_get_slot_info_v4(in, report, SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_WEEK_DAY)) == 0x0)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	// report->cmdClass = COMMAND_CLASS_SCHEDULE_ENTRY_LOCK; set in - fillOutgoingPacket
	// report->cmd = EXTENDED_SCHEDULE_ENTRY_LOCK_WEEK_DAY_SCHEDULE_REPORT; set in - fillOutgoingPacket
	report_week_day = (ScheduleEntryLockSaveUserIdentifierWeekDay_t *)&report->data[0x0];
	_schedule_entry_lock_week_day_get(userIdentifier, in->pre.scheduleSlotId, report_week_day);
	frame_report->packet.len = sizeof(report[0x0]) + sizeof(report_week_day[0x0]);
	return (ZUNO_COMMAND_ANSWERED);
}

static void _schedule_entry_lock_year_day_get(uint16_t userIdentifier, uint8_t scheduleSlotId, ScheduleEntryLockSaveUserIdentifierYearDay_t *report_year_day) {
	const ScheduleEntryLockSaveUserId_t							*user_id;
	ScheduleEntryLockSaveUserIdentifierYearDayMask_t			year_day_mask;
	uint32_t													addr;
	size_t														offset;
	uint16_t													crc16;

	userIdentifier--;
	offset = userIdentifier / (SCHEDULE_ENTRY_LOCK_NUMBER_MASK_LENGHT * 0x8);
	addr = (SCHEDULE_ENTRY_LOCK_ADDR_COMMON) + (offset * sizeof(ScheduleEntryLockSaveMask_t)) + (offset * ((SCHEDULE_ENTRY_LOCK_NUMBER_MASK_LENGHT * 0x8) * sizeof(ScheduleEntryLockSaveUserId_t)));
	user_id = (const ScheduleEntryLockSaveUserId_t *)(addr + sizeof(ScheduleEntryLockSaveMask_t));
	addr = (uint32_t)&user_id[userIdentifier % (SCHEDULE_ENTRY_LOCK_NUMBER_MASK_LENGHT * 0x8)].year_day_mask;
	zunoEEPROMRead(addr, sizeof(year_day_mask), (byte *)&year_day_mask);
	crc16 = CrcClass::crc16_ccitt_aug(&year_day_mask.mask[0x0], sizeof(year_day_mask.mask));
	scheduleSlotId--;
	if (memcmp(&crc16, &year_day_mask.crc16[0x0], sizeof(crc16)) != 0x0 || (year_day_mask.mask[scheduleSlotId / 0x8] & (0x1 << (scheduleSlotId % 8))) == 0x0) {
		memset(report_year_day, 0xFF, sizeof(report_year_day[0x0]));
		return ;
	}
	addr = (uint32_t)&user_id[userIdentifier % (SCHEDULE_ENTRY_LOCK_NUMBER_MASK_LENGHT * 0x8)].year_day[scheduleSlotId];
	zunoEEPROMRead(addr, sizeof(report_year_day[0x0]), (byte *)report_year_day);
}

static int _schedule_entry_lock_year_day_report(const ScheduleEntryLockV3GetSlotInfo_t *in, ZUNOCommandPacketReport_t *frame_report) {
	uint16_t														userIdentifier;
	ScheduleEntryLockV3GetSlotInfoReport_t							*report;
	ScheduleEntryLockSaveUserIdentifierYearDay_t					*report_year_day;

	report = (ScheduleEntryLockV3GetSlotInfoReport_t *)frame_report->packet.cmd;
	if ((userIdentifier = _schedule_entry_lock_test_get_slot_info_v3(in, report, SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_YEAR_DAY)) == 0x0)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	// report->cmdClass = COMMAND_CLASS_SCHEDULE_ENTRY_LOCK; set in - fillOutgoingPacket
	// report->cmd = SCHEDULE_ENTRY_LOCK_YEAR_DAY_REPORT; set in - fillOutgoingPacket
	report_year_day = (ScheduleEntryLockSaveUserIdentifierYearDay_t *)&report->data[0x0];
	_schedule_entry_lock_year_day_get(userIdentifier, in->pre.scheduleSlotId, report_year_day);
	frame_report->packet.len = sizeof(report[0x0]) + sizeof(report_year_day[0x0]);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _extended_schedule_entry_lock_year_day_report(const ScheduleEntryLockV4GetSlotInfo_t *in, ZUNOCommandPacketReport_t *frame_report) {
	uint16_t														userIdentifier;
	ScheduleEntryLockV4GetSlotInfoReport_t							*report;
	ScheduleEntryLockSaveUserIdentifierYearDay_t					*report_year_day;

	report = (ScheduleEntryLockV4GetSlotInfoReport_t *)frame_report->packet.cmd;
	if ((userIdentifier = _schedule_entry_lock_test_get_slot_info_v4(in, report, SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_YEAR_DAY)) == 0x0)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	// report->cmdClass = COMMAND_CLASS_SCHEDULE_ENTRY_LOCK; set in - fillOutgoingPacket
	// report->cmd = EXTENDED_SCHEDULE_ENTRY_LOCK_YEAR_DAY_SCHEDULE_REPORT; set in - fillOutgoingPacket
	report_year_day = (ScheduleEntryLockSaveUserIdentifierYearDay_t *)&report->data[0x0];
	_schedule_entry_lock_year_day_get(userIdentifier, in->pre.scheduleSlotId, report_year_day);
	frame_report->packet.len = sizeof(report[0x0]) + sizeof(report_year_day[0x0]);
	return (ZUNO_COMMAND_ANSWERED);
}

static void _schedule_entry_lock_daily_repeating_get(uint16_t userIdentifier, uint8_t scheduleSlotId, ScheduleEntryLockSaveUserIdentifierDayilyRepeating_t *report_daily_repeating) {
	const ScheduleEntryLockSaveUserId_t							*user_id;
	ScheduleEntryLockSaveUserIdentifierDayilyRepeatingMask_t	dayily_repeating_mask;
	uint32_t													addr;
	size_t														offset;
	uint16_t													crc16;

	userIdentifier--;
	offset = userIdentifier / (SCHEDULE_ENTRY_LOCK_NUMBER_MASK_LENGHT * 0x8);
	addr = (SCHEDULE_ENTRY_LOCK_ADDR_COMMON) + (offset * sizeof(ScheduleEntryLockSaveMask_t)) + (offset * ((SCHEDULE_ENTRY_LOCK_NUMBER_MASK_LENGHT * 0x8) * sizeof(ScheduleEntryLockSaveUserId_t)));
	user_id = (const ScheduleEntryLockSaveUserId_t *)(addr + sizeof(ScheduleEntryLockSaveMask_t));
	addr = (uint32_t)&user_id[userIdentifier % (SCHEDULE_ENTRY_LOCK_NUMBER_MASK_LENGHT * 0x8)].dayily_repeating_mask;
	zunoEEPROMRead(addr, sizeof(dayily_repeating_mask), (byte *)&dayily_repeating_mask);
	crc16 = CrcClass::crc16_ccitt_aug(&dayily_repeating_mask.mask[0x0], sizeof(dayily_repeating_mask.mask));
	scheduleSlotId--;
	if (memcmp(&crc16, &dayily_repeating_mask.crc16[0x0], sizeof(crc16)) != 0x0 || (dayily_repeating_mask.mask[scheduleSlotId / 0x8] & (0x1 << (scheduleSlotId % 8))) == 0x0) {
		memset(report_daily_repeating, 0xFF, sizeof(report_daily_repeating[0x0]));
		return ;
	}
	addr = (uint32_t)&user_id[userIdentifier % (SCHEDULE_ENTRY_LOCK_NUMBER_MASK_LENGHT * 0x8)].dayily_repeating[scheduleSlotId];
	zunoEEPROMRead(addr, sizeof(report_daily_repeating[0x0]), (byte *)report_daily_repeating);
}

static int _schedule_entry_lock_daily_repeating_report(const ScheduleEntryLockV3GetSlotInfo_t *in, ZUNOCommandPacketReport_t *frame_report) {
	uint16_t														userIdentifier;
	ScheduleEntryLockV3GetSlotInfoReport_t							*report;
	ScheduleEntryLockSaveUserIdentifierDayilyRepeating_t			*report_daily_repeating;

	report = (ScheduleEntryLockV3GetSlotInfoReport_t *)frame_report->packet.cmd;
	if ((userIdentifier = _schedule_entry_lock_test_get_slot_info_v3(in, report, SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_DAILY_REPEATING)) == 0x0)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	// report->cmdClass = COMMAND_CLASS_SCHEDULE_ENTRY_LOCK; set in - fillOutgoingPacket
	// report->cmd = SCHEDULE_ENTRY_LOCK_DAILY_REPEATING_REPORT; set in - fillOutgoingPacket
	report_daily_repeating = (ScheduleEntryLockSaveUserIdentifierDayilyRepeating_t *)&report->data[0x0];
	_schedule_entry_lock_daily_repeating_get(userIdentifier, in->pre.scheduleSlotId, report_daily_repeating);
	frame_report->packet.len = sizeof(report[0x0]) + sizeof(report_daily_repeating[0x0]);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _extended_schedule_entry_lock_daily_repeating_report(const ScheduleEntryLockV4GetSlotInfo_t *in, ZUNOCommandPacketReport_t *frame_report) {
	uint16_t														userIdentifier;
	ScheduleEntryLockV4GetSlotInfoReport_t							*report;
	ScheduleEntryLockSaveUserIdentifierDayilyRepeating_t			*report_daily_repeating;

	report = (ScheduleEntryLockV4GetSlotInfoReport_t *)frame_report->packet.cmd;
	if ((userIdentifier = _schedule_entry_lock_test_get_slot_info_v4(in, report, SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_DAILY_REPEATING)) == 0x0)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	// report->cmdClass = COMMAND_CLASS_SCHEDULE_ENTRY_LOCK; set in - fillOutgoingPacket
	// report->cmd = EXTENDED_SCHEDULE_ENTRY_LOCK_DAILY_REPEATING_REPORT; set in - fillOutgoingPacket
	report_daily_repeating = (ScheduleEntryLockSaveUserIdentifierDayilyRepeating_t *)&report->data[0x0];
	_schedule_entry_lock_daily_repeating_get(userIdentifier, in->pre.scheduleSlotId, report_daily_repeating);
	frame_report->packet.len = sizeof(report[0x0]) + sizeof(report_daily_repeating[0x0]);
	return (ZUNO_COMMAND_ANSWERED);
}

typedef struct					ScheduleEntryLockTimeOffsetReport_s
{
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	ScheduleEntryLockSaveTimeOffsetInfo_t	info;
}								ScheduleEntryLockTimeOffsetReport_t;

static int _schedule_entry_lock_time_offset_report(ZUNOCommandPacketReport_t *frame_report) {
	ScheduleEntryLockTimeOffsetReport_t							*report;
	uint16_t													crc16;
	ScheduleEntryLockSaveTimeOffset_t							time_offset;

	report = (ScheduleEntryLockTimeOffsetReport_t *)frame_report->packet.cmd;
	// report->cmdClass = COMMAND_CLASS_SCHEDULE_ENTRY_LOCK; set in - fillOutgoingPacket
	// report->cmd = SCHEDULE_ENTRY_LOCK_TIME_OFFSET_REPORT; set in - fillOutgoingPacket
	zunoEEPROMRead(SCHEDULE_ENTRY_LOCK_ADDR_TIME_OFFSET, sizeof(time_offset), (byte *)&time_offset);
	crc16 = CrcClass::crc16_ccitt_aug(&time_offset.info, sizeof(time_offset.info));
	if (memcmp(&crc16, &time_offset.crc16[0x0], sizeof(crc16)) != 0x0) {
		memset(&report->info, 0x0, sizeof(report->info));
	}
	else
		report->info = time_offset.info;
	frame_report->packet.len = sizeof(report[0x0]);
	return (ZUNO_COMMAND_ANSWERED);
}

typedef struct					ScheduleEntryLockTimeOffsetSet_s
{
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	ScheduleEntryLockSaveTimeOffsetInfo_t	info;
}								ScheduleEntryLockTimeOffsetSet_t;

static int _schedule_entry_lock_time_offset_set(const ScheduleEntryLockTimeOffsetSet_t *in) {
	uint16_t													crc16;
	ScheduleEntryLockSaveTimeOffset_t							time_offset;

	time_offset.info = in->info;
	crc16 = CrcClass::crc16_ccitt_aug(&time_offset.info, sizeof(time_offset.info));
	memcpy(&time_offset.crc16[0x0], &crc16, sizeof(time_offset.crc16));
	zunoEEPROMWrite(SCHEDULE_ENTRY_LOCK_ADDR_TIME_OFFSET, sizeof(time_offset), (byte *)&time_offset);
	return (ZUNO_COMMAND_PROCESSED);
}

typedef struct					ScheduleEntryLockV3SetSlotInfo_s
{
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						setAction;/**/
	ScheduleEntryLockV3SlotInfoPre_t	pre;
	uint8_t						data[];
}								ScheduleEntryLockV3SetSlotInfo_t;

typedef struct					ScheduleEntryLockV4SetSlotInfo_s
{
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						setAction;/**/
	ScheduleEntryLockV4SlotInfoPre_t	pre;
	uint8_t						data[];
}								ScheduleEntryLockV4SetSlotInfo_t;

static uint16_t _schedule_entry_lock_test_set_slot_info_v3(const ScheduleEntryLockV3SetSlotInfo_t *in, uint8_t slot_id_max) {
	uint16_t									userIdentifier;

	if (in->setAction > 0x1)
		return (0x0);
	if ((userIdentifier = _schedule_entry_lock_test_common_slot_info_v3(&in->pre, slot_id_max)) == 0x0)
		return (0x0);
	return (userIdentifier);
}

static uint16_t _schedule_entry_lock_test_set_slot_info_v4(const ScheduleEntryLockV4SetSlotInfo_t *in, uint8_t slot_id_max) {
	uint16_t									userIdentifier;

	if (in->setAction > 0x1)
		return (0x0);
	if ((userIdentifier = _schedule_entry_lock_test_common_slot_info_v4(&in->pre, slot_id_max)) == 0x0)
		return (0x0);
	return (userIdentifier);
}

static void _daily_repeating_set(uint16_t userIdentifier, uint8_t scheduleSlotId, const ScheduleEntryLockSaveUserIdentifierDayilyRepeating_t *daily_repeating, uint8_t setAction) {
	const ScheduleEntryLockSaveUserId_t							*user_id;
	ScheduleEntryLockSaveUserIdentifierDayilyRepeatingMask_t	dayily_repeating_mask;
	uint32_t													addr;
	size_t														offset;
	uint16_t													crc16;
	uint8_t														mask;

	userIdentifier--;
	offset = userIdentifier / (SCHEDULE_ENTRY_LOCK_NUMBER_MASK_LENGHT * 0x8);
	addr = (SCHEDULE_ENTRY_LOCK_ADDR_COMMON) + (offset * sizeof(ScheduleEntryLockSaveMask_t)) + (offset * ((SCHEDULE_ENTRY_LOCK_NUMBER_MASK_LENGHT * 0x8) * sizeof(ScheduleEntryLockSaveUserId_t)));
	user_id = (const ScheduleEntryLockSaveUserId_t *)(addr + sizeof(ScheduleEntryLockSaveMask_t));
	scheduleSlotId--;
	if (setAction == 0x1) {
		addr = (uint32_t)&user_id[userIdentifier % (SCHEDULE_ENTRY_LOCK_NUMBER_MASK_LENGHT * 0x8)].dayily_repeating[scheduleSlotId];
		zunoEEPROMWrite(addr, sizeof(daily_repeating[0x0]), (byte *)daily_repeating);
		mask = (0x1 << (scheduleSlotId % 8));
	}
	else
		mask = ~(0x1 << (scheduleSlotId % 8));
	addr = (uint32_t)&user_id[userIdentifier % (SCHEDULE_ENTRY_LOCK_NUMBER_MASK_LENGHT * 0x8)].dayily_repeating_mask;
	zunoEEPROMRead(addr, sizeof(dayily_repeating_mask), (byte *)&dayily_repeating_mask);
	dayily_repeating_mask.mask[scheduleSlotId / 0x8] = dayily_repeating_mask.mask[scheduleSlotId / 0x8] | mask;
	crc16 = CrcClass::crc16_ccitt_aug(&dayily_repeating_mask.mask[0x0], sizeof(dayily_repeating_mask.mask));
	memcpy(&dayily_repeating_mask.crc16[0x0], &crc16, sizeof(dayily_repeating_mask.crc16));
	zunoEEPROMWrite(addr, sizeof(dayily_repeating_mask), (byte *)&dayily_repeating_mask);
}

static int _schedule_entry_lock_daily_repeating_set(const ScheduleEntryLockV3SetSlotInfo_t *in) {
	uint16_t														userIdentifier;
	const ScheduleEntryLockSaveUserIdentifierDayilyRepeating_t		*dayily_repeating;

	if ((userIdentifier = _schedule_entry_lock_test_set_slot_info_v3(in, SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_DAILY_REPEATING)) == 0x0)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	dayily_repeating = (const ScheduleEntryLockSaveUserIdentifierDayilyRepeating_t *)&in->data[0x0];
	_daily_repeating_set(userIdentifier, in->pre.scheduleSlotId, dayily_repeating, in->setAction);
	return (ZUNO_COMMAND_PROCESSED);
}

static int _extended_schedule_entry_lock_daily_repeating_set(const ScheduleEntryLockV4SetSlotInfo_t *in) {
	uint16_t														userIdentifier;
	const ScheduleEntryLockSaveUserIdentifierDayilyRepeating_t		*dayily_repeating;

	if ((userIdentifier = _schedule_entry_lock_test_set_slot_info_v4(in, SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_DAILY_REPEATING)) == 0x0)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	dayily_repeating = (const ScheduleEntryLockSaveUserIdentifierDayilyRepeating_t *)&in->data[0x0];
	_daily_repeating_set(userIdentifier, in->pre.scheduleSlotId, dayily_repeating, in->setAction);
	return (ZUNO_COMMAND_PROCESSED);
}

static void _year_day_set(uint16_t userIdentifier, uint8_t scheduleSlotId, const ScheduleEntryLockSaveUserIdentifierYearDay_t *year_day, uint8_t setAction) {
	const ScheduleEntryLockSaveUserId_t							*user_id;
	ScheduleEntryLockSaveUserIdentifierYearDayMask_t			year_day_mask;
	uint32_t													addr;
	size_t														offset;
	uint16_t													crc16;
	uint8_t														mask;

	userIdentifier--;
	offset = userIdentifier / (SCHEDULE_ENTRY_LOCK_NUMBER_MASK_LENGHT * 0x8);
	addr = (SCHEDULE_ENTRY_LOCK_ADDR_COMMON) + (offset * sizeof(ScheduleEntryLockSaveMask_t)) + (offset * ((SCHEDULE_ENTRY_LOCK_NUMBER_MASK_LENGHT * 0x8) * sizeof(ScheduleEntryLockSaveUserId_t)));
	user_id = (const ScheduleEntryLockSaveUserId_t *)(addr + sizeof(ScheduleEntryLockSaveMask_t));
	scheduleSlotId--;
	if (setAction == 0x1) {
		addr = (uint32_t)&user_id[userIdentifier % (SCHEDULE_ENTRY_LOCK_NUMBER_MASK_LENGHT * 0x8)].year_day[scheduleSlotId];
		zunoEEPROMWrite(addr, sizeof(year_day[0x0]), (byte *)year_day);
		mask = (0x1 << (scheduleSlotId % 8));
	}
	else
		mask = ~(0x1 << (scheduleSlotId % 8));
	addr = (uint32_t)&user_id[userIdentifier % (SCHEDULE_ENTRY_LOCK_NUMBER_MASK_LENGHT * 0x8)].year_day_mask;
	zunoEEPROMRead(addr, sizeof(year_day_mask), (byte *)&year_day_mask);
	year_day_mask.mask[scheduleSlotId / 0x8] = year_day_mask.mask[scheduleSlotId / 0x8] | mask;
	crc16 = CrcClass::crc16_ccitt_aug(&year_day_mask.mask[0x0], sizeof(year_day_mask.mask));
	memcpy(&year_day_mask.crc16[0x0], &crc16, sizeof(year_day_mask.crc16));
	zunoEEPROMWrite(addr, sizeof(year_day_mask), (byte *)&year_day_mask);
}

static int _schedule_entry_lock_year_day_set(const ScheduleEntryLockV3SetSlotInfo_t *in) {
	uint16_t														userIdentifier;
	const ScheduleEntryLockSaveUserIdentifierYearDay_t				*year_day;

	if ((userIdentifier = _schedule_entry_lock_test_set_slot_info_v3(in, SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_YEAR_DAY)) == 0x0)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	year_day = (const ScheduleEntryLockSaveUserIdentifierYearDay_t *)&in->data[0x0];
	_year_day_set(userIdentifier, in->pre.scheduleSlotId, year_day, in->setAction);
	return (ZUNO_COMMAND_PROCESSED);
}

static int _extended_schedule_entry_lock_year_day_set(const ScheduleEntryLockV4SetSlotInfo_t *in) {
	uint16_t														userIdentifier;
	const ScheduleEntryLockSaveUserIdentifierYearDay_t				*year_day;

	if ((userIdentifier = _schedule_entry_lock_test_set_slot_info_v4(in, SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_YEAR_DAY)) == 0x0)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	year_day = (const ScheduleEntryLockSaveUserIdentifierYearDay_t *)&in->data[0x0];
	_year_day_set(userIdentifier, in->pre.scheduleSlotId, year_day, in->setAction);
	return (ZUNO_COMMAND_PROCESSED);
}

static void _week_day_set(uint16_t userIdentifier, uint8_t scheduleSlotId, const ScheduleEntryLockSaveUserIdentifierWeekDay_t *week_day, uint8_t setAction) {
	const ScheduleEntryLockSaveUserId_t							*user_id;
	ScheduleEntryLockSaveUserIdentifierWeekDayMask_t			week_day_mask;
	uint32_t													addr;
	size_t														offset;
	uint16_t													crc16;
	uint8_t														mask;

	userIdentifier--;
	offset = userIdentifier / (SCHEDULE_ENTRY_LOCK_NUMBER_MASK_LENGHT * 0x8);
	addr = (SCHEDULE_ENTRY_LOCK_ADDR_COMMON) + (offset * sizeof(ScheduleEntryLockSaveMask_t)) + (offset * ((SCHEDULE_ENTRY_LOCK_NUMBER_MASK_LENGHT * 0x8) * sizeof(ScheduleEntryLockSaveUserId_t)));
	user_id = (const ScheduleEntryLockSaveUserId_t *)(addr + sizeof(ScheduleEntryLockSaveMask_t));
	scheduleSlotId--;
	if (setAction == 0x1) {
		addr = (uint32_t)&user_id[userIdentifier % (SCHEDULE_ENTRY_LOCK_NUMBER_MASK_LENGHT * 0x8)].week_day[scheduleSlotId];
		zunoEEPROMWrite(addr, sizeof(week_day[0x0]), (byte *)week_day);
		mask = (0x1 << (scheduleSlotId % 8));
	}
	else
		mask = ~(0x1 << (scheduleSlotId % 8));
	addr = (uint32_t)&user_id[userIdentifier % (SCHEDULE_ENTRY_LOCK_NUMBER_MASK_LENGHT * 0x8)].week_day_mask;
	zunoEEPROMRead(addr, sizeof(week_day_mask), (byte *)&week_day_mask);
	week_day_mask.mask[scheduleSlotId / 0x8] = week_day_mask.mask[scheduleSlotId / 0x8] | mask;
	crc16 = CrcClass::crc16_ccitt_aug(&week_day_mask.mask[0x0], sizeof(week_day_mask.mask));
	memcpy(&week_day_mask.crc16[0x0], &crc16, sizeof(week_day_mask.crc16));
	zunoEEPROMWrite(addr, sizeof(week_day_mask), (byte *)&week_day_mask);
}

static int _schedule_entry_lock_week_day_set(const ScheduleEntryLockV3SetSlotInfo_t *in) {
	uint16_t														userIdentifier;
	const ScheduleEntryLockSaveUserIdentifierWeekDay_t				*week_day;

	if ((userIdentifier = _schedule_entry_lock_test_set_slot_info_v3(in, SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_WEEK_DAY)) == 0x0)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	week_day = (const ScheduleEntryLockSaveUserIdentifierWeekDay_t *)&in->data[0x0];
	_week_day_set(userIdentifier, in->pre.scheduleSlotId, week_day, in->setAction);
	return (ZUNO_COMMAND_PROCESSED);
}

static int _extended_schedule_entry_lock_week_day_set(const ScheduleEntryLockV4SetSlotInfo_t *in) {
	uint16_t														userIdentifier;
	const ScheduleEntryLockSaveUserIdentifierWeekDay_t				*week_day;

	if ((userIdentifier = _schedule_entry_lock_test_set_slot_info_v4(in, SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_WEEK_DAY)) == 0x0)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	week_day = (const ScheduleEntryLockSaveUserIdentifierWeekDay_t *)&in->data[0x0];
	_week_day_set(userIdentifier, in->pre.scheduleSlotId, week_day, in->setAction);
	return (ZUNO_COMMAND_PROCESSED);
}

int zuno_CCScheduleEntryLockHandler(ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	int								rs;

	switch (ZW_CMD) {
		case EXTENDED_SCHEDULE_ENTRY_LOCK_WEEK_DAY_SCHEDULE_SET:
			rs = _extended_schedule_entry_lock_week_day_set((const ScheduleEntryLockV4SetSlotInfo_t *)&cmd->cmd[0x0]);
			break ;
		case SCHEDULE_ENTRY_LOCK_WEEK_DAY_SET:
			rs = _schedule_entry_lock_week_day_set((const ScheduleEntryLockV3SetSlotInfo_t *)&cmd->cmd[0x0]);
			break ;
		case EXTENDED_SCHEDULE_ENTRY_LOCK_YEAR_DAY_SCHEDULE_SET:
			rs = _extended_schedule_entry_lock_year_day_set((const ScheduleEntryLockV4SetSlotInfo_t *)&cmd->cmd[0x0]);
			break ;
		case SCHEDULE_ENTRY_LOCK_YEAR_DAY_SET:
			rs = _schedule_entry_lock_year_day_set((const ScheduleEntryLockV3SetSlotInfo_t *)&cmd->cmd[0x0]);
			break ;
		case EXTENDED_SCHEDULE_ENTRY_LOCK_DAILY_REPEATING_SET:
			rs = _extended_schedule_entry_lock_daily_repeating_set((const ScheduleEntryLockV4SetSlotInfo_t *)&cmd->cmd[0x0]);
			break ;
		case SCHEDULE_ENTRY_LOCK_DAILY_REPEATING_SET:
			rs = _schedule_entry_lock_daily_repeating_set((const ScheduleEntryLockV3SetSlotInfo_t *)&cmd->cmd[0x0]);
			break ;
		case SCHEDULE_ENTRY_LOCK_TIME_OFFSET_SET:
			rs = _schedule_entry_lock_time_offset_set((const ScheduleEntryLockTimeOffsetSet_t *)&cmd->cmd[0x0]);
			break ;
		case SCHEDULE_ENTRY_LOCK_TIME_OFFSET_GET:
			rs = _schedule_entry_lock_time_offset_report(frame_report);
			break ;
		case EXTENDED_SCHEDULE_ENTRY_LOCK_DAILY_REPEATING_GET:
			rs = _extended_schedule_entry_lock_daily_repeating_report((const ScheduleEntryLockV4GetSlotInfo_t *)&cmd->cmd[0x0], frame_report);
			break ;
		case SCHEDULE_ENTRY_LOCK_DAILY_REPEATING_GET:
			rs = _schedule_entry_lock_daily_repeating_report((const ScheduleEntryLockV3GetSlotInfo_t *)&cmd->cmd[0x0], frame_report);
			break ;
		case EXTENDED_SCHEDULE_ENTRY_LOCK_YEAR_DAY_SCHEDULE_GET:
			rs = _extended_schedule_entry_lock_year_day_report((const ScheduleEntryLockV4GetSlotInfo_t *)&cmd->cmd[0x0], frame_report);
			break ;
		case SCHEDULE_ENTRY_LOCK_YEAR_DAY_GET:
			rs = _schedule_entry_lock_year_day_report((const ScheduleEntryLockV3GetSlotInfo_t *)&cmd->cmd[0x0], frame_report);
			break ;
		case EXTENDED_SCHEDULE_ENTRY_LOCK_WEEK_DAY_SCHEDULE_GET:
			rs = _extended_schedule_entry_lock_week_day_report((const ScheduleEntryLockV4GetSlotInfo_t *)&cmd->cmd[0x0], frame_report);
			break ;
		case SCHEDULE_ENTRY_LOCK_WEEK_DAY_GET:
			rs = _schedule_entry_lock_week_day_report((const ScheduleEntryLockV3GetSlotInfo_t *)&cmd->cmd[0x0], frame_report);
			break ;
		case SCHEDULE_ENTRY_TYPE_SUPPORTED_GET:
			rs = _schedule_entry_type_supported_report(frame_report);
			break ;
		default:
			rs = ZUNO_COMMAND_BLOCKED_NO_SUPPORT;
			break ;
	}
	return (rs);
}

#endif//WITH_CC_SCHEDULE_ENTRY_LOCK
