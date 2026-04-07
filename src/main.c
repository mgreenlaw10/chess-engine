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
            int clicked_col;
            int clicked_row;
            get_square_under_mouse(board_x, board_y, board_w, board_h, &clicked_col, &clicked_row);

            // If no piece is currently selected, select the clicked square
            if (gui.selected_col == NO_SELECTION || gui.selected_row == NO_SELECTION) 
            {
                gui.selected_col = clicked_col;
                gui.selected_row = clicked_row;
            }
            // If a piece is selected, move it to the clicked square
            // only if the clicked square is a valid move
            else 
            {
                move_t moves[32];
                int moved = 0;
                int num_moves = 0;

                all_moves_for_piece (
                    &board, 
                    gui.selected_row, 
                    gui.selected_col, 
                    moves, 
                    &num_moves
                );
                
                for (int i = 0; i < num_moves; i++) 
                {
                    if (moves[i].dest_column == clicked_col 
                     && moves[i].dest_row == clicked_row) 
                    {
                        move_piece(&board, gui.selected_col, gui.selected_row, clicked_col, clicked_row);
                        gui.selected_col = NO_SELECTION;
                        gui.selected_row = NO_SELECTION;
                        moved = 1;
                        break;
                    }
                }
                // If the clicked square is not a valid move, select it instead
                if (!moved) 
                {
                    gui.selected_col = clicked_col;
                    gui.selected_row = clicked_row;
                }              
            }
        }

        BeginDrawing();
        ClearBackground(WHITE);
        
        draw_board(&board, &gui, piece_textures, board_x, board_y, board_w, board_h);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
