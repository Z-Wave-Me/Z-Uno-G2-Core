#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCUserCode.h"
#include <string.h>

__WEAK uint8_t __g_zuno_user_code_asii_mask[0x10] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xFF, 0x03, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};


__WEAK ZwUserCodeParametr_t __g_zuno_user_code_param[] = 
{
	{
		.userCode = {0x0, 0x0, 0x0, 0x0},
		{
			.userIdStatus = USER_CODE_STATUS_AVAILABLE,
			.userCodeLen = 0x4
		}
	}
};
__WEAK uint16_t __g_zuno_user_code_param_count = (sizeof(__g_zuno_user_code_param) / sizeof(ZwUserCodeParametr_t));

static ZwUserCodeMaster_t __g_zuno_user_code_param_master;

static uint8_t __g_zuno_user_code_keypad_mode_current = USER_CODE_KEYPAD_MODE_NORMA;
// extern uint8_t __g_zuno_user_code_keypad_mode_current;

#define ZUNO_USER_CODE_KEYPAD_MODE_SET(mode)			__g_zuno_user_code_keypad_mode_current = mode
#define ZUNO_USER_CODE_KEYPAD_MODE_GET()				__g_zuno_user_code_keypad_mode_current

// extern __WEAK
static const uint32_t __g_zuno_user_code_status_mask = ((0x1 << USER_CODE_STATUS_AVAILABLE) | (0x1 << USER_CODE_STATUS_ENABLED_GRANT_ACCESS) | (0x1 << USER_CODE_STATUS_DISABLED));

static const uint32_t __g_zuno_user_code_keypad_mode = ((0x1 << USER_CODE_KEYPAD_MODE_NORMA) | (0x1 << USER_CODE_KEYPAD_MODE_VACATION));


static int _users_number_report(ZW_USERS_NUMBER_GET_FRAME *paket) {
	ZW_USERS_NUMBER_REPORT_FRAME_t			*report;
	size_t									count;

	report = (ZW_USERS_NUMBER_REPORT_FRAME_t *)&CMD_REPLY_CC;
	// // report->cmdClass = COMMAND_CLASS_USER_CODE; //set in - fillOutgoingPacket
	// // report->cmd = USERS_NUMBER_REPORT; //set in - fillOutgoingPacket
	if ((count = __g_zuno_user_code_param_count) > 0xFF)
		report->v2.supportedUsers = 0xFF;
	else
		report->v2.supportedUsers = count;
	_zme_memcpy(&report->v2.extendedSupportedUsers1, (uint8_t *)&count, sizeof(__g_zuno_user_code_param_count));
	CMD_REPLY_LEN = sizeof(report->v2);
	return (ZUNO_COMMAND_ANSWERED);
	(void)paket;
}

static int _user_code_capabilities_report(ZW_USER_CODE_CAPABILITIES_GET_V2_FRAME *paket) {
	ZW_USER_CODE_CAPABILITIES_REPORT_1BYTE_V2_FRAME						*report;
	uint8_t																*tmp;
	uint32_t															len;

	report = (ZW_USER_CODE_CAPABILITIES_REPORT_1BYTE_V2_FRAME *)&CMD_REPLY_CC;
	// // report->cmdClass = COMMAND_CLASS_USER_CODE; //set in - fillOutgoingPacket
	// // report->cmd = USER_CODE_CAPABILITIES_REPORT_V2; //set in - fillOutgoingPacket
	len = ((((sizeof(__g_zuno_user_code_status_mask) * 0x8) - __builtin_clz(__g_zuno_user_code_status_mask)) >> 0x3) + 0x1);
	report->properties1 = len | (USER_CODE_CAPABILITIES_REPORT_PROPERTIES1_MC_SUPPORT_BIT_MASK_V2 | USER_CODE_CAPABILITIES_REPORT_PROPERTIES1_MCD_SUPPORT_BIT_MASK_V2);
	tmp = &report->properties1 + 0x1;
	memcpy(tmp, (uint8_t *)&__g_zuno_user_code_status_mask, len);
	tmp = tmp + len;
	len = ((((sizeof(__g_zuno_user_code_keypad_mode) * 0x8) - __builtin_clz(__g_zuno_user_code_keypad_mode)) >> 0x3) + 0x1);
	tmp[0x0] = len | (USER_CODE_CAPABILITIES_REPORT_PROPERTIES2_MUCR_SUPPORT_BIT_MASK_V2 | USER_CODE_CAPABILITIES_REPORT_PROPERTIES2_MUCS_SUPPORT_BIT_MASK_V2 | USER_CODE_CAPABILITIES_REPORT_PROPERTIES2_UCC_SUPPORT_BIT_MASK_V2);//properties2
	tmp++;
	memcpy(tmp, (uint8_t *)&__g_zuno_user_code_keypad_mode, len);
	tmp = tmp + len;
	tmp[0x0] = sizeof(__g_zuno_user_code_asii_mask);//properties3
	tmp++;
	memcpy(tmp, &__g_zuno_user_code_asii_mask[0x0], sizeof(__g_zuno_user_code_asii_mask));
	CMD_REPLY_LEN = tmp - &CMD_REPLY_CC + sizeof(__g_zuno_user_code_asii_mask);
	return (ZUNO_COMMAND_ANSWERED);
	(void)paket;
}

static int _user_code_report(ZW_USER_CODE_GET_FRAME *paket) {
	size_t										userIdentifier;
	ZwUserCodeReportFrame_t						*report;
	ZwUserCodeParametr_t						*parametr;
	size_t										count;

	report = (ZwUserCodeReportFrame_t *)&CMD_REPLY_CC;
	// // report->cmdClass = COMMAND_CLASS_USER_CODE; //set in - fillOutgoingPacket
	// // report->cmd = USER_CODE_REPORT_V2; //set in - fillOutgoingPacket
	userIdentifier = paket->userIdentifier;
	report->userIdentifier = userIdentifier;
	if (userIdentifier == 0x0 || userIdentifier > __g_zuno_user_code_param_count) {
		report->userIdStatus = EXTENDED_USER_CODE_REPORT_STATUS_NOT_AVAILABLE_V2;
		memset(&report->userCode[0x0], 0x0, 0x4);
		CMD_REPLY_LEN = sizeof(ZwUserCodeReportFrame_t) + 0x4;
		return (ZUNO_COMMAND_ANSWERED);
	}
	parametr = &__g_zuno_user_code_param[userIdentifier - 0x1];
	report->userIdStatus = parametr->userIdStatus;
	count = parametr->userCodeLen;
	memcpy(&report->userCode[0x0], &parametr->userCode[0x0], count);
	CMD_REPLY_LEN = sizeof(ZwUserCodeReportFrame_t) + count;
	return (ZUNO_COMMAND_ANSWERED);
}

static int _extended_user_code_report(ZW_EXTENDED_USER_CODE_GET_V2_FRAME *paket) {
	size_t										userIdentifier;
	ZwExtendedUserCodeReportFrameStart_t		*start;
	ZwExtendedUserCodeReportFrameEnd_t			*end;
	ZwExtendedUserCodeReportFrameVg_t			*vg;
	ZwUserCodeParametr_t						*parametr;
	size_t										count;
	size_t										len;
	size_t										userIdStatus;

	start = (ZwExtendedUserCodeReportFrameStart_t *)&CMD_REPLY_CC;
	vg = (ZwExtendedUserCodeReportFrameVg_t *)(&CMD_REPLY_CC + sizeof(ZwExtendedUserCodeReportFrameStart_t));
	start->numberOfUserCodes = 0x1;
	// // start->cmdClass = COMMAND_CLASS_USER_CODE; //set in - fillOutgoingPacket
	// // start->cmd = EXTENDED_USER_CODE_REPORT_V2; //set in - fillOutgoingPacket
	userIdentifier = (paket->userIdentifier1 << 0x8) | paket->userIdentifier2;
	vg->userIdentifier1 = userIdentifier >> 0x8;
	vg->userIdentifier2 = userIdentifier;
	if (userIdentifier == 0x0 || userIdentifier > __g_zuno_user_code_param_count) {
		vg->userIdStatus = EXTENDED_USER_CODE_REPORT_STATUS_NOT_AVAILABLE_V2;
		vg->properties1 = 0x0;
		end = (ZwExtendedUserCodeReportFrameEnd_t *)((uint8_t *)vg + sizeof(ZwExtendedUserCodeReportFrameVg_t));
		end->nextUserIdentifier1 = 0x0;
		end->nextUserIdentifier2 = 0x0;
		CMD_REPLY_LEN = (sizeof(ZwExtendedUserCodeReportFrameStart_t) + sizeof(ZwExtendedUserCodeReportFrameEnd_t) + sizeof(ZwExtendedUserCodeReportFrameVg_t));
		return (ZUNO_COMMAND_ANSWERED);
	}
	parametr = &__g_zuno_user_code_param[userIdentifier - 0x1];
	if ((vg->userIdStatus = parametr->userIdStatus) != USER_CODE_STATUS_AVAILABLE) {
		count = parametr->userCodeLen;
		memcpy(&vg->userCode[0x0], &parametr->userCode[0x0], count);
	}
	else
		count = 0x0;
	vg->properties1 = count;
	len = (sizeof(ZwExtendedUserCodeReportFrameStart_t) + sizeof(ZwExtendedUserCodeReportFrameVg_t) + sizeof(ZwExtendedUserCodeReportFrameEnd_t)) + count;
	vg = (ZwExtendedUserCodeReportFrameVg_t *)((size_t)vg + sizeof(ZwExtendedUserCodeReportFrameVg_t) + count);
	userIdentifier++;
	if ((paket->properties1 & EXTENDED_USER_CODE_GET_PROPERTIES1_REPORT_MORE_BIT_MASK_V2) != 0x0) {
		while (userIdentifier <= __g_zuno_user_code_param_count) {
			parametr++;
			if ((userIdStatus = parametr->userIdStatus) == USER_CODE_STATUS_AVAILABLE) {
				userIdentifier++;
				continue ;
			}
			if (len + (sizeof(ZwExtendedUserCodeReportFrameVg_t)) >= ZUNO_COMMAND_PACKET_CMD_LEN_MAX_OUT)
				break ;
			len = len + (sizeof(ZwExtendedUserCodeReportFrameVg_t));
			vg->userIdentifier1 = userIdentifier >> 0x8;
			vg->userIdentifier2 = userIdentifier;
			vg->userIdStatus = userIdStatus;
			count = parametr->userCodeLen;
			if ((len + count) > ZUNO_COMMAND_PACKET_CMD_LEN_MAX_OUT) {
				len = len - (sizeof(ZwExtendedUserCodeReportFrameVg_t));
				break ;
			}
			memcpy(&vg->userCode[0x0], &parametr->userCode[0x0], count);
			vg->properties1 = count;
			vg = (ZwExtendedUserCodeReportFrameVg_t *)((size_t)vg + sizeof(ZwExtendedUserCodeReportFrameVg_t) + count);
			len = len + count;
			userIdentifier++;
			start->numberOfUserCodes++;
		}
	}
	if (userIdentifier > __g_zuno_user_code_param_count)
		userIdentifier = 0x0;
	end = (ZwExtendedUserCodeReportFrameEnd_t *)vg;
	end->nextUserIdentifier1 = userIdentifier >> 0x8;
	end->nextUserIdentifier2 = userIdentifier;
	CMD_REPLY_LEN = len;
	return (ZUNO_COMMAND_ANSWERED);
}

static void _user_code_set_all(void) {
	ZwUserCodeParametr_t						*b;
	ZwUserCodeParametr_t						*e;

	b = &__g_zuno_user_code_param[0x0];
	e = &__g_zuno_user_code_param[__g_zuno_user_code_param_count];
	while (b < e) {
		memset(&b->userCode[0x0], 0x0, 0x4);
		b->userCodeLen = 0x4;
		b->userIdStatus = USER_CODE_STATUS_AVAILABLE;
		b++;
	}
}

static size_t _user_code_set_one_test(uint8_t *b, size_t len) {
	uint8_t					*e;
	size_t					tempos;
	size_t					i;

	e = b + len;
	while (b < e) {
		tempos = b[0x0];
		if (tempos > (sizeof(__g_zuno_user_code_asii_mask) * 0x8 - 0x1))
			return (false);
		i = tempos / 0x8;
		if ((__g_zuno_user_code_asii_mask[i] & (0x1 << (tempos % 0x8))) == 0x0)
			return (false);
		b++;
	}
	return (true);
}

static size_t _user_code_set_one_duplicate(uint8_t *userCode, size_t len) {
	ZwUserCodeParametr_t						*b;
	ZwUserCodeParametr_t						*e;

	if (__g_zuno_user_code_param_master.masterCodeLen == len && memcmp(&__g_zuno_user_code_param_master.masterCode[0x0], userCode, len) == 0x0)
		return (false);
	b = &__g_zuno_user_code_param[0x0];
	e = &__g_zuno_user_code_param[__g_zuno_user_code_param_count];
	while (b < e) {
		if (b->userIdStatus != USER_CODE_STATUS_AVAILABLE && b->userCodeLen == len && memcmp(&b->userCode[0x0], userCode, len) == 0x0)
			return (false);
		b++;
	}
	return (true);
}

static int _user_code_set_one(size_t userIdentifier, size_t userIdStatus, uint8_t *b, size_t len) {
	ZwUserCodeParametr_t						*parametr;

	parametr = &__g_zuno_user_code_param[userIdentifier - 0x1];
	if (userIdStatus != USER_CODE_STATUS_AVAILABLE) {
		if (len < 0x4 || len > sizeof(parametr->userCode))
			return (ZUNO_COMMAND_BLOCKED_FAILL);
		if (_user_code_set_one_test(b, len) == false)
			return (ZUNO_COMMAND_BLOCKED_FAILL);
		if (_user_code_set_one_duplicate(b, len) == false)
			return (ZUNO_COMMAND_BLOCKED_FAILL);
		memcpy(&parametr->userCode[0x0], b, len);
	}
	else {
		memset(&parametr->userCode[0x0], 0x0, 0x4);
		len = 0x4;
	}
	parametr->userIdStatus = userIdStatus;
	parametr->userCodeLen = len;
	return (ZUNO_COMMAND_PROCESSED);
}


static int _user_code_set_universal(size_t userIdentifier, size_t userIdStatus, uint8_t *b, size_t UserCodeLength) {
	if (userIdentifier > __g_zuno_user_code_param_count)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	if (userIdStatus > (sizeof(__g_zuno_user_code_status_mask) * 0x8 - 0x1) || (__g_zuno_user_code_status_mask & (0x1 << userIdStatus)) == 0x0)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	if (userIdentifier == 0x0) {
		if (userIdStatus != USER_CODE_STATUS_AVAILABLE)
			return (ZUNO_COMMAND_BLOCKED_FAILL);
		_user_code_set_all();
		return (ZUNO_COMMAND_PROCESSED);
	}
	return (_user_code_set_one(userIdentifier, userIdStatus, b, UserCodeLength));
}

static int _user_code_set(ZwUserCodeSetFrame_t *paket, size_t len) {
	return (_user_code_set_universal(paket->userIdentifier, paket->userIdStatus, &paket->userCode[0x0], (len - sizeof(ZwUserCodeSetFrame_t))));
}

static int _user_code_keypad_mode_report(void) {
	ZW_USER_CODE_KEYPAD_MODE_REPORT_V2_FRAME			*report;

	report = (ZW_USER_CODE_KEYPAD_MODE_REPORT_V2_FRAME *)&CMD_REPLY_CC;
	// // report->cmdClass = COMMAND_CLASS_USER_CODE; //set in - fillOutgoingPacket
	// // report->cmd = USER_CODE_KEYPAD_MODE_REPORT_V2; //set in - fillOutgoingPacket
	report->keypadMode = ZUNO_USER_CODE_KEYPAD_MODE_GET();
	CMD_REPLY_LEN = sizeof(ZW_USER_CODE_KEYPAD_MODE_REPORT_V2_FRAME);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _user_code_keypad_mode_set(ZW_USER_CODE_KEYPAD_MODE_SET_V2_FRAME *paket) {
	size_t										keypadMode;

	keypadMode = paket->keypadMode;
	keypadMode = paket->keypadMode;
	if (keypadMode > (sizeof(__g_zuno_user_code_keypad_mode) * 0x8 - 0x1) || (__g_zuno_user_code_keypad_mode & (0x1 << keypadMode)) == 0x0)
		return (ZUNO_COMMAND_BLOCKED);
	ZUNO_USER_CODE_KEYPAD_MODE_SET(keypadMode);
	return (ZUNO_COMMAND_PROCESSED);
}

static int _extended_user_code_set(ZwExtendedUserCodeSetFrameStart_t *paket) {
	ZwExtendedUserCodeSetFrameVg_t						*vg;
	size_t												numberOfUserCodes;
	size_t												len;
	int													ret;

	vg = (ZwExtendedUserCodeSetFrameVg_t *)((uint8_t *)paket + sizeof(ZwExtendedUserCodeSetFrameStart_t));
	numberOfUserCodes = paket->numberOfUserCodes;
	ret = ZUNO_COMMAND_PROCESSED;
	while (numberOfUserCodes-- != 0x0) {
		len = vg->properties1 & MASTER_CODE_SET_PROPERTIES1_MASTER_CODE_LENGTH_MASK_V2;
		ret = _user_code_set_universal(((vg->userIdentifier1 << 0x8) | vg->userIdentifier2), vg->userIdStatus, &vg->userCode[0x0], len);
		vg = (ZwExtendedUserCodeSetFrameVg_t *)((uint8_t *)vg + sizeof(ZwExtendedUserCodeSetFrameVg_t) + len);
	}
	if (paket->numberOfUserCodes == 0x1)
		return (ret);
	return (ZUNO_COMMAND_PROCESSED);
}

static uint16_t _crc16_ccitt_aug(uint16_t crc16, uint8_t *data, size_t len) {
	uint8_t				i;

	while (len--) {
		crc16 = crc16 ^ data++[0] << 8;
		i = 0;
		while (i++ < 8)
			crc16 = ((crc16 & 0x8000) != 0) ? (crc16 << 1) ^ 0x1021 : crc16 << 1;
	}
	return (crc16);
} 

static int _user_code_checksum_report(void) {
	ZW_USER_CODE_CHECKSUM_REPORT_V2_FRAME		*report;
	ZwUserCodeParametr_t						*b;
	ZwUserCodeParametr_t						*e;
	uint16_t									userIdentifier;
	uint16_t									tempos;
	uint8_t										userIdStatus;
	size_t										i;
	uint16_t									crc16;

	report = (ZW_USER_CODE_CHECKSUM_REPORT_V2_FRAME *)&CMD_REPLY_CC;
	// report->cmdClass = COMMAND_CLASS_USER_CODE; //set in - fillOutgoingPacket
	// report->cmd = USER_CODE_CHECKSUM_REPORT_V2; //set in - fillOutgoingPacket
	b = &__g_zuno_user_code_param[0x0];
	e = &__g_zuno_user_code_param[__g_zuno_user_code_param_count];
	i = 0x0;
	userIdentifier = 0x1;
	crc16 = 0x1D0F;
	while (b < e) {
		if ((userIdStatus = b->userIdStatus) != USER_CODE_STATUS_AVAILABLE) {
			tempos = __builtin_bswap16(userIdentifier);
			crc16 = _crc16_ccitt_aug(crc16, (uint8_t *)&tempos, sizeof(tempos));
			crc16 = _crc16_ccitt_aug(crc16, &userIdStatus, sizeof(userIdStatus));
			crc16 = _crc16_ccitt_aug(crc16, &b->userCode[0x0], b->userCodeLen);
			i++;
		}
		userIdentifier++;
		b++;
	}
	if (i == 0x0)
		crc16 = 0x0;
	report->userCodeChecksum1 = crc16 >> 0x8;
	report->userCodeChecksum2 = crc16;
	CMD_REPLY_LEN = sizeof(ZW_USER_CODE_CHECKSUM_REPORT_V2_FRAME);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _user_code_master_report(void) {
	ZwMasterCodeReportFrame_t		*report;
	size_t							masterCodeLen;

	report = (ZwMasterCodeReportFrame_t *)&CMD_REPLY_CC;
	// report->cmdClass = COMMAND_CLASS_USER_CODE; //set in - fillOutgoingPacket
	// report->cmd = MASTER_CODE_REPORT_V2; //set in - fillOutgoingPacket
	masterCodeLen = __g_zuno_user_code_param_master.masterCodeLen;
	report->properties1 = masterCodeLen;
	memcpy(&report->masterCode[0x0], &__g_zuno_user_code_param_master.masterCode[0x0], masterCodeLen);
	CMD_REPLY_LEN = sizeof(ZwMasterCodeReportFrame_t) + masterCodeLen;
	return (ZUNO_COMMAND_ANSWERED);
}

static int _user_code_master_set(ZwMasterCodeSetFrame_t *paket) {
	size_t							masterCodeLen;

	masterCodeLen = paket->properties1 & MASTER_CODE_SET_PROPERTIES1_MASTER_CODE_LENGTH_MASK_V2;
	if (masterCodeLen != 0x0) {
		if (masterCodeLen < 0x4 || masterCodeLen > (sizeof(__g_zuno_user_code_param_master.masterCode)))
			return (ZUNO_COMMAND_BLOCKED_FAILL);
		if (_user_code_set_one_test(&paket->masterCode[0x0], masterCodeLen) == false)
			return (ZUNO_COMMAND_BLOCKED_FAILL);
		if (_user_code_set_one_duplicate(&paket->masterCode[0x0], masterCodeLen) == false)
			return (ZUNO_COMMAND_BLOCKED_FAILL);
	}
	__g_zuno_user_code_param_master.masterCodeLen = masterCodeLen;
	memcpy(&__g_zuno_user_code_param_master.masterCode[0x0], &paket->masterCode[0x0], masterCodeLen);
	return (ZUNO_COMMAND_PROCESSED);
}

int zuno_CCUserCodeHandler(ZUNOCommandPacket_t *cmd) {
	int								rs;

	switch (ZW_CMD) {
		case MASTER_CODE_SET_V2:
			rs = _user_code_master_set((ZwMasterCodeSetFrame_t *)&cmd->cmd[0x0]);
			break ;
		case MASTER_CODE_GET_V2:
			rs = _user_code_master_report();
			break ;
		case USER_CODE_CHECKSUM_GET_V2:
			rs = _user_code_checksum_report();
			break ;
		case USER_CODE_KEYPAD_MODE_SET_V2:
			rs = _user_code_keypad_mode_set((ZW_USER_CODE_KEYPAD_MODE_SET_V2_FRAME *)&cmd->cmd[0x0]);
			break ;
		case USER_CODE_KEYPAD_MODE_GET_V2:
			rs = _user_code_keypad_mode_report();
			break ;
		case EXTENDED_USER_CODE_GET_V2:
			rs = _extended_user_code_report((ZW_EXTENDED_USER_CODE_GET_V2_FRAME *)&cmd->cmd[0x0]);
			break ;
		case EXTENDED_USER_CODE_SET_V2:
			rs = _extended_user_code_set((ZwExtendedUserCodeSetFrameStart_t *)&cmd->cmd[0x0]);
			break ;
		case USER_CODE_GET_V2:
			rs = _user_code_report((ZW_USER_CODE_GET_FRAME *)&cmd->cmd[0x0]);
			break ;
		case USER_CODE_SET_V2:
			rs = _user_code_set((ZwUserCodeSetFrame_t *)&cmd->cmd[0x0], cmd->len);
			break ;
		case USER_CODE_CAPABILITIES_GET_V2:
			rs = _user_code_capabilities_report((ZW_USER_CODE_CAPABILITIES_GET_V2_FRAME *)&cmd->cmd[0x0]);
			break ;
		case USERS_NUMBER_GET_V2:
			rs = _users_number_report((ZW_USERS_NUMBER_GET_FRAME *)&cmd->cmd[0x0]);
			break ;
		default:
			rs = ZUNO_COMMAND_BLOCKED_NO_SUPPORT;
			break ;
	}
	return (rs);
}