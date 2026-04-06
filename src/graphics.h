#pragma once

#include "raylib.h"
#include "board.h"

#define DARK_SQUARE_COLOR (Color){49, 224, 85, 255}
#define LIGHT_SQUARE_COLOR (Color){247, 239, 185, 255}

void draw_board(board_t board, float x, float y, float w, float h);