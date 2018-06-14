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
    uint32_t index;
    std::vector<M> moves;
};

extern std::vector<Card> CardList;

#endif