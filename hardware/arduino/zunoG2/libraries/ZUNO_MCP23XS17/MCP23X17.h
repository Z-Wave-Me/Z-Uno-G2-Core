/*
 * Copyright (c) , Majenko Technologies
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


#ifndef _MCP23X17_H
#define _MCP23X17_H

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#define MCP23X17_READ_BIT   0x1
#define MCP23X17_WRITE_BIT  0x0
#define MCP23X17_BASE_ADDR  0x40


class MCP23X17 {
    protected:
        enum {
            IODIRA,     IODIRB,
            IPOLA,      IPOLB,
            GPINTENA,   GPINTENB,
            DEFVALA,    DEFVALB,
            INTCONA,    INTCONB,
            IOCONA,     IOCONB,
            GPPUA,      GPPUB,
            INTFA,      INTFB,
            INTCAPA,    INTCAPB,
            GPIOA,      GPIOB,
            OLATA,      OLATB
        };
        uint8_t _reg[22];   /*! Local mirrors of the 22 internal registers of the MCP23S17 chip */
        uint8_t _addr;  /*! 3-bit chip address */

        virtual void begin();
        virtual void readRegister(uint8_t addr); 
        virtual void writeRegister(uint8_t addr);
        virtual void readAll();
        virtual void writeAll();
    protected:
        MCP23X17();
    public:
       
        // void begin();
        void pinMode(uint8_t pin, uint16_t mode);
        void digitalWrite(uint8_t pin, uint8_t value);
        uint8_t digitalRead(uint8_t pin);
        uint8_t readPort(uint8_t port);
        uint16_t readPort();
        void writePort(uint8_t port, uint8_t val);
        void writePort(uint16_t val);
        void enableInterrupt(uint8_t pin, uint8_t type);
        void disableInterrupt(uint8_t pin);
        void setMirror(boolean m);
        uint16_t getInterruptPins();
        uint16_t getInterruptValue();
        void setInterruptLevel(uint8_t level);
        void setInterruptOD(boolean openDrain);
};


class MCP23017 : public MCP23X17{
    private:
        TwoWire     *_i2c;

        virtual void readRegister(uint8_t addr);
        virtual void writeRegister(uint8_t addr);
        virtual void readAll();
        virtual void writeAll();
    public:
        MCP23017(TwoWire *i2c, uint8_t addr);
        virtual void begin();
};

class MCP23S17 : public MCP23X17{
    private:
        SPIClass    *_spi; /*! This points to a valid SPI object created from the Arduino SPI library. */
        uint8_t     _cs;    /*! Chip select pin */

        void readRegister(uint8_t addr);
        void writeRegister(uint8_t addr);
        void readAll();
        void writeAll();
    public:
        void begin();
        MCP23S17(SPIClass *spi, uint8_t cs, uint8_t addr);
};

#endif
