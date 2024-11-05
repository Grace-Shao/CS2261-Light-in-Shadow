#include "gba.h"
#include "mode0.h"
#include "sprites.h"
#include "print.h"
#include "player.h"
#include "enemy.h"
#include <stdlib.h>
#include <time.h>

// sprite imports
#include "gengar.h"
#include "background.h"
#include "light.h"

int frameCount = 0;
int isFlashlightOn = 0;

void initGame() {
    initEnemies();
    initPlayer();

}

void updateGame() {
    updateEnemies();
    updatePlayer();
    toggleFlashlight();
    if (frameCount % 500 == 0) {
        mgba_printf("enemy movement triggered");
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
            mgba_printf("Flashlight turned on");
        } else {
            mgba_printf("Flashlight turned off");
        }
    }
}

void drawFlashlight() {
    if (isFlashlightOn) {
        // dma light 
        DMANow(3, lightTiles, &CHARBLOCK[3], lightTilesLen/2);
        //DMANow(3, lightPal, BG_PALETTE, lightPalLen / 2);
        DMANow(3, lightMap, &SCREENBLOCK[1], lightMapLen / 2);
    } else {
        // Clear the light map
        DMANow(3, 0, &SCREENBLOCK[1], backgroundMapLen / 2);
    }
}