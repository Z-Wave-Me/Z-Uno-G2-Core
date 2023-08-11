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
#include "ZWCCSoundSwitch.h"
#include "ZWCCCentralScene.h"
#include "CommandQueue.h"
#include "Debug.h"
#include "ZWCCWindowCovering.h"

#define ASSOCIATION_GROUP_ID				cmd->cmd[2]
#define ASSOCIATION_GROUP_ID_EX(x)			x->cmd[2]

#define ASSOCIATION_GROUP_NAME_LIFE_LINE	"Lifeline"
#define ASSOCIATION_GROUP_NAME_DEFAULT		"User group 00"
#define ASSOCIATION_GROUP_NAME_MAX			42

static int _group_id_rm(uint8_t groupIndex) {
	if (groupIndex > (ZUNO_CFG_ASSOCIATION_COUNT+1)) // 
		return (ZUNO_COMMAND_BLOCKED_FAILL);// drop the package
	// 0 is the right index for remove command
	return (ZUNO_UNKNOWN_CMD); //We throw off the parsing of the package
}
static int _group_id(uint8_t groupIndex) {
	if( groupIndex == 0){
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	}
	groupIndex--;
	if (groupIndex <= ZUNO_CFG_ASSOCIATION_COUNT)
		return (ZUNO_UNKNOWN_CMD);//We throw off the parsing of the package
	return (ZUNO_COMMAND_BLOCKED_FAILL);//drop the package
}

static int _assotiation_groupings_report(ZUNOCommandPacket_t *packet, ZUNOCommandPacketReport_t *frame_report) {
	ZwAssociationGroupingsReportFrame_t		*lp;
	size_t									supportedGroupings;

	lp = (ZwAssociationGroupingsReportFrame_t *)frame_report->packet.cmd;
	// lp->cmdClass = cmdClass; set in - fillOutgoingPacket
	// lp->cmd = cmd; set in - fillOutgoingPacket
	supportedGroupings = 1;//+1 for Lifeline group
	if (packet->dst_zw_channel == 0)
		supportedGroupings = supportedGroupings + ZUNO_CFG_ASSOCIATION_COUNT;
	lp->supportedGroupings = supportedGroupings;
	frame_report->packet.len = sizeof(ZwAssociationGroupingsReportFrame_t);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _assotiation_specific_group_report(ZUNOCommandPacketReport_t *frame_report) {
	ZwAssociationSpecificGroupReportFrame_t		*lp;

	lp = (ZwAssociationSpecificGroupReportFrame_t *)frame_report->packet.cmd;
	// lp->cmdClass = COMMAND_CLASS_ASSOCIATION; set in - fillOutgoingPacket
	// lp->cmd =  ASSOCIATION_SPECIFIC_GROUP_REPORT; set in - fillOutgoingPacket
	lp->group = 0;//Does not support, but for everything to work, you need to respond with zero
	frame_report->packet.len = sizeof(ZwAssociationSpecificGroupReportFrame_t);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _assotiation_get(ZUNOCommandPacket_t *packet, ZUNOCommandPacketReport_t *frame_report) {
	ZwAssociationReportFrameFake_t				*report;

	if (packet->dst_zw_channel != 0) {
		report = (ZwAssociationReportFrameFake_t *)frame_report->packet.cmd;
		// report->cmdClass = cmdClass; set in - fillOutgoingPacket
		// report->cmd =  cmd; set in - fillOutgoingPacket
		report->groupingIdentifier = 1;
		report->maxNodesSupported = 0;
		report->reportsToFollow = 0;
		frame_report->packet.len = sizeof(ZwAssociationReportFrameFake_t);
		return (ZUNO_COMMAND_ANSWERED);
	}
	if (_group_id(ASSOCIATION_GROUP_ID_EX(packet)) != ZUNO_UNKNOWN_CMD)
		ASSOCIATION_GROUP_ID_EX(packet) = ZUNO_LIFELINE_GRP;//A node that receives an unsupported Grouping Identifier SHOULD return information relating to Grouping Identifier 1.
	return (ZUNO_UNKNOWN_CMD);
}

int zuno_CCAssociationHandler(ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	int				rs = ZUNO_UNKNOWN_CMD;

	if(cmd->dst_zw_channel == 0)
		return rs;
	switch(ZW_CMD) {
		case ASSOCIATION_SET:
			rs = _group_id(ASSOCIATION_GROUP_ID);
			break;
		case ASSOCIATION_REMOVE:
			rs = _group_id_rm(ASSOCIATION_GROUP_ID);
			break ;
		case ASSOCIATION_GET:
			rs = _assotiation_get(cmd, frame_report);
			break ;
		case ASSOCIATION_GROUPINGS_GET:
			rs = _assotiation_groupings_report(cmd, frame_report);
			break ;
		case ASSOCIATION_SPECIFIC_GROUP_GET:
			rs = _assotiation_specific_group_report(frame_report);
			break ;
		default:
			rs = ZUNO_COMMAND_BLOCKED_NO_SUPPORT;
			break;
	}
	return (rs);
}

int zuno_CCMultiAssociationHandler(ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	int			rs = ZUNO_UNKNOWN_CMD;
	if(cmd->dst_zw_channel == 0)
		return rs;
	switch(ZW_CMD) {
		
		case MULTI_CHANNEL_ASSOCIATION_SET:
			rs = _group_id(ASSOCIATION_GROUP_ID);
			break ;
		case MULTI_CHANNEL_ASSOCIATION_REMOVE:
			rs = _group_id_rm(ASSOCIATION_GROUP_ID);
			break ;
		case MULTI_CHANNEL_ASSOCIATION_GET:
			rs = _assotiation_get(cmd, frame_report);
			break ;
		case MULTI_CHANNEL_ASSOCIATION_GROUPINGS_GET:
			rs = _assotiation_groupings_report(cmd, frame_report);
			break ;
		default:
			rs = ZUNO_COMMAND_BLOCKED_NO_SUPPORT;
			break ;
	}
	return (rs);
}

const char *zunoAssociationGroupName(uint8_t groupIndex) __attribute__ ((weak));
const char *zunoAssociationGroupName(uint8_t groupIndex) {
	(void)groupIndex;
	return (NULL);
}

static int _association_gpr_info_name_report(ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	char									group_name_default[sizeof(ASSOCIATION_GROUP_NAME_DEFAULT)];
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
	else if ((group_name = (char *)zunoAssociationGroupName(groupIndex - 1)) != NULL) {
		len = strlen(group_name);
		if (len > ASSOCIATION_GROUP_NAME_MAX)
			len = ASSOCIATION_GROUP_NAME_MAX;
	}
	else {
		group_name = &group_name_default[0];
		memcpy(group_name, ASSOCIATION_GROUP_NAME_DEFAULT, sizeof(ASSOCIATION_GROUP_NAME_DEFAULT));
		len = (sizeof(ASSOCIATION_GROUP_NAME_DEFAULT)- 1);
		group_name[len - 1] = groupIndex % 10 + 0x30;
		group_name[len - 2] = groupIndex / 10 + 0x30;
	}
	lp = (ZwAssociationGroupNameReportFrame_t *)frame_report->packet.cmd;
	// lp->cmdClass = COMMAND_CLASS_ASSOCIATION_GRP_INFO; set in - fillOutgoingPacket
	// lp->cmd = ASSOCIATION_GROUP_NAME_REPORT; set in - fillOutgoingPacket
	lp->groupingIdentifier = groupIndex;
	lp->lengthOfName = len;
	memcpy(&lp->name[0], group_name, len);
	frame_report->packet.len = sizeof(ZwAssociationGroupNameReportFrame_t) + len;
	return (ZUNO_COMMAND_ANSWERED);
}

#define ASSOCIATION_TYPE_SHIFT						0x0
#define ASSOCIATION_TYPE_MASK						0x7
#define ASSOCIATION_CHANNEL_SHIFT					0x3
#define ASSOCIATION_CHANNEL_MASK					0xF8

void zuno_CCSensorMultilevelGetProfile(uint8_t channel, ZwAssociationInfoOut_t *agi);
void zuno_CCNotificationGetProfile(uint8_t channel, ZwAssociationInfoOut_t *agi);
void zuno_CCMeterGetProfile(uint8_t channel, ZwAssociationInfoOut_t *agi);

static int _association_gpr_info_profile_report(ZUNOCommandPacket_t *packet, ZwAssociationGroupInfoGetFrame_t *in, ZUNOCommandPacketReport_t *frame_report) {
	uint8_t									groupIndex;
	uint8_t									groupIndex_end;
	ZwAssociationGroupInfoReportFrame_t		*lp;
	size_t									count;
	uint8_t									channel;
	ZwAssociationInfoOut_t					agi;

	lp = (ZwAssociationGroupInfoReportFrame_t *)frame_report->packet.cmd;
	// lp->cmdClass = COMMAND_CLASS_ASSOCIATION_GRP_INFO; set in - fillOutgoingPacket
	// lp->cmd = ASSOCIATION_GROUP_INFO_REPORT; set in - fillOutgoingPacket
	lp->properties1 = 0x0;
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
	count = 0x0;
	while (groupIndex <= groupIndex_end) {
		switch (groupIndex) {
			case ZUNO_LIFELINE_GRP:
				lp->variantgroup[count].groupingIdentifier = ZUNO_LIFELINE_GRP;
				lp->variantgroup[count].profile1 = 0;
				lp->variantgroup[count].profile2 = 1;
				break ;
			default:
				lp->variantgroup[count].groupingIdentifier = groupIndex;
				channel = (ZUNO_CFG_ASSOCIATION(groupIndex - 2).type & ASSOCIATION_CHANNEL_MASK) >> ASSOCIATION_CHANNEL_SHIFT;
				if (channel == 0x0) {
					agi.profile1 = 0x0;
					agi.profile2 = 0x0;
				}
				else {
					channel--;
					switch (ZUNO_CFG_CHANNEL(channel).type) {
						#if defined(WITH_CC_SENSOR_MULTILEVEL)
						case ZUNO_SENSOR_MULTILEVEL_CHANNEL_NUMBER:
							zuno_CCSensorMultilevelGetProfile(channel, &agi);
							break ;
						#endif
						#if defined(WITH_CC_NOTIFICATION)
						case ZUNO_SENSOR_BINARY_CHANNEL_NUMBER:
							zuno_CCNotificationGetProfile(channel, &agi);
							break ;
						#endif
						#if defined(WITH_CC_METER)
						case ZUNO_METER_CHANNEL_NUMBER:
							zuno_CCMeterGetProfile(channel, &agi);
							break ;
						#endif
						default:
							agi.profile1 = 0x0;
							agi.profile2 = 0x0;
							break ;
					}
				}
				lp->variantgroup[count].profile1 = agi.profile1;
				lp->variantgroup[count].profile2 = agi.profile2;
				break ;
		}
		lp->variantgroup[count].mode = 0x0;
		lp->variantgroup[count].reserved = 0x0;
		lp->variantgroup[count].eventCode1 = 0x0;
		lp->variantgroup[count].eventCode2 = 0x0;
		count++;
		groupIndex++;
		if (count == ((ZUNO_COMMAND_PACKET_CMD_LEN_MAX_OUT - sizeof(lp[0x0])) / sizeof(lp->variantgroup[0x0]))) {
			lp->properties1 = (lp->properties1 & (~0x3F) ) | count;
			frame_report->packet.len = sizeof(ZwAssociationGroupInfoReportFrame_t) + count * sizeof(lp->variantgroup[0x0]);
			zunoSendZWPackage(&frame_report->packet);
			count = 0x0;
		}
	}
	if (count != 0x0) {
		lp->properties1 = (lp->properties1 & (~0x3F) ) | count;
		frame_report->packet.len = sizeof(ZwAssociationGroupInfoReportFrame_t) + count * sizeof(lp->variantgroup[0x0]);
		zunoSendZWPackage(&frame_report->packet);
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
		#ifdef WITH_CC_WINDOW_COVERING
		case COMMAND_CLASS_WINDOW_COVERING:
			cmd = WINDOW_COVERING_REPORT;
			break ;
		#endif
		#ifdef WITH_CC_SOUND_SWITCH
		case COMMAND_CLASS_SOUND_SWITCH:
			command[0] = cmdClass;
			command[1] = SOUND_SWITCH_TONE_PLAY_REPORT;
			command = command + 0x2;
			cmd = SOUND_SWITCH_CONFIGURATION_REPORT;
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

static int _association_gpr_info_command_report(ZwAssociationGroupCommandListGetFrame_t *in, ZUNOCommandPacket_t *packet, ZUNOCommandPacketReport_t *frame_report) {
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
	lp = (ZwAssociationGroupCommandListReportFrame_t *)frame_report->packet.cmd;
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
		switch ((ZUNO_CFG_ASSOCIATION(groupIndex - 2).type & ASSOCIATION_TYPE_MASK) >> ASSOCIATION_TYPE_SHIFT) {
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
	frame_report->packet.len = sizeof(ZwAssociationGroupCommandListReportFrame_t) + listLength;
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCAssociationGprInfoHandler(ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	int				rs;

	rs = ZUNO_UNKNOWN_CMD;
	switch(ZW_CMD) {
		case ASSOCIATION_GROUP_NAME_GET:
			rs = _association_gpr_info_name_report(cmd, frame_report);
			break ;
		case ASSOCIATION_GROUP_INFO_GET:
			rs = _association_gpr_info_profile_report(cmd, (ZwAssociationGroupInfoGetFrame_t *)cmd->cmd, frame_report);
			break ;
		case ASSOCIATION_GROUP_COMMAND_LIST_GET:
			rs = _association_gpr_info_command_report((ZwAssociationGroupCommandListGetFrame_t *)cmd->cmd, cmd, frame_report);
			break ;
	}
	return (rs);
}

void zunoAddAssociation(byte type, uint8_t channel) {
	uint8_t						num;

	if (type == 0 || type > 0x4 || channel > 0x1F || (num = ZUNO_CFG_ASSOCIATION_COUNT) >= ZUNO_MAX_ASSOC_NUMBER)
		return ;
	ZUNO_CFG_ASSOCIATION_COUNT++;
	ZUNO_CFG_ASSOCIATION(num).type = (type << ASSOCIATION_TYPE_SHIFT) | (channel << ASSOCIATION_CHANNEL_SHIFT);
}

static void _init_group(ZUNOCommandPacketReport_t *frame, uint8_t groupIndex) {
	fillOutgoingRawPacket(&frame->packet, &frame->data[0x0], 0x0, ZUNO_PACKETFLAGS_GROUP | QUEUE_CHANNEL_CONTROL, groupIndex + 1);
}

static void _send_group(ZUNOCommandPacketReport_t *frame, size_t len) {
	frame->packet.len = len;
	// It's a user group (not LifeLine) and the queue is blocked
	if((frame->packet.dst_node > ZUNO_LIFELINE_GRP) && zunoCheckSystemQueueStatus(QUEUE_CHANNEL_CONTROL)){
		// Try to find the package for user group and substitude it to new one
		ZUNOCommandPacket_t * p	 = ZWQFindPackage(frame->packet.dst_node, frame->packet.flags, 0xFF, 0xFF);
		if(p != NULL){
			if(p->dst_zw_channel != 0){
				// Processing has been started -  add a new one package
			} else {
			  // Substitute an existing package
			  if(len == p->len){
			  	memcpy(p->cmd, frame->packet.cmd, len);
			  } else {
				#ifdef LOGGING_DBG
			  	LOGGING_UART.print(millis());
			  	LOGGING_UART.println(" (*ASSOC*) Wrong pkg length!!!");  
			  	#endif
			  }
			  #ifdef LOGGING_DBG
			  LOGGING_UART.print(millis());
			  LOGGING_UART.print(" (*ASSOC*) Replace pkg for grp:");
			  LOGGING_UART.println(frame->packet.dst_node);	  
		      #endif
			  return;
			}
		}
	}
	zunoSendZWPackage(&frame->packet);
}

void zunoSendToGroupSetValueCommand(uint8_t groupIndex, uint8_t value) {
	ZwBasicSetFrame_t								*lp;
	ZUNOCommandPacketReport_t						frame;

	if (_group_id(groupIndex) != ZUNO_UNKNOWN_CMD)
		return ;
	_init_group(&frame, groupIndex);
	lp = (ZwBasicSetFrame_t *)&frame.packet.cmd[0x0];
	lp->cmdClass = COMMAND_CLASS_BASIC;
	lp->cmd = BASIC_SET;
	lp->value = value;
	_send_group(&frame, sizeof(lp[0x0]));
}

void zunoSendToGroupDimmingCommand(uint8_t groupIndex, uint8_t direction, uint8_t start_stop) {
	ZwSwitchMultilevelStartLevelChangeFrame_t						*lp;
	ZUNOCommandPacketReport_t										frame;
	size_t															len;

	if (_group_id(groupIndex) != ZUNO_UNKNOWN_CMD)
		return ;
	_init_group(&frame, groupIndex);
	lp = (ZwSwitchMultilevelStartLevelChangeFrame_t *)&frame.packet.cmd[0x0];
	lp->v1.cmdClass = COMMAND_CLASS_SWITCH_MULTILEVEL;
	if(start_stop != false) {
		lp->v1.cmd = SWITCH_MULTILEVEL_START_LEVEL_CHANGE;
		lp->v1.properties1 = (direction == true) ? 0x60 : 0x20;
		lp->v1.startLevel = 0;
		len = sizeof(lp->v1);
	}
	else {
		lp->v1.cmd = SWITCH_MULTILEVEL_STOP_LEVEL_CHANGE;
		len = sizeof(ZwSwitchMultilevelStopLevelChangeFrame_t);
	}
	_send_group(&frame, len);
}

void zunoSendToGroupScene(uint8_t groupIndex, uint8_t scene) {
	ZwSceneActivationSetFrame_t								*lp;
	ZUNOCommandPacketReport_t								frame;

	if (_group_id(groupIndex) != ZUNO_UNKNOWN_CMD)
		return ;
	_init_group(&frame, groupIndex);
	lp = (ZwSceneActivationSetFrame_t *)&frame.packet.cmd[0x0];
	lp->cmdClass = COMMAND_CLASS_SCENE_ACTIVATION;
	lp->cmd = SCENE_ACTIVATION_SET;
	lp->sceneId = scene;
	//lp->dimmingDuration = 0xFF;//Specify dimming duration configured by the Scene Actuator Configuration Set and Scene Controller Configuration Set Command depending on device used.
	//CMD_REPORT_LEN = sizeof(ZwSceneActivationSetFrame_t);
	_send_group(&frame, 0x3);
}

void zunoSendToGroupDoorlockControlTiming(uint8_t groupIndex, uint8_t open_close, uint16_t seconds) {
	ZwDoorLockOperationSet_t								*lp;
	ZwDoorLockConfigurationSetFrame_t						*time;
	ZUNOCommandPacketReport_t								frame;
	size_t													lockTimeoutMinutes;
	size_t													lockTimeoutSeconds;
	size_t													operationType;
	size_t													doorLockMode;

	if (_group_id(groupIndex) != ZUNO_UNKNOWN_CMD)
		return ;
	_init_group(&frame, groupIndex);
	time = (ZwDoorLockConfigurationSetFrame_t *)&frame.packet.cmd[0x0];
	time->v3.cmdClass = COMMAND_CLASS_DOOR_LOCK;
	time->v3.cmd = DOOR_LOCK_CONFIGURATION_SET;
	if (seconds == 0x0) {
		operationType = DOOR_LOCK_CONFIGURATION_REPORT_CONSTANT_OPERATION_V4;
		lockTimeoutMinutes = 0xFE;
		lockTimeoutSeconds = 0xFE;
		if (open_close != false)
			doorLockMode = DOOR_LOCK_OPERATION_REPORT_DOOR_UNSECURED_V4;
		else
			doorLockMode = DOOR_LOCK_OPERATION_REPORT_DOOR_SECURED_V4;
	}
	else {
		if (seconds > 15239)//15239 max seconds
			seconds = 15239;
		operationType = DOOR_LOCK_CONFIGURATION_REPORT_TIMED_OPERATION_V4;
		lockTimeoutMinutes = seconds / 60;
		lockTimeoutSeconds = seconds % 60;
		doorLockMode = DOOR_LOCK_OPERATION_REPORT_DOOR_UNSECURED_WITH_TIMEOUT_V4;
	}
	time->v3.operationType = operationType;
	time->v3.properties1 = 0x0;
	time->v3.lockTimeoutMinutes = lockTimeoutMinutes;
	time->v3.lockTimeoutSeconds = lockTimeoutSeconds;
	_send_group(&frame, sizeof(time->v3));
	lp = (ZwDoorLockOperationSet_t *)&frame.packet.cmd[0x0];
	// lp->cmdClass = COMMAND_CLASS_DOOR_LOCK;
	lp->cmd = DOOR_LOCK_OPERATION_SET;
	lp->doorLockMode = doorLockMode;
	_send_group(&frame, sizeof(lp[0x0]));
	(void)seconds;
}