#include "main.h"

void main( void )
{
	// Global variables.
	//static bool global_pause;

	devkit_SMS_init();
	devkit_SMS_displayOff();

	devkit_SMS_setSpriteMode( devkit_SPRITEMODE_NORMAL() );
	devkit_SMS_useFirstHalfTilesforSprites_False();
	devkit_SMS_VDPturnOnFeature( devkit_VDPFEATURE_HIDEFIRSTCOL() );
	//devkit_SMS_zeroBGPalette();		// TODO

	devkit_SMS_setSpritePaletteColor( 0, 1, 1, 1 );
	devkit_SMS_displayOn();
	for( ;;)
	{
		devkit_SMS_waitForVBlank();
	}
}
