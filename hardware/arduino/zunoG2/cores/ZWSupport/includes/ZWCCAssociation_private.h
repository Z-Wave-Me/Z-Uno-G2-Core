#ifndef ZWCC_ASSOCIATION_PRIVATE_H
#define ZWCC_ASSOCIATION_PRIVATE_H

#include "Arduino.h"
#include "ZWCCBasic.h"
#include "ZWCCMultichannel.h"
#include "ZWCCDoorLock.h"

#define ASSOCIATION_GROUP_ID				cmd->cmd[2]

#define ASSOCIATION_GROUP_INDEX_LIFE_LINE	1

#define ASSOCIATION_GROUP_NAME_LIFE_LINE	"Lifeline"
#define ASSOCIATION_GROUP_NAME_DEFAULT		"User group 00"
#define ASSOCIATION_GROUP_NAME_MAX			42

/* Device Reset Locally command class commands */
#define DEVICE_RESET_LOCALLY_VERSION                                                     0x01
#define DEVICE_RESET_LOCALLY_NOTIFICATION                                                0x01

/* Scene Activation command class commands */
#define SCENE_ACTIVATION_VERSION                                                         0x01
#define SCENE_ACTIVATION_SET                                                             0x01

/************************************************************/
/* Association Groupings Report command class structs */     // is similar /* Multi Channel Association Groupings Report command class structs */
/************************************************************/
typedef struct								ZwAssociationGroupingsReportFrame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									supportedGroupings;/**/
}											ZwAssociationGroupingsReportFrame_t;

/************************************************************/
/* Association Specific Group Report command class structs */
/************************************************************/
typedef struct								ZwAssociationSpecificGroupReportFrame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									group;/**/
}											ZwAssociationSpecificGroupReportFrame_t;

/************************************************************/
/* Association Group Name Report command class structs */
/************************************************************/
typedef struct								ZwAssociationGroupNameReportFrame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									groupingIdentifier;/**/
	uint8_t									lengthOfName;/**/
	uint8_t									name[];//42 byte max
}											ZwAssociationGroupNameReportFrame_t;

/************************************************************/
/* Association Group Info Get command class structs */      
/************************************************************/
typedef struct								ZwAssociationGroupInfoGetFrame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									properties1;/* masked byte */
	uint8_t									groupingIdentifier;/**/
}											ZwAssociationGroupInfoGetFrame_t;

/************************************************************/
/* Association Group Info Report variant group structs */   
/************************************************************/
typedef struct								ZwAssociationGroupInfoReportVg_s
{
	uint8_t									groupingIdentifier;/**/
	uint8_t									mode;/**/
	uint8_t									profile1;/**/
	uint8_t									profile2;/**/
	uint8_t									reserved;/**/
	uint8_t									eventCode1;/* MSB */
	uint8_t									eventCode2;/* LSB */
}											ZwAssociationGroupInfoReportVg_t;

/************************************************************/
/* Association Group Info Report command class structs */
/************************************************************/
typedef struct								ZwAssociationGroupInfoReportFrame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									properties1;/* masked byte */
	ZwAssociationGroupInfoReportVg_t		variantgroup;/**/
}											ZwAssociationGroupInfoReportFrame_t;

/************************************************************/
/* Association Group Command List Get command class structs */
/************************************************************/
typedef struct								ZwAssociationGroupCommandListGetFrame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									properties1;/* masked byte */
	uint8_t									groupingIdentifier;/**/
}											ZwAssociationGroupCommandListGetFrame_t;

/************************************************************/
/* Association Group Command List Report command class structs */
/************************************************************/
typedef struct								ZwAssociationGroupCommandListReportFrame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									groupingIdentifier;/**/
	uint8_t									listLength;/**/
	uint8_t									command[];//(2 or 3 byte) * listLength// (cmdclass - 1 -2 byte plus command 1 byte) * listLength
}											ZwAssociationGroupCommandListReportFrame_t;

#endif // ZWCC_ASSOCIATION_PRIVATE_H