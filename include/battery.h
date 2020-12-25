
#ifndef ROASTER_PROBE_BATTERY_H
#define ROASTER_PROBE_BATTERY_H

#include <Arduino.h>

namespace Battery {
    extern unsigned long previousMillis;
    void readAndPublish();
}

#endif //ROASTER_PROBE_BATTERY_H
