#include "helpers/gba.h"
#include "helpers/mode0.h"
#include "sprites.h"
#include "print.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include <stdlib.h>
#include <time.h>

// sprite imports
#include "background.h"


SPRITE player;
typedef enum {DOWN, RIGHT, LEFT} DIRECTION;

void initPlayer() {
    player.x = 120;
    player.y = 80;
    player.width = 16;
    player.height = 24;
    player.xVel = 1;
    player.yVel = 1;
    player.direction = DOWN;
    player.numFrames = 4;
    player.timeUntilNextFrame = 13;
    player.oamIndex = 0;
}
void updatePlayer() {
    player.isAnimating = 0;

    int leftX = player.x;
    int rightX = player.x + player.width - 1;
    int topY = player.y;
    int bottomY = player.y + player.height - 1;

    if (BUTTON_HELD(BUTTON_B) && player.x > 0) {
        player.isAnimating = 1;
        player.direction = LEFT;
        player.x -= player.xVel;
    }
    if (BUTTON_HELD(BUTTON_A) && (player.x + player.width) < MAPWIDTH) {
        player.isAnimating = 1;
        player.direction = RIGHT;
        player.x += player.xVel;
    }
    // player animation
    if (player.isAnimating) {
        player.timeUntilNextFrame--;
        if (player.timeUntilNextFrame == 0) {
            player.currentFrame = (player.currentFrame + 1) % player.numFrames;
            player.timeUntilNextFrame = 13;
        }
    } else {
        player.currentFrame = 0;
        player.timeUntilNextFrame = 13;
    }
    centerPlayer();
}

void centerPlayer() {
    hOff = player.x - (SCREENWIDTH - player.width) / 2;
    vOff = player.y - (SCREENHEIGHT - player.height) / 2;

    // restrict camera movement to map
    if (hOff < 0) hOff = 0;
    if (vOff < 0) vOff = 0;
    if (hOff > (MAPWIDTH - SCREENWIDTH)) hOff = (MAPWIDTH - SCREENWIDTH);
    if (vOff > (MAPHEIGHT - SCREENHEIGHT)) vOff = (MAPHEIGHT - SCREENHEIGHT);


}

void drawPlayer() {
    // player in shadowOAM
    shadowOAM[player.oamIndex].attr0 = ATTR0_TALL | ATTR0_Y(player.y  - vOff);
    shadowOAM[player.oamIndex].attr1 = ATTR1_X(player.x - hOff) | ATTR1_MEDIUM;
    shadowOAM[player.oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY(2) | ATTR2_TILEID(player.currentFrame * 2, player.direction * 4);
}