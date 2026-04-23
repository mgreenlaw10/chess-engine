#include "../board.h"
#include "payoff.h"

// get all the moves

static int collect_all_moves(Board *board, PieceColor color, Move moves[])
{
    int total = 0;

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {

            piece_t piece = board->pieces[row][col];
    
            Move piece_moves[32];
            int found = get_possible_moves(board, row, col, piece_moves);

            for (int i = 0; i < found; i++) {
                moves[total++] = piece_moves[i];
            }
        }
    }
    return total;
}

// check for checkmate or stalemate for the peice thats about to move

static int is_game_over(Board *board)
{
    PieceColor to_move = board->team_to_move;
    return (king_in_checkmate(board, to_move) || king_in_stalemate(board, to_move));
}


//terminal_score
 
//Returns the appropriate score when the game is over
//Checkmate is a large penalty for losing side
//Stalemate is 0 for both sides

static int terminal_score(Board *board)
{
    PieceColor to_move = board->team_to_move;

    // want to make this a very large penalty for comparisons
    if (king_in_checkmate(board, to_move)) {
        return (to_move == PIECE_COLOR_WHITE) ? -100000 : 100000;
    }

    // stalemate = 0
    return 0;
}

// Search all possible moves with Alpha Beta
    // Let white be MAX player and black be MIN player
    // Alpha = best possible white payoff
    // Beta = best possible black payoff

int alpha_beta (Board* board, int depth, int Alpha, int Beta, int is_max){

    Move moves[256];
    
    // get total moves
    int total_moves = collect_all_moves(board, board->team_to_move, moves);

    // first check if game over
    if (is_game_over(board)) return terminal_score(board);
   

    for (int i = 0; i < total_moves; i++) {

    }      
}
    

