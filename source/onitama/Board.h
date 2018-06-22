#ifndef BOARD_H
#define BOARD_H

#include <cstdint>
#include <vector>

#include "Color.h"

class Board {
public:
    Board();
    Board clone();
    int *get_positions(Color color);
//private:
    uint32_t master[2];
    uint32_t pawns[2];
};

// Bit-manipulation black magic...
int *get_bit_indices(uint32_t);

#endif