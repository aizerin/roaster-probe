#ifndef ROASTER_PROBE_GYRO_H
#define ROASTER_PROBE_GYRO_H

namespace Gyro {
    extern unsigned long previousMillis;

    void setup();

    void readAndPublish();

}

#endif //ROASTER_PROBE_GYRO_H
