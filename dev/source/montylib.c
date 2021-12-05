//
// Created by Jordi Montornes on 04/04/2017.
//
#include "montylib.h"
//#include "SMSlib.h"
//#include "PSGlib.h"
//#include "randLut.h"
#include "../devkit/_sms_manager.h"
#include "../devkit/_snd_manager.h"
#include <stdbool.h>

//extern bool pause;
//extern unsigned char rand_index;
//extern unsigned int frame_cnt;
//
//void init_console() {
//    SMS_init();
//    SMS_setSpriteMode(SPRITEMODE_NORMAL);
//    SMS_displayOn();
//    pause = false;
//    rand_index = 0;
//}

void waitForFrame(){
	devkit_PSGFrame_Check();
	devkit_PSGSFXFrame_Check();
    devkit_SMS_waitForVBlank();
}

//unsigned char rand() {
//    return randLUT[rand_index++]; 
//}

//unsigned char getKeysHeld() {
//     return SMS_getKeysHeld();
//}

//void fadeOutBGPalette(unsigned char *palette) {
//    unsigned char i,j,redComponent, greenComponent, blueComponent;
//    unsigned char temporal_palette[16];
//    j= 0;
//    for(j = 0;j<16;j++) {
//        temporal_palette[j] = palette[j];
//    }
//    devkit_SMS_loadBGPalette(palette);
//    //green 
//    i = 0;
//    while(i<4) {
//        j = 0;
//        while(j<16) {
//            redComponent = getRedFromRGB(temporal_palette[j]);
//            greenComponent = getGreenFromRGB(temporal_palette[j]);
//            blueComponent = getBlueFromRGB(temporal_palette[j]);
//            if(greenComponent>0) {
//                greenComponent--;
//            }
//            temporal_palette[j] = RGB(redComponent,greenComponent,blueComponent);
//            j++;
//        }
//        waitForFrame();
//        devkit_SMS_loadBGPalette(temporal_palette);
//        i++;
//    }
//    //red
//    i = 0;
//    while(i<4) {
//        j = 0;
//        while(j<16) {
//            redComponent = getRedFromRGB(temporal_palette[j]);
//            greenComponent = getGreenFromRGB(temporal_palette[j]);
//            blueComponent = getBlueFromRGB(temporal_palette[j]);
//            if(redComponent>0) {
//                redComponent--;
//            }
//            temporal_palette[j] = RGB(redComponent,greenComponent,blueComponent);
//            j++;
//        }
//        waitForFrame();
//        devkit_SMS_loadBGPalette(temporal_palette);
//        i++;
//    }
//    //blue
//    i = 0;
//    while(i<4) {
//        j = 0;
//        while(j<16) {
//            redComponent = getRedFromRGB(temporal_palette[j]);
//            greenComponent = getGreenFromRGB(temporal_palette[j]);
//            blueComponent = getBlueFromRGB(temporal_palette[j]);
//            if(blueComponent>0) {
//                blueComponent--;
//            }
//            temporal_palette[j] = RGB(redComponent,greenComponent,blueComponent);
//            j++;
//        }
//        waitForFrame();
//        devkit_SMS_loadBGPalette(temporal_palette);
//        i++;
//    }
//    devkit_SMS_zeroBGPalette();
//}

void fadeInBGPalette(unsigned char *palette)
{
	unsigned char i, j, redComponent, greenComponent, blueComponent;
	unsigned char temporal_palette[ 16 ];
	devkit_SMS_zeroBGPalette();
	j = 0;
	for( j = 0; j < 16; j++ ) {
		temporal_palette[ j ] = 0;
	}
	// green
		i = 0;
	while( i < 4 ) {
		j = 0;
		while( j < 16 ) {
			redComponent = getRedFromRGB( temporal_palette[ j ] );
			greenComponent = getGreenFromRGB( temporal_palette[ j ] );
			blueComponent = getBlueFromRGB( temporal_palette[ j ] );
			if( greenComponent < getGreenFromRGB( palette[ j ] ) ) {
				greenComponent++;
			}
			temporal_palette[ j ] = devkit_RGB( redComponent, greenComponent, blueComponent );
			j++;
		}
		waitForFrame();
		devkit_SMS_loadBGPalette( temporal_palette );
		i++;
	}
	// red
		i = 0;
	while( i < 4 ) {
		j = 0;
		while( j < 16 ) {
			redComponent = getRedFromRGB( temporal_palette[ j ] );
			greenComponent = getGreenFromRGB( temporal_palette[ j ] );
			blueComponent = getBlueFromRGB( temporal_palette[ j ] );
			if( redComponent < getRedFromRGB( palette[ j ] ) ) {
				redComponent++;
			}
			temporal_palette[ j ] = devkit_RGB( redComponent, greenComponent, blueComponent );
			j++;
		}
		waitForFrame();
		devkit_SMS_loadBGPalette( temporal_palette );
		i++;
	}
	// blue
	i = 0;
	while( i < 4 ) {
		j = 0;
		while( j < 16 ) {
			redComponent = getRedFromRGB( temporal_palette[ j ] );
			greenComponent = getGreenFromRGB( temporal_palette[ j ] );
			blueComponent = getBlueFromRGB( temporal_palette[ j ] );
			if( blueComponent < getBlueFromRGB( palette[ j ] ) ) {
				blueComponent++;
			}
			temporal_palette[ j ] = devkit_RGB( redComponent, greenComponent, blueComponent );
			j++;
		}
		waitForFrame();
		devkit_SMS_loadBGPalette( temporal_palette );
		i++;
	}
}

//sprites

//void fadeOutSpritePalette(unsigned char *palette) {
//    unsigned char i,j,redComponent, greenComponent, blueComponent;
//    unsigned char temporal_palette[16];
//    j= 0;
//    for(j = 0;j<16;j++) {
//        temporal_palette[j] = palette[j];
//    }
//    SMS_loadSpritePalette(palette);
//    //green 
//    i = 0;
//    while(i<4) {
//        j = 0;
//        while(j<16) {
//            redComponent = getRedFromRGB(temporal_palette[j]);
//            greenComponent = getGreenFromRGB(temporal_palette[j]);
//            blueComponent = getBlueFromRGB(temporal_palette[j]);
//            if(greenComponent>0) {
//                greenComponent--;
//            }
//            temporal_palette[j] = RGB(redComponent,greenComponent,blueComponent);
//            j++;
//        }
//        waitForFrame();
//        SMS_loadSpritePalette(temporal_palette);
//        i++;
//    }
//    //red
//    i = 0;
//    while(i<4) {
//        j = 0;
//        while(j<16) {
//            redComponent = getRedFromRGB(temporal_palette[j]);
//            greenComponent = getGreenFromRGB(temporal_palette[j]);
//            blueComponent = getBlueFromRGB(temporal_palette[j]);
//            if(redComponent>0) {
//                redComponent--;
//            }
//            temporal_palette[j] = RGB(redComponent,greenComponent,blueComponent);
//            j++;
//        }
//        waitForFrame();
//        SMS_loadSpritePalette(temporal_palette);
//        i++;
//    }
//    //blue
//    i = 0;
//    while(i<4) {
//        j = 0;
//        while(j<16) {
//            redComponent = getRedFromRGB(temporal_palette[j]);
//            greenComponent = getGreenFromRGB(temporal_palette[j]);
//            blueComponent = getBlueFromRGB(temporal_palette[j]);
//            if(blueComponent>0) {
//                blueComponent--;
//            }
//            temporal_palette[j] = RGB(redComponent,greenComponent,blueComponent);
//            j++;
//        }
//        waitForFrame();
//        SMS_loadSpritePalette(temporal_palette);
//        i++;
//    }
//    SMS_zeroSpritePalette();
//}
//
//void fadeInSpritePalette(unsigned char *palette) {
//    unsigned char i,j,redComponent, greenComponent, blueComponent;
//    unsigned char temporal_palette[16];
//    SMS_zeroSpritePalette();
//    j= 0;
//    for(j = 0;j<16;j++) {
//        temporal_palette[j] = 0;
//    } 
//    //green 
//    i = 0;
//    while(i<4) {
//        j = 0;
//        while(j<16) {
//            redComponent = getRedFromRGB(temporal_palette[j]);
//            greenComponent = getGreenFromRGB(temporal_palette[j]);
//            blueComponent = getBlueFromRGB(temporal_palette[j]);
//            if(greenComponent<getGreenFromRGB(palette[j])) {
//                greenComponent++;
//            }
//            temporal_palette[j] = RGB(redComponent,greenComponent,blueComponent);
//            j++;
//        }
//        waitForFrame();
//        SMS_loadSpritePalette(temporal_palette);
//        i++;
//    }
//    //red
//    i = 0;
//    while(i<4) {
//        j = 0;
//        while(j<16) {
//            redComponent = getRedFromRGB(temporal_palette[j]);
//            greenComponent = getGreenFromRGB(temporal_palette[j]);
//            blueComponent = getBlueFromRGB(temporal_palette[j]);
//            if(redComponent<getRedFromRGB(palette[j])) {
//                redComponent++;
//            }
//            temporal_palette[j] = RGB(redComponent,greenComponent,blueComponent);
//            j++;
//        }
//        waitForFrame();
//        SMS_loadSpritePalette(temporal_palette);
//        i++;
//    }
//    //blue
//    i = 0;
//    while(i<4) {
//        j = 0;
//        while(j<16) {
//            redComponent = getRedFromRGB(temporal_palette[j]);
//            greenComponent = getGreenFromRGB(temporal_palette[j]);
//            blueComponent = getBlueFromRGB(temporal_palette[j]);
//            if(blueComponent<getBlueFromRGB(palette[j])) {
//                blueComponent++;
//            }
//            temporal_palette[j] = RGB(redComponent,greenComponent,blueComponent);
//            j++;
//        }
//        waitForFrame();
//        SMS_loadSpritePalette(temporal_palette);
//        i++;
//    }
//}