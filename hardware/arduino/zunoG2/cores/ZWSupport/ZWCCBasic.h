#ifndef BASIC_CC_H
#define BASIC_CC_H

#include "ZWSupport.h"

/* Basic command class commands */
#define BASIC_VERSION                                                                    0x02
#define BASIC_GET                                                                        0x02
#define BASIC_REPORT                                                                     0x03
#define BASIC_SET                                                                        0x01

/************************************************************/
/* Basic Set command class structs */                       
/************************************************************/
typedef struct								ZwBasicSetFrame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									value;/**/
}											ZwBasicSetFrame_t;

/************************************************************/
/* Basic Report command class structs */                    
/************************************************************/
typedef struct								ZwBasicReportV1Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									value;/**/
}											ZwBasicReportV1Frame_t;

typedef struct								ZwBasicReportV2Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									currentValue;/**/
	uint8_t									targetValue;/**/
	uint8_t									duration;/**/
}											ZwBasicReportV2Frame_t;

typedef union								ZwBasicReportFrame_u {//For more convenient support, several versions of commands
	ZwBasicReportV1Frame_t			v1;
	ZwBasicReportV2Frame_t			v2;
}											ZwBasicReportFrame_t;

void zunoBasicSaveInit(void);
void zunoBasicSaveSet(uint8_t channel, void *value);
uint8_t zunoBasicSaveGet(uint8_t channel);

void __zuno_BasicUniversalSetter1P(byte zuno_ch, uint8_t value);
uint8_t __zuno_BasicUniversalGetter1P(byte zuno_ch);
void __zuno_BasicUniversalTimerStop(uint8_t channel);
void __zuno_BasicUniversalDimingStop(uint8_t channel);
void __zuno_BasicUniversalGetCurrentValueDurationTargetValue(uint8_t channel, uint8_t *current_value, uint8_t *duration_table_8, uint8_t *target_value);

int zuno_CCBasicHandler(byte channel, const ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report);
#endif // BASIC_CC_H