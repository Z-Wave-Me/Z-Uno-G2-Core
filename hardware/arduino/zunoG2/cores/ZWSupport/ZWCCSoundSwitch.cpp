#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCSoundSwitch.h"
#include "ZWCCBasic.h"
#include "ZWCCTimer.h"

uint64_t rtcc_micros(void);

__WEAK void zunoSoundSwitchPlay(uint8_t channel, uint8_t toneIdentifier, uint8_t volume, uint16_t duration) {
	(void)channel;
	(void)toneIdentifier;
	(void)volume;
	(void)duration;
}

__WEAK const ZunoSoundSwitchParameterArray_t *zunoSoundSwitchGetParameterArrayUser(size_t channel) {
	return (0x0);
	(void)channel;
}

static const ZunoSoundSwitchParameterArray_t *_soundSwitchGetParameterArray(size_t channel) {
	static const ZunoSoundSwitchParameter_t					switch_parameter[] =
	{
		{
			.name = "Unknown",
			.toneDuration = 10
		}
	};
	static ZunoSoundSwitchParameterPlay_t switch_parameter_play =
	{
		.time_stamp = 0x0,
		.toneIdentifier = 0x0,
		.playCommandToneVolume = 0x0
	};
	static const ZunoSoundSwitchParameterArray_t			switch_parameter_array =
	{
		.parametr = &switch_parameter[0x0],
		.play = &switch_parameter_play,
		.count = ((sizeof(switch_parameter) / sizeof(switch_parameter[0x0])))
	};

	const ZunoSoundSwitchParameterArray_t					*parameter_array;

	if ((parameter_array = zunoSoundSwitchGetParameterArrayUser(channel + 0x1)) != 0x0)
		return (parameter_array);
	return (&switch_parameter_array);
}

static const ZunoSoundSwitchParameter_t *_soundSwitchParameter(const ZunoSoundSwitchParameterArray_t *parameter_array, size_t index) {
	if (index > parameter_array->count || index == 0x0)
		return (0x0);
	return (&parameter_array->parametr[index - 0x1]);
}

static int _soundSwitchTonesNumberReport(size_t channel) {
	const ZunoSoundSwitchParameterArray_t					*parameter_array;
	ZW_SOUND_SWITCH_TONES_NUMBER_REPORT_V2_FRAME			*report;

	report = (ZW_SOUND_SWITCH_TONES_NUMBER_REPORT_V2_FRAME *)&CMD_REPLY_CC;
	// report->cmdClass = COMMAND_CLASS_SOUND_SWITCH; set in - fillOutgoingPacket
	// report->cmd = SOUND_SWITCH_TONES_NUMBER_REPORT; set in - fillOutgoingPacket
	parameter_array = _soundSwitchGetParameterArray(channel);
	report->supportedTones = parameter_array->count;
	CMD_REPLY_LEN = sizeof(report[0x0]);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _soundSwitchToneInfoReport(const ZW_SOUND_SWITCH_TONE_INFO_GET_V2_FRAME *frame, size_t channel) {
	ZwSoundSwitchInfoReportFrame_t						*report;
	const ZunoSoundSwitchParameter_t					*parametr;
	size_t												toneIdentifier;
	size_t												toneDuration;
	size_t												len;

	report = (ZwSoundSwitchInfoReportFrame_t *)&CMD_REPLY_CC;
	// report->cmdClass = COMMAND_CLASS_SOUND_SWITCH; set in - fillOutgoingPacket
	// report->cmd = SOUND_SWITCH_TONE_INFO_REPORT; set in - fillOutgoingPacket
	toneIdentifier = frame->toneIdentifier;
	report->toneIdentifier = toneIdentifier;
	if ((parametr = _soundSwitchParameter(_soundSwitchGetParameterArray(channel), toneIdentifier)) == 0x0) {
		report->toneDuration1 = 0x0;
		report->toneDuration2 = 0x0;
		report->nameLength = 0x0;
		CMD_REPLY_LEN = sizeof(report[0x0]);
		return (ZUNO_COMMAND_ANSWERED);
	}
	toneDuration = parametr->toneDuration;
	report->toneDuration1 = toneDuration >> 0x8;
	report->toneDuration2 = toneDuration;
	len = strlen(parametr->name);
	if (len > (ZUNO_COMMAND_PACKET_CMD_LEN_MAX_OUT - sizeof(report[0x0])))
		len = (ZUNO_COMMAND_PACKET_CMD_LEN_MAX_OUT - sizeof(report[0x0]));
	report->nameLength = len;
	memcpy(&report->name[0x0], parametr->name, len);
	CMD_REPLY_LEN = sizeof(report[0x0]) + len;
	return (ZUNO_COMMAND_ANSWERED);
}

static int _soundSwitchConfigurationReport(size_t channel) {
	ZW_SOUND_SWITCH_CONFIGURATION_REPORT_V2_FRAME						*report;

	report = (ZW_SOUND_SWITCH_CONFIGURATION_REPORT_V2_FRAME *)&CMD_REPLY_CC;
	// report->cmdClass = COMMAND_CLASS_SOUND_SWITCH; set in - fillOutgoingPacket
	// report->cmd = SOUND_SWITCH_CONFIGURATION_REPORT; set in - fillOutgoingPacket
	report->volume = SOUND_SWITCH_DEFAULT_VOLUME(channel);
	report->defaultToneIdentifer = SOUND_SWITCH_DEFAULT_TONE_INDENTIFER(channel);
	CMD_REPLY_LEN = sizeof(report[0x0]);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _soundSwitchConfigurationSet(const ZW_SOUND_SWITCH_CONFIGURATION_SET_V2_FRAME *frame, size_t channel) {
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

	ms_old = parameter_array->play->time_stamp;
	if (ms == 0x0) {
		parameter_array->play->toneIdentifier = 0x0;
		parameter_array->play->playCommandToneVolume = 0x0;
		if (ms_old != 0x0)
			g_sleep_data.latch--;
	}
	else {
		if (ms_old == 0x0)
			g_sleep_data.latch++;
	}
	parameter_array->play->time_stamp = ms;
}

static void _soundSwitchTonePlaySetStop(const ZunoSoundSwitchParameterArray_t *parameter_array, size_t channel) {
	size_t										toneIdentifier;

	if ((toneIdentifier = parameter_array->play->toneIdentifier) == 0x0)
		return ;
	zunoEnterCritical();
	_lock(parameter_array, 0x0);
	zunoExitCritical();
	zunoSoundSwitchPlay(channel + 0x1, toneIdentifier, 0x0, 0x0);//stop
}

static int _soundSwitchTonePlaySetAdd(size_t channel, size_t toneIdentifier, size_t playCommandToneVolume) {
	size_t													toneDuration;
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
		toneIdentifier = 0x0;
	}
	else {
		parameter = _soundSwitchParameter(parameter_array, toneIdentifier);
		if ((toneDuration = parameter->toneDuration) == 0x0)
			time_stamp = 0x0;
		else {
			time_stamp = (rtcc_micros() / 1000) + toneDuration * 1000;
			zunoSoundSwitchPlay(channel + 0x1, toneIdentifier, playCommandToneVolume, toneDuration);//play
		}
	}
	zunoEnterCritical();
	_lock(parameter_array, time_stamp);
	parameter_array->play->toneIdentifier = toneIdentifier;
	parameter_array->play->playCommandToneVolume = playCommandToneVolume;
	zunoExitCritical();
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
	return (_soundSwitchTonePlaySetAdd(channel, toneIdentifier, playCommandToneVolume));
}

int zuno_CCSoundSwitchHandler(uint8_t channel, ZUNOCommandPacket_t *cmd) {
	int								rs;

	_soundSwitchDefault(channel);
	switch (ZW_CMD) {
		case SOUND_SWITCH_TONE_PLAY_GET_V2:
			_zunoMarkChannelRequested(channel);
			rs = zuno_CCSoundSwitchReport(channel, cmd);
			break ;
		case SOUND_SWITCH_TONE_PLAY_SET_V2:
			rs = _soundSwitchTonePlaySet((const ZwSoundSwitchTonePlayFrame_t *)&cmd->cmd[0x0], channel, cmd->len);
			break ;
		case SOUND_SWITCH_CONFIGURATION_SET_V2:
			rs = _soundSwitchConfigurationSet((const ZW_SOUND_SWITCH_CONFIGURATION_SET_V2_FRAME *)&cmd->cmd[0x0], channel);
			break ;
		case SOUND_SWITCH_CONFIGURATION_GET_V2:
			rs = _soundSwitchConfigurationReport(channel);
			break ;
		case SOUND_SWITCH_TONES_NUMBER_GET_V2:
			rs = _soundSwitchTonesNumberReport(channel);
			break ;
		case SOUND_SWITCH_TONE_INFO_GET_V2:
			rs = _soundSwitchToneInfoReport((const ZW_SOUND_SWITCH_TONE_INFO_GET_V2_FRAME *)&cmd->cmd[0x0], channel);
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
	_soundSwitchTonePlaySetAdd(channel, toneIdentifier, playCommandToneVolume);
}

int zuno_CCSoundSwitchReport(uint8_t channel, ZUNOCommandPacket_t *cmd) {
	ZW_SOUND_SWITCH_TONE_PLAY_REPORT_V2_FRAME							*report;
	const ZunoSoundSwitchParameterArray_t								*parameter_array;

	if (cmd != NULL) {
		report = (ZW_SOUND_SWITCH_TONE_PLAY_REPORT_V2_FRAME *)&CMD_REPLY_CC;
		CMD_REPLY_LEN = sizeof(report[0x0]);
	} else {
		report = (ZW_SOUND_SWITCH_TONE_PLAY_REPORT_V2_FRAME *)&CMD_REPORT_CC;
		CMD_REPORT_LEN = sizeof(report[0x0]);
	}
	report->cmdClass = COMMAND_CLASS_SOUND_SWITCH;
	report->cmd = SOUND_SWITCH_TONE_PLAY_REPORT_V2;
	parameter_array = _soundSwitchGetParameterArray(channel);
	report->toneIdentifier = parameter_array->play->toneIdentifier;
	report->playCommandToneVolume = parameter_array->play->playCommandToneVolume;
	if(cmd != NULL)
		zunoSendZWPackage(&g_outgoing_main_packet);
	else
		zunoSendZWPackage(&g_outgoing_report_packet);
	return (ZUNO_COMMAND_PROCESSED);
}

void zuno_CCSoundSwitchTimer(void) {
	size_t													channel;
	uint64_t													time_stamp_current;
	const ZunoSoundSwitchParameterArray_t					*parameter_array;

	channel = 0x0;
	time_stamp_current = (rtcc_micros() / 1000);
	while (channel < ZUNO_CFG_CHANNEL_COUNT)
	{
		if (ZUNO_CFG_CHANNEL(channel).type == ZUNO_SOUND_SWITCH_CHANNEL_NUMBER) {
			parameter_array = _soundSwitchGetParameterArray(channel);
			if (parameter_array->play->toneIdentifier != 0x0 && time_stamp_current >= parameter_array->play->time_stamp) {
				zunoSendReport(channel + 0x1);
				_soundSwitchTonePlaySetStop(parameter_array, channel);
			}
		}
		channel++;
	}
}

int zuno_CCSoundSwitchBasicSet(size_t channel, size_t toneIdentifier) {
	return (_soundSwitchTonePlaySetAdd(channel, toneIdentifier, SOUND_SWITCH_DEFAULT_VOLUME(channel)));
}

int zuno_CCSoundSwitchBasicGet(size_t channel, ZwBasicReportV2Frame_t *report) {
	const ZunoSoundSwitchParameterArray_t								*parameter_array;
	size_t																toneIdentifier;
	size_t																duration;
	uint64_t															time_stamp_current;
	uint64_t															time_stamp_save;

	parameter_array = _soundSwitchGetParameterArray(channel);
	toneIdentifier = parameter_array->play->toneIdentifier;
	report->currentValue = toneIdentifier;
	report->targetValue = toneIdentifier;
	if ((time_stamp_save = parameter_array->play->time_stamp) != 0x0) {
		time_stamp_current = (rtcc_micros() / 1000);
		if (time_stamp_save > time_stamp_current)
			duration = zuno_CCTimerTable8(time_stamp_save - time_stamp_current);
		else
			duration = 0x0;
	}
	else
		duration = 0x0;
	report->duration = duration;
	return (ZUNO_COMMAND_ANSWERED);
}
