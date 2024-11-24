#include "helpers/gba.h"
#include "helpers/mode0.h"
#include "helpers/sprites.h"
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
#include "artAssetsGBA/spritesheet2.h"
#include "artAssetsGBA/apartmentBGMap.h"
#include "artAssetsGBA/interiorsPalette.h"
#include "artAssetsGBA/letters.h"
#include "artAssetsGBA/lightRight.h"
#include "artAssetsGBA/instructions.h"
#include "artAssetsGBA/loseScreen.h"
#include "artAssetsGBA/forestBG.h"

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
    DMANow(3, instructionsTiles, &CHARBLOCK[3], instructionsTilesLen/2);
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
    // DMANow(3, forestBGTiles, &CHARBLOCK[3], forestBGTilesLen/2);
    // DMANow(3, forestBGPal, BG_PALETTE, forestBGPalLen / 2);
    // DMANow(3, forestBGMap, &SCREENBLOCK[0], forestBGMapLen / 2);
    DMANow(3, interiorsPaletteTiles, &CHARBLOCK[3], interiorsPaletteTilesLen /2);
    DMANow(3, interiorsPalettePal, BG_PALETTE, interiorsPalettePalLen / 2);
    DMANow(3, apartmentBGMapMap, &SCREENBLOCK[0], apartmentBGMapLen / 2);

    // DMA flashlight (starts r)
    DMANow(3, lightRightTiles, &CHARBLOCK[2], lightRightTilesLen/2);
    DMANow(3, lightRightMap, &SCREENBLOCK[1], lightRightMapLen / 2);

    // DMA sprite info 
    DMANow(3, spritesheet2Tiles, &CHARBLOCK[4], spritesheet2TilesLen / 2);
    DMANow(3, spritesheet2Pal, SPRITE_PAL, spritesheet2PalLen / 2);

    // dma letters (will use the same bg pal)
    DMANow(3, lettersTiles, &CHARBLOCK[1], lettersTilesLen / 2);
    //DMANow(3, lettersMap, &SCREENBLOCK[2], lettersMapLen / 2);
    
    // Clear what was on bg0cnt letters bg before
    DMANow(3, 0, &SCREENBLOCK[2], lettersMapLen / 2);

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

void goToLevel3() {
    mgba_printf("going to lvl3");

    // DMA bg
    DMANow(3, forestBGTiles, &CHARBLOCK[3], forestBGTilesLen /2);
    DMANow(3, forestBGPal, BG_PALETTE, forestBGPalLen / 2);
    DMANow(3, forestBGMap, &SCREENBLOCK[0], forestBGMapLen / 2);

    hideSprites();
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
    DMANow(3, LoseScreenTiles, &CHARBLOCK[3], LoseScreenTilesLen/2);
    DMANow(3, LoseScreenPal, BG_PALETTE, LoseScreenPalLen / 2);
    DMANow(3, LoseScreenMap, &SCREENBLOCK[0], LoseScreenMapLen / 2);
    state = LOSE;

}
