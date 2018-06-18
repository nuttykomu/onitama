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