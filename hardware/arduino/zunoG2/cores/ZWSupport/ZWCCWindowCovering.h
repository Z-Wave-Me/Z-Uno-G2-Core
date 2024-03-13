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

#define WINDOW_COVERING_PARAMETER_ID_OUT_LEFT_NA_DEFAULT								(0x00)
#define WINDOW_COVERING_PARAMETER_ID_OUT_LEFT_DEFAULT									(0x01)
#define WINDOW_COVERING_PARAMETER_ID_OUT_RIGHT_NA_DEFAULT								(0x02)
#define WINDOW_COVERING_PARAMETER_ID_OUT_RIGHT_DEFAULT									(0x03)
#define WINDOW_COVERING_PARAMETER_ID_IN_LEFT_NA_DEFAULT									(0x04)
#define WINDOW_COVERING_PARAMETER_ID_IN_LEFT_DEFAULT									(0x05)
#define WINDOW_COVERING_PARAMETER_ID_IN_RIGHT_NA_DEFAULT								(0x06)
#define WINDOW_COVERING_PARAMETER_ID_IN_RIGHT_DEFAULT									(0x07)
#define WINDOW_COVERING_PARAMETER_ID_IN_RIGHT_LEFT_NA_DEFAULT							(0x08)
#define WINDOW_COVERING_PARAMETER_ID_IN_RIGHT_LEFT_DEFAULT								(0x09)
#define WINDOW_COVERING_PARAMETER_ID_VERTICAL_SLATS_ANGLE_NA_DEFAULT					(0x0A)
#define WINDOW_COVERING_PARAMETER_ID_VERTICAL_SLATS_ANGLE_DEFAULT						(0x0B)
#define WINDOW_COVERING_PARAMETER_ID_OUT_BOTTOM_NA_DEFAULT								(0x0C)
#define WINDOW_COVERING_PARAMETER_ID_OUT_BOTTOM_DEFAULT									(0x0D)
#define WINDOW_COVERING_PARAMETER_ID_OUT_TOP_NA_DEFAULT									(0x0E)
#define WINDOW_COVERING_PARAMETER_ID_OUT_TOP_DEFAULT									(0x0F)
#define WINDOW_COVERING_PARAMETER_ID_IN_BOTTOM_NA_DEFAULT								(0x10)
#define WINDOW_COVERING_PARAMETER_ID_IN_BOTTOM_DEFAULT									(0x11)
#define WINDOW_COVERING_PARAMETER_ID_IN_TOP_NA_DEFAULT									(0x12)
#define WINDOW_COVERING_PARAMETER_ID_IN_TOP_DEFAULT										(0x13)
#define WINDOW_COVERING_PARAMETER_ID_IN_TOP_BOTTOM_NA_DEFAULT							(0x14)
#define WINDOW_COVERING_PARAMETER_ID_IN_TOP_BOTTOM_DEFAULT								(0x15)
#define WINDOW_COVERING_PARAMETER_ID_HORIZONTAL_SLATS_ANGLE_NA_DEFAULT					(0x16)
#define WINDOW_COVERING_PARAMETER_ID_HORIZONTAL_SLATS_ANGLE_DEFAULT						(0x17)

#define WINDOW_COVERING_PARAMETER_ID_OUT_LEFT_NA										(0x1 << 0x00)
#define WINDOW_COVERING_PARAMETER_ID_OUT_LEFT											(0x1 << 0x01)
#define WINDOW_COVERING_PARAMETER_ID_OUT_RIGHT_NA										(0x1 << 0x02)
#define WINDOW_COVERING_PARAMETER_ID_OUT_RIGHT											(0x1 << 0x03)
#define WINDOW_COVERING_PARAMETER_ID_IN_LEFT_NA											(0x1 << 0x04)
#define WINDOW_COVERING_PARAMETER_ID_IN_LEFT											(0x1 << 0x05)
#define WINDOW_COVERING_PARAMETER_ID_IN_RIGHT_NA										(0x1 << 0x06)
#define WINDOW_COVERING_PARAMETER_ID_IN_RIGHT											(0x1 << 0x07)
#define WINDOW_COVERING_PARAMETER_ID_IN_RIGHT_LEFT_NA									(0x1 << 0x08)
#define WINDOW_COVERING_PARAMETER_ID_IN_RIGHT_LEFT										(0x1 << 0x09)
#define WINDOW_COVERING_PARAMETER_ID_VERTICAL_SLATS_ANGLE_NA							(0x1 << 0x0A)
#define WINDOW_COVERING_PARAMETER_ID_VERTICAL_SLATS_ANGLE								(0x1 << 0x0B)
#define WINDOW_COVERING_PARAMETER_ID_OUT_BOTTOM_NA										(0x1 << 0x0C)
#define WINDOW_COVERING_PARAMETER_ID_OUT_BOTTOM											(0x1 << 0x0D)
#define WINDOW_COVERING_PARAMETER_ID_OUT_TOP_NA											(0x1 << 0x0E)
#define WINDOW_COVERING_PARAMETER_ID_OUT_TOP											(0x1 << 0x0F)
#define WINDOW_COVERING_PARAMETER_ID_IN_BOTTOM_NA										(0x1 << 0x10)
#define WINDOW_COVERING_PARAMETER_ID_IN_BOTTOM											(0x1 << 0x11)
#define WINDOW_COVERING_PARAMETER_ID_IN_TOP_NA											(0x1 << 0x12)
#define WINDOW_COVERING_PARAMETER_ID_IN_TOP												(0x1 << 0x13)
#define WINDOW_COVERING_PARAMETER_ID_IN_TOP_BOTTOM_NA									(0x1 << 0x14)
#define WINDOW_COVERING_PARAMETER_ID_IN_TOP_BOTTOM										(0x1 << 0x15)
#define WINDOW_COVERING_PARAMETER_ID_HORIZONTAL_SLATS_ANGLE_NA							(0x1 << 0x16)
#define WINDOW_COVERING_PARAMETER_ID_HORIZONTAL_SLATS_ANGLE								(0x1 << 0x17)
#define WINDOW_COVERING_PARAMETER_ID_MASK												0xFFFFFF

typedef struct _ZW_WINDOW_COVERING_SUPPORTED_REPORT_1BYTE_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   properties1;                  /* masked byte */
    uint8_t   parameterMask[];               
} ZW_WINDOW_COVERING_SUPPORTED_REPORT_1BYTE_FRAME;

/************************************************************/
/* Window Covering Set variant group structs */             
/************************************************************/
typedef struct _VG_WINDOW_COVERING_SET_VG_
{
    uint8_t   parameterId;                  /**/
    uint8_t   value;                        /**/
} VG_WINDOW_COVERING_SET_VG;

/************************************************************/
/* Window Covering Set 1byte command class structs */       
/************************************************************/
typedef struct _ZW_WINDOW_COVERING_SET_1BYTE_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   properties1;                  /* masked byte */
    VG_WINDOW_COVERING_SET_VG variantgroup1[];                /**/
} ZW_WINDOW_COVERING_SET_1BYTE_FRAME;

/************************************************************/
/* Window Covering Get command class structs */             
/************************************************************/
typedef struct _ZW_WINDOW_COVERING_GET_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   parameterId;                  /**/
} ZW_WINDOW_COVERING_GET_FRAME;

/************************************************************/
/* Window Covering Report command class structs */          
/************************************************************/
typedef struct _ZW_WINDOW_COVERING_REPORT_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   parameterId;                  /**/
    uint8_t   currentValue;                 /**/
    uint8_t   targetValue;                  /**/
    uint8_t   duration;                     /**/
} ZW_WINDOW_COVERING_REPORT_FRAME;

/************************************************************/
/* Window Covering Start Level Change command class structs */
/************************************************************/
typedef struct _ZW_WINDOW_COVERING_START_LEVEL_CHANGE_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   properties1;                  /* masked byte */
    uint8_t   parameterId;                  /**/
    uint8_t   duration;                     /**/
} ZW_WINDOW_COVERING_START_LEVEL_CHANGE_FRAME;

/************************************************************/
/* Window Covering Stop Level Change command class structs */
/************************************************************/
typedef struct _ZW_WINDOW_COVERING_STOP_LEVEL_CHANGE_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   parameterId;                  /**/
} ZW_WINDOW_COVERING_STOP_LEVEL_CHANGE_FRAME;

void __zunoWindowCoveringSet(uint8_t channel, uint8_t value);
uint8_t __zunoWindowCoveringGet(uint8_t channel);

void __zuno_CCWindowCoveringTimerStop(uint8_t channel);
void __zuno_CCWindowCoveringGetValues(uint8_t channel, uint8_t *current_value, uint8_t *duration_table_8, uint8_t *target_value);

int zuno_CCWindowCoveringHandler(uint8_t channel, ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report);
int zuno_CCWindowCoveringReport(uint8_t channel, ZUNOCommandPacket_t *packet);

#endif // ZWCC_WINDOW_COVERING_H