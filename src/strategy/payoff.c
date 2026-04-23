#include "payoff.h"

// Compute Payoff

int payoff(Board* board){

    return compute_material_score(board) + compute_mobility_score(board);
}

// Components of Payoff
    // if material is POSITIVE: score(W) > score(B)

int compute_material_score(Board* board){

    int wQ = board->num_white_queens;
    int bQ = board->num_black_queens;
    int wR = board->num_white_rooks;
    int bR = board->num_black_rooks;
    int wB = board->num_white_bishops;
    int bB = board->num_black_bishops;
    int wK = board->num_white_knights;
    int bK = board->num_black_knights;
    int wP = board->num_white_pawns;
    int bP = board->num_black_pawns;

    int material = QUEEN_SCORE  * (wQ- bQ) +
                   ROOK_SCORE   * (wR - bR) +
                   BISHOP_SCORE * (wB - bB) +
                   KNIGHT_SCORE * (wK - bK) +
                   1            * (wP - bP);
    return material;
}

int compute_mobility_score(Board* board){
   
    return 0;
}


