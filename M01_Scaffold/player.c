#include "gba.h"
#include "mode0.h"
#include "sprites.h"
#include "print.h"
#include "player.h"

// sprite imports
#include "background.h"


SPRITE player;
typedef enum {DOWN, RIGHT, UP, LEFT} DIRECTION;

// //x0 has to be smaller, x1 bigger
// void shineLight(int x0, int y0, int x1, int y1) {
//     mgba_printf("set to all black except the specified box");
//     // Set all palette entries to black
//     for (int i = 0; i < 256; i++) {
//         BG_PALETTE[i] = RGB(0, 0, 0);
//     }

//     // Set the specified box to white (or any other color you want)
//     for (int x = 0; x <= SCREENWIDTH; x++) {
//         for (int y = 0; y < SCREENHEIGHT; y++) {
//             if(x < x0 && x > x1) {
//                 BG_PALETTE[i] = RGB(0, 0, 0);
//             }
//     }
// }
void initPlayer() {
    player.x = 30;
    player.y = 20;
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

    if (BUTTON_HELD(BUTTON_UP) && player.y > 0) {
        mgba_printf("up selected");
        player.isAnimating = 1;
        player.direction = UP;
        player.y -= player.yVel;
       
    }
    if ((player.y + player.height) < 256) {
        player.isAnimating = 1;
        player.direction = DOWN;
        player.y += player.yVel;
        
    }
    if (BUTTON_HELD(BUTTON_LEFT) && player.x > 0) {
        mgba_printf("left selected");
        player.isAnimating = 1;
        player.direction = LEFT;
        player.x -= player.xVel;
    }
    if (BUTTON_HELD(BUTTON_RIGHT) && (player.x + player.width) < 256) {
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
    shadowOAM[player.oamIndex].attr2 = ATTR2_PALROW(0) | ATTR2_PRIORITY(0) | ATTR2_TILEID(player.currentFrame * 2, player.direction * 4);
}