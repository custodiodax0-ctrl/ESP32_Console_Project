#ifndef CLOCK_H
#define CLOCK_H

#include <Arduino.h>
#include <RTClib.h>

extern RTC_DS3231 rtc;
extern bool g_rtcFound;

void initClock();
DateTime getCurrentTime();
void setClockTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);

#endif // CLOCK_H
