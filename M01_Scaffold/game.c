#include "helpers/gba.h"
#include "helpers/mode0.h"
#include "helpers/sprites.h"
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
    updateEnemies();
    updatePlayer();
    toggleFlashlight();
    keyCollision();
    enterDoor();
    if (frameCount % 500 == 0) {
        //enemyMovement();
    }
}

void drawGame() {
    drawPlayer();
    drawEnemies();
    drawFlashlight();
    drawFlashlightBattery();
    drawKeys();
    drawDoors();
    // for parallax
    REG_BG3HOFF = hOff;
    REG_BG3VOFF = vOff;
}