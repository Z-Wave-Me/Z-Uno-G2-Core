#include "Arduino.h"
#include "ZWCCWindowCovering.h"
#include "ZWCCSwitchMultilevel.h"
#include "ZWCCSuperVision.h"

int zuno_CCWindowCoveringHandler(uint8_t channel, ZUNOCommandPacket_t *cmd, ZUNOCommandPacketReport_t *frame_report) {
	int				rs;

	switch(ZW_CMD) {
		case WINDOW_COVERING_SUPPORTED_GET:
			// break ;
		default:
			rs = ZUNO_COMMAND_BLOCKED_NO_SUPPORT;
			break ;
	}
	return (rs);
	(void)frame_report;
	(void)channel;
}