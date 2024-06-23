#ifndef ZUNO_SLEEP_H
#define ZUNO_SLEEP_H

void zunoSetSleepTimeout(uint8_t index, uint32_t timeout);
void zunoMarkDeviceToSleep(uint8_t mode = SLEEP_MODE_EM4);
void zunoSendDeviceToSleep(uint8_t mode = SLEEP_MODE_EM4);
void zunoLockSleep(void);
bool zunoIsSleepLocked();
void zunoKickSleepTimeout(uint32_t ms);
void zunoSetSleepingMode(byte mode);
uint8_t zunoGetSleepingMode(void);

#ifdef WITH_CC_WAKEUP
void zunoSendWakeUpNotification();
#endif
#ifdef WITH_CC_BATTERY
void zunoSendBatteryReport();
#endif


#endif//ZUNO_SLEEP_H