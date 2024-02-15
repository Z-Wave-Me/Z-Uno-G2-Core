#include "Arduino.h"
#include "ZWCCUserCredential.h"

#ifdef WITH_CC_USER_CREDENTIAL

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


int zuno_CCUserCredentialHandler(ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	int								rs;

	switch (ZW_CMD) {
		case USER_CREDENTIAL_CAPABILITIES_USER_GET:
			rs = _user_credential_capabilities_user_report(frame_report);
			break ;
		case USER_CREDENTIAL_CAPABILITIES_CREDENTIAL_GET:
			rs = _user_credential_capabilities_credential_report(frame_report);
			break ;
		default:
			rs = ZUNO_UNKNOWN_CMD;
			break ;
	}
	return (rs);
	(void)cmd;
	(void)frame_report;
}

#endif//WITH_CC_USER_CREDENTIAL