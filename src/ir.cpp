#include <HardwareSerial.h>
#include "ir.h"

const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

/**
 * The below code is obtained using the broadlink_ir_converer js utility
 */
uint16_t rawData[79] = {9044,4507,578,578,578,548,578,548,609,548,578,548,578,578,
578,548,578,548,609,1644,578,1674,578,578,578,548,578,1644,609,1644,609,1644,609,
1644,609,1644,609,1644,609,548,578,1644,609,548,578,578,578,548,578,1644,609,548,
578,578,578,1644,609,548,578,1644,609,1644,609,1644,609,548,578,42178,9075,2223,609,
96415,9044,2253,609,96385,9075,2253,578};

void setupIR() {
  irsend.begin();
}

void sendIR() {
  Serial.println("sending ir");
  irsend.sendRaw(rawData, 79, 38);  // Send a raw data capture at 38kHz.
}