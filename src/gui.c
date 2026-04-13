#include "gui.h"
#include <stdio.h>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

Color board_colors[COLOR_COUNT] = {
    [COLOR_DARK_SQUARE] = {181, 136, 99, 255},
    [COLOR_LIGHT_SQUARE] = {240, 217, 181, 255},
    [COLOR_SELECTED_SQUARE] = {247, 100, 100, 255},
    [COLOR_VALID_MOVE_SQUARE] = {160, 40, 80, 255}
};

Rectangle piece_texture_regions[TEXTURE_REGION_COUNT] = {
    [TEXTURE_REGION_WHITE_PAWN] = {300, 60, 60, 60},
    [TEXTURE_REGION_BLACK_PAWN] = {300, 0, 60, 60},
    [TEXTURE_REGION_WHITE_ROOK] = {120, 60, 60, 60},
    [TEXTURE_REGION_BLACK_ROOK] = {120, 0, 60, 60},
    [TEXTURE_REGION_WHITE_KNIGHT] = {180, 60, 60, 60},
    [TEXTURE_REGION_BLACK_KNIGHT] = {180, 0, 60, 60},
    [TEXTURE_REGION_WHITE_BISHOP] = {240, 60, 60, 60},
    [TEXTURE_REGION_BLACK_BISHOP] = {240, 0, 60, 60},
    [TEXTURE_REGION_WHITE_QUEEN] = {0, 60, 60, 60},
    [TEXTURE_REGION_BLACK_QUEEN] = {0, 0, 60, 60},
    [TEXTURE_REGION_WHITE_KING] = {60, 60, 60, 60},
    [TEXTURE_REGION_BLACK_KING] = {60, 0, 60, 60}
};

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
//
// Get a source region from the piece
// texture sheet for a certain piece.
//
static Rectangle get_source_region(piece_t piece) 
{
    Rectangle source;

    switch (PIECE_TYPE(piece)) {
        case PAWN:
            source = (PIECE_COLOR(piece) == PIECE_COLOR_WHITE)
                ? piece_texture_regions[TEXTURE_REGION_WHITE_PAWN]
                : piece_texture_regions[TEXTURE_REGION_BLACK_PAWN];
            break;

        case ROOK:
            source = (PIECE_COLOR(piece) == PIECE_COLOR_WHITE)
                ? piece_texture_regions[TEXTURE_REGION_WHITE_ROOK]
                : piece_texture_regions[TEXTURE_REGION_BLACK_ROOK];
            break;

        case KNIGHT:
            source = (PIECE_COLOR(piece) == PIECE_COLOR_WHITE)
                ? piece_texture_regions[TEXTURE_REGION_WHITE_KNIGHT]
                : piece_texture_regions[TEXTURE_REGION_BLACK_KNIGHT];
            break;

        case BISHOP:
            source = (PIECE_COLOR(piece) == PIECE_COLOR_WHITE)
                ? piece_texture_regions[TEXTURE_REGION_WHITE_BISHOP]
                : piece_texture_regions[TEXTURE_REGION_BLACK_BISHOP];
            break;

        case QUEEN:
            source = (PIECE_COLOR(piece) == PIECE_COLOR_WHITE)
                ? piece_texture_regions[TEXTURE_REGION_WHITE_QUEEN]
                : piece_texture_regions[TEXTURE_REGION_BLACK_QUEEN];
            break;

        case KING:
            source = (PIECE_COLOR(piece) == PIECE_COLOR_WHITE)
                ? piece_texture_regions[TEXTURE_REGION_WHITE_KING]
                : piece_texture_regions[TEXTURE_REGION_BLACK_KING];
            break;

        default:
            source = (Rectangle){0, 0, 0, 0};
            break;
    }

    return source;
}
//
// Main GUI draw loop for main menu.
//
void do_main_menu_loop(ProgramState* program_state) 
{
    int screen_w = GetScreenWidth();
    int screen_h = GetScreenHeight();
    int center_x = screen_w / 2;
    int center_y = screen_h / 2;

    int title_w = screen_w * 3.0f / 4.0f;
    int button_w = 200;

    Rectangle title_bounds = {
        screen_w / 2 - title_w / 2,
        48,
        title_w,
        128
    };

    Rectangle start_button_bounds = {
        center_x - button_w / 2,
        240,
        button_w,
        64
    };

    GuiSetStyle(DEFAULT, TEXT_SIZE, 24);

    BeginDrawing();
    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

    GuiLabel(title_bounds, "Welcome to the greatest chess\nsimulation on the planet >:)\n\nBy Mack and Evelyn <3");

    if (GuiButton(start_button_bounds, "Start Game")) 
    {
        *program_state = IN_GAME;
    }

    EndDrawing();
}
//
// Main update loop for game.
//
void do_game_loop(Board* board, GameGuiState* gui, Texture2D piece_textures) {
    
    // Handle mouse input
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
    {
        int clicked_col;
        int clicked_row;
        get_square_under_mouse(gui->board_x, gui->board_y, gui->board_w, gui->board_h, &clicked_col, &clicked_row);

        // If no piece is currently selected, select the clicked square
        if (gui->selected_col == NO_SELECTION || gui->selected_row == NO_SELECTION) 
        {
            gui->selected_col = clicked_col;
            gui->selected_row = clicked_row;
        }
        // If a piece is selected, move it to the clicked square
        // only if the clicked square is a valid move
        else 
        {
            // If the clicked square is not a valid move, select it instead
            if (try_move_piece(board, gui->selected_col, gui->selected_row, clicked_col, clicked_row) != MOVE_SUCCESS) 
            {
                gui->selected_col = clicked_col;
                gui->selected_row = clicked_row;
            } 
            else 
            {
                gui->selected_col = NO_SELECTION;
                gui->selected_row = NO_SELECTION;

                // After moving, check to see if the enemy king is in checkmate.
                int color = PIECE_COLOR(board->pieces[clicked_row][clicked_col]) == PIECE_COLOR_WHITE? PIECE_COLOR_BLACK : PIECE_COLOR_WHITE;
                if (king_in_checkmate(board, color))
                {
                    if (color == PIECE_COLOR_WHITE)
                    {
                        gui->white_king_in_checkmate = true;
                    }
                    else
                    {
                        gui->black_king_in_checkmate = true;
                    }
                }
            }   
        }
    }
    
    // Draw board state
    BeginDrawing();
    ClearBackground(WHITE);
    if (!gui->white_king_in_checkmate && !gui->black_king_in_checkmate)
    {
        draw_board(board, gui, piece_textures, gui->board_x, gui->board_y, gui->board_w, gui->board_h);
    }
    draw_game_gui(board, gui);
    EndDrawing();
}
//
// Only called in do_game_loop
//
void draw_game_gui(Board* board, GameGuiState* gui) 
{
    char turn_num_str[32];
    snprintf(turn_num_str, sizeof(turn_num_str), "Turn number: %d", board->turn_number);

    Rectangle turn_num_label_bounds = {
        24,
        24,
        288,
        48
    };

    Rectangle team_move_label_bounds = {
        312,
        24,
        288,
        48
    };

    GuiLabel(turn_num_label_bounds, turn_num_str);
    GuiLabel(team_move_label_bounds, white_move(board)? "White move" : "Black move");

    // If checkmate...
    if (gui->white_king_in_checkmate || gui->black_king_in_checkmate)
    {
        int screen_w = GetScreenWidth();
        int screen_h = GetScreenHeight();

        Rectangle game_result_label_bounds = {
            screen_w / 2,
            screen_h / 2,
            240,
            240
        };

        GuiLabel(game_result_label_bounds, !gui->white_king_in_checkmate? "Checkmate! White wins!" : "Checkmate! Black wins!");
    }
}
//
// Only called in do_game_loop
//
void draw_board(Board* board, GameGuiState* gui, Texture2D piece_textures, float x, float y, float w, float h) 
{
    float square_w = w / 8;
    float square_h = h / 8;
    //
    // Get possible moves for selected piece.
    // Must do this before drawing so we can highlight those tiles during draw.
    //
    piece_t selected_piece = (piece_t)NONE;
    move_t possible_moves[32];
    int num_possible_moves = 0;

    if (gui->selected_col != NO_SELECTION || 
        gui->selected_row != NO_SELECTION) 
    {
        selected_piece = board->pieces[gui->selected_row][gui->selected_col];
    }

    if (PIECE_TYPE(selected_piece) != NONE) 
    {
        get_possible_moves (
            board, 
            gui->selected_row, 
            gui->selected_col, 
            possible_moves, 
            &num_possible_moves
        );
    }
    //
    // Draw each square
    //
    for (int i = 0; i < 8; i++) 
    {
        for (int j = 0; j < 8; j++) 
        {
            float x_pos = x + j * square_w;
            float y_pos = y + i * square_h;

            int light_square = !((i + j) % 2);
            Color square_color = light_square? board_colors[COLOR_LIGHT_SQUARE] : board_colors[COLOR_DARK_SQUARE];

            Rectangle dst = {x_pos, y_pos, square_w, square_h};
            DrawRectangleRec(dst, square_color);
            //
            // Highlight square if it is a possible move of
            // the selected piece.
            //
            for (int m = 0; m < num_possible_moves; m++) 
            {   
                move_t move = possible_moves[m];
                if (move.dest_row == i && move.dest_column == j)
                {
                    DrawRectangleRec(dst, board_colors[COLOR_SELECTED_SQUARE]);
                }
            }
            //
            // Highlight square if it is the selected piece.
            //
            if (gui->selected_row == i && gui->selected_col == j) 
            {
                DrawRectangleRec(dst, board_colors[COLOR_VALID_MOVE_SQUARE]);
            }
            //
            // Draw the piece on the square.
            //
            piece_t piece = board->pieces[i][j];
            if (PIECE_TYPE(piece) == NONE) continue;
            
            DrawTexturePro(piece_textures, get_source_region(piece), dst, (Vector2){0, 0}, 0.0f, WHITE);
        }
    }
}