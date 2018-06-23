#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <cstdint>

#include "Color.h"

class Board {
public:
    Board();
    Board clone();
    std::array<int, 5> get_positions(Color color);
//private:
    uint32_t master[2];
    uint32_t pawns[2];
};

// Bit-manipulation black magic...
std::array<int, 5> get_bit_indices(uint32_t);

#endif