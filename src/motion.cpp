#include <Arduino.h>
#include <Ticker.h>
#include "motion.h"
#include "mqtt.h"

Ticker motionReadTicker;

uint16_t lastMotionValue = 0;

void readMotionSensor() {
  const uint16_t motionVal = digitalRead(21);
  digitalWrite(LED_BUILTIN, motionVal);

//   Serial.print("Motion sensor value ");
//   Serial.println(motionVal);

  if (motionVal == lastMotionValue) {
      return;
  }

  lastMotionValue = motionVal;

  if (motionVal == 1) {
    sendMqttMsg("roomhub-1/tele/motion", "ON");
  } else {
    sendMqttMsg("roomhub-1/tele/motion", "OFF");
  }
}

void setupMotion(float pollInterval) {
  pinMode(21, INPUT_PULLDOWN);
  pinMode(LED_BUILTIN, OUTPUT);
  motionReadTicker.attach(pollInterval, readMotionSensor);
}
