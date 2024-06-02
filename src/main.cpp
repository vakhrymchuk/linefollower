// #define DEBUGLF true

#include <Arduino.h>
#include <Wire.h>
#include "LineFollower.h"

static const long FAST_CLOCK = 400000;

LineFollower *lineFollower;

void setup() {
    Wire.begin();
    Wire.setClock(FAST_CLOCK);
#ifdef DEBUGLF
    Serial.begin(115200);
    Serial.println("Init");
#endif

    lineFollower = new LineFollower();
    delay(500);
    lineFollower->start();
#ifdef DEBUGLF
    Serial.println("Start");
#endif
}


void loop() {
    lineFollower->loop();
}
