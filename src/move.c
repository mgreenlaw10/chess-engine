#include "board.h"
#include "piece.h"

#define EMPTY 0
#define TAKEN 1
#define ENEMY 2

// helper for get possible moves
// determine state of a square (row,column) on the board
int target_state(board_t *board, int row, int column, int color){
    //access specific square on the board identified by its row and col
    piece_t target = board->pieces[row][column];

    // not sure how to identify empty square 
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

