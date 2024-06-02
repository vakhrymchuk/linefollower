#pragma once

#include <IRremote.hpp>

#define IR_PIN 2
#define GND_PIN 3
#define V_PIN 4

class IR
{
public:
    int code = 0;

    IR()
    {
        pinMode(GND_PIN, OUTPUT);
        pinMode(V_PIN, OUTPUT);
        digitalWrite(GND_PIN, LOW);
        digitalWrite(V_PIN, HIGH);
        IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
    }

    bool read()
    {
        if (IrReceiver.decode())
        {
            IrReceiver.resume();
            if (IrReceiver.decodedIRData.protocol == NEC)
            {
                code = IrReceiver.decodedIRData.command;
                return true;
            }
        }
        return false;
    }
};
