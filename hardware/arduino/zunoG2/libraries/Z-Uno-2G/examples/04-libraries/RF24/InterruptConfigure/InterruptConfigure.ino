/*
 * See documentation at https://nRF24.github.io/RF24
 * See License information at root directory of this library
 * Author: Brendan Doherty (2bndy5)
 */

/**
 * This example uses Acknowledgement (ACK) payloads attached to ACK packets to
 * demonstrate how the nRF24L01's IRQ (Interrupt Request) pin can be
 * configured to detect when data is received, or when data has transmitted
 * successfully, or when data has failed to transmit.
 *
 * This example was written to be used on 2 devices acting as "nodes".
 * Use the Serial Monitor to change each node's behavior.
 */

#define MY_SERIAL		Serial
#define printf_P MY_SERIAL.printf

#include <SPI.h>
// #include "printf.h"
#include "RF24.h"

// We will be using the nRF24L01's IRQ pin for this example
#define IRQ_PIN 2 // this needs to be a digital input capable pin
volatile bool wait_for_event = false; // used to wait for an IRQ event to trigger

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
// a string that changes on every transmission. (successful or not)
// Make a couple arrays of payloads & an iterator to traverse them
const uint8_t tx_pl_size = 5;
const uint8_t ack_pl_size = 4;
uint8_t pl_iterator = 0;
// The " + 1" compensates for the c-string's NULL terminating 0
char tx_payloads[][tx_pl_size + 1] = {"Ping ", "Pong ", "Radio", "1FAIL"};
char ack_payloads[][ack_pl_size + 1] = {"Yak ", "Back", " ACK"};

void interruptHandler(); // prototype to handle IRQ events
void printRxFifo();      // prototype to print RX FIFO with 1 buffer


void setup() {
  MY_SERIAL.begin(115200);

  // initialize the transceiver on the SPI bus
  if (!radio.begin()) {
    MY_SERIAL.println(F("radio hardware is not responding!!"));
    while (1) {} // hold in infinite loop
    delay(1);
  }

  // print example's introductory prompt
  MY_SERIAL.println(F("RF24/examples/InterruptConfigure"));

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

  // setup the IRQ_PIN
  pinMode(IRQ_PIN, INPUT);
  attachInterrupt(IRQ_PIN, interruptHandler, FALLING);
  // IMPORTANT: do not call radio.available() before calling
  // radio.whatHappened() when the interruptHandler() is triggered by the
  // IRQ pin FALLING event. According to the datasheet, the pipe information
  // is unreliable during the IRQ pin FALLING transition.

  // Set the PA Level low to try preventing power supply related problems
  // because these examples are likely run with nodes in close proximity to
  // each other.
  radio.setPALevel(RF24_PA_LOW);    // RF24_PA_MAX is default.

  // For this example we use acknowledgment (ACK) payloads to trigger the
  // IRQ pin when data is received on the TX node.
  // to use ACK payloads, we need to enable dynamic payload lengths
  radio.enableDynamicPayloads();    // ACK payloads are dynamically sized

  // Acknowledgement packets have no payloads by default. We need to enable
  // this feature for all nodes (TX & RX) to use ACK payloads.
  radio.enableAckPayload();
  // Fot this example, we use the same address to send data back and forth

  // set the TX address of the RX node into the TX pipe
  radio.openWritingPipe(address[radioNumber]);     // always uses pipe 0

  // set the RX address of the TX node into a RX pipe
  radio.openReadingPipe(1, address[!radioNumber]); // using pipe 1

  // additional setup specific to the node's role
  if (role) {
    // setup for TX mode
    radio.stopListening();                                  // put radio in TX mode

  } else {
    // setup for RX mode

    // let IRQ pin only trigger on "data ready" event in RX mode
    radio.maskIRQ(1, 1, 0); // args = "data_sent", "data_fail", "data_ready"

    // Fill the TX FIFO with 3 ACK payloads for the first 3 received
    // transmissions on pipe 1
    radio.writeAckPayload(1, &ack_payloads[0], ack_pl_size);
    radio.writeAckPayload(1, &ack_payloads[1], ack_pl_size);
    radio.writeAckPayload(1, &ack_payloads[2], ack_pl_size);

    radio.startListening(); // put radio in RX mode
  }

  // For debugging info
  // printf_begin();             // needed only once for printing details
  // radio.printDetails();       // (smaller) function that prints raw register values
  // radio.printPrettyDetails(); // (larger) function that prints human readable data

}

void loop() {
  if (role && !wait_for_event) {

    // delay(1); // wait for IRQ pin to fully RISE

    // This device is a TX node. This if block is only triggered when
    // NOT waiting for an IRQ event to happen

    if (pl_iterator == 0) {
      // Test the "data ready" event with the IRQ pin

      MY_SERIAL.println(F("\nConfiguring IRQ pin to ignore the 'data sent' event"));
      radio.maskIRQ(true, false, false); // args = "data_sent", "data_fail", "data_ready"
      MY_SERIAL.println(F("   Pinging RX node for 'data ready' event..."));

    } else if (pl_iterator == 1) {
      // Test the "data sent" event with the IRQ pin

      MY_SERIAL.println(F("\nConfiguring IRQ pin to ignore the 'data ready' event"));
      radio.maskIRQ(false, false, true); // args = "data_sent", "data_fail", "data_ready"
      MY_SERIAL.println(F("   Pinging RX node for 'data sent' event..."));

    } else if (pl_iterator == 2) {
      // Use this iteration to fill the RX node's FIFO which sets us up for the next test.

      // write() uses virtual interrupt flags that work despite the masking of the IRQ pin
      radio.maskIRQ(1, 1, 1); // disable IRQ masking for this step

      MY_SERIAL.println(F("\nSending 1 payload to fill RX node's FIFO. IRQ pin is neglected."));
      // write() will call flush_tx() on 'data fail' events
      if (radio.write(&tx_payloads[pl_iterator], tx_pl_size)) {
        if (radio.rxFifoFull()) {
          MY_SERIAL.println(F("RX node's FIFO is full; it is not listening any more"));
        } else {
          MY_SERIAL.println("Transmission successful, but the RX node might still be listening.");
        }
      } else {
        MY_SERIAL.println(F("Transmission failed or timed out. Continuing anyway."));
        radio.flush_tx(); // discard payload(s) that failed to transmit
      }

    } else if (pl_iterator == 3) {
      // test the "data fail" event with the IRQ pin

      MY_SERIAL.println(F("\nConfiguring IRQ pin to reflect all events"));
      radio.maskIRQ(0, 0, 0); // args = "data_sent", "data_fail", "data_ready"
      MY_SERIAL.println(F("   Pinging inactive RX node for 'data fail' event..."));
    }

    if (pl_iterator < 4 && pl_iterator != 2) {

      // IRQ pin is LOW when activated. Otherwise it is always HIGH
      // Wait until IRQ pin is activated.
      wait_for_event = true;

      // use the non-blocking call to write a payload and begin transmission
      // the "false" argument means we are expecting an ACK packet response
      radio.startFastWrite(tx_payloads[pl_iterator++], tx_pl_size, false);

      // In this example, the "data fail" event is always configured to
      // trigger the IRQ pin active. Because the auto-ACK feature is on by
      // default, we don't need a timeout check to prevent an infinite loop.

    } else if (pl_iterator == 4) {
      // all IRQ tests are done; flush_tx() and print the ACK payloads for fun

      // CE pin is still HIGH which consumes more power. Example is now idling so...
      radio.stopListening(); // ensure CE pin is LOW
      // stopListening() also calls flush_tx() when ACK payloads are enabled

      printRxFifo();
      pl_iterator++;


      // inform user what to do next
      MY_SERIAL.println(F("\n*** PRESS 'T' to restart the transmissions"));
      MY_SERIAL.println(F("*** PRESS 'R' to change to Receive role\n"));


    } else if (pl_iterator == 2) {
      pl_iterator++; // proceed from step 3 to last step (stop at step 4 for readability)
    }

  } else if (!role) {
    // This device is a RX node

    if (radio.rxFifoFull()) {
      // wait until RX FIFO is full then stop listening

      delay(100);             // let ACK payload finish transmitting
      radio.stopListening();  // also discards unused ACK payloads
      printRxFifo();          // flush the RX FIFO

      // Fill the TX FIFO with 3 ACK payloads for the first 3 received
      // transmissions on pipe 1.
      radio.writeAckPayload(1, &ack_payloads[0], ack_pl_size);
      radio.writeAckPayload(1, &ack_payloads[1], ack_pl_size);
      radio.writeAckPayload(1, &ack_payloads[2], ack_pl_size);

      delay(100);             // let TX node finish its role
      radio.startListening(); // We're ready to start over. Begin listening.
    }

  } // role

  if (MY_SERIAL.available()) {
    // change the role via the serial monitor

    char c = toupper(MY_SERIAL.read());
    if (c == 'T') {
      // Become the TX node
      if (!role)
        MY_SERIAL.println(F("*** CHANGING TO TRANSMIT ROLE -- PRESS 'R' TO SWITCH BACK"));
      else
        MY_SERIAL.println(F("*** RESTARTING IRQ PIN TEST ***"));

      role = true;
      wait_for_event = false;
      pl_iterator = 0;   // reset the iterator
      radio.flush_tx();  // discard any payloads in the TX FIFO

      // startListening() clears the IRQ masks also. This is required for
      // continued TX operations when a transmission fails.
      radio.stopListening(); // this also discards any unused ACK payloads

    } else if (c == 'R' && role) {
      // Become the RX node
      MY_SERIAL.println(F("*** CHANGING TO RECEIVE ROLE -- PRESS 'T' TO SWITCH BACK"));

      role = false;

      radio.maskIRQ(0, 0, 0); // the IRQ pin should only trigger on "data ready" event

      // Fill the TX FIFO with 3 ACK payloads for the first 3 received
      // transmissions on pipe 1
      radio.flush_tx(); // make sure there is room for 3 new ACK payloads
      radio.writeAckPayload(1, &ack_payloads[0], ack_pl_size);
      radio.writeAckPayload(1, &ack_payloads[1], ack_pl_size);
      radio.writeAckPayload(1, &ack_payloads[2], ack_pl_size);
      radio.startListening();
    }
  } // MY_SERIAL.available()
} // loop


/**
 * when the IRQ pin goes active LOW, call this fuction print out why
 */
void interruptHandler() {
  // print IRQ status and all masking flags' states

  MY_SERIAL.println(F("\tIRQ pin is actively LOW")); // show that this function was called
  delayMicroseconds(250);
  bool tx_ds, tx_df, rx_dr;                       // declare variables for IRQ masks
  radio.whatHappened(tx_ds, tx_df, rx_dr);        // get values for IRQ masks
  // whatHappened() clears the IRQ masks also. This is required for
  // continued TX operations when a transmission fails.
  // clearing the IRQ masks resets the IRQ pin to its inactive state (HIGH)

  MY_SERIAL.print(F("\tdata_sent: "));
  MY_SERIAL.print(tx_ds);                            // print "data sent" mask state
  MY_SERIAL.print(F(", data_fail: "));
  MY_SERIAL.print(tx_df);                            // print "data fail" mask state
  MY_SERIAL.print(F(", data_ready: "));
  MY_SERIAL.println(rx_dr);                          // print "data ready" mask state

  if (tx_df)                                      // if TX payload failed
    radio.flush_tx();                             // clear all payloads from the TX FIFO

  // print if test passed or failed. Unintentional fails mean the RX node was not listening.
  // pl_iterator has already been incremented by now
  if (pl_iterator <= 1) {
    MY_SERIAL.print(F("   'Data Ready' event test "));
    MY_SERIAL.println(rx_dr ? F("passed") : F("failed"));
  } else if (pl_iterator == 2) {
    MY_SERIAL.print(F("   'Data Sent' event test "));
    MY_SERIAL.println(tx_ds ? F("passed") : F("failed"));
  } else if (pl_iterator == 4) {
    MY_SERIAL.print(F("   'Data Fail' event test "));
    MY_SERIAL.println(tx_df ? F("passed") : F("failed"));
  }
  wait_for_event = false; // ready to continue with loop() operations
} // interruptHandler


/**
 * Print the entire RX FIFO with one buffer. This will also flush the RX FIFO.
 * Remember that the payload sizes are declared as tx_pl_size and ack_pl_size.
 */
void printRxFifo() {
  if (radio.available()) {                   // if there is data in the RX FIFO
    // to flush the data from the RX FIFO, we'll fetch it all using 1 buffer

    uint8_t pl_size = !role ? tx_pl_size : ack_pl_size;
    char rx_fifo[pl_size * 3 + 1];       // RX FIFO is full & we know ACK payloads' size
    if (radio.rxFifoFull()) {
      rx_fifo[pl_size * 3] = 0;          // add a NULL terminating char to use as a c-string
      radio.read(&rx_fifo, pl_size * 3); // this clears the RX FIFO (for this example)
    } else {
      uint8_t i = 0;
      while (radio.available()) {
        radio.read(&rx_fifo + (i * pl_size), pl_size);
        i++;
      }
      rx_fifo[i * pl_size] = 0;          // add a NULL terminating char to use as a c-string
    }
    MY_SERIAL.print(F("Complete RX FIFO: "));
    MY_SERIAL.println(rx_fifo);                 // print the entire RX FIFO with 1 buffer
  }
}