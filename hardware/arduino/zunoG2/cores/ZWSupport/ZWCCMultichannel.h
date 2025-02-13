#ifndef MULTICHANNEL_CC_H
#define MULTICHANNEL_CC_H

#include "ZWSupport.h"

#define MULTI_CHANNEL_VERSION_RELEASED 0x04

int zuno_CCMultichannel(ZUNOCommandCmd_t *cmd, ZUNOCommandPacketReport_t *frame_report);

#endif // MULTICHANNEL_CC_H