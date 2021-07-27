#ifndef BASIC_CC_H
#define BASIC_CC_H

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

#define ZWCC_BASIC_SAVE_LAST(channel)				ZUNO_CFG_CHANNEL(channel).params[0x0]
#define ZWCC_BASIC_SAVE_COLOR(channel)				ZUNO_CFG_CHANNEL(channel).params[0x1]

#ifdef WITH_CC_SWITCH_COLOR
	#define ZWCC_BASIC_SETTER_1P(zuno_ch, value)							zuno_SwitchMultilevelUniversalSetter1P(zuno_ch, value)
	#define ZWCC_BASIC_GETTER_1P(zuno_ch)									zuno_SwitchMultilevelUniversalGetter1P(zuno_ch)
#else
	#define ZWCC_BASIC_SETTER_1P(zuno_ch, value)							zuno_universalSetter1P(zuno_ch, value)
	#define ZWCC_BASIC_GETTER_1P(zuno_ch)									zuno_universalGetter1P(zuno_ch)
#endif

int zuno_CCBasicHandler(byte channel, ZUNOCommandPacket_t * cmd);
#endif // BASIC_CC_H