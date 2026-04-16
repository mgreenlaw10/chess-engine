#include <stdio.h>

#include "board.h"

//
// Use constant offsets for finding squares targeted
// by a knight because it's easier.
//
static int knight_move_offsets[8][2] = {
    {-2, -1},
    {-2,  1},
    {-1, -2},
    {-1,  2},
    { 1, -2},
    { 1,  2},
    { 2, -1},
    { 2,  1}
};

static void initialize_pieces(piece_t pieces[8][8]) {
    // Black on top
    pieces[0][0] = MAKE_PIECE(ROOK, PIECE_COLOR_BLACK);
    pieces[0][1] = MAKE_PIECE(KNIGHT, PIECE_COLOR_BLACK);
    pieces[0][2] = MAKE_PIECE(BISHOP, PIECE_COLOR_BLACK);
    pieces[0][3] = MAKE_PIECE(QUEEN, PIECE_COLOR_BLACK);
    pieces[0][4] = MAKE_PIECE(KING, PIECE_COLOR_BLACK);
    pieces[0][5] = MAKE_PIECE(BISHOP, PIECE_COLOR_BLACK);
    pieces[0][6] = MAKE_PIECE(KNIGHT, PIECE_COLOR_BLACK);
    pieces[0][7] = MAKE_PIECE(ROOK, PIECE_COLOR_BLACK);
    for (int i = 0; i < 8; i++) {
        pieces[1][i] = MAKE_PIECE(PAWN, PIECE_COLOR_BLACK);
    }
    // Fill in empty space
    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            pieces[i][j] = (piece_t)0;
        }
    }
    // White on bottom
    pieces[7][0] = MAKE_PIECE(ROOK, PIECE_COLOR_WHITE);
    pieces[7][1] = MAKE_PIECE(KNIGHT, PIECE_COLOR_WHITE);
    pieces[7][2] = MAKE_PIECE(BISHOP, PIECE_COLOR_WHITE);
    pieces[7][3] = MAKE_PIECE(QUEEN, PIECE_COLOR_WHITE);
    pieces[7][4] = MAKE_PIECE(KING, PIECE_COLOR_WHITE);
    pieces[7][5] = MAKE_PIECE(BISHOP, PIECE_COLOR_WHITE);
    pieces[7][6] = MAKE_PIECE(KNIGHT, PIECE_COLOR_WHITE);
    pieces[7][7] = MAKE_PIECE(ROOK, PIECE_COLOR_WHITE);
    for (int i = 0; i < 8; i++) {
        pieces[6][i] = MAKE_PIECE(PAWN, PIECE_COLOR_WHITE);
    }
}
//
// Get a new initialized board.
//
Board new_board() 
{
    Board board = {
        .turn_number = 1,
        .team_to_move = PIECE_COLOR_WHITE,
        .num_white_pawns = 8,
        .num_black_pawns = 8,
        .num_white_knights = 2,
        .num_black_knights = 2,
        .num_white_bishops = 2,
        .num_black_bishops = 2,
        .num_white_rooks = 2,
        .num_black_rooks = 2,
        .num_white_queens = 1,
        .num_black_queens = 1
    };
    initialize_pieces(board.pieces);
    return board;
}
//
// Remove a piece and decrement the board's
// respective counter flag.
//
static void capture_piece(Board* board, int col, int row)
{
    PieceType type = PIECE_TYPE(board->pieces[row][col]);

    if (type == NONE)
    {
        return;
    }

    PieceColor color = PIECE_COLOR(board->pieces[row][col]);

    switch (type)
    {
        case PAWN:
            if (color == PIECE_COLOR_WHITE)
            {
                board->num_white_pawns--;
            }
            else
            {
                board->num_black_pawns--;
            }
            break;

        case KNIGHT:
            if (color == PIECE_COLOR_WHITE)
            {
                board->num_white_knights--;
            }
            else
            {
                board->num_black_knights--;
            }
            break;

        case BISHOP:
            if (color == PIECE_COLOR_WHITE)
            {
                board->num_white_bishops--;
            }
            else
            {
                board->num_black_bishops--;
            }
            break;

        case ROOK:
            if (color == PIECE_COLOR_WHITE)
            {
                board->num_white_rooks--;
            }
            else
            {
                board->num_black_rooks--;
            }
            break;
        
        case QUEEN:
            if (color == PIECE_COLOR_WHITE)
            {
                board->num_white_queens--;
            }
            else
            {
                board->num_black_queens--;
            }
            break;
    }
    // Actually remove the piece
    board->pieces[row][col] = (piece_t)0;
}
//
// Return the position of a specific king.
// The king should never be taken so
// the return value should always be valid.
//
BoardPos find_king(Board* board, PieceColor color) 
{
    for (int i = 0; i < 8; i++) 
    {
        for (int j = 0; j < 8; j++) 
        {
            piece_t piece = board->pieces[i][j];
            if (PIECE_TYPE(piece) == KING && PIECE_COLOR(piece) == color) 
            {
                return (BoardPos){i, j};
            }
        }
    }
    // There is a bug if king was not found.
    printf("ERROR! The %s king is missing!", color == PIECE_COLOR_WHITE? "white" : "black");
}
//
// Take a board by value, execute a move,
// and return whether or not the new
// position puts the ally king in check.
//
static bool simulate_for_check(Board board, int src_col, int src_row, int dst_col, int dst_row) 
{
    move_piece(&board, src_col, src_row, dst_col, dst_row);
    return king_in_check(&board, PIECE_COLOR(board.pieces[dst_row][dst_col]));
}

typedef struct {
    int dx;
    int dy;
} Direction;

static Direction EAST       = { 1,  0};
static Direction WEST       = {-1,  0};
static Direction NORTH      = { 0, -1};
static Direction SOUTH      = { 0,  1};
static Direction NORTHWEST  = {-1, -1};
static Direction NORTHEAST  = { 1, -1};
static Direction SOUTHWEST  = {-1,  1};
static Direction SOUTHEAST  = { 1,  1};

static bool board_pos_in_bounds(BoardPos pos)
{
    return pos.col > -1 && pos.col < 8 && pos.row > -1 && pos.row < 8;
}

static bool first_occupied_square(Board* board, BoardPos origin, Direction direction, BoardPos* result)
{
    BoardPos target_pos = {
        .col = origin.col + direction.dx, 
        .row = origin.row + direction.dy
    };

    while (board_pos_in_bounds(target_pos) && PIECE_TYPE(board->pieces[target_pos.row][target_pos.col]) == NONE)
    {
        target_pos.col += direction.dx;
        target_pos.row += direction.dy;
    }

    if (board_pos_in_bounds(target_pos))
    {
        *result = target_pos;
        return true;
    }

    return false;
}
//
//
//
//
bool king_in_check(Board* board, PieceColor color)
{
    BoardPos king_pos = find_king(board, color);
    BoardPos target_pos;
    piece_t target_piece;

    // Find knight checks directly.
    //
    //
    for (int i = 0; i < 8; i++)
    {
        target_pos.row = king_pos.row + knight_move_offsets[i][0];
        target_pos.col = king_pos.col + knight_move_offsets[i][1];

        if (board_pos_in_bounds(target_pos))
        {
            target_piece = board->pieces[target_pos.row][target_pos.col];

            if (PIECE_TYPE(target_piece) == KNIGHT && PIECE_COLOR(target_piece) != color)
            {
                return true;
            }
        }
    }
    
    // Find pawn checks directly.
    //
    //
    int target_row;
    int target_col;

    switch (color)
    {
        case PIECE_COLOR_WHITE:

            target_row = king_pos.row - 1;

            if (target_row < 0)
            {
                break;
            }

            target_col = king_pos.col - 1;

            if (target_col > 0 && PIECE_TYPE(board->pieces[target_row][target_col]) == PAWN && PIECE_COLOR(board->pieces[target_row][target_col]) != color)
            {
                return true;
            }

            target_col = king_pos.col + 1;

            if (target_col < 8 && PIECE_TYPE(board->pieces[target_row][target_col]) == PAWN && PIECE_COLOR(board->pieces[target_row][target_col]) != color)
            {
                return true;
            }

            break;
        
        case PIECE_COLOR_BLACK:

            target_row = king_pos.row + 1;

            if (target_row > 7)
            {
                break;
            }

            target_col = king_pos.col - 1;

            if (target_col > 0 && PIECE_TYPE(board->pieces[target_row][target_col]) == PAWN && PIECE_COLOR(board->pieces[target_row][target_col]) != color)
            {
                return true;
            }

            target_col = king_pos.col + 1;

            if (target_col < 8 && PIECE_TYPE(board->pieces[target_row][target_col]) == PAWN && PIECE_COLOR(board->pieces[target_row][target_col]) != color)
            {
                return true;
            }

            break;
    }

    // Find remaining checks by tracing a path
    // in each direction and identifying the first piece found.
    //
    if (first_occupied_square(board, king_pos, WEST, &target_pos))
    {
        target_piece = board->pieces[target_pos.row][target_pos.col];

        if (PIECE_COLOR(target_piece) != color && (PIECE_TYPE(target_piece) == ROOK || PIECE_TYPE(target_piece) == QUEEN))
        {
            return true;
        }
    }

    if (first_occupied_square(board, king_pos, EAST, &target_pos))
    {
        target_piece = board->pieces[target_pos.row][target_pos.col];
        
        if (PIECE_COLOR(target_piece) != color && (PIECE_TYPE(target_piece) == ROOK || PIECE_TYPE(target_piece) == QUEEN))
        {
            return true;
        }
    }

    if (first_occupied_square(board, king_pos, NORTH, &target_pos))
    {
        target_piece = board->pieces[target_pos.row][target_pos.col];
        
        if (PIECE_COLOR(target_piece) != color && (PIECE_TYPE(target_piece) == ROOK || PIECE_TYPE(target_piece) == QUEEN))
        {
            return true;
        }
    }

    if (first_occupied_square(board, king_pos, SOUTH, &target_pos))
    {
        target_piece = board->pieces[target_pos.row][target_pos.col];
        
        if (PIECE_COLOR(target_piece) != color && (PIECE_TYPE(target_piece) == ROOK || PIECE_TYPE(target_piece) == QUEEN))
        {
            return true;
        }
    }

    if (first_occupied_square(board, king_pos, NORTHWEST, &target_pos))
    {
        target_piece = board->pieces[target_pos.row][target_pos.col];
        
        if (PIECE_COLOR(target_piece) != color && (PIECE_TYPE(target_piece) == BISHOP || PIECE_TYPE(target_piece) == QUEEN))
        {
            return true;
        }
    }

    if (first_occupied_square(board, king_pos, SOUTHWEST, &target_pos))
    {
        target_piece = board->pieces[target_pos.row][target_pos.col];
        
        if (PIECE_COLOR(target_piece) != color && (PIECE_TYPE(target_piece) == BISHOP || PIECE_TYPE(target_piece) == QUEEN))
        {
            return true;
        }
    }

    if (first_occupied_square(board, king_pos, NORTHEAST, &target_pos))
    {
        target_piece = board->pieces[target_pos.row][target_pos.col];
        
        if (PIECE_COLOR(target_piece) != color && (PIECE_TYPE(target_piece) == BISHOP || PIECE_TYPE(target_piece) == QUEEN))
        {
            return true;
        }
    }

    if (first_occupied_square(board, king_pos, SOUTHEAST, &target_pos))
    {
        target_piece = board->pieces[target_pos.row][target_pos.col];
        
        if (PIECE_COLOR(target_piece) != color && (PIECE_TYPE(target_piece) == BISHOP || PIECE_TYPE(target_piece) == QUEEN))
        {
            return true;
        }
    }

    return false;
}

//
// Determine whether or not the king 
// of the given color is in check.
//
// bool king_in_check(Board* board, PieceColor color) 
// {
//     BoardPos king_pos = find_king(board, color);

//     // Act like it's {!color}'s move while testing
//     PieceColor temp = board->team_to_move;
//     board->team_to_move = !color;

//     for (int i = 0; i < 8; i++) 
//     {
//         for (int j = 0; j < 8; j++) 
//         {
//             // If piece is an enemy, check its valid
//             // moves to see if one contains the king.
//             if (PIECE_COLOR(board->pieces[i][j]) != color) 
//             {
//                 Move moves[32];
//                 int num_moves = get_possible_moves(board, i, j, moves);

//                 for (int k = 0; k < num_moves; k++) 
//                 {
//                     Move move = moves[k];
//                     if (move.dst_row == king_pos.row && move.dst_col == king_pos.col) 
//                     {
//                         board->team_to_move = temp;
//                         return true;
//                     }
//                 }
//             }
//         }
//     }
//     board->team_to_move = temp;
//     return false;
// }
//
// Determine whether or not the king 
// of the given color is in checkmate.
//
bool king_in_checkmate(Board* board, PieceColor color) 
{
    // Maybe remove this later because it
    // is probably redundant as we will likely
    // be explicitly looking for check before
    // checkmate anyway.
    if (!king_in_check(board, color))
    {
        return false;
    }

    BoardPos king_pos = find_king(board, color);

    // act like it's {color}'s move while testing
    PieceColor temp = board->team_to_move;
    board->team_to_move = color;

    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++) 
        {
            // If piece is an ally, check each of its valid
            // moves to see if the result is a position
            // where the king is still in check.
            if (PIECE_COLOR(board->pieces[r][c]) == color) 
            {
                Move ally_moves[32];
                int num_ally_moves = get_possible_moves(board, r, c, ally_moves);

                for (int k = 0; k < num_ally_moves; k++) 
                {
                    Move ally_move = ally_moves[k];
                    // If any move an ally can make escapes check,
                    // the king is not in checkmate.
                    if (!simulate_for_check(*board, ally_move.col, ally_move.row, ally_move.dst_col, ally_move.dst_row))
                    {
                        board->team_to_move = temp;
                        return false;
                    }
                }
            }
        }
    }
    // If there is no move an ally can make that escapes check,
    // the king is in checkmate.
    board->team_to_move = temp;
    return true;
}
//
// Return whether or not a king is in stalemate.
// This is the same as checkmate but the king
// cannot currently be in check.
//
bool king_in_stalemate(Board* board, PieceColor color)
{
    if (king_in_check(board, color))
    {
        return false;
    }

    BoardPos king_pos = find_king(board, color);

    // act like it's {color}'s move while testing
    PieceColor temp = board->team_to_move;
    board->team_to_move = color;

    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++) 
        {
            // If piece is an ally, check each of its valid
            // moves to see if the result is a position
            // where the king is still in check.
            if (PIECE_COLOR(board->pieces[r][c]) == color) 
            {
                Move ally_moves[32];
                int num_ally_moves = get_possible_moves(board, r, c, ally_moves);

                for (int k = 0; k < num_ally_moves; k++) 
                {
                    Move ally_move = ally_moves[k];
                    // If any move an ally can make avoids check,
                    // the king is not in stalemate.
                    if (!simulate_for_check(*board, ally_move.col, ally_move.row, ally_move.dst_col, ally_move.dst_row))
                    {
                        board->team_to_move = temp;
                        return false;
                    }
                }
            }
        }
    }
    // If there is no move an ally can make that avoids check,
    // the king is in stalemate.
    board->team_to_move = temp;
    return true;
}
//
// Move a piece without checking whether
// or not the move is actually legal.
//
void move_piece(Board* board, int src_col, int src_row, int dst_col, int dst_row) 
{
    piece_t captured = board->pieces[dst_row][dst_col];

    capture_piece(board, dst_col, dst_row);

    board->pieces[dst_row][dst_col] = board->pieces[src_row][src_col];
    board->pieces[src_row][src_col] = (piece_t)NONE;

    int color = PIECE_COLOR(board->pieces[dst_row][dst_col]);
    int type = PIECE_TYPE(board->pieces[dst_row][dst_col]);
    
    // Castling
    
    // King
    if (type == KING && src_row == dst_row && (src_row == 7 || src_row == 0) && src_col == 4 && dst_col == 6) 
    {
        board->pieces[src_row][5] = board->pieces[src_row][7];
        board->pieces[src_row][7] = (piece_t)NONE;
        
    }
    // Queen
    if (type == KING && src_row == dst_row && (src_row == 7 || src_row == 0) && src_col == 4 && dst_col == 2) 
    {
        board->pieces[src_row][3] = board->pieces[src_row][0];
        board->pieces[src_row][0] = (piece_t)NONE;
    }
    if (type == ROOK && src_row == dst_row && (src_row == 7 || src_row == 0) && PIECE_TYPE(captured) == NONE) 
    {
        piece_t king = board->pieces[src_row][4];
        
        if (PIECE_TYPE(king) == KING && PIECE_COLOR(king) == color) 
        {
            if (src_col == 7 && dst_col == 5 && PIECE_TYPE(board->pieces[src_row][6]) == NONE) {
                board->pieces[src_row][6] = king;
                board->pieces[src_row][4] = (piece_t)NONE;

            } else if (src_col == 0 && dst_col == 3 && PIECE_TYPE(board->pieces[src_row][2]) == NONE) {
                board->pieces[src_row][2] = king;
                board->pieces[src_row][4] = (piece_t)NONE;
            }
        }
    }
    
    // Check if pawn should promote after moving.
    if (type == PAWN) 
    {
        if (color == PIECE_COLOR_WHITE && dst_row == 0) 
        {
            board->pieces[dst_row][dst_col] = MAKE_PIECE(QUEEN, PIECE_COLOR_WHITE);
        }
        else if (color == PIECE_COLOR_BLACK && dst_row == 7) 
        {
            board->pieces[dst_row][dst_col] = MAKE_PIECE(QUEEN, PIECE_COLOR_BLACK);
        }
    }

    board->team_in_check = king_in_check(board, !board->team_to_move);
}
//
// Try to move a piece and get back a result
// value describing whether the operation
// succeeded or why it failed.
//
MoveResult try_move_piece(Board* board, int src_col, int src_row, int dst_col, int dst_row) 
{
    // If moving to the same square...
    if (src_col == dst_col && src_row == dst_row)
    {
        return INVALID_MOVE;
    }
    // If the wrong color is selected...
    if (PIECE_COLOR(board->pieces[src_row][src_col]) != board->team_to_move) 
    {
        return WRONG_TEAM;
    }
    // If a king is in check, skip unless 
    // the selected piece is that king.
    //
    // Pass by value to copy
    if (simulate_for_check(*board, src_col, src_row, dst_col, dst_row)) 
    {
        return KING_IN_CHECK;
    }

    Move moves[32];
    int num_moves = get_possible_moves (
        board, 
        src_row, 
        src_col, 
        moves
    );
    // Check the destination against
    // all valid moves.
    for (int i = 0; i < num_moves; i++) 
    {   
        Move move = moves[i];
        if (move.dst_col == dst_col && move.dst_row == dst_row) 
        {
            move_piece(board, src_col, src_row, dst_col, dst_row);
            board->turn_number++;
            // Hacky way to flip enum value
            board->team_to_move = !board->team_to_move;
            return MOVE_SUCCESS;
        }
    }
    // If no valid move matched
    // the destination, return false.
    return INVALID_MOVE;
}

#define EMPTY 0
#define TAKEN 1
#define ENEMY 2

// helper for get possible moves
// determine state of a square (row,col) on the board
int target_state(Board *board, int row, int col, int color) {
    //access specific square on the board identified by its row and col
    piece_t target = board->pieces[row][col];

    // is this how to identify empty square ??
    if (PIECE_TYPE(target) == NONE) {
        return EMPTY;
    }
    // target occupied by same color piece 
    if (PIECE_COLOR(target) == color) {
        return TAKEN;
    }
    // other wise enemy
    // maybe can change this to also return piece type
    return ENEMY;
}
//
// Load moves[] with all found possible moves for the piece
// at [row][col] and return the number of moves found.
//
//
int get_possible_moves(Board *board, int row, int col, Move moves[]) 
{
    piece_t piece = board->pieces[row][col];
    PieceType type = PIECE_TYPE(piece);
    PieceColor color = PIECE_COLOR(piece);

    if (type == NONE || board->team_to_move != color) 
    {
        return 0;
    }
    
    switch (type)
    {
        case PAWN: return get_possible_moves_pawn(board, PIECE_COLOR(piece), row, col, moves);

        case KNIGHT: return get_possible_moves_knight(board, PIECE_COLOR(piece), row, col, moves);

        case BISHOP: return get_possible_moves_bishop(board, PIECE_COLOR(piece), row, col, moves);

        case ROOK: return get_possible_moves_rook(board, PIECE_COLOR(piece), row, col, moves);

        case QUEEN: return get_possible_moves_queen(board, PIECE_COLOR(piece), row, col, moves);

        case KING: return get_possible_moves_king(board, PIECE_COLOR(piece), row, col, moves);
    }

    return 0;
}
//
//
// Adds a move as long as it doesn't put you in check.
//
static bool add_if_valid_move(Board* board, int src_col, int src_row, int dst_col, int dst_row, Move move_list[], int index)
{
    if (!simulate_for_check(*board, src_col, src_row, dst_col, dst_row))
    {
        move_list[index] = (Move) {
            src_row, 
            src_col,
            dst_row, 
            dst_col,
            board->pieces[src_row][src_col],
            board->pieces[dst_row][dst_col]
        };
        return true;
    }
    return false;
}
//
// Find pawn moves:
// Check each diagonal for an enemy piece,
// and check in front for an empty square.
//
int get_possible_moves_pawn(Board *board, PieceColor color, int row, int col, Move moves[]) 
{
    int moves_found = 0;
    int target_row = (color == PIECE_COLOR_WHITE)? row - 1 : row + 1;

    // should never be true once promoting is implemented
    if (target_row < 0 || target_row > 7) 
    {
        return 0;
    }

    // check the three squares in front
    int result;
    
    // check side 1 for enemy piece
    if (col - 1 > 0) 
    {
        result = target_state(board, target_row, col - 1, color);
        if (result == ENEMY)
        {
            if (add_if_valid_move(board, col, row, col - 1, target_row, moves, moves_found))
            {
                moves_found++;
            }
            
        }
    }

    // check side 2 for enemy piece
    if (col + 1 < 8) 
    {
        result = target_state(board, target_row, col + 1, color);
        if (result == ENEMY)
        {
            if (add_if_valid_move(board, col, row, col + 1, target_row, moves, moves_found))
            {
                moves_found++;
            }
        }
    }

    // check in front for empty space
    result = target_state(board, target_row, col, color);
    if (result == EMPTY) 
    {
        if (add_if_valid_move(board, col, row, col, target_row, moves, moves_found))
        {
            moves_found++;
        }
    }

    // SPECIAL MOVES:
    // First move pawn can move 2 squares ahead
        // if white row = 6
        // if black row = 1
    if (color == PIECE_COLOR_WHITE && row == 6 && target_state(board, row - 2, col, color) == EMPTY)
    {
        if (add_if_valid_move(board, col, row, col, row - 2, moves, moves_found))
        {
            moves_found++;
        }
    }
    if (color == PIECE_COLOR_BLACK && row == 1 && target_state(board, row + 2, col, color) == EMPTY)
    {
        if (add_if_valid_move(board, col, row, col, row + 2, moves, moves_found))
        {
            moves_found++;
        }
    }
    
    return moves_found;
}
//
// Find rook moves:
// Walk each axis until you find the first piece.
//
int get_possible_moves_rook(Board *board, PieceColor color, int row, int col, Move moves[]) 
{
    int moves_found = 0;

    // move in positive col direction
    for (int i = col + 1; i < 8; i++) 
    {
        int result = target_state(board, row, i, color);
        if (result == TAKEN) break;
        if (add_if_valid_move(board, col, row, i, row, moves, moves_found))
        {
            moves_found++;
        }
        if (result == ENEMY) break;
    }

    // move in negative col direction
    for (int i = col - 1; i > -1; i--) 
    {
        int result = target_state(board, row, i, color);
        if (result == TAKEN) break;
        if (add_if_valid_move(board, col, row, i, row, moves, moves_found))
        {
            moves_found++;
        }
        if (result == ENEMY) break;
    }

    // move in positive row direction
    for (int i = row + 1; i < 8; i++) 
    {
        int result = target_state(board, i, col, color);
        if (result == TAKEN) break;
        if (add_if_valid_move(board, col, row, col, i, moves, moves_found))
        {
            moves_found++;
        }
        if (result == ENEMY) break;
    }

    // move in negative row direction
    for (int i = row - 1; i > -1; i--) 
    {
        int result = target_state(board, i, col, color);
        if (result == TAKEN) break;
        if (add_if_valid_move(board, col, row, col, i, moves, moves_found))
        {
            moves_found++;
        }
        if (result == ENEMY) break;
    }

    return moves_found;
}
//
// Find bishop moves:
// Walk each diagonal until you find the first piece.
//
int get_possible_moves_bishop(Board *board, PieceColor color, int row, int col, Move moves[]) 
{
    int moves_found = 0;
    int distance;
    
    // move right-down
    distance = (8-col) < (8-row)? 
               (8-col) : (8-row);

    for (int i = 1; i <= distance; i++) 
    {
        int target_row = row + i;
        int target_col = col + i;

        int result = target_state(board, target_row, target_col, color);

        if (result == TAKEN) break;
        if (add_if_valid_move(board, col, row, target_col, target_row, moves, moves_found))
        {
            moves_found++;
        }
        if (result == ENEMY) break;
    }

    // move right-up
    distance = (8-col) < (row)? 
               (8-col) : (row);

    for (int i = 1; i <= distance; i++) 
    {
        int target_row = row - i;
        int target_col = col + i;

        int result = target_state(board, target_row, target_col, color);

        if (result == TAKEN) break;
        if (add_if_valid_move(board, col, row, target_col, target_row, moves, moves_found))
        {
            moves_found++;
        }
        if (result == ENEMY) break;
    }

    // move left-down
    distance = (col) < (8-row)? 
               (col) : (8-row);

    for (int i = 1; i <= distance; i++) 
    {
        int target_row = row + i;
        int target_col = col - i;

        int result = target_state(board, target_row, target_col, color);

        if (result == TAKEN) break;
        if (add_if_valid_move(board, col, row, target_col, target_row, moves, moves_found))
        {
            moves_found++;
        }
        if (result == ENEMY) break;
    }

    // move left-up
    distance = (col) < (row)? 
               (col) : (row);

    for (int i = 1; i <= distance; i++) 
    {
        int target_row = row - i;
        int target_col = col - i;

        int result = target_state(board, target_row, target_col, color);

        if (result == TAKEN) break;
        if (add_if_valid_move(board, col, row, target_col, target_row, moves, moves_found))
        {
            moves_found++;
        }
        if (result == ENEMY) break;
    }

    return moves_found;
}
//
// Find queen moves:
// Combine rook moves and bishop moves.
//
int get_possible_moves_queen(Board *board, PieceColor color, int row, int col, Move moves[])
{
    int found_rook_moves = get_possible_moves_rook(board, color, row, col, moves);
    int found_bishop_moves = get_possible_moves_bishop(board, color, row, col, moves + found_rook_moves);

    return found_rook_moves + found_bishop_moves;
}

//
// Find knight moves:
// Check that each square from each offset is open or has an enemy piece.
//
int get_possible_moves_knight(Board *board, PieceColor color, int row, int col, Move moves[]) 
{
    int moves_found = 0;
    piece_t piece = board->pieces[row][col];

    for (int i = 0; i < 8; i++) 
    {
        int target_col = col + knight_move_offsets[i][0];
        int target_row = row + knight_move_offsets[i][1];

        if (target_col < 0 || target_col > 7 || target_row < 0 || target_row > 7) 
        {
            continue;
        }

        int result = target_state(board, target_row, target_col, color);

        if (result == EMPTY || result == ENEMY) 
        {
            if (add_if_valid_move(board, col, row, target_col, target_row, moves, moves_found))
            {
                moves_found++;
            }
        }
    }
    return moves_found;
}
//
// Use constant offsets for finding squares targeted
// by a knight because it's easier.
//
static int king_move_offsets[8][2] = {
    {-1, -1},
    {-1,  0},
    {-1,  1},
    { 0, -1},
    { 0,  1},
    { 1, -1},
    { 1,  0},
    { 1,  1}
};
//
//
//
//
int get_possible_moves_king(Board *board, PieceColor color, int row, int col, Move moves[]) 
{
    int moves_found = 0;
    piece_t piece = board->pieces[row][col];

    for (int i = 0; i < 8; i++) 
    {
        int target_col = col + king_move_offsets[i][0];
        int target_row = row + king_move_offsets[i][1];

        if (target_col < 0 || target_col > 7 || target_row < 0 || target_row > 7) 
        {
            continue;
        }

        int result = target_state(board, target_row, target_col, color);

        if (result == EMPTY || result == ENEMY) 
        {
            if (add_if_valid_move(board, col, row, target_col, target_row, moves, moves_found))
            {
                moves_found++;
            }
        }
    }
    // Castling

    // white
    if (color == PIECE_COLOR_WHITE && row == 7 && col == 4) {
        piece_t castle = board->pieces[7][7];
        if (PIECE_TYPE(castle) == ROOK && PIECE_COLOR(castle) == PIECE_COLOR_WHITE
            && target_state(board, 7, 5, color) == EMPTY
            && target_state(board, 7, 6, color) == EMPTY) {
            
            if (!board->team_in_check || !simulate_for_check(*board, col, row, 7, 6))
            {
                moves[moves_found++] = (Move) {
                    row,
                    col,
                    7,
                    6,
                    piece,
                    board->pieces[7][6]
                };
            }
        }
        piece_t far_castle = board->pieces[7][0];
        if (PIECE_TYPE(far_castle) == ROOK && PIECE_COLOR(far_castle) == PIECE_COLOR_WHITE
            && target_state(board, 7, 1, color) == EMPTY
            && target_state(board, 7, 2, color) == EMPTY
            && target_state(board, 7, 3, color) == EMPTY) {
 
            moves[moves_found++] = (Move) {
                row,
                col,
                7,
                2,
                piece,
                board->pieces[7][2]
            };
        }
    // black
    } else if (color == PIECE_COLOR_BLACK && row == 0 && col == 4) {

        piece_t castle = board->pieces[0][7];
        if (PIECE_TYPE(castle) == ROOK && PIECE_COLOR(castle) == PIECE_COLOR_BLACK
            && target_state(board, 0, 5, color) == EMPTY
            && target_state(board, 0, 6, color) == EMPTY) {
            moves[moves_found++] = (Move) {
                row,
                col,
                0,
                6,
                piece,
                board->pieces[0][6]
            };
        }
        piece_t far_castle = board->pieces[0][0];
        if (PIECE_TYPE(far_castle) == ROOK && PIECE_COLOR(far_castle) == PIECE_COLOR_BLACK
            && target_state(board, 0, 1, color) == EMPTY
            && target_state(board, 0, 2, color) == EMPTY
            && target_state(board, 0, 3, color) == EMPTY) {

            moves[moves_found++] = (Move) {
                row,
                col,
                0,
                2,
                piece,
                board->pieces[0][2]
            };
        }
    }
    return moves_found;
}

void print_piece_count(Board* board)
{
    printf("White pawns: %d\n", board->num_white_pawns);
    printf("Black pawns: %d\n", board->num_black_pawns);
    printf("White knights: %d\n", board->num_white_knights);
    printf("Black knights: %d\n", board->num_black_knights);
    printf("White bishops: %d\n", board->num_white_bishops);
    printf("Black bishops: %d\n", board->num_black_bishops);
    printf("White rooks: %d\n", board->num_white_rooks);
    printf("Black rooks: %d\n", board->num_black_rooks);
    printf("White queens: %d\n", board->num_white_queens);
    printf("Black queens: %d\n", board->num_black_queens);
}