#include "wifi_setup.h"

WiFiManager wifiManager;

void setupWifi() {
    wifiManager.setConfigPortalTimeout(180);
    wifiManager.autoConnect("RoomHub-9318rj");
}