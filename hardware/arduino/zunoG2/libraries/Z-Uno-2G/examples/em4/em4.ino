#include "Arduino.h"

#define MODEM_WUP_PIN					23//Btn

void setup() {
	pinMode(MODEM_WUP_PIN, INPUT_PULLUP_FILTER);
	zunoAttachSysHandler(ZUNO_HANDLER_SLEEP, 0, (void*) &_sleepHandler);
	zunoSetSleepingMode(ZUNO_SLEEPING_MODE_SLEEPING);

}

void _sleepHandler(void){
	zunoEM4EnablePinWakeup(MODEM_WUP_PIN);
}


void loop() {
	if (millis() > 5000)
		zunoSendDeviceToSleep();	
}