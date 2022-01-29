#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCAuthentication.h"

__WEAK ZwAuthenticationId_t __g_zuno_authentication_id[] = 
{
	{
		.st =
		{
			.fallbackStatus = AUTHENTICATION_STATUS_AVAILABLE,
			.userIdentifier1 = 0x0,
			.userIdentifier2 = 0x0,
			.scheduleId1 = 0x0,
			.scheduleId2 = 0x0,
			.properties1 = 0x0
		},
		.authenticationData = {0x0}
	}
};
__WEAK uint16_t __g_zuno_authentication_id_count = (sizeof(__g_zuno_authentication_id) / sizeof(__g_zuno_authentication_id[0x0]));


__WEAK ZwAuthenticationData_t __g_zuno_authentication_data[] = 
{
	{
		.authenticationDataLength = 0x0,
		.type = AUTHENTICATION_TECHNOLOGY_TYPE_RFID_TAG,
		.authenticationData = {0x0}
	}
};
__WEAK uint16_t __g_zuno_authentication_data_count = 1;

// extern __WEAK
static const uint32_t __g_zuno_authentication_technology_mask = ((0x1 << AUTHENTICATION_TECHNOLOGY_TYPE_RFID_TAG) | (0x1 << AUTHENTICATION_TECHNOLOGY_TYPE_MAGNETIC_CARD));
static const uint32_t __g_zuno_authentication_status_mask = ((0x1 << AUTHENTICATION_STATUS_AVAILABLE) | (0x1 << AUTHENTICATION_STATUS_ENABLED_GRANT_ACCESS) | (0x1 << AUTHENTICATION_STATUS_DISABLED));

static int _authentication_capability_report(void) {
	ZwAuthenticationCapabilityReportFrameStart_t						*start;
	ZwAuthenticationCapabilityReportFrameEnd_t							*end;
	uint32_t															len;

	start = (ZwAuthenticationCapabilityReportFrameStart_t *)&CMD_REPLY_CC;
	// start->cmdClass = COMMAND_CLASS_AUTHENTICATION; //set in - fillOutgoingPacket
	// start->cmd = AUTHENTICATION_CAPABILITY_REPORT; //set in - fillOutgoingPacket
	_zme_memcpy(&start->supportedAuthenticationIdEntries1, (uint8_t *)&__g_zuno_authentication_id_count, sizeof(__g_zuno_authentication_id_count));
	_zme_memcpy(&start->supportedDataIdEntries1, (uint8_t *)&__g_zuno_authentication_data_count, sizeof(__g_zuno_authentication_data_count));
	len = ((((sizeof(__g_zuno_authentication_technology_mask) * 0x8) - __builtin_clz(__g_zuno_authentication_technology_mask)) >> 0x3) + 0x1);
	start->properties1 = AUTHENTICATION_CAPABILITY_REPORT_PROPERTIES1_MAR_BIT_MASK | AUTHENTICATION_CAPABILITY_REPORT_PROPERTIES1_MADR_BIT_MASK | AUTHENTICATION_CAPABILITY_REPORT_PROPERTIES1_OR_BIT_MASK | len;
	memcpy(&start->supportedAuthenticationTechnologyTypeBitMask[0x0], (uint8_t *)&__g_zuno_authentication_technology_mask, len);
	end = (ZwAuthenticationCapabilityReportFrameEnd_t *)((uint8_t *)start + sizeof(ZwAuthenticationCapabilityReportFrameStart_t) + len);
	end->supportedChecksumTypeBitMask = (0x1 << AUTHENTICATION_CHECKSUM_GET_CHECKSUM_TYPE_AUTHENTICATION_DATA) | (0x1 << AUTHENTICATION_CHECKSUM_GET_CHECKSUM_TYPE_COMBINATION_ENTRIES);
	len = ((((sizeof(__g_zuno_authentication_status_mask) * 0x8) - __builtin_clz(__g_zuno_authentication_status_mask)) >> 0x3) + 0x1);
	end->properties2 = len;
	memcpy(&end->supportedFallbackStatusBitMask[0x0], (uint8_t *)&__g_zuno_authentication_status_mask, len);
	CMD_REPLY_LEN = ((uint8_t *)end - (uint8_t *)start) + sizeof(ZwAuthenticationCapabilityReportFrameEnd_t) + len;
	return (ZUNO_COMMAND_ANSWERED);
}

extern uint16_t __g_zuno_user_code_param_count;

static size_t _authentication_technologies_combination_set_test(ZwAuthenticationTechnologiesCombinationSet_t *packet, size_t len) {
	uint8_t						*b;
	uint8_t						*e;
	size_t						authenticationDataId;

	b = (uint8_t *)&packet->variantgroup;
	e = b + len;
	while (b < e) {
		authenticationDataId = (b[0x0] << 0x8) | b[0x1];
		if (authenticationDataId == 0x0 || authenticationDataId > __g_zuno_authentication_data_count)
			return (false);
		b = b + 0x2;
	}
	return (true);
}

static int _authentication_technologies_combination_set(ZwAuthenticationTechnologiesCombinationSet_t *packet) {
	size_t								authenticationId;
	size_t								userIdentifier;
	size_t								scheduleId;
	size_t								fallbackStatus;
	ZwAuthenticationId_t				*lp_id;
	ZwAuthenticationId_t				*b;
	ZwAuthenticationId_t				*e;
	size_t								len;
	uint8_t								*tmp;
	uint8_t								*authenticationData;

	authenticationId = (packet->authenticationId1 << 0x8) | packet->authenticationId2;
	if (authenticationId > __g_zuno_authentication_id_count)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	userIdentifier = (packet->st.userIdentifier1 << 0x8) | packet->st.userIdentifier2;
	scheduleId = (packet->st.scheduleId1 << 0x8) | packet->st.scheduleId2;
	if (authenticationId == 0x0) {
		if (packet->st.fallbackStatus != 0x0 || userIdentifier != 0x0 || scheduleId != 0x0 || packet->st.properties1 != 0x0)
			return (ZUNO_COMMAND_BLOCKED_FAILL);
		b = &__g_zuno_authentication_id[0x0];
		e = &__g_zuno_authentication_id[__g_zuno_authentication_id_count];
		while (b < e) {
			if ((b->st.properties1 & AUTHENTICATION_TECHNOLOGIES_COMBINATION_SET_PROPERTIES1_NUMBER_OF_AUTHENTICATION_DATA_IDS_MASK) > (sizeof(b->authenticationData) / 0x2)) {
				tmp = (uint8_t *)(b->authenticationData[0x0] | (b->authenticationData[0x1] << 8) | (b->authenticationData[0x2] << 16) | (b->authenticationData[03] << 24));
				free(tmp);
			}
			b->st.properties1 = 0x0;
			b++;
		}
		return (ZUNO_COMMAND_PROCESSED);
	}
	if (userIdentifier > __g_zuno_user_code_param_count)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	lp_id = &__g_zuno_authentication_id[authenticationId - 0x1];
	if (userIdentifier == 0x0) {
		fallbackStatus = packet->st.fallbackStatus;
		if (fallbackStatus > (sizeof(__g_zuno_authentication_status_mask) * 0x8 - 0x1) || (__g_zuno_authentication_status_mask & (0x1 << fallbackStatus)) == 0x0)
			return (ZUNO_COMMAND_BLOCKED_FAILL);
	}
	else
		packet->st.fallbackStatus = lp_id->st.fallbackStatus;
	len = packet->st.properties1 & AUTHENTICATION_TECHNOLOGIES_COMBINATION_SET_PROPERTIES1_NUMBER_OF_AUTHENTICATION_DATA_IDS_MASK * 2;
	if (len > 32)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	if (_authentication_technologies_combination_set_test(packet, len) == false)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	if (len > (sizeof(lp_id->authenticationData))) {
		if ((authenticationData = (uint8_t *)malloc(len)) == 0x0)
			return (ZUNO_COMMAND_BLOCKED_FAILL);
	}
	else
		authenticationData = &lp_id->authenticationData[0x0];
	if ((lp_id->st.properties1 & AUTHENTICATION_TECHNOLOGIES_COMBINATION_SET_PROPERTIES1_NUMBER_OF_AUTHENTICATION_DATA_IDS_MASK) > (sizeof(lp_id->authenticationData) / 0x2)) {
		tmp = (uint8_t *)(lp_id->authenticationData[0x0] | (lp_id->authenticationData[0x1] << 8) | (lp_id->authenticationData[0x2] << 16) | (lp_id->authenticationData[03] << 24));
		free(tmp);
	}
	if (len > (sizeof(lp_id->authenticationData))) {
		lp_id->authenticationData[0x0] = (size_t)authenticationData;
		lp_id->authenticationData[0x1] = (size_t)authenticationData >> 8;
		lp_id->authenticationData[0x2] = (size_t)authenticationData >> 16;
		lp_id->authenticationData[0x3] = (size_t)authenticationData >> 24;
	}
	memcpy(&lp_id->st, &packet->st, sizeof(packet->st));
	memcpy(authenticationData, &packet->variantgroup, len);
	return (ZUNO_COMMAND_PROCESSED);
}

static void _authentication_technologies_combination_get_set(ZwAuthenticationTechnologiesCombinationReportFrameMiddle_t *middle, ZwAuthenticationId_t *lp_id, size_t authenticationId, size_t count) {
	uint8_t								*tmp;
	
	middle->authenticationId1 = authenticationId >> 0x8;
	middle->authenticationId2 = authenticationId;
	middle->authenticationIdBlockLength = count;
	memcpy(&middle->st, &lp_id->st, sizeof(lp_id->st));
	count = count - sizeof(middle[0x0]);
	if (count > (sizeof(lp_id->authenticationData)))
		tmp = (uint8_t *)(lp_id->authenticationData[0x0] | (lp_id->authenticationData[0x1] << 8) | (lp_id->authenticationData[0x2] << 16) | (lp_id->authenticationData[03] << 24));
	else
		tmp = &lp_id->authenticationData[0x0];
	memcpy(&middle->variantgroup, tmp, count);
}

static int _authentication_technologies_combination_get(ZW_AUTHENTICATION_TECHNOLOGIES_COMBINATION_GET_FRAME *packet) {
	size_t																authenticationId;
	ZwAuthenticationTechnologiesCombinationReportFrameStart_t			*start;
	ZwAuthenticationTechnologiesCombinationReportFrameMiddle_t			*middle;
	ZwAuthenticationTechnologiesCombinationReportFrameEnd_t				*end;
	ZwAuthenticationId_t												*lp_id;
	size_t																len;
	size_t																count;


	start = (ZwAuthenticationTechnologiesCombinationReportFrameStart_t *)&CMD_REPLY_CC;
	// start->cmdClass = COMMAND_CLASS_AUTHENTICATION; //set in - fillOutgoingPacket
	// start->cmd = AUTHENTICATION_TECHNOLOGIES_COMBINATION_REPORT; //set in - fillOutgoingPacket
	authenticationId = (packet->authenticationId1 << 0x8) | packet->authenticationId2;
	start->numberOfAuthenticationIdBlocks = 0x0;
	middle = (ZwAuthenticationTechnologiesCombinationReportFrameMiddle_t *)((uint8_t *)start + sizeof(start[0x0]));
	if (authenticationId == 0x0 || authenticationId > __g_zuno_authentication_id_count) {
		end = (ZwAuthenticationTechnologiesCombinationReportFrameEnd_t *)(middle);
		end->nextAuthenticationId1 = 0x0;
		end->nextAuthenticationId2 = 0x0;
		CMD_REPLY_LEN = (sizeof(start[0x0]) + sizeof(end[0x0]));
		return (ZUNO_COMMAND_ANSWERED);
	}
	lp_id = &__g_zuno_authentication_id[authenticationId - 0x1];
	start->numberOfAuthenticationIdBlocks++;
	count = (lp_id->st.properties1 & AUTHENTICATION_TECHNOLOGIES_COMBINATION_SET_PROPERTIES1_NUMBER_OF_AUTHENTICATION_DATA_IDS_MASK) * 0x2 + sizeof(middle[0x0]);
	_authentication_technologies_combination_get_set(middle, lp_id, authenticationId, count);
	middle = (ZwAuthenticationTechnologiesCombinationReportFrameMiddle_t *)((uint8_t *)middle + count);
	len = count + sizeof(start[0x0]) + sizeof(end[0x0]);
	authenticationId++;
	if ((packet->properties1 & AUTHENTICATION_TECHNOLOGIES_COMBINATION_GET_PROPERTIES1_REPORT_MORE_BIT_MASK) != 0x0) {
		while (authenticationId <= __g_zuno_authentication_id_count) {
			lp_id++;
			if (lp_id->st.userIdentifier1 == 0x0 && lp_id->st.userIdentifier2 == 0x0 && lp_id->st.fallbackStatus == AUTHENTICATION_STATUS_AVAILABLE) {
				authenticationId++;
				continue ;
			}
			count = (lp_id->st.properties1 & AUTHENTICATION_TECHNOLOGIES_COMBINATION_SET_PROPERTIES1_NUMBER_OF_AUTHENTICATION_DATA_IDS_MASK) * 0x2 + sizeof(middle[0x0]);
			if ((len + count) >= ZUNO_COMMAND_PACKET_CMD_LEN_MAX_OUT)
				break ;
			start->numberOfAuthenticationIdBlocks++;
			_authentication_technologies_combination_get_set(middle, lp_id, authenticationId, count);
			authenticationId++;
			middle = (ZwAuthenticationTechnologiesCombinationReportFrameMiddle_t *)((uint8_t *)middle + count);
			len = len + count;
		}
	}
	while (authenticationId <= __g_zuno_authentication_id_count) {
		lp_id++;
		if (lp_id->st.userIdentifier1 != 0x0 || lp_id->st.userIdentifier2 != 0x0 || lp_id->st.fallbackStatus != AUTHENTICATION_STATUS_AVAILABLE)
			break ;
		authenticationId++;
	}
	if (authenticationId > __g_zuno_authentication_id_count)
		authenticationId = 0x0;
	end = (ZwAuthenticationTechnologiesCombinationReportFrameEnd_t *)middle;
	end->nextAuthenticationId1 = authenticationId >> 0x8;
	end->nextAuthenticationId2 = authenticationId;
	CMD_REPLY_LEN = len;
	return (ZUNO_COMMAND_ANSWERED);
}

static void _authentication_date_set_erase(ZwAuthenticationData_t *lp_data) {
	uint8_t								*tmp;

	tmp = (uint8_t *)(lp_data->authenticationData[0x0] | (lp_data->authenticationData[0x1] << 8) | (lp_data->authenticationData[0x2] << 16) | (lp_data->authenticationData[03] << 24));
	if (tmp == 0x0)
		return ;
	lp_data->authenticationDataLength = 0x0;
	free(tmp);
	memset(&lp_data->authenticationData[0x0], 0x0, sizeof(lp_data->authenticationData));
}

static void _authentication_date_set_erase_type(size_t type) {
	ZwAuthenticationData_t						*b;
	ZwAuthenticationData_t						*e;

	b = &__g_zuno_authentication_data[0x0];
	e = &__g_zuno_authentication_data[__g_zuno_authentication_data_count];
	while (b < e) {
		if (b->type == type)
			_authentication_date_set_erase(b);
		b++;
	}
}

static int _authentication_date_set(ZwAuthenticationDataSetFrame_t *packet) {
	size_t						authenticationDataId;
	size_t						authenticationDataLength;
	size_t						type;
	ZwAuthenticationData_t		*lp_data;
	uint8_t						*authenticationData;

	authenticationDataId = (packet->authenticationDataId1 << 0x8) | packet->authenticationDataId2;
	authenticationDataLength = packet->authenticationDataLength;
	if (authenticationDataId > __g_zuno_authentication_data_count)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	if (authenticationDataLength > 32)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	type = packet->properties1 & AUTHENTICATION_DATA_SET_PROPERTIES1_AUTHENTICATION_TECHNOLOGY_TYPE_MASK;
	if (type > (sizeof(__g_zuno_authentication_technology_mask) * 0x8 - 0x1) || (__g_zuno_authentication_technology_mask & (0x1 << type)) == 0x0)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	if (authenticationDataId == 0x0) {
		if (authenticationDataLength != 0x0)
			return (ZUNO_COMMAND_BLOCKED_FAILL);
		_authentication_date_set_erase_type(type);
		return (ZUNO_COMMAND_PROCESSED);
	}
	lp_data = &__g_zuno_authentication_data[authenticationDataId - 0x1];
	if (authenticationDataLength == 0x0) {
		_authentication_date_set_erase(lp_data);
		return (ZUNO_COMMAND_PROCESSED);
	}
	if ((authenticationData = (uint8_t *)malloc(authenticationDataLength)) == 0x0)
		return (ZUNO_COMMAND_BLOCKED_FAILL);
	_authentication_date_set_erase(lp_data);
	lp_data->authenticationDataLength = authenticationDataLength;
	lp_data->type = type;
	memcpy(authenticationData, &packet->authenticationData[0x0], authenticationDataLength);
	memcpy(&lp_data->authenticationData[0x0], &authenticationData, sizeof(lp_data->authenticationData));
	return (ZUNO_COMMAND_PROCESSED);
}

static void _authentication_date_report_set(ZwAuthenticationDataReportFrameMiddle_t *middle, ZwAuthenticationData_t *lp_data, size_t authenticationDataId, size_t count) {
	uint8_t									*tmp;

	count = lp_data->authenticationDataLength;
	middle->authenticationDataId1 = authenticationDataId >> 0x8;
	middle->authenticationDataId2 = authenticationDataId;
	middle->authenticationDataLength = count;
	middle->properties1 = lp_data->type;
	memcpy(&tmp, &lp_data->authenticationData[0x0], sizeof(lp_data->authenticationData));
	memcpy(&middle->authenticationData[0x0], tmp, count);
}

static int _authentication_date_report(ZW_AUTHENTICATION_DATA_GET_FRAME *packet) {
	ZwAuthenticationDataReportFrameStart_t									*start;
	ZwAuthenticationDataReportFrameEnd_t									*end;
	ZwAuthenticationDataReportFrameMiddle_t									*middle;
	size_t																	authenticationDataId;
	size_t																	count;
	size_t																	len;
	ZwAuthenticationData_t													*lp_data;

	start = (ZwAuthenticationDataReportFrameStart_t *)&CMD_REPLY_CC;
	// start->cmdClass = COMMAND_CLASS_AUTHENTICATION; //set in - fillOutgoingPacket
	// start->cmd = AUTHENTICATION_DATA_REPORT; //set in - fillOutgoingPacket
	authenticationDataId = (packet->authenticationDataId1 << 0x8) | packet->authenticationDataId2;
	start->numberOfAuthenticationDataIdBlocks = 0x0;
	middle = (ZwAuthenticationDataReportFrameMiddle_t *)((uint8_t *)start + sizeof(start[0x0]));
	if (authenticationDataId == 0x0 || authenticationDataId > __g_zuno_authentication_data_count) {
		end = (ZwAuthenticationDataReportFrameEnd_t *)(middle);
		end->nextAuthenticationDataId1 = 0x0;
		end->nextAuthenticationDataId2 = 0x0;
		CMD_REPLY_LEN = (sizeof(start[0x0]) + sizeof(end[0x0]));
		return (ZUNO_COMMAND_ANSWERED);
	}
	lp_data = &__g_zuno_authentication_data[authenticationDataId - 0x1];
	start->numberOfAuthenticationDataIdBlocks++;
	count = lp_data->authenticationDataLength;
	_authentication_date_report_set(middle, lp_data, authenticationDataId, count);
	count = count + sizeof(middle[0x0]);
	middle = (ZwAuthenticationDataReportFrameMiddle_t *)((uint8_t *)middle + count);
	len = count + sizeof(start[0x0]) + sizeof(end[0x0]);
	authenticationDataId++;
	if ((packet->properties1 & AUTHENTICATION_DATA_GET_PROPERTIES1_REPORT_MORE_BIT_MASK) != 0x0) {
		while (authenticationDataId <= __g_zuno_authentication_data_count) {
			lp_data++;
			if ((count = lp_data->authenticationDataLength) == 0x0) {
				authenticationDataId++;
				continue ;
			}
			if ((len + count + sizeof(middle[0x0])) >= ZUNO_COMMAND_PACKET_CMD_LEN_MAX_OUT)
				break ;
			start->numberOfAuthenticationDataIdBlocks++;
			_authentication_date_report_set(middle, lp_data, authenticationDataId, count);
			authenticationDataId++;
			count = count + sizeof(middle[0x0]);
			middle = (ZwAuthenticationDataReportFrameMiddle_t *)((uint8_t *)middle + count);
			len = len + count;
		}
	}
	while (authenticationDataId <= __g_zuno_authentication_data_count) {
		lp_data++;
		if (lp_data->authenticationDataLength != 0x0)
			break ;
		authenticationDataId++;
	}
	if (authenticationDataId > __g_zuno_authentication_data_count)
		authenticationDataId = 0x0;
	end = (ZwAuthenticationDataReportFrameEnd_t *)middle;
	end->nextAuthenticationDataId1 = authenticationDataId >> 0x8;
	end->nextAuthenticationDataId2 = authenticationDataId;
	CMD_REPLY_LEN = len;
	return (ZUNO_COMMAND_ANSWERED);
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

// static uint8_t *_authentication_checksum_report_combination_test(ZwAuthenticationId_t *b_id, size_t type) {
// 	uint8_t													*tmp;
// 	uint8_t													*b;
// 	size_t													count;
	
// 	if (b_id->st.userIdentifier1 == 0x0 && b_id->st.userIdentifier2 == 0x0 && b_id->st.fallbackStatus == AUTHENTICATION_STATUS_AVAILABLE)
// 		return (0x0);
// 	count = b_id->st.properties1 & AUTHENTICATION_TECHNOLOGIES_COMBINATION_SET_PROPERTIES1_NUMBER_OF_AUTHENTICATION_DATA_IDS_MASK;
// 	if (count > (sizeof(b_id->authenticationData) / 0x2))
// 		tmp = (uint8_t *)(b_id->authenticationData[0x0] | (b_id->authenticationData[0x1] << 8) | (b_id->authenticationData[0x2] << 16) | (b_id->authenticationData[03] << 24));
// 	else
// 		tmp = &b_id->authenticationData[0x0];
// 	b = tmp;
// 	if (count == 0x0) {
// 		return (0x0);
// 	while (count-- != 0x0) {
// 		if (__g_zuno_authentication_data[(b[0x0] << 0x8) | b[0x1]].type )
// 		{
// 			/* code */
// 		}
		
// 		b = b + 0x2;
// 	}
// 	return (tmp);
// }

static int _authentication_checksum_report(ZW_AUTHENTICATION_CHECKSUM_GET_FRAME *packet) {
	ZW_AUTHENTICATION_CHECKSUM_REPORT_FRAME									*report;
	size_t																	type;
	size_t																	properties1;
	uint16_t																crc16;
	size_t																	test;
	size_t																	authenticationDataLength;
	uint16_t																Identifie;
	uint16_t																tempos;
	ZwAuthenticationData_t													*b_data;
	ZwAuthenticationData_t													*e_data;
	uint8_t																	*tmp;
	ZwAuthenticationId_t													*b_id;
	ZwAuthenticationId_t													*e_id;
	ZwAuthenticationChecksumTypeCombination_t								combination;

	report = (ZW_AUTHENTICATION_CHECKSUM_REPORT_FRAME *)&CMD_REPLY_CC;
	// report->cmdClass = COMMAND_CLASS_AUTHENTICATION; //set in - fillOutgoingPacket
	// report->cmd = AUTHENTICATION_CHECKSUM_REPORT; //set in - fillOutgoingPacket
	CMD_REPLY_LEN = sizeof(ZW_AUTHENTICATION_CHECKSUM_REPORT_FRAME);
	properties1 = packet->properties1;
	report->properties1 = properties1;
	type = properties1 & AUTHENTICATION_CHECKSUM_GET_PROPERTIES1_AUTHENTICATION_TECHNOLOGY_TYPE_MASK;
	test = 0x0;
	if (type > (sizeof(__g_zuno_authentication_technology_mask) * 0x8 - 0x1) || (__g_zuno_authentication_technology_mask & (0x1 << type)) == 0x0) {
		;
	}
	else {
		Identifie = 0x1;
		crc16 = 0x1D0F;
		switch (((properties1 & AUTHENTICATION_CHECKSUM_GET_PROPERTIES1_CHECKSUM_TYPE_MASK) >> AUTHENTICATION_CHECKSUM_GET_PROPERTIES1_CHECKSUM_TYPE_SHIFT)) {
			case AUTHENTICATION_CHECKSUM_GET_CHECKSUM_TYPE_AUTHENTICATION_DATA:
				b_data = &__g_zuno_authentication_data[0x0];
				e_data = &__g_zuno_authentication_data[__g_zuno_authentication_data_count];
				while (b_data < e_data) {
					if ((authenticationDataLength = b_data->authenticationDataLength) != 0x0 && b_data->type == type) {
						test = 0x1;
						tempos = __builtin_bswap16(Identifie);
						crc16 = _crc16_ccitt_aug(crc16, (uint8_t *)&tempos, sizeof(tempos));
						memcpy(&tmp, &b_data->authenticationData[0x0], sizeof(b_data->authenticationData));
						crc16 = _crc16_ccitt_aug(crc16, tmp, authenticationDataLength);
					}
					Identifie++;
					b_data++;
				}
				break ;
			case AUTHENTICATION_CHECKSUM_GET_CHECKSUM_TYPE_COMBINATION_ENTRIES:
				b_id = &__g_zuno_authentication_id[0x0];
				e_id = &__g_zuno_authentication_id[__g_zuno_authentication_id_count];
				while (b_id < e_id) {
					if (b_id->st.userIdentifier1 == 0x0 && b_id->st.userIdentifier2 == 0x0 && b_id->st.fallbackStatus == AUTHENTICATION_STATUS_AVAILABLE) {
						;
					}
					else {
						test = 0x1;
						combination.authenticationId1 = Identifie >> 0x8;
						combination.authenticationId2 = Identifie;
						combination.st = b_id->st;
						tempos = (b_id->st.properties1 & AUTHENTICATION_TECHNOLOGIES_COMBINATION_SET_PROPERTIES1_NUMBER_OF_AUTHENTICATION_DATA_IDS_MASK);
						combination.st.properties1 = tempos;
						tempos = tempos * 0x2;
						combination.AuthenticationIDBlockLength = sizeof(combination) + tempos;
						crc16 = _crc16_ccitt_aug(crc16, (uint8_t *)&combination, sizeof(combination));
						if (tempos > (sizeof(b_id->authenticationData)))
							tmp = (uint8_t *)(b_id->authenticationData[0x0] | (b_id->authenticationData[0x1] << 8) | (b_id->authenticationData[0x2] << 16) | (b_id->authenticationData[03] << 24));
						else
							tmp = &b_id->authenticationData[0x0];
						crc16 = _crc16_ccitt_aug(crc16, tmp, tempos);
					}
					Identifie++;
					b_id++;
				}
				
				break ;
			default:
				break ;
		}
	}
	if (test == 0x0)
		crc16 = 0x0;
	report->checksum1 = crc16 >> 0x8;
	report->checksum2 = crc16;
	return (ZUNO_COMMAND_ANSWERED);
}

int zuno_CCAuthenticationHandler(ZUNOCommandPacket_t *cmd) {
	int								rs;

	switch (ZW_CMD) {
		case AUTHENTICATION_CAPABILITY_GET:
			rs = _authentication_capability_report();
			break ;
		case AUTHENTICATION_TECHNOLOGIES_COMBINATION_SET:
			rs = _authentication_technologies_combination_set((ZwAuthenticationTechnologiesCombinationSet_t *)&cmd->cmd[0x0]);
			break ;
		case AUTHENTICATION_TECHNOLOGIES_COMBINATION_GET:
			rs = _authentication_technologies_combination_get((ZW_AUTHENTICATION_TECHNOLOGIES_COMBINATION_GET_FRAME *)&cmd->cmd[0x0]);
			break ;
		case AUTHENTICATION_DATA_SET:
			rs = _authentication_date_set((ZwAuthenticationDataSetFrame_t *)&cmd->cmd[0x0]);
			break ;
		case AUTHENTICATION_DATA_GET:
			rs = _authentication_date_report((ZW_AUTHENTICATION_DATA_GET_FRAME *)&cmd->cmd[0x0]);
			break ;
		case AUTHENTICATION_CHECKSUM_GET:
			rs = _authentication_checksum_report((ZW_AUTHENTICATION_CHECKSUM_GET_FRAME *)&cmd->cmd[0x0]);
			break ;
		default:
			rs = ZUNO_COMMAND_BLOCKED_NO_SUPPORT;
			break ;
	}
	return (rs);
}