#include "ZWCCManufacturerSpecific.h"
#include <em_system.h>

#ifndef DEVICE_MANUFACTURER_ID
#define DEVICE_MANUFACTURER_ID g_zuno_sys->fw_static_header->vendor_id
#endif
#ifndef DEVICE_PRODUCT_TYPE_ID
#define DEVICE_PRODUCT_TYPE_ID g_zuno_sys->fw_static_header->product_type_id
#endif
#define DEVICE_UID_LEN 8

int zuno_CCManufacturerSpecificHandler(ZUNOCommandPacket_t *cmd, 
                            ZUNOCommandPacketReport_t *frame_report) {

    
    // "Report the way you was asked" approach is absolutely legal fo this CC
    uint8_t rx_s2level = cmd->zw_rx_secure_opts;
    frame_report->packet.zw_rx_secure_opts = rx_s2level;

	switch(ZW_CMD){
        case MANUFACTURER_SPECIFIC_GET:
            frame_report->packet.cmd[2] = (uint8_t)(DEVICE_MANUFACTURER_ID >> 8);
            frame_report->packet.cmd[3] = (uint8_t)(DEVICE_MANUFACTURER_ID &  0xFF);
            frame_report->packet.cmd[4] = (uint8_t)(DEVICE_PRODUCT_TYPE_ID  >> 8);
            frame_report->packet.cmd[5] = (uint8_t)(DEVICE_PRODUCT_TYPE_ID  &  0xFF);
            frame_report->packet.cmd[6] = (uint8_t)(g_zuno_sys->zw_protocol_data->product_id  >> 8);
            frame_report->packet.cmd[7] = (uint8_t)(g_zuno_sys->zw_protocol_data->product_id   &  0xFF);
            frame_report->packet.len = 8; 
            zunoSendZWPackage(&frame_report->packet);
            return ZUNO_COMMAND_PROCESSED;
        case DEVICE_SPECIFIC_GET:
            {
                uint64_t myid = SYSTEM_GetUnique();
                frame_report->packet.cmd[2] = (uint8_t)(DEVICE_ID_TYPE_SERIAL_NUMBER & 0x07);
                frame_report->packet.cmd[3] = (uint8_t)(((DEVICE_ID_FORMAT_BINARY << 0x05) & 0xE0) | DEVICE_UID_LEN);
                memcpy(frame_report->packet.cmd+4, &myid, DEVICE_UID_LEN);
                frame_report->packet.len = 4 + DEVICE_UID_LEN;  
            }
            zunoSendZWPackage(&frame_report->packet);
            return ZUNO_COMMAND_PROCESSED;
        default:
			return ZUNO_UNKNOWN_CMD;
    }
    return ZUNO_UNKNOWN_CMD;
}