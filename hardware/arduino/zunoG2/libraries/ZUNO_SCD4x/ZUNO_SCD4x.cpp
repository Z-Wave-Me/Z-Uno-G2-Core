/* CO2 sensor SCD4x library for Z-Uno G2
 *  v. 1.0 07.09.2023  by Michael Pruefer
 *  based on Sensirion sensor documentation
 *  see https://sensirion.com/media/documents/E0F04247/631EF271/CD_DS_SCD40_SCD41_Datasheet_D1.pdf
 *
 */

#include "Arduino.h"
#include "ZUNO_SCD4x.h"
#include "Wire.h"
ZUNO_SCD4x::ZUNO_SCD4x(){
}
bool ZUNO_SCD4x::startPeriodicMeasurement(void) {
  if (sendCmd(SCD4x_CMD_STPM, 0)) 
    return true;
  return false;
}
bool ZUNO_SCD4x::stopPeriodicMeasurement(void) {
  return sendCmd(SCD4x_CMD_SPPM, 500);
}
void ZUNO_SCD4x::readMeasurement(void) {
  if (!sendCmd(SCD4x_CMD_REAM, 1))
    return;
  Wire.requestFrom(SCD4x_ADDR, 9);
  uint16_t result;
  _extract2BytesValue(_CO2);
  if(_extract2BytesValue(result))
    _Temp = -45 +175.0f*result/65535.0f;
  if(_extract2BytesValue(result))
    _Hum=100.0f*result/65535.0f;
}
bool ZUNO_SCD4x::getDataReadyStatus(void) {
  uint16_t result = readDbyte(SCD4x_CMD_GDRA, 1);
  if (_comError != 0)  
    return false;
  //if least significant 11 bits are 0 → data not ready (docu)
  if ((result & 0x07ff) == 0x0000) 
    return false;
  return true;
}

bool ZUNO_SCD4x::setTemperatureOffset(float tempOffset) {
  uint16_t tOffset = tempOffset*65536/175; // ? 65535 may be is the right value?
  return sendCmd(SCD4x_CMD_STOF, tOffset, 1);
}
bool ZUNO_SCD4x::getTemperatureOffset(void){
  uint16_t result = readDbyte(SCD4x_CMD_GTOF, 1);
  if (_comError != COMMUNICATION_ERROR_OK)  
    return false;
  _TempOffset = ((float)result) * 175.0 / 65536; // ? 65535 may be is the right value?
  return true;
}
bool ZUNO_SCD4x::setSensorAltitude(uint16_t sensorAlt){
  return sendCmd(SCD4x_CMD_SSAL, sensorAlt, 1);
}
bool ZUNO_SCD4x::getSensorAltitude(void) { 
  uint16_t result = readDbyte(SCD4x_CMD_GSAL, 1);
  if (_comError != COMMUNICATION_ERROR_OK)  
    return false;
  _sensorAlt = result;
  return true;
}
bool ZUNO_SCD4x::setAmbientPressure(uint32_t ambPressure) {
  uint16_t sensorAmbPressure = ambPressure/100;
  return sendCmd(SCD4x_CMD_SAPR, sensorAmbPressure, 1);
}
bool ZUNO_SCD4x::setAutomaticSelfCalibrationEnabled(uint16_t ASCEnabled) {
  return sendCmd(SCD4x_CMD_SACA, ASCEnabled, 1);
}
bool ZUNO_SCD4x::getAutomaticSelfCalibrationEnabled(void) {
  uint16_t result = readDbyte(SCD4x_CMD_GACA, 1);
  if (_comError != COMMUNICATION_ERROR_OK)  
    return false;
  _sensorASC = result;
  return (true);
}
bool ZUNO_SCD4x::performFocedRecalibraion(uint16_t targetCO2ppm) {
  if (!sendCmd(SCD4x_CMD_SACA, targetCO2ppm, 400))
    return false;
  uint16_t Correction;
  if(!_extract2BytesValue(Correction)){
    return false;
  }
  if (Correction == 0xFFFF) 
    return false;
  _CO2Correction = ((float)Correction) - 32768;  // see doc : result - 0x8000
  return true;
}
bool ZUNO_SCD4x::startLowPowerPeriodicMeasurement(void) {
  return sendCmd(SCD4x_CMD_SLPM, 0);
}
bool ZUNO_SCD4x::PersistSettings(void) {
  return sendCmd(SCD4x_CMD_PERS, 800);
}
void __triade2HStr(uint8_t b, char * symb){
  *symb = '0' + b;
  if(b > 10)
    *symb = 'A' + (b-10); 
}
void __int16toHStr(uint16_t  val, char * &str) {
    int i;
    str += 4; // Use the descend byte order
    for(i=0;i<4;i++,str--,val>>=4)
      __triade2HStr(val & 0x0F, str);
    str += 4; // Fill the next field
}
bool ZUNO_SCD4x::getSerialNumber(void) {
  if (!sendCmd(SCD4x_CMD_GSER, 1))
    return false;
  _comError = COMMUNICATION_ERROR_OK;
  Wire.requestFrom(SCD4x_ADDR,9);
  int i;
  char * p_str = _serialNumber;
  for(i=0;i<3;i++){
    uint16_t rs;
    _extract2BytesValue(rs);
    __int16toHStr(rs, p_str);
  }
  if (_comError != COMMUNICATION_ERROR_OK) {
    strcpy(_serialNumber, "error");
    return false;
  }
  return true;
}
bool ZUNO_SCD4x::perfomFactoryReset(void) {
  return sendCmd(SCD4x_CMD_PFRS, 1200);
}
bool ZUNO_SCD4x::reinit(void) {
  return sendCmd(SCD4x_CMD_PRIN, 20);
}
bool ZUNO_SCD4x::measureSingleShot(void) {
  return sendCmd(SCD4x_CMD_MSSH, 5000);
}
bool ZUNO_SCD4x::measureSingleShotRHTOnly(void) {
  return sendCmd(SCD4x_CMD_MSS1, 50);
}
bool ZUNO_SCD4x::powerDown(void) {
  return sendCmd(SCD4x_CMD_PWDN, 1);
}
bool ZUNO_SCD4x::wakeUp(void) {
  return sendCmd(SCD4x_CMD_WKUP, 1);
}
bool ZUNO_SCD4x::getSensorData(void) {
  bool result=getSerialNumber();
  result &=  getTemperatureOffset();
  result &= getSensorAltitude();
  result &= getAutomaticSelfCalibrationEnabled();
  return result;
}  
uint16_t ZUNO_SCD4x::readDbyte(uint16_t cmdCode, uint16_t delayMs) {
  _comError = COMMUNICATION_ERROR_OK;
  uint16_t result = 0xFFFF;
  Wire.beginTransmission(SCD4x_ADDR);
  Wire.write(cmdCode >> 8);   
  Wire.write(cmdCode & 0xFF); 
  if (Wire.endTransmission() != 0) {
    _comError = COMMUNICATION_ERROR_I2C;  //no ACK from SCD4x
    return result;
  }  
  delay(delayMs);
  Wire.requestFrom((uint8_t)SCD4x_ADDR, (uint8_t)3); // Request data and CRC
  if (Wire.available()) {
    _extract2BytesValue(result);
  }
  return result;
}
bool ZUNO_SCD4x::sendCmd(uint16_t cmdCode, uint16_t delayMs) {
  _comError= COMMUNICATION_ERROR_OK;
  Wire.beginTransmission(SCD4x_ADDR);
  Wire.write(cmdCode >> 8);   
  Wire.write(cmdCode & 0xFF); 
  if (Wire.endTransmission() != 0) {
    _comError=COMMUNICATION_ERROR_I2C;                   //no ACK from SCD4x
    return false;
  }  
  delay(delayMs);
  return true;
}
bool ZUNO_SCD4x::sendCmd(uint16_t cmdCode, uint16_t parameter, uint16_t delayMs) {
  _comError = COMMUNICATION_ERROR_OK;
  uint8_t data[2];
  data[0] = parameter >> 8;
  data[1] = parameter & 0xFF;
  uint8_t dataCRC = calcCRC8(data, 2);
  Wire.beginTransmission(SCD4x_ADDR);
  Wire.write(cmdCode >> 8);   
  Wire.write(cmdCode & 0xFF); 
  Wire.write(data[0]);   
  Wire.write(data[1]); 
  Wire.write(dataCRC); 
  if (Wire.endTransmission() != 0) {
    _comError = COMMUNICATION_ERROR_I2C; //no ACK from SCD4x
    return false;
  }  
  delay(delayMs);
  return true;
}
// see Sensirion doc
uint8_t ZUNO_SCD4x::calcCRC8(uint8_t data[], uint8_t len){
  uint8_t crc = 0xFF; 
  for (uint8_t i = 0; i < len; i++) {
    crc ^= data[i]; 
    for (uint8_t bit = 8; bit > 0; --bit) {
      if ((crc & 0x80) != 0)
        crc = (uint8_t)((crc << 1) ^ 0x31);
      else
        crc <<= 1;
    }
  }
  return crc; 
}
bool ZUNO_SCD4x::_extract2BytesValue(uint16_t & result){
  uint8_t data[2];
  data[0] = Wire.read();
  data[1] = Wire.read();
  uint8_t crc = Wire.read();
  uint8_t expectedCRC = calcCRC8(data, 2);
  if(expectedCRC != crc) {
      _comError = COMMUNICATION_ERROR_CRC;
      return false;
  }
  result = ((((uint32_t)data[0]) << 8 ) | data[1]);
  return true;
}