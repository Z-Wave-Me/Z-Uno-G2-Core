#include "ZWCCUserCode.h"
#include "ZWCCEntryControl.h"
#include "ZWCCTimerParametrs.h"
#include "ZWCCSoundSwitch.h"
#include "ZWCCIndicator.h"
#include "ZWCCCentralScene.h"
#include "ZUNO_Buttons.h"

#define BUTTON						23
#define MY_SERIAL					Serial0

enum{ 
	SOUND_SWITCH_CHANNEL = 0x1,
	CENTRAL_SCENE_CHANNEL
};

// enum for parameter numbers
enum{
	TEMP_HYST_PARAM=64,
	HUMIDITY_HYST_PARAM,
	MOTION_RETRIGGER_TIME_PARAM 
};

// ZUNO_ENABLE setups some global extra build flags
ZUNO_ENABLE(
			WITH_CC_ENTRY_CONTROL WITH_CC_USER_CODE WITH_CC_TIME_PARAMETERS
			// LOGGING_DBG// Uncomment for console output on TX0
			// DBG_CONSOLE_PIN=0xFF
			MODERN_MULTICHANNEL_S2  // S2 encapsulated NIF in multichannel
			MODERN_MULTICHANNEL_S2_ALWAYS // Add S2 to multichannel if device included non-secure
			);

ZUNO_SETUP_CHANNELS(
	ZUNO_SOUND_SWITCH(50, 0x2),
	ZUNO_CENTRAL_SCENE()
);

ZUNO_CUSTOM_CC(
	ZUNO_CC_VERSION(COMMAND_CLASS_USER_CODE, USER_CODE_VERSION),
	ZUNO_CC_VERSION(COMMAND_CLASS_ENTRY_CONTROL, ENTRY_CONTROL_VERSION),
	ZUNO_CC_VERSION(COMMAND_CLASS_TIME_PARAMETERS, TIME_PARAMETERS_VERSION),
	ZUNO_CC_VERSION(COMMAND_CLASS_INDICATOR, INDICATOR_VERSION)
);

ZUNO_SETUP_CENTRAL_SCENE_COMMON(
	ZUNO_SETUP_CENTRAL_SCENE(CENTRAL_SCENE_CHANNEL, (CENTRAL_SCENE_KEY_PRESSED_1_MASK | CENTRAL_SCENE_KEY_RELEASED_MASK | CENTRAL_SCENE_KEY_HELD_DOWN_MASK | CENTRAL_SCENE_KEY_PRESSED_2_MASK | CENTRAL_SCENE_KEY_PRESSED_3_MASK),
		ZUNO_SETUP_CENTRAL_SCENE_SET()
	);
);

ZUNO_SETUP_INDICATOR(
	ZUNO_SETUP_INDICATOR_INFO(0x5, LED_BUILTIN)
);

ZUNO_SETUP_SOUND_SWITCH_COMMON(
	ZUNO_SETUP_SOUND_SWITCH(SOUND_SWITCH_CHANNEL,
		ZUNO_SETUP_SOUND_SWITCH_SET("First", 60),
		ZUNO_SETUP_SOUND_SWITCH_SET("Two", 1000),
		ZUNO_SETUP_SOUND_SWITCH_SET("Third", 2000)
	);
);

ZUNO_SETUP_USER_CODE_KEYS('a');
ZUNO_SETUP_USER_CODE(
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE(),
	ZUNO_SETUP_USER_CODE_AVAILABLE()
);

ZUNO_SETUP_ENTRY_CONTROL_KEYS('0','1', '2', '3', '4', '5', '6', '7', '8', '9');

// Device's configuration parametrs definitions  
ZUNO_SETUP_CONFIGPARAMETERS(
	ZUNO_CONFIG_PARAMETER_INFO("Temperature hysteresis", "Defines hysteresis of temperature", 1, 20, 5),
	ZUNO_CONFIG_PARAMETER_INFO("Humidity hysteresis", "Defines hysteresis of humidity", 1, 20, 5),
	ZUNO_CONFIG_PARAMETER_INFO("Motion trigger time", "Minimal trigger interval in ms", 0, 100000, 5000)
);

ZUNO_SETUP_SLEEPING_MODE(ZUNO_SLEEPING_MODE_FREQUENTLY_AWAKE);

// Associations of device
ZUNO_SETUP_ASSOCIATIONS(ZUNO_ASSOCIATION_GROUP_SET_VALUE); // Send Basic Set to association group

// Device's S2 keys
ZUNO_SETUP_S2ACCESS(SKETCH_FLAG_S2_AUTHENTICATED_BIT | SKETCH_FLAG_S2_UNAUTHENTICATED_BIT | SKETCH_FLAG_S0_BIT);

static void _reset_print(const char *txt) {
	const char							*tmp;

	switch (zunoGetWakeReason()) {
		case ZUNO_WAKEUP_REASON_PIN:
			tmp = "Triggered by reset pin\n";
			break ;
		case ZUNO_WAKEUP_REASON_WUT_EM4:
			tmp = "Triggered by timer from EM4 state\n";
			break ;
		case ZUNO_WAKEUP_REASON_WATCH_DOG:
			tmp = "Triggered by watchdog\n";
			break ;
		case ZUNO_WAKEUP_REASON_EXT_EM4:
			tmp = "Triggered by external interrupt from EM4 state\n";
			break ;
		case ZUNO_WAKEUP_REASON_POR:
			tmp = "Triggered by no power \n";
			break ;
		case ZUNO_WAKEUP_REASON_SOFTRESET:
			tmp = "Triggered by software\n";
			break ;
		case ZUNO_WAKEUP_REASON_BROWNOUT:
			tmp = "Triggered by voltage surges\n";
			break ;
		case ZUNO_WAKEUP_REASON_EXT_EM2:
			tmp = "Triggered by external interrupt from EM2 state\n";
			break ;
		case ZUNO_WAKEUP_REASON_WUT_EM2:
			tmp = "Triggered by timer from EM2 state\n";
			break ;
		case ZUNO_WAKEUP_REASON_RADIO_EM2:
			tmp = "Triggered by radio from EM2 state\n";
			break ;
		default:
			tmp = "Unknown\n";
			break ;
	}
	MY_SERIAL.print(txt);
	MY_SERIAL.print(tmp);
}

static void _wakeHandler(void){
	_reset_print("\nWakeup reason: ");
}

void setup() {
	MY_SERIAL.begin(115200);
	_reset_print("\nBoot reason: ");
	zunoAttachSysHandler(ZUNO_HANDLER_WUP, 0, (void*) &_wakeHandler);
	Btn.addButton(BUTTON);
}

void loop() {
	process_buttons();
	if (Btn.isFree(BUTTON))
		zunoSendDeviceToSleep(); // We don't need parameter for FLiRS here, Z-Uno will ingore parameter anyway
}

static uint8_t long_click = false;

void process_buttons() {
	if (long_click == true && Btn.isReleased(BUTTON)) {
		zuno_CCCentralSceneReport(CENTRAL_SCENE_CHANNEL, 0x1, CENTRAL_SCENE_KEY_RELEASED);
		long_click = false;
		MY_SERIAL.println("isReleased");
	}
	if(Btn.isSingleClick(BUTTON)) {
		zuno_CCCentralSceneReport(CENTRAL_SCENE_CHANNEL, 0x1, CENTRAL_SCENE_KEY_PRESSED_1);
		MY_SERIAL.println("isSingleClick");

	}
	if(Btn.isTripleClick(BUTTON)) {
		zuno_CCCentralSceneReport(CENTRAL_SCENE_CHANNEL, 0x1, CENTRAL_SCENE_KEY_PRESSED_3);
		MY_SERIAL.println("isTripleClick");

	}
	if(Btn.isLongClick(BUTTON)) {
		zuno_CCCentralSceneReport(CENTRAL_SCENE_CHANNEL, 0x1, CENTRAL_SCENE_KEY_HELD_DOWN);
		long_click = true;
		MY_SERIAL.println("isLongClick");

	}
	if(Btn.isDoubleClick(BUTTON)) {
		zuno_CCCentralSceneReport(CENTRAL_SCENE_CHANNEL, 0x1, CENTRAL_SCENE_KEY_PRESSED_2);
		MY_SERIAL.println("isDoubleClick");
	}
}