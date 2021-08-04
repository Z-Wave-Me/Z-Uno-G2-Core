#include "Arduino.h"

#define MODEM_WUP_PIN					23//Btn

ZUNO_ENABLE(WITH_CC_BATTERY LOGGING_DBG LOGGING_UART=Serial0);
uint32_t int_cnt=0;
uint32_t last_wake_time = 0;
void pinWakeInt(){
	int_cnt++;
}

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, 1);
    Serial0.begin();
    Serial0.print("START");
	pinMode(MODEM_WUP_PIN, INPUT_PULLUP_FILTER);
    attachInterrupt(MODEM_WUP_PIN, &pinWakeInt, FALLING);
	zunoAttachSysHandler(ZUNO_HANDLER_SLEEP, 0, (void*) &_sleepHandler);
    zunoAttachSysHandler(ZUNO_HANDLER_WUP, 0, (void*) &_wakeHandler);
    
    if(zunoStartDeviceConfiguration()) {
        zunoSetSleepingMode(ZUNO_SLEEPING_MODE_SLEEPING);
        zunoCommitCfg();
    }
    last_wake_time = millis();
	zunoSetSleepingMode(ZUNO_SLEEPING_MODE_SLEEPING);

}
void _wakeHandler(void){
    digitalWrite(LED_BUILTIN, 1);
    last_wake_time = millis();
}
void _sleepHandler(void){
    digitalWrite(LED_BUILTIN, 0);
	zunoEM4EnablePinWakeup(MODEM_WUP_PIN);
}


void loop() {
    Serial0.print("millis:");
    Serial0.print(millis());
    Serial0.print(" last wake:");
    Serial0.print(last_wake_time);
    Serial0.print(" ints:");
    Serial0.println(int_cnt);

	if ((millis() - last_wake_time) > 5000)
		zunoSendDeviceToSleep();
    	
}