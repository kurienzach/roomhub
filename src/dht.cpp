#include <Ticker.h>
#include "dht.h"
#include "DHTesp.h"
#include "mqtt.h"

Ticker dhtTicker;
Ticker dhtPublish;
DHTesp dht;

uint16_t readCount = 0;
bool isInitialized = false;
bool isStaleValue = true;
char lastTemp[10];
char lastHumidity[10];

void readDHTSensor() {
  TempAndHumidity newValues = dht.getTempAndHumidity();
  if (dht.getStatus() != 0) {
		Serial.println("DHT22 error status: " + String(dht.getStatusString()));
    isStaleValue = true;
		return;
	}

  // Discard the first few values since these cannot be incorrect
  if (readCount < 5) {
    readCount++;
    return;
  }

  isStaleValue = false;

  dtostrf(newValues.temperature, 6, 2, lastTemp);
  dtostrf(newValues.humidity, 6, 2, lastHumidity);
  readCount = 10;
  isInitialized = true;

  Serial.printf("%s %s\n", lastTemp, lastHumidity);
}

void publishDHTValues() {
  if (!isInitialized || isStaleValue) {
    return;
  }

  sendMqttMsg("roomhub-1/tele/temp", lastTemp);
  sendMqttMsg("roomhub-1/tele/humidity", lastHumidity);
}

void setupDHT(float pollInterval, float publishInterval) {
  dht.setup(19, DHTesp::DHT22);
  dhtTicker.attach(pollInterval, readDHTSensor);
  dhtPublish.attach(publishInterval, publishDHTValues);
}
