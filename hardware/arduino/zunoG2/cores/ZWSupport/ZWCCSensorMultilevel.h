#ifndef __SENSOR_MULTILEVEL_H__
#define __SENSOR_MULTILEVEL_H__

#include "ZWSupport.h"

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
/* Sensor Multilevel Get V4 command class structs */        
/************************************************************/
typedef struct										ZwSensorMultilevelGetV4Frame_s
{
	uint8_t											cmdClass;/* The command class */
	uint8_t											cmd;/* The command */
}													ZwSensorMultilevelGetV4Frame_t;

/************************************************************/
/* Sensor Multilevel Get V11 command class structs */       
/************************************************************/
typedef struct										ZwSensorMultilevelGetV11Frame_s
{
	uint8_t											cmdClass;/* The command class */
	uint8_t											cmd;/* The command */
	uint8_t											sensorType;/**/
	uint8_t											properties1;/* masked byte */
}													ZwSensorMultilevelGetV11Frame_t;

typedef union								ZwSensorMultilevelGetVFrame_u {//For more convenient support, several versions of commands
	ZwSensorMultilevelGetV4Frame_t			v4;
	ZwSensorMultilevelGetV11Frame_t			v11;
}											ZwSensorMultilevelGetVFrame_t;


/************************************************************/
/* Sensor Multilevel Report 1byte command class structs */  
/************************************************************/
typedef struct								ZwSensorMultilevelReportFrame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									sensorType;/**/
	uint8_t									level;/* masked byte */
	uint8_t									sensorValue[];/* MSB  LSB */
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

int zuno_CCSensorMultilevelHandler(byte channel, ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report);
int zuno_CCSensorMultilevelReport(byte channel, ZUNOCommandPacket_t *packet);

#endif // __SENSOR_MULTILEVEL_H__
