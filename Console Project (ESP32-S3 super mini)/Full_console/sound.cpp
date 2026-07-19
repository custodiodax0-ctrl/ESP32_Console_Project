#include "sound.h"
#include "config.h"

static bool g_soundEnabled = true;

void initSound() {
    pinMode(PIN_BUZZER, OUTPUT);
    digitalWrite(PIN_BUZZER, LOW);
}

void playTone(uint16_t freq, uint16_t durationMs) {
    if (!g_soundEnabled) return;
    tone(PIN_BUZZER, freq, durationMs);
}

void playClickSound() {
    playTone(1200, 15);
}

void playAlarmSound() {
    if (!g_soundEnabled) return;
    for (int i = 0; i < 3; i++) {
        tone(PIN_BUZZER, 2000, 100);
        delay(120);
        tone(PIN_BUZZER, 1500, 100);
        delay(120);
    }
}

void playSuccessSound() {
    if (!g_soundEnabled) return;
    tone(PIN_BUZZER, 800, 50);
    delay(60);
    tone(PIN_BUZZER, 1200, 80);
}

void setSoundEnabled(bool enabled) {
    g_soundEnabled = enabled;
}

bool isSoundEnabled() {
    return g_soundEnabled;
}
