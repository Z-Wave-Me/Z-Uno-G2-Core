#ifndef ZWCC_TIME_H
#define ZWCC_TIME_H

#include "ZWSupport.h"

/* Time command class commands */
#define TIME_VERSION                                                                     0x01
#define DATE_GET                                                                         0x03
#define DATE_REPORT                                                                      0x04
#define TIME_GET                                                                         0x01
#define TIME_OFFSET_GET                                                                  0x06
#define TIME_OFFSET_REPORT                                                               0x07
#define TIME_OFFSET_SET                                                                  0x05
#define TIME_REPORT                                                                      0x02
/* Values used for Time Offset Report command */
#define TIME_OFFSET_REPORT_LEVEL_HOUR_TZO_MASK                                           0x7F
#define TIME_OFFSET_REPORT_LEVEL_SIGN_TZO_BIT_MASK                                       0x80
#define TIME_OFFSET_REPORT_LEVEL2_MINUTE_OFFSET_DST_MASK                                 0x7F
#define TIME_OFFSET_REPORT_LEVEL2_SIGN_OFFSET_DST_BIT_MASK                               0x80
/* Values used for Time Offset Set command */
#define TIME_OFFSET_SET_LEVEL_HOUR_TZO_MASK                                              0x7F
#define TIME_OFFSET_SET_LEVEL_SIGN_TZO_BIT_MASK                                          0x80
#define TIME_OFFSET_SET_LEVEL2_MINUTE_OFFSET_DST_MASK                                    0x7F
#define TIME_OFFSET_SET_LEVEL2_SIGN_OFFSET_DST_BIT_MASK                                  0x80
/* Values used for Time Report command */
#define TIME_REPORT_PROPERTIES1_HOUR_LOCAL_TIME_MASK                                     0x1F
#define TIME_REPORT_PROPERTIES1_RESERVED_MASK                                            0x60
#define TIME_REPORT_PROPERTIES1_RESERVED_SHIFT                                           0x05
#define TIME_REPORT_PROPERTIES1_RTC_FAILURE_BIT_MASK                                     0x80

int zuno_CCTimeHandler(ZUNOCommandPacket_t *cmd);

#endif// ZWCC_TIME_H