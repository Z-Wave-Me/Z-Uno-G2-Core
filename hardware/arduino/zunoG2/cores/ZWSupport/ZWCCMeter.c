#include "ZWCCMeter.h"

typedef struct _ZW_METER_SUPPORTED_REPORT_1BYTE_V6_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   properties1;                  /* masked byte */
    uint8_t   properties2;                  /* masked byte */
    uint8_t   numberOfScaleSupportedBytesToFollow;/**/
    uint8_t   scaleSupported1[];              
} ZW_METER_SUPPORTED_REPORT_1BYTE_V6_FRAME;


// #ifdef WITH_CC_METER

static uint8_t _get_rate(uint8_t channel) {
	return (METER_REPORT_RATE_TYPE_IMPORT);
	(void)channel;
}

static uint8_t _get_type(uint8_t channel) {
	return ((ZUNO_CFG_CHANNEL(channel).sub_type & ZUNO_METER_SUBTYPE_TYPE_MASK) >> ZUNO_METER_SUBTYPE_TYPE_SHIFT);
}

static uint8_t _get_reset(uint8_t channel) {
	return ((ZUNO_CFG_CHANNEL(channel).sub_type & ZUNO_METER_SUBTYPE_RESETABLE_MASK) >> ZUNO_METER_SUBTYPE_RESETABLE_SHIFT);
}

static uint8_t _get_scale(uint8_t channel) {
	uint32_t							params;

	memcpy(&params, &ZUNO_CFG_CHANNEL(channel).params[0x0], sizeof(params));
	return ((params & ZUNO_METER_PARAMETR_SCALE_MASK) >> ZUNO_METER_PARAMETR_SCALE_SHIFT);
}

static uint8_t _get_size(uint8_t channel) {
	uint32_t							params;

	memcpy(&params, &ZUNO_CFG_CHANNEL(channel).params[0x0], sizeof(params));
	return (((params & ZUNO_METER_PARAMETR_SIZE_MASK) >> ZUNO_METER_PARAMETR_SIZE_SHIFT) + 0x1);
}

static uint8_t _get_precision(uint8_t channel) {
	uint32_t							params;

	memcpy(&params, &ZUNO_CFG_CHANNEL(channel).params[0x0], sizeof(params));
	return (((params & ZUNO_METER_PARAMETR_PRECISION_MASK) >> ZUNO_METER_PARAMETR_PRECISION_SHIFT));
}


uint8_t __meter_get_scale(const ZwMeterReportV6Frame_t *report) {
	uint8_t								scale;
	const uint8_t						*lp;
	uint32_t							channel_size;

	scale = (report->properties1 & METER_PROPERTIES_SCALE_MSB_MASK) >> METER_PROPERTIES_SCALE_MSB_SHIFT;
	scale = scale | (report->properties2 & METER_PROPERTIES_SCALE_LSB_MASK) >> METER_PROPERTIES_SCALE_LSB_SHIFT;
	if (scale != ZUNO_METER_SCALE_MST)
		return (scale);
	channel_size = report->properties2 & METER_PROPERTIES_SIZE_MASK;
	lp = &report->meterValue[0x0];
	return (scale + lp[channel_size + 0x2]);
}

int zuno_CCMeterReport(byte channel, const ZUNOCommandPacket_t *paket, ZUNOCommandPacket_t *report_paket) {//v6
	ZwMeterReportV6Frame_t				*report;
	uint32_t							channel_size;
	int32_t								value;
	uint8_t								*lp;
	size_t								len;
	const ZwMeterGetFrame_t				*cmd;
	uint8_t								scale;
	uint8_t								properties1;
	uint8_t								type;
	uint8_t								scale_device;

	scale_device = _get_scale(channel);
	if (paket != NULL) {
		cmd = (const ZwMeterGetFrame_t *)paket->cmd;
		len = paket->len;
		if (len != sizeof(cmd->v1)) {
			properties1 = cmd->v6.properties1;
			scale = (properties1 & METER_GET_PROPERTIES1_SCALE_MASK) >> METER_GET_PROPERTIES1_SCALE_SHIFT;
			if (len == sizeof(cmd->v6)) {
				type = (properties1 & METER_GET_PROPERTIES1_RATE_TYPE_MASK) >> METER_GET_PROPERTIES1_RATE_TYPE_SHIFT;
				if (type != METER_GET_RATE_TYPE_RESERVED && type != _get_rate(channel))
					return (ZUNO_COMMAND_BLOCKED);
				if (scale == ZUNO_METER_SCALE_MST)
					scale = scale + cmd->v6.scale2;
			}
			if (scale != scale_device)
				return (ZUNO_COMMAND_BLOCKED);
		}
	}
	report = (ZwMeterReportV6Frame_t *)&report_paket->cmd[0x0];
	report->cmdClass = COMMAND_CLASS_METER;
	report->cmd = METER_REPORT;
	properties1 = _get_type(channel);
	if (paket != NULL && len == sizeof(cmd->v1))
		;
	else
		properties1 = properties1 | (_get_rate(channel) << METER_REPORT_PROPERTIES1_RATE_TYPE_SHIFT) | (((scale_device >= ZUNO_METER_SCALE_MST ? ZUNO_METER_SCALE_MST: scale_device) & 0x4) << 0x5);
	report->properties1 = properties1;
	channel_size = _get_size(channel) ;
	report->properties2 = channel_size | ((_get_precision(channel) << METER_REPORT_PROPERTIES2_PRECISION_SHIFT) & METER_REPORT_PROPERTIES2_PRECISION_MASK) | (((scale_device >= ZUNO_METER_SCALE_MST ? ZUNO_METER_SCALE_MST: scale_device) << METER_REPORT_PROPERTIES2_SCALE_BITS_10_SHIFT) & METER_REPORT_PROPERTIES2_SCALE_BITS_10_MASK);
	value = zuno_universalGetter1P(channel);
	lp = &report->meterValue[0x0];
	_zme_memcpy(lp, (uint8_t *)&value, channel_size);
	lp[channel_size] = 0x0;//deltaTime1
	lp[channel_size + 0x1] = 0x0;//deltaTime2 if deltaTime == 0 previousMeterValue not support // update __meter_get_scale - if change
	if (scale_device >= ZUNO_METER_SCALE_MST) {
		scale_device = scale_device - ZUNO_METER_SCALE_MST;
		channel_size++;//+1 - scale2
		lp[channel_size + 0x1] = scale_device;
	}
	report_paket->len = sizeof(report[0x0]) + channel_size + 0x2;//+2 - deltaTime 
	return (ZUNO_COMMAND_ANSWERED);
}

static int _reset(size_t channel, const ZwMeterResetFrame_t *cmd, size_t len) {
	size_t							value;
	size_t							precision_new;
	size_t							precision_old;
	uint8_t							scale_device;
	uint8_t							size;

	value = 0x0;
	switch (len) {
		case sizeof(cmd->v2):
			break ;
		default:
			scale_device = _get_scale(channel);
			if (cmd->v6.properties1 != ((((scale_device >= ZUNO_METER_SCALE_MST ? ZUNO_METER_SCALE_MST: scale_device) & 0x4) << 0x5) | (_get_rate(channel) << METER_REPORT_PROPERTIES1_RATE_TYPE_SHIFT) | _get_type(channel)))
				return (ZUNO_COMMAND_BLOCKED);
			if (((cmd->v6.properties2 & METER_REPORT_PROPERTIES2_SCALE_BITS_10_MASK) >> METER_REPORT_PROPERTIES2_SCALE_BITS_10_SHIFT) != (((scale_device >= ZUNO_METER_SCALE_MST ? ZUNO_METER_SCALE_MST: scale_device) << METER_REPORT_PROPERTIES2_SCALE_BITS_10_SHIFT) & METER_REPORT_PROPERTIES2_SCALE_BITS_10_MASK))
				return (ZUNO_COMMAND_BLOCKED);
			size = _get_size(channel);
			if (scale_device >= ZUNO_METER_SCALE_MST && cmd->v6.meterValue[size] != (scale_device - ZUNO_METER_SCALE_MST))
				return (ZUNO_COMMAND_BLOCKED);
			_zme_memcpy((uint8_t *)&value, (uint8_t *)&cmd->v6.meterValue[0], size);
			precision_new = cmd->v6.properties2 >> METER_REPORT_PROPERTIES2_PRECISION_SHIFT;
			precision_old = _get_precision(channel);
			if (precision_new < precision_old) {
				precision_old = precision_old - precision_new;
				while (precision_old-- != 0)
					value = value * 10;
				
			}
			else if (precision_new > precision_old) {
				precision_new = precision_new - precision_old;
				while (precision_new-- != 0)
					value = value / 10;
				
			}
			break ;
	}
	zuno_universalSetter1P(channel, value);
	return (ZUNO_COMMAND_PROCESSED);
}

static int _support_metter(uint8_t channel, ZUNOCommandPacketReport_t *frame_report) {
	ZW_METER_SUPPORTED_REPORT_1BYTE_V6_FRAME				*report;
	uint8_t													properties1;
	uint8_t													properties2;
	uint8_t													scale;
	uint8_t													numberOfScaleSupportedBytesToFollow;

	report = (ZW_METER_SUPPORTED_REPORT_1BYTE_V6_FRAME *)&frame_report->packet.cmd[0x0];
	// report->cmdClass = COMMAND_CLASS_METER;
	// report->cmd = METER_SUPPORTED_REPORT;
	properties1 = _get_type(channel) | (_get_rate(channel) << METER_SUPPORTED_REPORT_PROPERTIES1_RATE_TYPE_SHIFT);
	if (_get_reset(channel) == METER_RESET_ENABLE)
		properties1 = properties1 | METER_SUPPORTED_REPORT_PROPERTIES1_METER_RESET_BIT_MASK;
	report->properties1 = properties1;
	scale = _get_scale(channel);
	if (scale < ZUNO_METER_SCALE_MST) {
		properties2 = 0x1 << scale;
		numberOfScaleSupportedBytesToFollow = -1;
	}
	else {
		properties2 = METER_SUPPORTED_REPORT_PROPERTIES2_M_S_T_BIT_MASK;
		numberOfScaleSupportedBytesToFollow = 0x1;
		report->scaleSupported1[0x0] = 0x1 << (scale - ZUNO_METER_SCALE_MST);
	}
	report->properties2 = properties2;
	report->numberOfScaleSupportedBytesToFollow = numberOfScaleSupportedBytesToFollow;
	frame_report->packet.len = sizeof(ZW_METER_SUPPORTED_REPORT_1BYTE_V6_FRAME) + numberOfScaleSupportedBytesToFollow;
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCMeterHandler(byte channel, ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	int								rs;

	switch (ZW_CMD) {
		case METER_GET:
			_zunoMarkChannelRequested(channel);
			rs = zuno_CCMeterReport(channel, cmd, &frame_report->packet);
			break ;
		case METER_SUPPORTED_GET:
			rs = _support_metter(channel, frame_report);
			break ;
		case METER_RESET:
			rs = _reset(channel, (const ZwMeterResetFrame_t *)cmd->cmd, cmd->len);
			break ;
		default:
			rs = ZUNO_COMMAND_BLOCKED_NO_SUPPORT;
			break ;
	}
	return (rs);
}
// #endif