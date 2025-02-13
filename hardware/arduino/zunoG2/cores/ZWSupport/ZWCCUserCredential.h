#ifndef ZWCC_USER_CREDENTIAL_H
#define ZWCC_USER_CREDENTIAL_H

#include "ZWSupport.h"

#define USER_CREDENTIAL_VERSION_RELEASED 0x01

int zuno_CCUserCredentialHandler(const ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report, const ZUNOCommandHandlerOption_t *options);
bool zuno_CCUserCredentialIsBlockMultiBroadcast(size_t cmd);
ssize_t zuno_CCUserCredentialAssociationGroupCommand(_ZwAssociationGroupCommand_t *gpr_info, size_t gpr_info_max);

#endif// ZWCC_USER_CREDENTIAL_H