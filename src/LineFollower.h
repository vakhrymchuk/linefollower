#pragma once

#include <Interval.h>
#include "Sensors.h"
#include "Mechanics.h"

class LineFollower {
public:
    static const int INTERVAL = 10;
    static const int MAX_SPEED = 50; // percentage

    static constexpr double PID_P = 0.25;
    static constexpr double PID_D = 6;

private:

    Interval interval = Interval(INTERVAL);
    Sensors sensors = Sensors();
    Mechanics mechanics = Mechanics();

    int lastError = 0;

public:

    void loop() {
        if (interval.isReady()) {

            sensors.read();

            int error = sensors.getState();
            int16_t speedDifference = PID_P * error + PID_D * (error - lastError);
            lastError = error;

            int16_t leftSpeed = constrain(MAX_SPEED + speedDifference, 0, MAX_SPEED);
            int16_t rightSpeed = constrain(MAX_SPEED - speedDifference, 0, MAX_SPEED);

            mechanics.run(leftSpeed, rightSpeed);
        }
    }

private:

};
