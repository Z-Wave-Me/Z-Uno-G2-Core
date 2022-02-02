#ifndef ZWCC_AUTHENTICATION_H
#define ZWCC_AUTHENTICATION_H

/* Authentication command class commands */
#define AUTHENTICATION_VERSION                                                           0x01
#define AUTHENTICATION_CAPABILITY_GET                                                    0x01
#define AUTHENTICATION_CAPABILITY_REPORT                                                 0x02
#define AUTHENTICATION_DATA_SET                                                          0x03
#define AUTHENTICATION_DATA_GET                                                          0x04
#define AUTHENTICATION_DATA_REPORT                                                       0x05
#define AUTHENTICATION_TECHNOLOGIES_COMBINATION_SET                                      0x06
#define AUTHENTICATION_TECHNOLOGIES_COMBINATION_GET                                      0x07
#define AUTHENTICATION_TECHNOLOGIES_COMBINATION_REPORT                                   0x08
#define AUTHENTICATION_CHECKSUM_GET                                                      0x09
#define AUTHENTICATION_CHECKSUM_REPORT                                                   0x0A
/* Values used for Authentication Capability Report command */
#define AUTHENTICATION_CAPABILITY_REPORT_PROPERTIES1_SUPPORTED_AUTHENTICATION_TECHNOLOGY_TYPE_BIT_MASK_LENGTH_MASK 0x0F
#define AUTHENTICATION_CAPABILITY_REPORT_PROPERTIES1_RESERVED1_BIT_MASK                  0x10
#define AUTHENTICATION_CAPABILITY_REPORT_PROPERTIES1_OR_BIT_MASK                         0x20
#define AUTHENTICATION_CAPABILITY_REPORT_PROPERTIES1_MADR_BIT_MASK                       0x40
#define AUTHENTICATION_CAPABILITY_REPORT_PROPERTIES1_MAR_BIT_MASK                        0x80
#define AUTHENTICATION_CAPABILITY_REPORT_PROPERTIES2_SUPPORTED_FALLBACK_STATUS_BIT_MASK_LENGTH_MASK 0x1F
#define AUTHENTICATION_CAPABILITY_REPORT_PROPERTIES2_RESERVED2_MASK                      0xE0
#define AUTHENTICATION_CAPABILITY_REPORT_PROPERTIES2_RESERVED2_SHIFT                     0x05
/* Values used for Authentication Data Set command */
#define AUTHENTICATION_DATA_SET_PROPERTIES1_AUTHENTICATION_TECHNOLOGY_TYPE_MASK          0x0F
#define AUTHENTICATION_DATA_SET_AUTHENTICATION_TECHNOLOGY_TYPE_RESERVED0                 0x00
#define AUTHENTICATION_DATA_SET_AUTHENTICATION_TECHNOLOGY_TYPE_RFID_TAG                  0x01
#define AUTHENTICATION_DATA_SET_AUTHENTICATION_TECHNOLOGY_TYPE_MAGNETIC_CARD             0x02
#define AUTHENTICATION_DATA_SET_PROPERTIES1_RESERVED1_MASK                               0xF0
#define AUTHENTICATION_DATA_SET_PROPERTIES1_RESERVED1_SHIFT                              0x04
/* Values used for Authentication Data Get command */
#define AUTHENTICATION_DATA_GET_PROPERTIES1_REPORT_MORE_BIT_MASK                         0x01
#define AUTHENTICATION_DATA_GET_PROPERTIES1_RESERVED1_MASK                               0xFE
#define AUTHENTICATION_DATA_GET_PROPERTIES1_RESERVED1_SHIFT                              0x01
/* Values used for Authentication Technologies Combination Set command */
#define AUTHENTICATION_TECHNOLOGIES_COMBINATION_SET_AVAILABLE                            0x00
#define AUTHENTICATION_TECHNOLOGIES_COMBINATION_SET_ENABLED                              0x01
#define AUTHENTICATION_TECHNOLOGIES_COMBINATION_SET_DISABLED                             0x02
#define AUTHENTICATION_TECHNOLOGIES_COMBINATION_SET_MESSAGING                            0x03
#define AUTHENTICATION_TECHNOLOGIES_COMBINATION_SET_PASSAGE_MODE                         0x04
#define AUTHENTICATION_TECHNOLOGIES_COMBINATION_SET_PROPERTIES1_NUMBER_OF_AUTHENTICATION_DATA_IDS_MASK 0x7F
#define AUTHENTICATION_TECHNOLOGIES_COMBINATION_SET_PROPERTIES1_OR_LOGIC_BIT_MASK        0x80
/* Values used for Authentication Technologies Combination Get command */
#define AUTHENTICATION_TECHNOLOGIES_COMBINATION_GET_PROPERTIES1_REPORT_MORE_BIT_MASK     0x01
#define AUTHENTICATION_TECHNOLOGIES_COMBINATION_GET_PROPERTIES1_RESERVED1_MASK           0xFE
#define AUTHENTICATION_TECHNOLOGIES_COMBINATION_GET_PROPERTIES1_RESERVED1_SHIFT          0x01
/* Values used for Authentication Technologies Combination Report command */
#define AUTHENTICATION_TECHNOLOGIES_COMBINATION_REPORT_AVAILABLE                         0x00
#define AUTHENTICATION_TECHNOLOGIES_COMBINATION_REPORT_ENABLED                           0x01
#define AUTHENTICATION_TECHNOLOGIES_COMBINATION_REPORT_DISABLED                          0x02
#define AUTHENTICATION_TECHNOLOGIES_COMBINATION_REPORT_MESSAGING                         0x03
#define AUTHENTICATION_TECHNOLOGIES_COMBINATION_REPORT_PASSAGE_MODE                      0x04
/* Values used for Authentication Checksum Get command */
#define AUTHENTICATION_CHECKSUM_GET_PROPERTIES1_AUTHENTICATION_TECHNOLOGY_TYPE_MASK      0x0F
#define AUTHENTICATION_CHECKSUM_GET_AUTHENTICATION_TECHNOLOGY_TYPE_RESERVED0             0x00
#define AUTHENTICATION_CHECKSUM_GET_AUTHENTICATION_TECHNOLOGY_TYPE_RFID_TAG              0x01
#define AUTHENTICATION_CHECKSUM_GET_AUTHENTICATION_TECHNOLOGY_TYPE_MAGNETIC_CARD         0x02
#define AUTHENTICATION_CHECKSUM_GET_PROPERTIES1_CHECKSUM_TYPE_MASK                       0x70
#define AUTHENTICATION_CHECKSUM_GET_PROPERTIES1_CHECKSUM_TYPE_SHIFT                      0x04
#define AUTHENTICATION_CHECKSUM_GET_CHECKSUM_TYPE_AUTHENTICATION_DATA                    0x00
#define AUTHENTICATION_CHECKSUM_GET_CHECKSUM_TYPE_COMBINATION_ENTRIES                    0x01
#define AUTHENTICATION_CHECKSUM_GET_CHECKSUM_TYPE_RESERVED2                              0x02
#define AUTHENTICATION_CHECKSUM_GET_CHECKSUM_TYPE_RESERVED3                              0x03
#define AUTHENTICATION_CHECKSUM_GET_CHECKSUM_TYPE_RESERVED4                              0x04
#define AUTHENTICATION_CHECKSUM_GET_CHECKSUM_TYPE_RESERVED5                              0x05
#define AUTHENTICATION_CHECKSUM_GET_CHECKSUM_TYPE_RESERVED6                              0x06
#define AUTHENTICATION_CHECKSUM_GET_CHECKSUM_TYPE_RESERVED7                              0x07
#define AUTHENTICATION_CHECKSUM_GET_PROPERTIES1_RESERVED1_BIT_MASK                       0x80
/* Values used for Authentication Checksum Report command */
#define AUTHENTICATION_CHECKSUM_REPORT_PROPERTIES1_AUTHENTICATION_TECHNOLOGY_TYPE_MASK   0x0F
#define AUTHENTICATION_CHECKSUM_REPORT_AUTHENTICATION_TECHNOLOGY_TYPE_RESERVED0          0x00
#define AUTHENTICATION_CHECKSUM_REPORT_AUTHENTICATION_TECHNOLOGY_TYPE_RFID_TAG           0x01
#define AUTHENTICATION_CHECKSUM_REPORT_AUTHENTICATION_TECHNOLOGY_TYPE_MAGNETIC_CARD      0x02
#define AUTHENTICATION_CHECKSUM_REPORT_PROPERTIES1_CHECKSUM_TYPE_MASK                    0x70
#define AUTHENTICATION_CHECKSUM_REPORT_PROPERTIES1_CHECKSUM_TYPE_SHIFT                   0x04
#define AUTHENTICATION_CHECKSUM_REPORT_CHECKSUM_TYPE_AUTHENTICATION_DATA                 0x00
#define AUTHENTICATION_CHECKSUM_REPORT_CHECKSUM_TYPE_COMBINATION_ENTRIES                 0x01
#define AUTHENTICATION_CHECKSUM_REPORT_CHECKSUM_TYPE_RESERVED2                           0x02
#define AUTHENTICATION_CHECKSUM_REPORT_CHECKSUM_TYPE_RESERVED3                           0x03
#define AUTHENTICATION_CHECKSUM_REPORT_CHECKSUM_TYPE_RESERVED4                           0x04
#define AUTHENTICATION_CHECKSUM_REPORT_CHECKSUM_TYPE_RESERVED5                           0x05
#define AUTHENTICATION_CHECKSUM_REPORT_CHECKSUM_TYPE_RESERVED6                           0x06
#define AUTHENTICATION_CHECKSUM_REPORT_CHECKSUM_TYPE_RESERVED7                           0x07
#define AUTHENTICATION_CHECKSUM_REPORT_PROPERTIES1_RESERVED1_BIT_MASK                    0x80

typedef struct												ZwAuthenticationTechnologiesCombinationSetStruc_s
{
	uint8_t													fallbackStatus;/**/
	uint8_t													userIdentifier1;/* MSB */
	uint8_t													userIdentifier2;/* LSB */
	uint8_t													scheduleId1;/* MSB */
	uint8_t													scheduleId2;/* LSB */
	uint8_t													properties1;/* masked byte */
}															ZwAuthenticationTechnologiesCombinationSetStruc_t;

typedef struct												ZwAuthenticationChecksumTypeCombination_s
{
	uint8_t													AuthenticationIDBlockLength;
	uint8_t													authenticationId1;/* MSB */
	uint8_t													authenticationId2;/* LSB */
	ZwAuthenticationTechnologiesCombinationSetStruc_t		st;
}															ZwAuthenticationChecksumTypeCombination_t;

/************************************************************/
/* Authentication Checksum Get command class structs */     
/************************************************************/
typedef struct _ZW_AUTHENTICATION_CHECKSUM_GET_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   properties1;                  /* masked byte */
} ZW_AUTHENTICATION_CHECKSUM_GET_FRAME;

/************************************************************/
/* Authentication Checksum Report command class structs */  
/************************************************************/
typedef struct _ZW_AUTHENTICATION_CHECKSUM_REPORT_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   properties1;                  /* masked byte */
    uint8_t   checksum1;                    /* MSB */
    uint8_t   checksum2;                    /* LSB */
} ZW_AUTHENTICATION_CHECKSUM_REPORT_FRAME;

typedef struct												ZwAuthenticationDataReportFrameStart_s
{
	uint8_t													cmdClass;/* The command class */
	uint8_t													cmd;/* The command */
	uint8_t													numberOfAuthenticationDataIdBlocks;/**/
}															ZwAuthenticationDataReportFrameStart_t;

typedef struct												ZwAuthenticationDataReportFrameMiddle_s
{
	uint8_t													authenticationDataId1;/* MSB */
	uint8_t													authenticationDataId2;/* LSB */
	uint8_t													properties1;/* masked byte */
	uint8_t													authenticationDataLength;/**/
	uint8_t													authenticationData[];/* MSB */
}															ZwAuthenticationDataReportFrameMiddle_t;

typedef struct												ZwAuthenticationDataReportFrameEnd_s
{
	uint8_t													nextAuthenticationDataId1;/* MSB */
	uint8_t													nextAuthenticationDataId2;/* LSB */
}															ZwAuthenticationDataReportFrameEnd_t;

/************************************************************/
/* Authentication Data Get command class structs */         
/************************************************************/
typedef struct _ZW_AUTHENTICATION_DATA_GET_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   authenticationDataId1;        /* MSB */
    uint8_t   authenticationDataId2;        /* LSB */
    uint8_t   properties1;                  /* masked byte */
} ZW_AUTHENTICATION_DATA_GET_FRAME;

typedef struct												ZwAuthenticationDataSetFrame_s
{
	uint8_t													cmdClass;/* The command class */
	uint8_t													cmd;/* The command */
	uint8_t													authenticationDataId1;/* MSB */
	uint8_t													authenticationDataId2;/* LSB */
	uint8_t													properties1;/* masked byte */
	uint8_t													authenticationDataLength;/**/
	uint8_t													authenticationData[];
}															ZwAuthenticationDataSetFrame_t;

typedef struct												ZwAuthenticationTechnologiesCombinationSetVg_s
{
	uint8_t													authenticationDataId1;/* MSB */
	uint8_t													authenticationDataId2;/* LSB */
}															ZwAuthenticationTechnologiesCombinationSetVg_t;

typedef struct											ZwAuthenticationTechnologiesCombinationReportFrameStart_s
{
	uint8_t												cmdClass;/* The command class */
	uint8_t												cmd;/* The command */
	uint8_t												numberOfAuthenticationIdBlocks;/**/
}														ZwAuthenticationTechnologiesCombinationReportFrameStart_t;

typedef struct											ZwAuthenticationTechnologiesCombinationReportFrameMiddle_s
{
	uint8_t												authenticationIdBlockLength;/**/
	uint8_t												authenticationId1;/* MSB */
	uint8_t												authenticationId2;/* LSB */
	ZwAuthenticationTechnologiesCombinationSetStruc_t	st;
	ZwAuthenticationTechnologiesCombinationSetVg_t		variantgroup[];/**/
}														ZwAuthenticationTechnologiesCombinationReportFrameMiddle_t;

typedef struct											ZwAuthenticationTechnologiesCombinationReportFrameEnd_s
{
	uint8_t												nextAuthenticationId1;/* MSB */
	uint8_t												nextAuthenticationId2;/* LSB */
}														ZwAuthenticationTechnologiesCombinationReportFrameEnd_t;

/************************************************************/
/* Authentication Technologies Combination Get command class structs */
/************************************************************/
typedef struct _ZW_AUTHENTICATION_TECHNOLOGIES_COMBINATION_GET_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   authenticationId1;            /* MSB */
    uint8_t   authenticationId2;            /* LSB */
    uint8_t   properties1;                  /* masked byte */
} ZW_AUTHENTICATION_TECHNOLOGIES_COMBINATION_GET_FRAME;

typedef struct												ZwAuthenticationTechnologiesCombinationSet_s
{
	uint8_t													cmdClass;/* The command class */
	uint8_t													cmd;/* The command */
	uint8_t													authenticationId1;/* MSB */
	uint8_t													authenticationId2;/* LSB */
	ZwAuthenticationTechnologiesCombinationSetStruc_t		st;
	ZwAuthenticationTechnologiesCombinationSetVg_t			variantgroup[];/**/
}															ZwAuthenticationTechnologiesCombinationSet_t;

typedef struct												ZwAuthenticationCapabilityReportFrameStart_s
{
	uint8_t													cmdClass;/* The command class */
	uint8_t													cmd;/* The command */
	uint8_t													supportedDataIdEntries1;/* MSB */
	uint8_t													supportedDataIdEntries2;/* LSB */
	uint8_t													supportedAuthenticationIdEntries1;/* MSB */
	uint8_t													supportedAuthenticationIdEntries2;/* LSB */
	uint8_t													properties1;/* masked byte */
	uint8_t													supportedAuthenticationTechnologyTypeBitMask[];/* MSB LSB */
}															ZwAuthenticationCapabilityReportFrameStart_t;

typedef struct												ZwAuthenticationCapabilityReportFrameEnd_s
{
	uint8_t													supportedChecksumTypeBitMask; /**/
	uint8_t													properties2;                  /* masked byte */
	uint8_t													supportedFallbackStatusBitMask[];/* MSB LSB */
}															ZwAuthenticationCapabilityReportFrameEnd_t;

#define AUTHENTICATION_TECHNOLOGY_TYPE_RFID_TAG									0x01
#define AUTHENTICATION_TECHNOLOGY_TYPE_MAGNETIC_CARD							0x02

#define AUTHENTICATION_STATUS_AVAILABLE						0x0
#define AUTHENTICATION_STATUS_ENABLED_GRANT_ACCESS			0x1
#define AUTHENTICATION_STATUS_DISABLED						0x2


typedef struct												ZwAuthenticationId_s
{
	ZwAuthenticationTechnologiesCombinationSetStruc_t		st;
	uint8_t													authenticationData[0x4];/* MSB LSB */ // or /* LSB MSB */ if pointer
}															ZwAuthenticationId_t;


#define ZUNO_SETUP_AUTHENTICATION_ID(...) 	\
							    ZwAuthenticationId_t __g_zuno_authentication_id[] = \
								{ \
									__VA_ARGS__, \
								};\
								uint16_t __g_zuno_authentication_id_count = (sizeof(__g_zuno_authentication_id) / sizeof(__g_zuno_authentication_id[0x0])); \


#define ZUNO_SETUP_AUTHENTICATION_ID_AVAILABLE()	\
{\
	.st = \
	{ \
		.fallbackStatus = AUTHENTICATION_STATUS_AVAILABLE, \
		.userIdentifier1 = 0x0, \
		.userIdentifier2 = 0x0, \
		.scheduleId1 = 0x0, \
		.scheduleId2 = 0x0, \
		.properties1 = 0x0, \
	}, \
	.authenticationData = {0x0} \
}\


typedef struct												ZwAuthenticationData_s
{
	uint8_t													authenticationDataLength;
	uint8_t													type;
	uint8_t													authenticationData[0x4];/* LSB MSB */ //- only pointer
}															ZwAuthenticationData_t;


#define ZUNO_SETUP_AUTHENTICATION_DATA(...) 	\
							    ZwAuthenticationData_t __g_zuno_authentication_data[] = \
								{ \
									__VA_ARGS__, \
								};\
								uint16_t __g_zuno_authentication_data_count = (sizeof(__g_zuno_authentication_data) / sizeof(__g_zuno_authentication_data[0x0])); \


#define ZUNO_SETUP_AUTHENTICATION_DATA_AVAILABLE()	\
{\
	.authenticationDataLength = 0x0, \
	.type = 0x0, \
	.authenticationData = {0x0} \
}\

int zuno_CCAuthenticationHandler(ZUNOCommandPacket_t *cmd);

#endif// ZWCC_AUTHENTICATION_H