#ifndef WIFI_SETUP_MY
#define WIFI_SETUP_MY

#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal

#ifdef ESP8266
#include <ESP8266WiFi.h>          //ESP8266 Core WiFi Library (you most likely already have this in your sketch)
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#elif defined(ESP32)
#include <WiFi.h>
#include <WebServer.h>
#endif

#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

boolean setupWifi();

#endif