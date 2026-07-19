#include "settings.h"
#include "display.h"
#include "buttons.h"
#include "sound.h"
#include "flashlight.h"
#include "wifi_mgr.h"
#include "bluetooth_mgr.h"
#include "state.h"

static int g_settingsIndex = 0;
static const int g_totalSettings = 4;

void initSettings() {
    g_settingsIndex = 0;
}

void updateSettings() {
    if (isButtonPressed(BTN_UP)) {
        playClickSound();
        g_settingsIndex--;
        if (g_settingsIndex < 0) g_settingsIndex = g_totalSettings - 1;
    }
    if (isButtonPressed(BTN_DOWN)) {
        playClickSound();
        g_settingsIndex++;
        if (g_settingsIndex >= g_totalSettings) g_settingsIndex = 0;
    }

    if (isButtonPressed(BTN_A)) {
        playClickSound();
        switch (g_settingsIndex) {
            case 0: setSoundEnabled(!isSoundEnabled()); break;
            case 1: toggleFlashlight(); break;
            case 2: toggleWifi(); break;
            case 3: toggleBluetooth(); break;
        }
    }

    if (isButtonPressed(BTN_B) || isButtonPressed(BTN_BACK) || isButtonPressed(BTN_SELECT)) {
        playClickSound();
        goBack();
        return;
    }

    display.clearDisplay();
    drawHeader("SYSTEM SETTINGS");

    const char* options[4] = {
        isSoundEnabled() ? "1. Sound: [ON]" : "1. Sound: [OFF]",
        getFlashlightState() ? "2. Flashlight: [ON]" : "2. Flashlight: [OFF]",
        isWifiConnected() ? "3. Wi-Fi: [ON]" : "3. Wi-Fi: [OFF]",
        isBluetoothEnabled() ? "4. Bluetooth: [ON]" : "4. Bluetooth: [OFF]"
    };

    for (int i = 0; i < 4; i++) {
        int y = 16 + (i * 11);
        if (i == g_settingsIndex) {
            display.fillRect(4, y - 1, 120, 10, SSD1306_WHITE);
            display.setTextColor(SSD1306_BLACK);
            display.setCursor(8, y);
            display.print(options[i]);
            display.setTextColor(SSD1306_WHITE);
        } else {
            display.setCursor(14, y);
            display.print(options[i]);
        }
    }

    display.display();
}
