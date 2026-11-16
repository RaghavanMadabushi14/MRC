#pragma once

#include <Arduino.h>
#include <stdio.h>
#include <SoftwareSerial.h>
#include "include/BluetoothReadWrite.h"

String Bluetooth_Read(SoftwareSerial* BTdevice){
    if(Serial.available()){
        return Serial.readStringUntil('\n');
    }
    return "";
}

void Bluetooth_Write(SoftwareSerial* BTdevice, String Response){
    Serial.println(Response);
}
