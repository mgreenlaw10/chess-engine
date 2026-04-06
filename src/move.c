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
    if (PIECE_COLOR(target) == NONE){
        return EMPTY;
    }
    // target occupied by same color piece 
    if (PIECE_COLOR(target) == color) {
        return TAKEN;
    }
    // other wise enemy
    // maybe can change this to also return piece type
    //return ENEMY;
    return PIECE_TYPE(target);
}

// i want to change the parameters for get possible moves
// gonna return an array with all of the moves
int all_moves_for_piece(board_t *board, int row, int column, move_t moves[]){

    piece_t piece = board->pieces[row][column];

    // can only do this for the squares with pieces
    if (target_state(board,row,column,PIECE_COLOR(piece)) != TAKEN){
        return 1;
    }

    int type = PIECE_TYPE(piece);

    if (type == PAWN) {
        get_possible_moves_pawn(board, row, column, moves);
    }
    else if (type == KNIGHT) {
        get_possible_moves_knight(board, row, column, moves);
    }
    else if (type == BISHOP) {
        get_possible_moves_bishop(board, row, column, moves);
    }
    else if (type == ROOK) {
        get_possible_moves_rook(board, row, column, moves);
    }
    else if (type == QUEEN) {
        get_possible_moves_queen(board, row, column, moves);
    }
    else if (type == KING) {
        get_possible_moves_king(board, row, column, moves);
    }

    return 0;

}

void get_possible_moves_pawn(board_t *board, int row, int column, move_t moves[]) {

}

void get_possible_moves_rook(board_t *board, int row, int column, move_t moves[]) {

}

void get_possible_moves_bishop(board_t *board, int row, int column, move_t moves[]) {

}

void get_possible_moves_knight(board_t *board, int row, int column, move_t moves[]) {

}

void get_possible_moves_king(board_t *board, int row, int column, move_t moves[]) {

}

void get_possible_moves_queen(board_t *board, int row, int column, move_t moves[]) {

}
