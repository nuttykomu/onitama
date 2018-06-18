#include "Board.h"

/**
 * The board is represented as four 25-bit bitboards (blue master, red master,
 * blue pawns, red pawns) that provide a mapping from of bit positions to
 * board squares. E.g.
 * 
 *    ╔════════════════╗   ╔════════════════╗
 *    ║  0  1  2  3  4 ║   ║ BP BP BM BP BP ║
 *    ║  5  6  7  8  9 ║   ║ __ __ __ __ __ ║
 *    ║ 10 11 12 13 14 ║ = ║ __ __ __ __ __ ║
 *    ║ 15 16 17 18 19 ║   ║ __ __ __ __ __ ║
 *    ║ 20 21 22 23 24 ║   ║ RP RP RM RP RP ║
 *    ╚════════════════╝   ╚════════════════╝
 * 
 * Above is the combined bitboard representing the initial starting board
 * state; resulting from applying a bitwise-OR (|) to all of the bitboards:
 * BM | BP | RM | RP. The least to most significant bit ranges from 0 to 24.
 */

#include "Color.h"

Board::Board() {
    this->master[🔵] = 1 << 2;
    this->master[🔴] = 1 << 22;
    this->pawns[🔵] = (1 << 0) | (1 << 1) | (1 << 3) | (1 << 4);
    this->pawns[🔴] = (1 << 20) | (1 << 21) | (1 << 23) | (1 << 24);
}

Board Board::clone() {
    Board clone;
    clone.master[🔵] = this->master[🔵];
    clone.master[🔴] = this->master[🔴];
    clone.pawns[🔵] = this->pawns[🔵];
    clone.pawns[🔴] = this->pawns[🔴];
    return clone;
}

std::vector<int> Board::get_positions(Color color) {
    auto bitboard = this->master[color] | this->pawns[color];
    return get_bit_indices(bitboard);
}

const int debruijn_table[32] = {
     0,  1, 28,  2, 29, 14, 24,  3,
    30, 22, 20, 15, 25, 17,  4,  8, 
    31, 27, 13, 23, 21, 19, 16,  7,
    26, 12, 18,  6, 11,  5, 10,  9
};

// Find the indices of all of the set bits in the bitboard, 'bb'.
// This function makes use of de Bruijn sequences (⚫✨) to quickly find
// the index of the next least significant bit in the bitboard.
//
// https://en.wikipedia.org/wiki/De_Bruijn_sequence
std::vector<int> get_bit_indices(uint32_t bb) {
    std::vector<int> positions;
    while (bb != 0) {
        int position = debruijn_table[((bb & -bb) * 0x077CB531U) >> 27];
        positions.push_back(position);
        bb &= ~(1 << position);
    }
    return positions;
}