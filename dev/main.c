#include "..\lib\\SMSlib.h"

#define productCode	9999
#define revision	0

#define verMaj		2
#define verMin		1
#define dateYear	2020
#define dateMonth	3
#define dateDay		27
#define author		"Steven Boland"
#define name		"Candy Kid"
#define descr		"Candy Kid game for the SMS Power! 2020 Competition"

void main( void )
{
	SMS_setSpritePaletteColor( 0, RGB( 3, 1, 0 ) );
	SMS_displayOn();
	for( ;;)
	{
		SMS_waitForVBlank();
	}
}

// Sega header.
#ifdef _CONSOLE
#else
SMS_EMBED_SEGA_ROM_HEADER( productCode, revision );
SMS_EMBED_SDSC_HEADER( verMaj, verMin, dateYear, dateMonth, dateDay, author, name, descr );
#endif