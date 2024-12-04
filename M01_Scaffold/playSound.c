#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "print.h"

#include "helpers/gba.h"
#include "helpers/mode0.h"
#include "helpers/sprites.h"

#include "playSound.h"
#include "helpers/digitalSound.h"
#include "scaryTheme.h"
#include "buttonClicked.h"
#include "screech.h"
#include "screech2.h"

void playTheme() {
    mgba_printf("theme activate");
    playSoundA(scaryTheme_data, scaryTheme_length, 1);
}

void playButtonClick() {
    playSoundB(buttonClicked_data, buttonClicked_length, 0);
}

void playScreech() {
    playSoundB(screech_data, screech_length, 0);
}

void playScreech2() {
    playSoundB(screech2_data, screech2_length, 0);
}

void setUpInterrupts() {
    REG_IME = 0;

    // TODO 1.0: Enable VBlank interrupts
    REG_IE = IRQ_VBLANK;
    REG_DISPSTAT = DISPSTAT_VBLANK_IRQ;

    REG_INTERRUPT = interruptHandler;
	REG_IME = 1;
}

void interruptHandler() {

	REG_IME = 0;

    // Handle VBlank interrupts
    if (REG_IF & IRQ_VBLANK) {
        if (soundA.isPlaying) {
            soundA.vBlankCount++;
            if (soundA.vBlankCount >= soundA.durationInVBlanks) {
                if (soundA.looping) {
                    // loop sound
                    playSoundA(soundA.data, soundA.dataLength, soundA.looping);
                } else {
                    soundA.isPlaying = 0;
                    REG_TM0CNT = TIMER_OFF;
                    DMA[1].ctrl = 0;
                }
            }
        }
        if (soundB.isPlaying) {
            soundB.vBlankCount++;
            if (soundB.vBlankCount >= soundB.durationInVBlanks) {
                if (soundB.looping) {
                    // loop sound
                    playSoundB(soundB.data, soundB.dataLength, soundB.looping);
                } else {
                    soundB.isPlaying = 0;
                    REG_TM1CNT = TIMER_OFF;
                    DMA[2].ctrl = 0;
                }
            }
        }
        if (soundC.isPlaying) {
            soundC.vBlankCount++;
            if (soundC.vBlankCount >= soundB.durationInVBlanks) {
                if (soundC.looping) {
                    // loop sound
                    playSoundB(soundC.data, soundC.dataLength, soundC.looping);
                } else {
                    soundB.isPlaying = 0;
                    REG_TM1CNT = TIMER_OFF;
                    DMA[2].ctrl = 0;
                }
            }
        }
    }
    REG_IF = REG_IF;
	REG_IME = 1;
} 