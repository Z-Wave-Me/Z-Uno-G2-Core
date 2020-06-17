#ifndef ZWCC_DOOOR_LOCK_PRIVATE_H
#define ZWCC_DOOOR_LOCK_PRIVATE_H

#include "Arduino.h"

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
/* Door Lock Operation Set command class structs */      
/************************************************************/
typedef struct							ZwDoorLockOperationSet_s
{
	uint8_t								cmdClass;/* The command class */
	uint8_t								cmd;/* The command */
	uint8_t								doorLockMode;/**/
}										ZwDoorLockOperationSet_t;//_ZW_DOOR_LOCK_OPERATION_SET_V4_FRAME_

#endif // ZWCC_DOOOR_LOCK_PRIVATE_H