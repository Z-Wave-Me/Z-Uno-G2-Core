#include "Arduino.h"

#define MODEM_WUP_PIN					23//Btn

ZUNO_ENABLE(
	WITH_CC_BASIC
	WITH_CC_BATTERY
	WITH_CC_WAKEUP
);

void setup() {
	zunoEM4EnablePinWakeup(MODEM_WUP_PIN);
	zunoAttachSysHandler(ZUNO_HANDLER_SLEEP, 0, (void*) &_sleepHandler);
	zunoSetSleepingMode(ZUNO_SLEEPING_MODE_SLEEPING);
	if(zunoStartDeviceConfiguration()) {
		zunoEnableSmartStart(false);
		zunoCommitCfg();
	}
}

void _sleepHandler(void){
	zunoEM4EnablePinWakeup(MODEM_WUP_PIN);
}


void loop() {
	if (millis() > 5000)
		zunoSendDeviceToSleep();	
}