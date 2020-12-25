#include "battery.h"
#include "mqtt.h"

#define READRATE 5000

using namespace Battery;

unsigned long Battery::previousMillis = 0;

void Battery::readAndPublish() {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis > READRATE) {
        // save the last time you blinked the LED
        previousMillis = currentMillis;

        int rawLevel = analogRead(A0);
        // the 10kΩ/47kΩ voltage divider reduces the voltage, so the ADC Pin can handle it
        // According to Wolfram Alpha, this results in the following values:
        // 10kΩ/(47kΩ+10kΩ)*  5v = 0.8772v
        // 10kΩ/(47kΩ+10kΩ)*3.7v = 0.649v
        // 10kΩ/(47kΩ+10kΩ)*3.1v = 0.544
        // * i asumed 3.1v as minimum voltage => see LiPO discharge diagrams
        // the actual minimum i've seen was 467, which would be 2.7V immediately before automatic cutoff
        // a measurement on the LiPo Pins directly resulted in >3.0V, so thats good to know, but no danger to the battery.

        // convert battery level to percent
        int level = map(rawLevel, 500, 649, 0, 100);

        // i'd like to report back the real voltage, so apply some math to get it back
        // 1. convert the ADC level to a float
        // 2. divide by (R2[1] / R1 + R2)
        // [1] the dot is a trick to handle it as float
        double realVoltage = (double) rawLevel / 1000 / (10000. / (47000 + 10000));

        // cap level to 100%, just for graphing, i don't want to see your lab, when the battery actually gets to that level
        int percentage = level < 150 ? level : 100;
        // USB is connected if the reading is ~870, as the voltage will be 5V, so we assume it's charging
        int charging = rawLevel > 800 ? 1 : 0;

        Mqtt::publishBattery(percentage, charging, realVoltage, rawLevel);
    }
};