#include "Custom_timestamp.h"

#define MY_SERIAL Serial

void setup() {
	if (zunoIsValidDate() == false)
		zunoSetTimeStamp(ZUNO_SKETCH_BUILD_TS + 1 + (3 * 60 * 60));//+ (3 * 60 * 60) sec - Mck; + 1 sec  - build and load
	MY_SERIAL.begin(112500);
}

static const  char *monthNames[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

static const char *dayNames[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};


void loop() {
	struct tm								timeinfo;
	time_t									time;

	time = zunoGetTimeStamp();
	gmtime_r(&time, &timeinfo);
	MY_SERIAL.print(timeinfo.tm_mday);
	MY_SERIAL.print(" ");
	MY_SERIAL.print(monthNames[timeinfo.tm_mon]);
	MY_SERIAL.print(" ");
	MY_SERIAL.print(timeinfo.tm_year + 1900);
	MY_SERIAL.print(" year ");
	MY_SERIAL.print(timeinfo.tm_hour);
	MY_SERIAL.print(" hour ");
	MY_SERIAL.print(timeinfo.tm_min);
	MY_SERIAL.print(" minuts ");
	MY_SERIAL.print(timeinfo.tm_sec);
	MY_SERIAL.print(" seconds - ");
	MY_SERIAL.print(dayNames[timeinfo.tm_wday]);
	MY_SERIAL.println();
	delay(2000);
}