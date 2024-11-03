#include "gba.h"
#include "mode0.h"
#include "sprites.h"
#include "print.h"
#include "player.h"

// sprite imports
#include "gengar.h"
#include "background.h"

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
    REG_DISPCTL = MODE(0) | BG_ENABLE(2) | SPRITE_ENABLE;
    REG_BG2CNT = BG_SCREENBLOCK(0) | BG_CHARBLOCK(2);
    
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
             
        // State Machine
        switch(state) {
            case START:
                start();
                break;
            // case INSTRUCTIONS:
            //     instructions();
            //     break;
            case GAME:
                game();
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
    //initGame();
    initPlayer();
}

void start() {
    state = START;
    if (BUTTON_HELD(BUTTON_START)) {
        mgba_printf("start button pressed");
        goToGame();
    }
}

void goToGame() {
    mgba_printf("going to game");

    //initGame();
    // later put this in initGame maybe
    DMANow(3, backgroundTiles, &CHARBLOCK[2], backgroundTilesLen/2);
    DMANow(3, backgroundPal, BG_PALETTE, backgroundPalLen / 2);
    DMANow(3, backgroundMap, &SCREENBLOCK[0], backgroundMapLen / 2);

     // DMA sprite info 
    DMANow(3, gengarTiles, &CHARBLOCK[4], gengarTilesLen / 2);
    DMANow(3, gengarPal, SPRITE_PAL, gengarPalLen / 2);

    //hideSprites();
    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*8);
    state = GAME;

}

void game() {
    //shineLight(1, 1, 100, 100);
    updatePlayer();
    drawPlayer();
    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*4);
}