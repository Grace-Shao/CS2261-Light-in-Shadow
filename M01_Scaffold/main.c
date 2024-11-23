#include "helpers/gba.h"
#include "helpers/mode0.h"
#include "sprites.h"
#include "print.h"
#include "game.h"
#include "state.h"
#include "player.h"
#include "enemy.h"
#include "flashlight.h"
#include "doorKeys.h"
#include <stdlib.h>
#include <time.h>

// bg/sprite imports
#include "spritesheet2.h"
#include "artAssetsGBA/apartmentBGMap.h"
#include "venomMonster.h"
#include "instructions.h"
#include "loseScreen.h"
#include "forestBG.h"
#include "light.h"

void start();
void goToStart();
void instructions();
void goToInstructions();
void game();
void goToGame();
void goToPause();
void pause();
void goToWin();
void win();
void initialize();
void goToLose();
void lose();

// States
STATE state = START;
OBJ_ATTR shadowOAM[128];
typedef enum {DOWN, RIGHT, UP, LEFT} DIRECTION;

// Button Variables
unsigned short buttons;
unsigned short oldButtons;


void initialize() {
    // Set up basic registers 
    REG_DISPCTL = MODE(0) | BG_ENABLE(2) | BG_ENABLE(3) | SPRITE_ENABLE;
    // set up orignal background
    REG_BG2CNT = BG_SCREENBLOCK(0) | BG_CHARBLOCK(2) | 3;
    // light bg
    REG_BG3CNT = BG_SCREENBLOCK(1) | BG_CHARBLOCK(3) | 1;

    buttons = REG_BUTTONS;
    oldButtons = 0;

    mgba_open();
    mgba_printf("initialized");
    //initSound();
    goToStart();
}

int main() {
    initialize();
    while(1) {
        oldButtons = buttons;
        buttons = REG_BUTTONS;
        
        frameCount += 1;
        // State Machine
        updateGameState(state);
    }
}

void start() {
    if (BUTTON_PRESSED(BUTTON_START)) {
        mgba_printf("start button pressed, go to Instructions");
        goToInstructions();
    }
}

void instructions() {
    if (BUTTON_PRESSED(BUTTON_START)) {
        mgba_printf("start button pressed, go to game");
        goToGame();
    }
}

void game() {
    if (BUTTON_PRESSED(BUTTON_START)) {
        mgba_printf("start button pressed, go to pause");
        goToPause();
    }
    updateGame();
    drawGame();
    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*4);
    if (lives < 1 || batteryRemaining < 0) {
        goToLose();
    }
 
    if (BUTTON_PRESSED(BUTTON_SELECT)) {
        mgba_printf("select button pressed, go to lvl2");
        goToLevel2();
    }
}

void level2() {
    updateGame();
    drawGame();
    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*4);
    if (lives < 1 || batteryRemaining < 0) {
        goToLose();
    }
}



void pause() {
    if (BUTTON_PRESSED(BUTTON_START)) {
        mgba_printf("start button pressed, go to pause");
        goToGame();
    }
}

void lose() {
    if (BUTTON_PRESSED(BUTTON_START)) {
        mgba_printf("start button pressed, go to start from lose");
        goToStart();
    }
}