#ifndef EEPROM_CONFIG_USER_CODE_H
#define EEPROM_CONFIG_USER_CODE_H

#if !defined(WITH_CC_USER_CREDENTIAL) && defined(WITH_CC_USER_CODE)

#define USER_CODE_ADDR								((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_code)
#define USER_CODE_SIZE								(sizeof(((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_code))

#ifndef USER_CODE_NUMBER
#define USER_CODE_NUMBER											6
#endif

typedef struct				UserCodeSaveUserId_s
{
	uint8_t					userCode[0xA];
	struct
	{
		uint8_t				userIdStatus: 0x4;
		uint8_t				userCodeLen: 0x4;
	};
}							UserCodeSaveUserId_t;

#if USER_CODE_NUMBER >= 0x20
#define USER_CODE_NUMBER_MASK_LENGHT						0x20
#else
#define USER_CODE_NUMBER_MASK_LENGHT						USER_CODE_NUMBER
#endif

typedef struct				UserCodeSaveMask_s
{
	uint8_t					crc16[0x2];//lsb - Msb
	uint8_t					crc16_mask[0x2 * USER_CODE_NUMBER_MASK_LENGHT];
}							UserCodeSaveMask_t;

typedef struct									UserCodeSaveMasterInfo_s
{
	uint8_t										masterCode[0xA];
	uint8_t										masterCodeLen;
}												UserCodeSaveMasterInfo_t;

typedef struct									UserCodeSaveMaster_s
{
	uint8_t										crc16[0x2];/* LSB  to MSB */
	UserCodeSaveMasterInfo_t					info;
}												UserCodeSaveMaster_t;

typedef struct									UserCodeSaveKeypadMode_s
{
	uint8_t										crc16[0x2];/* LSB  to MSB */
	uint8_t										mode;
}												UserCodeSaveKeypadMode_t;

typedef struct				UserCodeSaveCommon_s
{
	UserCodeSaveKeypadMode_t keypad_mode;
	UserCodeSaveMaster_t	master;
	UserCodeSaveMaster_t	master_local;
	#if USER_CODE_NUMBER == USER_CODE_NUMBER_MASK_LENGHT
	UserCodeSaveMask_t		user_id_mask[0x1];
	UserCodeSaveMask_t		user_id_mask_local[0x1];
	#else
	UserCodeSaveMask_t		user_id_mask[((((USER_CODE_NUMBER + ((USER_CODE_NUMBER_MASK_LENGHT) - 0x1)) & (0x0 - (USER_CODE_NUMBER_MASK_LENGHT))) / (USER_CODE_NUMBER_MASK_LENGHT)))];
	UserCodeSaveMask_t		user_id_mask_local[((((USER_CODE_NUMBER + ((USER_CODE_NUMBER_MASK_LENGHT) - 0x1)) & (0x0 - (USER_CODE_NUMBER_MASK_LENGHT))) / (USER_CODE_NUMBER_MASK_LENGHT)))];
	#endif
	UserCodeSaveUserId_t	user_id[USER_CODE_NUMBER];
}							UserCodeSaveCommon_t;

#endif//WITH_CC_USER_CODE

#endif//EEPROM_CONFIG_USER_CODE_H