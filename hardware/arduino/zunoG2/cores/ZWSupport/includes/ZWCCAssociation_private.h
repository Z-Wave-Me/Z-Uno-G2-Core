#ifndef ZWCC_ASSOCIATION_PRIVATE_H
#define ZWCC_ASSOCIATION_PRIVATE_H

#include "Arduino.h"

#define ASSOCIATION_GROUP_ID				cmd->cmd[2]

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

#endif // ZWCC_ASSOCIATION_PRIVATE_H