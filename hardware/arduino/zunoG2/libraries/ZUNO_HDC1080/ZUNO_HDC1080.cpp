#include "ZUNO_HDC1080.h"

ZUNO_HDC1080::ZUNO_HDC1080(){
	_temperatureRaw=0;
	_humidityRaw=0;
	_wire = &Wire;
	_addr = HDC1080_ADDR;
	_wire_speed = 400000;
}

ZUNO_HDC1080::ZUNO_HDC1080(uint32_t wire_speed){
	_temperatureRaw=0;
	_humidityRaw=0;
	_wire = &Wire;
	_addr = HDC1080_ADDR;
	_wire_speed = wire_speed;
}


void ZUNO_HDC1080::begin(){
	//config the temp sensor to read temp then humidity in one transaction
	//config the resolution to 14 bits for temp & humidity
	_wire->begin();
	_wire->setClock(this->_wire_speed); //set clock speed for I2C bus to maximum allowed for HDC1080
	delay(20);
	writeRegister(0x02,0x00);
	writeRegister(0x02,0x1000);
}

void ZUNO_HDC1080::begin(uint32_t wire_speed){
	//config the temp sensor to read temp then humidity in one transaction
	//config the resolution to 14 bits for temp & humidity
	_wire_speed = wire_speed;
	_wire->begin();
	_wire->setClock(this->_wire_speed); //set clock speed for I2C bus to maximum allowed for HDC1080
	delay(20);
	writeRegister(0x02,0x00);
	writeRegister(0x02,0x1000);


}

void ZUNO_HDC1080::writeRegister(uint8_t address, uint16_t value){
	_wire->beginTransmission(_addr);
	_wire->write(address);
	_wire->write(value >> 8);
	_wire->write(value & 0xff);
	_wire->endTransmission();
}

void ZUNO_HDC1080::readTempHumid(){
	//set pointer register
	this->_wire->beginTransmission(_addr);
	this->_wire->write(0x00);
	this->_wire->endTransmission();
	delay(15);
	this->_wire->requestFrom(_addr, 4);
	_temperatureRaw = _temperatureRaw << 8 | _wire->read();
	_temperatureRaw = _temperatureRaw << 8 | _wire->read();
	_humidityRaw = _humidityRaw << 8 | _wire->read();
	_humidityRaw = _humidityRaw << 8 | _wire->read();

}

//returns temp in celcius
float ZUNO_HDC1080::getTemp(){

	// (rawTemp/2^16)*165 - 40
	return ( (float)_temperatureRaw )*165/65536 - 40;

}

float ZUNO_HDC1080::getRelativeHumidity(){

	//(rawHumidity/2^16)*100
	return ( (float)_humidityRaw )*100/65536;
}

float* ZUNO_HDC1080::getTempHumid(float* tempHumid){

	*tempHumid = getTemp();
	*(tempHumid+1) = getRelativeHumidity();
	return tempHumid;
}

uint16_t ZUNO_HDC1080::readData(uint8_t address){
	_wire->beginTransmission(_addr);
	_wire->write(address);
	_wire->endTransmission();

	delay(10);
	_wire->requestFrom(_addr,2);

	byte msb = _wire->read();
	byte lsb = _wire->read();

	return msb << 8 | lsb;
}

void ZUNO_HDC1080::heatUp(uint8_t seconds) {
	uint16_t reg = readData(0x02);
	uint8_t buf[4];
	
	reg |= 1 << 13;
	writeRegister(0x02, reg);

	for (int i = 1; i < (seconds*56); i++) {
		_wire->beginTransmission(_addr);
		_wire->write(0x00);
		_wire->endTransmission();
		delay(15);
		_wire->requestFrom(_addr, 4);
		buf[3] = _wire->read();
		buf[2] = _wire->read();
		buf[1] = _wire->read();
		buf[0] = _wire->read();
	}
	
	reg ^= 1 << 13;
	writeRegister(0x02, reg);
}