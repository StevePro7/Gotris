#include "fade_manager.h"
#include "../devkit/_sms_manager.h"
#include "../banks/bank2.h"

void title_fade_in()
{
	devkit_SMS_mapROMBank( titlescreentiles_psgcompr_bank );
	//fadeInBGPalette( ( void * ) titlescreenpalette_bin );
}
void title_fade_out()
{
}

//void fadeInBGPalette( unsigned char *palette )
//{
//	unsigned char i, j, redComponent, greenComponent, blueComponent;
//	unsigned char temporal_palette[ 16 ];
//	devkit_SMS_zeroBGPalette();
//	j = 0;
//	for( j = 0; j < 16; j++ ) {
//		temporal_palette[ j ] = 0;
//	}
//	//green 
//	i = 0;
//	while( i < 4 ) {
//		j = 0;
//		while( j < 16 ) {
//			redComponent = getRedFromRGB( temporal_palette[ j ] );
//			greenComponent = getGreenFromRGB( temporal_palette[ j ] );
//			blueComponent = getBlueFromRGB( temporal_palette[ j ] );
//			if( greenComponent < getGreenFromRGB( palette[ j ] ) ) {
//				greenComponent++;
//			}
//			temporal_palette[ j ] = RGB( redComponent, greenComponent, blueComponent );
//			j++;
//		}
//		waitForFrame();
//		SMS_loadBGPalette( temporal_palette );
//		i++;
//	}
//}