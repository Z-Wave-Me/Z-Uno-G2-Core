#ifndef ZWCC_CONFIGURATION_PRIVATE_H
#define ZWCC_CONFIGURATION_PRIVATE_H

#include "Arduino.h"

typedef uint32_t CONFIGPARAM_MAX_SIZE;

#define CONFIGPARAM_MIN_PARAM			0x40
#define CONFIGPARAM_MAX_PARAM			0x60
#define CONFIGPARAM_EEPROM_ADDR(param)	(((param - CONFIGPARAM_MIN_PARAM) * sizeof(CONFIGPARAM_MAX_SIZE)) + 0x204)


extern zuno_configuration_changed *g_zuno_configuration_change;

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

#endif // ZWCC_CONFIGURATION_PRIVATE_H