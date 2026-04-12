#include <stdio.h>
#include <raylib.h>
#include "board.h"
#include "graphics.h"

bool move_selected_piece(board_t* board, gui_state* gui, int dst_row, int dst_col) {
    //
    // If a king is in check, skip unless 
    // the selected piece is that king.
    //
    if (king_in_check(board, PIECE_COLOR_WHITE)) 
    {
        if (PIECE_TYPE(board->pieces[gui->selected_row][gui->selected_col]) != KING
        || PIECE_COLOR(board->pieces[gui->selected_row][gui->selected_col]) != PIECE_COLOR_WHITE) return false;
    }
    if (king_in_check(board, PIECE_COLOR_BLACK))
    {
        if (PIECE_TYPE(board->pieces[gui->selected_row][gui->selected_col]) != KING
        || PIECE_COLOR(board->pieces[gui->selected_row][gui->selected_col]) != PIECE_COLOR_BLACK) return false;
    }
    //
    // Make sure that the destination is
    // a valid move for the selected piece.
    //
    move_t moves[32];
    int num_moves = 0;

    get_possible_moves (
        board, 
        gui->selected_row, 
        gui->selected_col, 
        moves, 
        &num_moves
    );
    //
    // Check the destination against
    // all valid moves.
    //
    for (int i = 0; i < num_moves; i++) 
    {
        if (moves[i].dest_column == dst_col 
            && moves[i].dest_row == dst_row) 
        {
            move_piece(board, gui->selected_col, gui->selected_row, dst_col, dst_row);
            return true;
        }
    }
    //
    // If no valid move matched
    // the destination, return false.
    return false;
}

int main(void) 
{
    int window_w = 900;
    int window_h = 900;
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

    while (!WindowShouldClose()) {   
        //
        // Handle mouse input
        //
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
                // If the clicked square is not a valid move, select it instead
                if (!move_selected_piece(&board, &gui, clicked_row, clicked_col)) 
                {
                    gui.selected_col = clicked_col;
                    gui.selected_row = clicked_row;
                } 
                else 
                {
                    gui.selected_col = NO_SELECTION;
                    gui.selected_row = NO_SELECTION;
                }   
            }
        }
        //
        // Draw
        //
        BeginDrawing();

        ClearBackground(WHITE);
        draw_board(&board, &gui, piece_textures, board_x, board_y, board_w, board_h);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
