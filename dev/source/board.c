//
// Created by Jordi Montornes on 04/04/2017.
//
#include <stdbool.h>
#include "board.h"
#include "globaldefinitions.h"
#include "resources.h"
#include "../libs/SMSlib.h"

extern unsigned char board[220];
extern unsigned char piece_index;
extern unsigned char row_index;

extern piece active_pieces[MAX_PIECES_ACTIVE];
extern square current_square;

void init_board() {
    unsigned char i,j;
    i=0;
    while(i<BOARD_ROWS) {
        j = 0;
        while(j<BOARD_COLUMNS) {
            board[(i << 3) + (i << 1) + j] = EMPTY_CELL;
            j++;
        }
        i++;
    }
}

void delete_square_pieces_board() {
    unsigned char position = (current_square.y << 3) + (current_square.y << 1) + current_square.x;
    board[position] = EMPTY_CELL;
    board[position+1] = EMPTY_CELL;
    board[position+10] = EMPTY_CELL;
    board[position+11] = EMPTY_CELL;
    draw_board_position(current_square.x, current_square.y, EMPTY_CELL);
    draw_board_position(current_square.x+1, current_square.y, EMPTY_CELL);
    draw_board_position(current_square.x, current_square.y+1, EMPTY_CELL);
    draw_board_position(current_square.x+1, current_square.y+1, EMPTY_CELL);
}

void create_individual_pieces_from_square() {
    //always create downside pieces before upside's
    active_pieces[piece_index].x = current_square.x;
    active_pieces[piece_index].y = current_square.y+1;
    active_pieces[piece_index].color = current_square.color10;
    piece_index++;
    active_pieces[piece_index].x = current_square.x+1;
    active_pieces[piece_index].y = current_square.y+1;
    active_pieces[piece_index].color = current_square.color11;
    piece_index++;
    active_pieces[piece_index].x = current_square.x;
    active_pieces[piece_index].y = current_square.y;
    active_pieces[piece_index].color = current_square.color00;
    piece_index++;
    active_pieces[piece_index].x = current_square.x+1;
    active_pieces[piece_index].y = current_square.y;
    active_pieces[piece_index].color = current_square.color01;
    piece_index++;
}

void create_individual_pieces_from_board_position(unsigned char x, unsigned char y, unsigned char position2check) {
    active_pieces[piece_index].x = x;
    active_pieces[piece_index].y = y;
    if(board[position2check] == CONNECTED_WHITE_CELL) {
        active_pieces[piece_index].color = WHITE_PIECE;
    } else if(board[position2check] == CONNECTED_BLACK_CELL){
        active_pieces[piece_index].color = BLACK_PIECE;
    }
    piece_index++;
}

void rotate_square_piece() {
    unsigned char backupColor00, backupColor01, backupColor10, backupColor11;
    backupColor00 =  current_square.color00;
    backupColor01 =  current_square.color01;
    backupColor10 =  current_square.color10;
    backupColor11 =  current_square.color11;
    current_square.color00 = backupColor01;
    current_square.color01 = backupColor11;
    current_square.color10 = backupColor00;
    current_square.color11 = backupColor10;
}

void rotate_inv_square_piece() {
    unsigned char backupColor00, backupColor01, backupColor10, backupColor11;
    backupColor00 =  current_square.color00;
    backupColor01 =  current_square.color01;
    backupColor10 =  current_square.color10;
    backupColor11 =  current_square.color11;
    current_square.color00 = backupColor10;
    current_square.color01 = backupColor00;
    current_square.color10 = backupColor11;
    current_square.color11 = backupColor01;
}

void delete_individual_pieces_board(unsigned char index) {     
    unsigned char position = (active_pieces[index].y << 3) + (active_pieces[index].y << 1) + active_pieces[index].x;
    board[position] = EMPTY_CELL;
    draw_board_position(active_pieces[index].x, active_pieces[index].y, EMPTY_CELL);
}

void put_individual_pieces_board(unsigned char index) {
    unsigned char position = (active_pieces[index].y << 3) + (active_pieces[index].y << 1) + active_pieces[index].x;
    board[position] = active_pieces[index].color;
    draw_board_position(active_pieces[index].x, active_pieces[index].y, active_pieces[index].color);
}

void mark_position_for_change_in_board(unsigned char x, unsigned char y) {
    //posible optimización usando restas 
    unsigned char position = (y << 3) + (y << 1) + x;
    if(x > 0 && board[position-1] == CONNECTED_WHITE_CELL) {
        board[position-1] = NOT_PROCESSED_WHITE_CELL;
        draw_board_position(x-1, y, NOT_PROCESSED_WHITE_CELL);
        mark_position_for_change_in_board_rec(x-1, y, NOT_PROCESSED_WHITE_CELL);
    }
    if(x<BOARD_COLUMNS-1 && board[position+1] == CONNECTED_WHITE_CELL) {
        board[position+1] = NOT_PROCESSED_WHITE_CELL;
        draw_board_position(x+1, y, NOT_PROCESSED_WHITE_CELL);
        mark_position_for_change_in_board_rec(x+1, y, NOT_PROCESSED_WHITE_CELL);
    }
    if(y<BOARD_ROWS-1 && board[position+10] == CONNECTED_WHITE_CELL) {
        board[position+10] = NOT_PROCESSED_WHITE_CELL;
        draw_board_position(x, y+1, NOT_PROCESSED_WHITE_CELL);
        mark_position_for_change_in_board_rec(x, y+1, NOT_PROCESSED_WHITE_CELL);
    }
    if(x > 0 && board[position-1] == CONNECTED_BLACK_CELL) {
        board[position-1] = NOT_PROCESSED_BLACK_CELL;
        draw_board_position(x-1, y, NOT_PROCESSED_BLACK_CELL);
        mark_position_for_change_in_board_rec(x-1, y, NOT_PROCESSED_BLACK_CELL);
    }
    if(x<BOARD_COLUMNS-1 && board[position+1] == CONNECTED_BLACK_CELL) {
        board[position+1] = NOT_PROCESSED_BLACK_CELL;
        draw_board_position(x+1, y, NOT_PROCESSED_BLACK_CELL);
        mark_position_for_change_in_board_rec(x+1, y, NOT_PROCESSED_BLACK_CELL);
    }
    if(y<BOARD_ROWS-1 && board[position+10] == CONNECTED_BLACK_CELL) {
        board[position+10] = NOT_PROCESSED_BLACK_CELL;
        draw_board_position(x, y+1, NOT_PROCESSED_BLACK_CELL);
        mark_position_for_change_in_board_rec(x, y+1, NOT_PROCESSED_BLACK_CELL);
    }
}

void mark_position_for_change_in_board_rec(unsigned char x, unsigned char y, unsigned char color) {
    unsigned char position = (y << 3) + (y << 1) + x;
    if(color == NOT_PROCESSED_WHITE_CELL) {
        if(x > 0 && board[position-1] == CONNECTED_WHITE_CELL) {
            board[position-1] = NOT_PROCESSED_WHITE_CELL;
            draw_board_position(x-1, y, NOT_PROCESSED_WHITE_CELL);
            mark_position_for_change_in_board_rec(x-1, y, NOT_PROCESSED_WHITE_CELL);
        }
        if(x<BOARD_COLUMNS-1 && board[position+1] == CONNECTED_WHITE_CELL) {
            board[position+1] = NOT_PROCESSED_WHITE_CELL;
            draw_board_position(x+1, y, NOT_PROCESSED_WHITE_CELL);
            mark_position_for_change_in_board_rec(x+1, y, NOT_PROCESSED_WHITE_CELL);
        }
        if(y > 0 && board[position-10] == CONNECTED_WHITE_CELL) {
            board[position-10] = NOT_PROCESSED_WHITE_CELL;
            draw_board_position(x, y-1, NOT_PROCESSED_WHITE_CELL);
            mark_position_for_change_in_board_rec(x, y-1, NOT_PROCESSED_WHITE_CELL);
        }
        if(y<BOARD_ROWS-1 && board[position+10] == CONNECTED_WHITE_CELL) {
            board[position+10] = NOT_PROCESSED_WHITE_CELL;
            draw_board_position(x, y+1, NOT_PROCESSED_WHITE_CELL);
            mark_position_for_change_in_board_rec(x, y+10, NOT_PROCESSED_WHITE_CELL);
        }
    } else if(color == NOT_PROCESSED_BLACK_CELL) {
        if(x > 0 && board[position-1] == CONNECTED_BLACK_CELL) {
            board[position-1] = NOT_PROCESSED_BLACK_CELL;
            draw_board_position(x-1, y, NOT_PROCESSED_BLACK_CELL);
            mark_position_for_change_in_board_rec(x-1, y, NOT_PROCESSED_BLACK_CELL);
        }
        if(x<BOARD_COLUMNS-1 && board[position+1] == CONNECTED_BLACK_CELL) {
            board[position+1] = NOT_PROCESSED_BLACK_CELL;
            draw_board_position(x+1, y, NOT_PROCESSED_BLACK_CELL);
            mark_position_for_change_in_board_rec(x+1, y, NOT_PROCESSED_BLACK_CELL);
        }
        if(y > 0 && board[position-10] == CONNECTED_BLACK_CELL) {
            board[position-10] = NOT_PROCESSED_BLACK_CELL;
            draw_board_position(x, y-1, NOT_PROCESSED_BLACK_CELL);
            mark_position_for_change_in_board_rec(x, y-1, NOT_PROCESSED_BLACK_CELL);
        }
        if(y<BOARD_ROWS-1 && board[position+10] == CONNECTED_BLACK_CELL) {
            board[position+10] = NOT_PROCESSED_BLACK_CELL;
            draw_board_position(x, y+1, NOT_PROCESSED_BLACK_CELL);
            mark_position_for_change_in_board_rec(x, y+10, NOT_PROCESSED_BLACK_CELL);
        }
    }
}

void put_square_pieces_board() {
    unsigned char position = (current_square.y << 3) + (current_square.y << 1) + current_square.x;
    board[position] = current_square.color00;
    board[position+1] = current_square.color01;
    board[position+10] = current_square.color10;
    board[position+11] = current_square.color11;
    draw_board_position(current_square.x, current_square.y, current_square.color00);
    draw_board_position(current_square.x+1, current_square.y, current_square.color01);
    draw_board_position(current_square.x, current_square.y+1, current_square.color10);
    draw_board_position(current_square.x+1, current_square.y+1, current_square.color11);
}

bool compute_path(unsigned char x, unsigned char y) {
    unsigned char position = (y << 3) + (y << 1) + x;
    if(board[position] == NOT_PROCESSED_WHITE_CELL) {
        if(y == 0 || y == (BOARD_ROWS - 1) || x == 0 || x == (BOARD_COLUMNS - 1)) {
            board[position] = CONNECTED_WHITE_CELL;
            draw_board_position(x, y, CONNECTED_WHITE_CELL);
            return true;
        } else {
            if(neighbour_connected(position)) {
                board[position] = CONNECTED_WHITE_CELL;
                draw_board_position(x, y, CONNECTED_WHITE_CELL);
                return true;
            } else if(!neighbour_notprocessed(position)) {
                board[position] = NOT_CONNECTED_WHITE_CELL;
                draw_board_position(x, y, NOT_CONNECTED_WHITE_CELL);
                return true;
            }
        }
    } else if(board[position] == NOT_PROCESSED_BLACK_CELL) {
        if(y == 0 || y == (BOARD_ROWS - 1) || x == 0 || x == (BOARD_COLUMNS - 1)) {
            board[position] = CONNECTED_BLACK_CELL;
            draw_board_position(x, y, CONNECTED_BLACK_CELL);
            return true;
        } else {
            if(neighbour_connected(position)) {
                board[position] = CONNECTED_BLACK_CELL;
                draw_board_position(x, y, CONNECTED_BLACK_CELL);
                return true;
            } else if(!neighbour_notprocessed(position)) {
                board[position] = NOT_CONNECTED_BLACK_CELL;
                draw_board_position(x, y, NOT_CONNECTED_BLACK_CELL);
                return true;
            }
        }
    }
    return false;
}

bool neighbour_connected(unsigned char position2check) {
    if((board[position2check - 10] == EMPTY_CELL || board[position2check - 1] == EMPTY_CELL 
            || board[position2check + 1] == EMPTY_CELL || board[position2check + 10] == EMPTY_CELL)) {
        return true;
    }
    if(board[position2check] == NOT_PROCESSED_WHITE_CELL && 
        (board[position2check - 10] == CONNECTED_WHITE_CELL || board[position2check - 1] == CONNECTED_WHITE_CELL 
            || board[position2check + 1] == CONNECTED_WHITE_CELL || board[position2check + 10] == CONNECTED_WHITE_CELL)) {
        return true;
    }
    if(board[position2check] == NOT_PROCESSED_BLACK_CELL && 
        (board[position2check - 10] == CONNECTED_BLACK_CELL || board[position2check - 1] == CONNECTED_BLACK_CELL 
            || board[position2check + 1] == CONNECTED_BLACK_CELL || board[position2check + 10] == CONNECTED_BLACK_CELL)) {
        return true;
    }
    return false;
}
bool neighbour_notprocessed(unsigned char position2check) {
    if(board[position2check] == NOT_PROCESSED_WHITE_CELL && 
        (board[position2check - 10] == NOT_PROCESSED_WHITE_CELL || board[position2check - 1] == NOT_PROCESSED_WHITE_CELL 
            || board[position2check + 1] == NOT_PROCESSED_WHITE_CELL || board[position2check + 10] == NOT_PROCESSED_WHITE_CELL)) {
        return true;
    }
    if(board[position2check] == NOT_PROCESSED_BLACK_CELL && 
        (board[position2check - 10] == NOT_PROCESSED_BLACK_CELL || board[position2check - 1] == NOT_PROCESSED_BLACK_CELL 
            || board[position2check + 1] == NOT_PROCESSED_BLACK_CELL || board[position2check + 10] == NOT_PROCESSED_BLACK_CELL)) {
        return true;
    }
    return false;
}

bool mark_as_disconnected(unsigned char x, unsigned char y, unsigned char position2check) {
    if(board[position2check] == NOT_PROCESSED_WHITE_CELL || board[position2check] == NOT_PROCESSED_BLACK_CELL) {
        board[position2check] = board[position2check] + 1;
        draw_board_position(x, y, board[position2check]);
        return true;
    }
    if(board[position2check] == NOT_CONNECTED_WHITE_CELL || board[position2check] == NOT_CONNECTED_BLACK_CELL) {
        return true;
    }
    return false;
}

unsigned char destroy_disconnected(unsigned char x, unsigned char y, unsigned char position2check) {
    unsigned char numPiecesDestroyed = 0;
    if(board[position2check] == NOT_CONNECTED_WHITE_CELL) {
        board[position2check] = EMPTY_CELL;
        draw_board_position(x, y, EMPTY_CELL);
        numPiecesDestroyed++;
        if((x > 0) && board[position2check-1] != NOT_CONNECTED_WHITE_CELL) {
            board[position2check-1] = EMPTY_CELL;
            draw_board_position(x-1, y, EMPTY_CELL);
            numPiecesDestroyed++;
        }
        if((x < BOARD_COLUMNS - 1) && board[position2check+1] != NOT_CONNECTED_WHITE_CELL) {
            board[position2check+1] = EMPTY_CELL;
            draw_board_position(x+1, y, EMPTY_CELL);
            numPiecesDestroyed++;
        }
        if((y>0) && board[position2check-10] != NOT_CONNECTED_WHITE_CELL) {
            board[position2check-10] = EMPTY_CELL;
            draw_board_position(x, y-1, EMPTY_CELL);
            numPiecesDestroyed++;
        }
        if((y < BOARD_ROWS-1) && board[position2check+10] != NOT_CONNECTED_WHITE_CELL) {
            board[position2check+10] = EMPTY_CELL;
            draw_board_position(x, y+1, EMPTY_CELL);
            numPiecesDestroyed++;
        }
    } else if(board[position2check] == NOT_CONNECTED_BLACK_CELL) {
        board[position2check] = EMPTY_CELL;
        draw_board_position(x, y, EMPTY_CELL);
        numPiecesDestroyed++;
        if((x > 0) && board[position2check-1] != NOT_CONNECTED_BLACK_CELL) {
            board[position2check-1] = EMPTY_CELL;
            draw_board_position(x-1, y, EMPTY_CELL);
            numPiecesDestroyed++;
        }
        if((x < BOARD_COLUMNS - 1) && board[position2check+1] != NOT_CONNECTED_BLACK_CELL) {
            board[position2check+1] = EMPTY_CELL;
            draw_board_position(x+1, y, EMPTY_CELL);
            numPiecesDestroyed++;
        }
        if((y>0) && board[position2check-10] != NOT_CONNECTED_BLACK_CELL) {
            board[position2check-10] = EMPTY_CELL;
            draw_board_position(x, y-1, EMPTY_CELL);
            numPiecesDestroyed++;
        }
        if((y < BOARD_ROWS-1) && board[position2check+10] != NOT_CONNECTED_BLACK_CELL) {
            board[position2check+10] = EMPTY_CELL;
            draw_board_position(x, y+1, EMPTY_CELL);
            numPiecesDestroyed++;
        }
    }
    return numPiecesDestroyed;
}

void block_board_position(unsigned char x, unsigned char y) {
    unsigned char position = (y << 3) + (y << 1) + x;
    board[position] = BLOCKED_CELL;
    draw_board_position(x,y,BLOCKED_CELL);
}
