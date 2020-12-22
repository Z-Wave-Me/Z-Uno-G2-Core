#include <Arduino.h>
#include "Mercury206Meter.h"
#include "ModBus.h"


#define MERCURY_BAUDRATE					(9600)
#define MERCURY_SERIAL						Serial1
#define MAX_MODBUS_BUFF						52

#define MERCURY_BADDATA_W 0xFFFF
#define MERCURY_BADDATA_B 0xFF

#define COMMAND_MERCURY_SETPOWERLIMIT              0x03
#define COMMAND_MERCURY_SETENERGYLIMIT             0x04
#define COMMAND_MERCURY_SETDISPLAYMODE             0x09
#define COMMAND_MERCURY_SETTARIFCOUNT              0x0A
#define COMMAND_MERCURY_SETTARIF                   0x0B
#define COMMAND_MERCURY_SETTARIFTABLE              0x11
#define COMMAND_MERCURY_RESETMAXIMUMS              0x12  
#define COMMAND_MERCURY_GETDATETIME                0x21
#define COMMAND_MERCURY_GETPOWERLIMIT              0x22
#define COMMAND_MERCURY_GETENERGYLIMIT             0x23
#define COMMAND_MERCURY_GETPOWER                   0x25
#define COMMAND_MERCURY_GETKWHCOUNTERS             0x27 
#define COMMAND_MERCURY_GETFWVERSION               0x28
#define COMMAND_MERCURY_GETBATTERYVOLTAGE          0x29
#define COMMAND_MERCURY_GETOFFDATETIME             0x2B
#define COMMAND_MERCURY_GETONDATETIME              0x2C
#define COMMAND_MERCURY_GETTARIFTABLE              0x31
#define COMMAND_MERCURY_GETMAXIMUMS                0x33 
#define COMMAND_MERCURY_GETVAW                     0x63
#define COMMAND_MERCURY_GETRELAYMODE               0x6D
#define COMMAND_MERCURY_SETDISPLAYAUX              0x70
#define COMMAND_MERCURY_SETRELAYMODE               0x71
#define COMMAND_MERCURY_GETFREQ                    0x81
#define COMMAND_MERCURY_GETPARAM                   0x86

//#define MODBUS_DBG

/*
Active HIGH for Driver Input Enable; 
Active LOW for Receiver Output Enable. 
It can be controlled by a common IO interface.
*/
#define MODBUS_TRANSMIT    HIGH
#define MODBUS_RECEIVE     LOW


/* Public Constructors */
Mercury206Meter::Mercury206Meter(uint32_t serialnumber, uint8_t dir_pin): _dir_pin(dir_pin) {
	uint8_t				*b;

	b = &this->_sn[0];
	b[3] =  serialnumber & 0xFF;
	serialnumber >>= 8;
	b[2] =  serialnumber & 0xFF;
	serialnumber >>= 8;
	b[1] =  serialnumber & 0xFF;
	serialnumber >>= 8;
	b[0] =  serialnumber & 0xFF;
}


/* Public Methods */
void Mercury206Meter::begin() {
	MERCURY_SERIAL.begin(MERCURY_BAUDRATE);
	pinMode(this->_dir_pin, OUTPUT);
}

bool Mercury206Meter::getVersion(MercuryFWVersion * p_fw_version) {
	uint8_t						buff[MAX_MODBUS_BUFF];

	if (this->_fillCmd(COMMAND_MERCURY_GETFWVERSION, 5, &buff[0]) == 0)
		return false;
	memcpy(p_fw_version, &buff[0] + 5, sizeof(MercuryFWVersion));
	return true;
}

bool Mercury206Meter::getCurrentVAW(MercuryVAW * vaw) {
	uint8_t						buff[MAX_MODBUS_BUFF];

	if (this->_fillCmd(COMMAND_MERCURY_GETVAW , 5, &buff[0]) == 0)
		return false;
	vaw->volts = this->_bcd2Word2(&buff[5]);
	vaw->amps = this->_bcd2Word2(&buff[7]);
	vaw->watts = this->_bcd2Word2(&buff[9]);
	return true;
}
bool Mercury206Meter::getCurrentLoadPower(word * p_power) {
	uint8_t						buff[MAX_MODBUS_BUFF];

	if (this->_fillCmd(COMMAND_MERCURY_GETPOWER , 5, &buff[0]) == 0)
		return false;
	p_power[0] = this->_bcd2Word2(&buff[5]);
	return true;
}
word Mercury206Meter::getBatteryVoltage() {
	uint8_t						buff[MAX_MODBUS_BUFF];

	if (this->_fillCmd(COMMAND_MERCURY_GETBATTERYVOLTAGE , 5, &buff[0]) == 0)
			return MERCURY_BADDATA_W;
	return (this->_bcd2Word2(&buff[5]));
}
bool Mercury206Meter::getKWhCounter(byte ci, dword * counter) {
	uint8_t						buff[MAX_MODBUS_BUFF];

	if (this->_fillCmd(COMMAND_MERCURY_GETKWHCOUNTERS , 5, &buff[0]) == 0)
		return false;
	ci <<= 2;
	ci += 5;
	counter[0] = this->_bcd2Dword(&buff[ci]);
	return true;
}
byte Mercury206Meter::getFrequencyTarif(word * freq) {
	uint8_t						buff[MAX_MODBUS_BUFF];

	if (this->_fillCmd(COMMAND_MERCURY_GETFREQ , 5, &buff[0]) == 0)
	return MERCURY_BADDATA_B;
	freq[0] = this->_bcd2Word2(&buff[5]);
	return buff[7];
}
word Mercury206Meter::getReactivePower() {
	uint8_t						buff[MAX_MODBUS_BUFF];

	buff[5] = 0; // Reactive power
	if (this->_fillCmd(COMMAND_MERCURY_GETPARAM, 6, &buff[0]) == 0)
		return MERCURY_BADDATA_W;
	return (this->_bcd2Word3(&buff[6]));
}
int  Mercury206Meter::getCosFi() {
	uint8_t						buff[MAX_MODBUS_BUFF];

	buff[5] = 2; // COS(Fi)
	if (this->_fillCmd(COMMAND_MERCURY_GETPARAM, 6, &buff[0]) == 0)
		return MERCURY_BADDATA_W;
	return (this->_bcd2Int2(&buff[5]));
}

byte Mercury206Meter::getRelayMode() {
	uint8_t						buff[MAX_MODBUS_BUFF];

	if (this->_fillCmd(COMMAND_MERCURY_GETRELAYMODE , 5, &buff[0]) == 0)
		return MERCURY_BADDATA_B;
	return buff[5];
}

bool Mercury206Meter::getMaximums(byte type, MercuryMaximums * maxs) {
	uint8_t						buff[MAX_MODBUS_BUFF];

	buff[5] = type; 
	if (this->_fillCmd(COMMAND_MERCURY_GETMAXIMUMS, 6, &buff[0]) == 0)
		return false;
	maxs->system_value = this->_bcd2Word2(&buff[5]);
	this->_fullDateTime(&maxs->system_datetime, &buff[7]);
	maxs->custom_value = this->_bcd2Word2(&buff[13]);
	this->_fullDateTime(&maxs->custom_datetime, &buff[15]);
	return true;
}
word Mercury206Meter::getEnergyLimit() {
	uint8_t						buff[MAX_MODBUS_BUFF];

	if (this->_fillCmd(COMMAND_MERCURY_GETENERGYLIMIT , 5, &buff[0]) == 0)
		return MERCURY_BADDATA_B;
	return (this->_bcd2Word2(&buff[5]));

}
word Mercury206Meter::getPowerLimit() {
	uint8_t						buff[MAX_MODBUS_BUFF];

	if (this->_fillCmd(COMMAND_MERCURY_GETPOWERLIMIT , 5, &buff[0]) == 0)
		return MERCURY_BADDATA_B;
	return (this->_bcd2Word2(&buff[5]));
}
bool Mercury206Meter::getCurrentDateTime(MercuryTimeDate *dt) {
	uint8_t						buff[MAX_MODBUS_BUFF];

	if (this->_fillCmd(COMMAND_MERCURY_GETDATETIME , 5, &buff[0]) == 0)
		return false;
	this->_fullDateTime(dt, &buff[6]);
	return true;
}
bool Mercury206Meter::getLastEnergyFail(MercuryTimeDate *dt) {
	uint8_t						buff[MAX_MODBUS_BUFF];

	if (this->_fillCmd(COMMAND_MERCURY_GETOFFDATETIME , 5, &buff[0]) == 0)
		return false;
	this->_fullDateTime(dt, &buff[6]);
	return true;
}
bool Mercury206Meter::getLastEnergyRecover(MercuryTimeDate *dt) {
	uint8_t						buff[MAX_MODBUS_BUFF];

	if (this->_fillCmd(COMMAND_MERCURY_GETONDATETIME , 5, &buff[0]) == 0)
		return false;
	this->_fullDateTime(dt, &buff[6]);
	return true;
}
byte Mercury206Meter::getRelayState() {
	uint8_t						buff[MAX_MODBUS_BUFF];

	buff[5] = 1; // Relay
	if (this->_fillCmd(COMMAND_MERCURY_GETPARAM, 6, &buff[0]) == 0)
		return MERCURY_BADDATA_B;
	return buff[6];
} 
bool Mercury206Meter::getMercuryTarifTable(byte ii2, MercuryTarifTimeTable * tt) {
	uint8_t						buff[MAX_MODBUS_BUFF];

	buff[5] = ii2; // Relay
	if (this->_fillCmd(COMMAND_MERCURY_GETTARIFTABLE, 6, &buff[0]) == 0)
		return false;
	memcpy(tt, buff+5, sizeof(MercuryTarifTimeTable));
	return true;
}
// SET
bool Mercury206Meter::setTarifCount(byte tc) {
	uint8_t						buff[MAX_MODBUS_BUFF];

	buff[5] = tc; 
	if (this->_fillCmd(COMMAND_MERCURY_SETTARIFCOUNT, 6, &buff[0]) == 0)
		return false;
	return true;
}
bool Mercury206Meter::setRelayMode(byte mode) {
	uint8_t						buff[MAX_MODBUS_BUFF];

	buff[5] = mode; 
	if (this->_fillCmd(COMMAND_MERCURY_SETRELAYMODE, 6, &buff[0]) == 0)
		return false;
	return true;
}
bool Mercury206Meter::setEnergyLimit(word energy) {
	uint8_t						buff[MAX_MODBUS_BUFF];

	buff[5] = energy/word(100);
	buff[6] = energy%word(100);
	if (this->_fillCmd(COMMAND_MERCURY_SETENERGYLIMIT, 7, &buff[0]) == 0)
		return false;
	return true;
}
bool Mercury206Meter::setPowerLimit(word power) {
	uint8_t						buff[MAX_MODBUS_BUFF];

	buff[5] = power/word(100);
	buff[6] = power%word(100);
	if (this->_fillCmd(COMMAND_MERCURY_SETPOWERLIMIT, 7, &buff[0]) == 0)
		return false;
	return true;
}
bool Mercury206Meter::resetMaximums(byte type) {
	uint8_t						buff[MAX_MODBUS_BUFF];

	memset(buff+5,0,8);
	buff[5+8] = type;
	if (this->_fillCmd(COMMAND_MERCURY_RESETMAXIMUMS, 5+9, &buff[0]) == 0)
		return false;
	return true;
}
bool Mercury206Meter::setMainDisplay(byte main) {
	uint8_t						buff[MAX_MODBUS_BUFF];

	buff[5] = main; 
	if (this->_fillCmd(COMMAND_MERCURY_SETDISPLAYMODE, 6, &buff[0]) == 0)
		return false;
	return true;

}
bool Mercury206Meter::setAuxDisplay(byte aux) {
	uint8_t						buff[MAX_MODBUS_BUFF];

	buff[5] = aux; 
	if (this->_fillCmd(COMMAND_MERCURY_SETDISPLAYAUX, 6, &buff[0]) == 0)
		return false;
	return true;
}
bool Mercury206Meter::setTarif(byte tarif) {
	uint8_t						buff[MAX_MODBUS_BUFF];

	buff[5] = tarif; 
	if (this->_fillCmd(COMMAND_MERCURY_SETTARIF, 6, &buff[0]) == 0)
		return false;
	return true;

}
bool Mercury206Meter::setTarifTable(byte ii2, MercuryTarifTimeTable * tt) {
	uint8_t						buff[MAX_MODBUS_BUFF];

	memcpy(buff+5, tt, sizeof(MercuryTarifTimeTable));
	buff[5+sizeof(MercuryTarifTimeTable)] = ii2; 
	if (this->_fillCmd(COMMAND_MERCURY_SETTARIFTABLE, 5+sizeof(MercuryTarifTimeTable)+1, &buff[0]) == 0)
		return false;
	return true;
}

/* Private Methods */
inline size_t Mercury206Meter::_fillCmd(byte cmd, size_t len, uint8_t *b) {
	memcpy(b, &this->_sn[0], sizeof(this->_sn));
	b[sizeof(this->_sn)] = cmd;
	digitalWrite(this->_dir_pin, MODBUS_TRANSMIT);
	delay(modbusDelay(MERCURY_BAUDRATE));
	if (modbusSend(&MERCURY_SERIAL, b, len) == false)
		return (0);
	delay(modbusDelay(MERCURY_BAUDRATE));
	digitalWrite(this->_dir_pin, MODBUS_RECEIVE);
	delay(4+MAX_MODBUS_BUFF+5);
	return (modbusReceive(&MERCURY_SERIAL, b, MAX_MODBUS_BUFF));
}

inline uint8_t Mercury206Meter::_bcd2dec(uint8_t c) {
	size_t dec;

	dec = (c>> 4);
	dec *= 10;
	dec += (c & 0x0F);
	return (dec);
}

inline void Mercury206Meter::_fullDateTime(MercuryTimeDate *dt, uint8_t *b) {
	dt->hour = this->_bcd2dec(b[0]);
	dt->minutes = this->_bcd2dec(b[1]);
	dt->seconds = this->_bcd2dec(b[2]);
	dt->day = this->_bcd2dec(b[3]);
	dt->month = this->_bcd2dec(b[4]);
	dt->year = this->_bcd2dec(b[5]);
}

inline uint16_t Mercury206Meter::_bcd2Word2(uint8_t *b) {
	uint16_t			w;

	w = this->_bcd2dec(b[0]);
	w *= 100;
	w += this->_bcd2dec(b[1]);
	return (w);
}

inline int Mercury206Meter::_bcd2Int2(uint8_t *b) {
	int					w;

	w = this->_bcd2dec((b[0]) & 0x7F);
	w *= 100;
	w += this->_bcd2dec(b[1]);
	w = (b[0] & 0x08) ? -w : w;
	return (w);
}

inline uint16_t Mercury206Meter::_bcd2Word3(uint8_t *b) {
	uint16_t			w;

	w = this->_bcd2Word2(b);
	w *= 100;
	w += this->_bcd2dec(b[2]);
	return (w);
}

inline uint32_t Mercury206Meter::_bcd2Dword(uint8_t *b) {
	uint32_t			w;

	w = this->_bcd2Word2(b);
	w *= 100;
	w += this->_bcd2dec(b[2]);
	w *= 100;
	w += this->_bcd2dec(b[3]);
	return (w);
}
