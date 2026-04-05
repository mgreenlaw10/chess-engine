#include "piece.h"

typedef struct {
    piece_t pieces[8][8];
    unsigned int turn_number;
} board_t;

board_t new_board();
void print_board(board_t);