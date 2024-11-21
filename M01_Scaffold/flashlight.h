// has general controls about the game (state machine is in main)
#ifndef FLASHLIGHT_H
#define FLASHLIGHT_H

extern int isFlashlightOn;
extern int flashlightDirection;
// number of clicks before runs out of battern
extern int batteryRemaining;

void toggleFlashlight();
void drawFlashlight();
void drawFlashlightBattery();

#endif