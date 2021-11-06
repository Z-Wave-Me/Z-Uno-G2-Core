#include "Arduino.h"
#include "ZUNO_NeoPixel.h"

// Simple demonstration on using an input device to trigger changes on your
// NeoPixels. Wire a momentary push button to connect from ground to a
// digital IO pin. When the button is pressed it will change to a new pixel
// animation. Initial state has all pixels off -- press the button once to
// start the first animation. As written, the button does not interrupt an
// animation in-progress, it works only when idle.

// Digital IO pin connected to the button. This will be driven with a
// pull-up resistor so the switch pulls the pin to ground momentarily.
// On a high -> low transition the button press logic will execute.

#define PIXEL_PIN    6  // Digital IO pin connected to the NeoPixels.

#define PIXEL_COUNT 16  // Number of NeoPixels

boolean oldState = HIGH;
int     mode     = 0;    // Currently-active animation mode, 0-9

void setup() {
	pinMode(BUTTON_PIN, INPUT_PULLUP);
	NeoPixel.addNeo(PIXEL_PIN, PIXEL_COUNT, 255, NEO_GRB | NEO_KHZ800); 
	NeoPixel.show(PIXEL_PIN);            // Turn OFF all pixels ASAP
}


void loop() {
	// Get current button state.
	boolean newState = digitalRead(BUTTON_PIN);

	// Check if state changed from high to low (button press).
	if((newState == LOW) && (oldState == HIGH)) {
		// Short delay to debounce button.
		delay(20);
		// Check if button is still low after debounce.
		newState = digitalRead(BUTTON_PIN);
		if(newState == LOW) {      // Yes, still low
		if(++mode > 8) mode = 0; // Advance to next mode, wrap around after #8
		switch(mode) {           // Start the new animation...
			case 0:
				colorWipe(NeoPixel.RGB(  0,   0,   0), 50);    // Black/off
				break;
			case 1:
				colorWipe(NeoPixel.RGB(255,   0,   0), 50);    // Red
				break;
			case 2:
				colorWipe(NeoPixel.RGB(  0, 255,   0), 50);    // Green
				break;
			case 3:
				colorWipe(NeoPixel.RGB(  0,   0, 255), 50);    // Blue
				break;
			case 4:
				theaterChase(NeoPixel.RGB(127, 127, 127), 50); // White
				break;
			case 5:
				theaterChase(NeoPixel.RGB(127,   0,   0), 50); // Red
				break;
			case 6:
				theaterChase(NeoPixel.RGB(  0,   0, 127), 50); // Blue
				break;
			case 7:
				rainbow(10);
				break;
			case 8:
				theaterChaseRainbow(50);
			break;
		}
		}
	}

	// Set the last-read button state to the old state.
	oldState = newState;
}

// Fill NeoPixel pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// NeoPixel.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(ZunoNeoColor_t color, int wait) {
	for(int i=0; i<PIXEL_COUNT; i++) { // For each pixel in NeoPixel...
		NeoPixel.setColor(PIXEL_PIN, i, color);         //  Set pixel's color (in RAM)
		NeoPixel.show(PIXEL_PIN);                          //  Update NeoPixel to match
		delay(wait);                           //  Pause for a moment
	}
}

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la NeoPixel.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(ZunoNeoColor_t color, int wait) {
	for(int a=0; a<10; a++) {  // Repeat 10 times...
		for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
			NeoPixel.clear(PIXEL_PIN);         //   Set all pixels in RAM to 0 (off)
			// 'c' counts up from 'b' to end of NeoPixel in steps of 3...
			for(int c=b; c<PIXEL_COUNT; c += 3) {
				NeoPixel.setColor(PIXEL_PIN, c, color); // Set pixel 'c' to value 'color'
			}
			NeoPixel.show(PIXEL_PIN); // Update NeoPixel with new contents
			delay(wait);  // Pause for a moment
		}
	}
}

// Rainbow cycle along whole NeoPixel. Pass delay time (in ms) between frames.
void rainbow(int wait) {
	// Hue of first pixel runs 3 complete loops through the color wheel.
	// Color wheel has a range of 65536 but it's OK if we roll over, so
	// just count from 0 to 3*65536. Adding 256 to firstPixelHue each time
	// means we'll make 3*65536/256 = 768 passes through this outer loop:
	for(long firstPixelHue = 0; firstPixelHue < 3*65536; firstPixelHue += 256) {
		for(int i=0; i<PIXEL_COUNT; i++) { // For each pixel in NeoPixel...
			// Offset pixel hue by an amount to make one full revolution of the
			// color wheel (range of 65536) along the length of the NeoPixel
			// (PIXEL_COUNT steps):
			int16_t pixelHue = firstPixelHue + (int16_t)(i * 65536L / PIXEL_COUNT);
			// NeoPixel.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
			// optionally add saturation and value (brightness) (each 0 to 255).
			// Here we're using just the single-argument hue variant. The result
			// is passed through NeoPixel.gamma32() to provide 'truer' colors
			// before assigning to each pixel:
			NeoPixel.setColor(PIXEL_PIN, i, NeoPixel.gamma32(NeoPixel.ColorHSV(pixelHue)));
			}
			NeoPixel.show(PIXEL_PIN); // Update NeoPixel with new contents
			delay(wait);  // Pause for a moment
	}
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
	int firstPixelHue = 0;     // First pixel starts at red (hue 0)
	for(int a=0; a<30; a++) {  // Repeat 30 times...
		for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
			NeoPixel.clear(PIXEL_PIN);         //   Set all pixels in RAM to 0 (off)
			// 'c' counts up from 'b' to end of NeoPixel in increments of 3...
			for(int c=b; c<PIXEL_COUNT; c += 3) {
				// hue of pixel 'c' is offset by an amount to make one full
				// revolution of the color wheel (range 65536) along the length
				// of the NeoPixel (PIXEL_COUNT steps):
				int16_t      hue   = firstPixelHue + c * 65536L / PIXEL_COUNT;
				ZunoNeoColor_t color = NeoPixel.gamma32(NeoPixel.ColorHSV(hue)); // hue -> RGB
				NeoPixel.setColor(PIXEL_PIN, c, color); // Set pixel 'c' to value 'color'
			}
			NeoPixel.show(PIXEL_PIN);                // Update NeoPixel with new contents
			delay(wait);                 // Pause for a moment
			firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
		}
	}
}
