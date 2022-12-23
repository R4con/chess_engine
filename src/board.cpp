#include "board.h"
#include <iostream>
#include <string>
#include <bitset>

Board::Board() {
    this->bitboard_w = init_default(White);
    this->bitboard_b = init_default(Black);

    std::cout << "Board Obj created" << std::endl;
}

Board::~Board() {
    std::cout << "Board Obj destroyed" << std::endl;
    delete[] bitboard_w;
    delete[] bitboard_b;
}

void Board::display_board() {
    char output[64];
    std::fill_n(output, 64, '.');

    for (uint8_t j = 0; j < 64; j++)
    {
        for (uint8_t i = 0; i < this->bitboard_size; i++) 
        {
            if ((this->bitboard_w[i].pieceboard & (1ULL << j)) != 0) {
                switch (this->bitboard_w[i].piece)
                {
                case Pawn:
                    output[j]='O';
                    break;
                case Knight:
                    output[j]='N';
                    break;
                case Bishop:
                    output[j]='B';
                    break;
                case Rook:
                    output[j]='R';
                    break;
                case Queen:
                    output[j]='Q';
                    break;
                case King:
                    output[j]='K';
                    break;
                default:
                    throw "Error: bitboard for no piece cannot be handelt.";
                    break;
                }
            }
            if ((this->bitboard_b[i].pieceboard & (1ULL << j)) != 0) {
                switch (this->bitboard_b[i].piece)
                {
                case Pawn:
                    output[j]='o';
                    break;
                case Knight:
                    output[j]='n';
                    break;
                case Bishop:
                    output[j]='b';
                    break;
                case Rook:
                    output[j]='r';
                    break;
                case Queen:
                    output[j]='q';
                    break;
                case King:
                    output[j]='k';
                    break;
                default:
                    throw "Error: bitboard for no piece cannot be handelt.";
                    break;
                }
            }
        }
    }  

    std::string s_output;

    for (int8_t i = 7; i >=0; i--)
    {
        for (int8_t j = 0; j < 8; j++)
        {
            if(j != 7) {
                s_output.push_back(output[8*i+j]);
                s_output.push_back(' ');
            }
            else {
                s_output.push_back(output[8*i+j]);
                s_output.push_back('\n');
            }
            
        }
    }

    std::cout << s_output;  
}

void Board::display_raw_board(uint64_t board, uint64_t mask) {
    std::string output = "";

    for (int8_t i = 7; i >= 0; i--)
    {
        for (int8_t j = 0; j < 8; j++)
        {
            if (mask & (1ULL << 8*i+j)) {
                output.push_back((board & (1ULL << 8*i+j)) ? '#' : '*');
            }
            else {
                output.push_back((board & (1ULL << 8*i+j)) ? '1' : '0');
            }
            if(j != 7) {
                output.push_back(' ');
            }
            else {
                output.push_back('\n');
            }
        }
    }

    std::cout << output;
    std::cout << "- - - - - - - -" << std::endl;
}

std::string Board::get_board_fen() {
    std::string str_output = "Not Implementet yet!";

    return str_output;
}

uint64_t Board::get_move_pattern(ChessPiece piece, ChessColor color, uint8_t pos) {
    uint64_t pattern = 0;

    switch (piece)
    {
    case Pawn:
        if (!color) // white=0
        {
            if (pos <= 63-8) pattern |= (1ULL << (pos + 8));
            if (pos <= 15 && pos >= 8) pattern |= (1ULL << (pos + 16));    
        } else 
        {
            if (pos >= 8) pattern |= (1ULL << (pos - 8));
            if (pos >= 63-15 && pos <= 63-8) pattern |= (1ULL << (pos - 16));
        }
        
        break;
    case Knight:
        if (pos <= 63-17 && pos%8 <= 6) pattern |= (1ULL << (pos + 17));
        if (pos <= 63-15 && pos%8 >= 1) pattern |= (1ULL << (pos + 15));
        if (pos <= 63-10 && pos%8 <= 5) pattern |= (1ULL << (pos + 10));
        if (pos <= 63-6  && pos%8 >= 2) pattern |= (1ULL << (pos + 6));
        if (pos >= 17    && pos%8 >= 1) pattern |= (1ULL << (pos - 17));
        if (pos >= 15    && pos%8 <= 6) pattern |= (1ULL << (pos - 15));
        if (pos >= 10    && pos%8 >= 2) pattern |= (1ULL << (pos - 10));
        if (pos >= 6     && pos%8 <= 5) pattern |= (1ULL << (pos - 6));
        break;
    case Bishop:
        {   //code block to limit lifetime of vars
            uint64_t maindia = 0x8040201008040201ULL;
            int64_t diag = (pos&7) - (pos>>3);
            pattern |= (diag >= 0 ? maindia >> diag*8 : maindia << -diag*8);

            uint64_t maindia1 = 0x0102040810204080ULL;
            diag = 7 - (pos&7) - (pos>>3);
            pattern |= (diag >= 0 ? maindia1 >> diag*8 : maindia1 << (-diag*8));
            pattern ^= 1ULL << pos;
        }
        break;
    case Rook:
        pattern |= (0x00000000000000FFULL << (pos & 56));
        pattern |= (0x0101010101010101ULL << (pos & 7));
        pattern ^= 1ULL << pos;
        break;
    case Queen:
        {
            pattern |= (0x00000000000000FFULL << (pos & 56));
            pattern |= (0x0101010101010101ULL << (pos & 7));

            uint64_t maindia = 0x8040201008040201ULL;
            int64_t diag = (pos&7) - (pos>>3);
            pattern |= (diag >= 0 ? maindia >> diag*8 : maindia << -diag*8);

            uint64_t maindia1 = 0x0102040810204080ULL;
            diag = 7 - (pos&7) - (pos>>3);
            pattern |= (diag >= 0 ? maindia1 >> diag*8 : maindia1 << (-diag*8));
            pattern ^= 1ULL << pos;
        }
        break;
    case King:
        if (pos <= 63-8)                pattern |= (1ULL << (pos + 8));
        if (pos >= 8   )                pattern |= (1ULL << (pos - 8));
        if (pos <= 63-9 && pos%8 <= 6)  pattern |= (1ULL << (pos + 9));
        if (pos >= 9    && pos%8 >= 1)  pattern |= (1ULL << (pos - 9));
        if (pos <= 63-7 && pos%8 >= 1)  pattern |= (1ULL << (pos + 7));
        if (pos >= 7    && pos%8 <= 6)  pattern |= (1ULL << (pos - 7));
        if (pos%8 <= 6)                 pattern |= (1ULL << (pos + 1));
        if (pos%8 >= 1)                 pattern |= (1ULL << (pos - 1));
        break;
    default:
        throw "Error: Attack Move cannot be generated for no piece!";
        break;
    }

    return pattern;
}

uint64_t Board::get_attack_pattern(ChessPiece piece, ChessColor color, uint8_t pos) {
    uint64_t pattern = 0;
    uint64_t mov_pattern = get_move_pattern(piece, color, pos);
    uint64_t blockers = 0;

    for (uint8_t i = 0; i < 6; i++)
    {
        blockers |= this->bitboard_w[i].pieceboard;
        blockers |= this->bitboard_b[i].pieceboard;
    }

    pattern = blockers ^ mov_pattern;

    return pattern;
}

Bitboard* Board::init_default(ChessColor color) {
    // color: 0=white, 1=black
    Bitboard* tmp_board = new Bitboard[6];

    tmp_board[0].color = color;
    tmp_board[0].piece = Pawn;
    tmp_board[0].pieceboard = color==White ? 0b11111111ULL << 8 : 0b11111111ULL << 48;

    tmp_board[1].color = color;
    tmp_board[1].piece = Knight;
    tmp_board[1].pieceboard = color==White ? 0b01000010ULL : 0b01000010ULL << 56;

    tmp_board[2].color = color;
    tmp_board[2].piece = Bishop;
    tmp_board[2].pieceboard = color==White ? 0b00100100ULL : 0b00100100ULL << 56;

    tmp_board[3].color = color;
    tmp_board[3].piece = Rook;
    tmp_board[3].pieceboard = color==White ? 0b10000001ULL : 0b10000001ULL << 56;

    tmp_board[4].color = color;
    tmp_board[4].piece = Queen;
    tmp_board[4].pieceboard = color==White ? 0b00010000ULL : 0b00010000ULL << 56;

    tmp_board[5].color = color;
    tmp_board[5].piece = King;
    tmp_board[5].pieceboard = color==White ? 0b00001000ULL : 0b00001000ULL << 56;

    return tmp_board;
}