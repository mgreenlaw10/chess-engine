#pragma once

#include "../board.h"

// Returns the score of the best possible outcome for the color
// searching to the given depth
int alpha_beta(Board* board, int depth, int Alpha, int Beta, PieceColor color);

// Returns the best move for whoever's turn it is
// search to the given depth
Move best_move(Board* board, int depth);
