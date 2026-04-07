#include "graphics.h"
#include <stdio.h>

int get_square_under_mouse(int board_x, int board_y, int board_w, int board_h, int* col, int* row) 
{
    int x = GetMouseX();
    int y = GetMouseY();
    int lx = x - board_x;
    int ly = y - board_y;

    if (lx < 0 || ly < 0 || lx > board_w || ly > board_h) {
        return 1;
    }

    *col = lx * 8 / board_w;
    *row = ly * 8 / board_h;
}

Texture2D load_piece_textures() 
{
    Texture2D texture = LoadTexture("res/pieces.png");
    SetTextureFilter(texture, TEXTURE_FILTER_BILINEAR);
    return texture;
}

static Rectangle get_source_region(piece_t piece) 
{
    Rectangle source;

    switch (PIECE_TYPE(piece)) {
        case PAWN:
            source = (PIECE_COLOR(piece) == PIECE_COLOR_WHITE)
                ? TEXTURE_REGION_WHITE_PAWN
                : TEXTURE_REGION_BLACK_PAWN;
            break;

        case ROOK:
            source = (PIECE_COLOR(piece) == PIECE_COLOR_WHITE)
                ? TEXTURE_REGION_WHITE_ROOK
                : TEXTURE_REGION_BLACK_ROOK;
            break;

        case KNIGHT:
            source = (PIECE_COLOR(piece) == PIECE_COLOR_WHITE)
                ? TEXTURE_REGION_WHITE_KNIGHT
                : TEXTURE_REGION_BLACK_KNIGHT;
            break;

        case BISHOP:
            source = (PIECE_COLOR(piece) == PIECE_COLOR_WHITE)
                ? TEXTURE_REGION_WHITE_BISHOP
                : TEXTURE_REGION_BLACK_BISHOP;
            break;

        case QUEEN:
            source = (PIECE_COLOR(piece) == PIECE_COLOR_WHITE)
                ? TEXTURE_REGION_WHITE_QUEEN
                : TEXTURE_REGION_BLACK_QUEEN;
            break;

        case KING:
            source = (PIECE_COLOR(piece) == PIECE_COLOR_WHITE)
                ? TEXTURE_REGION_WHITE_KING
                : TEXTURE_REGION_BLACK_KING;
            break;

        default:
            source = (Rectangle){0, 0, 0, 0};
            break;
    }

    return source;
}

void draw_board(board_t board, gui_state gui, Texture2D piece_textures, float x, float y, float w, float h) 
{
    float square_w = w / 8;
    float square_h = h / 8;    

    for (int i = 0; i < 8; i++) 
    {
        for (int j = 0; j < 8; j++) 
        {
            float x_pos = x + j * square_w;
            float y_pos = y + i * square_h;

            int light_square = !((i + j) % 2);

            Rectangle dst = {x_pos, y_pos, square_w, square_h};
            DrawRectangleRec(dst, light_square? LIGHT_SQUARE_COLOR : DARK_SQUARE_COLOR);
            
            // Highlight selected square
            if (gui.selected_col == j && gui.selected_row == i) 
            {
                DrawRectangleRec(dst, SELECT_TINT_COLOR);
            }

            piece_t piece = board.pieces[i][j];
            if (PIECE_TYPE(piece) == NONE) 
            {
                continue;
            }
            DrawTexturePro(piece_textures, get_source_region(piece), dst, (Vector2){0, 0}, 0.0f, WHITE);
        }
    }
}