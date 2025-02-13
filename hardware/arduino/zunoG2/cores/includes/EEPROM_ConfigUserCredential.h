#ifndef EEPROM_CONFIG_USER_CREDENTIAL_H
#define EEPROM_CONFIG_USER_CREDENTIAL_H

#ifdef WITH_CC_USER_CREDENTIAL

#define USER_CREDENTIAL_ADDR ((uint32_t)&((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential)
#define USER_CREDENTIAL_SIZE (sizeof(((ZwEepromSketh_t *)EEPROM_SKETH_ADDR)->common.info.user_credential))

#if !defined(USER_CREDENTIAL_USERS_COUNT)
#error "The number of users is not specified - to do this, define USER_CREDENTIALS_USERS_COUNT"
#endif

#if !defined(USER_CREDENTIAL_USERS_NAME_MAX_LENGHT)
#error "The length of the user name is not specified. For this, define USER_CREDENTIALS_USERS_COUNT"
#endif

#if !defined(USER_CREDENTIAL_PIN_CODE_SLOTS_COUNT) && !defined(USER_CREDENTIAL_PASSWORD_SLOTS_COUNT) && !defined(USER_CREDENTIAL_RFID_CODE_SLOTS_COUNT) && !defined(USER_CREDENTIAL_BLE_SLOTS_COUNT) && !defined(USER_CREDENTIAL_NFC_SLOTS_COUNT)\
&& !defined(USER_CREDENTIAL_UWB_SLOTS_COUNT) && !defined(USER_CREDENTIAL_EYE_BIOMETRIC_SLOTS_COUNT) && !defined(USER_CREDENTIAL_FACE_BIOMETRIC_SLOTS_COUNT) && !defined(USER_CREDENTIAL_FINGER_BIOMETRIC_SLOTS_COUNT)\
&& !defined(USER_CREDENTIAL_HAND_BIOMETRIC_SLOTS_COUNT) && !defined(USER_CREDENTIAL_UNSPECIFIED_BIOMETRIC_SLOTS_COUNT)
#error "No usercredential type is defined. To do this, specify only these define: USER_CREDENTIALS_PIN_CODE_SLOTS_COUNT, USER_CREDENTIAL_PASSWORD_SLOTS_COUNT, USER_CREDENTIAL_RFID_CODE_SLOTS_COUNT, USER_CREDENTIAL_BLE_SLOTS_COUNT, USER_CREDENTIAL_NFC_SLOTS_COUNT, USER_CREDENTIAL_UWB_SLOTS_COUNT,\
USER_CREDENTIAL_EYE_BIOMETRIC_SLOTS_COUNT, USER_CREDENTIAL_FACE_BIOMETRIC_SLOTS_COUNT, USER_CREDENTIAL_FINGER_BIOMETRIC_SLOTS_COUNT, USER_CREDENTIAL_HAND_BIOMETRIC_SLOTS_COUNT, USER_CREDENTIAL_UNSPECIFIED_BIOMETRIC_SLOTS_COUNT"
#endif

#if defined(USER_CREDENTIAL_PIN_CODE_SLOTS_COUNT)
	#if !defined(USER_CREDENTIAL_PIN_CODE_MIN_LENGHT)
	#error "The minimum data length for USER_CREDENTIAL_PIN_CODE_SLOTS_COUNT is not defined. To do this, define USER_CREDENTIAL_PIN_CODE_MIN_LENGHT"
	#endif
	#if !defined(USER_CREDENTIAL_PIN_CODE_MAX_LENGHT)
	#error "The maximum data length for USER_CREDENTIAL_PIN_CODE_SLOTS_COUNT is not defined, For this, define USER_CREDENTIAL_PIN_CODE_MAX_LENGHT"
	#endif
#endif
#if defined(USER_CREDENTIAL_PASSWORD_SLOTS_COUNT)
	#if !defined(USER_CREDENTIAL_PASSWORD_MIN_LENGHT)
	#error "The minimum data length for USER_CREDENTIAL_PASSWORD_SLOTS_COUNT is not defined. To do this, define USER_CREDENTIAL_PASSWORD_MIN_LENGHT"
	#endif
	#if !defined(USER_CREDENTIAL_PASSWORD_MAX_LENGHT)
	#error "The maximum data length for USER_CREDENTIAL_PASSWORD_SLOTS_COUNT is not defined. To do this, define USER_CREDENTIAL_PASSWORD_MAX_LENGHT"
	#endif
#endif
#if defined(USER_CREDENTIAL_RFID_CODE_SLOTS_COUNT)
	#if !defined(USER_CREDENTIAL_RFID_CODE_MIN_LENGHT)
	#error "The minimum data length for USER_CREDENTIAL_RFID_CODE_SLOTS_COUNT is not defined. To do this, define USER_CREDENTIAL_RFID_CODE_MIN_LENGHT"
	#endif
	#if !defined(USER_CREDENTIAL_RFID_CODE_MAX_LENGHT)
	#error "The maximum data length for USER_CREDENTIAL_RFID_CODE_SLOTS_COUNT is not defined. To do this, define USER_CREDENTIAL_RFID_CODE_MAX_LENGHT"
	#endif
#endif
#if defined(USER_CREDENTIAL_BLE_SLOTS_COUNT)
	#if !defined(USER_CREDENTIAL_BLE_MIN_LENGHT)
	#error "The minimum data length for USER_CREDENTIAL_BLE_SLOTS_COUNT is not defined. To do this, define USER_CREDENTIAL_BLE_MIN_LENGHT"
	#endif
	#if !defined(USER_CREDENTIAL_BLE_MAX_LENGHT)
	#error "The maximum data length for USER_CREDENTIAL_BLE_SLOTS_COUNT is not defined. To do this, define USER_CREDENTIAL_BLE_MAX_LENGHT"
	#endif
#endif
#if defined(USER_CREDENTIAL_NFC_SLOTS_COUNT)
	#if !defined(USER_CREDENTIAL_NFC_MIN_LENGHT)
	#error "The minimum data length for USER_CREDENTIAL_NFC_SLOTS_COUNT is not defined. To do this, define USER_CREDENTIAL_NFC_MIN_LENGHT"
	#endif
	#if !defined(USER_CREDENTIAL_NFC_MAX_LENGHT)
	#error "The maximum data length for USER_CREDENTIAL_NFC_SLOTS_COUNT is not defined. To do this, define USER_CREDENTIAL_NFC_MAX_LENGHT"
	#endif
#endif
#if defined(USER_CREDENTIAL_UWB_SLOTS_COUNT)
	#if !defined(USER_CREDENTIAL_UWB_MIN_LENGHT)
	#error "The minimum data length for USER_CREDENTIAL_UWB_SLOTS_COUNT is not defined. To do this, define USER_CREDENTIAL_UWB_MIN_LENGHT"
	#endif
	#if !defined(USER_CREDENTIAL_UWB_MAX_LENGHT)
	#error "The maximum data length for USER_CREDENTIAL_UWB_SLOTS_COUNT is not defined. To do this, define USER_CREDENTIAL_UWB_MAX_LENGHT"
	#endif
#endif
#if defined(USER_CREDENTIAL_EYE_BIOMETRIC_SLOTS_COUNT)
	#if !defined(USER_CREDENTIAL_EYE_BIOMETRIC_MIN_LENGHT)
	#error "The minimum data length for USER_CREDENTIAL_EYE_BIOMETRIC_SLOTS_COUNT is not defined. To do this, define USER_CREDENTIAL_EYE_BIOMETRIC_MIN_LENGHT"
	#endif
	#if !defined(USER_CREDENTIAL_EYE_BIOMETRIC_MAX_LENGHT)
	#error "The maximum data length for USER_CREDENTIAL_EYE_BIOMETRIC_SLOTS_COUNT is not defined. To do this, define USER_CREDENTIAL_EYE_BIOMETRIC_MAX_LENGHT"
	#endif
#endif
#if defined(USER_CREDENTIAL_FACE_BIOMETRIC_SLOTS_COUNT)
	#if !defined(USER_CREDENTIAL_FACE_BIOMETRIC_MIN_LENGHT)
	#error "The minimum data length for USER_CREDENTIAL_FACE_BIOMETRIC_SLOTS_COUNT is not defined. To do this, define USER_CREDENTIAL_FACE_BIOMETRIC_MIN_LENGHT"
	#endif
	#if !defined(USER_CREDENTIAL_FACE_BIOMETRIC_MAX_LENGHT)
	#error "The maximum data length for USER_CREDENTIAL_FACE_BIOMETRIC_SLOTS_COUNT is not defined. To do this, define USER_CREDENTIAL_FACE_BIOMETRIC_MAX_LENGHT"
	#endif
#endif
#if defined(USER_CREDENTIAL_FINGER_BIOMETRIC_SLOTS_COUNT)
	#if !defined(USER_CREDENTIAL_FINGER_BIOMETRIC_MIN_LENGHT)
	#error "The minimum data length for USER_CREDENTIAL_FINGER_BIOMETRIC_SLOTS_COUNT is not defined. To do this, define USER_CREDENTIAL_FINGER_BIOMETRIC_MIN_LENGHT"
	#endif
	#if !defined(USER_CREDENTIAL_FINGER_BIOMETRIC_MAX_LENGHT)
	#error "The maximum data length for USER_CREDENTIAL_FINGER_BIOMETRIC_SLOTS_COUNT is not defined. To do this, define USER_CREDENTIAL_FINGER_BIOMETRIC_MAX_LENGHT"
	#endif
#endif
#if defined(USER_CREDENTIAL_HAND_BIOMETRIC_SLOTS_COUNT)
	#if !defined(USER_CREDENTIAL_HAND_BIOMETRIC_MIN_LENGHT)
	#error "The minimum data length for USER_CREDENTIAL_HAND_BIOMETRIC_SLOTS_COUNT is not defined. To do this, define USER_CREDENTIAL_HAND_BIOMETRIC_MIN_LENGHT"
	#endif
	#if !defined(USER_CREDENTIAL_HAND_BIOMETRIC_MAX_LENGHT)
	#error "The maximum data length for USER_CREDENTIAL_HAND_BIOMETRIC_SLOTS_COUNT is not defined. To do this, define USER_CREDENTIAL_HAND_BIOMETRIC_MAX_LENGHT"
	#endif
#endif
#if defined(USER_CREDENTIAL_UNSPECIFIED_BIOMETRIC_SLOTS_COUNT)
	#if !defined(USER_CREDENTIAL_UNSPECIFIED_BIOMETRIC_MIN_LENGHT)
	#error "The minimum data length for USER_CREDENTIAL_UNSPECIFIED_BIOMETRIC_SLOTS_COUNT is not defined. To do this, define USER_CREDENTIAL_UNSPECIFIED_BIOMETRIC_MIN_LENGHT"
	#endif
	#if !defined(USER_CREDENTIAL_UNSPECIFIED_BIOMETRIC_MAX_LENGHT)
	#error "The maximum data length for USER_CREDENTIAL_UNSPECIFIED_BIOMETRIC_SLOTS_COUNT is not defined. To do this, define USER_CREDENTIAL_UNSPECIFIED_BIOMETRIC_MAX_LENGHT"
	#endif
#endif

#if USER_CREDENTIAL_USERS_COUNT >= 0x100
typedef uint16_t user_credential_user_id_type;
#else
typedef uint8_t user_credential_user_id_type;
#endif

typedef struct UserCredentialSaveUserIdInfoExpiring_s
{
	uint8_t ExpiringTimeoutMinutes[0x2];/*MSB - LSB*/
} UserCredentialSaveUserIdInfoExpiring_t;

typedef struct UserCredentialSaveUserIdInfoPart1_s
{
	uint8_t UserType;
	uint8_t profile2;
	uint8_t CredentialRule;
} UserCredentialSaveUserIdInfoPart1_t;

typedef struct UserCredentialSaveUserIdInfoPart2_s
{
	uint8_t profile3;
	uint8_t UserNameLength;
	uint8_t UserName[USER_CREDENTIAL_USERS_NAME_MAX_LENGHT];
} UserCredentialSaveUserIdInfoPart2_t;

typedef struct UserCredentialSaveUserIdInfoCrc_s
{
	UserCredentialSaveUserIdInfoPart1_t part1;
	UserCredentialSaveUserIdInfoPart2_t part2;
} UserCredentialSaveUserIdInfoCrc_t;

typedef struct UserCredentialSaveUserIdInfoModify_s
{
	uint8_t UserModifierType;
	uint8_t UserModifierNodeID[0x2];/*MSB - LSB*/
} UserCredentialSaveUserIdInfoModify_t;

typedef struct UserCredentialSaveUserIdCmp_s
{
	UserCredentialSaveUserIdInfoExpiring_t expiring;
	UserCredentialSaveUserIdInfoCrc_t crc;
} UserCredentialSaveUserIdCmp_t;

typedef struct UserCredentialSaveUserId_s
{
	UserCredentialSaveUserIdInfoModify_t modify;
	UserCredentialSaveUserIdCmp_t cmp;
} UserCredentialSaveUserId_t;


typedef struct UserCredentialSaveUserIdHeader_s
{
	uint8_t crc16[0x2];//LSB - MSB
} UserCredentialSaveUserIdHeader_t;

typedef struct UserCredentialSaveUserIdList_s
{
	UserCredentialSaveUserIdHeader_t header;
	UserCredentialSaveUserId_t info;
} UserCredentialSaveUserIdList_t;

typedef struct UserCredentialSaveMask_s
{
	uint8_t crc16[0x2];//LSB - MSB
	uint8_t crc16_mask[];
} UserCredentialSaveMask_t;

typedef struct UserCredentialSaveCredentialHeader_s
{
	uint8_t crc16[0x2];//LSB - MSB
	uint8_t crc8_data;
	uint8_t user_id[sizeof(user_credential_user_id_type)];
} UserCredentialSaveCredentialHeader_t;

typedef struct UserCredentialSaveCredentialInfo_s
{
	uint8_t CredentialModifierType;
	uint8_t CredentialModifierNodeID[0x2];/*MSB - LSB*/
	uint8_t CredentialLength;
	uint8_t CredentialData[];
} UserCredentialSaveCredentialInfo_t;

typedef struct UserCredentialSaveCredentialList_s
{
	UserCredentialSaveCredentialHeader_t header;
	UserCredentialSaveCredentialInfo_t info;
} UserCredentialSaveCredentialList_t;

typedef struct UserCredentialSaveCommonCredential_s
{
	uint8_t crc16_check[0x2];//LSB - MSB
	UserCredentialSaveUserIdList_t user[USER_CREDENTIAL_USERS_COUNT];
	#if defined(USER_CREDENTIAL_PIN_CODE_SLOTS_COUNT)
	uint8_t pin_code[(((sizeof(UserCredentialSaveCredentialList_t) + USER_CREDENTIAL_PIN_CODE_MAX_LENGHT) * USER_CREDENTIAL_PIN_CODE_SLOTS_COUNT))];
	#endif
	#if defined(USER_CREDENTIAL_PASSWORD_SLOTS_COUNT)
	uint8_t password[(((sizeof(UserCredentialSaveCredentialList_t) + USER_CREDENTIAL_PASSWORD_MAX_LENGHT) * USER_CREDENTIAL_PASSWORD_SLOTS_COUNT))];
	#endif
	#if defined(USER_CREDENTIAL_RFID_CODE_SLOTS_COUNT)
	uint8_t rfid_code[(((sizeof(UserCredentialSaveCredentialList_t) + USER_CREDENTIAL_RFID_CODE_MAX_LENGHT) * USER_CREDENTIAL_RFID_CODE_SLOTS_COUNT))];
	#endif
	#if defined(USER_CREDENTIAL_BLE_SLOTS_COUNT)
	uint8_t ble[(((sizeof(UserCredentialSaveCredentialList_t) + USER_CREDENTIAL_BLE_MAX_LENGHT) * USER_CREDENTIAL_BLE_SLOTS_COUNT))];
	#endif
	#if defined(USER_CREDENTIAL_NFC_SLOTS_COUNT)
	uint8_t nfc[(((sizeof(UserCredentialSaveCredentialList_t) + USER_CREDENTIAL_NFC_MAX_LENGHT) * USER_CREDENTIAL_NFC_SLOTS_COUNT))];
	#endif
	#if defined(USER_CREDENTIAL_UWB_SLOTS_COUNT)
	uint8_t uwb[(((sizeof(UserCredentialSaveCredentialList_t) + USER_CREDENTIAL_UWB_MAX_LENGHT) * USER_CREDENTIAL_UWB_SLOTS_COUNT))];
	#endif
	#if defined(USER_CREDENTIAL_EYE_BIOMETRIC_SLOTS_COUNT)
	uint8_t eye_biometric[(((sizeof(UserCredentialSaveCredentialList_t) + USER_CREDENTIAL_EYE_BIOMETRIC_MAX_LENGHT) * USER_CREDENTIAL_EYE_BIOMETRIC_SLOTS_COUNT))];
	#endif
	#if defined(USER_CREDENTIAL_FACE_BIOMETRIC_SLOTS_COUNT)
	uint8_t face_biometric[(((sizeof(UserCredentialSaveCredentialList_t) + USER_CREDENTIAL_FACE_BIOMETRIC_MAX_LENGHT) * USER_CREDENTIAL_FACE_BIOMETRIC_SLOTS_COUNT))];
	#endif
	#if defined(USER_CREDENTIAL_FINGER_BIOMETRIC_SLOTS_COUNT)
	uint8_t finger_biometric[(((sizeof(UserCredentialSaveCredentialList_t) + USER_CREDENTIAL_FINGER_BIOMETRIC_MAX_LENGHT) * USER_CREDENTIAL_FINGER_BIOMETRIC_SLOTS_COUNT))];
	#endif
	#if defined(USER_CREDENTIAL_HAND_BIOMETRIC_SLOTS_COUNT)
	uint8_t hand_biometric[(((sizeof(UserCredentialSaveCredentialList_t) + USER_CREDENTIAL_HAND_BIOMETRIC_MAX_LENGHT) * USER_CREDENTIAL_HAND_BIOMETRIC_SLOTS_COUNT))];
	#endif
	#if defined(USER_CREDENTIAL_UNSPECIFIED_BIOMETRIC_SLOTS_COUNT)
	uint8_t unspecified_biometric[(((sizeof(UserCredentialSaveCredentialList_t) + USER_CREDENTIAL_UNSPECIFIED_BIOMETRIC_MAX_LENGHT) * USER_CREDENTIAL_UNSPECIFIED_BIOMETRIC_SLOTS_COUNT))];
	#endif
} UserCredentialSaveCommonCredential_t;

typedef struct UserCredentialSaveCommon_s
{
	UserCredentialSaveCommonCredential_t credential;
} UserCredentialSaveCommon_t;

#endif//WITH_CC_USER_CREDENTIAL
#endif//EEPROM_CONFIG_USER_CREDENTIAL_H