#ifndef ROASTER_PROBE_MQTT_H
#define ROASTER_PROBE_MQTT_H

#pragma once

#include <WString.h>

namespace Mqtt {
    void connect();

    void testConnection();

    void publishLog(const char *message);

    void publishBattery(int percentage, int charging, double voltage, int rawLevel);

    void publishGyro(double yaw, double pitch, double roll);

    void publishTemp(double Tmax, double Tnow, double Tmin);
}


#endif //ROASTER_PROBE_MQTT_H
