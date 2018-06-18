#ifndef BOARD_H
#define BOARD_H

#include <cstdint>

class Board {
public:
    Board();
    Board clone();
    uint32_t master[2];
    uint32_t pawns[2];
};

#endif