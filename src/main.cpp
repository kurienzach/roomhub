#include <ESP8266WiFi.h>
#include "ota.h"
#include "wifi_setup.h"

#include <IRremoteESP8266.h>
#include <IRsend.h>

const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

// Example of data captured by IRrecvDumpV2.ino
// uint16_t rawData[67] = {9000, 4500, 650, 550, 650, 1650, 600, 550, 650, 550,
//                         600, 1650, 650, 550, 600, 1650, 650, 1650, 650, 1650,
//                         600, 550, 650, 1650, 650, 1650, 650, 550, 600, 1650,
//                         650, 1650, 650, 550, 650, 550, 650, 1650, 650, 550,
//                         650, 550, 650, 550, 600, 550, 650, 550, 650, 550,
//                         650, 1650, 600, 550, 650, 1650, 650, 1650, 650, 1650,
//                         650, 1650, 650, 1650, 650, 1650, 600};

/**
 * The below code is obtained using the broadlink_ir_converer js utility
 */
uint16_t rawData[79] = {9044,4507,578,578,578,548,578,548,609,548,578,548,578,578,
578,548,578,548,609,1644,578,1674,578,578,578,548,578,1644,609,1644,609,1644,609,
1644,609,1644,609,1644,609,548,578,1644,609,548,578,578,578,548,578,1644,609,548,
578,578,578,1644,609,548,578,1644,609,1644,609,1644,609,548,578,42178,9075,2223,609,
96415,9044,2253,609,96385,9075,2253,578};


void setup() {
  irsend.begin();
  Serial.begin(115200);
  Serial.println("Booting");

  // Setup Wifi with WifiManager
  // if (!setupWifi()) {
  //   Serial.println("Failed to connect and hit timeout");
  //   ESP.reset();
  //   delay(1000);
  // }

  // Setup OTA
  // setupOTA();

  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // pinMode(4, OUTPUT);
}

void loop() {
  // ArduinoOTA.handle();
  // Serial.println("NEC");
  // irsend.sendNEC(0x00FFE01FUL);
  // delay(2000);
  // Serial.println("Sony");
  // irsend.sendSony(0xa90, 12, 2);  // 12 bits & 2 repeats
  // delay(2000);
  Serial.println("sending ir");
  irsend.sendRaw(rawData, 79, 38);  // Send a raw data capture at 38kHz.

  // digitalWrite(4, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(2000);                       // wait for a second
  // digitalWrite(4, LOW);    // turn the LED off by making the voltage LOW
  // delay(1000); 
}