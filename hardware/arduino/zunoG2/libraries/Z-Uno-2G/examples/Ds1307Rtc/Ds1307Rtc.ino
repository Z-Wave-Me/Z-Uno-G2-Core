#include "Ds1307Rtc.h"

#define MY_SERIAL							Serial

#define EEPROM_STRING						"D8B2DB76-C6CC-41E6-B7AB-A1F365824ABF"

Ds1307RtcClass rtc = Ds1307RtcClass();

static const  char *monthNames[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

static const char *dayNames[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup(void) {
	char							buffer[sizeof(EEPROM_STRING)];
	uint8_t							bRun;
	uint8_t							bSet;

	MY_SERIAL.begin(115200);
	MY_SERIAL.print("\n");
	MY_SERIAL.println("Ds 1307 Rtc Example");
	if (rtc.begin(11, 12) != true) {
		MY_SERIAL.print("Error: cannot initilzed device\n");
		while (0xFF)
			delay(0x10);
	}
	if (rtc.isRunning() == true) {
		MY_SERIAL.print("The DS1307 is runnig.\n");
		bRun = true;
	}
	else {
		MY_SERIAL.print("The DS1307 is stopped.\n");
		bRun = false;
	}
	if (rtc.read(0x0, &buffer[0x0], sizeof(buffer)) != true) {
		MY_SERIAL.printf("Error: cannot read\n");
		while (0xFF)
			delay(0x10);
	}
	if (strncmp(&buffer[0x0], EEPROM_STRING, sizeof(buffer)) != 0x0) {
		MY_SERIAL.print("The DS1307 is not set.\n");
		bSet = false;
	}
	else {
		MY_SERIAL.print("The DS1307 is set.\n");
		bSet = true;
	}
	if (bRun == false || bSet == false) {
		if (rtc.set(zunoGetTimeStamp()) != true) {
			MY_SERIAL.print("Error: cannot set\n");
			while (0xFF)
				delay(0x10);
		}
		if (bSet == false) {
			if (rtc.write(0x0, EEPROM_STRING, sizeof(EEPROM_STRING)) != true) {
				MY_SERIAL.print("Error: cannot write\n");
				while (0xFF)
					delay(0x10);
			}
		}
	}
}

void loop(void) {
	struct tm								timeinfo;

	if (rtc.get(&timeinfo) != true) {
		MY_SERIAL.print("Error: cannot get\n");
		while (0xFF)
			delay(0x10);
	}
	if ((size_t)timeinfo.tm_mon >= (sizeof(monthNames) / sizeof(monthNames[0x0])) || (size_t)timeinfo.tm_wday >= (sizeof(dayNames) / sizeof(dayNames[0x0]))) {
		MY_SERIAL.print("Error: check your connection...\n");
		while (0xFF)
			delay(0x10);
	}
	MY_SERIAL.print(timeinfo.tm_mday);
	MY_SERIAL.print(" ");
	MY_SERIAL.print(monthNames[timeinfo.tm_mon]);
	MY_SERIAL.print(" ");
	MY_SERIAL.print(timeinfo.tm_year + 1900);
	MY_SERIAL.print(" year ");
	MY_SERIAL.printf("%02d", timeinfo.tm_hour);
	MY_SERIAL.print(" hour ");
	MY_SERIAL.printf("%02d", timeinfo.tm_min);
	MY_SERIAL.print(" minuts ");
	MY_SERIAL.printf("%02d", timeinfo.tm_sec);
	MY_SERIAL.print(" seconds - ");
	MY_SERIAL.print(dayNames[timeinfo.tm_wday]);
	MY_SERIAL.println();
	delay(2000);
}
