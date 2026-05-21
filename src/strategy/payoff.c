#include "payoff.h"
#include "pst.h"

// Compute Payoff

int payoff(Board* board){

    return compute_material_score(board) + compute_mobility_score(board);
}

// Components of Payoff
    // if material is POSITIVE: score(W) > score(B)

int compute_material_score(Board* board)
{
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
                   PAWN_SCORE   * (wP - bP);

    return material;
}

int compute_mobility_score(Board* board)
{
    int score = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            piece_t piece = board->pieces[j][i];
            switch (PIECE_TYPE(piece))
            {
                case PAWN:
                    score += PIECE_COLOR(piece) == PIECE_COLOR_WHITE? PAWN_PST[j][i] : -PAWN_PST[7 - j][i]; break;
                case KNIGHT:
                    score += PIECE_COLOR(piece) == PIECE_COLOR_WHITE? KNIGHT_PST[j][i] : -KNIGHT_PST[7 - j][i]; break;
                case ROOK:
                    score += PIECE_COLOR(piece) == PIECE_COLOR_WHITE? ROOK_PST[j][i] : -ROOK_PST[7 - j][i]; break;
                case BISHOP:
                    score += PIECE_COLOR(piece) == PIECE_COLOR_WHITE? BISHOP_PST[j][i] : -BISHOP_PST[7 - j][i]; break;
                case QUEEN:
                    score += PIECE_COLOR(piece) == PIECE_COLOR_WHITE? QUEEN_PST[j][i] : -QUEEN_PST[7 - j][i]; break;
                case KING:
                    score += PIECE_COLOR(piece) == PIECE_COLOR_WHITE? KING_PST[j][i] : -KING_PST[7 - j][i]; break;
            }
        }
    }
    return score;
}


