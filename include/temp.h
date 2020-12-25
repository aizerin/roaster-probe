#ifndef ROASTER_PROBE_TEMP_H
#define ROASTER_PROBE_TEMP_H

namespace Temp {
    extern unsigned long previousMillis;
    extern unsigned long previousPublishMillis;

    void setup();

    void readAndPublish();

}

#endif //ROASTER_PROBE_TEMP_H
