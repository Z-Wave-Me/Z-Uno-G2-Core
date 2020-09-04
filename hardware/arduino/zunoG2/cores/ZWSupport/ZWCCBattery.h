#ifndef ZWCC_BATTERY
#define ZWCC_BATTERY
#include "Arduino.h"

#define BATTERY_GET                                                                      0x02
#define BATTERY_REPORT                                                                   0x03

void    zunoSendBatteryReport();
int     zuno_CCBattery(ZUNOCommandPacket_t * cmd);
void    zuno_CCBattery_OnSetup();
#endif // ZWCC_BATTERY