#include "board.h"
#include <iostream>
#include <bitset>

int main() 
{
    Board board_obj;

    board_obj.display_raw_board( board_obj.get_move_pattern(Rook, White, 15) );    
}