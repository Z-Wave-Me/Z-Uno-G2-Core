#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCSoundSwitch.h"
#include "ZWCCBasic.h"
#include "ZWCCTimer.h"
#include "ZWCCSuperVision.h"

typedef enum								SoundSwitchPlayTimerStatus_e
{
	SoundSwitchPlayTimerStatusIdle,
	SoundSwitchPlayTimerStatusOn,
	SoundSwitchPlayTimerStatusOff
}											SoundSwitchPlayTimerStatus_t;

uint64_t rtcc_micros(void);

__WEAK void zunoSoundSwitchPlay(uint8_t channel, uint8_t volume, size_t freq) {
	(void)channel;
	(void)volume;
	(void)freq;
}

__WEAK void zunoSoundSwitchStop(uint8_t channel) {
	(void)channel;
}

extern const ZunoSoundSwitchParameterArray_t __start__switch_cc_array_list;
extern const ZunoSoundSwitchParameterArray_t __stop__switch_cc_array_list;

ZUNO_SETUP_SOUND_SWITCH_TONE_DURATION(UNKNOWN,
	ZUNO_SETUP_SOUND_SWITCH_TONE_DURATION_SET(10000, 0)
);

ZUNO_SETUP_SOUND_SWITCH(255,
	ZUNO_SETUP_SOUND_SWITCH_TONE("Unknown", UNKNOWN)
);

__WEAK const ZunoSoundSwitchParameterArray_t *zunoSoundSwitchGetParameterArrayUser(size_t channel) {
	const ZunoSoundSwitchParameterArray_t			*iter;

	channel++;
	iter = &__start__switch_cc_array_list;
	while (iter < &__stop__switch_cc_array_list) {
		if (iter->channel == channel)
			return (iter);
		iter++;
	}
	return (NULL);
}

static const ZunoSoundSwitchParameterArray_t *_soundSwitchGetParameterArray(size_t channel) {
	const ZunoSoundSwitchParameterArray_t			*iter;

	iter = zunoSoundSwitchGetParameterArrayUser(channel);
	if (iter != NULL)
		return (iter);
	return (&_switch_cc_parameter_array_255);
}

static const ZunoSoundSwitchParameter_t *_soundSwitchParameter(const ZunoSoundSwitchParameterArray_t *parameter_array, size_t index) {
	if (index > parameter_array->count || index == 0x0)
		return (0x0);
	return (&parameter_array->parametr[index - 0x1]);
}

static int _soundSwitchTonesNumberReport(size_t channel, ZUNOCommandPacketReport_t *frame_report) {
	const ZunoSoundSwitchParameterArray_t					*parameter_array;
	ZW_SOUND_SWITCH_TONES_NUMBER_REPORT_V2_FRAME			*report;

	report = (ZW_SOUND_SWITCH_TONES_NUMBER_REPORT_V2_FRAME *)frame_report->packet.cmd;
	// report->cmdClass = COMMAND_CLASS_SOUND_SWITCH; set in - fillOutgoingPacket
	// report->cmd = SOUND_SWITCH_TONES_NUMBER_REPORT; set in - fillOutgoingPacket
	parameter_array = _soundSwitchGetParameterArray(channel);
	report->supportedTones = parameter_array->count;
	frame_report->packet.len = sizeof(report[0x0]);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _soundSwitchToneInfoReport(const ZW_SOUND_SWITCH_TONE_INFO_GET_V2_FRAME *frame, size_t channel, ZUNOCommandPacketReport_t *frame_report) {
	ZwSoundSwitchInfoReportFrame_t						*report;
	const ZunoSoundSwitchParameter_t					*parametr;
	size_t												toneIdentifier;
	size_t												ms_duration;
	size_t												len;

	report = (ZwSoundSwitchInfoReportFrame_t *)frame_report->packet.cmd;
	// report->cmdClass = COMMAND_CLASS_SOUND_SWITCH; set in - fillOutgoingPacket
	// report->cmd = SOUND_SWITCH_TONE_INFO_REPORT; set in - fillOutgoingPacket
	toneIdentifier = frame->toneIdentifier;
	report->toneIdentifier = toneIdentifier;
	if ((parametr = _soundSwitchParameter(_soundSwitchGetParameterArray(channel), toneIdentifier)) == 0x0) {
		report->toneDuration1 = 0x0;
		report->toneDuration2 = 0x0;
		report->nameLength = 0x0;
		frame_report->packet.len = sizeof(report[0x0]);
		return (ZUNO_COMMAND_ANSWERED);
	}
	ms_duration = parametr->ms_duration;
	if ((ms_duration % 1000) != 0x0)
		ms_duration = ms_duration + 1000;
	ms_duration = ms_duration / 1000;
	report->toneDuration1 = ms_duration >> 0x8;
	report->toneDuration2 = ms_duration;
	len = strlen(parametr->name);
	if (len > (ZUNO_COMMAND_PACKET_CMD_LEN_MAX_OUT - sizeof(report[0x0])))
		len = (ZUNO_COMMAND_PACKET_CMD_LEN_MAX_OUT - sizeof(report[0x0]));
	report->nameLength = len;
	memcpy(&report->name[0x0], parametr->name, len);
	frame_report->packet.len = sizeof(report[0x0]) + len;
	return (ZUNO_COMMAND_ANSWERED);
}

static int _soundSwitchConfigurationReport(size_t channel, ZUNOCommandPacketReport_t *frame_report) {
	ZW_SOUND_SWITCH_CONFIGURATION_REPORT_V2_FRAME						*report;

	report = (ZW_SOUND_SWITCH_CONFIGURATION_REPORT_V2_FRAME *)frame_report->packet.cmd;
	report->cmdClass = COMMAND_CLASS_SOUND_SWITCH;
	report->cmd = SOUND_SWITCH_CONFIGURATION_REPORT;
	report->volume = SOUND_SWITCH_DEFAULT_VOLUME(channel);
	report->defaultToneIdentifer = SOUND_SWITCH_DEFAULT_TONE_INDENTIFER(channel);
	frame_report->packet.len = sizeof(report[0x0]);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _soundSwitchConfigurationSet(const ZW_SOUND_SWITCH_CONFIGURATION_SET_V2_FRAME *frame, size_t channel) {
	ZUNOCommandPacketReport_t											frame_report;
	size_t																defaultToneIdentifier;
	size_t																volume;

	if ((volume = frame->volume) == 0xFF)
		volume = SOUND_SWITCH_DEFAULT_VOLUME_SAVE(channel);
	if (volume > SOUND_SWITCH_DEFAULT_VOLUME_VALUE_MAX)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	if ((defaultToneIdentifier = frame->defaultToneIdentifier) != 0x0) {
		if (_soundSwitchParameter(_soundSwitchGetParameterArray(channel), defaultToneIdentifier) == 0x0)
			return (ZUNO_COMMAND_BLOCKED_FAILL);
		SOUND_SWITCH_DEFAULT_TONE_INDENTIFER(channel) = defaultToneIdentifier;
	}
	SOUND_SWITCH_DEFAULT_VOLUME(channel) = volume;
	if (volume != 0x0)
		SOUND_SWITCH_DEFAULT_VOLUME_SAVE(channel) = volume;
	fillOutgoingReportPacketAsyncReport(&frame_report, channel);
	_soundSwitchConfigurationReport(channel, &frame_report);
	zunoSendZWPackage(&frame_report.packet);
	return (ZUNO_COMMAND_PROCESSED);
}

void _soundSwitchDefault(size_t channel) {
	size_t									volume;

	if (SOUND_SWITCH_DEFAULT_TEST(channel) == true)
		return ;
	SOUND_SWITCH_DEFAULT_TEST(channel) = true;
	if ((volume = SOUND_SWITCH_DEFAULT_VOLUME(channel)) > SOUND_SWITCH_DEFAULT_VOLUME_VALUE_MAX)
		volume = SOUND_SWITCH_DEFAULT_VOLUME_VALUE;
	SOUND_SWITCH_DEFAULT_VOLUME(channel) = volume;
	SOUND_SWITCH_DEFAULT_VOLUME_SAVE(channel) = volume;
	if (_soundSwitchParameter(_soundSwitchGetParameterArray(channel), SOUND_SWITCH_DEFAULT_TONE_INDENTIFER(channel)) == 0x0)
		SOUND_SWITCH_DEFAULT_TONE_INDENTIFER(channel) = SOUND_SWITCH_DEFAULT_TONE_INDENTIFER_VALUE;
}

static void _lock(const ZunoSoundSwitchParameterArray_t *parameter_array, uint64_t ms) {
	uint64_t								ms_old;
	ZunoSoundSwitchParameterPlay_t			*play;

	play = parameter_array->play;
	ms_old = play->time_stamp;
	if (ms == 0x0) {
		play->toneIdentifier = 0x0;
		play->playCommandToneVolume = 0x0;
		if (ms_old != 0x0)
			g_sleep_data.latch--;
	}
	else {
		if (ms_old == 0x0)
			g_sleep_data.latch++;
	}
	play->time_stamp = ms;
}

static void _soundSwitchTonePlaySetStop(const ZunoSoundSwitchParameterArray_t *parameter_array, size_t channel) {
	size_t										toneIdentifier;

	if ((toneIdentifier = parameter_array->play->toneIdentifier) == 0x0)
		return ;
	zunoEnterCritical();
	_lock(parameter_array, 0x0);
	zunoExitCritical();
	zunoSoundSwitchStop(channel + 0x1);
}

static int _soundSwitchTonePlaySetAdd(size_t channel, size_t toneIdentifier, size_t playCommandToneVolume, uint8_t bReport) {
	size_t													ms_duration;
	uint64_t												time_stamp;
	const ZunoSoundSwitchParameterArray_t					*parameter_array;
	const ZunoSoundSwitchParameter_t						*parameter;
	int														result;

	parameter_array = _soundSwitchGetParameterArray(channel);
	result = ZUNO_COMMAND_PROCESSED;
	if (toneIdentifier == 0x0)//stop any
		playCommandToneVolume = 0x0;
	else {
		if (_soundSwitchParameter(parameter_array, toneIdentifier) == 0x0) {
			if (toneIdentifier != 0xFF)
				result = ZUNO_COMMAND_BLOCKED_FAILL;
			toneIdentifier = SOUND_SWITCH_DEFAULT_TONE_INDENTIFER(channel);
		}
		if (playCommandToneVolume == 0x0)
			playCommandToneVolume = SOUND_SWITCH_DEFAULT_VOLUME(channel);
		else if (playCommandToneVolume == 0xFF) {
			if ((playCommandToneVolume = parameter_array->play->playCommandToneVolume) == 0x0)
				playCommandToneVolume = SOUND_SWITCH_DEFAULT_VOLUME(channel);
			if (playCommandToneVolume == 0x0)
				playCommandToneVolume = SOUND_SWITCH_DEFAULT_VOLUME_SAVE(channel);
		}
	}
	_soundSwitchTonePlaySetStop(parameter_array, channel);
	if (playCommandToneVolume == 0x0) {//stop
		time_stamp = 0x0;
	}
	else {
		parameter = _soundSwitchParameter(parameter_array, toneIdentifier);
		if ((ms_duration = parameter->ms_duration) == 0x0) {
			time_stamp = 0x0;
		}
		else {
			time_stamp = (rtcc_micros() / 1000) + parameter->duration->play_ms;
		}
	}
	if (result == ZUNO_COMMAND_PROCESSED)
		zunoSendReport(channel + 1);
	if (time_stamp == 0x0) {
		return (result);
	}
	zunoSoundSwitchPlay(channel + 0x1, playCommandToneVolume, parameter->duration->freq);
	zunoEnterCritical();
	_lock(parameter_array, time_stamp);
	parameter_array->play->parameter = parameter;
	parameter_array->play->index = 0x0;
	parameter_array->play->status = SoundSwitchPlayTimerStatusOff;
	parameter_array->play->toneIdentifier = toneIdentifier;
	parameter_array->play->playCommandToneVolume = playCommandToneVolume;
	parameter_array->play->bReport = bReport;
	zunoExitCritical();
	if (result == ZUNO_COMMAND_PROCESSED)
		zunoSendReport(channel + 1);
	return (result);
}

static int _soundSwitchTonePlaySet(const ZwSoundSwitchTonePlayFrame_t *frame, size_t channel, size_t len) {
	size_t													toneIdentifier;
	size_t													playCommandToneVolume;

	switch (len) {
		case sizeof(frame->v1):
			playCommandToneVolume = SOUND_SWITCH_DEFAULT_VOLUME(channel);
			toneIdentifier = frame->v1.toneIdentifier;
			break ;
		case sizeof(frame->v2):
			playCommandToneVolume = frame->v2.playCommandToneVolume;
			toneIdentifier = frame->v2.toneIdentifier;
			break ;
		default:
			return (ZUNO_COMMAND_BLOCKED_FAILL);
			break ;
	}
	return (_soundSwitchTonePlaySetAdd(channel, toneIdentifier, playCommandToneVolume, true));
}

int zuno_CCSoundSwitchHandler(uint8_t channel, ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	int								rs;

	_soundSwitchDefault(channel);
	switch (ZW_CMD) {
		case SOUND_SWITCH_TONE_PLAY_GET_V2:
			_zunoMarkChannelRequested(channel);
			rs = zuno_CCSoundSwitchReport(channel, &frame_report->packet);
			break ;
		case SOUND_SWITCH_TONE_PLAY_SET_V2:
			rs = _soundSwitchTonePlaySet((const ZwSoundSwitchTonePlayFrame_t *)&cmd->cmd[0x0], channel, cmd->len);
			break ;
		case SOUND_SWITCH_CONFIGURATION_SET_V2:
			rs = _soundSwitchConfigurationSet((const ZW_SOUND_SWITCH_CONFIGURATION_SET_V2_FRAME *)&cmd->cmd[0x0], channel);
			break ;
		case SOUND_SWITCH_CONFIGURATION_GET_V2:
			rs = _soundSwitchConfigurationReport(channel, frame_report);
			break ;
		case SOUND_SWITCH_TONES_NUMBER_GET_V2:
			rs = _soundSwitchTonesNumberReport(channel, frame_report);
			break ;
		case SOUND_SWITCH_TONE_INFO_GET_V2:
			rs = _soundSwitchToneInfoReport((const ZW_SOUND_SWITCH_TONE_INFO_GET_V2_FRAME *)&cmd->cmd[0x0], channel, frame_report);
			break ;
		default:
			rs = ZUNO_COMMAND_BLOCKED_NO_SUPPORT;
			break ;
	}
	return (rs);
}

void zuno_CCSoundSwitchPlay(uint8_t channel, uint8_t toneIdentifier, uint8_t playCommandToneVolume) {
	if (channel == 0x0)
		return ;
	channel--;
	if (channel >= ZUNO_CFG_CHANNEL_COUNT)
		return ;
	if (ZUNO_CFG_CHANNEL(channel).type != ZUNO_SOUND_SWITCH_CHANNEL_NUMBER)
		return ;
	_soundSwitchTonePlaySetAdd(channel, toneIdentifier, playCommandToneVolume, false);
}

int zuno_CCSoundSwitchReport(uint8_t channel, ZUNOCommandPacket_t *packet) {
	ZW_SOUND_SWITCH_TONE_PLAY_REPORT_V2_FRAME							*report;
	const ZunoSoundSwitchParameterArray_t								*parameter_array;

	report = (ZW_SOUND_SWITCH_TONE_PLAY_REPORT_V2_FRAME *)&packet->cmd[0x0];
	report->cmdClass = COMMAND_CLASS_SOUND_SWITCH;
	report->cmd = SOUND_SWITCH_TONE_PLAY_REPORT_V2;
	parameter_array = _soundSwitchGetParameterArray(channel);
	report->toneIdentifier = parameter_array->play->toneIdentifier;
	report->playCommandToneVolume = parameter_array->play->playCommandToneVolume;
	packet->len = sizeof(report[0x0]);
	return (ZUNO_COMMAND_ANSWERED);
}

void zuno_CCSoundSwitchTimer(void) {
	size_t													channel;
	uint64_t												time_stamp_current;
	const ZunoSoundSwitchParameterArray_t					*parameter_array;
	ZunoSoundSwitchParameterPlay_t							*play;
	size_t													index;
	size_t													status;
	size_t													count;
	const ZunoSoundSwitchParameterDuration_t				*duration;
	size_t													ms;

	channel = 0x0;
	time_stamp_current = (rtcc_micros() / 1000);
	while (channel < ZUNO_CFG_CHANNEL_COUNT)
	{
		if (ZUNO_CFG_CHANNEL(channel).type == ZUNO_SOUND_SWITCH_CHANNEL_NUMBER) {
			parameter_array = _soundSwitchGetParameterArray(channel);
			play = parameter_array->play;
			if (play->toneIdentifier != 0x0 && time_stamp_current >= play->time_stamp) {
				index = play->index;
				count = play->parameter->count;
				status = play->status;
				ms = 0x0;
				duration = play->parameter->duration;
				while (index < count) {
					switch (status) {
						case SoundSwitchPlayTimerStatusOn:
								ms = duration[index].play_ms;
							status = SoundSwitchPlayTimerStatusOff;
							break ;
						case SoundSwitchPlayTimerStatusOff:
							ms = duration[index].pause_ms;
							status = SoundSwitchPlayTimerStatusOn;
							index++;
							break ;
						default:
							ms = 0x0;
							break ;
					}
					if (ms != 0x0)
						break ;
				}
				if (ms == 0x0) {
					if (play->bReport == true)
						zunoSendReport(channel + 0x1);
					_soundSwitchTonePlaySetStop(parameter_array, channel);
				}
				else {
					play->index = index;
					play->status = status;
					play->time_stamp = (rtcc_micros() / 1000) + ms;
					switch (status) {
						case SoundSwitchPlayTimerStatusOn:
							zunoSoundSwitchStop(channel + 0x1);
							break ;
						case SoundSwitchPlayTimerStatusOff:
							zunoSoundSwitchPlay(channel + 0x1, play->playCommandToneVolume, duration[index].freq);
							break ;
					}
				}
			}
		}
		channel++;
	}
}

int zuno_CCSoundSwitchBasicSet(size_t channel, size_t toneIdentifier) {
	return (_soundSwitchTonePlaySetAdd(channel, toneIdentifier, SOUND_SWITCH_DEFAULT_VOLUME(channel), true));
}

int zuno_CCSoundSwitchBasicGet(size_t channel, ZwBasicReportV2Frame_t *report) {
	const ZunoSoundSwitchParameterArray_t								*parameter_array;
	ZunoSoundSwitchParameterPlay_t										*play;
	const ZunoSoundSwitchParameterDuration_t							*lp_duration;
	size_t																toneIdentifier;
	size_t																duration;
	uint64_t															time_stamp_current;
	uint64_t															time_stamp_save;
	size_t																index;
	size_t																count;

	parameter_array = _soundSwitchGetParameterArray(channel);
	play = parameter_array->play;
	zunoEnterCritical();
	toneIdentifier = play->toneIdentifier;
	report->currentValue = toneIdentifier;
	report->targetValue = toneIdentifier;
	time_stamp_save = play->time_stamp;
	if (toneIdentifier != 0x0) {
		index = play->index;
		count = play->parameter->count;
		lp_duration = play->parameter->duration;
		while (index < count) {
			time_stamp_save = time_stamp_save + lp_duration[index].pause_ms + lp_duration[index].play_ms;
			index++;
		}
	}
	zunoExitCritical();
	time_stamp_current = (rtcc_micros() / 1000);
	if (time_stamp_save > time_stamp_current)
		duration = zuno_CCTimerTable8(time_stamp_save - time_stamp_current);
	else
		duration = 0x0;
	report->duration = duration;
	return (ZUNO_COMMAND_ANSWERED);
}
