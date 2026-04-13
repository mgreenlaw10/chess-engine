#include "board.h"
#include "piece.h"
#include "move.h"

#include <stdio.h>

#define EMPTY 0
#define TAKEN 1
#define ENEMY 2

// helper for get possible moves
// determine state of a square (row,col) on the board
int target_state(Board *board, int row, int col, int color){
    //access specific square on the board identified by its row and col
    piece_t target = board->pieces[row][col];

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
int get_possible_moves(Board *board, int row, int col, move_t moves[], int* num_moves) {

    piece_t piece = board->pieces[row][col];

    int type = PIECE_TYPE(piece);

    if (type == NONE) {
        return 1;
    }
    else if (type == PAWN) {
        get_possible_moves_pawn(board, PIECE_COLOR(piece), row, col, moves, num_moves);
    }
    else if (type == KNIGHT) {
        get_possible_moves_knight(board, PIECE_COLOR(piece), row, col, moves, num_moves);
    }
    else if (type == BISHOP) {
        get_possible_moves_bishop(board, PIECE_COLOR(piece), row, col, moves, num_moves);
    }
    else if (type == ROOK) {
        get_possible_moves_rook(board, PIECE_COLOR(piece), row, col, moves, num_moves);
    }
    else if (type == QUEEN) {
        get_possible_moves_queen(board, PIECE_COLOR(piece), row, col, moves, num_moves);
    }
    else if (type == KING) {
        get_possible_moves_king(board, PIECE_COLOR(piece), row, col, moves, num_moves);
    }

    return 0;
}
//
// Find pawn moves:
// Check each diagonal for an enemy piece,
// and check in front for an empty square.
//
void get_possible_moves_pawn(Board *board, unsigned char color, int row, int col, move_t moves[], int* num_moves) 
{
    int moves_found = 0;
    int target_row = (color == PIECE_COLOR_WHITE)? row - 1 : row + 1;

    // should never be true once promoting is implemented
    if (target_row < 0 || target_row > 7) 
    {
        *num_moves = 0;
        return;
    }

    // check the three squares in front
    int result;
    
    // check side 1 for enemy piece
    if (col - 1 > 0) 
    {
        result = target_state(board, target_row, col - 1, color);
        if (result == ENEMY)
        {
            moves[moves_found++] = (move_t) {
                row,
                col,
                target_row,
                col - 1,
                board->pieces[row][col],
                board->pieces[target_row][col - 1]
            };
        }
    }

    // check side 2 for enemy piece
    if (col + 1 < 8) 
    {
        result = target_state(board, target_row, col + 1, color);
        if (result == ENEMY)
        {
            moves[moves_found++] = (move_t) {
                row,
                col,
                target_row,
                col + 1,
                board->pieces[row][col],
                board->pieces[target_row][col + 1]
            };
        }
    }

    // check in front for empty space
    result = target_state(board, target_row, col, color);
    if (result == EMPTY) {
        moves[moves_found++] = (move_t) {
            row,
            col,
            target_row,
            col,
            board->pieces[row][col],
            board->pieces[target_row][col]
        };
    }

    // SPECIAL MOVES:
    // First move pawn can move 2 squares ahead
        // if white row = 6
        // if black row = 1
    if (color == PIECE_COLOR_WHITE && row == 6 && target_state(board, row - 2, col, color) == EMPTY){
        moves[moves_found++] = (move_t) {
                row,
                col,
                row - 2,
                col,
                board->pieces[row][col],
                board->pieces[row - 2][col]
            };
    }
    if (color == PIECE_COLOR_BLACK && row == 1 && target_state(board, row + 2, col, color) == EMPTY){
        moves[moves_found++] = (move_t) {
                row,
                col,
                row + 2,
                col,
                board->pieces[row][col],
                board->pieces[row + 2][col]
            };
    }
    

    *num_moves = moves_found;
}
//
// Find rook moves:
// Walk each axis until you find the first piece.
//
void get_possible_moves_rook(Board *board, unsigned char color, int row, int col, move_t moves[], int* num_moves) 
{
    int moves_found = 0;

    // move in positive col direction
    for (int i = col + 1; i < 8; i++) 
    {
        int result = target_state(board, row, i, color);
        if (result == TAKEN) break;
        moves[moves_found++] = (move_t) {
            row,
            col,
            row,
            i,
            board->pieces[row][col],
            board->pieces[row][i]
        };
        if (result == ENEMY) break;
    }

    // move in negative col direction
    for (int i = col - 1; i > -1; i--) 
    {
        int result = target_state(board, row, i, color);
        if (result == TAKEN) break;
        moves[moves_found++] = (move_t) {
            row,
            col,
            row,
            i,
            board->pieces[row][col],
            board->pieces[row][i]
        };
        if (result == ENEMY) break;
    }

    // move in positive row direction
    for (int i = row + 1; i < 8; i++) 
    {
        int result = target_state(board, i, col, color);
        if (result == TAKEN) break;
        moves[moves_found++] = (move_t) {
            row,
            col,
            i,
            col,
            board->pieces[row][col],
            board->pieces[i][col]
        };
        if (result == ENEMY) break;
    }

    // move in negative row direction
    for (int i = row - 1; i > -1; i--) 
    {
        int result = target_state(board, i, col, color);
        if (result == TAKEN) break;
        moves[moves_found++] = (move_t) {
            row,
            col,
            i,
            col,
            board->pieces[row][col],
            board->pieces[i][col]
        };
        if (result == ENEMY) break;
    }

    *num_moves = moves_found;
}
//
// Find bishop moves:
// Walk each diagonal until you find the first piece.
//
void get_possible_moves_bishop(Board *board, unsigned char color, int row, int col, move_t moves[], int* num_moves) 
{
    int moves_found = 0;
    int distance;
    
    // move right-down
    distance = (8-col) < (8-row)? 
               (8-col) : (8-row);

    for (int i = 1; i <= distance; i++) 
    {
        int target_row = row + i;
        int target_col = col + i;

        int result = target_state(board, target_row, target_col, color);

        if (result == TAKEN) break;
        moves[moves_found++] = (move_t) {
            row,
            col,
            target_row,
            target_col,
            board->pieces[row][col],
            board->pieces[target_row][target_col]
        };
        if (result == ENEMY) break;
    }

    // move right-up
    distance = (8-col) < (row)? 
               (8-col) : (row);

    for (int i = 1; i <= distance; i++) 
    {
        int target_row = row - i;
        int target_col = col + i;

        int result = target_state(board, target_row, target_col, color);

        if (result == TAKEN) break;
        moves[moves_found++] = (move_t) {
            row,
            col,
            target_row,
            target_col,
            board->pieces[row][col],
            board->pieces[target_row][target_col]
        };
        if (result == ENEMY) break;
    }

    // move left-down
    distance = (col) < (8-row)? 
               (col) : (8-row);

    for (int i = 1; i <= distance; i++) 
    {
        int target_row = row + i;
        int target_col = col - i;

        int result = target_state(board, target_row, target_col, color);

        if (result == TAKEN) break;
        moves[moves_found++] = (move_t) {
            row,
            col,
            target_row,
            target_col,
            board->pieces[row][col],
            board->pieces[target_row][target_col]
        };
        if (result == ENEMY) break;
    }

    // move left-up
    distance = (col) < (row)? 
               (col) : (row);

    for (int i = 1; i <= distance; i++) 
    {
        int target_row = row - i;
        int target_col = col - i;

        int result = target_state(board, target_row, target_col, color);

        if (result == TAKEN) break;
        moves[moves_found++] = (move_t) {
            row,
            col,
            target_row,
            target_col,
            board->pieces[row][col],
            board->pieces[target_row][target_col]
        };
        if (result == ENEMY) break;
    }

    *num_moves = moves_found;
}
//
// Find queen moves:
// Combine rook moves and bishop moves.
//
void get_possible_moves_queen(Board *board, unsigned char color, int row, int col, move_t moves[], int* num_moves)
{
    int found_rook_moves = 0;
    int found_bishop_moves = 0;

    get_possible_moves_rook(board, color, row, col, moves, &found_rook_moves);
    get_possible_moves_bishop(board, color, row, col, moves + found_rook_moves, &found_bishop_moves);

    *num_moves = found_rook_moves + found_bishop_moves;
}
//
// Use constant offsets for finding squares targeted
// by a knight because it's easier.
//
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
//
// Find knight moves:
// Check that each square from each offset is open or has an enemy piece.
//
void get_possible_moves_knight(Board *board, unsigned char color, int row, int col, move_t moves[], int* num_moves) 
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
//
// Use constant offsets for finding squares targeted
// by a knight because it's easier.
//
static int king_move_offsets[8][2] = {
    {-1, -1},
    {-1,  0},
    {-1,  1},
    { 0, -1},
    { 0,  1},
    { 1, -1},
    { 1,  0},
    { 1,  1}
};
//
// Find king moves:
// Check that each square from each offset is open or has an enemy piece.
//
// *Need to remove moves that would result in self-check.
//
void get_possible_moves_king(Board *board, unsigned char color, int row, int col, move_t moves[], int* num_moves) 
{
    int moves_found = 0;
    piece_t piece = board->pieces[row][col];

    for (int i = 0; i < 8; i++) 
    {
        int target_col = col + king_move_offsets[i][0];
        int target_row = row + king_move_offsets[i][1];

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
    // Castling

    // white
    if (color == PIECE_COLOR_WHITE && row == 7 && col == 4) {
        piece_t castle = board->pieces[7][7];
        if (PIECE_TYPE(castle) == ROOK && PIECE_COLOR(castle) == PIECE_COLOR_WHITE
            && target_state(board, 7, 5, color) == EMPTY
            && target_state(board, 7, 6, color) == EMPTY) {

            moves[moves_found++] = (move_t) {
                row,
                col,
                7,
                6,
                piece,
                board->pieces[7][6]
            };
        }
        piece_t far_castle = board->pieces[7][0];
        if (PIECE_TYPE(far_castle) == ROOK && PIECE_COLOR(far_castle) == PIECE_COLOR_WHITE
            && target_state(board, 7, 1, color) == EMPTY
            && target_state(board, 7, 2, color) == EMPTY
            && target_state(board, 7, 3, color) == EMPTY) {

            moves[moves_found++] = (move_t) {
                row,
                col,
                7,
                2,
                piece,
                board->pieces[7][2]
            };
        }
    // black
    } else if (color == PIECE_COLOR_BLACK && row == 0 && col == 4) {

        piece_t castle = board->pieces[0][7];
        if (PIECE_TYPE(castle) == ROOK && PIECE_COLOR(castle) == PIECE_COLOR_BLACK
            && target_state(board, 0, 5, color) == EMPTY
            && target_state(board, 0, 6, color) == EMPTY) {
            moves[moves_found++] = (move_t) {
                row,
                col,
                0,
                6,
                piece,
                board->pieces[0][6]
            };
        }
        piece_t far_castle = board->pieces[0][0];
        if (PIECE_TYPE(far_castle) == ROOK && PIECE_COLOR(far_castle) == PIECE_COLOR_BLACK
            && target_state(board, 0, 1, color) == EMPTY
            && target_state(board, 0, 2, color) == EMPTY
            && target_state(board, 0, 3, color) == EMPTY) {

            moves[moves_found++] = (move_t) {
                row,
                col,
                0,
                2,
                piece,
                board->pieces[0][2]
            };
        }
    }
    *num_moves = moves_found;
}