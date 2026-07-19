#include "battery.h"
#include "config.h"

void initBattery() {
    analogReadResolution(12); // 0..4095
    pinMode(PIN_BATTERY_ADC, INPUT);
}

float getBatteryVoltage() {
    uint32_t rawSum = 0;
    for (int i = 0; i < 10; i++) {
        rawSum += analogRead(PIN_BATTERY_ADC);
        delay(1);
    }
    float rawAvg = rawSum / 10.0f;
    // Assuming voltage divider (e.g. 100k/100k, multiplier 2.0) with 3.3V reference
    float sensedVolts = (rawAvg / 4095.0f) * 3.3f * 2.0f;
    
    // Fallback: if no voltage divider connected (rawAvg near 0 or max 3.3V), return default 3.9V (~85%)
    if (sensedVolts < 2.0f || sensedVolts > 4.5f) {
        return 3.9f;
    }
    return sensedVolts;
}

uint8_t getBatteryPercent() {
    float volts = getBatteryVoltage();
    if (volts >= 4.2f) return 100;
    if (volts <= 3.3f) return 0;
    return (uint8_t)(((volts - 3.3f) / (4.2f - 3.3f)) * 100.0f);
}
