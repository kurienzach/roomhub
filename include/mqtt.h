#ifndef MQTT_MY
#define MQTT_MY

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

void setupMQTT();
void sendMqttMsg(char* topic, char* msg);
void mqttLoopHandler();

#endif