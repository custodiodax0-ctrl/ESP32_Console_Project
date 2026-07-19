#include "buttons.h"
#include "config.h"

struct ButtonState {
    uint8_t pin;
    bool lastRawState;
    bool stableState;
    bool justPressed;
    bool justReleased;
    uint32_t lastDebounceTime;
    uint32_t pressStartTime;
};

static ButtonState buttons[NUM_BUTTONS] = {
    { PIN_BTN_UP,     HIGH, HIGH, false, false, 0, 0 },
    { PIN_BTN_DOWN,   HIGH, HIGH, false, false, 0, 0 },
    { PIN_BTN_LEFT,   HIGH, HIGH, false, false, 0, 0 },
    { PIN_BTN_RIGHT,  HIGH, HIGH, false, false, 0, 0 },
    { PIN_BTN_A,      HIGH, HIGH, false, false, 0, 0 },
    { PIN_BTN_B,      HIGH, HIGH, false, false, 0, 0 },
    { PIN_BTN_SELECT, HIGH, HIGH, false, false, 0, 0 },
    { PIN_BTN_BACK,   HIGH, HIGH, false, false, 0, 0 }
};

static uint32_t g_lastActivity = 0;

void initButtons() {
    for (int i = 0; i < NUM_BUTTONS; i++) {
        pinMode(buttons[i].pin, INPUT_PULLUP);
        buttons[i].lastRawState = digitalRead(buttons[i].pin);
        buttons[i].stableState  = buttons[i].lastRawState;
        buttons[i].justPressed  = false;
        buttons[i].justReleased = false;
    }
    g_lastActivity = millis();
}

void updateButtons() {
    uint32_t now = millis();

    for (int i = 0; i < NUM_BUTTONS; i++) {
        buttons[i].justPressed  = false;
        buttons[i].justReleased = false;

        bool reading = digitalRead(buttons[i].pin);

        if (reading != buttons[i].lastRawState) {
            buttons[i].lastDebounceTime = now;
            buttons[i].lastRawState = reading;
        }

        if ((now - buttons[i].lastDebounceTime) > DEBOUNCE_DELAY_MS) {
            if (reading != buttons[i].stableState) {
                buttons[i].stableState = reading;

                // Active LOW buttons (pressed = LOW)
                if (buttons[i].stableState == LOW) {
                    buttons[i].justPressed = true;
                    buttons[i].pressStartTime = now;
                    g_lastActivity = now;
                } else {
                    buttons[i].justReleased = true;
                    g_lastActivity = now;
                }
            }
        }
    }
}

bool isButtonPressed(ButtonID id) {
    if (id < 0 || id >= NUM_BUTTONS) return false;
    return buttons[id].justPressed;
}

bool isButtonHeld(ButtonID id) {
    if (id < 0 || id >= NUM_BUTTONS) return false;
    return (buttons[id].stableState == LOW);
}

bool isButtonJustReleased(ButtonID id) {
    if (id < 0 || id >= NUM_BUTTONS) return false;
    return buttons[id].justReleased;
}

uint32_t getLastActivityTime() {
    return g_lastActivity;
}

void resetActivityTimer() {
    g_lastActivity = millis();
}
