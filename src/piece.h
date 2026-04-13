#pragma once
//
// Game piece:
//
// LSB: color (0 = white, 1 = black)
// Remaining bits: type code
//
typedef unsigned char piece_t;

typedef enum {
    NONE    = 0,
    PAWN    = 1,
    KNIGHT  = 2,
    BISHOP  = 3,
    ROOK    = 4,
    QUEEN   = 5,
    KING    = 6
} PieceType;

typedef enum {
    PIECE_COLOR_WHITE = 0,
    PIECE_COLOR_BLACK = 1
} PieceColor;

#define PIECE_TYPE(piece) ((piece) >> 1)
#define PIECE_COLOR(piece) ((piece) & 0b00000001)

#define MAKE_PIECE(type, color) ((type << 1) | (color))