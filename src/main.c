#include <stdio.h>
#include "gui.h"

void loop(ProgramState* program_state, Board* board, GameGuiState* gui, Texture2D piece_textures) 
{
    switch (*program_state) 
    {
        case MAIN_MENU:

            do_main_menu_loop(program_state);
            break;

        case IN_GAME:

            do_game_loop(board, gui, piece_textures);

            // If gui requested game reset...
            if (gui->reset_game)
            {
                *board = new_board();
                board->turn_number = 1;
                gui->selected_col = NO_SELECTION;
                gui->selected_row = NO_SELECTION;
                gui->white_king_in_checkmate = false;
                gui->black_king_in_checkmate = false;
                gui->reset_game = false;
            }
            break;
    }
}

int main(void) 
{
    ProgramState state = MAIN_MENU;

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
    SetTargetFPS(60);

    Board board = new_board();

    GameGuiState gui = {
        .selected_col = NO_SELECTION,
        .selected_row = NO_SELECTION,
        .board_x = board_x,
        .board_y = board_y,
        .board_w = board_w,
        .board_h = board_h,
        .white_king_in_checkmate = false,
        .black_king_in_checkmate = false,
        .reset_game = false
    };

    Texture2D piece_textures = load_piece_textures();

    while (!WindowShouldClose()) 
    {   
        loop(&state, &board, &gui, piece_textures);
    }

    CloseWindow();
    return 0;
}
