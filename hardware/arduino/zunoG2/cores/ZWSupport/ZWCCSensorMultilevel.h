#ifndef __SENSOR_MULTILEVEL_H__
#define __SENSOR_MULTILEVEL_H__

/* Sensor Multilevel command class commands */
#define SENSOR_MULTILEVEL_VERSION                                                    0x0B
#define SENSOR_MULTILEVEL_GET                                                        0x04
#define SENSOR_MULTILEVEL_REPORT                                                     0x05
#define SENSOR_MULTILEVEL_SUPPORTED_GET_SENSOR                                       0x01
#define SENSOR_MULTILEVEL_SUPPORTED_SENSOR_REPORT                                    0x02
#define SENSOR_MULTILEVEL_SUPPORTED_GET_SCALE                                        0x03
#define SENSOR_MULTILEVEL_SUPPORTED_SCALE_REPORT                                     0x06

#define SENSOR_MULTILEVEL_PROPERTIES_PRECISION_SHIFT    0x05
#define SENSOR_MULTILEVEL_PROPERTIES_SCALE_MASK         0x18
#define SENSOR_MULTILEVEL_PROPERTIES_SCALE_SHIFT        0x03
#define SENSOR_MULTILEVEL_PROPERTIES_SIZE_MASK          0x07

#define SENSOR_MULTILEVEL_SUPPORTED_MAX_BYTE_MASK 6

/************************************************************/
/* Sensor Multilevel Report 1byte command class structs */  
/************************************************************/
typedef struct								ZwSensorMultilevelReportByte1Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									sensorType;/**/
	uint8_t									level;/* masked byte */
	uint8_t									sensorValue1;
}											ZwSensorMultilevelReportByte1Frame_t;

typedef struct								ZwSensorMultilevelReportByte2Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									sensorType;/**/
	uint8_t									level;/* masked byte */
	uint8_t									sensorValue1;/* MSB */
	uint8_t									sensorValue2;/* LSB */
}											ZwSensorMultilevelReportByte2Frame_t;

typedef struct								ZwSensorMultilevelReportByte3Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									sensorType;/**/
	uint8_t									level;/* masked byte */
	uint8_t									sensorValue1;/* MSB */
	uint8_t									sensorValue2;
	uint8_t									sensorValue3;/* LSB */
}											ZwSensorMultilevelReportByte3Frame_t;

typedef struct								ZwSensorMultilevelReportByte4Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									sensorType;/**/
	uint8_t									level;/* masked byte */
	uint8_t									sensorValue1;/* MSB */
	uint8_t									sensorValue2;
	uint8_t									sensorValue3;
	uint8_t									sensorValue4;/* LSB */
}											ZwSensorMultilevelReportByte4Frame_t;

typedef union								ZwSensorMultilevelReportFrame_u {//For more convenient support, several versions of commands
	ZwSensorMultilevelReportByte1Frame_t	byte1;
	ZwSensorMultilevelReportByte2Frame_t	byte2;
	ZwSensorMultilevelReportByte3Frame_t	byte3;
	ZwSensorMultilevelReportByte4Frame_t	byte4;
}											ZwSensorMultilevelReportFrame_t;

/************************************************************/
/* Sensor Multilevel Supported Get Scale command class structs */
/************************************************************/
typedef struct									ZwSensorMultilevelSupportedGetScaleFrame_s
{
	uint8_t										cmdClass;/* The command class */
	uint8_t										cmd;/* The command */
	uint8_t										sensorType;/**/
}												ZwSensorMultilevelSupportedGetScaleFrame_t;

/************************************************************/
/* Sensor Multilevel Supported Scale Report command class structs */
/************************************************************/
typedef struct									ZwSensorMultilevelSupportedScaleReportFrame_s
{
	uint8_t										cmdClass;/* The command class */
	uint8_t										cmd;/* The command */
	uint8_t										sensorType;/**/
	uint8_t										properties1;/* masked byte */
}												ZwSensorMultilevelSupportedScaleReportFrame_t;

/************************************************************/
/* Sensor Multilevel Supported Sensor Report command class structs */
/************************************************************/
typedef struct												ZwSensorMultilevelSupportedSensorReportFrame_s
{
	uint8_t													cmdClass;/* The command class */
	uint8_t													cmd;/* The command */
	uint8_t													bitMask[];/* MSB  LSB */
}															ZwSensorMultilevelSupportedSensorReportFrame_t;

int zuno_CCSensorMultilevelHandler(byte channel, ZUNOCommandPacket_t * cmd);
int zuno_CCSensorMultilevelReport(byte channel, bool reply);

#endif // __SENSOR_MULTILEVEL_H__
