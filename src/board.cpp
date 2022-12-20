#include "board.h"
#include <iostream>
#include <string>

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
    char output[64] = {' '};
    
    for (int8_t j = 0; j < 64; j++)
    {
        for (int8_t i = 0; i < this->bitboard_size; i++) 
        {
            if (this->bitboard_b[i].pieceboard & 0b1 << j == 0b1) {
                switch (this->bitboard_b[i].piece)
                {
                case Pawn:
                    this->bitboard_b[i].color == White ? output[j]='o' : output[j]='O';
                    break;
                case Knight:
                    this->bitboard_b[i].color == White ? output[j]='n' : output[j]='N';
                    break;
                case Bishop:
                    this->bitboard_b[i].color == White ? output[j]='b' : output[j]='B';
                    break;
                case Rook:
                    this->bitboard_b[i].color == White ? output[j]='r' : output[j]='R';
                    break;
                case Queen:
                    this->bitboard_b[i].color == White ? output[j]='q' : output[j]='Q';
                    break;
                case King:
                    this->bitboard_b[i].color == White ? output[j]='p' : output[j]='P';
                    break;
                default:
                    throw "Error: bitboard for no piece cannot be handelt.";
                    break;
                }
            }
            if (this->bitboard_w[i].pieceboard & 0b1 << j == 0b1) {
                switch (this->bitboard_b[i].piece)
                {
                case Pawn:
                    this->bitboard_w[i].color == White ? output[j]='o' : output[j]='O';
                    break;
                case Knight:
                    this->bitboard_w[i].color == White ? output[j]='n' : output[j]='N';
                    break;
                case Bishop:
                    this->bitboard_w[i].color == White ? output[j]='b' : output[j]='B';
                    break;
                case Rook:
                    this->bitboard_w[i].color == White ? output[j]='r' : output[j]='R';
                    break;
                case Queen:
                    this->bitboard_w[i].color == White ? output[j]='q' : output[j]='Q';
                    break;
                case King:
                    this->bitboard_w[i].color == White ? output[j]='p' : output[j]='P';
                    break;
                default:
                    throw "Error: bitboard for no piece cannot be handelt.";
                    break;
                }
            }
        }
    }

    std::string s_output;

    for (int8_t i = 0; i < 8; i++)
    {
        for (int8_t j = 0; j < 8; j++)
        {
            if(j != 7) {
                s_output += output[8*i+j] + ' ';
            }
            else {
                s_output += output[8*i+j] + '\n';
            }
            
        }
    }

    std::cout << s_output;  
}

Bitboard* Board::init_default(ChessColor color) {
    // color: 0=white, 1=black
    Bitboard* tmp_board = new Bitboard[6];

    tmp_board[0].color = color;
    tmp_board[0].piece = Pawn;
    tmp_board[0].pieceboard = color==White ? (uint64_t)0b11111111 << 48 : (uint64_t)0b11111111 << 8;

    tmp_board[1].color = color;
    tmp_board[1].piece = Knight;
    tmp_board[1].pieceboard = color==White ? (uint64_t)0b01000010 << 56 : (uint64_t)0b01000010;

    tmp_board[2].color = color;
    tmp_board[2].piece = Bishop;
    tmp_board[2].pieceboard = color==White ? (uint64_t)0b00100100 << 56 : (uint64_t)0b00100100;

    tmp_board[3].color = color;
    tmp_board[3].piece = Rook;
    tmp_board[3].pieceboard = color==White ? (uint64_t)0b10000001 << 56 : (uint64_t)0b10000001;

    tmp_board[4].color = color;
    tmp_board[4].piece = Queen;
    tmp_board[4].pieceboard = color==White ? (uint64_t)0b00010000 << 56 : (uint64_t)0b00010000;

    tmp_board[5].color = color;
    tmp_board[5].piece = King;
    tmp_board[5].pieceboard = color==White ? (uint64_t)0b00001000 << 56 : (uint64_t)0b00001000;

    return tmp_board;
}