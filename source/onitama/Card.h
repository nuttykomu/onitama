#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
#include <vector>

struct M {
    M(int32_t x, int32_t y) : x(x), y(y) { }
    int32_t x, y;
};

struct Card {
    std::string name;
    uint32_t color;
    std::vector<M> moves;
};

extern Card CardList[16];

#endif