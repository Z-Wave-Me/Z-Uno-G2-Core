#ifndef ZWCC_SWITCH_COLOR_H
#define ZWCC_SWITCH_COLOR_H

#include "Arduino.h"

/* Switch Color command class commands */
#define SWITCH_COLOR_VERSION                                                             0x01
#define SWITCH_COLOR_SUPPORTED_GET                                                       0x01
#define SWITCH_COLOR_SUPPORTED_REPORT                                                    0x02
#define SWITCH_COLOR_GET                                                                 0x03
#define SWITCH_COLOR_REPORT                                                              0x04
#define SWITCH_COLOR_SET                                                                 0x05
#define SWITCH_COLOR_START_LEVEL_CHANGE                                                  0x06
#define SWITCH_COLOR_STOP_LEVEL_CHANGE                                                   0x07
/* Values used for Switch Color Set command */
#define SWITCH_COLOR_SET_PROPERTIES1_COLOR_COMPONENT_COUNT_MASK                          0x1F
#define SWITCH_COLOR_SET_PROPERTIES1_RESERVED_MASK                                       0xE0
#define SWITCH_COLOR_SET_PROPERTIES1_RESERVED_SHIFT                                      0x05
/* Values used for Switch Color Start Level Change command */
#define SWITCH_COLOR_START_LEVEL_CHANGE_PROPERTIES1_RES1_MASK                            0x1F
#define SWITCH_COLOR_START_LEVEL_CHANGE_PROPERTIES1_IGNORE_START_STATE_BIT_MASK          0x20
#define SWITCH_COLOR_START_LEVEL_CHANGE_PROPERTIES1_UP_DOWN_BIT_MASK                     0x40
#define SWITCH_COLOR_START_LEVEL_CHANGE_PROPERTIES1_RES2_BIT_MASK                        0x80

/* Switch Color command class commands */
#define SWITCH_COLOR_VERSION_V2                                                          0x02
#define SWITCH_COLOR_SUPPORTED_GET_V2                                                    0x01
#define SWITCH_COLOR_SUPPORTED_REPORT_V2                                                 0x02
#define SWITCH_COLOR_GET_V2                                                              0x03
#define SWITCH_COLOR_REPORT_V2                                                           0x04
#define SWITCH_COLOR_SET_V2                                                              0x05
#define SWITCH_COLOR_START_LEVEL_CHANGE_V2                                               0x06
#define SWITCH_COLOR_STOP_LEVEL_CHANGE_V2                                                0x07
/* Values used for Switch Color Set command */
#define SWITCH_COLOR_SET_PROPERTIES1_COLOR_COMPONENT_COUNT_MASK_V2                       0x1F
#define SWITCH_COLOR_SET_PROPERTIES1_RESERVED_MASK_V2                                    0xE0
#define SWITCH_COLOR_SET_PROPERTIES1_RESERVED_SHIFT_V2                                   0x05
/* Values used for Switch Color Start Level Change command */
#define SWITCH_COLOR_START_LEVEL_CHANGE_PROPERTIES1_RES1_MASK_V2                         0x1F
#define SWITCH_COLOR_START_LEVEL_CHANGE_PROPERTIES1_IGNORE_START_STATE_BIT_MASK_V2       0x20
#define SWITCH_COLOR_START_LEVEL_CHANGE_PROPERTIES1_UP_DOWN_BIT_MASK_V2                  0x40
#define SWITCH_COLOR_START_LEVEL_CHANGE_PROPERTIES1_RES2_BIT_MASK_V2                     0x80

/* Switch Color command class commands */
#define SWITCH_COLOR_VERSION_V3                                                          0x03
#define SWITCH_COLOR_SUPPORTED_GET_V3                                                    0x01
#define SWITCH_COLOR_SUPPORTED_REPORT_V3                                                 0x02
#define SWITCH_COLOR_GET_V3                                                              0x03
#define SWITCH_COLOR_REPORT_V3                                                           0x04
#define SWITCH_COLOR_SET_V3                                                              0x05
#define SWITCH_COLOR_START_LEVEL_CHANGE_V3                                               0x06
#define SWITCH_COLOR_STOP_LEVEL_CHANGE_V3                                                0x07
/* Values used for Switch Color Report command */
#define SWITCH_COLOR_REPORT_ALREADY_AT_THE_TARGET_VALUE_V3                               0x00
#define SWITCH_COLOR_REPORT_UNKNOWN_DURATION_V3                                          0xFE
#define SWITCH_COLOR_REPORT_RESERVED_V3                                                  0xFF
/* Values used for Switch Color Set command */
#define SWITCH_COLOR_SET_PROPERTIES1_COLOR_COMPONENT_COUNT_MASK_V3                       0x1F
#define SWITCH_COLOR_SET_PROPERTIES1_RESERVED_MASK_V3                                    0xE0
#define SWITCH_COLOR_SET_PROPERTIES1_RESERVED_SHIFT_V3                                   0x05
#define SWITCH_COLOR_SET_INSTANTLY_V3                                                    0x00
#define SWITCH_COLOR_SET_DEFAULT_V3                                                      0xFF
/* Values used for Switch Color Start Level Change command */
#define SWITCH_COLOR_START_LEVEL_CHANGE_PROPERTIES1_RES1_MASK_V3                         0x1F
#define SWITCH_COLOR_START_LEVEL_CHANGE_PROPERTIES1_IGNORE_START_STATE_BIT_MASK_V3       0x20
#define SWITCH_COLOR_START_LEVEL_CHANGE_PROPERTIES1_UP_DOWN_BIT_MASK_V3                  0x40
#define SWITCH_COLOR_START_LEVEL_CHANGE_PROPERTIES1_RES2_BIT_MASK_V3                     0x80
#define SWITCH_COLOR_START_LEVEL_CHANGE_INSTANTLY_V3                                     0x00
#define SWITCH_COLOR_START_LEVEL_CHANGE_DEFAULT_V3                                       0xFF

int zuno_CCSwitchColorHandler(uint8_t channel, ZUNOCommandPacket_t *cmd);

#endif // ZWCC_SWITCH_COLOR_H