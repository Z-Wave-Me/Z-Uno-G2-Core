#ifndef ZWCC_SECURITY_H
#define ZWCC_SECURITY_H

/* Security 2 command class commands */
#define SECURITY_2_VERSION                                                               0x01
#define SECURITY_2_NONCE_GET                                                             0x01
#define SECURITY_2_NONCE_REPORT                                                          0x02
#define SECURITY_2_MESSAGE_ENCAPSULATION                                                 0x03
#define KEX_GET                                                                          0x04
#define KEX_REPORT                                                                       0x05
#define KEX_SET                                                                          0x06
#define KEX_FAIL                                                                         0x07
#define PUBLIC_KEY_REPORT                                                                0x08
#define SECURITY_2_NETWORK_KEY_GET                                                       0x09
#define SECURITY_2_NETWORK_KEY_REPORT                                                    0x0A
#define SECURITY_2_NETWORK_KEY_VERIFY                                                    0x0B
#define SECURITY_2_TRANSFER_END                                                          0x0C
#define SECURITY_2_COMMANDS_SUPPORTED_GET                                                0x0D
#define SECURITY_2_COMMANDS_SUPPORTED_REPORT                                             0x0E

/************************************************************/
/* Security 2 Commands Supported Report command class structs */
/************************************************************/
typedef struct										ZwSecurity2CommandsSupportedFrame_s
{
	uint8_t											cmdClass;/* The command class */
	uint8_t											cmd;/* The command */
	uint8_t											commandClass[];
}													ZwSecurity2CommandsSupportedFrame_t;

int zuno_CCSecurity(ZUNOCommandPacket_t *cmd);

#endif//ZWCC_SECURITY_H