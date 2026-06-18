#include "../board.h" // Ensure board.h defines board_t or include the correct file

#define QUEEN_SCORE 100
#define ROOK_SCORE 50
#define BISHOP_SCORE 30
#define KNIGHT_SCORE 30
#define PAWN_SCORE 10

const int PIECE_SCORES[6] = {
    10, 30, 33, 50, 90, 10000
};

// max material = queen + 2 rooks + 2 bishops + 2 knights + 8 pawns
#define MAX_PAYOFF (QUEEN_SCORE + 2*ROOK_SCORE + 2*BISHOP_SCORE + 2*KNIGHT_SCORE + 8*PAWN_SCORE)
#define MIN_PAYOFF (-MAX_PAYOFF)

// What contributes to payoff of a board:
    // 1. Material (value per piece)
    // *not done* 2. Mobility (number of legal moves the player has)

int payoff(Board* board);

int compute_material_score(Board* board);
int compute_mobility_score(Board* board);

