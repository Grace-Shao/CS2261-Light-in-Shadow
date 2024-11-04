#include "gba.h"
#include "mode0.h"
#include "sprites.h"
#include "print.h"
#include "game.h"
#include "background.h"
#include "gengar.h"
#include "enemy.h"
#include <stdlib.h>
#include <time.h>



SPRITE enemies[ENEMYCOUNT]; // Definition of the global enemies array
SPRITE player;

void initEnemies() {
    // enemy oam starts at 15
    for (int i = 0; i < ENEMYCOUNT; i++) {
        enemies[i].x = rand() % SCREENWIDTH; // Random position within screen width
        enemies[i].y = rand() % SCREENHEIGHT; // Random position within screen height
        mgba_printf("Enemy %d: x = %d, y = %d\n", i, enemies[i].x, enemies[i].y);
        enemies[i].numFrames = 4;
        enemies[i].timeUntilNextFrame = 13;
        enemies[i].direction = 0;
        enemies[i].isAnimating = 0;
        enemies[i].oamIndex = 15 + i;
        enemies[i].width = 12;
        enemies[i].height = 12;
        enemies[i].isActive = 1;
        // only active if they are on screen
    }
}

void enemyMovement() {
    for (int i = 0; i < ENEMYCOUNT; i++) {
        switch (rand() % 4) {
            case 0: // Move Bottom Right
                enemies[i].x += 1;
                enemies[i].y = 230;
                enemies[i].x = 0;
                break;
            case 1: // Move Top Right
                enemies[i].x += 1;
                enemies[i].y -= 1;
                break;
            case 2: // Move Left Up
                enemies[i].x -= 1;
                enemies[i].y -= 1;
                break;
            case 3: // Move Right Up
                enemies[i].x += 1;
                enemies[i].y -= 1;
                break;
        }
    }
}

// enemy movement
// enemies sometimes scurries left to right, up and down
// at random intervals, it will atack
// have it move to the player

void drawEnemies() {
    for (int i = 0; i < ENEMYCOUNT; i++) {
        if (enemies[i].isActive) {
            shadowOAM[enemies[i].oamIndex].attr0 = ATTR0_TALL | ATTR0_Y(enemies[i].y);
            shadowOAM[enemies[i].oamIndex].attr1 = ATTR1_X(enemies[i].x) | ATTR1_MEDIUM;
            shadowOAM[enemies[i].oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY(0) | 
            ATTR2_TILEID(0 + enemies[i].currentFrame * 3, 16 + (enemies[i].direction * 3));
        }
    }  
}