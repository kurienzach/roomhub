#include "wifi_setup.h"

WiFiManager wifiManager;

boolean setupWifi() {
    wifiManager.setConfigPortalTimeout(180);
    return wifiManager.autoConnect("RoomHub-9318rj");
}