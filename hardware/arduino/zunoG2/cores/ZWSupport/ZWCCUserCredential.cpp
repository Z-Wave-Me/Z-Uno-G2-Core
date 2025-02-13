#include "ArduinoTypes.h"
#include "LLCore.h"
#include "ZUNO_Definitions.h"
#include "ZWCCUserCredential.h"
#include "ZWCCSuperVision.h"
#include "CrcClass.h"
#include "EEPROM_Config.h"
#include <malloc.h>
#include "WCharacter.h"
#include "ZW_classcmd.h"

#ifdef WITH_CC_USER_CREDENTIAL

#define USER_CREDENTIAL_RULE_SINGLE													0x1
#define USER_CREDENTIAL_RULE_DUAL													0x2
#define USER_CREDENTIAL_RULE_TRIPLE													0x3

typedef struct ZwUserCredentialCommonUser_s
{
	uint16_t UserUniqueIdentifier;
	uint16_t NextUserIdentifier;
	uint8_t UserReportType;
} ZwUserCredentialCommonUser_t;

typedef struct ZwUserCredentialCommonCredentialFind_s
{
	uint16_t CredentialSlot;
	uint8_t CredentialType;
} ZwUserCredentialCommonCredentialFind_t;

typedef struct UserCredentialStorageInfo_s
{
	uint32_t addr_data;
	uint16_t slot_max;
	uint8_t type;
	uint8_t CredentialLengthMin;
	uint8_t CredentialLengthMax;
} UserCredentialStorageInfo_t;

static_assert(USER_CREDENTIAL_USERS_COUNT <= 0xFFFF && USER_CREDENTIAL_USERS_COUNT >= 0x1, "USER_CREDENTIAL_USERS_COUNT - max 0xFFFF and min 0x1!!!");
#if defined(USER_CREDENTIAL_PIN_CODE_SLOTS_COUNT)
static_assert(USER_CREDENTIAL_PIN_CODE_SLOTS_COUNT <= 0xFFFF && USER_CREDENTIAL_PIN_CODE_SLOTS_COUNT >= 0x1, "USER_CREDENTIAL_PIN_CODE_SLOTS_COUNT - max 0xFFFF and min 0x1!!!");
static_assert(USER_CREDENTIAL_PIN_CODE_MIN_LENGHT >= 0x4, "USER_CREDENTIAL_PIN_CODE_MIN_LENGHT - min 0x4!!!");
static_assert(USER_CREDENTIAL_PIN_CODE_MAX_LENGHT <= 0xFFFF, "USER_CREDENTIAL_PIN_CODE_MAX_LENGHT - max 0xFFFF!!!");
static_assert(USER_CREDENTIAL_PIN_CODE_MIN_LENGHT <= USER_CREDENTIAL_PIN_CODE_MAX_LENGHT, "Must USER_CREDENTIAL_PIN_CODE_MAX_LENGHT < USER_CREDENTIAL_PIN_CODE_MIN_LENGHT!!!");
#endif
#if defined(USER_CREDENTIAL_PASSWORD_SLOTS_COUNT)
static_assert(USER_CREDENTIAL_PASSWORD_SLOTS_COUNT <= 0xFFFF && USER_CREDENTIAL_PASSWORD_SLOTS_COUNT >= 0x1, "USER_CREDENTIAL_PASSWORD_SLOTS_COUNT - max 0xFFFF and min 0x1!!!");
static_assert(USER_CREDENTIAL_PASSWORD_MIN_LENGHT >= 0x1, "USER_CREDENTIAL_PASSWORD_MIN_LENGHT - min 0x1!!!");
static_assert(USER_CREDENTIAL_PASSWORD_MAX_LENGHT <= 0xFFFF, "USER_CREDENTIAL_PASSWORD_MAX_LENGHT - max 0xFFFF!!!");
static_assert(USER_CREDENTIAL_PASSWORD_MIN_LENGHT < USER_CREDENTIAL_PASSWORD_MAX_LENGHT, "Must USER_CREDENTIAL_PASSWORD_MAX_LENGHT < USER_CREDENTIAL_PASSWORD_MIN_LENGHT!!!");
#endif
#if defined(USER_CREDENTIAL_RFID_CODE_SLOTS_COUNT)
static_assert(USER_CREDENTIAL_RFID_CODE_SLOTS_COUNT <= 0xFFFF && USER_CREDENTIAL_RFID_CODE_SLOTS_COUNT >= 0x1, "USER_CREDENTIAL_RFID_CODE_SLOTS_COUNT - max 0xFFFF and min 0x1!!!");
static_assert(USER_CREDENTIAL_RFID_CODE_MIN_LENGHT >= 0x1, "USER_CREDENTIAL_RFID_CODE_MIN_LENGHT - min 0x1!!!");
static_assert(USER_CREDENTIAL_RFID_CODE_MAX_LENGHT <= 0xFFFF, "USER_CREDENTIAL_RFID_CODE_MAX_LENGHT - max 0xFFFF!!!");
static_assert(USER_CREDENTIAL_RFID_CODE_MIN_LENGHT < USER_CREDENTIAL_RFID_CODE_MAX_LENGHT, "Must USER_CREDENTIAL_RFID_CODE_MAX_LENGHT < USER_CREDENTIAL_RFID_CODE_MIN_LENGHT!!!");
#endif
#if defined(USER_CREDENTIAL_BLE_SLOTS_COUNT)
static_assert(USER_CREDENTIAL_BLE_SLOTS_COUNT <= 0xFFFF && USER_CREDENTIAL_BLE_SLOTS_COUNT >= 0x1, "USER_CREDENTIAL_BLE_SLOTS_COUNT - max 0xFFFF and min 0x1!!!");
static_assert(USER_CREDENTIAL_BLE_MIN_LENGHT >= 0x1, "USER_CREDENTIAL_BLE_MIN_LENGHT - min 0x1!!!");
static_assert(USER_CREDENTIAL_BLE_MAX_LENGHT <= 0xFFFF, "USER_CREDENTIAL_BLE_MAX_LENGHT - max 0xFFFF!!!");
static_assert(USER_CREDENTIAL_BLE_MIN_LENGHT < USER_CREDENTIAL_BLE_MAX_LENGHT, "Must USER_CREDENTIAL_BLE_MAX_LENGHT < USER_CREDENTIAL_BLE_MIN_LENGHT!!!");
#endif
#if defined(USER_CREDENTIAL_NFC_SLOTS_COUNT)
static_assert(USER_CREDENTIAL_NFC_SLOTS_COUNT <= 0xFFFF && USER_CREDENTIAL_NFC_SLOTS_COUNT >= 0x1, "USER_CREDENTIAL_NFC_SLOTS_COUNT - max 0xFFFF and min 0x1!!!");
static_assert(USER_CREDENTIAL_NFC_MIN_LENGHT >= 0x1, "USER_CREDENTIAL_NFC_MIN_LENGHT - min 0x1!!!");
static_assert(USER_CREDENTIAL_NFC_MAX_LENGHT <= 0xFFFF, "USER_CREDENTIAL_NFC_MAX_LENGHT - max 0xFFFF!!!");
static_assert(USER_CREDENTIAL_NFC_MIN_LENGHT < USER_CREDENTIAL_NFC_MAX_LENGHT, "Must USER_CREDENTIAL_NFC_MAX_LENGHT < USER_CREDENTIAL_NFC_MIN_LENGHT!!!");
#endif
#if defined(USER_CREDENTIAL_UWB_SLOTS_COUNT)
static_assert(USER_CREDENTIAL_UWB_SLOTS_COUNT <= 0xFFFF && USER_CREDENTIAL_UWB_SLOTS_COUNT >= 0x1, "USER_CREDENTIAL_UWB_SLOTS_COUNT - max 0xFFFF and min 0x1!!!");
static_assert(USER_CREDENTIAL_UWB_MIN_LENGHT >= 0x1, "USER_CREDENTIAL_UWB_MIN_LENGHT - min 0x1!!!");
static_assert(USER_CREDENTIAL_UWB_MAX_LENGHT <= 0xFFFF, "USER_CREDENTIAL_UWB_MAX_LENGHT - max 0xFFFF!!!");
static_assert(USER_CREDENTIAL_UWB_MIN_LENGHT < USER_CREDENTIAL_UWB_MAX_LENGHT, "Must USER_CREDENTIAL_UWB_MAX_LENGHT < USER_CREDENTIAL_UWB_MIN_LENGHT!!!");
#endif
#if defined(USER_CREDENTIAL_EYE_BIOMETRIC_SLOTS_COUNT)
static_assert(USER_CREDENTIAL_EYE_BIOMETRIC_SLOTS_COUNT <= 0xFFFF && USER_CREDENTIAL_EYE_BIOMETRIC_SLOTS_COUNT >= 0x1, "USER_CREDENTIAL_EYE_BIOMETRIC_SLOTS_COUNT - max 0xFFFF and min 0x1!!!");
static_assert(USER_CREDENTIAL_EYE_BIOMETRIC_MIN_LENGHT >= 0x1, "USER_CREDENTIAL_EYE_BIOMETRIC_MIN_LENGHT - min 0x1!!!");
static_assert(USER_CREDENTIAL_EYE_BIOMETRIC_MAX_LENGHT <= 0xFFFF, "USER_CREDENTIAL_EYE_BIOMETRIC_MAX_LENGHT - max 0xFFFF!!!");
static_assert(USER_CREDENTIAL_EYE_BIOMETRIC_MIN_LENGHT < USER_CREDENTIAL_EYE_BIOMETRIC_MAX_LENGHT, "Must USER_CREDENTIAL_EYE_BIOMETRIC_MAX_LENGHT < USER_CREDENTIAL_EYE_BIOMETRIC_MIN_LENGHT!!!");
#endif
#if defined(USER_CREDENTIAL_FACE_BIOMETRIC_SLOTS_COUNT)
static_assert(USER_CREDENTIAL_FACE_BIOMETRIC_SLOTS_COUNT <= 0xFFFF && USER_CREDENTIAL_FACE_BIOMETRIC_SLOTS_COUNT >= 0x1, "USER_CREDENTIAL_FACE_BIOMETRIC_SLOTS_COUNT - max 0xFFFF and min 0x1!!!");
static_assert(USER_CREDENTIAL_FACE_BIOMETRIC_MIN_LENGHT >= 0x1, "USER_CREDENTIAL_FACE_BIOMETRIC_MIN_LENGHT - min 0x1!!!");
static_assert(USER_CREDENTIAL_FACE_BIOMETRIC_MAX_LENGHT <= 0xFFFF, "USER_CREDENTIAL_FACE_BIOMETRIC_MAX_LENGHT - max 0xFFFF!!!");
static_assert(USER_CREDENTIAL_FACE_BIOMETRIC_MIN_LENGHT < USER_CREDENTIAL_FACE_BIOMETRIC_MAX_LENGHT, "Must USER_CREDENTIAL_FACE_BIOMETRIC_MAX_LENGHT < USER_CREDENTIAL_FACE_BIOMETRIC_MIN_LENGHT!!!");
#endif
#if defined(USER_CREDENTIAL_FINGER_BIOMETRIC_SLOTS_COUNT)
static_assert(USER_CREDENTIAL_FINGER_BIOMETRIC_SLOTS_COUNT <= 0xFFFF && USER_CREDENTIAL_FINGER_BIOMETRIC_SLOTS_COUNT >= 0x1, "USER_CREDENTIAL_FINGER_BIOMETRIC_SLOTS_COUNT - max 0xFFFF and min 0x1!!!");
static_assert(USER_CREDENTIAL_FINGER_BIOMETRIC_MIN_LENGHT >= 0x1, "USER_CREDENTIAL_FINGER_BIOMETRIC_MIN_LENGHT - min 0x1!!!");
static_assert(USER_CREDENTIAL_FINGER_BIOMETRIC_MAX_LENGHT <= 0xFFFF, "USER_CREDENTIAL_FINGER_BIOMETRIC_MAX_LENGHT - max 0xFFFF!!!");
static_assert(USER_CREDENTIAL_FINGER_BIOMETRIC_MIN_LENGHT < USER_CREDENTIAL_FINGER_BIOMETRIC_MAX_LENGHT, "Must USER_CREDENTIAL_FINGER_BIOMETRIC_MAX_LENGHT < USER_CREDENTIAL_FINGER_BIOMETRIC_MIN_LENGHT!!!");
#endif
#if defined(USER_CREDENTIAL_HAND_BIOMETRIC_SLOTS_COUNT)
static_assert(USER_CREDENTIAL_HAND_BIOMETRIC_SLOTS_COUNT <= 0xFFFF && USER_CREDENTIAL_HAND_BIOMETRIC_SLOTS_COUNT >= 0x1, "USER_CREDENTIAL_HAND_BIOMETRIC_SLOTS_COUNT - max 0xFFFF and min 0x1!!!");
static_assert(USER_CREDENTIAL_HAND_BIOMETRIC_MIN_LENGHT >= 0x1, "USER_CREDENTIAL_HAND_BIOMETRIC_MIN_LENGHT - min 0x1!!!");
static_assert(USER_CREDENTIAL_HAND_BIOMETRIC_MAX_LENGHT <= 0xFFFF, "USER_CREDENTIAL_HAND_BIOMETRIC_MAX_LENGHT - max 0xFFFF!!!");
static_assert(USER_CREDENTIAL_HAND_BIOMETRIC_MIN_LENGHT < USER_CREDENTIAL_HAND_BIOMETRIC_MAX_LENGHT, "Must USER_CREDENTIAL_HAND_BIOMETRIC_MAX_LENGHT < USER_CREDENTIAL_HAND_BIOMETRIC_MIN_LENGHT!!!");
#endif
#if defined(USER_CREDENTIAL_UNSPECIFIED_BIOMETRIC_SLOTS_COUNT)
static_assert(USER_CREDENTIAL_UNSPECIFIED_BIOMETRIC_SLOTS_COUNT <= 0xFFFF && USER_CREDENTIAL_UNSPECIFIED_BIOMETRIC_SLOTS_COUNT >= 0x1, "USER_CREDENTIAL_UNSPECIFIED_BIOMETRIC_SLOTS_COUNT - max 0xFFFF and min 0x1!!!");
static_assert(USER_CREDENTIAL_UNSPECIFIED_BIOMETRIC_MIN_LENGHT >= 0x1, "USER_CREDENTIAL_UNSPECIFIED_BIOMETRIC_MIN_LENGHT - min 0x1!!!");
static_assert(USER_CREDENTIAL_UNSPECIFIED_BIOMETRIC_MAX_LENGHT <= 0xFFFF, "USER_CREDENTIAL_UNSPECIFIED_BIOMETRIC_MAX_LENGHT - max 0xFFFF!!!");
static_assert(USER_CREDENTIAL_UNSPECIFIED_BIOMETRIC_MIN_LENGHT < USER_CREDENTIAL_UNSPECIFIED_BIOMETRIC_MAX_LENGHT, "Must USER_CREDENTIAL_UNSPECIFIED_BIOMETRIC_MAX_LENGHT < USER_CREDENTIAL_UNSPECIFIED_BIOMETRIC_MIN_LENGHT!!!");
#endif

static constexpr uint8_t NUMBER_OF_SUPPORTED_CREDENTIAL_TYPES = 0
#if defined(USER_CREDENTIAL_PIN_CODE_SLOTS_COUNT)
+ 0x1
#endif
#if defined(USER_CREDENTIAL_PASSWORD_SLOTS_COUNT)
+ 0x1
#endif
#if defined(USER_CREDENTIAL_RFID_CODE_SLOTS_COUNT)
+ 0x1
#endif
#if defined(USER_CREDENTIAL_BLE_SLOTS_COUNT)
+ 0x1
#endif
#if defined(USER_CREDENTIAL_NFC_SLOTS_COUNT)
+ 0x1
#endif
#if defined(USER_CREDENTIAL_UWB_SLOTS_COUNT)
+ 0x1
#endif
#if defined(USER_CREDENTIAL_EYE_BIOMETRIC_SLOTS_COUNT)
+ 0x1
#endif
#if defined(USER_CREDENTIAL_FACE_BIOMETRIC_SLOTS_COUNT)
+ 0x1
#endif
#if defined(USER_CREDENTIAL_FINGER_BIOMETRIC_SLOTS_COUNT)
+ 0x1
#endif
#if defined(USER_CREDENTIAL_HAND_BIOMETRIC_SLOTS_COUNT)
+ 0x1
#endif
#if defined(USER_CREDENTIAL_UNSPECIFIED_BIOMETRIC_SLOTS_COUNT)
+ 0x1
#endif
;

static constexpr uint32_t MASK_OF_SUPPORTED_CREDENTIAL_TYPES = 0
#if defined(USER_CREDENTIAL_PIN_CODE_SLOTS_COUNT)
| (0x1 << CREDENTIAL_REPORT_PIN_CODE)
#endif
#if defined(USER_CREDENTIAL_PASSWORD_SLOTS_COUNT)
| (0x1 << CREDENTIAL_REPORT_PASSWORD)
#endif
#if defined(USER_CREDENTIAL_RFID_CODE_SLOTS_COUNT)
| (0x1 << CREDENTIAL_REPORT_RFID_CODE)
#endif
#if defined(USER_CREDENTIAL_BLE_SLOTS_COUNT)
| (0x1 << CREDENTIAL_REPORT_BLE)
#endif
#if defined(USER_CREDENTIAL_NFC_SLOTS_COUNT)
| (0x1 << CREDENTIAL_REPORT_NFC)
#endif
#if defined(USER_CREDENTIAL_UWB_SLOTS_COUNT)
| (0x1 << CREDENTIAL_REPORT_UWB)
#endif
#if defined(USER_CREDENTIAL_EYE_BIOMETRIC_SLOTS_COUNT)
| (0x1 << CREDENTIAL_REPORT_EYE_BIOMETRIC)
#endif
#if defined(USER_CREDENTIAL_FACE_BIOMETRIC_SLOTS_COUNT)
| (0x1 << CREDENTIAL_REPORT_FACE_BIOMETRIC)
#endif
#if defined(USER_CREDENTIAL_FINGER_BIOMETRIC_SLOTS_COUNT)
| (0x1 << CREDENTIAL_REPORT_FINGER_BIOMETRIC)
#endif
#if defined(USER_CREDENTIAL_HAND_BIOMETRIC_SLOTS_COUNT)
| (0x1 << CREDENTIAL_REPORT_HAND_BIOMETRIC)
#endif
#if defined(USER_CREDENTIAL_UNSPECIFIED_BIOMETRIC_SLOTS_COUNT)
| (0x1 << CREDENTIAL_REPORT_UNSPECIFIED_BIOMETRIC)
#endif
;

typedef struct UserCredentialSaveCredentialAll_s
{
	union
	{
		#if defined(USER_CREDENTIAL_PIN_CODE_SLOTS_COUNT)
		uint8_t pin_code[(sizeof(((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.pin_code) / USER_CREDENTIAL_PIN_CODE_SLOTS_COUNT)];
		#endif
		#if defined(USER_CREDENTIAL_PASSWORD_SLOTS_COUNT)
		uint8_t password[(sizeof(((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.password) / USER_CREDENTIAL_PASSWORD_SLOTS_COUNT)];
		#endif
		#if defined(USER_CREDENTIAL_RFID_CODE_SLOTS_COUNT)
		uint8_t rfid_code[(sizeof(((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.rfid_code) / USER_CREDENTIAL_RFID_CODE_SLOTS_COUNT)];
		#endif
		#if defined(USER_CREDENTIAL_BLE_SLOTS_COUNT)
		uint8_t ble[(sizeof(((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.ble) / USER_CREDENTIAL_BLE_SLOTS_COUNT)];
		#endif
		#if defined(USER_CREDENTIAL_NFC_SLOTS_COUNT)
		uint8_t nfc[(sizeof(((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.nfc) / USER_CREDENTIAL_NFC_SLOTS_COUNT)];
		#endif
		#if defined(USER_CREDENTIAL_UWB_SLOTS_COUNT)
		uint8_t uwb[(sizeof(((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.uwb) / USER_CREDENTIAL_UWB_SLOTS_COUNT)];
		#endif
		#if defined(USER_CREDENTIAL_EYE_BIOMETRIC_SLOTS_COUNT)
		uint8_t eye_biometric[(sizeof(((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.eye_biometric) / USER_CREDENTIAL_EYE_BIOMETRIC_SLOTS_COUNT)];
		#endif
		#if defined(USER_CREDENTIAL_FACE_BIOMETRIC_SLOTS_COUNT)
		uint8_t face_biometric[(sizeof(((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.face_biometric) / USER_CREDENTIAL_FACE_BIOMETRIC_SLOTS_COUNT)];
		#endif
		#if defined(USER_CREDENTIAL_FINGER_BIOMETRIC_SLOTS_COUNT)
		uint8_t finger_biometric[(sizeof(((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.finger_biometric) / USER_CREDENTIAL_FINGER_BIOMETRIC_SLOTS_COUNT)];
		#endif
		#if defined(USER_CREDENTIAL_HAND_BIOMETRIC_SLOTS_COUNT)
		uint8_t hand_biometric[(sizeof(((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.hand_biometric) / USER_CREDENTIAL_HAND_BIOMETRIC_SLOTS_COUNT)];
		#endif
		#if defined(USER_CREDENTIAL_UNSPECIFIED_BIOMETRIC_SLOTS_COUNT)
		uint8_t unspecified_biometric[(sizeof(((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.unspecified_biometric) / USER_CREDENTIAL_UNSPECIFIED_BIOMETRIC_SLOTS_COUNT)];
		#endif
		UserCredentialSaveCredentialList_t list;
	};
} UserCredentialSaveCredentialAll_t;

typedef struct UserCredentialSaveCheck_s
{
	uint16_t user;
	#if defined(USER_CREDENTIAL_PIN_CODE_SLOTS_COUNT)
	uint16_t pin_code;
	#endif
	#if defined(USER_CREDENTIAL_PASSWORD_SLOTS_COUNT)
	uint16_t password;
	#endif
	#if defined(USER_CREDENTIAL_RFID_CODE_SLOTS_COUNT)
	uint16_t rfid_code;
	#endif
	#if defined(USER_CREDENTIAL_BLE_SLOTS_COUNT)
	uint16_t ble;
	#endif
	#if defined(USER_CREDENTIAL_NFC_SLOTS_COUNT)
	uint16_t nfc;
	#endif
	#if defined(USER_CREDENTIAL_UWB_SLOTS_COUNT)
	uint16_t uwb;
	#endif
	#if defined(USER_CREDENTIAL_EYE_BIOMETRIC_SLOTS_COUNT)
	uint16_t eye_biometric;
	#endif
	#if defined(USER_CREDENTIAL_FACE_BIOMETRIC_SLOTS_COUNT)
	uint16_t face_biometric;
	#endif
	#if defined(USER_CREDENTIAL_FINGER_BIOMETRIC_SLOTS_COUNT)
	uint16_t finger_biometric;
	#endif
	#if defined(USER_CREDENTIAL_HAND_BIOMETRIC_SLOTS_COUNT)
	uint16_t hand_biometric;
	#endif
	#if defined(USER_CREDENTIAL_UNSPECIFIED_BIOMETRIC_SLOTS_COUNT)
	uint16_t unspecified_biometric;
	#endif
} UserCredentialSaveCheck_t;

static const UserCredentialSaveCheck_t _save_check =
{
	.user = (sizeof(((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.user)),
	#if defined(USER_CREDENTIAL_PIN_CODE_SLOTS_COUNT)
	.pin_code = (sizeof(((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.pin_code)),
	#endif
	#if defined(USER_CREDENTIAL_PASSWORD_SLOTS_COUNT)
	.password = (sizeof(((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.password)),
	#endif
	#if defined(USER_CREDENTIAL_RFID_CODE_SLOTS_COUNT)
	.rfid_code = (sizeof(((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.rfid_code)),
	#endif
	#if defined(USER_CREDENTIAL_BLE_SLOTS_COUNT)
	.ble = (sizeof(((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.ble)),
	#endif
	#if defined(USER_CREDENTIAL_NFC_SLOTS_COUNT)
	.nfc = (sizeof(((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.nfc)),
	#endif
	#if defined(USER_CREDENTIAL_UWB_SLOTS_COUNT)
	.uwb = (sizeof(((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.uwb)),
	#endif
	#if defined(USER_CREDENTIAL_EYE_BIOMETRIC_SLOTS_COUNT)
	.eye_biometric = (sizeof(((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.eye_biometric)),
	#endif
	#if defined(USER_CREDENTIAL_FACE_BIOMETRIC_SLOTS_COUNT)
	.face_biometric = (sizeof(((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.face_biometric)),
	#endif
	#if defined(USER_CREDENTIAL_FINGER_BIOMETRIC_SLOTS_COUNT)
	.finger_biometric = (sizeof(((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.finger_biometric)),
	#endif
	#if defined(USER_CREDENTIAL_HAND_BIOMETRIC_SLOTS_COUNT)
	.hand_biometric = (sizeof(((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.hand_biometric)),
	#endif
	#if defined(USER_CREDENTIAL_UNSPECIFIED_BIOMETRIC_SLOTS_COUNT)
	.unspecified_biometric = (sizeof(((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.unspecified_biometric)),
	#endif
};

typedef struct ZwUserCredentialCommonCredential_s
{
	uint16_t UserUniqueIdentifier;
	uint8_t CredentialReportType;
	ZwUserCredentialCommonCredentialFind_t start;
	ZwUserCredentialCommonCredentialFind_t next;
} ZwUserCredentialCommonCredential_t;

typedef struct ZwUserCredentialCommon_s
{
	ZwUserCredentialCommonCredential_t credential;
	ZwUserCredentialCommonUser_t user;
	union
	{
		UserCredentialSaveCredentialAll_t list_credential;
		UserCredentialSaveUserIdList_t list_user;
	};
} ZwUserCredentialCommon_t;

static const UserCredentialStorageInfo_t _storage_info[] =
{
	#if defined(USER_CREDENTIAL_PIN_CODE_SLOTS_COUNT)
	{
		.addr_data = ((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.pin_code[0x0]),
		.slot_max = USER_CREDENTIAL_PIN_CODE_SLOTS_COUNT,
		.type = CREDENTIAL_REPORT_PIN_CODE,
		.CredentialLengthMin = USER_CREDENTIAL_PIN_CODE_MIN_LENGHT,
		.CredentialLengthMax = USER_CREDENTIAL_PIN_CODE_MAX_LENGHT,
	},
	#endif
	#if defined(USER_CREDENTIAL_PASSWORD_SLOTS_COUNT)
	{
		.addr_data = ((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.password[0x0]),
		.slot_max = USER_CREDENTIAL_PASSWORD_SLOTS_COUNT,
		.type = CREDENTIAL_REPORT_PASSWORD,
		.CredentialLengthMin = USER_CREDENTIAL_PASSWORD_MIN_LENGHT,
		.CredentialLengthMax = USER_CREDENTIAL_PASSWORD_MAX_LENGHT,
	},
	#endif
	#if defined(USER_CREDENTIAL_RFID_CODE_SLOTS_COUNT)
	{
		.addr_data = ((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.rfid_code[0x0]),
		.slot_max = USER_CREDENTIAL_RFID_CODE_SLOTS_COUNT,
		.type = CREDENTIAL_REPORT_RFID_CODE,
		.CredentialLengthMin = USER_CREDENTIAL_RFID_CODE_MIN_LENGHT,
		.CredentialLengthMax = USER_CREDENTIAL_RFID_CODE_MAX_LENGHT,
	},
	#endif
	#if defined(USER_CREDENTIAL_BLE_SLOTS_COUNT)
	{
		.addr_data = ((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.ble[0x0]),
		.slot_max = USER_CREDENTIAL_BLE_SLOTS_COUNT,
		.type = CREDENTIAL_REPORT_BLE,
		.CredentialLengthMin = USER_CREDENTIAL_BLE_MIN_LENGHT,
		.CredentialLengthMax = USER_CREDENTIAL_BLE_MAX_LENGHT,
	},
	#endif
	#if defined(USER_CREDENTIAL_NFC_SLOTS_COUNT)
	{
		.addr_data = ((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.nfc[0x0]),
		.slot_max = USER_CREDENTIAL_NFC_SLOTS_COUNT,
		.type = CREDENTIAL_REPORT_NFC,
		.CredentialLengthMin = USER_CREDENTIAL_NFC_MIN_LENGHT,
		.CredentialLengthMax = USER_CREDENTIAL_NFC_MAX_LENGHT,
	},
	#endif
	#if defined(USER_CREDENTIAL_UWB_SLOTS_COUNT)
	{
		.addr_data = ((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.uwb[0x0]),
		.slot_max = USER_CREDENTIAL_UWB_SLOTS_COUNT,
		.type = CREDENTIAL_REPORT_UWB,
		.CredentialLengthMin = USER_CREDENTIAL_UWB_MIN_LENGHT,
		.CredentialLengthMax = USER_CREDENTIAL_UWB_MAX_LENGHT,
	},
	#endif
	#if defined(USER_CREDENTIAL_EYE_BIOMETRIC_SLOTS_COUNT)
	{
		.addr_data = ((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.eye_biometric[0x0]),
		.slot_max = USER_CREDENTIAL_EYE_BIOMETRIC_SLOTS_COUNT,
		.type = CREDENTIAL_REPORT_EYE_BIOMETRIC,
		.CredentialLengthMin = USER_CREDENTIAL_EYE_BIOMETRIC_MIN_LENGHT,
		.CredentialLengthMax = USER_CREDENTIAL_EYE_BIOMETRIC_MAX_LENGHT,
	},
	#endif
	#if defined(USER_CREDENTIAL_FACE_BIOMETRIC_SLOTS_COUNT)
	{
		.addr_data = ((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.face_biometric[0x0]),
		.slot_max = USER_CREDENTIAL_FACE_BIOMETRIC_SLOTS_COUNT,
		.type = CREDENTIAL_REPORT_FACE_BIOMETRIC,
		.CredentialLengthMin = USER_CREDENTIAL_FACE_BIOMETRIC_MIN_LENGHT,
		.CredentialLengthMax = USER_CREDENTIAL_FACE_BIOMETRIC_MAX_LENGHT,
	},
	#endif
	#if defined(USER_CREDENTIAL_FINGER_BIOMETRIC_SLOTS_COUNT)
	{
		.addr_data = ((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.finger_biometric[0x0]),
		.slot_max = USER_CREDENTIAL_FINGER_BIOMETRIC_SLOTS_COUNT,
		.type = CREDENTIAL_REPORT_FINGER_BIOMETRIC,
		.CredentialLengthMin = USER_CREDENTIAL_FINGER_BIOMETRIC_MIN_LENGHT,
		.CredentialLengthMax = USER_CREDENTIAL_FINGER_BIOMETRIC_MAX_LENGHT,
	},
	#endif
	#if defined(USER_CREDENTIAL_HAND_BIOMETRIC_SLOTS_COUNT)
	{
		.addr_data = ((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.hand_biometric[0x0]),
		.slot_max = USER_CREDENTIAL_HAND_BIOMETRIC_SLOTS_COUNT,
		.type = CREDENTIAL_REPORT_HAND_BIOMETRIC,
		.CredentialLengthMin = USER_CREDENTIAL_HAND_BIOMETRIC_MIN_LENGHT,
		.CredentialLengthMax = USER_CREDENTIAL_HAND_BIOMETRIC_MAX_LENGHT,
	},
	#endif
	#if defined(USER_CREDENTIAL_UNSPECIFIED_BIOMETRIC_SLOTS_COUNT)
	{
		.addr_data = ((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.unspecified_biometric[0x0]),
		.slot_max = USER_CREDENTIAL_UNSPECIFIED_BIOMETRIC_SLOTS_COUNT,
		.type = CREDENTIAL_REPORT_UNSPECIFIED_BIOMETRIC,
		.CredentialLengthMin = USER_CREDENTIAL_UNSPECIFIED_BIOMETRIC_MIN_LENGHT,
		.CredentialLengthMax = USER_CREDENTIAL_UNSPECIFIED_BIOMETRIC_MAX_LENGHT,
	},
	#endif
};

static void _storage_full_erase(void *buff, size_t length, uint16_t crc16_check) {
	uint8_t *data;
	uint32_t addr;

	data = (uint8_t *)buff;
	memset(&data[0x0], 0x0, length);
	addr = ((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential);
	while (addr < (((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential) + sizeof(((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential))) {
		if ((addr + length) > (((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential) + sizeof(((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential)))
			length = (((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential) + sizeof(((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential)) - addr;
		WDOG_Feed();
		zunoEEPROMWrite(addr, length, (byte *)&data[0x0]);
		addr = addr + length;
	}
	zunoEEPROMWrite((((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.crc16_check)), sizeof(crc16_check), (byte *)&crc16_check);
}

void __zme_user_credential_init(void) {
	uint8_t data[0x20];
	uint16_t crc16_tmp;
	uint16_t crc16_check;

	zunoEEPROMRead((((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.crc16_check)), sizeof(crc16_tmp), (byte *)&crc16_tmp);
	crc16_check = CrcClass::crc16_ccitt_aug(&_save_check, sizeof(_save_check));
	if (crc16_tmp != crc16_check)
		_storage_full_erase(&data[0x0], sizeof(data), crc16_check);
}

static const UserCredentialStorageInfo_t *_get_credential_storage_info(uint8_t CredentialType) {
	uint8_t i;

	i = 0x0;
	while (i < (sizeof(_storage_info) / sizeof(_storage_info[0x0]))) {
		if (_storage_info[i].type == CredentialType)
			return (&_storage_info[i]);
		i++;
	}
	return (NULL);
}

static uint16_t _storage_read_user_header(uint16_t userIdentifier, UserCredentialSaveUserIdHeader_t *header) {
	uint16_t crc16;

	userIdentifier--;
	zunoEEPROMRead((((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.user[userIdentifier].header)), sizeof(UserCredentialSaveUserIdHeader_t), (byte *)header);
	memcpy(&crc16, &header->crc16[0x0], sizeof(crc16));
	return (crc16);
}

static uint16_t _storage_read_user_info(uint16_t userIdentifier, UserCredentialSaveUserId_t *info) {
	userIdentifier--;
	zunoEEPROMRead((((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.user[userIdentifier].info)), sizeof(UserCredentialSaveUserId_t), (byte *)info);
	return (CrcClass::crc16_ccitt_aug(info, sizeof(UserCredentialSaveUserId_t)));
}

static bool _storage_read_user(uint16_t userIdentifier, UserCredentialSaveUserIdList_t *list) {
	uint16_t crc16;

	if ((crc16 = _storage_read_user_header(userIdentifier, &list->header)) == 0x0)
		return (false);
	if (_storage_read_user_info(userIdentifier, &list->info) != crc16)
		return (false);
	return (true);
}

static void _storage_write_user(uint16_t userIdentifier, UserCredentialSaveUserIdList_t *list) {
	uint16_t crc16;

	crc16 = CrcClass::crc16_ccitt_aug(&list->info, sizeof(list->info));
	memcpy(&list->header.crc16[0x0], &crc16, sizeof(list->header.crc16));
	userIdentifier--;
	zunoEEPROMWrite((((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.user[userIdentifier])), sizeof(list[0x0]), (byte *)list);
}

static void _storage_clear_user(uint16_t userIdentifier, UserCredentialSaveUserIdList_t *list) {
	memset(&list->header, 0x0, sizeof(list->header));
	userIdentifier--;
	zunoEEPROMWrite((((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential.credential.user[userIdentifier].header)), sizeof(list->header), (byte *)&list->header);
}

static uint16_t _storage_next_user(uint16_t userIdentifier, UserCredentialSaveUserIdList_t *list_next) {
	userIdentifier++;
	while (userIdentifier <= USER_CREDENTIAL_USERS_COUNT) {
		if (_storage_read_user(userIdentifier, list_next) == true)
			return (userIdentifier);
		userIdentifier++;
	}
	return (0x0);
}

static bool _storage_credential_del_all_types(uint16_t userIdentifier, ZwUserCredentialCommon_t *info);
static bool _storage_del_user(uint16_t userIdentifier, ZwUserCredentialCommon_t *info) {
	uint16_t crc16;

	if ((crc16 = _storage_read_user_header(userIdentifier, &info->list_user.header)) == 0x0)
		return (false);
	if (_storage_read_user_info(userIdentifier, &info->list_user.info) != crc16) {
		_storage_clear_user(userIdentifier, &info->list_user);
		return (false);
	}
	_storage_credential_del_all_types(userIdentifier, info);
	_storage_read_user_info(userIdentifier, &info->list_user.info);
	_storage_clear_user(userIdentifier, &info->list_user);
	return (true);
}

static void _storage_del_all_user(ZwUserCredentialCommon_t *info) {
	uint16_t userIdentifier;
	uint16_t crc16_check;

	crc16_check = CrcClass::crc16_ccitt_aug(&_save_check, sizeof(_save_check));
	userIdentifier = 0x0;
	while (userIdentifier <= USER_CREDENTIAL_USERS_COUNT) {
		if (_storage_read_user(userIdentifier, &info->list_user) == true) {
			_storage_full_erase(info, sizeof(ZwUserCredentialCommon_t), crc16_check);
			return ;
		}
		userIdentifier++;
	}
}

static user_credential_user_id_type _storage_extract_credential_header_user_id(UserCredentialSaveCredentialList_t *list) {
	user_credential_user_id_type user_id;

	memcpy(&user_id, &list->header.user_id[0x0], sizeof(user_id));
	return (user_id);
}

static uint32_t _storage_extract_credential_header_addr(uint16_t slot, const UserCredentialStorageInfo_t *storage_info) {
	uint32_t addr_data;

	slot--;
	addr_data = storage_info->addr_data + (slot * (sizeof(UserCredentialSaveCredentialList_t) + storage_info->CredentialLengthMax));
	return (addr_data);
}

static uint16_t _storage_read_credential_header(uint16_t slot, const UserCredentialStorageInfo_t *storage_info, UserCredentialSaveCredentialList_t *list) {
	user_credential_user_id_type user_id;
	uint16_t crc16;

	zunoEEPROMRead(_storage_extract_credential_header_addr(slot, storage_info), sizeof(list->header), (byte *)&list->header);
	user_id = _storage_extract_credential_header_user_id(list);
	if (user_id == 0x0)
		return (0x0);
	if (user_id > USER_CREDENTIAL_USERS_COUNT)
		return (0x0);
	memcpy(&crc16, &list->header.crc16[0x0], sizeof(crc16));
	return (crc16);
}

static uint16_t _storage_read_credential_info(uint16_t slot, const UserCredentialStorageInfo_t *storage_info, UserCredentialSaveCredentialList_t *list) {
	uint32_t addr_data;

	addr_data = _storage_extract_credential_header_addr(slot, storage_info);
	zunoEEPROMRead(addr_data + sizeof(list->header), (sizeof(list->info) + storage_info->CredentialLengthMax), (byte *)&list->info);
	return (CrcClass::crc16_ccitt_aug((uint8_t *)list + sizeof(list->header.crc16), ((sizeof(UserCredentialSaveCredentialList_t) - sizeof(list->header.crc16)) + storage_info->CredentialLengthMax)));
}

static uint16_t _storage_read_credential(uint16_t userIdentifier, uint16_t slot, const UserCredentialStorageInfo_t *storage_info, UserCredentialSaveCredentialList_t *list) {
	uint16_t crc16;
	user_credential_user_id_type user_id;

	if ((crc16 = _storage_read_credential_header(slot, storage_info, list)) == 0x0)
		return (0x0);
	user_id = _storage_extract_credential_header_user_id(list);
	if (userIdentifier != 0x0)
		if (user_id != userIdentifier)
			return (0x0);
	if (_storage_read_credential_info(slot, storage_info, list) != crc16)
		return (0x0);
	return (user_id);
}

static void _storage_write_credential(uint16_t userIdentifier, uint16_t slot, const UserCredentialStorageInfo_t *storage_info, UserCredentialSaveCredentialList_t *list) {
	uint32_t addr_data;
	uint16_t crc16;
	
	memcpy(&list->header.user_id[0x0], &userIdentifier, sizeof(list->header.user_id));
	list->header.crc8_data = CrcClass::crc8_sapi(&list->info.CredentialData[0x0], list->info.CredentialLength);
	crc16 = CrcClass::crc16_ccitt_aug((uint8_t *)list + sizeof(list->header.crc16), ((sizeof(UserCredentialSaveCredentialList_t) - sizeof(list->header.crc16)) + storage_info->CredentialLengthMax));
	memcpy(&list->header.crc16[0x0], &crc16, sizeof(list->header.crc16));
	addr_data = _storage_extract_credential_header_addr(slot, storage_info);
	zunoEEPROMWrite(addr_data, (sizeof(UserCredentialSaveCredentialList_t) + storage_info->CredentialLengthMax), (byte *)list);
}

static void _storage_clear_credential(uint16_t slot, const UserCredentialStorageInfo_t *storage_info, UserCredentialSaveCredentialHeader_t *header) {
	uint32_t addr_data;
	
	memset(header, 0x0, sizeof(UserCredentialSaveCredentialHeader_t));
	addr_data = _storage_extract_credential_header_addr(slot, storage_info);
	zunoEEPROMWrite(addr_data, (sizeof(UserCredentialSaveCredentialHeader_t)), (byte *)header);
}

static uint16_t _storage_find_credential_uniq(uint8_t type, const uint8_t *CredentialData, uint8_t CredentialLength, ZwUserCredentialCommon_t *info) {
	const UserCredentialStorageInfo_t *storage_info;
	uint32_t CredentialTypeMask;
	uint16_t slot;
	uint16_t crc16;
	uint8_t CredentialType;
	uint8_t crc8;

	crc8 = CrcClass::crc8_sapi(CredentialData, CredentialLength);
	CredentialType = 0x0;
	CredentialTypeMask = MASK_OF_SUPPORTED_CREDENTIAL_TYPES;
	while (true) {
		CredentialType++;
		CredentialTypeMask = CredentialTypeMask >> 0x1;
		if (CredentialTypeMask == 0x0)
			break ;
		if (CredentialType != type)
			continue ;
		if ((storage_info = _get_credential_storage_info(CredentialType)) == NULL)
			continue ;
		slot = 0x0;
		while (slot < storage_info->slot_max) {
			slot++;
			if ((crc16 = _storage_read_credential_header(slot, storage_info, &info->list_credential.list)) == 0x0)
				continue ;
			if (info->list_credential.list.header.crc8_data != crc8)
				continue ;
			if (_storage_read_credential_info(slot, storage_info, &info->list_credential.list) != crc16)
				continue ;
			if (info->list_credential.list.info.CredentialLength != CredentialLength)
				continue ;
			if (memcmp(CredentialData, &info->list_credential.list.info.CredentialData, CredentialLength) != 0x0)
				continue ;
			return (slot);
		}
	}
	return (0);
}

static uint16_t _storage_next_credential(uint16_t userIdentifier, uint16_t slot, const UserCredentialStorageInfo_t *storage_info, UserCredentialSaveCredentialList_t *list) {
	uint16_t crc16;
	
	while (slot < storage_info->slot_max) {
		slot++;
		if ((crc16 = _storage_read_credential_header(slot, storage_info, list)) == 0x0)
			continue ;
		if (userIdentifier != 0x0)
			if (_storage_extract_credential_header_user_id(list) != userIdentifier)
				continue ;
		if (_storage_read_credential_info(slot, storage_info, list) != crc16)
			continue ;
		return (slot);
	}
	return (0x0);
}

static bool _storage_next_credential_type(uint16_t userIdentifier, UserCredentialSaveCredentialList_t *list, ZwUserCredentialCommonCredentialFind_t *next) {
	const UserCredentialStorageInfo_t *storage_info;
	uint32_t CredentialTypeMask;

	if (next->CredentialType != 0x0)
		next->CredentialType--;
	CredentialTypeMask = MASK_OF_SUPPORTED_CREDENTIAL_TYPES >> next->CredentialType;
	while (true) {
		next->CredentialType++;
		CredentialTypeMask = CredentialTypeMask >> 0x1;
		if (CredentialTypeMask == 0x0)
			break ;
		if ((storage_info = _get_credential_storage_info(next->CredentialType)) == NULL)
			continue ;
		if ((next->CredentialSlot = _storage_next_credential(userIdentifier, next->CredentialSlot, storage_info, list)) == 0x0)
			continue ;
		return (true);
	}
	memset(next, 0x0, sizeof(ZwUserCredentialCommonCredentialFind_t));
	return (false);
}

static bool _storage_credential_del_types_add(uint16_t userIdentifier, uint8_t CredentialType, UserCredentialSaveCredentialList_t *list) {
	const UserCredentialStorageInfo_t *storage_info;
	uint32_t count;
	uint16_t slot;
	uint16_t crc16;

	if ((storage_info = _get_credential_storage_info(CredentialType)) == NULL)
		return (false);
	count = 0x0;
	slot = 0x0;
	while (slot < storage_info->slot_max) {
		slot++;
		if ((crc16 = _storage_read_credential_header(slot, storage_info, list)) == 0x0)
			continue ;
		if (userIdentifier != 0x0) {
			if (_storage_extract_credential_header_user_id(list) != userIdentifier)
				continue ;
		}
		if (_storage_read_credential_info(slot, storage_info,list) != crc16)
			continue ;
		_storage_clear_credential(slot, storage_info, &list->header);
		count++;
	}
	if (count == 0x0)
		return (false);
	return (true);
}

static bool _storage_credential_del_types(uint16_t userIdentifier, uint8_t CredentialType, ZwUserCredentialCommon_t *info) {
	if (userIdentifier != 0x0)
		if (_storage_read_user(userIdentifier, &info->list_user) == false)
			return (false);
	return (_storage_credential_del_types_add(userIdentifier, CredentialType, &info->list_credential.list));
}

static bool _storage_credential_del_all_types(uint16_t userIdentifier, ZwUserCredentialCommon_t *info) {
	uint32_t count;
	uint32_t CredentialTypeMask;
	uint8_t CredentialType;

	if (userIdentifier != 0x0)
		if (_storage_read_user(userIdentifier, &info->list_user) == false)
			return (false);
	count = 0x0;
	CredentialType = 0x0;
	CredentialTypeMask = MASK_OF_SUPPORTED_CREDENTIAL_TYPES;
	while (true) {
		CredentialType++;
		CredentialTypeMask = CredentialTypeMask >> 0x1;
		if (CredentialTypeMask == 0x0)
			break ;
		if (_storage_credential_del_types_add(userIdentifier, CredentialType, &info->list_credential.list) == false)
			continue ;
		count++;
	}
	if (count == 0x0)
		return (false);
	return (true);
}

#define USER_CREDENTIAL_SUPPORT_LEARN							(0x7)
#define USER_CREDENTIAL_SUPPORT_SCHEDULE						(0x7)
#define USER_CREDENTIAL_SUPPORT_CHECKSUM_ALL_USERS				(0x6)
#define USER_CREDENTIAL_SUPPORT_CHECKSUM_USER					(0x5)

static constexpr uint32_t MASK_OF_SUPPORTED_USER_TYPES = ((0x1 << USER_SET_GENERAL_USER) | (0x1 << USER_SET_PROGRAMMING_USER) | (0x1 << USER_SET_NON_ACCESS_USER) | (0x1 << USER_SET_DURESS_USER) |
(0x1 << USER_SET_DISPOSABLE_USER) | (0x1 << USER_SET_EXPIRING_USER) | (0x1 << USER_SET_REMOTE_ONLY_USER));

static const uint32_t _user_supported_credential_rules_mask = ((0x1 << USER_CREDENTIAL_RULE_SINGLE) | (0x1 << USER_CREDENTIAL_RULE_DUAL) | (0x1 << USER_CREDENTIAL_RULE_TRIPLE));

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

	report = (UserCredentialCapabilitiesUserReport_t *)frame_report->info.packet.cmd;
	// report->cmdClass = COMMAND_CLASS_USER_CREDENTIAL; set in - fillOutgoingPacket
	// report->cmd = USER_CAPABILITIES_REPORT; set in - fillOutgoingPacket
	report->userIdentifier[0x0] = USER_CREDENTIAL_USERS_COUNT >> 0x8;
	report->userIdentifier[0x1] = USER_CREDENTIAL_USERS_COUNT;
	report->SupportedCredentialRulesBitMask = _user_supported_credential_rules_mask;
	report->MaxLengthofUserName = USER_CREDENTIAL_USERS_NAME_MAX_LENGHT;
	report->property1 = (0x1 << USER_CREDENTIAL_SUPPORT_CHECKSUM_USER);
	#ifdef WITH_CC_SCHEDULE_ENTRY_LOCK
	report->property1 = report->property1 | (0x1 << USER_CREDENTIAL_SUPPORT_SCHEDULE);
	#endif
	len = ((((sizeof(MASK_OF_SUPPORTED_USER_TYPES) * 0x8) - __builtin_clz(MASK_OF_SUPPORTED_USER_TYPES)) >> 0x3) + 0x1);
	report->SupportedUserTypesBitMaskLength = len;
	frame_report->info.packet.len = sizeof(report[0x0]) + len;
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
	uint8_t						MinLengthOfCredentialData[NUMBER_OF_SUPPORTED_CREDENTIAL_TYPES];
	uint8_t						MaxLengthOfCredentialData[NUMBER_OF_SUPPORTED_CREDENTIAL_TYPES];
	uint8_t						CLRecommendedTimeout[NUMBER_OF_SUPPORTED_CREDENTIAL_TYPES];
	uint8_t						CLNumberOfSteps[NUMBER_OF_SUPPORTED_CREDENTIAL_TYPES];
	uint8_t						MaximumCredentialHashLength[NUMBER_OF_SUPPORTED_CREDENTIAL_TYPES];
}								UserCredentialCapabilitiesCredentialReport_t;

static size_t _user_credential_capabilities_credential_report_set(UserCredentialCapabilitiesCredentialReport_t *report, uint8_t type, uint8_t number, uint8_t min, uint8_t max, size_t i) {
	report->CredentialType[i] = type;
	report->CLSupport[i] = 0x0;
	report->NumberofSupportedCredentialSlots[0x2 * i + 0x0] = number >> 0x8;
	report->NumberofSupportedCredentialSlots[0x2 * i + 0x1] = number;
	report->MinLengthOfCredentialData[i] = min;
	report->MaxLengthOfCredentialData[i] = max;
	report->CLRecommendedTimeout[i] = 0x0;
	report->CLNumberOfSteps[i] = 0x0;
	report->MaximumCredentialHashLength[i] = 0x0;
	i++;
	return (i);
}

static int _user_credential_capabilities_credential_report(ZUNOCommandPacketReport_t *frame_report) {
	UserCredentialCapabilitiesCredentialReport_t				*report;
	size_t														i;

	report = (UserCredentialCapabilitiesCredentialReport_t *)frame_report->info.packet.cmd;
	// report->cmdClass = COMMAND_CLASS_USER_CREDENTIAL; set in - fillOutgoingPacket
	// report->cmd = CREDENTIAL_CAPABILITIES_REPORT; set in - fillOutgoingPacket
	report->profile1 = (CREDENTIAL_CAPABILITIES_REPORT_PROPERTIES1_CREDENTIAL_CHECKSUM_SUPPORT_BIT_MASK);
	report->NumberOfSupportedCredentialTypes = NUMBER_OF_SUPPORTED_CREDENTIAL_TYPES;
	i = 0x0;
	#if defined(USER_CREDENTIAL_PIN_CODE_SLOTS_COUNT)
	i = _user_credential_capabilities_credential_report_set(report, CREDENTIAL_REPORT_PIN_CODE, USER_CREDENTIAL_PIN_CODE_SLOTS_COUNT, USER_CREDENTIAL_PIN_CODE_MIN_LENGHT, USER_CREDENTIAL_PIN_CODE_MAX_LENGHT, i);
	#endif
	#if defined(USER_CREDENTIAL_PASSWORD_SLOTS_COUNT)
	i = _user_credential_capabilities_credential_report_set(report, CREDENTIAL_REPORT_PASSWORD, USER_CREDENTIAL_PASSWORD_SLOTS_COUNT, USER_CREDENTIAL_PASSWORD_MIN_LENGHT, USER_CREDENTIAL_PASSWORD_MAX_LENGHT, i);
	#endif
	#if defined(USER_CREDENTIAL_RFID_CODE_SLOTS_COUNT)
	i = _user_credential_capabilities_credential_report_set(report, CREDENTIAL_REPORT_RFID_CODE, USER_CREDENTIAL_RFID_CODE_SLOTS_COUNT, USER_CREDENTIAL_RFID_CODE_MIN_LENGHT, USER_CREDENTIAL_RFID_CODE_MAX_LENGHT, i);
	#endif
	#if defined(USER_CREDENTIAL_BLE_SLOTS_COUNT)
	i = _user_credential_capabilities_credential_report_set(report, CREDENTIAL_REPORT_BLE, USER_CREDENTIAL_BLE_SLOTS_COUNT, USER_CREDENTIAL_BLE_MIN_LENGHT, USER_CREDENTIAL_BLE_MAX_LENGHT, i);
	#endif
	#if defined(USER_CREDENTIAL_NFC_SLOTS_COUNT)
	i = _user_credential_capabilities_credential_report_set(report, CREDENTIAL_REPORT_NFC, USER_CREDENTIAL_NFC_SLOTS_COUNT, USER_CREDENTIAL_NFC_MIN_LENGHT, USER_CREDENTIAL_NFC_MAX_LENGHT, i);
	#endif
	#if defined(USER_CREDENTIAL_UWB_SLOTS_COUNT)
	i = _user_credential_capabilities_credential_report_set(report, CREDENTIAL_REPORT_UWB, USER_CREDENTIAL_UWB_SLOTS_COUNT, USER_CREDENTIAL_UWB_MIN_LENGHT, USER_CREDENTIAL_UWB_MAX_LENGHT, i);
	#endif
	#if defined(USER_CREDENTIAL_EYE_BIOMETRIC_SLOTS_COUNT)
	i = _user_credential_capabilities_credential_report_set(report, CREDENTIAL_REPORT_EYE_BIOMETRIC, USER_CREDENTIAL_EYE_BIOMETRIC_SLOTS_COUNT, USER_CREDENTIAL_EYE_BIOMETRIC_MIN_LENGHT, USER_CREDENTIAL_EYE_BIOMETRIC_MAX_LENGHT, i);
	#endif
	#if defined(USER_CREDENTIAL_FACE_BIOMETRIC_SLOTS_COUNT)
	i = _user_credential_capabilities_credential_report_set(report, CREDENTIAL_REPORT_FACE_BIOMETRIC, USER_CREDENTIAL_FACE_BIOMETRIC_SLOTS_COUNT, USER_CREDENTIAL_FACE_BIOMETRIC_MIN_LENGHT, USER_CREDENTIAL_FACE_BIOMETRIC_MAX_LENGHT, i);
	#endif
	#if defined(USER_CREDENTIAL_FINGER_BIOMETRIC_SLOTS_COUNT)
	i = _user_credential_capabilities_credential_report_set(report, CREDENTIAL_REPORT_FINGER_BIOMETRIC, USER_CREDENTIAL_FINGER_BIOMETRIC_SLOTS_COUNT, USER_CREDENTIAL_FINGER_BIOMETRIC_MIN_LENGHT, USER_CREDENTIAL_FINGER_BIOMETRIC_MAX_LENGHT, i);
	#endif
	#if defined(USER_CREDENTIAL_HAND_BIOMETRIC_SLOTS_COUNT)
	i = _user_credential_capabilities_credential_report_set(report, CREDENTIAL_REPORT_HAND_BIOMETRIC, USER_CREDENTIAL_HAND_BIOMETRIC_SLOTS_COUNT, USER_CREDENTIAL_HAND_BIOMETRIC_MIN_LENGHT, USER_CREDENTIAL_HAND_BIOMETRIC_MAX_LENGHT, i);
	#endif
	#if defined(USER_CREDENTIAL_UNSPECIFIED_BIOMETRIC_SLOTS_COUNT)
	i = _user_credential_capabilities_credential_report_set(report, CREDENTIAL_REPORT_UNSPECIFIED_BIOMETRIC, USER_CREDENTIAL_UNSPECIFIED_BIOMETRIC_SLOTS_COUNT, USER_CREDENTIAL_UNSPECIFIED_BIOMETRIC_MIN_LENGHT, USER_CREDENTIAL_UNSPECIFIED_BIOMETRIC_MAX_LENGHT, i);
	#endif
	frame_report->info.packet.len = sizeof(report[0x0]);
	return (ZUNO_COMMAND_ANSWERED);
}

typedef struct					UserCredentialUserReportGet_s
{
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						UserReportType;
	uint8_t						NextUserIdentifier[0x2];/*MSB - LSB*/
	UserCredentialSaveUserIdInfoModify_t modify;
	uint8_t						UserUniqueIdentifier[0x2];/*MSB - LSB*/
	UserCredentialSaveUserIdInfoPart1_t part1;
	UserCredentialSaveUserIdInfoExpiring_t expiring;
	UserCredentialSaveUserIdInfoPart2_t part2;
}								UserCredentialUserReportGet_t;

typedef struct					UserCredentialUserGet_s
{
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						UserUniqueIdentifier[0x2];/*MSB - LSB*/
}								UserCredentialUserGet_t;

static void _user_credential_user_report_set_next(ZUNOCommandPacket_t *packet, uint16_t NextUserIdentifier) {
	UserCredentialUserReportGet_t				*report;

	report = (UserCredentialUserReportGet_t *)packet->packet.cmd;
	report->NextUserIdentifier[0x0] = NextUserIdentifier >> 0x8;
	report->NextUserIdentifier[0x1] = NextUserIdentifier;
}

static void _user_credential_user_report_set(ZUNOCommandPacket_t *packet, const ZwUserCredentialCommon_t *info) {
	UserCredentialUserReportGet_t				*report;

	report = (UserCredentialUserReportGet_t *)packet->packet.cmd;
	report->cmdClass = COMMAND_CLASS_USER_CREDENTIAL;
	report->cmd = USER_REPORT;
	report->UserReportType = info->user.UserReportType;
	report->UserUniqueIdentifier[0x0] = info->user.UserUniqueIdentifier >> 0x8;
	report->UserUniqueIdentifier[0x1] = info->user.UserUniqueIdentifier;
	_user_credential_user_report_set_next(packet, info->user.NextUserIdentifier);
	report->modify = info->list_user.info.modify;
	report->part1 = info->list_user.info.cmp.crc.part1;
	report->part2 = info->list_user.info.cmp.crc.part2;
	report->expiring = info->list_user.info.cmp.expiring;
	packet->packet.len = (sizeof(report[0x0]) - sizeof(report->part2.UserName)) + report->part2.UserNameLength;
}

static void _user_credential_user_report_get_dne(ZUNOCommandPacketReport_t *frame_report, ZwUserCredentialCommon_t *info) {
	memset(&info->list_user.info, 0x0, (sizeof(info->list_user.info) - sizeof(info->list_user.info.cmp.crc.part2.UserName)));
	#if USER_REPORT_DNE != 0x0
	info->list_user.info.modify.UserModifierType = USER_REPORT_DNE;
	#endif
	info->user.NextUserIdentifier = 0x0;
	info->list_user.info.cmp.crc.part1.CredentialRule = USER_CREDENTIAL_RULE_SINGLE;
	_user_credential_user_report_set(&frame_report->info, info);
}


static int _user_credential_user_report_get(ZUNOCommandPacketReport_t *frame_report, const UserCredentialUserGet_t *in, ZwUserCredentialCommon_t *info) {
	info->user.UserReportType = USER_REPORT_RESPONSE_TO_GET;
	if ((info->user.UserUniqueIdentifier = (in->UserUniqueIdentifier[0x0] << 0x8) | in->UserUniqueIdentifier[0x1]) == 0x0) {
		if ((info->user.UserUniqueIdentifier = _storage_next_user(0x0, &info->list_user)) == 0x0) {
			_user_credential_user_report_get_dne(frame_report, info);
			return (ZUNO_COMMAND_ANSWERED);
		}
	}
	else if (_storage_read_user(info->user.UserUniqueIdentifier, &info->list_user) == false) {
		_user_credential_user_report_get_dne(frame_report, info);
		return (ZUNO_COMMAND_ANSWERED);
	}
	_user_credential_user_report_set(&frame_report->info, info);
	_user_credential_user_report_set_next(&frame_report->info, _storage_next_user(info->user.UserUniqueIdentifier, &info->list_user));
	return (ZUNO_COMMAND_ANSWERED);
}

typedef struct					UserCredentialUserSet_s
{
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						profile1;
	uint8_t						UserUniqueIdentifier[0x2];/*MSB - LSB*/
	UserCredentialSaveUserIdInfoPart1_t part1;
	UserCredentialSaveUserIdInfoExpiring_t expiring;
	UserCredentialSaveUserIdInfoPart2_t part2;
}								UserCredentialUserSet_t;

static bool _user_credential_user_set_valid_in(const UserCredentialUserSet_t *in, uint16_t UserUniqueIdentifier) {
	uint8_t UserType;
	uint8_t CredentialRule;
	size_t i;

	if (UserUniqueIdentifier < 0x1)
		return (false);
	UserType = in->part1.UserType;
	if (UserType >= (sizeof(MASK_OF_SUPPORTED_USER_TYPES) * 0x8) || (MASK_OF_SUPPORTED_USER_TYPES & (0x1 << UserType)) == 0x0)
		return (false);
	CredentialRule = in->part1.CredentialRule;
	if (CredentialRule >= (sizeof(_user_supported_credential_rules_mask) * 0x8) || (_user_supported_credential_rules_mask & (0x1 << CredentialRule)) == 0x0)
		return (false);
	switch (((in->part2.profile3 & USER_SET_PROPERTIES3_USER_NAME_ENCODING_MASK))) {
		case USER_SET_USER_NAME_ENCODING_USING_STANDARD_ASCII_CODES:
			i = 0x0;
			while (i < in->part2.UserNameLength) {
				if (isascii(in->part2.UserName[i]) == false)
					return (false);
				i++;
			}
			break;
		case USER_SET_USER_NAME_ENCODING_USING_STANDARD_AND_OEM_EXTENDED_ASCII_CODES:
		case USER_SET_USER_NAME_ENCODING_UNICODE_UTF_16:
			break ;
		default:
			return (false);
			break ;
	}
	return (true);
}

extern "C" size_t zwaveme_utoa_base(size_t value, void *str, size_t base);
static void _user_credential_user_report_set_name(ZwUserCredentialCommon_t *info, const UserCredentialUserSet_t *in)
{
	static const char default_name[] = "User-";
	uint8_t UserNameLength;
	uint8_t lenght;
	char buffer[10];

	if ((UserNameLength = in->part2.UserNameLength) > sizeof(info->list_user.info.cmp.crc.part2.UserName))
		UserNameLength = sizeof(info->list_user.info.cmp.crc.part2.UserName);
	if (UserNameLength != 0x0) {
		memcpy(&info->list_user.info.cmp.crc.part2.UserName[0x0], &in->part2.UserName[0x0], UserNameLength);
	}
	else {
		UserNameLength = sizeof(default_name) - 0x1;
		if (UserNameLength > sizeof(info->list_user.info.cmp.crc.part2.UserName))
			UserNameLength = sizeof(info->list_user.info.cmp.crc.part2.UserName);
		memcpy(&info->list_user.info.cmp.crc.part2.UserName[0x0], default_name, UserNameLength);
		if (UserNameLength < sizeof(info->list_user.info.cmp.crc.part2.UserName)) {
			lenght = zwaveme_utoa_base(info->user.UserUniqueIdentifier, &buffer[0x0], 0xA);
			if (UserNameLength + lenght > sizeof(info->list_user.info.cmp.crc.part2.UserName))
				lenght = sizeof(info->list_user.info.cmp.crc.part2.UserName) - UserNameLength;
			memcpy(&info->list_user.info.cmp.crc.part2.UserName[UserNameLength], &buffer[0x0], lenght);
			UserNameLength = UserNameLength + lenght;
		}
	}
	info->list_user.info.cmp.crc.part2.UserNameLength = UserNameLength;
}

static void _user_credential_user_set_copy(const ZUNOCommandCmd_t *cmd, const UserCredentialUserSet_t *in, ZwUserCredentialCommon_t *info) {
	info->list_user.info.cmp.crc.part1.UserType = in->part1.UserType;
	info->list_user.info.cmp.crc.part1.profile2 = in->part1.profile2 & USER_SET_PROPERTIES2_USER_ACTIVE_STATE_BIT_MASK;
	info->list_user.info.cmp.crc.part1.CredentialRule = in->part1.CredentialRule;
	info->list_user.info.cmp.expiring = in->expiring;
	info->list_user.info.cmp.crc.part2.profile3 = in->part2.profile3 & USER_SET_PROPERTIES3_USER_NAME_ENCODING_MASK;
	_user_credential_user_report_set_name(info, in);
	info->list_user.info.modify.UserModifierType = CREDENTIAL_REPORT_Z_WAVE;
	info->list_user.info.modify.UserModifierNodeID[0x0] = cmd->src_node >> 0x8;
	info->list_user.info.modify.UserModifierNodeID[0x1] = cmd->src_node;
}

static uint8_t _user_credential_user_set_add(const ZUNOCommandCmd_t *cmd, const UserCredentialUserSet_t *in, ZwUserCredentialCommon_t *info) {
	uint16_t													crc16;

	_user_credential_user_set_copy(cmd, in, info);
	crc16 = CrcClass::crc16_ccitt_aug(&info->list_user.info.cmp, ((sizeof(info->list_user.info.cmp) - sizeof(info->list_user.info.cmp.crc.part2.UserName)) + info->list_user.info.cmp.crc.part2.UserNameLength));
	if (_storage_read_user(info->user.UserUniqueIdentifier, &info->list_user) == true) {
		if (CrcClass::crc16_ccitt_aug(&info->list_user.info.cmp, ((sizeof(info->list_user.info.cmp) - sizeof(info->list_user.info.cmp.crc.part2.UserName)) + info->list_user.info.cmp.crc.part2.UserNameLength))== crc16)
			return (USER_REPORT_UNCHANGED);
		return (USER_REPORT_ADD_AGAINST_OCCUPIED);
	}
	_user_credential_user_set_copy(cmd, in, info);
	_storage_write_user(info->user.UserUniqueIdentifier, &info->list_user);
	return (USER_REPORT_ADDED);
}

static uint8_t _user_credential_user_set_modify(const ZUNOCommandCmd_t *cmd, const UserCredentialUserSet_t *in, ZwUserCredentialCommon_t *info) {
	uint16_t													crc16;

	if (_storage_read_user(info->user.UserUniqueIdentifier, &info->list_user) == false) {
		_user_credential_user_set_copy(cmd, in, info);
		memset(&info->list_user.info.modify, 0x0, sizeof(info->list_user.info.modify));
		#if USER_REPORT_DNE != 0x0
		save_user_id->pre.UserModifierType = USER_REPORT_DNE;
		#endif
		return (USER_REPORT_MODIFY_AGAINST_EMPTY);
	}
	crc16 = CrcClass::crc16_ccitt_aug(&info->list_user.info.cmp, ((sizeof(info->list_user.info.cmp) - sizeof(info->list_user.info.cmp.crc.part2.UserName)) + info->list_user.info.cmp.crc.part2.UserNameLength));
	_user_credential_user_set_copy(cmd, in, info);
	if (CrcClass::crc16_ccitt_aug(&info->list_user.info.cmp, ((sizeof(info->list_user.info.cmp) - sizeof(info->list_user.info.cmp.crc.part2.UserName)) + info->list_user.info.cmp.crc.part2.UserNameLength)) == crc16)
		return (USER_REPORT_UNCHANGED);
	_storage_write_user(info->user.UserUniqueIdentifier, &info->list_user);
	return (USER_REPORT_MODIFIED);
}

static void _user_credential_user_set_del_dne(ZwUserCredentialCommon_t *info) {
	memset(&info->list_user.info, 0x0, (sizeof(info->list_user.info) - sizeof(info->list_user.info.cmp.crc.part2.UserName)));
	#if USER_REPORT_DNE != 0x0
	info->list_user.info.modify.UserModifierType = USER_REPORT_DNE;
	#endif
	info->list_user.info.cmp.crc.part1.CredentialRule = USER_CREDENTIAL_RULE_SINGLE;
}

static uint8_t _user_credential_user_set_del(ZwUserCredentialCommon_t *info) {
	if (info->user.UserUniqueIdentifier == 0x0) {
		info->user.NextUserIdentifier = 0x0;
		_storage_del_all_user(info);
		_user_credential_user_set_del_dne(info);
		return (USER_REPORT_DELETED);
	}
	info->user.NextUserIdentifier = _storage_next_user(info->user.UserUniqueIdentifier, &info->list_user);
	if (_storage_del_user(info->user.UserUniqueIdentifier, info) == false) {
		_user_credential_user_set_del_dne(info);
		return (USER_REPORT_UNCHANGED);
	}
	return (USER_REPORT_DELETED);
}

static int _user_credential_user_set(ZUNOCommandPacketReport_t *frame_report, const ZUNOCommandCmd_t *cmd, const UserCredentialUserSet_t *in, const ZUNOCommandHandlerOption_t *options, ZwUserCredentialCommon_t *info) {
	int rs;

	if ((info->user.UserUniqueIdentifier = (in->UserUniqueIdentifier[0x0] << 0x8) | in->UserUniqueIdentifier[0x1]) > USER_CREDENTIAL_USERS_COUNT)
		return (ZUNO_COMMAND_BLOCKED_FAIL);
	rs = ZUNO_COMMAND_PROCESSED;
	if ((in->profile1 & USER_SET_PROPERTIES1_OPERATION_TYPE_MASK) == USER_SET_OPERATION_TYPE_DELETE) {
		info->user.UserReportType = _user_credential_user_set_del(info);
	}
	else {
		if (_user_credential_user_set_valid_in(in, info->user.UserUniqueIdentifier) == false)
			return (ZUNO_COMMAND_BLOCKED_FAIL);
		info->user.NextUserIdentifier = _storage_next_user(info->user.UserUniqueIdentifier, &info->list_user);
		switch ((in->profile1 & USER_SET_PROPERTIES1_OPERATION_TYPE_MASK)) {
			case USER_SET_OPERATION_TYPE_ADD:
				info->user.UserReportType = _user_credential_user_set_add(cmd, in, info);
				break ;
			case USER_SET_OPERATION_TYPE_MODIFY:
				info->user.UserReportType = _user_credential_user_set_modify(cmd, in, info);
				break ;
			default:
				return (ZUNO_COMMAND_BLOCKED_FAIL);
				break;
		}
		switch (info->user.UserReportType) {
			case USER_REPORT_ADD_AGAINST_OCCUPIED:
			case USER_REPORT_MODIFY_AGAINST_EMPTY:
				rs = ZUNO_COMMAND_BLOCKED_FAIL;
				break ;
		}
		if (in->part2.UserNameLength > sizeof(in->part2.UserName))
			rs = ZUNO_COMMAND_BLOCKED_FAIL;
	}
	if (options->supervision == true)
		zuno_CCSupervisionReportSyncDefault(frame_report, rs);
	_user_credential_user_report_set(&frame_report->info, info);
	zunoSendZWPacketAdd(frame_report);
	switch (info->user.UserReportType) {
		case USER_REPORT_ADDED:
		case USER_REPORT_MODIFIED:
		case USER_REPORT_DELETED:
			fillOutgoingReportPacketUnsolicitedLifeLine(frame_report, options);
			_user_credential_user_report_set(&frame_report->info, info);
			zunoSendZWPacketAdd(frame_report);
			break ;
	}
	return (ZUNO_COMMAND_PROCESSED);
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


static void _user_credential_credential_set_copy_save(const ZUNOCommandCmd_t *cmd, const UserCredentialCredentialSet_t *in, ZwUserCredentialCommon_t *info) {
	info->list_credential.list.info.CredentialModifierType = CREDENTIAL_REPORT_Z_WAVE;
	info->list_credential.list.info.CredentialModifierNodeID[0x0] = cmd->src_node >> 0x8;
	info->list_credential.list.info.CredentialModifierNodeID[0x1] = cmd->src_node;
	info->list_credential.list.info.CredentialLength = in->CredentialLength;
	memcpy(&info->list_credential.list.info.CredentialData[0x0], &in->CredentialData[0x0], in->CredentialLength);
}

static bool _user_credential_credential_set_is_duplicate(const UserCredentialCredentialSet_t *in, ZwUserCredentialCommon_t *info) {
	uint16_t CredentialSlot;
	UserCredentialSaveCredentialInfo_t save_info;

	if ((CredentialSlot = _storage_find_credential_uniq(in->CredentialType, &in->CredentialData[0x0], in->CredentialLength, info)) != 0) {
		info->credential.UserUniqueIdentifier = _storage_extract_credential_header_user_id(&info->list_credential.list);
		info->credential.start.CredentialSlot = CredentialSlot;
		info->credential.next = info->credential.start;
		save_info = info->list_credential.list.info;
		_storage_next_credential_type(info->credential.UserUniqueIdentifier, &info->list_credential.list, &info->credential.next);
		info->list_credential.list.info = save_info;
		memcpy(&info->list_credential.list.info.CredentialData[0x0], &in->CredentialData[0x0], in->CredentialLength);
		return (true);
	}
	return (false);
}

static uint8_t _user_credential_credential_set_add(const ZUNOCommandCmd_t *cmd, const UserCredentialCredentialSet_t *in, ZwUserCredentialCommon_t *info, const UserCredentialStorageInfo_t *storage_info, bool *sender_life) {
	if (_storage_read_user(info->credential.UserUniqueIdentifier, &info->list_user) == false)
		return (CREDENTIAL_REPORT_WRONG_USER_UNIQUE_IDENTIFIER);
	if (_storage_read_credential(info->credential.UserUniqueIdentifier, info->credential.start.CredentialSlot, storage_info, &info->list_credential.list) != 0x0) {
		if (in->CredentialLength != info->list_credential.list.info.CredentialLength)
			return (CREDENTIAL_REPORT_ADD_AGAINST_OCCUPIED);
		if (memcmp(&in->CredentialData[0x0], &info->list_credential.list.info.CredentialData[0x0], in->CredentialLength) != 0x0)
			return (CREDENTIAL_REPORT_ADD_AGAINST_OCCUPIED);
		return (CREDENTIAL_REPORT_UNCHANGED);
	}
	if (_user_credential_credential_set_is_duplicate(in, info) == true)
		return (CREDENTIAL_REPORT_DUPLICATE);
	_user_credential_credential_set_copy_save(cmd, in, info);
	_storage_write_credential(info->credential.UserUniqueIdentifier, info->credential.start.CredentialSlot, storage_info, &info->list_credential.list);
	sender_life[0x0] = true;
	return (CREDENTIAL_REPORT_ADDED);
}

static uint8_t _user_credential_credential_modify(const ZUNOCommandCmd_t *cmd, const UserCredentialCredentialSet_t *in, ZwUserCredentialCommon_t *info, const UserCredentialStorageInfo_t *storage_info, bool *sender_life) {
	if (_storage_read_user(info->credential.UserUniqueIdentifier, &info->list_user) == false)
		return (CREDENTIAL_REPORT_WRONG_USER_UNIQUE_IDENTIFIER);
	if (_storage_read_credential(info->credential.UserUniqueIdentifier, info->credential.start.CredentialSlot, storage_info, &info->list_credential.list) == 0x0)
		return (CREDENTIAL_REPORT_MODIFY_AGAINST_EMPTY);
	if (in->CredentialLength == info->list_credential.list.info.CredentialLength)
		if (memcmp(&in->CredentialData[0x0], &info->list_credential.list.info.CredentialData[0x0], in->CredentialLength) == 0x0)
			return (CREDENTIAL_REPORT_UNCHANGED);
	if (_user_credential_credential_set_is_duplicate(in, info) == true)
		return (CREDENTIAL_REPORT_DUPLICATE);
	_user_credential_credential_set_copy_save(cmd, in, info);
	_storage_write_credential(info->credential.UserUniqueIdentifier, info->credential.start.CredentialSlot, storage_info, &info->list_credential.list);
	sender_life[0x0] = true;
	return (CREDENTIAL_REPORT_MODIFIED);
}

static void _user_credential_credential_set_del_fill(ZwUserCredentialCommon_t *info) {
	memset(&info->list_credential.list.info, 0x0, sizeof(info->list_credential.list.info));
	memset(&info->credential.next, 0x0, sizeof(info->credential.next));
	#if CREDENTIAL_REPORT_DNE != 0x0
	info->list_credential.credential.CredentialModifierType = CREDENTIAL_REPORT_DNE;
	#endif
}

static uint8_t _user_credential_credential_set_del(const UserCredentialStorageInfo_t *storage_info, ZwUserCredentialCommon_t *info, bool *sender_life) {
	uint16_t UserUniqueIdentifier;

	if (storage_info != NULL && info->credential.start.CredentialSlot != 0x0) {
		if ((UserUniqueIdentifier = _storage_read_credential(info->credential.UserUniqueIdentifier, info->credential.start.CredentialSlot, storage_info, &info->list_credential.list)) == 0x0) {
			_user_credential_credential_set_del_fill(info);
			return (CREDENTIAL_REPORT_UNCHANGED);
		}
		info->credential.UserUniqueIdentifier = UserUniqueIdentifier;
		_storage_next_credential_type(info->credential.UserUniqueIdentifier, &info->list_credential.list, &info->credential.next);
		_storage_read_credential(info->credential.UserUniqueIdentifier, info->credential.start.CredentialSlot, storage_info, &info->list_credential.list);
		_storage_clear_credential(info->credential.start.CredentialSlot, storage_info, &info->list_credential.list.header);
		sender_life[0x0] = true;
		return (CREDENTIAL_REPORT_DELETED);
	}
	if (info->credential.UserUniqueIdentifier != 0x0 && info->credential.start.CredentialType == 0x0) {
		sender_life[0x0] = _storage_credential_del_all_types(info->credential.UserUniqueIdentifier, info);
		_user_credential_credential_set_del_fill(info);
		return (CREDENTIAL_REPORT_DELETED);
	}
	if (info->credential.UserUniqueIdentifier == 0x0 && info->credential.start.CredentialType == 0x0 && info->credential.start.CredentialSlot == 0x0) {
		sender_life[0x0] = _storage_credential_del_all_types(0x0, info);
		_user_credential_credential_set_del_fill(info);
		return (CREDENTIAL_REPORT_DELETED);
	}
	if (info->credential.UserUniqueIdentifier != 0x0 && info->credential.start.CredentialType != 0x0 && info->credential.start.CredentialSlot == 0x0) {
		sender_life[0x0] = _storage_credential_del_types(info->credential.UserUniqueIdentifier, info->credential.start.CredentialType, info);
		_user_credential_credential_set_del_fill(info);
		return (CREDENTIAL_REPORT_DELETED);
	}
	if (info->credential.UserUniqueIdentifier == 0x0 && info->credential.start.CredentialType != 0x0 && info->credential.start.CredentialSlot == 0x0) {
		sender_life[0x0] = _storage_credential_del_types(0x0, info->credential.start.CredentialType, info);
		_user_credential_credential_set_del_fill(info);
		return (CREDENTIAL_REPORT_DELETED);
	}
	_user_credential_credential_set_del_fill(info);
	return (CREDENTIAL_REPORT_DELETED);
}

typedef struct					UserCredentialCredentialReportGet_s
{
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						CredentialReportType;
	uint8_t						UserUniqueIdentifier[0x2];/*MSB - LSB*/
	uint8_t						CredentialType;
	uint8_t						CredentialSlot[0x2];/*MSB - LSB*/
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

static void _user_credential_credential_report_set(ZUNOCommandPacketReport_t *frame_report, ZwUserCredentialCommon_t *info) {
	UserCredentialCredentialReportGet_t *report;
	UserCredentialCredentialReportGetEnd_t *report_end;

	report = (UserCredentialCredentialReportGet_t *)frame_report->info.packet.cmd;
	report->cmdClass = COMMAND_CLASS_USER_CREDENTIAL;
	report->cmd = CREDENTIAL_REPORT;
	report->UserUniqueIdentifier[0x0] = info->credential.UserUniqueIdentifier >> 0x8;
	report->UserUniqueIdentifier[0x1] = info->credential.UserUniqueIdentifier;
	report->CredentialReportType = info->credential.CredentialReportType;
	report->CredentialType = info->credential.start.CredentialType;
	report->CredentialSlot[0x0] = info->credential.start.CredentialSlot >> 0x8;
	report->CredentialSlot[0x1] = info->credential.start.CredentialSlot;
	if (report->CredentialType == 0x0)
		report->profile1 = 0x0;
	else
		report->profile1 = CREDENTIAL_REPORT_PROPERTIES1_CRB_BIT_MASK;
	report->CredentialLength = info->list_credential.list.info.CredentialLength;
	memcpy(&report->CredentialData[0x0], &info->list_credential.list.info.CredentialData[0x0], info->list_credential.list.info.CredentialLength);
	report_end = (UserCredentialCredentialReportGetEnd_t *)(frame_report->info.packet.cmd + sizeof(report[0x0]) + report->CredentialLength);
	report_end->CredentialModifierType = info->list_credential.list.info.CredentialModifierType;
	memcpy(&report_end->CredentialModifierNodeID[0x0], &info->list_credential.list.info.CredentialModifierNodeID[0x0], sizeof(report_end->CredentialModifierNodeID));
	report_end->NextCredentialType = info->credential.next.CredentialType;
	report_end->NextCredentialSlot[0x0] = info->credential.next.CredentialSlot >> 0x8;
	report_end->NextCredentialSlot[0x1] = info->credential.next.CredentialSlot;
	frame_report->info.packet.len = sizeof(report[0x0]) + report->CredentialLength + sizeof(report_end[0x0]);
}

static int _user_credential_credential_set(ZUNOCommandPacketReport_t *frame_report, const ZUNOCommandCmd_t *cmd, const UserCredentialCredentialSet_t *in, const ZUNOCommandHandlerOption_t *options, ZwUserCredentialCommon_t *info) {
	const UserCredentialStorageInfo_t *storage_info;
	int rs;
	bool sender_life;

	info->credential.UserUniqueIdentifier = (in->UserUniqueIdentifier[0x0] << 0x8) | in->UserUniqueIdentifier[0x1];
	info->credential.start.CredentialSlot = (in->CredentialSlot[0x0] << 0x8) | in->CredentialSlot[0x1];
	info->credential.start.CredentialType = in->CredentialType;
	rs = ZUNO_COMMAND_PROCESSED;
	sender_life = false;
	if (info->credential.start.CredentialType != 0x0) {
		if ((storage_info = _get_credential_storage_info(info->credential.start.CredentialType)) == NULL)
			return (ZUNO_COMMAND_BLOCKED_FAIL);
		if (info->credential.start.CredentialSlot > storage_info->slot_max)
			return (ZUNO_COMMAND_BLOCKED_FAIL);
	}
	else
		storage_info = NULL;
	info->credential.next = info->credential.start;
	if ((in->profile1 & USER_SET_PROPERTIES1_OPERATION_TYPE_MASK) == USER_SET_OPERATION_TYPE_DELETE) {
		info->credential.CredentialReportType = _user_credential_credential_set_del(storage_info, info, &sender_life);
	}
	else {
		if (storage_info == NULL)
			return (ZUNO_COMMAND_BLOCKED_FAIL);
		if (info->credential.UserUniqueIdentifier > USER_CREDENTIAL_USERS_COUNT)
			return (ZUNO_COMMAND_BLOCKED_FAIL);
		if (info->credential.UserUniqueIdentifier == 0x0)
			return (ZUNO_COMMAND_BLOCKED_FAIL);
		if (info->credential.start.CredentialSlot == 0x0)
			return (ZUNO_COMMAND_BLOCKED_FAIL);
		if (in->CredentialLength > storage_info->CredentialLengthMax)
			return (ZUNO_COMMAND_BLOCKED_FAIL);
		if (in->CredentialLength < storage_info->CredentialLengthMin)
			return (ZUNO_COMMAND_BLOCKED_FAIL);
		_storage_next_credential_type(info->credential.UserUniqueIdentifier, &info->list_credential.list, &info->credential.next);
		switch ((in->profile1 & USER_SET_PROPERTIES1_OPERATION_TYPE_MASK)) {
			case USER_SET_OPERATION_TYPE_ADD:
				info->credential.CredentialReportType = _user_credential_credential_set_add(cmd, in, info, storage_info, &sender_life);
				break ;
			case USER_SET_OPERATION_TYPE_MODIFY:
				info->credential.CredentialReportType = _user_credential_credential_modify(cmd, in, info, storage_info, &sender_life);
				break ;
			default:
				return (ZUNO_COMMAND_BLOCKED_FAIL);
				break;
		}
		switch (info->credential.CredentialReportType) {
			case CREDENTIAL_REPORT_MODIFY_AGAINST_EMPTY:
			case CREDENTIAL_REPORT_WRONG_USER_UNIQUE_IDENTIFIER:
				_user_credential_credential_set_copy_save(cmd, in, info);
				break ;
		}
		switch (info->credential.CredentialReportType) {
			case CREDENTIAL_REPORT_MODIFY_AGAINST_EMPTY:
			case CREDENTIAL_REPORT_WRONG_USER_UNIQUE_IDENTIFIER:
				info->list_credential.list.info.CredentialModifierType = CREDENTIAL_REPORT_DNE;
				memset(&info->list_credential.list.info.CredentialModifierNodeID[0x0], 0x0, sizeof(info->list_credential.list.info.CredentialModifierNodeID));
				break ;
		}
		switch (info->credential.CredentialReportType) {
			case CREDENTIAL_REPORT_DUPLICATE:
			case CREDENTIAL_REPORT_MODIFY_AGAINST_EMPTY:
			case CREDENTIAL_REPORT_ADD_AGAINST_OCCUPIED:
			case CREDENTIAL_REPORT_WRONG_USER_UNIQUE_IDENTIFIER:
				rs = ZUNO_COMMAND_BLOCKED_FAIL;
				break ;
		}
	}
	if (options->supervision == true)
		zuno_CCSupervisionReportSyncDefault(frame_report, rs);
	_user_credential_credential_report_set(frame_report, info);
	zunoSendZWPacketAdd(frame_report);
	if (sender_life == false)
		return (ZUNO_COMMAND_PROCESSED);
	fillOutgoingReportPacketUnsolicitedLifeLine(frame_report, options);
	_user_credential_credential_report_set(frame_report, info);
	zunoSendZWPacketAdd(frame_report);
	return (ZUNO_COMMAND_PROCESSED);
}

typedef struct					UserCredentialCredentialGet_s
{
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						UserUniqueIdentifier[0x2];/*MSB - LSB*/
	uint8_t						CredentialType;
	uint8_t						CredentialSlot[0x2];/*MSB - LSB*/
}								UserCredentialCredentialGet_t;

#define USER_CREDENTIAL_REPORT_GET_USER_ID_ZERO (0x1 << 0x0)
#define USER_CREDENTIAL_REPORT_GET_USER_ID_ZERO_NOT (0x1 << 0x1)
#define USER_CREDENTIAL_REPORT_GET_TYPE_ZERO (0x1 << 0x2)
#define USER_CREDENTIAL_REPORT_GET_TYPE_ZERO_NOT (0x1 << 0x3)
#define USER_CREDENTIAL_REPORT_GET_SLOT_ZERO (0x1 << 0x4)
#define USER_CREDENTIAL_REPORT_GET_SLOT_ZERO_NOT (0x1 << 0x5)

static bool _user_credential_credential_report_user_common(ZwUserCredentialCommon_t *info) {
	const UserCredentialStorageInfo_t *storage_info;

	if (info->credential.start.CredentialType != 0x0) {
		if (info->credential.start.CredentialSlot == 0x0) {
			if ((storage_info = _get_credential_storage_info(info->credential.start.CredentialType)) == NULL)
				return (false);
			if ((info->credential.start.CredentialSlot = _storage_next_credential(info->credential.UserUniqueIdentifier, info->credential.start.CredentialSlot, storage_info, &info->list_credential.list)) == 0x0)
				return (false);
		}
	}
	else if (_storage_next_credential_type(info->credential.UserUniqueIdentifier, &info->list_credential.list, &info->credential.start) == false)
		return (false);
	info->credential.next = info->credential.start;
	_storage_next_credential_type(info->credential.UserUniqueIdentifier, &info->list_credential.list, &info->credential.next);
	if ((storage_info = _get_credential_storage_info(info->credential.start.CredentialType)) == NULL)
		return (false);
	if (_storage_read_credential(info->credential.UserUniqueIdentifier, info->credential.start.CredentialSlot, storage_info, &info->list_credential.list) == 0x0)
		return (false);
	return (true);
}

static bool _user_credential_credential_report_user_not_zero(ZwUserCredentialCommon_t *info) {
	if (_storage_read_user(info->credential.UserUniqueIdentifier, &info->list_user) == false)
		return (false);
	return (_user_credential_credential_report_user_common(info));
}

static bool _user_credential_credential_report_user_zero(ZwUserCredentialCommon_t *info) {
	if (_user_credential_credential_report_user_common(info) == false)
		return (false);
	info->credential.UserUniqueIdentifier = _storage_extract_credential_header_user_id(&info->list_credential.list);
	return (true);
}

static int _user_credential_credential_report_get(ZUNOCommandPacketReport_t *frame_report, const UserCredentialCredentialGet_t *in, ZwUserCredentialCommon_t *info) {
	const UserCredentialStorageInfo_t *storage_info;
	bool res;

	if ((info->credential.UserUniqueIdentifier = (in->UserUniqueIdentifier[0x0] << 0x8) | in->UserUniqueIdentifier[0x1]) > USER_CREDENTIAL_USERS_COUNT)
		return (ZUNO_COMMAND_BLOCKED_FAIL);
	info->credential.start.CredentialSlot = (in->CredentialSlot[0x0] << 0x8) | in->CredentialSlot[0x1];
	if ((info->credential.start.CredentialType = in->CredentialType) != 0x0) {
		if ((storage_info = _get_credential_storage_info(info->credential.start.CredentialType)) == NULL)
			return (ZUNO_COMMAND_BLOCKED_FAIL);
		if (info->credential.start.CredentialSlot > storage_info->slot_max)
			return (ZUNO_COMMAND_BLOCKED_FAIL);
	}
	else if (info->credential.start.CredentialSlot != 0x0)
		return (ZUNO_COMMAND_BLOCKED_FAIL);
	if (info->credential.UserUniqueIdentifier != 0x0)
		res = _user_credential_credential_report_user_not_zero(info);
	else
		res = _user_credential_credential_report_user_zero(info);
	if (res == false)
	{
		memset(&info->credential.next, 0x0, sizeof(info->credential.next));
		memset(&info->list_credential.list.info, 0x0, sizeof(info->list_credential.list.info));
		#if CREDENTIAL_REPORT_DNE != 0x0
		info->list_credential.credential.CredentialModifierType = CREDENTIAL_REPORT_DNE;
		#endif
	}
	info->credential.CredentialReportType = CREDENTIAL_REPORT_RESPONSE_TO_GET;
	_user_credential_credential_report_set(frame_report, info);
	return (ZUNO_COMMAND_ANSWERED);
}

static uint16_t _calc_user_checksum(uint16_t UserUniqueIdentifier, ZwUserCredentialCommon_t *info) {
	uint16_t userChecksum;
	uint16_t CredentialSlot;

	if (_storage_read_user(UserUniqueIdentifier, &info->list_user) == false)
		return (0x0);
	userChecksum = CrcClass::crc16_ccitt_aug(&info->list_user.info.cmp.crc, sizeof(info->list_user.info.cmp.crc));
	memset(&info->credential.start, 0x0, sizeof(info->credential.start));
	while (true) {
		if (_storage_next_credential_type(UserUniqueIdentifier, &info->list_credential.list, &info->credential.start) == false)
			break ;
		info->list_credential.list.info.CredentialModifierType = info->credential.start.CredentialType;
		CredentialSlot = __builtin_bswap16(info->credential.start.CredentialSlot);
		memcpy(&info->list_credential.list.info.CredentialModifierNodeID[0x0], &CredentialSlot, sizeof(info->list_credential.list.info.CredentialModifierNodeID));
		userChecksum = CrcClass::crc16_ccitt_aug(userChecksum, &info->list_credential.list.info, sizeof(info->list_credential.list.info) + info->list_credential.list.info.CredentialLength);
	}
	return (userChecksum);
}

static int _user_credential_users_checksum_report(const ZW_USER_CHECKSUM_GET_FRAME *in, ZUNOCommandPacketReport_t *frame_report, ZwUserCredentialCommon_t *info) {
	ZW_USER_CHECKSUM_REPORT_FRAME *report;
	uint16_t UserUniqueIdentifier;
	uint16_t userChecksum;

	if ((UserUniqueIdentifier = (in->userUniqueIdentifier1 << 0x8) | in->userUniqueIdentifier2) > USER_CREDENTIAL_USERS_COUNT)
		return (ZUNO_COMMAND_BLOCKED_FAIL);
	if (UserUniqueIdentifier == 0x0)
		return (ZUNO_COMMAND_BLOCKED_FAIL);
	report = (ZW_USER_CHECKSUM_REPORT_FRAME *)frame_report->info.packet.cmd;
	// report->cmdClass = COMMAND_CLASS_USER_CREDENTIAL; set in - fillOutgoingPacket
	// report->cmd = USER_CHECKSUM_REPORT; set in - fillOutgoingPacket
	report->userUniqueIdentifier1 = in->userUniqueIdentifier1;
	report->userUniqueIdentifier2 = in->userUniqueIdentifier2;
	userChecksum = _calc_user_checksum(UserUniqueIdentifier, info);
	report->userChecksum1 = userChecksum >> 0x8;
	report->userChecksum2 = userChecksum;
	frame_report->info.packet.len = sizeof(report[0x0]);
	return (ZUNO_COMMAND_ANSWERED);
}

static uint16_t _calc_credential_checksum(const UserCredentialStorageInfo_t *storage_info, ZwUserCredentialCommon_t *info) {
	uint16_t credentialChecksum;
	uint16_t CredentialSlot;
	uint16_t tempos;
	size_t count;

	credentialChecksum = 0x1D0F;
	CredentialSlot = 0x0;
	count = 0x0;
	while (true) {
		if ((CredentialSlot = _storage_next_credential(0x0, CredentialSlot, storage_info, &info->list_credential.list)) == 0x0)
			break ;
		count++;
		tempos = __builtin_bswap16(CredentialSlot);
		memcpy(&info->list_credential.list.info.CredentialModifierNodeID[0x0], &tempos, sizeof(info->list_credential.list.info.CredentialModifierNodeID));
		credentialChecksum = CrcClass::crc16_ccitt_aug(credentialChecksum, &info->list_credential.list.info.CredentialModifierNodeID[0x0],
		(sizeof(info->list_credential.list.info) - sizeof(info->list_credential.list.info.CredentialModifierType)) + info->list_credential.list.info.CredentialLength);
	}
	if (count == 0x0)
		return (0x0);
	return (credentialChecksum);
}

static int _user_credential_credential_checksum_report(const ZW_CREDENTIAL_CHECKSUM_GET_FRAME *in, ZUNOCommandPacketReport_t *frame_report, ZwUserCredentialCommon_t *info) {
	const UserCredentialStorageInfo_t *storage_info;
	ZW_CREDENTIAL_CHECKSUM_REPORT_FRAME *report;
	uint16_t credentialChecksum;

	if ((storage_info = _get_credential_storage_info(in->credentialType)) == NULL)
		return (ZUNO_COMMAND_BLOCKED_FAIL);
	report = (ZW_CREDENTIAL_CHECKSUM_REPORT_FRAME *)frame_report->info.packet.cmd;
	// report->cmdClass = COMMAND_CLASS_USER_CREDENTIAL; set in - fillOutgoingPacket
	// report->cmd = USER_CHECKSUM_REPORT; set in - fillOutgoingPacket
	report->credentialType = in->credentialType;
	credentialChecksum = _calc_credential_checksum(storage_info, info);
	report->credentialChecksum1 = credentialChecksum >> 0x8;
	report->credentialChecksum2 = credentialChecksum;
	frame_report->info.packet.len = sizeof(report[0x0]);
	return (ZUNO_COMMAND_ANSWERED);
}

typedef struct ZwUserCredentialAssociationSetCommon_s
{
	uint8_t   CredentialType;         /**/
	uint8_t   sourceCredentialSlot1;        /* MSB */
	uint8_t   sourceCredentialSlot2;        /* LSB */
	uint8_t   destinationUserUniqueIdentifier1;/* MSB */
	uint8_t   destinationUserUniqueIdentifier2;/* LSB */
	uint8_t   destinationCredentialSlot1;   /* MSB */
	uint8_t   destinationCredentialSlot2;   /* LSB */
} ZwUserCredentialAssociationSetCommon_t;

typedef struct ZwUserCredentialAssociationSet_s
{
	uint8_t   cmdClass;                     /* The command class */
	uint8_t   cmd;                          /* The command */
	ZwUserCredentialAssociationSetCommon_t common;
} ZwUserCredentialAssociationSet_t;

typedef struct ZwUserCredentialAssociationSetReport_s
{
	uint8_t   cmdClass;                     /* The command class */
	uint8_t   cmd;                          /* The command */
	ZwUserCredentialAssociationSetCommon_t common;
	uint8_t   userCredentialAssociationStatus;/**/
} ZwUserCredentialAssociationSetReport_t;

static uint8_t _user_credential_association_set_report_sub(const ZwUserCredentialAssociationSet_t *in, ZwUserCredentialCommon_t *info) {
	UserCredentialSaveCredentialHeader_t header;
	const UserCredentialStorageInfo_t *storage_info;
	uint16_t destinationUserUniqueIdentifier;
	uint16_t sourceCredentialSlot;
	uint16_t destinationCredentialSlot;

	if ((storage_info = _get_credential_storage_info(in->common.CredentialType)) == NULL)
		return (USER_CREDENTIAL_ASSOCIATION_REPORT_CREDENTIAL_TYPE_INVALID);
	if ((destinationUserUniqueIdentifier = (in->common.destinationUserUniqueIdentifier1 << 0x8) | in->common.destinationUserUniqueIdentifier2) > USER_CREDENTIAL_USERS_COUNT)
		return (USER_CREDENTIAL_ASSOCIATION_REPORT_DESTINATION_USER_UNIQUE_IDENTIFIER_INVALID);
	if (destinationUserUniqueIdentifier == 0x0)
		return (USER_CREDENTIAL_ASSOCIATION_REPORT_DESTINATION_USER_UNIQUE_IDENTIFIER_INVALID);
	if ((sourceCredentialSlot = (in->common.sourceCredentialSlot1 << 0x8) | in->common.sourceCredentialSlot2) > storage_info->slot_max)
		return (USER_CREDENTIAL_ASSOCIATION_REPORT_SOURCE_CREDENTIAL_SLOT_INVALID);
	if (sourceCredentialSlot == 0x0)
		return (USER_CREDENTIAL_ASSOCIATION_REPORT_SOURCE_CREDENTIAL_SLOT_INVALID);
	if ((destinationCredentialSlot = (in->common.destinationCredentialSlot1 << 0x8) | in->common.destinationCredentialSlot2) > storage_info->slot_max)
		return (USER_CREDENTIAL_ASSOCIATION_REPORT_DESTINATION_CREDENTIAL_SLOT_INVALID);
	if (destinationCredentialSlot == 0x0)
		return (USER_CREDENTIAL_ASSOCIATION_REPORT_DESTINATION_CREDENTIAL_SLOT_INVALID);
	if (_storage_read_user(destinationUserUniqueIdentifier, &info->list_user) == false)
		return (USER_CREDENTIAL_ASSOCIATION_REPORT_DESTINATION_USER_UNIQUE_IDENTIFIER_NONEXISTENT);
	if (_storage_read_credential(destinationUserUniqueIdentifier, destinationCredentialSlot, storage_info, &info->list_credential.list) != 0x0)
		return (USER_CREDENTIAL_ASSOCIATION_REPORT_DESTINATION_CREDENTIAL_SLOT_OCCUPIED);
	if (_storage_read_credential(0x0, sourceCredentialSlot, storage_info, &info->list_credential.list) == 0x0)
		return (USER_CREDENTIAL_ASSOCIATION_REPORT_SOURCE_CREDENTIAL_SLOT_EMPTY);
	_storage_clear_credential(sourceCredentialSlot, storage_info, &header);
	_storage_write_credential(destinationUserUniqueIdentifier, destinationCredentialSlot, storage_info, &info->list_credential.list);
	return (USER_CREDENTIAL_ASSOCIATION_REPORT_SUCCESS);
}

static int _user_credential_association_set_report(const ZwUserCredentialAssociationSet_t *in, ZUNOCommandPacketReport_t *frame_report, ZwUserCredentialCommon_t *info) {
	ZwUserCredentialAssociationSetReport_t *report;

	report = (ZwUserCredentialAssociationSetReport_t *)frame_report->info.packet.cmd;
	// report->cmdClass = COMMAND_CLASS_USER_CREDENTIAL; set in - fillOutgoingPacket
	// report->cmd = USER_CREDENTIAL_ASSOCIATION_REPORT; set in - fillOutgoingPacket
	report->common = in->common;
	report->userCredentialAssociationStatus = _user_credential_association_set_report_sub(in, info);
	frame_report->info.packet.len = sizeof(report[0x0]);
	return (ZUNO_COMMAND_ANSWERED);
}

static int zuno_CCUserCredentialHandler_sub(const ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report, const ZUNOCommandHandlerOption_t *options, ZwUserCredentialCommon_t *info) {
	int rs;

	switch (ZW_CMD) {
		case USER_GET:
			rs = _user_credential_user_report_get(frame_report, ((const UserCredentialUserGet_t *)&cmd->cmd[0x0]), info);
			break ;
		case USER_SET:
			rs = _user_credential_user_set(frame_report, cmd, ((const UserCredentialUserSet_t *)&cmd->cmd[0x0]), options, info);
			break ;
		case CREDENTIAL_SET:
			rs = _user_credential_credential_set(frame_report, cmd, ((const UserCredentialCredentialSet_t *)&cmd->cmd[0x0]), options, info);
			break ;
		case CREDENTIAL_GET:
			rs = _user_credential_credential_report_get(frame_report, ((const UserCredentialCredentialGet_t *)&cmd->cmd[0x0]), info);
			break ;
		case USER_CHECKSUM_GET:
			rs = _user_credential_users_checksum_report(((const ZW_USER_CHECKSUM_GET_FRAME *)&cmd->cmd[0x0]), frame_report, info);
			break ;
		case CREDENTIAL_CHECKSUM_GET:
			rs = _user_credential_credential_checksum_report(((const ZW_CREDENTIAL_CHECKSUM_GET_FRAME *)&cmd->cmd[0x0]), frame_report, info);
			break ;
		case USER_CREDENTIAL_ASSOCIATION_SET:
			rs = _user_credential_association_set_report(((const ZwUserCredentialAssociationSet_t *)&cmd->cmd[0x0]), frame_report, info);
			break ;
		default:
			rs = ZUNO_COMMAND_BLOCKED_NO_SUPPORT;
			break ;
	}
	return (rs);
}

int zuno_CCUserCredentialHandler(const ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report, const ZUNOCommandHandlerOption_t *options) {
	ZwUserCredentialCommon_t *info;
	int rs;

	switch (ZW_CMD) {
		case USER_CAPABILITIES_GET:
			rs = _user_credential_capabilities_user_report(frame_report);
			break ;
		case CREDENTIAL_CAPABILITIES_GET:
			rs = _user_credential_capabilities_credential_report(frame_report);
			break ;
		default:
			if ((info = (ZwUserCredentialCommon_t *)malloc(sizeof(ZwUserCredentialCommon_t))) == NULL) {
				rs = ZUNO_COMMAND_BLOCKED_MALLOC;
				break ;
			}
			rs = zuno_CCUserCredentialHandler_sub(cmd, frame_report, options, info);
			free(info);
			break ;
	}
	return (rs);
}

bool zuno_CCUserCredentialIsBlockMultiBroadcast(size_t cmd) {
	if (cmd == USER_CAPABILITIES_GET)
		return (true);
	if (cmd == CREDENTIAL_CAPABILITIES_GET)
		return (true);
	if (cmd == USER_GET)
		return (true);
	if (cmd == CREDENTIAL_GET)
		return (true);
	if (cmd == ALL_USERS_CHECKSUM_GET)
		return (true);
	if (cmd == USER_CHECKSUM_GET)
		return (true);
	if (cmd == CREDENTIAL_CHECKSUM_GET)
		return (true);
	if (cmd == ADMIN_PIN_CODE_GET)
		return (true);
	return (false);
}

ssize_t zuno_CCUserCredentialAssociationGroupCommand(_ZwAssociationGroupCommand_t *gpr_info, size_t gpr_info_max) {
	if (gpr_info_max < 2)
		return (-1);
	gpr_info[0].cmdClass = COMMAND_CLASS_USER_CREDENTIAL;
	gpr_info[0].cmd = USER_REPORT;
	gpr_info[1].cmdClass = COMMAND_CLASS_USER_CREDENTIAL;
	gpr_info[1].cmd = CREDENTIAL_REPORT;
	return (2);
}

bool user_credential_find_key(const uint8_t *CredentialData, uint8_t CredentialLength) {
	return (false);
	(void)CredentialData;
	(void)CredentialLength;
}


#endif//WITH_CC_USER_CREDENTIAL