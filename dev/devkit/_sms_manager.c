#include "_sms_manager.h"
#include "..\game.h"
#include <stdbool.h>

#ifdef _CONSOLE
#include "..\..\tmp\SMSlib.h"
#else
#include "..\..\lib\SMSlib.h"
#endif

void devkit_SMS_init()
{
	SMS_init();
}
void devkit_SMS_displayOn()
{
	SMS_displayOn();
}
void devkit_SMS_displayOff()
{
	SMS_displayOff();
}
void devkit_SMS_mapROMBank( unsigned char n )
{
	SMS_mapROMBank( n );
}

void devkit_SMS_enableSRAM()
{
	SMS_enableSRAM();
}
void devkit_SMS_enableSRAMBank( unsigned char n )
{
	SMS_enableSRAMBank( n );
}
void devkit_SMS_disableSRAM()
{
	SMS_disableSRAM();
}
unsigned char* devkit_SMS_SRAM()
{
	return SMS_SRAM;
}

void devkit_SMS_setBGScrollX( unsigned char scrollX )
{
	SMS_setBGScrollX( scrollX );
}
void devkit_SMS_setBGScrollY( unsigned char scrollY )
{
	SMS_setBGScrollY( scrollY );
}
void devkit_SMS_setBackdropColor( unsigned char entry )
{
	SMS_setBackdropColor( entry );
}



void devkit_SMS_setSpriteMode( unsigned char mode )
{
	SMS_setSpriteMode( mode );
}
void devkit_SMS_useFirstHalfTilesforSprites_False()
{
	SMS_useFirstHalfTilesforSprites( false );
}
void devkit_SMS_useFirstHalfTilesforSprites_True()
{
	SMS_useFirstHalfTilesforSprites( true );
}
void devkit_SMS_VDPturnOnFeature( unsigned int feature )
{
	SMS_VDPturnOnFeature( feature );
}

void devkit_SMS_loadPSGaidencompressedTiles( void *src, unsigned int tilefrom )
{
	SMS_loadPSGaidencompressedTiles( src, tilefrom );
}
void devkit_SMS_loadSTMcompressedTileMap( unsigned char x, unsigned char y, unsigned char *src )
{
	SMS_loadSTMcompressedTileMap( x, y, src );
}

void devkit_SMS_loadBGPalette( void *palette )
{
	SMS_loadBGPalette( palette );
}
void devkit_SMS_loadSpritePalette( void *palette )
{
	SMS_loadSpritePalette( palette );
}
void devkit_SMS_setSpritePaletteColor( const unsigned char entry, const unsigned char r, const unsigned char g, const unsigned char b )
{
	const unsigned char color = RGB( r, g, b );
	SMS_setSpritePaletteColor( entry, color );
}



void devkit_SMS_setNextTileatXY( unsigned char x, unsigned char y )
{
	SMS_setNextTileatXY( x, y );
}
void devkit_SMS_setTile( const unsigned int tile )
{
	SMS_setTile( tile );
}
void devkit_SMS_setTilePriority( const unsigned char tile )
{
	SMS_setTile( tile | TILE_PRIORITY | TILE_USE_SPRITE_PALETTE );
}

void devkit_SMS_addSprite( unsigned char x, unsigned char y, int tile )
{
	SMS_addSprite( x, y, tile );
}
void devkit_SMS_initSprites()
{
	SMS_initSprites();
}
void devkit_SMS_finalizeSprites()
{
	SMS_finalizeSprites();
}
void devkit_SMS_waitForVBlank()
{
	SMS_waitForVBlank();
}
void devkit_SMS_copySpritestoSAT()
{
	UNSAFE_SMS_copySpritestoSAT();
}
void devkit_UNSAFE_SMS_copySpritestoSAT()
{
	UNSAFE_SMS_copySpritestoSAT();
}

unsigned char devkit_SMS_queryPauseRequested()
{
	return SMS_queryPauseRequested();
}
void devkit_SMS_resetPauseRequest()
{
	SMS_resetPauseRequest();
}

void devkit_SMS_setLineInterruptHandler( void( *theHandlerFunction )( void ) )
{
	SMS_setLineInterruptHandler( *theHandlerFunction );
}
void devkit_SMS_setLineCounter( unsigned char count )
{
	SMS_setLineCounter( count );
}
void devkit_SMS_enableLineInterrupt()
{
	SMS_VDPturnOnFeature( 0x0010 );   /* turns on line IRQ */
}

void devkit_SMS_disableLineInterrupt()
{
	SMS_VDPturnOffFeature( 0x0010 );  /* turns off line IRQ */
}

/* SMS functions to set a color / load a palette */
void devkit_RGB( const unsigned char r, const unsigned char g, const unsigned char b )
{
	RGB( r, g, b );
}
void devkit_RGB8( const unsigned char r, const unsigned char g, const unsigned char b )
{
	RGB8( r, g, b );
}
void devkit_RGBHTML( const unsigned long RGB24bit )
{
	RGBHTML( RGB24bit );
}
void devkit_SMS_loadBGPaletteHalfBrightness( void *palette )
{
	SMS_loadBGPaletteHalfBrightness( palette );
}
void devkit_SMS_loadSpritePaletteHalfBrightness( void *palette )
{
	SMS_loadSpritePaletteHalfBrightness( palette );
}
void devkit_SMS_zeroBGPalette( void )
{
	SMS_zeroBGPalette();
}
void devkit_SMS_zeroSpritePalette( void )
{
	SMS_zeroSpritePalette();
}


// collision
unsigned char devkit_isCollisionDetected()
{
	return ( SMS_VDPFlags & VDPFLAG_SPRITECOLLISION );
}

// input
unsigned int devkit_SMS_getKeysStatus()
{
	return SMS_getKeysStatus();
}

// #defines
unsigned char devkit_SPRITEMODE_NORMAL()
{
	return SPRITEMODE_NORMAL;
}
unsigned int devkit_VDPFEATURE_HIDEFIRSTCOL()
{
	return VDPFEATURE_HIDEFIRSTCOL;
}
unsigned int devkit_TILE_PRIORITY()
{
	return TILE_PRIORITY;
}
unsigned int devkit_TILE_USE_SPRITE_PALETTE()
{
	return TILE_USE_SPRITE_PALETTE;
}

// Sega header.
#ifdef _CONSOLE
#else
	SMS_EMBED_SEGA_ROM_HEADER( productCode, revision );
	SMS_EMBED_SDSC_HEADER( verMaj, verMin, dateYear, dateMonth, dateDay, author, name, descr );
#endif