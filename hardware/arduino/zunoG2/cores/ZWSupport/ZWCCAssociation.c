#include "ZWCCAssociation.h"
#include "./includes/ZWCCAssociation_private.h"

static int _group_id(uint8_t group_id)
{
	if (--group_id <= ZUNO_CFG_ASSOCIATION_COUNT)
		return (ZUNO_UNKNOWN_CMD);//We throw off the parsing of the package
	return (ZUNO_COMMAND_BLOCKED);//drop the package
}

static int _assotiation_groupings_report() {
	ZwAssociationGroupingsReportFrame_t		*lp;

	lp = (ZwAssociationGroupingsReportFrame_t *)&CMD_REPLY_CC;
	lp->cmdClass = COMMAND_CLASS_ASSOCIATION;
	lp->cmd =  ASSOCIATION_GROUPINGS_REPORT;
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
		case ASSOCIATION_GET:// FIXME В этом случае если не поддерживает такой канал о 1 певом нужно возратить
		case ASSOCIATION_REMOVE:
			rs = _group_id(ASSOCIATION_GROUP_ID);
			break ;
		case ASSOCIATION_GROUPINGS_GET:
			rs = _assotiation_groupings_report();
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

	}
	return (rs);
}


int zuno_CCAssociationGprInfoHandler(ZUNOCommandPacket_t *cmd) {
	int				rs;

	rs = ZUNO_UNKNOWN_CMD;
	switch(ZW_CMD) {

	}
	return (rs);
}

