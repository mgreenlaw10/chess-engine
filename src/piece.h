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

static inline PieceType PIECE_TYPE(piece_t piece) {return piece >> 1;}
static inline PieceColor PIECE_COLOR(piece_t piece) {return piece & 0b00000001;}
static inline piece_t MAKE_PIECE(PieceType type, PieceColor color) {return (type << 1) | color;}