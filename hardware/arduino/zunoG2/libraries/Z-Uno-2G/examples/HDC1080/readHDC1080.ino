//Example of reading from HDC1080


#include "ZUNO_HDC1080.h"
#include "Wire.h"

ZUNO_HDC1080 tempsensor;

void setup() {
  Serial.begin(9600);  // start serial for output

  tempsensor = ZUNO_HDC1080();
  tempsensor.begin();
  tempsensor.heatUp(20);
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
