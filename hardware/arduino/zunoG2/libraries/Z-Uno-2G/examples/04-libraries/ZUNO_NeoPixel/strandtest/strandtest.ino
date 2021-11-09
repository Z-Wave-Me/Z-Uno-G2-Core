#include "Arduino.h"
#include "ZUNO_NeoPixel.h"

// A basic everyday NeoPixel strip test program.

// NEOPIXEL BEST PRACTICES for most reliable operation:
// - Add 1000 uF CAPACITOR between NeoPixel strip's + and - connections.
// - MINIMIZE WIRING LENGTH between microcontroller board and first pixel.
// - NeoPixel strip's DATA-IN should pass through a 300-500 OHM RESISTOR.
// - AVOID connecting NeoPixels on a LIVE CIRCUIT. If you must, ALWAYS
//   connect GROUND (-) first, then +, then data.
// - When using a 3.3V microcontroller with a 5V-powered NeoPixel strip,
//   a LOGIC-LEVEL CONVERTER on the data line is STRONGLY RECOMMENDED.
// (Skipping these may work OK on your workbench but can fail in the field)


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
	// Fill along the length of the NeoPixel in various colors...
	colorWipe(NeoPixel.RGB(255,   0,   0), 50); // Red
	colorWipe(NeoPixel.RGB(  0, 255,   0), 50); // Green
	colorWipe(NeoPixel.RGB(  0,   0, 255), 50); // Blue

	// Do a theater marquee effect in various colors...
	theaterChase(NeoPixel.RGB(127, 127, 127), 50); // White, half brightness
	theaterChase(NeoPixel.RGB(127,   0,   0), 50); // Red, half brightness
	theaterChase(NeoPixel.RGB(  0,   0, 127), 50); // Blue, half brightness

	rainbow(10);             // Flowing rainbow cycle along the whole NeoPixel
	theaterChaseRainbow(50); // Rainbow-enhanced theaterChase variant
}


// Some functions of our own for creating animated effects -----------------

// Fill NeoPixel pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// NeoPixel.RGB(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(ZunoNeoColor_t color, int wait) {
	for(int i=0; i<LED_COUNT; i++) { // For each pixel in NeoPixel...
		NeoPixel.setColor(LED_PIN, i, color);         //  Set pixel's color (in RAM)
		NeoPixel.show(LED_PIN);                          //  Update NeoPixel to match
		delay(wait);                           //  Pause for a moment
	}
}

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la NeoPixel.RGB(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(ZunoNeoColor_t color, int wait) {
	for(int a=0; a<10; a++) {  // Repeat 10 times...
		for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
		NeoPixel.clear(LED_PIN);         //   Set all pixels in RAM to 0 (off)
		// 'c' counts up from 'b' to end of NeoPixel in steps of 3...
		for(int c=b; c<LED_COUNT; c += 3) {
			NeoPixel.setColor(LED_PIN, c, color); // Set pixel 'c' to value 'color'
		}
		NeoPixel.show(LED_PIN); // Update NeoPixel with new contents
		delay(wait);  // Pause for a moment
		}
	}
}

// Rainbow cycle along whole NeoPixel. Pass delay time (in ms) between frames.
void rainbow(int wait) {
	// Hue of first pixel runs 5 complete loops through the color wheel.
	// Color wheel has a range of 65536 but it's OK if we roll over, so
	// just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
	// means we'll make 5*65536/256 = 1280 passes through this outer loop:
	for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
		for(int i=0; i<LED_COUNT; i++) { // For each pixel in NeoPixel...
			// Offset pixel hue by an amount to make one full revolution of the
			// color wheel (range of 65536) along the length of the NeoPixel
			int16_t pixelHue = firstPixelHue + (int16_t)(i * 65536L / LED_COUNT);
			// NeoPixel.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
			// optionally add saturation and value (brightness) (each 0 to 255).
			// Here we're using just the single-argument hue variant. The result
			// is passed through NeoPixel.gamma32() to provide 'truer' colors
			// before assigning to each pixel:
			NeoPixel.setColor(LED_PIN, i, NeoPixel.gamma32(NeoPixel.ColorHSV(pixelHue)));
		}
		NeoPixel.show(LED_PIN); // Update NeoPixel with new contents
		delay(wait);  // Pause for a moment
	}
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
	int firstPixelHue = 0;     // First pixel starts at red (hue 0)
	for(int a=0; a<30; a++) {  // Repeat 30 times...
		for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
			NeoPixel.clear(LED_PIN);         //   Set all pixels in RAM to 0 (off)
			// 'c' counts up from 'b' to end of strip in increments of 3...
			for(int c=b; c<LED_COUNT; c += 3) {
				// hue of pixel 'c' is offset by an amount to make one full
				// revolution of the color wheel (range 65536) along the length
				// of the strip (LED_COUNT steps):
				int16_t      hue   = firstPixelHue + c * 65536L / LED_COUNT;
				NeoPixel.setColor(LED_PIN, c, NeoPixel.gamma32(NeoPixel.ColorHSV(hue))); // Set pixel 'c' to value 'color'
			}
			NeoPixel.show(LED_PIN);                // Update strip with new contents
			delay(wait);                 // Pause for a moment
			firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
		}
	}
}
