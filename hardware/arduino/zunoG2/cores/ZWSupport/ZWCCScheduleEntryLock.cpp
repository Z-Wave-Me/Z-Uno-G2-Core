#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCScheduleEntryLock.h"


#if defined(WITH_CC_SCHEDULE_ENTRY_LOCK)

static_assert(SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_WEEK_DAY <= 0xFF, "SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_WEEK_DAY - overflow!!!");
static_assert(SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_YEAR_DAY <= 0xFF, "SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_YEAR_DAY - overflow!!!");
static_assert(SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_DAILY_REPEATING <= 0xFF, "SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_DAILY_REPEATING - overflow!!!");
static_assert(SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_WEEK_DAY >= 0x1, "SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_WEEK_DAY - minimum 1!!!");
static_assert(SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_YEAR_DAY >= 0x1, "SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_YEAR_DAY - minimum 1!!!");
static_assert(SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_DAILY_REPEATING >= 0x1, "SCHEDULE_ENTRY_LOCK_NUMBER_SLOT_DAILY_REPEATING - minimum 1!!!");


/************************************************************/
/* Schedule Entry Type Supported Report V3 command class structs */
/************************************************************/
typedef struct _ZW_SCHEDULE_ENTRY_TYPE_SUPPORTED_REPORT_V3_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   numberOfSlotsWeekDay;         /**/
    uint8_t   numberOfSlotsYearDay;         /**/
    uint8_t   numberOfSlotsDailyRepeating;  /**/
} ZW_SCHEDULE_ENTRY_TYPE_SUPPORTED_REPORT_V3_FRAME;


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

int zuno_CCScheduleEntryLockHandler(ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	int								rs;

	switch (ZW_CMD) {
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


// #ifdef WITH_CC_SCHEDULE_ENTRY_LOCK
// #ifndef SCHEDULE_ENTRY_LOCK_EXTERNAL
// #define SCHEDULE_ENTRY_LOCK_ADDR							((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.schedule_entry_lock)
// #define SCHEDULE_ENTRY_LOCK_SIZE							(sizeof(((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.schedule_entry_lock))
// #endif
// #endif