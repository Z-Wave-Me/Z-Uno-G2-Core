#ifndef EEPROM_CONFIG_USER_CREDENTIAL_H
#define EEPROM_CONFIG_USER_CREDENTIAL_H

#ifdef WITH_CC_USER_CREDENTIAL

#define USER_CREDENTIAL_ADDR							((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential)
#define USER_CREDENTIAL_SIZE							(sizeof(((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential))

#ifndef USER_CREDENTIAL_NUMBER
#define USER_CREDENTIAL_NUMBER											6
#endif

#ifndef USER_CREDENTIAL_NAME_MAX_LENGHT
#define USER_CREDENTIAL_NAME_MAX_LENGHT									12
#endif

#if !defined(USER_CREDENTIAL_NUMBER_PIN_CODE) && !defined(USER_CREDENTIAL_NUMBER_PASSWORD) && !defined(USER_CREDENTIAL_NUMBER_RFID_CODE)
#define USER_CREDENTIAL_NUMBER_PIN_CODE									3
#define USER_CREDENTIAL_NUMBER_PIN_CODE_MIN_LENGHT						4
#define USER_CREDENTIAL_NUMBER_PIN_CODE_MAX_LENGHT						10
#endif

typedef struct				UserCredentialSaveUserId_s
{
	uint8_t					name_lenght;
	uint8_t					name[USER_CREDENTIAL_NAME_MAX_LENGHT];
}							UserCredentialSaveUserId_t;

#define USER_CREDENTIAL_NUMBER_MASK_LENGHT						0x2

typedef struct				UserCredentialSaveMask_s
{
	uint8_t					crc16[0x2];//lsb - Msb
	uint8_t					mask[USER_CREDENTIAL_NUMBER_MASK_LENGHT];
}							UserCredentialSaveMask_t;


typedef struct				UserCredentialSaveCommon_s
{
	UserCredentialSaveMask_t		user_id_mask[((((USER_CREDENTIAL_NUMBER + ((USER_CREDENTIAL_NUMBER_MASK_LENGHT * 0x8) - 0x1)) & (0x0 - (USER_CREDENTIAL_NUMBER_MASK_LENGHT * 0x8))) / (USER_CREDENTIAL_NUMBER_MASK_LENGHT * 0x8)))];
	UserCredentialSaveUserId_t		user_id[USER_CREDENTIAL_NUMBER];
}							UserCredentialSaveCommon_t;

#endif//WITH_CC_USER_CREDENTIAL
#endif//EEPROM_CONFIG_USER_CREDENTIAL_H