#include "helpers/gba.h"
#include "helpers/mode0.h"
#include "helpers/sprites.h"
#include "state.h"
#include "print.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "flashlight.h"
#include "doorKeys.h"
#include <stdlib.h> 
#include <time.h>

int frameCount = 0;
int lives = 1;
int hOff = 120;
int vOff = 80;

void initGame() {
    initEnemies();
    initPlayer();
    initFlashlightBattery();
    initBasicKeys();
    initBasicDoors();
    lives = 1;
    hOff = 120;
    vOff = 80;
    batteryRemaining = 30;

}

void updateGame() {
    if (BUTTON_PRESSED(BUTTON_START)) {
        mgba_printf("start button pressed, go to pause");
        goToPause();
    }
    displayKeysInUI();
    updateEnemies();
    updatePlayer();
    toggleFlashlight();
    keyCollision();
    enterDoor();
    if (frameCount % 500 == 0) {
        selectEnemy();
    }
}

void drawGame() {
    drawLevelUI();
    drawPlayer();
    drawEnemies();
    drawFlashlight();
    drawFlashlightBattery();
    drawKeys();
    drawDoors();
}

// shadowOAM at 30
void drawLevelUI() {
    shadowOAM[30].attr0 = ATTR0_WIDE | ATTR0_Y(10);
    shadowOAM[30].attr1 = ATTR1_X(SCREENWIDTH / 2 - 5) | ATTR1_SMALL;
    if (state == GAME) {
        // Display Floor 1
        shadowOAM[30].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY(0) | ATTR2_TILEID(0, 28);
    } else if (state == LEVEL2) {
        // Display Floor 2
        shadowOAM[30].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY(0) | ATTR2_TILEID(0, 29);
    } else if (state == LEVEL3) {
        // Display outside
        shadowOAM[30].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY(0) | ATTR2_TILEID(0, 30);
    } else if (state == PAUSE) {
        shadowOAM[30].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY(0) | ATTR2_TILEID(0, 31);
    }
}