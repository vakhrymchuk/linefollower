#pragma once

class ChannelTB6612 {
public:

private:
    byte pinPwm, pinA, pinB;
public:
    ChannelTB6612(byte pinPwm, int pinA, int pinB) : pinPwm(pinPwm), pinA(pinA), pinB(pinB) {
        pinMode(pinPwm, OUTPUT);
        pinMode(pinA, OUTPUT);
        pinMode(pinB, OUTPUT);
        run(0);
    }

    void run(int pwm) const {
        if (pwm >= 0) {
            digitalWrite(pinA, LOW);
            digitalWrite(pinB, HIGH);
        } else {
            digitalWrite(pinA, HIGH);
            digitalWrite(pinB, LOW);
            pwm = -pwm;
        }
        pwm = constrain(pwm, 0, 255);
        analogWrite(pinPwm, pwm);
    }

private:
};
