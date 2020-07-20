#include "mqtt.h"

WiFiClient espClient;
PubSubClient client(espClient);

const char* mqttServer = "192.168.1.100";
const int mqttPort = 37181;
const char* mqttUser = "mosquito";
const char* mqttPassword = "mosquito";

/**
 * MQTT Message received callback
 */
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);

  Serial.print("Message:");
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }

  Serial.println();
  Serial.println("-----------------------");
}

/**
 * Setup MQTT
 * Wifi Setup should be already done before setting up MQTT
 */
void setupMQTT() {
    client.setServer(mqttServer, mqttPort);
    client.setCallback(callback);
}

/**
 * Publish Message to topic
 */
void sendMqttMsg(char* topic, char* msg) {
    client.publish(topic, msg);
}

/**
 * MQTT Arduino Loop Handler
 */
void mqttLoopHandler() {
    client.loop();
}