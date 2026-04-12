#include "gamestate.h"
#include "valid_moves.h"

int get_valid_moves(game_state* game, int col, int row, board_pos move_buffer[]) 
{
    piece_t piece = game->board[row][col];

    switch (PIECE_TYPE(piece)) 
    {
        case PAWN: return get_valid_moves_pawn(game, col, row, move_buffer);
    }
}

void find_checks(game_state* game)
{
    board_pos move_buffer[32];
    board_pos white_king_pos;
    board_pos black_king_pos;
    //
    // Find kings on board.
    //
    for (int i = 0; i < 8; i++) 
    {
        for (int j = 0; j < 8; j++) 
        {
            if (PIECE_TYPE(game->board[i][j]) == KING) 
            {
                switch (PIECE_COLOR(game->board[i][j])) 
                {
                    case PIECE_COLOR_WHITE:
                        white_king_pos.row = i;
                        white_king_pos.col = j;
                        break;
                        
                    case PIECE_COLOR_BLACK:
                        black_king_pos.row = i;
                        black_king_pos.col = j;
                        break;
                }
            }
        }
    }
    //
    // If any piece can take a king
    // as a valid move, it is in check.
    //
    for (int i = 0; i < 8; i++) 
    {
        for (int j = 0; j < 8; j++) 
        {
            for (int k = 0; k < get_valid_moves(game, j, i, move_buffer); k++) 
            {
                if (move_buffer[k].row == white_king_pos.row &&
                    move_buffer[k].col == white_king_pos.col) 
                {
                    game->white_king_in_check = true;
                }
                if (move_buffer[k].row == black_king_pos.row &&
                    move_buffer[k].col == black_king_pos.col) 
                {
                    game->black_king_in_check = true;
                }
            }
        }
    }
}

static void try_pawn_promotion(game_state* game, int col, int row)
{
    piece_t piece = game->board[row][col];

    if (PIECE_TYPE(piece) == PAWN) 
    {
        switch PIECE_COLOR(piece) 
        {
            case PIECE_COLOR_WHITE:
                if (row == 0) 
                {
                    game->board[row][col] = MAKE_PIECE(QUEEN, PIECE_COLOR_WHITE);
                }
                break;

            case PIECE_COLOR_BLACK:
                if (row == 7) 
                {
                    game->board[row][col] = MAKE_PIECE(QUEEN, PIECE_COLOR_BLACK);
                }
                break;
        }
    }
}

move_result try_move_piece(game_state* game, int src_col, int src_row, int dst_col, int dst_row) 
{
    piece_t piece = game->board[src_row][src_col];

    game->board[dst_row][dst_col] = piece;
    game->board[src_row][src_col] = (piece_t)NONE;

    try_pawn_promotion(game, dst_col, dst_row);
    
    return MOVE_SUCCESS;
}