#include <Arduino.h>

#include "led.h"
#include "wifi.h"
#include "mqtt.h"
#include "gyro.h"
#include "battery.h"
#include "temp.h"

const int startupDelay = 1500;

void setup() {
    delay(startupDelay);
    Led::setup();
//#ifdef DEBUG
    Serial.begin(115200);
//    // todo timhle asi obalit tohle a pak logovani
//#endif
//
    Wifi::connect();
    Mqtt::connect();
    Gyro::setup();
    Temp::setup();
    Led::turnOnBlue();
}

void loop() {
    Mqtt::testConnection();
    Battery::readAndPublish();
    Gyro::readAndPublish();
    Temp::readAndPublish();
}