#ifndef EEPROM_CONFIG_DOOR_LOCK_H
#define EEPROM_CONFIG_DOOR_LOCK_H

#ifdef WITH_CC_DOORLOCK

typedef struct							ZwEepromDoorLockSaveInfo_s
{
	uint8_t								lockTimeoutMinutes;
	uint8_t								lockTimeoutSeconds;
	union
	{
		uint8_t							properties;
		struct
		{
			uint8_t						InsideDoorHandlesMode: 0x2;
			uint8_t						OutsideDoorHandlesMode: 0x2;
			uint8_t						operationType: 0x4;
		};
	};
}										ZwEepromDoorLockSaveInfo_t;

typedef struct							ZwEepromDoorLockSave_s
{
	ZwEepromDoorLockSaveInfo_t			info[ZUNO_MAX_MULTI_CHANNEL_NUMBER];
}										ZwEepromDoorLockSave_t;

#define EEPROM_DOOR_LOCK_SAVE_ADDR		((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->door_lock)
#define EEPROM_DOOR_LOCK_SAVE_SIZE		(sizeof(ZwEepromDoorLockSave_t))

#endif

#endif//EEPROM_CONFIG_DOOR_LOCK_H