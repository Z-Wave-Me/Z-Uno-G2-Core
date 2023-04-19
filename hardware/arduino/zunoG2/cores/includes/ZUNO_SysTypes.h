#ifndef __ZUNO_SYS_TYPES__
#define __ZUNO_SYS_TYPES__
#include "ZUNO_Definitions.h"

/*
 * Global nodeID type definitions.
 */
typedef uint16_t node_id_t;    // This is used where 2 byte nodeID is needed, like in all that is related to LR.
typedef uint8_t  node_id_8_t;  // This is used where a 1 byte nodeID is needed, like in all NVM3 related operations.

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
typedef struct ZUNOZWConfiguation_s {
	ZUNOChannel_t 		channels[ZUNO_MAX_MULTI_CHANNEL_NUMBER];
	uint8_t 			num_channels;
	ZUNOAssociation_t	associations[ZUNO_MAX_ASSOC_NUMBER];
	uint8_t 			num_associations;
	uint16_t            crc16;
} ZUNOZWConfiguation_t;
/*
typedef struct ZUNODeviceConfiguation_s {
	uint32_t            flags;
	ZUNOChannel_t 		channels[ZUNO_MAX_MULTI_CHANNEL_NUMBER];
	uint8_t 			num_channels;
	ZUNOAssociation_t	associations[ZUNO_MAX_ASSOC_NUMBER];
	uint8_t 			num_associations;
	uint8_t 			num_channel_types;
	ZUNOChannelCCS_t    channel_types[ZUNO_MAX_CCTYPES];
	ZUNOCCSVersion_t    custom_base_ccs[ZUNO_MAX_CUSTOM_CCS];
	uint8_t             num_custom_base_ccs;
	uint16_t            app_version;
	uint16_t            product_id;
	uint8_t				device_generic_type;
	uint8_t				device_specific_type;
	uint16_t			device_icon;
	uint16_t			device_app_icon;
	uint8_t				security_keys;
	uint16_t            __reserved;
	uint16_t            crc16;
}__attribute__((aligned(1),packed)) ZUNODeviceConfiguation_t;
*/
typedef struct ZUNOZWaveProtocolData_s{
	uint32_t flags;
	uint8_t  CCLstNSNI[MAX_CMDCLASES_NSNI];
	uint8_t  CCLstNSIS[MAX_CMDCLASES_CROPPED];
	uint8_t  CCLstSec[MAX_CMDCLASES_SECURED];
	uint8_t  CCLstNSNI_cnt;
	uint8_t  CCLstNSIS_cnt;
	uint8_t  CCLstSec_cnt;
	uint8_t  req_s2_keys;
	uint8_t  option_mask;
	uint8_t  association_count;
	uint16_t product_id;
	uint16_t device_icon;
	uint8_t  generic_type;
	uint8_t  specific_type;
	uint16_t crc16; 
}ZUNOZWaveProtocolData_t;
typedef struct ZUNOOTAFWDescr_s{
	uint16_t id;
	uint16_t version;
}ZUNOOTAFWDescr_t;
// Z-Wave packet
typedef struct ZUNOCommandPacket_s{
	uint8_t * cmd;   // 4B
	uint8_t   flags; // 5B
	uint8_t   len;   // 6B
	uint8_t   src_zw_channel;// 7
	uint8_t   dst_zw_channel;// 8
	node_id_t   src_node;// 9
	node_id_t   dst_node;// 10
	uint8_t   zw_rx_opts;// 11
	uint8_t   zw_rx_secure_opts;//12
	uint8_t	  aux_data[ZUNO_COMMAND_PACKET_MAX_AUX_DATA];
} __attribute__((aligned(1),packed)) ZUNOCommandPacket_t;
typedef struct ZUNOSysConfigData_s {
	uint8_t     b_sketch_valid;
	uint8_t     ifreq;
	uint8_t     maxTxDb;
	uint8_t     adjTxDb;
	uint8_t     secure_mode;
	uint8_t     maxLRTxDb;
	uint8_t     flags; 
	uint8_t     ml_interval;
	uint8_t     ifreq_deffered;
}ZUNOSysConfigData_t;
typedef struct ZUNOFWHeader_s{
	uint8_t 	sign[MAX_FWHEADER_SIGN];
	uint8_t     size;
	uint32_t	build_timestamp;
	uint32_t    build_sequence;
	uint16_t    hw_id;
	uint16_t    version;
	uint8_t     hw_button_pin;
	uint8_t     hw_led1_pin;
	uint8_t     hw_led2_pin;
	uint8_t     hw_uled_pin;
	uint8_t     hw_sapi_tx_pin;
	uint8_t     hw_sapi_rx_pin;
	uint8_t     hw_sapi_uart_number;
	uint8_t     hw_console_tx_pin;
	uint8_t     hw_console_rx_pin;
	uint8_t     hw_console_uart_number;
	uint16_t    vendor_id;
	uint16_t    product_type_id;
	uint32_t    flags;
	uint32_t    crc32;
} __attribute__((aligned(1),packed)) ZUNOFWHeader_t ;

// System variables mapping
typedef struct ZUNOSetupSysState_s {
	uint8_t wakeup_reason;
	uint8_t enclusion_state;
	node_id_t node_id;
	uint8_t granted_keys;
	uint8_t highest_security_level;
	uint32_t gpio_em4flags;
	uint32_t flags;
	// ZUNODeviceConfiguation_t * zwave_cfg;
	ZUNOZWaveProtocolData_t * zw_protocol_data;
	void *  hIOThread;
	void *  hMainThread;
	uint8_t sleep_latches;
	uint8_t sleep_highest_mode;
	uint8_t	persistent_timer_map;
	volatile uint8_t   rstat_priority_counts[4];
	volatile uint32_t  rstat_pkgs_queued;
	volatile uint32_t  rstat_pkgs_processed;
	volatile uint32_t  rstat_pkgs_sent;
	volatile uint32_t  rstat_pkgs_hp_time;
	ZUNOFWHeader_t *   fw_static_header;
	uint32_t  start_error_code;
	uint32_t  error_cnt;
	uint32_t  error_pc_value;
	ZUNOSysConfigData_t *   p_config;
	bool      fw_update_accepted;
	uint8_t   usr_retention[MAX_ZUNO_USER_RETENTION];
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

// Supervisor Call
typedef struct zuno_svc_calldata_s{
    uint8_t  call_number;
    uint8_t  param_count;
    uint32_t params[MAX_SYS_PARAMS];
    uint32_t ret_val;
}zuno_svc_calldata_t;

// Handler types
typedef void zuno_void_handler(void);
typedef void zuno_void_handler_ext_int(uint8_t pin);
typedef void zuno_irq_handler(void *p);
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
	uint32_t code_offset;
}HandlerFunc_t;

typedef struct ZUNOOnDemandHW_s {
	volatile uint8_t	keyGPT;
	struct
	{
		bool					bExtInit: 1;
		bool					ADCInitialized: 1;
	};
	uint32_t	adc_reference;
	uint8_t		adc_resolution;
	uint8_t		adc_acqtime;
	uint8_t		pwm_resolution;
	uint32_t 	pwm_freq;
	//HandlerFunc_t		h_sys_handler[MAX_AVAILIABLE_SYSHANDLERS];// HANDLERS
} ZUNOOnDemandHW_t;
extern ZUNOOnDemandHW_t g_zuno_odhw_cfg;

#define MAX_SLEEP_TIMERS 2
typedef struct ZUNOSleepData_s{
    uint32_t timeout;
    uint32_t wup_timeout;
    uint32_t em4_map;
     // Store user-defined timeouts
    uint32_t sleep_timers[MAX_SLEEP_TIMERS];
    uint32_t user_sleep_ts; // time mark when sleep mode was applied
    uint16_t latch;
    bool     user_latch:1;
    bool     inclusion_latch:1;
    bool     wup_latch:1;
    bool     fwupd_latch:1;
    bool     indicator_latch:1;
}ZUNOSleepData_t;

typedef struct ZUnoAssocNode_s{
    uint16_t   dest_nodeid;
    uint8_t    dest_channel;
    uint8_t    security_level;
}ZUnoAssocNode_t;

typedef struct ZUNORadioStat_s{
	volatile uint8_t queue_busy_flags;
	volatile uint32_t  pkgs_queued;
	volatile uint32_t  pkgs_processed;
	volatile uint32_t  pkgs_sent;
	volatile uint32_t  pkgs_hp_time;
}ZUNORadioStat_t;
typedef struct RadioTestFuncParams_s{
    uint8_t     region;
    uint8_t     channel;
    uint8_t     mode;
    uint8_t     power;
    uint32_t    timeout_ms;
}RadioTestFuncParams_t;
typedef struct SysCryticalStat_s{
	uint32_t max_lock_wait;
	uint32_t max_open_wait;
	uint32_t lock_timeout_count;
	uint32_t open_timeout_count;
	uint32_t systhread_delay_count;
}SysCryticalStat_t;
typedef struct ZUnoChannelDtaHandler_s{
	void * p_handler;     
					   // |    7   | 6 |  5    |   4 | 3 |2|1|0|
	uint8_t   descriptor; // | SIGNED | - | 2^NUM_BYTES |  TYPE   |
}ZUnoChannelDtaHandler_t;

extern ZUNOSleepData_t g_sleep_data;

#endif // __ZUNO_SYS_TYPES__