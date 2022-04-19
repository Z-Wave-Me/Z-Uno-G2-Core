#ifndef ZWCC_INDICATOR_H
#define ZWCC_INDICATOR_H

/* Indicator IDs */
#define INDICATOR_ID_NA											INDICATOR_SET_NA_V4
#define INDICATOR_ID_CODE_ACCEPTED								INDICATOR_SET_OK_V4
#define INDICATOR_ID_CODE_NOT_ACCEPTED							INDICATOR_SET_NOT_OK_V4
#define INDICATOR_ID_NODE_IDENTIFY								INDICATOR_SET_NODE_IDENTIFY_V4

#define INDICATOR_TOGGLING_STATE_ON									0x1
#define INDICATOR_TOGGLING_STATE_OFF								0x2

#define INDICATOR_PROP_TYPE_BINARY									0x2
#define INDICATOR_PROP_TYPE_TOGGLING								0x3
#define INDICATOR_PROP_TYPE_TIMEOUT									0x4

/* Property IDs */
#define INDICATOR_PROP_BINARY									INDICATOR_SET_BINARY_V4
#define INDICATOR_PROP_BINARY_MASK								((0x1 << INDICATOR_PROP_BINARY))

#define INDICATOR_PROP_TOGGLING_ON_OFF_PERIOD					INDICATOR_SET_ON_OFF_PERIOD_V4
#define INDICATOR_PROP_TOGGLING_ON_OFF_CYCLES					INDICATOR_SET_ON_OFF_CYCLES_V4
#define INDICATOR_PROP_TOGGLING_ON_TIME							INDICATOR_SET_ONE_TIME_ON_OFF_PERIOD_V4
#define INDICATOR_PROP_TOGGLING_MASK							((0x1 << INDICATOR_PROP_TOGGLING_ON_OFF_PERIOD) | (0x1 << INDICATOR_PROP_TOGGLING_ON_OFF_CYCLES) | (0x1 << INDICATOR_PROP_TOGGLING_ON_TIME))

#define INDICATOR_PROP_TIMEOUT_HOURS							0xA
#define INDICATOR_PROP_TIMEOUT_MINUTES							INDICATOR_SET_TIMEOUT_MINUTES_V4
#define INDICATOR_PROP_TIMEOUT_SECONDS							INDICATOR_SET_TIMEOUT_SECONDS_V4
#define INDICATOR_PROP_TIMEOUT_MASK								((0x1 << INDICATOR_PROP_TIMEOUT_HOURS) | (0x1 << INDICATOR_PROP_TIMEOUT_MINUTES) | (0x1 << INDICATOR_PROP_TIMEOUT_SECONDS))

#define INDICATOR_PROP_SUPPORT_MASK								(INDICATOR_PROP_TIMEOUT_MASK | INDICATOR_PROP_TOGGLING_MASK | INDICATOR_PROP_BINARY_MASK)


/* Indicator command class commands */
#define INDICATOR_VERSION                                                                0x04
#define INDICATOR_GET_V4                                                                 0x02
#define INDICATOR_REPORT_V4                                                              0x03
#define INDICATOR_SET_V4                                                                 0x01
#define INDICATOR_SUPPORTED_GET_V4                                                       0x04
#define INDICATOR_SUPPORTED_REPORT_V4                                                    0x05
#define INDICATOR_DESCRIPTION_GET_V4                                                     0x06
#define INDICATOR_DESCRIPTION_REPORT_V4                                                  0x07
/* Values used for Indicator Get command */
#define INDICATOR_GET_NA_V4                                                              0x00
#define INDICATOR_GET_ARMED_V4                                                           0x01
#define INDICATOR_GET_NOT_ARMED_V4                                                       0x02
#define INDICATOR_GET_READY_V4                                                           0x03
#define INDICATOR_GET_FAULT_V4                                                           0x04
#define INDICATOR_GET_BUSY_V4                                                            0x05
#define INDICATOR_GET_ENTER_ID_V4                                                        0x06
#define INDICATOR_GET_ENTER_PIN_V4                                                       0x07
#define INDICATOR_GET_OK_V4                                                              0x08
#define INDICATOR_GET_NOT_OK_V4                                                          0x09
#define INDICATOR_GET_ARMED_STAY_V4                                                      0x0A
#define INDICATOR_GET_ARMED_AWAY_V4                                                      0x0B
#define INDICATOR_GET_ALARMING_V4                                                        0x0C
#define INDICATOR_GET_ALARMING_BURGLAR_V4                                                0x0D
#define INDICATOR_GET_ALARMING_SMOKE_FIRE_V4                                             0x0E
#define INDICATOR_GET_ALARMING_CARBON_MONOXIDE_V4                                        0x0F
#define INDICATOR_GET_BYPASS_CHALLENGE_V4                                                0x10
#define INDICATOR_GET_ENTRY_DELAY_V4                                                     0x11
#define INDICATOR_GET_EXIT_DELAY_V4                                                      0x12
#define INDICATOR_GET_ZONE1_ARMED_V4                                                     0x20
#define INDICATOR_GET_ZONE2_ARMED_V4                                                     0x21
#define INDICATOR_GET_ZONE3_ARMED_V4                                                     0x22
#define INDICATOR_GET_ZONE4_ARMED_V4                                                     0x23
#define INDICATOR_GET_ZONE5_ARMED_V4                                                     0x24
#define INDICATOR_GET_ZONE6_ARMED_V4                                                     0x25
#define INDICATOR_GET_LCD_BACKLIGHT_V4                                                   0x30
#define INDICATOR_GET_BUTTON_BACKLIGHT_LETTERS_V4                                        0x40
#define INDICATOR_GET_BUTTON_BACKLIGHT_DIGITS_V4                                         0x41
#define INDICATOR_GET_BUTTON_BACKLIGHT_COMMAND_V4                                        0x42
#define INDICATOR_GET_BUTTON1_INDICATION_V4                                              0x43
#define INDICATOR_GET_BUTTON2_INDICATION_V4                                              0x44
#define INDICATOR_GET_BUTTON3_INDICATION_V4                                              0x45
#define INDICATOR_GET_BUTTON4_INDICATION_V4                                              0x46
#define INDICATOR_GET_BUTTON5_INDICATION_V4                                              0x47
#define INDICATOR_GET_BUTTON6_INDICATION_V4                                              0x48
#define INDICATOR_GET_BUTTON7_INDICATION_V4                                              0x49
#define INDICATOR_GET_BUTTON8_INDICATION_V4                                              0x4A
#define INDICATOR_GET_BUTTON9_INDICATION_V4                                              0x4B
#define INDICATOR_GET_BUTTON10_INDICATION_V4                                             0x4C
#define INDICATOR_GET_BUTTON11_INDICATION_V4                                             0x4D
#define INDICATOR_GET_BUTTON12_INDICATION_V4                                             0x4E
#define INDICATOR_GET_NODE_IDENTIFY_V4                                                   0x50
#define INDICATOR_GET_BUZZER_V4                                                          0xF0
/* Values used for Indicator Report command */
#define INDICATOR_REPORT_PROPERTIES1_INDICATOR_OBJECT_COUNT_MASK_V4                      0x1F
#define INDICATOR_REPORT_PROPERTIES1_RESERVED_MASK_V4                                    0xE0
#define INDICATOR_REPORT_PROPERTIES1_RESERVED_SHIFT_V4                                   0x05
#define INDICATOR_REPORT_NA_V4                                                           0x00
#define INDICATOR_REPORT_ARMED_V4                                                        0x01
#define INDICATOR_REPORT_NOT_ARMED_V4                                                    0x02
#define INDICATOR_REPORT_READY_V4                                                        0x03
#define INDICATOR_REPORT_FAULT_V4                                                        0x04
#define INDICATOR_REPORT_BUSY_V4                                                         0x05
#define INDICATOR_REPORT_ENTER_ID_V4                                                     0x06
#define INDICATOR_REPORT_ENTER_PIN_V4                                                    0x07
#define INDICATOR_REPORT_OK_V4                                                           0x08
#define INDICATOR_REPORT_NOT_OK_V4                                                       0x09
#define INDICATOR_REPORT_ARMED_STAY_V4                                                   0x0A
#define INDICATOR_REPORT_ARMED_AWAY_V4                                                   0x0B
#define INDICATOR_REPORT_ALARMING_V4                                                     0x0C
#define INDICATOR_REPORT_ALARMING_BURGLAR_V4                                             0x0D
#define INDICATOR_REPORT_ALARMING_SMOKE_FIRE_V4                                          0x0E
#define INDICATOR_REPORT_ALARMING_CARBON_MONOXIDE_V4                                     0x0F
#define INDICATOR_REPORT_BYPASS_CHALLENGE_V4                                             0x10
#define INDICATOR_REPORT_ENTRY_DELAY_V4                                                  0x11
#define INDICATOR_REPORT_EXIT_DELAY_V4                                                   0x12
#define INDICATOR_REPORT_ZONE1_ARMED_V4                                                  0x20
#define INDICATOR_REPORT_ZONE2_ARMED_V4                                                  0x21
#define INDICATOR_REPORT_ZONE3_ARMED_V4                                                  0x22
#define INDICATOR_REPORT_ZONE4_ARMED_V4                                                  0x23
#define INDICATOR_REPORT_ZONE5_ARMED_V4                                                  0x24
#define INDICATOR_REPORT_ZONE6_ARMED_V4                                                  0x25
#define INDICATOR_REPORT_LCD_BACKLIGHT_V4                                                0x30
#define INDICATOR_REPORT_BUTTON_BACKLIGHT_LETTERS_V4                                     0x40
#define INDICATOR_REPORT_BUTTON_BACKLIGHT_DIGITS_V4                                      0x41
#define INDICATOR_REPORT_BUTTON_BACKLIGHT_COMMAND_V4                                     0x42
#define INDICATOR_REPORT_BUTTON1_INDICATION_V4                                           0x43
#define INDICATOR_REPORT_BUTTON2_INDICATION_V4                                           0x44
#define INDICATOR_REPORT_BUTTON3_INDICATION_V4                                           0x45
#define INDICATOR_REPORT_BUTTON4_INDICATION_V4                                           0x46
#define INDICATOR_REPORT_BUTTON5_INDICATION_V4                                           0x47
#define INDICATOR_REPORT_BUTTON6_INDICATION_V4                                           0x48
#define INDICATOR_REPORT_BUTTON7_INDICATION_V4                                           0x49
#define INDICATOR_REPORT_BUTTON8_INDICATION_V4                                           0x4A
#define INDICATOR_REPORT_BUTTON9_INDICATION_V4                                           0x4B
#define INDICATOR_REPORT_BUTTON10_INDICATION_V4                                          0x4C
#define INDICATOR_REPORT_BUTTON11_INDICATION_V4                                          0x4D
#define INDICATOR_REPORT_BUTTON12_INDICATION_V4                                          0x4E
#define INDICATOR_REPORT_NODE_IDENTIFY_V4                                                0x50
#define INDICATOR_REPORT_BUZZER_V4                                                       0xF0
#define INDICATOR_REPORT_MULTILEVEL_V4                                                   0x01
#define INDICATOR_REPORT_BINARY_V4                                                       0x02
#define INDICATOR_REPORT_ON_OFF_PERIOD_V4                                                0x03
#define INDICATOR_REPORT_ON_OFF_CYCLES_V4                                                0x04
#define INDICATOR_REPORT_ONE_TIME_ON_OFF_PERIOD_V4                                       0x05
#define INDICATOR_REPORT_TIMEOUT_MINUTES_V4                                              0x06
#define INDICATOR_REPORT_TIMEOUT_SECONDS_V4                                              0x07
#define INDICATOR_REPORT_TIMEOUT_1_100_SECONDS_V4                                        0x08
#define INDICATOR_REPORT_SPECIFIC_VOLUME_V4                                              0x09
#define INDICATOR_REPORT_LOW_POWER_V4                                                    0x10
/* Values used for Indicator Set command */
#define INDICATOR_SET_PROPERTIES1_INDICATOR_OBJECT_COUNT_MASK_V4                         0x1F
#define INDICATOR_SET_PROPERTIES1_RESERVED_MASK_V4                                       0xE0
#define INDICATOR_SET_PROPERTIES1_RESERVED_SHIFT_V4                                      0x05
#define INDICATOR_SET_NA_V4                                                              0x00
#define INDICATOR_SET_ARMED_V4                                                           0x01
#define INDICATOR_SET_NOT_ARMED_V4                                                       0x02
#define INDICATOR_SET_READY_V4                                                           0x03
#define INDICATOR_SET_FAULT_V4                                                           0x04
#define INDICATOR_SET_BUSY_V4                                                            0x05
#define INDICATOR_SET_ENTER_ID_V4                                                        0x06
#define INDICATOR_SET_ENTER_PIN_V4                                                       0x07
#define INDICATOR_SET_OK_V4                                                              0x08
#define INDICATOR_SET_NOT_OK_V4                                                          0x09
#define INDICATOR_SET_ARMED_STAY_V4                                                      0x0A
#define INDICATOR_SET_ARMED_AWAY_V4                                                      0x0B
#define INDICATOR_SET_ALARMING_V4                                                        0x0C
#define INDICATOR_SET_ALARMING_BURGLAR_V4                                                0x0D
#define INDICATOR_SET_ALARMING_SMOKE_FIRE_V4                                             0x0E
#define INDICATOR_SET_ALARMING_CARBON_MONOXIDE_V4                                        0x0F
#define INDICATOR_SET_BYPASS_CHALLENGE_V4                                                0x10
#define INDICATOR_SET_ENTRY_DELAY_V4                                                     0x11
#define INDICATOR_SET_EXIT_DELAY_V4                                                      0x12
#define INDICATOR_SET_ZONE1_ARMED_V4                                                     0x20
#define INDICATOR_SET_ZONE2_ARMED_V4                                                     0x21
#define INDICATOR_SET_ZONE3_ARMED_V4                                                     0x22
#define INDICATOR_SET_ZONE4_ARMED_V4                                                     0x23
#define INDICATOR_SET_ZONE5_ARMED_V4                                                     0x24
#define INDICATOR_SET_ZONE6_ARMED_V4                                                     0x25
#define INDICATOR_SET_LCD_BACKLIGHT_V4                                                   0x30
#define INDICATOR_SET_BUTTON_BACKLIGHT_LETTERS_V4                                        0x40
#define INDICATOR_SET_BUTTON_BACKLIGHT_DIGITS_V4                                         0x41
#define INDICATOR_SET_BUTTON_BACKLIGHT_COMMAND_V4                                        0x42
#define INDICATOR_SET_BUTTON1_INDICATION_V4                                              0x43
#define INDICATOR_SET_BUTTON2_INDICATION_V4                                              0x44
#define INDICATOR_SET_BUTTON3_INDICATION_V4                                              0x45
#define INDICATOR_SET_BUTTON4_INDICATION_V4                                              0x46
#define INDICATOR_SET_BUTTON5_INDICATION_V4                                              0x47
#define INDICATOR_SET_BUTTON6_INDICATION_V4                                              0x48
#define INDICATOR_SET_BUTTON7_INDICATION_V4                                              0x49
#define INDICATOR_SET_BUTTON8_INDICATION_V4                                              0x4A
#define INDICATOR_SET_BUTTON9_INDICATION_V4                                              0x4B
#define INDICATOR_SET_BUTTON10_INDICATION_V4                                             0x4C
#define INDICATOR_SET_BUTTON11_INDICATION_V4                                             0x4D
#define INDICATOR_SET_BUTTON12_INDICATION_V4                                             0x4E
#define INDICATOR_SET_NODE_IDENTIFY_V4                                                   0x50
#define INDICATOR_SET_BUZZER_V4                                                          0xF0
#define INDICATOR_SET_MULTILEVEL_V4                                                      0x01
#define INDICATOR_SET_BINARY_V4                                                          0x02
#define INDICATOR_SET_ON_OFF_PERIOD_V4                                                   0x03
#define INDICATOR_SET_ON_OFF_CYCLES_V4                                                   0x04
#define INDICATOR_SET_ONE_TIME_ON_OFF_PERIOD_V4                                          0x05
#define INDICATOR_SET_TIMEOUT_MINUTES_V4                                                 0x06
#define INDICATOR_SET_TIMEOUT_SECONDS_V4                                                 0x07
#define INDICATOR_SET_TIMEOUT_1_100_SECONDS_V4                                           0x08
#define INDICATOR_SET_SPECIFIC_VOLUME_V4                                                 0x09
#define INDICATOR_SET_LOW_POWER_V4                                                       0x10
/* Values used for Indicator Supported Get command */
#define INDICATOR_SUPPORTED_GET_NA_V4                                                    0x00
#define INDICATOR_SUPPORTED_GET_ARMED_V4                                                 0x01
#define INDICATOR_SUPPORTED_GET_NOT_ARMED_V4                                             0x02
#define INDICATOR_SUPPORTED_GET_READY_V4                                                 0x03
#define INDICATOR_SUPPORTED_GET_FAULT_V4                                                 0x04
#define INDICATOR_SUPPORTED_GET_BUSY_V4                                                  0x05
#define INDICATOR_SUPPORTED_GET_ENTER_ID_V4                                              0x06
#define INDICATOR_SUPPORTED_GET_ENTER_PIN_V4                                             0x07
#define INDICATOR_SUPPORTED_GET_OK_V4                                                    0x08
#define INDICATOR_SUPPORTED_GET_NOT_OK_V4                                                0x09
#define INDICATOR_SUPPORTED_GET_ARMED_STAY_V4                                            0x0A
#define INDICATOR_SUPPORTED_GET_ARMED_AWAY_V4                                            0x0B
#define INDICATOR_SUPPORTED_GET_ALARMING_V4                                              0x0C
#define INDICATOR_SUPPORTED_GET_ALARMING_BURGLAR_V4                                      0x0D
#define INDICATOR_SUPPORTED_GET_ALARMING_SMOKE_FIRE_V4                                   0x0E
#define INDICATOR_SUPPORTED_GET_ALARMING_CARBON_MONOXIDE_V4                              0x0F
#define INDICATOR_SUPPORTED_GET_BYPASS_CHALLENGE_V4                                      0x10
#define INDICATOR_SUPPORTED_GET_ENTRY_DELAY_V4                                           0x11
#define INDICATOR_SUPPORTED_GET_EXIT_DELAY_V4                                            0x12
#define INDICATOR_SUPPORTED_GET_ZONE1_ARMED_V4                                           0x20
#define INDICATOR_SUPPORTED_GET_ZONE2_ARMED_V4                                           0x21
#define INDICATOR_SUPPORTED_GET_ZONE3_ARMED_V4                                           0x22
#define INDICATOR_SUPPORTED_GET_ZONE4_ARMED_V4                                           0x23
#define INDICATOR_SUPPORTED_GET_ZONE5_ARMED_V4                                           0x24
#define INDICATOR_SUPPORTED_GET_ZONE6_ARMED_V4                                           0x25
#define INDICATOR_SUPPORTED_GET_LCD_BACKLIGHT_V4                                         0x30
#define INDICATOR_SUPPORTED_GET_BUTTON_BACKLIGHT_LETTERS_V4                              0x40
#define INDICATOR_SUPPORTED_GET_BUTTON_BACKLIGHT_DIGITS_V4                               0x41
#define INDICATOR_SUPPORTED_GET_BUTTON_BACKLIGHT_COMMAND_V4                              0x42
#define INDICATOR_SUPPORTED_GET_BUTTON1_INDICATION_V4                                    0x43
#define INDICATOR_SUPPORTED_GET_BUTTON2_INDICATION_V4                                    0x44
#define INDICATOR_SUPPORTED_GET_BUTTON3_INDICATION_V4                                    0x45
#define INDICATOR_SUPPORTED_GET_BUTTON4_INDICATION_V4                                    0x46
#define INDICATOR_SUPPORTED_GET_BUTTON5_INDICATION_V4                                    0x47
#define INDICATOR_SUPPORTED_GET_BUTTON6_INDICATION_V4                                    0x48
#define INDICATOR_SUPPORTED_GET_BUTTON7_INDICATION_V4                                    0x49
#define INDICATOR_SUPPORTED_GET_BUTTON8_INDICATION_V4                                    0x4A
#define INDICATOR_SUPPORTED_GET_BUTTON9_INDICATION_V4                                    0x4B
#define INDICATOR_SUPPORTED_GET_BUTTON10_INDICATION_V4                                   0x4C
#define INDICATOR_SUPPORTED_GET_BUTTON11_INDICATION_V4                                   0x4D
#define INDICATOR_SUPPORTED_GET_BUTTON12_INDICATION_V4                                   0x4E
#define INDICATOR_SUPPORTED_GET_NODE_IDENTIFY_V4                                         0x50
#define INDICATOR_SUPPORTED_GET_BUZZER_V4                                                0xF0
/* Values used for Indicator Supported Report command */
#define INDICATOR_SUPPORTED_REPORT_NA_V4                                                 0x00
#define INDICATOR_SUPPORTED_REPORT_ARMED_V4                                              0x01
#define INDICATOR_SUPPORTED_REPORT_NOT_ARMED_V4                                          0x02
#define INDICATOR_SUPPORTED_REPORT_READY_V4                                              0x03
#define INDICATOR_SUPPORTED_REPORT_FAULT_V4                                              0x04
#define INDICATOR_SUPPORTED_REPORT_BUSY_V4                                               0x05
#define INDICATOR_SUPPORTED_REPORT_ENTER_ID_V4                                           0x06
#define INDICATOR_SUPPORTED_REPORT_ENTER_PIN_V4                                          0x07
#define INDICATOR_SUPPORTED_REPORT_OK_V4                                                 0x08
#define INDICATOR_SUPPORTED_REPORT_NOT_OK_V4                                             0x09
#define INDICATOR_SUPPORTED_REPORT_ARMED_STAY_V4                                         0x0A
#define INDICATOR_SUPPORTED_REPORT_ARMED_AWAY_V4                                         0x0B
#define INDICATOR_SUPPORTED_REPORT_ALARMING_V4                                           0x0C
#define INDICATOR_SUPPORTED_REPORT_ALARMING_BURGLAR_V4                                   0x0D
#define INDICATOR_SUPPORTED_REPORT_ALARMING_SMOKE_FIRE_V4                                0x0E
#define INDICATOR_SUPPORTED_REPORT_ALARMING_CARBON_MONOXIDE_V4                           0x0F
#define INDICATOR_SUPPORTED_REPORT_BYPASS_CHALLENGE_V4                                   0x10
#define INDICATOR_SUPPORTED_REPORT_ENTRY_DELAY_V4                                        0x11
#define INDICATOR_SUPPORTED_REPORT_EXIT_DELAY_V4                                         0x12
#define INDICATOR_SUPPORTED_REPORT_ZONE1_ARMED_V4                                        0x20
#define INDICATOR_SUPPORTED_REPORT_ZONE2_ARMED_V4                                        0x21
#define INDICATOR_SUPPORTED_REPORT_ZONE3_ARMED_V4                                        0x22
#define INDICATOR_SUPPORTED_REPORT_ZONE4_ARMED_V4                                        0x23
#define INDICATOR_SUPPORTED_REPORT_ZONE5_ARMED_V4                                        0x24
#define INDICATOR_SUPPORTED_REPORT_ZONE6_ARMED_V4                                        0x25
#define INDICATOR_SUPPORTED_REPORT_LCD_BACKLIGHT_V4                                      0x30
#define INDICATOR_SUPPORTED_REPORT_BUTTON_BACKLIGHT_LETTERS_V4                           0x40
#define INDICATOR_SUPPORTED_REPORT_BUTTON_BACKLIGHT_DIGITS_V4                            0x41
#define INDICATOR_SUPPORTED_REPORT_BUTTON_BACKLIGHT_COMMAND_V4                           0x42
#define INDICATOR_SUPPORTED_REPORT_BUTTON1_INDICATION_V4                                 0x43
#define INDICATOR_SUPPORTED_REPORT_BUTTON2_INDICATION_V4                                 0x44
#define INDICATOR_SUPPORTED_REPORT_BUTTON3_INDICATION_V4                                 0x45
#define INDICATOR_SUPPORTED_REPORT_BUTTON4_INDICATION_V4                                 0x46
#define INDICATOR_SUPPORTED_REPORT_BUTTON5_INDICATION_V4                                 0x47
#define INDICATOR_SUPPORTED_REPORT_BUTTON6_INDICATION_V4                                 0x48
#define INDICATOR_SUPPORTED_REPORT_BUTTON7_INDICATION_V4                                 0x49
#define INDICATOR_SUPPORTED_REPORT_BUTTON8_INDICATION_V4                                 0x4A
#define INDICATOR_SUPPORTED_REPORT_BUTTON9_INDICATION_V4                                 0x4B
#define INDICATOR_SUPPORTED_REPORT_BUTTON10_INDICATION_V4                                0x4C
#define INDICATOR_SUPPORTED_REPORT_BUTTON11_INDICATION_V4                                0x4D
#define INDICATOR_SUPPORTED_REPORT_BUTTON12_INDICATION_V4                                0x4E
#define INDICATOR_SUPPORTED_REPORT_NODE_IDENTIFY_V4                                      0x50
#define INDICATOR_SUPPORTED_REPORT_BUZZER_V4                                             0xF0
#define INDICATOR_SUPPORTED_REPORT_NA_V4                                                 0x00
#define INDICATOR_SUPPORTED_REPORT_ARMED_V4                                              0x01
#define INDICATOR_SUPPORTED_REPORT_NOT_ARMED_V4                                          0x02
#define INDICATOR_SUPPORTED_REPORT_READY_V4                                              0x03
#define INDICATOR_SUPPORTED_REPORT_FAULT_V4                                              0x04
#define INDICATOR_SUPPORTED_REPORT_BUSY_V4                                               0x05
#define INDICATOR_SUPPORTED_REPORT_ENTER_ID_V4                                           0x06
#define INDICATOR_SUPPORTED_REPORT_ENTER_PIN_V4                                          0x07
#define INDICATOR_SUPPORTED_REPORT_OK_V4                                                 0x08
#define INDICATOR_SUPPORTED_REPORT_NOT_OK_V4                                             0x09
#define INDICATOR_SUPPORTED_REPORT_ARMED_STAY_V4                                         0x0A
#define INDICATOR_SUPPORTED_REPORT_ARMED_AWAY_V4                                         0x0B
#define INDICATOR_SUPPORTED_REPORT_ALARMING_V4                                           0x0C
#define INDICATOR_SUPPORTED_REPORT_ALARMING_BURGLAR_V4                                   0x0D
#define INDICATOR_SUPPORTED_REPORT_ALARMING_SMOKE_FIRE_V4                                0x0E
#define INDICATOR_SUPPORTED_REPORT_ALARMING_CARBON_MONOXIDE_V4                           0x0F
#define INDICATOR_SUPPORTED_REPORT_BYPASS_CHALLENGE_V4                                   0x10
#define INDICATOR_SUPPORTED_REPORT_ENTRY_DELAY_V4                                        0x11
#define INDICATOR_SUPPORTED_REPORT_EXIT_DELAY_V4                                         0x12
#define INDICATOR_SUPPORTED_REPORT_ZONE1_ARMED_V4                                        0x20
#define INDICATOR_SUPPORTED_REPORT_ZONE2_ARMED_V4                                        0x21
#define INDICATOR_SUPPORTED_REPORT_ZONE3_ARMED_V4                                        0x22
#define INDICATOR_SUPPORTED_REPORT_ZONE4_ARMED_V4                                        0x23
#define INDICATOR_SUPPORTED_REPORT_ZONE5_ARMED_V4                                        0x24
#define INDICATOR_SUPPORTED_REPORT_ZONE6_ARMED_V4                                        0x25
#define INDICATOR_SUPPORTED_REPORT_LCD_BACKLIGHT_V4                                      0x30
#define INDICATOR_SUPPORTED_REPORT_BUTTON_BACKLIGHT_LETTERS_V4                           0x40
#define INDICATOR_SUPPORTED_REPORT_BUTTON_BACKLIGHT_DIGITS_V4                            0x41
#define INDICATOR_SUPPORTED_REPORT_BUTTON_BACKLIGHT_COMMAND_V4                           0x42
#define INDICATOR_SUPPORTED_REPORT_BUTTON1_INDICATION_V4                                 0x43
#define INDICATOR_SUPPORTED_REPORT_BUTTON2_INDICATION_V4                                 0x44
#define INDICATOR_SUPPORTED_REPORT_BUTTON3_INDICATION_V4                                 0x45
#define INDICATOR_SUPPORTED_REPORT_BUTTON4_INDICATION_V4                                 0x46
#define INDICATOR_SUPPORTED_REPORT_BUTTON5_INDICATION_V4                                 0x47
#define INDICATOR_SUPPORTED_REPORT_BUTTON6_INDICATION_V4                                 0x48
#define INDICATOR_SUPPORTED_REPORT_BUTTON7_INDICATION_V4                                 0x49
#define INDICATOR_SUPPORTED_REPORT_BUTTON8_INDICATION_V4                                 0x4A
#define INDICATOR_SUPPORTED_REPORT_BUTTON9_INDICATION_V4                                 0x4B
#define INDICATOR_SUPPORTED_REPORT_BUTTON10_INDICATION_V4                                0x4C
#define INDICATOR_SUPPORTED_REPORT_BUTTON11_INDICATION_V4                                0x4D
#define INDICATOR_SUPPORTED_REPORT_BUTTON12_INDICATION_V4                                0x4E
#define INDICATOR_SUPPORTED_REPORT_NODE_IDENTIFY_V4                                      0x50
#define INDICATOR_SUPPORTED_REPORT_BUZZER_V4                                             0xF0
#define INDICATOR_SUPPORTED_REPORT_PROPERTIES1_PROPERTY_SUPPORTED_BIT_MASK_LENGTH_MASK_V4 0x1F
#define INDICATOR_SUPPORTED_REPORT_PROPERTIES1_RESERVED_MASK_V4                          0xE0
#define INDICATOR_SUPPORTED_REPORT_PROPERTIES1_RESERVED_SHIFT_V4                         0x05

/************************************************************/
/* Indicator Set command class structs */                   
/************************************************************/
typedef struct _ZW_INDICATOR_SET_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   value;                        /**/
} ZW_INDICATOR_SET_FRAME;

/************************************************************/
/* Indicator Set V4 variant group structs */                
/************************************************************/
typedef struct _VG_INDICATOR_SET_V4_VG_
{
    uint8_t   indicatorId;                  /**/
    uint8_t   propertyId;                   /**/
    uint8_t   value;                        /**/
} VG_INDICATOR_SET_V4_VG;

/************************************************************/
/* Indicator Set V4 command class structs */          
/************************************************************/
typedef struct								ZwIndicatorSetV4Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									indicator0Value;/**/
	uint8_t									properties1;/* masked byte */
	VG_INDICATOR_SET_V4_VG					variantgroup[];/**/
}											ZwIndicatorSetV4Frame_t;

typedef union								ZwIndicatorSetFrame_u {//For more convenient support, several versions of commands
	ZW_INDICATOR_SET_FRAME					v1;
	ZwIndicatorSetV4Frame_t					v4;
}											ZwIndicatorSetFrame_t;

/************************************************************/
/* Indicator Report command class structs */                
/************************************************************/
typedef struct _ZW_INDICATOR_REPORT_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   value;                        /**/
} ZW_INDICATOR_REPORT_FRAME;

/************************************************************/
/* Indicator Report V4 variant group structs */             
/************************************************************/
typedef struct _VG_INDICATOR_REPORT_V4_VG_
{
    uint8_t   indicatorId;                  /**/
    uint8_t   propertyId;                   /**/
    uint8_t   value;                        /**/
} VG_INDICATOR_REPORT_V4_VG;

/************************************************************/
/* Indicator Report V4 command class structs */       
/************************************************************/
typedef struct								ZwIndicatorReportV4Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									indicator0Value;/**/
	uint8_t									properties1;/* masked byte */
	VG_INDICATOR_REPORT_V4_VG				variantgroup[];/**/
}											ZwIndicatorReportV4Frame_t;

typedef union								ZwIndicatorReportFrame_u {//For more convenient support, several versions of commands
	ZW_INDICATOR_REPORT_FRAME				v1;
	ZwIndicatorReportV4Frame_t				v4;
}											ZwIndicatorReportFrame_t;

/************************************************************/
/* Indicator Get command class structs */                   
/************************************************************/
typedef struct _ZW_INDICATOR_GET_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
} ZW_INDICATOR_GET_FRAME;

/************************************************************/
/* Indicator Get V4 command class structs */                
/************************************************************/
typedef struct _ZW_INDICATOR_GET_V4_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   indicatorId;                  /**/
} ZW_INDICATOR_GET_V4_FRAME;


typedef union								ZwIndicatorGetFrame_u {//For more convenient support, several versions of commands
	ZW_INDICATOR_GET_FRAME					v1;
	ZW_INDICATOR_GET_V4_FRAME				v4;
}											ZwIndicatorGetFrame_t;

/************************************************************/
/* Indicator Description Report V4 command class structs */
/************************************************************/
typedef struct									ZwIndicatorDescriptionReportFrame_s
{
	uint8_t										cmdClass;/* The command class */
	uint8_t										cmd;/* The command */
	uint8_t										indicatorId;/**/
	uint8_t										descriptionLength;/**/
	uint8_t										description[];
}												ZwIndicatorDescriptionReportFrame_t;

/************************************************************/
/* Indicator Description Get V4 command class structs */    
/************************************************************/
typedef struct _ZW_INDICATOR_DESCRIPTION_GET_V4_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   indicatorId;                  /**/
} ZW_INDICATOR_DESCRIPTION_GET_V4_FRAME;

/************************************************************/
/* Indicator Supported Get V4 command class structs */      
/************************************************************/
typedef struct _ZW_INDICATOR_SUPPORTED_GET_V4_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   indicatorId;                  /**/
} ZW_INDICATOR_SUPPORTED_GET_V4_FRAME;

/************************************************************/
/* Indicator Supported Report command class structs */
/************************************************************/
typedef struct											ZwIndicatorSupportedReportFrame_s
{
	uint8_t												cmdClass;/* The command class */
	uint8_t												cmd;/* The command */
	uint8_t												indicatorId;/**/
	uint8_t												nextIndicatorId;/**/
	uint8_t												properties1;/* masked byte */
	uint8_t												propertySupportedBitMask[];
}														ZwIndicatorSupportedReportFrame_t;

typedef struct						ZunoIndicatorParameter_s
{
	const char						*description;
	uint16_t						support_prop_mask;
	uint8_t							pin;
	uint8_t							indicatorId;
}									ZunoIndicatorParameter_t;

typedef struct						ZunoIndicatorTimerPropBinary_s
{
	uint8_t							value;
}									ZunoIndicatorTimerPropBinary_t;

typedef struct						ZunoIndicatorTimerPropToggling_s
{
	uint16_t						on_time_ms;
	uint16_t						off_time_ms;
	uint8_t							on_off_period;
	uint8_t							on_off_cycles;
	uint8_t							loop;
	uint8_t							on_time;
	uint8_t							state;
}									ZunoIndicatorTimerPropToggling_t;

typedef struct						ZunoIndicatorTimerPropTimeout_s
{
	uint8_t							hours;
	uint8_t							minutes;
	uint8_t							seconds;
}									ZunoIndicatorTimerPropTimeout_t;

typedef union							ZunoIndicatorTimerProp_u
{
	ZunoIndicatorTimerPropToggling_t	toggling;
	ZunoIndicatorTimerPropBinary_t		binary;
	ZunoIndicatorTimerPropTimeout_t		timeout;
}										ZunoIndicatorTimerProp_t;

typedef struct						ZunoIndicatorTimer_s
{
	uint64_t						ms;
	ZunoIndicatorTimerProp_t		prop;
	uint8_t							type_prop;
	uint8_t							sleep_lock;
}									ZunoIndicatorTimer_t;

#define ZUNO_SETUP_INDICATOR(...) 	\
								static const ZunoIndicatorParameter_t __g_zuno_indicator_parameter[]= \
								{ \
									__VA_ARGS__, \
								};\
								static ZunoIndicatorTimer_t __g_zuno_lp_indicator_timer[(sizeof(__g_zuno_indicator_parameter) / sizeof(__g_zuno_indicator_parameter[0x0]))]; \
								const ZunoIndicatorParameter_t *zunoIndicatorGetParameterArrayUser(void) { \
									return (&__g_zuno_indicator_parameter[0x0]); \
								}; \
								ZunoIndicatorTimer_t *zunoIndicatorGetParameterArrayUserTimer(void) { \
									return (&__g_zuno_lp_indicator_timer[0x0]); \
								}; \
								const ZunoIndicatorParameter_t *zunoIndicatorGetParameterArrayUserEnd(void) { \
									return (&__g_zuno_indicator_parameter[(sizeof(__g_zuno_indicator_parameter) / sizeof(__g_zuno_indicator_parameter[0x0]))]); \
								}; \

#define ZUNO_SETUP_INDICATOR_INFO(INDICATORID, PIN)	\
{\
	.description = 0x0,\
	.support_prop_mask = INDICATOR_PROP_SUPPORT_MASK, \
	.pin = PIN,\
	.indicatorId = INDICATORID\
}\

int zuno_CCIndicatorHandler(ZUNOCommandPacket_t *cmd);
void zuno_CCIndicatorToggling(uint8_t indicatorId, uint8_t on_off_period, uint8_t on_off_cycles, uint8_t on_time);

#endif // ZWCC_INDICATOR_H