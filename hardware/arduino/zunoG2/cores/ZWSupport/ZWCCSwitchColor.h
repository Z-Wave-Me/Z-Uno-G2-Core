#ifndef ZWCC_SWITCH_COLOR_H
#define ZWCC_SWITCH_COLOR_H

#include "Arduino.h"
#include "ZWSupport.h"

/* Switch Color command class commands */
#define SWITCH_COLOR_VERSION                                                             0x03
#define SWITCH_COLOR_SUPPORTED_GET                                                       0x01
#define SWITCH_COLOR_SUPPORTED_REPORT                                                    0x02
#define SWITCH_COLOR_GET                                                                 0x03
#define SWITCH_COLOR_REPORT                                                              0x04
#define SWITCH_COLOR_SET                                                                 0x05
#define SWITCH_COLOR_START_LEVEL_CHANGE                                                  0x06
#define SWITCH_COLOR_STOP_LEVEL_CHANGE                                                   0x07

# define ZUNO_TIMER_COLOR_MAX_VALUE			0xFF//Maximum value when dimming
# define ZUNO_TIMER_COLOR_MIN_VALUE			0x0//The minimum value when dimming

typedef struct					ZwSwitchColorSupportedReporFrame_s {
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						colorComponentMask1;/* MSB */
	uint8_t						colorComponentMask2;/* LSB */
}								ZwSwitchColorSupportedReporFrame_t;//ZW_SWITCH_COLOR_SUPPORTED_REPORTV3Frame

typedef struct					ZwSwitchColorGetFrame_s {
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						colorComponentId;/**/
}								ZwSwitchColorGetFrame_t;//ZW_SWITCH_COLOR_GETV3Frame

typedef struct					ZwSwitchColorReportV2Frame_s {
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						colorComponentId;/**/
	uint8_t						value;/**/
}								ZwSwitchColorReportV2Frame_t;

typedef struct					ZwSwitchColorReportV3Frame_s {
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						colorComponentId;/**/
	uint8_t						currentValue;/**/
	uint8_t						targetValue;/**/
	uint8_t						duration;/**/
}								ZwSwitchColorReportV3Frame_t;

typedef union					ZwSwitchColorReportFrame_u {//For more convenient support, several versions of commands
	ZwSwitchColorReportV2Frame_t					v2;
	ZwSwitchColorReportV3Frame_t					v3;
}								ZwSwitchColorReportFrame_t;

/************************************************************/
/* Switch Color Set variant group structs */                
/************************************************************/
typedef struct					VgSwitchColorSetVg_s {
	uint8_t						colorComponentId;/**/
	uint8_t						value;/**/
}								VgSwitchColorSetVg_t;//VG_SWITCH_COLOR_SET_V3_VG

typedef struct					ZwSwitchColorSetFrame_s {
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						properties1;/* masked byte */
	VgSwitchColorSetVg_t		variantgroup[0];/**/
}								ZwSwitchColorSetFrame_t;//ZW_SWITCH_COLOR_SET_4BYTE_FRAME

typedef struct					ZwSwitchColorStartLevelChangeV2Frame_s {
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						properties1;/* masked byte */
	uint8_t						colorComponentId;/**/
	uint8_t						startLevel;/**/
}								ZwSwitchColorStartLevelChangeV2Frame_t;


typedef struct					ZwSwitchColorStartLevelChangeV3Frame_s {
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						properties1;/* masked byte */
	uint8_t						colorComponentId;/**/
	uint8_t						startLevel;/**/
	uint8_t						duration;/**/
}								ZwSwitchColorStartLevelChangeV3Frame_t;

typedef union {//For more convenient support, several versions of commands
	ZwSwitchColorStartLevelChangeV2Frame_t		v2;
	ZwSwitchColorStartLevelChangeV3Frame_t		v3;
}								ZwSwitchColorStartLevelChange_FRAME_u;


typedef struct					ZwSwitchColorStopLevelChange_s {
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						colorComponentId;/**/
}								ZwSwitchColorStopLevelChange_t;//ZW_SWITCH_COLOR_STOP_LEVEL_CHANGEV3Frame

int zuno_CCSwitchColorHandler(uint8_t channel, ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report);
int zuno_CCSwitchColorReport(uint8_t channel, ZUNOCommandPacket_t *cmd, ZUNOCommandPacket_t *packet);

void zunoSwitchColorSaveInit(void);
void zunoSwitchColorSaveSet(uint8_t channel, void *value);
uint8_t zunoSwitchColorSaveGet(uint8_t channel);

#endif // ZWCC_SWITCH_COLOR_H