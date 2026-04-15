#pragma once

#include "piece.h"
#include <stdbool.h>

typedef struct {
    piece_t pieces[8][8];

    unsigned int turn_number;
    PieceColor team_to_move;
    // The team in check is necessarily the team to move,
    // so this tells you whether team_to_move is in check or not.
    bool team_in_check;

    unsigned char num_white_pawns;
    unsigned char num_black_pawns;
    unsigned char num_white_knights;
    unsigned char num_black_knights;
    unsigned char num_white_bishops;
    unsigned char num_black_bishops;
    unsigned char num_white_rooks;
    unsigned char num_black_rooks;
    unsigned char num_white_queens;
    unsigned char num_black_queens;
} Board;

typedef struct {
    int row;
    int col;
} BoardPos;

Board new_board();

BoardPos find_king(Board* board, PieceColor color);
bool king_in_check(Board* board, PieceColor color);
bool king_in_checkmate(Board* board, PieceColor color);
bool king_in_stalemate(Board* board, PieceColor color);

typedef enum {
    MOVE_SUCCESS,
    WRONG_TEAM,
    KING_IN_CHECK,
    INVALID_MOVE
} MoveResult;

void move_piece(Board* board, int src_col, int src_row, int dst_col, int dst_row);
MoveResult try_move_piece(Board* board, int src_col, int src_row, int dst_col, int dst_row);

void print_piece_count(Board* board);


