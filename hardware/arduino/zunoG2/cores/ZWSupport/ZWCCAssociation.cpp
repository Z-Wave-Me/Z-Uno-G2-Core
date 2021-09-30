#include "Arduino.h"
#include "ZWCCBasic.h"
#include "ZWCCSwitchMultilevel.h"
#include "ZWCCDoorLock.h"
#include "ZWCCAssociation.h"
#include "ZWCCNotification.h"
#include "ZWCCMeter.h"
#include "ZWCCSensorMultilevel.h"
#include "ZWCCSwitchColor.h"
#include "ZWCCThermostat.h"
#include "ZWCCBattery.h"
#include "ZWCCMeterTbl.h"

#define ASSOCIATION_GROUP_ID				cmd->cmd[2]
#define ASSOCIATION_GROUP_ID_EX(x)			x->cmd[2]

#define ASSOCIATION_GROUP_NAME_LIFE_LINE	"Lifeline"
#define ASSOCIATION_GROUP_NAME_DEFAULT		"User group 00"
#define ASSOCIATION_GROUP_NAME_MAX			42

static int _group_id(uint8_t groupIndex) {
	if (--groupIndex <= ZUNO_CFG_ASSOCIATION_COUNT)
		return (ZUNO_UNKNOWN_CMD);//We throw off the parsing of the package
	return (ZUNO_COMMAND_BLOCKED);//drop the package
}

static int _assotiation_groupings_report(ZUNOCommandPacket_t *packet) {
	ZwAssociationGroupingsReportFrame_t		*lp;
	size_t									supportedGroupings;

	lp = (ZwAssociationGroupingsReportFrame_t *)&CMD_REPLY_CC;
	// lp->cmdClass = cmdClass; set in - fillOutgoingPacket
	// lp->cmd = cmd; set in - fillOutgoingPacket
	supportedGroupings = 1;//+1 for Lifeline group
	if (packet->dst_zw_channel == 0)
		supportedGroupings = supportedGroupings + ZUNO_CFG_ASSOCIATION_COUNT;
	lp->supportedGroupings = supportedGroupings;
	CMD_REPLY_LEN = sizeof(ZwAssociationGroupingsReportFrame_t);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _assotiation_specific_group_report() {
	ZwAssociationSpecificGroupReportFrame_t		*lp;

	lp = (ZwAssociationSpecificGroupReportFrame_t *)&CMD_REPLY_CC;
	// lp->cmdClass = COMMAND_CLASS_ASSOCIATION; set in - fillOutgoingPacket
	// lp->cmd =  ASSOCIATION_SPECIFIC_GROUP_REPORT; set in - fillOutgoingPacket
	lp->group = 0;//Does not support, but for everything to work, you need to respond with zero
	CMD_REPLY_LEN = sizeof(ZwAssociationSpecificGroupReportFrame_t);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _assotiation_get(ZUNOCommandPacket_t *packet) {
	ZwAssociationReportFrameFake_t				*report;

	if (packet->dst_zw_channel != 0) {
		report = (ZwAssociationReportFrameFake_t *)&CMD_REPLY_CC;
		// report->cmdClass = cmdClass; set in - fillOutgoingPacket
		// report->cmd =  cmd; set in - fillOutgoingPacket
		report->groupingIdentifier = 1;
		report->maxNodesSupported = 0;
		report->reportsToFollow = 0;
		CMD_REPLY_LEN = sizeof(ZwAssociationReportFrameFake_t);
		return (ZUNO_COMMAND_ANSWERED);
	}
	if (_group_id(ASSOCIATION_GROUP_ID_EX(packet)) != ZUNO_UNKNOWN_CMD)
		ASSOCIATION_GROUP_ID_EX(packet) = ZUNO_LIFELINE_GRP;//A node that receives an unsupported Grouping Identifier SHOULD return information relating to Grouping Identifier 1.
	return (ZUNO_UNKNOWN_CMD);
}

int zuno_CCAssociationHandler(ZUNOCommandPacket_t *cmd) {
	int				rs;

	switch(ZW_CMD) {
		case ASSOCIATION_SET:
		case ASSOCIATION_REMOVE:
			rs = _group_id(ASSOCIATION_GROUP_ID);
			break ;
		case ASSOCIATION_GET:
			rs = _assotiation_get(cmd);
			break ;
		case ASSOCIATION_GROUPINGS_GET:
			rs = _assotiation_groupings_report(cmd);
			break ;
		case ASSOCIATION_SPECIFIC_GROUP_GET:
			rs = _assotiation_specific_group_report();
			break ;
		default:
			rs = ZUNO_UNKNOWN_CMD;
			break ;
	}
	return (rs);
}

int zuno_CCMultiAssociationHandler(ZUNOCommandPacket_t *cmd) {
	int				rs;

	switch(ZW_CMD) {
		case MULTI_CHANNEL_ASSOCIATION_SET:
		case MULTI_CHANNEL_ASSOCIATION_REMOVE:
			rs = _group_id(ASSOCIATION_GROUP_ID);
			break ;
		case MULTI_CHANNEL_ASSOCIATION_GET:
			rs = _assotiation_get(cmd);
			break ;
		case MULTI_CHANNEL_ASSOCIATION_GROUPINGS_GET:
			rs = _assotiation_groupings_report(cmd);
			break ;
		default:
			rs = ZUNO_UNKNOWN_CMD;
			break ;
	}
	return (rs);
}

const char *zunoAssociationGroupName(uint8_t groupIndex) __attribute__ ((weak));
const char *zunoAssociationGroupName(uint8_t groupIndex) {
	(void)groupIndex;
	return (NULL);
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
	else if ((group_name = (char *)zunoAssociationGroupName(groupIndex - 1)) != NULL && ((len = strlen(group_name)) < ASSOCIATION_GROUP_NAME_MAX) && len != 0)
		;
	else {
		group_name = &group_name_default[0];
		len = (sizeof(ASSOCIATION_GROUP_NAME_DEFAULT)- 1);
		group_name[len - 1] = groupIndex % 10 + 0x30;
		group_name[len - 2] = groupIndex / 10 + 0x30;
	}
	lp = (ZwAssociationGroupNameReportFrame_t *)&CMD_REPLY_CC;
	// lp->cmdClass = COMMAND_CLASS_ASSOCIATION_GRP_INFO; set in - fillOutgoingPacket
	// lp->cmd = ASSOCIATION_GROUP_NAME_REPORT; set in - fillOutgoingPacket
	lp->groupingIdentifier = groupIndex;
	lp->lengthOfName = len;
	memcpy(&lp->name[0], group_name, len);
	CMD_REPLY_LEN = sizeof(ZwAssociationGroupNameReportFrame_t) + len;
	return (ZUNO_COMMAND_ANSWERED);
}

static int _association_gpr_info_profile_report(ZUNOCommandPacket_t *packet, ZwAssociationGroupInfoGetFrame_t *in) {
	uint8_t									groupIndex;
	uint8_t									groupIndex_end;
	ZwAssociationGroupInfoReportFrame_t		*lp;

	lp = (ZwAssociationGroupInfoReportFrame_t *)&CMD_REPLY_CC;
	// lp->cmdClass = COMMAND_CLASS_ASSOCIATION_GRP_INFO; set in - fillOutgoingPacket
	// lp->cmd = ASSOCIATION_GROUP_INFO_REPORT; set in - fillOutgoingPacket
	lp->properties1 = 1;
	lp->variantgroup.mode = 0;
	lp->variantgroup.reserved = 0;
	lp->variantgroup.eventCode1 = 0;
	lp->variantgroup.eventCode2 = 0;
	CMD_REPLY_LEN = sizeof(ZwAssociationGroupInfoReportFrame_t);
	if ((in->properties1 & (1 << 6)) != 0) {
		lp->properties1 |= (1 << 7);//If List Mode is 1, a sending node is advertising the properties of all association groups. The sending node MAY return several Reports.
		groupIndex = ZUNO_LIFELINE_GRP;
		groupIndex_end = ZUNO_LIFELINE_GRP;//+1 for "Lifeline"
		if (packet->dst_zw_channel == 0)
			groupIndex_end = groupIndex_end + ZUNO_CFG_ASSOCIATION_COUNT;
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
				break ;
			default:
				lp->variantgroup.groupingIdentifier = groupIndex;
				lp->variantgroup.profile1 = 0x20;
				lp->variantgroup.profile2 = ZUNO_CFG_ASSOCIATION(groupIndex - 2).type;
				break ;
		}
		zunoSendZWPackage(&g_outgoing_main_packet);
		groupIndex++;
	}
	return (ZUNO_COMMAND_PROCESSED);
}

static uint8_t *_find_report(size_t cmdClass, uint8_t *command) {
	size_t				cmd;

	switch (cmdClass) {
		#ifdef WITH_CC_BATTERY
		case COMMAND_CLASS_BATTERY:
			cmd = BATTERY_REPORT;
			break ;
		#endif
		#ifdef WITH_CC_BASIC
		case COMMAND_CLASS_BASIC:
			cmd = BASIC_REPORT;
			break ;
		#endif
		#ifdef WITH_CC_SWITCH_BINARY
		case COMMAND_CLASS_SWITCH_BINARY:
			cmd = SWITCH_BINARY_REPORT;
			break ;
		#endif
		#ifdef WITH_CC_NOTIFICATION
		case COMMAND_CLASS_NOTIFICATION:
			cmd = NOTIFICATION_REPORT;
			break ;
		#endif
		#ifdef WITH_CC_SWITCH_MULTILEVEL
		case COMMAND_CLASS_SWITCH_MULTILEVEL:
			cmd = SWITCH_MULTILEVEL_REPORT;
			break ;
		#endif
		#ifdef WITH_CC_METER
		case COMMAND_CLASS_METER:
			cmd = METER_REPORT;
			break ;
		#endif
		#ifdef WITH_CC_SENSOR_MULTILEVEL
		case COMMAND_CLASS_SENSOR_MULTILEVEL:
			cmd = SENSOR_MULTILEVEL_REPORT;
			break ;
		#endif
		#ifdef WITH_CC_SWITCH_COLOR
		case COMMAND_CLASS_SWITCH_COLOR:
			cmd = SWITCH_COLOR_REPORT;
			break ;
		#endif
		#ifdef WITH_CC_THERMOSTAT_MODE
		case COMMAND_CLASS_THERMOSTAT_MODE:
			cmd = THERMOSTAT_MODE_REPORT;
			break ;
		#endif
		#ifdef WITH_CC_THERMOSTAT_SETPOINT
		case COMMAND_CLASS_THERMOSTAT_SETPOINT:
			cmd = THERMOSTAT_SETPOINT_REPORT;
			break ;
		#endif
		#ifdef WITH_CC_METER_TBL_MONITOR
		case COMMAND_CLASS_METER_TBL_MONITOR:
			cmd = METER_TBL_REPORT;
			break ;
		#endif
		default:
			return (command);
			break ;
	}
	command[0] = cmdClass;
	command[1] = cmd;
	return (command + 2);
}

static size_t _testCmdClassReplay(uint8_t *b, uint8_t *e, size_t cc) {
	while (b < e) {
		if (b[0] == cc)
			return (true);
		b = b + 2;
	}
	return (false);
}

static int _association_gpr_info_command_report(ZwAssociationGroupCommandListGetFrame_t *in, ZUNOCommandPacket_t *packet) {
	uint8_t											groupIndex;
	uint8_t											listLength;
	ZwAssociationGroupCommandListReportFrame_t		*lp;
	uint8_t											*command;
	uint8_t											*command_save;
	size_t											i;
	size_t											max;
	size_t											i_all;
	size_t											max_all;
	size_t											cc;
	size_t											dst_zw_channel;
	size_t											zw_channel;
	const ZUNOChannelCCS_t							*ccs;

	groupIndex = in->groupingIdentifier;
	if (_group_id(groupIndex) != ZUNO_UNKNOWN_CMD)
		groupIndex = ZUNO_LIFELINE_GRP;//A node that receives an unsupported Grouping Identifier SHOULD return information relating to Grouping Identifier 1.
	lp = (ZwAssociationGroupCommandListReportFrame_t *)&CMD_REPLY_CC;
	// lp->cmdClass = COMMAND_CLASS_ASSOCIATION_GRP_INFO; set in - fillOutgoingPacket
	// lp->cmd = ASSOCIATION_GROUP_COMMAND_LIST_REPORT; set in - fillOutgoingPacket
	lp->groupingIdentifier = groupIndex;
	command = &lp->command[0];
	if (groupIndex == ZUNO_LIFELINE_GRP) {//0x2503380371053105
		if ((dst_zw_channel = packet->dst_zw_channel) == 0) {
			command[0] = COMMAND_CLASS_DEVICE_RESET_LOCALLY;
			command[1] = DEVICE_RESET_LOCALLY_NOTIFICATION;
			command = command + 2;
			command_save = command;
			i_all = 1;
			max_all = ZUNO_CFG_CHANNEL_COUNT;
			while (i_all <= max_all) {
				zw_channel = ZUNO_CFG_CHANNEL(i_all - 1).zw_channel;
				if (zw_channel == 0x0 || (zw_channel & ZWAVE_CHANNEL_MAPPED_BIT) != 0x0)
				{
					ccs = &ZUNO_CC_TYPES[ZUNO_CFG_CHANNEL(i_all - 1).type - 1];
					i = 0;
					max = ccs->num_ccs;
					while (i < max) {
						cc = ccs->ccs[i++].cc;
						if (_testCmdClassReplay(command_save, command, cc) == false)
							command = _find_report(cc, command);
					}
				}
				i_all++;
			}
		}
		else {
			ccs = &ZUNO_CC_TYPES[ZUNO_CFG_CHANNEL(dst_zw_channel - 1).type - 1];
			i = 0;
			max = ccs->num_ccs;
			while (i < max)
				command = _find_report(ccs->ccs[i++].cc, command);
		}
	}
	else
	{
		switch (ZUNO_CFG_ASSOCIATION(groupIndex - 2).type) {
			case ZUNO_ASSOC_BASIC_SET_NUMBER:
				command[0] = COMMAND_CLASS_BASIC;
				command[1] = BASIC_SET;
				command = command + 2;
				break ;
			case ZUNO_ASSOC_BASIC_SET_AND_DIM_NUMBER:
				command[0] = COMMAND_CLASS_BASIC;
				command[1] = BASIC_SET;
				command[2] = COMMAND_CLASS_SWITCH_MULTILEVEL;
				command[3] = SWITCH_MULTILEVEL_START_LEVEL_CHANGE;
				command[4] = COMMAND_CLASS_SWITCH_MULTILEVEL;
				command[5] = SWITCH_MULTILEVEL_STOP_LEVEL_CHANGE;
				command = command + 6;
				break ;
			case ZUNO_ASSOC_SCENE_ACTIVATION_NUMBER:
				command[0] = COMMAND_CLASS_SCENE_ACTIVATION;
				command[1] = SCENE_ACTIVATION_SET;
				command = command + 2;
				break ;
			case ZUNO_ASSOC_DOORLOCK_CONTROL_NUMBER:
				command[0] = COMMAND_CLASS_DOOR_LOCK;
				command[1] = DOOR_LOCK_OPERATION_SET;
				command = command + 2;
				break ;
		}
	}
	listLength = command - &lp->command[0];
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
			rs = _association_gpr_info_profile_report(cmd, (ZwAssociationGroupInfoGetFrame_t *)cmd->cmd);
			break ;
		case ASSOCIATION_GROUP_COMMAND_LIST_GET:
			rs = _association_gpr_info_command_report((ZwAssociationGroupCommandListGetFrame_t *)cmd->cmd, cmd);
			break ;
	}
	return (rs);
}

void zunoAddAssociation(byte type, uint32_t params) {
	uint8_t						num;

	if (type == 0 || (num = ZUNO_CFG_ASSOCIATION_COUNT) >= ZUNO_MAX_ASSOC_NUMBER)
		return ;
	ZUNO_CFG_ASSOCIATION_COUNT++;
	ZUNO_CFG_ASSOCIATION(num).type = type;
	(void)params;
}

static void _send_group(uint8_t groupIndex)
{
	g_outgoing_report_packet.dst_node = groupIndex + 1;
	g_outgoing_report_packet.src_zw_channel = 0;
	zunoSendZWPackage(&g_outgoing_report_packet);
}


void zunoSendToGroupSetValueCommand(uint8_t groupIndex, uint8_t value) {
	ZwBasicSetFrame_t								*lp;

	if (_group_id(groupIndex) != ZUNO_UNKNOWN_CMD)
		return ;
	fillOutgoingReportPacket(0);
	lp = (ZwBasicSetFrame_t *)&CMD_REPORT_CC;
	lp->cmdClass = COMMAND_CLASS_BASIC;
	lp->cmd = BASIC_SET;
	lp->value = value;
	CMD_REPORT_LEN = sizeof(ZwBasicSetFrame_t);
	_send_group(groupIndex);
}

void zunoSendToGroupDimmingCommand(uint8_t groupIndex, uint8_t direction, uint8_t start_stop) {
	ZwSwitchMultilevelStartLevelChangeFrame_t						*lp;

	if (_group_id(groupIndex) != ZUNO_UNKNOWN_CMD)
		return ;
	fillOutgoingReportPacket(0);
	lp = (ZwSwitchMultilevelStartLevelChangeFrame_t *)&CMD_REPORT_CC;
	lp->v1.cmdClass = COMMAND_CLASS_SWITCH_MULTILEVEL;
	if(start_stop != false) {
		lp->v1.cmd = SWITCH_MULTILEVEL_START_LEVEL_CHANGE;
		lp->v1.properties1 = (direction == true) ? 0x60 : 0x20;
		lp->v1.startLevel = 0;
		CMD_REPORT_LEN = sizeof(lp->v1);
	}
	else {
		lp->v1.cmd = SWITCH_MULTILEVEL_STOP_LEVEL_CHANGE;
		CMD_REPORT_LEN = sizeof(ZwSwitchMultilevelStopLevelChangeFrame_t);
	}
	_send_group(groupIndex);
}

void zunoSendToGroupScene(uint8_t groupIndex, uint8_t scene) {
	ZwSceneActivationSetFrame_t								*lp;

	if (_group_id(groupIndex) != ZUNO_UNKNOWN_CMD)
		return ;
	fillOutgoingReportPacket(0);
	lp = (ZwSceneActivationSetFrame_t *)&CMD_REPORT_CC;
	lp->cmdClass = COMMAND_CLASS_SCENE_ACTIVATION;
	lp->cmd = SCENE_ACTIVATION_SET;
	lp->sceneId = scene;
	//lp->dimmingDuration = 0xFF;//Specify dimming duration configured by the Scene Actuator Configuration Set and Scene Controller Configuration Set Command depending on device used.
	//CMD_REPORT_LEN = sizeof(ZwSceneActivationSetFrame_t);
	CMD_REPORT_LEN = 3;
	_send_group(groupIndex);
}

void zunoSendToGroupDoorlockControl(uint8_t groupIndex, uint8_t open_close) {
	ZwDoorLockOperationSet_t								*lp;

	if (_group_id(groupIndex) != ZUNO_UNKNOWN_CMD)
		return ;
	fillOutgoingReportPacket(0);
	lp = (ZwDoorLockOperationSet_t *)&CMD_REPORT_CC;
	lp->cmdClass = COMMAND_CLASS_DOOR_LOCK;
	lp->cmd = DOOR_LOCK_OPERATION_SET;
	lp->doorLockMode = (open_close != false) ? 0x00 : 0xFF;
	CMD_REPORT_LEN = sizeof(ZwDoorLockOperationSet_t);// FIXME
	_send_group(groupIndex);
}