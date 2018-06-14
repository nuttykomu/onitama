#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>

struct Vector {
    int32_t x;
    int32_t y;
};

struct Card {
    std::string name;
    uint32_t color;
    Vector moves[4];
};

extern Card CardList[16];

#endif