#include <Arduino.h>
#include <Wire.h>
#include "LineFollower.h"

static const long FAST_CLOCK = 400000;

LineFollower *lineFollower;

void setup() {
    Wire.begin();
    Wire.setClock(FAST_CLOCK);
    Serial.begin(115200);

    lineFollower = new LineFollower();
}


void loop() {
    lineFollower->loop();
}
