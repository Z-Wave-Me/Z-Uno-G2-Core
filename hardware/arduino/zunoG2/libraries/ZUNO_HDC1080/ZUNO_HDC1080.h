
#ifndef _ZUNO_HDC1080_H
#define _ZUNO_HDC1080_H

#include "Arduino.h"
#include <Wire.h>

#define HDC1080_ADDR 0x40

//Can use up to 400khz Clockspeed

class ZUNO_HDC1080{
	public:
		ZUNO_HDC1080();
		ZUNO_HDC1080(uint32_t speed);
		void begin();
		void begin(uint32_t speed);
		void readTempHumid();
		void heatUp(uint8_t seconds);
		float getTemp();
		float getRelativeHumidity();
		float* getTempHumid(float* tempHumid);

	private:
		uint16_t _temperatureRaw;
		uint16_t _humidityRaw;
		TwoWire *_wire;
		uint8_t _addr;
		uint32_t _wire_speed;
		void writeRegister(uint8_t address, uint16_t value);
		uint16_t readData(uint8_t address);
};
#endif
