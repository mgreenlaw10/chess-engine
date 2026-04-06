#pragma once
//
// Game piece:
//
// LSB: color (0 = white, 1 = black)
// Remaining bits: type code
//
typedef unsigned char piece_t;
//
// Type codes
//
#define NONE 0x0
#define PAWN 0x1
#define KNIGHT 0x2
#define BISHOP 0x3
#define ROOK 0x4
#define QUEEN 0x5
#define KING 0x6
//
// Color codes
//
#define PIECE_COLOR_WHITE 0x0
#define PIECE_COLOR_BLACK 0x1
//
// Bitfield extractors
//
#define PIECE_TYPE(piece) ((piece) >> 1)
#define PIECE_COLOR(piece) ((piece) & 0b00000001)
//
// Piece constructor
//
#define MAKE_PIECE(type, color) ((type << 1) | (color))

void get_possible_moves(piece_t piece);
void get_possible_moves_pawn(piece_t pawn);
void get_possible_moves_rook(piece_t rook);
void get_possible_moves_bishop(piece_t bishop);
void get_possible_moves_knight(piece_t knight);
void get_possible_moves_king(piece_t king);
void get_possible_moves_queen(piece_t queen);