 #include "ZMEButtons.h"
 #include "Debug.h"
 #include "ZWCCCentralScene.h"
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
    if (d == NULL)
        return (true);
    return !isChannelPressed(channel, d);
}
bool ZMEVirtButtons::isIdled(uint8_t channel) {
    ZMEButtonState_t               *s;
    uint8_t                         st;

    zunoEnterCritical();
    s  = _extractChannelState(channel);
    if (s != NULL)
        st = s->state;
    else
        st = ZMEBUTTON_STATE_IDLE;
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
    innerProcessChannelEvent(s, type);
    if(_ext_handler != NULL){
        _ext_handler(s->channel, (ZMEButtonEventType)type);
    }
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
    else
        d = NULL;
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
    #ifdef WITH_CC_CENTRAL_SCENE
    if(flags & ZMEBUTTON_PIN_FLAG_CENTRAL_SCENE){
        uint32_t mask = (CENTRAL_SCENE_KEY_RELEASED_MASK | CENTRAL_SCENE_KEY_HELD_DOWN_MASK | CENTRAL_SCENE_KEY_PRESSED_1_MASK);
        for(int i=0;i<_max_clicks-1;i++){
            mask |= (1 << (CENTRAL_SCENE_KEY_PRESSED_2 + i));
        }
        zuno_CCCentralSceneAdd(pin_number, mask);
    }
    #endif
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
uint8_t _mapBtnEvent2CSEvent(uint8_t event){
    if((event >= ZMEBUTTON_EVENT_DOUBLE_CLICK) && 
       (event <= (ZMEBUTTON_EVENT_DOUBLE_CLICK+3))) {
            return CENTRAL_SCENE_KEY_PRESSED_2 + (event - ZMEBUTTON_EVENT_DOUBLE_CLICK);
    }
    switch(event){
        case ZMEBUTTON_EVENT_CLICK:
            return CENTRAL_SCENE_KEY_PRESSED_1;
        case ZMEBUTTON_EVENT_HOLD:
            return CENTRAL_SCENE_KEY_HELD_DOWN;
        case ZMEBUTTON_EVENT_HOLD_RELEASE:
            return CENTRAL_SCENE_KEY_RELEASED;
    }
    return 0xFF;
}
void ZMEGPIOButtons::innerProcessChannelEvent(ZMEButtonState_t * s, uint8_t type){
    (void)s;
    (void)type;
    #ifdef WITH_CC_CENTRAL_SCENE
    #pragma message "ZMEButtons library built with CentralScene suppoort"
    if((*((uint32_t*)s->custom_data)) & ZMEBUTTON_PIN_FLAG_CENTRAL_SCENE){
        uint8_t mapped_event = _mapBtnEvent2CSEvent(type);
        #if defined(LOGGING_DBG) &&ZME_BUTTONS_DBG
        LOGGING_UART.print("***CentralScene mapper ZE:");
        LOGGING_UART.print(type);
        LOGGING_UART.print(" CSE:");
        LOGGING_UART.println(mapped_event);
        #endif
        if(mapped_event != 0xFF){
            zuno_CCCentralSceneReport(s->channel, mapped_event);
        }
    }
    #endif
}

// ------------------------------------------------------------------------------
// class DimmableSwitchBtnController 
// ------------------------------------------------------------------------------
DimmableSwitchBtnController::DimmableSwitchBtnController( uint8_t btn_pin_number, 
                              uint8_t channel_number,
                              uint8_t * switch_level) {
      _btn_pin_number = btn_pin_number;
      _channel_number = channel_number;
      _plevel = switch_level;
}
void DimmableSwitchBtnController::begin(uint8_t btn_flags){
    ZBtn.addButton(_btn_pin_number, btn_flags);
}
void DimmableSwitchBtnController::end(){
    ZBtn.removeButton(_btn_pin_number);
}
void DimmableSwitchBtnController::process(){
    if (ZBtn.isSingleClick(_btn_pin_number)) {
         *_plevel =  (*_plevel > 0) ? 0 : 99; 
        zunoSendReport(_channel_number);
    }
    if (ZBtn.isHolded(_btn_pin_number)) {
        _dim_up = (*_plevel != 99);
        _start_level = *_plevel;
    }
    if (ZBtn.isHolding(_btn_pin_number)) {
        _dimLevel(_dim_up);
        if(_dimDiff(_start_level, _dim_up) > 10){
           _start_level = *_plevel;
           zunoSendReport(_channel_number);
        }
    }
    if (ZBtn.isHoldReleased(_btn_pin_number)) {
         zunoSendReport(_channel_number);
    }
}
void DimmableSwitchBtnController::_dimLevel(bool up){
    int level = *_plevel;
    if(up){
        level += 2;
        if(level > 99)
            level = 99;
    } else {
        level -= 2;
        if(level < 0)
            level = 0;
    }
    *_plevel = (uint8_t)level;
}
uint8_t DimmableSwitchBtnController::_dimDiff(uint8_t start_level, bool up){
    return (up) ? *_plevel - start_level : start_level - *_plevel;
}
ZMEGPIOButtons ZBtn;