#ifndef STATE_H
#define STATE_H

typedef enum STATE {START, INSTRUCTIONS, CUTSCENE, GAME, LEVEL2, LEVEL3, PAUSE, LOSE, WIN} STATE;
extern STATE state;
extern STATE prevState;


// Function prototypes
void updateGameState(STATE state);
void goToStart();
void goToInstructions();
void goToCutscene();
void goToGame();
void goToLevel2();
void goToLevel3();
void goToPause();
void goToLose();

#endif // STATE_H