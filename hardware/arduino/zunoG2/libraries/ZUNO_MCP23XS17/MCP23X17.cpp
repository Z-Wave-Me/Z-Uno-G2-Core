/*
 * Copyright (c) 2014, Majenko Technologies
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 * 
 *  1. Redistributions of source code must retain the above copyright notice, 
 *     this list of conditions and the following disclaimer.
 * 
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 * 
 *  3. Neither the name of Majenko Technologies nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without 
 *     specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE 
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <MCP23X17.h>
#include "Arduino.h"
/*! The constructor takes three parameters.  The first is an SPI class
 *  pointer.  This is the address of an SPI object (either the default
 *  SPI object on the Arduino, or an object made using the DSPIx classes
 *  on the chipKIT).  The second parameter is the chip select pin number
 *  to use when communicating with the chip.  The third is the internal
 *  address number of the chip.  This is controlled by the three Ax pins
 *  on the chip.
 *  
 *  Example:
 * 
 *  
 *      MCP23S17 myExpander(&SPI, 10, 0);
 * 
 */

MCP23X17::MCP23X17() {
    _reg[IODIRA] = 0xFF;
    _reg[IODIRB] = 0xFF;
    _reg[IPOLA] = 0x00;
    _reg[IPOLB] = 0x00;
    _reg[GPINTENA] = 0x00;
     _reg[GPINTENB] = 0x00;
    _reg[DEFVALA] = 0x00;
    _reg[DEFVALB] = 0x00;
    _reg[INTCONA] = 0x00;
    _reg[INTCONB] = 0x00;
    _reg[IOCONA] = 0x18;
    _reg[IOCONB] = 0x18;
    _reg[GPPUA] = 0x00;
    _reg[GPPUB] = 0x00;
    _reg[INTFA] = 0x00;
    _reg[INTFB] = 0x00;
    _reg[INTCAPA] = 0x00;
    _reg[INTCAPB] = 0x00;
    _reg[GPIOA] = 0x00;
    _reg[GPIOB] = 0x00;
    _reg[OLATA] = 0x00;
    _reg[OLATB] = 0x00;
}

void MCP23X17::begin(){

}
void MCP23X17::readRegister(uint8_t addr){

} 
void MCP23X17::writeRegister(uint8_t addr){

}
void MCP23X17::readAll(){

}
void MCP23X17::writeAll(){

}

void MCP23X17::pinMode(uint8_t pin, uint16_t mode) {
    if (pin >= 16) {
        return;
    }
    uint8_t dirReg = IODIRA;
    uint8_t puReg = GPPUA;
    if (pin >= 8) {
        pin -= 8;
        dirReg = IODIRB;
        puReg = GPPUB;
    }

    switch (mode) {
        case OUTPUT:
            _reg[dirReg] &= ~(1<<pin);
            writeRegister(dirReg);
            break;

        case INPUT:
        case INPUT_PULLUP:
            _reg[dirReg] |= (1<<pin);
            writeRegister(dirReg);
            if (mode == INPUT_PULLUP) {
                _reg[puReg] |= (1<<pin);
            } else {
                _reg[puReg] &= ~(1<<pin);
            }
            writeRegister(puReg);
            break;
    }
}

void MCP23X17::digitalWrite(uint8_t pin, uint8_t value) {
    if (pin >= 16) {
        return;
    }
    uint8_t dirReg = IODIRA;
    uint8_t puReg = GPPUA;
    uint8_t latReg = OLATA;
    if (pin >= 8) {
        pin -= 8;
        dirReg = IODIRB;
        puReg = GPPUB;
        latReg = OLATB;
    }

    uint8_t mode = (_reg[dirReg] & (1<<pin)) == 0 ? OUTPUT : INPUT;
    
    switch (mode) {
        case OUTPUT:
            if (value == 0) {
                _reg[latReg] &= ~(1<<pin);
            } else {
                _reg[latReg] |= (1<<pin);
            }
            writeRegister(latReg);
            break;

        case INPUT:
            if (value == 0) {
                _reg[puReg] &= ~(1<<pin);
            } else {
                _reg[puReg] |= (1<<pin);
            }
            writeRegister(puReg);
            break;
    }
}

uint8_t MCP23X17::digitalRead(uint8_t pin) {
    if (pin >= 16) {
        return 0;
    }
    uint8_t dirReg = IODIRA;
    uint8_t portReg = GPIOA;
    uint8_t latReg = OLATA;
    if (pin >= 8) {
        pin -= 8;
        dirReg = IODIRB;
        portReg = GPIOB;
        latReg = OLATB;
    }

    uint8_t mode = (_reg[dirReg] & (1<<pin)) == 0 ? OUTPUT : INPUT;

    switch (mode) {
        case OUTPUT: 
            return _reg[latReg] & (1<<pin) ? HIGH : LOW;
        case INPUT:
            readRegister(portReg);
            return _reg[portReg] & (1<<pin) ? HIGH : LOW;
    }
    return 0;
}

uint8_t MCP23X17::readPort(uint8_t port) {
    if (port == 0) {
        readRegister(GPIOA);
        return _reg[GPIOA];
    } else {
        readRegister(GPIOB);
        return _reg[GPIOB];
    }
}

uint16_t MCP23X17::readPort() {
    readRegister(GPIOA);
    readRegister(GPIOB);
    return (_reg[GPIOB] << 8) | _reg[GPIOA];
}

void MCP23X17::writePort(uint8_t port, uint8_t val) {
    if (port == 0) {
        _reg[OLATA] = val;
        writeRegister(OLATA);
    } else {
        _reg[OLATB] = val;
        writeRegister(OLATB);
    }
}

void MCP23X17::writePort(uint16_t val) {
    _reg[OLATB] = val >> 8;
    _reg[OLATA] = val & 0xFF;
    writeRegister(OLATA);
    writeRegister(OLATB);
}

void MCP23X17::enableInterrupt(uint8_t pin, uint8_t type) {
    if (pin >= 16) {
        return;
    }
    uint8_t intcon = INTCONA;
    uint8_t defval = DEFVALA;
    uint8_t gpinten = GPINTENA;

    if (pin >= 8) {
        pin -= 8;
        intcon = INTCONB;
        defval = DEFVALB;
        gpinten = GPINTENB;
    }
    switch (type) {
        case CHANGE:
            _reg[intcon] &= ~(1<<pin);
            break;
        case RISING:
            _reg[intcon] |= (1<<pin);
            _reg[defval] &= ~(1<<pin);
            break;
        case FALLING:
            _reg[intcon] |= (1<<pin);
            _reg[defval] |= (1<<pin);
            break;
    }
    _reg[gpinten] |= (1<<pin);
    writeRegister(intcon);
    writeRegister(defval);
    writeRegister(gpinten);
}

void MCP23X17::disableInterrupt(uint8_t pin) {
    if (pin >= 16) {
        return;
    }
    uint8_t gpinten = GPINTENA;

    if (pin >= 8) {
        pin -= 8;
        gpinten = GPINTENB;
    }

    _reg[gpinten] &= ~(1<<pin);
    writeRegister(gpinten);
}

void MCP23X17::setMirror(boolean m) {
    if (m) {
        _reg[IOCONA] |= (1<<6);
        _reg[IOCONB] |= (1<<6);
    } else {
        _reg[IOCONA] &= ~(1<<6);
        _reg[IOCONB] &= ~(1<<6);
    }
    writeRegister(IOCONA);
}

uint16_t MCP23X17::getInterruptPins() {
    readRegister(INTFA);
    readRegister(INTFB);

    return (_reg[INTFB] << 8) | _reg[INTFA];
}

void MCP23X17::setInterruptLevel(uint8_t level) {
    if (level == LOW) {
        _reg[IOCONA] &= ~(1<<1);
        _reg[IOCONB] &= ~(1<<1);
    } else {
        _reg[IOCONA] |= (1<<1);
        _reg[IOCONB] |= (1<<1);
    }
    writeRegister(IOCONA);
}

void MCP23X17::setInterruptOD(boolean openDrain) {
    if (openDrain) {
        _reg[IOCONA] |= (1<<2);
        _reg[IOCONB] |= (1<<2);
    } else {
        _reg[IOCONA] &= ~(1<<2);
        _reg[IOCONB] &= ~(1<<2);
    }
    writeRegister(IOCONA);
}

MCP23S17::MCP23S17(SPIClass *spi, uint8_t cs, uint8_t addr) {
    _spi = spi;
    _cs = cs;
    _addr = addr;
}

void MCP23S17::begin() {
    _spi->begin();
    _spi->beginTransaction(250000u, MSBFIRST, SPI_MODE0);
    ::pinMode(_cs, OUTPUT);
    ::digitalWrite(_cs, HIGH);
    uint8_t cmd = 0b01000000;
    ::digitalWrite(_cs, LOW);
    _spi->transfer(cmd);
    _spi->transfer(IOCONA);
    _spi->transfer(0x18);
    ::digitalWrite(_cs, HIGH);
    writeAll();
}

void MCP23S17::readRegister(uint8_t addr){
    if (addr > 21) {
        return;
    }
    uint8_t cmd = MCP23X17_BASE_ADDR | ((_addr & 0b111) << 1) | MCP23X17_READ_BIT;
    ::digitalWrite(_cs, LOW);
    delay(50);
    _spi->transfer(cmd);
    _spi->transfer(addr);
    _reg[addr] = _spi->transfer(0xFF);
    ::digitalWrite(_cs, HIGH);
}

void MCP23S17::writeRegister(uint8_t addr) {
    if (addr > 21) {
        return;
    }
    uint8_t cmd = MCP23X17_BASE_ADDR | ((_addr & 0b111) << 1) | MCP23X17_WRITE_BIT;
    ::digitalWrite(_cs, LOW);
    delay(50);
    _spi->transfer(cmd);
    _spi->transfer(addr);
    _spi->transfer(_reg[addr]);
    ::digitalWrite(_cs, HIGH);
}

void MCP23S17::writeAll() {
    uint8_t cmd = MCP23X17_BASE_ADDR | ((_addr & 0b111) << 1) | MCP23X17_WRITE_BIT;
    ::digitalWrite(_cs, LOW);
    delay(50);
    _spi->transfer(cmd);
    _spi->transfer((uint8_t)0);
    for (uint8_t i = 0; i < 22; i++) {
        _spi->transfer((const uint8_t)_reg[i]);
    }
    ::digitalWrite(_cs, HIGH);
}


void MCP23S17::readAll() {
    uint8_t cmd = MCP23X17_BASE_ADDR | ((_addr & 0b111) << 1) | MCP23X17_WRITE_BIT;
    ::digitalWrite(_cs, LOW);
    delay(50);
    _spi->transfer(cmd);
    _spi->transfer((uint8_t)0x00);
    for (uint8_t i = 0; i < 22; i++) {
        _reg[i] = _spi->transfer(0xFF);
    }
    ::digitalWrite(_cs, HIGH);
}


MCP23017::MCP23017(TwoWire *i2c, uint8_t addr){
    _i2c = i2c;
    _addr = addr;
}

void MCP23017::begin(){
    _i2c->begin();
    _i2c->beginTransmission(MCP23X17_BASE_ADDR >> 1 | _addr);
    _i2c->write(IOCONA);
    _i2c->write(0x18);
    _i2c->endTransmission();   
}

void MCP23017::writeRegister(uint8_t addr){
      if (addr > 21) {
        return;
    }
    _i2c->beginTransmission(MCP23X17_BASE_ADDR >> 1 | _addr);
    _i2c->write(addr);
    _i2c->write(_reg[addr]);
    _i2c->endTransmission();
}

void MCP23017::readRegister(uint8_t addr){
  if (addr > 21) {
        return;
    }
    uint8_t cmd = MCP23X17_BASE_ADDR >> 1| _addr; 
    _i2c->beginTransmission(cmd);
    _i2c->write(addr);
    _i2c->endTransmission();
    _i2c->requestFrom(cmd, 1);
    _reg[addr] = _i2c->read();
}

void MCP23017::writeAll(){
    uint8_t cmd = MCP23X17_BASE_ADDR >> 1 | _addr;
    _i2c->beginTransmission(cmd);
    _i2c->write((uint8_t)0);
    for (uint8_t i = 0; i < 22; i++) {
        _i2c->write((const uint8_t)_reg[i]);
    }
}

void MCP23017::readAll(){
    uint8_t cmd = MCP23X17_BASE_ADDR | ((_addr & 0b111) << 1) | MCP23X17_WRITE_BIT;
    _i2c->beginTransmission(cmd);
    _i2c->write((uint8_t)0x00);
    _i2c->endTransmission();
    _i2c->requestFrom(cmd, 21);
    uint8_t i = 0;
    while (_i2c->available())
    {
        _reg[i] = _i2c->read();
        i++;
    }
}