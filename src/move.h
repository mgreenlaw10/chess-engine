#include "board.h"

typedef struct {
    int row, column; 
    int dest_row, dest_column;
    piece_t piece;
    piece_t capture_piece;
} move_t;

int all_moves_for_piece(board_t *board, int row, int column, move_t moves[]);

void get_possible_moves(board_t *board, int row, int column, move_t moves[]);
void get_possible_moves_pawn(board_t *board, int row, int column, move_t moves[]);
void get_possible_moves_rook(board_t *board, int row, int column, move_t moves[]);
void get_possible_moves_bishop(board_t *board, int row, int column, move_t moves[]);
void get_possible_moves_knight(board_t *board, int row, int column, move_t moves[]);
void get_possible_moves_king(board_t *board, int row, int column, move_t moves[]);
void get_possible_moves_queen(board_t *board, int row, int column, move_t moves[]);