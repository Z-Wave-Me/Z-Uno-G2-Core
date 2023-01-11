#ifndef ZME_SYSTEM_SERVICE
#define ZME_SYSTEM_SERVICE
#include <Arduino.h>
#define SYSLED_ACTIVITY     28
#define SYSLED_LEARN        29
#define SYSBUTTON           BUTTON_PIN
#define SYS_LEARN_TIMEOUT   30
#define SUBMENU_TIMEOUT     10000
#define ERROR_IDENTITY_TIMEOUT 10000
#define ERROR_IDENTITY_DELAY   2000


enum{
    SYSLED_ACTIVITY_MODE_BLINK = 0
};
enum{
    SYSLED_LEARN_MODE_INCLUSION = 0,
    SYSLED_LEARN_MODE_SUBMENU_READY,
    SYSLED_LEARN_MODE_IDENTITY,
    SYSLED_LEARN_MODE_WAITING_RST,
    SYSLED_LEARN_MODE_SYSERROR_MEMORY,
    SYSLED_LEARN_MODE_SYSERROR_HW,
    SYSLED_LEARN_MODE_SYSERROR_WDOG,
};
enum{
    SYS_SVC_MODE_NORMAL = 0,
    SYS_SVC_MODE_SUBMENU = 1,
    SYS_SVC_MODE_LEARN = 2       
};

void SysServiceInit();
void SysServiceTimer();
void SysReconfigLeds();
void SysServiceEvent(ZUNOSysEvent_t * ev);
void SysServiceSleep();
void SysSetLearnLedMode(uint8_t mode, uint32_t timeout);

#endif // ZME_SYSTEM_SERVICE