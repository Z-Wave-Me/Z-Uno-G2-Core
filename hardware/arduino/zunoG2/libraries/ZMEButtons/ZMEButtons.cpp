 #include "ZMEButtons.h"
 #include "Debug.h"
 #ifndef ZME_BUTTONS_DBG
 #define ZME_BUTTONS_DBG 0
 #endif
 ZMEVirtButtons::ZMEVirtButtons(uint8_t  max_clicks,
                       uint32_t debounce_interval, 
                       uint32_t multiclick_interval,
                       uint32_t hold_interval){
    button_states = NULL;
    _max_clicks = max_clicks;
    _debounce_interval = debounce_interval;
    _multi_click_interval = multiclick_interval;
    _hold_click_interval = hold_interval;
    _ext_handler = NULL;
}
bool ZMEVirtButtons::removeButton(uint8_t channel){
    zunoEnterCritical();
    ZMEButtonState_t * s  = _extractChannelState(channel);
    zunoExitCritical();
    if(s!=NULL){
        znllRemoveP(&button_states, (void*)s);
        if(s->custom_data != NULL)
            free(s->custom_data);
        free(s);
        return true;
    }
    return false;
}

bool ZMEVirtButtons::isReleased(uint8_t channel) {
    void * d = extractCustomData(channel);
    return !isChannelPressed(channel, d);
}
bool ZMEVirtButtons::isIdled(uint8_t channel) {
    zunoEnterCritical();
    ZMEButtonState_t * s  = _extractChannelState(channel);
    uint8_t st = s->state;
    zunoExitCritical();
    return st == ZMEBUTTON_STATE_IDLE;
}
bool ZMEVirtButtons::isIdled() {
    bool ret = true;
    zunoEnterCritical();
    ZMEButtonState_t * s = NULL;
    ZNLinkedList_t* e;
    for(e=button_states;e;e=e->next) {
        s = (ZMEButtonState_t *)e->data;
        if(s->state != ZMEBUTTON_STATE_IDLE) {
            ret = false;
            break;
        }
    }
    zunoExitCritical();
    return ret;
}
bool ZMEVirtButtons::_process(bool pressed, ZMEButtonState_t * s){
    //#if defined(LOGGING_DBG) && ZME_BUTTONS_DBG
    uint32_t dbg_start_state = s->state;
	//#endif
    switch(s->state){
        case ZMEBUTTON_STATE_IDLE:
            if(pressed){
                s->state = ZMEBUTTON_STATE_DEBOUNCE;
                s->state_timeout = millis() + _debounce_interval;
                s->num_clicks = 0;
            }
            break;
        case ZMEBUTTON_STATE_DEBOUNCE:
            if(millis() > s->state_timeout){
                s->num_clicks++;
                s->state = ZMEBUTTON_STATE_PRESSED;
                s->state_timeout = millis() + _hold_click_interval;
            }
            if(!pressed){
                if(s->num_clicks == 0){
                    s->state = ZMEBUTTON_STATE_IDLE;
                    break;
                }
                _pushEvent(s, ((uint8_t)ZMEBUTTON_EVENT_CLICK)+s->num_clicks-1);
                break;
            }            
            break;
        case ZMEBUTTON_STATE_PRESSED:
            if(millis() > s->state_timeout){
                _pushEvent(s, ((uint8_t)ZMEBUTTON_EVENT_HOLD));
                s->state = ZMEBUTTON_STATE_HOLD;
                s->last_hold_start = millis();
            }
            if(!pressed){
                if(s->num_clicks >= _max_clicks){
                    s->state = ZMEBUTTON_STATE_IDLE;
                    _pushEvent(s, ((uint8_t)ZMEBUTTON_EVENT_CLICK)+s->num_clicks-1);
                    break;
                }
                s->state = ZMEBUTTON_STATE_WAIT_MULTI;
                s->state_timeout = millis() + _multi_click_interval;
                break;
            }
            break;
        case ZMEBUTTON_STATE_WAIT_MULTI:
            if(millis() > s->state_timeout){
                s->state = ZMEBUTTON_STATE_IDLE;
                _pushEvent(s, ((uint8_t)ZMEBUTTON_EVENT_CLICK)+s->num_clicks-1);
            }
            if(pressed){
                s->state = ZMEBUTTON_STATE_DEBOUNCE;
                s->state_timeout = millis() + _debounce_interval;
                break;
            }
            break;
        case ZMEBUTTON_STATE_HOLD:
            if(!pressed){
                s->last_hold_start = millis()-s->last_hold_start + _hold_click_interval;
                s->state = ZMEBUTTON_STATE_IDLE;
                _pushEvent(s, ((uint8_t)ZMEBUTTON_EVENT_HOLD_RELEASE));
                break;
            }
            break;
    }
    #if defined(LOGGING_DBG) &&ZME_BUTTONS_DBG
    if(dbg_start_state != s->state){
        LOGGING_UART.print("*** BTN id:");
        LOGGING_UART.print(s->channel);
        LOGGING_UART.print(" Press:");
        LOGGING_UART.print(pressed);
        LOGGING_UART.print(" Prev:");
        LOGGING_UART.print(dbg_start_state);
        LOGGING_UART.print(" Next:");
        LOGGING_UART.println(s->state);
    }
    #endif
    return (s->state != dbg_start_state);
}
bool  ZMEVirtButtons::_popEvent(uint8_t channel, uint8_t type) {
    uint8_t  oldest_event_i = 0xFF;
    uint32_t oldest_event_ts = 0;
    zunoEnterCritical();
    ZMEButtonState_t * s  = _extractChannelState(channel);
    if(s != NULL){
        for(int i=0;i<ZME_BUTTONS_MAX_EVENTS;i++){
            if(s->event[i].type != type)
                continue;
            if((oldest_event_ts == 0) || (oldest_event_ts > s->event[i].timestamp)){
                oldest_event_i = i;
                oldest_event_ts = s->event[i].timestamp;
            }
        }
        if(oldest_event_i != 0xFF){
            s->event[oldest_event_i].type = ZMEBUTTON_EVENT_NONE; // remove an event
        }
    }
    zunoExitCritical();
    return oldest_event_i != 0xFF;
}
void  ZMEVirtButtons::_pushEvent(ZMEButtonState_t * s, uint8_t type) {
    uint8_t  oldest_event_i = 0xFF;
    uint32_t oldest_event_ts = 0;
    for(int i=0;i<ZME_BUTTONS_MAX_EVENTS;i++){
        if(s->event[i].type == ZMEBUTTON_EVENT_NONE){
            oldest_event_i = i;
                break;
        }
        if((oldest_event_ts == 0) || (oldest_event_ts > s->event[i].timestamp)){
            oldest_event_i = i;
            oldest_event_ts = s->event[i].timestamp;
        }
    }
    if(oldest_event_i != 0xFF){
        s->event[oldest_event_i].type = type; // store an event
    }

}
void ZMEVirtButtons::clearEvents(uint8_t channel) {
    zunoEnterCritical();
    ZMEButtonState_t * s  = _extractChannelState(channel);
    if(s != NULL){
        memset(s->event, 0, sizeof(s->event));
    }
    zunoExitCritical();
}
void ZMEVirtButtons::clearEvents() {
    zunoEnterCritical();
    ZMEButtonState_t * s = NULL;
    ZNLinkedList_t* e;
    for(e=button_states;e;e=e->next){
        s = (ZMEButtonState_t *)e->data;
        memset(s->event, 0, sizeof(s->event));
    }
    zunoExitCritical();
}
void ZMEVirtButtons::poll(){
    zunoEnterCritical();
    ZMEButtonState_t * s = NULL;
    ZNLinkedList_t* e;
    for(e=button_states;e;e=e->next){
        s = (ZMEButtonState_t *)e->data;
        bool pressed = isChannelPressed(s->channel, s->custom_data);
        (void)pressed;
        _process(pressed, s);
    }
    zunoExitCritical();
}
ZMEButtonState_t *  ZMEVirtButtons::_extractChannelState(uint8_t channel){
    ZMEButtonState_t * s = NULL;
    ZNLinkedList_t* e;
    for(e=button_states;e;e=e->next){
        s = (ZMEButtonState_t *)e->data;
        if(s->channel == channel)
            break;
    }
    if(e == NULL)
        return NULL;
    return s;
}
bool ZMEVirtButtons::addButton(uint8_t channel, void * custom_data){

    ZMEButtonState_t * s = (ZMEButtonState_t *)malloc(sizeof(ZMEButtonState_t));
    if(s == NULL)
        return false;
    memset(s, 0, sizeof(ZMEButtonState_t));
    s->channel = channel;
    s->custom_data = custom_data;
    #if defined(LOGGING_DBG) &&ZME_BUTTONS_DBG
    LOGGING_UART.print("*** BTNV ADD:");
    LOGGING_UART.print(channel);
    LOGGING_UART.print(" D:");
    LOGGING_UART.print((uint32_t)s->custom_data, HEX);
    #endif
    if(znllPushBack(&button_states, s))
        return true;
    free(s);
    return false;
}
bool ZMEVirtButtons::isHolding(uint8_t channel){
    bool rt = false;
    zunoEnterCritical();
    ZMEButtonState_t * s  = _extractChannelState(channel);
    if(s != NULL){
        rt = (s->state == ZMEBUTTON_STATE_HOLD);
    }
    zunoExitCritical();
    return rt;
}
uint32_t ZMEVirtButtons::currentHoldTime(uint8_t channel){
    uint32_t rt = 0;
    zunoEnterCritical();
    ZMEButtonState_t * s  = _extractChannelState(channel);
    if(s != NULL){
        if(s->state == ZMEBUTTON_STATE_HOLD)
            rt = millis() - s->last_hold_start + _hold_click_interval;
        else
            rt = s->last_hold_start;
    }
    zunoExitCritical();
    return rt;
}
void * ZMEVirtButtons::extractCustomData(uint8_t channel){
    void * d;
    zunoEnterCritical();
    ZMEButtonState_t * s = _extractChannelState(channel);
    if(s!=NULL){
        d = s->custom_data;
    }
    zunoExitCritical();
    return d;
}
// ZMEPinButtons
ZMEGPIOButtons::ZMEGPIOButtons(
                       uint8_t  max_clicks,
                       uint32_t debounce_interval, 
                       uint32_t multiclick_interval,
                       uint32_t hold_interval,
                       bool enableHandling):
                       ZMEVirtButtons(max_clicks, debounce_interval, multiclick_interval, hold_interval),
                       ZMEHandlerMapper(SYS_HANLER_MAPPER_TIMER | SYS_HANLER_MAPPER_WAKE) {

    _handling_enable = enableHandling;
}
static void _DummyIntHandler() {
}
bool ZMEGPIOButtons::addButton(uint8_t pin_number, uint32_t flags) {
    #if defined(LOGGING_DBG) &&ZME_BUTTONS_DBG
    LOGGING_UART.print("*** BTNPIN SETUP:");
    LOGGING_UART.print(pin_number);
    LOGGING_UART.print(" F:");
    LOGGING_UART.print(flags, HEX);
    #endif
    uint32_t * btn_data = (uint32_t *)malloc(sizeof(uint32_t));
    if(btn_data == NULL)
        return false;
    *btn_data = flags;
    if(flags & ZMEBUTTON_PIN_FLAG_PULL) {
        if(flags & ZMEBUTTON_PIN_FLAG_FILTER) {
             if(flags & ZMEBUTTON_PIN_FLAG_INVERTED) {
                #if defined(LOGGING_DBG) &&ZME_BUTTONS_DBG
                LOGGING_UART.println("PULLUP_FILTER");
                #endif
                pinMode(pin_number, INPUT_PULLUP_FILTER);
             } else {
                #if defined(LOGGING_DBG) &&ZME_BUTTONS_DBG
                LOGGING_UART.println("PULLDOWN_FILTER");
                #endif
                pinMode(pin_number, INPUT_PULLDOWN_FILTER);
             }
        } else {
             if(flags & ZMEBUTTON_PIN_FLAG_INVERTED) {
                #if defined(LOGGING_DBG) &&ZME_BUTTONS_DBG
                LOGGING_UART.println("PULLUP");
                #endif
                pinMode(pin_number, INPUT_PULLUP);
             } else {
                #if defined(LOGGING_DBG) &&ZME_BUTTONS_DBG
                LOGGING_UART.println("PULLDOWN");
                #endif
                pinMode(pin_number, INPUT_PULLDOWN);
             }
        }
    } else {
        #if defined(LOGGING_DBG) &&ZME_BUTTONS_DBG
        LOGGING_UART.println("INPUT");
        #endif
        pinMode(pin_number, INPUT);
    }
    if(flags & ZMEBUTTON_PIN_FLAG_EM2_WAKE) {
        if(attachInterrupt(pin_number, _DummyIntHandler, CHANGE) != 1){
            #if defined(LOGGING_DBG) &&ZME_BUTTONS_DBG
            LOGGING_UART.print("CAN'T BIND BUTTON PIN:");
            LOGGING_UART.print(pin_number);
            LOGGING_UART.println("TO INTTERRUPT!");
            #endif
            free(btn_data);
            return false;
        }
    }
    return ZMEVirtButtons::addButton(pin_number, (void*) btn_data);
}
bool ZMEGPIOButtons::isChannelPressed(uint8_t channel, void  * custom_data) {
    uint32_t * bd = (uint32_t *)custom_data;
    bool p = (digitalRead(channel)  != 0);
    if(*bd & ZMEBUTTON_PIN_FLAG_INVERTED)
        p = !p;
    return p;
}
void ZMEGPIOButtons::handleSysTimer(uint32_t ticks) {
    (void) ticks;
    if(!_handling_enable)
        return;
    poll();
}
void ZMEGPIOButtons::handleSysWake(){
    if(!_handling_enable)
        return;
    poll();
    #if defined(LOGGING_DBG) &&ZME_BUTTONS_DBG
    LOGGING_UART.println("BTN:WAKEPOLL");
    #endif
}

ZMEGPIOButtons ZBtn;