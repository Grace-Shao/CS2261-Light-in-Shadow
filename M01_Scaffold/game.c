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

int frameCount = 0;

void initGame() {
    initEnemies();
    initPlayer();

}

void updateGame() {
    updateEnemies();
    updatePlayer();
    if (frameCount % 500 == 0) {
        mgba_printf("enemy movement triggered");
        enemyMovement();
    }
}

void drawGame() {
    drawPlayer();
    drawEnemies();
}