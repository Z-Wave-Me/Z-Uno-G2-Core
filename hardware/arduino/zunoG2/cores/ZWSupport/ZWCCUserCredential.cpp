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

static_assert(USER_CREDENTIAL_NUMBER <= 0xFFFF && USER_CREDENTIAL_NUMBER >= 0x1, "USER_CREDENTIAL_NUMBER - max 0xFFFF and min 0x1!!!");
#if defined(USER_CREDENTIAL_NUMBER_PIN_CODE)
static_assert(USER_CREDENTIAL_NUMBER_PIN_CODE <= 0xFFFF && USER_CREDENTIAL_NUMBER_PIN_CODE >= 0x1, "USER_CREDENTIAL_NUMBER_PIN_CODE - max 0xFFFF and min 0x1!!!");
static_assert(USER_CREDENTIAL_NUMBER_PIN_CODE_MIN_LENGHT >= 0x1, "USER_CREDENTIAL_NUMBER_PIN_CODE_MIN_LENGHT - min 0x1!!!");
static_assert(USER_CREDENTIAL_NUMBER_PIN_CODE_MAX_LENGHT <= 0xFFFF, "USER_CREDENTIAL_NUMBER_PIN_CODE_MAX_LENGHT - max 0xFFFF!!!");
static_assert(USER_CREDENTIAL_NUMBER_PIN_CODE_MIN_LENGHT < USER_CREDENTIAL_NUMBER_PIN_CODE_MAX_LENGHT, "Must USER_CREDENTIAL_NUMBER_PIN_CODE_MAX_LENGHT < USER_CREDENTIAL_NUMBER_PIN_CODE_MIN_LENGHT!!!");
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

#define USER_CREDENTIAL_TYPE_PIN_CODE							(0x1)
#define USER_CREDENTIAL_TYPE_PASSWORD							(0x2)
#define USER_CREDENTIAL_TYPE_RFID_CODE							(0x3)

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

static const uint32_t _user_credential_type_mask = ((0x1 << USER_CREDENTIAL_TYPE_GENERAL_USER));
static const uint32_t _user_supported_credential_rules_mask = ((0x1 << USER_CREDENTIAL_RULE_SINGLE) | (0x1 << USER_CREDENTIAL_RULE_DUAL) | (0x1 << USER_CREDENTIAL_RULE_TRIPLE));

static bool _get_user_add(UserCredentialSaveUserId_t *user, uint32_t addr, UserCredentialSaveMask_t *mask, uint16_t userIdentifier) {
	UserCredentialSaveUserId_t									user_temp;
	const UserCredentialSaveUserId_t							*user_id;
	uint16_t													crc16;

	crc16 = mask->crc16_mask[(0x2 * (userIdentifier % (USER_CREDENTIAL_NUMBER_MASK_LENGHT))) + 0x0] | (mask->crc16_mask[(0x2 * (userIdentifier % (USER_CREDENTIAL_NUMBER_MASK_LENGHT))) + 0x1] << 0x8);
	if (crc16 == 0x0)
		return (false);
	user_id = (const UserCredentialSaveUserId_t *)(addr + (sizeof(UserCredentialSaveMask_t) * 0x2));
	addr = (uint32_t)&user_id[userIdentifier % (USER_CREDENTIAL_NUMBER_MASK_LENGHT)];
	zunoEEPROMRead(addr, sizeof(user_temp), (byte *)&user_temp);
	if (CrcClass::crc16_ccitt_aug(&user_temp, sizeof(user_temp)) != crc16)
		return (false);
	user[0x0] = user_temp;
	return (true);
}

static bool _get_user(UserCredentialSaveUserId_t *user, uint16_t userIdentifier) {
	UserCredentialSaveMask_t									mask;
	uint32_t													addr;
	size_t														offset;
	uint16_t													crc16;

	userIdentifier--;
	offset = userIdentifier / (USER_CREDENTIAL_NUMBER_MASK_LENGHT);
	addr = (USER_CREDENTIAL_ADDR_USER) + (offset * (sizeof(UserCredentialSaveMask_t) * 0x2)) + (offset * ((USER_CREDENTIAL_NUMBER_MASK_LENGHT) * sizeof(UserCredentialSaveUserId_t)));
	zunoEEPROMRead(addr, sizeof(mask), (byte *)&mask);
	crc16 = CrcClass::crc16_ccitt_aug(&mask.crc16_mask[0x0], sizeof(mask.crc16_mask));
	if (memcmp(&crc16, &mask.crc16[0x0], sizeof(crc16)) != 0x0)
		return (false);
	return (_get_user_add(user, addr, &mask, userIdentifier));
}

static void _set_user(UserCredentialSaveUserId_t *user, uint16_t userIdentifier) {
	UserCredentialSaveMask_t									mask;
	const UserCredentialSaveUserId_t							*user_id;
	uint32_t													addr_user_id;
	uint32_t													addr_mask;
	size_t														offset;
	uint16_t													crc16;

	userIdentifier--;
	offset = userIdentifier / (USER_CREDENTIAL_NUMBER_MASK_LENGHT);
	addr_mask = (USER_CREDENTIAL_ADDR_USER) + (offset * (sizeof(UserCredentialSaveMask_t) * 0x2)) + (offset * ((USER_CREDENTIAL_NUMBER_MASK_LENGHT) * sizeof(UserCredentialSaveUserId_t)));
	zunoEEPROMRead(addr_mask, sizeof(mask), (byte *)&mask);
	crc16 = CrcClass::crc16_ccitt_aug(&mask.crc16_mask[0x0], sizeof(mask.crc16_mask));
	if (memcmp(&crc16, &mask.crc16[0x0], sizeof(crc16)) != 0x0) {
		memset(&mask.crc16_mask[0x0], 0x0, sizeof(mask.crc16_mask));
	}
	user_id = (const UserCredentialSaveUserId_t *)(addr_mask + (sizeof(UserCredentialSaveMask_t) * 0x2));
	addr_user_id = (uint32_t)&user_id[userIdentifier % (USER_CREDENTIAL_NUMBER_MASK_LENGHT)];
	zunoEEPROMWrite(addr_user_id, sizeof(user[0x0]), (byte *)user);
	crc16 = CrcClass::crc16_ccitt_aug(user, sizeof(user[0x0]));
	mask.crc16_mask[(0x2 * (userIdentifier % (USER_CREDENTIAL_NUMBER_MASK_LENGHT))) + 0x0] = crc16;
	mask.crc16_mask[(0x2 * (userIdentifier % (USER_CREDENTIAL_NUMBER_MASK_LENGHT))) + 0x1] = crc16 >> 0x8;
	crc16 = CrcClass::crc16_ccitt_aug(&mask.crc16_mask[0x0], sizeof(mask.crc16_mask));
	memcpy(&mask.crc16[0x0], &crc16, sizeof(crc16));
	zunoEEPROMWrite(addr_mask, sizeof(mask), (byte *)&mask);
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

static uint16_t _get_next_user(uint16_t userIdentifier) {
	uint32_t									addr_mask;
	size_t										offset;
	uint16_t									crc16;
	UserCredentialSaveMask_t					mask;
	UserCredentialSaveUserId_t					user;

	while (userIdentifier < USER_CREDENTIAL_NUMBER) {
		offset = (userIdentifier) / (USER_CREDENTIAL_NUMBER_MASK_LENGHT);
		addr_mask = (USER_CREDENTIAL_ADDR_USER) + (offset * (sizeof(UserCredentialSaveMask_t) * 0x2)) + (offset * ((USER_CREDENTIAL_NUMBER_MASK_LENGHT) * sizeof(UserCredentialSaveUserId_t)));
		zunoEEPROMRead(addr_mask, sizeof(mask), (byte *)&mask);
		crc16 = CrcClass::crc16_ccitt_aug(&mask.crc16_mask[0x0], sizeof(mask.crc16_mask));
		if (memcmp(&crc16, &mask.crc16[0x0], sizeof(crc16)) == 0x0) {
			while (userIdentifier < USER_CREDENTIAL_NUMBER_MASK_LENGHT && userIdentifier < USER_CREDENTIAL_NUMBER) {
				if (_get_user_add(&user, addr_mask, &mask, userIdentifier) == true) {
					return (userIdentifier + 0x1);
				}
				userIdentifier++;
			}
			continue ;
		}
		userIdentifier = userIdentifier + USER_CREDENTIAL_NUMBER_MASK_LENGHT;
	}
	return (0x0);
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
	report->SupportedCredentialRulesBitMask = (0x1 << USER_CREDENTIAL_RULE_SINGLE) | (0x1 << USER_CREDENTIAL_RULE_DUAL) | (0x1 << USER_CREDENTIAL_RULE_TRIPLE);
	report->MaxLengthofUserName = USER_CREDENTIAL_NAME_MAX_LENGHT;
	report->property1 = (0x1 << USER_CREDENTIAL_SUPPORT_CHECKSUM_ALL_USERS) | (0x1 << USER_CREDENTIAL_SUPPORT_CHECKSUM_USER);
	#ifdef WITH_CC_SCHEDULE_ENTRY_LOCK
	report->property1 = report->property1 | (0x1 << USER_CREDENTIAL_SUPPORT_SCHEDULE);
	#endif
	len = ((((sizeof(_user_credential_type_mask) * 0x8) - __builtin_clz(_user_credential_type_mask)) >> 0x3) + 0x1);
	report->SupportedUserTypesBitMaskLength = len;
	frame_report->packet.len = sizeof(report[0x0]) + len;
	memcpy(&report->SupportedUserTypesBitMask[0x0], (uint8_t *)&_user_credential_type_mask, len);
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
	uint16_t										NextUserIdentifier;

	NextUserIdentifier = _get_next_user(userIdentifier);
	report->NextUserIdentifier[0x0] = NextUserIdentifier >> 0x8;
	report->NextUserIdentifier[0x1] = NextUserIdentifier;
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
	uint16_t									NextUserIdentifier;
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
	if (_get_user(&save_user, userIdentifier) == false)
		return (_user_credential_user_report_get_not(frame_report, report, userIdentifier));
	NextUserIdentifier = _get_next_user(userIdentifier);
	report->NextUserIdentifier[0x0] = NextUserIdentifier >> 0x8;
	report->NextUserIdentifier[0x1] = NextUserIdentifier;
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
	if (UserType >= (sizeof(_user_credential_type_mask) * 0x8) || (_user_credential_type_mask & (0x1 << UserType)) == 0x0)
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

	save_user_id.set = in->set;
	if (_user_credential_user_set_valid_in(&save_user_id.set, UserUniqueIdentifier) == false)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	if (_get_user(&save_user_id, UserUniqueIdentifier) == true)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	save_user_id.UserModifierType = USER_CREDENTIAL_MODIFY_TYPE_ZWAVE;
	save_user_id.UserModifierNodeID[0x0] = cmd->src_node >> 0x8;
	save_user_id.UserModifierNodeID[0x1] = cmd->src_node;
	_set_user(&save_user_id, UserUniqueIdentifier);
	return (ZUNO_COMMAND_PROCESSED);
}

static int _user_credential_user_set_modify(ZUNOCommandPacket_t *cmd, const UserCredentialUserSet_t *in, uint16_t UserUniqueIdentifier) {
	UserCredentialSaveUserId_t									save_user_id;
	uint16_t													crc16;

	if (_get_user(&save_user_id, UserUniqueIdentifier) == false)
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
	_set_user(&save_user_id, UserUniqueIdentifier);
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
		default:
			Serial0.print("zuno_CCUserCredentialHandler: ");
			Serial0.println(ZW_CMD);
			rs = ZUNO_UNKNOWN_CMD;
			break ;
	}
	return (rs);
	(void)cmd;
	(void)frame_report;
}

#endif//WITH_CC_USER_CREDENTIAL