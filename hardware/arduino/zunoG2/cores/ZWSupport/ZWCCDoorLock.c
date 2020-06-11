#include "ZWCCDoorLock.h"
#include "./includes/ZWCCDoorLock_private.h"


int zuno_CCDoorLockHandler(uint8_t channel, ZUNOCommandPacket_t *cmd) {
	int				rs;

	rs = ZUNO_UNKNOWN_CMD;
	switch(ZW_CMD)
	{
		// case THERMOSTAT_SETPOINT_SET:
		// 	_set_setpoint(channel, cmd);
		// 	zunoSendReport(channel + 1);
		// 	rs = ZUNO_COMMAND_PROCESSED;
		// 	break ;
		// case THERMOSTAT_SETPOINT_GET:
		// 	rs = _report_setpoint(channel, cmd);
		// 	break ;
		// case THERMOSTAT_SETPOINT_SUPPORTED_GET:
		// 	rs = _supported_report_setpoint(channel);
		// 	break ;
	}
	return (rs);
}

int zuno_CCSDoorLockReport(uint8_t channel, ZUNOCommandPacket_t *cmd) {

	return (ZUNO_COMMAND_PROCESSED);
}