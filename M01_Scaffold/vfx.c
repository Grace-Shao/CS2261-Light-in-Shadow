#include "helpers/gba.h"
#include "helpers/mode0.h"
#include "helpers/sprites.h"
#include "helpers/digitalSound.h"
#include "playSound.h"
#include "print.h"
#include "game.h"
#include "state.h"
#include "player.h"
#include "enemy.h"
#include "flashlight.h"
#include "doorKeys.h"
#include <stdlib.h>
#include <time.h>

void spawnCracks() {
    static int counter = 0;
    counter++;
    if (counter >= 300) { // Assuming 60 FPS, 300 frames = 5 seconds
        counter = 0;
        // Your code to spawn cracks here
        int randomX = rand() % 32;
        int randomY = rand() % 10; // Upper half of the screen (0-15)
        SCREENBLOCK[0].tilemap[OFFSET(randomX, randomY, 32)] = TILEMAP_ENTRY_TILEID(12);
        SCREENBLOCK[0].tilemap[OFFSET(randomX, randomY + 1, 32)] = TILEMAP_ENTRY_TILEID(13);
        SCREENBLOCK[0].tilemap[OFFSET(randomX + 1, randomY, 32)] = TILEMAP_ENTRY_TILEID(43);
        SCREENBLOCK[0].tilemap[OFFSET(randomX + 1, randomY + 1, 32)] = TILEMAP_ENTRY_TILEID(44);
        mgba_printf("Spawn cracks called at x: %d, y: %d\n", randomX, randomY);

    }
}

void flashRed() {
    if (rand() % 100 < 10) { // 10% chance to flash red
        u16 originalColor = BG_PALETTE[3];
        BG_PALETTE[1] = RGB(31, 0, 0); // Dark red
    }
    if (rand() % 100 < 30) { // 30% chance to change back to original color
        BG_PALETTE[1] = RGB(1, 1, 1);
    }

}
