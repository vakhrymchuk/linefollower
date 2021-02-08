#pragma once

class Battery {
public:

private:
    byte pin;
public:
    Battery(byte pin) : pin(pin) {
        pinMode(pin, INPUT);
    }

    int read() const {
        return analogRead(pin);
    }

    double readVoltage() const {
        return 5.0 * analogRead(pin) / 1024;
    }

private:
};
