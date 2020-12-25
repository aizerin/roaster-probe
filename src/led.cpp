#include <Arduino.h>
#include "led.h"

using namespace Led;

const int blueLed = 2;
const int redLed = 0;

void Led::setup() {
    pinMode(redLed, OUTPUT);
    pinMode(blueLed, OUTPUT);
    digitalWrite(redLed, HIGH);
    digitalWrite(blueLed, HIGH);
}

void Led::flashRed(int flashCount) {
    flash(true, false, flashCount);
}

void Led::flashBlue(int flashCount) {
    flash(false, true, flashCount);
}

void Led::turnOnBlue() {
    digitalWrite(blueLed, LOW);
}

void Led::flash(bool red, bool blue, int flashCount = 1) {
    do {
        if (flashCount > 0) {
            delay(123);
        }
        if (red) {
            digitalWrite(redLed, LOW);
        }
        if (blue) {
            digitalWrite(blueLed, LOW);
        }
        delay(123);
        if (red) {
            digitalWrite(redLed, HIGH);
        }
        if (blue) {
            digitalWrite(blueLed, HIGH);
        }
    } while (--flashCount > 0);
}