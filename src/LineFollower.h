#pragma once

#include <Interval.h>
#include "Sensors.h"
#include "Mechanics.h"

class LineFollower {
public:
    static const int INTERVAL = 10;

private:

    Interval interval = Interval(INTERVAL);
    Sensors sensors = Sensors();
    Mechanics mechanics = Mechanics();

public:

    void loop() {
        if (interval.isReady()) {
            sensors.read();
            int state = sensors.getState();
            if (state > -300 && state < 300) {
                mechanics.run(100, 100);
            } else {
                mechanics.run(0, 0);
            }
        }
    }

private:

};
