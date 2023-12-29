#include "ZWCCCentralScene.h"
#include "ZUNO_Buttons.h"


#define BUTTON						0
#define MY_SERIAL					Serial0

#define CENTRAL_SCENE_ONE			1
#define CENTRAL_SCENE_TWO			100

ZUNO_ENABLE(
			// LOGGING_DBG
			CERT_BUILD
			// 
			DBG_CONSOLE_BAUDRATE=921600
			WITH_CC_CENTRAL_SCENE
);

byte switchBinaryValue = 0;

ZUNO_SETUP_S2ACCESS(SKETCH_FLAG_S2_AUTHENTICATED_BIT | SKETCH_FLAG_S2_UNAUTHENTICATED_BIT | SKETCH_FLAG_S0_BIT);

ZUNO_SETUP_CHANNELS(ZUNO_SWITCH_BINARY(switchBinaryValue, NULL));

void setup() {
	zuno_CCCentralSceneAdd(CENTRAL_SCENE_ONE, (CENTRAL_SCENE_KEY_RELEASED_MASK | CENTRAL_SCENE_KEY_HELD_DOWN_MASK));
	zuno_CCCentralSceneAdd(CENTRAL_SCENE_TWO, (CENTRAL_SCENE_KEY_PRESSED_1_MASK | CENTRAL_SCENE_KEY_PRESSED_2_MASK | CENTRAL_SCENE_KEY_PRESSED_3_MASK));
	#ifndef LOGGING_DBG
	MY_SERIAL.begin(DBG_CONSOLE_BAUDRATE);
	#endif
	pinMode(LED_BUILTIN, OUTPUT);
	Btn.addButton(BUTTON);
}

void loop() {
	if (switchBinaryValue == 0x0)
		digitalWrite(LED_BUILTIN, LOW);
	else
		digitalWrite(LED_BUILTIN, HIGH);
	process_buttons();
}

static uint8_t long_click = false;

void process_buttons() {
	if (long_click == true && Btn.isReleased(BUTTON)) {
		zuno_CCCentralSceneReport(CENTRAL_SCENE_ONE, CENTRAL_SCENE_KEY_RELEASED);
		long_click = false;
		MY_SERIAL.println("isReleased");
	}
	if(Btn.isSingleClick(BUTTON)) {
		zuno_CCCentralSceneReport(CENTRAL_SCENE_TWO, CENTRAL_SCENE_KEY_PRESSED_1);
		MY_SERIAL.println("isSingleClick");

	}
	if(Btn.isTripleClick(BUTTON)) {
		zuno_CCCentralSceneReport(CENTRAL_SCENE_TWO, CENTRAL_SCENE_KEY_PRESSED_3);
		MY_SERIAL.println("isTripleClick");

	}
	if(Btn.isLongClick(BUTTON)) {
		zuno_CCCentralSceneReport(CENTRAL_SCENE_ONE, CENTRAL_SCENE_KEY_HELD_DOWN);
		long_click = true;
		MY_SERIAL.println("isLongClick");

	}
	if(Btn.isDoubleClick(BUTTON)) {
		zuno_CCCentralSceneReport(CENTRAL_SCENE_TWO, CENTRAL_SCENE_KEY_PRESSED_2);
		MY_SERIAL.println("isDoubleClick");
	}
}
