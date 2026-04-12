#include <stdio.h>

#include "board.h"
#include "move.h"

static void initialize_pieces(piece_t pieces[8][8]) {
    // Black on top
    pieces[0][0] = MAKE_PIECE(ROOK, PIECE_COLOR_BLACK);
    pieces[0][1] = MAKE_PIECE(KNIGHT, PIECE_COLOR_BLACK);
    pieces[0][2] = MAKE_PIECE(BISHOP, PIECE_COLOR_BLACK);
    pieces[0][3] = MAKE_PIECE(QUEEN, PIECE_COLOR_BLACK);
    pieces[0][4] = MAKE_PIECE(KING, PIECE_COLOR_BLACK);
    pieces[0][5] = MAKE_PIECE(BISHOP, PIECE_COLOR_BLACK);
    pieces[0][6] = MAKE_PIECE(KNIGHT, PIECE_COLOR_BLACK);
    pieces[0][7] = MAKE_PIECE(ROOK, PIECE_COLOR_BLACK);
    for (int i = 0; i < 8; i++) {
        pieces[1][i] = MAKE_PIECE(PAWN, PIECE_COLOR_BLACK);
    }
    // Fill in empty space
    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            pieces[i][j] = (piece_t)0;
        }
    }
    // White on bottom
    pieces[7][0] = MAKE_PIECE(ROOK, PIECE_COLOR_WHITE);
    pieces[7][1] = MAKE_PIECE(KNIGHT, PIECE_COLOR_WHITE);
    pieces[7][2] = MAKE_PIECE(BISHOP, PIECE_COLOR_WHITE);
    pieces[7][3] = MAKE_PIECE(QUEEN, PIECE_COLOR_WHITE);
    pieces[7][4] = MAKE_PIECE(KING, PIECE_COLOR_WHITE);
    pieces[7][5] = MAKE_PIECE(BISHOP, PIECE_COLOR_WHITE);
    pieces[7][6] = MAKE_PIECE(KNIGHT, PIECE_COLOR_WHITE);
    pieces[7][7] = MAKE_PIECE(ROOK, PIECE_COLOR_WHITE);
    for (int i = 0; i < 8; i++) {
        pieces[6][i] = MAKE_PIECE(PAWN, PIECE_COLOR_WHITE);
    }
}

board_t new_board() {
    board_t board;
    initialize_pieces(board.pieces);
    board.turn_number = 0;
    return board;
}

void move_piece(board_t* board, int src_col, int src_row, int dst_col, int dst_row) 
{
    board->pieces[dst_row][dst_col] = board->pieces[src_row][src_col];
    board->pieces[src_row][src_col] = (piece_t)NONE;
    //
    // Check if pawn should promote after moving.
    //
    if (PIECE_TYPE(board->pieces[dst_row][dst_col]) == PAWN) 
    {
        if (PIECE_COLOR(board->pieces[dst_row][dst_col]) == PIECE_COLOR_WHITE && dst_row == 0) 
        {
            board->pieces[dst_row][dst_col] = MAKE_PIECE(QUEEN, PIECE_COLOR_WHITE);
        }
        else if (PIECE_COLOR(board->pieces[dst_row][dst_col]) == PIECE_COLOR_BLACK && dst_row == 7) 
        {
            board->pieces[dst_row][dst_col] = MAKE_PIECE(QUEEN, PIECE_COLOR_BLACK);
        }
    }

    if (king_in_check(board, PIECE_COLOR_BLACK)) {
        printf("black king in check\n");
    }
}
//
// Determine whether or not the king 
// of the given color is in check.
//
bool king_in_check(board_t* board, int color) 
{
    // Find the position of the king.
    int king_col;
    int king_row;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            if (PIECE_TYPE(board->pieces[i][j]) == KING &&
                PIECE_COLOR(board->pieces[i][j]) == color)
            {
                king_row = i;
                king_col = j;
            }
        }
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            if (PIECE_COLOR(board->pieces[i][j]) != color) {
                // If piece is an enemy, check its valid
                // moves to see if one contains the king.
                move_t moves[32];
                int num_moves = 0;

                get_possible_moves(board, i, j, moves, &num_moves);

                for (int k = 0; k < num_moves; k++) {
                    if (moves[k].dest_row == king_row && moves[k].dest_column == king_col) 
                        return true;
                }
            }
        }
    }
    return false;
}
 
