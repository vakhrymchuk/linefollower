#pragma once

#include <Relay.h>
#include "hal/Mechanics.h"
#include "ChannelTB6612.h"

class MechanicsTB6612 : public Mechanics {
public:

private:
    ChannelTB6612 leftMotor = ChannelTB6612(9, 8, 7);
    ChannelTB6612 rightMotor = ChannelTB6612(10, 11, 12);

    Relay standBy = Relay(6);

public:

    MechanicsTB6612() {
        standBy.disable();
    }

    void start() {
        standBy.enable();
    }

    void run(int leftSpeed, int rightSpeed) override {

        if (isLowBattery()) {
            leftMotor.run(0);
            rightMotor.run(0);
            return;
        }

        int maxPwm = getMaxPwm();

        leftMotor.run(constrain(leftSpeed, -maxPwm, maxPwm));
        rightMotor.run(constrain(rightSpeed, -maxPwm, maxPwm));
    }

};
