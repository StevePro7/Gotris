//
// Created by Jordi Montornes on 04/04/2017.
//

#ifndef GOTRIS_BOARD_H
#define GOTRIS_BOARD_H

#define BOARD_ROWS 22
#define BOARD_COLUMNS 10

#define EMPTY_CELL 0
#define NOT_PROCESSED_WHITE_CELL 1
#define NOT_CONNECTED_WHITE_CELL 2
#define CONNECTED_WHITE_CELL 3
#define NOT_PROCESSED_BLACK_CELL 4
#define NOT_CONNECTED_BLACK_CELL 5
#define CONNECTED_BLACK_CELL 6
#define BLOCKED_CELL 10

#define NULLED_PIECE 0
#define WHITE_PIECE 1
#define BLACK_PIECE 4

#define is_free_board_position_for_square_creation() !((board[current_square.x] != EMPTY_CELL) || (board[current_square.x+1] != EMPTY_CELL) || (board[current_square.x+10] != EMPTY_CELL) || (board[current_square.x+11] != EMPTY_CELL))
#define is_free_board_down_position_for_square(position2check) !((board[position2check+20] != EMPTY_CELL) || (board[position2check+21] != EMPTY_CELL))
#define is_free_board_left_position_for_square(position2check) !((board[position2check-1] != EMPTY_CELL) || (board[position2check+9] != EMPTY_CELL))
#define is_free_board_right_position_for_square(position2check) !((board[position2check+2] != EMPTY_CELL) || (board[position2check+12] != EMPTY_CELL))
#define is_free_board_next_position_for_piece(index) board[(active_pieces[index].y << 3) + (active_pieces[index].y << 1) + active_pieces[index].x+10] == EMPTY_CELL
#define is_free_board_next_position(x,y) (y < BOARD_ROWS-1) && (board[(y << 3) + (y << 1) + x+10] == EMPTY_CELL)
#define is_free_board_position(position2check) (board[position2check] == EMPTY_CELL)


void init_board();
void rotate_square_piece();
void rotate_inv_square_piece();
void delete_individual_pieces_board(unsigned char index);
void delete_square_pieces_board();
void create_individual_pieces_from_square();
void create_individual_pieces_from_board_position(unsigned char x, unsigned char y, unsigned char position);
void put_individual_pieces_board(unsigned char index);
void mark_position_for_change_in_board(unsigned char x, unsigned char y);
void mark_position_for_change_in_board_rec(unsigned char x, unsigned char y, unsigned char color);
void put_square_pieces_board();
bool compute_path(unsigned char x, unsigned char y);
bool neighbour_connected(unsigned char position);
bool neighbour_notprocessed(unsigned char position);
bool mark_as_disconnected(unsigned char x, unsigned char y, unsigned char position);
unsigned char destroy_disconnected(unsigned char x, unsigned char y, unsigned char position);
void block_board_position(unsigned char x, unsigned char y);

#endif //GOTRIS_BOARD_H
