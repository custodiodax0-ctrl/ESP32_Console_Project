#include <Arduino.h>
#include "config.h"
#include "state.h"
#include "buttons.h"
#include "display.h"
#include "sound.h"
#include "flashlight.h"
#include "battery.h"
#include "clock.h"
#include "wifi_mgr.h"
#include "bluetooth_mgr.h"
#include "dashboard.h"
#include "menu.h"
#include "calendar.h"
#include "stopwatch.h"
#include "timer_app.h"
#include "games.h"
#include "settings.h"
#include "about.h"

// ── Global State ──────────────────────────────────────────────────────────────
AppState gCurrentState  = APP_DASHBOARD;
AppState gPreviousState = APP_DASHBOARD;

void setState(AppState newState) {
    if (gCurrentState != newState) {
        gPreviousState = gCurrentState;
        gCurrentState  = newState;

        // Initialize state-specific views if needed
        switch (newState) {
            case APP_DASHBOARD: initDashboard(); break;
            case APP_MAIN_MENU: initMenu(); break;
            case APP_CALENDAR:  initCalendar(); break;
            case APP_STOPWATCH: initStopwatch(); break;
            case APP_TIMER:     initTimerApp(); break;
            case APP_GAMES:     initGames(); break;
            case APP_SETTINGS:  initSettings(); break;
            case APP_ABOUT:     initAbout(); break;
            default: break;
        }
    }
    resetActivityTimer();
}

void goBack() {
    if (gPreviousState != gCurrentState)
        setState(gPreviousState);
    else
        setState(APP_DASHBOARD);
}

void goHome() {
    setState(APP_DASHBOARD);
}

// ── Deep Sleep ────────────────────────────────────────────────────────────────
void checkDeepSleepInactivity() {
    if ((millis() - getLastActivityTime()) > DEEP_SLEEP_TIMEOUT_MS) {
        // Turn off display and LED before sleep
        setFlashlightState(false);
        display.clearDisplay();
        display.display();
#if USE_SH1106_OLED
        display.oled_command(SH110X_DISPLAYOFF);
#else
        display.ssd1306_command(SSD1306_DISPLAYOFF);
#endif

        // Configure wakeup sources on D-pad or A button (active LOW)
        esp_sleep_enable_ext0_wakeup((gpio_num_t)PIN_BTN_A, 0);

        esp_deep_sleep_start();
    }
}

// ── Arduino Setup ─────────────────────────────────────────────────────────────
void setup() {
    // 1. Initialize hardware I2C bus on GPIO 5 & 6 first
    Serial.begin(115200);
    delay(2000);
    Serial.println("\n--- Starting GameBoy Console ---");
    Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
    Wire.setClock(100000);

    Serial.printf("Scanning I2C bus on SDA=%d, SCL=%d...\n", PIN_I2C_SDA, PIN_I2C_SCL);
    int nDevices = 0;
    for (byte address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        if (Wire.endTransmission() == 0) {
            Serial.printf("I2C device found at address 0x%02X\n", address);
            nDevices++;
        }
    }
    if (nDevices == 0) {
        Serial.println("No I2C devices found! Check wiring of SDA and SCL pins.");
    }

    // 2. Initialize Subsystems
    initButtons();
    initDisplay();
    initSound();
    initFlashlight();
    initBattery();
    initClock();
    initWifiManager();
    initBluetoothManager();

    // Play startup chime
    playSuccessSound();

    setState(APP_DASHBOARD);
}

// ── Arduino Loop ──────────────────────────────────────────────────────────────
void loop() {
    // 1. Poll inputs non-blockingly
    updateButtons();

    // 2. State Machine Dispatcher
    switch (gCurrentState) {
        case APP_DASHBOARD:
            updateDashboard();
            break;

        case APP_MAIN_MENU:
            updateMenu();
            break;

        case APP_CALENDAR:
            updateCalendar();
            break;

        case APP_STOPWATCH:
            updateStopwatch();
            break;

        case APP_TIMER:
            updateTimerApp();
            break;

        case APP_GAMES:
            updateGames();
            break;

        case APP_SETTINGS:
            updateSettings();
            break;

        case APP_ABOUT:
            updateAbout();
            break;

        case APP_FLASHLIGHT:
            toggleFlashlight();
            goBack();
            break;

        default:
            updateDashboard();
            break;
    }

    // 3. Power Management Check
    checkDeepSleepInactivity();

    delay(10);
}
