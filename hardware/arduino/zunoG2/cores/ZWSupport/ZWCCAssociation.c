#include "ZWCCAssociation.h"
#include "./includes/ZWCCAssociation_private.h"

static char *g_zuno_associations_group_name[ZUNO_MAX_ASSOC_NUMBER_LIMITATION];

static int _group_id(uint8_t groupIndex) {
	if (--groupIndex <= ZUNO_CFG_ASSOCIATION_COUNT)
		return (ZUNO_UNKNOWN_CMD);//We throw off the parsing of the package
	return (ZUNO_COMMAND_BLOCKED);//drop the package
}

static int _assotiation_groupings_report(uint8_t cmdClass, uint8_t cmd) {
	ZwAssociationGroupingsReportFrame_t		*lp;

	lp = (ZwAssociationGroupingsReportFrame_t *)&CMD_REPLY_CC;
	lp->cmdClass = cmdClass;
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
			rs = _assotiation_groupings_report(COMMAND_CLASS_ASSOCIATION, ASSOCIATION_GROUPINGS_REPORT);
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
				ASSOCIATION_GROUP_ID = ZUNO_LIFELINE_GRP;//A node that receives an unsupported Grouping Identifier SHOULD return information relating to Grouping Identifier 1.
			break ;
		case MULTI_CHANNEL_ASSOCIATION_GROUPINGS_GET:
			rs = _assotiation_groupings_report(COMMAND_CLASS_MULTI_CHANNEL_ASSOCIATION, MULTI_CHANNEL_ASSOCIATION_GROUPINGS_REPORT);
			break ;
	}
	return (rs);
}

static int _association_gpr_info_name_report(ZUNOCommandPacket_t *cmd) {
	static char								group_name_default[] = ASSOCIATION_GROUP_NAME_DEFAULT;
	ZwAssociationGroupNameReportFrame_t		*lp;
	uint8_t									groupIndex;
	char									*group_name;
	uint32_t								len;

	groupIndex = ASSOCIATION_GROUP_ID;
	if (_group_id(groupIndex) != ZUNO_UNKNOWN_CMD)
		groupIndex = ZUNO_LIFELINE_GRP;//A node that receives an unsupported Grouping Identifier SHOULD return information relating to Grouping Identifier 1.
	if (groupIndex == ZUNO_LIFELINE_GRP) {
		group_name = (char *)ASSOCIATION_GROUP_NAME_LIFE_LINE;
		len = (sizeof(ASSOCIATION_GROUP_NAME_LIFE_LINE) - 1);
	}
	else if ((group_name = g_zuno_associations_group_name[groupIndex - 2]) != NULL && ((len = strlen(group_name)) < ASSOCIATION_GROUP_NAME_MAX) && len != 0)
		;
	else {
		group_name = &group_name_default[0];
		len = (sizeof(ASSOCIATION_GROUP_NAME_DEFAULT)- 1);
		group_name[len - 1] = groupIndex % 10 + 0x30;
		group_name[len - 2] = groupIndex / 10 + 0x30;
	}
	lp = (ZwAssociationGroupNameReportFrame_t *)&CMD_REPLY_CC;
	lp->cmdClass = COMMAND_CLASS_ASSOCIATION_GRP_INFO;
	lp->cmd = ASSOCIATION_GROUP_NAME_REPORT;
	lp->groupingIdentifier = groupIndex;
	lp->lengthOfName = len;
	memcpy(&lp->name[0], group_name, len);
	CMD_REPLY_LEN = sizeof(ZwAssociationGroupNameReportFrame_t) + len;
	return (ZUNO_COMMAND_ANSWERED);
}

static int _association_gpr_info_profile_report(ZwAssociationGroupInfoGetFrame_t *in) {
	uint8_t									groupIndex;
	uint8_t									groupIndex_end;
	ZwAssociationGroupInfoReportFrame_t		*lp;

	lp = (ZwAssociationGroupInfoReportFrame_t *)&CMD_REPLY_CC;
	lp->cmdClass = COMMAND_CLASS_ASSOCIATION_GRP_INFO;
	lp->cmd = ASSOCIATION_GROUP_INFO_REPORT;
	lp->properties1 = 1;// FIXME Уточнтить что будет ли динамически меняться - скорей сего нет
	lp->variantgroup.mode = 0;
	lp->variantgroup.reserved = 0;
	lp->variantgroup.eventCode1 = 0;
	lp->variantgroup.eventCode2 = 0;
	CMD_REPLY_LEN = sizeof(ZwAssociationGroupInfoReportFrame_t);
	if ((in->properties1 & (1 << 6)) != 0) {
		lp->properties1 |= (1 << 7);//If List Mode is 1, a sending node is advertising the properties of all association groups. The sending node MAY return several Reports.
		groupIndex = ZUNO_LIFELINE_GRP;
		groupIndex_end = ZUNO_CFG_ASSOCIATION_COUNT + 1;//+1 for "Lifeline"
	}
	else {
		groupIndex = in->groupingIdentifier;
		if (_group_id(groupIndex) != ZUNO_UNKNOWN_CMD) {
			groupIndex = ZUNO_LIFELINE_GRP;//A node that receives an unsupported Grouping Identifier SHOULD return information relating to Grouping Identifier 1.
			groupIndex_end = ZUNO_LIFELINE_GRP;
		}
		else
			groupIndex_end = groupIndex;
	}
	while (groupIndex <= groupIndex_end) {
		switch (groupIndex) {
			case 1:
				lp->variantgroup.groupingIdentifier = ZUNO_LIFELINE_GRP;
				lp->variantgroup.profile1 = 0;
				lp->variantgroup.profile2 = 1;
				break;
			default:
				lp->variantgroup.groupingIdentifier = groupIndex;
				lp->variantgroup.profile1 = 0x20;
				lp->variantgroup.profile2 = ZUNO_CFG_ASSOCIATION(groupIndex - 2).type;
				break;
		}
		zunoSendZWPackage(&g_outgoing_packet);
		groupIndex++;
	}
	return (ZUNO_COMMAND_PROCESSED);
}

static int _association_gpr_info_command_report(ZwAssociationGroupCommandListGetFrame_t *in) {
	uint8_t											groupIndex;
	uint8_t											listLength;
	ZwAssociationGroupCommandListReportFrame_t		*lp;

	groupIndex = in->groupingIdentifier;
	if (_group_id(groupIndex) != ZUNO_UNKNOWN_CMD)
		groupIndex = ZUNO_LIFELINE_GRP;//A node that receives an unsupported Grouping Identifier SHOULD return information relating to Grouping Identifier 1.
	lp = (ZwAssociationGroupCommandListReportFrame_t *)&CMD_REPLY_CC;
	lp->cmdClass = COMMAND_CLASS_ASSOCIATION_GRP_INFO;
	lp->cmd = ASSOCIATION_GROUP_COMMAND_LIST_REPORT;
	lp->groupingIdentifier = groupIndex;
	listLength = 2;
	if (groupIndex == ZUNO_LIFELINE_GRP)
	{
		lp->command[0] = COMMAND_CLASS_DEVICE_RESET_LOCALLY;
		lp->command[1] = DEVICE_RESET_LOCALLY_NOTIFICATION;
	}
	else
	{
		switch (ZUNO_CFG_ASSOCIATION(groupIndex - 2).type) {
			case ZUNO_ASSOC_BASIC_SET_NUMBER:
				lp->command[0] = COMMAND_CLASS_BASIC;
				lp->command[1] = BASIC_SET;
				break;
			case ZUNO_ASSOC_BASIC_SET_AND_DIM_NUMBER:
				listLength = 6;
				lp->command[0] = COMMAND_CLASS_BASIC;
				lp->command[1] = BASIC_SET;
				lp->command[2] = COMMAND_CLASS_SWITCH_MULTILEVEL;
				lp->command[3] = SWITCH_MULTILEVEL_START_LEVEL_CHANGE;
				lp->command[4] = COMMAND_CLASS_SWITCH_MULTILEVEL;
				lp->command[5] = SWITCH_MULTILEVEL_STOP_LEVEL_CHANGE;
				break;
			case ZUNO_ASSOC_SCENE_ACTIVATION_NUMBER:
				lp->command[0] = COMMAND_CLASS_SCENE_ACTIVATION;
				lp->command[1] = SCENE_ACTIVATION_SET;
				break;
			case ZUNO_ASSOC_DOORLOCK_CONTROL_NUMBER:
				lp->command[0] = COMMAND_CLASS_DOOR_LOCK;
				lp->command[1] = DOOR_LOCK_OPERATION_SET;
				break;
		}
	}
	lp->listLength = listLength;
	CMD_REPLY_LEN = sizeof(ZwAssociationGroupCommandListReportFrame_t) + listLength;
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCAssociationGprInfoHandler(ZUNOCommandPacket_t *cmd) {
	int				rs;

	rs = ZUNO_UNKNOWN_CMD;
	switch(ZW_CMD) {
		case ASSOCIATION_GROUP_NAME_GET:
			rs = _association_gpr_info_name_report(cmd);
			break ;
		case ASSOCIATION_GROUP_INFO_GET:
			rs = _association_gpr_info_profile_report((ZwAssociationGroupInfoGetFrame_t *)cmd->cmd);
			break ;
		case ASSOCIATION_GROUP_COMMAND_LIST_GET:
			rs = _association_gpr_info_command_report((ZwAssociationGroupCommandListGetFrame_t *)cmd->cmd);
			break ;
	}
	return (rs);
}

void zunoAddAssociation(byte type, uint32_t params) {
	uint8_t						num;

	if (type == 0 || (num = ZUNO_CFG_ASSOCIATION_COUNT) >= ZUNO_MAX_ASSOC_NUMBER_LIMITATION)
		return ;
	ZUNO_CFG_ASSOCIATION_COUNT++;
	ZUNO_CFG_ASSOCIATION(num).type = type;
}

void zunoSetAssociationGroupName(uint8_t groupIndex, char *group_name) {
	if (_group_id(groupIndex) != ZUNO_UNKNOWN_CMD)
		return ;
	g_zuno_associations_group_name[groupIndex - 1] = group_name;
}

static void _send_group(uint8_t groupIndex)
{
	g_outgoing_packet.dst_node = groupIndex + 1;
	g_outgoing_packet.src_zw_channel = 0;
	zunoSendZWPackage(&g_outgoing_packet);
}


void zunoSendToGroupSetValueCommand(uint8_t groupIndex, uint8_t value) {
	ZwBasicSetFrame_t								*lp;

	if (_group_id(groupIndex) != ZUNO_UNKNOWN_CMD)
		return ;
	fillOutgoingReportPacket(0);
	lp = (ZwBasicSetFrame_t *)&CMD_REPLY_CC;
	lp->cmdClass = COMMAND_CLASS_BASIC;
	lp->cmd = BASIC_SET;
	lp->value = value;
	CMD_REPLY_LEN = sizeof(ZwBasicSetFrame_t);
	_send_group(groupIndex);
}

void zunoSendToGroupDimmingCommand(uint8_t groupIndex, uint8_t direction, uint8_t start_stop) {
	ZwSwitchMultilevelStartLevelChangeFrame_t						*lp;

	if (_group_id(groupIndex) != ZUNO_UNKNOWN_CMD)
		return ;
	fillOutgoingReportPacket(0);
	lp = (ZwSwitchMultilevelStartLevelChangeFrame_t *)&CMD_REPLY_CC;
	lp->v1.cmdClass = COMMAND_CLASS_SWITCH_MULTILEVEL;
	if(start_stop != false) {
		lp->v1.cmd = SWITCH_MULTILEVEL_START_LEVEL_CHANGE;
		lp->v1.properties1 = (direction == true) ? 0x60 : 0x20;
		lp->v1.startLevel = 0;
		CMD_REPLY_LEN = sizeof(lp->v1);
	}
	else {
		lp->v1.cmd = SWITCH_MULTILEVEL_STOP_LEVEL_CHANGE;
		CMD_REPLY_LEN = sizeof(ZwSwitchMultilevelStopLevelChangeFrame_t);
	}
	_send_group(groupIndex);
}

void zunoSendToGroupScene(uint8_t groupIndex, uint8_t scene) {
	ZwSceneActivationSetFrame_t								*lp;

	if (_group_id(groupIndex) != ZUNO_UNKNOWN_CMD)
		return ;
	fillOutgoingReportPacket(0);
	lp = (ZwSceneActivationSetFrame_t *)&CMD_REPLY_CC;
	lp->cmdClass = COMMAND_CLASS_SCENE_ACTIVATION;
	lp->cmd = SCENE_ACTIVATION_SET;
	lp->sceneId = scene;
	//lp->dimmingDuration = 0xFF;//Specify dimming duration configured by the Scene Actuator Configuration Set and Scene Controller Configuration Set Command depending on device used.
	//CMD_REPLY_LEN = sizeof(ZwSceneActivationSetFrame_t);
	CMD_REPLY_LEN = 3;
	_send_group(groupIndex);
}

void zunoSendToGroupDoorlockControl(uint8_t groupIndex, uint8_t open_close) {
	ZwDoorLockOperationSet_t								*lp;

	if (_group_id(groupIndex) != ZUNO_UNKNOWN_CMD)
		return ;
	fillOutgoingReportPacket(0);
	lp = (ZwDoorLockOperationSet_t *)&CMD_REPLY_CC;
	lp->cmdClass = COMMAND_CLASS_DOOR_LOCK;
	lp->cmd = DOOR_LOCK_OPERATION_SET;
	lp->doorLockMode = (open_close != false) ? 0x00 : 0xFF;
	CMD_REPLY_LEN = sizeof(ZwDoorLockOperationSet_t);// FIXME
	_send_group(groupIndex);
}