#include "stopwatch.h"
#include "display.h"
#include "buttons.h"
#include "sound.h"
#include "state.h"

static bool g_swRunning = false;
static uint32_t g_swStartTime = 0;
static uint32_t g_swElapsedMillis = 0;
static uint32_t g_swLapMillis = 0;

void initStopwatch() {
    g_swRunning = false;
    g_swStartTime = 0;
    g_swElapsedMillis = 0;
    g_swLapMillis = 0;
}

void updateStopwatch() {
    if (isButtonPressed(BTN_A)) {
        playClickSound();
        if (g_swRunning) {
            g_swElapsedMillis += (millis() - g_swStartTime);
            g_swRunning = false;
        } else {
            g_swStartTime = millis();
            g_swRunning = true;
        }
    }
    if (isButtonPressed(BTN_B)) {
        playClickSound();
        if (g_swRunning) {
            g_swLapMillis = g_swElapsedMillis + (millis() - g_swStartTime);
        } else {
            g_swElapsedMillis = 0;
            g_swLapMillis = 0;
        }
    }
    if (isButtonPressed(BTN_BACK) || isButtonPressed(BTN_SELECT)) {
        playClickSound();
        goBack();
        return;
    }

    uint32_t currentElapsed = g_swElapsedMillis;
    if (g_swRunning) {
        currentElapsed += (millis() - g_swStartTime);
    }

    uint32_t totalSec = currentElapsed / 1000;
    uint32_t ms = (currentElapsed % 1000) / 10;
    uint32_t mm = totalSec / 60;
    uint32_t ss = totalSec % 60;

    display.clearDisplay();
    drawHeader("STOPWATCH");

    display.setTextSize(2);
    display.setCursor(16, 24);
    if (mm < 10) display.print("0");
    display.print(mm);
    display.print(":");
    if (ss < 10) display.print("0");
    display.print(ss);
    display.print(".");
    if (ms < 10) display.print("0");
    display.print(ms);
    display.setTextSize(1);

    display.setCursor(4, 46);
    display.print(g_swRunning ? "[A] Pause" : "[A] Start");
    display.setCursor(70, 46);
    display.print(g_swRunning ? "[B] Lap" : "[B] Reset");

    display.display();
}
