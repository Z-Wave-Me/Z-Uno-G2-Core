#include "Arduino.h"
#include "ZUNO_NeoPixel.h"

// NeoPixel test program showing use of the WHITE channel for RGBW
// pixels only (won't look correct on regular RGB NeoPixel strips).

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN     6

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT  60

// NeoPixel brightness, 0 (min) to 255 (max)
#define BRIGHTNESS 50 // Set BRIGHTNESS to about 1/5 (max = 255)


// setup() function -- runs once at startup --------------------------------
void setup() {
	NeoPixel.addNeo(LED_PIN, LED_COUNT, BRIGHTNESS, NEO_GRBW | NEO_KHZ800); // Set BRIGHTNESS to about 1/5 (max = 255)
	NeoPixel.show(LED_PIN);            // Turn OFF all pixels ASAP
}


// loop() function -- runs repeatedly as long as board is on ---------------
void loop() {
	// Fill along the length of the NeoPixel in various colors...
	colorWipe(NeoPixel.RGB(255,   0,   0)     , 50); // Red
	colorWipe(NeoPixel.RGB(  0, 255,   0)     , 50); // Green
	colorWipe(NeoPixel.RGB(  0,   0, 255)     , 50); // Blue
	colorWipe(NeoPixel.RGBW(  0,   0,   0, 255), 50); // True white (not RGB white)

	whiteOverRainbow(75, 5);

	pulseWhite(5);

	rainbowFade2White(3, 3, 1);
}


// Fill NeoPixel pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// NeoPixel.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(ZunoNeoColor_t color, int wait) {
	for(int i=0; i<LED_COUNT; i++) { // For each pixel in NeoPixel...
		NeoPixel.setColor(LED_PIN, i, color);         //  Set pixel's color (in RAM)
		NeoPixel.show(LED_PIN);                          //  Update NeoPixel to match
		delay(wait);                           //  Pause for a moment
	}
}

void whiteOverRainbow(uint32_t whiteSpeed, int whiteLength) {
	if(whiteLength >= LED_COUNT) whiteLength = LED_COUNT - 1;

	int      head          = whiteLength - 1;
	int      tail          = 0;
	int      loops         = 3;
	int      loopNum       = 0;
	uint32_t lastTime      = millis();
	uint32_t firstPixelHue = 0;

	for(;;) { // Repeat forever (or until a 'break' or 'return')
		for(int i=0; i<LED_COUNT; i++) {  // For each pixel in NeoPixel...
			if(((i >= tail) && (i <= head)) ||      //  If between head & tail...
				((tail > head) && ((i >= tail) || (i <= head)))) {
				NeoPixel.setColor(LED_PIN, i, NeoPixel.RGBW(0, 0, 0, 255)); // Set white
			} else {                                             // else set rainbow
				int16_t pixelHue = firstPixelHue + (int16_t)(i * 65536L / LED_COUNT);
				NeoPixel.setColor(LED_PIN, i, NeoPixel.gamma32(NeoPixel.ColorHSV(pixelHue)));
			}
		}

		NeoPixel.show(LED_PIN); // Update NeoPixel with new contents
		// There's no delay here, it just runs full-tilt until the timer and
		// counter combination below runs out.

		firstPixelHue += 40; // Advance just a little along the color wheel

		if((millis() - lastTime) > whiteSpeed) { // Time to update head/tail?
			if(++head >= LED_COUNT) {      // Advance head, wrap around
				head = 0;
				if(++loopNum >= loops) return;
			}
			if(++tail >= LED_COUNT) {      // Advance tail, wrap around
				tail = 0;
			}
			lastTime = millis();                   // Save time of last movement
		}
	}
}

void pulseWhite(uint8_t wait) {
	for(int j=0; j<256; j++) { // Ramp up from 0 to 255
		// Fill entire NeoPixel with white at gamma-corrected brightness level 'j':
		NeoPixel.fill(LED_PIN, 0, LED_COUNT, NeoPixel.RGBW(0, 0, 0, NeoPixel.gamma8(j)));
		NeoPixel.show(LED_PIN);
		delay(wait);
	}

	for(int j=255; j>=0; j--) { // Ramp down from 255 to 0
		NeoPixel.fill(LED_PIN, 0, LED_COUNT, NeoPixel.RGBW(0, 0, 0, NeoPixel.gamma8(j)));
		NeoPixel.show(LED_PIN);
		delay(wait);
	}
}

void rainbowFade2White(int wait, uint32_t rainbowLoops, int whiteLoops) {
	int fadeVal=0, fadeMax=100;

	// Hue of first pixel runs 'rainbowLoops' complete loops through the color
	// wheel. Color wheel has a range of 65536 but it's OK if we roll over, so
	// just count from 0 to rainbowLoops*65536, using steps of 256 so we
	// advance around the wheel at a decent clip.
	for(uint32_t firstPixelHue = 0; firstPixelHue < rainbowLoops*65536;
		firstPixelHue += 256) {

		for(int i=0; i<LED_COUNT; i++) { // For each pixel in NeoPixel...

			// Offset pixel hue by an amount to make one full revolution of the
			// color wheel (range of 65536) along the length of the NeoPixel
			// (LED_COUNT steps):
			uint32_t pixelHue = firstPixelHue + (i * 65536L / LED_COUNT);

			// NeoPixel.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
			// optionally add saturation and value (brightness) (each 0 to 255).
			// Here we're using just the three-argument variant, though the
			// second value (saturation) is a constant 255.
			NeoPixel.setColor(LED_PIN, i, NeoPixel.gamma32(NeoPixel.ColorHSV(pixelHue, 255, 255 * fadeVal / fadeMax)));
		}

		NeoPixel.show(LED_PIN);
		delay(wait);

		if(firstPixelHue < 65536) {                              // First loop,
			if(fadeVal < fadeMax) fadeVal++;                       // fade in
		} else if(firstPixelHue >= ((rainbowLoops-1) * 65536)) { // Last loop,
			if(fadeVal > 0) fadeVal--;                             // fade out
		} else {
			fadeVal = fadeMax; // Interim loop, make sure fade is at max
		}
  }

	for(int k=0; k<whiteLoops; k++) {
		for(int j=0; j<256; j++) { // Ramp up 0 to 255
			// Fill entire NeoPixel with white at gamma-corrected brightness level 'j':
			NeoPixel.fill(LED_PIN, 0, LED_COUNT, NeoPixel.RGBW(0, 0, 0, NeoPixel.gamma8(j)));
			NeoPixel.show(LED_PIN);
		}
		delay(1000); // Pause 1 second
		for(int j=255; j>=0; j--) { // Ramp down 255 to 0
			NeoPixel.fill(LED_PIN, 0, LED_COUNT, NeoPixel.RGBW(0, 0, 0, NeoPixel.gamma8(j)));
			NeoPixel.show(LED_PIN);
		}
	}

	delay(500); // Pause 1/2 second
}