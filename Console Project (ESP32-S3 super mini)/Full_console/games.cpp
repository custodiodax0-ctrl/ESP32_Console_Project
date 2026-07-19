#include "games.h"
#include "display.h"
#include "buttons.h"
#include "sound.h"
#include "state.h"

struct Point {
    int8_t x;
    int8_t y;
};

static Point g_snake[32];
static uint8_t g_snakeLength = 4;
static int8_t g_dirX = 1;
static int8_t g_dirY = 0;
static Point g_food = { 10, 5 };
static uint16_t g_score = 0;
static bool g_gameOver = false;
static uint32_t g_lastMoveTime = 0;

void initGames() {
    g_snakeLength = 4;
    g_dirX = 1;
    g_dirY = 0;
    g_score = 0;
    g_gameOver = false;
    g_food = { 15, 6 };
    for (int i = 0; i < g_snakeLength; i++) {
        g_snake[i] = { (int8_t)(6 - i), 5 };
    }
    g_lastMoveTime = millis();
}

void updateGames() {
    if (isButtonPressed(BTN_BACK) || isButtonPressed(BTN_SELECT)) {
        playClickSound();
        goBack();
        return;
    }

    if (g_gameOver) {
        if (isButtonPressed(BTN_A)) {
            playClickSound();
            initGames();
        }
        display.clearDisplay();
        drawHeader("SNAKE GAME");
        display.setCursor(32, 24);
        display.print("GAME OVER");
        display.setCursor(24, 38);
        display.print("Score: ");
        display.print(g_score);
        display.setCursor(14, 52);
        display.print("Press [A] Restart");
        display.display();
        return;
    }

    if (isButtonPressed(BTN_UP) && g_dirY == 0) { g_dirX = 0; g_dirY = -1; }
    if (isButtonPressed(BTN_DOWN) && g_dirY == 0) { g_dirX = 0; g_dirY = 1; }
    if (isButtonPressed(BTN_LEFT) && g_dirX == 0) { g_dirX = -1; g_dirY = 0; }
    if (isButtonPressed(BTN_RIGHT) && g_dirX == 0) { g_dirX = 1; g_dirY = 0; }

    uint32_t now = millis();
    if (now - g_lastMoveTime > 150) {
        g_lastMoveTime = now;

        Point newHead = { (int8_t)(g_snake[0].x + g_dirX), (int8_t)(g_snake[0].y + g_dirY) };

        // Wall collision (24x10 grid on 128x64 display, 4x4 px per cell, offset y=16)
        if (newHead.x < 0 || newHead.x >= 32 || newHead.y < 0 || newHead.y >= 11) {
            g_gameOver = true;
            playAlarmSound();
            return;
        }

        // Self collision
        for (int i = 0; i < g_snakeLength; i++) {
            if (g_snake[i].x == newHead.x && g_snake[i].y == newHead.y) {
                g_gameOver = true;
                playAlarmSound();
                return;
            }
        }

        // Move body
        for (int i = g_snakeLength - 1; i > 0; i--) {
            g_snake[i] = g_snake[i - 1];
        }
        g_snake[0] = newHead;

        // Food collision
        if (newHead.x == g_food.x && newHead.y == g_food.y) {
            playSuccessSound();
            g_score += 10;
            if (g_snakeLength < 32) g_snakeLength++;
            g_food.x = random(0, 31);
            g_food.y = random(0, 10);
        }
    }

    display.clearDisplay();
    drawHeader("RETRO SNAKE");

    // Draw food
    display.fillRect(g_food.x * 4, 16 + (g_food.y * 4), 3, 3, SSD1306_WHITE);

    // Draw snake
    for (int i = 0; i < g_snakeLength; i++) {
        display.fillRect(g_snake[i].x * 4, 16 + (g_snake[i].y * 4), 3, 3, SSD1306_WHITE);
    }

    display.display();
}
