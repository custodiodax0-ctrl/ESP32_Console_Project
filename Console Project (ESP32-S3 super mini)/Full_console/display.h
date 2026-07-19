#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Wire.h>
#include "config.h"

#if USE_SH1106_OLED
  #include <Adafruit_SH110X.h>
  extern Adafruit_SH1106G display;
  #define SSD1306_WHITE SH110X_WHITE
  #define SSD1306_BLACK SH110X_BLACK
  #define SSD1306_DISPLAYOFF SH110X_DISPLAYOFF
#else
  #include <Adafruit_GFX.h>
  #include <Adafruit_SSD1306.h>
  extern Adafruit_SSD1306 display;
#endif

void initDisplay();
void clearDisplay();
void renderDisplay();
void drawHeader(const char* title);

#endif // DISPLAY_H
