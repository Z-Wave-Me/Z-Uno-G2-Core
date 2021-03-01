#ifndef SWITCHBINARY_CC_H
#define SWITCHBINARY_CC_H

/* Switch Binary command class commands */
#define SWITCH_BINARY_VERSION                                                            0x02
#define SWITCH_BINARY_GET                                                                0x02
#define SWITCH_BINARY_REPORT                                                             0x03
#define SWITCH_BINARY_SET                                                                0x01

/************************************************************/
/* Switch Binary Set command class structs */               
/************************************************************/
typedef struct								ZwSwitchBinarySetV1Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									switchValue;/**/
}											ZwSwitchBinarySetV1Frame_t;

typedef struct								ZwSwitchBinarySetV2Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									targetValue;/**/
	uint8_t									duration;/**/
}											ZwSwitchBinarySetV2Frame_t;

typedef union								ZwSwitchBinarySetFrame_u {//For more convenient support, several versions of commands
	ZwSwitchBinarySetV1Frame_t				v1;
	ZwSwitchBinarySetV2Frame_t				v2;
}											ZwSwitchBinarySetFrame_t;

/************************************************************/
/* Switch Binary Report command class structs */            
/************************************************************/
typedef struct								ZwSwitchBinaryReportV1Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									value;/**/
}											ZwSwitchBinaryReportV1Frame_t;

typedef struct								ZwSwitchBinaryReportV2Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									currentValue;/**/
	uint8_t									targetValue;/**/
	uint8_t									duration;/**/
}											ZwSwitchBinaryReportV2Frame_t;

typedef union								ZwBasicBinaryReportFrame_u {//For more convenient support, several versions of commands
	ZwSwitchBinaryReportV1Frame_t			v1;
	ZwSwitchBinaryReportV2Frame_t			v2;
}											ZwBasicBinaryReportFrame_t;

int zuno_CCSwitchBinaryHandler(byte channel, ZUNOCommandPacket_t * cmd);
int zuno_CCSwitchBinaryReport(byte channel);
void zuno_CCSwitchBinaryTimer(size_t ticks);
#endif // SWITCHBINARY_CC_H