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
        void display_raw_board(uint64_t board, uint64_t mask = 0ULL); // Displays the given board to std::cout.
        std::string get_board_fen();    // Get current board in fen notation.

    //private:  //! Just for Testing!
        // Private Vars
        // bitboard for pieces Pawn, Knight, Bishop, Rook, Queen, King
        const uint8_t bitboard_size = 6;
        Bitboard* bitboard_w;
        Bitboard* bitboard_b;

        ChessColor active_color;

        // TODO change to move bitboard
        bool allowed_to_castle[4]; // 0: white Kingside,1: white Queenside,2: black Kingside,3: black Queenside
        bool possible_en_passant[2]; //0: white, 1:black

        // Private Methods
        Bitboard* init_default(ChessColor color);
        uint64_t get_move_pattern(ChessPiece piece, ChessColor color, uint8_t pos);
        uint64_t get_attack_pattern(ChessPiece piece, ChessColor color, uint8_t pos);
};

#endif