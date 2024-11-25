#ifndef STATE_H
#define STATE_H

typedef enum STATE {START, INSTRUCTIONS, GAME, LEVEL2, LEVEL3, PAUSE, LOSE, WIN} STATE;
extern STATE state;

// Function prototypes
void updateGameState(STATE state);
void goToStart();
void goToInstructions();
void goToGame();
void goToLevel2();
void goToLevel3();
void goToPause();
void goToLose();
void start();
void instructions();
void game();
void level2();
void pause();
void lose();

#endif // STATE_H