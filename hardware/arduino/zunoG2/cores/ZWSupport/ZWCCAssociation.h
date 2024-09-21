#ifndef ZWCC_ASSOCIATION_H
#define ZWCC_ASSOCIATION_H

#include "Arduino.h"
#include "ZWSupport.h"

/* Association command class commands */
#define ASSOCIATION_VERSION                                                              0x03
#define ASSOCIATION_GET                                                                  0x02
#define ASSOCIATION_GROUPINGS_GET                                                        0x05
#define ASSOCIATION_GROUPINGS_REPORT                                                     0x06
#define ASSOCIATION_REMOVE                                                               0x04
#define ASSOCIATION_REPORT                                                               0x03
#define ASSOCIATION_SET                                                                  0x01
#define ASSOCIATION_SPECIFIC_GROUP_GET                                                   0x0B
#define ASSOCIATION_SPECIFIC_GROUP_REPORT                                                0x0C

/* Multi Channel Association command class commands */
#define MULTI_CHANNEL_ASSOCIATION_VERSION                                                0x04
#define MULTI_CHANNEL_ASSOCIATION_GET                                                    0x02
#define MULTI_CHANNEL_ASSOCIATION_GROUPINGS_GET                                          0x05
#define MULTI_CHANNEL_ASSOCIATION_GROUPINGS_REPORT                                       0x06
#define MULTI_CHANNEL_ASSOCIATION_REMOVE                                                 0x04
#define MULTI_CHANNEL_ASSOCIATION_REPORT                                                 0x03
#define MULTI_CHANNEL_ASSOCIATION_SET                                                    0x01

/* Association Grp Info command class commands */
#define ASSOCIATION_GRP_INFO_VERSION                                                     0x03
#define ASSOCIATION_GROUP_NAME_GET                                                       0x01
#define ASSOCIATION_GROUP_NAME_REPORT                                                    0x02
#define ASSOCIATION_GROUP_INFO_GET                                                       0x03
#define ASSOCIATION_GROUP_INFO_REPORT                                                    0x04
#define ASSOCIATION_GROUP_COMMAND_LIST_GET                                               0x05
#define ASSOCIATION_GROUP_COMMAND_LIST_REPORT                                            0x06

int zuno_CCAssociationHandler(const ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report);
int zuno_CCMultiAssociationHandler(const ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report);
int zuno_CCAssociationGprInfoHandler(const ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report);


/* Device Reset Locally command class commands */
#define DEVICE_RESET_LOCALLY_VERSION                                                     0x01
#define DEVICE_RESET_LOCALLY_NOTIFICATION                                                0x01

/* Scene Activation command class commands */
#define SCENE_ACTIVATION_VERSION                                                         0x01
#define SCENE_ACTIVATION_SET                                                             0x01

/************************************************************/
/* Scene Activation Set command class structs */            
/************************************************************/
typedef struct								ZwSceneActivationSetFrame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									sceneId;/**/
	uint8_t									dimmingDuration;/**/
}											ZwSceneActivationSetFrame_t;

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
	ZwAssociationGroupInfoReportVg_t		variantgroup[];/**/
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


/************************************************************/
/* Association Report command class structs */     
/************************************************************/
typedef struct									ZwAssociationReportFrameFake_s
{
	uint8_t										cmdClass;/* The command class */
	uint8_t										cmd;/* The command */
	uint8_t										groupingIdentifier;/**/
	uint8_t										maxNodesSupported;/**/
	uint8_t										reportsToFollow;/**/
}												ZwAssociationReportFrameFake_t;

/************************************************************/
/* Association Set  command class structs */        
/************************************************************/
typedef struct									ZwAssociationSetFrame_s
{
	uint8_t										cmdClass;/* The command class */
	uint8_t										cmd;/* The command */
	uint8_t										groupingIdentifier;/**/
	uint8_t										nodeId[];
}												ZwAssociationSetFrame_t;

typedef struct								ZwAssociationInfoOut_s
{
	uint8_t									profile1;
	uint8_t									profile2;
}											ZwAssociationInfoOut_t;

#endif // ZWCC_ASSOCIATION_H