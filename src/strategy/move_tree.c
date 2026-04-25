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
    // alpha and beta are guarentees that have already been found in tree

int alpha_beta (Board* board, int depth, int Alpha, int Beta, PieceColor color){

    Move moves[256];
    
    // get total moves
    int total_moves = collect_all_moves(board, board->team_to_move, moves);

    // first check if game over
    if (is_game_over(board)) return terminal_score(board);
    if (depth == 0) return payoff(board);
   
    // WHITES turn
    if (color == PIECE_COLOR_WHITE) {
        int best = -100000; //start with something super low
        for (int i = 0; i < total_moves; i++) {

            // make a copy of the board (remove this if we have an undo)
            Board copy = *board;
            move_piece(&copy, moves[i].col, moves[i].row, moves[i].dst_col, moves[i].dst_row);

            // next depth recursive call - black turn
            int score = alpha_beta(&copy, depth - 1, Alpha, Beta, PIECE_COLOR_BLACK);
            // if max score then update best
            if (score > best) best = score;

            // pruning - compare guarentees 
                // white found better guarentee
            if (best > Alpha) Alpha = best;
                // black has a better move so white will never play this, skip the rest
            if (Alpha >= Beta) break;
        }
        return best;

    // BLACKS turn (minimizing)
    } else {
        int best = 100000;
        for (int i = 0; i < total_moves; i++) {
            // make a copy of the board (remove this if we have an undo)
            Board copy = *board;
            move_piece(&copy, moves[i].col, moves[i].row, moves[i].dst_col, moves[i].dst_row);
            // next depth recursive call
            int score = alpha_beta(&copy, depth - 1, Alpha, Beta, PIECE_COLOR_WHITE);

            if (score < best) best = score;
            // black found a better guarantee, update beta
            if (best < Beta) Beta = best;
            // white already has something better already, black will never get here
            if (Alpha >= Beta) break;
        }
        return best;
    }
}

// Returns the best move for whoever's turn it is
// calls alpha_beta on each possible move and tracks which one had the best score
Move best_move(Board* board, int depth) {
    // get all legal moves for current player
    Move moves[256];
    int total_moves = collect_all_moves(board, board->team_to_move, moves);

    // start with first move as default
    //set worst possible score so first real score always wins
    Move best = moves[0];
    int best_score = (board->team_to_move == PIECE_COLOR_WHITE) ? -100000 : 100000;

    for (int i = 0; i < total_moves; i++) {
        // make a copy of the board (remove this if we have an undo)
        Board copy = *board;
        move_piece(&copy, moves[i].col, moves[i].row, moves[i].dst_col, moves[i].dst_row);

        // after our move, call alpha beta for the opponent
        PieceColor opponent = (board->team_to_move == PIECE_COLOR_WHITE) ? PIECE_COLOR_BLACK : PIECE_COLOR_WHITE;
        int score = alpha_beta(&copy, depth - 1, -100000, 100000, opponent);

        // higher payoff  = better for white, lower = better for black
        if (board->team_to_move == PIECE_COLOR_WHITE && score > best_score) {
            best_score = score;
            best = moves[i];
        } else if (board->team_to_move == PIECE_COLOR_BLACK && score < best_score) {
            best_score = score;
            best = moves[i];
        }
    }
    // return the move that led to best score
    return best;
}
