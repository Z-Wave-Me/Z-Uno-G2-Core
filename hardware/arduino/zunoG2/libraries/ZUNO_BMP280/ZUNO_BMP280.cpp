/*************************************************** 
  This is a library for the Bosch BMP280/BME280 Barometric Pressure + Temp sensor + Humidity sensor

  Designed specifically to work with the Bosch BMP280 or BME280 sensors 
  Writen by Z-Wave>ME team for Z-Uno project.
  Used code from:
  1) Written by Limor Fried/Ladyada for Adafruit Industries.  
      https://github.com/adafruit/Adafruit_BME280_Library
      https://github.com/adafruit/Adafruit_BMP280_Library

  2) Bosch datasheets
    https://cdn-shop.adafruit.com/datasheets/BST-BMP280-DS001-11.pdf
    https://cdn-shop.adafruit.com/datasheets/BST-BME280_DS001-10.pdf

  Slightly adoptated for fix-point i8051 math and Z-Uno stack behaviour.
 ****************************************************/

#include "Arduino.h"
#include "ZUNO_BMP280.h"


/*!
 *   @brief  Initialise sensor with given parameters / settings
 *   @param addr the I2C address the device can be found on
 *   @param theWire the I2C object to use, defaults to &Wire
 *   @returns true on success, false otherwise
 */
bool ZUNO_BMP280::begin(uint8_t addr, TwoWire *theWire, uint8_t scl, uint8_t sda) {
	this->_wire = theWire;
	this->_wire_addr = addr;
	if (theWire->begin(0x0, scl, sda) != ZunoErrorOk)
		return (false);
	return (this->init());
}

bool ZUNO_BMP280::begin(SPIClass *spi, uint8_t sck, uint8_t miso, uint8_t mosi, uint8_t ss) {
	this->_spi = spi;
	this->_wire_addr = 0x0;
	if (spi->begin(sck, miso, mosi, ss) != ZunoErrorOk)
		return (false);
	return (this->init());
}

/*!
 *   @brief  Initialise sensor with given parameters / settings
 *   @returns true on success, false otherwise
 */
bool ZUNO_BMP280::init() {
	size_t					sensorID;

	sensorID = this->read8(BME280_REGISTER_CHIPID);
	this->_sensorID = sensorID;
	// check if sensor, i.e. the chip ID is correct
	if (sensorID != CHIPID_BMP280_1 && sensorID != CHIPID_BMP280_2 && sensorID != CHIPID_BMP280_3 && sensorID != CHIPID_BME280)
		return (false);
	if (sensorID == CHIPID_BME280)
	{
		// reset the device using soft-reset
		// this makes sure the IIR is off, etc.
		this->write8(BME280_REGISTER_SOFTRESET, 0xB6);
		// wait for chip to wake up.
		delay(10);
		// if chip is still reading calibration, delay
		while (isReadingCalibration())
			delay(10);
	}

	this->readCoefficients(); // read trimming parameters, see DS 4.2.2
	// write8(BMP280_REGISTER_CONTROL, 0x3F); /* needed? */
	this->setSampling(); // use defaults
	delay(100);
	return (true);
}

/*!
 *   @brief  setup sensor with given parameters / settings
 *
 *   This is simply a overload to the normal begin()-function, so SPI users
 *   don't get confused about the library requiring an address.
 *   @param mode the power mode to use for the sensor
 *   @param tempSampling the temp samping rate to use
 *   @param pressSampling the pressure sampling rate to use
 *   @param humSampling the humidity sampling rate to use
 *   @param filter the filter mode to use
 *   @param duration the standby duration to use
 */
void ZUNO_BMP280::setSampling(sensor_mode mode,
                                  sensor_sampling tempSampling,
                                  sensor_sampling pressSampling,
                                  sensor_sampling humSampling,
                                  sensor_filter filter,
                                  standby_duration duration) {
	/**************************************************************************/
	/*!
		@brief  config register
	*/
	/**************************************************************************/
	struct config {
		// inactive duration (standby time) in normal mode
		// 000 = 0.5 ms
		// 001 = 62.5 ms
		// 010 = 125 ms
		// 011 = 250 ms
		// 100 = 500 ms
		// 101 = 1000 ms
		// 110 = 10 ms
		// 111 = 20 ms
		unsigned int t_sb : 3; ///< inactive duration (standby time) in normal mode

		// filter settings
		// 000 = filter off
		// 001 = 2x filter
		// 010 = 4x filter
		// 011 = 8x filter
		// 100 and above = 16x filter
		unsigned int filter : 3; ///< filter settings

		// unused - don't set
		unsigned int none : 1;     ///< unused - don't set
		unsigned int spi3w_en : 1; ///< unused - don't set

		/// @return combined config register
		unsigned int get() { return (t_sb << 5) | (filter << 2) | spi3w_en; }
	};
	config				configReg; //!< config register object

	/**************************************************************************/
	/*!
		@brief  ctrl_hum register
	*/
	/**************************************************************************/
	struct ctrl_hum {
		/// unused - don't set
		unsigned int none : 5;

		// pressure oversampling
		// 000 = skipped
		// 001 = x1
		// 010 = x2
		// 011 = x4
		// 100 = x8
		// 101 and above = x16
		unsigned int osrs_h : 3; ///< pressure oversampling

		/// @return combined ctrl hum register
		unsigned int get() { return (osrs_h); }
	};
	ctrl_hum				humReg; //!< hum register object

	this->_measReg.mode = mode;
	this->_measReg.osrs_t = tempSampling;
	this->_measReg.osrs_p = pressSampling;

	configReg.filter = filter;
	configReg.t_sb = duration;
	configReg.spi3w_en = 0;

	if (this->_sensorID == CHIPID_BME280)
	{
		// making sure sensor is in sleep mode before setting configuration
		// as it otherwise may be ignored
		this->write8(BME280_REGISTER_CONTROL, MODE_SLEEP);

		// you must make sure to also set REGISTER_CONTROL after setting the
		// CONTROLHUMID register, otherwise the values won't be applied (see
		// DS 5.4.3)
		humReg.osrs_h = humSampling;
		this->write8(BME280_REGISTER_CONTROLHUMID, humReg.get());
	}
	this->write8(BME280_REGISTER_CONFIG, configReg.get());
	this->write8(BME280_REGISTER_CONTROL, this->_measReg.get());
}

/*!
 *   @brief  Writes an 8 bit value over I2C or SPI
 *   @param reg the register address to write to
 *   @param value the value to write to the register
 */
void ZUNO_BMP280::write8(byte reg, byte value) {
  byte buffer[2];
  buffer[1] = value;
  if (this->_wire_addr != 0x0) {
    buffer[0] = reg;
    this->_wire->transfer(this->_wire_addr, &buffer[0x0], 0x2);
  } else {
    buffer[0] = reg & ~0x80;
    // spi_dev->write(buffer, 2);
  }
}

/*!
 *   @brief  Reads an 8 bit value over I2C or SPI
 *   @param reg the register address to read from
 *   @returns the data byte read from the device
 */
uint8_t ZUNO_BMP280::read8(byte reg) {
  uint8_t buffer[1];
  if (this->_wire_addr != 0x0) {
    buffer[0] = uint8_t(reg);
    // i2c_dev->write_then_read(buffer, 1, buffer, 1);
  } else {
    buffer[0] = uint8_t(reg | 0x80);
    // spi_dev->write_then_read(buffer, 1, buffer, 1);
  }
  this->_read(buffer, 1, buffer, 1);
  return buffer[0];
}

/*!
 *   @brief  Reads a 16 bit value over I2C or SPI
 *   @param reg the register address to read from
 *   @returns the 16 bit data value read from the device
 */
uint16_t ZUNO_BMP280::read16(byte reg) {
  uint8_t buffer[2];

  if (this->_wire_addr != 0x0) {
    buffer[0] = uint8_t(reg);
    // i2c_dev->write_then_read(buffer, 1, buffer, 2);
  } else {
    buffer[0] = uint8_t(reg | 0x80);
    // spi_dev->write_then_read(buffer, 1, buffer, 2);
  }
  this->_read(buffer, 1, buffer, 2);
  return uint16_t(buffer[0]) << 8 | uint16_t(buffer[1]);
}

/*!
 *   @brief  Reads a signed 16 bit little endian value over I2C or SPI
 *   @param reg the register address to read from
 *   @returns the 16 bit data value read from the device
 */
uint16_t ZUNO_BMP280::read16_LE(byte reg) {
  uint16_t temp = read16(reg);
  return (temp >> 8) | (temp << 8);
}

/*!
 *   @brief  Reads a signed 16 bit value over I2C or SPI
 *   @param reg the register address to read from
 *   @returns the 16 bit data value read from the device
 */
int16_t ZUNO_BMP280::readS16(byte reg) { return (int16_t)read16(reg); }

/*!
 *   @brief  Reads a signed little endian 16 bit value over I2C or SPI
 *   @param reg the register address to read from
 *   @returns the 16 bit data value read from the device
 */
int16_t ZUNO_BMP280::readS16_LE(byte reg) {
  return (int16_t)read16_LE(reg);
}

/*!
 *   @brief  Reads a 24 bit value over I2C
 *   @param reg the register address to read from
 *   @returns the 24 bit data value read from the device
 */
uint32_t ZUNO_BMP280::read24(byte reg) {
  uint8_t buffer[3];

  if (this->_wire_addr != 0x0) {
    buffer[0] = uint8_t(reg);
    // i2c_dev->write_then_read(buffer, 1, buffer, 3);
  } else {
    buffer[0] = uint8_t(reg | 0x80);
    // spi_dev->write_then_read(buffer, 1, buffer, 3);
  }
  this->_read(buffer, 1, buffer, 3);
  return uint32_t(buffer[0]) << 16 | uint32_t(buffer[1]) << 8 |
         uint32_t(buffer[2]);
}

/*!
 *  @brief  Take a new measurement (only possible in forced mode)
    @returns true in case of success else false
 */
bool ZUNO_BMP280::takeForcedMeasurement(void) {
  bool return_value = false;
  // If we are in forced mode, the BME sensor goes back to sleep after each
  // measurement and we need to set it to forced mode once at this point, so
  // it will take the next measurement and then return to sleep again.
  // In normal mode simply does new measurements periodically.
  if (_measReg.mode == MODE_FORCED) {
    return_value = true;
    // set to forced mode, i.e. "take next measurement"
    write8(BME280_REGISTER_CONTROL, _measReg.get());
    // Store current time to measure the timeout
    uint32_t timeout_start = millis();
    // wait until measurement has been completed, otherwise we would read the
    // the values from the last measurement or the timeout occurred after 2 sec.
    while (read8(BME280_REGISTER_STATUS) & 0x08) {
      // In case of a timeout, stop the while loop
      if ((millis() - timeout_start) > 2000) {
        return_value = false;
        break;
      }
      delay(1);
    }
  }
  return return_value;
}

/*!
 *   @brief  Reads the factory-set coefficients
 */
void ZUNO_BMP280::readCoefficients(void) {
	_bme280_calib.dig_T1 = read16_LE(BME280_REGISTER_DIG_T1);
	_bme280_calib.dig_T2 = readS16_LE(BME280_REGISTER_DIG_T2);
	_bme280_calib.dig_T3 = readS16_LE(BME280_REGISTER_DIG_T3);

	_bme280_calib.dig_P1 = read16_LE(BME280_REGISTER_DIG_P1);
	_bme280_calib.dig_P2 = readS16_LE(BME280_REGISTER_DIG_P2);
	_bme280_calib.dig_P3 = readS16_LE(BME280_REGISTER_DIG_P3);
	_bme280_calib.dig_P4 = readS16_LE(BME280_REGISTER_DIG_P4);
	_bme280_calib.dig_P5 = readS16_LE(BME280_REGISTER_DIG_P5);
	_bme280_calib.dig_P6 = readS16_LE(BME280_REGISTER_DIG_P6);
	_bme280_calib.dig_P7 = readS16_LE(BME280_REGISTER_DIG_P7);
	_bme280_calib.dig_P8 = readS16_LE(BME280_REGISTER_DIG_P8);
	_bme280_calib.dig_P9 = readS16_LE(BME280_REGISTER_DIG_P9);

	if (this->_sensorID == CHIPID_BME280)
	{
		_bme280_calib.dig_H1 = read8(BME280_REGISTER_DIG_H1);
		_bme280_calib.dig_H2 = readS16_LE(BME280_REGISTER_DIG_H2);
		_bme280_calib.dig_H3 = read8(BME280_REGISTER_DIG_H3);
		_bme280_calib.dig_H4 = ((int8_t)read8(BME280_REGISTER_DIG_H4) << 4) |
								(read8(BME280_REGISTER_DIG_H4 + 1) & 0xF);
		_bme280_calib.dig_H5 = ((int8_t)read8(BME280_REGISTER_DIG_H5 + 1) << 4) |
								(read8(BME280_REGISTER_DIG_H5) >> 4);
		_bme280_calib.dig_H6 = (int8_t)read8(BME280_REGISTER_DIG_H6);
	}
}

/*!
 *   @brief return true if chip is busy reading cal data
 *   @returns true if reading calibration, false otherwise
 */
bool ZUNO_BMP280::isReadingCalibration(void) {
  uint8_t const rStatus = read8(BME280_REGISTER_STATUS);

  return (rStatus & (1 << 0)) != 0;
}

int16_t ZUNO_BMP280::readTemperatureC100(void) {
  int32_t var1, var2;

  int32_t adc_T = read24(BME280_REGISTER_TEMPDATA);
  if (adc_T == 0x800000) // value in case temp measurement was disabled
    return -1;
  adc_T >>= 4;

  var1 = (int32_t)((adc_T / 8) - ((int32_t)_bme280_calib.dig_T1 * 2));
  var1 = (var1 * ((int32_t)_bme280_calib.dig_T2)) / 2048;
  var2 = (int32_t)((adc_T / 16) - ((int32_t)_bme280_calib.dig_T1));
  var2 = (((var2 * var2) / 4096) * ((int32_t)_bme280_calib.dig_T3)) / 16384;

  t_fine = var1 + var2 + t_fine_adjust;

  int32_t T = (t_fine * 5 + 128) / 256;

  return T;
}

/*!
 *   @brief  Returns the temperature from the sensor
 *   @returns the temperature read from the device
 */
float ZUNO_BMP280::readTemperature(void) {
	int16_t			t;

	t = this->readTemperatureC100();
	if (t == -1)
		return (NAN);
	return (float)(t / 100.0f);
}

int32_t ZUNO_BMP280::_readPressurePa(void) {
  int64_t var1, var2, var3, var4;

  readTemperatureC100(); // must be done first to get t_fine

  int32_t adc_P = read24(BME280_REGISTER_PRESSUREDATA);
  if (adc_P == 0x800000) // value in case pressure measurement was disabled
    return -1;
  adc_P >>= 4;

  var1 = ((int64_t)t_fine) - 128000;
  var2 = var1 * var1 * (int64_t)_bme280_calib.dig_P6;
  var2 = var2 + ((var1 * (int64_t)_bme280_calib.dig_P5) * 131072);
  var2 = var2 + (((int64_t)_bme280_calib.dig_P4) * 34359738368);
  var1 = ((var1 * var1 * (int64_t)_bme280_calib.dig_P3) / 256) +
         ((var1 * ((int64_t)_bme280_calib.dig_P2) * 4096));
  var3 = ((int64_t)1) * 140737488355328;
  var1 = (var3 + var1) * ((int64_t)_bme280_calib.dig_P1) / 8589934592;

  if (var1 == 0) {
    return 0; // avoid exception caused by division by zero
  }

  var4 = 1048576 - adc_P;
  var4 = (((var4 * 2147483648) - var2) * 3125) / var1;
  var1 = (((int64_t)_bme280_calib.dig_P9) * (var4 / 8192) * (var4 / 8192)) /
         33554432;
  var2 = (((int64_t)_bme280_calib.dig_P8) * var4) / 524288;
  var4 = ((var4 + var1 + var2) / 256) + (((int64_t)_bme280_calib.dig_P7) * 16);

  return var4;
}

int32_t ZUNO_BMP280::readPressurePa(void) {
  int32_t  var4;

  var4 = this->_readPressurePa();
  if (var4 == -1)
    return (-1);
  return var4 / 256;
}

float ZUNO_BMP280::readPressureHgMM(void) {
  int32_t  var4;

  var4 = this->_readPressurePa();
  if (var4 == -1)
    return (-1);
  return (var4 / 256 / 133.322f);
}

int32_t ZUNO_BMP280::readPressureHgMM10(void) {
  int32_t  var4;

  var4 = this->_readPressurePa();
  if (var4 == -1)
    return (-1);
  return (var4 / 256 * 1000 / 13333);
}

/*!
 *   @brief  Returns the pressure from the sensor
 *   @returns the pressure value (in Pascal) read from the device
 */
float ZUNO_BMP280::readPressure(void) {
  int32_t  var4;

  var4 = this->_readPressurePa();
  if (var4 == -1)
    return (NAN);
  float P = var4 / 256.0f;
  return P;
}

int32_t ZUNO_BMP280::_readHumidity(void) {
  int32_t var1, var2, var3, var4, var5;

	if (this->_sensorID != CHIPID_BME280)
		return (-1);

  readTemperatureC100(); // must be done first to get t_fine

  int32_t adc_H = read16(BME280_REGISTER_HUMIDDATA);
  if (adc_H == 0x8000) // value in case humidity measurement was disabled
    return -1;

  var1 = t_fine - ((int32_t)76800);
  var2 = (int32_t)(adc_H * 16384);
  var3 = (int32_t)(((int32_t)_bme280_calib.dig_H4) * 1048576);
  var4 = ((int32_t)_bme280_calib.dig_H5) * var1;
  var5 = (((var2 - var3) - var4) + (int32_t)16384) / 32768;
  var2 = (var1 * ((int32_t)_bme280_calib.dig_H6)) / 1024;
  var3 = (var1 * ((int32_t)_bme280_calib.dig_H3)) / 2048;
  var4 = ((var2 * (var3 + (int32_t)32768)) / 1024) + (int32_t)2097152;
  var2 = ((var4 * ((int32_t)_bme280_calib.dig_H2)) + 8192) / 16384;
  var3 = var5 * var2;
  var4 = ((var3 / 32768) * (var3 / 32768)) / 128;
  var5 = var3 - ((var4 * ((int32_t)_bme280_calib.dig_H1)) / 16);
  var5 = (var5 < 0 ? 0 : var5);
  var5 = (var5 > 419430400 ? 419430400 : var5);
  return (var5 / 4096);
}

int16_t ZUNO_BMP280::readHumidityH10(void) {
  int32_t H;

  H = this->_readHumidity();
  if (H == -1)
    return (-1);
  return ((H * 10) >> 10);
}

/*!
 *  @brief  Returns the humidity from the sensor
 *  @returns the humidity value read from the device
 */
float ZUNO_BMP280::readHumidity(void) {
  int32_t H;

  H = this->_readHumidity();
  if (H == -1)
    return (NAN);
  return (float)H / 1024.0;
}

/*!
 *   Calculates the altitude (in meters) from the specified atmospheric
 *   pressure (in hPa), and sea-level pressure (in hPa).
 *   @param  seaLevel      Sea-level pressure in hPa
 *   @returns the altitude value read from the device
 */
float ZUNO_BMP280::readAltitude(float seaLevel) {
  // Equation taken from BMP180 datasheet (page 16):
  //  http://www.adafruit.com/datasheets/BST-BMP180-DS000-09.pdf

  // Note that using the equation from wikipedia can give bad results
  // at high altitude. See this thread for more information:
  //  http://forums.adafruit.com/viewtopic.php?f=22&t=58064

  float atmospheric = readPressure() / 100.0F;
  return 44330.0 * (1.0 - pow(atmospheric / seaLevel, 0.1903));
}

/*!
 *   Calculates the pressure at sea level (in hPa) from the specified
 * altitude (in meters), and atmospheric pressure (in hPa).
 *   @param  altitude      Altitude in meters
 *   @param  atmospheric   Atmospheric pressure in hPa
 *   @returns the pressure at sea level (in hPa) from the specified altitude
 */
float ZUNO_BMP280::seaLevelForAltitude(float altitude, float atmospheric) {
  // Equation taken from BMP180 datasheet (page 17):
  //  http://www.adafruit.com/datasheets/BST-BMP180-DS000-09.pdf

  // Note that using the equation from wikipedia can give bad results
  // at high altitude. See this thread for more information:
  //  http://forums.adafruit.com/viewtopic.php?f=22&t=58064

  return atmospheric / pow(1.0 - (altitude / 44330.0), 5.255);
}

/*!
 *   Returns Sensor ID found by init() for diagnostics
 *   @returns Sensor ID 0x60 for BME280, 0x56, 0x57, 0x58 BMP280
 */
uint32_t ZUNO_BMP280::sensorID(void) { return _sensorID; }

/*!
 *   Returns the current temperature compensation value in degrees Celcius
 *   @returns the current temperature compensation value in degrees Celcius
 */
float ZUNO_BMP280::getTemperatureCompensation(void) {
  return float((t_fine_adjust * 5) >> 8) / 100.0;
};

/*!
 *  Sets a value to be added to each temperature reading. This adjusted
 *  temperature is used in pressure and humidity readings.
 *  @param  adjustment  Value to be added to each tempature reading in Celcius
 */
void ZUNO_BMP280::setTemperatureCompensation(float adjustment) {
  // convert the value in C into and adjustment to t_fine
  t_fine_adjust = ((int32_t(adjustment * 100) << 8)) / 5;
};


void ZUNO_BMP280::_read(uint8_t *in, size_t in_count, uint8_t *out, size_t out_count) {
	SPIClass						*spi;
	TwoWire							*wire;

	if (this->_wire_addr != 0x0) {
		wire = this->_wire;
		wire->transfer(this->_wire_addr, in, in_count);
		wire->requestFrom(this->_wire_addr, out_count);// send data n-bytes read
		while (out_count-- != 0x0)
			out++[0x0] = wire->read();
		return ;
	}
	spi = this->_spi;
	spi->beginTransaction();
	out_count = out_count - in_count;
	while (in_count-- != 0x0)
		out++[0x0] = spi->transfer(in++[0x0]);
	while (out_count-- != 0x0)
		out++[0x0] = spi->transfer(0xFF);
	spi->endTransaction();
}