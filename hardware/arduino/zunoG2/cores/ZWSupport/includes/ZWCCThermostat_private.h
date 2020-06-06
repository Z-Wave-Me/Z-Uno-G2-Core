#ifndef ZWCC_SWITCH_THERMOSTAT_PRIVATE_H
#define ZWCC_SWITCH_THERMOSTAT_PRIVATE_H

#include "Arduino.h"

# define THERMOSTAT_MASK_4_BIT					0xF//Mode (4 bits)
# define THERMOSTAT_MASK_5_BIT					0x1F//Mode (5 bits)
# define THERMOSTAT_CELSIUS						0x0
# define THERMOSTAT_FAHRENHEIT					0x1
# define THERMOSTAT_SETPOINT_PRECISION			0x1
# define THERMOSTAT_SETPOINT_SIZE				0x2
# define THERMOSTAT_SETPOINT_RATIO				10//the number of zeros depends on THERMOSTAT_SETPOINT_PRECISION

# define THERMOSTAT_SETPOINT_SCALE(channel)		((ZUNO_CFG_CHANNEL(channel).params[0] & THERMOSTAT_UNITS_FAHRENHEIT) != 0 ? THERMOSTAT_FAHRENHEIT : THERMOSTAT_CELSIUS)

# define THERMOSTAT_SETPOINT_PARAMETR(size, scale, precision)		size | ((scale) << 3) | ((precision) << 5)


/******************Thermostat Mode*******************************************************************************************************/
/************************************************************/
/* Thermostat Mode Supported Report V3 command class structs */
/************************************************************/
typedef struct							ZwThermostatModeSupportedReport1ByteFrame_s
{
	uint8_t								cmdClass;/* The command class */
	uint8_t 							cmd;/* The command */
	uint8_t								bitMask1;
}										ZwThermostatModeSupportedReport1ByteFrame_t;

typedef struct							ZwThermostatModeSupportedReport2ByteFrame_s
{
	uint8_t								cmdClass;/* The command class */
	uint8_t 							cmd;/* The command */
	uint8_t								bitMask1;/* MSB */
	uint8_t								bitMask2;/* LSB */
}										ZwThermostatModeSupportedReport2ByteFrame_t;

typedef struct							ZwThermostatModeSupportedReport3ByteFrame_s
{
	uint8_t								cmdClass;/* The command class */
	uint8_t 							cmd;/* The command */
	uint8_t								bitMask1;/* MSB */
	uint8_t								bitMask2;
	uint8_t								bitMask3;/* LSB */
}										ZwThermostatModeSupportedReport3ByteFrame_t;

typedef struct							ZwThermostatModeSupportedReport4ByteFrame_s
{
	uint8_t								cmdClass;/* The command class */
	uint8_t 							cmd;/* The command */
	uint8_t								bitMask1;/* MSB */
	uint8_t								bitMask2;
	uint8_t								bitMask3;
	uint8_t								bitMask4;/* LSB */
}										ZwThermostatModeSupportedReport4ByteFrame_t;

typedef union							ZwThermostatModeSupportedReportFrame_u
{
	ZwThermostatModeSupportedReport1ByteFrame_t			byte1;
	ZwThermostatModeSupportedReport2ByteFrame_t			byte2;
	ZwThermostatModeSupportedReport3ByteFrame_t			byte3;
	ZwThermostatModeSupportedReport4ByteFrame_t			byte4;
}										ZwThermostatModeSupportedReportFrame_t;


/************************************************************/
/* Thermostat Mode Report V2 command class structs */       
/************************************************************/
typedef struct								ZwThermostatModeReportV2Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									level;/* masked byte */
}											ZwThermostatModeReportV2Frame_t;


/************************************************************/
/* Thermostat Mode Report V3 command class structs */ 
/************************************************************/
typedef struct								ZwThermostatModeReport1ByteV3Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									level;/* masked byte */
	uint8_t									manufacturerData1;
}											ZwThermostatModeReport1ByteV3Frame_t;

typedef struct								ZwThermostatModeReport2ByteV3Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									level;/* masked byte */
	uint8_t									manufacturerData1;
	uint8_t									manufacturerData2;
}											ZwThermostatModeReport2ByteV3Frame_t;

typedef struct								ZwThermostatModeReport3ByteV3Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									level;/* masked byte */
	uint8_t									manufacturerData1;
	uint8_t									manufacturerData2;
	uint8_t									manufacturerData3;
}											ZwThermostatModeReport3ByteV3Frame_t;

typedef struct								ZwThermostatModeReport4ByteV3Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									level;/* masked byte */
	uint8_t									manufacturerData1;
	uint8_t									manufacturerData2;
	uint8_t									manufacturerData3;
	uint8_t									manufacturerData4;
}											ZwThermostatModeReport4ByteV3Frame_t;

typedef union								ZwThermostatModeReportV3Frame_u
{
	ZwThermostatModeReport1ByteV3Frame_t	byte1;
	ZwThermostatModeReport2ByteV3Frame_t	byte2;
	ZwThermostatModeReport3ByteV3Frame_t	byte3;
	ZwThermostatModeReport4ByteV3Frame_t	byte4;
}											ZwThermostatModeReportV3Frame_t;

typedef union								ZwThermostatModeReportFrame_u
{
	ZwThermostatModeReportV2Frame_t			v2;
	ZwThermostatModeReportV3Frame_t			v3;
}											ZwThermostatModeReportFrame_t;


/************************************************************/
/* Thermostat Mode Set V2 command class structs */          
/************************************************************/
typedef struct								ZwThermostatModeSetV2Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									level;/* masked byte */
}											ZwThermostatModeSetV2Frame_t;


/************************************************************/
/* Thermostat Mode Set V3 command class structs */ 
/************************************************************/
typedef struct								ZwThermostatModeSet1ByteV3Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									level;/* masked byte */
	uint8_t									manufacturerData1;
}											ZwThermostatModeSet1ByteV3Frame_t;

typedef struct								ZwThermostatModeSet2ByteV3Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									level;/* masked byte */
	uint8_t									manufacturerData1;/* MSB */
	uint8_t									manufacturerData2;/* LSB */
}											ZwThermostatModeSet2ByteV3Frame_t;

typedef struct								ZwThermostatModeSet3ByteV3Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									level;/* masked byte */
	uint8_t									manufacturerData1;/* MSB */
	uint8_t									manufacturerData2;
	uint8_t									manufacturerData3;/* LSB */
}											ZwThermostatModeSet3ByteV3Frame_t;

typedef struct								ZwThermostatModeSet4ByteV3Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									level;/* masked byte */
	uint8_t									manufacturerData1;/* MSB */
	uint8_t									manufacturerData2;
	uint8_t									manufacturerData3;
	uint8_t									manufacturerData4;/* LSB */
}											ZwThermostatModeSet4ByteV3Frame_t;

typedef union								ZwThermostatModeSetV3Frame_u
{
	ZwThermostatModeSet1ByteV3Frame_t		byte1;
	ZwThermostatModeSet2ByteV3Frame_t		byte2;
	ZwThermostatModeSet3ByteV3Frame_t		byte3;
	ZwThermostatModeSet4ByteV3Frame_t		byte4;
}											ZwThermostatModeSetV3Frame_t;

typedef union								ZwThermostatModeSetFrame_u
{
	ZwThermostatModeSetV2Frame_t			v2;
	ZwThermostatModeSetV3Frame_t			v3;
}											ZwThermostatModeSetFrame_t;

/******************Thermostat Setpoint*******************************************************************************************************/
/************************************************************/
/* Thermostat Setpoint Supported Report V3 command class structs */
/************************************************************/
typedef struct							ZwThermostatSetpointSupportedReport1ByteFrame_s
{
	uint8_t								cmdClass;/* The command class */
	uint8_t 							cmd;/* The command */
	uint8_t								bitMask1;
}										ZwThermostatSetpointSupportedReport1ByteFrame_t;

typedef struct							ZwThermostatSetpointSupportedReport2ByteFrame_s
{
	uint8_t								cmdClass;/* The command class */
	uint8_t 							cmd;/* The command */
	uint8_t								bitMask1;/* MSB */
	uint8_t								bitMask2;/* LSB */
}										ZwThermostatSetpointSupportedReport2ByteFrame_t;

typedef struct							ZwThermostatSetpointSupportedReport3ByteFrame_s
{
	uint8_t								cmdClass;/* The command class */
	uint8_t 							cmd;/* The command */
	uint8_t								bitMask1;/* MSB */
	uint8_t								bitMask2;
	uint8_t								bitMask3;/* LSB */
}										ZwThermostatSetpointSupportedReport3ByteFrame_t;

typedef struct							ZwThermostatSetpointSupportedReport4ByteFrame_s
{
	uint8_t								cmdClass;/* The command class */
	uint8_t 							cmd;/* The command */
	uint8_t								bitMask1;/* MSB */
	uint8_t								bitMask2;
	uint8_t								bitMask3;
	uint8_t								bitMask4;/* LSB */
}										ZwThermostatSetpointSupportedReport4ByteFrame_t;

typedef union							ZwThermostatSetpointSupportedReportFrame_u
{
	ZwThermostatSetpointSupportedReport1ByteFrame_t			byte1;
	ZwThermostatSetpointSupportedReport2ByteFrame_t			byte2;
	ZwThermostatSetpointSupportedReport3ByteFrame_t			byte3;
	ZwThermostatSetpointSupportedReport4ByteFrame_t			byte4;
}										ZwThermostatSetpointSupportedReportFrame_t;


/************************************************************/
/* Thermostat Setpoint Get command class structs */      
/************************************************************/
typedef struct							ZwThermostatSetpointGetFrame_s
{
	uint8_t								cmdClass;/* The command class */
	uint8_t								cmd;/* The command */
	uint8_t								level;/* masked byte */
}										ZwThermostatSetpointGetFrame_t;

/************************************************************/
/* Thermostat Setpoint Report command class structs */
/************************************************************/
typedef struct							ZwThermostatSetpointReport1ByteFrame_s
{
	uint8_t								cmdClass;/* The command class */
	uint8_t								cmd;/* The command */
	uint8_t								level;/* masked byte */
	uint8_t								level2;/* masked byte */
	uint8_t								value1;
}										ZwThermostatSetpointReport1ByteFrame_t;

typedef struct							ZwThermostatSetpointReport2ByteFrame_s
{
	uint8_t								cmdClass;/* The command class */
	uint8_t								cmd;/* The command */
	uint8_t								level;/* masked byte */
	uint8_t								level2;/* masked byte */
	uint8_t								value1;/* MSB */
	uint8_t								value2;/* LSB */
}										ZwThermostatSetpointReport2ByteFrame_t;

typedef struct							ZwThermostatSetpointReport3ByteFrame_s
{
	uint8_t								cmdClass;/* The command class */
	uint8_t								cmd;/* The command */
	uint8_t								level;/* masked byte */
	uint8_t								level2;/* masked byte */
	uint8_t								value1;/* MSB */
	uint8_t								value2;
	uint8_t								value3;/* LSB */
}										ZwThermostatSetpointReport3ByteFrame_t;

typedef struct							ZwThermostatSetpointReport4ByteFrame_s
{
	uint8_t								cmdClass;/* The command class */
	uint8_t								cmd;/* The command */
	uint8_t								level;/* masked byte */
	uint8_t								level2;/* masked byte */
	uint8_t								value1;/* MSB */
	uint8_t								value2;
	uint8_t								value3;
	uint8_t								value4;/* LSB */
}										ZwThermostatSetpointReport4ByteFrame_t;

typedef union							ZwThermostatSetpointReportFrame_u
{
	ZwThermostatSetpointReport1ByteFrame_t			byte1;
	ZwThermostatSetpointReport2ByteFrame_t			byte2;
	ZwThermostatSetpointReport3ByteFrame_t			byte3;
	ZwThermostatSetpointReport4ByteFrame_t			byte4;
}										ZwThermostatSetpointReportFrame_t;


/************************************************************/
/* Thermostat Setpoint Set command class structs */
/************************************************************/
typedef struct							ZwThermostatSetpointSet1ByteFrame_s
{
	uint8_t								cmdClass;/* The command class */
	uint8_t								cmd;/* The command */
	uint8_t								level;/* masked byte */
	uint8_t								level2;/* masked byte */
	uint8_t								value1;
}										ZwThermostatSetpointSet1ByteFrame_t;

typedef struct							ZwThermostatSetpointSet2ByteFrame_s
{
	uint8_t								cmdClass;/* The command class */
	uint8_t								cmd;/* The command */
	uint8_t								level;/* masked byte */
	uint8_t								level2;/* masked byte */
	uint8_t								value1;/* MSB */
	uint8_t								value2;/* LSB */
}										ZwThermostatSetpointSet2ByteFrame_t;

typedef struct							ZwThermostatSetpointSet3ByteFrame_s
{
	uint8_t								cmdClass;/* The command class */
	uint8_t								cmd;/* The command */
	uint8_t								level;/* masked byte */
	uint8_t								level2;/* masked byte */
	uint8_t								value1;/* MSB */
	uint8_t								value2;
	uint8_t								value3;/* LSB */
}										ZwThermostatSetpointSet3ByteFrame_t;

typedef struct							ZwThermostatSetpointSet4ByteFrame_s
{
	uint8_t								cmdClass;/* The command class */
	uint8_t								cmd;/* The command */
	uint8_t								level;/* masked byte */
	uint8_t								level2;/* masked byte */
	uint8_t								value1;/* MSB */
	uint8_t								value2;
	uint8_t								value3;
	uint8_t								value4;/* LSB */
}										ZwThermostatSetpointSet4ByteFrame_t;

typedef union							ZwThermostatSetpointSetFrame_u
{
	ZwThermostatSetpointSet1ByteFrame_t			byte1;
	ZwThermostatSetpointSet2ByteFrame_t			byte2;
	ZwThermostatSetpointSet3ByteFrame_t			byte3;
	ZwThermostatSetpointSet4ByteFrame_t			byte4;
}										ZwThermostatSetpointSetFrame_t;

#endif // ZWCC_SWITCH_THERMOSTAT_PRIVATE_H