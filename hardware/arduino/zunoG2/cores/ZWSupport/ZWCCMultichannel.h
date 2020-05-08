#ifndef MULTICHANNEL_CC_H
#define MULTICHANNEL_CC_H
#include "Arduino.h"


/* Multi Channel command class commands */
#define MULTI_CHANNEL_VERSION                                                          0x03
#define MULTI_CHANNEL_CAPABILITY_GET                                                   0x09
#define MULTI_CHANNEL_CAPABILITY_REPORT                                                0x0A
#define MULTI_CHANNEL_CMD_ENCAP                                                        0x0D
#define MULTI_CHANNEL_END_POINT_FIND                                                   0x0B
#define MULTI_CHANNEL_END_POINT_FIND_REPORT                                            0x0C
#define MULTI_CHANNEL_END_POINT_GET                                                    0x07
#define MULTI_CHANNEL_END_POINT_REPORT                                                 0x08
#define MULTI_INSTANCE_CMD_ENCAP                                                       0x06
#define MULTI_INSTANCE_GET                                                             0x04
#define MULTI_INSTANCE_REPORT                                                          0x05
/* Values used for Multi Channel Capability Get command */
#define MULTI_CHANNEL_CAPABILITY_GET_PROPERTIES1_END_POINT_MASK                        0x7F
#define MULTI_CHANNEL_CAPABILITY_GET_PROPERTIES1_RES_BIT_MASK                          0x80
/* Values used for Multi Channel Capability Report command */
#define MULTI_CHANNEL_CAPABILITY_REPORT_PROPERTIES1_END_POINT_MASK                     0x7F
#define MULTI_CHANNEL_CAPABILITY_REPORT_PROPERTIES1_DYNAMIC_BIT_MASK                   0x80
/* Values used for Multi Channel Cmd Encap command */
#define MULTI_CHANNEL_CMD_ENCAP_PROPERTIES1_SOURCE_END_POINT_MASK                      0x7F
#define MULTI_CHANNEL_CMD_ENCAP_PROPERTIES1_RES_BIT_MASK                               0x80
#define MULTI_CHANNEL_CMD_ENCAP_PROPERTIES2_DESTINATION_END_POINT_MASK                 0x7F
#define MULTI_CHANNEL_CMD_ENCAP_PROPERTIES2_BIT_ADDRESS_BIT_MASK                       0x80
/* Values used for Multi Channel End Point Report command */
#define MULTI_CHANNEL_END_POINT_REPORT_PROPERTIES1_RES_MASK                            0x3F
#define MULTI_CHANNEL_END_POINT_REPORT_PROPERTIES1_IDENTICAL_BIT_MASK                  0x40
#define MULTI_CHANNEL_END_POINT_REPORT_PROPERTIES1_DYNAMIC_BIT_MASK                    0x80
#define MULTI_CHANNEL_END_POINT_REPORT_PROPERTIES2_END_POINTS_MASK                     0x7F
#define MULTI_CHANNEL_END_POINT_REPORT_PROPERTIES2_RES_BIT_MASK                        0x80
/* Values used for Multi Instance Cmd Encap command */
#define MULTI_INSTANCE_CMD_ENCAP_PROPERTIES1_INSTANCE_MASK                             0x7F
#define MULTI_INSTANCE_CMD_ENCAP_PROPERTIES1_RES_BIT_MASK                              0x80
/* Values used for Multi Instance Report command */
#define MULTI_INSTANCE_REPORT_PROPERTIES1_INSTANCES_MASK                               0x7F
#define MULTI_INSTANCE_REPORT_PROPERTIES1_RES_BIT_MASK                                 0x80

int zuno_CCMultichannel(ZUNOCommandPacket_t * cmd);
#endif // MULTICHANNEL_CC_H