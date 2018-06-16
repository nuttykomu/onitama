#ifndef MOVE_H
#define MOVE_H

#include <cstdint>

struct Move {
    int card;
    int start;
    int end;
};

void precompute_moves();
extern uint32_t MOVES[16][25];

#endif