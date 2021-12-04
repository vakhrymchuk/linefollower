#pragma once

#include <Interval.h>
#include <Timeout.h>
#include "Sensors.h"
#include "hal/tb6612/MechanicsTB6612.h"

class LineFollower {
public:
    static const int INTERVAL = 1;

    static constexpr float PID_P = 0.2;
    static constexpr float PID_D = 0.4;

private:

    Interval interval = Interval(INTERVAL);
    Sensors sensors = Sensors();
    MechanicsTB6612 mechanics = MechanicsTB6612();

    int speed = 170;

    int lastError = 0;

//    Interval speedUp = Interval(25, SECOND);

    Timeout timeout;
    int count = 0;

public:

    void start() {
        mechanics.start();
    }

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
