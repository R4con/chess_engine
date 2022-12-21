#ifndef BOARD_H
#define BOARD_H

#include <string>

enum ChessColor { White, Black };

enum ChessPiece { Pawn, Knight, Bishop, Rook, Queen, King };

struct Bitboard
{
    uint64_t pieceboard;
    ChessPiece piece;
    ChessColor color; // white=0, black=1
};


class Board {
    public:
        Board();    // Constructor
        ~Board();   // Destructor

        //Additional Methods
        void display_board();           // Display current board to std::cout.
        std::string get_board_fen();    // Get current board in fen notation.
        
    private:
        // Private Vars
        // bitboard for pieces Pawn, Knight, Bishop, Rook, Queen, King
        const uint8_t bitboard_size = 6;
        Bitboard* bitboard_w;
        Bitboard* bitboard_b;

        // Private Methods
        Bitboard* init_default(ChessColor color);

};

#endif