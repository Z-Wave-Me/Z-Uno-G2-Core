#ifndef ZME_HANDLER_MAPPER
#define ZME_HANDLER_MAPPER
#include "Arduino.h"

enum ZMEMapperType{
    SYS_HANDLER_MAPPER_TIMER = (1 << ZUNO_HANDLER_SYSTIMER),
    SYS_HANDLER_MAPPER_IRQ = (1 << ZUNO_HANDLER_IRQ),
    SYS_HANDLER_MAPPER_EVENT = (1 << ZUNO_HANDLER_SYSEVENT),
    SYS_HANDLER_MAPPER_SLEEP = (1 << ZUNO_HANDLER_SLEEP),
    SYS_HANDLER_MAPPER_WAKE = (1 << ZUNO_HANDLER_WUP),
    SYS_HANDLER_MAPPER_EXTINT = (1 << ZUNO_HANDLER_EXTINT)
};
class ZMEHandlerMapper {
    public:
        ZMEHandlerMapper(uint32_t event_map);
        virtual void handleSysTimer(uint32_t ticks){ (void)ticks;};
        virtual void handleSysIRQ(IOQueueMsg_t * irq_data){(void)irq_data;};
        virtual void handleExtInt(uint8_t pin){(void)pin;};
        virtual void handleSysEvent(ZUNOSysEvent_t* ev){(void)ev;};
        virtual void handleSysSleep(){};
        virtual void handleSysWake(){};
        bool isEventSupported(uint32_t event) const { return ((_event_map & (1 << event)) != 0);};
        virtual ~ZMEHandlerMapper();
    private:
        uint32_t _event_map;

};
#endif //ZME_HANDLER_MAPPER