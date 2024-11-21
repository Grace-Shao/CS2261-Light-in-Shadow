// has general controls about the game (state machine is in main)
#ifndef GAME_H
#define GAME_H

typedef enum STATE {START, INSTRUCTIONS, GAME, LEVEL2, PAUSE, LOSE, WIN} STATE;
extern STATE state;

#define MAPWIDTH 300
#define MAPHEIGHT 170

extern int frameCount;
extern int score;
extern int lives;
extern int hOff;
extern int vOff;

void initGame();
void updateGame();
void drawGame();
void displayScoreAndLives();

#endif