#ifndef BATTERY_H
#define BATTERY_H

#include <Arduino.h>

void initBattery();
uint8_t getBatteryPercent();
float getBatteryVoltage();

#endif // BATTERY_H
