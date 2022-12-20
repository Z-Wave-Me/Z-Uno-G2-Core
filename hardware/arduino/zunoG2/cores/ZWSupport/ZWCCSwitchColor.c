#include "Arduino.h"
#include "ZWCCTimer.h"
#include "ZWCCSwitchColor.h"
#include "ZWCCSwitchMultilevel.h"
#include "ZWCCSuperVision.h"

#ifdef WITH_CC_SWITCHCOLOR
typedef struct					ZunoColorDuration_s {
	uint8_t						targetValue;
	uint8_t						currentValue;
	uint8_t						channel;
	uint8_t						colorComponentId;
	struct
	{
		uint32_t				diming: 1;
		uint32_t				step: 31;
	};
	uint32_t					ticks;
}								ZunoColorDuration_t;

static ZunoColorDuration_t _duration[0xA];

static int _supported_report(uint8_t channel, ZUNOCommandPacketReport_t *frame_report) {//Processed to get the value of the color components
	ZwSwitchColorSupportedReporFrame_t		*lp;

	lp = (ZwSwitchColorSupportedReporFrame_t *)frame_report->packet.cmd;
	// lp->cmdClass = COMMAND_CLASS_SWITCH_COLOR; set in - fillOutgoingPacket
	// lp->cmd = SWITCH_COLOR_SUPPORTED_REPORT; set in - fillOutgoingPacket
	lp->colorComponentMask1 = ZUNO_CFG_CHANNEL(channel).sub_type;//It contains a bitmask of colors
	lp->colorComponentMask2 = 0;
	frame_report->packet.len = sizeof(ZwSwitchColorSupportedReporFrame_t);
	return (ZUNO_COMMAND_ANSWERED);
}

static void _start_level_set(size_t channel, size_t current_level, size_t targetValue, size_t colorComponentId, size_t step, size_t diming, size_t duration, ZUNOCommandPacketReport_t *frame_report) {
	ZunoTimerBasic_t								*lp;
	ZunoColorDuration_t								*lpDur_b;
	ZunoColorDuration_t								*lpDur_e;
	size_t											tempos;

	zunoEnterCritical();
	if ((lp = zuno_CCTimerBasicFind(channel)) != 0x0) {
		lpDur_b = &_duration[0];
		lpDur_e = &_duration[(sizeof(_duration) / sizeof(ZunoColorDuration_t))];
		tempos = channel + 0x1;
		while (lpDur_b < lpDur_e) {
			if (lpDur_b->channel == tempos && lpDur_b->colorComponentId == colorComponentId)
				break ;
			lpDur_b++;
		}
		if (lpDur_b == lpDur_e) {
			lpDur_b = &_duration[0];
			while (lpDur_b < lpDur_e) {
				if (lpDur_b->channel == 0x0)
					break ;
				lpDur_b++;
			}
		}
		if (lpDur_b != lpDur_e) {
			lp->bMode = ZUNO_TIMER_SWITCH_NO_BASIC;
			lp->channel = tempos;
			lpDur_b->channel = tempos;
			lpDur_b->diming = diming;
			lpDur_b->step = step;
			lpDur_b->ticks = millis();
			lpDur_b->colorComponentId = colorComponentId;
			lpDur_b->currentValue = current_level;
			lpDur_b->targetValue = targetValue;
			zunoExitCritical();
			zuno_CCSupervisionReport(ZUNO_COMMAND_BLOCKED_WORKING, duration, lp, frame_report);
			zunoEnterCritical();
		}
	}
	zunoExitCritical();
}

static int	_set_color(size_t channel, const ZwSwitchColorSetFrame_t *cmd, size_t len, ZUNOCommandPacketReport_t *frame_report) {
	const VgSwitchColorSetVg_t		*vg;
	size_t							count;
	size_t							step;
	size_t							diming;
	size_t							duration;
	size_t							currentValue;
	size_t							targetValue;
	size_t							colorComponentId;
	ZunoColorDuration_t				*lpDur_b;
	ZunoColorDuration_t				*lpDur_e;
	size_t							tempos;

	colorComponentId = ZUNO_CFG_CHANNEL(channel).sub_type;
	count = cmd->properties1 & 0x1F;//Color Component Count (5 bits)
	vg = &cmd->variantgroup[0];
	while (count-- != 0) {
		if ((colorComponentId & (0x1 << vg->colorComponentId)) == 0x0)
			return (ZUNO_COMMAND_BLOCKED_FAILL);
		vg++;
	}
	count = cmd->properties1 & 0x1F;//Color Component Count (5 bits)
	vg = &cmd->variantgroup[0];
	if (len == (sizeof(ZwSwitchColorSetFrame_t) + (count * sizeof(VgSwitchColorSetVg_t))) || (duration = zuno_CCTimerTicksTable7(((uint8_t *)cmd + len - 0x1)[0x0]))== 0x0) {
		if (zuno_CCTimerBasicFindStop(channel) == true) {
			lpDur_b = &_duration[0];
			lpDur_e = &_duration[(sizeof(_duration) / sizeof(ZunoColorDuration_t))];
			tempos = channel + 0x1;
			while (lpDur_b < lpDur_e) {
				if (lpDur_b->channel == tempos)
					lpDur_b->channel = 0x0;
				lpDur_b++;
		}
		}
		while (count-- != 0) {
			zuno_universalSetter2P(channel, vg->colorComponentId, vg->value);
			vg++;
		}
		zunoSendReport(channel + 1);
		return (ZUNO_COMMAND_PROCESSED);
	}
	while (count-- != 0) {
		colorComponentId = vg->colorComponentId;
		targetValue = vg->value;
		currentValue = zuno_universalGetter2P(channel, colorComponentId);
		if (currentValue != targetValue ) {
			if (targetValue > currentValue) {
				step = duration / (targetValue - currentValue);
				diming = 0x0;
			}
			else {
				step = duration  / (currentValue - targetValue);
				diming = 0x1;
			}
			_start_level_set(channel, currentValue, targetValue, colorComponentId, step, diming, duration, frame_report);
		}
		vg++;
	}
	return (ZUNO_COMMAND_PROCESSED);
}

static int _start_level(size_t channel, ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report) {// Prepare the structure for dimming
	ZwSwitchColorStartLevelChange_FRAME_u			*pk;
	size_t											current_level;
	size_t											targetValue;
	size_t											colorComponentId;
	size_t											step;
	size_t											diming;
	size_t											duration;


	pk = (ZwSwitchColorStartLevelChange_FRAME_u *)cmd->cmd;
	colorComponentId = pk->v2.colorComponentId;
	if ((ZUNO_CFG_CHANNEL(channel).sub_type & (0x1 << colorComponentId)) == 0x0)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	if ((pk->v2.properties1 & (1 << 5)) == 0) {// If the level from which you want to start dimming has come, make it current
		current_level = pk->v2.startLevel;
		zuno_universalSetter2P(channel, colorComponentId, current_level);
		zunoSendReport(channel + 1);
	}
	else// Otherwise, get the current
		current_level = zuno_universalGetter2P(channel, colorComponentId);
	if ((pk->v2.properties1 & (1 << 6)) == 0) {// Dimming to up
		targetValue = ZUNO_TIMER_COLOR_MAX_VALUE;
		diming = 0x0;
	}
	else {// Dimming to down
		targetValue = ZUNO_TIMER_COLOR_MIN_VALUE;
		diming = 0x1;
	}
	if (cmd->len == sizeof(ZwSwitchColorStartLevelChangeV2Frame_t)) {
		step = ZUNO_TIMER_SWITCH_DEFAULT_DURATION * (1000) / (ZUNO_TIMER_COLOR_MAX_VALUE + 1);// Depending on the version, set the default step to increase or from the command we will
		duration = ZUNO_TIMER_SWITCH_DEFAULT_DURATION;
	}
	else {
		step = zuno_CCTimerTicksTable7(pk->v3.duration) / (ZUNO_TIMER_COLOR_MAX_VALUE + 1);
		duration = pk->v3.duration;
	}
	if (current_level == targetValue)
		return (ZUNO_COMMAND_PROCESSED);
	if (step == 0x0) {
		zuno_universalSetter2P(channel, colorComponentId, targetValue);
		return (ZUNO_COMMAND_PROCESSED);
	}
	_start_level_set(channel, current_level, targetValue, colorComponentId, step, diming, duration, frame_report);
	return (ZUNO_COMMAND_PROCESSED);
}

static void _stop_level(uint8_t channel, uint8_t colorComponentId) {// Stop Dimming
	ZunoTimerBasic_t								*lp;
	ZunoColorDuration_t								*lpDur_b;
	ZunoColorDuration_t								*lpDur_e;
	size_t											count;

	zunoEnterCritical();
	channel++;
	if ((lp = zuno_CCTimerBasicFind(channel)) != 0x0) {
		lpDur_b = &_duration[0];
		lpDur_e = &_duration[(sizeof(_duration) / sizeof(ZunoColorDuration_t))];
		count = 0x0;
		while (lpDur_b < lpDur_e) {
			if (lpDur_b->channel == channel) {
				if (lpDur_b->colorComponentId == colorComponentId) {
					lpDur_b->channel = 0x0;
					break ;
				}
				else
					count++;
			}
			lpDur_b++;
		}
		if (count == 0x0) {
			while (lpDur_b < lpDur_e) {
				if (lpDur_b->channel == channel) {
					count++;
					break ;
				}
				lpDur_b++;
			}
		}
		if (count == 0x0)
			lp->channel = 0x0;
	}
	zunoExitCritical();
}


int zuno_CCSwitchColorHandler(uint8_t channel, ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	int				rs;

	switch(ZW_CMD)
	{
		case SWITCH_COLOR_SUPPORTED_GET:
			rs =_supported_report(channel, frame_report);
			break ;
		case SWITCH_COLOR_GET:
			_zunoMarkChannelRequested(channel);
			rs = zuno_CCSwitchColorReport(channel, cmd, &frame_report->packet);
			break ;
		case SWITCH_COLOR_SET:
			rs = _set_color(channel, (const ZwSwitchColorSetFrame_t *)cmd->cmd, cmd->len, frame_report);
			break ;
		case SWITCH_COLOR_START_LEVEL_CHANGE:
			rs = _start_level(channel, cmd, frame_report);
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


int zuno_CCSwitchColorReport(uint8_t channel, ZUNOCommandPacket_t *cmd, ZUNOCommandPacket_t *packet) {
	ZwSwitchColorReportFrame_t			*lp;
	uint8_t								colorComponentId;
	uint8_t								mask;
	ZunoColorDuration_t					*lpDur_b;
	ZunoColorDuration_t					*lpDur_e;
	size_t								tempos;
	size_t								currentValue;
	size_t								targetValue;
	
	if (cmd != NULL)
		mask = 1 << (((ZwSwitchColorGetFrame_t *)cmd->cmd)->colorComponentId);
	else
		mask = ZUNO_CFG_CHANNEL(channel).sub_type;//It contains a bitmask of colors
	lp = (ZwSwitchColorReportFrame_t *)&packet->cmd[0x0];
	packet->len = sizeof(lp->v3);
	lp->v3.cmdClass = COMMAND_CLASS_SWITCH_COLOR;
	lp->v3.cmd = SWITCH_COLOR_REPORT;
	colorComponentId = 0;
	tempos = channel + 0x1;
	lpDur_e = &_duration[(sizeof(_duration) / sizeof(ZunoColorDuration_t))];
	while (mask != 0) {//We will pass through all the colors and send a report for each
		if ((mask & 0x01) != 0) {
			lpDur_b = &_duration[0];
			while (lpDur_b < lpDur_e) {
				if (lpDur_b->channel == tempos && lpDur_b->colorComponentId == colorComponentId)
					break ;
				lpDur_b++;
			}
			currentValue = zuno_universalGetter2P(channel, colorComponentId);
			zunoEnterCritical();
			lp->v3.currentValue = currentValue;
			lp->v3.colorComponentId = colorComponentId;
			if (lpDur_b == lpDur_e) {
				lp->v3.targetValue = currentValue;
				lp->v3.duration = 0x0;
			}
			else {
				targetValue = lpDur_b->targetValue;
				currentValue = lpDur_b->currentValue;
				lp->v3.targetValue = targetValue;
				if (targetValue > currentValue)
					targetValue = targetValue - currentValue;
				else
					targetValue = currentValue - targetValue;
				lp->v3.duration = zuno_CCTimerTable8(targetValue * lpDur_b->step);
			}
			zunoExitCritical();
			zunoSendZWPackage(packet);
		}
		colorComponentId++;
		mask >>=  1;
	}
	return (ZUNO_COMMAND_PROCESSED);
}

void zuno_CCSwitchMultilevelTimer(ZunoTimerBasic_t *, ZUNOCommandPacketReport_t *frame_report);
void zuno_CCSwitchColorTimer(ZunoTimerBasic_t *lp, ZUNOCommandPacketReport_t *frame_report) {
	size_t									bMode;
	size_t									channel;
	ssize_t									value;
	size_t									count;
	size_t									tempos;
	size_t									step;
	ZunoColorDuration_t						*lpDur_b;
	ZunoColorDuration_t						*lpDur_e;
	size_t									ticks;

	if ((bMode = lp->bMode) == 0x0)
		return ;
	if ((bMode & ZUNO_TIMER_SWITCH_NO_BASIC) == 0x0)
		return (zuno_CCSwitchMultilevelTimer(lp, frame_report));
	channel = lp->channel;
	lpDur_b = &_duration[0];
	lpDur_e = &_duration[(sizeof(_duration) / sizeof(ZunoColorDuration_t))];
	count = 0x0;
	while (lpDur_b < lpDur_e) {
		if (lpDur_b->channel == channel) {
			ticks = millis();
			count++;
			step = lpDur_b->step;
			if ((tempos = lpDur_b->ticks + step) <= ticks) {
				ticks = ticks - tempos;
				lpDur_b->ticks = tempos + (ticks % step);
				ticks = ticks / step + 0x1;
				value = lpDur_b->currentValue;
				if (lpDur_b->diming == 0x0) {
					value += ticks;
					if (value >= lpDur_b->targetValue) {
						lpDur_b->channel = 0x0;
						count--;
					}
				}
				else {
					value -= ticks;
					if (value <= lpDur_b->targetValue) {
						lpDur_b->channel = 0x0;
						count--;
					}
				}
				lpDur_b->currentValue = value;
				zuno_universalSetter2P(channel - 1, lpDur_b->colorComponentId, value);
				zunoSendReport(channel);
			}
		}
		lpDur_b++;
	}
	if (count == 0x0) {
		lp->channel = 0x0;
		if ((lp->bMode & ZUNO_TIMER_SWITCH_SUPERVISION) != 0x0) {
			__cc_supervision._unpacked = true;
			zuno_CCSupervisionReport(ZUNO_COMMAND_PROCESSED, 0x0, 0x0, frame_report);
		}
	}
}
#endif