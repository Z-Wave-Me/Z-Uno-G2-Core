#ifndef DALLAS_DS_18B20LIB
#define DALLAS_DS_18B20LIB

#include "Arduino.h"
#include "ZUNO_OneWire.h"

#define BAD_TEMP -32767

enum
{
	DS18B20_RESOLUTION_9BIT = 0,
	DS18B20_RESOLUTION_10BIT,
	DS18B20_RESOLUTION_11BIT,
	DS18B20_RESOLUTION_12BIT	


};
class DS18B20Sensor
{
	public:
		DS18B20Sensor(OneWire * ow);

		// Search for all DS18B20 sensors connected to 1Wire bus. 
		// Copies found sensor's addresses (ROM) to buffer
		// one by one
		// Returns:
		//  number of found sensors
		byte								findAllSensors(byte *rom, byte max_sensors);
		inline byte							findAllSensors(byte *rom) { return (this->findAllSensors(rom, 128));};
		
		// Search for alone sensor. 
		// Copies found sensor's address (ROM) to buffer
		// Works faster for 1 sensor cases
		// Returns:
		//   1 if we have a valid sensor connected
		//   0 otherwise    
		byte scanAloneSensor(byte * rom);

		void								setResolution(byte res, byte *addr);
		inline void							setResolution(byte res) {this->setResolution(res, NULL);};

		inline byte							getResolution(){return (this->_current_resolution);};
		
		// Return temperarure in cents of Celsius
		// sonsume less memory of sketch than getTemperature()
		int									getTempC100(byte * addr = NULL);
		inline int							getTempC100(void) {return (this->getTempC100(NULL));};

		// Returns temperature as float in Celsius
		float								getTemperature(byte * addr);
		inline float						getTemperature(void) {return (this->getTemperature(NULL));};

	private:
		OneWire								*my_ow;
		byte								_current_resolution;
		byte								_current_delay;

};

#endif // DALLAS_DS_18B20LIB
