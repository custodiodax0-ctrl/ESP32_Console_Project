#include "flashlight.h"
#include "config.h"

static bool g_flashlightOn = false;

void initFlashlight() {
    pinMode(PIN_FLASHLIGHT, OUTPUT);
    digitalWrite(PIN_FLASHLIGHT, LOW);
    g_flashlightOn = false;
}

void setFlashlightState(bool on) {
    g_flashlightOn = on;
    digitalWrite(PIN_FLASHLIGHT, g_flashlightOn ? HIGH : LOW);
}

void toggleFlashlight() {
    setFlashlightState(!g_flashlightOn);
}

bool getFlashlightState() {
    return g_flashlightOn;
}
