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
KEY collectedKeys[KEYCOUNT];
int collectedKeyCount = 0;
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
    doors[0].base.y = 80;
    doors[1].base.x = 200;
    doors[1].base.y = 80;
    doors[2].base.x = 50;
    doors[2].base.y = 80;
    doors[3].base.x = 220;
    doors[3].base.y = 80;
    doors[4].base.x = 30;
    doors[4].base.y = 80;

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
    // turn keys of other lvls off
    keys[1].base.isActive = 0;
    keys[2].base.isActive = 0;

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
    // turn keys of other levels off
    keys[0].base.isActive = 0;

    keys[1].base.x = 100;
    keys[1].base.y = 75;
    keys[2].base.x = 180;
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

void initDoorsLevel3(){
    doors[4].base.isActive = 1;
}
void keyCollision() {
    // mgba_printf("Collected Keys Count: %d\n", collectedKeyCount);
    // for (int i = 0; i < collectedKeyCount; i++) {
    //     mgba_printf("Collected Key %d at position (%d, %d)\n", i, collectedKeys[i].base.x, collectedKeys[i].base.y);
    // }
    for (int i = 0; i < KEYCOUNT; i++) {
        if (keys[i].base.isActive && collision(player.x, player.y, player.width, player.height, keys[i].base.x, keys[i].base.y, keys[i].base.width, keys[i].base.height)) {
            keys[i].base.isActive = 0;

            // add to collected keys arr
            keys[i].isCollected = 1;
            collectedKeys[collectedKeyCount] = keys[i];
            collectedKeyCount += 1;

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
            shadowOAM[player.oamIndex].attr2 = ATTR2_TILEID(0, 0);
            mgba_printf("New player position: x = %d, y = %d\n", player.x, player.y);
            mgba_printf("Entered door %d with key collected %d\n", i, keys[i].isCollected);
           
            switch (doors[i].leadsTo->level) {
                case 1:
                    goToGame();
                    break;
                case 2:
                    goToLevel2();
                    break;
                case 3:
                    goToLevel3();
                    break;
                default:
                    break;
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
            // setting the keys to their own unique sprites (+ i)
            shadowOAM[keys[i].base.oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY(2) | ATTR2_TILEID(6 + i, 25);
            
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

// TODO: has a problem of not resetting after death
void displayKeysInUI() {
    for (int i = 0; i < collectedKeyCount; i++) {
        shadowOAM[collectedKeys[i].base.oamIndex].attr0 = ATTR0_TALL | ATTR0_Y(5);
        // space out the keys based on their index
        shadowOAM[collectedKeys[i].base.oamIndex].attr1 = ATTR1_X(50 + (i * 10)) | ATTR1_TINY;
        // if key isCollected, make it higher priority to show up in front of flashlight
        // else make it lower priority
        // Modify only the priority attribute of attr2
        int priority = 0; // Example priority value
        shadowOAM[collectedKeys[i].base.oamIndex].attr2 &= ~ATTR2_PRIORITY(3); // Clear the existing priority bits
        shadowOAM[collectedKeys[i].base.oamIndex].attr2 |= ATTR2_PRIORITY(priority); // Set the new priority bits

    }
}