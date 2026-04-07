#include "board.h"
#include "piece.h"
#include "move.h"

#include <stdio.h>

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

void get_possible_moves_rook(board_t *board, unsigned char color, int row, int column, move_t moves[], int* num_moves) 
{
    int moves_found = 0;
    // move in positive col direction
    for (int i = column + 1; i < 8; i++) 
    {
        int result = target_state(board, row, i, color);

        if (result == ENEMY) 
        {
            moves[moves_found++] = (move_t) {
                row,
                column,
                row,
                i,
                board->pieces[row][column],
                board->pieces[row][i]
            };
            break;
        }
        else if (result == TAKEN)
        {
            break;
        }
        else {
            moves[moves_found++] = (move_t) {
                row,
                column,
                row,
                i,
                board->pieces[row][column],
                board->pieces[row][i]
            };
        }
    }
    // move in negative col direction
    for (int i = column - 1; i > -1; i--) 
    {
        int result = target_state(board, row, i, color);

        if (result == ENEMY) 
        {
            moves[moves_found++] = (move_t) {
                row,
                column,
                row,
                i,
                board->pieces[row][column],
                board->pieces[row][i]
            };
            break;
        }
        else if (result == TAKEN)
        {
            break;
        }
        else {
            moves[moves_found++] = (move_t) {
                row,
                column,
                row,
                i,
                board->pieces[row][column],
                board->pieces[row][i]
            };
        }
    }
    // move in positive row direction
    for (int i = row + 1; i < 8; i++) 
    {
        int result = target_state(board, i, column, color);

        if (result == ENEMY) 
        {
            moves[moves_found++] = (move_t) {
                row,
                column,
                i,
                column,
                board->pieces[row][column],
                board->pieces[i][column]
            };
            break;
        }
        else if (result == TAKEN)
        {
            break;
        }
        else {
            moves[moves_found++] = (move_t) {
                row,
                column,
                i,
                column,
                board->pieces[row][column],
                board->pieces[i][column]
            };
        }
    }
    // move in negative row direction
    for (int i = row - 1; i > -1; i--) 
    {
        int result = target_state(board, i, column, color);

        if (result == ENEMY) 
        {
            moves[moves_found++] = (move_t) {
                row,
                column,
                i,
                column,
                board->pieces[row][column],
                board->pieces[i][column]
            };
            break;
        }
        else if (result == TAKEN)
        {
            break;
        }
        else {
            moves[moves_found++] = (move_t) {
                row,
                column,
                i,
                column,
                board->pieces[row][column],
                board->pieces[i][column]
            };
        }
    }

    *num_moves = moves_found;
}

void get_possible_moves_bishop(board_t *board, unsigned char color, int row, int column, move_t moves[], int* num_moves) 
{
    int moves_found = 0;
    int distance;

    distance = (7-column) < (7-row)? 
               (7-column) : (7-row);

    for (int i = 1; i < distance; i++) 
    {
        int target_row = row + i;
        int target_col = column + i;

        int result = target_state(board, target_row, target_col, color);

        if (result == ENEMY) 
        {
            moves[moves_found++] = (move_t) {
                row,
                column,
                target_row,
                target_col,
                board->pieces[row][column],
                board->pieces[target_row][target_col]
            };
            break;
        }
        else if (result == TAKEN)
        {
            break;
        }
        else {
            moves[moves_found++] = (move_t) {
                row,
                column,
                target_row,
                target_col,
                board->pieces[row][column],
                board->pieces[target_row][target_col]
            };
        }
    }

    *num_moves = moves_found;
}

static int knight_move_offsets[8][2] = {
    {-2, -1},
    {-2,  1},
    {-1, -2},
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
