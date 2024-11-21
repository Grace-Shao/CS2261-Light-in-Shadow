#include "gba.h"
#include "mode0.h"
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
#include "venomMonster.h"
#include "instructions.h"
#include "loseScreen.h"
#include "forestBG.h"
#include "light.h"

void updateGameState(STATE state) {
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

void goToStart() {
    initGame();
    state = START;
}

void goToInstructions() {
    DMANow(3, instructionsTiles, &CHARBLOCK[2], instructionsTilesLen/2);
    DMANow(3, instructionsPal, BG_PALETTE, instructionsPalLen / 2);
    DMANow(3, instructionsMap, &SCREENBLOCK[0], instructionsMapLen / 2);
    state = INSTRUCTIONS;
}

void goToGame() {
    mgba_printf("going to game");
    srand(frameCount);

    initKeysLevel1();
    initDoorsLevel1();
    

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

void goToLevel2() {
    mgba_printf("going to lvl2");
    //initGame();
    hideSprites();
    initDoorsLevel2();
    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*8);
    
    // initGame();
    state = LEVEL2;    
}

void goToPause() {
    state = PAUSE;
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
