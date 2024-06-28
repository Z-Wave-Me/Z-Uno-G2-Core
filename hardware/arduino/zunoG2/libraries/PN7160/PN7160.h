#ifndef PN7160_H
#define PN7160_H

#include "Arduino.h"
#include "Wire.h"

#define PN7160_CLASS_STATUS_REPEAT_CHECK_DEV						STATUS_CONSTRUCTOR_EXTENDED(STATUS_SEV_ERROR, STATUS_FACILITY_PN160, 0x0)
#define PN7160_CLASS_STATUS_RESET_CONFIG							STATUS_CONSTRUCTOR_EXTENDED(STATUS_SEV_ERROR, STATUS_FACILITY_PN160, 0x1)
#define PN7160_CLASS_STATUS_RECEIVER_TIMEOUT						STATUS_CONSTRUCTOR_EXTENDED(STATUS_SEV_ERROR, STATUS_FACILITY_PN160, 0x2)
#define PN7160_CLASS_STATUS_RECEIVER_I2C							STATUS_CONSTRUCTOR_EXTENDED(STATUS_SEV_ERROR, STATUS_FACILITY_PN160, 0x3)
#define PN7160_CLASS_STATUS_RSP										STATUS_CONSTRUCTOR_EXTENDED(STATUS_SEV_ERROR, STATUS_FACILITY_PN160, 0x4)
#define PN7160_CLASS_STATUS_NTF										STATUS_CONSTRUCTOR_EXTENDED(STATUS_SEV_ERROR, STATUS_FACILITY_PN160, 0x5)
#define PN7160_CLASS_STATUS_NDEF									STATUS_CONSTRUCTOR_EXTENDED(STATUS_SEV_ERROR, STATUS_FACILITY_PN160, 0x6)
#define PN7160_CLASS_STATUS_PPSE									STATUS_CONSTRUCTOR_EXTENDED(STATUS_SEV_ERROR, STATUS_FACILITY_PN160, 0x7)

#define PN7160_CLASS_ADRESS_I2C										0x28
#define PN7160_CLASS_MAX_NCI_FRAME_SIZE								258
#define PN7160_CLASS_EEPROM_SIZE									0x20

#define PN7160_CLASS_GENERIC_STATUS_OK								0x00

#define PN7160_CLASS_GID_TYPE_MASK									0x0F
#define PN7160_CLASS_GID_CMD										0x20
#define PN7160_CLASS_GID_RSP										0x40
#define PN7160_CLASS_GID_NTF										0x60

#define PN7160_CLASS_GID_CORE										0b0000
#define PN7160_CLASS_OID_CORE_RESET									0b0000
#define PN7160_CLASS_OID_CORE_INIT									0b0001
#define PN7160_CLASS_OID_CORE_SET_CONFIG							0b0010
#define PN7160_CLASS_OID_CORE_GET_CONFIG							0b0011
#define PN7160_CLASS_CORE_CONFIG_PARAMETER_TOTAL_DURATION			0x0
#define PN7160_CLASS_CORE_CONFIG_PARAMETER_TOTAL_EXT				0xA0
#define PN7160_CLASS_CORE_CONFIG_PARAMETER_TOTAL_POWER_TRANSMITTER	0x0F
#define PN7160_CLASS_CORE_CONFIG_PARAMETER_TOTAL_EEPROM				0x14

#define PN7160_CLASS_GID_RF											0b0001
#define PN7160_CLASS_OID_RF_DISCOVER								0b0011
#define PN7160_CLASS_OID_DISCOVER_SELECT							0b0100
#define PN7160_CLASS_OID_RF_INTF_ACTIVATED							0b0101
#define PN7160_CLASS_OID_RF_DEACTIVATE								0b0110

#define PN7160_CLASS_GID_PROPRIETARY								0b1111
#define PN7160_CLASS_OID_PROPRIETARY_SET_POWER_MODE					0b0000

#define PN7160_CLASS_POWER_TRANSMITTER_3_3V							0x0
#define PN7160_CLASS_POWER_TRANSMITTER_4_75_V						0x1
#define PN7160_CLASS_POWER_TRANSMITTER_2_7_V						0x2

#define PN7160_CLASS_RESET_TYPE_KEEP								0x0
#define PN7160_CLASS_RESET_TYPE_CLEAR								0x1

#define PN7160_CLASS_POWER_MODE_IDLE								0x0
#define PN7160_CLASS_POWER_MODE_STANDBY								0x1

#define PN7160_CLASS_MODE_CARDEMU				(0x1 << 0x0)
#define PN7160_CLASS_MODE_P2P					(0x1 << 0x1)
#define PN7160_CLASS_MODE_RW					(0x1 << 0x2)

//Flag definition used as Interface values
#define PN7160_CLASS_INTF_UNDETERMINED    0x0
#define PN7160_CLASS_INTF_FRAME           0x1
#define PN7160_CLASS_INTF_ISODEP          0x2
#define PN7160_CLASS_INTF_NFCDEP          0x3
#define PN7160_CLASS_INTF_TAGCMD          0x80

//Flag definition used as Protocol values
#define PN7160_CLASS_PROT_UNDETERMINED    0x0
#define PN7160_CLASS_PROT_T1T             0x1
#define PN7160_CLASS_PROT_T2T             0x2
#define PN7160_CLASS_PROT_T3T             0x3
#define PN7160_CLASS_PROT_ISODEP          0x4
#define PN7160_CLASS_PROT_NFCDEP          0x5
#define PN7160_CLASS_PROT_T5T             0x6
#define PN7160_CLASS_PROT_MIFARE          0x80

//Flag definition used as Mode values
#define PN7160_CLASS_MODE_POLL            0x00
#define PN7160_CLASS_MODE_LISTEN          0x80

// Flag definition used as Technologies values
#define PN7160_CLASS_TECH_PASSIVE_NFCA    0
#define PN7160_CLASS_TECH_PASSIVE_NFCB    1
#define PN7160_CLASS_TECH_PASSIVE_NFCF    2
#define PN7160_CLASS_TECH_ACTIVE_NFCA     3
#define PN7160_CLASS_TECH_ACTIVE_NFCF     5
#define PN7160_CLASS_TECH_PASSIVE_15693   6

//Definition of discovered remote device properties information
//POLL passive type A
typedef struct						PN7160ClassRfNfcInfoAPP_s
{
	unsigned char					SensRes[2];
	unsigned char					NfcIdLen;
	unsigned char					NfcId[10];
	unsigned char					SelResLen;
	unsigned char					SelRes[1];
	unsigned char					RatsLen;
	unsigned char					Rats[20];
}									PN7160ClassRfNfcInfoAPP_t;

//POLL passive type B
typedef struct						PN7160ClassRfNfcInfoBPP_s
{
	unsigned char					SensResLen;
	unsigned char					SensRes[12];
	unsigned char					AttribResLen;
	unsigned char					AttribRes[17];
}									PN7160ClassRfNfcInfoBPP_t;

//POLL passive type F
typedef struct						PN7160ClassRfNfcInfoFPP_s
{
	unsigned char					BitRate;
	unsigned char					SensResLen;
	unsigned char					SensRes[18];
}									PN7160ClassRfNfcInfoFPP_t;

//POLL passive type ISO15693
typedef struct						PN7160ClassRfNfcInfoVPP_s
{
	unsigned char					AFI;
	unsigned char					DSFID;
	unsigned char					ID[8];
}									PN7160ClassRfNfcInfoVPP_t;

typedef union						PN7160ClassRfNfcInfo_u
{
	PN7160ClassRfNfcInfoAPP_t		app;
	PN7160ClassRfNfcInfoBPP_t		bpp;
	PN7160ClassRfNfcInfoFPP_t		fpp;
	PN7160ClassRfNfcInfoVPP_t		vpp;
}									PN7160ClassRfNfcInfo_t;

#define PN7160_CLASS_NDEF_TAG_APPLICATION_LABEL_SIZE_MAX					0x10
#define PN7160_CLASS_NDEF_TAG_PAN_SIZE_NUMBER								0x8
#define PN7160_CLASS_NDEF_TAG_PAN_SIZE_DATE									0x2

typedef struct						PN7160ClassRfNfcCartTag4_s
{
	uint8_t							ApplicationLabelSize;
	uint8_t							ApplicationLabel[PN7160_CLASS_NDEF_TAG_APPLICATION_LABEL_SIZE_MAX];
	uint8_t							panNumberSize;
	uint8_t							panNumber[PN7160_CLASS_NDEF_TAG_PAN_SIZE_NUMBER];
	uint8_t							panDateSize;
	uint8_t							panDate[PN7160_CLASS_NDEF_TAG_PAN_SIZE_DATE];
}									PN7160ClassRfNfcCartTag4_t;

typedef union						PN7160ClassRfNfcCart_u
{
	PN7160ClassRfNfcCartTag4_t		cart_tag4;
}									PN7160ClassRfNfcCart_t;


typedef struct						PN7160ClassRfNfc_s
{
	uint8_t							id;
	uint8_t							protocol;
	uint8_t							mode_tech;
	PN7160ClassRfNfcInfo_t			parameters;
	PN7160ClassRfNfcCart_t			cart;
}									PN7160ClassRfNfc_t;

typedef struct						PN7160ClassRfNfcCommon_s
{
	uint8_t							count;
	uint8_t							index;
	PN7160ClassRfNfc_t				rf_nfc[0x2];
}									PN7160ClassRfNfcCommon_t;

typedef struct								PN7160ClassEeprom_s
{
	uint8_t									buffer[PN7160_CLASS_EEPROM_SIZE];
}											PN7160ClassEeprom_t;

typedef struct								PN7160ClassHeader_s
{
	uint8_t									gid;
	uint8_t									oid;
	uint8_t									len;//полная длина в байтах всего остального пакета после header
}											PN7160ClassHeader_t;

typedef struct								PN7160ClassCoreResetCmd_s
{
	PN7160ClassHeader_t						header;
	uint8_t									type_reset;
}											PN7160ClassCoreResetCmd_t;

typedef struct								PN7160ClassRsp_s
{
	PN7160ClassHeader_t						header;
	uint8_t									status;
}											PN7160ClassRsp_t;


typedef struct								PN7160ClassCoreResetRsp_s
{
	PN7160ClassRsp_t						rsp;
}											PN7160ClassCoreResetRsp_t;

typedef struct								PN7160ClassCoreResetNtfManufacturer_s
{
	uint8_t									Hardware_Version;//number New silicon
	uint8_t									ROM_Code_Version;//number New ROM Code
	uint8_t									FLASH_Major_version;//New Firmware, adding features
	uint8_t									FLASH_Minor_version;//New Firmware, solving bugs on existing features
}											PN7160ClassCoreResetNtfManufacturer_t;

typedef struct								PN7160ClassCoreResetNtf_s
{
	PN7160ClassHeader_t						header;
	uint8_t									Reset_Trigger;//0x02 (CORE_RESET_CMD was received)
	uint8_t									type_reset;//0x00 if configuration has been kept, 0x01 if configuration has been reset
	uint8_t									NCI_Version;//0x20 (NCI Version 2.0)
	uint8_t									Manufacturer_ID;//0x04 (NXP)
	uint8_t									Manufacturer_Specific_Information_Length;//0x4
	PN7160ClassCoreResetNtfManufacturer_t	Manufacturer_Specific_Information;
}											PN7160ClassCoreResetNtf_t;

typedef struct								PN7160ClassCoreGetConfigRspDuration_s
{
	uint8_t									sub;
	uint8_t									len;
	uint8_t									ms[0x2];/* LSB  to MSB */
}											PN7160ClassCoreGetConfigRspDuration_t;

typedef struct								PN7160ClassCoreGetConfigRspEeprom_s
{
	uint8_t									sub;
	uint8_t									sub_add;
	uint8_t									len;
	PN7160ClassEeprom_t						eeprom;
}											PN7160ClassCoreGetConfigRspEeprom_t;

typedef union								PN7160ClassCoreGetConfigRspParametrs_u
{
	PN7160ClassCoreGetConfigRspDuration_t	duration;
	PN7160ClassCoreGetConfigRspEeprom_t		eeprom;
}											PN7160ClassCoreGetConfigRspParametrs_t;

typedef struct								PN7160ClassCoreGetConfigRsp_s
{
	PN7160ClassRsp_t						rsp;
	uint8_t									NumberofParameters;
	PN7160ClassCoreGetConfigRspParametrs_t	parametrs[];
}											PN7160ClassCoreGetConfigRsp_t;

typedef struct								PN7160ClassRfIntfActivatedNtf_s
{
	PN7160ClassHeader_t						header;
	uint8_t									id;
	uint8_t									interface;//If this contains a value of 0x00 (NFCEE Direct RF Interface) then all following parameters SHALL contain a value of 0 and SHALL be ignored
	uint8_t									protocol;
	uint8_t									mode_tech;//RF Technology and Mode of the local device that were used for the collection of the RF Technology Specific Parameters below
	uint8_t									max_data;//Max Data Packet Payload Size the NFCC can receive for the Static RF Connection. A number from 1 – 255
	uint8_t									InitialNumberofCredits;//Initial Number of Credits given by the NFCC to the DH for the Static RF Connection
	uint8_t									len_parameters;//The length of RF Technology Specific Parameters field to follow
	PN7160ClassRfNfcInfo_t					parameters;//One of the below tables depending on the value of the RF Technology and Mode;Depends on RF Technology and Mode
	// .... - есть еще параметры
}											PN7160ClassRfIntfActivatedNtf_t;

typedef struct								PN7160ClassRfDiscoverNtf_s
{
	PN7160ClassHeader_t						header;
	uint8_t									id;
	uint8_t									protocol;
	uint8_t									mode_tech;//RF Technology and Mode of the local device that were used for the collection of the RF Technology Specific Parameters below
	uint8_t									len_parameters;//The length of RF Technology Specific Parameters field to follow
	PN7160ClassRfNfcInfo_t					parameters;//One of the below tables depending on the value of the RF Technology and Mode;Depends on RF Technology and Mode
	// .... - есть еще параметры 
}											PN7160ClassRfDiscoverNtf_t;

typedef struct								PN7160ClassRfDeactivateNtf_s
{
	PN7160ClassHeader_t						header;
	uint8_t									mode;
	uint8_t									reason;
}											PN7160ClassRfDeactivateNtf_t;

typedef struct								PN7160ClassNdefNtf_s
{
	PN7160ClassHeader_t						header;
	uint8_t									parameters[];//tag-len-value
}											PN7160ClassNdefNtf_t;

typedef union								PN7160ClassAnswer_u
{
	uint8_t									buffer[PN7160_CLASS_MAX_NCI_FRAME_SIZE];
	union
	{
		PN7160ClassRsp_t					rsp;
		PN7160ClassHeader_t					ntf;
		PN7160ClassRfDiscoverNtf_t			rf_discover_ntf;
		PN7160ClassRfIntfActivatedNtf_t		rf_intf_activated_inf;
		PN7160ClassCoreResetRsp_t			core_reset_rsp;
		PN7160ClassCoreResetNtf_t			core_reset_ntf;
		PN7160ClassCoreGetConfigRsp_t		core_get_config_rsp;
		PN7160ClassRfDeactivateNtf_t		rf_deactivate_ntf;
		PN7160ClassNdefNtf_t				ndef_ntf;
	};
	
}											PN7160ClassAnswer_t;

typedef struct								PN7160ClassRfDeactivateCmd_s
{
	PN7160ClassHeader_t						header;
	uint8_t									mode;
}											PN7160ClassRfDeactivateCmd_t;

typedef union					PN7160ClassTlvTagAdd_u
{
	uint8_t						tag;
	struct
	{
		uint8_t					tag_number: 0x7;
		uint8_t					tag_follows: 0x1;
	};
}								PN7160ClassTlvTagAdd_t;

typedef struct					PN7160ClassTlvTag_s
{
	union
	{
		uint8_t					tag;
		struct
		{
			uint8_t				tag_number: 0x5;//See subsequent bytes = 0x1F
			uint8_t				tag_object: 0x1;
			uint8_t				tag_class: 0x2;
		};
		
	};
	PN7160ClassTlvTagAdd_t		tag_add[];
}								PN7160ClassTlvTag_t;

class PN7160Class {
	public:
		PN7160Class(void (*event_irq)(void), TwoWire *wire, uint8_t scl, uint8_t sda, uint8_t irq, uint8_t ven, uint8_t addr = PN7160_CLASS_ADRESS_I2C);
		uint8_t											ppseExpirationDate(uint8_t index, void *buffer, uint8_t len);
		uint8_t											ppseCardNumber(uint8_t index, void *buffer, uint8_t len);
		uint8_t											ppsePaymentSystem(uint8_t index, void *buffer, uint8_t len);
		bool											ppse(uint8_t index);
		bool											discoveryRestart();
		void											infoWaitRemoval(void (*userFunc)(uint8_t) = 0x0);
		uint8_t											infoDsfid(uint8_t index, void *buffer, uint8_t len);
		uint8_t											infoAfi(uint8_t index, void *buffer, uint8_t len);
		uint8_t											infoId(uint8_t index, void *buffer, uint8_t len);
		uint16_t										infoBitRate(uint8_t index);
		uint8_t											infoSel(uint8_t index, void *buffer, uint8_t len);
		uint8_t											infoNfcid(uint8_t index, void *buffer, uint8_t len);
		uint8_t											infoSens(uint8_t index, void *buffer, uint8_t len);
		uint8_t											infoProtocol(uint8_t index);
		uint8_t											info(void);
		void											eventIrq(void);
		inline bool										eventIrqIs(void) { return (this->_irq_status);};
		bool											discovery();
		inline bool										configureMode(void) {return (this->_configureMode(PN7160_CLASS_MODE_RW));};
		bool											setCore(void);
		bool											setRf(void);
		bool											setPowerTransmitter(uint8_t mode);
		bool											setPowerMode(uint8_t mode);
		bool											setDuration(uint16_t ms);
		bool											applySettings(void);
		bool											setEEPROM(const PN7160ClassEeprom_t *eeprom);
		bool											getEEPROM(PN7160ClassEeprom_t *eeprom);
		bool											getDuration(uint16_t *ms);
		bool											connect(bool clear=false);
		inline uint8_t									getHardwareVersion(void) {return (this->_Manufacturer_Specific_Information.Hardware_Version);};
		inline uint8_t									getRomVersion(void) {return (this->_Manufacturer_Specific_Information.ROM_Code_Version);};
		inline uint8_t									getFwMajorVersion(void) {return (this->_Manufacturer_Specific_Information.FLASH_Major_version);};
		inline uint8_t									getFwMinorVersion(void) {return (this->_Manufacturer_Specific_Information.FLASH_Minor_version);};

	private:
		inline bool										_ppsePan(const PN7160ClassTlvTag_t *tag, size_t len_tag, PN7160ClassRfNfc_t *rf_nfc, PN7160ClassAnswer_t *answer);
		inline bool										_readerTag(const void *pBuffer, PN7160ClassAnswer_t *answer);
		inline uint8_t									_tagGetData(const PN7160ClassTlvTag_t *tag, void *dst, size_t len);
		inline const PN7160ClassTlvTag_t				*_tagFind(const PN7160ClassTlvTag_t *tag, const PN7160ClassAnswer_t *answer);
		inline const PN7160ClassTlvTag_t				*_tagFind_add(const PN7160ClassTlvTag_t *tag, const uint8_t *b, const uint8_t *e, size_t len);
		inline uint8_t									_tagGetLen(const PN7160ClassTlvTag_t *tag);
		inline bool										_rfRemoval(PN7160ClassAnswer_t *answer, const PN7160ClassRfNfc_t *rf_nfc);
		inline bool										_removal(PN7160ClassAnswer_t *answer, const PN7160ClassRfNfc_t *rf_nfc, bool *lpbActive);
		inline size_t									_protToIntf(size_t prot);
		inline bool										_rfDeactivate(PN7160ClassAnswer_t *answer, const PN7160ClassRfDeactivateCmd_t *rf_deactivate);
		inline bool										_rfSelect(PN7160ClassAnswer_t *answer, const PN7160ClassRfNfc_t *rf_nfc);
		inline bool										_select(PN7160ClassAnswer_t *answer, const PN7160ClassRfNfc_t *rf_nfc);
		inline uint8_t									_info_finish(void *buffer, void *b, size_t count, uint8_t len);
		inline PN7160ClassRfNfc_t						*_getInfo(uint8_t index);
		inline bool										_info(void);
		inline PN7160ClassRfNfc_t						*_info_set(PN7160ClassRfNfc_t *rf_nfc, PN7160ClassAnswer_t *answer);
		bool											_configureMode(uint8_t mode);
		inline bool										_resetInit(PN7160ClassAnswer_t *answer, bool clear);
		inline bool										_transceiveRspCheckSize(const void *pBuffer, PN7160ClassAnswer_t *answer, size_t size);
		inline bool										_transceiveRsp(const void *pBuffer, PN7160ClassAnswer_t *answer);
		inline bool										_transceive(const void *pBuffer, PN7160ClassAnswer_t *answer);
		inline bool										_wireSend(const void *pBuffer, size_t BufferLen);
		inline bool										_receiveNtfCheckSize(PN7160ClassAnswer_t *answer, ssize_t timeout, const PN7160ClassHeader_t *header, size_t size);
		inline bool										_receiveNtf(PN7160ClassAnswer_t *answer, ssize_t timeout, const PN7160ClassHeader_t *header);
		inline bool										_wireReceive(PN7160ClassAnswer_t *answer, ssize_t timeout);
		inline bool										_wireReceive_add(void *pBuffer, ssize_t timeout);
		inline size_t									_wireReceiveRead(void *pBuffer, size_t BufferLen);
		inline bool										_WaitForReceive(ssize_t timeout);
		inline bool										_lastStatus(uint32_t status, bool ret);

		void									(*_event_irq)(void);
		TwoWire									*_wire;
		PN7160ClassRfNfcCommon_t				_rf_nfc;
		uint8_t									_buffer_wire[(size_t)(PN7160_CLASS_MAX_NCI_FRAME_SIZE * 1.3)];
		uint8_t									_scl;
		uint8_t									_sda;
		uint8_t									_irq;
		uint8_t									_ven;
		uint8_t									_addr;
		uint8_t									_mode;
		bool									_irq_status;
		PN7160ClassCoreResetNtfManufacturer_t	_Manufacturer_Specific_Information;
};

#endif//PN7160_H
