#ifndef EEPROM_CONFIG_SOUND_SWITCH_H
#define EEPROM_CONFIG_SOUND_SWITCH_H

#if defined(WITH_CC_SOUND_SWITCH)

typedef struct								ZwSoundSwitchSave_s
{
	uint8_t									volume;
	uint8_t									volume_save;
	uint8_t									toneIdentifier;
}											ZwSoundSwitchSave_t;

#define EEPROM_SWITCH_SOUND_SAVE_ADDR					((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->switch_sound[0x0])
#define EEPROM_SWITCH_SOUND_SAVE_SIZE					(ZUNO_MAX_MULTI_CHANNEL_NUMBER * sizeof(ZwSoundSwitchSave_t))

#endif

#endif//EEPROM_CONFIG_SOUND_SWITCH_H