#include "graphics.h"

void draw_board(board_t board, float x, float y, float w, float h) 
{
    float square_w = w / 8;
    float square_h = h / 8;

    

    for (int i = 0; i < 8; i++) 
    {
        for (int j = 0; j < 8; j++) 
        {
            float x_pos = x + i * square_w;
            float y_pos = y + j * square_h;

            int light_square = !((i + j) % 2);
            
            DrawRectangle(x_pos, y_pos, square_w, square_h, light_square? LIGHT_SQUARE_COLOR : DARK_SQUARE_COLOR);
        }
    }
}