#pragma once

class Sensors {
public:
    static const int SENSORS_COUNT = 8;
    static const int SENSORS_ARRAY_ADDRESS = 9;
    static const int SENSORS_MAX_VALUE = 255;
    static const int SENSORS_LINE_THRESHOLD = 127;

    static const int8_t STATE_COEF[];
    static const int STATE_MAX_VALUE = 255;

private:
    byte data[SENSORS_COUNT];
    int state = 0;

public:

    /**
     * Read values from sensors. >SENSORS_LINE_THRESHOLD - black line
     */
    void read() {
        Wire.requestFrom(SENSORS_ARRAY_ADDRESS, 16);
        byte t = 0;
        while (Wire.available()) {
            int b = Wire.read();
            if (t < SENSORS_COUNT) {
                data[t] = SENSORS_MAX_VALUE - b;
                Wire.read();
            }
            t++;
        }
    }

    void out() {
        for (const auto &item : data) {
            Serial.print(item);
            Serial.print(' ');
        }
        Serial.print("    state = ");
        Serial.print(getState());
        Serial.print("    online = ");
        Serial.print(isOnLine());
        Serial.println();
    }

    bool isOnLine() {
        for (const auto &item : data) {
            if (item > SENSORS_LINE_THRESHOLD) {
                return true;
            }
        }
        return false;
    }

    bool hasWhite() {
        for (const auto &item : data) {
            if (item < SENSORS_LINE_THRESHOLD) {
                return true;
            }
        }
        return false;
    }

    /**
     * @return state from -STATE_MAX_VALUE to STATE_MAX_VALUE value divided by 100
     */
    int getState() {
        if (isOnLine()) {
            state = 0;
            for (byte i = 0; i < SENSORS_COUNT; i++) {
                state += STATE_COEF[i] * data[i];
            }
            state = state / 8;
        } else {
            state = state * 2;
        }

        state = constrain(state, -STATE_MAX_VALUE, STATE_MAX_VALUE);
        return state;
    }

private:

};

const int8_t Sensors::STATE_COEF[] = {-4, -3, -2, -1, 1, 2, 3, 4};
