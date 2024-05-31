#include "BL0937.h"

BL0937::BL0937(byte cfPin, byte cf1Pin,byte selPin, float vRef):
                ZMEHandlerMapper(SYS_HANLER_MAPPER_TIMER),
                _cfPin(cfPin),
                _cf1Pin(cf1Pin),
                _selPin(selPin),
                _vRef(vRef){
}
void BL0937::begin(){
    unsigned long currentTime = millis();
    pinMode(_cfPin, INPUT);
    pinMode(_cf1Pin, INPUT);
    pinMode(_selPin, OUTPUT);

    _lastMeasurementTime = currentTime;
    _lastStorageTime = currentTime;
    
}
float BL0937::readActivePower() {
    unsigned long pulseDuration = _readPulseDuration(_cfPin);
    if (pulseDuration > 0) {
        float frequency = 1000000.0 / pulseDuration;
        _activePower = (frequency * _vRef * _vRef) / 1721506.0;
        return _activePower;
    }
    return 0;
}
float BL0937::readVoltageRMS() {
    digitalWrite(_selPin, LOW);
    delay(10);
    unsigned long pulseDuration = _readPulseDuration(_cf1Pin);
    if (pulseDuration > 0) {
        float frequency = 1000000.0 / pulseDuration;
        _voltageRMS = (frequency * _vRef) / 15397.0;
        return _voltageRMS;
    }
    return 0;
}
float BL0937::readCurrentRMS() {
    digitalWrite(_selPin, HIGH);
    delay(10);
    unsigned long pulseDuration = _readPulseDuration(_cf1Pin);
    if (pulseDuration > 0) {
        float frequency = 1000000.0 / pulseDuration;
        _currentRMS = (frequency * _vRef) / 94638.0;
        return _currentRMS;
    }
    return 0;
}

unsigned long BL0937::_readPulseDuration(int pin) {
    // unsigned long pulseDurationHigh = pulseIn(pin, HIGH);
    //the pulse width is fixed to 38uS(typical);
    unsigned long pulseDurationLow = pulseIn(pin, LOW);
    if (pulseDurationLow > 0) {
        return 38 + pulseDurationLow;
    }
    return 0;
}
void BL0937::calcEnergy(){
    _previousPower = _activePower;
    readActivePower();
    unsigned long currentTime = millis();
    unsigned long elapsedTime = currentTime - _lastMeasurementTime;
    _lastMeasurementTime = currentTime;
    _accumulatedEnergy += (_previousPower + _activePower) * 0.5f * (elapsedTime / 3600000.0f); // Translate from seconds to hours, because of KWh
}
void BL0937::handleSysTimer(uint32_t ticks){
    // (void) ticks;
    // every 10 ticks => about 100ms
    if ((ticks % 10) == 0)
        calcEnergy();
}
