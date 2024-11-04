#ifndef GAME_H
#define GAME_H

extern int frameCount;
extern int score;
extern int lives;

void initGame();
void updateGame();
void drawGame();
void displayScoreAndLives();

#endif