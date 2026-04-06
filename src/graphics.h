#pragma once

#include "raylib.h"
#include "board.h"
//
// Board colors
//
#define DARK_SQUARE_COLOR (Color){49, 224, 85, 255}
#define LIGHT_SQUARE_COLOR (Color){247, 239, 185, 255}
//
// Texture source regions
//
#define TEXTURE_REGION_WHITE_PAWN (Rectangle){300, 60, 60, 60}
#define TEXTURE_REGION_BLACK_PAWN (Rectangle){300, 0, 60, 60}
#define TEXTURE_REGION_WHITE_ROOK (Rectangle){120, 60, 60, 60}
#define TEXTURE_REGION_BLACK_ROOK (Rectangle){120, 0, 60, 60}
#define TEXTURE_REGION_WHITE_KNIGHT (Rectangle){180, 60, 60, 60}
#define TEXTURE_REGION_BLACK_KNIGHT (Rectangle){180, 0, 60, 60}
#define TEXTURE_REGION_WHITE_BISHOP (Rectangle){240, 60, 60, 60}
#define TEXTURE_REGION_BLACK_BISHOP (Rectangle){240, 0, 60, 60}
#define TEXTURE_REGION_WHITE_QUEEN (Rectangle){0, 60, 60, 60}
#define TEXTURE_REGION_BLACK_QUEEN (Rectangle){0, 0, 60, 60}
#define TEXTURE_REGION_WHITE_KING (Rectangle){60, 60, 60, 60}
#define TEXTURE_REGION_BLACK_KING (Rectangle){60, 0, 60, 60}

Texture2D get_piece_textures();

void draw_board(board_t, Texture2D, float, float, float, float);