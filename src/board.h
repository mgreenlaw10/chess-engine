#pragma once

#include "piece.h"
#include <stdbool.h>

typedef struct {
    piece_t pieces[8][8];
    unsigned int turn_number;
} Board;

typedef struct {
    int row;
    int col;
} BoardPos;

Board new_board();

BoardPos find_king(Board* board, int color);
bool king_in_check(Board* board, int color);
bool king_in_checkmate(Board* board, int color);
bool king_in_stalemate(Board* board, int color);

bool white_move(Board* board);

typedef enum {
    MOVE_SUCCESS,
    WRONG_TEAM,
    KING_IN_CHECK,
    INVALID_MOVE
} MoveResult;

void move_piece(Board* board, int src_col, int src_row, int dst_col, int dst_row);
MoveResult try_move_piece(Board* board, int src_col, int src_row, int dst_col, int dst_row);


