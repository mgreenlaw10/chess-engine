#pragma once

#include "board.h"

typedef struct {
    int row, column; 
    int dest_row, dest_column;
    piece_t piece;
    piece_t capture_piece;
} move_t;

int get_possible_moves(Board *board, int row, int column, move_t moves[], int* num_moves);

void get_possible_moves_pawn(Board *board, unsigned char color, int row, int column, move_t moves[], int* num_moves);
void get_possible_moves_rook(Board *board, unsigned char color, int row, int column, move_t moves[], int* num_moves);
void get_possible_moves_bishop(Board *board, unsigned char color, int row, int column, move_t moves[], int* num_moves);
void get_possible_moves_knight(Board *board, unsigned char color, int row, int column, move_t moves[], int* num_moves);
void get_possible_moves_king(Board *board, unsigned char color, int row, int column, move_t moves[], int* num_moves);
void get_possible_moves_queen(Board *board, unsigned char color, int row, int column, move_t moves[], int* num_moves);