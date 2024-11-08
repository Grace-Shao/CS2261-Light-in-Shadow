#include "gba.h"
#include "mode0.h"
#include "sprites.h"
#include "print.h"
#include "player.h"
#include "enemy.h"
#include <stdlib.h>
#include <time.h>

// sprite imports
#include "spritesheet1.h"
#include "background.h"
#include "lightRight.h"
#include "lightLeft.h"
#include "lightUp.h"
#include "lightDown.h"

int frameCount = 0;
int isFlashlightOn = 0;
int flashlightDirection = 0;
int lives = 1;

void initGame() {
    initEnemies();
    initPlayer();
    lives = 1;
}

void updateGame() {
    updateEnemies();
    updatePlayer();
    toggleFlashlight();
    if (frameCount % 500 == 0) {
        enemyMovement();
    }
}

void drawGame() {
    drawPlayer();
    drawEnemies();
    drawFlashlight();
}

void toggleFlashlight() {
    if (BUTTON_PRESSED(BUTTON_RIGHT)) {
        // Code to toggle the flashlight
        isFlashlightOn = !isFlashlightOn;
        if (isFlashlightOn) {
            flashlightDirection = 1;
            mgba_printf("Flashlight turned on");
        } else {
            mgba_printf("Flashlight turned off");
        }
    }
    if (BUTTON_PRESSED(BUTTON_LEFT)) {
        // Code to toggle the flashlight
        isFlashlightOn = !isFlashlightOn;
        if (isFlashlightOn) {
            flashlightDirection = -1;
            mgba_printf("Flashlight turned on");
        } else {
            mgba_printf("Flashlight turned off");
        }
    }
    if (BUTTON_PRESSED(BUTTON_UP)) {
        // Code to toggle the flashlight
        isFlashlightOn = !isFlashlightOn;
        if (isFlashlightOn) {
            flashlightDirection = 2;
            mgba_printf("Flashlight turned on");
        } else {
            mgba_printf("Flashlight turned off");
        }
    }
    if (BUTTON_PRESSED(BUTTON_DOWN)) {
        // Code to toggle the flashlight
        isFlashlightOn = !isFlashlightOn;
        if (isFlashlightOn) {
            flashlightDirection = -2;
            mgba_printf("Flashlight turned on");
        } else {
            mgba_printf("Flashlight turned off");
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