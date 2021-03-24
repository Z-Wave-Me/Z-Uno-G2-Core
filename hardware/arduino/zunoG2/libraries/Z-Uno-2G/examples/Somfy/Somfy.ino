#include "Arduino.h"
#include "ZUNO_Somfy.h"

#define MY_SERIAL Serial0 

SomfyClass gSomfy = SomfyClass();

uint8_t switchMultiGetter(uint8_t ch);
void switchMultiSetter(uint8_t ch, uint8_t value);
zuno_handler_multi_gettersetter_t getter_setter = {(void*)&switchMultiGetter, (void*)&switchMultiSetter, 0};

uint8_t gValueArray[ZUNO_MAX_MULTI_CHANNEL_NUMBER] = {0};
uint8_t gValueArrayNew[ZUNO_MAX_MULTI_CHANNEL_NUMBER] = {0};
uint8_t gValueArrayUpdate[ZUNO_MAX_MULTI_CHANNEL_NUMBER] = {0};

size_t					gCountDevice;

void setup(void) {
	uint8_t					ch;
	size_t					position;

	MY_SERIAL.begin(115200);
	gSomfy.begin(ZUNO_SOMFY_TYPE_RS480_GLYDEA);
	gCountDevice = gSomfy.getCountDevice();
	if (gCountDevice > ZUNO_MAX_MULTI_CHANNEL_NUMBER)
		gCountDevice = ZUNO_MAX_MULTI_CHANNEL_NUMBER;
	if(zunoStartDeviceConfiguration() && gCountDevice != 0) {
		if (gCountDevice == 1) {
			zunoAddChannel(ZUNO_SWITCH_MULTILEVEL_CHANNEL_NUMBER, 0, 0);
			zunoSetZWChannel( 0x0, 0x0);
		}
		else {
			for(size_t i = 0; i < gCountDevice; i++) {
				ch = (i + 1);
				if(!i)
					ch |= ZWAVE_CHANNEL_MAPPED_BIT;
				zunoAddChannel(ZUNO_SWITCH_MULTILEVEL_CHANNEL_NUMBER, 0, 0);
				zunoSetZWChannel(i, ch);
			}
		}
		zunoCommitCfg();
		for(size_t i = 0; i < gCountDevice; i++) {
			position = gSomfy.getPosition(i);
			if (position == ZUNO_SOMFY_INVALID_VALUE)
				position = 0;
			gValueArray[i] = position;
			gValueArrayNew[i] = position;
			gValueArrayUpdate[i] = false;
			zunoAppendChannelHandler(i, 1, CHANNEL_HANDLER_MULTI_GETTERSETTER, &getter_setter);
		}
	}
}

void loop(void) {
	size_t					position;

	for(size_t i = 0; i < gCountDevice; i++) {
		if (gValueArrayNew[i] != gValueArray[i]) {
			gValueArray[i] = gValueArrayNew[i];
			gValueArrayUpdate[i] = true;
			gSomfy.move(i, gValueArrayNew[i]);
		}
		if (gValueArrayUpdate[i] == true) {
			gValueArrayUpdate[i] = false;
			if ((position = gSomfy.getPosition(i)) != ZUNO_SOMFY_INVALID_VALUE) {
				if (gValueArray[i] != position) {
					gValueArray[i] = position;
					gValueArrayNew[i] = position;
					zunoSendReport(i + 1);
				}
			}
		}
	}
}

uint8_t switchMultiGetter(uint8_t ch) {
	gValueArrayUpdate[ch] = true;
	return (gValueArray[ch]);
}

void switchMultiSetter(uint8_t ch, uint8_t value) {
	if (value > 99)
		value = 99;
	gValueArrayNew[ch] = value;
}