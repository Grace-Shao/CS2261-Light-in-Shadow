#include "gba.h"
#include "mode0.h"
#include "sprites.h"
#include "print.h"

void start();
void goToStart();
void instructions();
void goToInstructions();
void game();
void goToGame();
void goToPause();
void pause();
void goToWin();
void win();
void initialize();
void goToLose();
void lose();

// States
enum STATE {START, INSTRUCTIONS, GAME, PAUSE, LOSE, WIN} state;
OBJ_ATTR shadowOAM[128];
typedef enum {DOWN, RIGHT, UP, LEFT} DIRECTION;

// Button Variables
unsigned short buttons;
unsigned short oldButtons;

void initialize() {
    // Set up basic registers 
    REG_DISPCTL = MODE(0) | BG_ENABLE(2) | SPRITE_ENABLE;
    REG_BG2CNT = BG_SCREENBLOCK(0) | BG_CHARBLOCK(2);
    
    buttons = REG_BUTTONS;
    oldButtons = 0;

    mgba_open();
    mgba_printf("initialized");
    //initSound();
    goToStart();
}

int main() {
    initialize();
    while(1) {
        oldButtons = buttons;
        buttons = REG_BUTTONS;
             
        // State Machine
        switch(state) {
            case START:
                start();
                break;
            // case INSTRUCTIONS:
            //     instructions();
            //     break;
            case GAME:
                game();
                break;
            // case LOSE:
            //     lose();
            //     break;
            default:
                break;
        }      
    }
}

void goToStart() {
    //initGame();
}

void start() {
    state = START;
    if (BUTTON_HELD(BUTTON_START)) {
        mgba_printf("start button pressed");
        goToGame();
    }
}

void goToGame() {
    mgba_printf("going to game");
    state = GAME;
}

void game() {

}