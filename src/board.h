#ifndef BOARD_H
#define BOARD_H

#include <string>

class Board {
    public:
        Board();    // Constructor
        ~Board();   // Destructor

        //Additional Methods
        void Say_Hello(std::string Hello);

    private:
        // Private Vars
        char tmp;
        // Private Methods

};

#endif