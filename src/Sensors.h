#pragma once

class Sensors {
public:
    static const int SENSORS_COUNT = 8;
    static const int SENSORS_ARRAY_ADDRESS = 9;
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

private:

};
