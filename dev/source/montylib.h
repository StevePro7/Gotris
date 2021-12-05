//
// Created by Jordi Montornes on 04/04/2017.
//

#ifndef GOTRIS_MONTYLIB_H_H
#define GOTRIS_MONTYLIB_H_H

#define VRAM_BASE_SPRITES 256
#define SCREEN_COLUMNS 32
#define SCREEN_ROWS 24
#define NUM_FPS_FRAME 60

#define KEY_DOWN	0x0002
#define KEY_LEFT	0x0004
#define KEY_RIGHT	0x0008
#define KEY_ONE     0x0010
#define KEY_TWO     0x0020

#define getRedFromRGB(color)        (color&11)
#define getGreenFromRGB(color)      ((color&1100)>>2)
#define getBlueFromRGB(color)      ((color&110000)>>4)

//void init_console();
void waitForFrame();

//unsigned char rand();
//unsigned char getKeysHeld();

//void fadeOutBGPalette(unsigned char *palette);
//void fadeInBGPalette(unsigned char *palette);
//void fadeOutSpritePalette(unsigned char *palette);
//void fadeInSpritePalette(unsigned char *palette);

#endif //GOTRIS_MONTYLIB_H_H
