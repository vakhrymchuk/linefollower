#include <Arduino.h>
#include <Wire.h>
#include <hal/ADC.h>
#include "LineFollower.h"

static const long FAST_CLOCK = 400000;

LineFollower *lineFollower;

void setup() {
    ADC_setup();
    Wire.begin();
    Wire.setClock(FAST_CLOCK);
    Serial.begin(115200);

    lineFollower = new LineFollower();
    delay(500);
    lineFollower->start();
}


void loop() {
    lineFollower->loop();
}
