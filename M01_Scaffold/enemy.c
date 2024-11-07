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
        enemies[i].x = 10; 
        enemies[i].y = 10; 
        enemies[i].numFrames = 4;
        enemies[i].timeUntilNextFrame = 13;
        enemies[i].direction = 0;
        enemies[i].isAnimating = 0;
        enemies[i].oamIndex = 15 + i;
        enemies[i].width = 12;
        enemies[i].height = 12;
        enemies[i].isActive = 0;
        enemies[i].isAttacking = 0;
        enemies[i].movementType = rand() % ENEMYCOUNT;
    }
}

void enemyMovement() {
    int chosenEnemyIndex = rand() % ENEMYCOUNT;
    mgba_printf("Randomly chosen index: %d\n", chosenEnemyIndex);
    SPRITE *chosenEnemy = &enemies[chosenEnemyIndex];

    switch (chosenEnemy->movementType) {
        // left side, move right
        case 0:
            // Movement case 0
            mgba_printf("Chosen enemy is movement 0\n");
            chosenEnemy->isActive = 1; 
            chosenEnemy->x = 10;
            chosenEnemy->y = 10;
            chosenEnemy->movementType = 0;
            break;
        // left side move down
        case 1:
            // Movement case 1
            mgba_printf("Chosen enemy is movement 1\n");
            chosenEnemy->isActive = 1;
            chosenEnemy->x = 10;
            chosenEnemy->y = 10;
            chosenEnemy->movementType = 1;
            enemyAttack(chosenEnemyIndex);
            break;
        // right side, move left
        case 2:
            // Movement case 2
            mgba_printf("Chosen enemy is movement 2\n");
            chosenEnemy->isActive = 1;
            chosenEnemy->x = 240;
            chosenEnemy->y = 0;
            chosenEnemy->movementType = 2;
            enemyAttack(chosenEnemyIndex);
            break;
        // right side, move up
        case 3:
            // Movement case 3
            mgba_printf("Chosen enemy is movement 3\n");
            chosenEnemy->isActive = 1;
            chosenEnemy->x = 0;
            chosenEnemy->y = 240;
            chosenEnemy->movementType = 3;
            enemyAttack(chosenEnemyIndex);
            break;
    }
}

void enemyAttack(int i) {
    if (enemies[i].isActive && (rand() % 4 == 0)) {
        mgba_printf("Enemy %d is attacking!\n", i);
        enemies[i].isAttacking = 1;
    }
}

// enemy movement
// enemies sometimes scurries left to right, up and down
// at random intervals, it will atack
// have it move to the player
void updateEnemies() {
    for (int i = 0; i < ENEMYCOUNT; i++) {
        if (enemies[i].isActive && enemies[i].isAttacking == 0) {
            switch (enemies[i].movementType) {
                case 0:
                    enemies[i].x += 1;
                    if (enemies[i].x > SCREENWIDTH) {
                        enemies[i].isActive = 0;
                    }
                    break;
                case 1:
                    enemies[i].y += 1;
                    if (enemies[i].y > SCREENHEIGHT) {
                        enemies[i].isActive = 0;
                    }
                    break;
                case 2:
                    enemies[i].x -= 1;
                    if (enemies[i].x < -10) {
                        enemies[i].isActive = 0;
                    }
                    break;
                case 3:
                    enemies[i].y -= 1;
                    if (enemies[i].y < -10) {
                        enemies[i].isActive = 0;
                    }
                    break;
                default:
                    mgba_printf("Unknown movement type for enemy %d\n", i);
                    break;
            
            }
        }
        // Implement attack logic here
        // For example, move towards the player
        if (enemies[i].isActive && enemies[i].isAttacking) {
            if (enemies[i].x < player.x) {
                enemies[i].x += 1;
            } else if (enemies[i].x > player.x) {
                enemies[i].x -= 1;
            }
            if (enemies[i].y < player.y) {
                enemies[i].y += 1;
            } else if (enemies[i].y > player.y) {
                enemies[i].y -= 1;
            }
        }
    }
}

void drawEnemies() {
    for (int i = 0; i < ENEMYCOUNT; i++) {
        if (enemies[i].isActive) {
            shadowOAM[enemies[i].oamIndex].attr0 = ATTR0_TALL | ATTR0_Y(enemies[i].y);
            shadowOAM[enemies[i].oamIndex].attr1 = ATTR1_X(enemies[i].x) | ATTR1_MEDIUM;
            shadowOAM[enemies[i].oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY(2) | 
            ATTR2_TILEID(0, 16);
        }
    }  
}