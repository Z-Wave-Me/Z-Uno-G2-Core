#include "Arduino.h"
#include "ZWCCUserCredential.h"

#ifdef WITH_CC_USER_CREDENTIAL

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

typedef struct					UserCredentialCapabilitiesReport_s
{
	uint8_t						cmdClass;/* The command class */
	uint8_t						cmd;/* The command */
	uint8_t						userIdentifier[0x2];/*MSB - LSB*/
	uint8_t						SupportedCredentialRulesBitMask;
	uint8_t						MaxLengthofUserName;
	uint8_t						property1;
	uint8_t						SupportedUserTypesBitMaskLength;
	uint8_t						SupportedUserTypesBitMask[];
}								UserCredentialCapabilitiesReport_t;

static int _user_credential_capabilities_report(ZUNOCommandPacketReport_t *frame_report) {
	UserCredentialCapabilitiesReport_t				*report;
	uint8_t											len;

	report = (UserCredentialCapabilitiesReport_t *)frame_report->packet.cmd;
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


int zuno_CCUserCredentialHandler(ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	int								rs;

	switch (ZW_CMD) {
		case USER_CREDENTIAL_CAPABILITIES_USER_GET:
			rs = _user_credential_capabilities_report(frame_report);
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