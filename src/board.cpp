#include "board.h"
#include <iostream>
#include <string>

Board::Board() {
    std::cout << "Board Obj created" << std::endl;
    this->tmp = 'x';
}

Board::~Board() {
    std::cout << "Board Obj destroyed" << this->tmp << std::endl;
}

void Board::Say_Hello(std::string Hello) {
    std::cout <<  "Hello from a Method!" << std::endl << Hello << std::endl;
}
