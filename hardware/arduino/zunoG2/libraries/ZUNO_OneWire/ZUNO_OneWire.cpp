/*
Copyright (c) 2007, Jim Studt  (original old version - many contributors since)

The latest version of this library may be found at:
  http://www.pjrc.com/teensy/td_libs_OneWire.html

OneWire has been maintained by Paul Stoffregen (paul@pjrc.com) since
January 2010.  At the time, it was in need of many bug fixes, but had
been abandoned the original author (Jim Studt).  None of the known
contributors were interested in maintaining OneWire.  Paul typically
works on OneWire every 6 to 12 months.  Patches usually wait that
long.  If anyone is interested in more actively maintaining OneWire,
please contact Paul.

Version 2.3:
  Unknonw chip fallback mode, Roger Clark
  Teensy-LC compatibility, Paul Stoffregen
  Search bug fix, Love Nystrom

Version 2.2:
  Teensy 3.0 compatibility, Paul Stoffregen, paul@pjrc.com
  Arduino Due compatibility, http://arduino.cc/forum/index.php?topic=141030
  Fix DS18B20 example negative temperature
  Fix DS18B20 example's low res modes, Ken Butcher
  Improve reset timing, Mark Tillotson
  Add const qualifiers, Bertrik Sikken
  Add initial value input to crc16, Bertrik Sikken
  Add target_search() function, Scott Roberts

Version 2.1:
  Arduino 1.0 compatibility, Paul Stoffregen
  Improve temperature example, Paul Stoffregen
  DS250x_PROM example, Guillermo Lovato
  PIC32 (chipKit) compatibility, Jason Dangel, dangel.jason AT gmail.com
  Improvements from Glenn Trewitt:
  - crc16() now works
  - check_crc16() does all of calculation/checking work.
  - Added read_bytes() and write_bytes(), to reduce tedious loops.
  - Added ds2408 example.
  Delete very old, out-of-date readme file (info is here)

Version 2.0: Modifications by Paul Stoffregen, January 2010:
http://www.pjrc.com/teensy/td_libs_OneWire.html
  Search fix from Robin James
    http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1238032295/27#27
  Use direct optimized I/O in all cases
  Disable interrupts during timing critical sections
    (this solves many random communication errors)
  Disable interrupts during read-modify-write I/O
  Reduce RAM consumption by eliminating unnecessary
    variables and trimming many to 8 bits
  Optimize both crc8 - table version moved to flash

Modified to work with larger numbers of devices - avoids loop.
Tested in Arduino 11 alpha with 12 sensors.
26 Sept 2008 -- Robin James
http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1238032295/27#27

Updated to work with arduino-0008 and to include skip() as of
2007/07/06. --RJL20

Modified to calculate the 8-bit CRC directly, avoiding the need for
the 256-byte lookup table to be loaded in RAM.  Tested in arduino-0010
-- Tom Pollard, Jan 23, 2008

Jim Studt's original library was modified by Josh Larios.

Tom Pollard, pollard@alum.mit.edu, contributed around May 20, 2008

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall beincluded in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Much of the code was inspired by Derek Yerger's code, though I don't
think much of that remains.  In any event that was..
    (copyleft) 2006 by Derek Yerger - Free to distribute freely.

The CRC code was excerpted and inspired by the Dallas Semiconductor
sample code bearing this copyright.
//---------------------------------------------------------------------------
// Copyright (C) 2000 Dallas Semiconductor Corporation, All Rights Reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY,  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL DALLAS SEMICONDUCTOR BE LIABLE FOR ANY CLAIM, DAMAGES
// OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//
// Except as contained in this notice, the name of Dallas Semiconductor
// shall not be used except as stated in the Dallas Semiconductor
// Branding Policy.
//--------------------------------------------------------------------------
*/

#include "Arduino.h"
#include "ZUNO_OneWire.h"

#define ONEWARE_INPUT()			this->_pinModeFast(INPUT & 0xFF);
#define ONEWARE_OUTPUT()		this->_digitalWriteFast(LOW); this->_pinModeFast(OUTPUT & 0xFF);

/* Public Constructors */
OneWire::OneWire(byte pin) {//Here we caching some values for better perfomance
	size_t			real_port;
	size_t			real_pin;
	size_t			aliasAddr_in;
	size_t			aliasAddr_out;
	
	real_pin = getRealPin(pin);
	real_port = getRealPort(pin);
	this->_real_pin = real_pin;
	this->_real_port = real_port;
	aliasAddr_in = ((uint32_t) & GPIO->P[real_port].DIN);
	aliasAddr_in -= PER_MEM_BASE;
	aliasAddr_in <<= 5;
	aliasAddr_in += BITBAND_PER_BASE;
	aliasAddr_in += (real_pin << 2);
	this->_aliasAddr_in = aliasAddr_in;
	aliasAddr_out = ((uint32_t) & GPIO->P[real_port].DOUT);
	aliasAddr_out -= PER_MEM_BASE;
	aliasAddr_out <<= 5;
	aliasAddr_out += BITBAND_PER_BASE;
	aliasAddr_out += (real_pin << 2);
	this->_aliasAddr_out = aliasAddr_out;
	this->reset_search();
}

/* Public Methods */
void OneWire::reset_search() {// We use global vars here to minimize stack usage
	memset(&this->_date, 0, sizeof(this->_date));
}

/*
// Perform the onewire reset function.  We will wait up to 250uS for
// the bus to come high, if it doesn't then it is broken or shorted
// and we return a 0;
//
// Returns 1 if a device asserted a presence pulse, 0 otherwise.
*/
byte OneWire::reset(void) {
	size_t			out;

	ONEWARE_INPUT();
	delay(1);
	if (this->_digitalReadFast() == 0)
		return (false);
	ONEWARE_OUTPUT();
	delayMicroseconds(480);
	noInterrupts();
	ONEWARE_INPUT();
	delayMicroseconds(70);
	out = this->_digitalReadFast();
	interrupts();
	if (out != 0)
		return (false);
	delayMicroseconds(410);
	return (true);
}

void OneWire::write(byte v, byte power) {
	byte					bitMask;

	noInterrupts();
	ONEWARE_OUTPUT();
	for (bitMask = 0x01; bitMask; bitMask <<= 1) {
		this->_digitalWriteFast(0);
		if ((bitMask & v)) {
			delayMicroseconds(10);
			this->_digitalWriteFast(1);
			delayMicroseconds(55);
		} else {
			delayMicroseconds(65);
			this->_digitalWriteFast(1);
			delayMicroseconds(5);
		}
	}
	interrupts();
	if (!power)
		ONEWARE_INPUT();
}

void OneWire::write_bytes(const uint8_t *buf, uint16_t count, bool power /* = 0 */) {
	for (uint16_t i = 0 ; i < count ; i++)
		this->write(buf[i], power);
}

byte OneWire::read() {
	byte bitMask;
	byte r;
	byte res = 0;

	noInterrupts();
	for (bitMask = 0x01; bitMask; bitMask <<= 1) {
		ONEWARE_OUTPUT();
		this->_digitalWriteFast(0);
		delayMicroseconds(2);
		ONEWARE_INPUT(); // let pin float, pull up will raise
		delayMicroseconds(10);
		r = this->_digitalReadFast();
		delayMicroseconds(53);
		if (r)
			res |= bitMask;
	}
	interrupts();
	return res;
}


void OneWire::read_bytes(uint8_t *buf, uint16_t count) {
	for (uint16_t i = 0 ; i < count ; i++)
		buf[i] = this->read();
}

// Do a ROM select
void OneWire::select(byte * rom) {
	size_t				i;

	this->write(0x55); // Choose ROM
	for (i = 0; i < 8; i++)
		this->write(rom[i]);
}

void OneWire::depower() {
	ONEWARE_INPUT();
}

void OneWire::readROM(byte * rom) {
	size_t				i;

	this->write(0x33);
	for (i = 0; i < 8; i++)
		rom[i] = read();
}

byte OneWire::crc8(byte * addr, byte len) {
	uint8_t crc = 0;

	while (len--) {
		byte inbyte = * addr++;
		for (byte i = 8; i; i--) {
			byte mix = (crc ^ inbyte) & 0x01;
			crc >>= 1;
			if (mix)
				crc ^= 0x8C;
			inbyte >>= 1;
		}
	}
	return crc;
}

bool OneWire::check_crc16(const uint8_t* input, uint16_t len, const uint8_t* inverted_crc, uint16_t crc) {
	crc = ~OneWire::crc16(input, len, crc);
	return (crc & 0xFF) == inverted_crc[0] && (crc >> 8) == inverted_crc[1];
}

uint16_t OneWire::crc16(const uint8_t* input, uint16_t len, uint16_t crc) {
	static const uint8_t oddparity[16] =
		{ 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0 };

	for (uint16_t i = 0 ; i < len ; i++) {
		// Even though we're just copying a byte from the input,
		// we'll be doing 16-bit computation with it.
		uint16_t cdata = input[i];
		cdata = (cdata ^ crc) & 0xff;
		crc >>= 8;

		if (oddparity[cdata & 0x0F] ^ oddparity[cdata >> 4])
			crc ^= 0xC001;

		cdata <<= 6;
		crc ^= cdata;
		cdata <<= 1;
		crc ^= cdata;
	}
	return crc;
}

/*
// Perform a search. If this function returns a '1' then it has
// enumerated the next device and you may retrieve the ROM from the
// OneWire::address variable. If there are no devices, no further
// devices, or something horrible happens in the middle of the
// enumeration then a 0 is returned.  If a new device is found then
// its address is copied to newAddr.  Use OneWire::reset_search() to
// start over.
//
// --- Replaced by the one from the Dallas Semiconductor web site ---
//--------------------------------------------------------------------------
// Perform the 1-Wire Search Algorithm on the 1-Wire bus using the existing
// search state.
// Return TRUE  : device found, ROM number in ROM_NO buffer
//        FALSE : device not found, end of search
*/
bool OneWire::search(uint8_t * newAddr) {
	byte				ows_last_zero;
	byte				ows_rom_byte_number;
	byte				ows_search_result;
	byte				ows_id_bit_number;
	byte				ows_rom_byte_mask;

	byte				ows_id_bit;
	byte				ows_cmp_id_bit;
	byte				ows_search_direction;

	ows_last_zero = 0;// initialize for search
	ows_rom_byte_number = 0;
	ows_search_result = false;
	ows_id_bit_number = 1;
	ows_rom_byte_mask = 1;
	if (!this->_date.LastDeviceFlag) {// if the last call was not the last one
		if (!reset()) {// 1-Wire reset
			this->_date.LastDiscrepancy = 0;// reset the search
			this->_date.LastDeviceFlag = false;
			//this->_date.LastFamilyDiscrepancy = 0;
			return false;
		}
		this->write(0xF0);// issue the search command
		do {// loop to do the search serial number search direction write bit read a bit and its complement
			ows_id_bit = this->read_bit();
			ows_cmp_id_bit = this->read_bit();
			if ((ows_id_bit == 1) && (ows_cmp_id_bit == 1))// check for no devices on 1-wire
				break;
			if (ows_id_bit != ows_cmp_id_bit) {// all devices coupled have 0 or 1
				ows_search_direction = ows_id_bit; // bit write value for search
			} else {// if this discrepancy if before the Last Discrepancy on a previous next then pick the same as last time
				if (ows_id_bit_number < this->_date.LastDiscrepancy) {
					ows_search_direction = this->_date.ows_ROM_NO[ows_rom_byte_number];
					ows_search_direction &= ows_rom_byte_mask;
					ows_search_direction = (ows_search_direction > 0);
				} else// if equal to last pick 1, if not then pick 0
					ows_search_direction = (ows_id_bit_number == this->_date.LastDiscrepancy);
				if (ows_search_direction == 0) {// if 0 was picked then record its position in LastZero
					ows_last_zero = ows_id_bit_number;
					// if (ows_last_zero < 9)// check for Last discrepancy in family
					// 	this->_date.LastFamilyDiscrepancy = ows_last_zero;
				}
			}
			if (ows_search_direction)// set or clear the bit in the ROM byte rom_byte_number with mask rom_byte_mask
				this->_date.ows_ROM_NO[ows_rom_byte_number] |= ows_rom_byte_mask;
			else
				this->_date.ows_ROM_NO[ows_rom_byte_number] &= ~(ows_rom_byte_mask);
			this->write_bit(ows_search_direction);// serial number search direction write bit
			ows_id_bit_number++;// increment the byte counter id_bit_number and shift the mask rom_byte_mask
			ows_rom_byte_mask <<= 1;
			if (ows_rom_byte_mask == 0) {// if the mask is 0 then go to new SerialNum byte rom_byte_number and reset mask
				ows_rom_byte_number++;
				ows_rom_byte_mask = 1;
			}
		}
		while (ows_rom_byte_number < 8); // loop until through all ROM bytes 0-7
		if (ows_id_bit_number > 64) {// if the search was successful then search successful so set LastDiscrepancy,LastDeviceFlag,search_result
			this->_date.LastDiscrepancy = ows_last_zero;
			if (this->_date.LastDiscrepancy == 0)// check for last device
				this->_date.LastDeviceFlag = true;
			ows_search_result = true;
		}
	}
	
	if (!ows_search_result || !this->_date.ows_ROM_NO[0]) {// if no device found then reset counters so next 'search' will be like a first
		this->_date.LastDiscrepancy = 0;
		this->_date.LastDeviceFlag = false;
		//this->_date.LastFamilyDiscrepancy = 0;
		ows_search_result = false;
	}
	for (byte i = 0; i < 8; i++)
		newAddr[i] = this->_date.ows_ROM_NO[i];
	return (ows_search_result);
}

bool OneWire::read_bit() {
	bool			r;

	noInterrupts();
	ONEWARE_OUTPUT();
	delayMicroseconds(3);
	ONEWARE_INPUT(); // let pin float, pull up will raise
	delayMicroseconds(15);
	r = this->_digitalReadFast();
	delayMicroseconds(73);
	interrupts();
	return r != 0;
}

void OneWire::write_bit(bool bit) {
	noInterrupts();
	ONEWARE_OUTPUT();
	if (bit) {
		delayMicroseconds(10);
		this->_digitalWriteFast(1);
		delayMicroseconds(55);
	} else {
		delayMicroseconds(65);
		this->_digitalWriteFast(1);
		delayMicroseconds(5);
	}
	interrupts();
}

/* Private Methods */
inline void OneWire::_digitalWriteFast(uint8_t val) {//Digital write with some cached values for better perfomance
	*(volatile uint32_t *)this->_aliasAddr_out = (uint32_t) val;
}

inline size_t OneWire::_digitalReadFast() {//Digital read with some cached values for better perfomance
	return (*(volatile uint32_t *)this->_aliasAddr_in);
}

inline void OneWire::_pinModeFast(uint8_t mode) {//pinMode with some cached values for better perfomance
	size_t					real_pin;
	size_t					real_port;

	real_port = this->_real_port;
	if((real_pin = this->_real_pin) < 8)
		GPIO->P[real_port].MODEL = (GPIO->P[real_port].MODEL & ~(0xFu << (real_pin << 2))) | (mode << (real_pin << 2 ));
	else 
		GPIO->P[real_port].MODEH = (GPIO->P[real_port].MODEH & ~(0xFu << ((real_pin - 8) << 2))) | (mode << ((real_pin - 8) << 2));
}
