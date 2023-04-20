#ifndef ZWCC_SOUND_SWITCH_H
#define ZWCC_SOUND_SWITCH_H

#include "ZWSupport.h"

/* Sound Switch command class commands */
#define SOUND_SWITCH_VERSION                                                             SOUND_SWITCH_VERSION_V2
#define SOUND_SWITCH_TONES_NUMBER_GET                                                    0x01
#define SOUND_SWITCH_TONES_NUMBER_REPORT                                                 0x02
#define SOUND_SWITCH_TONE_INFO_GET                                                       0x03
#define SOUND_SWITCH_TONE_INFO_REPORT                                                    0x04
#define SOUND_SWITCH_CONFIGURATION_SET                                                   0x05
#define SOUND_SWITCH_CONFIGURATION_GET                                                   0x06
#define SOUND_SWITCH_CONFIGURATION_REPORT                                                0x07
#define SOUND_SWITCH_TONE_PLAY_SET                                                       0x08
#define SOUND_SWITCH_TONE_PLAY_GET                                                       0x09
#define SOUND_SWITCH_TONE_PLAY_REPORT                                                    0x0A

/* Sound Switch command class commands */
#define SOUND_SWITCH_VERSION_V2                                                          0x02
#define SOUND_SWITCH_TONES_NUMBER_GET_V2                                                 0x01
#define SOUND_SWITCH_TONES_NUMBER_REPORT_V2                                              0x02
#define SOUND_SWITCH_TONE_INFO_GET_V2                                                    0x03
#define SOUND_SWITCH_TONE_INFO_REPORT_V2                                                 0x04
#define SOUND_SWITCH_CONFIGURATION_SET_V2                                                0x05
#define SOUND_SWITCH_CONFIGURATION_GET_V2                                                0x06
#define SOUND_SWITCH_CONFIGURATION_REPORT_V2                                             0x07
#define SOUND_SWITCH_TONE_PLAY_SET_V2                                                    0x08
#define SOUND_SWITCH_TONE_PLAY_GET_V2                                                    0x09
#define SOUND_SWITCH_TONE_PLAY_REPORT_V2                                                 0x0A

#define SOUND_SWITCH_DEFAULT_VOLUME(channel)						ZUNO_CFG_CHANNEL(channel).sub_type
#define SOUND_SWITCH_DEFAULT_VOLUME_SAVE(channel)					ZUNO_CFG_CHANNEL(channel).params[0x1]
#define SOUND_SWITCH_DEFAULT_TONE_INDENTIFER(channel)				ZUNO_CFG_CHANNEL(channel).params[0x0]
#define SOUND_SWITCH_DEFAULT_TEST(channel)							ZUNO_CFG_CHANNEL(channel).params[0x2]
#define SOUND_SWITCH_DEFAULT_VOLUME_VALUE							(0x32)
#define SOUND_SWITCH_DEFAULT_VOLUME_VALUE_MAX						(0x64)
#define SOUND_SWITCH_DEFAULT_TONE_INDENTIFER_VALUE					(0x1)


#define SOUND_SWITCH_NOT_PLAY_VALUE									{0x0}


/************************************************************/
/* Sound Switch Tone Play Report V2 command class structs */
/************************************************************/
typedef struct _ZW_SOUND_SWITCH_TONE_PLAY_REPORT_V2_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   toneIdentifier;               /**/
    uint8_t   playCommandToneVolume;        /**/
} ZW_SOUND_SWITCH_TONE_PLAY_REPORT_V2_FRAME;


/************************************************************/
/* Sound Switch Tone Play Set command class structs */      
/************************************************************/
typedef struct _ZW_SOUND_SWITCH_TONE_PLAY_SET_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   toneIdentifier;               /**/
} ZW_SOUND_SWITCH_TONE_PLAY_SET_FRAME;


/************************************************************/
/* Sound Switch Tone Play Set V2 command class structs */   
/************************************************************/
typedef struct _ZW_SOUND_SWITCH_TONE_PLAY_SET_V2_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   toneIdentifier;               /**/
    uint8_t   playCommandToneVolume;        /**/
} ZW_SOUND_SWITCH_TONE_PLAY_SET_V2_FRAME;


typedef union					ZwSoundSwitchTonePlayFrame_u {//For more convenient support, several versions of commands
	ZW_SOUND_SWITCH_TONE_PLAY_SET_FRAME				v1;
	ZW_SOUND_SWITCH_TONE_PLAY_SET_V2_FRAME			v2;
}								ZwSoundSwitchTonePlayFrame_t;


/************************************************************/
/* Sound Switch Configuration Set V2 command class structs */
/************************************************************/
typedef struct _ZW_SOUND_SWITCH_CONFIGURATION_SET_V2_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   volume;                       /**/
    uint8_t   defaultToneIdentifier;        /**/
} ZW_SOUND_SWITCH_CONFIGURATION_SET_V2_FRAME;


/************************************************************/
/* Sound Switch Configuration Report V2 command class structs */
/************************************************************/
typedef struct _ZW_SOUND_SWITCH_CONFIGURATION_REPORT_V2_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   volume;                       /**/
    uint8_t   defaultToneIdentifer;         /**/
} ZW_SOUND_SWITCH_CONFIGURATION_REPORT_V2_FRAME;

/************************************************************/
/* Sound Switch Tone Info Report command class structs */
/************************************************************/
typedef struct											ZwSoundSwitchInfoReportFrame_s
{
	uint8_t												cmdClass;/* The command class */
	uint8_t												cmd;/* The command */
	uint8_t												toneIdentifier;/**/
	uint8_t												toneDuration1;/* MSB */
	uint8_t												toneDuration2;/* LSB */
	uint8_t												nameLength;/**/
	uint8_t												name[];
}														ZwSoundSwitchInfoReportFrame_t;

/************************************************************/
/* Sound Switch Tone Info Get V2 command class structs */   
/************************************************************/
typedef struct _ZW_SOUND_SWITCH_TONE_INFO_GET_V2_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   toneIdentifier;               /**/
} ZW_SOUND_SWITCH_TONE_INFO_GET_V2_FRAME;

/************************************************************/
/* Sound Switch Tones Number Report V2 command class structs */
/************************************************************/
typedef struct _ZW_SOUND_SWITCH_TONES_NUMBER_REPORT_V2_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   supportedTones;               /**/
} ZW_SOUND_SWITCH_TONES_NUMBER_REPORT_V2_FRAME;


typedef struct						ZunoSoundSwitchParameterDuration_s
{
	uint16_t						freq;
	uint16_t						play_ms;
	uint16_t						pause_ms;
}									ZunoSoundSwitchParameterDuration_t;


typedef struct						ZunoSoundSwitchParameter_s
{
	const char						*name;
	const ZunoSoundSwitchParameterDuration_t	*duration;
	uint32_t						count:8;
	uint32_t						ms_duration:24;
}									ZunoSoundSwitchParameter_t;

typedef struct						ZunoSoundSwitchParameterPlay_s
{
	uint64_t						time_stamp;
	const ZunoSoundSwitchParameter_t	*parameter;
	uint8_t							index;
	uint8_t							status;
	uint8_t							toneIdentifier;
	uint8_t							playCommandToneVolume;
	uint8_t							bReport;
}									ZunoSoundSwitchParameterPlay_t;

typedef struct								ZunoSoundSwitchParameterArray_s
{
	const ZunoSoundSwitchParameter_t		*parametr;
	ZunoSoundSwitchParameterPlay_t			*play;
	uint8_t									count;
	uint8_t									channel;
}											ZunoSoundSwitchParameterArray_t;



#define ZUNO_SETUP_SOUND_SWITCH_TONE_DURATION(TONE, ...)	\
static const ZunoSoundSwitchParameterDuration_t _switch_cc_parameter_##TONE[] = \
{\
	__VA_ARGS__, \
};\

#define ZUNO_SETUP_SOUND_SWITCH_TONE_DURATION_SET(MS_PLAY, MS_PAUSE)	\
{\
	.freq = 0x0,\
	.play_ms = MS_PLAY,\
	.pause_ms = MS_PAUSE\
}\

#define ZUNO_SETUP_SOUND_SWITCH(CHANNEL, ...) 	\
	static const ZunoSoundSwitchParameter_t _switch_cc_parameter_##CHANNEL[]= \
	{ \
		__VA_ARGS__, \
	};\
	static ZunoSoundSwitchParameterPlay_t _switch_cc_parameter_play_##CHANNEL = \
	{ \
		.time_stamp = 0x0,														\
		.parameter = NULL,														\
		.index = 0x0,													\
		.status = 0x0,													\
		.toneIdentifier = 0x0,													\
		.playCommandToneVolume = 0x0,											\
		.bReport = false														\
	};\
	static const ZunoSoundSwitchParameterArray_t _switch_cc_parameter_array_##CHANNEL __attribute__((__used__, __section__("_switch_cc_array_list"))) = \
	{ \
		.parametr = &_switch_cc_parameter_##CHANNEL[0x0],									\
		.play = &_switch_cc_parameter_play_##CHANNEL,									\
		.count = ((sizeof(_switch_cc_parameter_##CHANNEL) / sizeof(_switch_cc_parameter_##CHANNEL[0x0]))),			\
		.channel = CHANNEL\
	};\

static constexpr uint16_t _soundSwitchGetParameterCountDurationMs(const ZunoSoundSwitchParameterDuration_t *duration, uint8_t count) {
	size_t								ms = 0x0;
	uint8_t								i = 0x0;

	while (i < count){
		ms = ms + duration[i].pause_ms + duration[i].play_ms;
		i++;
	}
	return (ms);
}

#define ZUNO_SETUP_SOUND_SWITCH_TONE(NAME, TONE)	\
{\
	.name = NAME,\
	.duration = &_switch_cc_parameter_##TONE[0x0],\
	.count = ((sizeof(_switch_cc_parameter_##TONE) / sizeof(_switch_cc_parameter_##TONE[0x0]))),			\
	.ms_duration = _soundSwitchGetParameterCountDurationMs(&_switch_cc_parameter_##TONE[0x0], ((sizeof(_switch_cc_parameter_##TONE) / sizeof(_switch_cc_parameter_##TONE[0x0]))))\
}\

int zuno_CCSoundSwitchHandler(uint8_t channel, ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report);
int zuno_CCSoundSwitchReport(uint8_t channel, ZUNOCommandPacket_t *packet);
void zuno_CCSoundSwitchPlay(uint8_t channel, uint8_t toneIdentifier, uint8_t playCommandToneVolume);

#endif// ZWCC_SOUND_SWITCH_H