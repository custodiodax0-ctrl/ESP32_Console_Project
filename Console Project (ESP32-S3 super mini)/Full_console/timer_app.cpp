#include "timer_app.h"
#include "display.h"
#include "buttons.h"
#include "sound.h"
#include "state.h"

static int g_timerMinutes = 5;
static int g_timerSeconds = 0;
static bool g_timerRunning = false;
static uint32_t g_timerTargetMillis = 0;

void initTimerApp() {
    g_timerMinutes = 5;
    g_timerSeconds = 0;
    g_timerRunning = false;
}

void updateTimerApp() {
    if (!g_timerRunning) {
        if (isButtonPressed(BTN_UP)) { playClickSound(); g_timerMinutes++; if (g_timerMinutes > 99) g_timerMinutes = 1; }
        if (isButtonPressed(BTN_DOWN)) { playClickSound(); g_timerMinutes--; if (g_timerMinutes < 1) g_timerMinutes = 99; }
        if (isButtonPressed(BTN_A)) {
            playClickSound();
            g_timerTargetMillis = millis() + ((g_timerMinutes * 60 + g_timerSeconds) * 1000);
            g_timerRunning = true;
        }
    } else {
        if (isButtonPressed(BTN_A) || isButtonPressed(BTN_B)) {
            playClickSound();
            g_timerRunning = false;
        }
    }

    if (isButtonPressed(BTN_BACK) || isButtonPressed(BTN_SELECT)) {
        playClickSound();
        goBack();
        return;
    }

    int displayMm = g_timerMinutes;
    int displaySs = g_timerSeconds;

    if (g_timerRunning) {
        uint32_t now = millis();
        if (now >= g_timerTargetMillis) {
            g_timerRunning = false;
            playAlarmSound();
            displayMm = 0;
            displaySs = 0;
        } else {
            uint32_t remainSec = (g_timerTargetMillis - now) / 1000;
            displayMm = remainSec / 60;
            displaySs = remainSec % 60;
        }
    }

    display.clearDisplay();
    drawHeader("COUNTDOWN TIMER");

    display.setTextSize(2);
    display.setCursor(32, 24);
    if (displayMm < 10) display.print("0");
    display.print(displayMm);
    display.print(":");
    if (displaySs < 10) display.print("0");
    display.print(displaySs);
    display.setTextSize(1);

    display.setCursor(12, 48);
    if (g_timerRunning) {
        display.print("[A/B] Cancel Timer");
    } else {
        display.print("[Up/Down] Set [A] Start");
    }

    display.display();
}
