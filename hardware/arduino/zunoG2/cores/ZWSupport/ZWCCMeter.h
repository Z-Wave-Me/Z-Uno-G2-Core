#ifndef __ZWCC_METER_H__
#define __ZWCC_METER_H__
#include "Arduino.h"
#include "ZWSupport.h"

#ifdef ZUNO_STATICGATHERING_PHASE
#define ZUNO_METER(TYPE, RESETABLE, SCALE, SIZE, PRECISION, GETTER, RESETTER) {ZUNO_METER_CHANNEL_NUMBER,\
		((TYPE << ZUNO_METER_SUBTYPE_TYPE_SHIFT) & ZUNO_METER_SUBTYPE_TYPE_MASK) | ((RESETABLE << ZUNO_METER_SUBTYPE_RESETABLE_SHIFT) & ZUNO_METER_SUBTYPE_RESETABLE_MASK),\
		((SCALE << ZUNO_METER_PARAMETR_SCALE_SHIFT) & ZUNO_METER_PARAMETR_SCALE_MASK) |\
		(((SIZE - 0x1) << ZUNO_METER_PARAMETR_SIZE_SHIFT) & ZUNO_METER_PARAMETR_SIZE_MASK) |\
		((PRECISION << ZUNO_METER_PARAMETR_PRECISION_SHIFT) & ZUNO_METER_PARAMETR_PRECISION_MASK),\
		(void*)GETTER, (void*)RESETTER, (void*)0, (void*)0}
#endif


#define ZUNO_METER_SUBTYPE_TYPE_SHIFT							0x00
#define ZUNO_METER_SUBTYPE_TYPE_MASK							(0x0F << ZUNO_METER_SUBTYPE_TYPE_SHIFT)
#define ZUNO_METER_SUBTYPE_RESETABLE_SHIFT						0x07
#define ZUNO_METER_SUBTYPE_RESETABLE_MASK						(0x01 << ZUNO_METER_SUBTYPE_RESETABLE_SHIFT)
#define ZUNO_METER_PARAMETR_SCALE_SHIFT							0x00
#define ZUNO_METER_PARAMETR_SCALE_MASK							(0x0F << ZUNO_METER_PARAMETR_SCALE_SHIFT)
#define ZUNO_METER_PARAMETR_SIZE_SHIFT							0x04
#define ZUNO_METER_PARAMETR_SIZE_MASK							(0x03 << ZUNO_METER_PARAMETR_SIZE_SHIFT)
#define ZUNO_METER_PARAMETR_PRECISION_SHIFT						0x06
#define ZUNO_METER_PARAMETR_PRECISION_MASK						(0x03 << ZUNO_METER_PARAMETR_PRECISION_SHIFT)

#define ZUNO_METER_SCALE_MST									0x07

#define ZUNO_METER_TYPE_ELECTRIC								0x01
#define ZUNO_METER_ELECTRIC_SCALE_KWH							0x00
#define ZUNO_METER_ELECTRIC_SCALE_KVAH							0x01
#define ZUNO_METER_ELECTRIC_SCALE_WATTS							0x02
#define ZUNO_METER_ELECTRIC_SCALE_PULSECOUNT					0x03
#define ZUNO_METER_ELECTRIC_SCALE_VOLTS							0x04
#define ZUNO_METER_ELECTRIC_SCALE_AMPS							0x05
#define ZUNO_METER_ELECTRIC_SCALE_POWERFACTOR					0x06
#define ZUNO_METER_ELECTRIC_SCALE_KVAR							(ZUNO_METER_SCALE_MST + 0x0)
#define ZUNO_METER_ELECTRIC_SCALE_KVARH							(ZUNO_METER_SCALE_MST + 0x1)
#define ZUNO_METER_TYPE_GAS										0x02
#define ZUNO_METER_GAS_SCALE_METERS3							0x00
#define ZUNO_METER_GAS_SCALE_FEET3								0x01
#define ZUNO_METER_GAS_SCALE_PULSECOUNT							0x03
#define ZUNO_METER_TYPE_WATER									0x03
#define ZUNO_METER_WATER_SCALE_METERS3							0x00
#define ZUNO_METER_WATER_SCALE_FEET3							0x01
#define ZUNO_METER_WATER_SCALE_GALLONS							0x02
#define ZUNO_METER_WATER_SCALE_PULSECOUNT						0x03
#define ZUNO_METER_TYPE_HEATING									0x04
#define ZUNO_METER_HEATING_SCALE_KWH							0x00
#define ZUNO_METER_TYPE_COOLING									0x05
#define ZUNO_METER_COOLING_SCALE_KWH							0x00
#define ZUNO_METER_RESETABLE									0x80
#define METER_RESET_ENABLE										0x01
#define METER_RESET_DISABLE										0x00
#define METER_EMPTY_RESETTER							
#define METER_PRECISION_ZERO_DECIMALS							0x00
#define METER_PRECISION_ONE_DECIMAL								0x01
#define METER_PRECISION_TWO_DECIMALS							0x02
#define METER_PRECISION_THREE_DECIMALS							0x03
#define METER_SIZE_ONE_BYTE										0x01
#define METER_SIZE_TWO_BYTES									0x02
#define METER_SIZE_FOUR_BYTES									0x04


// cmd class
#define METER_GET               0x01
#define METER_REPORT            0x02
#define METER_SUPPORTED_GET     0x03
#define METER_RESET             0x05
#define METER_VERSION           0x06

#define METER_PROPERTIES_PRECISION_SHIFT		0x05
#define METER_PROPERTIES_SCALE_MSB_MASK			0x80
#define METER_PROPERTIES_SCALE_MSB_SHIFT		0x05
#define METER_PROPERTIES_SCALE_LSB_MASK			0x18
#define METER_PROPERTIES_SCALE_LSB_SHIFT		0x03
#define METER_PROPERTIES_TYPE_MASK				0x1F
#define METER_PROPERTIES_SIZE_MASK				0x07

/* Meter command class commands */
#define METER_VERSION                                                                    0x06
#define METER_GET                                                                        0x01
#define METER_REPORT                                                                     0x02
#define METER_RESET                                                                      0x05
#define METER_SUPPORTED_GET                                                              0x03
#define METER_SUPPORTED_REPORT                                                           0x04
/* Values used for Meter Get command */
#define METER_GET_PROPERTIES1_RESERVED_MASK                                              0x07
#define METER_GET_PROPERTIES1_SCALE_MASK                                                 0x38
#define METER_GET_PROPERTIES1_SCALE_SHIFT                                                0x03
#define METER_GET_PROPERTIES1_RATE_TYPE_MASK                                             0xC0
#define METER_GET_PROPERTIES1_RATE_TYPE_SHIFT                                            0x06
#define METER_GET_RATE_TYPE_RESERVED                                                     0x00
#define METER_GET_RATE_TYPE_IMPORT                                                       0x01
#define METER_GET_RATE_TYPE_EXPORT                                                       0x02
#define METER_GET_RATE_TYPE_NOT_TO_BE_USED                                               0x03
/* Values used for Meter Report command */
#define METER_REPORT_PROPERTIES1_METER_TYPE_MASK                                         0x1F
#define METER_REPORT_METER_TYPE_RESERVED                                                 0x00
#define METER_REPORT_METER_TYPE_ELECTRIC_METER                                           0x01
#define METER_REPORT_METER_TYPE_GAS_METER                                                0x02
#define METER_REPORT_METER_TYPE_WATER_METER                                              0x03
#define METER_REPORT_METER_TYPE_HEATING_METER                                            0x04
#define METER_REPORT_METER_TYPE_COOLING_METER                                            0x05
#define METER_REPORT_PROPERTIES1_RATE_TYPE_MASK                                          0x60
#define METER_REPORT_PROPERTIES1_RATE_TYPE_SHIFT                                         0x05
#define METER_REPORT_RATE_TYPE_RESERVED                                                  0x00
#define METER_REPORT_RATE_TYPE_IMPORT                                                    0x01
#define METER_REPORT_RATE_TYPE_EXPORT                                                    0x02
#define METER_REPORT_RATE_TYPE_NOT_TO_BE_USED                                            0x03
#define METER_REPORT_PROPERTIES1_SCALE_BIT_2_BIT_MASK                                    0x80
#define METER_REPORT_PROPERTIES2_SIZE_MASK                                               0x07
#define METER_REPORT_PROPERTIES2_SCALE_BITS_10_MASK                                      0x18
#define METER_REPORT_PROPERTIES2_SCALE_BITS_10_SHIFT                                     0x03
#define METER_REPORT_PROPERTIES2_PRECISION_MASK                                          0xE0
#define METER_REPORT_PROPERTIES2_PRECISION_SHIFT                                         0x05
/* Values used for Meter Reset command */
#define METER_RESET_PROPERTIES1_METER_TYPE_MASK                                          0x1F
#define METER_RESET_METER_TYPE_RESERVED                                                  0x00
#define METER_RESET_METER_TYPE_ELECTRIC_METER                                            0x01
#define METER_RESET_METER_TYPE_GAS_METER                                                 0x02
#define METER_RESET_METER_TYPE_WATER_METER                                               0x03
#define METER_RESET_METER_TYPE_HEATING_METER                                             0x04
#define METER_RESET_METER_TYPE_COOLING_METER                                             0x05
#define METER_RESET_PROPERTIES1_SIZE_MASK                                                0xE0
#define METER_RESET_PROPERTIES1_SIZE_SHIFT                                               0x05
/* Values used for Meter Supported Report command */
#define METER_SUPPORTED_REPORT_PROPERTIES1_METER_TYPE_MASK                               0x1F
#define METER_SUPPORTED_REPORT_METER_TYPE_RESERVED                                       0x00
#define METER_SUPPORTED_REPORT_METER_TYPE_ELECTRIC_METER                                 0x01
#define METER_SUPPORTED_REPORT_METER_TYPE_GAS_METER                                      0x02
#define METER_SUPPORTED_REPORT_METER_TYPE_WATER_METER                                    0x03
#define METER_SUPPORTED_REPORT_METER_TYPE_HEATING_METER                                  0x04
#define METER_SUPPORTED_REPORT_METER_TYPE_COOLING_METER                                  0x05
#define METER_SUPPORTED_REPORT_PROPERTIES1_RATE_TYPE_MASK                                0x60
#define METER_SUPPORTED_REPORT_PROPERTIES1_RATE_TYPE_SHIFT                               0x05
#define METER_SUPPORTED_REPORT_RATE_TYPE_RESERVED                                        0x00
#define METER_SUPPORTED_REPORT_RATE_TYPE_IMPORT_ONLY                                     0x01
#define METER_SUPPORTED_REPORT_RATE_TYPE_EXPORT_ONLY                                     0x02
#define METER_SUPPORTED_REPORT_RATE_TYPE_IMPORT_AND_EXPORT                               0x03
#define METER_SUPPORTED_REPORT_PROPERTIES1_METER_RESET_BIT_MASK                          0x80
#define METER_SUPPORTED_REPORT_PROPERTIES2_SCALE_SUPPORTED_0_MASK                        0x7F
#define METER_SUPPORTED_REPORT_PROPERTIES2_M_S_T_BIT_MASK                                0x80

/************************************************************/
/* Meter Get command class structs */                       
/************************************************************/
typedef struct _ZW_METER_GET_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
} ZW_METER_GET_FRAME;

/************************************************************/
/* Meter Get V3 command class structs */                    
/************************************************************/
typedef struct _ZW_METER_GET_V3_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   properties1;                  /* masked byte */
} ZW_METER_GET_V3_FRAME;


/************************************************************/
/* Meter Get V5 command class structs */                    
/************************************************************/
typedef struct _ZW_METER_GET_V6_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   properties1;                  /* masked byte */
    uint8_t   scale2;                       /**/
} ZW_METER_GET_V6_FRAME;

typedef union								ZwMeterGetFrame_u {//For more convenient support, several versions of commands
	ZW_METER_GET_FRAME						v1;
	ZW_METER_GET_V3_FRAME					v3;
	ZW_METER_GET_V6_FRAME					v6;
}											ZwMeterGetFrame_t;

/************************************************************/
/* Meter Reset V2 command class structs */                  
/************************************************************/
typedef struct _ZW_METER_RESET_V2_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
} ZW_METER_RESET_V2_FRAME;

/************************************************************/
/* Meter Reset 1byte V6 command class structs */            
/************************************************************/
typedef struct _ZW_METER_RESET_1BYTE_V6_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   properties1;                  /* masked byte */
    uint8_t   properties2;                  /* masked byte */
    uint8_t   meterValue[];                  
} ZW_METER_RESET_1BYTE_V6_FRAME;

typedef union								ZwMeterResetFrame_u {//For more convenient support, several versions of commands
	ZW_METER_RESET_V2_FRAME					v2;
	ZW_METER_RESET_1BYTE_V6_FRAME			v6;
}											ZwMeterResetFrame_t;

typedef struct								ZwMeterReportV6Frame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									properties1;/* masked byte */
	uint8_t									properties2;/* masked byte */
	uint8_t									meterValue[];
}											ZwMeterReportV6Frame_t;

int zuno_CCMeterHandler(byte channel, const ZUNOCommandCmd_t * cmd, ZUNOCommandPacketReport_t *frame_report);
int zuno_CCMeterReport(byte channel, const ZUNOCommandCmd_t *paket, ZUNOCommandPacket_t *report_paket);

uint8_t __meter_get_scale(const ZwMeterReportV6Frame_t *report);

#define REPORT_METER_TYPE(report_data)						(((ZwMeterReportV6Frame_t *)((ReportAuxData_t *)report_data)->rawReportData)->properties1 & METER_PROPERTIES_TYPE_MASK)
#define REPORT_METER_SIZE(report_data)						(((ZwMeterReportV6Frame_t *)((ReportAuxData_t *)report_data)->rawReportData)->properties2 & METER_PROPERTIES_SIZE_MASK)
#define REPORT_METER_SCALE(report_data)						__meter_get_scale((ZwMeterReportV6Frame_t *)((ReportAuxData_t *)report_data)->rawReportData)
#define REPORT_METER_PRECISION(report_data)					(((ZwMeterReportV6Frame_t *)((ReportAuxData_t *)report_data)->rawReportData)->properties2 >> METER_PROPERTIES_PRECISION_SHIFT)
#define REPORT_METER_VALUE_1B(report_data)					(((ZwMeterReportV6Frame_t *)((ReportAuxData_t *)report_data)->rawReportData)->meterValue[0x0])
#define REPORT_METER_VALUE_2B(report_data)					((uint16_t)(((ZwMeterReportV6Frame_t *)((ReportAuxData_t *)report_data)->rawReportData)->meterValue[0x0] << 0x8) | ((ZwMeterReportV6Frame_t *)((ReportAuxData_t *)report_data)->rawReportData)->meterValue[0x1])
#define REPORT_METER_VALUE_4B(report_data)					((uint32_t)((((ZwMeterReportV6Frame_t *)((ReportAuxData_t *)report_data)->rawReportData)->meterValue[0x0] << 0x18) | (((ZwMeterReportV6Frame_t *)((ReportAuxData_t *)report_data)->rawReportData)->meterValue[0x1] << 0x10) | (((ZwMeterReportV6Frame_t *)((ReportAuxData_t *)report_data)->rawReportData)->meterValue[0x2] << 0x8) | ((ZwMeterReportV6Frame_t *)((ReportAuxData_t *)report_data)->rawReportData)->meterValue[0x3]))
#define REPORT_METER_VALUE(report_data)						zunoFixToFloat(REPORT_METER_SIZE(report_data), REPORT_METER_PRECISION(report_data), &((ZwMeterReportV6Frame_t *)((ReportAuxData_t *)report_data)->rawReportData)->meterValue[0x0])

#endif // __ZWCC_METER_H__