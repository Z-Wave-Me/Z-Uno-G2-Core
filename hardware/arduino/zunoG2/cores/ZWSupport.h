#ifndef ZW_COMMAND_CLASS_SUPPORT
#define ZW_COMMAND_CLASS_SUPPORT
#define MAX_ZW_PACKAGE 56

// DBG
#define LOGGING_DBG           1

#define WITH_CC_SWITCH_BINARY 1

#if LOGGING_DBG
#ifndef LOGGING_UART 
#define LOGGING_UART Serial0
#endif
#endif
// 
enum {
    COMMAND_CLASS_BASIC = 0x20,
    COMMAND_CLASS_SWITCH_BINARY = 0x25,
    COMMAND_CLASS_SWITCH_MULTILEVEL = 0x26,
    COMMAND_CLASS_SENSOR_MULTILEVEL = 0x31,
    COMMAND_CLASS_METER = 0x32,
    COMMAND_CLASS_DOOR_LOCK = 0x62,
    COMMAND_CLASS_NOTIFICATION = 0x71,
    COMMAND_CLASS_BATTERY = 0x80,
};


// SINGLE_GETTER
typedef uint8_t zuno_singlegetter1ub_t(void);
typedef uint16_t zuno_singlegetter2ub_t(void);
typedef uint32_t zuno_singlegetter4ub_t(void);
typedef int8_t  zuno_singlegetter1b_t(void);
typedef int16_t zuno_singlegetter2b_t(void);
typedef int32_t zuno_singlegetter4b_t(void);
// MULTI_GETTER
typedef uint8_t zuno_multigetter1ub_t(uint8_t);
typedef uint16_t zuno_multigetter2ub_t(uint8_t);
typedef uint32_t zuno_multigetter4ub_t(uint8_t);
typedef int8_t  zuno_multigetter1b_t(uint8_t);
typedef int16_t zuno_multigetter2b_t(uint8_t);
typedef int32_t zuno_multigetter4b_t(uint8_t);
// SINGLE_SETTER
typedef void zuno_singlesetter1ub_t(uint8_t);
typedef void zuno_singlesetter2ub_t(uint16_t);
typedef void zuno_singlesetter4ub_t(uint32_t);
typedef void zuno_singlesetter1b_t(int8_t);
typedef void zuno_singlesetter2b_t(int16_t);
typedef void zuno_singlesetter4b_t(int32_t);
// MULTI_SETTER
typedef void zuno_multisetter1ub_t(uint8_t, uint8_t);
typedef void zuno_multisetter2ub_t(uint8_t, uint16_t);
typedef void zuno_multisetter4ub_t(uint8_t, uint32_t);
typedef void zuno_multisetter1b_t(uint8_t, int8_t);
typedef void zuno_multisetter2b_t(uint8_t, int16_t);
typedef void zuno_multisetter4b_t(uint8_t, int32_t);


// Common CC subroutines and data
extern ZUNOCommandPacket_t g_outgoing_packet;
void zuno_universalSetter1P(byte zuno_ch, int32_t value);
int32_t zuno_universalGetter1P(byte zuno_ch);

#define CMD_REPLY_LEN g_outgoing_packet.len 
#define CMD_REPLY_CMD g_outgoing_packet.cmd[1]
#define CMD_REPLY_DATA(N) g_outgoing_packet.cmd[N+2]

#define ZW_CMD_CLASS          (cmd->cmd[0])
#define ZW_CMD                (cmd->cmd[1])
#define ZW_CMD_BPARAM(N)      (cmd->cmd[2+N])

#define ZUNO_CFG_CHANNEL_COUNT  (g_zuno_sys->zwave_cfg->num_channels)
#define ZUNO_CFG_CHANNEL(N)     g_zuno_sys->zwave_cfg->channels[N]
#define ZUNO_CFG_TYPE_COUNT     (g_zuno_sys->zwave_cfg->num_channel_types)
#define ZUNO_CFG_TYPE(N)        g_zuno_sys->zwave_cfg->channel_types[N]
/* Battery command class commands */
#define BATTERY_VERSION                                                                  0x01
#define BATTERY_GET                                                                      0x02
#define BATTERY_REPORT                                                                   0x03




#endif // ZW_COMMAND_CLASS_SUPPORT