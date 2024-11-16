#include "gba.h"
#include "mode0.h"
#include "sprites.h"
#include "print.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "flashlight.h"
#include "doorKeys.h"
#include <stdlib.h>
#include <time.h>

// bg/sprite imports
#include "spritesheet2.h"
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
enum STATE {START, INSTRUCTIONS, GAME, LEVEL2, PAUSE, LOSE, WIN} state;
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
        switch(state) {
            case START:
                start();
                break;
            case INSTRUCTIONS:
                instructions();
                break;
            case GAME:
                game();
                break;
            case LEVEL2:
                level2();
                break;
            case PAUSE:
                pause();
                break;
            case LOSE:
                lose();
                break;
            default:
                break;
        }      
    }
}

void goToStart() {
    state = START;
}

void start() {
    if (BUTTON_PRESSED(BUTTON_START)) {
        mgba_printf("start button pressed, go to Instructions");
        goToInstructions();
    }
}

void goToInstructions() {
    DMANow(3, instructionsTiles, &CHARBLOCK[2], instructionsTilesLen/2);
    DMANow(3, instructionsPal, BG_PALETTE, instructionsPalLen / 2);
    DMANow(3, instructionsMap, &SCREENBLOCK[0], instructionsMapLen / 2);
    state = INSTRUCTIONS;
}

void instructions() {
    if (BUTTON_PRESSED(BUTTON_START)) {
        mgba_printf("start button pressed, go to game");
        goToGame();
    }
}

void goToGame() {
    mgba_printf("going to game");

    initGame();
    initKeysLevel1();
    // not actually random
    srand(frameCount);

    // DMA bg
    DMANow(3, forestBGTiles, &CHARBLOCK[2], forestBGTilesLen/2);
    DMANow(3, forestBGPal, BG_PALETTE, forestBGPalLen / 2);
    DMANow(3, forestBGMap, &SCREENBLOCK[0], forestBGMapLen / 2);

    // DMA sprite info 
    DMANow(3, spritesheet2Tiles, &CHARBLOCK[4], spritesheet2TilesLen / 2);
    DMANow(3, spritesheet2Pal, SPRITE_PAL, spritesheet2PalLen / 2);

    hideSprites();
    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*8);
    state = GAME;

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
void goToLevel2() {
    initGame();
    hideSprites();
    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*8);
    // initGame();
    state = LEVEL2;    
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

void goToPause() {
    state = PAUSE;
}

void pause() {
    if (BUTTON_PRESSED(BUTTON_START)) {
        mgba_printf("start button pressed, go to pause");
        goToGame();
    }
}

void goToLose() {
    hideSprites();
    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*4);
    // replaces the flashlight bg so it covers up the other sprites
    DMANow(3, LoseScreenTiles, &CHARBLOCK[2], LoseScreenTilesLen/2);
    DMANow(3, LoseScreenPal, BG_PALETTE, LoseScreenPalLen / 2);
    DMANow(3, LoseScreenMap, &SCREENBLOCK[0], LoseScreenMapLen / 2);
    state = LOSE;

}

void lose() {
    if (BUTTON_PRESSED(BUTTON_START)) {
        mgba_printf("start button pressed, go to start from lose");
        goToStart();
    }
}