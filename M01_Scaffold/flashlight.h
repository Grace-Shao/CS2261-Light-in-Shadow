// has general controls about the game (state machine is in main)
#ifndef FLASHLIGHT_H
#define FLASHLIGHT_H

extern int isFlashlightOn;
extern int flashlightDirection;

void toggleFlashlight();
void drawFlashlight();

#endif