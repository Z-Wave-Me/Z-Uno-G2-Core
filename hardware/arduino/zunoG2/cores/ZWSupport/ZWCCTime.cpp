#include "Arduino.h"
#include "ZWSupport.h"
#include "ZWCCTime.h"

#ifdef WITH_CC_TIME

int zuno_CCTimeHandler(ZUNOCommandPacket_t *cmd) {
	int								rs;

	switch (ZW_CMD) {
		default:
			rs = ZUNO_UNKNOWN_CMD;
			break ;
	}
	return (rs);
	(void)cmd;
}

#endif//WITH_CC_TIME