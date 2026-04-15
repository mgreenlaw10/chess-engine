#pragma once

#include "board.h"

typedef struct {
    int row;
    int col; 
    int dst_row;
    int dst_col;
    piece_t piece;
    piece_t capture_piece;
} Move;

int get_possible_moves(Board *board, int row, int col, Move moves[]);

int get_possible_moves_pawn(Board *board, PieceColor color, int row, int col, Move moves[]);
int get_possible_moves_rook(Board *board, PieceColor color, int row, int col, Move moves[]);
int get_possible_moves_bishop(Board *board, PieceColor color, int row, int col, Move moves[]);
int get_possible_moves_knight(Board *board, PieceColor color, int row, int col, Move moves[]);
int get_possible_moves_king(Board *board, PieceColor color, int row, int col, Move moves[]);
int get_possible_moves_queen(Board *board, PieceColor color, int row, int col, Move moves[]);