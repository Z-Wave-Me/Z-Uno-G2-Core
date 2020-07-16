#ifndef SWITCHMULTILEVEL_CC_H
#define SWITCHMULTILEVEL_CC_H
#include "Arduino.h"

/* Switch Multilevel command class commands */
#define SWITCH_MULTILEVEL_VERSION                                                        0x02
#define SWITCH_MULTILEVEL_GET                                                            0x02
#define SWITCH_MULTILEVEL_REPORT                                                         0x03
#define SWITCH_MULTILEVEL_SET                                                            0x01
#define SWITCH_MULTILEVEL_START_LEVEL_CHANGE                                             0x04
#define SWITCH_MULTILEVEL_STOP_LEVEL_CHANGE                                              0x05
#define SWITCH_MULTILEVEL_SUPPORTED_GET                                                  0x06
#define SWITCH_MULTILEVEL_SUPPORTED_REPORT                                               0x07
/* Values used for Switch Multilevel Start Level Change command */
#define SWITCH_MULTILEVEL_START_LEVEL_CHANGE_PROPERTIES1_RESERVED_MASK                    0x07
#define SWITCH_MULTILEVEL_START_LEVEL_CHANGE_PROPERTIES1_INC_DEC_MASK                     0x18
#define SWITCH_MULTILEVEL_START_LEVEL_CHANGE_PROPERTIES1_INC_DEC_SHIFT                    0x03
#define SWITCH_MULTILEVEL_START_LEVEL_CHANGE_INC_DEC_INCREMENT                            0x00
#define SWITCH_MULTILEVEL_START_LEVEL_CHANGE_INC_DEC_DECREMENT                            0x01
#define SWITCH_MULTILEVEL_START_LEVEL_CHANGE_INC_DEC_RESERVED                             0x02
#define SWITCH_MULTILEVEL_START_LEVEL_CHANGE_INC_DEC_NONE                                 0x03
#define SWITCH_MULTILEVEL_START_LEVEL_CHANGE_PROPERTIES1_IGNORE_START_LEVEL_BIT_MASK      0x20
#define SWITCH_MULTILEVEL_START_LEVEL_CHANGE_PROPERTIES1_UP_DOWN_MASK                     0xC0
#define SWITCH_MULTILEVEL_START_LEVEL_CHANGE_PROPERTIES1_UP_DOWN_SHIFT                    0x06
#define SWITCH_MULTILEVEL_START_LEVEL_CHANGE_UP_DOWN_UP                                   0x00
#define SWITCH_MULTILEVEL_START_LEVEL_CHANGE_UP_DOWN_DOWN                                 0x01
#define SWITCH_MULTILEVEL_START_LEVEL_CHANGE_UP_DOWN_RESERVED                             0x02
#define SWITCH_MULTILEVEL_START_LEVEL_CHANGE_UP_DOWN_NONE                                 0x03
/* Values used for Switch Multilevel Supported Report command */
#define SWITCH_MULTILEVEL_SUPPORTED_REPORT_PROPERTIES1_PRIMARY_SWITCH_TYPE_MASK           0x1F
#define SWITCH_MULTILEVEL_SUPPORTED_REPORT_PROPERTIES1_RESERVED_MASK                      0xE0
#define SWITCH_MULTILEVEL_SUPPORTED_REPORT_PROPERTIES1_RESERVED_SHIFT                     0x05
#define SWITCH_MULTILEVEL_SUPPORTED_REPORT_PROPERTIES2_SECONDARY_SWITCH_TYPE_MASK         0x1F
#define SWITCH_MULTILEVEL_SUPPORTED_REPORT_PROPERTIES2_RESERVED_MASK                      0xE0
#define SWITCH_MULTILEVEL_SUPPORTED_REPORT_PROPERTIES2_RESERVED_SHIFT                     0x05

/************************************************************/
/* Switch Multilevel Start Level Change command class structs */
/************************************************************/
typedef struct					ZwSwitchMultilevelStartLevelChangeV1Frame_s {
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						properties1;/* masked byte */
	uint8_t						startLevel;/**/
}								ZwSwitchMultilevelStartLevelChangeV1Frame_t;

typedef struct					ZwSwitchMultilevelStartLevelChangeV2Frame_s {
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						properties1;/* masked byte */
	uint8_t						startLevel;/**/
	uint8_t						dimmingDuration;/**/
}								ZwSwitchMultilevelStartLevelChangeV2Frame_t;

typedef struct					ZwSwitchMultilevelStartLevelChangeV3Frame_s {
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						properties1;/* masked byte */
	uint8_t						startLevel;/**/
	uint8_t						dimmingDuration;/**/
	uint8_t						stepSize;/**/
}								ZwSwitchMultilevelStartLevelChangeV3Frame_t;

typedef union					ZwSwitchMultilevelStartLevelChangeFrame_u {//For more convenient support, several versions of commands
	ZwSwitchMultilevelStartLevelChangeV1Frame_t	v1;
	ZwSwitchMultilevelStartLevelChangeV2Frame_t	v2;
	ZwSwitchMultilevelStartLevelChangeV3Frame_t	v3;
}								ZwSwitchMultilevelStartLevelChangeFrame_t;

/************************************************************/
/* Switch Multilevel Stop Level Change command class structs */
/************************************************************/
typedef struct					ZwSwitchMultilevelStopLevelChangeFrame_s
{
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
}								ZwSwitchMultilevelStopLevelChangeFrame_t;

int zuno_CCSwitchMultilevelReport(byte channel);
int zuno_CCSwitchMultilevelHandler(byte channel, ZUNOCommandPacket_t * cmd);
void zuno_CCSwitchMultilevelTimer(uint32_t ticks);

#endif // SWITCHMULTILEVEL_CC_H