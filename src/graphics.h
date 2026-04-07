#pragma once

#include "raylib.h"
#include "board.h"
//
// GUi state
//
#define NO_SELECTION 0xFAFA
typedef struct {
    int selected_col, 
        selected_row;
} gui_state;

inline gui_state new_gui_state(void) 
{
    return (gui_state) {
        NO_SELECTION, 
        NO_SELECTION
    };
}
//
// Board colors
//
#define DARK_SQUARE_COLOR (Color){49, 224, 85, 255}
#define LIGHT_SQUARE_COLOR (Color){247, 239, 185, 255}
#define SELECT_TINT_COLOR (Color){200, 60, 60, 63}
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

Texture2D load_piece_textures();

int get_square_under_mouse(int board_x, int board_y, int board_w, int board_h, int* col, int* row);

void draw_board (
    board_t board, 
    gui_state gui,
    Texture2D piece_textures, 
    float x, 
    float y, 
    float w, 
    float h
);