#include "PN7160.h"
#include "Status.h"

#ifdef LOGGING_DBG
	#ifndef LOGGING_UART
		#define PN7160_CLASS_DEBUG					Serial0
	#else
		#define PN7160_CLASS_DEBUG					LOGGING_UART
	#endif
#endif

#define PN7160_CLASS_TIMEOUT_INFINITE					0
#define PN7160_CLASS_TIMEOUT_100MS						100
#define PN7160_CLASS_TIMEOUT_200MS						200
#define PN7160_CLASS_TIMEOUT_1S							1000
#define PN7160_CLASS_TIMEOUT_2S							2000

typedef struct								PN7160ClassRfDiscoveryCmdParameters_s
{
	uint8_t									mode_tech;
	uint8_t									freq;
}											PN7160ClassRfDiscoveryCmdParameters_t;

typedef struct								PN7160ClassRfDiscoveryCmd_s
{
	PN7160ClassHeader_t						header;
	uint8_t									NumberofParameters;
	PN7160ClassRfDiscoveryCmdParameters_t	parameters[0x4];
}											PN7160ClassRfDiscoveryCmd_t;

typedef struct								PN7160ClassProprietarySetPowerModeCmd_s
{
	PN7160ClassHeader_t						header;
	uint8_t									mode;
}											PN7160ClassProprietarySetPowerModeCmd_t;

typedef struct								PN7160ClassCoreInitCmdV1_s
{
	PN7160ClassHeader_t						header;
}											PN7160ClassCoreInitCmdV1_t;

typedef struct								PN7160ClassCoreInitCmdV2_s
{
	PN7160ClassHeader_t						header;
	uint8_t									Feature_Enable[0x2];//zero
}											PN7160ClassCoreInitCmdV2_t;

typedef struct					PN7160ClassNdefCmd_s
{
	PN7160ClassHeader_t			header;
	uint8_t						cla;
	uint8_t						ins;
	uint8_t						p1;
	uint8_t						p2;
	uint8_t						lc;
	uint8_t						value[];//tag-len-value
}								PN7160ClassNdefCmd_t;


typedef struct					PN7160ClassNdefReadRecords_s
{
	PN7160ClassHeader_t			header;
	uint8_t						cla;
	uint8_t						ins;
	uint8_t						p1;
	uint8_t						p2;
	uint8_t						le;
}								PN7160ClassNdefReadRecords_t;

typedef struct					PN7160ClassNdefAfl_s
{
	uint8_t						sfi;// Short file identifier
	uint8_t						srec;// номер первой записи SFI
	uint8_t						erec;// номер последней записи SFI
	uint8_t						number;// (Offline Data Authentication), т.е. для проверки подлинности карты.
}								PN7160ClassNdefAfl_t;


#define PN7160_CLASS_NDEF							0x0
#define PN7160_CLASS_NDEF_CMD						0x0

#define PN7160_CLASS_NDEF_TAG_APPLICATION_DEDICATED_FILE_NAME				0x4F
#define PN7160_CLASS_NDEF_TAG_APPLICATION_DEDICATED_FILE_NAME_SIZE_MAX		0x10

#define PN7160_CLASS_NDEF_TAG_APPLICATION_LABEL								0x50
#define PN7160_CLASS_NDEF_TAG_APPLICATION_LABEL_SIZE_MAX					0x10

#define PN7160_CLASS_NDEF_TAG_FCI											0x6F
#define PN7160_CLASS_NDEF_TAG_FCI_SIZE_MAX									0xFC

#define PN7160_CLASS_NDEF_TAG_AFL											0x94

#define PN7160_CLASS_NDEF_TAG_PAN											0x57
#define PN7160_CLASS_NDEF_TAG_PAN_V2										0x9F, 0x6B
#define PN7160_CLASS_NDEF_TAG_PAN_SIZE_NUMBER								0x8
#define PN7160_CLASS_NDEF_TAG_PAN_SIZE_DATE									0x2
#define PN7160_CLASS_NDEF_TAG_PAN_SIZE_DATE_TEST							0xD0
#define PN7160_CLASS_NDEF_TAG_PAN_SIZE_MAX									0x13

#define PN7160_CLASS_NDEF_TAG_PDOL											0x9F, 0x38

#define PN7160_CLASS_NDEF_TAG_TTQ											0x9F, 0x66

typedef struct					PN7160ClassNdef_s
{
	PN7160ClassHeader_t			header;
	uint8_t						value[];//tag-len-value
}								PN7160ClassNdef_t;

#define PN7160_CLASS_NDEF_DEFAULT(...)												\
{																					\
	PN7160_CLASS_NDEF,																\
	PN7160_CLASS_NDEF_CMD,															\
	sizeof((uint8_t []){__VA_ARGS__}),												\
	__VA_ARGS__																	\
}																					\

//EMV Book 1 Version 4.3 - 11.3.2
#define PN7160_CLASS_NDEF_SELECT_PSE																				\
	0x0,/* CLA */																									\
	0xA4,/* INS */																									\
	0x4,/* P1 - Select by name */																					\
	0x0,/* P2 - First or only occurrence */																			\
	0xE,/* Lc - Length data */																						\
	0x32, 0x50, 0x41, 0x59, 0x2E, 0x53, 0x59, 0x53, 0x2E, 0x44, 0x44, 0x46, 0x30, 0x31,/* 2PAY. SYS.DDF01 */		\
	0x0/* Le */																										\

//EMV Book 1 Version 4.3 - 11.3.2
#define PN7160_CLASS_NDEF_SELECT_PSE_ADF()											\
{																					\
	{																				\
		.gid = PN7160_CLASS_NDEF,												\
		.oid = PN7160_CLASS_NDEF_CMD,												\
		.len = 0x0																	\
	},																				\
	.cla = 0x0,																		\
	.ins = 0xA4,																	\
	.p1 = 0x4,/* P1 - Select by name */												\
	.p2 = 0x0,																		\
	.lc = 0x0																		\
}																					\

//EMV Book 3 Version 4.3 - 6.5.8 
#define PN7160_CLASS_NDEF_GET_PROCESSING_OPTIONS_DEFAULT()							\
{																					\
	{																				\
		.gid = PN7160_CLASS_NDEF,												\
		.oid = PN7160_CLASS_NDEF_CMD,												\
		.len = 0x0																	\
	},																				\
	.cla = 0x80,																	\
	.ins = 0xA8,																	\
	.p1 = 0x0,																		\
	.p2 = 0x0,																		\
	.lc = 0x0																		\
}																					\


//EMV Book 3 Version 4.3 - 6.5.11 
#define PN7160_CLASS_NDEF_READ_RECORDS_DEFAULT(record_number, sfi)					\
{																					\
	{																				\
		.gid = PN7160_CLASS_NDEF,												\
		.oid = PN7160_CLASS_NDEF_CMD,												\
		.len = (sizeof(PN7160ClassNdefReadRecords_t) - sizeof(PN7160ClassHeader_t))	\
	},																				\
	.cla = 0x0,																		\
	.ins = 0xB2,																	\
	.p1 = record_number,															\
	.p2 = (uint8_t)(sfi | 0x4),/* 0x4 - P1 is a record number*/						\
	.le = 0x0																		\
}																					\

#define PN7160_CLASS_RF_DEACTIVATE_MODE_IDLE			0x0
#define PN7160_CLASS_RF_DEACTIVATE_MODE_SLEEP			0x1
#define PN7160_CLASS_RF_DEACTIVATE_MODE_SLEEP_AF		0x2
#define PN7160_CLASS_RF_DEACTIVATE_MODE_DISCOVERY		0x3

typedef struct								PN7160ClassRfDiscoverSelectCmd_s
{
	PN7160ClassHeader_t						header;
	uint8_t									DiscoveryID;
	uint8_t									protocol;
	uint8_t									interface;
}											PN7160ClassRfDiscoverSelectCmd_t;

typedef struct								PN7160ClassCoreGetConfigCmd_s
{
	PN7160ClassHeader_t						header;
	uint8_t									NumberofParameters;
	uint8_t									parametrs[];
}											PN7160ClassCoreGetConfigCmd_t;

typedef struct								PN7160ClassCoreSetConfigEepromCmd_s
{
	PN7160ClassHeader_t						header;
	uint8_t									NumberofParameters;
	uint8_t									sub;
	uint8_t									sub_add;
	uint8_t									sub_len;
	PN7160ClassEeprom_t						eeprom;
}											PN7160ClassCoreSetConfigEepromCmd_t;

typedef struct								PN7160ClassCoreSetConfigTotalDurationCmd_s
{
	PN7160ClassHeader_t						header;
	uint8_t									NumberofParameters;
	uint8_t									sub;
	uint8_t									sub_len;
	uint8_t									ms[0x2];/* LSB  to MSB */
}											PN7160ClassCoreSetConfigTotalDurationCmd_t;

#define PN7160_CLASS_CORE_GET_CONFIG_CMD_DEFAULT(...)								\
{																					\
	(PN7160_CLASS_GID_CMD | PN7160_CLASS_GID_CORE),									\
	PN7160_CLASS_OID_CORE_GET_CONFIG,												\
	(0x1 + sizeof((uint8_t []){__VA_ARGS__})),										\
	sizeof((uint8_t []){__VA_ARGS__}),												\
	__VA_ARGS__																		\
}																					\

#define PN7160_CLASS_CORE_GET_CONFIG_CMD_DEFAULT_EXT(...)							\
{																					\
	(PN7160_CLASS_GID_CMD | PN7160_CLASS_GID_CORE),									\
	PN7160_CLASS_OID_CORE_GET_CONFIG,												\
	(0x1 + sizeof((uint8_t []){__VA_ARGS__})),										\
	(sizeof((uint8_t []){__VA_ARGS__}) / 0x2),										\
	__VA_ARGS__																		\
}																					\

static const PN7160ClassRfDeactivateCmd_t			_deactivate_sleep =
{
	.header =
	{
		.gid = (PN7160_CLASS_GID_CMD | PN7160_CLASS_GID_RF),
		.oid = (PN7160_CLASS_OID_RF_DEACTIVATE),
		.len = (sizeof(_deactivate_sleep) - sizeof(_deactivate_sleep.header)),
	},
	.mode = PN7160_CLASS_RF_DEACTIVATE_MODE_SLEEP
};
static const uint16_t SW1SW2 = 0x0090;

/* Public Constructors */
PN7160Class::PN7160Class(void (*event_irq)(void), TwoWire *wire, uint8_t scl, uint8_t sda, uint8_t irq, uint8_t ven, uint8_t addr):
			_event_irq(event_irq), _wire(wire), _scl(scl), _sda(sda), _irq(irq), _ven(ven), _addr(addr), _mode(0x0), _irq_status(false)
{
	this->_rf_nfc.count = 0x0;
	this->_rf_nfc.index = 0x0;
	memset(&this->_Manufacturer_Specific_Information, 0x0, sizeof(this->_Manufacturer_Specific_Information));
}


/* Public Methods */
uint8_t PN7160Class::ppseExpirationDate(uint8_t index, void *buffer, uint8_t len) {
	size_t							count;
	void							*b;
	PN7160ClassRfNfc_t				*rf_nfc;

	if ((rf_nfc = this->_getInfo(index)) == 0x0) {
		b = 0x0;
		count = 0x0;
	}
	else {
		switch(rf_nfc->protocol) {
			case (PN7160_CLASS_PROT_ISODEP):
				b = &rf_nfc->cart.cart_tag4.panDate[0x0];
				count = rf_nfc->cart.cart_tag4.panDateSize;
				break ;
			default:
				b = 0x0;
				count = 0x0;
				break ;
		}
	}
	return (this->_info_finish(buffer, b, count, len));
}

uint8_t PN7160Class::ppseCardNumber(uint8_t index, void *buffer, uint8_t len) {
	size_t							count;
	void							*b;
	PN7160ClassRfNfc_t				*rf_nfc;

	if ((rf_nfc = this->_getInfo(index)) == 0x0) {
		b = 0x0;
		count = 0x0;
	}
	else {
		switch(rf_nfc->protocol) {
			case (PN7160_CLASS_PROT_ISODEP):
				b = &rf_nfc->cart.cart_tag4.panNumber[0x0];
				count = rf_nfc->cart.cart_tag4.panNumberSize;
				break ;
			default:
				b = 0x0;
				count = 0x0;
				break ;
		}
	}
	return (this->_info_finish(buffer, b, count, len));
}

uint8_t PN7160Class::ppsePaymentSystem(uint8_t index, void *buffer, uint8_t len) {
	size_t							count;
	void							*b;
	PN7160ClassRfNfc_t				*rf_nfc;

	if ((rf_nfc = this->_getInfo(index)) == 0x0) {
		b = 0x0;
		count = 0x0;
	}
	else {
		switch(rf_nfc->protocol) {
			case (PN7160_CLASS_PROT_ISODEP):
				b = &rf_nfc->cart.cart_tag4.ApplicationLabel[0x0];
				count = rf_nfc->cart.cart_tag4.ApplicationLabelSize;
				break ;
			default:
				b = 0x0;
				count = 0x0;
				break ;
		}
	}
	return (this->_info_finish(buffer, b, count, len));
}

bool PN7160Class::ppse(uint8_t index) {
	static const uint8_t							select_pse[] = PN7160_CLASS_NDEF_DEFAULT(PN7160_CLASS_NDEF_SELECT_PSE);
	static const PN7160ClassNdefCmd_t				select_adf = PN7160_CLASS_NDEF_SELECT_PSE_ADF();
	static const PN7160ClassNdefCmd_t				get_processing_options = PN7160_CLASS_NDEF_GET_PROCESSING_OPTIONS_DEFAULT();
	static const uint8_t							tag_application_label[] = {PN7160_CLASS_NDEF_TAG_APPLICATION_LABEL};
	static const uint8_t							tag_adf[] = {PN7160_CLASS_NDEF_TAG_APPLICATION_DEDICATED_FILE_NAME};
	static const uint8_t							tag_pdol[] = {PN7160_CLASS_NDEF_TAG_PDOL};
	static const uint8_t							tag_ttq[] = {PN7160_CLASS_NDEF_TAG_TTQ};
	static const uint8_t							tag_pan[] = {PN7160_CLASS_NDEF_TAG_PAN};
	static const uint8_t							tag_pan_v2[] = {PN7160_CLASS_NDEF_TAG_PAN_V2};
	static const uint8_t							tag_afl[] = {PN7160_CLASS_NDEF_TAG_AFL};
	PN7160ClassRfNfc_t								*rf_nfc;
	PN7160ClassAnswer_t								answer;
	PN7160ClassNdefReadRecords_t					read_records;
	union
	{
		PN7160ClassNdefCmd_t						ndef_cmd;
		uint8_t										buffer[PN7160_CLASS_MAX_NCI_FRAME_SIZE];
	};
	size_t											len;
	size_t											srec;
	size_t											len_tag;
	size_t											len_data;
	const uint8_t									*b;
	const uint8_t									*e;
	const PN7160ClassNdefAfl_t						*b_afl;
	const PN7160ClassNdefAfl_t						*e_afl;

	if ((rf_nfc = this->_getInfo(index)) == 0x0)
		return (this->_lastStatus((STATUS_CONSTRUCTOR(STATUS_SEV_ERROR, STATUS_FACILITY_PN160, STATUS_BAD_ARGUMENTS)), false));
	if (rf_nfc->protocol != PN7160_CLASS_PROT_ISODEP)
		return (this->_lastStatus((STATUS_CONSTRUCTOR(STATUS_SEV_ERROR, STATUS_FACILITY_PN160, STATUS_BAD_ARGUMENTS)), false));
	if (this->_select(&answer, rf_nfc) != true)
		return (false);
	if (this->_readerTag(&select_pse, &answer) != true)
		return (false);
	ndef_cmd = select_adf;
	if ((len = this->_tagGetData(this->_tagFind((const PN7160ClassTlvTag_t *)&tag_adf[0x0], &answer), &ndef_cmd.value[0x0], PN7160_CLASS_NDEF_TAG_APPLICATION_DEDICATED_FILE_NAME_SIZE_MAX)) == 0x0)
		return (this->_lastStatus((PN7160_CLASS_STATUS_PPSE), false));
	ndef_cmd.lc = len;
	ndef_cmd.value[len] = 0x0;//Le
	ndef_cmd.header.len = (sizeof(ndef_cmd) - sizeof(ndef_cmd.header)) + len + 0x1;//+0x1 - le
	if (this->_readerTag(&ndef_cmd, &answer) != true)
		return (false);
	rf_nfc->cart.cart_tag4.ApplicationLabelSize = this->_tagGetData(this->_tagFind((const PN7160ClassTlvTag_t *)&tag_application_label[0x0], &answer), &rf_nfc->cart.cart_tag4.ApplicationLabel[0x0], sizeof(rf_nfc->cart.cart_tag4.ApplicationLabel));
	ndef_cmd = get_processing_options;
	ndef_cmd.value[0x0] = 0x83;
	len = 0x2;
	if ((b = (const uint8_t *)this->_tagFind((const PN7160ClassTlvTag_t *)&tag_pdol[0x0], &answer)) != 0x0) {
		e = b + b[sizeof(tag_pdol)] + sizeof(tag_pdol) + 0x1;//+0x1 - len
		b = b + sizeof(tag_pdol) + 0x1;//+0x1 - len
		while (b < e) {
			len_tag = this->_tagGetLen((const PN7160ClassTlvTag_t *)b);
			len_data = b[len_tag];
			if (len_tag == sizeof(tag_ttq) && memcmp(b, &tag_ttq[0x0], sizeof(tag_ttq)) == 0x0) {
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
	if (this->_readerTag(&ndef_cmd, &answer) != true)
		return (false);
	rf_nfc->cart.cart_tag4.panNumberSize = 0x0;
	rf_nfc->cart.cart_tag4.panDateSize = 0x0;
	if (this->_ppsePan((const PN7160ClassTlvTag_t *)&tag_pan[0x0], sizeof(tag_pan), rf_nfc, &answer) == true || this->_ppsePan((const PN7160ClassTlvTag_t *)&tag_pan_v2[0x0], sizeof(tag_pan_v2), rf_nfc, &answer) == true)
		;
	else if ((b = (const uint8_t *)this->_tagFind((const PN7160ClassTlvTag_t *)&tag_afl, &answer)) != 0x0) {
		len_tag = this->_tagGetLen((const PN7160ClassTlvTag_t *)b);
		b = b + len_tag + 0x1;//+1 - len
		b_afl = (const PN7160ClassNdefAfl_t *)b;
		e_afl = (const PN7160ClassNdefAfl_t *)(b + b[-1]);
		read_records = PN7160_CLASS_NDEF_READ_RECORDS_DEFAULT(0x0, 0x0);
		while (b_afl < e_afl) {
			read_records.p2 = b_afl->sfi | 0x4;
			srec = b_afl->srec;
			while (srec <= b_afl->erec) {
				read_records.p1 = srec++;
				if (this->_readerTag(&read_records, (PN7160ClassAnswer_t *)&buffer[0x0]) == true) {
					if (this->_ppsePan((const PN7160ClassTlvTag_t *)&tag_pan[0x0], sizeof(tag_pan), rf_nfc, (PN7160ClassAnswer_t *)&buffer[0x0]) == true || this->_ppsePan((const PN7160ClassTlvTag_t *)&tag_pan_v2[0x0], sizeof(tag_pan_v2), rf_nfc, (PN7160ClassAnswer_t *)&buffer[0x0]) == true) {
						b_afl = e_afl;
						break ;
					}
				}
			}
			b_afl++;
		}
	}
	return (this->_lastStatus(STATUS_SUCCESS, true));
}


bool PN7160Class::discoveryRestart(void) {
	static const PN7160ClassRfDeactivateCmd_t		deactivate_idle =
	{
		.header =
		{
			.gid = (PN7160_CLASS_GID_CMD | PN7160_CLASS_GID_RF),
			.oid = (PN7160_CLASS_OID_RF_DEACTIVATE),
			.len = (sizeof(deactivate_idle) - sizeof(deactivate_idle.header)),
		},
		.mode = PN7160_CLASS_RF_DEACTIVATE_MODE_IDLE
	};
	PN7160ClassAnswer_t								answer;

	while (this->_wireReceive(&answer, PN7160_CLASS_TIMEOUT_100MS) == true)
		;
	if (this->_transceiveRsp(&deactivate_idle, &answer) == true)//Если еще карточка в зоне - то деактивируем
		this->_wireReceive(&answer, PN7160_CLASS_TIMEOUT_1S);
	return (this->discovery());
}

void PN7160Class::infoWaitRemoval(void (*userFunc)(uint8_t)) {
	PN7160ClassAnswer_t								answer;
	static const size_t								delay_period = 100;
	PN7160ClassRfNfc_t								*rf_nfc;
	PN7160ClassRfNfc_t								*rf_nfc_e;
	size_t											count;

	rf_nfc = &this->_rf_nfc.rf_nfc[0x0];
	rf_nfc_e = &this->_rf_nfc.rf_nfc[this->_rf_nfc.count];
	count = 0x0;
	while (rf_nfc < rf_nfc_e) {
		if (rf_nfc->protocol != PN7160_CLASS_PROT_UNDETERMINED)
			count++;
		rf_nfc++;
	}
	if (count == 0x0)
		return ;
	while (count != 0x0) {
		if (rf_nfc >= rf_nfc_e)
			rf_nfc = &this->_rf_nfc.rf_nfc[0x0];
		if (rf_nfc == &this->_rf_nfc.rf_nfc[0x0])
			delay(delay_period);
		if (rf_nfc->protocol != PN7160_CLASS_PROT_UNDETERMINED) {
			if (this->_rfRemoval(&answer, rf_nfc) == true) {
				if (userFunc != 0x0)
					userFunc(rf_nfc->protocol);
				count--;
				rf_nfc->protocol = PN7160_CLASS_PROT_UNDETERMINED;
			}
		}
		rf_nfc++;
	}
	return ;
}

uint8_t PN7160Class::infoDsfid(uint8_t index, void *buffer, uint8_t len) {
	size_t							count;
	void							*b;
	PN7160ClassRfNfc_t				*rf_nfc;

	if ((rf_nfc = this->_getInfo(index)) == 0x0) {
		b = 0x0;
		count = 0x0;
	}
	else {
		switch(rf_nfc->mode_tech) {
			case (PN7160_CLASS_MODE_POLL | PN7160_CLASS_TECH_PASSIVE_15693):
				b = &rf_nfc->parameters.vpp.DSFID;
				count = sizeof(rf_nfc->parameters.vpp.DSFID);
			break ;
			case (PN7160_CLASS_MODE_POLL | PN7160_CLASS_TECH_PASSIVE_NFCA):
			case (PN7160_CLASS_MODE_POLL | PN7160_CLASS_TECH_PASSIVE_NFCB):
			case (PN7160_CLASS_MODE_POLL | PN7160_CLASS_TECH_PASSIVE_NFCF):
			default:
				b = 0x0;
				count = 0x0;
				break ;
		}
	}
	return (this->_info_finish(buffer, b, count, len));
}

uint8_t PN7160Class::infoAfi(uint8_t index, void *buffer, uint8_t len) {
	size_t							count;
	void							*b;
	PN7160ClassRfNfc_t				*rf_nfc;

	if ((rf_nfc = this->_getInfo(index)) == 0x0) {
		b = 0x0;
		count = 0x0;
	}
	else {
		switch(rf_nfc->mode_tech) {
			case (PN7160_CLASS_MODE_POLL | PN7160_CLASS_TECH_PASSIVE_15693):
				b = &rf_nfc->parameters.vpp.AFI;
				count = sizeof(rf_nfc->parameters.vpp.AFI);
			break ;
			case (PN7160_CLASS_MODE_POLL | PN7160_CLASS_TECH_PASSIVE_NFCA):
			case (PN7160_CLASS_MODE_POLL | PN7160_CLASS_TECH_PASSIVE_NFCB):
			case (PN7160_CLASS_MODE_POLL | PN7160_CLASS_TECH_PASSIVE_NFCF):
			default:
				b = 0x0;
				count = 0x0;
				break ;
		}
	}
	return (this->_info_finish(buffer, b, count, len));
}

uint8_t PN7160Class::infoId(uint8_t index, void *buffer, uint8_t len) {
	size_t							count;
	void							*b;
	PN7160ClassRfNfc_t				*rf_nfc;

	if ((rf_nfc = this->_getInfo(index)) == 0x0) {
		b = 0x0;
		count = 0x0;
	}
	else {
		switch(rf_nfc->mode_tech) {
			case (PN7160_CLASS_MODE_POLL | PN7160_CLASS_TECH_PASSIVE_15693):
				b = &rf_nfc->parameters.vpp.ID[0x0];
				count = sizeof(rf_nfc->parameters.vpp.ID);
			break ;
			case (PN7160_CLASS_MODE_POLL | PN7160_CLASS_TECH_PASSIVE_NFCA):
			case (PN7160_CLASS_MODE_POLL | PN7160_CLASS_TECH_PASSIVE_NFCB):
			case (PN7160_CLASS_MODE_POLL | PN7160_CLASS_TECH_PASSIVE_NFCF):
			default:
				b = 0x0;
				count = 0x0;
				break ;
		}
	}
	return (this->_info_finish(buffer, b, count, len));
}

uint16_t PN7160Class::infoBitRate(uint8_t index) {
	uint16_t						value;
	PN7160ClassRfNfc_t				*rf_nfc;

	if ((rf_nfc = this->_getInfo(index)) == 0x0)
		value = 0x0;
	else {
		switch(rf_nfc->mode_tech) {
			case (PN7160_CLASS_MODE_POLL | PN7160_CLASS_TECH_PASSIVE_NFCF):
				value = (rf_nfc->parameters.fpp.BitRate == 0x1) ? 212 : 424;
				break ;
			case (PN7160_CLASS_MODE_POLL | PN7160_CLASS_TECH_PASSIVE_NFCA):
			case (PN7160_CLASS_MODE_POLL | PN7160_CLASS_TECH_PASSIVE_NFCB):
			case (PN7160_CLASS_MODE_POLL | PN7160_CLASS_TECH_PASSIVE_15693):
			default:
				value = 0x0;
				break ;
		}
	}
	return (value);
}

uint8_t PN7160Class::infoSel(uint8_t index, void *buffer, uint8_t len) {
	size_t							count;
	void							*b;
	uint8_t							*tmp;
	PN7160ClassRfNfc_t				*rf_nfc;

	if ((rf_nfc = this->_getInfo(index)) == 0x0) {
		b = 0x0;
		count = 0x0;
	}
	else {
		switch(rf_nfc->mode_tech) {
			case (PN7160_CLASS_MODE_POLL | PN7160_CLASS_TECH_PASSIVE_NFCA):
				tmp = &rf_nfc->parameters.app.NfcId[rf_nfc->parameters.app.NfcIdLen];
				b = tmp + 0x1;
				count = tmp[0x0];
			break ;
			case (PN7160_CLASS_MODE_POLL | PN7160_CLASS_TECH_PASSIVE_NFCB):
			case (PN7160_CLASS_MODE_POLL | PN7160_CLASS_TECH_PASSIVE_NFCF):
			case (PN7160_CLASS_MODE_POLL | PN7160_CLASS_TECH_PASSIVE_15693):
			default:
				b = 0x0;
				count = 0x0;
				break ;
		}
	}

	return (this->_info_finish(buffer, b, count, len));
}


uint8_t PN7160Class::infoNfcid(uint8_t index, void *buffer, uint8_t len) {
	size_t							count;
	void							*b;
	PN7160ClassRfNfc_t				*rf_nfc;

	if ((rf_nfc = this->_getInfo(index)) == 0x0) {
		b = 0x0;
		count = 0x0;
	}
	else {
		switch(rf_nfc->mode_tech) {
			case (PN7160_CLASS_MODE_POLL | PN7160_CLASS_TECH_PASSIVE_NFCA):
				b = &rf_nfc->parameters.app.NfcId[0x0];
				count = rf_nfc->parameters.app.NfcIdLen;
			break ;
			case (PN7160_CLASS_MODE_POLL | PN7160_CLASS_TECH_PASSIVE_NFCB):
			case (PN7160_CLASS_MODE_POLL | PN7160_CLASS_TECH_PASSIVE_NFCF):
			case (PN7160_CLASS_MODE_POLL | PN7160_CLASS_TECH_PASSIVE_15693):
			default:
				b = 0x0;
				count = 0x0;
				break ;
		}
	}
	return (this->_info_finish(buffer, b, count, len));
}

uint8_t PN7160Class::infoSens(uint8_t index, void *buffer, uint8_t len) {
	size_t							count;
	void							*b;
	PN7160ClassRfNfc_t				*rf_nfc;

	if ((rf_nfc = this->_getInfo(index)) == 0x0) {
		b = 0x0;
		count = 0x0;
	}
	else {
		switch(rf_nfc->mode_tech) {
			case (PN7160_CLASS_MODE_POLL | PN7160_CLASS_TECH_PASSIVE_NFCA):
				b = &rf_nfc->parameters.app.SensRes[0x0];
				count = sizeof(rf_nfc->parameters.app.SensRes);
			break ;
			case (PN7160_CLASS_MODE_POLL | PN7160_CLASS_TECH_PASSIVE_NFCB):
				b = &rf_nfc->parameters.bpp.SensRes[0x0];
				count = rf_nfc->parameters.bpp.SensResLen;
				break ;
			case (PN7160_CLASS_MODE_POLL | PN7160_CLASS_TECH_PASSIVE_NFCF):
				b = &rf_nfc->parameters.fpp.SensRes[0x0];
				count = rf_nfc->parameters.fpp.SensResLen;
				break ;
			case (PN7160_CLASS_MODE_POLL | PN7160_CLASS_TECH_PASSIVE_15693):
			default:
				b = 0x0;
				count = 0x0;
				break ;
		}
	}
	return (this->_info_finish(buffer, b, count, len));
}

uint8_t PN7160Class::infoProtocol(uint8_t index) {
	PN7160ClassRfNfc_t												*rf_nfc;

	if ((rf_nfc = this->_getInfo(index)) == 0x0)
		return (PN7160_CLASS_PROT_UNDETERMINED);
	return (rf_nfc->protocol);
}

uint8_t PN7160Class::info(void) {
	this->_info();
	return (this->_rf_nfc.count);
}

void PN7160Class::eventIrq(void) {
	if (this->_irq_status == true)
		return ;
	detachInterrupt(this->_irq);
	this->_irq_status = true;
}

bool PN7160Class::discovery() {
	static const PN7160ClassRfDiscoveryCmd_t				rf_discovery =
	{
		.header =
		{
			.gid = (PN7160_CLASS_GID_CMD | PN7160_CLASS_GID_RF),
			.oid = (PN7160_CLASS_OID_RF_DISCOVER),
			.len = (sizeof(rf_discovery) - sizeof(rf_discovery.header)),
		},
		.NumberofParameters = (sizeof(rf_discovery.parameters) / sizeof(rf_discovery.parameters[0x0])),
		.parameters =
		{
			{
				.mode_tech = (PN7160_CLASS_MODE_POLL | PN7160_CLASS_TECH_PASSIVE_NFCA),
				.freq = 0x1
			},
			{
				.mode_tech = (PN7160_CLASS_MODE_POLL | PN7160_CLASS_TECH_PASSIVE_NFCB),
				.freq = 0x1
			},
			{
				.mode_tech = (PN7160_CLASS_MODE_POLL | PN7160_CLASS_TECH_PASSIVE_NFCF),
				.freq = 0x1
			},
			{
				.mode_tech = (PN7160_CLASS_MODE_POLL | PN7160_CLASS_TECH_PASSIVE_15693),
				.freq = 0x1
			}
		}
	};
	PN7160ClassAnswer_t										answer;

	if (this->_transceiveRsp(&rf_discovery, &answer) != true)
		return (false);
	this->_irq_status = false;
	if (attachInterrupt(this->_irq, this->_event_irq, RISING) != ZunoErrorOk)
		return (this->_lastStatus(STATUS_TMP_FOR_REPLACE, false));
	if (digitalRead(this->_irq) == HIGH)
		this->_event_irq();
	return (this->_lastStatus(STATUS_SUCCESS, true));
}

/* settings are not versatile, so configuration only applied if there are changes (application build timestamp) 
	or in case of PN7150B0HN/C11004 Anti-tearing recovery procedure inducing RF setings were restored to their default value */
bool PN7160Class::setCore(void) {
	static const uint8_t											NxpNci_CORE_CONF_EXTN[] =
	{
		0x20, 0x02, 0x05, 0x01,/* CORE_SET_CONFIG_CMD */
		0xA0, 0x40, 0x01, 0x00/* TAG_DETECTOR_CFG */
	};
	static const uint8_t											NxpNci_CLK_CONF[]=
	{
		0x20, 0x02, 0x05, 0x01,/* CORE_SET_CONFIG_CMD */
		0xA0, 0x03, 0x01, 0x08/* CLOCK_SEL_CFG */
	};
	PN7160ClassAnswer_t												answer;

	if (this->_transceiveRsp(&NxpNci_CORE_CONF_EXTN[0x0], &answer) != true)
		return (false);
	if (this->_transceiveRsp(&NxpNci_CLK_CONF[0x0], &answer) != true)
		return (false);
	return (this->_lastStatus(STATUS_SUCCESS, true));
}

/* settings are not versatile, so configuration only applied if there are changes (application build timestamp) 
	or in case of PN7150B0HN/C11004 Anti-tearing recovery procedure inducing RF setings were restored to their default value */
bool PN7160Class::setRf(void) {
	static const uint8_t											NxpNci_RF_CONF[]=
	{
		0x20, 0x02, 0x4C, 0x09,
		0xA0, 0x0D, 0x03, 0x78, 0x0D, 0x02,
		0xA0, 0x0D, 0x03, 0x78, 0x14, 0x02,
		0xA0, 0x0D, 0x06, 0x4C, 0x44, 0x65, 0x09, 0x00, 0x00,
		0xA0, 0x0D, 0x06, 0x4C, 0x2D, 0x05, 0x35, 0x1E, 0x01,
		0xA0, 0x0D, 0x06, 0x82, 0x4A, 0x55, 0x07, 0x00, 0x07,
		0xA0, 0x0D, 0x06, 0x44, 0x44, 0x03, 0x04, 0xC4, 0x00,
		0xA0, 0x0D, 0x06, 0x46, 0x30, 0x50, 0x00, 0x18, 0x00,
		0xA0, 0x0D, 0x06, 0x48, 0x30, 0x50, 0x00, 0x18, 0x00,
		0xA0, 0x0D, 0x06, 0x4A, 0x30, 0x50, 0x00, 0x08, 0x00
	};
	PN7160ClassAnswer_t												answer;

	if (this->_transceiveRsp(&NxpNci_RF_CONF[0x0], &answer) != true)
		return (false);
	return (this->_lastStatus(STATUS_SUCCESS, true));
}

/* settings are not versatile, so configuration only applied if there are changes (application build timestamp) 
	or in case of PN7150B0HN/C11004 Anti-tearing recovery procedure inducing RF setings were restored to their default value */
bool PN7160Class::setPowerTransmitter(uint8_t mode) {
	PN7160ClassAnswer_t												answer;
	const uint8_t													*set_power_transmitter;
	static const uint8_t											set_power_transmitter_3_3V[]={0x20, 0x02, 0x0F, 0x01, 0xA0, 0x0E, 0x0B, 0x11, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0xD0, 0x0C};
	static const uint8_t											set_power_transmitter_4_75V[]={0x20, 0x02, 0x0F, 0x01, 0xA0, 0x0E, 0x0B, 0x11, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x40, 0x00, 0xD0, 0x0C};

	switch (mode) {
		case PN7160_CLASS_POWER_TRANSMITTER_3_3V:
			set_power_transmitter = &set_power_transmitter_3_3V[0x0];
			break ;
		case PN7160_CLASS_POWER_TRANSMITTER_4_75_V:
			set_power_transmitter = &set_power_transmitter_4_75V[0x0];
			break ;
		default:
			return (this->_lastStatus((STATUS_CONSTRUCTOR(STATUS_SEV_ERROR, STATUS_FACILITY_PN160, STATUS_BAD_ARGUMENTS)), false));
			break ;
	}
	if (this->_transceiveRsp(set_power_transmitter, &answer) != true)
		return (false);
	return (this->_lastStatus(STATUS_SUCCESS, true));
}

/* NCI standard dedicated settings
 * Refer to NFC Forum NCI standard for more details
 */
bool PN7160Class::setPowerMode(uint8_t mode) {
	PN7160ClassProprietarySetPowerModeCmd_t							set_power_mode;
	PN7160ClassAnswer_t												answer;

	switch (mode) {
		case PN7160_CLASS_POWER_MODE_IDLE:
		case PN7160_CLASS_POWER_MODE_STANDBY:
			break ;
		default:
			return (this->_lastStatus((STATUS_CONSTRUCTOR(STATUS_SEV_ERROR, STATUS_FACILITY_PN160, STATUS_BAD_ARGUMENTS)), false));
			break ;
	}
	set_power_mode.header.gid = (PN7160_CLASS_GID_CMD | PN7160_CLASS_GID_PROPRIETARY);
	set_power_mode.header.oid = (PN7160_CLASS_OID_PROPRIETARY_SET_POWER_MODE);
	set_power_mode.header.len = (sizeof(set_power_mode) - sizeof(set_power_mode.header));
	set_power_mode.mode = mode;
	if (this->_transceiveRsp(&set_power_mode, &answer) != true)
		return (false);
	return (this->_lastStatus(STATUS_SUCCESS, true));
}

/* NCI standard dedicated settings
 * Refer to NFC Forum NCI standard for more details
 */
bool PN7160Class::setDuration(uint16_t ms) {
	PN7160ClassAnswer_t													answer;
	PN7160ClassCoreSetConfigTotalDurationCmd_t							set_total_duration;

	if (ms > 65000 || ms < 20)
		return (this->_lastStatus((STATUS_CONSTRUCTOR(STATUS_SEV_ERROR, STATUS_FACILITY_PN160, STATUS_BAD_ARGUMENTS)), false));
	set_total_duration.header.gid = (PN7160_CLASS_GID_CMD | PN7160_CLASS_GID_CORE);
	set_total_duration.header.oid = (PN7160_CLASS_OID_CORE_SET_CONFIG);
	set_total_duration.header.len = (sizeof(set_total_duration) - sizeof(set_total_duration.header));
	set_total_duration.NumberofParameters = 0x1;
	set_total_duration.sub = PN7160_CLASS_CORE_CONFIG_PARAMETER_TOTAL_DURATION;
	set_total_duration.sub_len = sizeof(set_total_duration.ms);
	set_total_duration.ms[0x0] = ms;
	set_total_duration.ms[0x1] = ms >> 0x8;
	if (this->_transceiveRsp(&set_total_duration, &answer) != true)
		return (false);
	return (this->_lastStatus(STATUS_SUCCESS, true));
}


bool PN7160Class::setEEPROM(const PN7160ClassEeprom_t *eeprom) {
	PN7160ClassAnswer_t															answer;
	PN7160ClassCoreSetConfigEepromCmd_t											set_eeprom;

	set_eeprom.header.gid = (PN7160_CLASS_GID_CMD | PN7160_CLASS_GID_CORE);
	set_eeprom.header.oid = (PN7160_CLASS_OID_CORE_SET_CONFIG);
	set_eeprom.header.len = (sizeof(set_eeprom) - sizeof(set_eeprom.header));
	set_eeprom.NumberofParameters = 0x1;
	set_eeprom.sub = PN7160_CLASS_CORE_CONFIG_PARAMETER_TOTAL_EXT;
	set_eeprom.sub_add = PN7160_CLASS_CORE_CONFIG_PARAMETER_TOTAL_EEPROM;
	set_eeprom.sub_len = sizeof(set_eeprom.eeprom);
	memcpy(&set_eeprom.eeprom, eeprom, sizeof(set_eeprom.eeprom));
	if (this->_transceiveRsp(&set_eeprom, &answer) != true)
		return (false);
	return (this->_lastStatus(STATUS_SUCCESS, true));
}

bool PN7160Class::applySettings(void) {
	PN7160ClassAnswer_t															answer;

	if (this->_resetInit(&answer, false) != true)
		return (false);
	return (this->_lastStatus(STATUS_SUCCESS, true));
}

bool PN7160Class::getEEPROM(PN7160ClassEeprom_t *eeprom) {
	static const uint8_t														get_eeprom[] = PN7160_CLASS_CORE_GET_CONFIG_CMD_DEFAULT_EXT(PN7160_CLASS_CORE_CONFIG_PARAMETER_TOTAL_EXT, PN7160_CLASS_CORE_CONFIG_PARAMETER_TOTAL_EEPROM);
	PN7160ClassAnswer_t															answer;

	if (this->_transceiveRspCheckSize(&get_eeprom, &answer, (sizeof(answer.core_get_config_rsp) + sizeof(answer.core_get_config_rsp.parametrs->eeprom))) != true)
		return (false);
	memcpy(&eeprom->buffer[0x0], &answer.core_get_config_rsp.parametrs[0x0].eeprom.eeprom.buffer[0x0], sizeof(eeprom->buffer));
	return (this->_lastStatus(STATUS_SUCCESS, true));
}

bool PN7160Class::getDuration(uint16_t *ms) {
	static const uint8_t														get_duration[] = PN7160_CLASS_CORE_GET_CONFIG_CMD_DEFAULT(PN7160_CLASS_CORE_CONFIG_PARAMETER_TOTAL_DURATION);
	PN7160ClassAnswer_t															answer;

	if (this->_transceiveRspCheckSize(&get_duration, &answer, (sizeof(answer.core_get_config_rsp) + sizeof(answer.core_get_config_rsp.parametrs->duration))) != true)
		return (false);
	memcpy(ms, &answer.core_get_config_rsp.parametrs[0x0].duration.ms[0x0], sizeof(ms[0x0]));
	return (this->_lastStatus(STATUS_SUCCESS, true));
}

bool PN7160Class::connect(bool clear) {
	PN7160ClassAnswer_t						answer;
	size_t									i;

	if (this->_wire->begin(0x0, this->_scl, this->_sda, &this->_buffer_wire[0x0], sizeof(this->_buffer_wire)) != ZunoErrorOk)
		return (this->_lastStatus(STATUS_TMP_FOR_REPLACE, false));
	pinMode(this->_irq, INPUT_DOWN);
	pinMode(this->_ven, OUTPUT_DOWN);
	digitalWrite(this->_ven, HIGH);
	delay(0xA);
	digitalWrite(this->_ven, LOW);
	delay(0xA);
	digitalWrite(this->_ven, HIGH);
	/* Loop until NXPNCI answers */
	i = 0x0;
	while (true) {
		if (this->_resetInit(&answer, clear) == true)
			break;
		if (i++ >= 0x1)
			return (this->_lastStatus((PN7160_CLASS_STATUS_REPEAT_CHECK_DEV), false));
		delay(500);
	}
	return (this->_lastStatus(STATUS_SUCCESS, true));
}

#define REMOVE_CARDEMU_SUPPORT
#define REMOVED_CARDEMU_SUPPORT
#define REMOVE_P2P_SUPPORT

/* Private Methods */
bool PN7160Class::_ppsePan(const PN7160ClassTlvTag_t *tag, size_t len_tag, PN7160ClassRfNfc_t *rf_nfc, PN7160ClassAnswer_t *answer) {
	const uint8_t									*b;
	size_t											len;

	if ((b = (const uint8_t *)this->_tagFind(tag, answer)) != 0x0 && (len = b[len_tag]) >= PN7160_CLASS_NDEF_TAG_PAN_SIZE_NUMBER) {
		b = b + len_tag + 0x1;//+0x1 len
		rf_nfc->cart.cart_tag4.panNumberSize = sizeof(rf_nfc->cart.cart_tag4.panNumber);
		memcpy(&rf_nfc->cart.cart_tag4.panNumber[0x0], b, sizeof(rf_nfc->cart.cart_tag4.panNumber));
		if (len >= (PN7160_CLASS_NDEF_TAG_PAN_SIZE_NUMBER + (PN7160_CLASS_NDEF_TAG_PAN_SIZE_DATE + 0x1))) {
			rf_nfc->cart.cart_tag4.panDateSize = sizeof(rf_nfc->cart.cart_tag4.panDate);
			rf_nfc->cart.cart_tag4.panDate[0x0] = ((b[PN7160_CLASS_NDEF_TAG_PAN_SIZE_NUMBER + 0x1] & 0xF) << 0x4) | ((b[PN7160_CLASS_NDEF_TAG_PAN_SIZE_NUMBER + 0x2] >> 0x4));
			rf_nfc->cart.cart_tag4.panDate[0x1] = ((b[PN7160_CLASS_NDEF_TAG_PAN_SIZE_NUMBER] << 0x4)) | (b[PN7160_CLASS_NDEF_TAG_PAN_SIZE_NUMBER + 0x1] >> 0x4);
		}
		return (true);
	}
	return (false);
}

bool PN7160Class::_readerTag(const void *pBuffer, PN7160ClassAnswer_t *answer) {

	if (this->_transceive(pBuffer, answer) != true)
		return (false);
	if (this->_wireReceive(answer, PN7160_CLASS_TIMEOUT_1S) != true)
		return (false);
	if (answer->ndef_ntf.header.gid != PN7160_CLASS_NDEF || answer->ndef_ntf.header.oid != PN7160_CLASS_NDEF_CMD)
		return (this->_lastStatus((PN7160_CLASS_STATUS_NDEF), false));
	if (memcmp(&SW1SW2, &answer->buffer[sizeof(answer->ndef_ntf.header) + answer->ndef_ntf.header.len - sizeof(SW1SW2)], sizeof(SW1SW2)) != 0x0)
		return (this->_lastStatus((PN7160_CLASS_STATUS_NDEF), false));
	// switch (answer->ndef.parameters[0x0]) {//tag-len-value
	// 	case PN7160_CLASS_NDEF_TAG_FCI:
	// 		if (memcmp(&SW1SW2, &answer->buffer[sizeof(answer->ndef.header) + answer->ndef.header.len - sizeof(SW1SW2)], sizeof(SW1SW2)) != 0x0)
	// 			return (PN7160ClassStatusHeader);
	// 		break ;
	// 	default:
	// 		break ;
	// }
	return (true);
}

uint8_t PN7160Class::_tagGetData(const PN7160ClassTlvTag_t *tag, void *dst, size_t len) {
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

const PN7160ClassTlvTag_t *PN7160Class::_tagFind(const PN7160ClassTlvTag_t *tag, const PN7160ClassAnswer_t *answer) {
	size_t									len;
	const uint8_t							*b;
	const uint8_t							*e;

	len = (answer->ndef_ntf.header.len + (sizeof(answer->ndef_ntf.header) - sizeof(SW1SW2)));
	switch (answer->ndef_ntf.parameters[0x0]) {
		case 0x70:
		case 0x77://EMV Book 3 Version 4.3
			if (answer->ndef_ntf.parameters[0x1] != len && answer->ndef_ntf.parameters[0x1] == 0x81) {
				b = &answer->ndef_ntf.parameters[0x3];
				e = &answer->ndef_ntf.parameters[0x3] + answer->ndef_ntf.parameters[0x2];
			}
			else {
				b = &answer->ndef_ntf.parameters[0x0];
				e = (const uint8_t *)((uint8_t *)answer + len);
			}
			break ;
		default:
			b = &answer->ndef_ntf.parameters[0x0];
			e = (const uint8_t *)((uint8_t *)answer + len);
			break ;
	}
	return (this->_tagFind_add(tag, b, e, this->_tagGetLen(tag)));
}

const PN7160ClassTlvTag_t *PN7160Class::_tagFind_add(const PN7160ClassTlvTag_t *tag, const uint8_t *b, const uint8_t *e, size_t len) {
	const PN7160ClassTlvTag_t								*tag_add;
	size_t													len_add;
	const PN7160ClassTlvTag_t								*out;
	const uint8_t											*tmp;

	while (b < e) {
		tag_add = (const PN7160ClassTlvTag_t *)b;
		len_add = this->_tagGetLen(tag_add);
		if (len_add == len && memcmp(tag_add, tag, len) == 0x0)
			return (tag_add);
		tmp = b + len_add + 0x1 + b[len_add];//tag-len-value
		if (tag_add->tag_object == true)
			if ((out = this->_tagFind_add(tag, b + len_add + 0x1, tmp, len)) != 0x0)//tag-len-value
				return (out);
		b = tmp;
	}
	return (0x0);
}

uint8_t PN7160Class::_tagGetLen(const PN7160ClassTlvTag_t *tag) {
	const PN7160ClassTlvTagAdd_t		*tag_add;

	if (tag->tag_number != 0x1F)
		return (0x1);
	tag_add = &tag->tag_add[0x0];
	while (tag_add->tag_follows == true)
		tag_add++;
	return (0x2 + (tag_add - &tag->tag_add[0x0]));
}

bool PN7160Class::_rfRemoval(PN7160ClassAnswer_t *answer, const PN7160ClassRfNfc_t *rf_nfc) {
	static const uint8_t							NCIPresCheckT1T[] = {0x00, 0x00, 0x07, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	static const uint8_t							NCIPresCheckT2T[] = {0x00, 0x00, 0x02, 0x30, 0x00};
	static const uint8_t							NCIPresCheckT3T[] = {0x21, 0x08, 0x04, 0xFF, 0xFF, 0x00, 0x01};
	static const uint8_t							NCIPresCheckIsoDep[] = {0x2F, 0x11, 0x00};
	static const uint8_t							NCIPresCheckIsoDepNtf[] = {0x6F, 0x11, 0x1, 0x0};
	static const uint8_t							NCIPresCheckIso15693[] = {0x00, 0x00, 0x0B, 0x26, 0x01, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	uint8_t											NCIPresCheckIso15693_dup[sizeof(NCIPresCheckIso15693)];
	size_t											i;

	switch (rf_nfc->protocol) {
		case PN7160_CLASS_PROT_T1T:
			if (this->_select(answer, rf_nfc) != true)
				return (true);
			if (this->_transceive(NCIPresCheckT1T, answer) != true)
				return (true);
			if (this->_wireReceive(answer, PN7160_CLASS_TIMEOUT_100MS) != true)
				return (true);
			if (((answer->buffer[0] == 0x00) && (answer->buffer[1] == 0x00)) == false)
				return (true);
			break ;
		case PN7160_CLASS_PROT_T2T:
			if (this->_select(answer, rf_nfc) != true)
				return (true);
			if (this->_transceive(NCIPresCheckT2T, answer) != true)
				return (true);
			if (this->_wireReceive(answer, PN7160_CLASS_TIMEOUT_100MS) != true)
				return (true);
			if (((answer->buffer[0] == 0x00) && (answer->buffer[1] == 0x00) && (answer->buffer[2] == 0x11)) == false)
				return (true);
			break ;
		case PN7160_CLASS_PROT_T3T:
			if (this->_select(answer, rf_nfc) != true)
				return (true);
			if (this->_transceive(NCIPresCheckT3T, answer) != true)
				return (true);
			if (this->_wireReceive(answer, PN7160_CLASS_TIMEOUT_100MS) != true)
				return (true);
			if (((answer->buffer[0] == 0x61) && (answer->buffer[1] == 0x08) && ((answer->buffer[3] == 0x00) || (answer->buffer[4] > 0x00))) == false)
				return (true);
			break ;
		case PN7160_CLASS_PROT_ISODEP:
			if (this->_select(answer, rf_nfc) != true)
				return (true);
			if (this->_transceiveRsp(NCIPresCheckIsoDep, answer) != true)
				return (true);
			if (this->_wireReceive(answer, PN7160_CLASS_TIMEOUT_1S) != true)
				return (true);
			if (memcmp(answer, &NCIPresCheckIsoDepNtf[0x0], sizeof(NCIPresCheckIsoDepNtf)) == 0x0)
				return (true);
			break ;
		case PN7160_CLASS_PROT_T5T:
			memcpy(NCIPresCheckIso15693_dup, NCIPresCheckIso15693, sizeof(NCIPresCheckIso15693_dup));
			for(i=0; i<8; i++) NCIPresCheckIso15693_dup[i+6] = rf_nfc->parameters.vpp.ID[7-i];
			if (this->_select(answer, rf_nfc) != true)
				return (true);
			if (this->_transceive(NCIPresCheckIso15693_dup, answer) != true)
				return (true);
			if (this->_wireReceive(answer, PN7160_CLASS_TIMEOUT_100MS) != true)
				return (true);
			if (((answer->buffer[0] == 0x00) && (answer->buffer[1] == 0x00) && (answer->buffer[(answer->rsp.header.len + sizeof(answer->rsp.header))-1] == 0x00)) == false)
				return (true);
			break ;
		case PN7160_CLASS_PROT_MIFARE:
			if (this->_rfDeactivate(answer, &_deactivate_sleep) != true)
				return (true);
			if (this->_rfSelect(answer, rf_nfc) != true)
				return (true);
			break ;
		default:
			return (true);
			break ;
	}
	return (false);
}

bool PN7160Class::_removal(PN7160ClassAnswer_t *answer, const PN7160ClassRfNfc_t *rf_nfc, bool *lpbActive) {
	static const uint8_t							NCIPresCheckT1T[] = {0x00, 0x00, 0x07, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	static const uint8_t							NCIPresCheckT2T[] = {0x00, 0x00, 0x02, 0x30, 0x00};
	static const uint8_t							NCIPresCheckT3T[] = {0x21, 0x08, 0x04, 0xFF, 0xFF, 0x00, 0x01};
	static const uint8_t							NCIPresCheckIsoDep[] = {0x2F, 0x11, 0x00};
	static const uint8_t							NCIPresCheckIsoDepNtf[] = {0x6F, 0x11, 0x1, 0x0};
	static const uint8_t							NCIDeactivate[] = {0x21, 0x06, 0x01, 0x01};
	static const uint8_t							NCISelectMIFARE[] = {0x21, 0x04, 0x03, 0x01, 0x80, 0x80};
	static const uint8_t							NCIPresCheckIso15693[] = {0x00, 0x00, 0x0B, 0x26, 0x01, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	uint8_t											NCIPresCheckIso15693_dup[sizeof(NCIPresCheckIso15693)];
	size_t											i;
	bool											bActive;

	bActive = false;
	switch (rf_nfc->protocol) {
		case PN7160_CLASS_PROT_T1T:
			while (true) {
				if (this->_transceive(NCIPresCheckT1T, answer) != true)
					return (false);
				if (this->_wireReceive(answer, PN7160_CLASS_TIMEOUT_100MS) != true)
					break ;
				if (((answer->buffer[0] == 0x00) && (answer->buffer[1] == 0x00)) == false)
					break ;
				bActive = true;
				break ;
			}
			break ;
		case PN7160_CLASS_PROT_T2T:
			while (true) {
				if (this->_transceive(NCIPresCheckT2T, answer) != true)
					return (false);
				if (this->_wireReceive(answer, PN7160_CLASS_TIMEOUT_100MS) != true)
					break ;
				if (((answer->buffer[0] == 0x00) && (answer->buffer[1] == 0x00) && (answer->buffer[2] == 0x11)) == false)
					break ;
				bActive = true;
				break ;
			}
			break ;
		case PN7160_CLASS_PROT_T3T:
			while (true) {
				if (this->_transceive(NCIPresCheckT3T, answer) != true)
					return (false);
				if (this->_wireReceive(answer, PN7160_CLASS_TIMEOUT_100MS) != true)
					break ;
				if (((answer->buffer[0] == 0x61) && (answer->buffer[1] == 0x08) && ((answer->buffer[3] == 0x00) || (answer->buffer[4] > 0x00))) == false)
					break ;
				bActive = true;
				break ;
			}
			break ;
		case PN7160_CLASS_PROT_ISODEP:
			while (true) {
				if (this->_transceiveRsp(NCIPresCheckIsoDep, answer) != true)
					return (false);
				if (this->_wireReceive(answer, PN7160_CLASS_TIMEOUT_1S) != true)
					return (false);
				if (memcmp(answer, &NCIPresCheckIsoDepNtf[0x0], sizeof(NCIPresCheckIsoDepNtf)) == 0x0)
					break ;
				bActive = true;
				break ;
			}
			break ;
		case PN7160_CLASS_PROT_T5T:
			memcpy(NCIPresCheckIso15693_dup, NCIPresCheckIso15693, sizeof(NCIPresCheckIso15693_dup));
			for(i=0; i<8; i++) NCIPresCheckIso15693_dup[i+6] = rf_nfc->parameters.vpp.ID[7-i];
			while (true) {
				if (this->_transceiveRsp(NCIPresCheckIso15693_dup, answer) != true)
					return (false);
				if (this->_wireReceive(answer, PN7160_CLASS_TIMEOUT_100MS) != true)
					return (false);
				if (((answer->buffer[0] == 0x00) && (answer->buffer[1] == 0x00) && (answer->buffer[(answer->rsp.header.len + sizeof(answer->rsp.header))-1] == 0x00)) == false)
					break ;
				bActive = true;
				break ;
			}
			break ;
		case PN7160_CLASS_PROT_MIFARE:
			while (true) {
				if (this->_transceiveRsp(NCIDeactivate, answer) != true)
					return (false);
				if (this->_wireReceive(answer, PN7160_CLASS_TIMEOUT_1S) != true)
					return (false);
				if (this->_transceiveRsp(NCISelectMIFARE, answer) != true)
					return (false);
				if (this->_wireReceive(answer, PN7160_CLASS_TIMEOUT_1S) != true)
					return (false);
				if (answer->rf_intf_activated_inf.header.gid != (PN7160_CLASS_GID_NTF | PN7160_CLASS_GID_RF) && answer->rf_intf_activated_inf.header.oid != PN7160_CLASS_OID_RF_INTF_ACTIVATED)
					break ;
				bActive = true;
				break ;
			}
			break ;
		default:
			return (false);
			break ;
	}
	lpbActive[0x0] = bActive;
	return (true);
}

size_t PN7160Class::_protToIntf(size_t prot) {
	size_t						intf;

	switch (prot) {
		case PN7160_CLASS_PROT_ISODEP:
			intf = PN7160_CLASS_INTF_ISODEP;
			break ;
		case PN7160_CLASS_PROT_NFCDEP:
			intf = PN7160_CLASS_INTF_NFCDEP;
			break ;
		case PN7160_CLASS_PROT_MIFARE:
			intf = PN7160_CLASS_INTF_TAGCMD;
			break ;
		default:
			intf = PN7160_CLASS_INTF_FRAME;
			break ;
	}
	return (intf);
}

bool PN7160Class::_rfDeactivate(PN7160ClassAnswer_t *answer, const PN7160ClassRfDeactivateCmd_t *rf_deactivate) {
	if (this->_transceiveRsp(rf_deactivate, answer) != true)
		return (false);
	if (this->_receiveNtfCheckSize(answer, PN7160_CLASS_TIMEOUT_100MS, &rf_deactivate->header, sizeof(answer->rf_deactivate_ntf)) != true)
		return (false);
	if (answer->rf_deactivate_ntf.mode != rf_deactivate->mode)
		return (this->_lastStatus((PN7160_CLASS_STATUS_NTF), false));
	return (true);
}

bool PN7160Class::_select(PN7160ClassAnswer_t *answer, const PN7160ClassRfNfc_t *rf_nfc) {
	if (this->_rf_nfc.index == (rf_nfc - &this->_rf_nfc.rf_nfc[0x0]))
		return (true);
	if (this->_rfDeactivate(answer, &_deactivate_sleep) != true)
		return (false);
	if (this->_rfSelect(answer, rf_nfc) != true)
		return (false);
	return (true);
}

bool PN7160Class::_rfSelect(PN7160ClassAnswer_t *answer, const PN7160ClassRfNfc_t *rf_nfc) {
	PN7160ClassRfDiscoverSelectCmd_t					select;
	size_t												protocol;

	select.header.gid = (PN7160_CLASS_GID_CMD | PN7160_CLASS_GID_RF);
	select.header.oid = (PN7160_CLASS_OID_DISCOVER_SELECT);
	select.header.len = (sizeof(select) - sizeof(select.header)),
	select.DiscoveryID = rf_nfc->id;
	protocol = rf_nfc->protocol;
	select.protocol = protocol;
	select.interface = this->_protToIntf(protocol);
	if (this->_transceiveRsp(&select, answer) != true)
		return (false);
	if (this->_wireReceive(answer, PN7160_CLASS_TIMEOUT_100MS) != true)
		return (false);
	if (answer->ntf.gid != (PN7160_CLASS_GID_NTF | PN7160_CLASS_GID_RF))
		return (this->_lastStatus((PN7160_CLASS_STATUS_NTF), false));
	if (answer->ntf.oid != (PN7160_CLASS_OID_RF_INTF_ACTIVATED))
		return (this->_lastStatus((PN7160_CLASS_STATUS_NTF), false));
	this->_rf_nfc.index = rf_nfc - &this->_rf_nfc.rf_nfc[0x0];
	return (true);
}

uint8_t PN7160Class::_info_finish(void *buffer, void *b, size_t count, uint8_t len) {
	if (buffer == 0x0)
		return (count);
	if (count > len)
		count = len;
	memcpy(buffer, b, count);
	return (count);
}

PN7160ClassRfNfc_t *PN7160Class::_getInfo(uint8_t index) {
	if (index >= this->_rf_nfc.count)
		return (0x0);
	return (&this->_rf_nfc.rf_nfc[index]);
}

bool PN7160Class::_info(void) {
	PN7160ClassAnswer_t												answer;
	uint8_t															mode;
	size_t															oid;
	PN7160ClassRfNfc_t												*rf_nfc;
	PN7160ClassRfNfc_t												*rf_nfc_e;

	this->_rf_nfc.count = 0x0;
	this->_rf_nfc.index = 0x0;
	mode = this->_mode;
	if ((mode & (PN7160_CLASS_MODE_RW)) == 0x0)
		return (this->_lastStatus((STATUS_CONSTRUCTOR(STATUS_SEV_ERROR, STATUS_FACILITY_PN160, STATUS_BAD_ARGUMENTS)), false));
	if (this->_wireReceive(&answer, PN7160_CLASS_TIMEOUT_100MS) != true)
		return (false);
	if (answer.ntf.gid != (PN7160_CLASS_GID_NTF | PN7160_CLASS_GID_RF))
		return (this->_lastStatus((PN7160_CLASS_STATUS_NTF), false));
	rf_nfc = &this->_rf_nfc.rf_nfc[0x0];
	if ((oid = answer.ntf.oid) == PN7160_CLASS_OID_RF_INTF_ACTIVATED) {
		this->_rf_nfc.count = 0x1;
		rf_nfc->id = answer.rf_intf_activated_inf.id;
		rf_nfc->protocol = answer.rf_intf_activated_inf.protocol;
		rf_nfc->mode_tech = answer.rf_intf_activated_inf.mode_tech;
		rf_nfc->parameters = answer.rf_intf_activated_inf.parameters;
		memset(&rf_nfc->cart, 0x0, sizeof(rf_nfc->cart));
		return (this->_lastStatus(STATUS_SUCCESS, true));
	}
	else if (oid != PN7160_CLASS_OID_RF_DISCOVER)
		return (this->_lastStatus((PN7160_CLASS_STATUS_NTF), false));
	rf_nfc = this->_info_set(rf_nfc, &answer);
	rf_nfc_e = &this->_rf_nfc.rf_nfc[(sizeof(this->_rf_nfc.rf_nfc) / sizeof(this->_rf_nfc.rf_nfc[0x0]))];
	while (true) {
		if (this->_wireReceive(&answer, PN7160_CLASS_TIMEOUT_100MS) != true)
			return (false);
		if (answer.ntf.gid != (PN7160_CLASS_GID_NTF | PN7160_CLASS_GID_RF))
			continue ;
		if (answer.ntf.oid != PN7160_CLASS_OID_RF_DISCOVER)
			continue ;
		if (rf_nfc >= rf_nfc_e)
			return (this->_lastStatus((STATUS_CONSTRUCTOR(STATUS_SEV_ERROR, STATUS_FACILITY_PN160, STATUS_NOT_ENOUGH_MEMORY)), false));
		rf_nfc = this->_info_set(rf_nfc, &answer);
		if (answer.buffer[(sizeof(answer.ntf) + answer.ntf.len) - 0x1] != 0x2)// Remaining NTF ? - 2 More Notification to follow
			break ;
	}
	this->_rf_nfc.count = rf_nfc - &this->_rf_nfc.rf_nfc[0x0];
	if (this->_rfSelect(&answer, &this->_rf_nfc.rf_nfc[0x0]) != true) {
		this->_rf_nfc.count = 0x0;
		return (false);
	}
	return (this->_lastStatus(STATUS_SUCCESS, true));
}

PN7160ClassRfNfc_t *PN7160Class::_info_set(PN7160ClassRfNfc_t *rf_nfc, PN7160ClassAnswer_t *answer) {
	rf_nfc->id = answer->rf_discover_ntf.id;
	rf_nfc->protocol = answer->rf_discover_ntf.protocol;
	rf_nfc->mode_tech = answer->rf_discover_ntf.mode_tech;
	rf_nfc->parameters = answer->rf_discover_ntf.parameters;
	memset(&rf_nfc->cart, 0x0, sizeof(rf_nfc->cart));
	rf_nfc++;
	return (rf_nfc);
}

bool PN7160Class::_configureMode(uint8_t mode) {
	PN7160ClassAnswer_t						answer;
	uint8_t									Command[sizeof(answer)];
	size_t									Item;
	static const uint8_t					NCIDiscoverMap[] = {0x21, 0x00};
	static const uint8_t					DM_RW[] = {0x1, 0x1, 0x1, 0x2, 0x1, 0x1, 0x3, 0x1, 0x1, 0x4, 0x1, 0x2, 0x80, 0x01, 0x80};
	static const uint8_t					NCIPropAct[] = {0x2F, 0x02, 0x00};
#ifndef REMOVE_CARDEMU_SUPPORT
	static const uint8_t					DM_CARDEMU[] = {0x4, 0x2, 0x2};
	static const uint8_t					R_CARDEMU[] = {0x1, 0x3, 0x0, 0x1, 0x4};
#endif //#ifndef REMOVE_CARDEMU_SUPPORT
#ifndef REMOVE_P2P_SUPPORT
	static const uint8_t					DM_P2P[] = {0x5, 0x3, 0x3};
	static const uint8_t					R_P2P[] = {0x1, 0x3, 0x0, 0x1, 0x5};
	static const uint8_t					NCISetConfig_NFC[] = {0x20, 0x02, 0x1F, 0x02, 0x29, 0x0D, 0x46, 0x66, 0x6D, 0x01, 0x01, 0x11, 0x03, 0x02, 0x00, 0x01, 0x04, 0x01, 0xFA, 0x61, 0x0D, 0x46, 0x66, 0x6D, 0x01, 0x01, 0x11, 0x03, 0x02, 0x00, 0x01, 0x04, 0x01, 0xFA};
#endif //#ifndef REMOVE_P2P_SUPPORT
#if !((defined REMOVE_P2P_SUPPORT) && (defined REMOVED_CARDEMU_SUPPORT))
	static const uint8_t					NCIRouting[] = {0x21, 0x01, 0x07, 0x00, 0x01};
	uint8_t									NCISetConfig_NFCA_SELRSP[] = {0x20, 0x02, 0x04, 0x01, 0x32, 0x01, 0x00};
#endif //#if !((defined REMOVE_P2P_SUPPORT) && (defined REMOVED_CARDEMU_SUPPORT))

	if (mode != (mode & (PN7160_CLASS_MODE_RW)) || mode == 0x0)
		return (this->_lastStatus((STATUS_CONSTRUCTOR(STATUS_SEV_ERROR, STATUS_FACILITY_PN160, STATUS_BAD_ARGUMENTS)), false));
	/* Enable Proprietary interface for T4T card presence check procedure */
	if (mode == PN7160_CLASS_MODE_RW)
		if (this->_transceiveRsp(&NCIPropAct[0x0], &answer) != true)
			return (false);
	/* Building Discovery Map command */
	Item = 0;
#ifndef REMOVE_CARDEMU_SUPPORT
	if (mode & PN7160_CLASS_MODE_CARDEMU)
	{
		memcpy(&Command[4+(3*Item)], DM_CARDEMU, sizeof(DM_CARDEMU));
		Item++;
	}
#endif //#ifndef REMOVE_CARDEMU_SUPPORT
#ifndef REMOVE_P2P_SUPPORT
	if (mode & PN7160_CLASS_MODE_P2P)
	{
		memcpy(&Command[4+(3*Item)], DM_P2P, sizeof(DM_P2P));
		Item++;
	}
#endif //#ifndef REMOVE_P2P_SUPPORT
	if (mode & PN7160_CLASS_MODE_RW) {
		memcpy(&Command[4+(3*Item)], DM_RW, sizeof(DM_RW));
		Item+=sizeof(DM_RW)/3;
	}
	memcpy(Command, NCIDiscoverMap, sizeof(NCIDiscoverMap));
	Command[2] = 1 + (Item*3);
	Command[3] = Item;
	if (this->_transceiveRsp(&Command[0x0], &answer) != true)
		return (false);
	/* Configuring routing */
	Item = 0;
#ifndef REMOVE_CARDEMU_SUPPORT
	if (mode & PN7160_CLASS_MODE_CARDEMU)
	{
		memcpy(&Command[5+(5*Item)], R_CARDEMU, sizeof(R_CARDEMU));
		Item++;
	}
#endif //#ifndef REMOVE_CARDEMU_SUPPORT
#ifndef REMOVE_P2P_SUPPORT
	if (mode & PN7160_CLASS_MODE_P2P)
	{
		memcpy(&Command[5+(5*Item)], R_P2P, sizeof(R_P2P));
		Item++;
	}
#endif //#ifndef REMOVE_P2P_SUPPORT
#if !((defined REMOVE_P2P_SUPPORT) && (defined REMOVED_CARDEMU_SUPPORT))
	if (Item != 0)
	{
		memcpy(Command, NCIRouting, sizeof(NCIRouting));
		Command[2] = 2 + (Item*5);
		Command[4] = Item;
		NxpNci_HostTransceive(Command, 3 + Command[2] , Answer, sizeof(Answer), &AnswerSize);
		if ((Answer[0] != 0x41) || (Answer[1] != 0x01) || (Answer[3] != 0x00)) return PN7160_CLASS_ERROR;
	}
#endif //#if !((defined REMOVE_P2P_SUPPORT) && (defined REMOVED_CARDEMU_SUPPORT))

	/* Setting NFCA SEL_RSP */
#ifndef REMOVE_CARDEMU_SUPPORT
	if (mode & PN7160_CLASS_MODE_CARDEMU)
	{
		NCISetConfig_NFCA_SELRSP[6] += 0x20;
	}
#endif //#ifndef REMOVE_CARDEMU_SUPPORT
#ifndef REMOVE_P2P_SUPPORT
	if (mode & PN7160_CLASS_MODE_P2P)
	{
		NCISetConfig_NFCA_SELRSP[6] += 0x40;
	}
#endif //#ifndef REMOVE_P2P_SUPPORT
#if !((defined REMOVE_P2P_SUPPORT) && (defined REMOVED_CARDEMU_SUPPORT))
	if (NCISetConfig_NFCA_SELRSP[6] != 0x00)
	{
		NxpNci_HostTransceive(NCISetConfig_NFCA_SELRSP, sizeof(NCISetConfig_NFCA_SELRSP), Answer, sizeof(Answer), &AnswerSize);
		if ((Answer[0] != 0x40) || (Answer[1] != 0x02) || (Answer[3] != 0x00)) return PN7160_CLASS_ERROR;
	}
#endif //#if !((defined REMOVE_P2P_SUPPORT) && (defined REMOVED_CARDEMU_SUPPORT))

#ifndef REMOVE_P2P_SUPPORT
	/* Setting LLCP support */
	if (mode & PN7160_CLASS_MODE_P2P)
	{
		NxpNci_HostTransceive(NCISetConfig_NFC, sizeof(NCISetConfig_NFC), Answer, sizeof(Answer), &AnswerSize);
		if ((Answer[0] != 0x40) || (Answer[1] != 0x02) || (Answer[3] != 0x00)) return PN7160_CLASS_ERROR;
	}
#endif //#ifndef REMOVE_P2P_SUPPORT
	this->_mode = mode;
	return (this->_lastStatus(STATUS_SUCCESS, true));
}

bool PN7160Class::_resetInit(PN7160ClassAnswer_t *answer, bool clear) {
	const PN7160ClassCoreResetCmd_t					*core_reset;
	static const PN7160ClassCoreResetCmd_t			core_reset_keep =
	{
		.header =
		{
			.gid = (PN7160_CLASS_GID_CMD | PN7160_CLASS_GID_CORE),
			.oid = (PN7160_CLASS_OID_CORE_RESET),
			.len = (sizeof(core_reset_keep) - sizeof(core_reset_keep.header)),
		},
		.type_reset = PN7160_CLASS_RESET_TYPE_KEEP
	};
	static const PN7160ClassCoreResetCmd_t			core_reset_clear =
	{
		.header =
		{
			.gid = (PN7160_CLASS_GID_CMD | PN7160_CLASS_GID_CORE),
			.oid = (PN7160_CLASS_OID_CORE_RESET),
			.len = (sizeof(core_reset_clear) - sizeof(core_reset_clear.header)),
		},
		.type_reset = PN7160_CLASS_RESET_TYPE_CLEAR
	};
	// static const PN7160ClassCoreInitCmdV1_t 		core_init =
	// {
	// 	.header =
	// 	{
	// 		.gid = (PN7160_CLASS_GID_CMD | PN7160_CLASS_GID_CORE),
	// 		.oid = (PN7160_CLASS_OID_CORE_INIT),
	// 		.len = (sizeof(core_init) - sizeof(core_init.header)),
	// 	}
	// };
	static const PN7160ClassCoreInitCmdV2_t 		core_init =
	{
		.header =
		{
			.gid = (PN7160_CLASS_GID_CMD | PN7160_CLASS_GID_CORE),
			.oid = (PN7160_CLASS_OID_CORE_INIT),
			.len = (sizeof(core_init) - sizeof(core_init.header)),
		},
		.Feature_Enable = {0x0, 0x0}
	};


	if (clear == true)
		core_reset = &core_reset_clear;
	else
		core_reset = &core_reset_keep;
	this->_wireReceive(answer, 0x1);//Прежде чем ресетить нужно попробовать все что есть считать - потому и ждем не долго
	if (this->_transceiveRspCheckSize(core_reset, answer, sizeof(answer->core_reset_rsp)) != true)
		return (false);
	if (this->_receiveNtfCheckSize(answer, PN7160_CLASS_TIMEOUT_100MS, &core_reset->header, sizeof(answer->core_reset_ntf)) != true)
		return (false);
	if (answer->core_reset_ntf.type_reset != core_reset->type_reset)
		return (this->_lastStatus((PN7160_CLASS_STATUS_RESET_CONFIG), false));
	this->_Manufacturer_Specific_Information = answer->core_reset_ntf.Manufacturer_Specific_Information;
	if (this->_transceiveRsp(&core_init, answer) != true)
		return (false);
	return (true);
}

bool PN7160Class::_transceiveRspCheckSize(const void *pBuffer, PN7160ClassAnswer_t *answer, size_t size) {

	if (this->_transceiveRsp(pBuffer, answer) != true)
		return (false);
	if ((answer->rsp.header.len + sizeof(answer->rsp.header)) != size)
		return (this->_lastStatus((PN7160_CLASS_STATUS_RSP), false));
	return (true);
}

bool PN7160Class::_transceiveRsp(const void *pBuffer, PN7160ClassAnswer_t *answer) {
	const PN7160ClassHeader_t						*header;

	if (this->_transceive(pBuffer, answer) != true)
		return (false);
	header = (const PN7160ClassHeader_t *)pBuffer;
	if (answer->rsp.header.gid != ((header->gid & PN7160_CLASS_GID_TYPE_MASK) | PN7160_CLASS_GID_RSP))
		return (this->_lastStatus((PN7160_CLASS_STATUS_RSP), false));
	if (answer->rsp.header.oid != (header->oid))
		return (this->_lastStatus((PN7160_CLASS_STATUS_RSP), false));
	if (answer->rsp.status != PN7160_CLASS_GENERIC_STATUS_OK)
		return (this->_lastStatus((PN7160_CLASS_STATUS_RSP), false));
	return (true);
}

bool PN7160Class::_transceive(const void *pBuffer, PN7160ClassAnswer_t *answer) {
	const PN7160ClassHeader_t				*header;
	size_t									BufferLen;

	header = (const PN7160ClassHeader_t *)pBuffer;
	BufferLen = header->len + sizeof(header[0x0]);
	if (this->_wireSend(pBuffer, BufferLen) != true)
		return (false);
	if (this->_wireReceive(answer, PN7160_CLASS_TIMEOUT_1S) != true)
		return (false);
	return (true);
}

bool PN7160Class::_wireSend(const void *pBuffer, size_t BufferLen) {
	if (this->_wire->transfer(this->_addr, (void *)pBuffer, BufferLen) != WIRE_ERORR_TRANSMISSION_SUCCESS) {
		delay(0xA);
		if (this->_wire->transfer(this->_addr, (void *)pBuffer, BufferLen) != WIRE_ERORR_TRANSMISSION_SUCCESS)
			return (this->_lastStatus(STATUS_TMP_FOR_REPLACE, false));
	}
	#ifdef PN7160_CLASS_DEBUG
	PN7160_CLASS_DEBUG.print("NCI >> ");
	PN7160_CLASS_DEBUG.dumpPrint((uint8_t *)pBuffer, BufferLen, BufferLen);
	#endif // PN7160_CLASS_DEBUG
	return (true);
}

bool PN7160Class::_receiveNtfCheckSize(PN7160ClassAnswer_t *answer, ssize_t timeout, const PN7160ClassHeader_t *header, size_t size) {
	if (this->_receiveNtf(answer, timeout, header) != true)
		return (false);
	if ((answer->ntf.len + sizeof(answer->ntf)) != size)
		return (this->_lastStatus((PN7160_CLASS_STATUS_NTF), false));
	return (true);
}

bool PN7160Class::_receiveNtf(PN7160ClassAnswer_t *answer, ssize_t timeout, const PN7160ClassHeader_t *header) {
	if (this->_wireReceive(answer, timeout) != true)
		return (false);
	if (answer->rsp.header.gid != ((header->gid & PN7160_CLASS_GID_TYPE_MASK) | PN7160_CLASS_GID_NTF))
		return (this->_lastStatus((PN7160_CLASS_STATUS_NTF), false));
	if (answer->rsp.header.oid != (header->oid))
		return (this->_lastStatus((PN7160_CLASS_STATUS_NTF), false));
	return (true);
}

bool PN7160Class::_wireReceive(PN7160ClassAnswer_t *answer, ssize_t timeout) {

	if (this->_wireReceive_add(answer, timeout) != true)
		return (false);
	#ifdef PN7160_CLASS_DEBUG
	PN7160_CLASS_DEBUG.print("NCI << ");
	PN7160_CLASS_DEBUG.dumpPrint((uint8_t *)answer, (sizeof(answer->rsp.header) + answer->rsp.header.len), (sizeof(answer->rsp.header) + answer->rsp.header.len));
	#endif // PN7160_CLASS_DEBUG
	return (true);
}

bool PN7160Class::_wireReceive_add(void *pBuffer, ssize_t timeout) {
	const PN7160ClassHeader_t				*header;
	size_t									tempos;

	if (this->_WaitForReceive(timeout) != true)
		return (false);
	if (this->_wireReceiveRead(pBuffer, sizeof(header[0x0])) != sizeof(header[0x0]))
		return (this->_lastStatus(PN7160_CLASS_STATUS_RECEIVER_I2C, false));
	header = (PN7160ClassHeader_t *)pBuffer;
	if ((tempos = header->len) == 0x0)
		return (true);
	if (this->_wireReceiveRead((uint8_t *)pBuffer + sizeof(header[0x0]), tempos) != tempos)
		return (this->_lastStatus(PN7160_CLASS_STATUS_RECEIVER_I2C, false));
	return (true);
}

size_t PN7160Class::_wireReceiveRead(void *pBuffer, size_t BufferLen) {
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

bool PN7160Class::_WaitForReceive(ssize_t timeout) {
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
				return (this->_lastStatus(PN7160_CLASS_STATUS_RECEIVER_TIMEOUT, false));
		}
	}
	return (true);
}

bool PN7160Class::_lastStatus(uint32_t status, bool ret) {
	SetLastStatus(status);
	return (ret);
}