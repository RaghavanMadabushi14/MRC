#pragma once

#include <Arduino.h>
#include <stdio.h>
#include <SoftwareSerial.h>

String Bluetooth_Read(SoftwareSerial* BTdevice);

void Bluetooth_Write(SoftwareSerial* BTdevice, String Respone);

void Serial_Bluetooth_Switch(bool YesSerialControl);
