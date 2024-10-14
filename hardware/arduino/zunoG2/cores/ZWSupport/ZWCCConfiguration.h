#ifndef ZWCC_CONFIGURATION_H
#define ZWCC_CONFIGURATION_H

#include "ZWSupport.h"

#define MAX_CFGUPDATE_LISTENERS 2
/* Configuration command class commands */
#define CONFIGURATION_VERSION                                                            0x04
#define CONFIGURATION_BULK_GET                                                           0x08
#define CONFIGURATION_BULK_REPORT                                                        0x09
#define CONFIGURATION_BULK_SET                                                           0x07
#define CONFIGURATION_GET                                                                0x05
#define CONFIGURATION_REPORT                                                             0x06
#define CONFIGURATION_SET                                                                0x04
#define CONFIGURATION_NAME_GET                                                           0x0A
#define CONFIGURATION_NAME_REPORT                                                        0x0B
#define CONFIGURATION_INFO_GET                                                           0x0C
#define CONFIGURATION_INFO_REPORT                                                        0x0D
#define CONFIGURATION_PROPERTIES_GET                                                     0x0E
#define CONFIGURATION_PROPERTIES_REPORT                                                  0x0F
#define CONFIGURATION_DEFAULT_RESET                                                      0x01

/* Values used for Configuration Bulk Report command */
#define CONFIGURATION_BULK_REPORT_PROPERTIES1_SIZE_MASK                                  0x07
#define CONFIGURATION_BULK_REPORT_PROPERTIES1_RESERVED_MASK                              0x38
#define CONFIGURATION_BULK_REPORT_PROPERTIES1_RESERVED_SHIFT                             0x03
#define CONFIGURATION_BULK_REPORT_PROPERTIES1_HANDSHAKE_BIT_MASK                         0x40
#define CONFIGURATION_BULK_REPORT_PROPERTIES1_DEFAULT_BIT_MASK                           0x80
/* Values used for Configuration Bulk Set command */
#define CONFIGURATION_BULK_SET_PROPERTIES1_SIZE_MASK                                     0x07
#define CONFIGURATION_BULK_SET_PROPERTIES1_RESERVED_MASK                                 0x38
#define CONFIGURATION_BULK_SET_PROPERTIES1_RESERVED_SHIFT                                0x03
#define CONFIGURATION_BULK_SET_PROPERTIES1_HANDSHAKE_BIT_MASK                            0x40
#define CONFIGURATION_BULK_SET_PROPERTIES1_DEFAULT_BIT_MASK                              0x80
/* Values used for Configuration Report command */
#define CONFIGURATION_REPORT_LEVEL_SIZE_MASK                                             0x07
#define CONFIGURATION_REPORT_LEVEL_RESERVED_MASK                                         0xF8
#define CONFIGURATION_REPORT_LEVEL_RESERVED_SHIFT                                        0x03
/* Values used for Configuration Set command */
#define CONFIGURATION_SET_LEVEL_SIZE_MASK                                                0x07
#define CONFIGURATION_SET_LEVEL_RESERVED_MASK                                            0x78
#define CONFIGURATION_SET_LEVEL_RESERVED_SHIFT                                           0x03
#define CONFIGURATION_SET_LEVEL_DEFAULT_BIT_MASK                                         0x80
/* Values used for Configuration Properties Report command */
#define CONFIGURATION_PROPERTIES_REPORT_PROPERTIES1_SIZE_MASK                            0x07
#define CONFIGURATION_PROPERTIES_REPORT_PROPERTIES1_FORMAT_MASK                          0x38
#define CONFIGURATION_PROPERTIES_REPORT_PROPERTIES1_FORMAT_SHIFT                         0x03
#define CONFIGURATION_PROPERTIES_REPORT_FORMAT_SIGNED_INTEGER                            0x00
#define CONFIGURATION_PROPERTIES_REPORT_FORMAT_UNSIGNED_INTEGER                          0x01
#define CONFIGURATION_PROPERTIES_REPORT_FORMAT_ENUMERATED                                0x02
#define CONFIGURATION_PROPERTIES_REPORT_FORMAT_BIT_FIELD                                 0x03
#define CONFIGURATION_PROPERTIES_REPORT_PROPERTIES1_READONLY_BIT_MASK                    0x40
#define CONFIGURATION_PROPERTIES_REPORT_PROPERTIES1_ALTERING_CAPABILITIES_BIT_MASK       0x80
#define CONFIGURATION_PROPERTIES_REPORT_PROPERTIES2_ADVANCED_BIT_MASK                    0x01
#define CONFIGURATION_PROPERTIES_REPORT_PROPERTIES2_NO_BULK_SUPPORT_BIT_MASK             0x02
#define CONFIGURATION_PROPERTIES_REPORT_PROPERTIES2_RESERVED1_MASK                       0xFC
#define CONFIGURATION_PROPERTIES_REPORT_PROPERTIES2_RESERVED1_SHIFT                      0x02

/************************************************************/
/* Configuration Get command class structs */               
/************************************************************/
typedef struct								ZwConfigurationGetFrame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									parameterNumber;/**/
}											ZwConfigurationGetFrame_t;

/************************************************************/
/* Configuration Report command class structs */      
/************************************************************/
typedef struct							ZwConfigurationReport1ByteFrame_s
{
	uint8_t								cmdClass;/* The command class */
	uint8_t								cmd;/* The command */
	uint8_t								parameterNumber;/**/
	uint8_t								level;/* masked byte */
	uint8_t								configurationValue1;
}										ZwConfigurationReport1ByteFrame_t;

typedef struct							ZwConfigurationReport2ByteFrame_s
{
	uint8_t								cmdClass;/* The command class */
	uint8_t								cmd;/* The command */
	uint8_t								parameterNumber;/**/
	uint8_t								level;/* masked byte */
	uint8_t								configurationValue1;/* MSB */
	uint8_t								configurationValue2;/* LSB */
}										ZwConfigurationReport2ByteFrame_t;

typedef struct							ZwConfigurationReport3ByteFrame_s
{
	uint8_t								cmdClass;/* The command class */
	uint8_t								cmd;/* The command */
	uint8_t								parameterNumber;/**/
	uint8_t								level;/* masked byte */
	uint8_t								configurationValue1;/* MSB */
	uint8_t								configurationValue2;
	uint8_t								configurationValue3;/* LSB */
}										ZwConfigurationReport3ByteFrame_t;

typedef struct							ZwConfigurationReport4ByteFrame_s
{
	uint8_t								cmdClass;/* The command class */
	uint8_t								cmd;/* The command */
	uint8_t								parameterNumber;/**/
	uint8_t								level;/* masked byte */
	uint8_t								configurationValue1;/* MSB */
	uint8_t								configurationValue2;
	uint8_t								configurationValue3;
	uint8_t								configurationValue4;/* LSB */
}										ZwConfigurationReport4ByteFrame_t;


typedef union							ZwConfigurationReportFrame_u {//For more convenient support, several versions of commands
	ZwConfigurationReport1ByteFrame_t	byte1;
	ZwConfigurationReport2ByteFrame_t	byte2;
	ZwConfigurationReport3ByteFrame_t	byte3;
	ZwConfigurationReport4ByteFrame_t	byte4;
}										ZwConfigurationReportFrame_t;

/************************************************************/
/* Configuration Set command class structs */      
/************************************************************/
typedef struct							ZwConfigurationSet1ByteFrame_s
{
	uint8_t								cmdClass;/* The command class */
	uint8_t								cmd;/* The command */
	uint8_t								parameterNumber;/**/
	uint8_t								level;/* masked byte */
	uint8_t								configurationValue1;
}										ZwConfigurationSet1ByteFrame_t;

typedef struct							ZwConfigurationSet2ByteFrame_s
{
	uint8_t								cmdClass;/* The command class */
	uint8_t								cmd;/* The command */
	uint8_t								parameterNumber;/**/
	uint8_t								level;/* masked byte */
	uint8_t								configurationValue1;/* MSB */
	uint8_t								configurationValue2;/* LSB */
}										ZwConfigurationSet2ByteFrame_t;

typedef struct							ZwConfigurationSet3ByteFrame_s
{
	uint8_t								cmdClass;/* The command class */
	uint8_t								cmd;/* The command */
	uint8_t								parameterNumber;/**/
	uint8_t								level;/* masked byte */
	uint8_t								configurationValue1;/* MSB */
	uint8_t								configurationValue2;
	uint8_t								configurationValue3;/* LSB */
}										ZwConfigurationSet3ByteFrame_t;

typedef struct							ZwConfigurationSet4ByteFrame_s
{
	uint8_t								cmdClass;/* The command class */
	uint8_t								cmd;/* The command */
	uint8_t								parameterNumber;/**/
	uint8_t								level;/* masked byte */
	uint8_t								configurationValue1;/* MSB */
	uint8_t								configurationValue2;
	uint8_t								configurationValue3;
	uint8_t								configurationValue4;/* LSB */
}										ZwConfigurationSet4ByteFrame_t;


typedef union							ZwConfigurationSetFrame_u {//For more convenient support, several versions of commands
	ZwConfigurationSet1ByteFrame_t		byte1;
	ZwConfigurationSet2ByteFrame_t		byte2;
	ZwConfigurationSet3ByteFrame_t		byte3;
	ZwConfigurationSet4ByteFrame_t		byte4;
}										ZwConfigurationSetFrame_t;

/************************************************************/
/* Configuration Properties Get command class structs */ 
/************************************************************/
typedef struct									ZwConfigurationPropertiesGetFrame_s
{
	uint8_t										cmdClass;/* The command class */
	uint8_t										cmd;/* The command */
	uint8_t										parameterNumber1;/* MSB */
	uint8_t										parameterNumber2;/* LSB */
}												ZwConfigurationPropertiesGetFrame_t;

/************************************************************/
/* Configuration Properties Report command class structs */
/************************************************************/
typedef struct									ZwConfigurationPropertiesPeportByte1FrameV3_s
{
	uint8_t										cmdClass;/* The command class */
	uint8_t										cmd;/* The command */
	uint8_t										parameterNumber1;/* MSB */
	uint8_t										parameterNumber2;/* LSB */
	uint8_t										properties1;/* masked byte */
	uint8_t										minValue1;
	uint8_t										maxValue1;
	uint8_t										defaultValue1;
	uint8_t										nextParameterNumber1;/* MSB */
	uint8_t										nextParameterNumber2;/* LSB */
}												ZwConfigurationPropertiesPeportByte1FrameV3_t;

typedef struct									ZwConfigurationPropertiesPeportByte2FrameV3_s
{
	uint8_t										cmdClass;/* The command class */
	uint8_t										cmd;/* The command */
	uint8_t										parameterNumber1;/* MSB */
	uint8_t										parameterNumber2;/* LSB */
	uint8_t										properties1;/* masked byte */
	uint8_t										minValue1;/* MSB */
	uint8_t										minValue2;/* LSB */
	uint8_t										maxValue1;/* MSB */
	uint8_t										maxValue2;/* LSB */
	uint8_t										defaultValue1;/* MSB */
	uint8_t										defaultValue2;/* LSB */
	uint8_t										nextParameterNumber1;/* MSB */
	uint8_t										nextParameterNumber2;/* LSB */
}												ZwConfigurationPropertiesPeportByte2FrameV3_t;

typedef struct									ZwConfigurationPropertiesPeportByte3FrameV3_s
{
	uint8_t										cmdClass;/* The command class */
	uint8_t										cmd;/* The command */
	uint8_t										parameterNumber1;/* MSB */
	uint8_t										parameterNumber2;/* LSB */
	uint8_t										properties1;/* masked byte */
	uint8_t										minValue1;/* MSB */
	uint8_t										minValue2;
	uint8_t										minValue3;/* LSB */
	uint8_t										maxValue1;/* MSB */
	uint8_t										maxValue2;
	uint8_t										maxValue3;/* LSB */
	uint8_t										defaultValue1;/* MSB */
	uint8_t										defaultValue2;
	uint8_t										defaultValue3;/* LSB */
	uint8_t										nextParameterNumber1;/* MSB */
	uint8_t										nextParameterNumber2;/* LSB */
}												ZwConfigurationPropertiesPeportByte3FrameV3_t;

typedef struct									ZwConfigurationPropertiesPeportByte4FrameV3_s
{
	uint8_t										cmdClass;/* The command class */
	uint8_t										cmd;/* The command */
	uint8_t										parameterNumber1;/* MSB */
	uint8_t										parameterNumber2;/* LSB */
	uint8_t										properties1;/* masked byte */
	uint8_t										minValue1;/* MSB */
	uint8_t										minValue2;
	uint8_t										minValue3;
	uint8_t										minValue4;/* LSB */
	uint8_t										maxValue1;/* MSB */
	uint8_t										maxValue2;
	uint8_t										maxValue3;
	uint8_t										maxValue4;/* LSB */
	uint8_t										defaultValue1;/* MSB */
	uint8_t										defaultValue2;
	uint8_t										defaultValue3;
	uint8_t										defaultValue4;/* LSB */
	uint8_t										nextParameterNumber1;/* MSB */
	uint8_t										nextParameterNumber2;/* LSB */
}												ZwConfigurationPropertiesPeportByte4FrameV3_t;

typedef union										ZwConfigurationPropertiesPeportFrameV3_u//For more convenient support, several versions of commands
{
	ZwConfigurationPropertiesPeportByte1FrameV3_t	byte1;
	ZwConfigurationPropertiesPeportByte2FrameV3_t	byte2;
	ZwConfigurationPropertiesPeportByte3FrameV3_t	byte3;
	ZwConfigurationPropertiesPeportByte4FrameV3_t	byte4;
}													ZwConfigurationPropertiesPeportFrameV3_t;

typedef struct									ZwConfigurationPropertiesPeportByte4FrameV4End_s
{
	uint8_t										nextParameterNumber1;/* MSB */
	uint8_t										nextParameterNumber2;/* LSB */
	uint8_t										properties2;/* masked byte */
}												ZwConfigurationPropertiesPeportByte4FrameV4End_t;

typedef struct									ZwConfigurationPropertiesPeportByte1FrameV4_s
{
	uint8_t										cmdClass;/* The command class */
	uint8_t										cmd;/* The command */
	uint8_t										parameterNumber1;/* MSB */
	uint8_t										parameterNumber2;/* LSB */
	uint8_t										properties1;/* masked byte */
	uint8_t										minValue1;
	uint8_t										maxValue1;
	uint8_t										defaultValue1;
	ZwConfigurationPropertiesPeportByte4FrameV4End_t	end;
}												ZwConfigurationPropertiesPeportByte1FrameV4_t;

typedef struct									ZwConfigurationPropertiesPeportByte2FrameV4_s
{
	uint8_t										cmdClass;/* The command class */
	uint8_t										cmd;/* The command */
	uint8_t										parameterNumber1;/* MSB */
	uint8_t										parameterNumber2;/* LSB */
	uint8_t										properties1;/* masked byte */
	uint8_t										minValue1;/* MSB */
	uint8_t										minValue2;/* LSB */
	uint8_t										maxValue1;/* MSB */
	uint8_t										maxValue2;/* LSB */
	uint8_t										defaultValue1;/* MSB */
	uint8_t										defaultValue2;/* LSB */
	ZwConfigurationPropertiesPeportByte4FrameV4End_t	end;
}												ZwConfigurationPropertiesPeportByte2FrameV4_t;

typedef struct									ZwConfigurationPropertiesPeportByte3FrameV4_s
{
	uint8_t										cmdClass;/* The command class */
	uint8_t										cmd;/* The command */
	uint8_t										parameterNumber1;/* MSB */
	uint8_t										parameterNumber2;/* LSB */
	uint8_t										properties1;/* masked byte */
	uint8_t										minValue1;/* MSB */
	uint8_t										minValue2;
	uint8_t										minValue3;/* LSB */
	uint8_t										maxValue1;/* MSB */
	uint8_t										maxValue2;
	uint8_t										maxValue3;/* LSB */
	uint8_t										defaultValue1;/* MSB */
	uint8_t										defaultValue2;
	uint8_t										defaultValue3;/* LSB */
	ZwConfigurationPropertiesPeportByte4FrameV4End_t	end;
}												ZwConfigurationPropertiesPeportByte3FrameV4_t;

typedef struct									ZwConfigurationPropertiesPeportByte4FrameV4_s
{
	uint8_t										cmdClass;/* The command class */
	uint8_t										cmd;/* The command */
	uint8_t										parameterNumber1;/* MSB */
	uint8_t										parameterNumber2;/* LSB */
	uint8_t										properties1;/* masked byte */
	uint8_t										minValue1;/* MSB */
	uint8_t										minValue2;
	uint8_t										minValue3;
	uint8_t										minValue4;/* LSB */
	uint8_t										maxValue1;/* MSB */
	uint8_t										maxValue2;
	uint8_t										maxValue3;
	uint8_t										maxValue4;/* LSB */
	uint8_t										defaultValue1;/* MSB */
	uint8_t										defaultValue2;
	uint8_t										defaultValue3;
	uint8_t										defaultValue4;/* LSB */
	ZwConfigurationPropertiesPeportByte4FrameV4End_t	end;
}												ZwConfigurationPropertiesPeportByte4FrameV4_t;

typedef union										ZwConfigurationPropertiesPeportFrameV4_u//For more convenient support, several versions of commands
{
	ZwConfigurationPropertiesPeportByte1FrameV4_t	byte1;
	ZwConfigurationPropertiesPeportByte2FrameV4_t	byte2;
	ZwConfigurationPropertiesPeportByte3FrameV4_t	byte3;
	ZwConfigurationPropertiesPeportByte4FrameV4_t	byte4;
}													ZwConfigurationPropertiesPeportFrameV4_t;

typedef union										ZwConfigurationPropertiesPeportFrame_u//For more convenient support, several versions of commands
{
	ZwConfigurationPropertiesPeportFrameV3_t		v3;
	ZwConfigurationPropertiesPeportFrameV4_t		v4;
}													ZwConfigurationPropertiesPeportFrame_t;

/************************************************************/
/* Configuration Name Get command class structs */       
/************************************************************/
typedef struct										ZwConfigurationNameGetFrame_s
{
	uint8_t											cmdClass;/* The command class */
	uint8_t											cmd;/* The command */
	uint8_t											parameterNumber1;/* MSB */
	uint8_t											parameterNumber2;/* LSB */
}													ZwConfigurationNameGetFrame_t;

/************************************************************/
/* Configuration Name Report command class structs */
/************************************************************/
typedef struct										ZwConfigurationNameReportFrame_s
{
	uint8_t											cmdClass;/* The command class */
	uint8_t											cmd;/* The command */
	uint8_t											parameterNumber1;/* MSB */
	uint8_t											parameterNumber2;/* LSB */
	uint8_t											reportsToFollow;/**/
	uint8_t											name[];
}													ZwConfigurationNameReportFrame_t;

/************************************************************/
/* Configuration Info Get command class structs */       
/************************************************************/
typedef struct										ZwConfigurationInfoGetFrame_s
{
	uint8_t											cmdClass;/* The command class */
	uint8_t											cmd;/* The command */
	uint8_t											parameterNumber1;/* MSB */
	uint8_t											parameterNumber2;/* LSB */
}													ZwConfigurationInfoGetFrame_t;

/************************************************************/
/* Configuration Info Report command class structs */
/************************************************************/
typedef struct										ZwConfigurationInfoReportFrame_s
{
	uint8_t											cmdClass;/* The command class */
	uint8_t											cmd;/* The command */
	uint8_t											parameterNumber1;/* MSB */
	uint8_t											parameterNumber2;/* LSB */
	uint8_t											reportsToFollow;/**/
	uint8_t											info[];
}													ZwConfigurationInfoReportFrame_t;

/************************************************************/
/* Configuration Bulk Get command class structs */       
/************************************************************/
typedef struct										ZwConfigurationBuilkGetFrame_s
{
	uint8_t											cmdClass;/* The command class */
	uint8_t											cmd;/* The command */
	uint8_t											parameterOffset1;/* MSB */
	uint8_t											parameterOffset2;/* LSB */
	uint8_t											numberOfParameters;/**/
}													ZwConfigurationBuilkGetFrame_t;

/************************************************************/
/* Configuration Bulk Report V4 command class structs */
/************************************************************/
typedef struct										ZwConfigurationBuilkReportFrame_s
{
	uint8_t											cmdClass;/* The command class */
	uint8_t											cmd;/* The command */
	uint8_t											parameterOffset1;/* MSB */
	uint8_t											parameterOffset2;/* LSB */
	uint8_t											numberOfParameters;/**/
	uint8_t											reportsToFollow;/**/
	uint8_t											properties1;/* masked byte */
	uint8_t											parameter[];/* MSB  LSB */
}													ZwConfigurationBuilkReportFrame_t;

int zuno_CCConfigurationHandler(const ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report);
typedef enum{
	PARAM_SV_SYSTEM_OK,
	PARAM_SV_USER_OK,
	PARAM_SV_UNKNOWN_PARAM,
	PARAM_SV_WRONG_VALUE,
	PARAM_SV_WRONG_PARAM_SIZE
} PARAM_SV_STATUS;
uint8_t checkConfigurationParameterSVSet(uint8_t * cmd);

#endif // ZWCC_CONFIGURATION_H