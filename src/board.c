#include <stdio.h>

#include "board.h"

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

 
