#include "board.h"
#include "piece.h"
#include "move.h"

#define EMPTY 0
#define TAKEN 1
#define ENEMY 2

// helper for get possible moves
// determine state of a square (row,column) on the board
int target_state(board_t *board, int row, int column, int color){
    //access specific square on the board identified by its row and col
    piece_t target = board->pieces[row][column];

    // is this how to identify empty square ??
    if (PIECE_TYPE(target) == NONE) {
        return EMPTY;
    }
    // target occupied by same color piece 
    if (PIECE_COLOR(target) == color) {
        return TAKEN;
    }
    // other wise enemy
    // maybe can change this to also return piece type
    return ENEMY;
}

// i want to change the parameters for get possible moves
// gonna return an array with all of the moves
int all_moves_for_piece(board_t *board, int row, int column, move_t moves[], int* num_moves) {

    piece_t piece = board->pieces[row][column];

    int type = PIECE_TYPE(piece);

    if (type == NONE) {
        return 1;
    }
    else if (type == PAWN) {
        get_possible_moves_pawn(board, PIECE_COLOR(piece), row, column, moves, num_moves);
    }
    else if (type == KNIGHT) {
        get_possible_moves_knight(board, PIECE_COLOR(piece), row, column, moves, num_moves);
    }
    else if (type == BISHOP) {
        get_possible_moves_bishop(board, PIECE_COLOR(piece), row, column, moves, num_moves);
    }
    else if (type == ROOK) {
        get_possible_moves_rook(board, PIECE_COLOR(piece), row, column, moves, num_moves);
    }
    else if (type == QUEEN) {
        get_possible_moves_queen(board, PIECE_COLOR(piece), row, column, moves, num_moves);
    }
    else if (type == KING) {
        get_possible_moves_king(board, PIECE_COLOR(piece), row, column, moves, num_moves);
    }

    return 0;
}

void get_possible_moves_pawn(board_t *board, unsigned char color, int row, int column, move_t moves[], int* num_moves) {

}

void get_possible_moves_rook(board_t *board, unsigned char color, int row, int column, move_t moves[], int* num_moves) {

}

void get_possible_moves_bishop(board_t *board, unsigned char color, int row, int column, move_t moves[], int* num_moves) {

}

static int knight_move_offsets[8][2] = {
    {-2, -1},
    {-2,  1},
    {-1. -2},
    {-1,  2},
    { 1, -2},
    { 1,  2},
    { 2, -1},
    { 2,  1}
};

void get_possible_moves_knight(board_t *board, unsigned char color, int row, int col, move_t moves[], int* num_moves) 
{
    int moves_found = 0;
    piece_t piece = board->pieces[row][col];

    for (int i = 0; i < 8; i++) 
    {
        int target_col = col + knight_move_offsets[i][0];
        int target_row = row + knight_move_offsets[i][1];

        if (target_col < 0 || target_col > 7 || target_row < 0 || target_row > 7) 
        {
            continue;
        }

        int result = target_state(board, target_row, target_col, color);

        if (result == EMPTY || result == ENEMY) 
        {
            moves[moves_found++] = (move_t) {
                row,
                col,
                target_row,
                target_col,
                piece,
                board->pieces[target_row][target_col]
            };
        }
    }
    *num_moves = moves_found;
}

void get_possible_moves_king(board_t *board, unsigned char color, int row, int column, move_t moves[], int* num_moves) {

}

void get_possible_moves_queen(board_t *board, unsigned char color, int row, int column, move_t moves[], int* num_moves) {

}
