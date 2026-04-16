#include "payoff.h"

// Compute Payoff

int payoff(Board* board, int color){

    return compute_material_score(board) + compute_mobility_score(board);
}

// Components of Payoff

int compute_material_score(Board* board){
    
    // int material = QUEEN_SCORE  * (wQ - bQ) +
    //                ROOK_SCORE   * (wR - bR) +
    //                BISHOP_SCORE * (wB - bB) +
    //                KNIGHT_SCORE * (wK - bK) +
    //                1            * (wP - bP);
    return 0;
}

int compute_mobility_score(Board* board){
   
    return 0;
}