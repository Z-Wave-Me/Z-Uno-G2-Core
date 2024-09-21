#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCUserCode.h"
#include <string.h>
#include "CrcClass.h"

#if !defined(WITH_CC_USER_CREDENTIAL) && defined(WITH_CC_USER_CODE)

static_assert(USER_CODE_NUMBER > 0x0, "USER_CODE_NUMBER must != 0x0!!!");

#define EEPROM_USER_CODE_KEYPAD_MODE_ADDR		(EEPROM_USER_CODE_ADDR)
#define EEPROM_USER_CODE_MASTER_ADDR			(EEPROM_USER_CODE_KEYPAD_MODE_ADDR + sizeof(UserCodeSaveKeypadMode_t))
#define EEPROM_USER_CODE_MASTER_LOCAL_ADDR		(EEPROM_USER_CODE_MASTER_ADDR + sizeof(UserCodeSaveMaster_t))
#define EEPROM_USER_CODE_USER_ADDR				(EEPROM_USER_CODE_MASTER_LOCAL_ADDR + (sizeof(UserCodeSaveMaster_t)))

#define USER_CODE_ASII_MASK_SIZE						0x10

__WEAK const uint8_t *__g_zuno_user_code_asii_function(void) {
	static uint8_t _user_code_asii_mask[0x10];
	_user_code_asii_mask[0x6] = 0xFF;
	_user_code_asii_mask[0x7] = 0x3;
	return (&_user_code_asii_mask[0x0]);
}

static const UserCodeSaveUserId_t _user_code_default = 
{
	.userCode = {0x0, 0x0, 0x0, 0x0},
	{
		.userIdStatus = USER_CODE_STATUS_AVAILABLE,
		.userCodeLen = 0x4
	}
};

static const uint32_t _user_code_status_mask = ((0x1 << USER_CODE_STATUS_AVAILABLE) | (0x1 << USER_CODE_STATUS_ENABLED_GRANT_ACCESS) | (0x1 << USER_CODE_STATUS_DISABLED));

static const uint32_t _user_code_keypad_mode_mask = ((0x1 << USER_CODE_KEYPAD_MODE_NORMA) | (0x1 << USER_CODE_KEYPAD_MODE_VACATION));

static uint8_t _keypad_mode_get(void) {
	UserCodeSaveKeypadMode_t			keypad_mode;
	uint16_t							crc16;

	zunoEEPROMRead(EEPROM_USER_CODE_KEYPAD_MODE_ADDR, sizeof(keypad_mode), (byte *)&keypad_mode);
	crc16 = CrcClass::crc16_ccitt_aug((void *)&keypad_mode.mode, sizeof(keypad_mode.mode));
	if (memcmp(&crc16, &keypad_mode.crc16[0x0], sizeof(crc16)) != 0x0)
		return (USER_CODE_KEYPAD_MODE_NORMA);
	return (keypad_mode.mode);
}

static void _keypad_mode_set(uint8_t mode) {
	UserCodeSaveKeypadMode_t			keypad_mode;
	uint16_t							crc16;

	keypad_mode.mode = mode;
	crc16 = CrcClass::crc16_ccitt_aug((void *)&keypad_mode.mode, sizeof(keypad_mode.mode));
	memcpy(&crc16, &keypad_mode.crc16[0x0], sizeof(crc16));
	zunoEEPROMWrite(EEPROM_USER_CODE_KEYPAD_MODE_ADDR, sizeof(keypad_mode), (byte *)&keypad_mode);
}

static uint8_t _master_get(void *masterCode) {
	UserCodeSaveMaster_t				master;
	uint16_t							crc16;
	uint8_t								masterCodeLen;

	zunoEEPROMRead(EEPROM_USER_CODE_MASTER_ADDR, sizeof(UserCodeSaveMaster_t), (byte *)&master);
	crc16 = CrcClass::crc16_ccitt_aug((void *)&master.info, sizeof(master.info));
	if (memcmp(&crc16, &master.crc16[0x0], sizeof(crc16)) != 0x0)
		return (0x0);
	masterCodeLen = master.info.masterCodeLen;
	memcpy(masterCode, &master.info.masterCode[0x0], masterCodeLen);
	return (masterCodeLen);
}

static void _master_save(void *masterCode, size_t masterCodeLen) {
	UserCodeSaveMaster_t				master;
	uint16_t							crc16;

	master.info.masterCodeLen = masterCodeLen;
	memcpy(&master.info.masterCode[0x0], masterCode, masterCodeLen);
	crc16 = CrcClass::crc16_ccitt_aug((void *)&master.info, sizeof(master.info));
	memcpy(&master.crc16[0x0], &crc16, sizeof(master.crc16));
	zunoEEPROMWrite(EEPROM_USER_CODE_MASTER_ADDR, sizeof(UserCodeSaveMaster_t), (byte *)&master);
}

static void _get_user_code(UserCodeSaveUserId_t *user_code, uint16_t userIdentifier) {
	UserCodeSaveMask_t											mask;
	const UserCodeSaveUserId_t									*user_id;
	uint32_t													addr;
	size_t														offset;
	uint16_t													crc16;

	userIdentifier--;
	offset = userIdentifier / (USER_CODE_NUMBER_MASK_LENGHT);
	addr = (EEPROM_USER_CODE_USER_ADDR) + (offset * (sizeof(UserCodeSaveMask_t) * 0x2)) + (offset * ((USER_CODE_NUMBER_MASK_LENGHT) * sizeof(UserCodeSaveUserId_t)));
	zunoEEPROMRead(addr, sizeof(mask), (byte *)&mask);
	crc16 = CrcClass::crc16_ccitt_aug(&mask.crc16_mask[0x0], sizeof(mask.crc16_mask));
	if (memcmp(&crc16, &mask.crc16[0x0], sizeof(crc16)) != 0x0) {
		user_code[0x0] = _user_code_default;
		return ;
	}
	if (mask.crc16_mask[(0x2 * (userIdentifier % (USER_CODE_NUMBER_MASK_LENGHT))) + 0x0] == 0x0 && mask.crc16_mask[(0x2 * (userIdentifier % (USER_CODE_NUMBER_MASK_LENGHT))) + 0x1] == 0x0) {
		user_code[0x0] = _user_code_default;
		return ;
	}
	user_id = (const UserCodeSaveUserId_t *)(addr + (sizeof(UserCodeSaveMask_t) * 0x2));
	addr = (uint32_t)&user_id[userIdentifier % (USER_CODE_NUMBER_MASK_LENGHT)];
	zunoEEPROMRead(addr, sizeof(user_code[0x0]), (byte *)user_code);
}

static void _set_user_code(UserCodeSaveUserId_t *user_code, uint16_t userIdentifier) {
	UserCodeSaveMask_t											mask;
	const UserCodeSaveUserId_t									*user_id;
	uint32_t													addr_user_id;
	uint32_t													addr_mask;
	size_t														offset;
	uint16_t													crc16;

	userIdentifier--;
	offset = userIdentifier / (USER_CODE_NUMBER_MASK_LENGHT);
	addr_mask = (EEPROM_USER_CODE_USER_ADDR) + (offset * (sizeof(UserCodeSaveMask_t) * 0x2)) + (offset * ((USER_CODE_NUMBER_MASK_LENGHT) * sizeof(UserCodeSaveUserId_t)));
	zunoEEPROMRead(addr_mask, sizeof(mask), (byte *)&mask);
	crc16 = CrcClass::crc16_ccitt_aug(&mask.crc16_mask[0x0], sizeof(mask.crc16_mask));
	if (memcmp(&crc16, &mask.crc16[0x0], sizeof(crc16)) != 0x0) {
		memset(&mask.crc16_mask[0x0], 0x0, sizeof(mask.crc16_mask));
	}
	mask.crc16_mask[(0x2 * (userIdentifier % (USER_CODE_NUMBER_MASK_LENGHT))) + 0x0] = 0x0;
	mask.crc16_mask[(0x2 * (userIdentifier % (USER_CODE_NUMBER_MASK_LENGHT))) + 0x1] = 0x0;
	crc16 = CrcClass::crc16_ccitt_aug(&mask.crc16_mask[0x0], sizeof(mask.crc16_mask));
	memcpy(&mask.crc16[0x0], &crc16, sizeof(crc16));
	zunoEEPROMWrite(addr_mask, sizeof(mask), (byte *)&mask);
	if (user_code->userIdStatus == USER_CODE_STATUS_AVAILABLE)
		return ;
	user_id = (const UserCodeSaveUserId_t *)(addr_mask + (sizeof(UserCodeSaveMask_t) * 0x2));
	addr_user_id = (uint32_t)&user_id[userIdentifier % (USER_CODE_NUMBER_MASK_LENGHT)];
	zunoEEPROMWrite(addr_user_id, sizeof(user_code[0x0]), (byte *)user_code);
	crc16 = CrcClass::crc16_ccitt_aug(&user_code->userCode[0x0], user_code->userCodeLen);
	mask.crc16_mask[(0x2 * (userIdentifier % (USER_CODE_NUMBER_MASK_LENGHT))) + 0x0] = crc16;
	mask.crc16_mask[(0x2 * (userIdentifier % (USER_CODE_NUMBER_MASK_LENGHT))) + 0x1] = crc16 >> 0x8;
	crc16 = CrcClass::crc16_ccitt_aug(&mask.crc16_mask[0x0], sizeof(mask.crc16_mask));
	memcpy(&mask.crc16[0x0], &crc16, sizeof(crc16));
	zunoEEPROMWrite(addr_mask, sizeof(mask), (byte *)&mask);
}

static void _user_code_all_free(void) {
	size_t										userIdentifier;
	uint32_t									addr_mask;
	size_t										offset;
	uint16_t									crc16;
	UserCodeSaveMask_t							mask;

	memset(&mask.crc16_mask[0x0], 0x0, sizeof(mask.crc16_mask));
	crc16 = CrcClass::crc16_ccitt_aug(&mask.crc16_mask[0x0], sizeof(mask.crc16_mask));
	memcpy(&mask.crc16[0x0], &crc16, sizeof(crc16));
	userIdentifier = 0x1;
	while (userIdentifier <= USER_CODE_NUMBER) {
		offset = (userIdentifier - 0x1) / (USER_CODE_NUMBER_MASK_LENGHT);
		addr_mask = (EEPROM_USER_CODE_USER_ADDR) + (offset * (sizeof(UserCodeSaveMask_t) * 0x2)) + (offset * ((USER_CODE_NUMBER_MASK_LENGHT) * sizeof(UserCodeSaveUserId_t)));
		zunoEEPROMWrite(addr_mask, sizeof(mask), (byte *)&mask);
		userIdentifier = userIdentifier + USER_CODE_NUMBER_MASK_LENGHT;
	}
}

static int _users_number_report(ZW_USERS_NUMBER_GET_FRAME *paket, ZUNOCommandPacketReport_t *frame_report) {
	ZW_USERS_NUMBER_REPORT_FRAME_t			*report;
	size_t									count;

	report = (ZW_USERS_NUMBER_REPORT_FRAME_t *)frame_report->info.packet.cmd;
	// // report->cmdClass = COMMAND_CLASS_USER_CODE; //set in - fillOutgoingPacket
	// // report->cmd = USERS_NUMBER_REPORT; //set in - fillOutgoingPacket
	if ((count = USER_CODE_NUMBER) > 0xFF)
		report->v2.supportedUsers = 0xFF;
	else
		report->v2.supportedUsers = count;
	_zme_memcpy(&report->v2.extendedSupportedUsers1, (uint8_t *)&count, 0x2);
	frame_report->info.packet.len = sizeof(report->v2);
	return (ZUNO_COMMAND_ANSWERED);
	(void)paket;
}

static int _user_code_capabilities_report(ZW_USER_CODE_CAPABILITIES_GET_V2_FRAME *paket, ZUNOCommandPacketReport_t *frame_report) {
	ZW_USER_CODE_CAPABILITIES_REPORT_1BYTE_V2_FRAME						*report;
	uint8_t																*tmp;
	uint32_t															len;

	report = (ZW_USER_CODE_CAPABILITIES_REPORT_1BYTE_V2_FRAME *)frame_report->info.packet.cmd;
	// // report->cmdClass = COMMAND_CLASS_USER_CODE; //set in - fillOutgoingPacket
	// // report->cmd = USER_CODE_CAPABILITIES_REPORT_V2; //set in - fillOutgoingPacket
	len = ((((sizeof(_user_code_status_mask) * 0x8) - __builtin_clz(_user_code_status_mask)) >> 0x3) + 0x1);
	report->properties1 = len | (USER_CODE_CAPABILITIES_REPORT_PROPERTIES1_MC_SUPPORT_BIT_MASK_V2 | USER_CODE_CAPABILITIES_REPORT_PROPERTIES1_MCD_SUPPORT_BIT_MASK_V2);
	tmp = &report->properties1 + 0x1;
	memcpy(tmp, (uint8_t *)&_user_code_status_mask, len);
	tmp = tmp + len;
	len = ((((sizeof(_user_code_keypad_mode_mask) * 0x8) - __builtin_clz(_user_code_keypad_mode_mask)) >> 0x3) + 0x1);
	tmp[0x0] = len | (USER_CODE_CAPABILITIES_REPORT_PROPERTIES2_MUCR_SUPPORT_BIT_MASK_V2 | USER_CODE_CAPABILITIES_REPORT_PROPERTIES2_MUCS_SUPPORT_BIT_MASK_V2 | USER_CODE_CAPABILITIES_REPORT_PROPERTIES2_UCC_SUPPORT_BIT_MASK_V2);//properties2
	tmp++;
	memcpy(tmp, (uint8_t *)&_user_code_keypad_mode_mask, len);
	tmp = tmp + len;
	tmp[0x0] = USER_CODE_ASII_MASK_SIZE;//properties3
	tmp++;
	memcpy(tmp, __g_zuno_user_code_asii_function(), USER_CODE_ASII_MASK_SIZE);
	frame_report->info.packet.len = tmp - frame_report->info.packet.cmd + USER_CODE_ASII_MASK_SIZE;
	return (ZUNO_COMMAND_ANSWERED);
	(void)paket;
}

static int _user_code_report(ZW_USER_CODE_GET_FRAME *paket, ZUNOCommandPacketReport_t *frame_report) {
	size_t										userIdentifier;
	ZwUserCodeReportFrame_t						*report;
	UserCodeSaveUserId_t						parametr;
	size_t										count;

	report = (ZwUserCodeReportFrame_t *)frame_report->info.packet.cmd;
	// // report->cmdClass = COMMAND_CLASS_USER_CODE; //set in - fillOutgoingPacket
	// // report->cmd = USER_CODE_REPORT_V2; //set in - fillOutgoingPacket
	userIdentifier = paket->userIdentifier;
	report->userIdentifier = userIdentifier;
	if (userIdentifier == 0x0 || userIdentifier > USER_CODE_NUMBER) {
		report->userIdStatus = EXTENDED_USER_CODE_REPORT_STATUS_NOT_AVAILABLE_V2;
		memset(&report->userCode[0x0], 0x0, 0x4);
		frame_report->info.packet.len = sizeof(ZwUserCodeReportFrame_t) + 0x4;
		return (ZUNO_COMMAND_ANSWERED);
	}
	_get_user_code(&parametr, userIdentifier);
	report->userIdStatus = parametr.userIdStatus;
	count = parametr.userCodeLen;
	memcpy(&report->userCode[0x0], &parametr.userCode[0x0], count);
	frame_report->info.packet.len = sizeof(ZwUserCodeReportFrame_t) + count;
	return (ZUNO_COMMAND_ANSWERED);
}

static int _extended_user_code_report(ZW_EXTENDED_USER_CODE_GET_V2_FRAME *paket, ZUNOCommandPacketReport_t *frame_report) {
	size_t										userIdentifier;
	ZwExtendedUserCodeReportFrameStart_t		*start;
	ZwExtendedUserCodeReportFrameEnd_t			*end;
	ZwExtendedUserCodeReportFrameVg_t			*vg;
	UserCodeSaveUserId_t						parametr;
	size_t										count;
	size_t										len;
	size_t										userIdStatus;

	start = (ZwExtendedUserCodeReportFrameStart_t *)frame_report->info.packet.cmd;
	vg = (ZwExtendedUserCodeReportFrameVg_t *)(frame_report->info.packet.cmd + sizeof(ZwExtendedUserCodeReportFrameStart_t));
	start->numberOfUserCodes = 0x1;
	// // start->cmdClass = COMMAND_CLASS_USER_CODE; //set in - fillOutgoingPacket
	// // start->cmd = EXTENDED_USER_CODE_REPORT_V2; //set in - fillOutgoingPacket
	userIdentifier = (paket->userIdentifier1 << 0x8) | paket->userIdentifier2;
	vg->userIdentifier1 = userIdentifier >> 0x8;
	vg->userIdentifier2 = userIdentifier;
	if (userIdentifier == 0x0 || userIdentifier > USER_CODE_NUMBER) {
		vg->userIdStatus = EXTENDED_USER_CODE_REPORT_STATUS_NOT_AVAILABLE_V2;
		vg->properties1 = 0x0;
		end = (ZwExtendedUserCodeReportFrameEnd_t *)((uint8_t *)vg + sizeof(ZwExtendedUserCodeReportFrameVg_t));
		end->nextUserIdentifier1 = 0x0;
		end->nextUserIdentifier2 = 0x0;
		frame_report->info.packet.len = (sizeof(ZwExtendedUserCodeReportFrameStart_t) + sizeof(ZwExtendedUserCodeReportFrameEnd_t) + sizeof(ZwExtendedUserCodeReportFrameVg_t));
		return (ZUNO_COMMAND_ANSWERED);
	}
	_get_user_code(&parametr, userIdentifier);
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
		while (userIdentifier <= USER_CODE_NUMBER) {
			_get_user_code(&parametr, userIdentifier);
			if ((userIdStatus = parametr.userIdStatus) == USER_CODE_STATUS_AVAILABLE) {
				userIdentifier++;
				continue ;
			}
			count = parametr.userCodeLen;
			if (len + (sizeof(ZwExtendedUserCodeReportFrameVg_t) + count) >= ZUNO_COMMAND_PACKET_CMD_OUT_MAX_RECOMMENDED)
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
	while (userIdentifier <= USER_CODE_NUMBER) {
		_get_user_code(&parametr, userIdentifier);
		if (parametr.userIdStatus != USER_CODE_STATUS_AVAILABLE)
			break ;
		userIdentifier++;
	}
	if (userIdentifier > USER_CODE_NUMBER)
		userIdentifier = 0x0;
	end = (ZwExtendedUserCodeReportFrameEnd_t *)vg;
	end->nextUserIdentifier1 = userIdentifier >> 0x8;
	end->nextUserIdentifier2 = userIdentifier;
	frame_report->info.packet.len = len;
	return (ZUNO_COMMAND_ANSWERED);
}

static size_t _user_code_set_one_test(uint8_t *b, size_t len) {
	uint8_t					*e;
	size_t					tempos;
	size_t					i;
	const uint8_t			*user_code_asii_mask;

	user_code_asii_mask = __g_zuno_user_code_asii_function();
	e = b + len;
	while (b < e) {
		tempos = b[0x0];
		if (tempos > (USER_CODE_ASII_MASK_SIZE * 0x8 - 0x1))
			return (false);
		i = tempos / 0x8;
		if ((user_code_asii_mask[i] & (0x1 << (tempos % 0x8))) == 0x0)
			return (false);
		b++;
	}
	return (true);
}

static bool _user_code_set_one_duplicate_crc(uint16_t userIdentifier, uint16_t crc16_userIdentifier) {
	UserCodeSaveMask_t											mask;
	uint32_t													addr;
	size_t														offset;
	uint16_t													crc16;
	size_t														i;

	userIdentifier--;
	offset = userIdentifier / (USER_CODE_NUMBER_MASK_LENGHT);
	addr = (EEPROM_USER_CODE_USER_ADDR) + (offset * (sizeof(UserCodeSaveMask_t) * 0x2)) + (offset * ((USER_CODE_NUMBER_MASK_LENGHT) * sizeof(UserCodeSaveUserId_t)));
	zunoEEPROMRead(addr, sizeof(mask), (byte *)&mask);
	crc16 = CrcClass::crc16_ccitt_aug(&mask.crc16_mask[0x0], sizeof(mask.crc16_mask));
	if (memcmp(&crc16, &mask.crc16[0x0], sizeof(crc16)) != 0x0) {
		return (false);
	}
	i = 0x0;
	while (i < sizeof(mask.crc16_mask)) {
		if (crc16_userIdentifier == ((mask.crc16_mask[i + 0x1] << 0x8) | mask.crc16_mask[i + 0x0]))
			return (true);
		i = i + 0x2;
	}
	return (false);
}


static size_t _user_code_set_one_duplicate(uint8_t *userCode, size_t len) {
	uint16_t									crc16;
	uint8_t										userCodeLen;
	UserCodeSaveMaster_t						master;
	uint16_t									userIdentifier;
	
	userCodeLen = _master_get(&master.info.masterCode[0x0]);
	crc16 = CrcClass::crc16_ccitt_aug(userCode, len);
	if (userCodeLen != 0x0) {
		if (crc16 == CrcClass::crc16_ccitt_aug((void *)&master.info.masterCode[0x0], userCodeLen))
			return (false);
	}
	userIdentifier = 0x1;
	while (userIdentifier <= USER_CODE_NUMBER) {
		if (_user_code_set_one_duplicate_crc(userIdentifier, crc16) == true)
			return (false);
		userIdentifier = userIdentifier + USER_CODE_NUMBER_MASK_LENGHT;
	}
	return (true);
}

static int _user_code_set_one(size_t userIdentifier, size_t userIdStatus, uint8_t *b, size_t len) {
	UserCodeSaveUserId_t						user_code;

	if (userIdStatus != USER_CODE_STATUS_AVAILABLE) {
		if (len < 0x4 || len > sizeof(user_code.userCode))
			return (ZUNO_COMMAND_BLOCKED_FAILL);
		if (_user_code_set_one_test(b, len) == false)
			return (ZUNO_COMMAND_BLOCKED_FAILL);
		if (_user_code_set_one_duplicate(b, len) == false)
			return (ZUNO_COMMAND_BLOCKED_FAILL);
		memcpy(&user_code.userCode[0x0], b, len);
	}
	else {
		memset(&user_code.userCode[0x0], 0x0, 0x4);
		len = 0x4;
	}
	user_code.userIdStatus = userIdStatus;
	user_code.userCodeLen = len;
	_set_user_code(&user_code, userIdentifier);
	return (ZUNO_COMMAND_PROCESSED);
}


static int _user_code_set_universal(size_t userIdentifier, size_t userIdStatus, uint8_t *b, size_t UserCodeLength) {
	if (userIdentifier > USER_CODE_NUMBER)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	if (userIdStatus > (sizeof(_user_code_status_mask) * 0x8 - 0x1) || (_user_code_status_mask & (0x1 << userIdStatus)) == 0x0)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	if (userIdentifier == 0x0) {
		if (userIdStatus != USER_CODE_STATUS_AVAILABLE)
			return (ZUNO_COMMAND_BLOCKED_FAILL);
		_user_code_all_free();
		return (ZUNO_COMMAND_PROCESSED);
	}
	return (_user_code_set_one(userIdentifier, userIdStatus, b, UserCodeLength));
}

static int _user_code_set(ZwUserCodeSetFrame_t *paket, size_t len) {
	return (_user_code_set_universal(paket->userIdentifier, paket->userIdStatus, &paket->userCode[0x0], (len - sizeof(ZwUserCodeSetFrame_t))));
}

static int _user_code_keypad_mode_report(ZUNOCommandPacketReport_t *frame_report) {
	ZW_USER_CODE_KEYPAD_MODE_REPORT_V2_FRAME			*report;

	report = (ZW_USER_CODE_KEYPAD_MODE_REPORT_V2_FRAME *)frame_report->info.packet.cmd;
	// // report->cmdClass = COMMAND_CLASS_USER_CODE; //set in - fillOutgoingPacket
	// // report->cmd = USER_CODE_KEYPAD_MODE_REPORT_V2; //set in - fillOutgoingPacket
	report->keypadMode = _keypad_mode_get();
	frame_report->info.packet.len = sizeof(ZW_USER_CODE_KEYPAD_MODE_REPORT_V2_FRAME);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _user_code_keypad_mode_set(ZW_USER_CODE_KEYPAD_MODE_SET_V2_FRAME *paket) {
	size_t										keypadMode;

	keypadMode = paket->keypadMode;
	keypadMode = paket->keypadMode;
	if (keypadMode > (sizeof(_user_code_keypad_mode_mask) * 0x8 - 0x1) || (_user_code_keypad_mode_mask & (0x1 << keypadMode)) == 0x0)
		return (ZUNO_COMMAND_BLOCKED);
	_keypad_mode_set(keypadMode);
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
	UserCodeSaveUserId_t						parametr;
	uint16_t									userIdentifier;
	uint16_t									tempos;
	uint8_t										userIdStatus;
	size_t										i;
	uint16_t									crc16;

	report = (ZW_USER_CODE_CHECKSUM_REPORT_V2_FRAME *)frame_report->info.packet.cmd;
	// report->cmdClass = COMMAND_CLASS_USER_CODE; //set in - fillOutgoingPacket
	// report->cmd = USER_CODE_CHECKSUM_REPORT_V2; //set in - fillOutgoingPacket
	i = 0x0;
	userIdentifier = 0x1;
	crc16 = 0x1D0F;
	while (userIdentifier <= USER_CODE_NUMBER) {
		_get_user_code(&parametr, userIdentifier);
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
	frame_report->info.packet.len = sizeof(ZW_USER_CODE_CHECKSUM_REPORT_V2_FRAME);
	return (ZUNO_COMMAND_ANSWERED);
}

static int _user_code_master_report(ZUNOCommandPacketReport_t *frame_report) {
	ZwMasterCodeReportFrame_t		*report;
	size_t							masterCodeLen;

	report = (ZwMasterCodeReportFrame_t *)frame_report->info.packet.cmd;
	// report->cmdClass = COMMAND_CLASS_USER_CODE; //set in - fillOutgoingPacket
	// report->cmd = MASTER_CODE_REPORT_V2; //set in - fillOutgoingPacket
	masterCodeLen = _master_get(&report->masterCode[0x0]);
	report->properties1 = masterCodeLen;
	frame_report->info.packet.len = sizeof(ZwMasterCodeReportFrame_t) + masterCodeLen;
	return (ZUNO_COMMAND_ANSWERED);
}

static int _user_code_master_set(ZwMasterCodeSetFrame_t *paket) {
	size_t							masterCodeLen;
	const UserCodeSaveMaster_t		*master;

	masterCodeLen = paket->properties1 & MASTER_CODE_SET_PROPERTIES1_MASTER_CODE_LENGTH_MASK_V2;
	if (masterCodeLen != 0x0) {
		if (masterCodeLen < 0x4 || masterCodeLen > (sizeof(master->info.masterCode)))
			return (ZUNO_COMMAND_BLOCKED_FAILL);
		if (_user_code_set_one_test(&paket->masterCode[0x0], masterCodeLen) == false)
			return (ZUNO_COMMAND_BLOCKED_FAILL);
		if (_user_code_set_one_duplicate(&paket->masterCode[0x0], masterCodeLen) == false)
			return (ZUNO_COMMAND_BLOCKED_FAILL);
	}
	_master_save(&paket->masterCode[0x0], masterCodeLen);
	return (ZUNO_COMMAND_PROCESSED);
}

int zuno_CCUserCodeHandler(const ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
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
#endif