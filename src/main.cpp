#include <Ticker.h>
#include "ota.h"
#include "wifi_setup.h"
#include "mqtt.h"
#include "ir.h"

#define LED_PIN 15

void blinkLED() {
  Serial.println("Toggle LED");
  digitalWrite(LED_PIN, !(digitalRead(LED_PIN)));
}

Ticker blinker;

void setup() {
  Serial.begin(115200);
  Serial.println("Booting");

  // Setup Wifi with WifiManager
  if (!setupWifi()) {
    Serial.println("Failed to connect and hit timeout");
#ifdef ESP8266
    ESP.reset();
#elif defined(ESP32)
    ESP.restart();
#endif
    delay(1000);
  }

  setupOTA();
  setupMQTT();
  setupIR();

  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  pinMode(LED_PIN, OUTPUT);
  blinker.attach(1, blinkLED);
}

void loop() {
  ArduinoOTA.handle();
  mqttLoopHandler();
}