#pragma once

#include "hal/Mechanics.h"
#include "Motor.h"

class MechanicsTransistors : public Mechanics {
public:

private:
    Motor leftMotor = Motor(9);
    Motor rightMotor = Motor(10);

public:

    void run(int leftSpeed, int rightSpeed) override {

        if (isLowBattery()) {
            leftMotor.run(0);
            rightMotor.run(0);
            return;
        }

        int maxPwm = getMaxPwm();

        leftMotor.run(constrain(leftSpeed, 0, maxPwm));
        rightMotor.run(constrain(rightSpeed , 0, maxPwm));
    }

};
