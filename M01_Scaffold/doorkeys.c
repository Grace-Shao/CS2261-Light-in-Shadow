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

KEY keys[KEYCOUNT];
DOOR doors[DOORCOUNT];
SPRITE player;

// keys are oam 20-22
// doors oam 25 - 29
void initBasicKeys() {
    for (int i = 0; i < KEYCOUNT; i++) {
        keys[i].base.oamIndex = 20 + i;
        keys[i].base.height = 16;
        keys[i].base.width = 8;
        keys[i].isCollected = 0;
    }
}

void initBasicDoors() {
    for (int i = 0; i < DOORCOUNT; i++) {
        doors[i].base.oamIndex = 25 + i;
        doors[i].base.height = 32;
        doors[i].base.width = 16;
    }
}
void initKeysLevel1(){
    // Manually set unique x and y positions for each key
    for (int i = 0; i < 2; i++) {
        keys[i].base.isActive = 1;
    }
    keys[0].base.x = 200;
    keys[0].base.y = 100;
    keys[1].base.x = 60;
    keys[1].base.y = 100;
}

void initDoorsLevel1(){
    for (int i = 0; i < 2; i++) {
        doors[i].base.isActive = 1;
    }
    doors[0].base.x = 230;
    doors[0].base.y = 75;
    doors[0].level = 1;

    doors[1].base.x = 200;
    doors[1].base.y = 120;
    doors[1].level = 2;


    doors[0].leadsTo = &doors[1];
    //doors[1].leadsTo = &doors[0];
}
void keyCollision() {
    for (int i = 0; i < KEYCOUNT; i++) {
        if (keys[i].base.isActive && collision(player.x, player.y, player.width, player.height, keys[i].base.x, keys[i].base.y, keys[i].base.width, keys[i].base.height)) {
            keys[i].base.isActive = 0;
            keys[i].isCollected = 1;
            shadowOAM[keys[i].base.oamIndex].attr0 = ATTR0_HIDE;
            mgba_printf("Collided with key %d\n", i);
        }
    }
}

int enterDoor() {
    // todo: change this to doorcount later
    for (int i = 0; i < 2; i++) {
        if (doors[i].base.isActive && collision(player.x, player.y, player.width, player.height, doors[i].base.x, doors[i].base.y, doors[i].base.width, doors[i].base.height)) {
            player.x = doors[i].leadsTo->base.x;
            player.y = doors[i].leadsTo->base.y;
            shadowOAM[player.oamIndex].attr2 = ATTR2_TILEID(0, 0);
            mgba_printf("Entered door %d\n", i);
            // TODO: change this later
            return 1;
            // } else {
            //     mgba_printf("Can't enter door %d\n", i);
            // }
            // Add any additional logic for entering the door here
        }
    }
    return 0;
}

void drawKeys() {
    for (int i = 0; i < KEYCOUNT; i++) {
        if (keys[i].base.isActive) {
            shadowOAM[keys[i].base.oamIndex].attr0 = ATTR0_TALL | ATTR0_Y(keys[i].base.y - vOff);
            shadowOAM[keys[i].base.oamIndex].attr1 = ATTR1_X(keys[i].base.x - hOff) | ATTR1_TINY;
            shadowOAM[keys[i].base.oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY(2) | ATTR2_TILEID(6, 25);
        }
    }
}

void drawDoors() {
    for (int i = 0; i < DOORCOUNT; i++) {
        if (doors[i].base.isActive) {
            shadowOAM[doors[i].base.oamIndex].attr0 = ATTR0_TALL | ATTR0_Y(doors[i].base.y - vOff);
            shadowOAM[doors[i].base.oamIndex].attr1 = ATTR1_X(doors[i].base.x - hOff) | ATTR1_MEDIUM;
            shadowOAM[doors[i].base.oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY(2) | ATTR2_TILEID(16, 4);
        }
    }
}