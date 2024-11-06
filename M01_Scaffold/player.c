#include "gba.h"
#include "mode0.h"
#include "sprites.h"
#include "print.h"
#include "player.h"

// sprite imports
#include "background.h"


SPRITE player;
typedef enum {DOWN, RIGHT, UP, LEFT} DIRECTION;

void initPlayer() {
    player.x = 88;
    player.y = 55;
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
        mgba_printf("left selected");
        player.isAnimating = 1;
        player.direction = LEFT;
        player.x -= player.xVel;
    }
    if (BUTTON_HELD(BUTTON_A) && (player.x + player.width) < 256) {
        mgba_printf("right selected");

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
}

void drawPlayer() {
    // player in shadowOAM
    shadowOAM[player.oamIndex].attr0 = ATTR0_TALL | ATTR0_Y(player.y);
    shadowOAM[player.oamIndex].attr1 = ATTR1_X(player.x) | ATTR1_MEDIUM;
    shadowOAM[player.oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY(2) | ATTR2_TILEID(player.currentFrame * 2, player.direction * 4);
}