#include "Arduino.h"

#define MY_SERIAL Serial0

ZUNO_SETUP_ISR_GPTIMER(gpt_handler);

unsigned long count_gpt = 0;

void gpt_handler() {
	count_gpt++;
}

// the setup function runs once, when you press reset or power the board
void setup() {
	MY_SERIAL.begin();
	MY_SERIAL.println("Setup");
	zunoGPTInit(ZUNO_GPT_SCALE1024 | ZUNO_GPT_CYCLIC);
	zunoGPTSet(5000);
	zunoGPTEnable(1); 
}

// the loop function runs over and over again forever
void loop() {
	MY_SERIAL.println(count_gpt);
	delay(1000);
}