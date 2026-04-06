#include <stdio.h>
#include <raylib.h>
#include "board.h"
#include "graphics.h"

int main(void) {

    InitWindow(600, 600, "Chess Engine");
    SetTargetFPS(10);

    board_t board = new_board();
    Texture2D piece_textures = get_piece_textures();

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(WHITE);
        
        draw_board(board, piece_textures, 20, 20, 560, 560);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
