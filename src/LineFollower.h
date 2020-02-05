#pragma once

#include <Interval.h>
#include "Sensors.h"

class LineFollower {
public:
    static const int INTERVAL = 10;

private:

    Interval interval = Interval(INTERVAL);
    Sensors sensors = Sensors();

public:

    void loop() {
        if (interval.isReady()) {
            sensors.read();
            int state = sensors.getState();
        }
    }

private:

};
