#ifndef FLASHLIGHT_H
#define FLASHLIGHT_H

#include <Arduino.h>

void initFlashlight();
void toggleFlashlight();
void setFlashlightState(bool on);
bool getFlashlightState();

#endif // FLASHLIGHT_H
