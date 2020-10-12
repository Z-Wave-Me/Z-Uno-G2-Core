#ifndef __ZUNO_SYS_TYPES__
#define __ZUNO_SYS_TYPES__
#include "ZUNO_Definitions.h"
// Sketch setup
typedef struct ZUNOChannel_s {
	uint8_t type;
	uint8_t sub_type;//additional type values SWITCH_COLOR_FLAGS_RED in ZUNO_SWITCH_COLOR
	uint8_t params[MAX_CHANNEL_PARAMS];
	uint8_t zw_channel;
} ZUNOChannel_t;
typedef struct ZUNOCCSVersion_s {
	uint8_t cc;
	uint8_t version;
} ZUNOCCSVersion_t;
typedef struct ZUNOChannelCCS_s {
	uint8_t type;
	uint8_t flags;
	uint8_t num_ccs;
	ZUNOCCSVersion_t ccs[ZUNO_NAX_CCS_FOR_CHANNEL];
} ZUNOChannelCCS_t;
typedef struct ZUNOAssociation_s {
	uint8_t type;
} ZUNOAssociation_t;
typedef struct ZUNODeviceConfiguation_s {
	uint32_t            flags;
	ZUNOChannel_t 		channels[ZUNO_MAX_MULTI_CHANNEL_NUMBER];
	uint8_t 			num_channels;
	ZUNOAssociation_t	associations[ZUNO_MAX_ASSOC_NUMBER];
	uint8_t 			num_associations;
	uint8_t 			num_channel_types;
	ZUNOChannelCCS_t    channel_types[ZUNO_MAX_CCTYPES];
	uint16_t            app_version;
	uint16_t            product_id;
	uint8_t				device_generic_type;
	uint8_t				device_specific_type;
	uint16_t			device_icon;
	uint16_t			device_app_icon;
	uint8_t				security_keys;
	uint16_t            __reserved;
	uint16_t            crc16;
}ZUNODeviceConfiguation_t;
// Z-Wave packet
typedef struct ZUNOCommandPacket_s{
	uint8_t   flags;
	uint8_t * cmd;
	uint8_t   len;
	uint8_t   src_zw_channel;
	uint8_t   dst_zw_channel;
	uint8_t   src_node;
	uint8_t   dst_node;
	uint8_t   zw_rx_opts;
	uint8_t   zw_rx_secure_opts;
}ZUNOCommandPacket_t;
// System variables mapping
typedef struct ZUNOSetupSysState_s {
	uint8_t reset_reason;
	uint8_t enclusion_state;
	uint8_t node_id;
	uint8_t avaliable_keys;
	uint32_t gpio_em4flags;
	uint32_t flags;
	ZUNODeviceConfiguation_t * zwave_cfg;
}ZUNOSetupSysState_t;

// Handlers
typedef struct zuno_handler_single_gettersetter_s{
    void * getter;
    void * setter;
}zuno_handler_single_gettersetter_t;
typedef struct zuno_handler_multi_getter_s{
    void * getter;
    uint8_t offset;
}zuno_handler_multi_getter_t;
typedef struct zuno_handler_multi_gettersetter_s{
    void * getter;
    void * setter;
    uint8_t offset;
}zuno_handler_multi_gettersetter_t;
typedef struct		zuno_handler_single_thermostat_s {
	void			*getter1;
	void			*setter1;
	void			*getter2;
	void			*setter2;
}					zuno_handler_single_thermostat_t;
typedef struct		zuno_handler_multi_thermostat_s {
	void			*getter1;
	void			*setter1;
	void			*getter2;
	void			*setter2;
	uint8_t			offset;
}					zuno_handler_multi_thermostat_t;

typedef struct ZUNOSysEvent_s{
	uint8_t event;
	uint32_t params[2];
}ZUNOSysEvent_t;
typedef struct ZUNOSysDbgMessage_s{
	uint8_t type;
	char *  p_text;
}ZUNOSysDbgMessage_t;
typedef void zuno_void_handler(void);
typedef void zuno_dbgprint_handler(ZUNOSysDbgMessage_t * msg);
typedef void zuno_user_systimer_handler(uint32_t);
typedef void zuno_user_sysevent_handler(ZUNOSysEvent_t * ev);
typedef void zuno_configuartionhandler_t(uint8_t, uint32_t);
typedef void *zuno_battery_handler_t(void);

// Hardware
typedef struct ZUNOUARTOptions_s{
    uint32_t baudrate;
    uint8_t rx_pin;
    uint8_t tx_pin;
}ZUNOUARTOptions_t;

typedef struct HandlerFunc_s{
	uint8_t main_type;
	uint8_t sub_type;
	uint16_t code_offset;
}HandlerFunc_t;

#if MAX_ZUNO_PWMS > 8
	#error "Error pin pwm!"
#endif

typedef struct				ZunoBitField_s
{
	bool					bLockTimer0: 1;
	bool					bLockTimer1: 1;
	bool					bLockWTimer0: 1;
	bool					bLockUsart0: 1;
	bool					bLockUsart1: 1;
	bool					bLockUsart2: 1;
	bool					bExtInit: 1;
	bool					bGPTInit: 1;
	bool					bZDMAInit: 1;
	bool					ADCInitialized: 1;
}							ZunoBitField_t;

typedef struct ZUNOOnDemandHW_s {
	uint32_t			pwm_freq;
	uint32_t			tone_freq_set;
	uint8_t				pwm_pins[MAX_ZUNO_PWMS];
	uint8_t				pwm_pins_state;
	uint8_t				tone_pin;
	volatile uint8_t	ExtPin;// The index of the processed pin
	uint16_t			tone_freq;
	// HANDLERS
	HandlerFunc_t		h_sys_handler[MAX_AVAILIABLE_SYSHANDLERS];
} ZUNOOnDemandHW_t;
extern ZUNOOnDemandHW_t g_zuno_odhw_cfg;
extern ZunoBitField_t g_bit_field;

 
#endif // __ZUNO_SYS_TYPES__