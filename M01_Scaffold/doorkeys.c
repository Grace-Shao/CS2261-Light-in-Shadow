#include "gba.h"
#include "mode0.h"
#include "sprites.h"
#include "print.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "flashlight.h"
#include "doorkeys.h"
#include <stdlib.h>
#include <time.h>

SPRITE keys[KEYCOUNT];

// keys are oam 20
// doors oam 21
void initBasicKeys() {
    for (int i = 0; i < KEYCOUNT; i++) {
        keys[i].oamIndex = 20;
        keys[i].height = 16;
        keys[i].width = 8;
    }
}
void initKeysLevel1(){
    // Manually set unique x and y positions for each key
    for (int i = 0; i < 2; i++) {
        keys[i].isActive = 1;
    }
    keys[0].x = 30;
    keys[0].y = 50;
    keys[1].x = 60;
    keys[1].y = 100;
}

void drawKeys() {
    for (int i = 0; i < KEYCOUNT; i++) {
        if (keys[i].isActive) {
            shadowOAM[keys[i].oamIndex].attr0 = ATTR0_TALL | ATTR0_Y(keys[i].y);
            shadowOAM[keys[i].oamIndex].attr1 = ATTR1_X(keys[i].x) | ATTR1_TINY;
            shadowOAM[keys[i].oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY(1) | ATTR2_TILEID(6, 25);
        }
    }
}

void drawDoors() {

}