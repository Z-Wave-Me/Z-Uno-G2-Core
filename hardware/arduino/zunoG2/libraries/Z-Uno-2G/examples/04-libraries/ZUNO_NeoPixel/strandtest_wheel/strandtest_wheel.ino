#include "Arduino.h"
#include "ZUNO_NeoPixel.h"

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.


// Which pin on the Zuno is connected to the NeoPixels?
#define LED_PIN    6

// How many NeoPixels are attached to the Zuno?
#define LED_COUNT 60


// setup() function -- runs once at startup --------------------------------
void setup() {
	NeoPixel.addNeo(LED_PIN, LED_COUNT, 50, NEO_GRB | NEO_KHZ800); // Set BRIGHTNESS to about 1/5 (max = 255)
	NeoPixel.show(LED_PIN);            // Turn OFF all pixels ASAP
}


// loop() function -- runs repeatedly as long as board is on ---------------
void loop() {
	// Some example procedures showing how to display to the pixels:
	colorWipe(NeoPixel.RGB(255, 0, 0), 50); // Red
	colorWipe(NeoPixel.RGB(0, 255, 0), 50); // Green
	colorWipe(NeoPixel.RGB(0, 0, 255), 50); // Blue
	//colorWipe(NeoPixel.RGB(0, 0, 0, 255), 50); // White RGBW
	// Send a theater pixel chase in...
	theaterChase(NeoPixel.RGB(127, 127, 127), 50); // White
	theaterChase(NeoPixel.RGB(127, 0, 0), 50); // Red
	theaterChase(NeoPixel.RGB(0, 0, 127), 50); // Blue

	rainbow(20);
	rainbowCycle(20);
	theaterChaseRainbow(50);
}

// Fill the dots one after the other with a color
void colorWipe(ZunoNeoColor_t color, uint8_t wait) {
	for(uint16_t i=0; i<LED_COUNT; i++) { // For each pixel in NeoPixel...
		NeoPixel.setColor(LED_PIN, i, color);         //  Set pixel's color (in RAM)
		NeoPixel.show(LED_PIN);                          //  Update NeoPixel to match
		delay(wait);                           //  Pause for a moment
	}
}

//Theatre-style crawling lights.
void theaterChase(ZunoNeoColor_t c, uint8_t wait) {
	ZunoNeoColor_t				color;

	color.color = 0x0;
	for (int j=0; j<10; j++) {  //do 10 cycles of chasing
		for (int q=0; q < 3; q++) {
			for (uint16_t i=0; i < LED_COUNT; i=i+3) {
				NeoPixel.setColor(LED_PIN,i+q, c);    //turn every third pixel on
			}
			NeoPixel.show(LED_PIN);
			delay(wait);
			for (uint16_t i=0; i < LED_COUNT; i=i+3) {
				NeoPixel.setColor(LED_PIN, i+q, color);        //turn every third pixel off
			}
		}
	}
}

void rainbow(uint8_t wait) {
	uint16_t i, j;

	for(j=0; j<256; j++) {
		for(i=0; i<LED_COUNT; i++) {
			NeoPixel.setColor(LED_PIN, i, Wheel((i+j) & 255));
		}
		NeoPixel.show(LED_PIN);
		delay(wait);
	}
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
	uint16_t i, j;

	for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
		for(i=0; i< LED_COUNT; i++) {
			NeoPixel.setColor(LED_PIN, i, Wheel(((i * 256 / LED_COUNT) + j) & 255));
		}
		NeoPixel.show(LED_PIN);
		delay(wait);
	}
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
	ZunoNeoColor_t				color;

	color.color = 0x0;
	for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
		for (int q=0; q < 3; q++) {
			for (uint16_t i=0; i < LED_COUNT; i=i+3) {
				NeoPixel.setColor(LED_PIN,i+q, Wheel( (i+j) % 255));    //turn every third pixel on
			}
			NeoPixel.show(LED_PIN);

			delay(wait);

			for (uint16_t i=0; i < LED_COUNT; i=i+3) {
				NeoPixel.setColor(LED_PIN, i+q, color);        //turn every third pixel off
			}
		}
	}
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
ZunoNeoColor_t Wheel(byte WheelPos) {
	WheelPos = 255 - WheelPos;
	if(WheelPos < 85) {
		return NeoPixel.RGB(255 - WheelPos * 3, 0, WheelPos * 3);
	}
	if(WheelPos < 170) {
		WheelPos -= 85;
		return NeoPixel.RGB(0, WheelPos * 3, 255 - WheelPos * 3);
	}
	WheelPos -= 170;
	return NeoPixel.RGB(WheelPos * 3, 255 - WheelPos * 3, 0);
}
