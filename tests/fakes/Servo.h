#pragma once

#include "Arduino.h"

class Servo {
public:
    void attach(int pin){ attachedPin = pin; }
    void write(int angle){ lastAngle = angle; }
    int read(){ return lastAngle; }

    int attachedPin = -1;
    int lastAngle = -1;
};
