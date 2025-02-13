#include "Arduino.h"
#include "ZWCCTimer.h"
#include "ZWCCSwitchColor.h"
#include "ZWCCSwitchMultilevel.h"
#include "ZWCCSuperVision.h"

#ifdef WITH_CC_SWITCH_COLOR
uint64_t rtcc_micros(void);

static uint32_t _get_color_component_mask(uint8_t channel) {
	return (ZUNO_CFG_CHANNEL(channel).sub_type);
}

static uint8_t _get_value(uint8_t channel, uint8_t colorComponentId) {
	uint8_t current_level;

	current_level = zuno_universalGetter2P(channel, colorComponentId);
	return (current_level);
}

static bool _get_values(uint8_t channel, uint8_t colorComponentId, uint8_t *current_value, uint8_t *duration_table_8, uint8_t *target_value) {
	uint8_t												currentValue;

	currentValue = _get_value(channel, colorComponentId);
	current_value[0x0] = currentValue;
	return (zunoTimerTreadDimingGetValues(zunoTimerTreadDimingTypeSwitchColor, channel, currentValue, duration_table_8, target_value, &colorComponentId, 0x1));
}

static void _get_set_full(uint8_t channel, ZUNOCommandPacket_t *packet, uint8_t colorComponentId) {
	ZwSwitchColorReportFrame_t *report;

	report = (ZwSwitchColorReportFrame_t *)&packet->packet.cmd[0x0];
	packet->packet.len = sizeof(report->v3);
	report->v3.cmdClass = COMMAND_CLASS_SWITCH_COLOR;
	report->v3.cmd = SWITCH_COLOR_REPORT;
	report->v3.colorComponentId = colorComponentId;
	_get_values(channel, colorComponentId, &report->v3.currentValue, &report->v3.duration, &report->v3.targetValue);
}

static void _timer_stop(uint8_t channel, uint8_t colorComponentId) {
	zunoTimerTreadDimingStop(zunoTimerTreadDimingTypeSwitchColor, channel, &colorComponentId, 0x1);
}

void __zunoSwitchColorSet(uint8_t channel, uint8_t colorComponentId, uint8_t value) {
	zuno_universalSetter2P(channel, colorComponentId, value);
}

static int _supported_report(uint8_t channel, ZUNOCommandPacketReport_t *frame_report) {//Processed to get the value of the color components
	ZwSwitchColorSupportedReporFrame_t		*lp;

	lp = (ZwSwitchColorSupportedReporFrame_t *)frame_report->info.packet.cmd;
	// lp->cmdClass = COMMAND_CLASS_SWITCH_COLOR; set in - fillOutgoingPacket
	// lp->cmd = SWITCH_COLOR_SUPPORTED_REPORT; set in - fillOutgoingPacket
	lp->colorComponentMask1 = _get_color_component_mask(channel);//It contains a bitmask of colors
	lp->colorComponentMask2 = 0;
	frame_report->info.packet.len = sizeof(ZwSwitchColorSupportedReporFrame_t);
	return (ZUNO_COMMAND_ANSWERED);
}

static bool _set_color_test(uint32_t mask, const VgSwitchColorSetVg_t *vg) {
	if ((mask & (0x1 << vg->colorComponentId)) == 0x0)
		return (false);
	return (true);
}

static int _set_color(size_t channel, const ZwSwitchColorSetFrame_t *cmd, size_t len, ZUNOCommandPacketReport_t *frame_report, const ZUNOCommandCmd_t *packet, const ZUNOCommandHandlerOption_t *options) {
	const VgSwitchColorSetVg_t *vg;
	ZwSwitchColorReportFrame_t *report;
	zunoTimerTreadDiming_t *parameter;
	uint32_t mask;
	size_t step;
	size_t duration;
	int result;
	uint8_t count;
	uint8_t currentValue;

	mask = _get_color_component_mask(channel);
	count = cmd->properties1 & 0x1F;//Color Component Count (5 bits)
	vg = &cmd->variantgroup[0];
	result = ZUNO_COMMAND_PROCESSED;
	while (count-- != 0) {
		if (_set_color_test(mask, vg) == false)
			result = ZUNO_COMMAND_BLOCKED_FAIL;
		vg++;
	}
	count = cmd->properties1 & 0x1F;//Color Component Count (5 bits)
	vg = &cmd->variantgroup[0];
	if (len == (sizeof(ZwSwitchColorSetFrame_t) + (count * sizeof(VgSwitchColorSetVg_t))) || (duration = zuno_CCTimerTicksTable7(((uint8_t *)cmd + len - 0x1)[0x0])) == 0x0) {
		zuno_CCSupervisionReportSyncDefault(frame_report, result);
		zunoSendReportSet(channel, frame_report, options, NULL);
		report = (ZwSwitchColorReportFrame_t *)frame_report->info.packet.cmd;
		frame_report->info.packet.len = sizeof(report->v3);
		report->v3.cmdClass = COMMAND_CLASS_SWITCH_COLOR;
		report->v3.cmd = SWITCH_COLOR_REPORT;
		report->v3.duration = 0;
		while (count-- != 0) {
			if (_set_color_test(mask, vg) == true) {
				_timer_stop(channel, vg->colorComponentId);
				__zunoSwitchColorSet(channel, vg->colorComponentId, vg->value);
				report->v3.colorComponentId = vg->colorComponentId;
				report->v3.targetValue = vg->value;
				report->v3.currentValue = vg->value;
				zunoSendZWPacketAdd(frame_report);
			}
			vg++;
		}
		return (result);
	}
	while (count-- != 0) {
		if ((parameter = zunoTimerTreadDimingCreate()) == NULL)
			return (ZUNO_COMMAND_BLOCKED_FAIL);
		_timer_stop(channel, vg->colorComponentId);
		if (zuno_CCSupervisionReportSyncWorking(frame_report, ((uint8_t *)cmd + len - 0x1)[0x0]) == true) {
			parameter->flag = ZUNO_TIMER_TREA_DIMING_FLAG_SUPERVISION;
			zuno_CCSupervisionAsyncProcessedSet(packet, &parameter->super_vision);
		}
		else
			parameter->flag = 0x0;
		currentValue = _get_value(channel, vg->colorComponentId);
		if (vg->value > currentValue) {
			step = duration / (vg->value - currentValue);
			parameter->flag = parameter->flag | ZUNO_TIMER_TREA_DIMING_FLAG_MODE_UP;
		}
		else {
			step = duration / (currentValue - vg->value);
			parameter->flag = parameter->flag | ZUNO_TIMER_TREA_DIMING_FLAG_MODE_DOWN;
		}
		parameter->step = step;
		parameter->current_value = currentValue;
		parameter->ticks_end = (rtcc_micros() / 1000) + duration;
		parameter->target_value = vg->value;
		parameter->type = zunoTimerTreadDimingTypeSwitchColor;
		parameter->channel = channel;
		parameter->colorComponentId = vg->colorComponentId;
		zunoTimerTreadDimingAdd(parameter, options);
		vg++;
	}
	return (result);
}

static void _start_level_set_fast(uint8_t channel, ZUNOCommandPacketReport_t *frame_report, const ZUNOCommandHandlerOption_t *options, uint8_t current_level, uint8_t colorComponentId) {
	ZwSwitchColorReportFrame_t *report;

	__zunoSwitchColorSet(channel, colorComponentId, current_level);
	zuno_CCSupervisionReportSyncDefault(frame_report, ZUNO_COMMAND_PROCESSED);
	zunoSendReportSet(channel, frame_report, options, NULL);
	report = (ZwSwitchColorReportFrame_t *)frame_report->info.packet.cmd;
	frame_report->info.packet.len = sizeof(report->v3);
	report->v3.cmdClass = COMMAND_CLASS_SWITCH_COLOR;
	report->v3.cmd = SWITCH_COLOR_REPORT;
	report->v3.duration = 0;
	report->v3.colorComponentId = colorComponentId;
	report->v3.targetValue = current_level;
	report->v3.currentValue = current_level;
	zunoSendZWPacketAdd(frame_report);
}

static int _start_level(size_t channel, const ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report, const ZUNOCommandHandlerOption_t *options) {// Prepare the structure for dimming
	const ZwSwitchColorStartLevelChange_FRAME_u *pk;
	zunoTimerTreadDiming_t *parameter;
	uint8_t colorComponentId;
	uint8_t current_level;
	uint8_t targetValue;
	size_t step;

	pk = (ZwSwitchColorStartLevelChange_FRAME_u *)cmd->cmd;
	colorComponentId = pk->v2.colorComponentId;
	if ((_get_color_component_mask(channel) & (0x1 << colorComponentId)) == 0x0)
		return (ZUNO_COMMAND_BLOCKED_FAIL);
	_timer_stop(channel, colorComponentId);
	if ((pk->v2.properties1 & (1 << 5)) == 0) {// If the level from which you want to start dimming has come, make it current
		current_level = pk->v2.startLevel;
		__zunoSwitchColorSet(channel, colorComponentId, current_level);
	}
	else// Otherwise, get the current
		current_level = _get_value(channel, colorComponentId);
	if (cmd->len == sizeof(ZwSwitchColorStartLevelChangeV2Frame_t)) {
		step = ZUNO_TIMER_SWITCH_DEFAULT_DURATION * (1000);// Depending on the version, set the default step to increase or from the command we will
	}
	else {
		step = zuno_CCTimerTicksTable7(pk->v3.duration);
	}
	if ((pk->v2.properties1 & (1 << 6)) == 0)// Dimming to up
		targetValue = ZUNO_TIMER_COLOR_MAX_VALUE;
	else// Dimming to down
		targetValue = ZUNO_TIMER_COLOR_MIN_VALUE;
	if (current_level == targetValue)
		return (ZUNO_COMMAND_PROCESSED);
	step = step / (ZUNO_TIMER_COLOR_MAX_VALUE);
	if (step == 0) {// If the step turned out to be zero - immediately set the desired level
		_start_level_set_fast(channel, frame_report, options, targetValue, colorComponentId);
		return (ZUNO_COMMAND_PROCESSED);
	}
	if ((parameter = zunoTimerTreadDimingCreate()) == NULL)
		return (ZUNO_COMMAND_BLOCKED_FAIL);
	parameter->colorComponentId = colorComponentId;
	parameter->channel = channel;
	parameter->type = zunoTimerTreadDimingTypeSwitchColor;
	parameter->step = step;
	parameter->current_value = current_level;
	parameter->target_value = targetValue;
	parameter->flag = 0x0;
	zunoTimerTreadDimingAddStartLevel(parameter, options);
	return (ZUNO_COMMAND_PROCESSED);
}

static void _stop_level(uint8_t channel, uint8_t colorComponentId) {// Stop Dimming
	_timer_stop(channel, colorComponentId);
}

static int _report_get_color(uint8_t channel, const ZwSwitchColorGetFrame_t *in, ZUNOCommandPacketReport_t *frame_report) {
	_get_set_full(channel, &frame_report->info, in->colorComponentId);
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCSwitchColorHandler(uint8_t channel, const ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report, const ZUNOCommandHandlerOption_t *options) {
	int				rs;

	switch(ZW_CMD)
	{
		case SWITCH_COLOR_SUPPORTED_GET:
			rs = _supported_report(channel, frame_report);
			break ;
		case SWITCH_COLOR_GET:
			_zunoMarkChannelRequested(channel);
			rs = _report_get_color(channel, (ZwSwitchColorGetFrame_t *)cmd->cmd, frame_report);
			break ;
		case SWITCH_COLOR_SET:
			rs = _set_color(channel, (const ZwSwitchColorSetFrame_t *)cmd->cmd, cmd->len, frame_report, cmd, options);
			break ;
		case SWITCH_COLOR_START_LEVEL_CHANGE:
			rs = _start_level(channel, cmd, frame_report, options);
			break ;
		case SWITCH_COLOR_STOP_LEVEL_CHANGE:
			_stop_level(channel, ((ZwSwitchColorStopLevelChange_t *)cmd->cmd)->colorComponentId);
			rs = ZUNO_COMMAND_PROCESSED;
			break ;
		default:
			rs = ZUNO_COMMAND_BLOCKED_NO_SUPPORT;
			break ;
	}
	return (rs);
}

void zuno_CCSwitchColorReportTimer(ZUNOCommandPacketReport_t *frame_report, const zunoTimerTreadDiming_t *list) {
	zunoSendReportSet(list->channel, frame_report, &list->options, NULL);
	_get_set_full(list->channel, &frame_report->info, list->colorComponentId);
	zunoSendZWPacketAdd(frame_report);
}

int zuno_CCSwitchColorReport(uint8_t channel, ZUNOCommandPacket_t *packet) {
	uint8_t colorComponentId;
	uint8_t mask;
	
	mask = _get_color_component_mask(channel);//It contains a bitmask of colors
	colorComponentId = 0;
	while (mask != 0) {//We will pass through all the colors and send a report for each
		if ((mask & 0x01) != 0) {
			_get_set_full(channel, packet, colorComponentId);
			zunoSendZWPacket(packet);
		}
		colorComponentId++;
		mask >>=  1;
	}
	return (ZUNO_COMMAND_PROCESSED);
}

#endif