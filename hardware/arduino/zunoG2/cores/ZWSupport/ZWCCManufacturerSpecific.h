#ifndef MANUFACTURER_SPECIFIC_CC_H
#define MANUFACTURER_SPECIFIC_CC_H

#include "Arduino.h"
#include "ZWSupport.h"

/* Version command class commands */
#define MANUFACTURER_SPECIFIC_GET                                                    0x04
#define MANUFACTURER_SPECIFIC_REPORT                                                 0x05
#define DEVICE_SPECIFIC_GET                                                          0x06
#define DEVICE_SPECIFIC_REPORT                                                       0x07
typedef enum {
  DEVICE_ID_TYPE_OEM,
  DEVICE_ID_TYPE_SERIAL_NUMBER,
  DEVICE_ID_TYPE_PSEUDO_RANDOM,
  NUMBER_OF_DEVICE_ID_TYPES
}device_id_type_t;
typedef enum {
  DEVICE_ID_FORMAT_UTF_8,
  DEVICE_ID_FORMAT_BINARY,
  NUMBER_OF_DEVICE_ID_FORMATS
}device_id_format_t;
int zuno_CCManufacturerSpecificHandler(ZUNOCommandPacket_t *cmd, 
                            ZUNOCommandPacketReport_t *frame_report);

#endif // MANUFACTURER_SPECIFIC_CC_H