#ifndef PN7150_H
#define PN7150_H

#include "Arduino.h"
#include "Wire.h"


//Flag definition used as Interface values
#define PN7150_CLASS_INTF_UNDETERMINED    0x0
#define PN7150_CLASS_INTF_FRAME           0x1
#define PN7150_CLASS_INTF_ISODEP          0x2
#define PN7150_CLASS_INTF_NFCDEP          0x3
#define PN7150_CLASS_INTF_TAGCMD          0x80

//Flag definition used as Protocol values
#define PN7150_CLASS_PROT_UNDETERMINED    0x0
#define PN7150_CLASS_PROT_T1T             0x1
#define PN7150_CLASS_PROT_T2T             0x2
#define PN7150_CLASS_PROT_T3T             0x3
#define PN7150_CLASS_PROT_ISODEP          0x4
#define PN7150_CLASS_PROT_NFCDEP          0x5
#define PN7150_CLASS_PROT_T5T             0x6
#define PN7150_CLASS_PROT_MIFARE          0x80

//Flag definition used as Mode values
#define PN7150_CLASS_MODE_POLL            0x00
#define PN7150_CLASS_MODE_LISTEN          0x80

// Flag definition used as Technologies values
#define PN7150_CLASS_TECH_PASSIVE_NFCA    0
#define PN7150_CLASS_TECH_PASSIVE_NFCB    1
#define PN7150_CLASS_TECH_PASSIVE_NFCF    2
#define PN7150_CLASS_TECH_ACTIVE_NFCA     3
#define PN7150_CLASS_TECH_ACTIVE_NFCF     5
#define PN7150_CLASS_TECH_PASSIVE_15693   6

#define PN7150_CLASS_MODE_CARDEMU				(0x1 << 0x0)
#define PN7150_CLASS_MODE_P2P					(0x1 << 0x1)
#define PN7150_CLASS_MODE_RW					(0x1 << 0x2)

#define PN7150_CLASS_HARDWARE_VERSION_V1				0x1
#define PN7150_CLASS_HARDWARE_VERSION_V2				0x2

#define PN7150_CLASS_ADRESS_I2C				0x28

#define PN7150_CLASS_MAX_NCI_FRAME_SIZE		258

#define PN7150_CLASS_EEPROM_SIZE			0x20

#define PN7150_CLASS_GENERIC_STATUS_OK						0x0

#define PN7150_CLASS_CMD_CORE								0x20
#define PN7150_CLASS_CMD_CORE_RSP							0x40
#define PN7150_CLASS_CMD_CORE_NTF							0x60

#define PN7150_CLASS_CMD_RF									0x21
#define PN7150_CLASS_CMD_RF_RSP								0x41
#define PN7150_CLASS_CMD_RF_NTF								0x61

#define PN7150_CLASS_CMD_NFCEE								0x22
#define PN7150_CLASS_CMD_NFCEE_RSP							0x42
#define PN7150_CLASS_CMD_NFCEE_NTF							0x62

#define PN7150_CLASS_CMD_PROPRIETARY						0x2F
#define PN7150_CLASS_CMD_PROPRIETARY_RSP					0x4F
#define PN7150_CLASS_CMD_PROPRIETARY_NTF					0x6F

#define PN7150_CLASS_CMD_RF_DISCOVER_CMD						0x3
#define PN7150_CLASS_CMD_RF_DISCOVER_RSP						0x3
#define PN7150_CLASS_CMD_RF_DISCOVER_NTTF						0x3
#define PN7150_CLASS_RF_DISCOVER_SELECT_CMD						0x4
#define PN7150_CLASS_RF_DISCOVER_SELECT_RSP						0x4
#define PN7150_CLASS_CMD_RF_INTF_ACTIVATED_NTF					0x5
#define PN7150_CLASS_CMD_RF_DEACTIVATE_CMD						0x6
#define PN7150_CLASS_CMD_RF_DEACTIVATE_RSP						0x6
#define PN7150_CLASS_CMD_RF_DEACTIVATE_NTF						0x6

#define PN7150_CLASS_CMD_RF_DEACTIVATE_MODE_IDLE			0x0
#define PN7150_CLASS_CMD_RF_DEACTIVATE_MODE_SLEEP			0x1
#define PN7150_CLASS_CMD_RF_DEACTIVATE_MODE_SLEEP_AF		0x2
#define PN7150_CLASS_CMD_RF_DEACTIVATE_MODE_DISCOVERY		0x3

#define PN7150_CLASS_CORE_RESET_CMD								0x0
#define PN7150_CLASS_CORE_INIT_CMD								0x1
#define PN7150_CLASS_CORE_RESET_CMD_TYPE_KEEP					0x0//Keep Configuration;Reset the NFCC and keep the NCI RF Configuration (if supported).
#define PN7150_CLASS_CORE_RESET_CMD_TYPE_CLEAR					0x1//Reset Configuration;Reset the NFCC including the NCI RF 

#define PN7150_CLASS_PROPRIETARY_POWER_MODE_CMD					0x0
#define PN7150_CLASS_CORE_SET_CONFIG_CMD						0x2
#define PN7150_CLASS_CORE_GET_CONFIG_CMD						0x3
#define PN7150_CLASS_CORE_CONFIG_CMD_PARAMETER_TOTAL_DURATION	0x0
#define PN7150_CLASS_CORE_CONFIG_CMD_PARAMETER_EXT				0xA0
#define PN7150_CLASS_CORE_CONFIG_CMD_PARAMETER_EXT_EEPROM_V1	0xF
#define PN7150_CLASS_CORE_CONFIG_CMD_PARAMETER_EXT_EEPROM_V2	0x14
#define PN7150_CLASS_CORE_CONFIG_CMD_PARAMETER_EXT_POWER_TRANSMITTER_V1	0x13
#define PN7150_CLASS_CORE_CONFIG_CMD_PARAMETER_EXT_POWER_TRANSMITTER_V2	0xE

#define PN7150_CLASS_RF_DISCOVER_SELECT_CMD_DEFAULT(set_id, set_protocol, set_interface)	\
{																					\
	{																				\
		.unknown = PN7150_CLASS_CMD_RF,												\
		.cmd = PN7150_CLASS_RF_DISCOVER_SELECT_CMD,									\
		.len = (sizeof(PN7150ClassRfDiscoverSelectCmd_t) - sizeof(PN7150ClassCmdHeader_t))	\
	},																				\
	.DiscoveryID = (uint8_t)set_id,													\
	.protocol = (uint8_t)set_protocol,												\
	.interface = (uint8_t)set_interface												\
}																					\

#define PN7150_CLASS_CORE_RESET_CMD_DEFAULT(type_reset)								\
{																					\
	{																				\
		.unknown = PN7150_CLASS_CMD_CORE,											\
		.cmd = PN7150_CLASS_CORE_RESET_CMD,											\
		.len = (sizeof(PN7150ClassCmdCoreReset_t) - sizeof(PN7150ClassCmdHeader_t))	\
	},																				\
	.type = type_reset																\
}																					\

#define PN7150_CLASS_CORE_INIT_CMD_DEFAULT()										\
{																					\
	{																				\
		.unknown = PN7150_CLASS_CMD_CORE,											\
		.cmd = PN7150_CLASS_CORE_INIT_CMD,											\
		.len = (sizeof(PN7150ClassCmdCoreInit_t) - sizeof(PN7150ClassCmdHeader_t))	\
	}																				\
}																					\

#define PN7150_CLASS_CMD_RF_DEACTIVATE_CMD_DEFAULT(set_mode)						\
{																					\
	{																				\
		.unknown = PN7150_CLASS_CMD_RF,												\
		.cmd = PN7150_CLASS_CMD_RF_DEACTIVATE_CMD,									\
		.len = (sizeof(PN7150ClassCmdRfDeactivate_t) - sizeof(PN7150ClassCmdHeader_t))	\
	},																				\
	.mode = set_mode																\
}																					\

#define PN7150_CLASS_CORE_GET_CONFIG_CMD_DEFAULT(...)									\
{																					\
	{																				\
		.unknown = PN7150_CLASS_CMD_CORE,											\
		.cmd = PN7150_CLASS_CORE_GET_CONFIG_CMD,									\
		.len = (sizeof(PN7150ClassCmdGetConfig_t) - sizeof(PN7150ClassCmdHeader_t) + sizeof((uint8_t []){__VA_ARGS__}))	\
	},																				\
	.NumberofParameters = sizeof((uint8_t []){__VA_ARGS__}),														\
	.parametrs = {__VA_ARGS__}																	\
}																					\

#define PN7150_CLASS_CORE_GET_CONFIG_CMD_DEFAULT_EXT(...)									\
{																					\
	{																				\
		.unknown = PN7150_CLASS_CMD_CORE,											\
		.cmd = PN7150_CLASS_CORE_GET_CONFIG_CMD,									\
		.len = (sizeof(PN7150ClassCmdGetConfig_t) - sizeof(PN7150ClassCmdHeader_t) + sizeof((uint8_t []){__VA_ARGS__}))	\
	},																				\
	.NumberofParameters = (sizeof((uint8_t []){__VA_ARGS__}) / 0x2),														\
	.parametrs = {__VA_ARGS__}																	\
}																					\

#define PN7150_CLASS_CORE_CONFIG_CMD_PARAMETER_TOTAL_DURATION_DEFAULT(duration)		\
{																					\
	{																				\
		.unknown = PN7150_CLASS_CMD_CORE,											\
		.cmd = PN7150_CLASS_CORE_SET_CONFIG_CMD,									\
		.len = (sizeof(PN7150ClassCmdSetConfigTotalDuration_t) - sizeof(PN7150ClassCmdHeader_t))	\
	},																				\
	.NumberofParameters = 0x1,														\
	.sub = PN7150_CLASS_CORE_CONFIG_CMD_PARAMETER_TOTAL_DURATION,					\
	.sub_len = 0x2,																	\
	.ms = {(uint8_t)duration, (uint8_t)(duration >> 0x8)}												\
}																					\

#define PN7150_CLASS_CORE_CONFIG_CMD_PARAMETER_EXT_EEPROM_DEFAULT(cmd)		\
{																					\
	{																				\
		.unknown = PN7150_CLASS_CMD_CORE,											\
		.cmd = PN7150_CLASS_CORE_SET_CONFIG_CMD,									\
		.len = (sizeof(PN7150ClassCmdSetConfigExtEeprom_t) - sizeof(PN7150ClassCmdHeader_t))	\
	},																				\
	.NumberofParameters = 0x1,														\
	.sub = PN7150_CLASS_CORE_CONFIG_CMD_PARAMETER_EXT,								\
	.sub_add = (uint8_t)cmd,														\
	.sub_len = PN7150_CLASS_EEPROM_SIZE,											\
	.buffer = {0x0}																	\
}																					\

#define PN7150_CLASS_PROPRIETARY_POWER_MODE_CMD_DEFAULT(power_mode)					\
{																					\
	{																				\
		.unknown = PN7150_CLASS_CMD_PROPRIETARY,											\
		.cmd = PN7150_CLASS_PROPRIETARY_POWER_MODE_CMD,								\
		.len = (sizeof(PN7150ClassCmdSetPowerMode_t) - sizeof(PN7150ClassCmdHeader_t))	\
	},																				\
	.mode = power_mode																\
}																					\

#define PN7150_CLASS_CORE_CONFIG_CMD_PARAMETER_EXT_POWER_TRANSMITTER_V1_DEFAULT(prop)	\
{																					\
	{																				\
		.unknown = PN7150_CLASS_CMD_CORE,											\
		.cmd = PN7150_CLASS_CORE_SET_CONFIG_CMD,									\
		.len = (sizeof(PN7150ClassCmdSetConfigExtPowerTransmitterV1_t) - sizeof(PN7150ClassCmdHeader_t))	\
	},																				\
	.NumberofParameters = 0x1,														\
	.sub = PN7150_CLASS_CORE_CONFIG_CMD_PARAMETER_EXT,								\
	.sub_add = PN7150_CLASS_CORE_CONFIG_CMD_PARAMETER_EXT_POWER_TRANSMITTER_V1,		\
	.sub_len = 0x1,																	\
	.properties = (uint8_t)prop														\
}																					\

#define PN7150_CLASS_CORE_CONFIG_CMD_PARAMETER_EXT_POWER_TRANSMITTER_V2_DEFAULT(prop1, prop2, prop3)	\
{																					\
	{																				\
		.unknown = PN7150_CLASS_CMD_CORE,											\
		.cmd = PN7150_CLASS_CORE_SET_CONFIG_CMD,									\
		.len = (sizeof(PN7150ClassCmdSetConfigExtPowerTransmitterV2_t) - sizeof(PN7150ClassCmdHeader_t))	\
	},																				\
	.NumberofParameters = 0x1,														\
	.sub = PN7150_CLASS_CORE_CONFIG_CMD_PARAMETER_EXT,								\
	.sub_add = PN7150_CLASS_CORE_CONFIG_CMD_PARAMETER_EXT_POWER_TRANSMITTER_V2,		\
	.sub_len = 0x3,																	\
	.properties1 = (uint8_t)prop1,													\
	.properties2 = (uint8_t)prop2,													\
	.properties3 = (uint8_t)prop3													\
}																					\

#define PN7150_CLASS_NDEF							0x0
#define PN7150_CLASS_NDEF_CMD						0x0

#define PN7150_CLASS_NDEF_TAG_APPLICATION_DEDICATED_FILE_NAME				0x4F
#define PN7150_CLASS_NDEF_TAG_APPLICATION_DEDICATED_FILE_NAME_SIZE_MAX		0x10

#define PN7150_CLASS_NDEF_TAG_APPLICATION_LABEL								0x50
#define PN7150_CLASS_NDEF_TAG_APPLICATION_LABEL_SIZE_MAX					0x10

#define PN7150_CLASS_NDEF_TAG_FCI											0x6F
#define PN7150_CLASS_NDEF_TAG_FCI_SIZE_MAX									0xFC

#define PN7150_CLASS_NDEF_TAG_AFL											0x94

#define PN7150_CLASS_NDEF_TAG_PAN											0x57
#define PN7150_CLASS_NDEF_TAG_PAN_V2										0x9F, 0x6B
#define PN7150_CLASS_NDEF_TAG_PAN_SIZE_NUMBER								0x8
#define PN7150_CLASS_NDEF_TAG_PAN_SIZE_DATE									0x2
#define PN7150_CLASS_NDEF_TAG_PAN_SIZE_DATE_TEST							0xD0
#define PN7150_CLASS_NDEF_TAG_PAN_SIZE_MAX									0x13

#define PN7150_CLASS_NDEF_TAG_PDOL											0x9F, 0x38

#define PN7150_CLASS_NDEF_TAG_TTQ											0x9F, 0x66

#define PN7150_CLASS_NDEF_DEFAULT(...)												\
{																					\
	{																				\
		.unknown = PN7150_CLASS_NDEF,												\
		.cmd = PN7150_CLASS_NDEF_CMD,												\
		.len = sizeof((uint8_t []){__VA_ARGS__})									\
	},																				\
	.value = {__VA_ARGS__}															\
}																					\

//EMV Book 1 Version 4.3 - 11.3.2
#define PN7150_CLASS_NDEF_SELECT_PSE																				\
	0x0,/* CLA */																									\
	0xA4,/* INS */																									\
	0x4,/* P1 - Select by name */																					\
	0x0,/* P2 - First or only occurrence */																			\
	0xE,/* Lc - Length data */																						\
	0x32, 0x50, 0x41, 0x59, 0x2E, 0x53, 0x59, 0x53, 0x2E, 0x44, 0x44, 0x46, 0x30, 0x31,/* 2PAY. SYS.DDF01 */		\
	0x0/* Le */																										\

//EMV Book 1 Version 4.3 - 11.3.2
#define PN7150_CLASS_NDEF_SELECT_PSE_ADF()											\
{																					\
	{																				\
		.unknown = PN7150_CLASS_NDEF,												\
		.cmd = PN7150_CLASS_NDEF_CMD,												\
		.len = 0x0																	\
	},																				\
	.cla = 0x0,																		\
	.ins = 0xA4,																	\
	.p1 = 0x4,/* P1 - Select by name */												\
	.p2 = 0x0,																		\
	.lc = 0x0																		\
}																					\

//EMV Book 3 Version 4.3 - 6.5.8 
#define PN7150_CLASS_NDEF_GET_PROCESSING_OPTIONS_DEFAULT()							\
{																					\
	{																				\
		.unknown = PN7150_CLASS_NDEF,												\
		.cmd = PN7150_CLASS_NDEF_CMD,												\
		.len = 0x0																	\
	},																				\
	.cla = 0x80,																	\
	.ins = 0xA8,																	\
	.p1 = 0x0,																		\
	.p2 = 0x0,																		\
	.lc = 0x0																		\
}																					\


//EMV Book 3 Version 4.3 - 6.5.11 
#define PN7150_CLASS_NDEF_READ_RECORDS_DEFAULT(record_number, sfi)					\
{																					\
	{																				\
		.unknown = PN7150_CLASS_NDEF,												\
		.cmd = PN7150_CLASS_NDEF_CMD,												\
		.len = (sizeof(PN7150ClassNdefReadRecords_t) - sizeof(PN7150ClassCmdHeader_t))	\
	},																				\
	.cla = 0x0,																		\
	.ins = 0xB2,																	\
	.p1 = record_number,															\
	.p2 = (uint8_t)(sfi | 0x4),/* 0x4 - P1 is a record number*/						\
	.le = 0x0																		\
}																					\

typedef union					PN7150ClassTlvTagAdd_u
{
	uint8_t						tag;
	struct
	{
		uint8_t					tag_number: 0x7;
		uint8_t					tag_follows: 0x1;
	};
}								PN7150ClassTlvTagAdd_t;

typedef struct					PN7150ClassTlvTag_s
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
	PN7150ClassTlvTagAdd_t		tag_add[];
}								PN7150ClassTlvTag_t;

#define TIMEOUT_INFINITE	0
#define TIMEOUT_100MS		100
#define TIMEOUT_1S			1000
#define TIMEOUT_2S			2000


//Definition of discovered remote device properties information
//POLL passive type A
typedef struct						PN7150ClassRfNfcInfoAPP_s
{
	unsigned char					SensRes[2];
	unsigned char					NfcIdLen;
	unsigned char					NfcId[10];
	unsigned char					SelResLen;
	unsigned char					SelRes[1];
	unsigned char					RatsLen;
	unsigned char					Rats[20];
}									PN7150ClassRfNfcInfoAPP_t;

//POLL passive type B
typedef struct						PN7150ClassRfNfcInfoBPP_s
{
	unsigned char					SensResLen;
	unsigned char					SensRes[12];
	unsigned char					AttribResLen;
	unsigned char					AttribRes[17];
}									PN7150ClassRfNfcInfoBPP_t;

//POLL passive type F
typedef struct						PN7150ClassRfNfcInfoFPP_s
{
	unsigned char					BitRate;
	unsigned char					SensResLen;
	unsigned char					SensRes[18];
}									PN7150ClassRfNfcInfoFPP_t;

//POLL passive type ISO15693
typedef struct						PN7150ClassRfNfcInfoVPP_s
{
	unsigned char					AFI;
	unsigned char					DSFID;
	unsigned char					ID[8];
}									PN7150ClassRfNfcInfoVPP_t;

typedef union						PN7150ClassRfNfcInfo_u
{
	PN7150ClassRfNfcInfoAPP_t		app;
	PN7150ClassRfNfcInfoBPP_t		bpp;
	PN7150ClassRfNfcInfoFPP_t		fpp;
	PN7150ClassRfNfcInfoVPP_t		vpp;
}									PN7150ClassRfNfcInfo_t;

typedef struct						PN7150ClassRfNfcCartTag4_s
{
	uint8_t							ApplicationLabelSize;
	uint8_t							ApplicationLabel[PN7150_CLASS_NDEF_TAG_APPLICATION_LABEL_SIZE_MAX];
	uint8_t							panNumberSize;
	uint8_t							panNumber[PN7150_CLASS_NDEF_TAG_PAN_SIZE_NUMBER];
	uint8_t							panDateSize;
	uint8_t							panDate[PN7150_CLASS_NDEF_TAG_PAN_SIZE_DATE];
}									PN7150ClassRfNfcCartTag4_t;

typedef struct						PN7150ClassRfNfc_s
{
	uint8_t							protocol;
	uint8_t							mode_tech;
	PN7150ClassRfNfcInfo_t			parameters;
	union
	{
		PN7150ClassRfNfcCartTag4_t	cart_tag4;
	};
}									PN7150ClassRfNfc_t;

typedef struct					PN7150ClassCmdHeader_s
{
	uint8_t						unknown;
	uint8_t						cmd;//сама команда
	uint8_t						len;//полная длина в байтах всего остального пакета после header
}								PN7150ClassCmdHeader_t;

typedef struct					PN7150ClassCmdRsp_s
{
	PN7150ClassCmdHeader_t		header;
	uint8_t						status;
}								PN7150ClassCmdRsp_t;

typedef struct					PN7150ClassCmdRspReset_s
{
	PN7150ClassCmdHeader_t		header;
	uint8_t						status;
	uint8_t						nci_version;
	uint8_t						type;
}								PN7150ClassCmdRspReset_t;

typedef struct					PN7150ClassCmdRspGetConfigParametrTotalDuration_s
{
	uint8_t						sub;
	uint8_t						len;
	uint8_t						ms[0x2];/* LSB  to MSB */
}								PN7150ClassCmdRspGetConfigParametrTotalDuration_t;

typedef struct					PN7150ClassCmdRspGetConfigParametrExtEeprom_s
{
	uint8_t						sub;
	uint8_t						sub_add;
	uint8_t						len;
	uint8_t						buffer[PN7150_CLASS_EEPROM_SIZE];
}								PN7150ClassCmdRspGetConfigParametrExtEeprom_t;

typedef struct					PN7150ClassCmdRspGetConfigParametrExtPowerTransmitterV1_s
{
	uint8_t						sub;
	uint8_t						sub_add;
	uint8_t						len;
	uint8_t						properties;
}								PN7150ClassCmdRspGetConfigParametrExtPowerTransmitterV1_t;

typedef struct					PN7150ClassCmdRspGetConfigParametrExtPowerTransmitterV2_s
{
	uint8_t						sub;
	uint8_t						sub_add;
	uint8_t						len;
	uint8_t						properties1;
	uint8_t						properties2;
	uint8_t						properties3;
}								PN7150ClassCmdRspGetConfigParametrExtPowerTransmitterV2_t;

typedef union					PN7150ClassCmdRspGetConfigParametrs_u
{
	PN7150ClassCmdRspGetConfigParametrTotalDuration_t			duration;
	PN7150ClassCmdRspGetConfigParametrExtEeprom_t				eeprom;
	PN7150ClassCmdRspGetConfigParametrExtPowerTransmitterV1_t	power_transmitter_v1;
	PN7150ClassCmdRspGetConfigParametrExtPowerTransmitterV2_t	power_transmitter_v2;
}								PN7150ClassCmdRspGetConfigParametrs_t;

typedef struct					PN7150ClassCmdRspGetConfig_s
{
	PN7150ClassCmdHeader_t		header;
	uint8_t						status;
	uint8_t						NumberofParameters;
	PN7150ClassCmdRspGetConfigParametrs_t	parametrs[];
}								PN7150ClassCmdRspGetConfig_t;

typedef struct					PN7150ClassCmdRspSetConfig_s
{
	PN7150ClassCmdHeader_t		header;
	uint8_t						status;
	uint8_t						NumberofParameters;
	uint8_t						parametrs[];
}								PN7150ClassCmdRspSetConfig_t;

typedef struct					PN7150ClassCmdRspSetPowerMode_s
{
	PN7150ClassCmdHeader_t		header;
	uint8_t						status;
}								PN7150ClassCmdRspSetPowerMode_t;

typedef struct					PN7150ClassCmdNtfRfIntfActivated_s
{
	PN7150ClassCmdHeader_t		header;
	uint8_t						id;
	uint8_t						interface;//If this contains a value of 0x00 (NFCEE Direct RF Interface) then all following parameters SHALL contain a value of 0 and SHALL be ignored
	uint8_t						protocol;
	uint8_t						mode_tech;//RF Technology and Mode of the local device that were used for the collection of the RF Technology Specific Parameters below
	uint8_t						max_data;//Max Data Packet Payload Size the NFCC can receive for the Static RF Connection. A number from 1 – 255
	uint8_t						InitialNumberofCredits;//Initial Number of Credits given by the NFCC to the DH for the Static RF Connection
	uint8_t						len_parameters;//The length of RF Technology Specific Parameters field to follow
	PN7150ClassRfNfcInfo_t		parameters;//One of the below tables depending on the value of the RF Technology and Mode;Depends on RF Technology and Mode
	// .... - есть еще параметры
}								PN7150ClassCmdNtfRfIntfActivated_t;

typedef struct					PN7150ClassRfDiscoverNtf_s
{
	PN7150ClassCmdHeader_t		header;
	uint8_t						id;
	uint8_t						protocol;
	uint8_t						mode_tech;//RF Technology and Mode of the local device that were used for the collection of the RF Technology Specific Parameters below
	uint8_t						len_parameters;//The length of RF Technology Specific Parameters field to follow
	PN7150ClassRfNfcInfo_t		parameters;//One of the below tables depending on the value of the RF Technology and Mode;Depends on RF Technology and Mode
	// .... - есть еще параметры 
}								PN7150ClassRfDiscoverNtf_t;

typedef struct					PN7150ClassRfDeactivateNtf_s
{
	PN7150ClassCmdHeader_t		header;
	uint8_t						mode;
	uint8_t						reason;
}								PN7150ClassRfDeactivateNtf_t;

typedef struct					PN7150ClassNdefNtf_s
{
	PN7150ClassCmdHeader_t		header;
	uint8_t						parameters[];//tag-len-value
}								PN7150ClassNdefNtf_t;

typedef union						PN7150ClassCmdRspCommon_u
{
	uint8_t							buffer[PN7150_CLASS_MAX_NCI_FRAME_SIZE];
	PN7150ClassCmdRsp_t				rsp;
	PN7150ClassCmdHeader_t			ntf;
	PN7150ClassNdefNtf_t			ndef;
	PN7150ClassCmdRspReset_t		core_reset;
	PN7150ClassCmdRspGetConfig_t	get_config;
	PN7150ClassCmdRspSetConfig_t	set_config;
	PN7150ClassCmdRspSetPowerMode_t	power_mode;
	PN7150ClassCmdNtfRfIntfActivated_t	rf_intf_activated;
	PN7150ClassRfDiscoverNtf_t		RfDiscoverNtf;
	PN7150ClassRfDeactivateNtf_t	RfDeactivateNtf;
}									PN7150ClassCmdRspCommon_t;

typedef struct					PN7150ClassCmdSetConfigExtPowerTransmitterV1_s
{
	PN7150ClassCmdHeader_t		header;
	uint8_t						NumberofParameters;
	uint8_t						sub;
	uint8_t						sub_add;
	uint8_t						sub_len;
	uint8_t						properties;
}								PN7150ClassCmdSetConfigExtPowerTransmitterV1_t;

typedef struct					PN7150ClassCmdSetConfigExtPowerTransmitterV2_s
{
	PN7150ClassCmdHeader_t		header;
	uint8_t						NumberofParameters;
	uint8_t						sub;
	uint8_t						sub_add;
	uint8_t						sub_len;
	uint8_t						properties1;
	uint8_t						properties2;
	uint8_t						properties3;
}								PN7150ClassCmdSetConfigExtPowerTransmitterV2_t;

typedef struct					PN7150ClassCmdSetDiscoveryParameters_s
{
	uint8_t						mode_tech;
	uint8_t						freq;
}								PN7150ClassCmdSetDiscoveryParameters_t;

typedef struct					PN7150ClassCmdSetDiscovery_s
{
	PN7150ClassCmdHeader_t		header;
	uint8_t						NumberofParameters;
	PN7150ClassCmdSetDiscoveryParameters_t		parameters[];
}								PN7150ClassCmdSetDiscovery_t;

typedef struct					PN7150ClassCmdSetPowerMode_s
{
	PN7150ClassCmdHeader_t		header;
	uint8_t						mode;
}								PN7150ClassCmdSetPowerMode_t;

typedef struct					PN7150ClassCmdCoreReset_s
{
	PN7150ClassCmdHeader_t		header;
	uint8_t						type;
}								PN7150ClassCmdCoreReset_t;


typedef struct					PN7150ClassCmdCoreInit_s
{
	PN7150ClassCmdHeader_t		header;
}								PN7150ClassCmdCoreInit_t;

typedef struct					PN7150ClassCmdGetConfig_s
{
	PN7150ClassCmdHeader_t		header;
	uint8_t						NumberofParameters;
	uint8_t						parametrs[];
}								PN7150ClassCmdGetConfig_t;

typedef struct					PN7150ClassCmdSetConfigTotalDuration_s
{
	PN7150ClassCmdHeader_t		header;
	uint8_t						NumberofParameters;
	uint8_t						sub;
	uint8_t						sub_len;
	uint8_t						ms[0x2];/* LSB  to MSB */
}								PN7150ClassCmdSetConfigTotalDuration_t;

typedef struct					PN7150ClassCmdSetConfigExtEeprom_s
{
	PN7150ClassCmdHeader_t		header;
	uint8_t						NumberofParameters;
	uint8_t						sub;
	uint8_t						sub_add;
	uint8_t						sub_len;
	uint8_t						buffer[PN7150_CLASS_EEPROM_SIZE];
}								PN7150ClassCmdSetConfigExtEeprom_t;

typedef struct					PN7150ClassCmdRfDeactivate_s
{
	PN7150ClassCmdHeader_t		header;
	uint8_t						mode;
}								PN7150ClassCmdRfDeactivate_t;


typedef struct					PN7150ClassRfDiscoverSelectCmd_s
{
	PN7150ClassCmdHeader_t		header;
	uint8_t						DiscoveryID;
	uint8_t						protocol;
	uint8_t						interface;
}								PN7150ClassRfDiscoverSelectCmd_t;

typedef struct					PN7150ClassNdef_s
{
	PN7150ClassCmdHeader_t		header;
	uint8_t						value[];//tag-len-value
}								PN7150ClassNdef_t;

typedef struct					PN7150ClassNdefCmd_s
{
	PN7150ClassCmdHeader_t		header;
	uint8_t						cla;
	uint8_t						ins;
	uint8_t						p1;
	uint8_t						p2;
	uint8_t						lc;
	uint8_t						value[];//tag-len-value
}								PN7150ClassNdefCmd_t;


typedef struct					PN7150ClassNdefReadRecords_s
{
	PN7150ClassCmdHeader_t		header;
	uint8_t						cla;
	uint8_t						ins;
	uint8_t						p1;
	uint8_t						p2;
	uint8_t						le;
}								PN7150ClassNdefReadRecords_t;

typedef struct					PN7150ClassNdefAfl_s
{
	uint8_t						sfi;// Short file identifier
	uint8_t						srec;// номер первой записи SFI
	uint8_t						erec;// номер последней записи SFI
	uint8_t						number;// (Offline Data Authentication), т.е. для проверки подлинности карты.
}								PN7150ClassNdefAfl_t;

typedef enum					PN7150ClassStatus_e
{
	PN7150ClassStatusOk = 0x0,//Good!!!
	PN7150ClassStatusI2cBegin,
	PN7150ClassStatusI2cReceive,
	PN7150ClassStatusI2cSend,
	PN7150ClassStatusReceiveTimeout,
	PN7150ClassStatusFailed,
	PN7150ClassStatusArgument,
	PN7150ClassStatusNew,
	PN7150ClassStatusNotSupport,
	PN7150ClassStatusClearConfig,
	PN7150ClassStatusHeader,
	PN7150ClassStatusFailedStatus,
	PN7150ClassStatusIrq,
	PN7150ClassStatusMemory,
	PN7150ClassStatusConfigure,
	PN7150ClassStatusActive,
	PN7150ClassStatusNotSupportInterface
}								PN7150ClassStatus_t;

typedef enum					PN7150ClassPowerMode_e
{
	PN7150ClassPowerModeIdle= 0x0,
	PN7150ClassPowerModeStandby
}								PN7150ClassPowerMode_t;

typedef enum					PN7150ClassPowerTransmitter_e
{
	PN7150ClassPowerTransmitter_2_7_V,
	PN7150ClassPowerTransmitter_3_0_V,
	PN7150ClassPowerTransmitter_3_1_V,
	PN7150ClassPowerTransmitter_3_3_V,
	PN7150ClassPowerTransmitter_3_6_V,
	PN7150ClassPowerTransmitter_4_5_V,
	PN7150ClassPowerTransmitter_4_7_V
}								PN7150ClassPowerTransmitter_t;


class PN7150Class {
	public:
		PN7150Class(TwoWire *wire, uint8_t scl, uint8_t sda, uint8_t irq, uint8_t ven, uint8_t addr = PN7150_CLASS_ADRESS_I2C);
		uint8_t											ppsePaymentSystem(uint8_t index, void *buffer, uint8_t len);
		uint8_t											ppseCardNumber(uint8_t index, void *buffer, uint8_t len);
		uint8_t											ppseExpirationDate(uint8_t index, void *buffer, uint8_t len);
		PN7150ClassStatus_t								ppse(uint8_t index);
		PN7150ClassStatus_t								setRf(void);
		PN7150ClassStatus_t								connect(bool clear=false);
		PN7150ClassStatus_t								discovery(void (*userFunc)(void));
		PN7150ClassStatus_t								discoveryRestart(void (*userFunc)(void));
		PN7150ClassStatus_t								configureMode(uint8_t mode);
		inline PN7150ClassStatus_t						configureMode(void) {return (this->configureMode(PN7150_CLASS_MODE_RW));};
		PN7150ClassStatus_t								info(uint8_t *count);
		PN7150ClassStatus_t								infoWaitRemoval(void (*userFunc)(uint8_t) = 0x0);
		uint8_t											infoSens(uint8_t index, void *buffer, uint8_t len);
		uint8_t											infoSel(uint8_t index, void *buffer, uint8_t len);
		uint8_t											infoId(uint8_t index, void *buffer, uint8_t len);
		uint8_t											infoAfi(uint8_t index, void *buffer, uint8_t len);
		uint8_t											infoDsfid(uint8_t index, void *buffer, uint8_t len);
		uint16_t										infoBitRate(uint8_t index);
		uint8_t											infoNfcid(uint8_t index, void *buffer, uint8_t len);
		uint8_t											infoProtocol(uint8_t index);
		PN7150ClassStatus_t								applySettings(void);
		PN7150ClassStatus_t								setPowerMode(PN7150ClassPowerMode_t mode);
		PN7150ClassStatus_t								setPowerTransmitter(PN7150ClassPowerTransmitter_t mode);
		PN7150ClassStatus_t								getPowerTransmitter(PN7150ClassPowerTransmitter_t *mode);
		PN7150ClassStatus_t								getEEPROM(uint8_t buffer[PN7150_CLASS_EEPROM_SIZE]);
		PN7150ClassStatus_t								setEEPROM(uint8_t buffer[PN7150_CLASS_EEPROM_SIZE]);
		PN7150ClassStatus_t								getDuration(uint16_t *ms);
		PN7150ClassStatus_t								setDuration(uint16_t ms);
		inline uint8_t									getHardwareVersion(void) {return (this->_NfcController_generation);};
		inline uint8_t									getRomVersion(void) {return (this->_NfcController_fw_version[0x0]);};
		inline uint8_t									getFwMajorVersion(void) {return (this->_NfcController_fw_version[0x1]);};
		inline uint8_t									getFwMinorVersion(void) {return (this->_NfcController_fw_version[0x2]);};

	private:
		inline PN7150ClassStatus_t						_ppsePan(const PN7150ClassTlvTag_t *tag, size_t len_tag, PN7150ClassRfNfc_t *info, PN7150ClassCmdRspCommon_t *answer);
		inline uint8_t									_tagGetData(const PN7150ClassTlvTag_t *tag, void *dst, size_t len);
		inline const PN7150ClassTlvTag_t				*_tagFind(const PN7150ClassTlvTag_t *tag, const PN7150ClassCmdRspCommon_t *answer);//tag-len-value - return
		inline const PN7150ClassTlvTag_t				*_tagFind_add(const PN7150ClassTlvTag_t *tag, const uint8_t *b, const uint8_t *e, size_t len);
		inline uint8_t									_tagGetLen(const PN7150ClassTlvTag_t *tag);
		inline PN7150ClassStatus_t						_select(PN7150ClassCmdRspCommon_t *answer, size_t index);
		inline PN7150ClassStatus_t						_removal(PN7150ClassCmdRspCommon_t *answer, PN7150ClassRfNfc_t *info);
		inline size_t									_protToIntf(size_t prot);
		inline size_t									_getCountCart(void);
		inline PN7150ClassStatus_t						_info(void);
		inline PN7150ClassRfNfc_t						*_info_set(PN7150ClassRfNfc_t *info, PN7150ClassCmdRspCommon_t *answer);
		inline PN7150ClassRfNfc_t						*_getInfo(uint8_t index);
		inline uint8_t									_info_finish(void *buffer, void *b, size_t count, uint8_t len);
		inline PN7150ClassStatus_t						_transceive(const void *pBuffer, PN7150ClassCmdRspCommon_t *answer);
		inline PN7150ClassStatus_t						_NxpNci_HostTransceive(const void *pBuffer, PN7150ClassCmdRspCommon_t *answer);
		inline PN7150ClassStatus_t						_NxpNci_ReaderTagCmd(const void *pBuffer, PN7150ClassCmdRspCommon_t *answer);
		inline PN7150ClassStatus_t						_NxpNci_CheckDevPres(PN7150ClassCmdRspCommon_t *answer, size_t bClear, PN7150ClassStatus_t *recovery);
		inline PN7150ClassStatus_t						_wireReceive_add(void *pBuffer, ssize_t timeout);
		inline PN7150ClassStatus_t						_wireReceive(PN7150ClassCmdRspCommon_t *answer, ssize_t timeout);
		inline size_t									_wireReceiveRead(void *pBuffer, size_t BufferLen);
		inline PN7150ClassStatus_t						_WaitForReceive(ssize_t timeout);
		inline PN7150ClassStatus_t						_wireSend(const void *pBuffer, size_t BufferLen);
		TwoWire									*_wire;
		PN7150ClassRfNfc_t						*_info_lp;
		uint8_t									_info_max;
		uint8_t									_info_count;
		uint8_t									_info_index;//текущий активны не равный 0x0
		uint8_t									_buffer_wire[(size_t)(PN7150_CLASS_MAX_NCI_FRAME_SIZE * 1.3)];
		uint8_t									_scl;
		uint8_t									_sda;
		uint8_t									_irq;
		uint8_t									_ven;
		uint8_t									_addr;
		uint8_t									_mode;
		uint8_t									_NfcController_generation;
		PN7150ClassRfNfc_t						_info_array[0x2];
		uint8_t									_NfcController_fw_version[0x3];
};

#endif//PN7150_H
