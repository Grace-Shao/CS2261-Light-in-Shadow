#ifndef ENEMY_H
#define ENEMY_H
#include "gba.h"
#include "game.h"
#include "sprites.h"

#define ENEMYCOUNT 2

void initEnemies();
void updateEnemies();
void drawEnemies();
void checkEnemyCollision();

extern SPRITE enemies[ENEMYCOUNT]; // Declaration of the global enemies array
SPRITE *enemyToErase;

#endif