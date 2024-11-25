#ifndef ENEMY_H
#define ENEMY_H
#include "helpers/gba.h"
#include "game.h"
#include "helpers/sprites.h"

#define ENEMYCOUNT 3

void initEnemies();
void enemyMovement();
void updateEnemies();
void drawEnemies();
void freezeEnemies();
void checkEnemyCollision();

extern SPRITE enemies[ENEMYCOUNT]; 
SPRITE *enemyToErase;

#endif