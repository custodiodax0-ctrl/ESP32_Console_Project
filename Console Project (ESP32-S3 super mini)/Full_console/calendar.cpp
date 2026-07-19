#include "calendar.h"
#include "display.h"
#include "clock.h"
#include "buttons.h"
#include "sound.h"
#include "state.h"

static int g_calMonth = 1;
static int g_calYear = 2026;

static int daysInMonth(int m, int y) {
    if (m == 2) {
        if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) return 29;
        return 28;
    }
    if (m == 4 || m == 6 || m == 9 || m == 11) return 30;
    return 31;
}

void initCalendar() {
    DateTime now = getCurrentTime();
    g_calMonth = now.month();
    g_calYear = now.year();
}

void updateCalendar() {
    if (isButtonPressed(BTN_LEFT)) {
        playClickSound();
        g_calMonth--;
        if (g_calMonth < 1) { g_calMonth = 12; g_calYear--; }
    }
    if (isButtonPressed(BTN_RIGHT)) {
        playClickSound();
        g_calMonth++;
        if (g_calMonth > 12) { g_calMonth = 1; g_calYear++; }
    }
    if (isButtonPressed(BTN_B) || isButtonPressed(BTN_BACK)) {
        playClickSound();
        goBack();
        return;
    }

    display.clearDisplay();
    drawHeader("CALENDAR");

    display.setCursor(4, 16);
    display.print(g_calYear);
    display.print("-");
    if (g_calMonth < 10) display.print("0");
    display.print(g_calMonth);

    display.setCursor(4, 28);
    display.print("Su Mo Tu We Th Fr Sa");

    int totalDays = daysInMonth(g_calMonth, g_calYear);
    int startCol = 0; // simplified offset for grid
    int row = 0;
    int col = startCol;

    for (int day = 1; day <= totalDays; day++) {
        int x = 4 + (col * 18);
        int y = 38 + (row * 8);

        if (y > 56) break;

        display.setCursor(x, y);
        if (day < 10) display.print(" ");
        display.print(day);

        col++;
        if (col >= 7) {
            col = 0;
            row++;
        }
    }

    display.display();
}
