#ifndef ZWCC_DOOOR_LOCK_H
#define ZWCC_DOOOR_LOCK_H

#include "Arduino.h"
#include "ZWSupport.h"

/* Door Lock command class commands */
#define DOOR_LOCK_VERSION                                                                0x04
#define DOOR_LOCK_CONFIGURATION_GET                                                      0x05
#define DOOR_LOCK_CONFIGURATION_REPORT                                                   0x06
#define DOOR_LOCK_CONFIGURATION_SET                                                      0x04
#define DOOR_LOCK_OPERATION_GET                                                          0x02
#define DOOR_LOCK_OPERATION_REPORT                                                       0x03
#define DOOR_LOCK_OPERATION_SET                                                          0x01
#define DOOR_LOCK_CAPABILITIES_GET                                                       0x07
#define DOOR_LOCK_CAPABILITIES_REPORT                                                    0x08


/* Values used for Door Lock Configuration Report command */
#define DOOR_LOCK_CONFIGURATION_REPORT_CONSTANT_OPERATION_V4                             0x01
#define DOOR_LOCK_CONFIGURATION_REPORT_TIMED_OPERATION_V4                                0x02
#define DOOR_LOCK_CONFIGURATION_REPORT_PROPERTIES1_INSIDE_DOOR_HANDLES_STATE_MASK_V4     0x0F
#define DOOR_LOCK_CONFIGURATION_REPORT_PROPERTIES1_OUTSIDE_DOOR_HANDLES_STATE_MASK_V4    0xF0
#define DOOR_LOCK_CONFIGURATION_REPORT_PROPERTIES1_OUTSIDE_DOOR_HANDLES_STATE_SHIFT_V4   0x04
#define DOOR_LOCK_CONFIGURATION_REPORT_PROPERTIES2_TA_BIT_MASK_V4                        0x01
#define DOOR_LOCK_CONFIGURATION_REPORT_PROPERTIES2_BTB_BIT_MASK_V4                       0x02
#define DOOR_LOCK_CONFIGURATION_REPORT_PROPERTIES2_RESERVED1_MASK_V4                     0xFC
#define DOOR_LOCK_CONFIGURATION_REPORT_PROPERTIES2_RESERVED1_SHIFT_V4                    0x02
/* Values used for Door Lock Configuration Set command */
#define DOOR_LOCK_CONFIGURATION_SET_CONSTANT_OPERATION_V4                                0x01
#define DOOR_LOCK_CONFIGURATION_SET_TIMED_OPERATION_V4                                   0x02
#define DOOR_LOCK_CONFIGURATION_SET_PROPERTIES1_INSIDE_DOOR_HANDLES_STATE_MASK_V4        0x0F
#define DOOR_LOCK_CONFIGURATION_SET_PROPERTIES1_OUTSIDE_DOOR_HANDLES_STATE_MASK_V4       0xF0
#define DOOR_LOCK_CONFIGURATION_SET_PROPERTIES1_OUTSIDE_DOOR_HANDLES_STATE_SHIFT_V4      0x04
#define DOOR_LOCK_CONFIGURATION_SET_PROPERTIES2_TA_BIT_MASK_V4                           0x01
#define DOOR_LOCK_CONFIGURATION_SET_PROPERTIES2_BTB_BIT_MASK_V4                          0x02
#define DOOR_LOCK_CONFIGURATION_SET_PROPERTIES2_RESERVED1_MASK_V4                        0xFC
#define DOOR_LOCK_CONFIGURATION_SET_PROPERTIES2_RESERVED1_SHIFT_V4                       0x02
/* Values used for Door Lock Operation Report command */
#define DOOR_LOCK_OPERATION_REPORT_DOOR_UNSECURED_V4                                     0x00
#define DOOR_LOCK_OPERATION_REPORT_DOOR_UNSECURED_WITH_TIMEOUT_V4                        0x01
#define DOOR_LOCK_OPERATION_REPORT_DOOR_UNSECURED_FOR_INSIDE_DOOR_HANDLES_V4             0x10
#define DOOR_LOCK_OPERATION_REPORT_DOOR_UNSECURED_FOR_INSIDE_DOOR_HANDLES_WITH_TIMEOUT_V4 0x11
#define DOOR_LOCK_OPERATION_REPORT_DOOR_UNSECURED_FOR_OUTSIDE_DOOR_HANDLES_V4            0x20
#define DOOR_LOCK_OPERATION_REPORT_DOOR_UNSECURED_FOR_OUTSIDE_DOOR_HANDLES_WITH_TIMEOUT_V4 0x21
#define DOOR_LOCK_OPERATION_REPORT_DOOR_LOCK_STATE_UNKNOWN_V4                            0xFE
#define DOOR_LOCK_OPERATION_REPORT_DOOR_SECURED_V4                                       0xFF
#define DOOR_LOCK_OPERATION_REPORT_PROPERTIES1_INSIDE_DOOR_HANDLES_MODE_MASK_V4          0x0F
#define DOOR_LOCK_OPERATION_REPORT_PROPERTIES1_OUTSIDE_DOOR_HANDLES_MODE_MASK_V4         0xF0
#define DOOR_LOCK_OPERATION_REPORT_PROPERTIES1_OUTSIDE_DOOR_HANDLES_MODE_SHIFT_V4        0x04
#define DOOR_LOCK_OPERATION_REPORT_DOOR_UNSECURED_V4                                     0x00
#define DOOR_LOCK_OPERATION_REPORT_DOOR_UNSECURED_WITH_TIMEOUT_V4                        0x01
#define DOOR_LOCK_OPERATION_REPORT_DOOR_UNSECURED_FOR_INSIDE_DOOR_HANDLES_V4             0x10
#define DOOR_LOCK_OPERATION_REPORT_DOOR_UNSECURED_FOR_INSIDE_DOOR_HANDLES_WITH_TIMEOUT_V4 0x11
#define DOOR_LOCK_OPERATION_REPORT_DOOR_UNSECURED_FOR_OUTSIDE_DOOR_HANDLES_V4            0x20
#define DOOR_LOCK_OPERATION_REPORT_DOOR_UNSECURED_FOR_OUTSIDE_DOOR_HANDLES_WITH_TIMEOUT_V4 0x21
#define DOOR_LOCK_OPERATION_REPORT_DOOR_LOCK_STATE_UNKNOWN_V4                            0xFE
#define DOOR_LOCK_OPERATION_REPORT_DOOR_SECURED_V4                                       0xFF
#define DOOR_LOCK_OPERATION_REPORT_ALREADY_AT_THE_TARGET_VALUE_V4                        0x00
#define DOOR_LOCK_OPERATION_REPORT_UNKNOWN_DURATION_V4                                   0xFE
#define DOOR_LOCK_OPERATION_REPORT_RESERVED_V4                                           0xFF
/* Values used for Door Lock Operation Set command */
#define DOOR_LOCK_OPERATION_SET_DOOR_UNSECURED_V4                                        0x00
#define DOOR_LOCK_OPERATION_SET_DOOR_UNSECURED_WITH_TIMEOUT_V4                           0x01
#define DOOR_LOCK_OPERATION_SET_DOOR_UNSECURED_FOR_INSIDE_DOOR_HANDLES_V4                0x10
#define DOOR_LOCK_OPERATION_SET_DOOR_UNSECURED_FOR_INSIDE_DOOR_HANDLES_WITH_TIMEOUT_V4   0x11
#define DOOR_LOCK_OPERATION_SET_DOOR_UNSECURED_FOR_OUTSIDE_DOOR_HANDLES_V4               0x20
#define DOOR_LOCK_OPERATION_SET_DOOR_UNSECURED_FOR_OUTSIDE_DOOR_HANDLES_WITH_TIMEOUT_V4  0x21
#define DOOR_LOCK_OPERATION_SET_DOOR_LOCK_STATE_UNKNOWN_V4                               0xFE
#define DOOR_LOCK_OPERATION_SET_DOOR_SECURED_V4                                          0xFF
/* Values used for Door Lock Capabilities Report command */
#define DOOR_LOCK_CAPABILITIES_REPORT_PROPERTIES1_SUPPORTED_OPERATION_TYPE_BIT_MASK_LENGTH_MASK_V4 0x1F
#define DOOR_LOCK_CAPABILITIES_REPORT_PROPERTIES1_RESERVED_MASK_V4                       0xE0
#define DOOR_LOCK_CAPABILITIES_REPORT_PROPERTIES1_RESERVED_SHIFT_V4                      0x05
#define DOOR_LOCK_CAPABILITIES_REPORT_PROPERTIES2_SUPPORTED_INSIDE_HANDLE_MODES_BITMASK_MASK_V4 0x0F
#define DOOR_LOCK_CAPABILITIES_REPORT_PROPERTIES2_SUPPORTED_OUTSIDE_HANDLE_MODES_BITMASK_MASK_V4 0xF0
#define DOOR_LOCK_CAPABILITIES_REPORT_PROPERTIES2_SUPPORTED_OUTSIDE_HANDLE_MODES_BITMASK_SHIFT_V4 0x04
#define DOOR_LOCK_CAPABILITIES_REPORT_PROPERTIES3_BTBS_BIT_MASK_V4                       0x01
#define DOOR_LOCK_CAPABILITIES_REPORT_PROPERTIES3_TAS_BIT_MASK_V4                        0x02
#define DOOR_LOCK_CAPABILITIES_REPORT_PROPERTIES3_HRS_BIT_MASK_V4                        0x04
#define DOOR_LOCK_CAPABILITIES_REPORT_PROPERTIES3_ARS_BIT_MASK_V4                        0x08
#define DOOR_LOCK_CAPABILITIES_REPORT_PROPERTIES3_RESERVED_MASK_V4                       0xF0
#define DOOR_LOCK_CAPABILITIES_REPORT_PROPERTIES3_RESERVED_SHIFT_V4                      0x04

/************************************************************/
/* Door Lock Operation Set command class structs */      
/************************************************************/
typedef struct							ZwDoorLockOperationSet_s
{
	uint8_t								cmdClass;/* The command class */
	uint8_t								cmd;/* The command */
	uint8_t								doorLockMode;/**/
}										ZwDoorLockOperationSet_t;//_ZW_DOOR_LOCK_OPERATION_SET_V4_FRAME_

/************************************************************/
/* Door Lock Configuration Report command class structs */
/************************************************************/
typedef struct							ZwDoorLockConfigurationReportV3Frame_s
{
	uint8_t								cmdClass;/* The command class */
	uint8_t								cmd;/* The command */
	uint8_t								operationType;/**/
	uint8_t								properties1;/* masked byte */
	uint8_t								lockTimeoutMinutes;/**/
	uint8_t								lockTimeoutSeconds;/**/
}										ZwDoorLockConfigurationReportV3Frame_t;


typedef struct							ZwDoorLockConfigurationReportV4Frame_s
{
	uint8_t								cmdClass;/* The command class */
	uint8_t								cmd;/* The command */
	uint8_t								operationType;/**/
	uint8_t								properties1;/* masked byte */
	uint8_t								lockTimeoutMinutes;/**/
	uint8_t								lockTimeoutSeconds;/**/
	uint8_t								autoRelockTime1;/* MSB */
	uint8_t								autoRelockTime2;/* LSB */
	uint8_t								holdAndReleaseTime1;/* MSB */
	uint8_t								holdAndReleaseTime2;/* LSB */
	uint8_t								properties2;/* masked byte */
}										ZwDoorLockConfigurationReportV4Frame_t;

typedef union							ZwDoorLockConfigurationReportFrame_u {//For more convenient support, several versions of commands
	ZwDoorLockConfigurationReportV3Frame_t	v3;
	ZwDoorLockConfigurationReportV4Frame_t	v4;
}										ZwDoorLockConfigurationReportFrame_t;

/************************************************************/
/* Door Lock Operation Report command class structs */   
/************************************************************/
typedef struct							ZwDoorLockOperationReportV2Frame_s
{
	uint8_t								cmdClass;/* The command class */
	uint8_t								cmd;/* The command */
	uint8_t								doorLockMode;/**/
	uint8_t								properties1;/* masked byte */
	uint8_t								doorCondition;/**/
	uint8_t								lockTimeoutMinutes;/**/
	uint8_t								lockTimeoutSeconds;/**/
}										ZwDoorLockOperationReportV2Frame_t;

typedef struct							ZwDoorLockOperationReportV4Frame_s
{
	uint8_t								cmdClass;/* The command class */
	uint8_t								cmd;/* The command */
	uint8_t								currentDoorLockMode;/**/
	uint8_t								properties1;/* masked byte */
	uint8_t								doorCondition;/**/
	uint8_t								lockTimeoutMinutes;/**/
	uint8_t								lockTimeoutSeconds;/**/
	uint8_t								targetDoorLockMode;/**/
	uint8_t								duration;/**/
}										ZwDoorLockOperationReportV4Frame_t;

typedef union							ZwDoorLockOperationReportFrame_u {//For more convenient support, several versions of commands
	ZwDoorLockOperationReportV2Frame_t	v2;
	ZwDoorLockOperationReportV4Frame_t	v4;
}										ZwDoorLockOperationReportFrame_t;

/************************************************************/
/* Door Lock Configuration Set command class structs */     
/************************************************************/
typedef struct _ZW_DOOR_LOCK_CONFIGURATION_SET_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   operationType;                /**/
    uint8_t   properties1;                  /* masked byte */
    uint8_t   lockTimeoutMinutes;           /**/
    uint8_t   lockTimeoutSeconds;           /**/
} ZW_DOOR_LOCK_CONFIGURATION_SET_FRAME;

typedef struct _ZW_DOOR_LOCK_CONFIGURATION_SET_V4_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   operationType;                /**/
    uint8_t   properties1;                  /* masked byte */
    uint8_t   lockTimeoutMinutes;           /**/
    uint8_t   lockTimeoutSeconds;           /**/
    uint8_t   autoRelockTime1;              /* MSB */
    uint8_t   autoRelockTime2;              /* LSB */
    uint8_t   holdAndReleaseTime1;          /* MSB */
    uint8_t   holdAndReleaseTime2;          /* LSB */
    uint8_t   properties2;                  /* masked byte */
} ZW_DOOR_LOCK_CONFIGURATION_SET_V4_FRAME;

typedef union							ZwDoorLockConfigurationSetFrame_u {//For more convenient support, several versions of commands
	ZW_DOOR_LOCK_CONFIGURATION_SET_FRAME	v3;
	ZW_DOOR_LOCK_CONFIGURATION_SET_V4_FRAME	v4;
}										ZwDoorLockConfigurationSetFrame_t;

int zuno_CCDoorLockHandler(uint8_t channel, const ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report);
int zuno_CCDoorLockReport(uint8_t channel, ZUNOCommandPacket_t *packet);

void __zunoDoorLockSaveInit(void);
void __zuno_CCDoorLockTimerStop(uint8_t channel);
void __zuno_CCDoorLockGetValues(uint8_t channel, uint8_t *current_value, uint8_t *duration_table_8, uint8_t *target_value);

#endif // ZWCC_DOOOR_LOCK_H