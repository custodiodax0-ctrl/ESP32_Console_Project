#ifndef WIFI_MGR_H
#define WIFI_MGR_H

#include <Arduino.h>

void initWifiManager();
bool isWifiConnected();
void toggleWifi();
void updateWeatherAndNTP();

float getLatestTempC();
uint8_t getLatestHumidity();
const char* getWeatherConditionText();

#endif // WIFI_MGR_H
