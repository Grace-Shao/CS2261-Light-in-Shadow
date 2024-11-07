#include "gba.h"
#include "mode0.h"
#include "sprites.h"
#include "print.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include <stdlib.h>
#include <time.h>

// bg/sprite imports
#include "gengar.h"
#include "instructions.h"
#include "background.h"
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
enum STATE {START, INSTRUCTIONS, GAME, PAUSE, LOSE, WIN} state;
OBJ_ATTR shadowOAM[128];
typedef enum {DOWN, RIGHT, UP, LEFT} DIRECTION;

// Button Variables
unsigned short buttons;
unsigned short oldButtons;


void initialize() {
    // Set up basic registers 
    REG_DISPCTL = MODE(0) | BG_ENABLE(2) | BG_ENABLE(3) | SPRITE_ENABLE;
    // set up orignal background
    REG_BG2CNT = BG_SCREENBLOCK(0) | BG_CHARBLOCK(2) | 2;
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
            case PAUSE:
                pause();
                break;
            // case LOSE:
            //     lose();
            //     break;
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
    // not actually random
    srand(frameCount);

    // DMA bg
    DMANow(3, backgroundTiles, &CHARBLOCK[2], backgroundTilesLen/2);
    DMANow(3, backgroundPal, BG_PALETTE, backgroundPalLen / 2);
    DMANow(3, backgroundMap, &SCREENBLOCK[0], backgroundMapLen / 2);

    // // dma light 
    // DMANow(3, lightTiles, &CHARBLOCK[3], lightTilesLen/2);
    // //DMANow(3, lightPal, BG_PALETTE, lightPalLen / 2);
    // DMANow(3, lightMap, &SCREENBLOCK[1], lightMapLen / 2);

     // DMA sprite info 
    DMANow(3, gengarTiles, &CHARBLOCK[4], gengarTilesLen / 2);
    DMANow(3, gengarPal, SPRITE_PAL, gengarPalLen / 2);

    //hideSprites();
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