#ifndef ZWCC_WINDOW_COVERING_H
#define ZWCC_WINDOW_COVERING_H

#include "Arduino.h"
#include "ZWSupport.h"

/* Window Covering command class commands */
#define WINDOW_COVERING_VERSION                                                          0x01
#define WINDOW_COVERING_SUPPORTED_GET                                                    0x01
#define WINDOW_COVERING_SUPPORTED_REPORT                                                 0x02
#define WINDOW_COVERING_GET                                                              0x03
#define WINDOW_COVERING_REPORT                                                           0x04
#define WINDOW_COVERING_SET                                                              0x05
#define WINDOW_COVERING_START_LEVEL_CHANGE                                               0x06
#define WINDOW_COVERING_STOP_LEVEL_CHANGE                                                0x07
/* Values used for Window Covering Supported Report command */
#define WINDOW_COVERING_SUPPORTED_REPORT_PROPERTIES1_NUMBER_OF_PARAMETER_MASK_BYTES_MASK 0x0F
#define WINDOW_COVERING_SUPPORTED_REPORT_PROPERTIES1_RESERVED_MASK                       0xF0
#define WINDOW_COVERING_SUPPORTED_REPORT_PROPERTIES1_RESERVED_SHIFT                      0x04
/* Values used for Window Covering Get command */
#define WINDOW_COVERING_GET_OUT_LEFT_1                                                   0x00
#define WINDOW_COVERING_GET_OUT_LEFT_2                                                   0x01
#define WINDOW_COVERING_GET_OUT_RIGHT_1                                                  0x02
#define WINDOW_COVERING_GET_OUT_RIGHT_2                                                  0x03
#define WINDOW_COVERING_GET_IN_LEFT_1                                                    0x04
#define WINDOW_COVERING_GET_IN_LEFT_2                                                    0x05
#define WINDOW_COVERING_GET_IN_RIGHT_1                                                   0x06
#define WINDOW_COVERING_GET_IN_RIGHT_2                                                   0x07
#define WINDOW_COVERING_GET_IN_RIGHT_LEFT_1                                              0x08
#define WINDOW_COVERING_GET_IN_RIGHT_LEFT_2                                              0x09
#define WINDOW_COVERING_GET_VERTICAL_SLATS_ANGLE_1                                       0x0A
#define WINDOW_COVERING_GET_VERTICAL_SLATS_ANGLE_2                                       0x0B
#define WINDOW_COVERING_GET_OUT_BOTTOM_1                                                 0x0C
#define WINDOW_COVERING_GET_OUT_BOTTOM_2                                                 0x0D
#define WINDOW_COVERING_GET_OUT_TOP_1                                                    0x0E
#define WINDOW_COVERING_GET_OUT_TOP_2                                                    0x0F
#define WINDOW_COVERING_GET_IN_BOTTOM_1                                                  0x10
#define WINDOW_COVERING_GET_IN_BOTTOM_2                                                  0x11
#define WINDOW_COVERING_GET_IN_TOP_1                                                     0x12
#define WINDOW_COVERING_GET_IN_TOP_2                                                     0x13
#define WINDOW_COVERING_GET_IN_TOP_BOTTOM_1                                              0x14
#define WINDOW_COVERING_GET_IN_TOP_BOTTOM_2                                              0x15
#define WINDOW_COVERING_GET_HORIZONTAL_SLATS_ANGLE_1                                     0x16
#define WINDOW_COVERING_GET_HORIZONTAL_SLATS_ANGLE_2                                     0x17
/* Values used for Window Covering Report command */
#define WINDOW_COVERING_REPORT_OUT_LEFT_1                                                0x00
#define WINDOW_COVERING_REPORT_OUT_LEFT_2                                                0x01
#define WINDOW_COVERING_REPORT_OUT_RIGHT_1                                               0x02
#define WINDOW_COVERING_REPORT_OUT_RIGHT_2                                               0x03
#define WINDOW_COVERING_REPORT_IN_LEFT_1                                                 0x04
#define WINDOW_COVERING_REPORT_IN_LEFT_2                                                 0x05
#define WINDOW_COVERING_REPORT_IN_RIGHT_1                                                0x06
#define WINDOW_COVERING_REPORT_IN_RIGHT_2                                                0x07
#define WINDOW_COVERING_REPORT_IN_RIGHT_LEFT_1                                           0x08
#define WINDOW_COVERING_REPORT_IN_RIGHT_LEFT_2                                           0x09
#define WINDOW_COVERING_REPORT_VERTICAL_SLATS_ANGLE_1                                    0x0A
#define WINDOW_COVERING_REPORT_VERTICAL_SLATS_ANGLE_2                                    0x0B
#define WINDOW_COVERING_REPORT_OUT_BOTTOM_1                                              0x0C
#define WINDOW_COVERING_REPORT_OUT_BOTTOM_2                                              0x0D
#define WINDOW_COVERING_REPORT_OUT_TOP_1                                                 0x0E
#define WINDOW_COVERING_REPORT_OUT_TOP_2                                                 0x0F
#define WINDOW_COVERING_REPORT_IN_BOTTOM_1                                               0x10
#define WINDOW_COVERING_REPORT_IN_BOTTOM_2                                               0x11
#define WINDOW_COVERING_REPORT_IN_TOP_1                                                  0x12
#define WINDOW_COVERING_REPORT_IN_TOP_2                                                  0x13
#define WINDOW_COVERING_REPORT_IN_TOP_BOTTOM_1                                           0x14
#define WINDOW_COVERING_REPORT_IN_TOP_BOTTOM_2                                           0x15
#define WINDOW_COVERING_REPORT_HORIZONTAL_SLATS_ANGLE_1                                  0x16
#define WINDOW_COVERING_REPORT_HORIZONTAL_SLATS_ANGLE_2                                  0x17
/* Values used for Window Covering Set command */
#define WINDOW_COVERING_SET_PROPERTIES1_PARAMETER_COUNT_MASK                             0x1F
#define WINDOW_COVERING_SET_PROPERTIES1_RESERVED_MASK                                    0xE0
#define WINDOW_COVERING_SET_PROPERTIES1_RESERVED_SHIFT                                   0x05
#define WINDOW_COVERING_SET_OUT_LEFT_1                                                   0x00
#define WINDOW_COVERING_SET_OUT_LEFT_2                                                   0x01
#define WINDOW_COVERING_SET_OUT_RIGHT_1                                                  0x02
#define WINDOW_COVERING_SET_OUT_RIGHT_2                                                  0x03
#define WINDOW_COVERING_SET_IN_LEFT_1                                                    0x04
#define WINDOW_COVERING_SET_IN_LEFT_2                                                    0x05
#define WINDOW_COVERING_SET_IN_RIGHT_1                                                   0x06
#define WINDOW_COVERING_SET_IN_RIGHT_2                                                   0x07
#define WINDOW_COVERING_SET_IN_RIGHT_LEFT_1                                              0x08
#define WINDOW_COVERING_SET_IN_RIGHT_LEFT_2                                              0x09
#define WINDOW_COVERING_SET_VERTICAL_SLATS_ANGLE_1                                       0x0A
#define WINDOW_COVERING_SET_VERTICAL_SLATS_ANGLE_2                                       0x0B
#define WINDOW_COVERING_SET_OUT_BOTTOM_1                                                 0x0C
#define WINDOW_COVERING_SET_OUT_BOTTOM_2                                                 0x0D
#define WINDOW_COVERING_SET_OUT_TOP_1                                                    0x0E
#define WINDOW_COVERING_SET_OUT_TOP_2                                                    0x0F
#define WINDOW_COVERING_SET_IN_BOTTOM_1                                                  0x10
#define WINDOW_COVERING_SET_IN_BOTTOM_2                                                  0x11
#define WINDOW_COVERING_SET_IN_TOP_1                                                     0x12
#define WINDOW_COVERING_SET_IN_TOP_2                                                     0x13
#define WINDOW_COVERING_SET_IN_TOP_BOTTOM_1                                              0x14
#define WINDOW_COVERING_SET_IN_TOP_BOTTOM_2                                              0x15
#define WINDOW_COVERING_SET_HORIZONTAL_SLATS_ANGLE_1                                     0x16
#define WINDOW_COVERING_SET_HORIZONTAL_SLATS_ANGLE_2                                     0x17
/* Values used for Window Covering Start Level Change command */
#define WINDOW_COVERING_START_LEVEL_CHANGE_PROPERTIES1_RES1_MASK                         0x3F
#define WINDOW_COVERING_START_LEVEL_CHANGE_PROPERTIES1_UP_DOWN_BIT_MASK                  0x40
#define WINDOW_COVERING_START_LEVEL_CHANGE_PROPERTIES1_RES2_BIT_MASK                     0x80
#define WINDOW_COVERING_START_LEVEL_CHANGE_OUT_LEFT_1                                    0x00
#define WINDOW_COVERING_START_LEVEL_CHANGE_OUT_LEFT_2                                    0x01
#define WINDOW_COVERING_START_LEVEL_CHANGE_OUT_RIGHT_1                                   0x02
#define WINDOW_COVERING_START_LEVEL_CHANGE_OUT_RIGHT_2                                   0x03
#define WINDOW_COVERING_START_LEVEL_CHANGE_IN_LEFT_1                                     0x04
#define WINDOW_COVERING_START_LEVEL_CHANGE_IN_LEFT_2                                     0x05
#define WINDOW_COVERING_START_LEVEL_CHANGE_IN_RIGHT_1                                    0x06
#define WINDOW_COVERING_START_LEVEL_CHANGE_IN_RIGHT_2                                    0x07
#define WINDOW_COVERING_START_LEVEL_CHANGE_IN_RIGHT_LEFT_1                               0x08
#define WINDOW_COVERING_START_LEVEL_CHANGE_IN_RIGHT_LEFT_2                               0x09
#define WINDOW_COVERING_START_LEVEL_CHANGE_VERTICAL_SLATS_ANGLE_1                        0x0A
#define WINDOW_COVERING_START_LEVEL_CHANGE_VERTICAL_SLATS_ANGLE_2                        0x0B
#define WINDOW_COVERING_START_LEVEL_CHANGE_OUT_BOTTOM_1                                  0x0C
#define WINDOW_COVERING_START_LEVEL_CHANGE_OUT_BOTTOM_2                                  0x0D
#define WINDOW_COVERING_START_LEVEL_CHANGE_OUT_TOP_1                                     0x0E
#define WINDOW_COVERING_START_LEVEL_CHANGE_OUT_TOP_2                                     0x0F
#define WINDOW_COVERING_START_LEVEL_CHANGE_IN_BOTTOM_1                                   0x10
#define WINDOW_COVERING_START_LEVEL_CHANGE_IN_BOTTOM_2                                   0x11
#define WINDOW_COVERING_START_LEVEL_CHANGE_IN_TOP_1                                      0x12
#define WINDOW_COVERING_START_LEVEL_CHANGE_IN_TOP_2                                      0x13
#define WINDOW_COVERING_START_LEVEL_CHANGE_IN_TOP_BOTTOM_1                               0x14
#define WINDOW_COVERING_START_LEVEL_CHANGE_IN_TOP_BOTTOM_2                               0x15
#define WINDOW_COVERING_START_LEVEL_CHANGE_HORIZONTAL_SLATS_ANGLE_1                      0x16
#define WINDOW_COVERING_START_LEVEL_CHANGE_HORIZONTAL_SLATS_ANGLE_2                      0x17
/* Values used for Window Covering Stop Level Change command */
#define WINDOW_COVERING_STOP_LEVEL_CHANGE_OUT_LEFT_1                                     0x00
#define WINDOW_COVERING_STOP_LEVEL_CHANGE_OUT_LEFT_2                                     0x01
#define WINDOW_COVERING_STOP_LEVEL_CHANGE_OUT_RIGHT_1                                    0x02
#define WINDOW_COVERING_STOP_LEVEL_CHANGE_OUT_RIGHT_2                                    0x03
#define WINDOW_COVERING_STOP_LEVEL_CHANGE_IN_LEFT_1                                      0x04
#define WINDOW_COVERING_STOP_LEVEL_CHANGE_IN_LEFT_2                                      0x05
#define WINDOW_COVERING_STOP_LEVEL_CHANGE_IN_RIGHT_1                                     0x06
#define WINDOW_COVERING_STOP_LEVEL_CHANGE_IN_RIGHT_2                                     0x07
#define WINDOW_COVERING_STOP_LEVEL_CHANGE_IN_RIGHT_LEFT_1                                0x08
#define WINDOW_COVERING_STOP_LEVEL_CHANGE_IN_RIGHT_LEFT_2                                0x09
#define WINDOW_COVERING_STOP_LEVEL_CHANGE_VERTICAL_SLATS_ANGLE_1                         0x0A
#define WINDOW_COVERING_STOP_LEVEL_CHANGE_VERTICAL_SLATS_ANGLE_2                         0x0B
#define WINDOW_COVERING_STOP_LEVEL_CHANGE_OUT_BOTTOM_1                                   0x0C
#define WINDOW_COVERING_STOP_LEVEL_CHANGE_OUT_BOTTOM_2                                   0x0D
#define WINDOW_COVERING_STOP_LEVEL_CHANGE_OUT_TOP_1                                      0x0E
#define WINDOW_COVERING_STOP_LEVEL_CHANGE_OUT_TOP_2                                      0x0F
#define WINDOW_COVERING_STOP_LEVEL_CHANGE_IN_BOTTOM_1                                    0x10
#define WINDOW_COVERING_STOP_LEVEL_CHANGE_IN_BOTTOM_2                                    0x11
#define WINDOW_COVERING_STOP_LEVEL_CHANGE_IN_TOP_1                                       0x12
#define WINDOW_COVERING_STOP_LEVEL_CHANGE_IN_TOP_2                                       0x13
#define WINDOW_COVERING_STOP_LEVEL_CHANGE_IN_TOP_BOTTOM_1                                0x14
#define WINDOW_COVERING_STOP_LEVEL_CHANGE_IN_TOP_BOTTOM_2                                0x15
#define WINDOW_COVERING_STOP_LEVEL_CHANGE_HORIZONTAL_SLATS_ANGLE_1                       0x16
#define WINDOW_COVERING_STOP_LEVEL_CHANGE_HORIZONTAL_SLATS_ANGLE_2                       0x17

int zuno_CCWindowCoveringHandler(uint8_t channel, ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report);

#endif // ZWCC_WINDOW_COVERING_H