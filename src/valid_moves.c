#include "valid_moves.h"

#define EMPTY 0
#define TAKEN 1
#define ENEMY 2

// helper for get possible moves
// determine state of a square (row,column) on the board
static int target_state(game_state* game, int src_col, int src_row, int dst_col, int dst_row) 
{
    //access specific square on the board identified by its row and col
    piece_t piece = game->board[src_row][src_col];
    piece_t target = game->board[dst_row][dst_col];
    // is this how to identify empty square ??
    if (PIECE_TYPE(target) == NONE) return EMPTY;
    // target occupied by same color piece 
    if (PIECE_COLOR(target) == PIECE_COLOR(piece)) return TAKEN;
    // other wise enemy
    // maybe can change this to also return piece type
    return ENEMY;
}

int get_valid_moves_pawn(game_state* game, int col, int row, board_pos move_buffer[]) 
{
    piece_t piece = game->board[row][col];
    int moves_found = 0;
    int target_row = (PIECE_COLOR(piece) == PIECE_COLOR_WHITE)? row - 1 : row + 1;
    int result;
    
    // Check side 1 for enemy piece
    if (col - 1 > 0) {
        result = target_state(game, col, row, col - 1, target_row);
        if (result == ENEMY) move_buffer[moves_found++] = (board_pos) {col - 1, target_row};
    }

    // Check side 2 for enemy piece
    if (col + 1 < 8) {
        result = target_state(game, col, row, col + 1, target_row);
        if (result == ENEMY) move_buffer[moves_found++] = (board_pos) {col + 1, target_row};
    }
    
    // Check in front for empty square
    result = target_state(game, col, row, col, target_row);
    if (result == ENEMY) move_buffer[moves_found++] = (board_pos) {col, target_row};

    // SPECIAL MOVES:
    // First move pawn can move 2 squares ahead
    // if white row = 6
    // if black row = 1
    if (PIECE_COLOR(piece) == PIECE_COLOR_WHITE && row == 6 && target_state(game, col, row, col, row - 2) == EMPTY) {
        move_buffer[moves_found++] = (board_pos) {col, row - 2};
    }
    if (PIECE_COLOR(piece) == PIECE_COLOR_WHITE && row == 1 && target_state(game, col, row, col, row + 2) == EMPTY) {
        move_buffer[moves_found++] = (board_pos) {col, row + 2};
    }

    return moves_found;
}

int get_valid_moves_rook(game_state* game, int col, int row, board_pos move_buffer[]) {

}

int get_valid_moves_knight(game_state* game, int col, int row, board_pos move_buffer[]) {

}

int get_valid_moves_bishop(game_state* game, int col, int row, board_pos move_buffer[]) {

}

int get_valid_moves_queen(game_state* game, int col, int row, board_pos move_buffer[]) {

}

int get_valid_moves_king(game_state* game, int col, int row, board_pos move_buffer[]) {

}
