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
#include "artAssetsGBA/apartmentBGWide.h"
#include "artAssetsGBA/apartmentBGMapLvl2.h"
#include "artAssetsGBA/interiorsPalette.h"
#include "artAssetsGBA/interiorsPalette2.h"
#include "artAssetsGBA/letters.h"
#include "artAssetsGBA/clouds.h"
#include "artAssetsGBA/redMoon.h"
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
        case LEVEL3:
            level3();
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
    playTheme();
    initGame();

    // dma the moon into bg3
    DMANow(3, redMoonTiles, &CHARBLOCK[3], redMoonTilesLen /2);
    //DMANow(3, redMoonPal, BG_PALETTE, interiorsPalettePalLen / 2);
    DMANow(3, redMoonMap, &SCREENBLOCK[0], redMoonMapLen / 2);

    DMANow(3, cloudsTiles, &CHARBLOCK[2], cloudsTilesLen/2);
    DMANow(3, cloudsPal, BG_PALETTE, cloudsPalLen / 2);
    DMANow(3, cloudsMap, &SCREENBLOCK[2], cloudsMapLen / 2);

    state = START;
}

void goToInstructions() {
    // clear out prev bgs
    volatile short zero = 0;
    DMANow(3, &zero, &SCREENBLOCK[2], DMA_SOURCE_FIXED | 1024);
    DMANow(3, &zero, &SCREENBLOCK[0], DMA_SOURCE_FIXED | 1024);


    DMANow(3, instructionsTiles, &CHARBLOCK[3], instructionsTilesLen/2);
    DMANow(3, instructionsPal, BG_PALETTE, instructionsPalLen / 2);
    DMANow(3, instructionsMap, &SCREENBLOCK[0], instructionsMapLen / 2);
    state = INSTRUCTIONS;
}

void goToGame() {
    mgba_printf("going to game");
    srand(frameCount);

    //reset bg2 hoff (if not, will mess w flashlight)
    REG_BG2HOFF = 0;


    deactivateAllDoors();
    initKeysLevel1();
    initDoorsLevel1();
    
    // DMA bg
    DMANow(3, interiorsPaletteTiles, &CHARBLOCK[3], interiorsPaletteTilesLen /2);
    DMANow(3, interiorsPalettePal, BG_PALETTE, interiorsPalettePalLen / 2);
    DMANow(3, apartmentBGWideMap, &SCREENBLOCK[0], apartmentBGWideLen / 2);

    // DMA flashlight (starts r)
    // DMANow(3, lightRightTiles, &CHARBLOCK[2], lightRightTilesLen/2);
    // DMANow(3, lightRightMap, &SCREENBLOCK[1], lightRightMapLen / 2);

    // DMA sprite info 
    DMANow(3, spritesheet2Tiles, &CHARBLOCK[4], spritesheet2TilesLen / 2);
    DMANow(3, spritesheet2Pal, SPRITE_PAL, spritesheet2PalLen / 2);

    // dma letters (will use the same bg pal)
    //DMANow(3, lettersTiles, &CHARBLOCK[1], lettersTilesLen / 2);
    //DMANow(3, lettersMap, &SCREENBLOCK[2], lettersMapLen / 2);

    hideSprites();
    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*8);
    state = GAME;
}

void goToLevel2() {
    mgba_printf("going to lvl2");
    // This map is broken
    // DMANow(3, interiorsPalette2Tiles,  &CHARBLOCK[3], interiorsPaletteTilesLen /2);
    // DMANow(3, interiorsPalette2Pal,  BG_PALETTE, interiorsPalette2PalLen /2);
    DMANow(3, apartmentBGMapLvl2Map,  &SCREENBLOCK[0], apartmentBGMapLvl2Len /2);

    hideSprites();
    deactivateAllDoors();
    initDoorsLevel2();
    initKeysLevel2();
    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*8);
    
    state = LEVEL2;    
}

void goToLevel3() {
    mgba_printf("going to lvl3");

    // DMA bg
    DMANow(3, forestBGTiles, &CHARBLOCK[3], forestBGTilesLen /2);
    DMANow(3, forestBGPal, BG_PALETTE, forestBGPalLen / 2);
    DMANow(3, forestBGMap, &SCREENBLOCK[0], forestBGMapLen / 2);

    REG_BG3HOFF = 0;
    REG_BG3VOFF = 0;

    deactivateAllDoors();
    hideSprites();
    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*8);
    state = LEVEL3;    
}

void goToPause() {
    prevState = state;
    state = PAUSE;
}

void goToLose() {
    // reset bg3 hoff so lose screen is centered
    REG_BG3HOFF = 0;

    clearCollectedKeys();

    // clear the flashlight
    volatile short zero = 0;
    DMANow(3, &zero, &SCREENBLOCK[2], DMA_SOURCE_FIXED | 1024);
    
    hideSprites();
    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128*4);
    // replaces the flashlight bg so it covers up the other sprites
    DMANow(3, LoseScreenTiles, &CHARBLOCK[3], LoseScreenTilesLen/2);
    DMANow(3, LoseScreenPal, BG_PALETTE, LoseScreenPalLen / 2);
    DMANow(3, LoseScreenMap, &SCREENBLOCK[0], LoseScreenMapLen / 2);
    state = LOSE;

}
