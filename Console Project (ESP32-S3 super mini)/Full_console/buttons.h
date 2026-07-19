#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>

enum ButtonID {
    BTN_UP = 0,
    BTN_DOWN,
    BTN_LEFT,
    BTN_RIGHT,
    BTN_A,
    BTN_B,
    BTN_SELECT,
    BTN_BACK,
    NUM_BUTTONS
};

void initButtons();
void updateButtons();

bool isButtonPressed(ButtonID id);
bool isButtonHeld(ButtonID id);
bool isButtonJustReleased(ButtonID id);

uint32_t getLastActivityTime();
void resetActivityTimer();

#endif // BUTTONS_H
