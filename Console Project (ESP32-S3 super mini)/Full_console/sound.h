#ifndef SOUND_H
#define SOUND_H

#include <Arduino.h>

void initSound();
void playTone(uint16_t freq, uint16_t durationMs);
void playClickSound();
void playAlarmSound();
void playSuccessSound();
void setSoundEnabled(bool enabled);
bool isSoundEnabled();

#endif // SOUND_H
