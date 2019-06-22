//
// Created by Jordi Montornes on 07/04/2017.
//

#ifndef GOTRIS_GAMELOGIC_H
#define GOTRIS_GAMELOGIC_H

#define GAME_STATUS_NOACTION 0
#define GAME_STATUS_SQUAREPIECEFALLING 1
#define GAME_STATUS_PIECESFALLING 2
#define GAME_STATUS_CALCULATIONS 3
#define GAME_STATUS_CHECK_CALCULATIONS 4 
#define GAME_STATUS_COMPUTE_DISCONNECTED 5
#define GAME_STATUS_ANIMATE_DISCONNECTED 6
#define GAME_STATUS_DESTROY_DISCONNECTED 7
#define GAME_STATUS_MAKE_PIECES_FALL 8
#define GAME_STATUS_CHECK_PIECES_FALL 9
#define GAME_STATUS_PIECESFALLING_2 10
#define GAME_STATUS_LOOSING_GAME 11
#define GAME_STATUS_GAMEOVER 12
#define GAME_STATUS_RESET 13

void init_game();
void init_gamestatus();
void logo_screen();
void title_screen();
void game_loop();
void execute_game_logic();
void get_control_input();
#endif //GOTRIS_GAMELOGIC_H
