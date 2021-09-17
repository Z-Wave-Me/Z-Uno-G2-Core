#include "Arduino.h"
#include "SPI.h"
#include "ZUNO_ST77XX.h"
#include "ZUNO_LOGO.h"
#include "voc_img.h"
#include "co2_img.h"
#include "F77_Minecraft8x10.h"
#include "F77_Minecraft12x14.h"
#include "ZUNO_SGP30.h"

// ZUNO_ST7735_128_160 lcd_tft(20, 21, 22);
ZUNO_ST7735_80_160 lcd_tft(20, 21, 22);
ZUNO_SGP30 sgp;

/* return absolute humidity [mg/m^3] with approximation formula
* @param temperature [°C]
* @param humidity [%RH]
*/
uint32_t getAbsoluteHumidity(float temperature, float humidity) {
	// approximation formula from Sensirion SGP30 Driver Integration chapter 3.15
	const float absoluteHumidity = 216.7f * ((humidity / 100.0f) * 6.112f * exp((17.62f * temperature) / (243.12f + temperature)) / (273.15f + temperature)); // [g/m^3]
	const uint32_t absoluteHumidityScaled = static_cast<uint32_t>(1000.0f * absoluteHumidity); // [mg/m^3]
	return absoluteHumidityScaled;
}

void setup()
{
	Serial.begin();
	lcd_tft.begin();
	lcd_tft.drawImage_1bpp(0,0, (uint8_t*)zuno_logo, 0x79f, BLACK);
	lcd_tft.drawImage(35,5, (uint16_t*)voc_img,0);
	lcd_tft.drawImage(31,54, (uint16_t*)co2_img,0);

	lcd_tft.setFont((uint8_t*)fontF77_Minecraft8x10);
	lcd_tft.setCursor(139,17);
	lcd_tft.print("ppb");
	lcd_tft.setCursor(139,66);
	lcd_tft.print("ppm");
	if (!sgp.begin()){
		Serial.println("Sensor not found :(");
		while (1);
		Serial.print("Found SGP30 serial #");
		Serial.print(sgp.serialnumber[0], HEX);
		Serial.print(sgp.serialnumber[1], HEX);
		Serial.println(sgp.serialnumber[2], HEX);
	}
	lcd_tft.setFont((uint8_t*)fontF77_Minecraft12x14);
}


int counter = 0;
uint last_tvoc = -1, last_eco2 = -1;
void loop()
{
	// If you have a temperature / humidity sensor, you can set the absolute humidity to enable the humditiy compensation for the air quality signals
	//float temperature = 22.1; // [°C]
	//float humidity = 45.2; // [%RH]
	//sgp.setHumidity(getAbsoluteHumidity(temperature, humidity));

	int tvoc = sgp.TVOC, eco2 = sgp.eCO2;

	if (!sgp.IAQmeasure()) {
		lcd_tft.setFontColor(RED);
	}
	else
		lcd_tft.setFontColor(WHITE);

	Serial.print("TVOC "); Serial.print(tvoc); Serial.print(" ppb\t");
	Serial.print("eCO2 "); Serial.print(eco2); Serial.println(" ppm\t");

	if (last_tvoc != tvoc)
	{
		lcd_tft.setCursor(67,13);
		lcd_tft.fillRect(67,13,139-67,14,BLACK);
		lcd_tft.print(tvoc);
		last_tvoc = tvoc;
	}
	if (last_eco2 != eco2)
	{
		lcd_tft.setCursor(67,63);
		lcd_tft.fillRect(67,63,139-67,14,BLACK);
		lcd_tft.print(eco2);
		last_eco2 = eco2;
	}

	if (! sgp.IAQmeasureRaw()) {
		Serial.println("\nRaw Measurement failed");
		return;
	}
	Serial.print("Raw H2 "); Serial.print(sgp.rawH2); Serial.print(" \t");
	Serial.print("Raw Ethanol "); Serial.print(sgp.rawEthanol); Serial.println("");

	delay(1000);

	counter++;
	if (counter == 30) {
		counter = 0;

		uint16_t TVOC_base, eCO2_base;
		if (! sgp.getIAQBaseline(&eCO2_base, &TVOC_base)) {
			Serial.println("Failed to get baseline readings");
			return;
		}
		Serial.print("****Baseline values: eCO2: 0x"); Serial.print(eCO2_base, HEX);
		Serial.print(" & TVOC: 0x"); Serial.println(TVOC_base, HEX);
	}
}