#include "ZWCCResetLocally.h"
#include "SysService.h"
#include "ZWSupport.h"
#include "CommandQueue.h"
#include "Debug.h"



typedef struct RSTLocallyData_s{
    bool started;
    uint32_t timeout;
}RSTLocallyData_t;
RSTLocallyData_t g_rst_locally_data = {false, 0};


void zunoResetLocally(){
    #ifdef LOGGING_DBG
    LOGGING_UART.println("*** ZUNO RST LOCALLY USR CALL");
    #endif
    ZUNOCommandPacketReport_t			frame;
    fillOutgoingRawPacket(&frame.info, frame.data, 0, ZUNO_PACKETFLAGS_GROUP | RST_LOCALLY_QUEUE_CHANNEL, ZUNO_LIFELINE_GRP);
	frame.info.packet.cmd[0] = COMMAND_CLASS_DEVICE_RESET_LOCALLY;
    frame.info.packet.cmd[1] = DEVICE_RESET_LOCALLY_NOTIFICATION;
    frame.info.packet.len = 2;
	zunoSendZWPackage(&frame.info);
    g_rst_locally_data.started = true;
    g_rst_locally_data.timeout = millis() + RST_LOCALLY_TIMEOUT;
    #ifndef NO_SYS_SVC
    SysSetLearnLedMode(SYSLED_LEARN_MODE_WAITING_RST, RST_LOCALLY_TIMEOUT);
    #endif
}
void RSTLocallyTick(){
    if(g_rst_locally_data.started){
        // The package is in queue yet
        if(ZWQFindPackage(0xFF, 0xFF, COMMAND_CLASS_DEVICE_RESET_LOCALLY, DEVICE_RESET_LOCALLY_NOTIFICATION) != NULL)
            return;
        // Check if the package was processed by ZW Stack
        if(zunoCheckSystemQueueStatus(RST_LOCALLY_QUEUE_CHANNEL))
            return;
        #ifdef LOGGING_DBG
        LOGGING_UART.println("*** ZUNO RST LOCALLY: FLUSH SYS. MEM");
        #endif
        // Call OS to reset all SDK memory
        zunoSysCall(ZUNO_SYSFUNC_SETDEFAULT, 1, 0);
        g_rst_locally_data.started = false;
    }
}