#include "gba.h"
#include "mode0.h"
#include "sprites.h"
#include "print.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "flashlight.h"
#include <stdlib.h>
#include <time.h>

// sprite imports
#include "spritesheet1.h"
#include "background.h"
#include "lightRight.h"
#include "lightLeft.h"
#include "lightUp.h"
#include "lightDown.h"

// variable intial settings are redefined in main
int isFlashlightOn = 0;
int flashlightDirection = 0;
int batteryRemaining;

SPRITE flashlightBattery;

void initFlashlightBattery() {
    flashlightBattery.x = 10;
    flashlightBattery.y = 10;
    flashlightBattery.width = 32;
    flashlightBattery.height = 8;
    flashlightBattery.oamIndex = 2;
}

void toggleFlashlight() {
    if (BUTTON_PRESSED(BUTTON_RIGHT) || BUTTON_PRESSED(BUTTON_LEFT) || BUTTON_PRESSED(BUTTON_UP) || BUTTON_PRESSED(BUTTON_DOWN)) {
        isFlashlightOn = !isFlashlightOn;
        if (isFlashlightOn == 0) {
            batteryRemaining -= 1;
            mgba_printf("Battery remaining: %d", batteryRemaining);
        }
        // Check specific button presses for direction
        if (BUTTON_PRESSED(BUTTON_RIGHT)) {
            flashlightDirection = 1;
            mgba_printf("Flashlight turned right");
        } else if (BUTTON_PRESSED(BUTTON_LEFT)) {
            flashlightDirection = -1;
            mgba_printf("Flashlight turned left");
        } else if (BUTTON_PRESSED(BUTTON_UP)) {
            flashlightDirection = 2;
            mgba_printf("Flashlight turned up");
        } else if (BUTTON_PRESSED(BUTTON_DOWN)) {
            flashlightDirection = -2;
            mgba_printf("Flashlight turned down");
        }
    }
    
}

void drawFlashlight() {
    if (isFlashlightOn) {
        // dma light
        if (flashlightDirection == 1) {
            DMANow(3, lightRightTiles, &CHARBLOCK[3], lightRightTilesLen/2);
            DMANow(3, lightRightMap, &SCREENBLOCK[1], lightRightMapLen / 2);
        } else if (flashlightDirection == -1)
        {
            DMANow(3, lightLeftTiles, &CHARBLOCK[3], lightLeftTilesLen/2);
            DMANow(3, lightLeftMap, &SCREENBLOCK[1], lightLeftMapLen / 2);
        } 
        else if (flashlightDirection == 2) {
            DMANow(3, lightUpTiles, &CHARBLOCK[3], lightUpTilesLen/2);
            DMANow(3, lightUpMap, &SCREENBLOCK[1], lightUpMapLen / 2);
        } else if (flashlightDirection == -2) {
            DMANow(3, lightDownTiles, &CHARBLOCK[3], lightDownTilesLen/2);
            DMANow(3, lightDownMap, &SCREENBLOCK[1], lightDownMapLen / 2);
        }
    } else {
        // Clear the light map
        DMANow(3, 0, &SCREENBLOCK[1], backgroundMapLen / 2);
    }
}

void drawFlashlightBattery() {
    shadowOAM[flashlightBattery.oamIndex].attr0 = ATTR0_WIDE | ATTR0_Y(flashlightBattery.y);
    shadowOAM[flashlightBattery.oamIndex].attr1 = ATTR1_X(flashlightBattery.x) | ATTR1_SMALL;
    int sizeOfTile = 4;
    int tileIDX = 0;
    int tileIDY = 0;
    if (batteryRemaining < 1) {
        tileIDX = 2 * sizeOfTile;
        tileIDY = 1;
    } else if (batteryRemaining < 10) {
        tileIDX = 1 * sizeOfTile;
        tileIDY = 1;
    } else if (batteryRemaining < 15) {
        tileIDX = 0;
        tileIDY = 1;
    } else if (batteryRemaining < 20) {
        tileIDX = 2 * sizeOfTile;
    } else if (batteryRemaining < 25) {
        tileIDX = 1 * sizeOfTile;
    } else {
        tileIDX = 0;
        tileIDY = 0;
    }
    shadowOAM[flashlightBattery.oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY(0) | ATTR2_TILEID(0 + tileIDX, 23 + tileIDY);

}