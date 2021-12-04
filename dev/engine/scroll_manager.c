#include "scroll_manager.h"
#include "../devkit/_sms_manager.h"

//title screen
unsigned int scroll_x[ 6 ];
unsigned char lineCnt;

void lineScrollHandler( void )
{
	devkit_SMS_setBGScrollX( ( scroll_x[ lineCnt++ ] ) >> 8 );
}

void init_scroll_title_screen()
{
	scroll_x[ 0 ] = 255 << 8;
	scroll_x[ 1 ] = 255 << 8;
	scroll_x[ 2 ] = 255 << 8;
	scroll_x[ 3 ] = 255 << 8;
	scroll_x[ 4 ] = 255 << 8;
	scroll_x[ 5 ] = 255 << 8;
	lineCnt = 0;

	devkit_SMS_setLineInterruptHandler( &lineScrollHandler );
	devkit_SMS_setLineCounter( 31 );    /* we're updating every 32 scanlines... */
	devkit_SMS_enableLineInterrupt();
}

