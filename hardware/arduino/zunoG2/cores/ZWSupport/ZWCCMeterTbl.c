#include "Arduino.h"
#include "ZWCCMeterTbl.h"

int zuno_CCMeterTblMonitorReport(byte channel) {
	return (ZUNO_COMMAND_ANSWERED);
	(void)channel;
}

int zuno_CCMeterTblMonitorHandler(byte channel, ZUNOCommandPacket_t *cmd) {
	int								rs;

	switch (ZW_CMD) {
		default:
			rs = ZUNO_UNKNOWN_CMD;
			break ;
	}
	return (rs);
	(void)channel;
}