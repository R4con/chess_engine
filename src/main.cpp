#include "board.h"
#include <iostream>
#include <bitset>

int main() 
{
    Board board_obj;
    uint8_t pos = 27;
    board_obj.display_raw_board( board_obj.get_attack_pattern(Queen, White, pos), 1ULL << pos );
    
    //board_obj.display_raw_board( board_obj.get_move_pattern(Bishop, White, pos), 1ULL << pos );    
}