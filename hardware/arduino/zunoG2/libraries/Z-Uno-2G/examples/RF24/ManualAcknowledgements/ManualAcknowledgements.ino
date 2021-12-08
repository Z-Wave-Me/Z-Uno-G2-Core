/*
 * See documentation at https://nRF24.github.io/RF24
 * See License information at root directory of this library
 * Author: Brendan Doherty (2bndy5)
 */

/**
 * A simple example of sending data from 1 nRF24L01 transceiver to another
 * with manually transmitted (non-automatic) Acknowledgement (ACK) payloads.
 * This example still uses ACK packets, but they have no payloads. Instead the
 * acknowledging response is sent with `write()`. This tactic allows for more
 * updated acknowledgement payload data, where actual ACK payloads' data are
 * outdated by 1 transmission because they have to loaded before receiving a
 * transmission.
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
bool role = false;  // true = TX node, false = RX node

// For this example, we'll be using a payload containing
// a string & an integer number that will be incremented
// on every successful transmission.
// Make a data structure to store the entire payload of different datatypes
struct PayloadStruct {
  char message[7];          // only using 6 characters for TX & RX payloads
  uint8_t counter;
};
PayloadStruct payload;

void setup() {

  // append a NULL terminating character for printing as a c-string
  payload.message[6] = 0;

  MY_SERIAL.begin(115200);

  // initialize the transceiver on the SPI bus
  if (!radio.begin()) {
    MY_SERIAL.println(F("radio hardware is not responding!!"));
    while (1) {} // hold in infinite loop
    delay(1);
  }

  // print example's introductory prompt
  MY_SERIAL.println(F("RF24/examples/ManualAcknowledgements"));

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
  radio.setPALevel(RF24_PA_LOW); // RF24_PA_MAX is default.

  // save on transmission time by setting the radio to only transmit the
  // number of bytes we need to transmit a float
  radio.setPayloadSize(sizeof(payload)); // char[7] & uint8_t datatypes occupy 8 bytes

  // set the TX address of the RX node into the TX pipe
  radio.openWritingPipe(address[radioNumber]);     // always uses pipe 0

  // set the RX address of the TX node into a RX pipe
  radio.openReadingPipe(1, address[!radioNumber]); // using pipe 1

  if (role) {
    // setup the TX node

    memcpy(payload.message, "Hello ", 6); // set the outgoing message
    radio.stopListening();                // put radio in TX mode
  } else {
    // setup the RX node

    memcpy(payload.message, "World ", 6); // set the outgoing message
    radio.startListening();               // put radio in RX mode
  }

  // For debugging info
  // printf_begin();             // needed only once for printing details
  // radio.printDetails();       // (smaller) function that prints raw register values
  // radio.printPrettyDetails(); // (larger) function that prints human readable data

} // setup()

void loop() {

  if (role) {
    // This device is a TX node

    unsigned long start_timer = micros();                 // start the timer
    bool report = radio.write(&payload, sizeof(payload)); // transmit & save the report

    if (report) {
      // transmission successful; wait for response and print results

      radio.startListening();                                // put in RX mode
      unsigned long start_timeout = millis();                // timer to detect timeout
      while (!radio.available()) {                           // wait for response
        if (millis() - start_timeout > 200)                  // only wait 200 ms
          break;
        delay(1);
      }
      unsigned long end_timer = micros();                    // end the timer
      radio.stopListening();                                 // put back in TX mode

      // print summary of transactions
      MY_SERIAL.print(F("Transmission successful!"));           // payload was delivered
      uint8_t pipe;
      if (radio.available(&pipe)) {                          // is there a payload received
        MY_SERIAL.print(F(" Round-trip delay: "));
        MY_SERIAL.print(end_timer - start_timer);               // print the timer result
        MY_SERIAL.print(F(" us. Sent: "));
        MY_SERIAL.print(payload.message);                       // print the outgoing payload's message
        MY_SERIAL.print(payload.counter);                       // print outgoing payload's counter
        PayloadStruct received;
        radio.read(&received, sizeof(received));             // get payload from RX FIFO
        MY_SERIAL.print(F(" Received "));
        MY_SERIAL.print(radio.getPayloadSize());                // print the size of the payload
        MY_SERIAL.print(F(" bytes on pipe "));
        MY_SERIAL.print(pipe);                                  // print the pipe number
        MY_SERIAL.print(F(": "));
        MY_SERIAL.print(received.message);                      // print the incoming payload's message
        MY_SERIAL.println(received.counter);                    // print the incoming payload's counter
        payload.counter = received.counter;                  // save incoming counter for next outgoing counter
      } else {
        MY_SERIAL.println(F(" Recieved no response."));         // no response received
      }
    } else {
      MY_SERIAL.println(F("Transmission failed or timed out")); // payload was not delivered
    } // report

    // to make this example readable in the serial monitor
    delay(1000);  // slow transmissions down by 1 second

  } else {
    // This device is a RX node

    uint8_t pipe;
    if (radio.available(&pipe)) {              // is there a payload? get the pipe number that recieved it
      PayloadStruct received;
      radio.read(&received, sizeof(received)); // get incoming payload
      payload.counter = received.counter + 1;  // increment incoming counter for next outgoing response

      // transmit response & save result to `report`
      radio.stopListening();                   // put in TX mode

      radio.writeFast(&payload, sizeof(payload));  // load response to TX FIFO
      bool report = radio.txStandBy(150);   // keep retrying for 150 ms

      radio.startListening();                  // put back in RX mode

      // print summary of transactions
      MY_SERIAL.print(F("Received "));
      MY_SERIAL.print(radio.getPayloadSize());    // print the size of the payload
      MY_SERIAL.print(F(" bytes on pipe "));
      MY_SERIAL.print(pipe);                      // print the pipe number
      MY_SERIAL.print(F(": "));
      MY_SERIAL.print(received.message);          // print incoming message
      MY_SERIAL.print(received.counter);          // print incoming counter

      if (report) {
        MY_SERIAL.print(F(" Sent: "));
        MY_SERIAL.print(payload.message);         // print outgoing message
        MY_SERIAL.println(payload.counter);       // print outgoing counter
      } else {
        MY_SERIAL.println(" Response failed.");   // failed to send response
      }
    }
  } // role

  if (MY_SERIAL.available()) {
    // change the role via the serial monitor

    char c = toupper(MY_SERIAL.read());
    if (c == 'T' && !role) {
      // Become the TX node

      role = true;
      memcpy(payload.message, "Hello ", 6); // set the outgoing message
      MY_SERIAL.println(F("*** CHANGING TO TRANSMIT ROLE -- PRESS 'R' TO SWITCH BACK"));
      radio.stopListening();                // put in TX mode

    } else if (c == 'R' && role) {
      // Become the RX node

      role = false;
      memcpy(payload.message, "World ", 6); // set the response message
      MY_SERIAL.println(F("*** CHANGING TO RECEIVE ROLE -- PRESS 'T' TO SWITCH BACK"));
      radio.startListening();               // put in RX mode
    }
  }
} // loop