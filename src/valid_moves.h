#include "gamestate.h"
//
// Store valid moves in move_buffer and
// return the number of valid moves.
//
int get_valid_moves_pawn(game_state* game, int col, int row, board_pos move_buffer[]);
int get_valid_moves_rook(game_state* game, int col, int row, board_pos move_buffer[]);
int get_valid_moves_knight(game_state* game, int col, int row, board_pos move_buffer[]);
int get_valid_moves_bishop(game_state* game, int col, int row, board_pos move_buffer[]);
int get_valid_moves_queen(game_state* game, int col, int row, board_pos move_buffer[]);
int get_valid_moves_king(game_state* game, int col, int row, board_pos move_buffer[]);