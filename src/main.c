#include <stdio.h>
#include <raylib.h>
#include "board.h"
#include "graphics.h"

int main(void) 
{
    int window_w = 600;
    int window_h = 600;
    int board_w = window_w * 0.8;
    int board_h = window_h * 0.8;
    int board_x = window_w * 0.1;
    int board_y = window_h * 0.1;

    InitWindow (
        window_w, 
        window_h, 
        "Chess Engine"
    );
    SetTargetFPS(10);

    board_t board = new_board();
    gui_state gui = new_gui_state();
    Texture2D piece_textures = load_piece_textures();

    while (!WindowShouldClose()) 
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
        {
            get_square_under_mouse(board_x, board_y, board_w, board_h, &gui.selected_col, &gui.selected_row);
        }

        BeginDrawing();
        ClearBackground(WHITE);
        
        draw_board(&board, &gui, piece_textures, board_x, board_y, board_w, board_h);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
