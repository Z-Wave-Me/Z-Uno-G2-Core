#include "Arduino.h"
#include "LinkedList.h"
#include "Debug.h"
#include "LLCore.h"
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
    for(e=g_syshandler_map; e; e=e->next){
         h = (HandlerFunc_t *) e->data;
         if(h->main_type != type)
            continue;
         if((h->sub_type != sub_type) && (h->sub_type != 0xFF)) // 0xFF is a "wild card"
            continue;
         
         byte *	 base_addr = (byte*)h->code_offset;
         if(base_addr < (( byte *)&g_zuno_codeheader)){
            #ifdef LOGGING_DBG
            LOGGING_UART.print("*** WRONG HANDLER ");
            LOGGING_UART.print(type);
            LOGGING_UART.print(" ADDR:");
            LOGGING_UART.println((uint32_t)base_addr, HEX);
            #endif
            continue;
         }
         switch(type){
            case ZUNO_HANDLER_SYSTIMER:
                    va_start (args, sub_type);
                    ((zuno_user_systimer_handler*)(base_addr))(va_arg(args,uint32_t));
                    va_end (args);
                    break;
            case ZUNO_HANDLER_REPORT:
                    va_start (args, sub_type);
                    ((zuno_user_zuno_handler_report*)(base_addr))(va_arg(args,ReportAuxData_t *));
                    va_end (args);
                    break;
            case ZUNO_HANDLER_SYSEVENT:
                    va_start (args, sub_type);
                    ((zuno_user_sysevent_handler*)(base_addr))(va_arg(args,ZUNOSysEvent_t*));
                    va_end (args);
                    break;
            case ZUNO_HANDLER_IRQ:{
                    //return NULL;
                    va_start (args, sub_type);
                    IOQueueMsg_t * p_msg = va_arg(args,IOQueueMsg_t *);
                    ((zuno_irq_handler*)(base_addr))((void*)p_msg->param);
                    va_end (args);
                    }
                    break;
            case ZUNO_HANDLER_EXTINT:
                    //return NULL;
                    va_start (args, sub_type);
                    ((zuno_void_handler_ext_int*)(base_addr))((uint8_t)va_arg(args,size_t));
                    va_end (args);
                    break;
            case ZUNO_HANDLER_GPT:
            case ZUNO_HANDLER_SLEEP:
            case ZUNO_HANDLER_WUP:
            case ZUNO_HANDLER_NOTIFICATON_TIME_STAMP:
                    ((zuno_void_handler*)(base_addr))();
                    break;
            case ZUNO_HANDLER_ZW_CFG:
                    va_start (args, sub_type);
                    ((zuno_configuartionhandler_t*)(base_addr))((uint8_t)va_arg(args,uint32_t), va_arg(args,uint32_t));
                    va_end (args);
                    break;
            case ZUNO_HANDLER_ZW_BATTERY:
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