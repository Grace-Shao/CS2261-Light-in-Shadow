#include "helpers/gba.h"
#include "helpers/mode0.h"
#include "helpers/sprites.h"
#include "print.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "playSound.h"
#include "flashlight.h"
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
        enemies[i].movementType = rand() % 4;
    }
}

// choses a random enemy every 30 seconds (see game.c) and selects their movement type and x and y pos
void selectEnemy() {
    int chosenEnemyIndex = rand() % ENEMYCOUNT;
    mgba_printf("Randomly chosen index: %d\n", chosenEnemyIndex);
    SPRITE *chosenEnemy = &enemies[chosenEnemyIndex];
    chosenEnemy->isAnimating = 1; 
    chosenEnemy->isActive = 1; 

    switch (chosenEnemy->movementType) {
        // top left side, move right
        case 0:
            // Movement case 0
            mgba_printf("Chosen enemy is movement 0\n");
            
            chosenEnemy->x = 10;
            chosenEnemy->y = 10;
            break;
        // left side move down
        case 1:
            // Movement case 1
            mgba_printf("Chosen enemy is movement 1\n");
            chosenEnemy->x = 10;
            chosenEnemy->y = 10;
            break;
        // right side, move left
        case 2:
            // Movement case 2
            mgba_printf("Chosen enemy is movement 2\n");
            chosenEnemy->x = 240;
            chosenEnemy->y = 0;
            break;
        // right side, move up
        case 3:
            // Movement case 3
            mgba_printf("Chosen enemy is movement 3\n");
            chosenEnemy->x = 0;
            chosenEnemy->y = 240;
            break;
    }
    chanceOfEnemyAttack(chosenEnemyIndex);
}

// 50% chance of attacking & play screech
void chanceOfEnemyAttack(int i) {
    if (enemies[i].isActive && (rand() % 4 == 0)) {
        mgba_printf("Enemy %d attacking! movement type: %d\n", i, enemies[i].movementType);
        enemies[i].isAttacking = 1;
        playScreech2();
        if (rand() % 2 == 0) {
            playScreech();
        } else {
            playScreech2();
        }
    }
}

// updates enemies and calls the appropriate methods
// updates enemy movement (if isActive) and enemy attack movement (if isAttacking)
// enemies sometimes scurries left to right, up and down
void updateEnemies() {
    for (int i = 0; i < ENEMYCOUNT; i++) {
        enemyMovement(i);
        
        enemyAttacking(i);

        // animate enemies here
        // player animation
        if (enemies[i].isAnimating) {
            enemies[i].timeUntilNextFrame--;
            if (enemies[i].timeUntilNextFrame == 0) {
                enemies[i].currentFrame = (enemies[i].currentFrame + 1) % enemies[i].numFrames;
                enemies[i].timeUntilNextFrame = 13;
            }
        } else {
            enemies[i].currentFrame = 0;
            enemies[i].timeUntilNextFrame = 13;
        }
        checkEnemyCollision(i);

        // if enemy recently collided w flashlight, have a collision cooldown (enemy will be displayed for 1/2 sec)
        if (enemies[i].collisionCooldown > 0) {
            mgba_printf("collision cooldown", enemies[i].collisionCooldown);
            enemies[i].collisionCooldown -= 1;

            // can finally hide that enemy
            if (enemies[i].collisionCooldown == 0) {
                shadowOAM[enemies[i].oamIndex].attr0 = ATTR0_HIDE;
            }
        }
    }
}

// moves the enemy across the screen and set them inactive if out of bounds
void enemyMovement(int i) {
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
}

// Implement attack logic here
// based on enemy movement type (for ex 0 case), enemy updates its y (get on same height as player)
// then moves towards player vertically to simulate attacking from right
void enemyAttacking(i) {
    if (enemies[i].isActive && enemies[i].isAttacking) {
        switch (enemies[i].movementType) {
            // top left side, move right
            case 0:
                if (enemies[i].y < player.y - vOff) {
                    enemies[i].y += 2;
                } else if (enemies[i].x < player.x - hOff) {
                    enemies[i].x += 2;
                }
                break;
            case 1:
                if (enemies[i].x < player.x - hOff) {
                    enemies[i].x += 2;
                } else if (enemies[i].y < player.y - vOff) {
                    enemies[i].y += 2;
                }
                break;
            case 2:
                if (enemies[i].y < player.y - vOff) {
                    enemies[i].y += 2;
                } else if (enemies[i].x > player.x - hOff) {
                    enemies[i].x -= 2;
                } else if (enemies[i].x < player.x - hOff) {
                    enemies[i].x += 2;
                }
                break;
            case 3:
                if (enemies[i].y > player.y - vOff) {
                    enemies[i].y -= 2;
                } else if (enemies[i].x < player.x - hOff) {
                    enemies[i].x += 2;
                }
                break;
        }
    }
}



// todo: enemy doesn't freeze
void freezeEnemies(SPRITE *enemy) {
    int enemyX = enemy->x;
    int enemyY = enemy->y;
    int enemyWidth = enemy->width;
    int enemyHeight = enemy->height;
    // right
    if (flashlightDirection == 1 && isFlashlightOn) {
        if (collision(128, 71, 17, 16, enemyX, enemyY, enemyWidth, enemyHeight) ||
            collision(145, 63, 22, 34, enemyX, enemyY, enemyWidth, enemyHeight) ||
            collision(168, 48, 21, 63, enemyX, enemyY, enemyWidth, enemyHeight) ||
            collision(199, 39, 25, 88, enemyX, enemyY, enemyWidth, enemyHeight) ||
            collision(225, 26, 14, 109, enemyX, enemyY, enemyWidth, enemyHeight)) {
            mgba_printf("collided w flashlight");
            shadowOAM[enemy->oamIndex].attr0 = ATTR0_HIDE;
            enemy->collisionCooldown = 30;
            enemy->isActive = 0;
            mgba_printf("Enemy isActive: %d\n", enemy->isActive);
        } 
    } 
    // up
    if (flashlightDirection == 2 && isFlashlightOn) {
        if (collision(112, 56, 15, 15, enemyX, enemyY, enemyWidth, enemyHeight) ||
            collision(104, 32, 32, 32, enemyX, enemyY, enemyWidth, enemyHeight) ||
            collision(88, 9, 64, 22, enemyX, enemyY, enemyWidth, enemyHeight)) {
            mgba_printf("collided w flashlight");
            shadowOAM[enemy->oamIndex].attr0 = ATTR0_HIDE;
            enemy->collisionCooldown = 30;
            enemy->isActive = 0;
            mgba_printf("Enemy isActive: %d\n", enemy->isActive);
        }
    } 
    // left
    if (flashlightDirection == -1 && isFlashlightOn) {
        if (collision(0, 40, 28, 80, enemyX, enemyY, enemyWidth, enemyHeight) ||
            collision(40, 48, 32, 56, enemyX, enemyY, enemyWidth, enemyHeight) ||
            collision(80, 65, 32, 30, enemyX, enemyY, enemyWidth, enemyHeight)) {
            mgba_printf("collided w flashlight");
            shadowOAM[enemy->oamIndex].attr0 = ATTR0_HIDE;
            enemy->collisionCooldown = 30;
            enemy->isActive = 0;
            mgba_printf("Enemy isActive: %d\n", enemy->isActive);
        }
    } 
    // add bottom later
}

// could prob combine it w enemy movement to make it more efficient
void checkEnemyCollision(int i) {
    if (enemies[i].isActive) {
        // check enemy collision with flashlight
        freezeEnemies(&enemies[i]);
        // Check for collision with player's screen coordinates
        if (collision(player.x - hOff, player.y - vOff, 10, 10, enemies[i].x, enemies[i].y, 10, 10)) {
            player.currentFrame = 0;
            enemies[i].isActive = 0;
            // hide sprites isn't working
            shadowOAM[player.oamIndex].attr0 = ATTR0_HIDE;
            mgba_printf("Player index: %d\n", player.oamIndex);
            mgba_printf("Enemy index: %d\n", enemies[i].oamIndex);

            shadowOAM[enemies[i].oamIndex].attr0 = ATTR0_HIDE;
            lives -= 1;
            mgba_printf("Lives remaining: %d\n", lives);
            mgba_printf("Collision with enemy %d at x = %d, y = %d\n", i, enemies[i].x, enemies[i].y);
            mgba_printf("Player coordinates: x = %d, y = %d\n", player.x, player.y);
            mgba_printf("Player screen coordinates: x = %d, y = %d\n", player.x - hOff, player.y - vOff);
        }           
    }
}

// if on palRow 1, can only see red eyes, if flashlight shone on them, show whole body
void drawEnemies() {
    for (int i = 0; i < ENEMYCOUNT; i++) {
        if (enemies[i].isActive || enemies[i].collisionCooldown > 0) {
            drawEnemyEyes(&enemies[i]);
            shadowOAM[enemies[i].oamIndex].attr0 = ATTR0_SQUARE | ATTR0_Y(enemies[i].y);
            shadowOAM[enemies[i].oamIndex].attr1 = ATTR1_X(enemies[i].x) | ATTR1_MEDIUM;
            // another way is the hide the sprite in random intervals (first tile is w eyes, 2nd is no eyes)
            //int tileID = (rand() % 4 == 0) ? ATTR2_TILEID(0, 16) : ATTR2_TILEID(3, 16);
            shadowOAM[enemies[i].oamIndex].attr2 = ATTR2_PALROW(1) | ATTR2_PRIORITY(0) | ATTR2_TILEID(enemies[i].currentFrame * 4, 16 + enemies[i].direction * 4);
        }
    }  
}

// todo: ask TA's how to implement enemy eyes, at oam index 20
// enemy eyes will reveal the sprite behind
void drawEnemyEyes(SPRITE *enemy) {
    // shadowOAM[20].attr0 = ATTR0_SQUARE | ATTR0_Y(enemy->y);
    // shadowOAM[20].attr1 = ATTR1_X(enemy->x) | ATTR1_SMALL;
    // shadowOAM[20].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY(0) | 
    // ATTR2_TILEID(0, 23);
 
}