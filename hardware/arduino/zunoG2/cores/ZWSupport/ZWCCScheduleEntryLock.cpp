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

typedef struct _ZW_SCHEDULE_ENTRY_TYPE_SUPPORTED_REPORT_V3_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   numberOfSlotsWeekDay;         /**/
    uint8_t   numberOfSlotsYearDay;         /**/
    uint8_t   numberOfSlotsDailyRepeating;  /**/
} ZW_SCHEDULE_ENTRY_TYPE_SUPPORTED_REPORT_V3_FRAME;

typedef struct					ScheduleEntryLockV3GetSlotInfoPre_s
{
	uint8_t						userIdentifier;/**/
	uint8_t						scheduleSlotId;/**/
}								ScheduleEntryLockV3GetSlotInfoPre_t;

typedef struct					ScheduleEntryLockV3GetSlotInfo_s
{
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	ScheduleEntryLockV3GetSlotInfoPre_t	pre;
}								ScheduleEntryLockV3GetSlotInfo_t;

typedef struct					ScheduleEntryLockV3GetSlotInfoReport_s
{
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	ScheduleEntryLockV3GetSlotInfoPre_t	pre;
	uint8_t						data[];
}								ScheduleEntryLockV3GetSlotInfoReport_t;

typedef struct					ScheduleEntryLockV4GetSlotInfoPre_s
{
	uint8_t						userIdentifier[0x2];/*MSB - LSB*/
	uint8_t						scheduleSlotId;/**/
}								ScheduleEntryLockV4GetSlotInfoPre_t;

typedef struct					ScheduleEntryLockV4GetSlotInfo_s
{
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	ScheduleEntryLockV4GetSlotInfoPre_t	pre;
}								ScheduleEntryLockV4GetSlotInfo_t;

typedef struct					ScheduleEntryLockV4GetSlotInfoReport_s
{
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	ScheduleEntryLockV4GetSlotInfoPre_t	pre;
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

static uint16_t _schedule_entry_lock_test_get_slot_info_v3(const ScheduleEntryLockV3GetSlotInfo_t *in, ScheduleEntryLockV3GetSlotInfoReport_t *report, uint8_t slot_id_max) {
	uint16_t									userIdentifier;
	uint8_t										scheduleSlotId;

	if ((userIdentifier = in->pre.userIdentifier) > SCHEDULE_ENTRY_LOCK_NUMBER)
		return (0x0);
	if ((scheduleSlotId = in->pre.scheduleSlotId) > slot_id_max || scheduleSlotId == 0x0)
		return (0x0);
	report->pre = in->pre;
	return (userIdentifier);
}

static uint16_t _schedule_entry_lock_test_get_slot_info_v4(const ScheduleEntryLockV4GetSlotInfo_t *in, ScheduleEntryLockV4GetSlotInfoReport_t *report, uint8_t slot_id_max) {
	uint16_t									userIdentifier;
	uint8_t										scheduleSlotId;

	if ((userIdentifier = ((in->pre.userIdentifier[0x0] << 0x8) | in->pre.userIdentifier[0x1])) > SCHEDULE_ENTRY_LOCK_NUMBER)
		return (0x0);
	if ((scheduleSlotId = in->pre.scheduleSlotId) > slot_id_max || scheduleSlotId == 0x0)
		return (0x0);
	report->pre = in->pre;
	return (userIdentifier);
}

static void _schedule_entry_lock_week_day_get(uint16_t userIdentifier, uint8_t scheduleSlotId, ScheduleEntryLockSaveUserIdentifierWeekDay_t *report_week_day) {
	const ScheduleEntryLockSaveUserId_t							*user_id;
	ScheduleEntryLockSaveUserIdentifierWeekDayCrc_t				week_day;
	uint32_t													addr;
	size_t														offset;
	uint16_t													crc16;

	userIdentifier--;
	offset = userIdentifier / (SCHEDULE_ENTRY_LOCK_NUMBER_MASK_LENGHT * 0x8);
	addr = (SCHEDULE_ENTRY_LOCK_ADDR) + (offset * sizeof(ScheduleEntryLockSaveMask_t)) + (offset * ((SCHEDULE_ENTRY_LOCK_NUMBER_MASK_LENGHT * 0x8) * sizeof(ScheduleEntryLockSaveUserId_t)));
	user_id = (const ScheduleEntryLockSaveUserId_t *)(addr + sizeof(ScheduleEntryLockSaveMask_t));
	scheduleSlotId--;
	addr = (uint32_t)&user_id[userIdentifier % (SCHEDULE_ENTRY_LOCK_NUMBER_MASK_LENGHT * 0x8)].week_day[scheduleSlotId];
	zunoEEPROMRead(addr, sizeof(week_day), (byte *)&week_day);
	crc16 = CrcClass::crc16_ccitt_aug(&week_day.info, sizeof(week_day.info));
	if (memcmp(&crc16, &week_day.crc16[0x0], sizeof(crc16)) != 0x0) {
		memset(report_week_day, 0xFF, sizeof(report_week_day[0x0]));
		return ;
	}
	report_week_day[0x0] = week_day.info;
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
	// report->cmdClass = EXTENDED_SCHEDULE_ENTRY_LOCK_WEEK_DAY_SCHEDULE_GET; set in - fillOutgoingPacket
	// report->cmd = EXTENDED_SCHEDULE_ENTRY_LOCK_WEEK_DAY_SCHEDULE_REPORT; set in - fillOutgoingPacket
	report_week_day = (ScheduleEntryLockSaveUserIdentifierWeekDay_t *)&report->data[0x0];
	_schedule_entry_lock_week_day_get(userIdentifier, in->pre.scheduleSlotId, report_week_day);
	frame_report->packet.len = sizeof(report[0x0]) + sizeof(report_week_day[0x0]);
	return (ZUNO_COMMAND_ANSWERED);
}

static void _schedule_entry_lock_year_day_get(uint16_t userIdentifier, uint8_t scheduleSlotId, ScheduleEntryLockSaveUserIdentifierYearDay_t *report_year_day) {
	const ScheduleEntryLockSaveUserId_t							*user_id;
	ScheduleEntryLockSaveUserIdentifierYearDayCrc_t				year_day;
	uint32_t													addr;
	size_t														offset;
	uint16_t													crc16;

	userIdentifier--;
	offset = userIdentifier / (SCHEDULE_ENTRY_LOCK_NUMBER_MASK_LENGHT * 0x8);
	addr = (SCHEDULE_ENTRY_LOCK_ADDR) + (offset * sizeof(ScheduleEntryLockSaveMask_t)) + (offset * ((SCHEDULE_ENTRY_LOCK_NUMBER_MASK_LENGHT * 0x8) * sizeof(ScheduleEntryLockSaveUserId_t)));
	user_id = (const ScheduleEntryLockSaveUserId_t *)(addr + sizeof(ScheduleEntryLockSaveMask_t));
	scheduleSlotId--;
	addr = (uint32_t)&user_id[userIdentifier % (SCHEDULE_ENTRY_LOCK_NUMBER_MASK_LENGHT * 0x8)].year_day[scheduleSlotId];
	zunoEEPROMRead(addr, sizeof(year_day), (byte *)&year_day);
	crc16 = CrcClass::crc16_ccitt_aug(&year_day.info, sizeof(year_day.info));
	if (memcmp(&crc16, &year_day.crc16[0x0], sizeof(crc16)) != 0x0) {
		memset(report_year_day, 0xFF, sizeof(report_year_day[0x0]));
		return ;
	}
	report_year_day[0x0] = year_day.info;
}

static int _schedule_entry_lock_year_day_report(const ScheduleEntryLockV3GetSlotInfo_t *in, ZUNOCommandPacketReport_t *frame_report) {
	uint16_t														userIdentifier;
	ScheduleEntryLockV3GetSlotInfoReport_t							*report;
	ScheduleEntryLockSaveUserIdentifierYearDay_t					*report_year_day;

	report = (ScheduleEntryLockV3GetSlotInfoReport_t *)frame_report->packet.cmd;
	if ((userIdentifier = _schedule_entry_lock_test_get_slot_info_v3(in, report, SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_YEAR_DAY)) == 0x0)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	// report->cmdClass = SCHEDULE_ENTRY_LOCK_YEAR_DAY_GET; set in - fillOutgoingPacket
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
	// report->cmdClass = EXTENDED_SCHEDULE_ENTRY_LOCK_YEAR_DAY_SCHEDULE_GET; set in - fillOutgoingPacket
	// report->cmd = EXTENDED_SCHEDULE_ENTRY_LOCK_YEAR_DAY_SCHEDULE_REPORT; set in - fillOutgoingPacket
	report_year_day = (ScheduleEntryLockSaveUserIdentifierYearDay_t *)&report->data[0x0];
	_schedule_entry_lock_year_day_get(userIdentifier, in->pre.scheduleSlotId, report_year_day);
	frame_report->packet.len = sizeof(report[0x0]) + sizeof(report_year_day[0x0]);
	return (ZUNO_COMMAND_ANSWERED);
}

static void _schedule_entry_lock_daily_repeating_get(uint16_t userIdentifier, uint8_t scheduleSlotId, ScheduleEntryLockSaveUserIdentifierDayilyRepeating_t *report_daily_repeating) {
	const ScheduleEntryLockSaveUserId_t							*user_id;
	ScheduleEntryLockSaveUserIdentifierDayilyRepeatingCrc_t		dayily_repeating;
	uint32_t													addr;
	size_t														offset;
	uint16_t													crc16;

	userIdentifier--;
	offset = userIdentifier / (SCHEDULE_ENTRY_LOCK_NUMBER_MASK_LENGHT * 0x8);
	addr = (SCHEDULE_ENTRY_LOCK_ADDR) + (offset * sizeof(ScheduleEntryLockSaveMask_t)) + (offset * ((SCHEDULE_ENTRY_LOCK_NUMBER_MASK_LENGHT * 0x8) * sizeof(ScheduleEntryLockSaveUserId_t)));
	user_id = (const ScheduleEntryLockSaveUserId_t *)(addr + sizeof(ScheduleEntryLockSaveMask_t));
	scheduleSlotId--;
	addr = (uint32_t)&user_id[userIdentifier % (SCHEDULE_ENTRY_LOCK_NUMBER_MASK_LENGHT * 0x8)].dayily_repeating[scheduleSlotId];
	zunoEEPROMRead(addr, sizeof(dayily_repeating), (byte *)&dayily_repeating);
	crc16 = CrcClass::crc16_ccitt_aug(&dayily_repeating.info, sizeof(dayily_repeating.info));
	if (memcmp(&crc16, &dayily_repeating.crc16[0x0], sizeof(crc16)) != 0x0) {
		memset(report_daily_repeating, 0xFF, sizeof(report_daily_repeating[0x0]));
		return ;
	}
	report_daily_repeating[0x0] = dayily_repeating.info;
}

static int _schedule_entry_lock_daily_repeating_report(const ScheduleEntryLockV3GetSlotInfo_t *in, ZUNOCommandPacketReport_t *frame_report) {
	uint16_t														userIdentifier;
	ScheduleEntryLockV3GetSlotInfoReport_t							*report;
	ScheduleEntryLockSaveUserIdentifierDayilyRepeating_t			*report_daily_repeating;

	report = (ScheduleEntryLockV3GetSlotInfoReport_t *)frame_report->packet.cmd;
	if ((userIdentifier = _schedule_entry_lock_test_get_slot_info_v3(in, report, SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_DAILY_REPEATING)) == 0x0)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	// report->cmdClass = SCHEDULE_ENTRY_LOCK_DAILY_REPEATING_GET; set in - fillOutgoingPacket
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
	// report->cmdClass = SCHEDULE_ENTRY_LOCK_DAILY_REPEATING_GET; set in - fillOutgoingPacket
	// report->cmd = SCHEDULE_ENTRY_LOCK_DAILY_REPEATING_REPORT; set in - fillOutgoingPacket
	report_daily_repeating = (ScheduleEntryLockSaveUserIdentifierDayilyRepeating_t *)&report->data[0x0];
	_schedule_entry_lock_daily_repeating_get(userIdentifier, in->pre.scheduleSlotId, report_daily_repeating);
	frame_report->packet.len = sizeof(report[0x0]) + sizeof(report_daily_repeating[0x0]);
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCScheduleEntryLockHandler(ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	int								rs;

	switch (ZW_CMD) {
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
