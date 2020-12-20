#ifndef __ZWCC_METER_H__
#define __ZWCC_METER_H__
#include "Arduino.h"

#define METER_GET               0x01
#define METER_REPORT            0x02
#define METER_SUPPORTED_GET     0x03
#define METER_RESET             0x05
#define METER_RATE_IMPORT       0x20
#define METER_VERSION           0x03

#define METER_PROPERTIES_PRECISION_SHIFT		0x05
#define METER_PROPERTIES_SCALE_MSB_MASK			0x80
#define METER_PROPERTIES_SCALE_MSB_SHIFT		0x05
#define METER_PROPERTIES_SCALE_LSB_MASK			0x18
#define METER_PROPERTIES_SCALE_LSB_SHIFT		0x03
#define METER_PROPERTIES_TYPE_MASK				0x1F
#define METER_PROPERTIES_SIZE_MASK				0x07

#define GET_SCALE2(params) ((params & 0x04) << 5)
#define GET_SCALE1(params) ((params & 0x03) << 3)
#define GET_SIZE(params) ((params >> 6) + 1)
#define GET_PRECISION(params) ((params << 2) & 0xE0)

#define COMBINE_PARAMS(params) (GET_SCALE1(params) | GET_SIZE(params) | GET_PRECISION(params))

/************************************************************/
/* Meter Report byte command class structs */              
/************************************************************/
typedef struct								ZwMeterReportV1Byte1Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									meterType;/**/
	uint8_t									properties1;/* masked byte */
	uint8_t									meterValue1;
}											ZwMeterReportV1Byte1Frame_t;

typedef struct								ZwMeterReportV1Byte2Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									meterType;/**/
	uint8_t									properties1;/* masked byte */
	uint8_t									meterValue1;/* MSB */
	uint8_t									meterValue2;/* LSB */
}											ZwMeterReportV1Byte2Frame_t;

typedef struct								ZwMeterReportV1Byte3Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									meterType;/**/
	uint8_t									properties1;/* masked byte */
	uint8_t									meterValue1;/* MSB */
	uint8_t									meterValue2;
	uint8_t									meterValue3;/* LSB */
}											ZwMeterReportV1Byte3Frame_t;

typedef struct								ZwMeterReportV1Byte4Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									meterType;/**/
	uint8_t									properties1;/* masked byte */
	uint8_t									meterValue1;/* MSB */
	uint8_t									meterValue2;
	uint8_t									meterValue3;
	uint8_t									meterValue4;/* LSB */
}											ZwMeterReportV1Byte4Frame_t;

typedef union								ZwMeterReportV1Frame_u {//For more convenient support, several versions of commands
	ZwMeterReportV1Byte1Frame_t				byte1;
	ZwMeterReportV1Byte2Frame_t				byte2;
	ZwMeterReportV1Byte3Frame_t				byte3;
	ZwMeterReportV1Byte4Frame_t				byte4;
}											ZwMeterReportV1Frame_t;


typedef struct								ZwMeterReportV2Byte1Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									properties1;/* masked byte */
	uint8_t									properties2;/* masked byte */
	uint8_t									meterValue1;
	uint8_t									deltaTime1;/* MSB */
	uint8_t									deltaTime2;/* LSB */
	uint8_t									previousMeterValue1;
}											ZwMeterReportV2Byte1Frame_t;

typedef struct								ZwMeterReportV2Byte2Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									properties1;/* masked byte */
	uint8_t									properties2;/* masked byte */
	uint8_t									meterValue1;/* MSB */
	uint8_t									meterValue2;/* LSB */
	uint8_t									deltaTime1;/* MSB */
	uint8_t									deltaTime2;/* LSB */
	uint8_t									previousMeterValue1;/* MSB */
	uint8_t									previousMeterValue2;/* LSB */
}											ZwMeterReportV2Byte2Frame_t;

typedef struct								ZwMeterReportV2Byte3Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									properties1;/* masked byte */
	uint8_t									properties2;/* masked byte */
	uint8_t									meterValue1;/* MSB */
	uint8_t									meterValue2;
	uint8_t									meterValue3;/* LSB */
	uint8_t									deltaTime1;/* MSB */
	uint8_t									deltaTime2;/* LSB */
	uint8_t									previousMeterValue1;/* MSB */
	uint8_t									previousMeterValue2;
	uint8_t									previousMeterValue3;/* LSB */
}											ZwMeterReportV2Byte3Frame_t;

typedef struct								ZwMeterReportV2Byte4Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									properties1;/* masked byte */
	uint8_t									properties2;/* masked byte */
	uint8_t									meterValue1;/* MSB */
	uint8_t									meterValue2;
	uint8_t									meterValue3;
	uint8_t									meterValue4;/* LSB */
	uint8_t									deltaTime1;/* MSB */
	uint8_t									deltaTime2;/* LSB */
	uint8_t									previousMeterValue1;/* MSB */
	uint8_t									previousMeterValue2;
	uint8_t									previousMeterValue3;
	uint8_t									previousMeterValue4;/* LSB */
}											ZwMeterReportV2Byte4Frame_t;

typedef union								ZwMeterReportV2Frame_u {//For more convenient support, several versions of commands
	ZwMeterReportV2Byte1Frame_t				byte1;
	ZwMeterReportV2Byte2Frame_t				byte2;
	ZwMeterReportV2Byte3Frame_t				byte3;
	ZwMeterReportV2Byte4Frame_t				byte4;
}											ZwMeterReportV2Frame_t;

typedef struct								ZwMeterReportV3Byte1Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									properties1;/* masked byte */
	uint8_t									properties2;/* masked byte */
	uint8_t									meterValue1;
	uint8_t									deltaTime1;/* MSB */
	uint8_t									deltaTime2;/* LSB */
	uint8_t									previousMeterValue1;
}											ZwMeterReportV3Byte1Frame_t;

typedef struct								ZwMeterReportV3Byte2Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									properties1;/* masked byte */
	uint8_t									properties2;/* masked byte */
	uint8_t									meterValue1;/* MSB */
	uint8_t									meterValue2;/* LSB */
	uint8_t									deltaTime1;/* MSB */
	uint8_t									deltaTime2;/* LSB */
	uint8_t									previousMeterValue1;/* MSB */
	uint8_t									previousMeterValue2;/* LSB */
}											ZwMeterReportV3Byte2Frame_t;

typedef struct								ZwMeterReportV3Byte3Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									properties1;/* masked byte */
	uint8_t									properties2;/* masked byte */
	uint8_t									meterValue1;/* MSB */
	uint8_t									meterValue2;
	uint8_t									meterValue3;/* LSB */
	uint8_t									deltaTime1;/* MSB */
	uint8_t									deltaTime2;/* LSB */
	uint8_t									previousMeterValue1;/* MSB */
	uint8_t									previousMeterValue2;
	uint8_t									previousMeterValue3;/* LSB */
}											ZwMeterReportV3Byte3Frame_t;

typedef struct								ZwMeterReportV3Byte4Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									properties1;/* masked byte */
	uint8_t									properties2;/* masked byte */
	uint8_t									meterValue1;/* MSB */
	uint8_t									meterValue2;
	uint8_t									meterValue3;
	uint8_t									meterValue4;/* LSB */
	uint8_t									deltaTime1;/* MSB */
	uint8_t									deltaTime2;/* LSB */
	uint8_t									previousMeterValue1;/* MSB */
	uint8_t									previousMeterValue2;
	uint8_t									previousMeterValue3;
	uint8_t									previousMeterValue4;/* LSB */
}											ZwMeterReportV3Byte4Frame_t;

typedef union								ZwMeterReportV3Frame_u {//For more convenient support, several versions of commands
	ZwMeterReportV3Byte1Frame_t				byte1;
	ZwMeterReportV3Byte2Frame_t				byte2;
	ZwMeterReportV3Byte3Frame_t				byte3;
	ZwMeterReportV3Byte4Frame_t				byte4;
}											ZwMeterReportV3Frame_t;

typedef union								ZwMeterReportFrame_u {//For more convenient support, several versions of commands
	ZwMeterReportV1Frame_t					v1;
	ZwMeterReportV2Frame_t					v2;
	ZwMeterReportV3Frame_t					v3;
}											ZwMeterReportFrame_t;

int zuno_CCMeterHandler(byte channel, ZUNOCommandPacket_t * cmd);
int zuno_CCMeterReport(byte channel);

#endif // __ZWCC_METER_H__