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

#include "ZUNO_OneWire.h"

#include "Arduino.h"

//disable interrupts macros
#define NOINTERRUPTS() __asm volatile("cpsid i"::: "memory")
//inable interrupts macros
# define INTERRUPTS() __asm volatile("cpsie i"::: "memory")

OneWire::OneWire(byte pin): bus_pin(pin) {
	//Here we caching some values for better perfomance
    real_pin = getRealPin(pin);
    real_port = getRealPort(pin);

    aliasAddr_in = ((uint32_t) & GPIO->P[real_port].DIN);

    aliasAddr_out = ((uint32_t) & GPIO->P[real_port].DOUT);

    aliasAddr_out -= PER_MEM_BASE;
    aliasAddr_out <<= 5;
    aliasAddr_out += BITBAND_PER_BASE;
    aliasAddr_out += (real_pin << 2);

    aliasAddr_in -= PER_MEM_BASE;
    aliasAddr_in <<= 5;
    aliasAddr_in += BITBAND_PER_BASE;
    aliasAddr_in += (real_pin << 2);

    pinModeFast(INPUT);
    reset_search();
}
//Digital write with some cached values for better perfomance
inline void OneWire::digitalWriteFast(uint8_t val) {
    *(volatile uint32_t * ) aliasAddr_out = (uint32_t) val;
}

//Digital read with some cached values for better perfomance
inline int OneWire::digitalReadFast() {
    return ( * (volatile uint32_t * ) aliasAddr_in);
}
//pinMode with some cached values for better perfomance
inline void OneWire::pinModeFast(uint8_t mode) {
    int real_mode = mode & 0xFF;
    bool on_off = ((mode & 0x100)  != 0);

    if( real_mode != DISABLED )
        digitalWriteFast(on_off);
		//digitalWrite(pin, on_off);
    
	if(real_pin < 8)
    	GPIO->P[real_port].MODEL = (GPIO->P[real_port].MODEL & ~(0xFu << 		(real_pin))) | (real_mode << (real_pin << 2 ));
	else 
      GPIO->P[real_port].MODEH = (GPIO->P[real_port].MODEH & ~(0xFu << ((real_pin - 8) << 2))) | (mode << ((real_pin - 8) << 2));
	
	if( real_mode == DISABLED )
		digitalWriteFast(on_off);
        //digitalWrite(pin, on_off);

}
// Perform the onewire reset function.  We will wait up to 250uS for
// the bus to come high, if it doesn't then it is broken or shorted
// and we return a 0;
//
// Returns 1 if a device asserted a presence pulse, 0 otherwise.
//
byte OneWire::reset(void) {
    byte r;
    byte retries = 125;

	NOINTERRUPTS();
    // noInterrupts();
    // sysClockSet(SYSCLOCK_NORMAL);
    // pinMode(bus_pin, INPUT);
    pinModeFast(INPUT);
	// wait until the wire is high... just in case
    do {
        if ((--retries) == 0)
            return 0;
        delayMicroseconds(2);
    } while (!digitalReadFast());
    // pinMode(bus_pin, OUTPUT);
	pinModeFast(OUTPUT);
	digitalWriteFast(0);
    //digitalWrite(bus_pin, 0);
    INTERRUPTS();
	// interrupts();
    delayMicroseconds(480);

	NOINTERRUPTS();
    // noInterrupts();
    // pinMode(bus_pin, INPUT); // allow it to float
    pinModeFast(INPUT);
	delayMicroseconds(70);
    r = digitalReadFast();
	INTERRUPTS();
    // interrupts();

    delayMicroseconds(410);
    // sysClockNormallize();
    return r == 0;
}

void OneWire::write(byte v, byte power) {
    byte bitMask;
    NOINTERRUPTS();
    // sysClockSet(SYSCLOCK_NORMAL);
    //digitalWrite(27, 0);
    pinModeFast(OUTPUT);;
    //digitalWrite(27, 1); //for debug purposes
    for (bitMask = 0x01; bitMask; bitMask <<= 1) {

        //digitalWrite(bus_pin, 0);
        digitalWriteFast(0);

        if ((bitMask & v)) {
            delayMicroseconds(10);
            //digitalWrite(bus_pin, 1);
            digitalWriteFast(1);
            delayMicroseconds(55);
        } else {
            delayMicroseconds(65);
            //digitalWrite(bus_pin, 1);
            digitalWriteFast(1);
            delayMicroseconds(5);
        }
        INTERRUPTS();
    }
    if (!power) {
        pinModeFast(INPUT);;
    }
    // sysClockNormallize();
}
byte OneWire::read() {
    byte bitMask;
    byte r;
    byte res = 0;

    //sysClockSet(SYSCLOCK_NORMAL);
	NOINTERRUPTS();

    for (bitMask = 0x01; bitMask; bitMask <<= 1) {

        pinModeFast(OUTPUT);;
        // digitalWrite(bus_pin, 0);
        digitalWriteFast(0);
        delayMicroseconds(7);

        pinModeFast(INPUT); // let pin float, pull up will raise
        delayMicroseconds(15);

        r = digitalReadFast();
        delayMicroseconds(94);

        if (r)
            res |= bitMask;
    }
	INTERRUPTS();
    //sysClockNormallize();
    return res;
}

//
// Do a ROM select
//
void OneWire::select(byte * rom) {
    byte i;

    write(0x55); // Choose ROM

    for (i = 0; i < 8; i++)
        write(rom[i]);
}

void OneWire::skip() {
    write(0xCC); // Skip ROM
}
void OneWire::depower() {
    pinModeFast(INPUT);;
}
void OneWire::readROM(byte * rom) {
    byte i;

    write(0x33);
    for (i = 0; i < 8; i++)
        rom[i] = read();

}

bool OneWire::read_bit() {
    bool r;
    // sysClockSet(SYSCLOCK_NORMAL);
    // noInterrupts(); 
    NOINTERRUPTS();
    pinModeFast(OUTPUT);;
    digitalWrite(bus_pin, 0);
    delayMicroseconds(3);
    pinModeFast(INPUT);; // let pin float, pull up will raise
    delayMicroseconds(15);
    r = digitalReadFast();
    delayMicroseconds(73);
    INTERRUPTS();
    // sysClockNormallize();
    // interrupts();

    return r != 0;
}
void OneWire::write_bit(bool bit) {
    //Serial0.println("BIT");
    // sysClockSet(SYSCLOCK_NORMAL);
    // noInterrupts();
	NOINTERRUPTS();
    pinModeFast(OUTPUT);;
    digitalWrite(bus_pin, 0);
    if (bit) {
        delayMicroseconds(10);
		digitalWriteFast(1);
        // digitalWrite(bus_pin, 1);
        delayMicroseconds(55);
    } else {
        delayMicroseconds(65);
		digitalWriteFast(1);
        // digitalWrite(bus_pin, 1);
        delayMicroseconds(5);
    }
	INTERRUPTS();
    // sysClockNormallize();
    // interrupts();
}

//
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
//
// ------------------------------------------------------------
// We use global vars here to minimize stack usage
// ------------------------------------------------------------
void OneWire::reset_search() {
    LastDiscrepancy = 0;
    LastDeviceFlag = FALSE;
    LastFamilyDiscrepancy = 0;
    byte i = 7;
    while (i--)
        ows_ROM_NO[i] = 0;
}
bool OneWire::search(uint8_t * newAddr) {

    // initialize for search
    ows_id_bit_number = 1;
    ows_last_zero = 0;
    ows_rom_byte_number = 0;
    ows_rom_byte_mask = 1;
    ows_search_result = false;

    // if the last call was not the last one
    if (!LastDeviceFlag) {
        // 1-Wire reset
        if (!reset()) {
            // reset the search
            LastDiscrepancy = 0;
            LastDeviceFlag = false;
            LastFamilyDiscrepancy = 0;
            return false;
        }

        // issue the search command
        write(0xF0);

        // loop to do the search
        do {
            // serial number search direction write bit
            //write_bit(1); 
            // read a bit and its complement
            ows_id_bit = read_bit();
            ows_cmp_id_bit = read_bit();

            //Serial0.print(0x80 | ows_id_bit << 1 | ows_cmp_id_bit ,HEX);

            // check for no devices on 1-wire
            if ((ows_id_bit == 1) && (ows_cmp_id_bit == 1))
                break;
            // all devices coupled have 0 or 1
            if (ows_id_bit != ows_cmp_id_bit) {
                ows_search_direction = ows_id_bit; // bit write value for search
            } else {
                // if this discrepancy if before the Last Discrepancy
                // on a previous next then pick the same as last time
                if (ows_id_bit_number < LastDiscrepancy) {
                    ows_search_direction = ows_ROM_NO[ows_rom_byte_number];
                    ows_search_direction &= ows_rom_byte_mask;
                    ows_search_direction = (ows_search_direction > 0);
                } else {
                    // if equal to last pick 1, if not then pick 0
                    ows_search_direction = (ows_id_bit_number == LastDiscrepancy);

                }

                // if 0 was picked then record its position in LastZero
                if (ows_search_direction == 0) {
                    ows_last_zero = ows_id_bit_number;

                    // check for Last discrepancy in family
                    if (ows_last_zero < 9)
                        LastFamilyDiscrepancy = ows_last_zero;
                }
            }
            // set or clear the bit in the ROM byte rom_byte_number
            // with mask rom_byte_mask
            if (ows_search_direction) {
                ows_ROM_NO[ows_rom_byte_number] |= ows_rom_byte_mask;
            } else {
                ows_ROM_NO[ows_rom_byte_number] &= ~(ows_rom_byte_mask);
            }
            // serial number search direction write bit
            write_bit(ows_search_direction);

            // increment the byte counter id_bit_number
            // and shift the mask rom_byte_mask
            ows_id_bit_number++;
            ows_rom_byte_mask <<= 1;

            // if the mask is 0 then go to new SerialNum byte rom_byte_number and reset mask
            if (ows_rom_byte_mask == 0) {
                ows_rom_byte_number++;
                ows_rom_byte_mask = 1;
            }

        }
        while (ows_rom_byte_number < 8); // loop until through all ROM bytes 0-7

        // if the search was successful then
        if (ows_id_bit_number > 64) {
            // search successful so set LastDiscrepancy,LastDeviceFlag,search_result
            LastDiscrepancy = ows_last_zero;

            // check for last device
            if (LastDiscrepancy == 0)
                LastDeviceFlag = true;

            ows_search_result = true;
        }
    }

    // if no device found then reset counters so next 'search' will be like a first
    if (!ows_search_result || !ows_ROM_NO[0]) {
        LastDiscrepancy = 0;
        LastDeviceFlag = false;
        LastFamilyDiscrepancy = 0;
        ows_search_result = false;
    }
    for (byte i = 0; i < 8; i++)
        newAddr[i] = ows_ROM_NO[i];
    return ows_search_result;

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