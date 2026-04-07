#pragma once

#include "piece.h"

typedef struct {
    piece_t pieces[8][8];
    unsigned int turn_number;
} board_t;

board_t new_board();

void move_piece(board_t* board, int src_col, int src_row, int dst_col, int dst_row);