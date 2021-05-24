#include "Arduino.h"
#include "ZWCCSensorMultilevel.h"

int zuno_CCSensorMultilevelReport(byte channel, bool reply) {
	ZwSensorMultilevelReportFrame_t					*report;
	size_t											channel_size;
	size_t											value;

	channel_size = ZUNO_CFG_CHANNEL(channel).params[0];
	if(reply){
		report = (ZwSensorMultilevelReportFrame_t *)&CMD_REPLY_CC;
		CMD_REPLY_LEN = channel_size + (sizeof(report->byte1) - 1);
	} else {
		report = (ZwSensorMultilevelReportFrame_t *)&CMD_REPORT_CC;
		CMD_REPORT_LEN = channel_size + (sizeof(report->byte1) - 1);
	}
	report->byte1.cmdClass = COMMAND_CLASS_SENSOR_MULTILEVEL;
	report->byte1.cmd = SENSOR_MULTILEVEL_REPORT;
	report->byte1.sensorType = ZUNO_CFG_CHANNEL(channel).sub_type;
	report->byte1.level = channel_size;
	channel_size &= SENSOR_MULTILEVEL_PROPERTIES_SIZE_MASK;
	value = zuno_universalGetter1P(channel);
	_zme_memcpy(&report->byte1.sensorValue1, (uint8_t *)&value, channel_size);
	
	return (ZUNO_COMMAND_ANSWERED);
}

static int _supported_scale(ZwSensorMultilevelSupportedGetScaleFrame_t *cmd, size_t channel) {
	ZwSensorMultilevelSupportedScaleReportFrame_t				*report;
	size_t														sensorType;
	size_t														properties1;

	report = (ZwSensorMultilevelSupportedScaleReportFrame_t *)&CMD_REPLY_CC;
	sensorType = cmd->sensorType;
	report->cmdClass = COMMAND_CLASS_SENSOR_MULTILEVEL;
	report->cmd = SENSOR_MULTILEVEL_SUPPORTED_SCALE_REPORT;
	report->sensorType = sensorType;
	if (ZUNO_CFG_CHANNEL(channel).sub_type == sensorType)
		properties1 = 1 << ((ZUNO_CFG_CHANNEL(channel).params[0] & SENSOR_MULTILEVEL_PROPERTIES_SCALE_MASK) >> SENSOR_MULTILEVEL_PROPERTIES_SCALE_SHIFT);
	else
		properties1 = 0;
	report->properties1 = properties1;
	CMD_REPLY_LEN = sizeof(ZwSensorMultilevelSupportedScaleReportFrame_t);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _supported_sensor(ZUNOCommandPacket_t *pack, size_t channel) {
	ZwSensorMultilevelSupportedSensorReportFrame_t		*report;
	size_t												i;

	report = (ZwSensorMultilevelSupportedSensorReportFrame_t *)&CMD_REPLY_CC;
	memset(&report->bitMask[0], 0, SENSOR_MULTILEVEL_SUPPORTED_MAX_BYTE_MASK);// clear reply bit mask
	report->cmdClass = COMMAND_CLASS_SENSOR_MULTILEVEL;
	report->cmd = SENSOR_MULTILEVEL_SUPPORTED_SENSOR_REPORT;
	if(pack->dst_zw_channel == 0) {// In case it's a 0 channel mapping we have to declare all the types.
		for (i = 0; i < ZUNO_CFG_CHANNEL_COUNT; i++){
			if (ZUNO_CFG_CHANNEL(i).type != ZUNO_SENSOR_MULTILEVEL_CHANNEL_NUMBER)
				continue;
			if ((ZUNO_CFG_CHANNEL(i).zw_channel & 0x80) || (ZUNO_CFG_CHANNEL(i).zw_channel == 0))
				zunoSetupBitMask(&report->bitMask[0], ZUNO_CFG_CHANNEL(i).sub_type - 1, SENSOR_MULTILEVEL_SUPPORTED_MAX_BYTE_MASK);// bit index starts from 0
		}
	}
	else// If we use multichannel => just one bit in one mask bit index starts from 0
		zunoSetupBitMask(&report->bitMask[0], ZUNO_CFG_CHANNEL(channel).sub_type - 1, SENSOR_MULTILEVEL_SUPPORTED_MAX_BYTE_MASK);
	CMD_REPLY_LEN = sizeof(ZwSensorMultilevelSupportedSensorReportFrame_t) + SENSOR_MULTILEVEL_SUPPORTED_MAX_BYTE_MASK;
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCSensorMultilevelHandler(byte channel, ZUNOCommandPacket_t *cmd) {
	int							rs;

	switch (ZW_CMD) {
		case SENSOR_MULTILEVEL_GET:
			rs = zuno_CCSensorMultilevelReport(channel, true);
			break;
		case SENSOR_MULTILEVEL_SUPPORTED_GET_SENSOR:
			rs = _supported_sensor(cmd, channel);
			break;
		case SENSOR_MULTILEVEL_SUPPORTED_GET_SCALE:
			rs = _supported_scale((ZwSensorMultilevelSupportedGetScaleFrame_t *)cmd->cmd, channel);
			break;
		default:
			rs = ZUNO_UNKNOWN_CMD;
			break ;
	}

	return rs;
}