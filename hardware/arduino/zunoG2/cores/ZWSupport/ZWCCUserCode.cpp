#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCUserCode.h"
#include <string.h>
#include "CrcClass.h"

#define EEPROM_USER_CODE_MASTER_ADDR		EEPROM_USER_CODE_ADDR
#define EEPROM_USER_CODE_MASTER_SIZE		(sizeof(ZwUserCodeMasterFlash_t))
#define EEPROM_USER_CODE_USER_ADDR			(EEPROM_USER_CODE_MASTER_ADDR + EEPROM_USER_CODE_MASTER_SIZE)

uint8_t __g_zuno_user_code_asii_mask[0x10];
__WEAK void __g_zuno_user_code_asii_function(void) {
	__g_zuno_user_code_asii_mask[0x6] = 0xFF;
	__g_zuno_user_code_asii_mask[0x7] = 0x3;
}

__WEAK const ZwUserCodeMaster_t *__g_zuno_user_code_master_get_function(void) {
	static const ZwUserCodeMaster_t							_master =
	{
		.masterCode = {0x0},
		.masterCodeLen = 0x0
	};

	return (&_master);
}
static uint16_t __g_zuno_user_code_param_master_crc16 = 0x0;

static const ZwUserCodeParametr_t __g_zuno_user_code_param_array[] = 
{
	{
		.userCode = {0x0, 0x0, 0x0, 0x0},
		{
			.userIdStatus = USER_CODE_STATUS_AVAILABLE,
			.userCodeLen = 0x4
		}
	}
};
__WEAK const ZwUserCodeParametr_t *__g_zuno_user_code_user_array_get_function(void) {
	return (&__g_zuno_user_code_param_array[0x0]);
}
__WEAK uint16_t __g_zuno_user_code_param_count = (sizeof(__g_zuno_user_code_param_array) / sizeof(__g_zuno_user_code_param_array[0x0]));
__WEAK uint16_t __g_zuno_user_code_param_crc16[(sizeof(__g_zuno_user_code_param_array) / sizeof(__g_zuno_user_code_param_array[0x0]))];

static uint8_t __g_zuno_user_code_keypad_mode_current = USER_CODE_KEYPAD_MODE_NORMA;

#define ZUNO_USER_CODE_KEYPAD_MODE_SET(mode)			__g_zuno_user_code_keypad_mode_current = mode
#define ZUNO_USER_CODE_KEYPAD_MODE_GET()				__g_zuno_user_code_keypad_mode_current

static const uint32_t __g_zuno_user_code_status_mask = ((0x1 << USER_CODE_STATUS_AVAILABLE) | (0x1 << USER_CODE_STATUS_ENABLED_GRANT_ACCESS) | (0x1 << USER_CODE_STATUS_DISABLED));

static const uint32_t __g_zuno_user_code_keypad_mode = ((0x1 << USER_CODE_KEYPAD_MODE_NORMA) | (0x1 << USER_CODE_KEYPAD_MODE_VACATION));

static uint8_t _master_get(void *masterCode) {
	const ZwUserCodeMaster_t			*master_parametr;
	ZwUserCodeMasterFlash_t				master;
	uint16_t							crc16;
	size_t								masterCodeLen;

	zunoEEPROMRead(EEPROM_USER_CODE_MASTER_ADDR, EEPROM_USER_CODE_MASTER_SIZE, (byte *)&master);
	master_parametr = __g_zuno_user_code_master_get_function();
	crc16 = CrcClass::crc16_ccitt_aug((void *)&master.crc, sizeof(master.crc));
	if (memcmp(&crc16, &master.cr16_flash[0x0], sizeof(crc16)) == 0x0) {
		crc16 = CrcClass::crc16_ccitt_aug(master_parametr, sizeof(master_parametr[0x0]));
		if (memcmp(&crc16, &master.crc.cr16_rom[0x0], sizeof(crc16)) == 0x0) {
			masterCodeLen = master.crc.code.masterCodeLen;
			memcpy(masterCode, &master.crc.code.masterCode[0x0], masterCodeLen);
			return (masterCodeLen);
		}
	}
	masterCodeLen = master_parametr->masterCodeLen;
	memcpy(masterCode, &master_parametr->masterCode[0x0], masterCodeLen);
	return (masterCodeLen);
}

static void _master_save(void *masterCode, size_t masterCodeLen) {
	const ZwUserCodeMaster_t			*master_parametr;
	ZwUserCodeMasterFlash_t				master;
	uint16_t							crc16;

	__g_zuno_user_code_param_master_crc16 = CrcClass::crc16_ccitt_aug(masterCode, masterCodeLen);
	master.crc.code.masterCodeLen = masterCodeLen;
	memcpy(&master.crc.code.masterCode[0x0], masterCode, masterCodeLen);
	master_parametr = __g_zuno_user_code_master_get_function();
	crc16 = CrcClass::crc16_ccitt_aug(master_parametr, sizeof(master_parametr[0x0]));
	memcpy(&master.crc.cr16_rom[0x0], &crc16, sizeof(master.crc.cr16_rom));
	crc16 = CrcClass::crc16_ccitt_aug((void *)&master.crc, sizeof(master.crc));
	memcpy(&master.cr16_flash[0x0], &crc16, sizeof(master.cr16_flash));
	zunoEEPROMWrite(EEPROM_USER_CODE_MASTER_ADDR, EEPROM_USER_CODE_MASTER_SIZE, (byte *)&master);
}

static void _user_code_get(ZwUserCodeParametr_t *out, size_t userIdentifier) {
	ZwUserCodeParametrFlash_t			user;
	uint16_t							crc16;
	const ZwUserCodeParametr_t			*user_array;

	user_array = __g_zuno_user_code_user_array_get_function();
	userIdentifier--;
	zunoEEPROMRead(EEPROM_USER_CODE_ADDR + (userIdentifier * sizeof(user)), sizeof(user), (byte *)&user);
	crc16 = CrcClass::crc16_ccitt_aug((void *)&user.crc, sizeof(user.crc));
	if (memcmp(&crc16, &user.cr16_flash[0x0], sizeof(crc16)) == 0x0) {
		crc16 = CrcClass::crc16_ccitt_aug(&user_array[userIdentifier], sizeof(user_array[0x0]));
		if (memcmp(&crc16, &user.crc.cr16_rom[0x0], sizeof(crc16)) == 0x0) {
			memcpy(out, &user.crc.code, sizeof(out[0x0]));
			return ;
		}
	}
	memcpy(out, &user_array[userIdentifier], sizeof(out[0x0]));
}

static void _user_code_save(ZwUserCodeParametrFlash_t *user, size_t userIdentifier, size_t userIdStatus) {
	uint16_t									crc16;
	const ZwUserCodeParametr_t					*user_array;

	user_array = __g_zuno_user_code_user_array_get_function();
	userIdentifier--;
	if (userIdStatus != USER_CODE_STATUS_AVAILABLE)
		crc16 = CrcClass::crc16_ccitt_aug(&user->crc.code.userCode[0x0], user->crc.code.userCodeLen);
	else
		crc16 = 0x0;
	__g_zuno_user_code_param_crc16[userIdentifier] = crc16;
	crc16 = CrcClass::crc16_ccitt_aug(&user_array[userIdentifier], sizeof(user_array[0x0]));
	memcpy(&user->crc.cr16_rom[0x0], &crc16, sizeof(user->crc.cr16_rom));
	crc16 = CrcClass::crc16_ccitt_aug((void *)&user->crc, sizeof(user->crc));
	memcpy(&user->cr16_flash[0x0], &crc16, sizeof(user->cr16_flash));
	zunoEEPROMWrite(EEPROM_USER_CODE_ADDR + (userIdentifier * sizeof(user[0x0])), sizeof(user[0x0]), (byte *)user);
}

void __g_zuno_user_code_init(void) {
	size_t								i;
	union
	{
		ZwUserCodeMaster_t				master;
		ZwUserCodeParametr_t			user;
	};
	size_t								userCodeLen;

	__g_zuno_user_code_asii_function();
	i = _master_get(&master.masterCode[0x0]);
	if (i > 0x4)
		__g_zuno_user_code_param_master_crc16 = CrcClass::crc16_ccitt_aug((void *)&master.masterCode[0x0], i);
	i = 0x1;
	while (i <= __g_zuno_user_code_param_count) {
		_user_code_get(&user, i);
		userCodeLen = user.userCodeLen;
		if (user.userIdStatus != USER_CODE_STATUS_AVAILABLE && userCodeLen > 0x4)
			__g_zuno_user_code_param_crc16[i - 0x1] = CrcClass::crc16_ccitt_aug((void *)&user.userCode[0x0], userCodeLen);
		i++;
	}
}

static int _users_number_report(ZW_USERS_NUMBER_GET_FRAME *paket, ZUNOCommandPacketReport_t *frame_report) {
	ZW_USERS_NUMBER_REPORT_FRAME_t			*report;
	size_t									count;

	report = (ZW_USERS_NUMBER_REPORT_FRAME_t *)frame_report->packet.cmd;
	// // report->cmdClass = COMMAND_CLASS_USER_CODE; //set in - fillOutgoingPacket
	// // report->cmd = USERS_NUMBER_REPORT; //set in - fillOutgoingPacket
	if ((count = __g_zuno_user_code_param_count) > 0xFF)
		report->v2.supportedUsers = 0xFF;
	else
		report->v2.supportedUsers = count;
	_zme_memcpy(&report->v2.extendedSupportedUsers1, (uint8_t *)&count, sizeof(__g_zuno_user_code_param_count));
	frame_report->packet.len = sizeof(report->v2);
	return (ZUNO_COMMAND_ANSWERED);
	(void)paket;
}

static int _user_code_capabilities_report(ZW_USER_CODE_CAPABILITIES_GET_V2_FRAME *paket, ZUNOCommandPacketReport_t *frame_report) {
	ZW_USER_CODE_CAPABILITIES_REPORT_1BYTE_V2_FRAME						*report;
	uint8_t																*tmp;
	uint32_t															len;

	report = (ZW_USER_CODE_CAPABILITIES_REPORT_1BYTE_V2_FRAME *)frame_report->packet.cmd;
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
	frame_report->packet.len = tmp - frame_report->packet.cmd + sizeof(__g_zuno_user_code_asii_mask);
	return (ZUNO_COMMAND_ANSWERED);
	(void)paket;
}

static int _user_code_report(ZW_USER_CODE_GET_FRAME *paket, ZUNOCommandPacketReport_t *frame_report) {
	size_t										userIdentifier;
	ZwUserCodeReportFrame_t						*report;
	ZwUserCodeParametr_t						parametr;
	size_t										count;

	report = (ZwUserCodeReportFrame_t *)frame_report->packet.cmd;
	// // report->cmdClass = COMMAND_CLASS_USER_CODE; //set in - fillOutgoingPacket
	// // report->cmd = USER_CODE_REPORT_V2; //set in - fillOutgoingPacket
	userIdentifier = paket->userIdentifier;
	report->userIdentifier = userIdentifier;
	if (userIdentifier == 0x0 || userIdentifier > __g_zuno_user_code_param_count) {
		report->userIdStatus = EXTENDED_USER_CODE_REPORT_STATUS_NOT_AVAILABLE_V2;
		memset(&report->userCode[0x0], 0x0, 0x4);
		frame_report->packet.len = sizeof(ZwUserCodeReportFrame_t) + 0x4;
		return (ZUNO_COMMAND_ANSWERED);
	}
	_user_code_get(&parametr, userIdentifier);
	report->userIdStatus = parametr.userIdStatus;
	count = parametr.userCodeLen;
	memcpy(&report->userCode[0x0], &parametr.userCode[0x0], count);
	frame_report->packet.len = sizeof(ZwUserCodeReportFrame_t) + count;
	return (ZUNO_COMMAND_ANSWERED);
}

static int _extended_user_code_report(ZW_EXTENDED_USER_CODE_GET_V2_FRAME *paket, ZUNOCommandPacketReport_t *frame_report) {
	size_t										userIdentifier;
	ZwExtendedUserCodeReportFrameStart_t		*start;
	ZwExtendedUserCodeReportFrameEnd_t			*end;
	ZwExtendedUserCodeReportFrameVg_t			*vg;
	ZwUserCodeParametr_t						parametr;
	size_t										count;
	size_t										len;
	size_t										userIdStatus;

	start = (ZwExtendedUserCodeReportFrameStart_t *)frame_report->packet.cmd;
	vg = (ZwExtendedUserCodeReportFrameVg_t *)(frame_report->packet.cmd + sizeof(ZwExtendedUserCodeReportFrameStart_t));
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
		frame_report->packet.len = (sizeof(ZwExtendedUserCodeReportFrameStart_t) + sizeof(ZwExtendedUserCodeReportFrameEnd_t) + sizeof(ZwExtendedUserCodeReportFrameVg_t));
		return (ZUNO_COMMAND_ANSWERED);
	}
	_user_code_get(&parametr, userIdentifier);
	if ((vg->userIdStatus = parametr.userIdStatus) != USER_CODE_STATUS_AVAILABLE) {
		count = parametr.userCodeLen;
		memcpy(&vg->userCode[0x0], &parametr.userCode[0x0], count);
	}
	else
		count = 0x0;
	vg->properties1 = count;
	len = (sizeof(ZwExtendedUserCodeReportFrameStart_t) + sizeof(ZwExtendedUserCodeReportFrameVg_t) + sizeof(ZwExtendedUserCodeReportFrameEnd_t)) + count;
	vg = (ZwExtendedUserCodeReportFrameVg_t *)((size_t)vg + sizeof(ZwExtendedUserCodeReportFrameVg_t) + count);
	userIdentifier++;
	if ((paket->properties1 & EXTENDED_USER_CODE_GET_PROPERTIES1_REPORT_MORE_BIT_MASK_V2) != 0x0) {
		while (userIdentifier <= __g_zuno_user_code_param_count) {
			_user_code_get(&parametr, userIdentifier);
			if ((userIdStatus = parametr.userIdStatus) == USER_CODE_STATUS_AVAILABLE) {
				userIdentifier++;
				continue ;
			}
			count = parametr.userCodeLen;
			if (len + (sizeof(ZwExtendedUserCodeReportFrameVg_t) + count) >= ZUNO_COMMAND_PACKET_CMD_LEN_MAX_OUT)
				break ;
			len = len + (sizeof(ZwExtendedUserCodeReportFrameVg_t)) + count;
			vg->userIdentifier1 = userIdentifier >> 0x8;
			vg->userIdentifier2 = userIdentifier;
			vg->userIdStatus = userIdStatus;
			memcpy(&vg->userCode[0x0], &parametr.userCode[0x0], count);
			vg->properties1 = count;
			vg = (ZwExtendedUserCodeReportFrameVg_t *)((size_t)vg + sizeof(ZwExtendedUserCodeReportFrameVg_t) + count);
			len = len + count;
			userIdentifier++;
			start->numberOfUserCodes++;
		}
	}
	while (userIdentifier <= __g_zuno_user_code_param_count) {
		_user_code_get(&parametr, userIdentifier);
		if (parametr.userIdStatus != USER_CODE_STATUS_AVAILABLE)
			break ;
		userIdentifier++;
	}
	if (userIdentifier > __g_zuno_user_code_param_count)
		userIdentifier = 0x0;
	end = (ZwExtendedUserCodeReportFrameEnd_t *)vg;
	end->nextUserIdentifier1 = userIdentifier >> 0x8;
	end->nextUserIdentifier2 = userIdentifier;
	frame_report->packet.len = len;
	return (ZUNO_COMMAND_ANSWERED);
}

static void _user_code_set_all(void) {
	ZwUserCodeParametrFlash_t					user;
	size_t										userIdentifier;

	memset(&user.crc.code.userCode[0x0], 0x0, 0x4);
	user.crc.code.userCodeLen = 0x4;
	user.crc.code.userIdStatus = USER_CODE_STATUS_AVAILABLE;
	userIdentifier = 0x1;
	while (userIdentifier <= __g_zuno_user_code_param_count) {
		_user_code_save(&user, userIdentifier, USER_CODE_STATUS_AVAILABLE);
		userIdentifier++;
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
	uint16_t									*b;
	uint16_t									*e;
	uint16_t									crc16;
	
	crc16 = CrcClass::crc16_ccitt_aug(userCode, len);
	if (crc16 == __g_zuno_user_code_param_master_crc16)
		return (false);
	b = &__g_zuno_user_code_param_crc16[0x0];
	e = &__g_zuno_user_code_param_crc16[__g_zuno_user_code_param_count];
	while (b < e) {
		if (b[0x0] == crc16)
			return (false);
		b++;
	}
	return (true);
}

static int _user_code_set_one(size_t userIdentifier, size_t userIdStatus, uint8_t *b, size_t len) {
	ZwUserCodeParametrFlash_t						user;

	if (userIdStatus != USER_CODE_STATUS_AVAILABLE) {
		if (len < 0x4 || len > sizeof(user.crc.code.userCode))
			return (ZUNO_COMMAND_BLOCKED_FAILL);
		if (_user_code_set_one_test(b, len) == false)
			return (ZUNO_COMMAND_BLOCKED_FAILL);
		if (_user_code_set_one_duplicate(b, len) == false)
			return (ZUNO_COMMAND_BLOCKED_FAILL);
		memcpy(&user.crc.code.userCode[0x0], b, len);
	}
	else {
		memset(&user.crc.code.userCode[0x0], 0x0, 0x4);
		len = 0x4;
	}
	user.crc.code.userIdStatus = userIdStatus;
	user.crc.code.userCodeLen = len;
	_user_code_save(&user, userIdentifier, userIdStatus);
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

static int _user_code_keypad_mode_report(ZUNOCommandPacketReport_t *frame_report) {
	ZW_USER_CODE_KEYPAD_MODE_REPORT_V2_FRAME			*report;

	report = (ZW_USER_CODE_KEYPAD_MODE_REPORT_V2_FRAME *)frame_report->packet.cmd;
	// // report->cmdClass = COMMAND_CLASS_USER_CODE; //set in - fillOutgoingPacket
	// // report->cmd = USER_CODE_KEYPAD_MODE_REPORT_V2; //set in - fillOutgoingPacket
	report->keypadMode = ZUNO_USER_CODE_KEYPAD_MODE_GET();
	frame_report->packet.len = sizeof(ZW_USER_CODE_KEYPAD_MODE_REPORT_V2_FRAME);
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

static int _user_code_checksum_report(ZUNOCommandPacketReport_t *frame_report) {
	ZW_USER_CODE_CHECKSUM_REPORT_V2_FRAME		*report;
	ZwUserCodeParametr_t						parametr;
	uint16_t									userIdentifier;
	uint16_t									tempos;
	uint8_t										userIdStatus;
	size_t										i;
	uint16_t									crc16;

	report = (ZW_USER_CODE_CHECKSUM_REPORT_V2_FRAME *)frame_report->packet.cmd;
	// report->cmdClass = COMMAND_CLASS_USER_CODE; //set in - fillOutgoingPacket
	// report->cmd = USER_CODE_CHECKSUM_REPORT_V2; //set in - fillOutgoingPacket
	i = 0x0;
	userIdentifier = 0x1;
	crc16 = 0x1D0F;
	while (userIdentifier <= __g_zuno_user_code_param_count) {
		_user_code_get(&parametr, userIdentifier);
		if ((userIdStatus = parametr.userIdStatus) != USER_CODE_STATUS_AVAILABLE) {
			tempos = __builtin_bswap16(userIdentifier);
			crc16 = CrcClass::crc16_ccitt_aug(crc16, (uint8_t *)&tempos, sizeof(tempos));
			crc16 = CrcClass::crc16_ccitt_aug(crc16, &userIdStatus, sizeof(userIdStatus));
			crc16 = CrcClass::crc16_ccitt_aug(crc16, &parametr.userCode[0x0], parametr.userCodeLen);
			i++;
		}
		userIdentifier++;
	}
	if (i == 0x0)
		crc16 = 0x0;
	report->userCodeChecksum1 = crc16 >> 0x8;
	report->userCodeChecksum2 = crc16;
	frame_report->packet.len = sizeof(ZW_USER_CODE_CHECKSUM_REPORT_V2_FRAME);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _user_code_master_report(ZUNOCommandPacketReport_t *frame_report) {
	ZwMasterCodeReportFrame_t		*report;
	size_t							masterCodeLen;

	report = (ZwMasterCodeReportFrame_t *)frame_report->packet.cmd;
	// report->cmdClass = COMMAND_CLASS_USER_CODE; //set in - fillOutgoingPacket
	// report->cmd = MASTER_CODE_REPORT_V2; //set in - fillOutgoingPacket
	masterCodeLen = _master_get(&report->masterCode[0x0]);
	report->properties1 = masterCodeLen;
	frame_report->packet.len = sizeof(ZwMasterCodeReportFrame_t) + masterCodeLen;
	return (ZUNO_COMMAND_ANSWERED);
}

static int _user_code_master_set(ZwMasterCodeSetFrame_t *paket) {
	size_t							masterCodeLen;
	const ZwUserCodeMaster_t		*master_parametr;

	masterCodeLen = paket->properties1 & MASTER_CODE_SET_PROPERTIES1_MASTER_CODE_LENGTH_MASK_V2;
	if (masterCodeLen != 0x0) {
		if (masterCodeLen < 0x4 || masterCodeLen > (sizeof(master_parametr->masterCode)))
			return (ZUNO_COMMAND_BLOCKED_FAILL);
		if (_user_code_set_one_test(&paket->masterCode[0x0], masterCodeLen) == false)
			return (ZUNO_COMMAND_BLOCKED_FAILL);
		if (_user_code_set_one_duplicate(&paket->masterCode[0x0], masterCodeLen) == false)
			return (ZUNO_COMMAND_BLOCKED_FAILL);
	}
	_master_save(&paket->masterCode[0x0], masterCodeLen);
	return (ZUNO_COMMAND_PROCESSED);
}

int zuno_CCUserCodeHandler(ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	int								rs;

	switch (ZW_CMD) {
		case MASTER_CODE_SET_V2:
			rs = _user_code_master_set((ZwMasterCodeSetFrame_t *)&cmd->cmd[0x0]);
			break ;
		case MASTER_CODE_GET_V2:
			rs = _user_code_master_report(frame_report);
			break ;
		case USER_CODE_CHECKSUM_GET_V2:
			rs = _user_code_checksum_report(frame_report);
			break ;
		case USER_CODE_KEYPAD_MODE_SET_V2:
			rs = _user_code_keypad_mode_set((ZW_USER_CODE_KEYPAD_MODE_SET_V2_FRAME *)&cmd->cmd[0x0]);
			break ;
		case USER_CODE_KEYPAD_MODE_GET_V2:
			rs = _user_code_keypad_mode_report(frame_report);
			break ;
		case EXTENDED_USER_CODE_GET_V2:
			rs = _extended_user_code_report((ZW_EXTENDED_USER_CODE_GET_V2_FRAME *)&cmd->cmd[0x0], frame_report);
			break ;
		case EXTENDED_USER_CODE_SET_V2:
			rs = _extended_user_code_set((ZwExtendedUserCodeSetFrameStart_t *)&cmd->cmd[0x0]);
			break ;
		case USER_CODE_GET_V2:
			rs = _user_code_report((ZW_USER_CODE_GET_FRAME *)&cmd->cmd[0x0], frame_report);
			break ;
		case USER_CODE_SET_V2:
			rs = _user_code_set((ZwUserCodeSetFrame_t *)&cmd->cmd[0x0], cmd->len);
			break ;
		case USER_CODE_CAPABILITIES_GET_V2:
			rs = _user_code_capabilities_report((ZW_USER_CODE_CAPABILITIES_GET_V2_FRAME *)&cmd->cmd[0x0], frame_report);
			break ;
		case USERS_NUMBER_GET_V2:
			rs = _users_number_report((ZW_USERS_NUMBER_GET_FRAME *)&cmd->cmd[0x0], frame_report);
			break ;
		default:
			rs = ZUNO_COMMAND_BLOCKED_NO_SUPPORT;
			break ;
	}
	return (rs);
}

uint8_t zuno_CCUserCodeAccess(uint8_t *code, uint8_t len) {
	uint16_t										*b;
	uint16_t										*e;
	uint16_t										crc16;
	const ZwUserCodeParametr_t						*user_array;

	if (len < 0x4 || len > sizeof(user_array->userCode))
		return (false);
	if (_user_code_set_one_test(code, len) == false)
		return (false);
	crc16 = CrcClass::crc16_ccitt_aug(code, len);
	b = &__g_zuno_user_code_param_crc16[0x0];
	e = &__g_zuno_user_code_param_crc16[__g_zuno_user_code_param_count];
	while (b < e) {
		if (b[0x0] == crc16)
			return (true);
		b++;
	}
	return (false);
}

uint16_t zuno_CCUserCodeCount(void) {
	const ZwUserCodeParametr_t						*b;
	const ZwUserCodeParametr_t						*e;
	uint16_t										count;

	b = __g_zuno_user_code_user_array_get_function();
	e = &b[__g_zuno_user_code_param_count];
	count = 0x0;
	while (b < e) {
		if (b->userIdStatus != USER_CODE_STATUS_AVAILABLE)
			count++;
		b++;
	}
	return (count);
}