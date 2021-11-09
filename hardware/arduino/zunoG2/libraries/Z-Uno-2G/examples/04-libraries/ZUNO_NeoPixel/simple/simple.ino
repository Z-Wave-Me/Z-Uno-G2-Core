#include "Arduino.h"
#include "ZUNO_NeoPixel.h"

// NeoPixel Ring simple sketch
// Released under the GPLv3 license to match the rest of the


// Which pin on the Zuno is connected to the NeoPixels?
#define PIN        6

// How many NeoPixels are attached to the Zuno?
#define NUMPIXELS 16 // Popular NeoPixel ring size


#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

void setup() {
	NeoPixel.addNeo(PIN, NUMPIXELS, 255, NEO_GRB | NEO_KHZ800); 
}

void loop() {
	NeoPixel.clear(PIN); // Set all pixel colors to 'off'

	// The first NeoPixel in a strand is #0, second is 1, all the way up
	// to the count of pixels minus one.
	for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

		// NeoPixel.RGB() takes RGB values, from 0,0,0 up to 255,255,255
		// Here we're using a moderately bright green color:
		NeoPixel.setColor(PIN, i, NeoPixel.RGB(0, 150, 0));

		NeoPixel.show(PIN);   // Send the updated pixel colors to the hardware.

		delay(DELAYVAL); // Pause before next pass through loop
	}
}