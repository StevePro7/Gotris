//
// Created by JordiM on 13/04/2017.
//

#ifndef GOTRIS_RESOURCES_H
#define GOTRIS_RESOURCES_H

#define DIGITS_BASE_ADDRESS 11

#define blackBackgroundPalette() SMS_zeroBGPalette()


void load_logo_assets();
void load_title_assets();
void play_logo_jingle();
void play_title_jingle();
void load_game_assets();

void logo_fade_in();
void logo_fade_out();

void title_fade_in();
void title_fade_out();

void init_scroll_title_screen();
void scroll_title_screen();
void lineScrollHandler(void);
void clear_scroll_title_screen();

void game_fade_in();
void game_fade_out();

void game_full_palette();
void draw_game_background();
void draw_game_screen();
void play_ingame_music();
void play_gameover_music();
#define stop_music() PSGStop()
#define draw_board_position(x, y, tile) SMS_setTileatXY(x+11,y+1,tile|TILE_USE_SPRITE_PALETTE)
void pieces_to_red_palette();
void pieces_to_normal_palette();
void print_unsigned_char(unsigned char x, unsigned char y, unsigned char number);
void print_unsigned_int(unsigned char x, unsigned char y, unsigned int number);
void print_score_value(unsigned char x, unsigned char y, unsigned int number);
#endif //GOTRIS_RESOURCES_H
