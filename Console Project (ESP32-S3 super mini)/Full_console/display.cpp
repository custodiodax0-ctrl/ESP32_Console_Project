#include "display.h"
#include "config.h"

#if USE_SH1106_OLED
  Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#else
  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#endif

void initDisplay() {
    Wire.setPins(PIN_I2C_SDA, PIN_I2C_SCL);
    Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
    Wire.setClock(100000); // 100kHz standard I2C speed for max stability across shared OLED + DS3231 bus

#if USE_SH1106_OLED
    if (!display.begin(OLED_I2C_ADDR, true)) {
        Wire.setPins(PIN_I2C_SDA, PIN_I2C_SCL);
        Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
        display.begin(0x3D, true); // Try fallback address 0x3D
    }
#else
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDR)) {
        Wire.setPins(PIN_I2C_SDA, PIN_I2C_SCL);
        Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
        display.begin(SSD1306_SWITCHCAPVCC, 0x3D); // Try fallback address 0x3D
    }
#endif

    Wire.setPins(PIN_I2C_SDA, PIN_I2C_SCL);
    Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL); // Re-lock I2C pins

    display.clearDisplay();
    display.setTextWrap(false);
    display.setTextColor(SSD1306_WHITE);
    display.display();
}

void clearDisplay() {
    display.clearDisplay();
}

void renderDisplay() {
    display.display();
}

void drawHeader(const char* title) {
    display.fillRect(0, 0, 128, 12, SSD1306_WHITE);
    display.setTextColor(SSD1306_BLACK);
    display.setTextSize(1);
    display.setCursor(4, 2);
    display.print(title);
    display.setTextColor(SSD1306_WHITE);
}
