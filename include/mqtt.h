#ifndef MQTT_MY
#define MQTT_MY

#ifdef ESP8266
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#endif
#include <PubSubClient.h>

void setupMQTT();
void sendMqttMsg(char* topic, char* msg);
void mqttLoopHandler();

#endif