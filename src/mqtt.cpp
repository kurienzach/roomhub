#include <ArduinoJson.h>
#include "mqtt.h"
extern "C" {
#include "crypto/base64.h"
}
#include "ir.h"

WiFiClient espClient;
PubSubClient client(espClient);

const char* mqttServer = "192.168.1.100";
const int mqttPort = 1883;
const char* mqttUser = "mosquitto";
const char* mqttPassword = "mosquitto";
String device_id = "roomhub-1";

void irHandler(char *base64Str, unsigned int length) {
  size_t outputLength = 0;
  Serial.println(length);
  unsigned char * decoded = base64_decode((const unsigned char *)base64Str, length, &outputLength);

  uint16_t failCount = 0;
  while(outputLength == 0 && failCount < 5) {
    Serial.println("Base64 decoding failed, trying again after delay");
    delay(50);
    decoded = base64_decode((const unsigned char *)base64Str, strlen(base64Str), &outputLength);
    failCount++;
  }

  Serial.println(outputLength);
  sendIR((uint16_t*)decoded, outputLength/2);
  free(decoded);
}

/**
 * MQTT Message received callback
 */
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);

  if (strcmp(topic, (device_id + "/cmnd/ir_send").c_str()) == 0) {
    Serial.println("IR msg received");
    irHandler((char*)payload, length);
  }

  Serial.print("Message:\n");
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
  client.setBufferSize(512);
}


/**
 * Connect to MQTT Server
 */
void reconnect() {
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(device_id.c_str(), mqttUser, mqttPassword)) {
      Serial.println("connected");
      client.subscribe((device_id + "/cmnd/#").c_str()); // write your unique ID here
    }
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
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
  if (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    reconnect();
  }
  client.loop();
}