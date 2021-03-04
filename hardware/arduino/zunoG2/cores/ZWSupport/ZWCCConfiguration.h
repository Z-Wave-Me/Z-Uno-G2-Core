#ifndef ZWCC_CONFIGURATION_H
#define ZWCC_CONFIGURATION_H

#define MAX_CFGUPDATE_LISTENERS 2
/* Configuration command class commands */
#define CONFIGURATION_VERSION                                                            0x01
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

int zuno_CCConfigurationHandler(ZUNOCommandPacket_t *cmd);

#endif // ZWCC_CONFIGURATION_H