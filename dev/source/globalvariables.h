#ifndef GOTRIS_GLOBALVARIABLES_H_H
#define GOTRIS_GLOBALVARIABLES_H_H

//montylib
bool pause;
unsigned char rand_index;
unsigned int frame_cnt;

//title screen
unsigned int scroll_x[6];
unsigned char lineCnt;

//game logic
unsigned char game_status;
unsigned int score;
bool piecesUpdated;
bool piecesDestroyed;
bool downPressed;
bool leftPressed;
bool rightPressed;
bool keyonePressed;
bool keytwoPressed;
bool isPaletteRed;
unsigned char fallRatio;

//board
//10 tokens wide (5 squares), 22 token high  (11 squares)
unsigned char board[220];
unsigned char piece_index;
unsigned char row_index;

piece active_pieces[MAX_PIECES_ACTIVE];
square current_square;
#endif //GOTRIS_GLOBALVARIABLES_H_H