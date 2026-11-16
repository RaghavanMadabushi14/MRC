#pragma once

#include <Arduino.h>
#include <stdio.h>
#include <SoftwareSerial.h>

#define YesSerial true

String Bluetooth_Read(SoftwareSerial* BTdevice);

void Bluetooth_Write(SoftwareSerial* BTdevice, String Respone);
