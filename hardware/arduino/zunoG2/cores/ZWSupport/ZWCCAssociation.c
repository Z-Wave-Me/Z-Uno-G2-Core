#include "ZWCCAssociation.h"
#include "./includes/ZWCCAssociation_private.h"

static int _group_id(uint8_t group_id) {
	if (--group_id <= ZUNO_CFG_ASSOCIATION_COUNT)
		return (ZUNO_UNKNOWN_CMD);//We throw off the parsing of the package
	return (ZUNO_COMMAND_BLOCKED);//drop the package
}

static int _assotiation_groupings_report(uint8_t cmd) {
	ZwAssociationGroupingsReportFrame_t		*lp;

	lp = (ZwAssociationGroupingsReportFrame_t *)&CMD_REPLY_CC;
	lp->cmdClass = COMMAND_CLASS_ASSOCIATION;
	lp->cmd = cmd;
	lp->supportedGroupings = ZUNO_CFG_ASSOCIATION_COUNT + 1;//+1 for Lifeline group
	CMD_REPLY_LEN = sizeof(ZwAssociationGroupingsReportFrame_t);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _assotiation_specific_group_report() {
	ZwAssociationSpecificGroupReportFrame_t		*lp;

	lp = (ZwAssociationSpecificGroupReportFrame_t *)&CMD_REPLY_CC;
	lp->cmdClass = COMMAND_CLASS_ASSOCIATION;
	lp->cmd =  ASSOCIATION_SPECIFIC_GROUP_REPORT;
	lp->group = 0;//Does not support, but for everything to work, you need to respond with zero
	CMD_REPLY_LEN = sizeof(ZwAssociationSpecificGroupReportFrame_t);
	return (ZUNO_COMMAND_ANSWERED);
}


int zuno_CCAssociationHandler(ZUNOCommandPacket_t *cmd) {
	int				rs;

	rs = ZUNO_UNKNOWN_CMD;
	switch(ZW_CMD) {
		case ASSOCIATION_SET:
		case ASSOCIATION_REMOVE:
			rs = _group_id(ASSOCIATION_GROUP_ID);
			break ;
		case ASSOCIATION_GET:
			if (_group_id(ASSOCIATION_GROUP_ID) != ZUNO_UNKNOWN_CMD)
				ASSOCIATION_GROUP_ID = 1;//A node that receives an unsupported Grouping Identifier SHOULD return information relating to Grouping Identifier 1.
			break ;
		case ASSOCIATION_GROUPINGS_GET:
			rs = _assotiation_groupings_report(ASSOCIATION_GROUPINGS_REPORT);
			break ;
		case ASSOCIATION_SPECIFIC_GROUP_GET:
			rs = _assotiation_specific_group_report();
			break ;
	}
	return (rs);
}

int zuno_CCMultiAssociationHandler(ZUNOCommandPacket_t *cmd) {
	int				rs;

	rs = ZUNO_UNKNOWN_CMD;
	switch(ZW_CMD) {
		case MULTI_CHANNEL_ASSOCIATION_SET:
		case MULTI_CHANNEL_ASSOCIATION_REMOVE:
			rs = _group_id(ASSOCIATION_GROUP_ID);
			break ;
		case MULTI_CHANNEL_ASSOCIATION_GET:
			if (_group_id(ASSOCIATION_GROUP_ID) != ZUNO_UNKNOWN_CMD)
				ASSOCIATION_GROUP_ID = 1;//A node that receives an unsupported Grouping Identifier SHOULD return information relating to Grouping Identifier 1.
			break ;
		case MULTI_CHANNEL_ASSOCIATION_GROUPINGS_GET:
			rs = _assotiation_groupings_report(MULTI_CHANNEL_ASSOCIATION_GROUPINGS_REPORT);
			break ;
	}
	return (rs);
}


int zuno_CCAssociationGprInfoHandler(ZUNOCommandPacket_t *cmd) {
	int				rs;

	rs = ZUNO_UNKNOWN_CMD;
	switch(ZW_CMD) {
		case ASSOCIATION_GROUP_NAME_GET:
			if (_group_id(ASSOCIATION_GROUP_ID) != ZUNO_UNKNOWN_CMD)
				ASSOCIATION_GROUP_ID = 1;//A node that receives an unsupported Grouping Identifier SHOULD return information relating to Grouping Identifier 1.
			break ;
	}
	return (rs);
}

