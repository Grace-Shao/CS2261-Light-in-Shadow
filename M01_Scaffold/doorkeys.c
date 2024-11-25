#include "helpers/gba.h"
#include "helpers/mode0.h"
#include "helpers/sprites.h"
#include "print.h"
#include "game.h"
#include "state.h"
#include "player.h"
#include "enemy.h"
#include "flashlight.h"
#include "doorKeys.h"
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

    // set up the position of all 4 doors (some r not active yet)
    doors[0].base.x = 200;
    doors[0].base.y = 75;
    doors[1].base.x = 200;
    doors[1].base.y = 75;
    doors[2].base.x = 50;
    doors[2].base.y = 75;
    doors[3].base.x = 220;
    doors[3].base.y = 75;
    doors[4].base.x = 15;
    doors[4].base.y = 75;

    // each door has a different lvl they belong in (lvl 1 is first game lvl)
    doors[0].level = 1;
    doors[3].level = 1;

    doors[1].level = 2;
    doors[2].level = 2;

    doors[4].level = 3;

    // some door links up to another door
    doors[0].leadsTo = &doors[2];
    doors[1].leadsTo = &doors[3];
    doors[2].leadsTo = &doors[4];

    // assign them keys
    doors[0].assignedKey = &keys[0];
    doors[1].assignedKey = &keys[1];
    doors[2].assignedKey = &keys[2];

}

// this is the reset the doors before initDoorsLevel1 (where doors and keys r draw again)
void deactivateAllDoors() {
    for (int i = 0; i < DOORCOUNT; i++) {
        doors[i].base.isActive = 0;
    }
}

void initKeysLevel1(){
    // Manually set unique x and y positions for each key
    if (!keys[0].isCollected) {
        keys[0].base.isActive = 1;
    }
    keys[0].base.x = 100;
    keys[0].base.y = 75;
}

void initKeysLevel2() {
    // Manually set unique x and y positions for each key
    if (!keys[1].isCollected) {
        keys[1].base.isActive = 1;
    }
    if (!keys[2].isCollected) {
        keys[2].base.isActive = 1;
    }
    keys[1].base.x = 100;
    keys[1].base.y = 75;
    keys[2].base.x = 200;
    keys[2].base.y = 75;
}

void initDoorsLevel1(){
    doors[0].base.isActive = 1;
    doors[3].base.isActive = 1;
}

void initDoorsLevel2(){
    doors[2].base.isActive = 1;
    doors[1].base.isActive = 1;
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

void enterDoor() {
    for (int i = 0; i < DOORCOUNT; i++) {
        // if the door is active and leads to somewhere and u collected the correct key
        if (doors[i].base.isActive && doors[i].leadsTo != NULL && doors[i].assignedKey->isCollected && collision(player.x, player.y, player.width, player.height, doors[i].base.x, doors[i].base.y, doors[i].base.width, doors[i].base.height)) {
            player.x = doors[i].leadsTo->base.x;
            player.y = doors[i].leadsTo->base.y;
            mgba_printf("New player position: x = %d, y = %d\n", player.x, player.y);
            shadowOAM[player.oamIndex].attr2 = ATTR2_TILEID(0, 0);
            mgba_printf("Entered door %d\n", i);
            if (doors[i].leadsTo->level == 1) {
                goToGame();
            } else {
                goToLevel2();
            }
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