#pragma once

#include "piece.h"
#include <stdbool.h>

typedef struct {
    piece_t board[8][8];
    bool white_king_in_check;
    bool black_king_in_check;
} game_state;

typedef struct {
    int row;
    int col;
} board_pos;

typedef enum {
    MOVE_SUCCESS,
    MOVE_INVALID,
    KING_IN_CHECK
} move_result;
//
// Loads all valid moves for the piece at (col, row) into
// move_buffer and returns the number of moves.
//
int get_valid_moves(game_state* game, int col, int row, board_pos move_buffer[]);
//
// Determines whether any king is in check and
// updates the check flags in game.
//
void find_checks(game_state* game);
//
// Tries to move a piece and returns a status flag
// with infomation about the result because this
// can fail if the move is invalid or puts the
// friendly king in check.
//
move_result try_move_piece(game_state* game, int src_col, int src_row, int dst_col, int dst_row);