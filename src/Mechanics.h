#pragma once

#include "Motor.h"

class Mechanics {
public:
    static const int MAX_SPEED = 150;

private:
    Motor leftMotor = Motor(9);
    Motor rightMotor = Motor(10);

public:

    void run(byte leftSpeedPercentage, byte rightSpeedPercentage) {
        leftMotor.run(leftSpeedPercentage * 0.01 * MAX_SPEED);
        rightMotor.run(rightSpeedPercentage * 0.01 * MAX_SPEED);
    }

private:
};
