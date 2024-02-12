#ifndef ZWCC_USER_CODE_H
#define ZWCC_USER_CODE_H

#include "ZWSupport.h"

/* User Code command class commands */
#define USER_CODE_VERSION                                                                USER_CODE_VERSION_V2
#define USER_CODE_GET                                                                    0x02
#define USER_CODE_REPORT                                                                 0x03
#define USER_CODE_SET                                                                    0x01
#define USERS_NUMBER_GET                                                                 0x04
#define USERS_NUMBER_REPORT                                                              0x05
/* Values used for User Code Report command */
#define USER_CODE_REPORT_AVAILABLE_NOT_SET                                               0x00
#define USER_CODE_REPORT_OCCUPIED                                                        0x01
#define USER_CODE_REPORT_RESERVED_BY_ADMINISTRATOR                                       0x02
#define USER_CODE_REPORT_STATUS_NOT_AVAILABLE                                            0xFE
/* Values used for User Code Set command */
#define USER_CODE_SET_AVAILABLE_NOT_SET                                                  0x00
#define USER_CODE_SET_OCCUPIED                                                           0x01
#define USER_CODE_SET_RESERVED_BY_ADMINISTRATOR                                          0x02
#define USER_CODE_SET_STATUS_NOT_AVAILABLE                                               0xFE

/* User Code command class commands */
#define USER_CODE_VERSION_V2                                                             0x02
#define USER_CODE_GET_V2                                                                 0x02
#define USER_CODE_REPORT_V2                                                              0x03
#define USER_CODE_SET_V2                                                                 0x01
#define USERS_NUMBER_GET_V2                                                              0x04
#define USERS_NUMBER_REPORT_V2                                                           0x05
#define EXTENDED_USER_CODE_SET_V2                                                        0x0B
#define EXTENDED_USER_CODE_GET_V2                                                        0x0C
#define EXTENDED_USER_CODE_REPORT_V2                                                     0x0D
#define USER_CODE_CAPABILITIES_GET_V2                                                    0x06
#define USER_CODE_CAPABILITIES_REPORT_V2                                                 0x07
#define USER_CODE_KEYPAD_MODE_SET_V2                                                     0x08
#define USER_CODE_KEYPAD_MODE_GET_V2                                                     0x09
#define USER_CODE_KEYPAD_MODE_REPORT_V2                                                  0x0A
#define MASTER_CODE_SET_V2                                                               0x0E
#define MASTER_CODE_GET_V2                                                               0x0F
#define MASTER_CODE_REPORT_V2                                                            0x10
#define USER_CODE_CHECKSUM_GET_V2                                                        0x11
#define USER_CODE_CHECKSUM_REPORT_V2                                                     0x12
/* Values used for User Code Report command */
#define USER_CODE_REPORT_AVAILABLE_V2                                                    0x00
#define USER_CODE_REPORT_ENABLED_GRANT_ACCESS_V2                                         0x01
#define USER_CODE_REPORT_DISABLED_V2                                                     0x02
#define USER_CODE_REPORT_MESSAGING_V2                                                    0x03
#define USER_CODE_REPORT_PASSAGE_MODE_V2                                                 0x04
#define USER_CODE_REPORT_STATUS_NOT_AVAILABLE_V2                                         0xFE
/* Values used for User Code Set command */
#define USER_CODE_SET_AVAILABLE_V2                                                       0x00
#define USER_CODE_SET_ENABLED_GRANT_ACCESS_V2                                            0x01
#define USER_CODE_SET_DISABLED_V2                                                        0x02
#define USER_CODE_SET_MESSAGING_V2                                                       0x03
#define USER_CODE_SET_PASSAGE_MODE_V2                                                    0x04
#define USER_CODE_SET_STATUS_NOT_AVAILABLE_V2                                            0xFE
/* Values used for Extended User Code Set command */
#define EXTENDED_USER_CODE_SET_AVAILABLE_V2                                              0x00
#define EXTENDED_USER_CODE_SET_ENABLED_GRANT_ACCESS_V2                                   0x01
#define EXTENDED_USER_CODE_SET_DISABLED_V2                                               0x02
#define EXTENDED_USER_CODE_SET_MESSAGING_V2                                              0x03
#define EXTENDED_USER_CODE_SET_PASSAGE_MODE_V2                                           0x04
#define EXTENDED_USER_CODE_SET_STATUS_NOT_AVAILABLE_V2                                   0xFE
/* Values used for Extended User Code Get command */
#define EXTENDED_USER_CODE_GET_PROPERTIES1_REPORT_MORE_BIT_MASK_V2                       0x01
#define EXTENDED_USER_CODE_GET_PROPERTIES1_RESERVED_MASK_V2                              0xFE
#define EXTENDED_USER_CODE_GET_PROPERTIES1_RESERVED_SHIFT_V2                             0x01
/* Values used for Extended User Code Report command */
#define EXTENDED_USER_CODE_REPORT_AVAILABLE_V2                                           0x00
#define EXTENDED_USER_CODE_REPORT_ENABLED_GRANT_ACCESS_V2                                0x01
#define EXTENDED_USER_CODE_REPORT_DISABLED_V2                                            0x02
#define EXTENDED_USER_CODE_REPORT_MESSAGING_V2                                           0x03
#define EXTENDED_USER_CODE_REPORT_PASSAGE_MODE_V2                                        0x04
#define EXTENDED_USER_CODE_REPORT_STATUS_NOT_AVAILABLE_V2                                0xFE
/* Values used for User Code Capabilities Report command */
#define USER_CODE_CAPABILITIES_REPORT_PROPERTIES1_SUPPORTED_USER_ID_STATUS_BIT_MASK_LENGTH_MASK_V2 0x1F
#define USER_CODE_CAPABILITIES_REPORT_PROPERTIES1_RESERVED1_BIT_MASK_V2                  0x20
#define USER_CODE_CAPABILITIES_REPORT_PROPERTIES1_MCD_SUPPORT_BIT_MASK_V2                0x40
#define USER_CODE_CAPABILITIES_REPORT_PROPERTIES1_MC_SUPPORT_BIT_MASK_V2                 0x80
#define USER_CODE_CAPABILITIES_REPORT_PROPERTIES2_SUPPORTED_KEYPAD_MODES_BIT_MASK_LENGTH_MASK_V2 0x1F
#define USER_CODE_CAPABILITIES_REPORT_PROPERTIES2_MUCS_SUPPORT_BIT_MASK_V2               0x20
#define USER_CODE_CAPABILITIES_REPORT_PROPERTIES2_MUCR_SUPPORT_BIT_MASK_V2               0x40
#define USER_CODE_CAPABILITIES_REPORT_PROPERTIES2_UCC_SUPPORT_BIT_MASK_V2                0x80
#define USER_CODE_CAPABILITIES_REPORT_PROPERTIES3_SUPPORTED_KEYS_BIT_MASK_LENGTH_MASK_V2 0x1F
#define USER_CODE_CAPABILITIES_REPORT_PROPERTIES3_RESERVED2_MASK_V2                      0xE0
#define USER_CODE_CAPABILITIES_REPORT_PROPERTIES3_RESERVED2_SHIFT_V2                     0x05
/* Values used for User Code Keypad Mode Set command */
#define USER_CODE_KEYPAD_MODE_SET_NORMAL_MODE_V2                                         0x00
#define USER_CODE_KEYPAD_MODE_SET_VACATION_MODE_V2                                       0x01
#define USER_CODE_KEYPAD_MODE_SET_PRIVACY_MODE_V2                                        0x02
#define USER_CODE_KEYPAD_MODE_SET_LOCKED_OUT_MODE_V2                                     0x03
/* Values used for User Code Keypad Mode Report command */
#define USER_CODE_KEYPAD_MODE_REPORT_NORMAL_MODE_V2                                      0x00
#define USER_CODE_KEYPAD_MODE_REPORT_VACATION_MODE_V2                                    0x01
#define USER_CODE_KEYPAD_MODE_REPORT_PRIVACY_MODE_V2                                     0x02
#define USER_CODE_KEYPAD_MODE_REPORT_LOCKED_OUT_MODE_V2                                  0x03
/* Values used for Master Code Set command */
#define MASTER_CODE_SET_PROPERTIES1_MASTER_CODE_LENGTH_MASK_V2                           0x0F
#define MASTER_CODE_SET_PROPERTIES1_RESERVED_MASK_V2                                     0xF0
#define MASTER_CODE_SET_PROPERTIES1_RESERVED_SHIFT_V2                                    0x04
/* Values used for Master Code Report command */
#define MASTER_CODE_REPORT_PROPERTIES1_MASTER_CODE_LENGTH_MASK_V2                        0x0F
#define MASTER_CODE_REPORT_PROPERTIES1_RESERVED_MASK_V2                                  0xF0
#define MASTER_CODE_REPORT_PROPERTIES1_RESERVED_SHIFT_V2                                 0x04


typedef struct									ZwMasterCodeSetFrame_s
{
	uint8_t										cmdClass;/* The command class */
	uint8_t										cmd;/* The command */
	uint8_t										properties1;/* masked byte */
	uint8_t										masterCode[];
}												ZwMasterCodeSetFrame_t;


typedef struct									ZwMasterCodeReportFrame_s
{
	uint8_t										cmdClass;/* The command class */
	uint8_t										cmd;/* The command */
	uint8_t										properties1;/* masked byte */
	uint8_t										masterCode[];
}												ZwMasterCodeReportFrame_t;

/************************************************************/
/* User Code Checksum Report V2 command class structs */    
/************************************************************/
typedef struct _ZW_USER_CODE_CHECKSUM_REPORT_V2_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   userCodeChecksum1;            /* MSB */
    uint8_t   userCodeChecksum2;            /* LSB */
} ZW_USER_CODE_CHECKSUM_REPORT_V2_FRAME;

typedef struct									ZwExtendedUserCodeSetFrameVg_s
{
	uint8_t										userIdentifier1;/* MSB */
	uint8_t										userIdentifier2;/* LSB */
	uint8_t										userIdStatus;/**/
	uint8_t										properties1;/* masked byte */
	uint8_t										userCode[];/* MSB  LSB */
}												ZwExtendedUserCodeSetFrameVg_t;

typedef struct									ZwExtendedUserCodeSetFrameStart_s
{
	uint8_t										cmdClass;/* The command class */
	uint8_t										cmd;/* The command */
	uint8_t										numberOfUserCodes;/**/
}												ZwExtendedUserCodeSetFrameStart_t;

/************************************************************/
/* User Code Keypad Mode Set V2 command class structs */    
/************************************************************/
typedef struct _ZW_USER_CODE_KEYPAD_MODE_SET_V2_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   keypadMode;                   /**/
} ZW_USER_CODE_KEYPAD_MODE_SET_V2_FRAME;

/************************************************************/
/* User Code Keypad Mode Report V2 command class structs */ 
/************************************************************/
typedef struct _ZW_USER_CODE_KEYPAD_MODE_REPORT_V2_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   keypadMode;                   /**/
} ZW_USER_CODE_KEYPAD_MODE_REPORT_V2_FRAME;

/************************************************************/
/* Extended User Code Get V2 command class structs */       
/************************************************************/
typedef struct _ZW_EXTENDED_USER_CODE_GET_V2_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   userIdentifier1;              /* MSB */
    uint8_t   userIdentifier2;              /* LSB */
    uint8_t   properties1;                  /* masked byte */
} ZW_EXTENDED_USER_CODE_GET_V2_FRAME;


typedef struct								ZwExtendedUserCodeReportFrameStart_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									numberOfUserCodes;
}											ZwExtendedUserCodeReportFrameStart_t;

typedef struct								ZwExtendedUserCodeReportFrameVg_s
{
	uint8_t									userIdentifier1;/* MSB */
	uint8_t									userIdentifier2;/* LSB */
	uint8_t									userIdStatus;/**/
	uint8_t									properties1;/* masked byte */
	uint8_t									userCode[];/* MSB  LSB */
}											ZwExtendedUserCodeReportFrameVg_t;

typedef struct								ZwExtendedUserCodeReportFrameEnd_s
{
	uint8_t									nextUserIdentifier1;/* MSB */
	uint8_t									nextUserIdentifier2;/* LSB */
}											ZwExtendedUserCodeReportFrameEnd_t;

typedef struct								ZwUserCodeSetFrame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									userIdentifier;/**/
	uint8_t									userIdStatus;/**/
	uint8_t									userCode[];/* MSB  LSB */
}											ZwUserCodeSetFrame_t;

/************************************************************/
/* User Code Get command class structs */                   
/************************************************************/
typedef struct _ZW_USER_CODE_GET_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   userIdentifier;               /**/
} ZW_USER_CODE_GET_FRAME;

typedef struct								ZwUserCodeReportFrame_s
{
	uint8_t									cmdClass;/* The command class */
	uint8_t									cmd;/* The command */
	uint8_t									userIdentifier;/**/
	uint8_t									userIdStatus;/**/
	uint8_t									userCode[];/* MSB  LSB */
}											ZwUserCodeReportFrame_t;

/************************************************************/
/* User Code Capabilities Get V2 command class structs */   
/************************************************************/
typedef struct _ZW_USER_CODE_CAPABILITIES_GET_V2_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
} ZW_USER_CODE_CAPABILITIES_GET_V2_FRAME;

/************************************************************/
/* User Code Capabilities Report 1byte V2 command class structs */
/************************************************************/
typedef struct _ZW_USER_CODE_CAPABILITIES_REPORT_1BYTE_V2_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   properties1;                  /* masked byte */
    uint8_t   supportedUserIdStatusBitMask1;
    uint8_t   properties2;                  /* masked byte */
    uint8_t   supportedKeypadModesBitMask1; 
    uint8_t   properties3;                  /* masked byte */
    uint8_t   supportedKeysBitMask1;        
} ZW_USER_CODE_CAPABILITIES_REPORT_1BYTE_V2_FRAME;

/************************************************************/
/* Users Number Get command class structs */                
/************************************************************/
typedef struct _ZW_USERS_NUMBER_GET_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
} ZW_USERS_NUMBER_GET_FRAME;


/************************************************************/
/* Users Number Report command class structs */             
/************************************************************/
typedef struct _ZW_USERS_NUMBER_REPORT_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   supportedUsers;               /**/
} ZW_USERS_NUMBER_REPORT_FRAME;


/************************************************************/
/* Users Number Report V2 command class structs */          
/************************************************************/
typedef struct _ZW_USERS_NUMBER_REPORT_V2_FRAME_
{
    uint8_t   cmdClass;                     /* The command class */
    uint8_t   cmd;                          /* The command */
    uint8_t   supportedUsers;               /**/
    uint8_t   extendedSupportedUsers1;      /* MSB */
    uint8_t   extendedSupportedUsers2;      /* LSB */
} ZW_USERS_NUMBER_REPORT_V2_FRAME;

typedef union								ZW_USERS_NUMBER_REPORT_FRAME_u {//For more convenient support, several versions of commands
	ZW_USERS_NUMBER_REPORT_FRAME			v1;
	ZW_USERS_NUMBER_REPORT_V2_FRAME			v2;
}											ZW_USERS_NUMBER_REPORT_FRAME_t;

#define USER_CODE_STATUS_AVAILABLE						0x0
#define USER_CODE_STATUS_ENABLED_GRANT_ACCESS			0x1
#define USER_CODE_STATUS_DISABLED						0x2

#define USER_CODE_KEYPAD_MODE_NORMA						0x0
#define USER_CODE_KEYPAD_MODE_VACATION					0x1


#define ZUNO_SETUP_USER_CODE_KEYS_COMMON(...)	\
								const uint8_t *__g_zuno_user_code_asii_function(void) { \
									static uint8_t _user_code_asii_mask[0x10]; \
									size_t					tempos; \
									size_t					i; \
									_user_code_asii_mask[0x6] = 0xFF; \
									_user_code_asii_mask[0x7] = 0x3; \
									__VA_ARGS__ ;\
									return (&_user_code_asii_mask[0x0]);\
								} \

#define ZUNO_SETUP_USER_CODE_KEYS_SET(KEY)		\
									if (KEY <= 0x7F) { \
									tempos = KEY; \
									i = tempos / 0x8; \
									_user_code_asii_mask[i] = _user_code_asii_mask[i] | (0x1 << (tempos % 0x8)); \
									} \

#define ZUNO_SETUP_USER_CODE_KEYS_INTERVAL(START, END) \
									if (START <= 0x7F && END <= 0x7F && START <= END) { \
										tempos = START; \
										while (tempos <= END) { \
											i = tempos / 0x8; \
											_user_code_asii_mask[i] = _user_code_asii_mask[i] | (0x1 << (tempos % 0x8)); \
											tempos++; \
										} \
									} \

int zuno_CCUserCodeHandler(ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report);

#endif// ZWCC_TIMER_PARAMETERS_H