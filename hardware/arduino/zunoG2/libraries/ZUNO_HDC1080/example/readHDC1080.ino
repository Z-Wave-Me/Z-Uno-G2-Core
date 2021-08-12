//Example of reading from HDC1080

#include "Arduino.h"
#include "ZUNO_HDC1080.h"
#include "Wire.h"

ZUNO_HDC1080 tempsensor;

void setup() {
  Wire.begin();
  Wire.setClock(400000); //set clock speed for I2C bus to maximum allowed for HDC1080
  Serial.begin(9600);  // start serial for output

  tempsensor = ZUNO_HDC1080();
  tempsensor.config();
}

void loop() {

  tempsensor.readTempHumid();
  float temp = tempsensor.getTemp();
  float humid = tempsensor.getRelativeHumidity();

  Serial.print("T=");
  Serial.print(temp);
  Serial.print("C, RH=");
  Serial.print(humid);
  Serial.println("%");
  delay(1000);
}
