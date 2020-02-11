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

    void run(byte pwm) {
        analogWrite(pin, pwm);
    }

private:
};
