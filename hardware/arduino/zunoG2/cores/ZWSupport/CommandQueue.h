#ifndef ZWPACKAGE_QUEUE
#define ZWPACKAGE_QUEUE
#include "LinkedList.h"
#include "Arduino.h"
#ifndef MAX_PROCESSED_QUEUE_PKGS
#define MAX_PROCESSED_QUEUE_PKGS 8
#endif
#ifndef MAX_SYS_QUEUE_PKGS
#define MAX_SYS_QUEUE_PKGS 3
#endif

#ifndef SYSTEM_PKG_DOMINATION_TIME
#define SYSTEM_PKG_DOMINATION_TIME 2000
#endif

bool ZWQPushPackage(ZUNOCommandPacket_t * pkg);
bool zunoExtractGroupNode(uint8_t g, uint8_t i, ZUnoAssocNode_t * node);
bool zunoCheckSystemQueueStatus(uint8_t channel);
ZUNOCommandPacket_t * ZWQFindPackage(uint8_t dst_id, uint8_t flags);
void ZWQProcess();
bool ZWQIsEmpty();


#endif // ZWPACKAGE_QUEUE