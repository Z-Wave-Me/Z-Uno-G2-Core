/*
 * See documentation at https://nRF24.github.io/RF24
 * See License information at root directory of this library
 * Author: Brendan Doherty 2bndy5
 */

/**
 * A simple example of streaming data from 1 nRF24L01 transceiver to another.
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
bool radioNumber; // 0 uses address[0] to transmit, 1 uses address[1] to transmit

// Used to control whether this node is sending or receiving
bool role = false; // true = TX node, false = RX node

// For this example, we'll be sending 32 payloads each containing
// 32 bytes of data that looks like ASCII art when printed to the serial
// monitor. The TX node and RX node needs only a single 32 byte buffer.
#define SIZE 32            // this is the maximum for this example. (minimum is 1)
char buffer[SIZE + 1];     // for the RX node
uint8_t counter = 0;       // for counting the number of received payloads
void makePayload(uint8_t); // prototype to construct a payload dynamically


void setup() {

  buffer[SIZE] = 0;        // add a NULL terminating character (for easy printing)

  MY_SERIAL.begin(115200);

  // initialize the transceiver on the SPI bus
  if (!radio.begin()) {
    MY_SERIAL.println(F("radio hardware is not responding!!"));
    while (1) {} // hold in infinite loop
    delay(1);
  }

  // print example's introductory prompt
  MY_SERIAL.println(F("RF24/examples/StreamingData"));

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
  // number of bytes we need to transmit
  radio.setPayloadSize(SIZE);     // default value is the maximum 32 bytes

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

} // setup()


void loop() {

  if (role) {
    // This device is a TX node

    radio.flush_tx();
    uint8_t i = 0;
    uint8_t failures = 0;
    unsigned long start_timer = micros();       // start the timer
    while (i < SIZE) {
      makePayload(i);                           // make the payload
      if (!radio.writeFast(&buffer, SIZE)) {
        failures++;
        radio.reUseTX();
      } else {
        i++;
      }

      if (failures >= 100) {
        MY_SERIAL.print(F("Too many failures detected. Aborting at payload "));
        MY_SERIAL.println(buffer[0]);
        break;
      }
    }
    unsigned long end_timer = micros();         // end the timer

    MY_SERIAL.print(F("Time to transmit = "));
    MY_SERIAL.print(end_timer - start_timer);      // print the timer result
    MY_SERIAL.print(F(" us with "));
    MY_SERIAL.print(failures);                     // print failures detected
    MY_SERIAL.println(F(" failures detected"));

    // to make this example readable in the serial monitor
    delay(1000);  // slow transmissions down by 1 second

  } else {
    // This device is a RX node

    if (radio.available()) {         // is there a payload?
      radio.read(&buffer, SIZE);     // fetch payload from FIFO
      MY_SERIAL.print(F("Received: "));
      MY_SERIAL.print(buffer);          // print the payload's value
      MY_SERIAL.print(F(" - "));
      MY_SERIAL.println(counter++);     // print the received counter
    }
  } // role

  if (MY_SERIAL.available()) {
    // change the role via the serial monitor

    char c = toupper(MY_SERIAL.read());
    if (c == 'T' && !role) {
      // Become the TX node

      role = true;
      counter = 0; //reset the RX node's counter
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


void makePayload(uint8_t i) {
  // Make a single payload based on position in stream.
  // This example employs function to save memory on certain boards.

  // let the first character be an identifying alphanumeric prefix
  // this lets us see which payload didn't get received
  buffer[0] = i + (i < 26 ? 65 : 71);
  for (uint8_t j = 0; j < SIZE - 1; ++j) {
    char chr = j >= (SIZE - 1) / 2 + abs((SIZE - 1) / 2 - i);
    chr |= j < (SIZE - 1) / 2 - abs((SIZE - 1) / 2 - i);
    buffer[j + 1] = chr + 48;
  }
}