// has general controls about the game (state machine is in main)
#ifndef GAME_H
#define GAME_H

#define MAPWIDTH 512
#define MAPHEIGHT 256

extern int frameCount;
extern int score;
extern int lives;
extern int hOff;
extern int vOff;

void initGame();
void updateGame();
void drawGame();
void drawLevelUI();

#endif