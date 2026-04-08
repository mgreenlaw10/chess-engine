#pragma once

#include "piece.h"

#include <stdbool.h>

typedef struct {
    piece_t pieces[8][8];
    unsigned int turn_number;
} board_t;

board_t new_board();

bool king_in_check(board_t* board, int color);
void move_piece(board_t* board, int src_col, int src_row, int dst_col, int dst_row);

