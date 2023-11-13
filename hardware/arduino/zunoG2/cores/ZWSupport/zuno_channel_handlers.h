#ifndef ZUNO_CHANNEL_HANDLERS_H
#define ZUNO_CHANNEL_HANDLERS_H

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
} zuno_handler_single_thermostat_t;
typedef struct		zuno_handler_multi_thermostat_s {
	void			*getter1;
	void			*setter1;
	void			*getter2;
	void			*setter2;
	uint8_t			offset;
}	zuno_handler_multi_thermostat_t;
typedef struct		zuno_handler_soundswitch_s {
	void            *tone_info;
	void			*play;
	void			*stop;
} zuno_handler_soundswitch_t;
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


// SINGLE_GETTER 2P
typedef uint8_t zuno_singlegetter1ub_2p_t(uint32_t);
typedef uint16_t zuno_singlegetter2ub_2p_t(uint32_t);
typedef uint32_t zuno_singlegetter4ub_2p_t(uint32_t);
// MULTI_GETTER 2P
typedef uint8_t zuno_multigetter1ub_2p_t(uint8_t, uint32_t);
typedef uint16_t zuno_multigetter2ub_2p_t(uint8_t, uint32_t);
typedef uint32_t zuno_multigetter4ub_2p_t(uint8_t, uint32_t);
// SINGLE_SETTER 2P
typedef void zuno_singlesetter1ub_2p_t(uint32_t, uint8_t);
typedef void zuno_singlesetter2ub_2p_t(uint32_t, uint16_t);
typedef void zuno_singlesetter4ub_2p_t(uint32_t, uint32_t);
// MULTI_SETTER 2P
typedef void zuno_multisetter1ub_2p_t(uint8_t, uint32_t, uint8_t);
typedef void zuno_multisetter2ub_2p_t(uint8_t, uint32_t, uint16_t);
typedef void zuno_multisetter4ub_2p_t(uint8_t, uint32_t, uint32_t);

void zuno_universalSetter1P(byte zuno_ch, int32_t value);
void zuno_universalSetter2P(byte zuno_ch, uint32_t value, uint32_t value_add);
int32_t zuno_universalGetter1P(byte zuno_ch);
uint32_t zuno_universalGetter2P(byte zuno_ch, uint32_t value);

enum {
	HADLER_ARGTYPE_1UB,
	HADLER_ARGTYPE_2UB,
	HADLER_ARGTYPE_4UB,
	HADLER_ARGTYPE_1SB = HADLER_ARGTYPE_1UB | 0x08,
	HADLER_ARGTYPE_2SB = HADLER_ARGTYPE_2UB | 0x08,
	HADLER_ARGTYPE_4SB = HADLER_ARGTYPE_4UB | 0x08
};

enum
{
	CHANNEL_HANDLER_EMPTY,      // DEFAULT_VALUE
	CHANNEL_HANDLER_SINGLE_GETTER,
	CHANNEL_HANDLER_SINGLE_GETTERSETTER,
	CHANNEL_HANDLER_SINGLE_VALUEMAPPER,
	CHANNEL_HANDLER_MULTI_GETTER,
	CHANNEL_HANDLER_MULTI_GETTERSETTER,
	CHANNEL_HANDLER_MULTI_MAPPER,
	CHANNEL_HANDLER_SINGLE_GETTERSETTER_2P,
	CHANNEL_HANDLER_MULTI_GETTERSETTER_2P,
	CHANNEL_HANDLER_SINGLE_THERMOSTAT,
	CHANNEL_HANDLER_MULTI_THERMOSTAT,
	CHANNEL_HANDLER_SOUNDSWITCH,
	CHANNEL_HANDLER_SINGLE_WINDOWCOVERING,
	CHANNEL_HANDLER_MULTI_WINDOWCOVERING
};


#define ZUNO_CHANNEL_HANDLERS_FLAGS_POINTER				(0x1 << 0x0)
#define ZUNO_CHANNEL_HANDLERS_FLAGS_MULTI				(0x1 << 0x1)
#define ZUNO_CHANNEL_HANDLERS_FLAGS_SETTER				(0x1 << 0x2)
#define ZUNO_CHANNEL_HANDLERS_FLAGS_POINTER_SIZE_SHIFT	(0x3)
#define ZUNO_CHANNEL_HANDLERS_FLAGS_POINTER_SIZE_MASK	(0x3 << ZUNO_CHANNEL_HANDLERS_FLAGS_POINTER_SIZE_SHIFT)
#define ZUNO_CHANNEL_HANDLERS_FLAGS_POINTER_SIZE_1		(0x0 << ZUNO_CHANNEL_HANDLERS_FLAGS_POINTER_SIZE_SHIFT)
#define ZUNO_CHANNEL_HANDLERS_FLAGS_POINTER_SIZE_2		(0x1 << ZUNO_CHANNEL_HANDLERS_FLAGS_POINTER_SIZE_SHIFT)
#define ZUNO_CHANNEL_HANDLERS_FLAGS_POINTER_SIZE_4		(0x2 << ZUNO_CHANNEL_HANDLERS_FLAGS_POINTER_SIZE_SHIFT)

typedef struct			ZUnoChannelHandlerArray_s
{
	uint32_t			flag;
	void				*handler;
}						ZUnoChannelHandlerArray_t;

typedef struct ZUnoChannelHandler_s
{
	uint8_t offset;
	uint8_t count;
	uint8_t old;
	ZUnoChannelHandlerArray_t array[];
} ZUnoChannelHandler_t;

void zunoAppendChannelHandler(byte ch, byte value_size, byte type, void * handler);
void zunoAppendChannelHandlerEx(uint8_t channel, const ZUnoChannelHandler_t *handler);
int32_t zuno_universalGetterSetter(uint8_t zuno_ch, uint8_t index, uint8_t argc, ...);
void * zunoExtractChannelHandlerPtr(uint8_t zuno_ch, uint8_t * type);
#endif//ZUNO_CHANNEL_HANDLERS_H