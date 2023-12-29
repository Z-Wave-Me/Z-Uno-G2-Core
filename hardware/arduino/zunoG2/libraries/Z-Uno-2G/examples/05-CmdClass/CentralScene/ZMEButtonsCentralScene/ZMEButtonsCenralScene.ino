#include "ZMEButtons.h"
#include "Debug.h"
const uint8_t BTN_PINS[] = {7, 8, 9, 10};
ZUNO_ENABLE(//DBG_CONSOLE_PIN=0xFE
            LOGGING_DBG 
            DBG_CONSOLE_BAUDRATE=921600
            ZME_BUTTONS_DBG=1
            WITH_CC_CENTRAL_SCENE // для поддежки класса команд CentralScene
            );   

void setup(){
    for(unsigned int i=0;i<sizeof(BTN_PINS);i++)
         ZBtn.addButton(BTN_PINS[i], DEFAULT_BTN_FLAGS | ZMEBUTTON_PIN_FLAG_CENTRAL_SCENE);
    #ifdef LOGGING_DBG
    LOGGING_UART.print("--SETUP--");  
    #endif
}
void printBTNEvent(uint8_t btn_num, const char * event){
    #ifdef LOGGING_DBG
    LOGGING_UART.print(millis());
    LOGGING_UART.print(" BTN");
    LOGGING_UART.print(btn_num);
    LOGGING_UART.print(":");
    LOGGING_UART.println(event);
    #endif
}
void loop(){
    for(unsigned int i=0;i<sizeof(BTN_PINS);i++) {
        if(ZBtn.isSingleClick(BTN_PINS[i]))
            printBTNEvent(i, "click");  
        if(ZBtn.isDoubleClick(BTN_PINS[i]))
            printBTNEvent(i, "dclick"); 
        if(ZBtn.isTripleClick(BTN_PINS[i]))
            printBTNEvent(i, "tclick");  
        if(ZBtn.isHolded(BTN_PINS[i]))
            printBTNEvent(i, "holded");  
        if(ZBtn.isHoldReleased(BTN_PINS[i]))
            printBTNEvent(i, "hold_released");  
    }
    delay(100);
}