#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCSoundSwitch.h"
#include "ZWCCBasic.h"
#include "ZWCCTimer.h"
#include "ZWCCSuperVision.h"
#include "zuno_channel_handlers.h"
uint64_t rtcc_micros(void);

#if defined(WITH_CC_SOUND_SWITCH)

void __zuno_CCSoundSwitchTimerStop(uint8_t channel) {
	zunoTimerTreadDimingStop(zunoTimerTreadDimingTypeSoundSwitch, channel);
}

void __zuno_CCSoundSwitchGetValues(uint8_t channel, uint8_t *current_value, uint8_t *duration_table_8, uint8_t *target_value) {
	zunoTimerTreadDimingGetValues(zunoTimerTreadDimingTypeSoundSwitch, channel, 0x0, duration_table_8, target_value);
	current_value[0x0] = target_value[0x0];
}

static const zuno_handler_soundswitch_t *_get_handler(size_t channel) {
	const zuno_handler_soundswitch_t			*iter;
	uint8_t										type;

	iter = (const zuno_handler_soundswitch_t *)zunoExtractChannelHandlerPtr(channel, &type);
	if (iter != NULL && type == CHANNEL_HANDLER_SOUNDSWITCH)
		return (iter);
	return (NULL);
}


static void _zunoSoundSwitchPlay(uint8_t channel, uint8_t toneIdentifier, uint8_t volume) {
	const zuno_handler_soundswitch_t				*handler;
	void											(*play)(uint8_t melody_id, uint8_t volume);

	handler = _get_handler(channel);
	if (handler == NULL)
		return ;
	play = (void(*)(uint8_t, uint8_t))handler->play;
	play(toneIdentifier, volume);
}

void __zunoSoundSwitchStop(uint8_t channel, uint8_t toneIdentifier) {
	const zuno_handler_soundswitch_t				*handler;
	void											(*stop)(uint8_t melody_id);

	handler = _get_handler(channel);
	if (handler == NULL)
		return ;
	stop = (void(*)(uint8_t))handler->stop;
	stop(toneIdentifier);
}


static const ZunoSoundSwitchParameterArray_t * _switch_cc_parameter_array_255(void) {
	static const ZunoSoundSwitchParameter_t									switch_cc_parameter[]= {{ .name = "Unknown", .sec_duration = 10}, };
	static const ZunoSoundSwitchParameterArray_t							&switch_cc_parameter_array = {
		.parametr = &switch_cc_parameter[0x0],
		.count = ((sizeof(switch_cc_parameter) / sizeof(switch_cc_parameter[0x0])))
	};
	return (&switch_cc_parameter_array);
};

static const ZunoSoundSwitchParameterArray_t *_soundSwitchGetParameterArray(size_t channel) {
	const zuno_handler_soundswitch_t				*handler;
	const ZunoSoundSwitchParameterArray_t			*(*tone_info)(void);

	handler = _get_handler(channel);
	if (handler == NULL)
		return (_switch_cc_parameter_array_255());
	tone_info = (const ZunoSoundSwitchParameterArray_t *(*)(void))handler->tone_info;
	return (tone_info());
}

static const ZunoSoundSwitchParameter_t *_soundSwitchParameter(const ZunoSoundSwitchParameterArray_t *parameter_array, size_t index) {
	if (index > parameter_array->count || index == 0x0)
		return (0x0);
	return (&parameter_array->parametr[index - 0x1]);
}

void zunoSoundSwitchSaveInit(void) {
	uint8_t					buffer[EEPROM_SWITCH_SOUND_SAVE_SIZE];
	uint8_t					channel;
	uint8_t					volume;
	uint8_t					toneIdentifier;
	ZwSoundSwitchSave_t		*switch_save;

	channel = 0x0;
	while (channel < ZUNO_CFG_CHANNEL_COUNT) {
		if (ZUNO_CFG_CHANNEL(channel).type == ZUNO_SOUND_SWITCH_CHANNEL_NUMBER) {
			switch_save = (ZwSoundSwitchSave_t *)&buffer[channel * sizeof(switch_save[0x0])];
			if ((volume = SOUND_SWITCH_DEFAULT_VOLUME(channel)) > SOUND_SWITCH_DEFAULT_VOLUME_VALUE_MAX)
				volume = SOUND_SWITCH_DEFAULT_VOLUME_VALUE;
			switch_save->volume = volume;
			switch_save->volume_save = volume;
			toneIdentifier = SOUND_SWITCH_DEFAULT_TONE_INDENTIFER(channel);
			if (_soundSwitchParameter(_soundSwitchGetParameterArray(channel), toneIdentifier) == 0x0)
				toneIdentifier = SOUND_SWITCH_DEFAULT_TONE_INDENTIFER_VALUE;
			switch_save->toneIdentifier = toneIdentifier;
		}
		channel++;
	}
	zunoEEPROMWrite(EEPROM_SWITCH_SOUND_SAVE_ADDR, sizeof(buffer), &buffer[0x0]);
}

void zunoSoundSwitchSaveSet(uint8_t channel, const ZwSoundSwitchSave_t *switch_save) {
	zunoEEPROMWrite(EEPROM_SWITCH_SOUND_SAVE_ADDR + (channel * sizeof(switch_save[0x0])), sizeof(switch_save[0x0]), (byte *)switch_save);
}


void zunoSoundSwitchSaveGet(uint8_t channel, ZwSoundSwitchSave_t *switch_save) {
	zunoEEPROMRead(EEPROM_SWITCH_SOUND_SAVE_ADDR + (channel * sizeof(switch_save[0x0])), sizeof(switch_save[0x0]), (byte *)switch_save);
	if (switch_save->volume > SOUND_SWITCH_DEFAULT_VOLUME_VALUE_MAX)
		switch_save->volume = SOUND_SWITCH_DEFAULT_VOLUME_VALUE_MAX;
	if (switch_save->volume_save > SOUND_SWITCH_DEFAULT_VOLUME_VALUE_MAX)
		switch_save->volume_save = SOUND_SWITCH_DEFAULT_VOLUME_VALUE_MAX;
	if (_soundSwitchParameter(_soundSwitchGetParameterArray(channel), switch_save->toneIdentifier) == 0x0)
		switch_save->toneIdentifier = SOUND_SWITCH_DEFAULT_TONE_INDENTIFER_VALUE;
}


static int _soundSwitchTonesNumberReport(size_t channel, ZUNOCommandPacketReport_t *frame_report) {
	const ZunoSoundSwitchParameterArray_t					*parameter_array;
	ZW_SOUND_SWITCH_TONES_NUMBER_REPORT_V2_FRAME			*report;

	report = (ZW_SOUND_SWITCH_TONES_NUMBER_REPORT_V2_FRAME *)frame_report->info.packet.cmd;
	// report->cmdClass = COMMAND_CLASS_SOUND_SWITCH; set in - fillOutgoingPacket
	// report->cmd = SOUND_SWITCH_TONES_NUMBER_REPORT; set in - fillOutgoingPacket
	parameter_array = _soundSwitchGetParameterArray(channel);
	report->supportedTones = parameter_array->count;
	frame_report->info.packet.len = sizeof(report[0x0]);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _soundSwitchToneInfoReport(const ZW_SOUND_SWITCH_TONE_INFO_GET_V2_FRAME *frame, size_t channel, ZUNOCommandPacketReport_t *frame_report) {
	ZwSoundSwitchInfoReportFrame_t						*report;
	const ZunoSoundSwitchParameter_t					*parametr;
	size_t												toneIdentifier;
	uint16_t											sec_duration;
	size_t												len;

	report = (ZwSoundSwitchInfoReportFrame_t *)frame_report->info.packet.cmd;
	// report->cmdClass = COMMAND_CLASS_SOUND_SWITCH; set in - fillOutgoingPacket
	// report->cmd = SOUND_SWITCH_TONE_INFO_REPORT; set in - fillOutgoingPacket
	toneIdentifier = frame->toneIdentifier;
	report->toneIdentifier = toneIdentifier;
	if ((parametr = _soundSwitchParameter(_soundSwitchGetParameterArray(channel), toneIdentifier)) == 0x0) {
		report->toneDuration1 = 0x0;
		report->toneDuration2 = 0x0;
		report->nameLength = 0x0;
		frame_report->info.packet.len = sizeof(report[0x0]);
		return (ZUNO_COMMAND_ANSWERED);
	}
	sec_duration = parametr->sec_duration;
	report->toneDuration1 = sec_duration >> 0x8;
	report->toneDuration2 = sec_duration;
	len = strlen(parametr->name);
	if (len > (ZUNO_COMMAND_PACKET_CMD_OUT_MAX_RECOMMENDED - sizeof(report[0x0])))
		len = (ZUNO_COMMAND_PACKET_CMD_OUT_MAX_RECOMMENDED - sizeof(report[0x0]));
	report->nameLength = len;
	memcpy(&report->name[0x0], parametr->name, len);
	frame_report->info.packet.len = sizeof(report[0x0]) + len;
	return (ZUNO_COMMAND_ANSWERED);
}

static int _soundSwitchConfigurationReport(size_t channel, ZUNOCommandPacketReport_t *frame_report) {
	ZW_SOUND_SWITCH_CONFIGURATION_REPORT_V2_FRAME						*report;
	ZwSoundSwitchSave_t													switch_save;

	zunoSoundSwitchSaveGet(channel, &switch_save);
	report = (ZW_SOUND_SWITCH_CONFIGURATION_REPORT_V2_FRAME *)frame_report->info.packet.cmd;
	report->cmdClass = COMMAND_CLASS_SOUND_SWITCH;
	report->cmd = SOUND_SWITCH_CONFIGURATION_REPORT;
	report->volume = switch_save.volume;
	report->defaultToneIdentifer = switch_save.toneIdentifier;
	frame_report->info.packet.len = sizeof(report[0x0]);
	return (ZUNO_COMMAND_ANSWERED);
}

static void _config_report_asyn(size_t channel) {
	ZUNOCommandPacketReport_t											frame_report;

	fillOutgoingReportPacketAsync(&frame_report, ZUNO_CFG_CHANNEL(channel).zw_channel);
	_soundSwitchConfigurationReport(channel, &frame_report);
	zunoSendZWPacket(&frame_report.info);
}

static int _soundSwitchConfigurationSet(const ZW_SOUND_SWITCH_CONFIGURATION_SET_V2_FRAME *frame, size_t channel) {
	size_t																defaultToneIdentifier;
	size_t																volume;
	ZwSoundSwitchSave_t													switch_save;

	zunoSoundSwitchSaveGet(channel, &switch_save);
	if ((volume = frame->volume) == 0xFF)
		volume = switch_save.volume_save;
	if (volume > SOUND_SWITCH_DEFAULT_VOLUME_VALUE_MAX)
		return (ZUNO_COMMAND_BLOCKED_FAIL);
	if ((defaultToneIdentifier = frame->defaultToneIdentifier) != 0x0) {
		if (_soundSwitchParameter(_soundSwitchGetParameterArray(channel), defaultToneIdentifier) == 0x0)
			return (ZUNO_COMMAND_BLOCKED_FAIL);
		switch_save.toneIdentifier = defaultToneIdentifier;
	}
	switch_save.volume = volume;
	if (volume != 0x0)
		switch_save.volume_save = volume;
	zunoSoundSwitchSaveSet(channel, &switch_save);
	_config_report_asyn(channel);
	return (ZUNO_COMMAND_PROCESSED);
}

static int _soundSwitchTonePlaySetAdd(size_t channel, size_t toneIdentifier, size_t playCommandToneVolume, const ZUNOCommandHandlerOption_t *options) {
	uint16_t												sec_duration;
	uint64_t												time_stamp;
	const ZunoSoundSwitchParameterArray_t					*parameter_array;
	const ZunoSoundSwitchParameter_t						*parameter;
	int														result;
	ZwSoundSwitchSave_t										switch_save;
	zunoTimerTreadDiming_t									*parameter_diming;
	zunoTimerTreadDiming_t									list;
	uint8_t													playCommandToneVolume_last;

	if (zunoTimerTreadDimingGetInfo(zunoTimerTreadDimingTypeSoundSwitch, channel, &list) == true) {
		__zuno_BasicUniversalTimerStop(channel);
		__zunoSoundSwitchStop(channel, toneIdentifier);
		playCommandToneVolume_last = list.current_value;
	}
	else
		playCommandToneVolume_last = 0x0;
	parameter_array = _soundSwitchGetParameterArray(channel);
	result = ZUNO_COMMAND_PROCESSED;
	if (toneIdentifier == 0x0)//stop any
		playCommandToneVolume = 0x0;
	else {
		zunoSoundSwitchSaveGet(channel, &switch_save);
		if (_soundSwitchParameter(parameter_array, toneIdentifier) == 0x0) {
			if (toneIdentifier != 0xFF)
				result = ZUNO_COMMAND_BLOCKED_FAIL;
			toneIdentifier = switch_save.toneIdentifier;
		}
		if (playCommandToneVolume == 0x0)
			playCommandToneVolume = switch_save.volume;
		else if (playCommandToneVolume == 0xFF) {
			if ((playCommandToneVolume = playCommandToneVolume_last) == 0x0)
				playCommandToneVolume = switch_save.volume;
			if (playCommandToneVolume == 0x0)
				playCommandToneVolume = switch_save.volume_save;
		}
	}
	if (playCommandToneVolume == 0x0) {//stop
		time_stamp = 0x0;
	}
	else {
		parameter = _soundSwitchParameter(parameter_array, toneIdentifier);
		if ((sec_duration = parameter->sec_duration) == 0x0) {
			time_stamp = 0x0;
		}
		else {
			time_stamp = (rtcc_micros() / 1000) + parameter->sec_duration * 1000;
		}
	}
	if (result == ZUNO_COMMAND_PROCESSED)
		zunoSendReport(channel + 1);
	if (time_stamp == 0x0) {
		return (result);
	}
	if ((parameter_diming = zunoTimerTreadDimingCreate()) == NULL)
		return (ZUNO_COMMAND_BLOCKED_FAIL);
	parameter_diming->flag = 0x0;
	parameter_diming->channel = channel;
	parameter_diming->ticks_end = time_stamp;
	parameter_diming->current_value = playCommandToneVolume;
	parameter_diming->target_value = toneIdentifier;
	parameter_diming->type = zunoTimerTreadDimingTypeSoundSwitch;
	zunoTimerTreadDimingAdd(parameter_diming, options);
	_zunoSoundSwitchPlay(channel, toneIdentifier, playCommandToneVolume);
	return (result);
}

static int _soundSwitchTonePlaySet(const ZwSoundSwitchTonePlayFrame_t *frame, size_t channel, size_t len, const ZUNOCommandHandlerOption_t *options) {
	size_t													toneIdentifier;
	size_t													playCommandToneVolume;
	ZwSoundSwitchSave_t										switch_save;

	switch (len) {
		case sizeof(frame->v1):
			zunoSoundSwitchSaveGet(channel, &switch_save);
			playCommandToneVolume = switch_save.volume;
			toneIdentifier = frame->v1.toneIdentifier;
			break ;
		case sizeof(frame->v2):
			playCommandToneVolume = frame->v2.playCommandToneVolume;
			toneIdentifier = frame->v2.toneIdentifier;
			break ;
		default:
			return (ZUNO_COMMAND_BLOCKED_FAIL);
			break ;
	}
	return (_soundSwitchTonePlaySetAdd(channel, toneIdentifier, playCommandToneVolume, options));
}

int zuno_CCSoundSwitchHandler(uint8_t channel, const ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report, const ZUNOCommandHandlerOption_t *options) {
	int								rs;

	switch (ZW_CMD) {
		case SOUND_SWITCH_TONE_PLAY_GET_V2:
			_zunoMarkChannelRequested(channel);
			rs = zuno_CCSoundSwitchReport(channel, &frame_report->info);
			break ;
		case SOUND_SWITCH_TONE_PLAY_SET_V2:
			rs = _soundSwitchTonePlaySet((const ZwSoundSwitchTonePlayFrame_t *)&cmd->cmd[0x0], channel, cmd->len, options);
			if (rs == ZUNO_COMMAND_PROCESSED)
				_config_report_asyn(channel);
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
	ZUNOCommandHandlerOption_t							options;

	if (channel == 0x0)
		return ;
	channel--;
	if (channel >= ZUNO_CFG_CHANNEL_COUNT)
		return ;
	if (ZUNO_CFG_CHANNEL(channel).type != ZUNO_SOUND_SWITCH_CHANNEL_NUMBER)
		return ;
	options = ZUNO_COMMAND_HANDLER_OPTIONS_DEFAULT();
	_soundSwitchTonePlaySetAdd(channel, toneIdentifier, playCommandToneVolume, &options);
}

void zuno_CCSoundSwitchStop(uint8_t channel) {
	zuno_CCSoundSwitchPlay(channel, 0x0, 0x0);
}

int zuno_CCSoundSwitchReport(uint8_t channel, ZUNOCommandPacket_t *packet) {
	ZW_SOUND_SWITCH_TONE_PLAY_REPORT_V2_FRAME							*report;
	zunoTimerTreadDiming_t												list;
	uint8_t																toneIdentifier;
	uint8_t																playCommandToneVolume;

	report = (ZW_SOUND_SWITCH_TONE_PLAY_REPORT_V2_FRAME *)&packet->packet.cmd[0x0];
	report->cmdClass = COMMAND_CLASS_SOUND_SWITCH;
	report->cmd = SOUND_SWITCH_TONE_PLAY_REPORT_V2;
	if (zunoTimerTreadDimingGetInfo(zunoTimerTreadDimingTypeSoundSwitch, channel, &list) == true) {
		toneIdentifier = list.target_value;
		playCommandToneVolume = list.current_value;
	}
	else {
		toneIdentifier = 0x0;
		playCommandToneVolume = 0x0;
	}
	report->toneIdentifier = toneIdentifier;
	report->playCommandToneVolume = playCommandToneVolume;
	packet->packet.len = sizeof(report[0x0]);
	return (ZUNO_COMMAND_ANSWERED);
}

bool zuno_CCSoundSwitchIsRun(uint8_t channel) {
	zunoTimerTreadDiming_t												list;

	if (channel == 0x0)
		return (false);
	channel--;
	if (channel > ZUNO_CFG_CHANNEL_COUNT)
		return (false);
	if (zunoTimerTreadDimingGetInfo(zunoTimerTreadDimingTypeSoundSwitch, channel, &list) == false)
		return (false);
	return (true);
}

int zuno_CCSoundSwitchBasicSet(size_t channel, size_t toneIdentifier, const ZUNOCommandHandlerOption_t *options) {
	ZwSoundSwitchSave_t								switch_save;

	zunoSoundSwitchSaveGet(channel, &switch_save);
	return (_soundSwitchTonePlaySetAdd(channel, toneIdentifier, switch_save.volume, options));
}

#include "ZWCCZWavePlusInfo.h"

#define ICON_TYPE_GENERIC_SOUND_SWITCH										0x2200
#define ICON_TYPE_SPECIFIC_SOUND_SWITCH_DOORBELL							0x2201
#define ICON_TYPE_SPECIFIC_SOUND_SWITCH_CHIME								0x2202
#define ICON_TYPE_SPECIFIC_SOUND_SWITCH_ALARM_CLOCK							0x2203

void zuno_CCSoundSwitchGetIcon(ZwZwavePlusInfoIcon_t *icon) {
	uint16_t								installerIconType;
	uint16_t								userIconType;

	installerIconType = ICON_TYPE_GENERIC_SOUND_SWITCH;
	userIconType = ICON_TYPE_GENERIC_SOUND_SWITCH;
	icon->installerIconType = installerIconType;
	icon->userIconType = userIconType;
}

#endif//WITH_CC_SOUND_SWITCH