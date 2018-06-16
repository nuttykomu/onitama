#include "Card.h"
#include "Move.h"

// A pre-computed table of all possible moves:
//  [Input] card index | start position index.
// [Output] bitboard encoding of end position indices.
const int CARD_COUNT = 16;
const int BOARD_SPACES = 25;
uint32_t MOVES[CARD_COUNT][BOARD_SPACES];

void precompute_moves() {
    for (int card = 0; card < CARD_COUNT; card++) {
        for (int start = 0; start < BOARD_SPACES; start++) {
            // initialize bitboard.
            uint32_t bitboard = 0x0000'0000;
            for (auto move : CARD_LIST[card].moves) {
                // generate.
                int shift_x = -move.x;
                int shift_y = move.y * 5;
                int end = start + shift_x + shift_y;
                // test.
                int start_row = start / 5;
                int end_row = (start + shift_x) / 5;
                bool valid_shift_x = start_row == end_row;
                bool valid_shift_y = end >= 0 && end < BOARD_SPACES;
                // update bitboard.
                if (valid_shift_x && valid_shift_y) {
                    bitboard |= 1 << end;
                }
            }
            // cache bitboard.
            MOVES[card][start] = bitboard;
        }
    }
}