#pragma once

class Sensors {
public:
    static const int SENSORS_COUNT = 8;
    static const int SENSORS_ARRAY_ADDRESS = 9;
    static const int SENSORS_MAX_VALUE = 255;
    static const int SENSORS_LINE_THRESHOLD = 150;

    static const int8_t STATE_COEF[];
    static const int STATE_MAX_VALUE = SENSORS_MAX_VALUE * SENSORS_COUNT / 2;

private:
    byte data[SENSORS_COUNT];
    int state = 0;

public:

    /**
     * Read values from sensors. >200 - white, <100 - black line
     */
    void read() {
        uint8_t size = Wire.requestFrom(SENSORS_ARRAY_ADDRESS, 16);
        byte t = 0;
        while (Wire.available()) {
            int b = Wire.read();
            if (t < SENSORS_COUNT) {
                data[t] = b;
                Wire.read();
            }
            t++;
        }
    }

    bool isOnLine() {
        for (const auto &item : data) {
            if (item > SENSORS_LINE_THRESHOLD) {
                return true;
            }
        }
        return false;
    }

    /**
     * @return state from -1020 to 1020 value
     */
    int getState() {
        if (isOnLine()) {
            for (byte i = 0; i < SENSORS_COUNT; i++) {
                state += STATE_COEF[i] * data[i];
            }
        } else {
            state = state * STATE_MAX_VALUE;
        }

        return constrain(state, -STATE_MAX_VALUE, STATE_MAX_VALUE);
    }

private:

};

const int8_t Sensors::STATE_COEF[] = {-4, -3, -2, -1, 1, 2, 3, 4};
