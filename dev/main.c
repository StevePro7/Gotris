#include "main.h"

void main( void )
{
	devkit_SMS_init();
	devkit_SMS_displayOff();

	devkit_SMS_setSpriteMode( devkit_SPRITEMODE_NORMAL() );
	devkit_SMS_useFirstHalfTilesforSprites_False();
	devkit_SMS_VDPturnOnFeature( devkit_VDPFEATURE_HIDEFIRSTCOL() );

	devkit_SMS_setSpritePaletteColor( 0, 3, 3, 3 );
	devkit_SMS_displayOn();
	for( ;;)
	{
		devkit_SMS_waitForVBlank();
	}
}
