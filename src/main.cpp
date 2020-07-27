#include <Ticker.h>
#include "ota.h"
#include "wifi_setup.h"
#include "mqtt.h"
#include "ir.h"
#include "motion.h"
#include "dht.h"

#define LED_PIN 4

void blinkLED() {
  sendMqttMsg("roomhub-1/status", "DONE");
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
  setupMotion(1);
  setupDHT(2, 5);

  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  blinker.attach(120, blinkLED);
}

void loop() {
  ArduinoOTA.handle();
  mqttLoopHandler();
}