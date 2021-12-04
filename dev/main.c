#include "main.h"

void main( void )
{
	// Global variables.
	//static bool global_pause;
	unsigned char open_screen_type;

	devkit_SMS_init();
	//devkit_SMS_displayOff();

	devkit_SMS_setSpriteMode( devkit_SPRITEMODE_NORMAL() );
	devkit_SMS_useFirstHalfTilesforSprites_False();
	devkit_SMS_VDPturnOnFeature( devkit_VDPFEATURE_HIDEFIRSTCOL() );
	//devkit_SMS_zeroBGPalette();		// TODO
	

	open_screen_type = screen_type_title;
	engine_screen_manager_init( open_screen_type );
	//devkit_SMS_displayOn();
	for( ;;)
	{
		devkit_SMS_initSprites();
		engine_input_manager_update();
		engine_screen_manager_update();

		devkit_SMS_finalizeSprites();
		devkit_SMS_waitForVBlank();
		devkit_SMS_copySpritestoSAT();

		devkit_PSGFrame();
		devkit_PSGSFXFrame();
	}
}
