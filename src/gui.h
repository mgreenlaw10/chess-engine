#pragma once

#include <raylib.h>
#include <raygui.h>

#include "board.h"
#include "move.h"
#include "program_state.h"
//
// GUI state (GuiState name conflicts with RayGUI)
//
#define NO_SELECTION 0xFAFA
typedef struct {
    int board_x;
    int board_y;
    int board_w;
    int board_h;
    int selected_col; 
    int selected_row;
    bool white_king_in_checkmate;
    bool black_king_in_checkmate;
    bool reset_game;
} GameGuiState;
//
// Board colors
//
typedef enum {
    COLOR_DARK_SQUARE,
    COLOR_LIGHT_SQUARE,
    COLOR_SELECTED_SQUARE,
    COLOR_VALID_MOVE_SQUARE,

    COLOR_COUNT
} BoardColor;
//
// Texture source regions
//
typedef enum {
    TEXTURE_REGION_WHITE_PAWN,
    TEXTURE_REGION_BLACK_PAWN,
    TEXTURE_REGION_WHITE_ROOK,
    TEXTURE_REGION_BLACK_ROOK,
    TEXTURE_REGION_WHITE_KNIGHT,
    TEXTURE_REGION_BLACK_KNIGHT,
    TEXTURE_REGION_WHITE_BISHOP,
    TEXTURE_REGION_BLACK_BISHOP,
    TEXTURE_REGION_WHITE_QUEEN,
    TEXTURE_REGION_BLACK_QUEEN,
    TEXTURE_REGION_WHITE_KING,
    TEXTURE_REGION_BLACK_KING,

    TEXTURE_REGION_COUNT
} PieceTextureRegion;
//
// Implemented in gui.c
//
extern Color board_colors[COLOR_COUNT];
extern Rectangle piece_texture_regions[TEXTURE_REGION_COUNT];

Texture2D load_piece_textures();

bool get_square_under_mouse(int board_x, int board_y, int board_w, int board_h, int* col, int* row);
//
// Main update loop functions
//
void do_main_menu_loop(ProgramState* program_state);
void do_game_loop(Board* board, GameGuiState* gui, Texture2D piece_textures);
//
// Draw functions called by udpate loop functions
//
void draw_game_gui(Board* board, GameGuiState* gui);
void draw_board (
    Board* board, 
    GameGuiState* gui,
    Texture2D piece_textures, 
    float x, 
    float y, 
    float w, 
    float h
);