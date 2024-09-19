#include "Arduino.h"
#include "ZWCCUserCredential.h"
#include "CrcClass.h"

#ifdef WITH_CC_USER_CREDENTIAL

#define USER_CREDENTIAL_ADDR_USER							((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.user)

#define USER_CREDENTIAL_MODIFY_TYPE_DNE								0x0
#define USER_CREDENTIAL_MODIFY_TYPE_UNKNOWN							0x1
#define USER_CREDENTIAL_MODIFY_TYPE_ZWAVE							0x2
#define USER_CREDENTIAL_MODIFY_TYPE_LOCALLY							0x3
#define USER_CREDENTIAL_MODIFY_TYPE_MOBILLY							0x4

#define USER_CREDENTIAL_TYPE_PIN_CODE							(0x1)
#define USER_CREDENTIAL_TYPE_PASSWORD							(0x2)
#define USER_CREDENTIAL_TYPE_RFID_CODE							(0x3)

typedef struct					UserCredentialSaveArg_s
{
	uint16_t					CredentialSlotMax;
	uint8_t						CredentialLengthMin;
	uint8_t						CredentialLengthMax;
	uint8_t						mask_lenght;
}								UserCredentialSaveArg_t;

static_assert(USER_CREDENTIAL_NUMBER <= 0xFFFF && USER_CREDENTIAL_NUMBER >= 0x1, "USER_CREDENTIAL_NUMBER - max 0xFFFF and min 0x1!!!");
#if defined(USER_CREDENTIAL_NUMBER_PIN_CODE)
static_assert(USER_CREDENTIAL_NUMBER_PIN_CODE <= 0xFFFF && USER_CREDENTIAL_NUMBER_PIN_CODE >= 0x1, "USER_CREDENTIAL_NUMBER_PIN_CODE - max 0xFFFF and min 0x1!!!");
static_assert(USER_CREDENTIAL_NUMBER_PIN_CODE_MIN_LENGHT >= 0x1, "USER_CREDENTIAL_NUMBER_PIN_CODE_MIN_LENGHT - min 0x1!!!");
static_assert(USER_CREDENTIAL_NUMBER_PIN_CODE_MAX_LENGHT <= 0xFFFF, "USER_CREDENTIAL_NUMBER_PIN_CODE_MAX_LENGHT - max 0xFFFF!!!");
static_assert(USER_CREDENTIAL_NUMBER_PIN_CODE_MIN_LENGHT <= USER_CREDENTIAL_NUMBER_PIN_CODE_MAX_LENGHT, "Must USER_CREDENTIAL_NUMBER_PIN_CODE_MAX_LENGHT < USER_CREDENTIAL_NUMBER_PIN_CODE_MIN_LENGHT!!!");
#endif
#if defined(USER_CREDENTIAL_NUMBER_PASSWORD)
static_assert(USER_CREDENTIAL_NUMBER_PASSWORD <= 0xFFFF && USER_CREDENTIAL_NUMBER_PASSWORD >= 0x1, "USER_CREDENTIAL_NUMBER_PASSWORD - max 0xFFFF and min 0x1!!!");
static_assert(USER_CREDENTIAL_NUMBER_PASSWORD_MIN_LENGHT >= 0x1, "USER_CREDENTIAL_NUMBER_PASSWORD_MIN_LENGHT - min 0x1!!!");
static_assert(USER_CREDENTIAL_NUMBER_PASSWORD_MAX_LENGHT <= 0xFFFF, "USER_CREDENTIAL_NUMBER_PASSWORD_MAX_LENGHT - max 0xFFFF!!!");
static_assert(USER_CREDENTIAL_NUMBER_PASSWORD_MIN_LENGHT < USER_CREDENTIAL_NUMBER_PASSWORD_MAX_LENGHT, "Must USER_CREDENTIAL_NUMBER_PASSWORD_MAX_LENGHT < USER_CREDENTIAL_NUMBER_PASSWORD_MIN_LENGHT!!!");
#endif
#if defined(USER_CREDENTIAL_NUMBER_RFID_CODE)
static_assert(USER_CREDENTIAL_NUMBER_RFID_CODE <= 0xFFFF && USER_CREDENTIAL_NUMBER_RFID_CODE >= 0x1, "USER_CREDENTIAL_NUMBER_RFID_CODE - max 0xFFFF and min 0x1!!!");
static_assert(USER_CREDENTIAL_NUMBER_RFID_CODE_MIN_LENGHT >= 0x1, "USER_CREDENTIAL_NUMBER_RFID_CODE_MIN_LENGHT - min 0x1!!!");
static_assert(USER_CREDENTIAL_NUMBER_RFID_CODE_MAX_LENGHT <= 0xFFFF, "USER_CREDENTIAL_NUMBER_RFID_CODE_MAX_LENGHT - max 0xFFFF!!!");
static_assert(USER_CREDENTIAL_NUMBER_RFID_CODE_MIN_LENGHT < USER_CREDENTIAL_NUMBER_RFID_CODE_MAX_LENGHT, "Must USER_CREDENTIAL_NUMBER_RFID_CODE_MAX_LENGHT < USER_CREDENTIAL_NUMBER_RFID_CODE_MIN_LENGHT!!!");
#endif

static constexpr uint8_t NUMBER_OF_SUPPORTED_CREDENTIAL_TYPES = 0
#if defined(USER_CREDENTIAL_NUMBER_PIN_CODE)
+ 0x1
#endif
#if defined(USER_CREDENTIAL_NUMBER_PASSWORD)
+ 0x1
#endif
#if defined(USER_CREDENTIAL_NUMBER_RFID_CODE)
+ 0x1
#endif
;

static constexpr uint32_t MASK_OF_SUPPORTED_CREDENTIAL_TYPES = 0
#if defined(USER_CREDENTIAL_NUMBER_PIN_CODE)
| (0x1 << USER_CREDENTIAL_TYPE_PIN_CODE)
#endif
#if defined(USER_CREDENTIAL_NUMBER_PASSWORD)
| (0x1 << USER_CREDENTIAL_TYPE_PASSWORD)
#endif
#if defined(USER_CREDENTIAL_NUMBER_RFID_CODE)
| (0x1 << USER_CREDENTIAL_TYPE_RFID_CODE)
#endif
;

#define USER_CREDENTIAL_STRUCT_SAVE_ARG(name)									\
static const UserCredentialSaveArg_t _save_arg_##name =							\
{																				\
	.CredentialSlotMax = USER_CREDENTIAL_NUMBER_##name,							\
	.CredentialLengthMin = USER_CREDENTIAL_NUMBER_##name##_MIN_LENGHT,			\
	.CredentialLengthMax = USER_CREDENTIAL_NUMBER_##name##_MAX_LENGHT,			\
	.mask_lenght = USER_CREDENTIAL_NUMBER_##name##_MASK_LENGHT,					\
};																				\

#if defined(USER_CREDENTIAL_NUMBER_PIN_CODE)
	USER_CREDENTIAL_STRUCT_SAVE_ARG(PIN_CODE)
#endif

#if defined(USER_CREDENTIAL_NUMBER_PASSWORD)
	USER_CREDENTIAL_STRUCT_SAVE_ARG(PASSWORD)
#endif
#if defined(USER_CREDENTIAL_NUMBER_RFID_CODE)
	USER_CREDENTIAL_STRUCT_SAVE_ARG(RFID_CODE)
#endif

#define USER_CREDENTIAL_SWTCH_SET_ARG(name)																											\
		case USER_CREDENTIAL_TYPE_##name:																											\
			arg = &_save_arg_##name;																												\
			credential = (UserCredentialSaveCredential_t *)&name[0x0];																				\
			addr = ((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential._##name[UserUniqueIdentifier - 0x1]);					\
			break ;

#define USER_CREDENTIAL_SUPPORT_CHECKSUM_CREDENTIAL				(0x7)
#define USER_CREDENTIAL_SUPPORT_LEARN							(0x7)
#define USER_CREDENTIAL_SUPPORT_SCHEDULE						(0x7)
#define USER_CREDENTIAL_SUPPORT_CHECKSUM_ALL_USERS				(0x6)
#define USER_CREDENTIAL_SUPPORT_CHECKSUM_USER					(0x5)

// User has access, provided proper Credential is supplied.
#define USER_CREDENTIAL_TYPE_GENERAL_USER						(0x0)
/*
User has the ability to both program and MAY operate the node. This user can manage the users and  user schedules. In all other respects the user matches the general (default) user.
Programming User is the  only user that can disable the user interface (keypad,  remote, etc.). This can also be referred to as admin  user.
*/
#define USER_CREDENTIAL_TYPE_PROGRAMING_USER					(0x3)
/*
User access and PIN code is restricted to remote lock/unlock commands only.
This type of user might be useful for regular delivery services to prevent a PIN code Credential created for them from being used at the keypad.
The PIN code Credential would only be provided over-the-air for the lock/unlock commands.
*/
#define USER_CREDENTIAL_TYPE_REMOTE_ONLY_USER					(0x9)

static constexpr uint32_t MASK_OF_SUPPORTED_USER_TYPES = ((0x1 << USER_CREDENTIAL_TYPE_GENERAL_USER) | (0x1 << USER_CREDENTIAL_TYPE_PROGRAMING_USER));

static const uint32_t _user_supported_credential_rules_mask = ((0x1 << USER_CREDENTIAL_RULE_SINGLE));


typedef struct				UserCredentialSaveMaskTemp_s
{
	uint8_t					crc16[0x2];//lsb - Msb
	uint8_t					crc16_mask[];//lsb - Msb
}							UserCredentialSaveMaskTemp_t;

static bool _get_eeprom_data_add(uint32_t addr, uint8_t mask_size, uint8_t mask_lenght, uint16_t id, UserCredentialSaveMaskTemp_t *mask, void *buffer, size_t leght, uint8_t offset_crc16) {
	uint16_t													crc16;

	crc16 = mask->crc16_mask[(0x2 * (id % (mask_lenght))) + 0x0] | (mask->crc16_mask[(0x2 * (id % (mask_lenght))) + 0x1] << 0x8);
	if (crc16 == 0x0)
		return (false);
	addr = addr + (mask_size * 0x2) + ((id % (mask_lenght)) * leght);
	zunoEEPROMRead(addr, leght, (byte *)buffer);
	if (CrcClass::crc16_ccitt_aug((uint8_t *)buffer + offset_crc16, leght - offset_crc16) != crc16)
		return (false);
	return (true);
}

static bool _read_eeprom_id(uint32_t addr, uint8_t mask_lenght, uint16_t id, void *buffer, size_t leght, uint8_t offset_crc16) {
	UserCredentialSaveMaskTemp_t								*mask_temp;
	uint8_t														mask_size;
	uint8_t														mask[sizeof(UserCredentialSaveMaskTemp_t) + 0x2 * USER_CREDENTIAL_NUMBER_DEFAULT_MASK_LENGHT];
	size_t														offset;
	uint16_t													crc16;

	mask_temp = (UserCredentialSaveMaskTemp_t *)&mask[0x0];
	mask_size = sizeof(UserCredentialSaveMaskTemp_t) + 0x2 * mask_lenght;
	id--;
	offset = id / (mask_lenght);
	addr = addr + (offset * (mask_size * 0x2)) + (offset * ((mask_lenght) * leght));
	zunoEEPROMRead(addr, mask_size, (byte *)&mask);
	crc16 = CrcClass::crc16_ccitt_aug(&mask_temp->crc16_mask[0x0], 0x2 * mask_lenght);
	if (memcmp(&crc16, &mask_temp->crc16[0x0], sizeof(crc16)) != 0x0)
		return (false);
	return (_get_eeprom_data_add(addr, mask_size, mask_lenght, id, mask_temp, buffer, leght, offset_crc16));
}

static bool _read_eeprom_id_user(uint16_t id, void *buffer, size_t leght) {
	return (_read_eeprom_id(USER_CREDENTIAL_ADDR_USER, USER_CREDENTIAL_NUMBER_MASK_LENGHT, id, buffer, leght, 0x0));
}

static bool _read_eeprom_id_credential(uint16_t CredentialSlot, uint32_t addr, UserCredentialSaveCredential_t *credential, const UserCredentialSaveArg_t *arg) {
	return (_read_eeprom_id(addr, arg->mask_lenght, CredentialSlot, credential, sizeof(credential[0x0]) + arg->CredentialLengthMax, sizeof(credential[0x0])));
}

static void _write_eeprom_id(uint32_t addr, uint8_t mask_lenght, uint16_t id, void *buffer, size_t leght, uint8_t offset_crc16) {
	UserCredentialSaveMaskTemp_t								*mask_temp;
	uint8_t														mask_size;
	uint8_t														mask[sizeof(UserCredentialSaveMaskTemp_t) + 0x2 * USER_CREDENTIAL_NUMBER_DEFAULT_MASK_LENGHT];
	uint32_t													addr_user_id;
	uint32_t													addr_mask;
	size_t														offset;
	uint16_t													crc16;

	mask_temp = (UserCredentialSaveMaskTemp_t *)&mask[0x0];
	mask_size = sizeof(UserCredentialSaveMaskTemp_t) + 0x2 * mask_lenght;
	id--;
	offset = id / (mask_lenght);
	addr_mask = (addr) + (offset * (mask_size * 0x2)) + (offset * ((mask_lenght) * leght));
	zunoEEPROMRead(addr_mask, mask_size, (byte *)&mask);
	crc16 = CrcClass::crc16_ccitt_aug(&mask_temp->crc16_mask[0x0], 0x2 * mask_lenght);
	if (memcmp(&crc16, &mask_temp->crc16[0x0], sizeof(crc16)) != 0x0) {
		memset(&mask_temp->crc16_mask[0x0], 0x0, 0x2 * mask_lenght);
	}
	addr_user_id = addr_mask + (mask_size * 0x2) + ((id % (mask_lenght)) * leght);
	zunoEEPROMWrite(addr_user_id, leght, (byte *)buffer);
	crc16 = CrcClass::crc16_ccitt_aug((uint8_t *)buffer + offset_crc16, leght - offset_crc16);
	mask_temp->crc16_mask[(0x2 * (id % (mask_lenght))) + 0x0] = crc16;
	mask_temp->crc16_mask[(0x2 * (id % (mask_lenght))) + 0x1] = crc16 >> 0x8;
	crc16 = CrcClass::crc16_ccitt_aug(&mask_temp->crc16_mask[0x0], 0x2 * mask_lenght);
	memcpy(&mask_temp->crc16[0x0], &crc16, sizeof(crc16));
	zunoEEPROMWrite(addr_mask, mask_size, (byte *)&mask);
}

static void _write_eeprom_id_user(uint16_t id, void *buffer, size_t leght) {
	return (_write_eeprom_id(USER_CREDENTIAL_ADDR_USER, USER_CREDENTIAL_NUMBER_MASK_LENGHT, id, buffer, leght, 0x0));
}

static void _write_eeprom_id_credential(uint16_t CredentialSlot, uint32_t addr, UserCredentialSaveCredential_t *credential, const UserCredentialSaveArg_t *arg) {
	return (_write_eeprom_id(addr, arg->mask_lenght, CredentialSlot, credential, sizeof(credential[0x0]) + arg->CredentialLengthMax, sizeof(credential[0x0])));
}

static void _delete_eeprom_id(uint32_t addr, uint8_t mask_lenght, uint16_t id, size_t leght) {
	UserCredentialSaveMaskTemp_t								*mask_temp;
	uint8_t														mask_size;
	uint8_t														mask[sizeof(UserCredentialSaveMaskTemp_t) + 0x2 * USER_CREDENTIAL_NUMBER_DEFAULT_MASK_LENGHT];
	size_t														offset;
	uint16_t													crc16;

	mask_temp = (UserCredentialSaveMaskTemp_t *)&mask[0x0];
	mask_size = sizeof(UserCredentialSaveMaskTemp_t) + 0x2 * mask_lenght;
	id--;
	offset = id / (mask_lenght);
	addr = addr + (offset * (mask_size * 0x2)) + (offset * ((mask_lenght) * leght));
	zunoEEPROMRead(addr, mask_size, (byte *)&mask);
	crc16 = CrcClass::crc16_ccitt_aug(&mask_temp->crc16_mask[0x0], 0x2 * mask_lenght);
	if (memcmp(&crc16, &mask_temp->crc16[0x0], sizeof(crc16)) != 0x0)
		return ;
	crc16 = mask_temp->crc16_mask[(0x2 * (id % (mask_lenght))) + 0x0] | (mask_temp->crc16_mask[(0x2 * (id % (mask_lenght))) + 0x1] << 0x8);
	if (crc16 == 0x0)
		return ;
	mask_temp->crc16_mask[(0x2 * (id % (mask_lenght))) + 0x0] = 0x0;
	mask_temp->crc16_mask[(0x2 * (id % (mask_lenght))) + 0x1] = 0x0;
	crc16 = CrcClass::crc16_ccitt_aug(&mask_temp->crc16_mask[0x0], 0x2 * mask_lenght);
	memcpy(&mask_temp->crc16[0x0], &crc16,sizeof(mask_temp->crc16));
	zunoEEPROMWrite(addr, mask_size, (byte *)&mask);
}

static void _delete_eeprom_credential_all_one_user_add(uint16_t id, uint16_t id_max, uint8_t mask_lenght, uint32_t addr, size_t leght) {
	UserCredentialSaveMaskTemp_t				*mask_temp;
	uint8_t										mask_size;
	uint8_t										mask[sizeof(UserCredentialSaveMaskTemp_t) + 0x2 * USER_CREDENTIAL_NUMBER_DEFAULT_MASK_LENGHT];
	uint32_t									addr_mask;
	size_t										offset;
	uint16_t									crc16;

	mask_temp = (UserCredentialSaveMaskTemp_t *)&mask[0x0];
	mask_size = sizeof(UserCredentialSaveMaskTemp_t) + 0x2 * mask_lenght;
	while (id < id_max) {
		offset = (id) / (mask_lenght);
		addr_mask = (addr) + (offset * (mask_size * 0x2)) + (offset * ((mask_lenght) * leght));
		zunoEEPROMRead(addr_mask, mask_size, (byte *)&mask);
		crc16 = CrcClass::crc16_ccitt_aug(&mask_temp->crc16_mask[0x0], 0x2 * mask_lenght);
		if (memcmp(&crc16, &mask_temp->crc16[0x0], sizeof(crc16)) == 0x0) {
			memset(mask_temp, 0x0, mask_size);
			zunoEEPROMWrite(addr_mask, mask_size, (byte *)&mask);
		}
		id = id + mask_lenght;
	}
}

static void _delete_eeprom_credential_all_one_user(uint16_t UserUniqueIdentifier) {
	uint8_t											CredentialType;
	uint32_t										CredentialTypeMask;
	uint32_t										addr;
	#if defined(USER_CREDENTIAL_NUMBER_PIN_CODE)
	uint8_t											PIN_CODE[(sizeof(UserCredentialSaveCredential_t) + USER_CREDENTIAL_NUMBER_PIN_CODE_MAX_LENGHT)];
	#endif
	UserCredentialSaveCredential_t					*credential;
	const UserCredentialSaveArg_t					*arg;

	CredentialType = 0x0;
	CredentialTypeMask = MASK_OF_SUPPORTED_CREDENTIAL_TYPES >> CredentialType;
	while (true) {
		CredentialType++;
		CredentialTypeMask = CredentialTypeMask >> 0x1;
		if (CredentialTypeMask == 0x0)
			break ;
		switch (CredentialType) {
			#if defined(USER_CREDENTIAL_NUMBER_PIN_CODE)
			USER_CREDENTIAL_SWTCH_SET_ARG(PIN_CODE)
			#endif
			#if defined(USER_CREDENTIAL_NUMBER_PASSWORD)
			USER_CREDENTIAL_SWTCH_SET_ARG(PASSWORD)
			#endif
			#if defined(USER_CREDENTIAL_NUMBER_RFID_CODE)
			USER_CREDENTIAL_SWTCH_SET_ARG(RFID_CODE)
			#endif
			default:
				arg = NULL;
				break ;
		}
		if (arg == NULL)
			continue ;
		_delete_eeprom_credential_all_one_user_add(0x0, arg->CredentialSlotMax, arg->mask_lenght, addr, sizeof(credential[0x0]) + arg->CredentialLengthMax);
	}
}

static void _delete_eeprom_credential_all_one_user_one_type(uint16_t UserUniqueIdentifier, uint8_t CredentialType) {
	uint32_t										addr;
	#if defined(USER_CREDENTIAL_NUMBER_PIN_CODE)
	uint8_t											PIN_CODE[(sizeof(UserCredentialSaveCredential_t) + USER_CREDENTIAL_NUMBER_PIN_CODE_MAX_LENGHT)];
	#endif
	UserCredentialSaveCredential_t					*credential;
	const UserCredentialSaveArg_t					*arg;

	switch (CredentialType) {
		#if defined(USER_CREDENTIAL_NUMBER_PIN_CODE)
		USER_CREDENTIAL_SWTCH_SET_ARG(PIN_CODE)
		#endif
		#if defined(USER_CREDENTIAL_NUMBER_PASSWORD)
		USER_CREDENTIAL_SWTCH_SET_ARG(PASSWORD)
		#endif
		#if defined(USER_CREDENTIAL_NUMBER_RFID_CODE)
		USER_CREDENTIAL_SWTCH_SET_ARG(RFID_CODE)
		#endif
		default:
			arg = NULL;
			break ;
	}
	if (arg == NULL)
		return ;
	_delete_eeprom_credential_all_one_user_add(0x0, arg->CredentialSlotMax, arg->mask_lenght, addr, sizeof(credential[0x0]) + arg->CredentialLengthMax);
}

static void _delete_eeprom_credential_all_full_user_one_type(uint8_t CredentialType) {
	size_t											UserUniqueIdentifier;

	UserUniqueIdentifier = 0x1;
	while (UserUniqueIdentifier <= USER_CREDENTIAL_NUMBER) {
		_delete_eeprom_credential_all_one_user_one_type(UserUniqueIdentifier, CredentialType);
		UserUniqueIdentifier++;
	}
}

static void _delete_eeprom_credential_all_full_user() {
	size_t											UserUniqueIdentifier;

	UserUniqueIdentifier = 0x1;
	while (UserUniqueIdentifier <= USER_CREDENTIAL_NUMBER) {
		_delete_eeprom_credential_all_one_user(UserUniqueIdentifier);
		UserUniqueIdentifier++;
	}
}

static bool _credential_test_uniq_add(uint16_t id, uint16_t id_max, uint8_t mask_lenght, uint32_t addr, size_t leght, uint16_t crc16_cmp) {
	UserCredentialSaveMaskTemp_t				*mask_temp;
	uint8_t										mask_size;
	uint8_t										mask[sizeof(UserCredentialSaveMaskTemp_t) + 0x2 * USER_CREDENTIAL_NUMBER_DEFAULT_MASK_LENGHT];
	uint32_t									addr_mask;
	size_t										offset;
	uint16_t									crc16;
	uint16_t									id_tmp;

	mask_temp = (UserCredentialSaveMaskTemp_t *)&mask[0x0];
	mask_size = sizeof(UserCredentialSaveMaskTemp_t) + 0x2 * mask_lenght;
	while (id < id_max) {
		offset = (id) / (mask_lenght);
		addr_mask = (addr) + (offset * (mask_size * 0x2)) + (offset * ((mask_lenght) * leght));
		zunoEEPROMRead(addr_mask, mask_size, (byte *)&mask);
		crc16 = CrcClass::crc16_ccitt_aug(&mask_temp->crc16_mask[0x0], 0x2 * mask_lenght);
		if (memcmp(&crc16, &mask_temp->crc16[0x0], sizeof(crc16)) == 0x0) {
			id_tmp = id + mask_lenght;
			while (id < id_tmp && id < id_max) {
				if ((mask_temp->crc16_mask[(0x2 * (id % (mask_lenght))) + 0x0] | (mask_temp->crc16_mask[(0x2 * (id % (mask_lenght))) + 0x1] << 0x8)) == crc16_cmp)
					return (true);
				id++;
			}
			continue ;
		}
		id = id + mask_lenght;
	}
	return (false);
}

static bool _credential_test_uniq(uint16_t crc16) {
	uint8_t											CredentialType;
	uint32_t										CredentialTypeMask;
	size_t											UserUniqueIdentifier;
	uint32_t										addr;
	#if defined(USER_CREDENTIAL_NUMBER_PIN_CODE)
	uint8_t											PIN_CODE[(sizeof(UserCredentialSaveCredential_t) + USER_CREDENTIAL_NUMBER_PIN_CODE_MAX_LENGHT)];
	#endif
	UserCredentialSaveCredential_t					*credential;
	const UserCredentialSaveArg_t					*arg;

	UserUniqueIdentifier = 0x1;
	while (UserUniqueIdentifier <= USER_CREDENTIAL_NUMBER) {
		CredentialType = 0x0;
		CredentialTypeMask = MASK_OF_SUPPORTED_CREDENTIAL_TYPES >> CredentialType;
		while (true) {
			CredentialType++;
			CredentialTypeMask = CredentialTypeMask >> 0x1;
			if (CredentialTypeMask == 0x0)
				break;
			switch (CredentialType) {
				#if defined(USER_CREDENTIAL_NUMBER_PIN_CODE)
				USER_CREDENTIAL_SWTCH_SET_ARG(PIN_CODE)
				#endif
				#if defined(USER_CREDENTIAL_NUMBER_PASSWORD)
				USER_CREDENTIAL_SWTCH_SET_ARG(PASSWORD)
				#endif
				#if defined(USER_CREDENTIAL_NUMBER_RFID_CODE)
				USER_CREDENTIAL_SWTCH_SET_ARG(RFID_CODE)
				#endif
				default:
					arg = NULL;
					break ;
			}
			if (arg == NULL)
				continue ;
			if (_credential_test_uniq_add(0x0, arg->CredentialSlotMax, arg->mask_lenght, addr, sizeof(credential[0x0]) + arg->CredentialLengthMax, crc16) == true)
				return (true);
		}
		UserUniqueIdentifier++;
	}
	return (false);
}

static void _del_all_user(void) {
	size_t										userIdentifier;
	uint32_t									addr_mask;
	size_t										offset;
	UserCredentialSaveMask_t					mask;

	memset(&mask.crc16_mask[0x0], 0x0, sizeof(mask.crc16_mask));
	userIdentifier = 0x0;
	while (userIdentifier < USER_CREDENTIAL_NUMBER) {
		offset = (userIdentifier) / (USER_CREDENTIAL_NUMBER_MASK_LENGHT);
		addr_mask = (USER_CREDENTIAL_ADDR_USER) + (offset * (sizeof(UserCredentialSaveMask_t) * 0x2)) + (offset * ((USER_CREDENTIAL_NUMBER_MASK_LENGHT) * sizeof(UserCredentialSaveUserId_t)));
		zunoEEPROMWrite(addr_mask, sizeof(mask), (byte *)&mask);
		userIdentifier = userIdentifier + USER_CREDENTIAL_NUMBER_MASK_LENGHT;
	}
}

static void _del_user(uint16_t userIdentifier) {
	UserCredentialSaveMask_t									mask;
	uint32_t													addr;
	size_t														offset;
	uint16_t													crc16;

	if (userIdentifier == 0x0) {
		_del_all_user();
		return ;
	}
	if (userIdentifier > USER_CREDENTIAL_NUMBER)
		return ;
	_delete_eeprom_credential_all_one_user(userIdentifier);
	userIdentifier--;
	offset = userIdentifier / (USER_CREDENTIAL_NUMBER_MASK_LENGHT);
	addr = (USER_CREDENTIAL_ADDR_USER) + (offset * (sizeof(UserCredentialSaveMask_t) * 0x2)) + (offset * ((USER_CREDENTIAL_NUMBER_MASK_LENGHT) * sizeof(UserCredentialSaveUserId_t)));
	zunoEEPROMRead(addr, sizeof(mask), (byte *)&mask);
	crc16 = CrcClass::crc16_ccitt_aug(&mask.crc16_mask[0x0], sizeof(mask.crc16_mask));
	if (memcmp(&crc16, &mask.crc16[0x0], sizeof(crc16)) != 0x0)
		return ;
	crc16 = mask.crc16_mask[(0x2 * (userIdentifier % (USER_CREDENTIAL_NUMBER_MASK_LENGHT))) + 0x0] | (mask.crc16_mask[(0x2 * (userIdentifier % (USER_CREDENTIAL_NUMBER_MASK_LENGHT))) + 0x1] << 0x8);
	if (crc16 == 0x0)
		return ;
	mask.crc16_mask[(0x2 * (userIdentifier % (USER_CREDENTIAL_NUMBER_MASK_LENGHT))) + 0x0] = 0x0;
	mask.crc16_mask[(0x2 * (userIdentifier % (USER_CREDENTIAL_NUMBER_MASK_LENGHT))) + 0x1] = 0x0;
	zunoEEPROMWrite(addr, sizeof(mask), (byte *)&mask);
}

static uint16_t _get_next(uint16_t id, uint16_t id_max, uint8_t mask_lenght, uint32_t addr, void *buffer, size_t leght, uint8_t offset_crc16) {
	UserCredentialSaveMaskTemp_t				*mask_temp;
	uint8_t										mask_size;
	uint8_t										mask[sizeof(UserCredentialSaveMaskTemp_t) + 0x2 * USER_CREDENTIAL_NUMBER_DEFAULT_MASK_LENGHT];
	uint32_t									addr_mask;
	size_t										offset;
	uint16_t									crc16;
	uint16_t									id_tmp;

	mask_temp = (UserCredentialSaveMaskTemp_t *)&mask[0x0];
	mask_size = sizeof(UserCredentialSaveMaskTemp_t) + 0x2 * mask_lenght;
	while (id < id_max) {
		offset = (id) / (mask_lenght);
		addr_mask = (addr) + (offset * (mask_size * 0x2)) + (offset * ((mask_lenght) * leght));
		zunoEEPROMRead(addr_mask, mask_size, (byte *)&mask);
		crc16 = CrcClass::crc16_ccitt_aug(&mask_temp->crc16_mask[0x0], 0x2 * mask_lenght);
		if (memcmp(&crc16, &mask_temp->crc16[0x0], sizeof(crc16)) == 0x0) {
			id_tmp = id + mask_lenght;
			while (id < id_tmp && id < id_max) {
				if (_get_eeprom_data_add(addr_mask, mask_size, mask_lenght, id, mask_temp, buffer, leght, offset_crc16) == true) {
					return (id + 0x1);
				}
				id++;
			}
			continue ;
		}
		id = id + mask_lenght;
	}
	return (0x0);
}

static uint16_t _get_next_credential(uint16_t CredentialSlot, uint32_t addr, UserCredentialSaveCredential_t *credential, const UserCredentialSaveArg_t *arg) {
	return (_get_next(CredentialSlot, arg->CredentialSlotMax, arg->mask_lenght, addr, credential, sizeof(credential[0x0]) + arg->CredentialLengthMax, sizeof(credential[0x0])));
}
static uint16_t _get_next_user(uint16_t userIdentifier) {
	UserCredentialSaveUserId_t					user;

	return (_get_next(userIdentifier, USER_CREDENTIAL_NUMBER, USER_CREDENTIAL_NUMBER_MASK_LENGHT, USER_CREDENTIAL_ADDR_USER, &user, sizeof(user), 0x0));
}

static void _get_next_user_struct(uint16_t userIdentifier, uint8_t *next_id) {
	uint16_t									NextUserIdentifier;

	NextUserIdentifier = _get_next_user(userIdentifier);
	next_id[0x0] = NextUserIdentifier >> 0x8;
	next_id[0x1] = NextUserIdentifier;
}

typedef struct					UserCredentialCapabilitiesUserReport_s
{
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						userIdentifier[0x2];/*MSB - LSB*/
	uint8_t						SupportedCredentialRulesBitMask;
	uint8_t						MaxLengthofUserName;
	uint8_t						property1;
	uint8_t						SupportedUserTypesBitMaskLength;
	uint8_t						SupportedUserTypesBitMask[];
}								UserCredentialCapabilitiesUserReport_t;

static int _user_credential_capabilities_user_report(ZUNOCommandPacketReport_t *frame_report) {
	UserCredentialCapabilitiesUserReport_t			*report;
	uint8_t											len;

	report = (UserCredentialCapabilitiesUserReport_t *)frame_report->packet.cmd;
	// report->cmdClass = COMMAND_CLASS_USER_CREDENTIAL; set in - fillOutgoingPacket
	// report->cmd = USER_CREDENTIAL_CAPABILITIES_USER_REPORT; set in - fillOutgoingPacket
	report->userIdentifier[0x0] = USER_CREDENTIAL_NUMBER >> 0x8;
	report->userIdentifier[0x1] = USER_CREDENTIAL_NUMBER;
	report->SupportedCredentialRulesBitMask = _user_supported_credential_rules_mask;
	report->MaxLengthofUserName = USER_CREDENTIAL_NAME_MAX_LENGHT;
	report->property1 = (0x1 << USER_CREDENTIAL_SUPPORT_CHECKSUM_ALL_USERS) | (0x1 << USER_CREDENTIAL_SUPPORT_CHECKSUM_USER);
	#ifdef WITH_CC_SCHEDULE_ENTRY_LOCK
	report->property1 = report->property1 | (0x1 << USER_CREDENTIAL_SUPPORT_SCHEDULE);
	#endif
	len = ((((sizeof(MASK_OF_SUPPORTED_USER_TYPES) * 0x8) - __builtin_clz(MASK_OF_SUPPORTED_USER_TYPES)) >> 0x3) + 0x1);
	report->SupportedUserTypesBitMaskLength = len;
	frame_report->packet.len = sizeof(report[0x0]) + len;
	memcpy(&report->SupportedUserTypesBitMask[0x0], (uint8_t *)&MASK_OF_SUPPORTED_USER_TYPES, len);
	return (ZUNO_COMMAND_ANSWERED);
}

typedef struct					UserCredentialCapabilitiesCredentialReport_s
{
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						profile1;
	uint8_t						NumberOfSupportedCredentialTypes;
	uint8_t						CredentialType[NUMBER_OF_SUPPORTED_CREDENTIAL_TYPES];
	uint8_t						CLSupport[NUMBER_OF_SUPPORTED_CREDENTIAL_TYPES];
	uint8_t						NumberofSupportedCredentialSlots[NUMBER_OF_SUPPORTED_CREDENTIAL_TYPES * 0x2];
	uint8_t						MinLengthOfCredentialData[NUMBER_OF_SUPPORTED_CREDENTIAL_TYPES * 0x2];
	uint8_t						MaxLengthOfCredentialData[NUMBER_OF_SUPPORTED_CREDENTIAL_TYPES * 0x2];
	uint8_t						CLRecommendedTimeout[NUMBER_OF_SUPPORTED_CREDENTIAL_TYPES * 0x2];
	uint8_t						CLNumberOfSteps[NUMBER_OF_SUPPORTED_CREDENTIAL_TYPES * 0x2];
}								UserCredentialCapabilitiesCredentialReport_t;

static int _user_credential_capabilities_credential_report(ZUNOCommandPacketReport_t *frame_report) {
	UserCredentialCapabilitiesCredentialReport_t				*report;
	size_t														i;

	report = (UserCredentialCapabilitiesCredentialReport_t *)frame_report->packet.cmd;
	// report->cmdClass = COMMAND_CLASS_USER_CREDENTIAL; set in - fillOutgoingPacket
	// report->cmd = USER_CREDENTIAL_CAPABILITIES_CREDENTIAL_REPORT; set in - fillOutgoingPacket
	report->profile1 = (0x1 << USER_CREDENTIAL_SUPPORT_CHECKSUM_CREDENTIAL);
	report->NumberOfSupportedCredentialTypes = NUMBER_OF_SUPPORTED_CREDENTIAL_TYPES;
	i = 0x0;
	#if defined(USER_CREDENTIAL_NUMBER_PIN_CODE)
	report->CredentialType[i] = USER_CREDENTIAL_TYPE_PIN_CODE;
	report->CLSupport[i] = 0x0;
	report->NumberofSupportedCredentialSlots[0x2 * i + 0x0] = USER_CREDENTIAL_NUMBER_PIN_CODE >> 0x8;
	report->NumberofSupportedCredentialSlots[0x2 * i + 0x1] = USER_CREDENTIAL_NUMBER_PIN_CODE;
	report->MinLengthOfCredentialData[0x2 * i + 0x0] = USER_CREDENTIAL_NUMBER_PIN_CODE_MIN_LENGHT >> 0x8;
	report->MinLengthOfCredentialData[0x2 * i + 0x1] = USER_CREDENTIAL_NUMBER_PIN_CODE_MIN_LENGHT;
	report->MaxLengthOfCredentialData[0x2 * i + 0x0] = USER_CREDENTIAL_NUMBER_PIN_CODE_MAX_LENGHT >> 0x8;
	report->MaxLengthOfCredentialData[0x2 * i + 0x1] = USER_CREDENTIAL_NUMBER_PIN_CODE_MAX_LENGHT;
	report->CLRecommendedTimeout[i] = 0x0;
	report->CLNumberOfSteps[i] = 0x0;
	i++;
	#endif
	#if defined(USER_CREDENTIAL_NUMBER_PASSWORD)
	report->CredentialType[i] = USER_CREDENTIAL_TYPE_PASSWORD;
	report->CLSupport[i] = 0x0;
	report->NumberofSupportedCredentialSlots[0x2 * i + 0x0] = USER_CREDENTIAL_NUMBER_PASSWORD >> 0x8;
	report->NumberofSupportedCredentialSlots[0x2 * i + 0x1] = USER_CREDENTIAL_NUMBER_PASSWORD;
	report->MinLengthOfCredentialData[0x2 * i + 0x0] = USER_CREDENTIAL_NUMBER_PASSWORD_MIN_LENGHT >> 0x8;
	report->MinLengthOfCredentialData[0x2 * i + 0x1] = USER_CREDENTIAL_NUMBER_PASSWORD_MIN_LENGHT;
	report->MaxLengthOfCredentialData[0x2 * i + 0x0] = USER_CREDENTIAL_NUMBER_PASSWORD_MAX_LENGHT >> 0x8;
	report->MaxLengthOfCredentialData[0x2 * i + 0x1] = USER_CREDENTIAL_NUMBER_PASSWORD_MAX_LENGHT;
	report->CLRecommendedTimeout[i] = 0x0;
	report->CLNumberOfSteps[i] = 0x0;
	i++;
	#endif
	#if defined(USER_CREDENTIAL_NUMBER_RFID_CODE)
	report->CredentialType[i] = USER_CREDENTIAL_TYPE_RFID_CODE;
	report->CLSupport[i] = 0x0;
	report->NumberofSupportedCredentialSlots[0x2 * i + 0x0] = USER_CREDENTIAL_NUMBER_RFID_CODE >> 0x8;
	report->NumberofSupportedCredentialSlots[0x2 * i + 0x1] = USER_CREDENTIAL_NUMBER_RFID_CODE;
	report->MinLengthOfCredentialData[0x2 * i + 0x0] = USER_CREDENTIAL_NUMBER_RFID_CODE_MIN_LENGHT >> 0x8;
	report->MinLengthOfCredentialData[0x2 * i + 0x1] = USER_CREDENTIAL_NUMBER_RFID_CODE_MIN_LENGHT;
	report->MaxLengthOfCredentialData[0x2 * i + 0x0] = USER_CREDENTIAL_NUMBER_RFID_CODE_MAX_LENGHT >> 0x8;
	report->MaxLengthOfCredentialData[0x2 * i + 0x1] = USER_CREDENTIAL_NUMBER_RFID_CODE_MAX_LENGHT;
	report->CLRecommendedTimeout[i] = 0x0;
	report->CLNumberOfSteps[i] = 0x0;
	i++;
	#endif
	frame_report->packet.len = sizeof(report[0x0]);
	return (ZUNO_COMMAND_ANSWERED);
}

typedef struct					UserCredentialUserReportGet_s
{
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						NextUserIdentifier[0x2];/*MSB - LSB*/
	uint8_t						UserModifierType;
	uint8_t						UserModifierNodeID[0x2];/*MSB - LSB*/
	uint8_t						UserUniqueIdentifier[0x2];/*MSB - LSB*/
	UserCredentialSaveUserIdInfoSet_t	set;
}								UserCredentialUserReportGet_t;

typedef struct					UserCredentialUserGet_s
{
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						UserUniqueIdentifier[0x2];/*MSB - LSB*/
}								UserCredentialUserGet_t;

static int _user_credential_user_report_get_not(ZUNOCommandPacketReport_t *frame_report, UserCredentialUserReportGet_t *report, uint16_t userIdentifier) {
	_get_next_user_struct(userIdentifier, &report->NextUserIdentifier[0x0]);
	report->UserModifierType = USER_CREDENTIAL_MODIFY_TYPE_DNE;
	report->set.UserNameLength = 0x0;
	frame_report->packet.len = (sizeof(report[0x0]) - sizeof(report->set.UserName));
	return (ZUNO_COMMAND_ANSWERED);
}

extern "C" size_t zwaveme_utoa_base(size_t value, void *str, size_t base);
static int _user_credential_user_report_get(ZUNOCommandPacketReport_t *frame_report, const UserCredentialUserGet_t *in) {
	UserCredentialUserReportGet_t				*report;
	uint16_t									userIdentifier;
	UserCredentialSaveUserId_t					save_user;
	static const char							default_name[] = "User-";
	size_t										offset;
	size_t										lenght;
	char										buffer[10];

	userIdentifier = (in->UserUniqueIdentifier[0x0] << 0x8) | in->UserUniqueIdentifier[0x1];
	report = (UserCredentialUserReportGet_t *)frame_report->packet.cmd;
	// report->cmdClass = USER_CREDENTIAL_USER_GET; set in - fillOutgoingPacket
	// report->cmd = USER_CREDENTIAL_USER_REPORT; set in - fillOutgoingPacket
	report->UserUniqueIdentifier[0x0] = userIdentifier >> 0x8;
	report->UserUniqueIdentifier[0x1] = userIdentifier;
	if (userIdentifier < 0x1 || userIdentifier > USER_CREDENTIAL_NUMBER)
		return (_user_credential_user_report_get_not(frame_report, report, userIdentifier));
	if (_read_eeprom_id_user(userIdentifier, &save_user, sizeof(save_user)) == false)
		return (_user_credential_user_report_get_not(frame_report, report, userIdentifier));
	_get_next_user_struct(userIdentifier, &report->NextUserIdentifier[0x0]);
	report->UserModifierType = save_user.UserModifierType;
	memcpy(&report->UserModifierNodeID[0x0], &save_user.UserModifierNodeID[0x0], sizeof(report->UserModifierNodeID));
	report->set = save_user.set;
	if (report->set.UserNameLength == 0x0) {
		offset = sizeof(default_name) - 0x1;
		if (offset > sizeof(report->set.UserName))
			offset = sizeof(report->set.UserName);
		memcpy(&report->set.UserName[0x0], default_name, offset);
		if (offset < sizeof(report->set.UserName)) {
			lenght = zwaveme_utoa_base(userIdentifier, &buffer[0x0], 0xA);
			if (offset + lenght > sizeof(report->set.UserName))
				lenght = sizeof(report->set.UserName) - offset;
			memcpy(&report->set.UserName[offset], &buffer[0x0], lenght);
			offset = offset + lenght;
		}
		report->set.UserNameLength = offset;
	}
	frame_report->packet.len = sizeof(report[0x0]) - (sizeof(report->set.UserName) - report->set.UserNameLength);
	return (ZUNO_COMMAND_ANSWERED);
}

typedef struct					UserCredentialUserSet_s
{
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						profile1;
	uint8_t						UserUniqueIdentifier[0x2];/*MSB - LSB*/
	UserCredentialSaveUserIdInfoSet_t	set;
}								UserCredentialUserSet_t;

#define USER_CREDENTIAL_USER_SET_OPERATION_MASK										0x3
#define USER_CREDENTIAL_USER_SET_OPERATION_SHIFT									0x0
#define USER_CREDENTIAL_USER_SET_OPERATION_ADD										0x0
#define USER_CREDENTIAL_USER_SET_OPERATION_MODIFY									0x1
#define USER_CREDENTIAL_USER_SET_OPERATION_DELETE									0x2

#define USER_CREDENTIAL_USER_SET_USER_ACTIVE_STATE_MASK								0x1
#define USER_CREDENTIAL_USER_SET_USER_ACTIVE_STATE_SHIFT							0x0

#define USER_CREDENTIAL_USER_SET_USER_NAME_ENCODING_MASK							0x7
#define USER_CREDENTIAL_USER_SET_USER_NAME_ENCODING_SHIFT							0x0
#define USER_CREDENTIAL_USER_SET_USER_NAME_ENCODING_ASCII							0x0
#define USER_CREDENTIAL_USER_SET_USER_NAME_ENCODING_OEM_ASCII						0x1
#define USER_CREDENTIAL_USER_SET_USER_NAME_ENCODING_UTF16							0x2

static bool _user_credential_user_set_valid_in(UserCredentialSaveUserIdInfoSet_t *set, uint16_t UserUniqueIdentifier) {
	uint8_t													UserType;
	uint8_t													CredentialRule;
	uint8_t													UserNameEncoding;

	if (UserUniqueIdentifier < 0x1)
		return (false);
	UserType = set->UserType;
	if (UserType >= (sizeof(MASK_OF_SUPPORTED_USER_TYPES) * 0x8) || (MASK_OF_SUPPORTED_USER_TYPES & (0x1 << UserType)) == 0x0)
		return (false);
	set->profile2 = set->profile2 & USER_CREDENTIAL_USER_SET_USER_ACTIVE_STATE_MASK;
	CredentialRule = set->CredentialRule;
	if (CredentialRule >= (sizeof(_user_supported_credential_rules_mask) * 0x8) || (_user_supported_credential_rules_mask & (0x1 << CredentialRule)) == 0x0)
		return (false);
	UserNameEncoding = ((set->profile3 & USER_CREDENTIAL_USER_SET_USER_NAME_ENCODING_MASK) >> USER_CREDENTIAL_USER_SET_USER_NAME_ENCODING_SHIFT);
	switch (UserNameEncoding) {
		case USER_CREDENTIAL_USER_SET_USER_NAME_ENCODING_ASCII:
		case USER_CREDENTIAL_USER_SET_USER_NAME_ENCODING_OEM_ASCII:
		case USER_CREDENTIAL_USER_SET_USER_NAME_ENCODING_UTF16:
			break ;
		default:
			return (false);
			break ;
	}
	set->profile3 = UserNameEncoding;
	if (set->UserNameLength > sizeof(set->UserName))
		return (false);
	return (true);
}

static int _user_credential_user_set_add(ZUNOCommandPacket_t *cmd, const UserCredentialUserSet_t *in, uint16_t UserUniqueIdentifier) {
	UserCredentialSaveUserId_t									save_user_id;

	if (_read_eeprom_id_user(UserUniqueIdentifier, &save_user_id, sizeof(save_user_id)) == true)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	save_user_id.set = in->set;
	if (_user_credential_user_set_valid_in(&save_user_id.set, UserUniqueIdentifier) == false)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	save_user_id.UserModifierType = USER_CREDENTIAL_MODIFY_TYPE_ZWAVE;
	save_user_id.UserModifierNodeID[0x0] = cmd->src_node >> 0x8;
	save_user_id.UserModifierNodeID[0x1] = cmd->src_node;
	_write_eeprom_id_user(UserUniqueIdentifier, &save_user_id, sizeof(save_user_id));
	return (ZUNO_COMMAND_PROCESSED);
}

static int _user_credential_user_set_modify(ZUNOCommandPacket_t *cmd, const UserCredentialUserSet_t *in, uint16_t UserUniqueIdentifier) {
	UserCredentialSaveUserId_t									save_user_id;
	uint16_t													crc16;

	if (_read_eeprom_id_user(UserUniqueIdentifier, &save_user_id, sizeof(save_user_id)) == false)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	crc16 = CrcClass::crc16_ccitt_aug(&save_user_id, sizeof(save_user_id));
	save_user_id.set = in->set;
	if (_user_credential_user_set_valid_in(&save_user_id.set, UserUniqueIdentifier) == false)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	save_user_id.UserModifierType = USER_CREDENTIAL_MODIFY_TYPE_ZWAVE;
	save_user_id.UserModifierNodeID[0x0] = cmd->src_node >> 0x8;
	save_user_id.UserModifierNodeID[0x1] = cmd->src_node;
	if (CrcClass::crc16_ccitt_aug(&save_user_id, sizeof(save_user_id)) == crc16)
		return (ZUNO_COMMAND_PROCESSED);
	_write_eeprom_id_user(UserUniqueIdentifier, &save_user_id, sizeof(save_user_id));
	return (ZUNO_COMMAND_PROCESSED);
}

static int _user_credential_user_set_del(uint16_t UserUniqueIdentifier) {
	_del_user(UserUniqueIdentifier);
	return (ZUNO_COMMAND_PROCESSED);
}


static int _user_credential_user_set(ZUNOCommandPacket_t *cmd, const UserCredentialUserSet_t *in) {
	uint16_t										UserUniqueIdentifier;
	int												rs;

	UserUniqueIdentifier = (in->UserUniqueIdentifier[0x0] << 0x8) | in->UserUniqueIdentifier[0x1];
	if (UserUniqueIdentifier > USER_CREDENTIAL_NUMBER)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	switch ((in->profile1 & USER_CREDENTIAL_USER_SET_OPERATION_MASK) >> USER_CREDENTIAL_USER_SET_OPERATION_SHIFT) {
		case USER_CREDENTIAL_USER_SET_OPERATION_ADD:
			rs = _user_credential_user_set_add(cmd, in, UserUniqueIdentifier);
			break ;
		case USER_CREDENTIAL_USER_SET_OPERATION_MODIFY:
			rs = _user_credential_user_set_modify(cmd, in, UserUniqueIdentifier);
			break ;
		case USER_CREDENTIAL_USER_SET_OPERATION_DELETE:
			rs = _user_credential_user_set_del(UserUniqueIdentifier);
			break ;
		default:
			rs = ZUNO_COMMAND_BLOCKED_FAILL;
			break;
	}
	return (rs);
}

typedef struct					UserCredentialCredentialSet_s
{
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						UserUniqueIdentifier[0x2];/*MSB - LSB*/
	uint8_t						CredentialType;
	uint8_t						CredentialSlot[0x2];/*MSB - LSB*/
	uint8_t						profile1;
	uint8_t						CredentialLength;
	uint8_t						CredentialData[];
}								UserCredentialCredentialSet_t;


static int _user_credential_credential_set_add(ZUNOCommandPacket_t *cmd, const UserCredentialCredentialSet_t *in, UserCredentialSaveCredential_t *credential, uint32_t addr, uint16_t CredentialSlot, uint16_t UserUniqueIdentifier, const UserCredentialSaveArg_t *arg) {
	uint8_t											CredentialLength;
	UserCredentialSaveUserId_t						save_user;
	uint16_t										crc16;

	if (_read_eeprom_id_user(UserUniqueIdentifier, &save_user, sizeof(save_user)) == false)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	if (_read_eeprom_id_credential(CredentialSlot, addr, credential, arg) == true)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	credential->CredentialModifierType = USER_CREDENTIAL_MODIFY_TYPE_ZWAVE;
	credential->CredentialModifierNodeID[0x0] = cmd->src_node >> 0x8;
	credential->CredentialModifierNodeID[0x1] = cmd->src_node;
	CredentialLength = in->CredentialLength;
	credential->CredentialLength = CredentialLength;
	memcpy(&credential->CredentialData[0x0], &in->CredentialData[0x0], CredentialLength);
	memset(&credential->CredentialData[CredentialLength], 0x0, arg->CredentialLengthMax - CredentialLength);
	crc16 = CrcClass::crc16_ccitt_aug(&credential->CredentialData[0x0], arg->CredentialLengthMax);
	if (_credential_test_uniq(crc16) == true)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	_write_eeprom_id_credential(CredentialSlot, addr, credential, arg);
	return (ZUNO_COMMAND_PROCESSED);
}

static int _user_credential_credential_set_modify(ZUNOCommandPacket_t *cmd, const UserCredentialCredentialSet_t *in, UserCredentialSaveCredential_t *credential, uint32_t addr, uint16_t CredentialSlot, const UserCredentialSaveArg_t *arg) {
	uint16_t													crc16;
	uint8_t														CredentialLength;

	if (_read_eeprom_id_credential(CredentialSlot, addr, credential, arg) == false)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	crc16 = CrcClass::crc16_ccitt_aug(credential, sizeof(credential[0x0]) + arg->CredentialLengthMax);
	credential->CredentialModifierType = USER_CREDENTIAL_MODIFY_TYPE_ZWAVE;
	credential->CredentialModifierNodeID[0x0] = cmd->src_node >> 0x8;
	credential->CredentialModifierNodeID[0x1] = cmd->src_node;
	CredentialLength = in->CredentialLength;
	credential->CredentialLength = CredentialLength;
	memcpy(&credential->CredentialData[0x0], &in->CredentialData[0x0], CredentialLength);
	memset(&credential->CredentialData[CredentialLength], 0x0, arg->CredentialLengthMax - CredentialLength);
	if (CrcClass::crc16_ccitt_aug(credential, sizeof(credential[0x0]) + arg->CredentialLengthMax) == crc16)
		return (ZUNO_COMMAND_PROCESSED);
	crc16 = CrcClass::crc16_ccitt_aug(&credential->CredentialData[0x0], arg->CredentialLengthMax);
	if (_credential_test_uniq(crc16) == true)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	_write_eeprom_id_credential(CredentialSlot, addr, credential, arg);
	return (ZUNO_COMMAND_PROCESSED);
}

static int _user_credential_credential_set_del(uint16_t UserUniqueIdentifier, uint16_t CredentialSlot, uint8_t CredentialType) {
	uint32_t										addr;
	#if defined(USER_CREDENTIAL_NUMBER_PIN_CODE)
	uint8_t											PIN_CODE[(sizeof(UserCredentialSaveCredential_t) + USER_CREDENTIAL_NUMBER_PIN_CODE_MAX_LENGHT)];
	#endif
	UserCredentialSaveCredential_t					*credential;
	const UserCredentialSaveArg_t					*arg;

	if (CredentialSlot == 0x0 && CredentialType != 0x0) {
		if (UserUniqueIdentifier == 0x0) {
			_delete_eeprom_credential_all_full_user_one_type(CredentialType);
			return (ZUNO_COMMAND_PROCESSED);
		}
		_delete_eeprom_credential_all_one_user_one_type(UserUniqueIdentifier, CredentialType);
		return (ZUNO_COMMAND_PROCESSED);
	}
	if (UserUniqueIdentifier == 0x0) {
		_delete_eeprom_credential_all_full_user();
		return (ZUNO_COMMAND_PROCESSED);
	}
	if (CredentialType == 0x0) {
		_delete_eeprom_credential_all_one_user(UserUniqueIdentifier);
		return (ZUNO_COMMAND_PROCESSED);
	}
	if (CredentialSlot == 0x0)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	switch (CredentialType) {
		#if defined(USER_CREDENTIAL_NUMBER_PIN_CODE)
		USER_CREDENTIAL_SWTCH_SET_ARG(PIN_CODE)
		#endif
		#if defined(USER_CREDENTIAL_NUMBER_PASSWORD)
		USER_CREDENTIAL_SWTCH_SET_ARG(PASSWORD)
		#endif
		#if defined(USER_CREDENTIAL_NUMBER_RFID_CODE)
		USER_CREDENTIAL_SWTCH_SET_ARG(RFID_CODE)
		#endif
		default:
			return (ZUNO_COMMAND_BLOCKED_FAILL);
			break ;
	}
	_delete_eeprom_id(addr, arg->mask_lenght, CredentialSlot, sizeof(credential[0x0]) + arg->CredentialLengthMax);
	return (ZUNO_COMMAND_PROCESSED);
}

static int _user_credential_credential_set(ZUNOCommandPacket_t *cmd, const UserCredentialCredentialSet_t *in) {
	uint16_t										UserUniqueIdentifier;
	uint8_t											operation_type;
	uint8_t											CredentialType;
	uint16_t										CredentialSlot;
	int												rs;
	uint32_t										addr;
	#if defined(USER_CREDENTIAL_NUMBER_PIN_CODE)
	uint8_t											PIN_CODE[(sizeof(UserCredentialSaveCredential_t) + USER_CREDENTIAL_NUMBER_PIN_CODE_MAX_LENGHT)];
	#endif
	UserCredentialSaveCredential_t					*credential;
	const UserCredentialSaveArg_t					*arg;

	UserUniqueIdentifier = (in->UserUniqueIdentifier[0x0] << 0x8) | in->UserUniqueIdentifier[0x1];
	if (UserUniqueIdentifier > USER_CREDENTIAL_NUMBER)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	CredentialSlot = (in->CredentialSlot[0x0] << 0x8) | in->CredentialSlot[0x1];
	operation_type = (in->profile1 & USER_CREDENTIAL_USER_SET_OPERATION_MASK) >> USER_CREDENTIAL_USER_SET_OPERATION_SHIFT;
	CredentialType = in->CredentialType;
	if (operation_type == USER_CREDENTIAL_USER_SET_OPERATION_DELETE)
		return (_user_credential_credential_set_del(UserUniqueIdentifier, CredentialSlot, CredentialType));
	switch (CredentialType) {
		#if defined(USER_CREDENTIAL_NUMBER_PIN_CODE)
		USER_CREDENTIAL_SWTCH_SET_ARG(PIN_CODE)
		#endif
		#if defined(USER_CREDENTIAL_NUMBER_PASSWORD)
		USER_CREDENTIAL_SWTCH_SET_ARG(PASSWORD)
		#endif
		#if defined(USER_CREDENTIAL_NUMBER_RFID_CODE)
		USER_CREDENTIAL_SWTCH_SET_ARG(RFID_CODE)
		#endif
		default:
			return (ZUNO_COMMAND_BLOCKED_FAILL);
			break ;
	}
	if (UserUniqueIdentifier == 0x0)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	if (CredentialSlot == 0x0)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	if (CredentialSlot > arg->CredentialSlotMax)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	if (in->CredentialLength > arg->CredentialLengthMax || in->CredentialLength < arg->CredentialLengthMin)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	switch ((in->profile1 & USER_CREDENTIAL_USER_SET_OPERATION_MASK) >> USER_CREDENTIAL_USER_SET_OPERATION_SHIFT) {
		case USER_CREDENTIAL_USER_SET_OPERATION_ADD:
			rs = _user_credential_credential_set_add(cmd, in, credential, addr, CredentialSlot, UserUniqueIdentifier, arg);
			break ;
		case USER_CREDENTIAL_USER_SET_OPERATION_MODIFY:
			rs = _user_credential_credential_set_modify(cmd, in, credential, addr, CredentialSlot, arg);
			break ;
		default:
			rs = ZUNO_COMMAND_BLOCKED_FAILL;
			break;
	}
	return (rs);
}

typedef struct					UserCredentialCredentialGetInfo_s
{
	uint8_t						UserUniqueIdentifier[0x2];/*MSB - LSB*/
	uint8_t						CredentialType;
	uint8_t						CredentialSlot[0x2];/*MSB - LSB*/
}								UserCredentialCredentialGetInfo_t;

typedef struct					UserCredentialCredentialGet_s
{
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	UserCredentialCredentialGetInfo_t	pre;
}								UserCredentialCredentialGet_t;

typedef struct					UserCredentialCredentialReportGet_s
{
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	UserCredentialCredentialGetInfo_t	pre;
	uint8_t						profile1;
	uint8_t						CredentialLength;
	uint8_t						CredentialData[];
}								UserCredentialCredentialReportGet_t;

typedef struct					UserCredentialCredentialReportGetEnd_s
{
	uint8_t						CredentialModifierType;
	uint8_t						CredentialModifierNodeID[0x2];/*MSB - LSB*/
	uint8_t						NextCredentialType;
	uint8_t						NextCredentialSlot[0x2];/*MSB - LSB*/
}								UserCredentialCredentialReportGetEnd_t;

static uint16_t _user_credential_credential_report_get_next_any(uint8_t CredentialType, uint16_t UserUniqueIdentifier, uint8_t *NextCredentialType) {
	uint32_t										addr;
	#if defined(USER_CREDENTIAL_NUMBER_PIN_CODE)
	uint8_t											PIN_CODE[(sizeof(UserCredentialSaveCredential_t) + USER_CREDENTIAL_NUMBER_PIN_CODE_MAX_LENGHT)];
	#endif
	UserCredentialSaveCredential_t					*credential;
	const UserCredentialSaveArg_t					*arg;
	uint32_t										CredentialTypeMask;
	uint16_t										NextUserIdentifier;

	CredentialTypeMask = MASK_OF_SUPPORTED_CREDENTIAL_TYPES >> CredentialType;
	while (true) {
		CredentialType++;
		CredentialTypeMask = CredentialTypeMask >> 0x1;
		if (CredentialTypeMask == 0x0)
			return (0x0);
		if ((CredentialTypeMask & 0x1) == 0x0)
			continue ;
		switch (CredentialType) {
			#if defined(USER_CREDENTIAL_NUMBER_PIN_CODE)
			USER_CREDENTIAL_SWTCH_SET_ARG(PIN_CODE)
			#endif
			#if defined(USER_CREDENTIAL_NUMBER_PASSWORD)
			USER_CREDENTIAL_SWTCH_SET_ARG(PASSWORD)
			#endif
			#if defined(USER_CREDENTIAL_NUMBER_RFID_CODE)
			USER_CREDENTIAL_SWTCH_SET_ARG(RFID_CODE)
			#endif
			default:
				arg = NULL;
				break ;
		}
		if (arg == NULL)
			continue ;
		NextUserIdentifier = _get_next_credential(0x0, addr, credential, arg);
		if (NextUserIdentifier == 0x0)
			continue ;
		NextCredentialType[0x0] = CredentialType;
		return (NextUserIdentifier);
	}
	return (0x0);
}

static int _user_credential_credential_report_get_not(ZUNOCommandPacketReport_t *frame_report, UserCredentialCredentialReportGet_t *report, uint16_t UserUniqueIdentifier) {
	uint16_t										NextUserIdentifier;
	UserCredentialCredentialReportGetEnd_t			*report_end;

	report->CredentialLength = 0x0;
	report_end = (UserCredentialCredentialReportGetEnd_t *)(frame_report->packet.cmd + sizeof(report[0x0]));
	NextUserIdentifier = _user_credential_credential_report_get_next_any(0x0, UserUniqueIdentifier, &report_end->NextCredentialType);
	if (NextUserIdentifier == 0x0)
		report_end->NextCredentialType = 0x0;
	report_end->NextCredentialSlot[0x0] = NextUserIdentifier >> 0x8;
	report_end->NextCredentialSlot[0x1] = NextUserIdentifier;
	frame_report->packet.len = sizeof(report[0x0]) + sizeof(report_end[0x0]);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _user_credential_credential_report_get(ZUNOCommandPacketReport_t *frame_report, const UserCredentialCredentialGet_t *in) {
	UserCredentialCredentialReportGet_t				*report;
	UserCredentialCredentialReportGetEnd_t			*report_end;
	uint16_t										UserUniqueIdentifier;
	uint16_t										CredentialSlot;
	uint16_t										NextUserIdentifier;
	uint32_t										addr;
	#if defined(USER_CREDENTIAL_NUMBER_PIN_CODE)
	uint8_t											PIN_CODE[(sizeof(UserCredentialSaveCredential_t) + USER_CREDENTIAL_NUMBER_PIN_CODE_MAX_LENGHT)];
	#endif
	UserCredentialSaveCredential_t					*credential;
	const UserCredentialSaveArg_t					*arg;

	report = (UserCredentialCredentialReportGet_t *)frame_report->packet.cmd;
	// report->cmdClass = COMMAND_CLASS_USER_CREDENTIAL; set in - fillOutgoingPacket
	// report->cmd = USER_CREDENTIAL_CREDENTIAL_REPORT; set in - fillOutgoingPacket
	report->pre = in->pre;
	report->profile1 = 0x0;
	UserUniqueIdentifier = (in->pre.UserUniqueIdentifier[0x0] << 0x8) | in->pre.UserUniqueIdentifier[0x1];
	CredentialSlot = (in->pre.CredentialSlot[0x0] << 0x8) | in->pre.CredentialSlot[0x1];
	if (UserUniqueIdentifier > USER_CREDENTIAL_NUMBER || UserUniqueIdentifier < 0x1)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	if (CredentialSlot == 0x0 && in->pre.CredentialType == 0x0)
		return (_user_credential_credential_report_get_not(frame_report, report, UserUniqueIdentifier));
	if (CredentialSlot < 0x1)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	switch (in->pre.CredentialType) {
		#if defined(USER_CREDENTIAL_NUMBER_PIN_CODE)
		USER_CREDENTIAL_SWTCH_SET_ARG(PIN_CODE)
		#endif
		#if defined(USER_CREDENTIAL_NUMBER_PASSWORD)
		USER_CREDENTIAL_SWTCH_SET_ARG(PASSWORD)
		#endif
		#if defined(USER_CREDENTIAL_NUMBER_RFID_CODE)
		USER_CREDENTIAL_SWTCH_SET_ARG(RFID_CODE)
		#endif
		default:
			return (ZUNO_COMMAND_BLOCKED_FAILL);
			break ;
	}
	if (CredentialSlot > arg->CredentialSlotMax)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	if (_read_eeprom_id_credential(CredentialSlot, addr, credential, arg) == false)
		return (_user_credential_credential_report_get_not(frame_report, report, UserUniqueIdentifier));
	report->CredentialLength = credential->CredentialLength;
	memcpy(&report->CredentialData[0x0], &credential->CredentialData[0x0], report->CredentialLength);
	report_end = (UserCredentialCredentialReportGetEnd_t *)(frame_report->packet.cmd + sizeof(report[0x0]) + report->CredentialLength);
	report_end->CredentialModifierType = credential->CredentialModifierType;
	report_end->NextCredentialType = in->pre.CredentialType;
	memcpy(&report_end->CredentialModifierNodeID[0x0], &credential->CredentialModifierNodeID[0x0], sizeof(report_end->CredentialModifierNodeID));
	NextUserIdentifier = _get_next_credential(CredentialSlot, addr, credential, arg);
	if (NextUserIdentifier == 0x0) {
		NextUserIdentifier = _user_credential_credential_report_get_next_any(report_end->NextCredentialType, UserUniqueIdentifier, &report_end->NextCredentialType);
		if (NextUserIdentifier == 0x0)
			report_end->NextCredentialType = 0x0;
	}
	report_end->NextCredentialSlot[0x0] = NextUserIdentifier >> 0x8;
	report_end->NextCredentialSlot[0x1] = NextUserIdentifier;
	frame_report->packet.len = sizeof(report[0x0]) + report->CredentialLength + sizeof(report_end[0x0]);
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCUserCredentialHandler(ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	int								rs;

	switch (ZW_CMD) {
		case USER_CREDENTIAL_CAPABILITIES_USER_GET:
			rs = _user_credential_capabilities_user_report(frame_report);
			break ;
		case USER_CREDENTIAL_CAPABILITIES_CREDENTIAL_GET:
			rs = _user_credential_capabilities_credential_report(frame_report);
			break ;
		case USER_CREDENTIAL_USER_GET:
			rs = _user_credential_user_report_get(frame_report, ((const UserCredentialUserGet_t *)&cmd->cmd[0x0]));
			break ;
		case USER_CREDENTIAL_USER_SET:
			rs = _user_credential_user_set(cmd, ((const UserCredentialUserSet_t *)&cmd->cmd[0x0]));
			break ;
		case USER_CREDENTIAL_CREDENTIAL_SET:
			rs = _user_credential_credential_set(cmd, ((const UserCredentialCredentialSet_t *)&cmd->cmd[0x0]));
			break ;
		case USER_CREDENTIAL_CREDENTIAL_GET:
			rs = _user_credential_credential_report_get(frame_report, ((const UserCredentialCredentialGet_t *)&cmd->cmd[0x0]));
			break ;
		default:
			rs = ZUNO_UNKNOWN_CMD;
			break ;
	}
	return (rs);
	(void)cmd;
	(void)frame_report;
}


static bool _user_credential_find_key(const uint8_t *CredentialData, uint8_t CredentialLength, UserCredentialSaveCredential_t *credential, const UserCredentialSaveArg_t *arg) {
	uint16_t													crc16;

	crc16 = CrcClass::crc16_ccitt_aug(credential, sizeof(credential[0x0]) + arg->CredentialLengthMax);
	credential->CredentialLength = CredentialLength;
	memcpy(&credential->CredentialData[0x0], CredentialData, CredentialLength);
	memset(&credential->CredentialData[CredentialLength], 0x0, arg->CredentialLengthMax - CredentialLength);
	crc16 = CrcClass::crc16_ccitt_aug(&credential->CredentialData[0x0], arg->CredentialLengthMax);
	if (_credential_test_uniq(crc16) == true)
		return (true);
	return (false);
}


bool user_credential_find_key(const uint8_t *CredentialData, uint8_t CredentialLength) {
	uint8_t											UserUniqueIdentifier;
	uint8_t											CredentialType;
	uint32_t										addr;
	#if defined(USER_CREDENTIAL_NUMBER_PIN_CODE)
	uint8_t											PIN_CODE[(sizeof(UserCredentialSaveCredential_t) + USER_CREDENTIAL_NUMBER_PIN_CODE_MAX_LENGHT)];
	#endif
	UserCredentialSaveCredential_t					*credential;
	const UserCredentialSaveArg_t					*arg;

	UserUniqueIdentifier = 0x1;
	CredentialType = USER_CREDENTIAL_TYPE_PIN_CODE;
	switch (CredentialType) {
		#if defined(USER_CREDENTIAL_NUMBER_PIN_CODE)
		USER_CREDENTIAL_SWTCH_SET_ARG(PIN_CODE)
		#endif
		#if defined(USER_CREDENTIAL_NUMBER_PASSWORD)
		USER_CREDENTIAL_SWTCH_SET_ARG(PASSWORD)
		#endif
		#if defined(USER_CREDENTIAL_NUMBER_RFID_CODE)
		USER_CREDENTIAL_SWTCH_SET_ARG(RFID_CODE)
		#endif
		default:
			return (false);
			break ;
	}
	return (_user_credential_find_key(CredentialData, CredentialLength, credential, arg));
	(void)addr;
}


#endif//WITH_CC_USER_CREDENTIAL