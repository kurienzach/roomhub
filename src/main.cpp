#include <ESP8266WiFi.h>
#include "ota.h"
#include "wifi_setup.h"
#include "ir.h"

void setup() {
  Serial.begin(115200);
  Serial.println("Booting");

  // Setup Wifi with WifiManager
  if (!setupWifi()) {
    Serial.println("Failed to connect and hit timeout");
    ESP.reset();
    delay(1000);
  }

  // Setup OTA
  setupOTA();

  setupIR();

  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
void loop() {
  ArduinoOTA.handle();
}