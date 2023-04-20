#include "Arduino.h"
#include "ZWCCSensorMultilevel.h"

#ifdef WITH_CC_SENSOR_MULTILEVEL
int zuno_CCSensorMultilevelReport(byte channel, ZUNOCommandPacket_t *packet) {
	ZwSensorMultilevelReportFrame_t					*report;
	size_t											channel_size;
	size_t											value;

	channel_size = ZUNO_CFG_CHANNEL(channel).params[0];
	uint8_t sz = channel_size & SENSOR_MULTILEVEL_PROPERTIES_SIZE_MASK;
	report = (ZwSensorMultilevelReportFrame_t *)&packet->cmd[0x0];
	packet->len = sz + sizeof(report[0x0]);
	report->cmdClass = COMMAND_CLASS_SENSOR_MULTILEVEL;
	report->cmd = SENSOR_MULTILEVEL_REPORT;
	report->sensorType = ZUNO_CFG_CHANNEL(channel).sub_type;
	report->level = channel_size;
	value = zuno_universalGetter1P(channel);
	_zme_memcpy(&report->sensorValue[0], (uint8_t *)&value, sz);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _supported_scale(ZwSensorMultilevelSupportedGetScaleFrame_t *cmd, size_t channel, ZUNOCommandPacketReport_t *frame_report) {
	ZwSensorMultilevelSupportedScaleReportFrame_t				*report;
	size_t														sensorType;
	size_t														properties1;
	size_t														i;

	report = (ZwSensorMultilevelSupportedScaleReportFrame_t *)frame_report->packet.cmd;
	report->cmd = SENSOR_MULTILEVEL_SUPPORTED_SCALE_REPORT;
	sensorType = cmd->sensorType;
	// report->cmdClass = COMMAND_CLASS_SENSOR_MULTILEVEL; set in - fillOutgoingPacket
	// report->cmd = SENSOR_MULTILEVEL_SUPPORTED_SCALE_REPORT; set in - fillOutgoingPacket
	report->sensorType = sensorType;
	properties1 = 0x0;
	if (ZUNO_CFG_CHANNEL(channel).type == ZUNO_SENSOR_MULTILEVEL_CHANNEL_NUMBER) {
		if (ZUNO_CFG_CHANNEL(channel).sub_type == sensorType)
			properties1 = 1 << ((ZUNO_CFG_CHANNEL(channel).params[0] & SENSOR_MULTILEVEL_PROPERTIES_SCALE_MASK) >> SENSOR_MULTILEVEL_PROPERTIES_SCALE_SHIFT);
	}
	else {
		i = 0x0;
		while (i < ZUNO_CFG_CHANNEL_COUNT) {
			if (ZUNO_CFG_CHANNEL(i).type == ZUNO_SENSOR_MULTILEVEL_CHANNEL_NUMBER && ZUNO_CFG_CHANNEL(i).sub_type == sensorType) {
				properties1 = 1 << ((ZUNO_CFG_CHANNEL(i).params[0] & SENSOR_MULTILEVEL_PROPERTIES_SCALE_MASK) >> SENSOR_MULTILEVEL_PROPERTIES_SCALE_SHIFT);
				break ;
			}
			i++;
		}
	}

	report->properties1 = properties1;
	frame_report->packet.len = sizeof(ZwSensorMultilevelSupportedScaleReportFrame_t);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _supported_sensor(ZUNOCommandPacket_t *pack, size_t channel, ZUNOCommandPacketReport_t *frame_report) {
	ZwSensorMultilevelSupportedSensorReportFrame_t		*report;
	size_t												i;

	report = (ZwSensorMultilevelSupportedSensorReportFrame_t *)frame_report->packet.cmd;
	memset(&report->bitMask[0], 0, SENSOR_MULTILEVEL_SUPPORTED_MAX_BYTE_MASK);// clear reply bit mask
	// report->cmdClass = COMMAND_CLASS_SENSOR_MULTILEVEL; set in - fillOutgoingPacket
	// report->cmd = SENSOR_MULTILEVEL_SUPPORTED_SENSOR_REPORT; set in - fillOutgoingPacket
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
	frame_report->packet.len = sizeof(ZwSensorMultilevelSupportedSensorReportFrame_t) + SENSOR_MULTILEVEL_SUPPORTED_MAX_BYTE_MASK;
	return (ZUNO_COMMAND_ANSWERED);
}

static int _sensor_multilevel_get(size_t channel, ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	const ZwSensorMultilevelGetV11Frame_t			*paket;
	size_t											i;
	size_t											sensorType;

	_zunoMarkChannelRequested(channel);
	paket = (const ZwSensorMultilevelGetV11Frame_t *)cmd->cmd;
	if (cmd->len != sizeof(ZwSensorMultilevelGetV4Frame_t))
		sensorType = paket->sensorType;
	else
		sensorType = (size_t)-1;
	if (ZUNO_CFG_CHANNEL(channel).type == ZUNO_SENSOR_MULTILEVEL_CHANNEL_NUMBER)
		return (zuno_CCSensorMultilevelReport(channel, &frame_report->packet));
	i = 0x0;
	while (i < ZUNO_CFG_CHANNEL_COUNT) {
		if (ZUNO_CFG_CHANNEL(i).type == ZUNO_SENSOR_MULTILEVEL_CHANNEL_NUMBER) {
			channel = i;
			if (ZUNO_CFG_CHANNEL(i).sub_type == sensorType)
				return (zuno_CCSensorMultilevelReport(i, &frame_report->packet));
		}
		i++;
	}
	return (zuno_CCSensorMultilevelReport(channel, &frame_report->packet));
}

int zuno_CCSensorMultilevelHandler(byte channel, ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	int							rs;

	switch (ZW_CMD) {
		case SENSOR_MULTILEVEL_GET:
			rs = _sensor_multilevel_get(channel, cmd, frame_report);
			break;
		case SENSOR_MULTILEVEL_SUPPORTED_GET_SENSOR:
			rs = _supported_sensor(cmd, channel, frame_report);
			break;
		case SENSOR_MULTILEVEL_SUPPORTED_GET_SCALE:
			rs = _supported_scale((ZwSensorMultilevelSupportedGetScaleFrame_t *)cmd->cmd,channel, frame_report);
			break;
		default:
			rs = ZUNO_UNKNOWN_CMD;
			break ;
	}
	return (rs);
}
#endif // WITH_CC_SENSOR_MULTILEVEL