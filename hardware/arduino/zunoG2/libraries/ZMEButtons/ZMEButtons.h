#ifndef ZME_BUTTONS
#define ZME_BUTTONS

#include "Arduino.h"
#include "LinkedList.h"
#include "HandlerMapper.h"


#define ZME_BUTTONS_MAX_EVENTS  5
#define ZME_BUTTONS_INVALID_CHANNEL 0xFF
#define ZME_BUTTONS_DEFAULT_DEBOUNCE 20
#define ZME_BUTTONS_DEFAULT_MULTICLICK 200
#define ZME_BUTTONS_DEFAULT_HOLDINTERVAL 500

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
    uint32_t              last_hold_start;
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
    bool isHolding(uint8_t channel);
    uint32_t currentHoldTime(uint8_t channel);
    bool isHoldReleased(uint8_t channel) { return _popEvent(channel, ZMEBUTTON_EVENT_HOLD_RELEASE);};
    bool isReleased(uint8_t channel);
    bool isIdled(uint8_t channel);
    bool isIdled();
    void clearEvents(uint8_t channel);
    void clearEvents();
    // External polling/processing
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
        virtual void innerProcessChannelEvent(ZMEButtonState_t * s, uint8_t type)=0;
        void * extractCustomData(uint8_t channel);
    private:
        bool         _popEvent(uint8_t channel, uint8_t type);
        void         _pushEvent(ZMEButtonState_t * s, uint8_t type);
        ZMEButtonState_t *  _extractChannelState(uint8_t channel);
    protected:
        uint8_t             _max_clicks;
    private:
        ZNLinkedList_t     * button_states;
        ZMEButtonHandlerFunc_t _ext_handler;
        uint32_t _debounce_interval;
        uint32_t _multi_click_interval; 
        uint32_t _hold_click_interval;   
};

enum ZMEPinButtonFlags{
   ZMEBUTTON_PIN_FLAG_INVERTED=0x01,
   ZMEBUTTON_PIN_FLAG_PULL=0x02,
   ZMEBUTTON_PIN_FLAG_FILTER=0x04,
   ZMEBUTTON_PIN_FLAG_EM2_WAKE=0x08,
   ZMEBUTTON_PIN_FLAG_CENTRAL_SCENE=0x10
};
#define MAX_IRQ_VECPIN_MAPPING 16
#define DEFAULT_BTN_FLAGS (ZMEBUTTON_PIN_FLAG_INVERTED | ZMEBUTTON_PIN_FLAG_PULL| ZMEBUTTON_PIN_FLAG_FILTER)
#define DEFAULT_BTN_FLAGS_EM2 (DEFAULT_BTN_FLAGS | ZMEBUTTON_PIN_FLAG_EM2_WAKE )
#ifndef DEFAULT_BTN_HANDLE_MODE 
#define DEFAULT_BTN_HANDLE_MODE ZMEBUTTON_HANDLE_AUTO
#endif

class ZMEGPIOButtons: public ZMEVirtButtons, protected ZMEHandlerMapper {
    public:
        ZMEGPIOButtons(uint8_t  max_clicks=3,
                       uint32_t debounce_interval=ZME_BUTTONS_DEFAULT_DEBOUNCE, 
                       uint32_t multiclick_interval=ZME_BUTTONS_DEFAULT_MULTICLICK,
                       uint32_t hold_interval=ZME_BUTTONS_DEFAULT_HOLDINTERVAL,
                       bool enableHandling = true);
        bool addButton(uint8_t pin_number, uint32_t flags=DEFAULT_BTN_FLAGS);
    protected:
        virtual bool isChannelPressed(uint8_t channel, void  * custom_data);
        virtual void handleSysTimer(uint32_t ticks);
        virtual void handleSysWake();
        virtual void innerProcessChannelEvent(ZMEButtonState_t * s, uint8_t type);
        bool _handling_enable;

    
};
class DimmableSwitchBtnController{
  public:
    DimmableSwitchBtnController( uint8_t btn_pin_number, 
                              uint8_t channel_number,
                              uint8_t * switch_level);
    void begin(uint8_t btn_flags = DEFAULT_BTN_FLAGS);
    void end();
    void process();
  private:
    uint8_t _btn_pin_number;
    uint8_t _channel_number;
    uint8_t * _plevel;
    bool    _dim_up;
    uint8_t _start_level;
    void _dimLevel(bool up);
    uint8_t _dimDiff(uint8_t start_level, bool up);
  
};
extern ZMEGPIOButtons ZBtn;
#endif // ZME_BUTTONS