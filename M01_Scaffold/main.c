#include "helpers/gba.h"
#include "helpers/mode0.h"
#include "helpers/sprites.h"
#include "helpers/digitalSound.h"
#include "playSound.h"
#include "print.h"
#include "game.h"
#include "state.h"
#include "player.h"
#include "enemy.h"
#include "flashlight.h"
#include "doorKeys.h"
#include "vfx.h"
#include <stdlib.h>
#include <time.h>

// bg/sprite imports
#include "artAssetsGBA/spritesheet2.h"
#include "artAssetsGBA/instructions.h"
#include "artAssetsGBA/loseScreen.h"
#include "artAssetsGBA/forestBG.h"

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
    REG_BG3CNT = BG_SCREENBLOCK(0) | BG_CHARBLOCK(3) | BG_SIZE_WIDE | 3;
    // light bg
    REG_BG2CNT = BG_SCREENBLOCK(2) | BG_CHARBLOCK(2) | 1;
    // for letters (prob should not be called bg1)
    //REG_BG0CNT = BG_SCREENBLOCK(2) | BG_CHARBLOCK(1) | 0;

    buttons = REG_BUTTONS;
    oldButtons = 0;

    mgba_open();
    mgba_printf("initialized");
    setUpInterrupts();
    setupSounds();
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
    if (frameCount % 5 == 0) {
        hOff += 1;
    }

    if (BUTTON_PRESSED(BUTTON_START)) {
        mgba_printf("start button pressed, go to Instructions");
        goToInstructions();
    }
    waitForVBlank();
    REG_BG2HOFF = hOff;

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
    if (BUTTON_PRESSED(BUTTON_DOWN)) {
        mgba_printf("modified tile");
        SCREENBLOCK[0].tilemap[OFFSET(6, 2, 32)] = TILEMAP_ENTRY_TILEID(12);
    }
    spawnCracks();
    // if (BUTTON_PRESSED(BUTTON_DOWN)) {
    //     mgba_printf("modified tile");
    //     SCREENBLOCK[2].tilemap[OFFSET(6, 2, 32)] = TILEMAP_ENTRY_TILEID(2);
    // }
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
    flashRed();
    spawnCracks();

    updateGame();
    drawGame();
    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*4);
    if (lives < 1 || batteryRemaining < 0) {
        goToLose();
    }
    if (BUTTON_PRESSED(BUTTON_SELECT)) {
        mgba_printf("select button pressed, go to lvl3");
        goToLevel3();
    }
}

void level3() {
    updateGame();
    drawGame();
    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*4);
    if (lives < 1 || batteryRemaining < 0) {
        goToLose();
    }
    if (BUTTON_PRESSED(BUTTON_START)) {
        mgba_printf("start button pressed, go to lose");
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