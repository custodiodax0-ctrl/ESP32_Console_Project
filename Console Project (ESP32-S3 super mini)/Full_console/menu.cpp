#include "menu.h"
#include "display.h"
#include "buttons.h"
#include "sound.h"
#include "state.h"

struct MenuItem {
    const char* label;
    AppState targetState;
};

static MenuItem g_menuItems[] = {
    { "1. Clock & RTC",   APP_CLOCK },
    { "2. Calendar",      APP_CALENDAR },
    { "3. Stopwatch",     APP_STOPWATCH },
    { "4. Timer",         APP_TIMER },
    { "5. Retro Games",   APP_GAMES },
    { "6. Flashlight",    APP_FLASHLIGHT },
    { "7. Settings",      APP_SETTINGS },
    { "8. About System",  APP_ABOUT }
};

static const int g_totalMenuItems = sizeof(g_menuItems) / sizeof(g_menuItems[0]);
static int g_selectedIndex = 0;

void initMenu() {
    g_selectedIndex = 0;
}

void updateMenu() {
    if (isButtonPressed(BTN_UP)) {
        playClickSound();
        g_selectedIndex--;
        if (g_selectedIndex < 0) g_selectedIndex = g_totalMenuItems - 1;
    }
    if (isButtonPressed(BTN_DOWN)) {
        playClickSound();
        g_selectedIndex++;
        if (g_selectedIndex >= g_totalMenuItems) g_selectedIndex = 0;
    }
    if (isButtonPressed(BTN_A) || isButtonPressed(BTN_SELECT)) {
        playClickSound();
        setState(g_menuItems[g_selectedIndex].targetState);
        return;
    }
    if (isButtonPressed(BTN_B) || isButtonPressed(BTN_BACK)) {
        playClickSound();
        goHome();
        return;
    }

    display.clearDisplay();
    drawHeader("MAIN MENU");

    int startIdx = (g_selectedIndex / 4) * 4;
    for (int i = 0; i < 4 && (startIdx + i) < g_totalMenuItems; i++) {
        int idx = startIdx + i;
        int y = 16 + (i * 12);

        if (idx == g_selectedIndex) {
            display.fillRect(4, y - 1, 120, 11, SSD1306_WHITE);
            display.setTextColor(SSD1306_BLACK);
            display.setCursor(8, y);
            display.print("> ");
            display.print(g_menuItems[idx].label);
            display.setTextColor(SSD1306_WHITE);
        } else {
            display.setCursor(14, y);
            display.print(g_menuItems[idx].label);
        }
    }

    display.display();
}
