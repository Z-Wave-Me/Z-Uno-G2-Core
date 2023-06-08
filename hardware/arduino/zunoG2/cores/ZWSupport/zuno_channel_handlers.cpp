#include "Arduino.h"
#include "zuno_channel_handlers.h"
#include "Debug.h"

#define ZUNO_CHANNEL_HANDLERS_MAX_ARG				0x5

static const ZUnoChannelHandler_t *_channelhandlers[ZUNO_MAX_MULTI_CHANNEL_NUMBER];

int32_t static _zuno_universalGetterSetter_map(uint8_t chi, uint32_t flag, uint8_t argc, void *handler, va_list ap) {
	uint8_t							*lp_point_1;
	uint16_t						*lp_point_2;
	uint32_t						*lp_point_4;
	uint32_t						arg;

	Serial.printf("_zuno_universalGetterSetter_map: %ld %d %p\n", (flag & ZUNO_CHANNEL_HANDLERS_FLAGS_POINTER_SIZE_MASK), chi, handler);
	switch ((flag & ZUNO_CHANNEL_HANDLERS_FLAGS_POINTER_SIZE_MASK)) {
		case ZUNO_CHANNEL_HANDLERS_FLAGS_POINTER_SIZE_4:
			lp_point_4 = (uint32_t *)handler;
			if ((flag & ZUNO_CHANNEL_HANDLERS_FLAGS_MULTI) != 0x0)
				lp_point_4 = &lp_point_4[chi];
			if (argc == 0x0)
				return (lp_point_4[0x0]);
			arg = va_arg(ap, uint32_t);
			lp_point_4[0x0] = arg;
			break ;
		case ZUNO_CHANNEL_HANDLERS_FLAGS_POINTER_SIZE_2:
			lp_point_2 = (uint16_t *)handler;
			if ((flag & ZUNO_CHANNEL_HANDLERS_FLAGS_MULTI) != 0x0)
				lp_point_2 = &lp_point_2[chi];
			if (argc == 0x0)
				return (lp_point_2[0x0]);
			arg = va_arg(ap, uint32_t);
			lp_point_2[0x0] = arg;
			break ;
		case ZUNO_CHANNEL_HANDLERS_FLAGS_POINTER_SIZE_1:
		default:
			lp_point_1 = (uint8_t *)handler;
			if ((flag & ZUNO_CHANNEL_HANDLERS_FLAGS_MULTI) != 0x0)
				lp_point_1 = &lp_point_1[chi];
			if (argc == 0x0)
				return (lp_point_1[0x0]);
			arg = va_arg(ap, uint32_t);
			lp_point_1[0x0] = arg;
			break ;
	}
	return (0x0);
}

int32_t static _zuno_universalGetterSetter(uint8_t chi, uint8_t argc, uint32_t flag, void *handler, va_list ap) {
	uint32_t						args[ZUNO_CHANNEL_HANDLERS_MAX_ARG];
	uint8_t							i;
	int32_t							out;

	if ((flag & ZUNO_CHANNEL_HANDLERS_FLAGS_POINTER) != 0x0)
		return (_zuno_universalGetterSetter_map(chi, flag, argc, handler, ap));
	i = 0x0;
	if ((flag & ZUNO_CHANNEL_HANDLERS_FLAGS_MULTI) != 0x0) {
		args[0x0] = chi;
		i++;
		argc++;
	}
	if (argc > ZUNO_CHANNEL_HANDLERS_MAX_ARG)
		return (0x0);
	while (i < argc) {
		args[i] = va_arg(ap, uint32_t);
		i++;
	}
	Serial.printf("_zuno_universalGetterSetter: %d %p\n", chi, handler);
	switch (argc) {
		case 0x0:
			out = ((int32_t (*)(void))handler)();
			break ;
		case 0x1:
			out = ((int32_t (*)(uint32_t))handler)(args[0x0]);
			break ;
		case 0x2:
			out = ((int32_t (*)(uint32_t, uint32_t))handler)(args[0x0], args[0x1]);
			break ;
		case 0x3:
			out = ((int32_t (*)(uint32_t, uint32_t, uint32_t))handler)(args[0x0], args[0x1], args[0x2]);
			break ;
		case 0x4:
			out = ((int32_t (*)(uint32_t, uint32_t, uint32_t, uint32_t))handler)(args[0x0], args[0x1], args[0x2], args[0x3]);
			break ;
		case 0x5:
			out = ((int32_t (*)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))handler)(args[0x0], args[0x1], args[0x2], args[0x3], args[0x4]);
			break ;
		default:
			out = 0x0;
			break ;
	}
	return (out);
}

int32_t zuno_universalGetterSetter(uint8_t zuno_ch, uint8_t index, uint8_t argc, ...) {
	int32_t										out;
	va_list										ap;
	const ZUnoChannelHandler_t					*handler;
	const ZUnoChannelHandlerArray_t				*handler_array;

	if (zuno_ch >= ZUNO_CFG_CHANNEL_COUNT)
		return (0x0);
	if((handler = _channelhandlers[zuno_ch]) == NULL)
		return (0x0);
	if (index >= handler->count)
		return (0x0);
	va_start(ap, argc);
	handler_array = &handler->array[index];
	out = _zuno_universalGetterSetter(zuno_ch - handler->offset, argc, handler_array->flag, handler_array->handler, ap);
	va_end(ap);
	return (out);
}

void zunoAppendChannelHandlerEx(uint8_t channel, const ZUnoChannelHandler_t *handler) {
	if (channel >= ZUNO_MAX_MULTI_CHANNEL_NUMBER)
		return ;
	#ifdef LOGGING_DBG
	LOGGING_UART.print("SETUP CH:");
	LOGGING_UART.print(channel);
	LOGGING_UART.print(" HANDLER:");
	LOGGING_UART.println((uint32_t)handler, HEX);
	#endif
	_channelhandlers[channel] = handler;
}

static uint32_t _get_size_old(byte value_size) {
	uint32_t						out;

	switch (value_size) {
		case 0x4:
			out = ZUNO_CHANNEL_HANDLERS_FLAGS_POINTER_SIZE_4;
			break;
		case 0x2:
			out = ZUNO_CHANNEL_HANDLERS_FLAGS_POINTER_SIZE_2;
			break;
		case 0x1:
		default:
			out = ZUNO_CHANNEL_HANDLERS_FLAGS_POINTER_SIZE_1;
			break ;
	}
	return (out);
}

bool _zunoAppendChannelHandler(byte ch, byte value_size, byte type, void *handler) {
	ZUnoChannelHandler_t								*channel_handler;
	uint8_t												count;
	uint32_t											flag;
	uint8_t												offset;
	const zuno_handler_single_gettersetter_t			*single_gettersetter;
	const zuno_handler_multi_getter_t					*multi_getter;
	const zuno_handler_multi_gettersetter_t				*multi_gettersetter;
	const zuno_handler_single_thermostat_t				*single_thermostat;
	const zuno_handler_multi_thermostat_t				*multi_thermostat;

	if (ch >= ZUNO_MAX_MULTI_CHANNEL_NUMBER)
		return (false);
	if ((channel_handler = (ZUnoChannelHandler_t *)_channelhandlers[ch]) != NULL && channel_handler->old == true) {
		free(channel_handler);
		_channelhandlers[ch] = NULL;
	}
	switch (type) {
		case CHANNEL_HANDLER_SINGLE_GETTER:
			if ((channel_handler = (ZUnoChannelHandler_t *)malloc((sizeof(ZUnoChannelHandler_t) + (sizeof(ZUnoChannelHandlerArray_t) * 0x1)))) == NULL)
				return (false);
			channel_handler->array[0x0].handler = handler;
			channel_handler->array[0x0].flag = 0x0;
			count = 0x1;
			offset = 0x0;
			break ;
		case CHANNEL_HANDLER_MULTI_GETTER:
			if ((channel_handler = (ZUnoChannelHandler_t *)malloc((sizeof(ZUnoChannelHandler_t) + (sizeof(ZUnoChannelHandlerArray_t) * 0x1)))) == NULL)
				return (false);
			multi_getter = (const zuno_handler_multi_getter_t *)handler;
			channel_handler->array[0x0].handler = multi_getter->getter;
			channel_handler->array[0x0].flag = ZUNO_CHANNEL_HANDLERS_FLAGS_MULTI;
			count = 0x1;
			offset = multi_getter->offset;
			break ;
		case CHANNEL_HANDLER_SINGLE_GETTERSETTER:
		case CHANNEL_HANDLER_SINGLE_GETTERSETTER_2P:
			if ((channel_handler = (ZUnoChannelHandler_t *)malloc((sizeof(ZUnoChannelHandler_t) + (sizeof(ZUnoChannelHandlerArray_t) * 0x2)))) == NULL)
				return (false);
			single_gettersetter = (const zuno_handler_single_gettersetter_t *)handler;
			channel_handler->array[0x0].handler = single_gettersetter->getter;
			channel_handler->array[0x0].flag = 0x0;
			channel_handler->array[0x1].handler = single_gettersetter->setter;
			channel_handler->array[0x1].flag = 0x0;
			count = 0x2;
			offset = 0x0;
			break ;
		case CHANNEL_HANDLER_MULTI_GETTERSETTER:
		case CHANNEL_HANDLER_MULTI_GETTERSETTER_2P:
			if ((channel_handler = (ZUnoChannelHandler_t *)malloc((sizeof(ZUnoChannelHandler_t) + (sizeof(ZUnoChannelHandlerArray_t) * 0x2)))) == NULL)
				return (false);
			multi_gettersetter = (const zuno_handler_multi_gettersetter_t *)handler;
			channel_handler->array[0x0].handler = multi_gettersetter->getter;
			channel_handler->array[0x0].flag = ZUNO_CHANNEL_HANDLERS_FLAGS_MULTI;
			channel_handler->array[0x1].handler = multi_gettersetter->setter;
			channel_handler->array[0x1].flag = ZUNO_CHANNEL_HANDLERS_FLAGS_MULTI;
			count = 0x2;
			offset = multi_gettersetter->offset;
			break ;
		case CHANNEL_HANDLER_SINGLE_VALUEMAPPER:
			if ((channel_handler = (ZUnoChannelHandler_t *)malloc((sizeof(ZUnoChannelHandler_t) + (sizeof(ZUnoChannelHandlerArray_t) * 0x2)))) == NULL)
				return (false);
			flag = _get_size_old(value_size) | ZUNO_CHANNEL_HANDLERS_FLAGS_POINTER;
			channel_handler->array[0x0].handler = handler;
			channel_handler->array[0x0].flag = flag;
			channel_handler->array[0x1].handler = handler;
			channel_handler->array[0x1].flag = flag;
			count = 0x2;
			offset = 0x0;
			break ;
		case CHANNEL_HANDLER_MULTI_MAPPER:
			if ((channel_handler = (ZUnoChannelHandler_t *)malloc((sizeof(ZUnoChannelHandler_t) + (sizeof(ZUnoChannelHandlerArray_t) * 0x2)))) == NULL)
				return (false);
			multi_getter = (const zuno_handler_multi_getter_t *)handler;
			flag = _get_size_old(value_size) | (ZUNO_CHANNEL_HANDLERS_FLAGS_POINTER | ZUNO_CHANNEL_HANDLERS_FLAGS_MULTI);
			channel_handler->array[0x0].handler = multi_getter->getter;
			channel_handler->array[0x0].flag = flag;
			channel_handler->array[0x1].handler = multi_getter->getter;
			channel_handler->array[0x1].flag = flag;
			count = 0x2;
			offset = multi_getter->offset;
			break ;
		case CHANNEL_HANDLER_SINGLE_THERMOSTAT:
			if ((channel_handler = (ZUnoChannelHandler_t *)malloc((sizeof(ZUnoChannelHandler_t) + (sizeof(ZUnoChannelHandlerArray_t) * 0x4)))) == NULL)
				return (false);
			single_thermostat = (const zuno_handler_single_thermostat_t *)handler;
			channel_handler->array[0x0].handler = single_thermostat->getter1;
			channel_handler->array[0x0].flag = 0x0;
			channel_handler->array[0x1].handler = single_thermostat->setter1;
			channel_handler->array[0x1].flag = 0x0;
			channel_handler->array[0x2].handler = single_thermostat->getter2;
			channel_handler->array[0x2].flag = 0x0;
			channel_handler->array[0x3].handler = single_thermostat->setter2;
			channel_handler->array[0x3].flag = 0x0;
			count = 0x4;
			offset = 0x0;
			break ;
		case CHANNEL_HANDLER_MULTI_THERMOSTAT:
			if ((channel_handler = (ZUnoChannelHandler_t *)malloc((sizeof(ZUnoChannelHandler_t) + (sizeof(ZUnoChannelHandlerArray_t) * 0x4)))) == NULL)
				return (false);
			multi_thermostat = (const zuno_handler_multi_thermostat_t *)handler;
			channel_handler->array[0x0].handler = multi_thermostat->getter1;
			channel_handler->array[0x0].flag = ZUNO_CHANNEL_HANDLERS_FLAGS_MULTI;
			channel_handler->array[0x1].handler = multi_thermostat->setter1;
			channel_handler->array[0x1].flag = ZUNO_CHANNEL_HANDLERS_FLAGS_MULTI;
			channel_handler->array[0x2].handler = multi_thermostat->getter2;
			channel_handler->array[0x2].flag = ZUNO_CHANNEL_HANDLERS_FLAGS_MULTI;
			channel_handler->array[0x3].handler = multi_thermostat->setter2;
			channel_handler->array[0x3].flag = ZUNO_CHANNEL_HANDLERS_FLAGS_MULTI;
			count = 0x4;
			offset = multi_thermostat->offset;
			break ;
		default:
			return (false);
			break ;
	}
	channel_handler->count = count;
	channel_handler->offset = offset;
	channel_handler->old = true;
	zunoAppendChannelHandlerEx(ch, channel_handler);
	return (true);
}

// void zuno_universalSetter1P(byte zuno_ch, int32_t value) {
// 	zuno_universalGetterSetter(zuno_ch, 0x1, 0x1, value);
// }
// void zuno_universalSetter2P(byte zuno_ch, uint32_t value, uint32_t value_add) {
// 	zuno_universalGetterSetter(zuno_ch, 0x1, 0x2, value, value_add);
// }
// int32_t zuno_universalGetter1P(byte zuno_ch) {
// 	return (zuno_universalGetterSetter(zuno_ch, 0x0, 0x0));
// }
// uint32_t zuno_universalGetter2P(byte zuno_ch, uint32_t value) {
// 	return (zuno_universalGetterSetter(zuno_ch, 0x0, 0x1, value));
// }

// void zunoAppendChannelHandler(byte ch, byte value_size, byte type, void * handler) {
// 	_zunoAppendChannelHandler(ch, value_size, type, handler);
// }


ZUnoChannelDtaHandler_t g_zuno_channelhandlers_map[ZUNO_MAX_MULTI_CHANNEL_NUMBER];

#define HANDLER_DESCRIPTOR_TYPE_MASK     0x0F
#define HANDLER_DESCRIPTOR_LEN_SHIFT     0x04
#define HANDLER_DESCRIPTOR_LEN_MASK      0x03
#define HANDLER_DESCRIPTOR_SIGNED_BIT    0x80

void zunoAppendChannelHandler(byte ch, byte value_size, byte type, void * handler) {
	#ifdef LOGGING_DBG
	LOGGING_UART.print("SETUP CH:");
	LOGGING_UART.print(ch);
	LOGGING_UART.print(" HANDLER:");
	LOGGING_UART.println((uint32_t)handler, HEX);
	#endif
	g_zuno_channelhandlers_map[ch].descriptor = (((value_size >> 1)&HANDLER_DESCRIPTOR_LEN_MASK) << HANDLER_DESCRIPTOR_LEN_SHIFT) | (type & HANDLER_DESCRIPTOR_TYPE_MASK);
	g_zuno_channelhandlers_map[ch].p_handler = handler;
}

// Universal staff for CC support
int32_t zuno_callGetter(byte val_type, byte ch, void * handler){
	if(handler == 0)
		return 0;
	switch(val_type){
		case HADLER_ARGTYPE_1UB:
		case HADLER_ARGTYPE_1SB:
			if(ch != UNKNOWN_CHANNEL)
				return ((zuno_multigetter1ub_t*)handler)(ch);
			return ((zuno_singlegetter1ub_t*)handler)();
		case HADLER_ARGTYPE_2UB:
		case HADLER_ARGTYPE_2SB:
			if(ch != UNKNOWN_CHANNEL)
				return ((zuno_multigetter2ub_t*)handler)(ch);
			return ((zuno_singlegetter2ub_t*)handler)();
		case HADLER_ARGTYPE_4UB:
		case HADLER_ARGTYPE_4SB:
			if(ch != UNKNOWN_CHANNEL)
				return ((zuno_multigetter4ub_t*)handler)(ch);
			return ((zuno_singlegetter4ub_t*)handler)();
	}
	return (0);
}
void zuno_callSetter(byte val_type, byte ch, void * handler, int32_t value) {
	if(handler == 0)
		return;
	switch(val_type){
		case HADLER_ARGTYPE_1UB:
		case HADLER_ARGTYPE_1SB: {
				uint8_t v =  value & 0xFF;
				if(ch != UNKNOWN_CHANNEL)
				{
					((zuno_multisetter1ub_t*)handler)(ch, v);
					 break;
				}
				((zuno_singlesetter1ub_t*)handler)(v);
			}
			break;
		case HADLER_ARGTYPE_2UB:
		case HADLER_ARGTYPE_2SB:{
				uint16_t v =  value & 0xFFFF;
				if(ch != UNKNOWN_CHANNEL){
					((zuno_multisetter2ub_t*)handler)(ch, v);
					break;
				}
				((zuno_singlesetter2ub_t*)handler)(v);
			}
			break;
		case HADLER_ARGTYPE_4UB:
		case HADLER_ARGTYPE_4SB:
			if(ch != UNKNOWN_CHANNEL)
			{
				((zuno_multisetter4ub_t*)handler)(ch, value);
				break;
			}
			((zuno_singlesetter4ub_t*)handler)(value);
			break;
	}
}
int zuno_getMappedValue(byte val_type, byte ch, void * handler){
	switch(val_type){
		case HADLER_ARGTYPE_1UB:
		case HADLER_ARGTYPE_1SB:
			if(ch != UNKNOWN_CHANNEL)
				return ((uint8_t*)handler)[ch];
			return *((uint8_t*)handler);
		case HADLER_ARGTYPE_2UB:
		case HADLER_ARGTYPE_2SB:
			if(ch != UNKNOWN_CHANNEL)
				return ((uint16_t*)handler)[ch];
			return *((uint16_t*)handler);
		case HADLER_ARGTYPE_4UB:
		case HADLER_ARGTYPE_4SB:
			if(ch != UNKNOWN_CHANNEL)
				return ((uint32_t*)handler)[ch];
			return *((uint32_t*)handler);
	}
	return (0);
}

void zuno_setMappedValue(byte val_type, byte ch, void * handler, int32_t value){
	switch(val_type){
		case HADLER_ARGTYPE_1UB:
		case HADLER_ARGTYPE_1SB:
			if(ch != UNKNOWN_CHANNEL)
			{
				((uint8_t*)handler)[ch] = value & 0xFF;
				break;
			}
			*((uint8_t*)handler) = value & 0xFF;
			break;
		case HADLER_ARGTYPE_2UB:
		case HADLER_ARGTYPE_2SB:
			if(ch != UNKNOWN_CHANNEL)
			{
				((uint16_t*)handler)[ch] = value & 0xFFFF;
				break;
			}
			*((uint16_t*)handler) = value & 0xFFFF;
			break;
		case HADLER_ARGTYPE_4UB:
		case HADLER_ARGTYPE_4SB:
			if(ch != UNKNOWN_CHANNEL)
			{
				((uint32_t*)handler)[ch] = value;
				break;
			}
			*((uint32_t*)handler) = value;
			break;
	}
}
int32_t zuno_universalGetter1P(byte zuno_ch) {
	if(zuno_ch>ZUNO_CFG_CHANNEL_COUNT)
		return 0;
	if(g_zuno_channelhandlers_map[zuno_ch].p_handler == NULL)
		return 0;
	byte type = g_zuno_channelhandlers_map[zuno_ch].descriptor & HANDLER_DESCRIPTOR_TYPE_MASK;
	byte val_type = (g_zuno_channelhandlers_map[zuno_ch].descriptor >> HANDLER_DESCRIPTOR_LEN_SHIFT);
	#ifdef LOGGING_DBG
	LOGGING_UART.print("***Universal Getter T:");
	LOGGING_UART.print(type);
	LOGGING_UART.print(" H:");
	LOGGING_UART.println((uint32_t)g_zuno_channelhandlers_map[zuno_ch].p_handler,HEX);
	delay(10);
	#endif
	switch(type){
		case CHANNEL_HANDLER_EMPTY:
			return 0;
		case CHANNEL_HANDLER_SINGLE_GETTER:
			return zuno_callGetter(val_type, UNKNOWN_CHANNEL, g_zuno_channelhandlers_map[zuno_ch].p_handler);
		case CHANNEL_HANDLER_SINGLE_GETTERSETTER:
		{
			zuno_handler_single_gettersetter_t * p_gs = (zuno_handler_single_gettersetter_t *) g_zuno_channelhandlers_map[zuno_ch].p_handler;
			return zuno_callGetter(val_type, UNKNOWN_CHANNEL, p_gs->getter);
		}
		case CHANNEL_HANDLER_SINGLE_VALUEMAPPER:
			return zuno_getMappedValue(val_type, UNKNOWN_CHANNEL, g_zuno_channelhandlers_map[zuno_ch].p_handler);
		case CHANNEL_HANDLER_MULTI_GETTER:{
			zuno_handler_multi_getter_t * p_mg = (zuno_handler_multi_getter_t *) g_zuno_channelhandlers_map[zuno_ch].p_handler;
			return zuno_callGetter(val_type, zuno_ch-p_mg->offset, p_mg->getter);
		}
		case CHANNEL_HANDLER_MULTI_GETTERSETTER:
		{
			zuno_handler_multi_gettersetter_t * p_mgs = (zuno_handler_multi_gettersetter_t *) g_zuno_channelhandlers_map[zuno_ch].p_handler;
			return zuno_callGetter(val_type, zuno_ch-p_mgs->offset, p_mgs->getter);
		}
		case CHANNEL_HANDLER_MULTI_MAPPER:{
			zuno_handler_multi_getter_t * p_mw = (zuno_handler_multi_getter_t *) g_zuno_channelhandlers_map[zuno_ch].p_handler;
			return zuno_getMappedValue(val_type, zuno_ch - p_mw->offset, p_mw->getter);
		}
		case CHANNEL_HANDLER_SINGLE_THERMOSTAT:
		{
			zuno_handler_single_thermostat_t *p_gs = (zuno_handler_single_thermostat_t *) g_zuno_channelhandlers_map[zuno_ch].p_handler;
			return zuno_callGetter(val_type, UNKNOWN_CHANNEL, p_gs->getter1);
		}
		case CHANNEL_HANDLER_MULTI_THERMOSTAT:
		{
			zuno_handler_multi_thermostat_t *p_mgs = (zuno_handler_multi_thermostat_t *) g_zuno_channelhandlers_map[zuno_ch].p_handler;
			return zuno_callGetter(val_type, zuno_ch-p_mgs->offset, p_mgs->getter1);
		}
	}
	return 0;
}

void zuno_universalSetter1P(byte zuno_ch, int32_t value) {
	if(zuno_ch > ZUNO_CFG_CHANNEL_COUNT)
		return;
	_zunoMarkChannelUpdated(zuno_ch);
	byte type = g_zuno_channelhandlers_map[zuno_ch].descriptor & HANDLER_DESCRIPTOR_TYPE_MASK;
	byte val_type = (g_zuno_channelhandlers_map[zuno_ch].descriptor >> HANDLER_DESCRIPTOR_LEN_SHIFT);
	switch(type) {
		case CHANNEL_HANDLER_SINGLE_GETTERSETTER: {
				zuno_handler_single_gettersetter_t * p_gs = (zuno_handler_single_gettersetter_t *) g_zuno_channelhandlers_map[zuno_ch].p_handler;
				zuno_callSetter(val_type, UNKNOWN_CHANNEL, p_gs->setter, value);
			}
			break;
		case CHANNEL_HANDLER_SINGLE_VALUEMAPPER:
			zuno_setMappedValue(val_type, UNKNOWN_CHANNEL, g_zuno_channelhandlers_map[zuno_ch].p_handler, value);
			break;
		case CHANNEL_HANDLER_MULTI_GETTERSETTER: {
				zuno_handler_multi_gettersetter_t * p_mgs = (zuno_handler_multi_gettersetter_t *) g_zuno_channelhandlers_map[zuno_ch].p_handler;
				zuno_callSetter(val_type, zuno_ch-p_mgs->offset, p_mgs->setter, value);
			}
			break;
		case CHANNEL_HANDLER_MULTI_MAPPER: {
				zuno_handler_multi_getter_t * p_mw = (zuno_handler_multi_getter_t *) g_zuno_channelhandlers_map[zuno_ch].p_handler;
				zuno_setMappedValue(val_type, zuno_ch - p_mw->offset, p_mw->getter, value);
			}
			break;
		case CHANNEL_HANDLER_SINGLE_THERMOSTAT: {
				zuno_handler_single_thermostat_t *p_gs = (zuno_handler_single_thermostat_t *) g_zuno_channelhandlers_map[zuno_ch].p_handler;
				zuno_callSetter(val_type, UNKNOWN_CHANNEL, p_gs->setter1, value);
			}
			break;
		case CHANNEL_HANDLER_MULTI_THERMOSTAT: {
				zuno_handler_multi_thermostat_t * p_mgs = (zuno_handler_multi_thermostat_t *) g_zuno_channelhandlers_map[zuno_ch].p_handler;
				zuno_callSetter(val_type, zuno_ch-p_mgs->offset, p_mgs->setter1, value);
			}
			break;
	}
}

static uint32_t _callGetter2P(byte val_type, byte ch, void * handler, uint32_t value){
	if (handler == 0)
		return (0);
	switch(val_type) {
		case HADLER_ARGTYPE_1UB:
		case HADLER_ARGTYPE_1SB:
			if(ch != UNKNOWN_CHANNEL)
				return (((zuno_multigetter1ub_2p_t *)handler)(ch, value));
			else
				return (((zuno_singlegetter1ub_2p_t *)handler)(value));
			break;
		case HADLER_ARGTYPE_2UB:
		case HADLER_ARGTYPE_2SB:
			if(ch != UNKNOWN_CHANNEL)
				return (((zuno_multigetter2ub_2p_t *)handler)(ch, value));
			else
				return (((zuno_singlegetter2ub_2p_t *)handler)(value));
			break;
		case HADLER_ARGTYPE_4UB:
		case HADLER_ARGTYPE_4SB:
			if(ch != UNKNOWN_CHANNEL)
				return (((zuno_multigetter4ub_2p_t *)handler)(ch, value));
			else
				return (((zuno_singlegetter4ub_2p_t *)handler)(value));
			break;
		default:
			return (0);
	}
	
}


uint32_t zuno_universalGetter2P(byte zuno_ch, uint32_t value) {
	void							*lp;
	uint8_t							type;
	uint8_t							val_type;

	if (zuno_ch > ZUNO_CFG_CHANNEL_COUNT)
		return (0);
	_zunoMarkChannelUpdated(zuno_ch);
	lp = &g_zuno_channelhandlers_map[zuno_ch];
	type = ((ZUnoChannelDtaHandler_t *)lp)->descriptor & HANDLER_DESCRIPTOR_TYPE_MASK;
	val_type = (((ZUnoChannelDtaHandler_t *)lp)->descriptor >> HANDLER_DESCRIPTOR_LEN_SHIFT);
	lp = ((ZUnoChannelDtaHandler_t *)lp)->p_handler;
	switch(type) {
		case CHANNEL_HANDLER_SINGLE_GETTERSETTER_2P:
			return _callGetter2P(val_type, UNKNOWN_CHANNEL, ((zuno_handler_single_gettersetter_t *)lp)->getter, value);
		case CHANNEL_HANDLER_MULTI_GETTERSETTER_2P:
			return _callGetter2P(val_type, zuno_ch - ((zuno_handler_multi_gettersetter_t *)lp)->offset, ((zuno_handler_multi_gettersetter_t *)lp)->getter, value);
		case CHANNEL_HANDLER_SINGLE_THERMOSTAT:
			return _callGetter2P(HADLER_ARGTYPE_2UB, UNKNOWN_CHANNEL, ((zuno_handler_single_thermostat_t *)lp)->getter2, value);
		case CHANNEL_HANDLER_MULTI_THERMOSTAT:
			return _callGetter2P(HADLER_ARGTYPE_2UB, zuno_ch - ((zuno_handler_multi_thermostat_t *)lp)->offset, ((zuno_handler_multi_thermostat_t *)lp)->getter2, value);
	}
	return 0;
}

static void _callSetter2P(byte val_type, byte ch, void *handler, uint32_t value, uint32_t value_add) {
	if (handler == 0)
		return ;
	
	switch(val_type) {
		case HADLER_ARGTYPE_1UB:
		case HADLER_ARGTYPE_1SB:
			value = value & 0xFF;
			value_add = value_add & 0xFF;
			if(ch != UNKNOWN_CHANNEL)
				((zuno_multisetter1ub_2p_t *)handler)(ch, value, value_add);
			else
				((zuno_singlesetter1ub_2p_t *)handler)(value, value_add);
			break;
		case HADLER_ARGTYPE_2UB:
		case HADLER_ARGTYPE_2SB:
			value = value & 0xFFFF;
			value_add = value_add & 0xFFFF;
			if(ch != UNKNOWN_CHANNEL)
				((zuno_multisetter2ub_2p_t *)handler)(ch, value, value_add);
			else
				((zuno_singlesetter2ub_2p_t *)handler)(value, value_add);
			break;
		case HADLER_ARGTYPE_4UB:
		case HADLER_ARGTYPE_4SB:
			if(ch != UNKNOWN_CHANNEL)
				((zuno_multisetter4ub_2p_t *)handler)(ch, value, value_add);
			else
				((zuno_singlesetter4ub_2p_t *)handler)(value, value_add);
			break;
		default:
			return ;
	}
	
}

void zuno_universalSetter2P(byte zuno_ch, uint32_t value, uint32_t value_add) {
	void							*lp;
	uint8_t							type;
	uint8_t							val_type;

	if(zuno_ch > ZUNO_CFG_CHANNEL_COUNT)
		return;
	lp = &g_zuno_channelhandlers_map[zuno_ch];
	type = ((ZUnoChannelDtaHandler_t *)lp)->descriptor & HANDLER_DESCRIPTOR_TYPE_MASK;
	val_type = (((ZUnoChannelDtaHandler_t *)lp)->descriptor >> HANDLER_DESCRIPTOR_LEN_SHIFT);
	lp = ((ZUnoChannelDtaHandler_t *)lp)->p_handler;
	switch(type) {
		case CHANNEL_HANDLER_SINGLE_GETTERSETTER_2P:
			_callSetter2P(val_type, UNKNOWN_CHANNEL, ((zuno_handler_single_gettersetter_t *)lp)->setter, value, value_add);
			break;
		case CHANNEL_HANDLER_MULTI_GETTERSETTER_2P:
			_callSetter2P(val_type, zuno_ch - ((zuno_handler_multi_gettersetter_t *)lp)->offset, ((zuno_handler_multi_gettersetter_t *)lp)->setter, value, value_add);
			break;
		case CHANNEL_HANDLER_SINGLE_THERMOSTAT:
			_callSetter2P(HADLER_ARGTYPE_2UB, UNKNOWN_CHANNEL, ((zuno_handler_single_thermostat_t *)lp)->setter2, value, value_add);
			break;
		case CHANNEL_HANDLER_MULTI_THERMOSTAT:
			_callSetter2P(HADLER_ARGTYPE_2UB, zuno_ch - ((zuno_handler_multi_thermostat_t *)lp)->offset, ((zuno_handler_multi_thermostat_t *)lp)->setter2, value, value_add);
			break;
	}
}
