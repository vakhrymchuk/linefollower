#pragma once

class Sensors {
public:
    static const int SENSORS_COUNT = 8;
    static const int SENSORS_ARRAY_ADDRESS = 9;
    static const int8_t STATE_COEF[];
private:
    byte data[SENSORS_COUNT];

public:
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

    int getState() {
        int state = 0;
        for (byte i = 0; i < SENSORS_COUNT; i++) {
            state += STATE_COEF[i] * data[i];
        }
        return state;
    }

private:

};

const int8_t Sensors::STATE_COEF[] = {-4, -3, -2, -1, 1, 2, 3, 4};
