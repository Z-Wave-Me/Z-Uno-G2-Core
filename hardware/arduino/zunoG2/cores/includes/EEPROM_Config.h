#ifndef EEPROM_CONFIG_H
#define EEPROM_CONFIG_H

#define EEPROM_SKETH_ADDR								0x0
#define EEPROM_SKETH_SIZE								0xE00

#define EEPROM_NOTIFICATION_ADDR						((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->notification[0x0])
#define EEPROM_NOTIFICATION_SIZE						4
#define EEPROM_WAKEUP_ADDR								((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->wakeup[0x0])
#define EEPROM_WAKEUP_SIZE								4

#ifdef WITH_CC_BASIC
#define EEPROM_BASIC_SAVE_ADDR							((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->basic[0x0])
#define EEPROM_BASIC_SAVE_SIZE							(1 * ZUNO_MAX_MULTI_CHANNEL_NUMBER)
#endif

#if defined(WITH_CC_CENTRAL_SCENE)
#define EEPROM_CENTRAL_SCENE_SAVE_ADDR					((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->central_scene[0x0])
#define EEPROM_CENTRAL_SCENE_SAVE_SIZE					(1)
#endif

#define EEPROM_USER_CHANNELS_EEPROM_ADDR				((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->zuno_zw_cfg)
#define EEPROM_USER_CHANNELS_EEPROM_SIZE				sizeof(g_zuno_zw_cfg)

// All last
#define EEPROM_CONFIGURATION_ADDR						((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->config_param)
#ifdef CONFIGPARAMETERS_MAX_COUNT
	#define EEPROM_CONFIGURATION_SIZE					(CONFIGPARAMETERS_MAX_COUNT * 0x4)
#else
	#define EEPROM_CONFIGURATION_SIZE					(0x20 * 0x4)
#endif

#define EEPROM_MAX_SIZE									0x1300

#include "EEPROM_ConfigScheduleEntryLock.h"
#include "EEPROM_ConfigUserCredential.h"
#include "EEPROM_ConfigDoorLock.h"
#include "EEPROM_ConfigSoundSwitch.h"

typedef struct									ZwEepromSkethCommonInfo_s
{
	#ifdef WITH_CC_USER_CREDENTIAL
	UserCredentialSaveCommon_t					user_credential;
	#endif
	#ifdef WITH_CC_SCHEDULE_ENTRY_LOCK
	ScheduleEntryLockSaveCommon_t				schedule_entry_lock;
	#endif
}												ZwEepromSkethCommonInfo_t;

#define EEPROM_SKETH_SIZE_ACTUAL				(EEPROM_SKETH_SIZE - sizeof(ZwEepromSkethCommonInfo_t))

typedef struct									ZwEepromSkethCommon_s
{
	uint8_t										user_code[EEPROM_SKETH_SIZE_ACTUAL];
	ZwEepromSkethCommonInfo_t					info;
}												ZwEepromSkethCommon_t;

typedef struct									ZwEepromSkethConfigParam_s
{
	uint8_t										config_param[EEPROM_CONFIGURATION_SIZE];
} __attribute__((aligned(0x100),packed))		ZwEepromSkethConfigParam_t;

typedef struct									ZwEepromSketh_s
{
	ZwEepromSkethCommon_t						common;
	uint8_t										notification[EEPROM_NOTIFICATION_SIZE];
	uint8_t										wakeup[EEPROM_WAKEUP_SIZE];
	#if defined(WITH_CC_BASIC)
	uint8_t										basic[EEPROM_BASIC_SAVE_SIZE];
	#endif
	#if defined(WITH_CC_SOUND_SWITCH)
	uint8_t										switch_sound[EEPROM_SWITCH_SOUND_SAVE_SIZE];
	#endif
	#if defined(WITH_CC_CENTRAL_SCENE)
	uint8_t										central_scene[EEPROM_CENTRAL_SCENE_SAVE_SIZE];
	#endif
	#ifdef WITH_CC_DOORLOCK
	ZwEepromDoorLockSave_t						door_lock;
	#endif
	ZUNOZWConfiguation_t						zuno_zw_cfg;
	ZwEepromSkethConfigParam_t					config_param;
}												ZwEepromSketh_t;


inline int zunoEEPROMWrite(word address, word size, byte * data) {return (int)zunoSysCall(ZUNO_SYSFUNC_EEPROM_IO, 4, true, address, size, data);};
inline int zunoEEPROMRead(word address, word size, byte * data) {return (int)zunoSysCall(ZUNO_SYSFUNC_EEPROM_IO, 4, false, address, size, data);};
inline int zunoEEPROMErase(void) {return (int)zunoSysCall(ZUNO_SYSFUNC_EEPROM_ERASE, 1, 0xCAFE0ACE);};

#endif//EEPROM_CONFIG_H