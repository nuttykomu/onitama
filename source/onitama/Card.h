#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>

#include "Color.h"

struct Vector {
    int x, y;
    Vector(int x, int y)
        : x(x), y(y) {}
};

struct Card {
    int index;
    Color color;
    std::string name;
    std::vector<Vector> moves;
};

extern std::vector<Card> CARD_LIST;

#endif