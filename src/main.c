#include <stdio.h>
#include "board.h"

int main(void) {
    board_t board = new_board();
    print_board(board);
    return 0;
}
