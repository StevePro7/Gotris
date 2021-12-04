//
// Created by Jordi Montornes on 07/04/2017.
//
#include <stdbool.h>
#include "gamelogic.h"
#include "globaldefinitions.h"
#include "board.h"
#include "resources.h"
#include "../libs/montylib.h"
#include "../libs/SMSlib.h"
#include "../libs/PSGlib.h"

extern unsigned char game_status;
extern unsigned int score;
extern bool piecesUpdated;
extern bool piecesDestroyed;
extern bool downPressed;
extern bool leftPressed;
extern bool rightPressed;
extern bool keyonePressed;
extern bool keytwoPressed;
extern unsigned char piece_index;
extern unsigned char row_index;
extern square current_square;
extern piece active_pieces[MAX_PIECES_ACTIVE];

extern unsigned int frame_cnt;
extern unsigned char rand_index;
extern bool pause;

extern unsigned char board[220];

extern bool isPaletteRed;
extern unsigned char fallRatio;


void init_game() {
    init_console();
    blackBackgroundPalette();
}

void init_gamestatus() {
    game_status = GAME_STATUS_NOACTION;
    score = 0;
    piece_index = 0;
    row_index = 0;
    piecesUpdated = false;
    piecesDestroyed = false;
    isPaletteRed = false;
    fallRatio = 63;
}

void logo_screen() {
    load_logo_assets();
    frame_cnt = 0;
    logo_fade_in();
    play_logo_jingle();
    while (frame_cnt < 60) {
        frame_cnt++;
        waitForFrame();
    }
    logo_fade_out();
    stop_music();
    blackBackgroundPalette();
}

void title_screen() {
    load_title_assets();
    init_scroll_title_screen();
    title_fade_in();
    frame_cnt = 0;
    play_title_jingle();
    while (!keyonePressed) {
        frame_cnt++;
        get_control_input();
        waitForFrame();
        scroll_title_screen();
    }
    frame_cnt = 0;
    rand_index = frame_cnt; 
    //rand_index = 0; //Uncoment that for deterministic gameplay
    title_fade_out();
    clear_scroll_title_screen();
    stop_music();
}

void game_loop() {
    load_game_assets();
    draw_game_background();
    init_board();
    game_fade_in();
    game_full_palette();
    frame_cnt = 0;
    while(frame_cnt < 180) {
        frame_cnt++;
        waitForFrame();
    }
    play_ingame_music();
    draw_game_screen();
    init_gamestatus();
    print_score_value(24,22,score);
    while (game_status!=GAME_STATUS_RESET) {
        if(!pause) {
            execute_game_logic();
            get_control_input();
        }
        waitForFrame();
        frame_cnt++;
    }
    game_fade_out();
    blackBackgroundPalette();
    frame_cnt = 0;
    while(frame_cnt < 180) {
        frame_cnt++;
        waitForFrame();
    }
}

void generate_square_piece() {
    unsigned char randnumber;
    randnumber = rand();
    current_square.x = (randnumber & 7) + 1;
    current_square.y = 0;
    if(!is_free_board_position_for_square_creation()) {
        game_status = GAME_STATUS_LOOSING_GAME;
        row_index = BOARD_ROWS - 1;
        stop_music();
        return;
    }
    randnumber = rand() & 1;
    if(randnumber) {
        current_square.color00 = WHITE_PIECE;   
    } else {
        current_square.color00 = BLACK_PIECE;
    }
    randnumber = rand() & 1;
    if(randnumber) {
        current_square.color01 = WHITE_PIECE;   
    } else {
        current_square.color01 = BLACK_PIECE;
    }
    randnumber = rand() & 1;
    if(randnumber) {
        current_square.color10 = WHITE_PIECE;   
    } else {
        current_square.color10 = BLACK_PIECE;
    }
    randnumber = rand() & 1;
    if(randnumber) {
        current_square.color11 = WHITE_PIECE;   
    } else {
        current_square.color11 = BLACK_PIECE;
    }
    game_status = GAME_STATUS_SQUAREPIECEFALLING;
}

void fall_square_piece() {
    if((frame_cnt & 1) == 0) {
        if(downPressed && current_square.y < (BOARD_ROWS - 2) && is_free_board_down_position_for_square((current_square.y << 3) + (current_square.y << 1) + current_square.x)) {
            delete_square_pieces_board();
            current_square.y++;
            put_square_pieces_board();
        }
        downPressed = false;
    }
    if((frame_cnt & 7) == 0) {
        if(rightPressed && (current_square.x < BOARD_COLUMNS -2) && is_free_board_right_position_for_square((current_square.y << 3) + (current_square.y << 1) + current_square.x)) {
            delete_square_pieces_board();
            current_square.x++;
            put_square_pieces_board();
        } 
        else if(leftPressed && (current_square.x > 0 && is_free_board_left_position_for_square((current_square.y << 3) + (current_square.y << 1) + current_square.x))) {
            delete_square_pieces_board();
            current_square.x--;
            put_square_pieces_board();
        }

        if(keyonePressed) {
            delete_square_pieces_board();
            rotate_square_piece();
            put_square_pieces_board();
        } else if(keytwoPressed) {
            delete_square_pieces_board();
            rotate_inv_square_piece();
            put_square_pieces_board();
        }
        leftPressed = false;
        rightPressed = false;
        keyonePressed = false;
        keytwoPressed = false;
    }
    if((frame_cnt & fallRatio) == 0 ) {
        if(current_square.y < (BOARD_ROWS - 2) && is_free_board_down_position_for_square((current_square.y+1 << 3) + (current_square.y+1 << 1) + current_square.x)) {
            delete_square_pieces_board();
            current_square.y++;
            put_square_pieces_board();
        } else {
            create_individual_pieces_from_square();
            game_status = GAME_STATUS_PIECESFALLING;
            return;
        }
    }
}

bool fall_pieces() {
    bool onepieceupdated = false;
    unsigned char i = 0;
    for(i = 0;i<piece_index;i++) {
        if(active_pieces[i].color != NULLED_PIECE) {
            //only works if downside pieces created before upside's
            if(active_pieces[i].y < (BOARD_ROWS - 1) && is_free_board_next_position_for_piece(i)) {
                delete_individual_pieces_board(i);
                active_pieces[i].y++;
                put_individual_pieces_board(i);
                onepieceupdated = true;
            } else {
                mark_position_for_change_in_board(active_pieces[i].x,active_pieces[i].y);
                active_pieces[i].color = NULLED_PIECE;
            }
        }
    }
    return onepieceupdated;
}

bool compute_paths() {
    bool somePiece = false;
    bool someChangeHappened = false;
    unsigned char position = (row_index << 3) + (row_index << 1);
    unsigned char i;
    for(i=0;i<BOARD_COLUMNS;i++) {
        if(!is_free_board_position(position)) {
            someChangeHappened = someChangeHappened || compute_path(i,row_index);
            somePiece = true;
        }
        position++;
    }
    if(row_index > 0 && somePiece) {
        row_index--;
    } else {
        game_status = GAME_STATUS_CHECK_CALCULATIONS; 
    }
    return someChangeHappened;
}

bool compute_disconnected_pieces() {
    bool somePiece = false;
    bool somePieceDestroyed = false;
    unsigned char position = (row_index << 3) + (row_index << 1);
    unsigned char i;
    for(i=0;i<BOARD_COLUMNS;i++) {
        if(!is_free_board_position(position)) {
            somePieceDestroyed = mark_as_disconnected(i, row_index, position) || somePieceDestroyed;
            somePiece = true;
        }
        position++;
    }
    if(row_index > 0 && somePiece) {
        row_index--;
    } else {
        game_status = GAME_STATUS_ANIMATE_DISCONNECTED;   
        frame_cnt = 0;
        row_index = BOARD_ROWS-1;
    }
    return somePieceDestroyed;
}

void destroy_disconnected_pieces() {
    bool somePiece = false;
    unsigned char position = (row_index << 3) + (row_index << 1);
    unsigned char i;
    unsigned char numPiecesDestroyed = 0;
    for(i=0;i<BOARD_COLUMNS;i++) {
        if(!is_free_board_position(position)) {
            numPiecesDestroyed = numPiecesDestroyed + destroy_disconnected(i, row_index, position);
            somePiece = true;
        }
        position++;
    }
    score = score + numPiecesDestroyed;
    if(fallRatio == 63 && score > 10) {
        fallRatio = 31;
    }
    if(fallRatio == 31 && score > 100) {
        fallRatio = 15;
    }
    if(fallRatio == 15 && score > 500) { 
        fallRatio = 7;
    }
    print_score_value(24,22,score);
    if(row_index > 0 && somePiece) {
        row_index--;
    } else {
        game_status = GAME_STATUS_MAKE_PIECES_FALL;
        row_index = BOARD_ROWS-1;
        piecesUpdated = false;
    }
}

bool make_pieces_fall() {
    bool somePieceFalled = false;
    unsigned char position = (row_index << 3) + (row_index << 1);
    unsigned char i;
    for(i=0;i<BOARD_COLUMNS;i++) {
        if(!is_free_board_position(position) && is_free_board_next_position(i, row_index)) {
            create_individual_pieces_from_board_position(i, row_index, position);
            somePieceFalled = true;
        }
        position++;
    }
    if(row_index > 0) {
        row_index--;
    } else {
        game_status = GAME_STATUS_CHECK_PIECES_FALL;
        row_index = BOARD_ROWS-1;
    }
    return somePieceFalled;
}

void clear_line() {
    unsigned char i;
    for(i=0;i<BOARD_COLUMNS;i++) {
        block_board_position(i, row_index);
    }
}

void execute_game_logic() {
    if(game_status == GAME_STATUS_NOACTION) {
        generate_square_piece();
    } else if(game_status == GAME_STATUS_SQUAREPIECEFALLING) {
        fall_square_piece();
    } else if(game_status == GAME_STATUS_PIECESFALLING) {
        piecesUpdated = fall_pieces();
        if(!piecesUpdated) {
            game_status = GAME_STATUS_CALCULATIONS;
            piece_index = 0;
            row_index = BOARD_ROWS-1;
            piecesUpdated = false;
        }
    } else if(game_status == GAME_STATUS_CALCULATIONS) {
        piecesUpdated = compute_paths() || piecesUpdated;
    } else if(game_status == GAME_STATUS_CHECK_CALCULATIONS) {
        if(!piecesUpdated) {
            game_status = GAME_STATUS_COMPUTE_DISCONNECTED;
            row_index = BOARD_ROWS-1;
            piecesUpdated = false;
        } else {
            game_status = GAME_STATUS_CALCULATIONS;
            row_index = BOARD_ROWS-1;
            piecesUpdated = false;
        }
    } else if(game_status == GAME_STATUS_COMPUTE_DISCONNECTED) {
        piecesUpdated = compute_disconnected_pieces() || piecesUpdated;
    } else if(game_status == GAME_STATUS_ANIMATE_DISCONNECTED) {
        if(!piecesUpdated) {
            game_status = GAME_STATUS_DESTROY_DISCONNECTED;
        } else {
            if(frame_cnt > 120) {
                game_status = GAME_STATUS_DESTROY_DISCONNECTED;
            } else {
                if((frame_cnt & 7) == 0) {
                    if(!isPaletteRed) {
                        pieces_to_red_palette();
                        isPaletteRed = true;
                    } else {
                        pieces_to_normal_palette();
                        isPaletteRed = false;
                    }
                } 
                
            }
        }
    } else if(game_status == GAME_STATUS_DESTROY_DISCONNECTED) {
        if(!piecesUpdated) {
            game_status = GAME_STATUS_NOACTION;
            row_index = BOARD_ROWS-1;
            piecesUpdated = false;
        } else {
            destroy_disconnected_pieces();  
        }
    } else if(game_status == GAME_STATUS_MAKE_PIECES_FALL) {
        piecesUpdated = make_pieces_fall() || piecesUpdated;
    }  else if(game_status == GAME_STATUS_CHECK_PIECES_FALL) {
        if(!piecesUpdated) {
            game_status = GAME_STATUS_CALCULATIONS;
            row_index = BOARD_ROWS-1;
            piecesUpdated = false;
        } else {
            game_status = GAME_STATUS_PIECESFALLING_2;
            row_index = BOARD_ROWS-1;
            piecesUpdated = false;
        }
    } else if(game_status == GAME_STATUS_PIECESFALLING_2) {
        piecesUpdated = fall_pieces();
        if(!piecesUpdated) {
            game_status = GAME_STATUS_MAKE_PIECES_FALL;
            piece_index = 0;
            row_index = BOARD_ROWS-1;
            piecesUpdated = false;
        }
    } else if(game_status == GAME_STATUS_LOOSING_GAME) {
        if(row_index > 0) {
            clear_line();
            row_index--;
        } else {
            clear_line();
            play_gameover_music();
            game_status = GAME_STATUS_GAMEOVER;
            frame_cnt = 0;
        }
    } else if(game_status == GAME_STATUS_GAMEOVER) {
            if(frame_cnt > 250) {
                game_status = GAME_STATUS_RESET;
            }
    }
}

void get_control_input() {
    unsigned char keys = getKeysHeld();
    if(keys & KEY_ONE) {
        if(keytwoPressed) {
            keyonePressed = false;
            keytwoPressed = false;
        } else {
            keyonePressed = true;    
        }
    }
    if(keys & KEY_TWO) {
        if(keyonePressed) {
            keyonePressed = false;
            keytwoPressed = false;
        } else {
            keytwoPressed = true;
        }
    }
    if(keys & KEY_DOWN) {
        downPressed = true;
    }
    if(keys & KEY_LEFT) {
        if(rightPressed) {
            rightPressed = false;
            leftPressed = false;
        } else {
            leftPressed = true;
        }
    }
    if(keys & KEY_RIGHT) {
        if(leftPressed) {
            rightPressed = false;
            leftPressed = false;
        } else {
            rightPressed = true;
        }
    }
}
