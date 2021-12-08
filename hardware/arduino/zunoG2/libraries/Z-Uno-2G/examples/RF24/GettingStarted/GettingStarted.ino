/*
 * See documentation at https://nRF24.github.io/RF24
 * See License information at root directory of this library
 * Author: Brendan Doherty (2bndy5)
 */

/**
 * A simple example of sending data from 1 nRF24L01 transceiver to another.
 *
 * This example was written to be used on 2 devices acting as "nodes".
 * Use the Serial Monitor to change each node's behavior.
 */

#define MY_SERIAL		Serial
#define printf_P MY_SERIAL.printf

#include <SPI.h>
// #include "printf.h"
#include "RF24.h"

// instantiate an object for the nRF24L01 transceiver
RF24 radio(7, 8); // using pin 7 for the CE pin, and pin 8 for the CSN pin

// Let these addresses be used for the pair
uint8_t address[][6] = {"1Node", "2Node"};
// It is very helpful to think of an address as a path instead of as
// an identifying device destination

// to use different addresses on a pair of radios, we need a variable to
// uniquely identify which address this radio will use to transmit
bool radioNumber = 1; // 0 uses address[0] to transmit, 1 uses address[1] to transmit

// Used to control whether this node is sending or receiving
bool role = false;  // true = TX role, false = RX role

// For this example, we'll be using a payload containing
// a single float number that will be incremented
// on every successful transmission
float payload = 0.0;

void setup() {

  MY_SERIAL.begin(115200);

  // initialize the transceiver on the SPI bus
  if (!radio.begin()) {
    MY_SERIAL.println(F("radio hardware is not responding!!"));
    while (1) {} // hold in infinite loop
    delay(1);
  }

  // print example's introductory prompt
  MY_SERIAL.println(F("RF24/examples/GettingStarted"));

  // To set the radioNumber via the Serial monitor on startup
  MY_SERIAL.println(F("Which radio is this? Enter '0' or '1'. Defaults to '0'"));
  while (!MY_SERIAL.available()) {
    // wait for user input
    delay(1);
  }
  char input = MY_SERIAL.parseInt();
  radioNumber = input == 1;
  MY_SERIAL.print(F("radioNumber = "));
  MY_SERIAL.println((int)radioNumber);

  // role variable is hardcoded to RX behavior, inform the user of this
  MY_SERIAL.println(F("*** PRESS 'T' to begin transmitting to the other node"));

  // Set the PA Level low to try preventing power supply related problems
  // because these examples are likely run with nodes in close proximity to
  // each other.
  radio.setPALevel(RF24_PA_LOW);  // RF24_PA_MAX is default.

  // save on transmission time by setting the radio to only transmit the
  // number of bytes we need to transmit a float
  radio.setPayloadSize(sizeof(payload)); // float datatype occupies 4 bytes

  // set the TX address of the RX node into the TX pipe
  radio.openWritingPipe(address[radioNumber]);     // always uses pipe 0

  // set the RX address of the TX node into a RX pipe
  radio.openReadingPipe(1, address[!radioNumber]); // using pipe 1

  // additional setup specific to the node's role
  if (role) {
    radio.stopListening();  // put radio in TX mode
  } else {
    radio.startListening(); // put radio in RX mode
  }

  // For debugging info
  // printf_begin();             // needed only once for printing details
  // radio.printDetails();       // (smaller) function that prints raw register values
  // radio.printPrettyDetails(); // (larger) function that prints human readable data

} // setup

void loop() {

  if (role) {
    // This device is a TX node

    unsigned long start_timer = micros();                    // start the timer
    bool report = radio.write(&payload, sizeof(float));      // transmit & save the report
    unsigned long end_timer = micros();                      // end the timer

    if (report) {
      MY_SERIAL.print(F("Transmission successful! "));          // payload was delivered
      MY_SERIAL.print(F("Time to transmit = "));
      MY_SERIAL.print(end_timer - start_timer);                 // print the timer result
      MY_SERIAL.print(F(" us. Sent: "));
      MY_SERIAL.println(payload);                               // print payload sent
      payload += 0.01;                                       // increment float payload
    } else {
      MY_SERIAL.println(F("Transmission failed or timed out")); // payload was not delivered
    }

    // to make this example readable in the serial monitor
    delay(1000);  // slow transmissions down by 1 second

  } else {
    // This device is a RX node

    uint8_t pipe;
    if (radio.available(&pipe)) {             // is there a payload? get the pipe number that recieved it
      uint8_t bytes = radio.getPayloadSize(); // get the size of the payload
      radio.read(&payload, bytes);            // fetch payload from FIFO
      MY_SERIAL.print(F("Received "));
      MY_SERIAL.print(bytes);                    // print the size of the payload
      MY_SERIAL.print(F(" bytes on pipe "));
      MY_SERIAL.print(pipe);                     // print the pipe number
      MY_SERIAL.print(F(": "));
      MY_SERIAL.println(payload);                // print the payload's value
    }
  } // role

  if (MY_SERIAL.available()) {
    // change the role via the serial monitor

    char c = toupper(MY_SERIAL.read());
    if (c == 'T' && !role) {
      // Become the TX node

      role = true;
      MY_SERIAL.println(F("*** CHANGING TO TRANSMIT ROLE -- PRESS 'R' TO SWITCH BACK"));
      radio.stopListening();

    } else if (c == 'R' && role) {
      // Become the RX node

      role = false;
      MY_SERIAL.println(F("*** CHANGING TO RECEIVE ROLE -- PRESS 'T' TO SWITCH BACK"));
      radio.startListening();
    }
  }

} // loop
