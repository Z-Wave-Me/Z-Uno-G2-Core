#include "Arduino.h"
#include "ZWCCCentralScene.h"
#include "ZUNO_Buttons.h"

#define BUTTON_ONE 0
#define BUTTON_TWO 1
#define MY_SERIAL Serial0

#define CENTRAL_SCENE_ONE 1
#define CENTRAL_SCENE_TWO 100

ZUNO_ENABLE(
			// LOGGING_DBG
			CERT_BUILD
			// 
			DBG_CONSOLE_BAUDRATE=921600
			WITH_CC_CENTRAL_SCENE
);

byte switchBinaryValue_old = 1;
byte switchBinaryValue = 0;

ZUNO_SETUP_S2ACCESS(SKETCH_FLAG_S2_UNAUTHENTICATED_BIT | SKETCH_FLAG_S2_AUTHENTICATED_BIT | SKETCH_FLAG_S2_ACCESS_BIT | SKETCH_FLAG_S0_BIT);

ZUNO_SETUP_CHANNELS(ZUNO_SWITCH_BINARY(switchBinaryValue, NULL));

void setup(void)
{
	zuno_CCCentralSceneAdd(CENTRAL_SCENE_ONE, (CENTRAL_SCENE_KEY_RELEASED_MASK | CENTRAL_SCENE_KEY_HELD_DOWN_MASK | CENTRAL_SCENE_KEY_PRESSED_1_MASK));
	zuno_CCCentralSceneAdd(CENTRAL_SCENE_TWO, (CENTRAL_SCENE_KEY_RELEASED_MASK | CENTRAL_SCENE_KEY_HELD_DOWN_MASK | CENTRAL_SCENE_KEY_PRESSED_1_MASK));
	#ifndef LOGGING_DBG
	MY_SERIAL.begin(DBG_CONSOLE_BAUDRATE);
	#endif
	pinMode(LED_BUILTIN, OUTPUT);
	Btn.addButton(BUTTON_ONE);
	Btn.addButton(BUTTON_TWO);
}

static uint8_t long_click_one = false;
static uint8_t long_click_two = false;

void process_buttons(uint8_t *const long_click, const uint8_t id, const uint8_t scene)
{
	if (*long_click == true && Btn.isReleased(id))
	{
		zuno_CCCentralSceneReport(scene, CENTRAL_SCENE_KEY_RELEASED);
		*long_click = false;
		MY_SERIAL.print("isReleased: ");
		MY_SERIAL.println(id);
		return;
	}
	if(Btn.isSingleClick(id))
	{
		zuno_CCCentralSceneReport(scene, CENTRAL_SCENE_KEY_PRESSED_1);
		MY_SERIAL.print("isSingleClick: ");
		MY_SERIAL.println(id);
		return;
	}
	if(Btn.isTripleClick(id))
	{
		zuno_CCCentralSceneReport(scene, CENTRAL_SCENE_KEY_PRESSED_3);
		MY_SERIAL.print("isTripleClick: ");
		MY_SERIAL.println(id);
		return;
	}
	if(Btn.isLongClick(id))
	{
		zuno_CCCentralSceneReport(scene, CENTRAL_SCENE_KEY_HELD_DOWN);
		*long_click = true;
		MY_SERIAL.print("isLongClick: ");
		MY_SERIAL.println(id);
		return;
	}
	if(Btn.isDoubleClick(id))
	{
		zuno_CCCentralSceneReport(scene, CENTRAL_SCENE_KEY_PRESSED_2);
		MY_SERIAL.print("isDoubleClick: ");
		MY_SERIAL.println(id);
		return;
	}
}

void loop(void)
{
	if (switchBinaryValue_old != switchBinaryValue)
	{
		switchBinaryValue_old = switchBinaryValue;
		if (switchBinaryValue_old == 0)
		{
			digitalWrite(LED_BUILTIN, LOW);
		}
		else
		{
			digitalWrite(LED_BUILTIN, HIGH);
		}
	}
	process_buttons(&long_click_one, BUTTON_ONE, CENTRAL_SCENE_ONE);
	process_buttons(&long_click_two, BUTTON_TWO, CENTRAL_SCENE_TWO);
}
