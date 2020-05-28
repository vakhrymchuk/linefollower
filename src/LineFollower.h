#pragma once

#include <Interval.h>
#include <Timeout.h>
#include "Sensors.h"
#include "Mechanics.h"

class LineFollower {
public:
    static const int INTERVAL = 1;

    static constexpr float PID_P = 1.0;
    static constexpr float PID_D = 0.0;

private:

    Interval interval = Interval(INTERVAL);
    Sensors sensors = Sensors();
    Mechanics mechanics = Mechanics();

    int speed = 100;

    int lastError = 0;

//    Interval speedUp = Interval(25, SECOND);

    Timeout timeout;
    int count = 0;

public:

    void loop() {
        if (interval.isReady()) {
            count++;
            if (timeout.isReady()) {
                Serial.println(count);

                sensors.out();

                count = 0;
                timeout.start(1000);
            }

            sensors.read();

            int error = sensors.getState();
            int speedDifference = PID_P * error + PID_D * (error - lastError);
            lastError = error;

            mechanics.run(speed + speedDifference, speed - speedDifference);
        }
//        if (speedUp.isReady()) {
//            speed++;
//        }
    }

private:

};
