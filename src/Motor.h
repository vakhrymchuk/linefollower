#pragma once

class Motor {
public:

private:
    byte pin;
public:
    Motor(byte pin) : pin(pin) {
        pinMode(pin, OUTPUT);
        run(0);
    }

    void run(int pwm) const {
        pwm = constrain(pwm, 0, 255);
        analogWrite(pin, pwm);
    }

private:
};
