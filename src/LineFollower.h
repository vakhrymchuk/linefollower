#pragma once

#include <Interval.h>
#include "Sensors.h"
#include "hal/tb6612/MechanicsTB6612.h"

class LineFollower {
public:
    static const int INTERVAL = 5;

    static constexpr float PID_P = 1.5;
    static constexpr float PID_D = 3.0;

private:

    Interval interval = Interval(INTERVAL);
    Interval intervalDisplay = Interval(300);
    Sensors sensors = Sensors();
    MechanicsTB6612 mechanics = MechanicsTB6612();

    int speed = 120;

    int lastError = 0;

    int count = 0;

public:

    void start() {
        mechanics.start();
    }

    void loop() {

        if (interval.isReady()) {
            count++;

            sensors.read();

            int error = sensors.getState();
            float speedAdjust = speed / 100.f;
            float kp = PID_P * speedAdjust;
            float kd = PID_D * speedAdjust * speedAdjust;
            int speedDifference = (int) (kp * error + kd * (error - lastError));
            lastError = error;

            int baseSpeed = speed;
            if (speed + abs(speedDifference) > 255) {
               baseSpeed = 255 - abs(speedDifference);
            }

            mechanics.run(baseSpeed + speedDifference, baseSpeed - speedDifference);

#ifdef DEBUG
            if (intervalDisplay.isReady()) {
                Serial.print("FPS: ");
                Serial.print(count);
                Serial.print("   error: ");
                Serial.print(error);
                Serial.print("   speedDifference: ");
                Serial.print(speedDifference);
                Serial.print("   ");

                sensors.out();

                count = 0;
            }
#endif

        }
    }

private:

};
