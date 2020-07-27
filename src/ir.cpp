#include <HardwareSerial.h>
#include "ir.h"

const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

/**
 * Setup IR
 */
void setupIR() {
  irsend.begin();
}

/**
 * Send IR Raw Data
 */
void sendIR(const uint16_t buf[], int len) {
  Serial.println("sending ir");
  irsend.sendRaw(buf, len, 38);  // Send a raw data capture at 38kHz.
}