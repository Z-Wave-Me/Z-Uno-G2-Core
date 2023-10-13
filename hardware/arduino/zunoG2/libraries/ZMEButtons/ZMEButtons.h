#ifndef ZME_BUTTONS
#define ZME_BUTTONS
#include "LinkedList.h"
#include "Arduino.h"
#include "HandlerMapper.h"


#define ZME_BUTTONS_MAX_EVENTS  5
#define ZME_BUTTONS_INVALID_CHANNEL 0xFF
#define ZME_BUTTONS_DEFAULT_DEBOUNCE 20
#define ZME_BUTTONS_DEFAULT_MULTICLICK 200
#define ZME_BUTTONS_DEFAULT_HOLDINTERVAL 700

#define ZME_BUTTONS_MAX_PULSE_LIST  16
#define ZME_BUTTONS_MAX_EVENT_LIST  8
#define ZME_BUTTONS_PULSE_EVENT_TIME_BITS  30
#define ZME_BUTTONS_PULSE_EVENT_TIME_MASK  ((1<<ZME_BUTTONS_PULSE_EVENT_TIME_BITS)-1)
#define ZME_BUTTONS_PULSE_EVENT_TRIG_BIT   (1<<(ZME_BUTTONS_PULSE_EVENT_TIME_BITS+1))

#define ZME_PINBUTTON_FLAG_INVERTED 0x01
enum ZMEButtonEventType{
   ZMEBUTTON_EVENT_NONE,
   ZMEBUTTON_EVENT_CLICK,
   ZMEBUTTON_EVENT_DOUBLE_CLICK,
   ZMEBUTTON_EVENT_TRIPLE_CLICK,
   ZMEBUTTON_EVENT_HOLD = ZMEBUTTON_EVENT_CLICK+10,
   ZMEBUTTON_EVENT_HOLD_RELEASE = ZMEBUTTON_EVENT_HOLD+1
};
enum ZMEButtonLocalState{
   ZMEBUTTON_STATE_IDLE,
   ZMEBUTTON_STATE_DEBOUNCE,
   ZMEBUTTON_STATE_PRESSED,
   ZMEBUTTON_STATE_WAIT_MULTI,
   ZMEBUTTON_STATE_HOLD
};
typedef struct ZMEButtonEvent_s{
    uint32_t  timestamp;
    uint8_t  type;
}ZMEButtonEven_t;
typedef struct ZMEButtonState_s{
    uint8_t           channel;
    void            * custom_data;
    ZMEButtonLocalState   state;
    uint32_t              state_timeout;
    uint8_t               num_clicks;
    ZMEButtonEven_t   event[ZME_BUTTONS_MAX_EVENTS];
}ZMEButtonState_t;
typedef void (*ZMEButtonHandlerFunc_t)(uint8_t channel, ZMEButtonEventType event);

class ZMEVirtButtons{
    public:
        ZMEVirtButtons(uint8_t  max_clicks,
                       uint32_t debounce_interval, 
                       uint32_t multiclick_interval,
                       uint32_t hold_interval);
    virtual bool removeButton(uint8_t channel);
    // Button events
    bool isSingleClick(uint8_t channel) { return _popEvent(channel, ZMEBUTTON_EVENT_CLICK); };
    bool isDoubleClick(uint8_t channel) { return _popEvent(channel, ZMEBUTTON_EVENT_DOUBLE_CLICK);};
    bool isTripleClick(uint8_t channel) { return _popEvent(channel, ZMEBUTTON_EVENT_TRIPLE_CLICK);};
    bool isNClick(uint8_t channel, uint8_t n) {return _popEvent(channel, ZMEBUTTON_EVENT_CLICK+n-1);};
    bool isHolded(uint8_t channel) { return _popEvent(channel, ZMEBUTTON_EVENT_HOLD);};
    bool isHoldReleased(uint8_t channel) { return _popEvent(channel, ZMEBUTTON_EVENT_HOLD_RELEASE);};
    
    bool isReleased(uint8_t channel);
    bool isIdled(uint8_t channel);
    bool isIdled();
    void clearEvents(uint8_t channel);
    void clearEvents();
    // External polling/processing
    bool process(uint8_t channel);
    void poll();
    // External event handling using callback-function
    void setEventCallback(ZMEButtonHandlerFunc_t f){_ext_handler = f;};
    // Precise tweak
    void setDebounceInterval(uint32_t interval){_debounce_interval = interval; };
    void setMultiClickInterval(uint32_t interval){_multi_click_interval = interval; };
    void setHoldInterval(uint32_t interval){_hold_click_interval = interval; };
    void setMaxMultiClickCount(uint8_t clicks){_max_clicks = clicks;};
    protected:
        bool _process(bool pressed, ZMEButtonState_t * s);
        virtual bool isChannelPressed(uint8_t channel, void  * custom_data)=0;
        virtual bool addButton(uint8_t channel, void * custom_data);
        void * extractCustomData(uint8_t channel);
    private:
        bool                _popEvent(uint8_t channel, uint8_t type);
        static void         _pushEvent(ZMEButtonState_t * s, uint8_t type);
        ZMEButtonState_t *  _extractChannelState(uint8_t channel);
    private:
        uint8_t             _max_clicks;
        ZNLinkedList_t     * button_states;
        ZMEButtonHandlerFunc_t _ext_handler;
        uint32_t _debounce_interval;
        uint32_t _multi_click_interval; 
        uint32_t _hold_click_interval;   
};
enum ZMEPinButtonHandlingType{
   ZMEBUTTON_HANDLE_NONE,
   ZMEBUTTON_HANDLE_TIMERPOLL,
   ZMEBUTTON_HANDLE_INT,
   ZMEBUTTON_HANDLE_AUTO
};
enum ZMEPinButtonFlags{
   ZMEBUTTON_PIN_FLAG_INVERTED=1,
   ZMEBUTTON_PIN_FLAG_PULL=2,
   ZMEBUTTON_PIN_FLAG_FILTER=4,
   ZMEBUTTON_PIN_FLAG_EM2_WAKE=8
};
#define MAX_IRQ_VECPIN_MAPPING 16
#define DEFAULT_BTN_FLAGS (ZMEBUTTON_PIN_FLAG_INVERTED | ZMEBUTTON_PIN_FLAG_PULL| ZMEBUTTON_PIN_FLAG_FILTER)
#define DEFAULT_BTN_FLAGS_EM2 (DEFAULT_BTN_FLAGS | ZMEBUTTON_PIN_FLAG_EM2_WAKE)
#ifndef DEFAULT_BTN_HANDLE_MODE 
#define DEFAULT_BTN_HANDLE_MODE ZMEBUTTON_HANDLE_AUTO
#endif

class ZMEGPIOButtons: public ZMEVirtButtons, protected ZMEHandlerMapper {
    public:
        ZMEGPIOButtons(ZMEPinButtonHandlingType handling_type = ZMEBUTTON_HANDLE_AUTO,
                       uint8_t  max_clicks=3,
                       uint32_t debounce_interval=ZME_BUTTONS_DEFAULT_DEBOUNCE, 
                       uint32_t multiclick_interval=ZME_BUTTONS_DEFAULT_MULTICLICK,
                       uint32_t hold_interval=ZME_BUTTONS_DEFAULT_HOLDINTERVAL);
        bool addButton(uint8_t pin_number, uint32_t flags=DEFAULT_BTN_FLAGS);
    protected:
        virtual bool isChannelPressed(uint8_t channel, void  * custom_data);
        virtual void handleSysTimer(uint32_t ticks);
        virtual void handleSysWake();
        ZMEPinButtonHandlingType _handle_type;

    
};
extern ZMEGPIOButtons ZBtn;
#endif // ZME_BUTTONS