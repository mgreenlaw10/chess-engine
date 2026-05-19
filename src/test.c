#include "test.h"

void print_move(Move move)
{
    char move_str[8];
    int i = 0;

    switch (PIECE_TYPE(move.piece))
    {
        case PAWN: move_str[i++] = 'p'; break;
        case KNIGHT: move_str[i++] = 'k'; break;
        case BISHOP: move_str[i++] = 'b'; break;
        case ROOK: move_str[i++] = 'r'; break;
        case QUEEN: move_str[i++] = 'q'; break;
        case KING: move_str[i++] = 'K'; break;
    }

    move_str[i++] = (char)move.col + 97;
    move_str[i++] = '8' - (char)move.row;
    move_str[i++] = (char)move.dst_col + 97;
    move_str[i++] = '8' - (char)move.dst_row;

    move_str[i] = '\0';
    printf("%s", move_str);
}

void print_moves(Move moves[], int num_moves)
{
    for (int i = 0; i < num_moves; i++)
    {
        print_move(moves[i]);
    }
}