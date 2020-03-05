#ifndef __ZUNO_SYS_TYPES__
#define __ZUNO_SYS_TYPES__

// Sketch setup
typedef struct ZUNOChannel_s {
    uint8_t type;
    uint8_t sub_type;
    uint8_t params[MAX_CHANNEL_PARAMS];
    uint8_t zw_channel;
} ZUNOChannel_t;
typedef struct ZUNOAssociation_s {
    uint8_t type;
} ZUNOAssociation_t;
typedef struct ZUNODeviceConfiguation_s {
    uint32_t            flags;
    ZUNOChannel_t       channels[ZUNO_MAX_MULTI_CHANNEL_NUMBER];
    uint8_t             num_channels;
    ZUNOAssociation_t   associations[ZUNO_MAX_ASSOC_NUMBER];
    uint8_t             num_associations;
    uint16_t            app_version;
    uint16_t            product_id;
    uint8_t             security_keys;
}ZUNODeviceConfiguation_t;

// Handlers
typedef struct ZUNOCommandPacket_s{
    uint8_t * cmd;
    uint8_t   len;
    uint8_t   zw_channel;
    uint8_t   src_node;
    uint8_t   result;
}ZUNOCommandPacket_t;

// Hardware
typedef struct ZUNOUARTOptions_s{
    uint32_t baudrate;
    uint8_t rx_pin;
    uint8_t tx_pin;
}ZUNOUARTOptions_t;

#endif // __ZUNO_SYS_TYPES__