#include "about.h"
#include "display.h"
#include "buttons.h"
#include "sound.h"
#include "state.h"

void initAbout() {}

void updateAbout() {
    if (isButtonPressed(BTN_B) || isButtonPressed(BTN_BACK) || isButtonPressed(BTN_A) || isButtonPressed(BTN_SELECT)) {
        playClickSound();
        goBack();
        return;
    }

    display.clearDisplay();
    drawHeader("ABOUT CONSOLE");

    display.setCursor(4, 16);
    display.print("MCU: ESP32-S3 Mini");

    display.setCursor(4, 27);
    display.print("OLED: 1.3\" SSD1306");

    display.setCursor(4, 38);
    display.print("RTC: DS3231 I2C");

    display.setCursor(4, 49);
    display.print("Free Heap: ");
    display.print(ESP.getFreeHeap() / 1024);
    display.print(" KB");

    display.display();
}
