#include <stdio.h>
#include <raylib.h>
#include "board.h"
#include "graphics.h"

int main(void) {

    InitWindow(900, 900, "Chess Engine");
    SetTargetFPS(10);

    board_t board = new_board();
    Texture2D piece_textures = get_piece_textures();

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(WHITE);
        
        draw_board(board, piece_textures, 50, 50, 800, 800);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
