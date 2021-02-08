#pragma once

#include "Battery.h"

class Mechanics {
public:
    static constexpr double MAX_ALLOWED_MOTOR_VOLTAGE = 3.0;
    static constexpr double MIN_ALLOWED_BATTERY_VOLTAGE = 3.3;

private:
    Battery battery = Battery(A0);

public:

    virtual void run(int leftSpeed, int rightSpeed) = 0;

protected:

    bool isLowBattery() const {
        return battery.readVoltage() < MIN_ALLOWED_BATTERY_VOLTAGE;
    }

    int getMaxPwm() const {
        return (int) (255 * MAX_ALLOWED_MOTOR_VOLTAGE / battery.readVoltage());
    }


private:
};
