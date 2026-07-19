#include "clock.h"
#include "config.h"

RTC_DS3231 rtc;
bool g_rtcFound = false;
static uint32_t g_systemTimeOffsetSec = 0;

void initClock() {
    // Ensure I2C pins remain locked to PIN_I2C_SDA and PIN_I2C_SCL
    Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
    g_rtcFound = rtc.begin(&Wire);
    Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL); // Re-assert custom GPIO pins to prevent RTClib from resetting I2C pin matrix

    if (g_rtcFound && rtc.lostPower()) {
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
}

DateTime getCurrentTime() {
    if (g_rtcFound) {
        return rtc.now();
    }
    // Fallback: system time based on millis()
    uint32_t currentSec = (millis() / 1000) + g_systemTimeOffsetSec;
    return DateTime((uint32_t)currentSec);
}

void setClockTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second) {
    DateTime dt(year, month, day, hour, minute, second);
    if (g_rtcFound) {
        rtc.adjust(dt);
    }
    g_systemTimeOffsetSec = dt.unixtime() - (millis() / 1000);
}
