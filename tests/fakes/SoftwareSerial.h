#pragma once

#include "Arduino.h"

class SoftwareSerial {
public:
    SoftwareSerial(int rx, int tx) : rxPin(rx), txPin(tx) {}
    void begin(long baud){ this->baud = baud; }
    int available(){ return pendingInput.length() > 0; }
    String readStringUntil(char){
        String s = pendingInput;
        pendingInput = String();
        return s;
    }
    void println(const String& s){
        lastReply = s;
        replyCount++;
    }

    int rxPin, txPin;
    long baud = 0;
    String pendingInput;
    String lastReply;
    int replyCount = 0;
};
