#include "../board.h" // Ensure board.h defines board_t or include the correct file

#define QUEEN_SCORE 10
#define ROOK_SCORE 5
#define BISHOP_SCORE 3
#define KNIGHT_SCORE 3
// pawn score is 1

// What contributes to payoff of a board:
    // 1. Material (value per piece)
    // 2. Mobility (number of legal moves the player has)

int payoff(Board* board);

int compute_material_score(Board* board);
int compute_mobility_score(Board* board);

