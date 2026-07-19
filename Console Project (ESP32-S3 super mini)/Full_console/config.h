#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ── Pin Allocation (GPIO 1 to 13) ──────────────────────────────────────────
#define PIN_BTN_UP       1
#define PIN_BTN_DOWN     2
#define PIN_BTN_LEFT     3
#define PIN_BTN_RIGHT    4

#define PIN_I2C_SDA      5
#define PIN_I2C_SCL      6

#define PIN_BTN_A        7
#define PIN_BTN_B        8
#define PIN_BTN_SELECT   9
#define PIN_BTN_BACK     10

#define PIN_BUZZER       11
#define PIN_FLASHLIGHT   12
#define PIN_BATTERY_ADC  13

// ── Display Parameters ─────────────────────────────────────────────────────
#define SCREEN_WIDTH     128
#define SCREEN_HEIGHT    64
#define OLED_RESET       -1
#define OLED_I2C_ADDR    0x3C

// Set to 1 if using 1.3" SH1106 OLED (most common for 1.3"), or 0 for 0.96"/1.3" SSD1306
#define USE_SH1106_OLED  1 

// ── Power & Timeout Defaults ──────────────────────────────────────────────
#define DEEP_SLEEP_TIMEOUT_MS  60000  // 60 seconds of inactivity
#define DEBOUNCE_DELAY_MS      30     // Button debounce threshold

#endif // CONFIG_H
