/*
  Packet Trace Interface example
  ZUno v2 has builtin interface of modem that shows all sending ang receiving radio packages
  You can enable it in any progect to see the Z-Wave trafic around your device.
  To use this interface you need an extra license that you can purcase on z-wave.me site.
  
  Connect Z-Uno to your PC and start in terminal:
  $ zme_make tracer -d <YOUR_ZUNO_COM/tty port>
 */
ZUNO_ENABLE(LOGGING_DBG); 
#define PTI_PIN         TX2     // TX2 is default USB CDC pin
                                // You are able to sketch ANY ZUno pin
#define PTI_BAUDRATE    230400L // The minimal baud is 230400
                                // The maximum baud is 1.6MBit
void setup() {                  
  Serial0.begin(115200); 
  delay(1000);
  Serial0.print("\n\nEnable Packet Trace Interface on pin#");
  Serial0.print(PTI_PIN);
  Serial0.print(" BAUD:");
  Serial0.print(PTI_BAUDRATE);
  Serial0.print(" ");
  if(zunoPTIConfigUART(PTI_PIN, PTI_BAUDRATE)){
    Serial0.println("[Done]");
  } else {
    Serial0.println("[Failed]");
  }
}
// Just an empty loop function
void loop() {   
}

