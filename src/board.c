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
    piece_t captured = board->pieces[dst_row][dst_col];

    board->pieces[dst_row][dst_col] = board->pieces[src_row][src_col];
    board->pieces[src_row][src_col] = (piece_t)NONE;

    int color = PIECE_COLOR(board->pieces[dst_row][dst_col]);
    int type = PIECE_TYPE(board->pieces[dst_row][dst_col]);
    
    // Castling
    
    // King
    if (type == KING && src_row == dst_row
        && (src_row == 7 || src_row == 0) && src_col == 4 && dst_col == 6) {

        board->pieces[src_row][5] = board->pieces[src_row][7];
        board->pieces[src_row][7] = (piece_t)NONE;
        
    }
    
    // Queen
    if (type == KING && src_row == dst_row
        && (src_row == 7 || src_row == 0) && src_col == 4 && dst_col == 2) {
    
        board->pieces[src_row][3] = board->pieces[src_row][0];
        board->pieces[src_row][0] = (piece_t)NONE;
    }
    if (type == ROOK && src_row == dst_row
        && (src_row == 7 || src_row == 0) && PIECE_TYPE(captured) == NONE) {

        piece_t king = board->pieces[src_row][4];
        
        if (PIECE_TYPE(king) == KING && PIECE_COLOR(king) == color) {

            if (src_col == 7 && dst_col == 5 && PIECE_TYPE(board->pieces[src_row][6]) == NONE) {
                board->pieces[src_row][6] = king;
                board->pieces[src_row][4] = (piece_t)NONE;

            } else if (src_col == 0 && dst_col == 3 && PIECE_TYPE(board->pieces[src_row][2]) == NONE) {
                board->pieces[src_row][2] = king;
                board->pieces[src_row][4] = (piece_t)NONE;
            }
        }
    }
    
    // Check if pawn should promote after moving.
    
    if (type == PAWN) 
    {
        if (color == PIECE_COLOR_WHITE && dst_row == 0) 
        {
            board->pieces[dst_row][dst_col] = MAKE_PIECE(QUEEN, PIECE_COLOR_WHITE);
        }
        else if (color == PIECE_COLOR_BLACK && dst_row == 7) 
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

bool white_move(board_t* board) {
    return board->turn_number % 2 != 0;
}

static bool simulate_for_check(board_t board, int src_col, int src_row, int dst_col, int dst_row) {
    move_piece(&board, src_col, src_row, dst_col, dst_row);
    return king_in_check(&board, PIECE_COLOR(board.pieces[dst_row][dst_col]));
}

MoveResult try_move_piece(board_t* board, int src_col, int src_row, int dst_col, int dst_row) {
    //
    // If the wrong color is selected...
    //
    if (PIECE_COLOR(board->pieces[src_row][src_col]) == PIECE_COLOR_WHITE) {
        if (!white_move(board)) return WRONG_TEAM;
    }
    else if (white_move(board)) return WRONG_TEAM;
    //
    // If a king is in check, skip unless 
    // the selected piece is that king.
    //
    // Pass by value to copy
    //
    if (simulate_for_check(*board, src_col, src_row, dst_col, dst_row)) {
        return KING_IN_CHECK;
    }

    move_t moves[32];
    int num_moves = 0;

    get_possible_moves (
        board, 
        src_row, 
        src_col, 
        moves, 
        &num_moves
    );
    //
    // Check the destination against
    // all valid moves.
    //
    for (int i = 0; i < num_moves; i++) 
    {
        if (moves[i].dest_column == dst_col 
            && moves[i].dest_row == dst_row) 
        {
            move_piece(board, src_col, src_row, dst_col, dst_row);
            board->turn_number++;
            return MOVE_SUCCESS;
        }
    }
    //
    // If no valid move matched
    // the destination, return false.
    //
    return INVALID_MOVE;
}
 
