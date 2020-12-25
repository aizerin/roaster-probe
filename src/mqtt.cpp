#include "mqtt.h"
#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <ArduinoJson.h>
#include "led.h"

#define SERVERNAME      "raspberrypi.local"
#define SERVERPORT      1883
#define USERNAME        "roaster"
#define PASSWORD        "roastervole"

using namespace Mqtt;

// Uncomment/comment to turn on/off debug output messages.
//#define MQTT_DEBUG

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, SERVERNAME, SERVERPORT, USERNAME, PASSWORD);

Adafruit_MQTT_Publish batteryFeed = Adafruit_MQTT_Publish(&mqtt, "/feeds/battery");
Adafruit_MQTT_Publish logFeed = Adafruit_MQTT_Publish(&mqtt, "/feeds/logs");
Adafruit_MQTT_Publish gyroFeed = Adafruit_MQTT_Publish(&mqtt, "/feeds/gyro");
Adafruit_MQTT_Publish tempFeed = Adafruit_MQTT_Publish(&mqtt, "/feeds/temp");

void Mqtt::connect() {
    Serial.println(F("Connecting to MQTT Broker...!"));
    int8_t ret;
    while ((ret = mqtt.connect()) != 0) {
        Led::flashRed(2);
        Serial.println(mqtt.connectErrorString(ret));
        if (ret >= 0) {
            mqtt.disconnect();
        }
        Serial.println(F("."));
        delay(5000);
    }
    Led::flashBlue(2);
    Serial.println(F("MQTT Broker Connected!"));
}

void Mqtt::testConnection() {
    if (!mqtt.ping(3)) {
        // reconnect to MQTT Broker
        if (!mqtt.connected()) {
            connect();
            Serial.println(F("MQTT Connection Restarted"));
        }
    }
}

void Mqtt::publishLog(const char *message) {
    Serial.println(message);
    logFeed.publish(message);
}


const size_t capacityBattery = JSON_OBJECT_SIZE(4);

void Mqtt::publishBattery(int percentage, int charging, double voltage, int rawLevel) {
    char output[128];
    DynamicJsonDocument doc(capacityBattery);

    doc["percentage"] = percentage;
    doc["charging"] = charging;
    doc["voltage"] = voltage;
    doc["rawLevel"] = rawLevel;

    serializeJson(doc, output);
    //TODO DEBUG IFDEF
    serializeJson(doc, Serial);
    Serial.println();
    batteryFeed.publish(output);
}

const size_t capacityGyro = JSON_OBJECT_SIZE(3);

void Mqtt::publishGyro(double yaw, double pitch, double roll) {
    char output[128];
    DynamicJsonDocument doc(capacityGyro);

    doc["yaw"] = yaw;
    doc["pitch"] = pitch;
    doc["roll"] = roll;

    serializeJson(doc, output);
    //TODO DEBUG IFDEF
    serializeJson(doc, Serial);
    Serial.println();
    gyroFeed.publish(output);
}

const size_t capacityTemp = JSON_OBJECT_SIZE(3);

void Mqtt::publishTemp(double Tmax, double Tnow, double Tmin) {
    char output[128];
    DynamicJsonDocument doc(capacityTemp);

    doc["env"] = Tmax;
    doc["now"] = Tnow;
    doc["bean"] = Tmin;

    serializeJson(doc, output);
    //TODO DEBUG IFDEF
    serializeJson(doc, Serial);
    Serial.println();
    tempFeed.publish(output);
}