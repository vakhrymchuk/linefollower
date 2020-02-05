#pragma once

#include "Motor.h"

class Mechanics {
public:

private:
    Motor leftMotor = Motor(9);
    Motor rightMotor = Motor(10);

public:

    void run(byte leftSpeed, byte rightSpeed) {
        leftMotor.run(leftSpeed);
        rightMotor.run(rightSpeed);
    }

private:
};
