#include "Arduino.h"
#include "ZUNO_NeoPixel.h"

/*
 * Demo sketch for NeoPxel library for Z-Uno
 * (c) Z-Wave.Me 2017 for Z-Uno project
 * some ideas was used from Adafruit library 
 */

#define MY_SERIAL Serial0

/* LED counter */
#define LED_COUNT				150

/* LED pin number */
#define LED_PIN					9

/* the setup function runs once, when you press reset or power the board */
void setup() {
	MY_SERIAL.begin();
	MY_SERIAL.println("Setup");
	Neo.addNeo(LED_PIN, LED_COUNT);
}

/* the loop function runs over and over again forever */
void loop() {
	/* Turn on all LEDs */
	Neo.fill(LED_PIN, 0, LED_COUNT, Neo.RGB(255, 255, 0));
	/* Transferring colors to the ribbon */
	Neo.show(LED_PIN); 
	delay(500); 
	/* Turn off all LEDs */
	Neo.clear(LED_PIN);
	/* Transferring colors to the ribbon */
	Neo.show(LED_PIN); 
	delay(500); 
}
