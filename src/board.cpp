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
    std::fill_n(output, 64, ' ');

    for (uint8_t j = 0; j < 64; j++)
    {
        for (uint8_t i = 0; i < this->bitboard_size; i++) 
        {
            if ((this->bitboard_w[i].pieceboard & (1LL << j)) != 0) {
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
            if ((this->bitboard_b[i].pieceboard & (1LL << j)) != 0) {
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

    for (uint8_t i = 0; i < 64; i++)
    {
        //std::cout << std::bitset<8>(output[i]) << std::endl;
    }
    
    

    std::string s_output;

    for (uint8_t i = 0; i < 8; i++)
    {
        for (uint8_t j = 0; j < 8; j++)
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

std::string Board::get_board_fen() {
    std::string str_output = "Not Implementet yet!";

    return str_output;
}

uint64_t Board::get_attack_pattern(ChessPiece piece, ChessColor color,uint8_t pos) {
    uint64_t pattern = 0;
    int8_t color_sgn = color ? -1 : 1;

    switch (piece)
    {
    case Pawn:
        pattern |= 1 << (pos + 8 * color_sgn);
        pattern |= 1 << (pos + 16 * color_sgn);
        break;
    case Knight:
        pattern |= 1 << (pos + 17);
        pattern |= 1 << (pos + 15);
        pattern |= 1 << (pos + 10);
        pattern |= 1 << (pos + 6);
        pattern |= 1 << (pos - 17);
        pattern |= 1 << (pos - 15);
        pattern |= 1 << (pos - 10);
        pattern |= 1 << (pos - 6);
        break;
    case Bishop:
        
        break;
    case Rook:
        pattern |= 0x00000000000000FF << 8 * pos/8;
        pattern |= 
        break;
    case Queen:
        
        break;
    case King:
        pattern |= 1 << (pos + 8);
        pattern |= 1 << (pos - 8);
        pattern |= 1 << (pos + 9);
        pattern |= 1 << (pos - 9);
        pattern |= 1 << (pos + 7);
        pattern |= 1 << (pos - 7);
        pattern |= 1 << (pos + 1);
        pattern |= 1 << (pos - 1);
        break;
    default:
        throw "Error: Attack Move cannot be generated for no piece!";
        break;
    }
}

Bitboard* Board::init_default(ChessColor color) {
    // color: 0=white, 1=black
    Bitboard* tmp_board = new Bitboard[6];

    tmp_board[0].color = color;
    tmp_board[0].piece = Pawn;
    tmp_board[0].pieceboard = color==White ? 0b11111111LL << 48 : 0b11111111LL << 8;

    tmp_board[1].color = color;
    tmp_board[1].piece = Knight;
    tmp_board[1].pieceboard = color==White ? 0b01000010LL << 56 : 0b01000010LL;

    tmp_board[2].color = color;
    tmp_board[2].piece = Bishop;
    tmp_board[2].pieceboard = color==White ? 0b00100100LL << 56 : 0b00100100LL;

    tmp_board[3].color = color;
    tmp_board[3].piece = Rook;
    tmp_board[3].pieceboard = color==White ? 0b10000001LL << 56 : 0b10000001LL;

    tmp_board[4].color = color;
    tmp_board[4].piece = Queen;
    tmp_board[4].pieceboard = color==White ? 0b00010000LL << 56 : 0b00010000LL;

    tmp_board[5].color = color;
    tmp_board[5].piece = King;
    tmp_board[5].pieceboard = color==White ? 0b00001000LL << 56 : 0b00001000LL;

    return tmp_board;
}