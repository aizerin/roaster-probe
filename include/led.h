#ifndef ROASTER_PROBE_LED_H
#define ROASTER_PROBE_LED_H

#include <Arduino.h>

#pragma once

namespace Led {

    void flash(bool red, bool blue, int flashCount);

    void flashRed(int flashCount);

    void flashBlue(int flashCount);

    void setup();

    void turnOnBlue();
}

#endif //ROASTER_PROBE_LED_H
