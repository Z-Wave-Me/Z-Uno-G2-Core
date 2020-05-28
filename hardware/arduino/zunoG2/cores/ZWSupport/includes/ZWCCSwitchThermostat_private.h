#ifndef ZWCC_SWITCH_THERMOSTAT_PRIVATE_H
#define ZWCC_SWITCH_THERMOSTAT_PRIVATE_H

#include "Arduino.h"

# define THERMOSTAT_MODE_MASK					0x1F//Mode (5 bits)

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
	uint8_t								bitMask1;
	uint8_t								bitMask2;
}										ZwThermostatModeSupportedReport2ByteFrame_t;

typedef struct							ZwThermostatModeSupportedReport3ByteFrame_s
{
	uint8_t								cmdClass;/* The command class */
	uint8_t 							cmd;/* The command */
	uint8_t								bitMask1;
	uint8_t								bitMask2;
	uint8_t								bitMask3;
}										ZwThermostatModeSupportedReport3ByteFrame_t;

typedef struct							ZwThermostatModeSupportedReport4ByteFrame_s
{
	uint8_t								cmdClass;/* The command class */
	uint8_t 							cmd;/* The command */
	uint8_t								bitMask1;
	uint8_t								bitMask2;
	uint8_t								bitMask3;
	uint8_t								bitMask4;
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

#endif // ZWCC_SWITCH_THERMOSTAT_PRIVATE_H