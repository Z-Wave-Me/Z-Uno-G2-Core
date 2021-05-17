#ifndef ZWCC_WAKEUP
#define ZWCC_WAKEUP
#include "Arduino.h"

#define WAKE_UP_INTERVAL_CAPABILITIES_GET                                             0x09
#define WAKE_UP_INTERVAL_CAPABILITIES_REPORT                                          0x0A
#define WAKE_UP_INTERVAL_GET                                                          0x05
#define WAKE_UP_INTERVAL_REPORT                                                       0x06
#define WAKE_UP_INTERVAL_SET                                                          0x04
#define WAKE_UP_NOTIFICATION                                                          0x07
#define WAKE_UP_NO_MORE_INFORMATION                                                   0x08

#ifndef WAKEUP_INTERVAL_MIN 
#define WAKEUP_INTERVAL_MIN                                                           60
#endif 
#ifndef WAKEUP_INTERVAL_MAX 
#define WAKEUP_INTERVAL_MAX                                                           3942000 // 3 years
#endif 
#ifndef WAKEUP_INTERVAL_DEFAULT 
#define WAKEUP_INTERVAL_DEFAULT                                                       3600 // Once in a hour
#endif 
#ifndef WAKEUP_INTERVAL_STEP 
#define WAKEUP_INTERVAL_STEP                                                          1 // One second
#endif 
#define WAKEUP_SLEEP_TIMEOUT                                                          3000
#define WAKEUP_MAXIMUM_CONTROLLER_TIMEOUT                                             15000 

void zuno_sendWUP_Notification();
void zuno_CCWakeup_OnSetup();
void zuno_CCWakeup_OnDefault();
int zuno_CCWakeupHandler(ZUNOCommandPacket_t * cmd);
void zuno_CCWakeup_OnAnyRx();


#endif // ZWCC_WAKEUP