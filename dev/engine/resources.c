//
// Created by JordiM on 13/04/2017.
//
#include <stdbool.h>
#include "resources.h"
#include "../libs/SMSlib.h"
#include "../libs/PSGlib.h"
#include "../libs/montylib.h"
#include "../bank2.h"
#include "../bank3.h"


extern unsigned int scroll_x[6];
extern unsigned char lineCnt;

const unsigned char pieces_palette[] = {
    //0x11,0x29,0x36,0x3E,0x3B,0x00,0x3F,0x2A,0x08,0x20,0x02,0x12,0x24,0x0F
    0x11,0x29,0x36,0x3E,0x3B,0x00,0x3F,0x2A,0x00,0x3F,0x2A,0x00,0x3F,0x2A
};


void load_logo_assets() {
    SMS_mapROMBank(logotiles_psgcompr_bank);
    SMS_loadPSGaidencompressedTiles(logotiles_psgcompr, 0);
    SMS_loadSTMcompressedTileMap(0, 0, logotilemap_stmcompr);
}

void logo_fade_in() {
    SMS_mapROMBank(logotiles_psgcompr_bank);
    fadeInBGPalette(logopalette_bin);
}

void logo_fade_out() {
    SMS_mapROMBank(logotiles_psgcompr_bank);
    fadeOutBGPalette(logopalette_bin);
}

void load_title_assets() {
    SMS_mapROMBank(titlescreentiles_psgcompr_bank);
    SMS_loadPSGaidencompressedTiles(titlescreentiles_psgcompr, 0);
    SMS_loadSTMcompressedTileMap(0, 0, titlescreentilemap_stmcompr);
}

void title_fade_in() {
    SMS_mapROMBank(titlescreentiles_psgcompr_bank);
    fadeInBGPalette(titlescreenpalette_bin);
}

void title_fade_out() {
    SMS_mapROMBank(titlescreentiles_psgcompr_bank);
    fadeOutBGPalette(titlescreenpalette_bin);
}

void game_fade_in() {
    SMS_mapROMBank(backgroundpalette_bin_bank);
    fadeInBGPalette(backgroundpalette_bin);
    fadeInSpritePalette(piecespalette_bin);
}

void game_fade_out() {
    SMS_mapROMBank(backgroundpalette_bin_bank);
    fadeOutBGPalette(backgroundpalette_bin);
    fadeOutSpritePalette(piecespalette_bin);
}

void play_logo_jingle() {
    SMS_mapROMBank(logo1985music_psg_bank);
    PSGPlay(logo1985music_psg);
}

void play_title_jingle() {
    SMS_mapROMBank(titlescreen_psg_bank);
    PSGPlay(titlescreen_psg);
}

void init_scroll_title_screen() {
    scroll_x[0] = 255<<8;
    scroll_x[1] = 255<<8;
    scroll_x[2] = 255<<8;
    scroll_x[3] = 255<<8;
    scroll_x[4] = 255<<8;
    scroll_x[5] = 255<<8;
    lineCnt = 0;
    SMS_VDPturnOnFeature(VDPFEATURE_LEFTCOLBLANK);
    SMS_setLineInterruptHandler(&lineScrollHandler);
    SMS_setLineCounter(31);    /* we're updating every 32 scanlines... */
    SMS_enableLineInterrupt();
}

void scroll_title_screen() {
    scroll_x[0] = scroll_x[0] - 128; //0.5<<8
    scroll_x[1] = scroll_x[1] - 160; //0.5<<8 + (0.125<<8)
    scroll_x[2] = scroll_x[2] - 160;
    scroll_x[3] = scroll_x[3] - 160;
    scroll_x[4] = scroll_x[4] - 160;
    //scroll_x[5] = scroll_x[5] - 1;

    lineCnt = 0;
}

void lineScrollHandler(void) {
  SMS_setBGScrollX((scroll_x[lineCnt++])>>8);
}

void clear_scroll_title_screen() {
    SMS_disableLineInterrupt();
    scroll_x[0] = 255<<8;
    scroll_x[1] = 255<<8;
    scroll_x[2] = 255<<8;
    scroll_x[3] = 255<<8;
    scroll_x[4] = 255<<8;
    scroll_x[5] = 255<<8;
    SMS_setBGScrollX(scroll_x[0]>>8);
    SMS_VDPturnOffFeature(VDPFEATURE_LEFTCOLBLANK);
}

void load_game_assets() {
    SMS_mapROMBank(backgroundpalette_bin_bank);
    SMS_loadPSGaidencompressedTiles(piecestiles_psgcompr, 0)
    SMS_loadPSGaidencompressedTiles(simplefont_psgcompr,DIGITS_BASE_ADDRESS);
    SMS_loadPSGaidencompressedTiles(backgroundtiles_psgcompr, DIGITS_BASE_ADDRESS + 10);
    
}

void game_full_palette() {
    SMS_mapROMBank(backgroundpalette_bin_bank);
    SMS_loadSpritePalette(pieces_palette);
}

void draw_game_background() {
    SMS_mapROMBank(backgroundtilemap_stmcompr_bank);
    SMS_loadSTMcompressedTileMap(0, 0, backgroundtilemap_stmcompr); 
}

void draw_game_screen() {
    unsigned char i,j;
    SMS_setTileatXY(10,0,TILE_USE_SPRITE_PALETTE|7);
    for(i=11;i < 21;i++) {
        SMS_setTileatXY(i,0,TILE_USE_SPRITE_PALETTE|8);
    }
    SMS_setTileatXY(10,0,TILE_USE_SPRITE_PALETTE|7);
    SMS_setTileatXY(21,0,TILE_USE_SPRITE_PALETTE|TILE_FLIPPED_X|7);
    for(j=1;j<23;j++) {
        SMS_setTileatXY(10,j,TILE_USE_SPRITE_PALETTE|9);
        for(i=11;i < 21;i++) {
            SMS_setTileatXY(i,j,TILE_USE_SPRITE_PALETTE|0);
        }
        SMS_setTileatXY(21,j,TILE_USE_SPRITE_PALETTE|TILE_FLIPPED_X|9);
    }
    SMS_setTileatXY(10,23,TILE_USE_SPRITE_PALETTE|TILE_FLIPPED_Y|7);
    SMS_setTileatXY(21,23,TILE_USE_SPRITE_PALETTE|TILE_FLIPPED_X|TILE_FLIPPED_Y|7);
    for(i=11;i < 21;i++) {
        SMS_setTileatXY(i,23,TILE_USE_SPRITE_PALETTE|TILE_FLIPPED_Y|8);
    }
}

void play_ingame_music() {
    SMS_mapROMBank(ingame_psg_bank);
    PSGPlay(ingame_psg);
}

void play_gameover_music() {
    SMS_mapROMBank(gameover_psg_bank);
    PSGPlay(gameover_psg);
}

void pieces_to_red_palette() {
    SMS_setNextSpriteColoratIndex(8);
    SMS_setColor(0x03);
    SMS_setColor(0x03);
    SMS_setColor(0x03);
}

void pieces_to_normal_palette() {
    SMS_setNextSpriteColoratIndex(8);
    SMS_setColor(0x00);
    SMS_setColor(0x3F);
    SMS_setColor(0x2A);
}

void print_unsigned_char(unsigned char x, unsigned char y, unsigned char number) {
    unsigned char tmpHundreds, tmpTens, tmpUnits;
    SMS_setNextTileatXY(x,y);
    tmpHundreds = number / 100;
    SMS_setTile(TILE_USE_SPRITE_PALETTE|DIGITS_BASE_ADDRESS + tmpHundreds);
    tmpTens = (number - (tmpHundreds * 100)) / 10;
    SMS_setTile(TILE_USE_SPRITE_PALETTE|DIGITS_BASE_ADDRESS + tmpTens);
    tmpUnits = (number - (tmpHundreds * 100) - (tmpTens * 10));
    SMS_setTile(TILE_USE_SPRITE_PALETTE|DIGITS_BASE_ADDRESS + tmpUnits);
}

void print_unsigned_int(unsigned char x, unsigned char y, unsigned int number) {
    unsigned char tmpTenThousands, tmpThousands, tmpHundreds, tmpTens, tmpUnits;
    SMS_setNextTileatXY(x,y);
    tmpTenThousands = number / 10000;
    SMS_setTile(TILE_USE_SPRITE_PALETTE|DIGITS_BASE_ADDRESS + tmpTenThousands);
    tmpThousands = (number - (tmpTenThousands * 10000)) / 1000;
    SMS_setTile(TILE_USE_SPRITE_PALETTE|DIGITS_BASE_ADDRESS + tmpThousands);
    tmpHundreds = (number - (tmpTenThousands * 10000) - (tmpThousands*1000)) / 100;
    SMS_setTile(TILE_USE_SPRITE_PALETTE|DIGITS_BASE_ADDRESS + tmpHundreds);
    tmpTens = (number - (tmpTenThousands * 10000) - (tmpThousands*1000) - (tmpHundreds * 100)) / 10;
    SMS_setTile(TILE_USE_SPRITE_PALETTE|DIGITS_BASE_ADDRESS + tmpTens);
    tmpUnits = (number - (tmpTenThousands * 10000) - (tmpThousands*1000) - (tmpHundreds * 100) - (tmpTens * 10));
    SMS_setTile(TILE_USE_SPRITE_PALETTE|DIGITS_BASE_ADDRESS + tmpUnits);
}

void print_score_value(unsigned char x, unsigned char y, unsigned int number) {
    unsigned char tmpTenThousands, tmpThousands, tmpHundreds, tmpTens, tmpUnits;
    SMS_setNextTileatXY(x,y);
    tmpTenThousands = number / 10000;
    SMS_setTile(TILE_USE_SPRITE_PALETTE|DIGITS_BASE_ADDRESS + tmpTenThousands);
    tmpThousands = (number - (tmpTenThousands * 10000)) / 1000;
    SMS_setTile(TILE_USE_SPRITE_PALETTE|DIGITS_BASE_ADDRESS + tmpThousands);
    tmpHundreds = (number - (tmpTenThousands * 10000) - (tmpThousands*1000)) / 100;
    SMS_setTile(TILE_USE_SPRITE_PALETTE|DIGITS_BASE_ADDRESS + tmpHundreds);
    tmpTens = (number - (tmpTenThousands * 10000) - (tmpThousands*1000) - (tmpHundreds * 100)) / 10;
    SMS_setTile(TILE_USE_SPRITE_PALETTE|DIGITS_BASE_ADDRESS + tmpTens);
    tmpUnits = (number - (tmpTenThousands * 10000) - (tmpThousands*1000) - (tmpHundreds * 100) - (tmpTens * 10));
    SMS_setTile(TILE_USE_SPRITE_PALETTE|DIGITS_BASE_ADDRESS + tmpUnits);
    SMS_setTile(TILE_USE_SPRITE_PALETTE|DIGITS_BASE_ADDRESS);
    SMS_setTile(TILE_USE_SPRITE_PALETTE|DIGITS_BASE_ADDRESS);
}