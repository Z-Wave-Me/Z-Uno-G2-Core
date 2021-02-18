#include "Arduino.h"
#include "ZUNO_Buttons.h"
#include "ZUNO_LEDS.h"


#define MY_SERIAL			Serial0
#define BUTTON				23

enum {
	LED_MODE_NWI,
	LED_MODE_HEARTBEAT,
	LED_MODE_CLOSED,
	LED_MODE_FWAUTH,
	LED_MAX_MODES
};

const ZunoLedMode_t ValveLEDModes[] = {{8,0xAAAAAAAA},
	{32,0x00000003},
	{8,0xF000F000},
	{8,0x00A00A00}
};

const ZunoLedModeGroups_t ValveLEDModesGrups[] = {
	{ValveLEDModes, 29, false},
	{ValveLEDModes, LED_BUILTIN, false}
};

/* the setup function runs once, when you press reset or power the board */
void setup() {
	MY_SERIAL.begin();
	pinMode(BUTTON, INPUT_PULLUP);
	MY_SERIAL.println("Setup");
	Btn.addButton(BUTTON);
	Led.addLed(ValveLEDModesGrups, 2, LED_MAX_MODES);
	Led.addLed(ValveLEDModesGrups, 2, LED_MAX_MODES);
	Led.deleteLed(ValveLEDModesGrups);
	Led.addLed(ValveLEDModesGrups, 2, LED_MAX_MODES);
}

/* the loop function runs over and over again forever */
void loop() {
	process_buttons();
}

void process_buttons()
{
	if(Btn.isSingleClick(BUTTON)) {
		MY_SERIAL.println("isSingleClick");
		Led.setMode(ValveLEDModesGrups, LED_MODE_NWI);
	}

	if(Btn.isLongClick(BUTTON)) {
		MY_SERIAL.println("isLongClick");
		Led.setMode(ValveLEDModesGrups, LED_MODE_FWAUTH);
	}
}