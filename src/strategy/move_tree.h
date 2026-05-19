#pragma once

#include "../board.h"

// pair of move and payoff
typedef struct {
    Move move;
    float score;
} MoveScore;

// Returns the score of the best possible outcome for the color
// searching to the given depth
int alpha_beta(Board* board, int depth, int Alpha, int Beta, PieceColor color);

// Returns the best move for whoever's turn it is
// search to the given depth
Move best_move(Board* board, int depth);

// Returns all legal moves for the current player with their payoff scores
// score is normalized to [0, 1] where 1 = best possible for white, 0 = best for black
int get_score(Board* board, Move moves[], int num_moves, MoveScore scores[]);
