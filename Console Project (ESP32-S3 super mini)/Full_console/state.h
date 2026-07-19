#ifndef STATE_H
#define STATE_H

enum AppState {
    APP_DASHBOARD,
    APP_MAIN_MENU,
    APP_CLOCK,
    APP_CALENDAR,
    APP_STOPWATCH,
    APP_TIMER,
    APP_GAMES,
    APP_SETTINGS,
    APP_FLASHLIGHT,
    APP_ABOUT
};

extern AppState gCurrentState;
extern AppState gPreviousState;

void setState(AppState newState);
void goBack();
void goHome();

#endif // STATE_H
