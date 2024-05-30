#ifndef _BL0937_
#define _BL0937_

#include "Arduino.h"
#include "ZUNO_Buttons.h"
#include "HandlerMapper.h"
#include "EEPROM.h"

#define DEF_V_REF 1.218

class BL0937 : protected ZMEHandlerMapper {
    public:
        BL0937(byte cfPin, byte cf1Pin,byte selPin, float vRef=DEF_V_REF);
        // ZMEHandlerMapper(SYS_HANLER_MAPPER_TIMER){
        // }


        void begin();
        
        float readActivePower();
        float readVoltageRMS();
        float readCurrentRMS();
        float getAccumulatedE(){ return _accumulatedEnergy; };
        void setKWH(float kwh) {_accumulatedEnergy = kwh;};
        void resKWH() {_accumulatedEnergy = 0;};
        void calcEnergy();

    private:
        byte _cfPin;
        byte _cf1Pin;
        byte _selPin;
        float _vRef;
        float _accumulatedEnergy;
        float _activePower;
        float _voltageRMS;
        float _currentRMS;
        unsigned long _lastMeasurementTime = 0;
        unsigned long _lastStorageTime = 0;

        unsigned long _readPulseDuration(int pin);

    protected:
        virtual void handleSysTimer(uint32_t ticks);
};

#endif