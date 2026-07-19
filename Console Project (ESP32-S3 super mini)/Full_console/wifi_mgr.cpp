#include "wifi_mgr.h"
#include <WiFi.h>

static bool g_wifiEnabled = false;
static float g_tempC = 27.5f;
static uint8_t g_humidity = 65;
static String g_condition = "Sunny";

void initWifiManager() {
    WiFi.mode(WIFI_OFF);
    g_wifiEnabled = false;
}

bool isWifiConnected() {
    return (g_wifiEnabled && (WiFi.status() == WL_CONNECTED));
}

void toggleWifi() {
    g_wifiEnabled = !g_wifiEnabled;
    if (g_wifiEnabled) {
        WiFi.mode(WIFI_STA);
        // Connect if credentials configured
    } else {
        WiFi.disconnect(true);
        WiFi.mode(WIFI_OFF);
    }
}

void updateWeatherAndNTP() {
    if (!isWifiConnected()) return;
    // NTP / Open-Meteo API update logic can run non-blockingly here
}

float getLatestTempC() {
    return g_tempC;
}

uint8_t getLatestHumidity() {
    return g_humidity;
}

const char* getWeatherConditionText() {
    return g_condition.c_str();
}
