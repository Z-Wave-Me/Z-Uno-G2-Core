#include "Arduino.h"
#include "LinkedList.h"
#include "Debug.h"
#include "LLCore.h"
#include "HandlerMapper.h"
extern ZUNOCodeHeader_t g_zuno_codeheader;
static ZNLinkedList_t * g_syshandler_map = NULL;
static HandlerFunc_t  * findHandlerByType(byte type, byte sub_type, void *handler = NULL, int *index = NULL){
    ZNLinkedList_t * e;
    HandlerFunc_t  * h;
    uint32_t	   code_offset = (uint32_t)((byte*)handler);
    int i;
    for(e=g_syshandler_map, i=0; e; e=e->next, i++){
        h = (HandlerFunc_t *) e->data;
        if ( (h->main_type == type) &&
             (h->sub_type == sub_type) && 
             ((code_offset != 0) && (h->code_offset == code_offset))){
            if(index != NULL)
                *index = i;
            return h;
        }
    }
    
    return NULL;
}
bool zunoAttachSysHandler(byte type, byte sub_type, void *handler) {
    uint32_t	   code_offset = (uint32_t)((byte*)handler);
    if(findHandlerByType(type, sub_type, handler) != NULL)
        return true;
    HandlerFunc_t  * h = (HandlerFunc_t  *)malloc(sizeof(ZUNOCommandPacket_t));
    if(h == NULL)
        return false;
    h->main_type   =  type;
    h->sub_type    =  sub_type;
    h->code_offset =  code_offset;
    znllPushBack(&g_syshandler_map, (void*)h);
    return true;
}
bool zunoDetachSysHandler(byte type, byte sub_type, void *handler) {
    int index;
    HandlerFunc_t  * h = findHandlerByType(type, sub_type, handler, &index);
    if(h == NULL)
        return false;
    znllRemove(&g_syshandler_map, index);
    free(h);
    return true;
}

bool zunoDetachSysHandlerAllSubType(byte type, byte sub_type) {
    bool found = true;
    HandlerFunc_t  * h;
    int rc = 0;
    while(found) {
        int index;
        h = findHandlerByType(type, sub_type, NULL, &index);
        found = (h != NULL);
        if(found){
            znllRemove(&g_syshandler_map, index);
            free(h);
            rc ++;
        }   
    }
    return rc != 0;
}

void * zunoSysHandlerCall(uint8_t type, uint8_t sub_type, ...){
    void * result = NULL;
    va_list args;
    ZNLinkedList_t * e;
    HandlerFunc_t  * h;
    ZMEHandlerMapper * p_mapper;
    byte *	 base_addr;
    base_addr = NULL;
    p_mapper = NULL;
    for(e=g_syshandler_map; e; e=e->next){
         p_mapper = NULL;
         h = (HandlerFunc_t *) e->data;
        //  #ifdef LOGGING_DBG
        //  LOGGING_UART.print("*** PMAPPER T1: ");
        //  LOGGING_UART.print(h->main_type);
        //  LOGGING_UART.print(" T2: ");
        //  LOGGING_UART.print(type);
        //  LOGGING_UART.print(" H: ");
        //  LOGGING_UART.println((uint32_t)h->code_offset, HEX);
        //  #endif
         if(h->main_type == ZUNO_HANDLER_OBJ_MAPPER){
            p_mapper = (ZMEHandlerMapper*)h->code_offset;
            // #ifdef LOGGING_DBG
            // LOGGING_UART.print("*** PMAPPER ADDR: ");
            // LOGGING_UART.println((uint32_t)p_mapper, HEX);
            // #endif
            if(p_mapper == NULL)
                continue;
            bool bs = p_mapper->isEventSupported(type);
            // #ifdef LOGGING_DBG
            // LOGGING_UART.print("*** BS: ");
            // LOGGING_UART.println(bs);
            // #endif
            if(!bs)
                continue;
         } else {
            if(h->main_type != type)
                continue;
            if((h->sub_type != sub_type) && (h->sub_type != 0xFF)) // 0xFF is a "wild card"
                continue;
            base_addr = (byte*)h->code_offset;
            if(base_addr < (( byte *)&g_zuno_codeheader)){
                base_addr = NULL;
                #ifdef LOGGING_DBG
                LOGGING_UART.print("*** WRONG HANDLER ");
                LOGGING_UART.print(type);
                LOGGING_UART.print(" ADDR:");
                LOGGING_UART.println((uint32_t)base_addr, HEX);
                #endif
                continue;
            }
         }
         switch(type){
            case ZUNO_HANDLER_SYSTIMER:{
                    if (base_addr == NULL && p_mapper == NULL)
                        return (result);
                    va_start (args, sub_type);
                    uint32_t ticks = va_arg(args,uint32_t);
                    if(p_mapper)
                        p_mapper->handleSysTimer(ticks);
                    else
                        ((zuno_user_systimer_handler*)(base_addr))(ticks);
                    va_end (args);
                    }
                    break;
            case ZUNO_HANDLER_REPORT:
                    if (base_addr == NULL)
                        return (result);
                    va_start (args, sub_type);
                    ((zuno_user_zuno_handler_report*)(base_addr))(va_arg(args,ReportAuxData_t *));
                    va_end (args);
                    break;
            case ZUNO_HANDLER_SYSEVENT: {
                    if (base_addr == NULL && p_mapper == NULL)
                        return (result);
                    va_start (args, sub_type);
                    ZUNOSysEvent_t* ev = va_arg(args,ZUNOSysEvent_t*);
                    if(p_mapper)
                        p_mapper->handleSysEvent(ev);
                    else
                        ((zuno_user_sysevent_handler*)(base_addr))(ev);
                    va_end (args);
                    }
                    break;
            case ZUNO_HANDLER_IRQ:{
                    if (base_addr == NULL && p_mapper == NULL)
                        return (result);
                    va_start (args, sub_type);
                    IOQueueMsg_t * p_msg = va_arg(args,IOQueueMsg_t *);
                    if(p_mapper)
                        p_mapper->handleSysIRQ(p_msg);
                    else
                        ((zuno_irq_handler*)(base_addr))((void*)p_msg->param);
                    va_end (args);
                    }
                    break;
            case ZUNO_HANDLER_EXTINT:{
                    if (base_addr == NULL && p_mapper == NULL)
                        return (result);
                    va_start (args, sub_type);
                    uint8_t pin_index = (uint8_t)va_arg(args,size_t);
                    if(p_mapper)
                        p_mapper->handleExtInt(pin_index);
                    else
                        ((zuno_void_handler_ext_int*)(base_addr))(pin_index);
                    va_end (args);
                    }
                    break;
            case ZUNO_HANDLER_GPT:
            case ZUNO_HANDLER_SLEEP:
            case ZUNO_HANDLER_WUP:
            case ZUNO_HANDLER_NOTIFICATON_TIME_STAMP:
                    if (base_addr == NULL && p_mapper == NULL)
                        return (result);
                    if(p_mapper) {
                        if(type == ZUNO_HANDLER_SLEEP)
                            p_mapper->handleSysSleep();
                        else 
                            p_mapper->handleSysWake();
                    }
                    else
                        ((zuno_void_handler*)(base_addr))();
                    break;
            case ZUNO_HANDLER_ZW_CFG:
                    if (base_addr == NULL)
                        return (result);
                    va_start (args, sub_type);
                    ((zuno_configuartionhandler_t*)(base_addr))((uint8_t)va_arg(args,uint32_t), va_arg(args,uint32_t));
                    va_end (args);
                    break;
            case ZUNO_HANDLER_ZW_BATTERY:
                    if (base_addr == NULL)
                        return (result);
                    result = (void*)(((zuno_battery_handler_t*)(base_addr))());
                    break;
            default:
                #ifdef LOGGING_DBG
                LOGGING_UART.print("(!) zunoSysHandlerCall: Unknown type:");
                LOGGING_UART.println(type);
                #endif
                break;
        }
    }
    return result;
}