#ifndef ZWCC_METER_TBL_H
#define ZWCC_METER_TBL_H

#include "ZWSupport.h"
#include "ZWCCTimerParametrs.h"

/* Meter Tbl Monitor command class commands */
#define METER_TBL_MONITOR_VERSION                                                        0x03
#define METER_TBL_STATUS_REPORT                                                          0x0B
#define METER_TBL_STATUS_DATE_GET                                                        0x0A
#define METER_TBL_STATUS_DEPTH_GET                                                       0x09
#define METER_TBL_STATUS_SUPPORTED_GET                                                   0x07
#define METER_TBL_STATUS_SUPPORTED_REPORT                                                0x08
#define METER_TBL_CURRENT_DATA_GET                                                       0x0C
#define METER_TBL_CURRENT_DATA_REPORT                                                    0x0D
#define METER_TBL_HISTORICAL_DATA_GET                                                    0x0E
#define METER_TBL_HISTORICAL_DATA_REPORT                                                 0x0F
#define METER_TBL_REPORT                                                                 0x06
#define METER_TBL_TABLE_CAPABILITY_GET                                                   0x05
#define METER_TBL_TABLE_ID_GET                                                           0x03
#define METER_TBL_TABLE_ID_REPORT                                                        0x04
#define METER_TBL_TABLE_POINT_ADM_NO_GET                                                 0x01
#define METER_TBL_TABLE_POINT_ADM_NO_REPORT                                              0x02
/* Values used for Meter Tbl Current Data Report command */
#define METER_TBL_CURRENT_DATA_REPORT_PROPERTIES1_RATE_TYPE_MASK                         0x03
#define METER_TBL_CURRENT_DATA_REPORT_PROPERTIES1_RESERVED_MASK                          0x7C
#define METER_TBL_CURRENT_DATA_REPORT_PROPERTIES1_RESERVED_SHIFT                         0x02
#define METER_TBL_CURRENT_DATA_REPORT_PROPERTIES1_OPERATING_STATUS_INDICATION_BIT_MASK    0x80
/* Values used for Meter Tbl Historical Data Report command */
#define METER_TBL_HISTORICAL_DATA_REPORT_PROPERTIES1_RATE_TYPE_MASK                      0x03
#define METER_TBL_HISTORICAL_DATA_REPORT_PROPERTIES1_RESERVED_MASK                       0x7C
#define METER_TBL_HISTORICAL_DATA_REPORT_PROPERTIES1_RESERVED_SHIFT                      0x02
#define METER_TBL_HISTORICAL_DATA_REPORT_PROPERTIES1_OPERATING_STATUS_INDICATION_BIT_MASK    0x80
/* Values used for Meter Tbl Report command */
#define METER_TBL_REPORT_PROPERTIES1_RATE_TYPE_MASK                                      0xC0
#define METER_TBL_REPORT_PAY_METER_RESERVED                                              0x00
#define METER_TBL_REPORT_PAY_METER_CREDITMETER                                           0x01
#define METER_TBL_REPORT_PAY_METER_PREPAYMENT_METER                                      0x02
#define METER_TBL_REPORT_PAY_METER_PREPAYMENT_METER_DEBT                                 0x03
#define METER_TBL_REPORT_PROPERTIES2_RESERVED_MASK                                       0xF0
#define METER_TBL_REPORT_PROPERTIES2_RESERVED_SHIFT                                      0x04
/* Values used for Meter Tbl Table Id Report command */
#define METER_TBL_TABLE_ID_REPORT_PROPERTIES1_NUMBER_OF_CHARACTERS_MASK                  0x1F
#define METER_TBL_TABLE_ID_REPORT_PROPERTIES1_RESERVED_MASK                              0xE0
#define METER_TBL_TABLE_ID_REPORT_PROPERTIES1_RESERVED_SHIFT                             0x05
/* Values used for Meter Tbl Table Point Adm No Report command */
#define METER_TBL_TABLE_POINT_ADM_NO_REPORT_PROPERTIES1_NUMBER_OF_CHARACTERS_MASK        0x1F
#define METER_TBL_TABLE_POINT_ADM_NO_REPORT_PROPERTIES1_RESERVED_MASK                    0xE0
#define METER_TBL_TABLE_POINT_ADM_NO_REPORT_PROPERTIES1_RESERVED_SHIFT                   0x05

/************************************************************/
/* Meter Tbl Status Supported Report command class structs */
/************************************************************/
typedef struct												ZwMeterTblSupportedFrame_s
{
	uint8_t													cmdClass;                     /* The command class */
	uint8_t													cmd;                          /* The command */
	uint8_t													supportedOperatingStatus1;/* MSB */
	uint8_t													supportedOperatingStatus2;
	uint8_t													supportedOperatingStatus3;/* LSB */
	uint8_t													statusEventLogDepth;/**/
}															ZwMeterTblSupportedFrame_t;

/************************************************************/
/* Meter Tbl Table Point Adm No Report command class structs */
/************************************************************/
typedef struct												ZwMeterTblPointAdmNoReportFrame_s
{
	uint8_t													cmdClass;/* The command class */
	uint8_t													cmd;/* The command */
	uint8_t													properties1;/* masked byte */
	uint8_t													meterPointAdmNumberCharacter[];/* MSB to LSB */
}															ZwMeterTblPointAdmNoReportFrame_t;

/************************************************************/
/* Meter Tbl Table Id Report command class structs */
/************************************************************/
typedef struct												ZwMeterTblTableIdReportFrame_s
{
	uint8_t													cmdClass;/* The command class */
	uint8_t													cmd;/* The command */
	uint8_t													properties1;/* masked byte */
	uint8_t													meterIdCharacter[];/* MSB to LSB */
}															ZwMeterTblTableIdReportFrame_t;

/************************************************************/
/* Meter Tbl Report command class structs */             
/************************************************************/
typedef struct												ZwMeterTblReportFrame_s
{
	uint8_t													cmdClass;/* The command class */
	uint8_t													cmd;/* The command */
	uint8_t													properties1;/* masked byte */
	uint8_t													properties2;/* masked byte */
	uint8_t													datasetSupported[3];/* MSB to LSB */
	uint8_t													datasetHistorySupported[3];/* MSB to LSB */
	uint8_t													dataHistorySupported[3];/* MSB to LSB */
}															ZwMeterTblReportFrame_t;

/************************************************************/
/* Meter Tbl Current Data Get command class structs */   
/************************************************************/
typedef struct												ZwMeterTblCurrentDataGetFrame_s
{
	uint8_t													cmdClass;/* The command class */
	uint8_t													cmd;/* The command */
	uint8_t													datasetRequested[3];/* MSB to LSB */
}															ZwMeterTblCurrentDataGetFrame_t;

/************************************************************/
/* Meter Tbl Current Data Report command class structs */
/************************************************************/
typedef struct												ZwMeterTblCurrentDataReportFrame_s
{
	uint8_t													cmdClass;/* The command class */
	uint8_t													cmd;/* The command */
	uint8_t													reportsToFollow;/**/
	uint8_t													properties1;/* masked byte */
	uint8_t													dataset[3];/* MSB to LSB */
	ZwTimerParametrs_t										time;
	uint8_t													properties2;/* masked byte */
	uint8_t													currentValue[4];/* MSB to LSB */
}															ZwMeterTblCurrentDataReportFrame_t;

/************************************************************/
/* Meter Tbl Historical Data Get command class structs */
/************************************************************/
typedef struct												ZwMeterTblHistoricalDataGet_s
{
	uint8_t													cmdClass;/* The command class */
	uint8_t													cmd;/* The command */
	uint8_t													maximumReports;/**/
	uint8_t													historicalDatasetRequested[3];/* MSB to LSB */
	ZwTimerParametrs_t										start_time;
	ZwTimerParametrs_t										stop_time;
}															ZwMeterTblHistoricalDataGet_t;

/************************************************************/
/* Meter Tbl Historical Data Report 1byte V3 command class structs */
/************************************************************/
typedef struct												ZwMeterTblHistoricalDataReport_s
{
	uint8_t													cmdClass;/* The command class */
	uint8_t													cmd;/* The command */
	uint8_t													reportsToFollow;/**/
	uint8_t													properties1;/* masked byte */
	uint8_t													dataset[3];/* MSB to LSB */
	ZwTimerParametrs_t										time;
	uint8_t													properties2;/* masked byte */
	uint8_t													historicalValue[4];/* MSB to LSB */
}															ZwMeterTblHistoricalDataReport_t;

int zuno_CCMeterTblMonitorHandler(byte channel, ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report);

#endif // ZWCC_METER_TBL_H