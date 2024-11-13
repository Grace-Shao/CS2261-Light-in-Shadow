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
#include "spritesheet2.h"
#include "background.h"
#include "lightRight.h"
#include "lightLeft.h"
#include "lightUp.h"
#include "lightDown.h"

int frameCount = 0;
int lives = 1;
int hOff = 120;
int vOff = 80;

void initGame() {
    initEnemies();
    initPlayer();
    lives = 1;
    hOff = 120;
    vOff = 80;
    batteryRemaining = 30;

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
    // for parallax
    REG_BG2HOFF = hOff;
    REG_BG2VOFF = vOff;
}