/* CO2 sensor SCD4x library for Z-Uno G2
 *  v. 1.0 07.09.2023  by Michael Pruefer
 *  based on Sensirion sensor documentation
 *  see https://sensirion.com/media/documents/E0F04247/631EF271/CD_DS_SCD40_SCD41_Datasheet_D1.pdf
 *
 */

#include "Arduino.h"
#include "ZUNO_SCD4x.h"
#include "Wire.h"

ZUNO_SCD4x::ZUNO_SCD4x()
{
}
	
bool ZUNO_SCD4x::startPeriodicMeasurement(void)
{
  if (sendCmd(SCD4x_CMD_STPM, 0)) return (true);
  return (false);
}

bool ZUNO_SCD4x::stopPeriodicMeasurement(void)
{
  if (sendCmd(SCD4x_CMD_SPPM, 500)) return (true);
  return (false);
}

void ZUNO_SCD4x::readMeasurement(void)
{
  if (sendCmd(SCD4x_CMD_REAM, 1))
  {
    Wire.requestFrom(SCD4x_ADDR, 9);
    byte data[2];
    data[0] = Wire.read();
    data[1] = Wire.read();
    uint8_t crc = Wire.read();
    uint8_t expectedCRC = calcCRC8(data, 2);
    if(expectedCRC == crc) CO2=data[0]*256 + data[1]; else comError=2;

    data[0] = Wire.read();
    data[1] = Wire.read();
    crc = Wire.read();
    expectedCRC = calcCRC8(data, 2);
    if(expectedCRC == crc) Temp=-45+175.0*(data[0]*256+data[1])/(65535); else comError=2;
    data[0] = Wire.read();
    data[1] = Wire.read();
    crc = Wire.read();
    expectedCRC = calcCRC8(data, 2);
    if(expectedCRC == crc) Hum=100.0*(data[0]*256+data[1])/(65535); else comError=2;
  }
}

bool ZUNO_SCD4x::getDataReadyStatus(void)
{
  uint16_t result = readDbyte(SCD4x_CMD_GDRA, 1);
  if (comError != 0)  return (false);

  //if least significant 11 bits are 0 → data not ready (docu)
  if ((result & 0x07ff) == 0x0000) return (false);

  return (true);
}

bool ZUNO_SCD4x::setTemperatureOffset(float tempOffset)
{
  uint16_t tOffset = tempOffset*65536/175;
  if (sendCmd(SCD4x_CMD_STOF, tOffset, 1)) return (true);
  return (false);
}

bool ZUNO_SCD4x::getTemperatureOffset(void)
{
  uint16_t result = readDbyte(SCD4x_CMD_GTOF, 1);
  if (comError != 0)  return (false);
  TempOffset = ((float)result) * 175.0 / 65536;
  return (true);
}

bool ZUNO_SCD4x::setSensorAltitude(uint16_t sensorAlt)
{
  if (sendCmd(SCD4x_CMD_SSAL, sensorAlt, 1)) return (true);
  return (false);
}

bool ZUNO_SCD4x::getSensorAltitude(void)
{
  uint16_t result = readDbyte(SCD4x_CMD_GSAL, 1);
  if (comError != 0)  return (false);
  sensorAlt=result;
  return (true);
}

bool ZUNO_SCD4x::setAmbientPressure(uint32_t ambPressure)
{
  uint16_t sensorAmbPressure = ambPressure/100;
  if (sendCmd(SCD4x_CMD_SAPR, sensorAmbPressure, 1)) return (true);
  return (false);
}

bool ZUNO_SCD4x::setAutomaticSelfCalibrationEnabled(uint16_t ASCEnabled)
{
  if (sendCmd(SCD4x_CMD_SACA, ASCEnabled, 1)) return (true);
  return (false);
}

bool ZUNO_SCD4x::getAutomaticSelfCalibrationEnabled(void)
{
  uint16_t result = readDbyte(SCD4x_CMD_GACA, 1);
  if (comError != 0)  return (false);
  sensorASC=result;
  return (true);
}

bool ZUNO_SCD4x::perform_forced_recalibration(uint16_t targetCO2ppm)
{
  if (sendCmd(SCD4x_CMD_SACA, targetCO2ppm, 400)) 
  {
    byte data1[2];
    Wire.requestFrom(SCD4x_ADDR,3);
    data1[0] = Wire.read();
    data1[1] = Wire.read();
    crc = Wire.read();
    uint8_t dataCRC = calcCRC8(data1, 2);
    if (crc != dataCRC) 
    {
      comError=2;
      return (false);
    }  
    uint16_t Correction = (uint16_t)data1[0] << 8 | data1[1]; 
    if (CO2Correction == 0xFFFF) return (false);
    CO2Correction = ((float)Correction) - 32768;  // see doc : result - 0x8000
    return (true);
  }
  return (false);
}

bool ZUNO_SCD4x::startLowPowerPeriodicMeasurement(void)
{
  if (sendCmd(SCD4x_CMD_SLPM, 0)) return (true);
  return (false);
}

bool ZUNO_SCD4x::PersistSettings(void)
{
  if (sendCmd(SCD4x_CMD_PERS, 800)) return (true);
  return (false);
}

bool ZUNO_SCD4x::getSerialNumber(void)
{
  if (sendCmd(SCD4x_CMD_GSER, 1))
  {
    byte sn1[2];
    byte sn2[2];
    byte sn3[2];
    uint8_t crc;
    comError=0;
    Wire.requestFrom(SCD4x_ADDR,9);
    sn1[0] = Wire.read();
    sn1[1] = Wire.read();
    crc = Wire.read();
    uint8_t dataCRC = calcCRC8(sn1, 2);
    if (crc != dataCRC) comError=2;
    sn2[0] = Wire.read();
    sn2[1] = Wire.read();
    crc = Wire.read();
    dataCRC = calcCRC8(sn2, 2);
    if (crc != dataCRC) comError=2;
    sn3[0] = Wire.read();
    sn3[1] = Wire.read();
    crc = Wire.read();
    dataCRC = calcCRC8(sn3, 2);
    if (crc != dataCRC) comError=2;
    if (comError ==0) 
    {
      char str[5];
      arrayToString(sn1,2,str);
      SerialNumber += str;
      arrayToString(sn2,2,str);
      SerialNumber += str;
      arrayToString(sn3,2,str);
      SerialNumber += str;
      return (true);
    }
    else
    { 
      SerialNumber ="error";    
    }  
  }
  return (false);
}

bool ZUNO_SCD4x::perfomFactoryReset(void)
{
  if (sendCmd(SCD4x_CMD_PFRS, 1200)) return (true);
  return (false);
}

bool ZUNO_SCD4x::reinit(void)
{
  if (sendCmd(SCD4x_CMD_PRIN, 20)) return (true);
  return (false);
}

bool ZUNO_SCD4x::measureSingleShot(void)
{
  if (sendCmd(SCD4x_CMD_MSSH, 5000)) return (true);
  return (false);
}

bool ZUNO_SCD4x::measureSingleShotRHTOnly(void)
{
  if (sendCmd(SCD4x_CMD_MSS1, 50)) return (true);
  return (false);
}

bool ZUNO_SCD4x::powerDown(void)
{
  if (sendCmd(SCD4x_CMD_PWDN, 1)) return (true);
  return (false);
}

bool ZUNO_SCD4x::wakeUp(void)
{
  if (sendCmd(SCD4x_CMD_WKUP, 1)) return (true);
  return (false);
}

bool ZUNO_SCD4x::getSensorData(void)
{
  bool result=getSerialNumber();
  result = result && getTemperatureOffset();
  result = result && getSensorAltitude();
  result = result && getAutomaticSelfCalibrationEnabled();
  return (result);
}  

uint16_t ZUNO_SCD4x::readDbyte(uint16_t cmdCode, uint16_t delayMs)
{
  comError=0;
  uint16_t result = 0xFFFF;
  Wire.beginTransmission(SCD4x_ADDR);
  Wire.write(cmdCode >> 8);   
  Wire.write(cmdCode & 0xFF); 
  if (Wire.endTransmission() != 0)
  {
    comError=1;                   //no ACK from SCD4x
    return result;
  }  
  delay(delayMs);

  Wire.requestFrom((uint8_t)SCD4x_ADDR, (uint8_t)3); // Request data and CRC
  if (Wire.available())
  {
    uint8_t data[2];
    data[0] = Wire.read();
    data[1] = Wire.read();
    uint8_t crc = Wire.read();
    result = (uint16_t)data[0] << 8 | data[1];
    uint8_t dataCRC = calcCRC8(data, 2);
    if (crc != dataCRC) 
      comError=2;
  }
  return (result);
}

bool ZUNO_SCD4x::sendCmd(uint16_t cmdCode, uint16_t delayMs)
{
  comError=0;
  Wire.beginTransmission(SCD4x_ADDR);
  Wire.write(cmdCode >> 8);   
  Wire.write(cmdCode & 0xFF); 
  if (Wire.endTransmission() != 0)
  {
    comError=1;                   //no ACK from SCD4x
    return (false);
  }  
  delay(delayMs);

  return (true);
}

bool ZUNO_SCD4x::sendCmd(uint16_t cmdCode, uint16_t parameter, uint16_t delayMs)
{
  comError=0;
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
  if (Wire.endTransmission() != 0)
  {
    comError=1;                   //no ACK from SCD4x
    return (false);
  }  
  delay(delayMs);

  return (true);
}

uint8_t ZUNO_SCD4x::calcCRC8(uint8_t data[], uint8_t len)
// see Sensirion doc
{
  uint8_t crc = 0xFF; 

  for (uint8_t i = 0; i < len; i++)
  {
    crc ^= data[i]; 
    for (uint8_t bit = 8; bit > 0; --bit)
    {
      if ((crc & 0x80) != 0)
        crc = (uint8_t)((crc << 1) ^ 0x31);
      else
        crc <<= 1;
    }
  }
  return crc; 
}

void ZUNO_SCD4x::arrayToString(byte array[], uint8_t len, char strBuffer[])
{
    for (uint8_t i = 0; i < len; i++)
    {
      byte nib1 = (array[i] >> 4) & 0x0F;
      byte nib2 = (array[i] >> 0) & 0x0F;
      strBuffer[i*2+0] = nib1 < 10 ? '0' + nib1 : 'A' + nib1 - 10;
      strBuffer[i*2+1] = nib2 < 10 ? '0' + nib2 : 'A' + nib2 - 10;
    }
    strBuffer[len*2] = '\0';
}