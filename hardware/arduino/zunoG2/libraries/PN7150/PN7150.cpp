#include "PN7150.h"

#define PN7150_CLASS_DEBUG Serial0

static const uint16_t SW1SW2 = 0x0090;
static const PN7150ClassCmdCoreReset_t NCICoreResetKeep = PN7150_CLASS_CORE_RESET_CMD_DEFAULT(PN7150_CLASS_CORE_RESET_CMD_TYPE_KEEP);
static const PN7150ClassCmdCoreReset_t NCICoreResetClear = PN7150_CLASS_CORE_RESET_CMD_DEFAULT(PN7150_CLASS_CORE_RESET_CMD_TYPE_CLEAR);
static const PN7150ClassCmdCoreInit_t NCICoreInit = PN7150_CLASS_CORE_INIT_CMD_DEFAULT();

/* Public Constructors */
PN7150Class::PN7150Class(TwoWire *wire, uint8_t scl, uint8_t sda, uint8_t irq, uint8_t ven, uint8_t addr):
			_wire(wire), _info_lp(0x0), _info_max(0x0), _info_count(0x0),  _info_index(0x0),_scl(scl), _sda(sda), _irq(irq), _ven(ven), _addr(addr), _mode(0x0), _NfcController_generation(0x0)
{
	this->_info_lp = &this->_info_array[0x0];
	this->_info_max = (sizeof(this->_info_array) / sizeof(this->_info_array[0x0]));
	memset(&this->_NfcController_fw_version[0x0], 0x0, sizeof(this->_NfcController_fw_version));
}


/* Public Methods */
uint8_t PN7150Class::ppsePaymentSystem(uint8_t index, void *buffer, uint8_t len) {
	size_t							count;
	void							*b;
	PN7150ClassRfNfc_t				*info;

	if ((info = this->_getInfo(index)) == 0x0) {
		b = 0x0;
		count = 0x0;
	}
	else {
		switch(info->protocol) {
			case (PN7150_CLASS_PROT_ISODEP):
				b = &info->cart_tag4.ApplicationLabel[0x0];
				count = info->cart_tag4.ApplicationLabelSize;
				break ;
			default:
				b = 0x0;
				count = 0x0;
				break ;
		}
	}
	return (this->_info_finish(buffer, b, count, len));
}

uint8_t PN7150Class::ppseCardNumber(uint8_t index, void *buffer, uint8_t len) {
	size_t							count;
	void							*b;
	PN7150ClassRfNfc_t				*info;

	if ((info = this->_getInfo(index)) == 0x0) {
		b = 0x0;
		count = 0x0;
	}
	else {
		switch(info->protocol) {
			case (PN7150_CLASS_PROT_ISODEP):
				b = &info->cart_tag4.panNumber[0x0];
				count = info->cart_tag4.panNumberSize;
				break ;
			default:
				b = 0x0;
				count = 0x0;
				break ;
		}
	}
	return (this->_info_finish(buffer, b, count, len));
}

uint8_t PN7150Class::ppseExpirationDate(uint8_t index, void *buffer, uint8_t len) {
	size_t							count;
	void							*b;
	PN7150ClassRfNfc_t				*info;

	if ((info = this->_getInfo(index)) == 0x0) {
		b = 0x0;
		count = 0x0;
	}
	else {
		switch(info->protocol) {
			case (PN7150_CLASS_PROT_ISODEP):
				b = &info->cart_tag4.panDate[0x0];
				count = info->cart_tag4.panDateSize;
				break ;
			default:
				b = 0x0;
				count = 0x0;
				break ;
		}
	}
	return (this->_info_finish(buffer, b, count, len));
}

PN7150ClassStatus_t PN7150Class::ppse(uint8_t index) {
	static const PN7150ClassNdef_t					select_pse = PN7150_CLASS_NDEF_DEFAULT(PN7150_CLASS_NDEF_SELECT_PSE);
	static const PN7150ClassNdefCmd_t				select_adf = PN7150_CLASS_NDEF_SELECT_PSE_ADF();
	static const PN7150ClassNdefCmd_t				get_processing_options = PN7150_CLASS_NDEF_GET_PROCESSING_OPTIONS_DEFAULT();
	static const PN7150ClassTlvTag_t				tag_application_label = {PN7150_CLASS_NDEF_TAG_APPLICATION_LABEL};
	static const PN7150ClassTlvTag_t				tag_adf = {PN7150_CLASS_NDEF_TAG_APPLICATION_DEDICATED_FILE_NAME};
	static const PN7150ClassTlvTag_t				tag_pdol = {PN7150_CLASS_NDEF_TAG_PDOL};
	static const PN7150ClassTlvTag_t				tag_ttq = {PN7150_CLASS_NDEF_TAG_TTQ};
	static const PN7150ClassTlvTag_t				tag_pan = {PN7150_CLASS_NDEF_TAG_PAN};
	static const PN7150ClassTlvTag_t				tag_pan_v2 = {PN7150_CLASS_NDEF_TAG_PAN_V2};
	static const PN7150ClassTlvTag_t				tag_afl = {PN7150_CLASS_NDEF_TAG_AFL};
	PN7150ClassStatus_t								ret;
	PN7150ClassRfNfc_t								*info;
	PN7150ClassCmdRspCommon_t						answer;
	PN7150ClassNdefReadRecords_t					read_records;
	union
	{
		PN7150ClassNdefCmd_t						ndef_cmd;
		uint8_t										buffer[PN7150_CLASS_MAX_NCI_FRAME_SIZE];
	};
	size_t											len;
	size_t											srec;
	size_t											len_tag;
	size_t											len_data;
	const uint8_t									*b;
	const uint8_t									*e;
	const PN7150ClassNdefAfl_t						*b_afl;
	const PN7150ClassNdefAfl_t						*e_afl;

	if ((info = this->_getInfo(index)) == 0x0)
		return (PN7150ClassStatusArgument);
	if (info->protocol != PN7150_CLASS_PROT_ISODEP)
		return (PN7150ClassStatusArgument);
	if ((ret = this->_select(&answer, index)) != PN7150ClassStatusOk)
		return (ret);
	if ((ret = this->_NxpNci_ReaderTagCmd(&select_pse, &answer)) != PN7150ClassStatusOk)
		return (ret);
	ndef_cmd = select_adf;
	if ((len = this->_tagGetData(this->_tagFind(&tag_adf, &answer), &ndef_cmd.value[0x0], PN7150_CLASS_NDEF_TAG_APPLICATION_DEDICATED_FILE_NAME_SIZE_MAX)) == 0x0)
		return (PN7150ClassStatusFailed);
	ndef_cmd.lc = len;
	ndef_cmd.value[len] = 0x0;//Le
	ndef_cmd.header.len = (sizeof(ndef_cmd) - sizeof(ndef_cmd.header)) + len + 0x1;//+0x1 - le
	if ((ret = this->_NxpNci_ReaderTagCmd(&ndef_cmd, &answer)) != PN7150ClassStatusOk)
		return (ret);
	info->cart_tag4.ApplicationLabelSize = this->_tagGetData(this->_tagFind(&tag_application_label, &answer), &info->cart_tag4.ApplicationLabel[0x0], sizeof(info->cart_tag4.ApplicationLabel));
	ndef_cmd = get_processing_options;
	ndef_cmd.value[0x0] = 0x83;
	len = 0x2;
	if ((b = (const uint8_t *)this->_tagFind(&tag_pdol, &answer)) != 0x0) {
		e = b + b[sizeof((uint8_t []){PN7150_CLASS_NDEF_TAG_PDOL})] + sizeof((uint8_t []){PN7150_CLASS_NDEF_TAG_PDOL}) + 0x1;//+0x1 - len
		b = b + sizeof((uint8_t []){PN7150_CLASS_NDEF_TAG_PDOL}) + 0x1;//+0x1 - len
		while (b < e) {
			len_tag = this->_tagGetLen((const PN7150ClassTlvTag_t *)b);
			len_data = b[len_tag];
			if (len_tag == sizeof((uint8_t []){PN7150_CLASS_NDEF_TAG_TTQ}) && memcmp(b, &tag_ttq, sizeof((uint8_t []){PN7150_CLASS_NDEF_TAG_TTQ})) == 0x0) {
				ndef_cmd.value[len] = 0xF0;//Terminal Transaction Qualifiers (TTQ)
				memset(&ndef_cmd.value[len + 0x1], 0x0, len_data - 0x1);
			}
			else
				memset(&ndef_cmd.value[len], 0x0, len_data);
			len = len + len_data;
			b = b + len_tag + 0x1;//+0x1 - len
		}
	}
	ndef_cmd.value[0x1] = len - 0x2;
	ndef_cmd.lc = len;
	ndef_cmd.value[len] = 0x0;//Le
	ndef_cmd.header.len = (sizeof(ndef_cmd) - sizeof(ndef_cmd.header)) + len + 0x1;//+0x1 - le
	if ((ret = this->_NxpNci_ReaderTagCmd(&ndef_cmd, &answer)) != PN7150ClassStatusOk)
		return (ret);
	info->cart_tag4.panNumberSize = 0x0;
	info->cart_tag4.panDateSize = 0x0;
	if (this->_ppsePan(&tag_pan, sizeof((uint8_t []){PN7150_CLASS_NDEF_TAG_PAN}), info, &answer) == PN7150ClassStatusOk || this->_ppsePan(&tag_pan_v2, sizeof((uint8_t []){PN7150_CLASS_NDEF_TAG_PAN_V2}), info, &answer) == PN7150ClassStatusOk)
		;
	else if ((b = (const uint8_t *)this->_tagFind(&tag_afl, &answer)) != 0x0) {
		len_tag = this->_tagGetLen((const PN7150ClassTlvTag_t *)b);
		b = b + len_tag + 0x1;//+1 - len
		b_afl = (const PN7150ClassNdefAfl_t *)b;
		e_afl = (const PN7150ClassNdefAfl_t *)(b + b[-1]);
		read_records = PN7150_CLASS_NDEF_READ_RECORDS_DEFAULT(0x0, 0x0);
		while (b_afl < e_afl) {
			read_records.p2 = b_afl->sfi | 0x4;
			srec = b_afl->srec;
			while (srec <= b_afl->erec) {
				read_records.p1 = srec++;
				if (this->_NxpNci_ReaderTagCmd(&read_records, (PN7150ClassCmdRspCommon_t *)&buffer[0x0]) == PN7150ClassStatusOk) {
					if (this->_ppsePan(&tag_pan, sizeof((uint8_t []){PN7150_CLASS_NDEF_TAG_PAN}), info, (PN7150ClassCmdRspCommon_t *)&buffer[0x0]) == PN7150ClassStatusOk || this->_ppsePan(&tag_pan_v2, sizeof((uint8_t []){PN7150_CLASS_NDEF_TAG_PAN_V2}), info, (PN7150ClassCmdRspCommon_t *)&buffer[0x0]) == PN7150ClassStatusOk) {
						b_afl = e_afl;
						break ;
					}
				}
			}
			b_afl++;
		}
	}
	// Serial0.dumpPrint((uint8_t *)&select_pse, (sizeof(select_pse.header) + select_pse.header.len), (sizeof(select_pse.header) + select_pse.header.len));
	return (PN7150ClassStatusOk);
}

PN7150ClassStatus_t PN7150Class::infoWaitRemoval(void (*userFunc)(uint8_t)) {
	static const size_t								delay_period = 100;
	PN7150ClassStatus_t								ret;
	PN7150ClassCmdRspCommon_t						answer;
	size_t											count;
	PN7150ClassRfNfc_t								*b;
	PN7150ClassRfNfc_t								*save;
	PN7150ClassRfNfc_t								*e;

	count = 0x0;
	b = &this->_info_lp[0x0];
	e = &this->_info_lp[this->_info_count];
	while (b < e) {
		if (b->protocol != PN7150_CLASS_PROT_UNDETERMINED)
			count++;
		b++;
	}
	if (count == 0x0)
		return (PN7150ClassStatusOk);
	if ((b = this->_getInfo(this->_info_index)) == 0x0) {
		if ((ret = this->_select(&answer, 0x1)) != PN7150ClassStatusOk)
			return (ret);
		if ((b = this->_getInfo(this->_info_index)) == 0x0)
			return (PN7150ClassStatusFailed);
	}
	save = b;
	while (count != 0x0) {
		if (b >= e)
			b = &this->_info_lp[0x0];
		if (b == save)
			delay(delay_period);
		if (b->protocol != PN7150_CLASS_PROT_UNDETERMINED) {
			if ((this->_select(&answer, (b - &this->_info_lp[0x0]) + 0x1) != PN7150ClassStatusOk) || (this->_removal(&answer, b) != PN7150ClassStatusActive)) {
				if (userFunc != 0x0)
					userFunc(b->protocol);
				count--;
				b->protocol = PN7150_CLASS_PROT_UNDETERMINED;
			}
		}
		b++;
	}
	return (PN7150ClassStatusOk);
}


uint8_t PN7150Class::infoDsfid(uint8_t index, void *buffer, uint8_t len) {
	size_t							count;
	void							*b;
	PN7150ClassRfNfc_t				*info;

	if ((info = this->_getInfo(index)) == 0x0) {
		b = 0x0;
		count = 0x0;
	}
	else {
		switch(info->mode_tech) {
			case (PN7150_CLASS_MODE_POLL | PN7150_CLASS_TECH_PASSIVE_15693):
				b = &info->parameters.vpp.DSFID;
				count = sizeof(info->parameters.vpp.DSFID);
			break ;
			case (PN7150_CLASS_MODE_POLL | PN7150_CLASS_TECH_PASSIVE_NFCA):
			case (PN7150_CLASS_MODE_POLL | PN7150_CLASS_TECH_PASSIVE_NFCB):
			case (PN7150_CLASS_MODE_POLL | PN7150_CLASS_TECH_PASSIVE_NFCF):
			default:
				b = 0x0;
				count = 0x0;
				break ;
		}
	}
	return (this->_info_finish(buffer, b, count, len));
}

uint8_t PN7150Class::infoAfi(uint8_t index, void *buffer, uint8_t len) {
	size_t							count;
	void							*b;
	PN7150ClassRfNfc_t				*info;

	if ((info = this->_getInfo(index)) == 0x0) {
		b = 0x0;
		count = 0x0;
	}
	else {
		switch(info->mode_tech) {
			case (PN7150_CLASS_MODE_POLL | PN7150_CLASS_TECH_PASSIVE_15693):
				b = &info->parameters.vpp.AFI;
				count = sizeof(info->parameters.vpp.AFI);
			break ;
			case (PN7150_CLASS_MODE_POLL | PN7150_CLASS_TECH_PASSIVE_NFCA):
			case (PN7150_CLASS_MODE_POLL | PN7150_CLASS_TECH_PASSIVE_NFCB):
			case (PN7150_CLASS_MODE_POLL | PN7150_CLASS_TECH_PASSIVE_NFCF):
			default:
				b = 0x0;
				count = 0x0;
				break ;
		}
	}
	return (this->_info_finish(buffer, b, count, len));
}

uint8_t PN7150Class::infoId(uint8_t index, void *buffer, uint8_t len) {
	size_t							count;
	void							*b;
	PN7150ClassRfNfc_t				*info;

	if ((info = this->_getInfo(index)) == 0x0) {
		b = 0x0;
		count = 0x0;
	}
	else {
		switch(info->mode_tech) {
			case (PN7150_CLASS_MODE_POLL | PN7150_CLASS_TECH_PASSIVE_15693):
				b = &info->parameters.vpp.ID[0x0];
				count = sizeof(info->parameters.vpp.ID);
			break ;
			case (PN7150_CLASS_MODE_POLL | PN7150_CLASS_TECH_PASSIVE_NFCA):
			case (PN7150_CLASS_MODE_POLL | PN7150_CLASS_TECH_PASSIVE_NFCB):
			case (PN7150_CLASS_MODE_POLL | PN7150_CLASS_TECH_PASSIVE_NFCF):
			default:
				b = 0x0;
				count = 0x0;
				break ;
		}
	}
	return (this->_info_finish(buffer, b, count, len));
}

uint16_t PN7150Class::infoBitRate(uint8_t index) {
	uint16_t						value;
	PN7150ClassRfNfc_t				*info;

	if ((info = this->_getInfo(index)) == 0x0)
		value = 0x0;
	else {
		switch(info->mode_tech) {
			case (PN7150_CLASS_MODE_POLL | PN7150_CLASS_TECH_PASSIVE_NFCF):
				value = (info->parameters.fpp.BitRate == 0x1) ? 212 : 424;
				break ;
			case (PN7150_CLASS_MODE_POLL | PN7150_CLASS_TECH_PASSIVE_NFCA):
			case (PN7150_CLASS_MODE_POLL | PN7150_CLASS_TECH_PASSIVE_NFCB):
			case (PN7150_CLASS_MODE_POLL | PN7150_CLASS_TECH_PASSIVE_15693):
			default:
				value = 0x0;
				break ;
		}
	}
	return (value);
}

uint8_t PN7150Class::infoSel(uint8_t index, void *buffer, uint8_t len) {
	size_t							count;
	void							*b;
	uint8_t							*tmp;
	PN7150ClassRfNfc_t				*info;

	if ((info = this->_getInfo(index)) == 0x0) {
		b = 0x0;
		count = 0x0;
	}
	else {
		switch(info->mode_tech) {
			case (PN7150_CLASS_MODE_POLL | PN7150_CLASS_TECH_PASSIVE_NFCA):
				tmp = &info->parameters.app.NfcId[info->parameters.app.NfcIdLen];
				b = tmp + 0x1;
				count = tmp[0x0];
			break ;
			case (PN7150_CLASS_MODE_POLL | PN7150_CLASS_TECH_PASSIVE_NFCB):
			case (PN7150_CLASS_MODE_POLL | PN7150_CLASS_TECH_PASSIVE_NFCF):
			case (PN7150_CLASS_MODE_POLL | PN7150_CLASS_TECH_PASSIVE_15693):
			default:
				b = 0x0;
				count = 0x0;
				break ;
		}
	}

	return (this->_info_finish(buffer, b, count, len));
}

uint8_t PN7150Class::infoProtocol(uint8_t index) {
	PN7150ClassRfNfc_t				*info;

	if ((info = this->_getInfo(index)) == 0x0)
		return (PN7150_CLASS_PROT_UNDETERMINED);
	return (info->protocol);
}

uint8_t PN7150Class::infoNfcid(uint8_t index, void *buffer, uint8_t len) {
	size_t							count;
	void							*b;
	PN7150ClassRfNfc_t				*info;

	if ((info = this->_getInfo(index)) == 0x0) {
		b = 0x0;
		count = 0x0;
	}
	else {
		switch(info->mode_tech) {
			case (PN7150_CLASS_MODE_POLL | PN7150_CLASS_TECH_PASSIVE_NFCA):
				b = &info->parameters.app.NfcId[0x0];
				count = info->parameters.app.NfcIdLen;
			break ;
			case (PN7150_CLASS_MODE_POLL | PN7150_CLASS_TECH_PASSIVE_NFCB):
			case (PN7150_CLASS_MODE_POLL | PN7150_CLASS_TECH_PASSIVE_NFCF):
			case (PN7150_CLASS_MODE_POLL | PN7150_CLASS_TECH_PASSIVE_15693):
			default:
				b = 0x0;
				count = 0x0;
				break ;
		}
	}
	return (this->_info_finish(buffer, b, count, len));
}

uint8_t PN7150Class::infoSens(uint8_t index, void *buffer, uint8_t len) {
	size_t							count;
	void							*b;
	PN7150ClassRfNfc_t				*info;

	if ((info = this->_getInfo(index)) == 0x0) {
		b = 0x0;
		count = 0x0;
	}
	else {
		switch(info->mode_tech) {
			case (PN7150_CLASS_MODE_POLL | PN7150_CLASS_TECH_PASSIVE_NFCA):
				b = &info->parameters.app.SensRes[0x0];
				count = sizeof(info->parameters.app.SensRes);
			break ;
			case (PN7150_CLASS_MODE_POLL | PN7150_CLASS_TECH_PASSIVE_NFCB):
				b = &info->parameters.bpp.SensRes[0x0];
				count = info->parameters.bpp.SensResLen;
				break ;
			case (PN7150_CLASS_MODE_POLL | PN7150_CLASS_TECH_PASSIVE_NFCF):
				b = &info->parameters.fpp.SensRes[0x0];
				count = info->parameters.fpp.SensResLen;
				break ;
			case (PN7150_CLASS_MODE_POLL | PN7150_CLASS_TECH_PASSIVE_15693):
			default:
				b = 0x0;
				count = 0x0;
				break ;
		}
	}
	return (this->_info_finish(buffer, b, count, len));
}

PN7150ClassStatus_t PN7150Class::info(uint8_t *count) {
	PN7150ClassStatus_t								ret;

	if ((this->_mode & (PN7150_CLASS_MODE_RW | PN7150_CLASS_MODE_P2P | PN7150_CLASS_MODE_CARDEMU)) == 0x0)
		return (PN7150ClassStatusArgument);
	if (digitalRead(this->_irq) == LOW)
		return (PN7150ClassStatusIrq);
	detachInterrupt(this->_irq);
	ret = this->_info();
	count[0x0] = this->_info_count;
	return (ret);
}

PN7150ClassStatus_t PN7150Class::setRf(void) {
	static const uint8_t NxpNci_CORE_CONF_EXTN[] =
	{
		0x20, 0x02, 0x0D, 0x03,/* CORE_SET_CONFIG_CMD */
		0xA0, 0x40, 0x01, 0x00,/* TAG_DETECTOR_CFG */
		0xA0, 0x41, 0x01, 0x04,/* TAG_DETECTOR_THRESHOLD_CFG */
		0xA0, 0x43, 0x01, 0x00/* TAG_DETECTOR_FALLBACK_CNT_CFG */
	};
	static const uint8_t NxpNci_CLK_CONF[]=
	{
		0x20, 0x02, 0x05, 0x01,/* CORE_SET_CONFIG_CMD */
		0xA0, 0x03, 0x01, 0x08/* CLOCK_SEL_CFG */
	};
	static const uint8_t NxpNci_RF_CONF_1stGen[]=
	{
		0x20, 0x02, 0x38, 0x07,
		0xA0, 0x0D, 0x06, 0x06, 0x42, 0x01, 0x00, 0xF1, 0xFF,   /* RF_CLIF_CFG_TARGET          CLIF_ANA_TX_AMPLITUDE_REG */
		0xA0, 0x0D, 0x06, 0x06, 0x44, 0xA3, 0x90, 0x03, 0x00,   /* RF_CLIF_CFG_TARGET          CLIF_ANA_RX_REG */
		0xA0, 0x0D, 0x06, 0x34, 0x2D, 0xDC, 0x50, 0x0C, 0x00,   /* RF_CLIF_CFG_BR_106_I_RXA_P  CLIF_SIGPRO_RM_CONFIG1_REG */
		0xA0, 0x0D, 0x04, 0x06, 0x03, 0x00, 0x70,               /* RF_CLIF_CFG_TARGET          CLIF_TRANSCEIVE_CONTROL_REG */
		0xA0, 0x0D, 0x03, 0x06, 0x16, 0x00,                     /* RF_CLIF_CFG_TARGET          CLIF_TX_UNDERSHOOT_CONFIG_REG */
		0xA0, 0x0D, 0x03, 0x06, 0x15, 0x00,                     /* RF_CLIF_CFG_TARGET          CLIF_TX_OVERSHOOT_CONFIG_REG */
		0xA0, 0x0D, 0x06, 0x32, 0x4A, 0x53, 0x07, 0x01, 0x1B    /* RF_CLIF_CFG_BR_106_I_TXA    CLIF_ANA_TX_SHAPE_CONTROL_REG */
	};
	/* RF configuration related to 2nd generation of NXP-NCI controller (e.g PN7150)*/
	/* Following configuration relates to performance optimization of OM5578/PN7150 NFC Controller demo kit */
	static const uint8_t NxpNci_RF_CONF_2ndGen[]=
	{
		0x20, 0x02, 0x94, 0x11,
		0xA0, 0x0D, 0x06, 0x04, 0x35, 0x90, 0x01, 0xF4, 0x01,    /* RF_CLIF_CFG_INITIATOR        CLIF_AGC_INPUT_REG */
		0xA0, 0x0D, 0x06, 0x06, 0x30, 0xB0, 0x01, 0x10, 0x00,    /* RF_CLIF_CFG_TARGET           CLIF_SIGPRO_ADCBCM_THRESHOLD_REG */
		0xA0, 0x0D, 0x06, 0x06, 0x42, 0x02, 0x00, 0xFF, 0xFF,    /* RF_CLIF_CFG_TARGET           CLIF_ANA_TX_AMPLITUDE_REG */
		0xA0, 0x0D, 0x06, 0x20, 0x42, 0x88, 0x00, 0xFF, 0xFF,    /* RF_CLIF_CFG_TECHNO_I_TX15693 CLIF_ANA_TX_AMPLITUDE_REG */
		0xA0, 0x0D, 0x04, 0x22, 0x44, 0x22, 0x00,                /* RF_CLIF_CFG_TECHNO_I_RX15693 CLIF_ANA_RX_REG */
		0xA0, 0x0D, 0x06, 0x22, 0x2D, 0x50, 0x34, 0x0C, 0x00,    /* RF_CLIF_CFG_TECHNO_I_RX15693 CLIF_SIGPRO_RM_CONFIG1_REG */
		0xA0, 0x0D, 0x06, 0x32, 0x42, 0xF8, 0x00, 0xFF, 0xFF,    /* RF_CLIF_CFG_BR_106_I_TXA     CLIF_ANA_TX_AMPLITUDE_REG */
		0xA0, 0x0D, 0x06, 0x34, 0x2D, 0x24, 0x37, 0x0C, 0x00,    /* RF_CLIF_CFG_BR_106_I_RXA_P   CLIF_SIGPRO_RM_CONFIG1_REG */
		0xA0, 0x0D, 0x06, 0x34, 0x33, 0x80, 0x86, 0x00, 0x70,    /* RF_CLIF_CFG_BR_106_I_RXA_P   CLIF_AGC_CONFIG0_REG */
		0xA0, 0x0D, 0x04, 0x34, 0x44, 0x22, 0x00,                /* RF_CLIF_CFG_BR_106_I_RXA_P   CLIF_ANA_RX_REG */
		0xA0, 0x0D, 0x06, 0x42, 0x2D, 0x15, 0x45, 0x0D, 0x00,    /* RF_CLIF_CFG_BR_848_I_RXA     CLIF_SIGPRO_RM_CONFIG1_REG */
		0xA0, 0x0D, 0x04, 0x46, 0x44, 0x22, 0x00,                /* RF_CLIF_CFG_BR_106_I_RXB     CLIF_ANA_RX_REG */
		0xA0, 0x0D, 0x06, 0x46, 0x2D, 0x05, 0x59, 0x0E, 0x00,    /* RF_CLIF_CFG_BR_106_I_RXB     CLIF_SIGPRO_RM_CONFIG1_REG */
		0xA0, 0x0D, 0x06, 0x44, 0x42, 0x88, 0x00, 0xFF, 0xFF,    /* RF_CLIF_CFG_BR_106_I_TXB     CLIF_ANA_TX_AMPLITUDE_REG */
		0xA0, 0x0D, 0x06, 0x56, 0x2D, 0x05, 0x9F, 0x0C, 0x00,    /* RF_CLIF_CFG_BR_212_I_RXF_P   CLIF_SIGPRO_RM_CONFIG1_REG */
		0xA0, 0x0D, 0x06, 0x54, 0x42, 0x88, 0x00, 0xFF, 0xFF,    /* RF_CLIF_CFG_BR_212_I_TXF     CLIF_ANA_TX_AMPLITUDE_REG */
		0xA0, 0x0D, 0x06, 0x0A, 0x33, 0x80, 0x86, 0x00, 0x70     /* RF_CLIF_CFG_I_ACTIVE         CLIF_AGC_CONFIG0_REG */
	};
	PN7150ClassCmdRspCommon_t									answer;
	PN7150ClassStatus_t											ret;
	const void													*b;

	if ((ret = this->_NxpNci_HostTransceive(&NxpNci_CORE_CONF_EXTN, &answer)) != PN7150ClassStatusOk)
		return (ret);
	if ((ret = this->_NxpNci_HostTransceive(&NxpNci_CLK_CONF, &answer)) != PN7150ClassStatusOk)
		return (ret);
	switch (this->_NfcController_generation) {
		case PN7150_CLASS_HARDWARE_VERSION_V1:
			b = &NxpNci_RF_CONF_1stGen[0x0];
			break ;
		case PN7150_CLASS_HARDWARE_VERSION_V2:
			b = &NxpNci_RF_CONF_2ndGen[0x0];
			break ;
		default:
			return (PN7150ClassStatusNew);
			break ;
	}
	if ((ret = this->_NxpNci_HostTransceive(b, &answer)) != PN7150ClassStatusOk)
		return (ret);
	return (PN7150ClassStatusOk);
}

PN7150ClassStatus_t PN7150Class::setPowerTransmitter(PN7150ClassPowerTransmitter_t mode) {
	PN7150ClassCmdSetConfigExtPowerTransmitterV1_t				set_power_transmitter_v1;
	PN7150ClassCmdSetConfigExtPowerTransmitterV2_t				set_power_transmitter_v2;
	size_t														prop;
	size_t														prop1;
	size_t														prop2;
	size_t														prop3;
	PN7150ClassCmdRspCommon_t									answer;
	PN7150ClassStatus_t											ret;

	switch (this->_NfcController_generation) {
		case PN7150_CLASS_HARDWARE_VERSION_V1:
			switch (mode) {
				case PN7150ClassPowerTransmitter_3_1_V:
					prop = 0x0;
					break ;
				case PN7150ClassPowerTransmitter_2_7_V:
					prop = 0xA;
					break ;
				default:
					return (PN7150ClassStatusNotSupport);
					break ;
			}
			set_power_transmitter_v1 = PN7150_CLASS_CORE_CONFIG_CMD_PARAMETER_EXT_POWER_TRANSMITTER_V1_DEFAULT(prop);
			if ((ret = this->_NxpNci_HostTransceive(&set_power_transmitter_v1, &answer)) != PN7150ClassStatusOk)
				return (ret);
			break ;
		case PN7150_CLASS_HARDWARE_VERSION_V2:
			switch (mode) {
				case PN7150ClassPowerTransmitter_3_0_V:
					prop1 = (0x2 | (0x0 << 0x2));
					prop2 = (0x0 | (0x0 << 0x3));
					prop3 = 0x0;
					break ;
				case PN7150ClassPowerTransmitter_3_3_V:
					prop1 = (0x2 | (0x0 << 0x2));
					prop2 = (0x1 | (0x1 << 0x3));
					prop3 = 0x0;
					break ;
				case PN7150ClassPowerTransmitter_3_6_V:
					prop1 = (0x2 | (0x0 << 0x2));
					prop2 = (0x2 | (0x2 << 0x3));
					prop3 = 0x0;
					break ;
				case PN7150ClassPowerTransmitter_4_5_V:
					prop1 = (0x2 | (0x1 << 0x2));
					prop2 = ((0x3 | (0x3 << 0x3)) | (0x1 << 0x6));
					prop3 = 0x1;
					break ;
				case PN7150ClassPowerTransmitter_4_7_V:
					prop1 = (0x2 | (0x1 << 0x2));
					prop2 = ((0x4 | (0x4 << 0x3)) | (0x1 << 0x6));
					prop3 = 0x1;
					break ;
				default:
					return (PN7150ClassStatusNotSupport);
					break ;
			}
			set_power_transmitter_v2 = PN7150_CLASS_CORE_CONFIG_CMD_PARAMETER_EXT_POWER_TRANSMITTER_V2_DEFAULT(prop1, prop2, prop3);
			if ((ret = this->_NxpNci_HostTransceive(&set_power_transmitter_v2, &answer)) != PN7150ClassStatusOk)
				return (ret);
			break ;
		default:
			return (PN7150ClassStatusNew);
			break ;
	}
	return (PN7150ClassStatusOk);
}

PN7150ClassStatus_t PN7150Class::getPowerTransmitter(PN7150ClassPowerTransmitter_t *mode) {
	static const PN7150ClassCmdGetConfig_t					get_power_transmitter_v1 = PN7150_CLASS_CORE_GET_CONFIG_CMD_DEFAULT_EXT(PN7150_CLASS_CORE_CONFIG_CMD_PARAMETER_EXT, PN7150_CLASS_CORE_CONFIG_CMD_PARAMETER_EXT_POWER_TRANSMITTER_V1);
	static const PN7150ClassCmdGetConfig_t					get_power_transmitter_v2 = PN7150_CLASS_CORE_GET_CONFIG_CMD_DEFAULT_EXT(PN7150_CLASS_CORE_CONFIG_CMD_PARAMETER_EXT, PN7150_CLASS_CORE_CONFIG_CMD_PARAMETER_EXT_POWER_TRANSMITTER_V2);
	const PN7150ClassCmdGetConfig_t							*get_power_transmitter;
	PN7150ClassCmdRspCommon_t								answer;
	PN7150ClassStatus_t										ret;
	size_t													len;
	PN7150ClassPowerTransmitter_t							out;

	switch (this->_NfcController_generation) {
		case PN7150_CLASS_HARDWARE_VERSION_V1:
			get_power_transmitter = &get_power_transmitter_v1;
			len = (sizeof(answer.get_config) - sizeof(answer.get_config.header) + sizeof(answer.get_config.parametrs[0x0].power_transmitter_v1));
			break ;
		case PN7150_CLASS_HARDWARE_VERSION_V2:
			get_power_transmitter = &get_power_transmitter_v2;
			len = (sizeof(answer.get_config) - sizeof(answer.get_config.header) + sizeof(answer.get_config.parametrs[0x0].power_transmitter_v2));
			break ;
		default:
			return (PN7150ClassStatusNew);
			break ;
	}
	if ((ret = this->_NxpNci_HostTransceive(get_power_transmitter, &answer)) != PN7150ClassStatusOk)
		return (ret);
	if (answer.get_config.header.len != len)
		return (PN7150ClassStatusHeader);
	switch (this->_NfcController_generation) {
		case PN7150_CLASS_HARDWARE_VERSION_V1:
			if (answer.get_config.parametrs[0x0].power_transmitter_v1.properties == 0x0)
				out = PN7150ClassPowerTransmitter_3_1_V;
			else
				out = PN7150ClassPowerTransmitter_2_7_V;
			break ;
		case PN7150_CLASS_HARDWARE_VERSION_V2:
			switch (answer.get_config.parametrs[0x0].power_transmitter_v2.properties2) {
				case (0x0 | (0x0 << 0x3)):
					out = PN7150ClassPowerTransmitter_3_0_V;
					break ;
				case (0x1 | (0x1 << 0x3)):
					out = PN7150ClassPowerTransmitter_3_3_V;
					break ;
				case (0x2 | (0x2 << 0x3)):
					out = PN7150ClassPowerTransmitter_3_6_V;
					break ;
				case ((0x3 | (0x3 << 0x3)) | (0x1 << 0x6)):
					out = PN7150ClassPowerTransmitter_4_5_V;
					break ;
				case ((0x4 | (0x4 << 0x3)) | (0x1 << 0x6)):
					out = PN7150ClassPowerTransmitter_4_7_V;
					break ;
				default:
					return (PN7150ClassStatusNew);
					break ;
			}
			break ;
		default:
			return (PN7150ClassStatusNew);
			break ;
	}
	mode[0] = out;
	return (PN7150ClassStatusOk);
}

PN7150ClassStatus_t PN7150Class::discoveryRestart(void (*userFunc)(void)) {
	static const PN7150ClassCmdRfDeactivate_t		deactivate = PN7150_CLASS_CMD_RF_DEACTIVATE_CMD_DEFAULT(PN7150_CLASS_CMD_RF_DEACTIVATE_MODE_IDLE);
	PN7150ClassCmdRspCommon_t						answer;
	PN7150ClassStatus_t								ret;

	while (this->_wireReceive(&answer, TIMEOUT_100MS) == PN7150ClassStatusOk)
		;
	if ((ret = this->_NxpNci_HostTransceive(&deactivate, &answer)) != PN7150ClassStatusOk)
		return (ret);
	this->_wireReceive(&answer, TIMEOUT_1S);
	return (this->discovery(userFunc));
}

PN7150ClassStatus_t PN7150Class::discovery(void (*userFunc)(void)) {
	static const PN7150ClassCmdSetDiscoveryParameters_t			parameters_rw_p2p[] =
	{
		{
			.mode_tech = (PN7150_CLASS_MODE_POLL | PN7150_CLASS_TECH_PASSIVE_NFCA),
			.freq = 0x1//Всегда такая менять бесполезно
		},
		{
			.mode_tech = (PN7150_CLASS_MODE_POLL | PN7150_CLASS_TECH_PASSIVE_NFCF),
			.freq = 0x1//Всегда такая менять бесполезно
		}
	};
	static const PN7150ClassCmdSetDiscoveryParameters_t			parameters_rw[] =
	{
		{
			.mode_tech = (PN7150_CLASS_MODE_POLL | PN7150_CLASS_TECH_PASSIVE_NFCB),
			.freq = 0x1//Всегда такая менять бесполезно
		},
		{
			.mode_tech = (PN7150_CLASS_MODE_POLL | PN7150_CLASS_TECH_PASSIVE_15693),
			.freq = 0x1//Всегда такая менять бесполезно
		}
	};
	static const PN7150ClassCmdSetDiscoveryParameters_t			parameters_p2p_cardemu[] =
	{
		{
			.mode_tech = (PN7150_CLASS_MODE_LISTEN | PN7150_CLASS_TECH_PASSIVE_NFCA),
			.freq = 0x1//Всегда такая менять бесполезно
		}
	};
	static const PN7150ClassCmdSetDiscoveryParameters_t			parameters_cardemu[] =
	{
		{
			.mode_tech = (PN7150_CLASS_MODE_LISTEN | PN7150_CLASS_TECH_PASSIVE_NFCB),
			.freq = 0x1//Всегда такая менять бесполезно
		}
	};
	static const PN7150ClassCmdSetDiscoveryParameters_t			parameters_p2p[] =
	{
		{
			.mode_tech = (PN7150_CLASS_MODE_POLL | PN7150_CLASS_TECH_ACTIVE_NFCA),/* Only one POLL ACTIVE mode can be enabled, if both are defined only NFCF applies */
			.freq = 0x1//Всегда такая менять бесполезно
		},
		// {
		// 	.mode_tech = (PN7150_CLASS_MODE_POLL | PN7150_CLASS_TECH_ACTIVE_NFCF),
		// 	.freq = 0x1//Всегда такая менять бесполезно
		// },
		{
			.mode_tech = (PN7150_CLASS_MODE_LISTEN | PN7150_CLASS_TECH_PASSIVE_NFCF),
			.freq = 0x1//Всегда такая менять бесполезно
		},
		{
			.mode_tech = (PN7150_CLASS_MODE_LISTEN | PN7150_CLASS_TECH_ACTIVE_NFCA),
			.freq = 0x1//Всегда такая менять бесполезно
		},
		{
			.mode_tech = (PN7150_CLASS_MODE_LISTEN | PN7150_CLASS_TECH_ACTIVE_NFCF),
			.freq = 0x1//Всегда такая менять бесполезно
		}
	};
	size_t											len;
	PN7150ClassStatus_t								ret;
	size_t											mode;
	PN7150ClassCmdRspCommon_t						answer;
	uint8_t											*lp;
	union 
	{
		uint8_t										command[PN7150_CLASS_MAX_NCI_FRAME_SIZE];
		PN7150ClassCmdSetDiscovery_t				set_discovery;
	};

	mode = this->_mode;
	if ((mode & (PN7150_CLASS_MODE_RW | PN7150_CLASS_MODE_P2P | PN7150_CLASS_MODE_CARDEMU)) == 0x0)
		return (PN7150ClassStatusArgument);
	set_discovery.header.unknown = PN7150_CLASS_CMD_RF;
	set_discovery.header.cmd = PN7150_CLASS_CMD_RF_DISCOVER_CMD;
	lp = (uint8_t *)&set_discovery.parameters[0x0];
	if ((mode & (PN7150_CLASS_MODE_RW | PN7150_CLASS_MODE_P2P)) != 0x0) {
		memcpy(lp, &parameters_rw_p2p, sizeof(parameters_rw_p2p));
		lp = lp + sizeof(parameters_rw_p2p);
	}
	if ((mode & (PN7150_CLASS_MODE_RW)) != 0x0) {
		memcpy(lp, &parameters_rw, sizeof(parameters_rw));
		lp = lp + sizeof(parameters_rw);
	}
	if ((mode & (PN7150_CLASS_MODE_P2P | PN7150_CLASS_MODE_CARDEMU)) != 0x0) {
		memcpy(lp, &parameters_p2p_cardemu, sizeof(parameters_p2p_cardemu));
		lp = lp + sizeof(parameters_p2p_cardemu);
	}
	if ((mode & (PN7150_CLASS_MODE_CARDEMU)) != 0x0) {
		memcpy(lp, &parameters_cardemu, sizeof(parameters_cardemu));
		lp = lp + sizeof(parameters_cardemu);
	}
	if ((mode & (PN7150_CLASS_MODE_P2P)) != 0x0) {
		memcpy(lp, &parameters_p2p, sizeof(parameters_p2p));
		lp = lp + sizeof(parameters_p2p);
	}
	len = lp - (uint8_t *)&set_discovery.parameters[0x0];
	set_discovery.header.len = len + (sizeof(set_discovery) - sizeof(set_discovery.header));
	set_discovery.NumberofParameters = len / (sizeof(PN7150ClassCmdSetDiscoveryParameters_t));
	if ((ret = this->_NxpNci_HostTransceive(&set_discovery, &answer)) != PN7150ClassStatusOk)
		return (ret);
	if (attachInterrupt(this->_irq, userFunc, RISING) != ZunoErrorOk)
		return (PN7150ClassStatusIrq);
	return (PN7150ClassStatusOk);
}

PN7150ClassStatus_t PN7150Class::configureMode(uint8_t mode) {
	uint8_t											Command[PN7150_CLASS_MAX_NCI_FRAME_SIZE];
	uint8_t											Answer[PN7150_CLASS_MAX_NCI_FRAME_SIZE];
	PN7150ClassStatus_t								ret;
	size_t											Item;
	const static uint8_t							NCIDiscoverMap[] = {0x21, 0x00};
	const static uint8_t							DM_CARDEMU[] = {0x4, 0x2, 0x2};
	const static uint8_t							R_CARDEMU[] = {0x1, 0x3, 0x0, 0x1, 0x4};
	const static uint8_t							DM_P2P[] = {0x5, 0x3, 0x3};
	const static uint8_t							R_P2P[] = {0x1, 0x3, 0x0, 0x1, 0x5};
	const static uint8_t							NCISetConfig_NFC[] = {0x20, 0x02, 0x1F, 0x02, 0x29, 0x0D, 0x46, 0x66, 0x6D, 0x01, 0x01, 0x11, 0x03, 0x02, 0x00, 0x01, 0x04, 0x01, 0xFA, 0x61, 0x0D, 0x46, 0x66, 0x6D, 0x01, 0x01, 0x11, 0x03, 0x02, 0x00, 0x01, 0x04, 0x01, 0xFA};
	const static uint8_t							DM_RW[] = {0x1, 0x1, 0x1, 0x2, 0x1, 0x1, 0x3, 0x1, 0x1, 0x4, 0x1, 0x2, 0x80, 0x01, 0x80};
	const static uint8_t							NCIPropAct[] = {0x2F, 0x02, 0x00};
	const static uint8_t							NCIRouting[] = {0x21, 0x01, 0x07, 0x00, 0x01};
	const static uint8_t							NCISetConfig_NFCA_SELRSP[] = {0x20, 0x02, 0x04, 0x01, 0x32, 0x01, 0x00};

	if ((mode & (PN7150_CLASS_MODE_P2P | PN7150_CLASS_MODE_CARDEMU)) != 0x0)
		return (PN7150ClassStatusArgument);
	mode = (mode & (~(PN7150_CLASS_MODE_RW | PN7150_CLASS_MODE_P2P | PN7150_CLASS_MODE_CARDEMU))) | PN7150_CLASS_MODE_RW;
	/* Enable Proprietary interface for T4T card presence check procedure */
	if (mode == PN7150_CLASS_MODE_RW) {
		if ((ret = this->_NxpNci_HostTransceive(NCIPropAct, (PN7150ClassCmdRspCommon_t *)&Answer[0x0])) != PN7150ClassStatusOk)
			return (ret);
	}
	/* Building Discovery Map command */
	Item = 0;
	if (mode & PN7150_CLASS_MODE_CARDEMU) {
		memcpy(&Command[4+(3*Item)], DM_CARDEMU, sizeof(DM_CARDEMU));
		Item++;
	}
	if (mode & PN7150_CLASS_MODE_P2P) {
		memcpy(&Command[4+(3*Item)], DM_P2P, sizeof(DM_P2P));
		Item++;
	}
	if (mode & PN7150_CLASS_MODE_RW) {
		memcpy(&Command[4+(3*Item)], DM_RW, sizeof(DM_RW));
		Item+=sizeof(DM_RW)/3;
	}
	memcpy(Command, NCIDiscoverMap, sizeof(NCIDiscoverMap));
	Command[2] = 1 + (Item*3);
	Command[3] = Item;
	if ((ret = this->_NxpNci_HostTransceive(Command, (PN7150ClassCmdRspCommon_t *)&Answer[0x0])) != PN7150ClassStatusOk)
		return (ret);
	/* Configuring routing */
	Item = 0;
	if (mode & PN7150_CLASS_MODE_CARDEMU) {
		memcpy(&Command[5+(5*Item)], R_CARDEMU, sizeof(R_CARDEMU));
		Item++;
	}
	if (mode & PN7150_CLASS_MODE_P2P) {
		memcpy(&Command[5+(5*Item)], R_P2P, sizeof(R_P2P));
		Item++;
	}
	if (Item != 0) {
		memcpy(Command, NCIRouting, sizeof(NCIRouting));
		Command[2] = 2 + (Item*5);
		Command[4] = Item;
		if ((ret = this->_NxpNci_HostTransceive(Command, (PN7150ClassCmdRspCommon_t *)&Answer[0x0])) != PN7150ClassStatusOk)
			return (ret);
	}
	/* Setting NFCA SEL_RSP */
	if ((mode & (PN7150_CLASS_MODE_CARDEMU | PN7150_CLASS_MODE_P2P)) != 0x0) {
		memcpy(Command, NCISetConfig_NFCA_SELRSP, sizeof(NCISetConfig_NFCA_SELRSP));
		if (mode & PN7150_CLASS_MODE_CARDEMU)
			Command[6] += 0x20;
		if (mode & PN7150_CLASS_MODE_P2P)
			Command[6] += 0x40;
		if ((ret = this->_NxpNci_HostTransceive(Command, (PN7150ClassCmdRspCommon_t *)&Answer[0x0])) != PN7150ClassStatusOk)
			return (ret);
	}
	/* Setting LLCP support */
	if (mode & PN7150_CLASS_MODE_P2P) {
		if ((ret = this->_NxpNci_HostTransceive(NCISetConfig_NFC, (PN7150ClassCmdRspCommon_t *)&Answer[0x0])) != PN7150ClassStatusOk)
			return (ret);
	}
	this->_mode = mode;
	return (PN7150ClassStatusOk);
}

PN7150ClassStatus_t PN7150Class::setPowerMode(PN7150ClassPowerMode_t mode) {
	static const PN7150ClassCmdSetPowerMode_t					power_idle = PN7150_CLASS_PROPRIETARY_POWER_MODE_CMD_DEFAULT(PN7150ClassPowerModeIdle);
	static const PN7150ClassCmdSetPowerMode_t					power_standby = PN7150_CLASS_PROPRIETARY_POWER_MODE_CMD_DEFAULT(PN7150ClassPowerModeStandby);
	const PN7150ClassCmdSetPowerMode_t							*power_mode;
	PN7150ClassStatus_t											ret;
	PN7150ClassCmdRspCommon_t									answer;

	switch (mode) {
		case PN7150ClassPowerModeStandby:
			power_mode = &power_standby;
			break ;
		case PN7150ClassPowerModeIdle:
		default:
			power_mode = &power_idle;
			break ;
	}
	if ((ret = this->_NxpNci_HostTransceive(power_mode, &answer)) != PN7150ClassStatusOk)
		return (ret);
	return (PN7150ClassStatusOk);
}

PN7150ClassStatus_t PN7150Class::setEEPROM(uint8_t buffer[PN7150_CLASS_EEPROM_SIZE]) {
	PN7150ClassCmdSetConfigExtEeprom_t				eeprom;
	size_t											cmd;
	PN7150ClassStatus_t								ret;
	PN7150ClassCmdRspCommon_t						answer;

	switch (this->_NfcController_generation) {
		case PN7150_CLASS_HARDWARE_VERSION_V1:
			cmd = PN7150_CLASS_CORE_CONFIG_CMD_PARAMETER_EXT_EEPROM_V1;
			break ;
		case PN7150_CLASS_HARDWARE_VERSION_V2:
			cmd = PN7150_CLASS_CORE_CONFIG_CMD_PARAMETER_EXT_EEPROM_V2;
			break ;
		default:
			return (PN7150ClassStatusNew);
			break ;
	}
	eeprom = PN7150_CLASS_CORE_CONFIG_CMD_PARAMETER_EXT_EEPROM_DEFAULT(cmd);
	memcpy(&eeprom.buffer[0x0], buffer, PN7150_CLASS_EEPROM_SIZE);
	if ((ret = this->_NxpNci_HostTransceive(&eeprom, &answer)) != PN7150ClassStatusOk)
		return (ret);
	return (PN7150ClassStatusOk);
}

PN7150ClassStatus_t PN7150Class::getEEPROM(uint8_t buffer[PN7150_CLASS_EEPROM_SIZE]) {
	static const PN7150ClassCmdGetConfig_t					get_eeprom_v1 = PN7150_CLASS_CORE_GET_CONFIG_CMD_DEFAULT_EXT(PN7150_CLASS_CORE_CONFIG_CMD_PARAMETER_EXT, PN7150_CLASS_CORE_CONFIG_CMD_PARAMETER_EXT_EEPROM_V1);
	static const PN7150ClassCmdGetConfig_t					get_eeprom_v2 = PN7150_CLASS_CORE_GET_CONFIG_CMD_DEFAULT_EXT(PN7150_CLASS_CORE_CONFIG_CMD_PARAMETER_EXT, PN7150_CLASS_CORE_CONFIG_CMD_PARAMETER_EXT_EEPROM_V2);
	const PN7150ClassCmdGetConfig_t							*get_eeprom;
	PN7150ClassCmdRspCommon_t								answer;
	PN7150ClassStatus_t										ret;

	switch (this->_NfcController_generation) {
		case PN7150_CLASS_HARDWARE_VERSION_V1:
			get_eeprom = &get_eeprom_v1;
			break ;
		case PN7150_CLASS_HARDWARE_VERSION_V2:
			get_eeprom = &get_eeprom_v2;
			break ;
		default:
			return (PN7150ClassStatusNew);
			break ;
	}
	if ((ret = this->_NxpNci_HostTransceive(get_eeprom, &answer)) != PN7150ClassStatusOk)
		return (ret);
	if (answer.get_config.header.len != (sizeof(answer.get_config) - sizeof(answer.get_config.header) + sizeof(answer.get_config.parametrs[0x0].eeprom)))
		return (PN7150ClassStatusHeader);
	memcpy(buffer, &answer.get_config.parametrs[0x0].eeprom.buffer[0x0], PN7150_CLASS_EEPROM_SIZE);
	return (PN7150ClassStatusOk);
}

PN7150ClassStatus_t PN7150Class::setDuration(uint16_t ms) {
	PN7150ClassCmdSetConfigTotalDuration_t		total_duration;
	PN7150ClassCmdRspCommon_t					answer;
	PN7150ClassStatus_t							ret;

	if (ms > 2570)
		ms = 2570;
	total_duration = PN7150_CLASS_CORE_CONFIG_CMD_PARAMETER_TOTAL_DURATION_DEFAULT(ms);
	if ((ret = this->_NxpNci_HostTransceive(&total_duration, &answer)) != PN7150ClassStatusOk)
		return (ret);
	if (answer.set_config.header.len != (sizeof(answer.set_config) - sizeof(answer.set_config.header)))
		return (PN7150ClassStatusHeader);
	return (PN7150ClassStatusOk);
}

PN7150ClassStatus_t PN7150Class::getDuration(uint16_t *ms) {
	static const PN7150ClassCmdGetConfig_t					get_duration = PN7150_CLASS_CORE_GET_CONFIG_CMD_DEFAULT(PN7150_CLASS_CORE_CONFIG_CMD_PARAMETER_TOTAL_DURATION);
	PN7150ClassCmdRspCommon_t								answer;
	PN7150ClassStatus_t										ret;

	if ((ret = this->_NxpNci_HostTransceive(&get_duration, &answer)) != PN7150ClassStatusOk)
		return (ret);
	if (answer.get_config.header.len != (sizeof(answer.get_config) - sizeof(answer.get_config.header) + sizeof(answer.get_config.parametrs[0x0].duration)))
		return (PN7150ClassStatusHeader);
	if (answer.get_config.parametrs[0x0].duration.sub != PN7150_CLASS_CORE_CONFIG_CMD_PARAMETER_TOTAL_DURATION)
		return (PN7150ClassStatusHeader);
	memcpy(ms, &answer.get_config.parametrs[0x0].duration.ms[0x0], sizeof(ms[0x0]));
	return (PN7150ClassStatusOk);
}

PN7150ClassStatus_t PN7150Class::applySettings(void) {
	PN7150ClassCmdRspCommon_t					answer;
	PN7150ClassStatus_t							ret;

	/* Reset the NFC Controller to insure new settings apply */
	if ((ret = this->_NxpNci_HostTransceive(&NCICoreResetKeep, &answer)) != PN7150ClassStatusOk)
		return (ret);
	if (answer.core_reset.type != PN7150_CLASS_CORE_RESET_CMD_TYPE_KEEP)
		return (PN7150ClassStatusConfigure);
	if ((ret = this->_NxpNci_HostTransceive(&NCICoreInit, &answer)) != PN7150ClassStatusOk)
		return (ret);
	return (PN7150ClassStatusOk);
}

PN7150ClassStatus_t PN7150Class::connect(bool clear) {
	PN7150ClassCmdRspCommon_t					answer;
	PN7150ClassStatus_t							ret;
	size_t										i;
	size_t										offset;
	PN7150ClassStatus_t							recovery;

	if (this->_wire->begin(this->_addr, this->_scl, this->_sda, &this->_buffer_wire[0x0], sizeof(this->_buffer_wire)) != ZunoErrorOk)
		return (PN7150ClassStatusI2cBegin);
	pinMode(this->_irq, INPUT);
	pinMode(this->_ven, OUTPUT);
	digitalWrite(this->_ven, HIGH);
	delay(0xA);
	digitalWrite(this->_ven, LOW);
	delay(0xA);
	digitalWrite(this->_ven, HIGH);
	/* Loop until NXPNCI answers */
	i = 0x0;
	while (this->_NxpNci_CheckDevPres(&answer, clear, &recovery) != PN7150ClassStatusOk) {
		if (i++ > 0x2)
			return (PN7150ClassStatusFailed);
		delay(500);
	}
	if ((ret = this->_NxpNci_HostTransceive(&NCICoreInit, &answer)) != PN7150ClassStatusOk)
		return (ret);
	offset = answer.buffer[8];
	/* Retrieve NXP-NCI NFC Controller generation */
	switch (answer.buffer[17 + offset]) {
		case 0x08:
			this->_NfcController_generation = PN7150_CLASS_HARDWARE_VERSION_V1;
			break ;
		case 0x10:
			this->_NfcController_generation = PN7150_CLASS_HARDWARE_VERSION_V2;
			break ;
	}
	//Retrieve NXP-NCI NFC Controller FW version
	memcpy(&this->_NfcController_fw_version[0x0], &answer.buffer[17 + offset], sizeof(this->_NfcController_fw_version));
	if (recovery != PN7150ClassStatusOk)
		return (recovery);
	return (PN7150ClassStatusOk);
}

/* Private Methods */
PN7150ClassStatus_t PN7150Class::_ppsePan(const PN7150ClassTlvTag_t *tag, size_t len_tag, PN7150ClassRfNfc_t *info, PN7150ClassCmdRspCommon_t *answer) {
	const uint8_t									*b;
	size_t											len;

	if ((b = (const uint8_t *)this->_tagFind(tag, answer)) != 0x0 && (len = b[len_tag]) >= PN7150_CLASS_NDEF_TAG_PAN_SIZE_NUMBER) {
		b = b + len_tag + 0x1;//+0x1 len
		info->cart_tag4.panNumberSize = sizeof(info->cart_tag4.panNumber);
		memcpy(&info->cart_tag4.panNumber[0x0], b, sizeof(info->cart_tag4.panNumber));
		if (len >= (PN7150_CLASS_NDEF_TAG_PAN_SIZE_NUMBER + (PN7150_CLASS_NDEF_TAG_PAN_SIZE_DATE + 0x1))) {
			info->cart_tag4.panDateSize = sizeof(info->cart_tag4.panDate);
			info->cart_tag4.panDate[0x0] = ((b[PN7150_CLASS_NDEF_TAG_PAN_SIZE_NUMBER + 0x1] & 0xF) << 0x4) | ((b[PN7150_CLASS_NDEF_TAG_PAN_SIZE_NUMBER + 0x2] >> 0x4));
			info->cart_tag4.panDate[0x1] = ((b[PN7150_CLASS_NDEF_TAG_PAN_SIZE_NUMBER] << 0x4)) | (b[PN7150_CLASS_NDEF_TAG_PAN_SIZE_NUMBER + 0x1] >> 0x4);
		}
		return (PN7150ClassStatusOk);
	}
	return (PN7150ClassStatusFailed);
}

uint8_t PN7150Class::_tagGetData(const PN7150ClassTlvTag_t *tag, void *dst, size_t len) {
	size_t													len_tag;
	size_t													count;
	const uint8_t											*b;

	if (tag == 0x0)
		return (0x0);
	len_tag = this->_tagGetLen(tag);
	b = (const uint8_t *)tag;
	if ((count = b[len_tag]) > len)
		count = len;
	memcpy(dst, b + len_tag + 0x1, count);//tag-len-value
	return (count);
}

const PN7150ClassTlvTag_t *PN7150Class::_tagFind(const PN7150ClassTlvTag_t *tag, const PN7150ClassCmdRspCommon_t *answer) {
	size_t									len;
	const uint8_t							*b;
	const uint8_t							*e;

	len = this->_tagGetLen(tag);
	b = &answer->ndef.parameters[0x0];
	e = (const uint8_t *)((uint8_t *)answer + (answer->ndef.header.len + (sizeof(answer->ndef.header) - sizeof(SW1SW2))));
	return (this->_tagFind_add(tag, b, e, len));
}

const PN7150ClassTlvTag_t *PN7150Class::_tagFind_add(const PN7150ClassTlvTag_t *tag, const uint8_t *b, const uint8_t *e, size_t len) {
	const PN7150ClassTlvTag_t								*tag_add;
	size_t													len_add;
	const PN7150ClassTlvTag_t								*out;

	while (b < e) {
		tag_add = (const PN7150ClassTlvTag_t *)b;
		len_add = this->_tagGetLen(tag_add);
		if (len_add == len && memcmp(tag_add, tag, len) == 0x0)
			return (tag_add);
		if (tag_add->tag_object == true)
			if ((out = this->_tagFind_add(tag, b + len_add + 0x1, b + b[len_add], len)) != 0x0)//tag-len-value
				return (out);
		b = b + len_add + 0x1 + b[len_add];//tag-len-value
	}
	return (0x0);
}

uint8_t PN7150Class::_tagGetLen(const PN7150ClassTlvTag_t *tag) {
	const PN7150ClassTlvTagAdd_t		*tag_add;

	if (tag->tag_number != 0x1F)
		return (0x1);
	tag_add = &tag->tag_add[0x0];
	while (tag_add->tag_follows == true)
		tag_add++;
	return (0x2 + (tag_add - &tag->tag_add[0x0]));
}

PN7150ClassRfNfc_t *PN7150Class::_getInfo(uint8_t index) {
	if (index > this->_info_count || index == 0x0)
		return (0x0);
	return (&this->_info_lp[index - 0x1]);
}

PN7150ClassRfNfc_t *PN7150Class::_info_set(PN7150ClassRfNfc_t *info, PN7150ClassCmdRspCommon_t *answer) {
	info->protocol = answer->RfDiscoverNtf.protocol;
	info->mode_tech = answer->RfDiscoverNtf.mode_tech;
	info->parameters = answer->RfDiscoverNtf.parameters;
	info++;
	return (info);
}

PN7150ClassStatus_t PN7150Class::_removal(PN7150ClassCmdRspCommon_t *answer, PN7150ClassRfNfc_t *info) {
	static const uint8_t							NCIPresCheckT1T[] = {0x00, 0x00, 0x07, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	static const uint8_t							NCIPresCheckT2T[] = {0x00, 0x00, 0x02, 0x30, 0x00};
	static const uint8_t							NCIPresCheckT3T[] = {0x21, 0x08, 0x04, 0xFF, 0xFF, 0x00, 0x01};
	static const uint8_t							NCIPresCheckIsoDep[] = {0x2F, 0x11, 0x00};
	static const uint8_t							NCIPresCheckIsoDepNtf[] = {0x6F, 0x11, 0x1, 0x0};
	static const uint8_t							NCIDeactivate[] = {0x21, 0x06, 0x01, 0x01};
	static const uint8_t							NCISelectMIFARE[] = {0x21, 0x04, 0x03, 0x01, 0x80, 0x80};
	static const uint8_t							NCIPresCheckIso15693[] = {0x00, 0x00, 0x0B, 0x26, 0x01, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	uint8_t											NCIPresCheckIso15693_dup[sizeof(NCIPresCheckIso15693)];
	PN7150ClassStatus_t								ret;
	size_t											i;

	switch (info->protocol) {
		case PN7150_CLASS_PROT_T1T:
			while (true) {
				if ((ret = this->_transceive(NCIPresCheckT1T, answer)) != PN7150ClassStatusOk)
					return (ret);
				if ((ret = this->_wireReceive(answer, TIMEOUT_100MS)) != PN7150ClassStatusOk)
					break ;
				if (((answer->buffer[0] == 0x00) && (answer->buffer[1] == 0x00)) == false)
					break ;
				return (PN7150ClassStatusActive);
			}
			break ;
		case PN7150_CLASS_PROT_T2T:
			while (true) {
				if ((ret = this->_transceive(NCIPresCheckT2T, answer)) != PN7150ClassStatusOk)
					return (ret);
				if ((ret = this->_wireReceive(answer, TIMEOUT_100MS)) != PN7150ClassStatusOk)
					break ;
				if (((answer->buffer[0] == 0x00) && (answer->buffer[1] == 0x00) && (answer->buffer[2] == 0x11)) == false)
					break ;
				return (PN7150ClassStatusActive);
			}
			break ;
		case PN7150_CLASS_PROT_T3T:
			while (true) {
				if ((ret = this->_transceive(NCIPresCheckT3T, answer)) != PN7150ClassStatusOk)
					return (ret);
				if ((ret = this->_wireReceive(answer, TIMEOUT_100MS)) != PN7150ClassStatusOk)
					break ;
				if (((answer->buffer[0] == 0x61) && (answer->buffer[1] == 0x08) && ((answer->buffer[3] == 0x00) || (answer->buffer[4] > 0x00))) == false)
					break ;
				return (PN7150ClassStatusActive);
			}
			break ;
		case PN7150_CLASS_PROT_ISODEP:
			while (true) {
				if ((ret = this->_NxpNci_HostTransceive(NCIPresCheckIsoDep, answer)) != PN7150ClassStatusOk)
					return (ret);
				if ((ret = this->_wireReceive(answer, TIMEOUT_INFINITE)) != PN7150ClassStatusOk)
					return (ret);
				if (memcmp(answer, &NCIPresCheckIsoDepNtf[0x0], sizeof(NCIPresCheckIsoDepNtf)) == 0x0)
					break ;
				return (PN7150ClassStatusActive);
			}
			break ;
		case PN7150_CLASS_PROT_T5T:
			memcpy(NCIPresCheckIso15693_dup, NCIPresCheckIso15693, sizeof(NCIPresCheckIso15693_dup));
			for(i=0; i<8; i++) NCIPresCheckIso15693_dup[i+6] = info->parameters.vpp.ID[7-i];
			while (true) {
				if ((ret = this->_NxpNci_HostTransceive(NCIPresCheckIso15693_dup, answer)) != PN7150ClassStatusOk)
					return (ret);
				if ((ret = this->_wireReceive(answer, TIMEOUT_100MS)) != PN7150ClassStatusOk)
					return (ret);
				if (((answer->buffer[0] == 0x00) && (answer->buffer[1] == 0x00) && (answer->buffer[(answer->rsp.header.len + sizeof(answer->rsp.header))-1] == 0x00)) == false)
					break ;
				return (PN7150ClassStatusActive);
			}
			break ;
		case PN7150_CLASS_PROT_MIFARE:
			while (true) {
				if ((ret = this->_NxpNci_HostTransceive(NCIDeactivate, answer)) != PN7150ClassStatusOk)
					return (ret);
				if ((ret = this->_wireReceive(answer, TIMEOUT_INFINITE)) != PN7150ClassStatusOk)
					return (ret);
				if ((ret = this->_NxpNci_HostTransceive(NCISelectMIFARE, answer)) != PN7150ClassStatusOk)
					return (ret);
				if ((ret = this->_wireReceive(answer, TIMEOUT_INFINITE)) != PN7150ClassStatusOk)
					return (ret);
				if (answer->rf_intf_activated.header.unknown != PN7150_CLASS_CMD_RF_NTF && answer->rf_intf_activated.header.cmd != PN7150_CLASS_CMD_RF_INTF_ACTIVATED_NTF)
					break ;
				return (PN7150ClassStatusActive);
			}
			break ;
		default:
			break ;
	}
	return (PN7150ClassStatusOk);
}

size_t PN7150Class::_protToIntf(size_t prot) {
	size_t						intf;

	switch (prot) {
		case PN7150_CLASS_PROT_ISODEP:
			intf = PN7150_CLASS_INTF_ISODEP;
			break ;
		case PN7150_CLASS_PROT_NFCDEP:
			intf = PN7150_CLASS_INTF_NFCDEP;
			break ;
		case PN7150_CLASS_PROT_MIFARE:
			intf = PN7150_CLASS_INTF_TAGCMD;
			break ;
		default:
			intf = PN7150_CLASS_INTF_FRAME;
			break ;
	}
	return (intf);
}

size_t PN7150Class::_getCountCart(void) {
	PN7150ClassRfNfc_t							*b;
	PN7150ClassRfNfc_t							*e;
	size_t										count;

	count = 0x0;
	b = &this->_info_lp[0x0];
	e = &this->_info_lp[this->_info_count];
	while (b < e) {
		if (b->protocol != PN7150_CLASS_PROT_UNDETERMINED)
			count++;
		b++;
	}
	return (count);
}

PN7150ClassStatus_t PN7150Class::_select(PN7150ClassCmdRspCommon_t *answer, size_t index) {
	static const PN7150ClassCmdRfDeactivate_t			deactivate = PN7150_CLASS_CMD_RF_DEACTIVATE_CMD_DEFAULT(PN7150_CLASS_CMD_RF_DEACTIVATE_MODE_SLEEP);
	PN7150ClassRfDiscoverSelectCmd_t					select;
	PN7150ClassRfNfc_t									*info;
	PN7150ClassRfNfc_t									*info_old;
	size_t												protocol;
	PN7150ClassStatus_t									ret;

	if ((info = this->_getInfo(index)) == 0x0) {
		return (PN7150ClassStatusArgument);
	}
	info_old = this->_getInfo(this->_info_index);
	if (info == info_old)//Если активна то не выбираем повторно
		return (PN7150ClassStatusOk);
	if (info_old != 0x0) {
		if ((ret = this->_NxpNci_HostTransceive(&deactivate, answer)) != PN7150ClassStatusOk)
			return (ret);
		if ((ret = this->_wireReceive(answer, TIMEOUT_100MS)) != PN7150ClassStatusOk)
			return (ret);
		if (answer->RfDeactivateNtf.header.unknown != PN7150_CLASS_CMD_RF_NTF || answer->RfDeactivateNtf.header.cmd != PN7150_CLASS_CMD_RF_DEACTIVATE_NTF || answer->RfDeactivateNtf.mode != PN7150_CLASS_CMD_RF_DEACTIVATE_MODE_SLEEP)
			return (PN7150ClassStatusHeader);
	}
	protocol = info->protocol;
	select = PN7150_CLASS_RF_DISCOVER_SELECT_CMD_DEFAULT(index, protocol, this->_protToIntf(protocol));
	if ((ret = this->_NxpNci_HostTransceive(&select, answer)) != PN7150ClassStatusOk)
		return (ret);
	if ((ret = this->_wireReceive(answer, TIMEOUT_100MS)) != PN7150ClassStatusOk)
		return (ret);
	if (answer->ntf.unknown != PN7150_CLASS_CMD_RF_NTF)
		return (PN7150ClassStatusHeader);
	if (answer->ntf.cmd != PN7150_CLASS_CMD_RF_INTF_ACTIVATED_NTF)
		return (PN7150ClassStatusHeader);
	this->_info_index = index;
	return (PN7150ClassStatusOk);
}

PN7150ClassStatus_t PN7150Class::_info(void) {
	PN7150ClassCmdRspCommon_t							answer;
	PN7150ClassStatus_t									ret;
	size_t												cmd;
	PN7150ClassRfNfc_t									*info;
	PN7150ClassRfNfc_t									*info_e;

	this->_info_count = 0x0;
	this->_info_index = 0x0;
	if ((ret = this->_wireReceive(&answer, TIMEOUT_100MS)) != PN7150ClassStatusOk)
		return (ret);
	if (answer.ntf.unknown != PN7150_CLASS_CMD_RF_NTF)
		return (PN7150ClassStatusHeader);
	info = &this->_info_lp[0x0];
	if ((cmd = answer.ntf.cmd) == PN7150_CLASS_CMD_RF_INTF_ACTIVATED_NTF) {
		this->_info_count = 0x1;
		this->_info_index = 0x1;
		info->protocol = answer.rf_intf_activated.protocol;
		info->mode_tech = answer.rf_intf_activated.mode_tech;
		info->parameters = answer.rf_intf_activated.parameters;
		return (PN7150ClassStatusOk);
	}
	else if (cmd != PN7150_CLASS_CMD_RF_DISCOVER_NTTF)
		return (PN7150ClassStatusHeader);
	info = this->_info_set(info, &answer);
	info_e = &this->_info_lp[this->_info_max];
	//Get all NTF for further activation
	while (true) {
		if ((ret = this->_wireReceive(&answer, TIMEOUT_100MS)) != PN7150ClassStatusOk)
			return (ret);
		if (answer.ntf.unknown != PN7150_CLASS_CMD_RF_NTF)
			continue ;
		if (answer.ntf.cmd != PN7150_CLASS_CMD_RF_DISCOVER_NTTF)
			continue ;
		if (info >= info_e)
			return (PN7150ClassStatusMemory);
		info = this->_info_set(info, &answer);
		if (answer.buffer[(sizeof(answer.ntf) + answer.ntf.len) - 0x1] != 0x2)// Remaining NTF ? - 2 More Notification to follow
			break ;
	}
	this->_info_count = info - &this->_info_lp[0x0];
	return (this->_select(&answer, 0x1));
}

uint8_t PN7150Class::_info_finish(void *buffer, void *b, size_t count, uint8_t len) {
	if (buffer == 0x0)
		return (count);
	if (count > len)
		count = len;
	memcpy(buffer, b, count);
	return (count);
}

PN7150ClassStatus_t PN7150Class::_NxpNci_CheckDevPres(PN7150ClassCmdRspCommon_t *answer, size_t bClear, PN7150ClassStatus_t *recovery) {
	PN7150ClassStatus_t							ret;
	const PN7150ClassCmdCoreReset_t				*core_reset;

	if (bClear == true)
		core_reset = &NCICoreResetClear;
	else
		core_reset = &NCICoreResetKeep;
	if ((ret = this->_NxpNci_HostTransceive(core_reset, answer)) != PN7150ClassStatusOk)
		return (ret);
	if (answer->core_reset.type != core_reset->type)
		return (PN7150ClassStatusConfigure);
	/* Catch potential notifications */
	if (this->_wireReceive(answer, TIMEOUT_100MS) == PN7150ClassStatusOk) {
		if ((answer->rsp.header.unknown == 0x60) && (answer->rsp.header.cmd == 0x07)) {
			/* Is PN7150B0HN/C11004 Anti-tearing recovery procedure triggered ? */
			if ((answer->rsp.status == 0xE6)) {
				recovery[0x0] = PN7150ClassStatusClearConfig;
				return (PN7150ClassStatusOk);
			}
		}
		else
			return (PN7150ClassStatusFailed);
	}
	recovery[0x0] = PN7150ClassStatusOk;
	return (PN7150ClassStatusOk);
}

PN7150ClassStatus_t PN7150Class::_transceive(const void *pBuffer, PN7150ClassCmdRspCommon_t *answer) {
	PN7150ClassStatus_t							ret;
	const PN7150ClassCmdHeader_t				*header;
	size_t										BufferLen;

	header = (const PN7150ClassCmdHeader_t *)pBuffer;
	BufferLen = header->len + sizeof(header[0x0]);
	if ((ret = this->_wireSend(pBuffer, BufferLen)) != PN7150ClassStatusOk)
		return (ret);
	if ((ret = this->_wireReceive(answer, TIMEOUT_1S)) != PN7150ClassStatusOk)
		return (ret);
	return (PN7150ClassStatusOk);
}

PN7150ClassStatus_t PN7150Class::_NxpNci_ReaderTagCmd(const void *pBuffer, PN7150ClassCmdRspCommon_t *answer) {
	PN7150ClassStatus_t							ret;

	if ((ret = this->_transceive(pBuffer, answer)) != PN7150ClassStatusOk)
		return (ret);
	if ((ret = this->_wireReceive(answer, TIMEOUT_1S)) != PN7150ClassStatusOk)
		return (ret);
	if (answer->ndef.header.unknown != PN7150_CLASS_NDEF || answer->ndef.header.cmd != PN7150_CLASS_NDEF_CMD)
		return (PN7150ClassStatusHeader);
	if (memcmp(&SW1SW2, &answer->buffer[sizeof(answer->ndef.header) + answer->ndef.header.len - sizeof(SW1SW2)], sizeof(SW1SW2)) != 0x0)
		return (PN7150ClassStatusFailedStatus);
	// switch (answer->ndef.parameters[0x0]) {//tag-len-value
	// 	case PN7150_CLASS_NDEF_TAG_FCI:
	// 		if (memcmp(&SW1SW2, &answer->buffer[sizeof(answer->ndef.header) + answer->ndef.header.len - sizeof(SW1SW2)], sizeof(SW1SW2)) != 0x0)
	// 			return (PN7150ClassStatusHeader);
	// 		break ;
	// 	default:
	// 		break ;
	// }
	return (PN7150ClassStatusOk);
}

PN7150ClassStatus_t PN7150Class::_NxpNci_HostTransceive(const void *pBuffer, PN7150ClassCmdRspCommon_t *answer) {
	PN7150ClassStatus_t							ret;
	const PN7150ClassCmdHeader_t				*header;

	if ((ret = this->_transceive(pBuffer, answer)) != PN7150ClassStatusOk)
		return (ret);
	header = (const PN7150ClassCmdHeader_t *)pBuffer;
	if (answer->rsp.header.unknown != (header->unknown + 0x20))
		return (PN7150ClassStatusHeader);
	if (answer->rsp.header.cmd != header->cmd)
		return (PN7150ClassStatusHeader);
	if (answer->rsp.status != PN7150_CLASS_GENERIC_STATUS_OK)
		return (PN7150ClassStatusHeader);
	return (PN7150ClassStatusOk);
}

PN7150ClassStatus_t PN7150Class::_wireReceive(PN7150ClassCmdRspCommon_t *answer, ssize_t timeout) {
	PN7150ClassStatus_t						ret;

	if ((ret = this->_wireReceive_add(answer, timeout)) != PN7150ClassStatusOk)
		return (ret);
	#ifdef PN7150_CLASS_DEBUG
	PN7150_CLASS_DEBUG.print("NCI << ");
	PN7150_CLASS_DEBUG.dumpPrint((uint8_t *)answer, (sizeof(answer->rsp.header) + answer->rsp.header.len), (sizeof(answer->rsp.header) + answer->rsp.header.len));
	#endif // PN7150_CLASS_DEBUG
	return (PN7150ClassStatusOk);
}

PN7150ClassStatus_t PN7150Class::_wireReceive_add(void *pBuffer, ssize_t timeout) {
	PN7150ClassStatus_t						ret;
	PN7150ClassCmdHeader_t					*header;
	size_t									tempos;

	if ((ret = this->_WaitForReceive(timeout)) != PN7150ClassStatusOk)
		return (ret);
	// /* Workaround of an issue preventing read after write */
	// for(uint8_t i=0; i<100; i++) asm("nop");
	if (this->_wireReceiveRead(pBuffer, sizeof(PN7150ClassCmdHeader_t)) != sizeof(PN7150ClassCmdHeader_t))
		return (PN7150ClassStatusI2cReceive);
	header = (PN7150ClassCmdHeader_t *)pBuffer;
	if ((tempos = header->len) == 0x0)
		return (PN7150ClassStatusOk);
	if (this->_wireReceiveRead((uint8_t *)pBuffer + sizeof(PN7150ClassCmdHeader_t), tempos) != tempos)
		return (PN7150ClassStatusI2cReceive);
	return (PN7150ClassStatusOk);
}

size_t PN7150Class::_wireReceiveRead(void *pBuffer, size_t BufferLen) {
	size_t									i;
	uint8_t									*b;

	if (this->_wire->requestFrom((int)this->_addr, (int)BufferLen) == 0x0)
		return (0x0);
	i = 0x0;
	b = (uint8_t *)pBuffer;
	while(this->_wire->available()) {
		if(BufferLen == 0)
			break ;
		b[i] = this->_wire->read();
		i++;
		BufferLen--; 
		
	}
	return (i);
}

PN7150ClassStatus_t PN7150Class::_WaitForReceive(ssize_t timeout) {
	delay(0x1);
	if (timeout == 0) {
		while (digitalRead(this->_irq) == LOW)
			delay(0x1);
	}
	else {
		while (digitalRead(this->_irq) == LOW) {
			delay(0xA);
			timeout -= 10;
			if (timeout <= 0)
				return (PN7150ClassStatusReceiveTimeout);
		}
	}
	return (PN7150ClassStatusOk);
}

PN7150ClassStatus_t PN7150Class::_wireSend(const void *pBuffer, size_t BufferLen) {
	// /* Workaround of an issue preventing write after read */
	// for(uint8_t i=0; i<100; i++) asm("nop");

	if (this->_wire->transfer(this->_addr, (void *)pBuffer, BufferLen) != WIRE_ERORR_TRANSMISSION_SUCCESS)
	{
		delay(0xA);
		if (this->_wire->transfer(this->_addr, (void *)pBuffer, BufferLen) != WIRE_ERORR_TRANSMISSION_SUCCESS)
			return (PN7150ClassStatusI2cSend);
	}
	#ifdef PN7150_CLASS_DEBUG
	PN7150_CLASS_DEBUG.print("NCI >> ");
	PN7150_CLASS_DEBUG.dumpPrint((uint8_t *)pBuffer, BufferLen, BufferLen);
	#endif // PN7150_CLASS_DEBUG
	return (PN7150ClassStatusOk);
}