#ifndef ZWCC_SWITCH_THERMOSTAT_H
#define ZWCC_SWITCH_THERMOSTAT_H

#include "Arduino.h"
#include "ZWSupport.h"

/* Switch Thermostat command class commands */
#define COMMAND_CLASS_THERMOSTAT_FAN_MODE                                                0x44
#define COMMAND_CLASS_THERMOSTAT_FAN_STATE                                               0x45
#define COMMAND_CLASS_THERMOSTAT_HEATING                                                 0x38
#define COMMAND_CLASS_THERMOSTAT_OPERATING_STATE                                         0x42
#define COMMAND_CLASS_THERMOSTAT_SETBACK                                                 0x47

/* Thermostat Fan Mode command class commands */
#define THERMOSTAT_FAN_MODE_VERSION                                                      0x01
#define THERMOSTAT_FAN_MODE_GET                                                          0x02
#define THERMOSTAT_FAN_MODE_REPORT                                                       0x03
#define THERMOSTAT_FAN_MODE_SET                                                          0x01
#define THERMOSTAT_FAN_MODE_SUPPORTED_GET                                                0x04
#define THERMOSTAT_FAN_MODE_SUPPORTED_REPORT                                             0x05

/* Thermostat Heating command class commands */
#define THERMOSTAT_HEATING_VERSION                                                       0x01
#define THERMOSTAT_HEATING_STATUS_REPORT                                                 0x0D
#define THERMOSTAT_HEATING_MODE_GET                                                      0x02
#define THERMOSTAT_HEATING_MODE_REPORT                                                   0x03
#define THERMOSTAT_HEATING_MODE_SET                                                      0x01
#define THERMOSTAT_HEATING_RELAY_STATUS_GET                                              0x09
#define THERMOSTAT_HEATING_RELAY_STATUS_REPORT                                           0x0A
#define THERMOSTAT_HEATING_SETPOINT_GET                                                  0x05
#define THERMOSTAT_HEATING_SETPOINT_REPORT                                               0x06
#define THERMOSTAT_HEATING_SETPOINT_SET                                                  0x04
#define THERMOSTAT_HEATING_STATUS_GET                                                    0x0C
#define THERMOSTAT_HEATING_STATUS_SET                                                    0x0B
#define THERMOSTAT_HEATING_TIMED_OFF_SET                                                 0x11

/* Thermostat Mode command class commands */
#define THERMOSTAT_MODE_VERSION                                                          0x03
#define THERMOSTAT_MODE_GET                                                              0x02
#define THERMOSTAT_MODE_REPORT                                                           0x03
#define THERMOSTAT_MODE_SET                                                              0x01
#define THERMOSTAT_MODE_SUPPORTED_GET                                                    0x04
#define THERMOSTAT_MODE_SUPPORTED_REPORT                                                 0x05

/* Thermostat Operating State command class commands */
#define THERMOSTAT_OPERATING_STATE_VERSION                                               0x01
#define THERMOSTAT_OPERATING_STATE_GET                                                   0x02
#define THERMOSTAT_OPERATING_STATE_REPORT                                                0x03

/* Thermostat Setback command class commands */
#define THERMOSTAT_SETBACK_VERSION                                                       0x01
#define THERMOSTAT_SETBACK_GET                                                           0x02
#define THERMOSTAT_SETBACK_REPORT                                                        0x03
#define THERMOSTAT_SETBACK_SET                                                           0x01

/* Thermostat Setpoint command class commands */
#define THERMOSTAT_SETPOINT_VERSION                                                      0x03
#define THERMOSTAT_SETPOINT_GET                                                          0x02
#define THERMOSTAT_SETPOINT_REPORT                                                       0x03
#define THERMOSTAT_SETPOINT_SET                                                          0x01
#define THERMOSTAT_SETPOINT_SUPPORTED_GET                                                0x04
#define THERMOSTAT_SETPOINT_SUPPORTED_REPORT                                             0x05
#define THERMOSTAT_SETPOINT_CAPABILITIES_GET                                             0x09
#define THERMOSTAT_SETPOINT_CAPABILITIES_REPORT                                          0x0A

/* Thermostat Setpoint command class commands */
#define THERMOSTAT_SETPOINT_VERSION                                                      0x03
#define THERMOSTAT_SETPOINT_GET                                                          0x02
#define THERMOSTAT_SETPOINT_REPORT                                                       0x03
#define THERMOSTAT_SETPOINT_SET                                                          0x01
#define THERMOSTAT_SETPOINT_SUPPORTED_GET                                                0x04
#define THERMOSTAT_SETPOINT_SUPPORTED_REPORT                                             0x05
#define THERMOSTAT_SETPOINT_CAPABILITIES_GET                                             0x09
#define THERMOSTAT_SETPOINT_CAPABILITIES_REPORT                                          0x0A
/* Values used for Thermostat Setpoint Get command */
#define THERMOSTAT_SETPOINT_GET_LEVEL_SETPOINT_TYPE_MASK                                 0x0F
#define THERMOSTAT_SETPOINT_GET_SETPOINT_TYPE_NOT_SUPPORTED                              0x00
#define THERMOSTAT_SETPOINT_GET_SETPOINT_TYPE_HEATING_1                                  0x01
#define THERMOSTAT_SETPOINT_GET_SETPOINT_TYPE_COOLING_1                                  0x02
#define THERMOSTAT_SETPOINT_GET_SETPOINT_TYPE_NOT_SUPPORTED1                             0x03
#define THERMOSTAT_SETPOINT_GET_SETPOINT_TYPE_NOT_SUPPORTED2                             0x04
#define THERMOSTAT_SETPOINT_GET_SETPOINT_TYPE_NOT_SUPPORTED3                             0x05
#define THERMOSTAT_SETPOINT_GET_SETPOINT_TYPE_NOT_SUPPORTED4                             0x06
#define THERMOSTAT_SETPOINT_GET_SETPOINT_TYPE_FURNACE                                    0x07
#define THERMOSTAT_SETPOINT_GET_SETPOINT_TYPE_DRY_AIR                                    0x08
#define THERMOSTAT_SETPOINT_GET_SETPOINT_TYPE_MOIST_AIR                                  0x09
#define THERMOSTAT_SETPOINT_GET_SETPOINT_TYPE_AUTO_CHANGEOVER                            0x0A
#define THERMOSTAT_SETPOINT_GET_SETPOINT_TYPE_ENERGY_SAVE_HEATING                        0x0B
#define THERMOSTAT_SETPOINT_GET_SETPOINT_TYPE_ENERGY_SAVE_COOLING                        0x0C
#define THERMOSTAT_SETPOINT_GET_SETPOINT_TYPE_AWAY_HEATING                               0x0D
#define THERMOSTAT_SETPOINT_GET_SETPOINT_TYPE_AWAY_COOLING                               0x0E
#define THERMOSTAT_SETPOINT_GET_SETPOINT_TYPE_FULL_POWER                                 0x0F
#define THERMOSTAT_SETPOINT_GET_LEVEL_RESERVED_MASK                                      0xF0
#define THERMOSTAT_SETPOINT_GET_LEVEL_RESERVED_SHIFT                                     0x04
/* Values used for Thermostat Setpoint Report command */
#define THERMOSTAT_SETPOINT_REPORT_LEVEL_SETPOINT_TYPE_MASK                              0x0F
#define THERMOSTAT_SETPOINT_REPORT_SETPOINT_TYPE_NOT_SUPPORTED                           0x00
#define THERMOSTAT_SETPOINT_REPORT_SETPOINT_TYPE_HEATING_1                               0x01
#define THERMOSTAT_SETPOINT_REPORT_SETPOINT_TYPE_COOLING_1                               0x02
#define THERMOSTAT_SETPOINT_REPORT_SETPOINT_TYPE_NOT_SUPPORTED1                          0x03
#define THERMOSTAT_SETPOINT_REPORT_SETPOINT_TYPE_NOT_SUPPORTED2                          0x04
#define THERMOSTAT_SETPOINT_REPORT_SETPOINT_TYPE_NOT_SUPPORTED3                          0x05
#define THERMOSTAT_SETPOINT_REPORT_SETPOINT_TYPE_NOT_SUPPORTED4                          0x06
#define THERMOSTAT_SETPOINT_REPORT_SETPOINT_TYPE_FURNACE                                 0x07
#define THERMOSTAT_SETPOINT_REPORT_SETPOINT_TYPE_DRY_AIR                                 0x08
#define THERMOSTAT_SETPOINT_REPORT_SETPOINT_TYPE_MOIST_AIR                               0x09
#define THERMOSTAT_SETPOINT_REPORT_SETPOINT_TYPE_AUTO_CHANGEOVER                         0x0A
#define THERMOSTAT_SETPOINT_REPORT_SETPOINT_TYPE_ENERGY_SAVE_HEATING                     0x0B
#define THERMOSTAT_SETPOINT_REPORT_SETPOINT_TYPE_ENERGY_SAVE_COOLING                     0x0C
#define THERMOSTAT_SETPOINT_REPORT_SETPOINT_TYPE_AWAY_HEATING                            0x0D
#define THERMOSTAT_SETPOINT_REPORT_SETPOINT_TYPE_AWAY_COOLING                            0x0E
#define THERMOSTAT_SETPOINT_REPORT_SETPOINT_TYPE_FULL_POWER                              0x0F
#define THERMOSTAT_SETPOINT_REPORT_LEVEL_RESERVED_MASK                                   0xF0
#define THERMOSTAT_SETPOINT_REPORT_LEVEL_RESERVED_SHIFT                                  0x04
#define THERMOSTAT_SETPOINT_REPORT_LEVEL2_SIZE_MASK                                      0x07
#define THERMOSTAT_SETPOINT_REPORT_LEVEL2_SCALE_MASK                                     0x18
#define THERMOSTAT_SETPOINT_REPORT_LEVEL2_SCALE_SHIFT                                    0x03
#define THERMOSTAT_SETPOINT_REPORT_LEVEL2_PRECISION_MASK                                 0xE0
#define THERMOSTAT_SETPOINT_REPORT_LEVEL2_PRECISION_SHIFT                                0x05
/* Values used for Thermostat Setpoint Set command */
#define THERMOSTAT_SETPOINT_SET_LEVEL_SETPOINT_TYPE_MASK                                 0x0F
#define THERMOSTAT_SETPOINT_SET_SETPOINT_TYPE_NOT_SUPPORTED                              0x00
#define THERMOSTAT_SETPOINT_SET_SETPOINT_TYPE_HEATING_1                                  0x01
#define THERMOSTAT_SETPOINT_SET_SETPOINT_TYPE_COOLING_1                                  0x02
#define THERMOSTAT_SETPOINT_SET_SETPOINT_TYPE_NOT_SUPPORTED1                             0x03
#define THERMOSTAT_SETPOINT_SET_SETPOINT_TYPE_NOT_SUPPORTED2                             0x04
#define THERMOSTAT_SETPOINT_SET_SETPOINT_TYPE_NOT_SUPPORTED3                             0x05
#define THERMOSTAT_SETPOINT_SET_SETPOINT_TYPE_NOT_SUPPORTED4                             0x06
#define THERMOSTAT_SETPOINT_SET_SETPOINT_TYPE_FURNACE                                    0x07
#define THERMOSTAT_SETPOINT_SET_SETPOINT_TYPE_DRY_AIR                                    0x08
#define THERMOSTAT_SETPOINT_SET_SETPOINT_TYPE_MOIST_AIR                                  0x09
#define THERMOSTAT_SETPOINT_SET_SETPOINT_TYPE_AUTO_CHANGEOVER                            0x0A
#define THERMOSTAT_SETPOINT_SET_SETPOINT_TYPE_ENERGY_SAVE_HEATING                        0x0B
#define THERMOSTAT_SETPOINT_SET_SETPOINT_TYPE_ENERGY_SAVE_COOLING                        0x0C
#define THERMOSTAT_SETPOINT_SET_SETPOINT_TYPE_AWAY_HEATING                               0x0D
#define THERMOSTAT_SETPOINT_SET_SETPOINT_TYPE_AWAY_COOLING                               0x0E
#define THERMOSTAT_SETPOINT_SET_SETPOINT_TYPE_FULL_POWER                                 0x0F
#define THERMOSTAT_SETPOINT_SET_LEVEL_RESERVED_MASK                                      0xF0
#define THERMOSTAT_SETPOINT_SET_LEVEL_RESERVED_SHIFT                                     0x04
#define THERMOSTAT_SETPOINT_SET_LEVEL2_SIZE_MASK                                         0x07
#define THERMOSTAT_SETPOINT_SET_LEVEL2_SCALE_MASK                                        0x18
#define THERMOSTAT_SETPOINT_SET_LEVEL2_SCALE_SHIFT                                       0x03
#define THERMOSTAT_SETPOINT_SET_LEVEL2_PRECISION_MASK                                    0xE0
#define THERMOSTAT_SETPOINT_SET_LEVEL2_PRECISION_SHIFT                                   0x05
/* Values used for Thermostat Setpoint Capabilities Get command */
#define THERMOSTAT_SETPOINT_CAPABILITIES_GET_PROPERTIES1_SETPOINT_TYPE_MASK              0x0F
#define THERMOSTAT_SETPOINT_CAPABILITIES_GET_SETPOINT_TYPE_NOT_SUPPORTED                 0x00
#define THERMOSTAT_SETPOINT_CAPABILITIES_GET_SETPOINT_TYPE_HEATING_1                     0x01
#define THERMOSTAT_SETPOINT_CAPABILITIES_GET_SETPOINT_TYPE_COOLING_1                     0x02
#define THERMOSTAT_SETPOINT_CAPABILITIES_GET_SETPOINT_TYPE_NOT_SUPPORTED1                0x03
#define THERMOSTAT_SETPOINT_CAPABILITIES_GET_SETPOINT_TYPE_NOT_SUPPORTED2                0x04
#define THERMOSTAT_SETPOINT_CAPABILITIES_GET_SETPOINT_TYPE_NOT_SUPPORTED3                0x05
#define THERMOSTAT_SETPOINT_CAPABILITIES_GET_SETPOINT_TYPE_NOT_SUPPORTED4                0x06
#define THERMOSTAT_SETPOINT_CAPABILITIES_GET_SETPOINT_TYPE_FURNACE                       0x07
#define THERMOSTAT_SETPOINT_CAPABILITIES_GET_SETPOINT_TYPE_DRY_AIR                       0x08
#define THERMOSTAT_SETPOINT_CAPABILITIES_GET_SETPOINT_TYPE_MOIST_AIR                     0x09
#define THERMOSTAT_SETPOINT_CAPABILITIES_GET_SETPOINT_TYPE_AUTO_CHANGEOVER               0x0A
#define THERMOSTAT_SETPOINT_CAPABILITIES_GET_SETPOINT_TYPE_ENERGY_SAVE_HEATING           0x0B
#define THERMOSTAT_SETPOINT_CAPABILITIES_GET_SETPOINT_TYPE_ENERGY_SAVE_COOLING           0x0C
#define THERMOSTAT_SETPOINT_CAPABILITIES_GET_SETPOINT_TYPE_AWAY_HEATING                  0x0D
#define THERMOSTAT_SETPOINT_CAPABILITIES_GET_SETPOINT_TYPE_AWAY_COOLING                  0x0E
#define THERMOSTAT_SETPOINT_CAPABILITIES_GET_SETPOINT_TYPE_FULL_POWER                    0x0F
#define THERMOSTAT_SETPOINT_CAPABILITIES_GET_PROPERTIES1_RESERVED_MASK                   0xF0
#define THERMOSTAT_SETPOINT_CAPABILITIES_GET_PROPERTIES1_RESERVED_SHIFT                  0x04
/* Values used for Thermostat Setpoint Capabilities Report command */
#define THERMOSTAT_SETPOINT_CAPABILITIES_REPORT_PROPERTIES1_SETPOINT_TYPE_MASK           0x0F
#define THERMOSTAT_SETPOINT_CAPABILITIES_REPORT_SETPOINT_TYPE_NOT_SUPPORTED              0x00
#define THERMOSTAT_SETPOINT_CAPABILITIES_REPORT_SETPOINT_TYPE_HEATING_1                  0x01
#define THERMOSTAT_SETPOINT_CAPABILITIES_REPORT_SETPOINT_TYPE_COOLING_1                  0x02
#define THERMOSTAT_SETPOINT_CAPABILITIES_REPORT_SETPOINT_TYPE_NOT_SUPPORTED1             0x03
#define THERMOSTAT_SETPOINT_CAPABILITIES_REPORT_SETPOINT_TYPE_NOT_SUPPORTED2             0x04
#define THERMOSTAT_SETPOINT_CAPABILITIES_REPORT_SETPOINT_TYPE_NOT_SUPPORTED3             0x05
#define THERMOSTAT_SETPOINT_CAPABILITIES_REPORT_SETPOINT_TYPE_NOT_SUPPORTED4             0x06
#define THERMOSTAT_SETPOINT_CAPABILITIES_REPORT_SETPOINT_TYPE_FURNACE                    0x07
#define THERMOSTAT_SETPOINT_CAPABILITIES_REPORT_SETPOINT_TYPE_DRY_AIR                    0x08
#define THERMOSTAT_SETPOINT_CAPABILITIES_REPORT_SETPOINT_TYPE_MOIST_AIR                  0x09
#define THERMOSTAT_SETPOINT_CAPABILITIES_REPORT_SETPOINT_TYPE_AUTO_CHANGEOVER            0x0A
#define THERMOSTAT_SETPOINT_CAPABILITIES_REPORT_SETPOINT_TYPE_ENERGY_SAVE_HEATING        0x0B
#define THERMOSTAT_SETPOINT_CAPABILITIES_REPORT_SETPOINT_TYPE_ENERGY_SAVE_COOLING        0x0C
#define THERMOSTAT_SETPOINT_CAPABILITIES_REPORT_SETPOINT_TYPE_AWAY_HEATING               0x0D
#define THERMOSTAT_SETPOINT_CAPABILITIES_REPORT_SETPOINT_TYPE_AWAY_COOLING               0x0E
#define THERMOSTAT_SETPOINT_CAPABILITIES_REPORT_SETPOINT_TYPE_FULL_POWER                 0x0F
#define THERMOSTAT_SETPOINT_CAPABILITIES_REPORT_PROPERTIES1_RESERVED_MASK                0xF0
#define THERMOSTAT_SETPOINT_CAPABILITIES_REPORT_PROPERTIES1_RESERVED_SHIFT               0x04
#define THERMOSTAT_SETPOINT_CAPABILITIES_REPORT_PROPERTIES2_SIZE1_MASK                   0x07
#define THERMOSTAT_SETPOINT_CAPABILITIES_REPORT_PROPERTIES2_SCALE1_MASK                  0x18
#define THERMOSTAT_SETPOINT_CAPABILITIES_REPORT_PROPERTIES2_SCALE1_SHIFT                 0x03
#define THERMOSTAT_SETPOINT_CAPABILITIES_REPORT_PROPERTIES2_PRECISION1_MASK              0xE0
#define THERMOSTAT_SETPOINT_CAPABILITIES_REPORT_PROPERTIES2_PRECISION1_SHIFT             0x05
#define THERMOSTAT_SETPOINT_CAPABILITIES_REPORT_PROPERTIES3_SIZE2_MASK                   0x07
#define THERMOSTAT_SETPOINT_CAPABILITIES_REPORT_PROPERTIES3_SCALE2_MASK                  0x18
#define THERMOSTAT_SETPOINT_CAPABILITIES_REPORT_PROPERTIES3_SCALE2_SHIFT                 0x03
#define THERMOSTAT_SETPOINT_CAPABILITIES_REPORT_PROPERTIES3_PRECISION2_MASK              0xE0
#define THERMOSTAT_SETPOINT_CAPABILITIES_REPORT_PROPERTIES3_PRECISION2_SHIFT             0x05

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
typedef struct							ZwThermostatSetpointReportFrame_s
{
	uint8_t								cmdClass;/* The command class */
	uint8_t								cmd;/* The command */
	uint8_t								level;/* masked byte */
	uint8_t								level2;/* masked byte */
	uint8_t								value[];/* MSB  LSB */
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

/************************************************************/
/* Thermostat Setpoint Capabilities Get command class structs */
/************************************************************/
typedef struct							ZwThermostatSetpointCapabilitiesGetFrame_s
{
	uint8_t								cmdClass;/* The command class */
	uint8_t								cmd;/* The command */
	uint8_t								properties1;/* masked byte */
}										ZwThermostatSetpointCapabilitiesGetFrame_t;


/************************************************************/
/* Thermostat Setpoint Capabilities Report command class structs */
/************************************************************/
typedef struct							ZwThermostatSetpointCapabilitiesReportFrame_s
{
	uint8_t								cmdClass;/* The command class */
	uint8_t								cmd;/* The command */
	uint8_t								properties1;/* masked byte */
	uint8_t								data[];
}										ZwThermostatSetpointCapabilitiesReportFrame_t;

int zuno_CCThermostatModeHandler(uint8_t channel, const ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report);
int zuno_CCThermostatReport(byte channel, ZUNOCommandPacket_t *packet);
int zuno_CCThermostatSetPointHandler(uint8_t channel, const ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report);
#endif // ZWCC_SWITCH_THERMOSTAT_H