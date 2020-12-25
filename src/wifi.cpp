#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "wifi.h"
#include "led.h"

#define WLAN_SSID       "TP-Link_C0AA"
// todo https://github.com/tzapu/WiFiManager
#define WLAN_PASS       "***"

using namespace Wifi;

void Wifi::connect() {
    Serial.print(F("Connecting to "));
    Serial.println(WLAN_SSID);
    Serial.println();

    WiFi.begin(WLAN_SSID, WLAN_PASS);
    while (WiFi.status() != WL_CONNECTED) {
        Led::flashRed(1);
        delay(500);
        Serial.print(F("."));
    }
    Led::flashBlue(1);
    // print WiFi connection diagnostics
    Serial.println(F("WiFi connected"));
    Serial.println(F("IP address: "));
    Serial.println(WiFi.localIP());
}