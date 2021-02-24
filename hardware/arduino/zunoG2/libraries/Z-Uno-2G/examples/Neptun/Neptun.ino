#include "Arduino.h"
#include "ZUNO_Neptun.h"

#define MY_SERIAL Serial0

NeptunClass gNeptun;

// the setup function runs once, when you press reset or power the board
void setup() {
	NeptunStatusDev_t					status;
	NeptunConfigModule_t				config;
	NeptunConfigLine1And2_t				value1;
	NeptunConfigLine3And4_t				value2;

	MY_SERIAL.begin(115200);
	MY_SERIAL.println("Setup");
	gNeptun.begin();
	gNeptun.setAdress(20);
	status = gNeptun.devGetStatus();
	status.bGrouping = true;
	status.bFloorCleaning = false;
	status.bTapsStatusGroup1 = true;
	status.bTapsStatusGroup2 = true;
	gNeptun.devSetStatus(status);
	value1.bLineControl1 = NeptunSensorsGroopFirst;
	value1.bLineControl2 = NeptunSensorsGroopFirst;
	gNeptun.devSetConfigLine1And2(value1);
	value2.bLineControl3 = NeptunSensorsGroopSecond;
	value2.bLineControl4 = NeptunSensorsGroopSecond;
	gNeptun.devSetConfigLine3And4(value2);
	config = gNeptun.devGetConfigModule();
	if (config.status == ZunoErrorOk)
		MY_SERIAL.printf("adress: %d, baudrate: %d\n", config.adress, gNeptun.convertInBaudrate(config.baudrate));
}

// the loop function runs over and over again forever
void loop() {
	NeptunConfigLine_t			status_line;

	MY_SERIAL.print("Status: ");
	MY_SERIAL.println(gNeptun.devGetStatus().raw, 0x10);
	status_line = gNeptun.devGetStatusLine();
	if (status_line.status != ZunoErrorOk)
		MY_SERIAL.printf("Failed to get sensor status!!\n");
	else {
			if (status_line.bLine1 == true)
				MY_SERIAL.printf("1 line sensors alarm !!\n");
			if (status_line.bLine2 == true)
				MY_SERIAL.printf("2 line sensors alarm !!\n");
			if (status_line.bLine3 == true)
				MY_SERIAL.printf("3 line sensors alarm !!\n");
			if (status_line.bLine4 == true)
				MY_SERIAL.printf("4 line sensors alarm !!\n");
	}
		
	delay(2000);
}

