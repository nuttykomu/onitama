#ifndef STATE_H
#define STATE_H

#include "Board.h"
#include "Card.h"
#include "Color.h"

class State {
public:
    void initialize();
    State clone();
private:
    Board board;
    Card hand[2][2];
    Card extra_card;
    Color turn;
};

#endif