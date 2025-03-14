#ifndef ZWPACKAGE_QUEUE
#define ZWPACKAGE_QUEUE
#include "LinkedList.h"
#include "Arduino.h"
#ifndef MAX_PROCESSED_QUEUE_PKTS
#define MAX_PROCESSED_QUEUE_PKTS 8
#endif
#ifndef MAX_SYS_QUEUE_PKTS
#define MAX_SYS_QUEUE_PKTS 3
#endif

#ifndef CONTROLLER_INTERVIEW_REQUEST_INTERVAL
#define CONTROLLER_INTERVIEW_REQUEST_INTERVAL 2000
#endif

#ifndef SYSTEM_PKG_DOMINATION_TIME
#define SYSTEM_PKG_DOMINATION_TIME 2000
#endif

bool ZWQPushPacket(ZUNOCommandPacket_t * pkg);
bool zunoExtractGroupNode(uint8_t g, uint8_t i, ZUnoAssocNode_t * node);
bool zunoCheckSystemQueueStatus(uint8_t channel);
ZUNOCommandPacket_t * ZWQFindPackage(uint8_t dst_id, uint8_t flags, uint8_t cc, uint8_t cmd);
void ZWQProcess();
bool ZWQIsEmpty();
void ZWQIncomingStat(const ZUNOCommandCmd_t * pkg);


#endif // ZWPACKAGE_QUEUE