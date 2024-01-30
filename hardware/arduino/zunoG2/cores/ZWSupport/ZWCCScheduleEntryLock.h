#ifndef ZWCC_SCHEDULE_ENTRY_LOCK_H
#define ZWCC_SCHEDULE_ENTRY_LOCK_H

#include "ZWSupport.h"

/* Schedule Entry Lock command class commands */
#define SCHEDULE_ENTRY_LOCK_VERSION                                                      0x03
#define SCHEDULE_ENTRY_LOCK_ENABLE_ALL_SET                                               0x02
#define SCHEDULE_ENTRY_LOCK_ENABLE_SET                                                   0x01
#define SCHEDULE_ENTRY_LOCK_TIME_OFFSET_GET                                              0x0B
#define SCHEDULE_ENTRY_LOCK_TIME_OFFSET_REPORT                                           0x0C
#define SCHEDULE_ENTRY_LOCK_TIME_OFFSET_SET                                              0x0D
#define SCHEDULE_ENTRY_LOCK_WEEK_DAY_GET                                                 0x04
#define SCHEDULE_ENTRY_LOCK_WEEK_DAY_REPORT                                              0x05
#define SCHEDULE_ENTRY_LOCK_WEEK_DAY_SET                                                 0x03
#define SCHEDULE_ENTRY_LOCK_YEAR_DAY_GET                                                 0x07
#define SCHEDULE_ENTRY_LOCK_YEAR_DAY_REPORT                                              0x08
#define SCHEDULE_ENTRY_LOCK_YEAR_DAY_SET                                                 0x06
#define SCHEDULE_ENTRY_TYPE_SUPPORTED_GET                                                0x09
#define SCHEDULE_ENTRY_TYPE_SUPPORTED_REPORT                                             0x0A
#define SCHEDULE_ENTRY_LOCK_DAILY_REPEATING_GET                                          0x0E
#define SCHEDULE_ENTRY_LOCK_DAILY_REPEATING_REPORT                                       0x0F
#define SCHEDULE_ENTRY_LOCK_DAILY_REPEATING_SET                                          0x10
/* Values used for Schedule Entry Lock Time Offset Report command */
#define SCHEDULE_ENTRY_LOCK_TIME_OFFSET_REPORT_LEVEL_HOUR_TZO_MASK                       0x7F
#define SCHEDULE_ENTRY_LOCK_TIME_OFFSET_REPORT_LEVEL_SIGN_TZO_BIT_MASK                   0x80
#define SCHEDULE_ENTRY_LOCK_TIME_OFFSET_REPORT_LEVEL2_MINUTE_OFFSET_DST_MASK             0x7F
#define SCHEDULE_ENTRY_LOCK_TIME_OFFSET_REPORT_LEVEL2_SIGN_OFFSET_DST_BIT_MASK           0x80
/* Values used for Schedule Entry Lock Time Offset Set command */
#define SCHEDULE_ENTRY_LOCK_TIME_OFFSET_SET_LEVEL_HOUR_TZO_MASK                          0x7F
#define SCHEDULE_ENTRY_LOCK_TIME_OFFSET_SET_LEVEL_SIGN_TZO_BIT_MASK                      0x80
#define SCHEDULE_ENTRY_LOCK_TIME_OFFSET_SET_LEVEL2_MINUTE_OFFSET_DST_MASK                0x7F
#define SCHEDULE_ENTRY_LOCK_TIME_OFFSET_SET_LEVEL2_SIGN_OFFSET_DST_BIT_MASK              0x80

int zuno_CCScheduleEntryLockHandler(ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report);

#endif// ZWCC_SCHEDULE_ENTRY_LOCK_H