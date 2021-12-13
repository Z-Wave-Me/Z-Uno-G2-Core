#include "LeUartClass.h"

byte dimmerValue=0;
ZUNO_SETUP_SLEEPING_MODE(ZUNO_SLEEPING_MODE_FREQUENTLY_AWAKE);
ZUNO_SETUP_CHANNELS(ZUNO_SWITCH_MULTILEVEL(&dimmerValue,NULL));

#define MY_SERIAL LeUart

uint32_t loop_count = 0; // the variable that illustrates that RAM is alive during FLiRS mode too

void setup(){
	MY_SERIAL.begin(1200, LE_UART_SERIAL_8N1, 8, 7);
	MY_SERIAL.print("BOOT REASON:");
	MY_SERIAL.println(zunoGetWakeReason(), HEX);
	zunoAttachSysHandler(ZUNO_HANDLER_WUP, 0, (void*) &_wakeHandler);
	pinMode(LED_BUILTIN, OUTPUT);
	NVIC_ClearPendingIRQ(LEUART0_IRQn);
	NVIC_EnableIRQ(LEUART0_IRQn);
	LEUART0->SIGFRAME = '0';
	LEUART_IntEnable(LEUART0, LEUART_IEN_SIGF);
}
void _wakeHandler(void){
	MY_SERIAL.print("wake time:");
	MY_SERIAL.println(millis());
	MY_SERIAL.print("loop count =");
	MY_SERIAL.println(loop_count);
	MY_SERIAL.print("WAKEUP REASON:");
	MY_SERIAL.println(zunoGetWakeReason(), HEX);
}
void loop(){
	if(zunoIsSleepLocked()){
		// Here we do all sleep uninterruptable logic
		analogWrite(LED_BUILTIN, dimmerValue); // Apply dimmer value from controller to builtin LED
		MY_SERIAL.print("go sleep time:");
		MY_SERIAL.println(millis()); // Print moment when we are ready to go to sleep
		MY_SERIAL.print("loop count =");
		MY_SERIAL.println(loop_count);
		zunoSendDeviceToSleep(); // We don't need parameter for FLiRS here, Z-Uno will ingore parameter anyway
	}
	// Here you can do something that could be interrupted by sleep mode
	// ...
	loop_count++; // Increment variable
	delay(1000);
	MY_SERIAL.println("Loop");
}