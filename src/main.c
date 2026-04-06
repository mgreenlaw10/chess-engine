#include <stdio.h>
#include <raylib.h>
#include "board.h"
#include "graphics.h"

int main(void) {

    InitWindow(900, 900, "Chess Engine");
    SetTargetFPS(10);

    board_t board = new_board();
    //print_board(board);

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(WHITE);
        
        //DrawCircle(100, 100, 20, BLACK);
        draw_board(board, 50, 50, 800, 800);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
