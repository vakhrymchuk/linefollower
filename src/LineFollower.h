#pragma once

#include <Interval.h>
#include "Sensors.h"
#include "Mechanics.h"

class LineFollower {
public:
    static const int INTERVAL = 10;

    static constexpr double PID_P = 7.0;
    static constexpr double PID_D = 18.0;
    // 40 1.5 5   40 1 2
    // 45 2 5
    // 50 4 10 50 4.5 11 50 6 12
    // 45 7 18

private:

    Interval interval = Interval(INTERVAL);
    Sensors sensors = Sensors();
    Mechanics mechanics = Mechanics();

    int speed = 45; // percentage

    int lastError = 0;

//    Interval speedUp = Interval(25, SECOND);

public:

    void loop() {
        if (interval.isReady()) {

            sensors.read();

            int error = sensors.getState();
            int16_t speedDifference = PID_P * error + PID_D * (error - lastError);
            lastError = error;

            int16_t leftSpeed = constrain(speed + speedDifference, 0, 100);
            int16_t rightSpeed = constrain(speed - speedDifference, 0, 100);

            mechanics.run(leftSpeed, rightSpeed);
        }
//        if (speedUp.isReady()) {
//            speed++;
//        }
    }

private:

};
