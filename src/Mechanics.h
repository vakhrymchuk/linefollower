#pragma once

#include "Motor.h"
#include "Battery.h"

class Mechanics {
public:
    static constexpr double MAX_ALLOWED_MOTOR_VOLTAGE = 3.0;
    static constexpr double MIN_ALLOWED_BATTERY_VOLTAGE = 3.3;

private:
    Motor leftMotor = Motor(9);
    Motor rightMotor = Motor(10);
    Battery battery = Battery(A0);

public:

    void run(byte leftSpeedPerc, byte rightSpeedPerc) {

        double batteryVoltage = battery.readVoltage();
//        Serial.print("v = ");
//        Serial.println(batteryVoltage);
        if (batteryVoltage < MIN_ALLOWED_BATTERY_VOLTAGE) {
            leftMotor.run(0);
            rightMotor.run(0);
            return;
        }

        int maxPwm = (int) (255 * MAX_ALLOWED_MOTOR_VOLTAGE / batteryVoltage);
//        Serial.print("maxPwm = ");
//        Serial.println(maxPwm);

        leftMotor.run(leftSpeedPerc * 0.01 * maxPwm);
        rightMotor.run(rightSpeedPerc * 0.01 * maxPwm);
    }

private:
};
