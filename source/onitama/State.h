#ifndef STATE_H
#define STATE_H

#include "Board.h"
#include "Card.h"
#include "Color.h"
#include "Move.h"

class State {
public:
    void initialize();
    State clone();
    std::vector<Move> get_moves();
    void apply_move(Move move);
    friend std::ostream& operator<<(std::ostream&, const State&);
//private:
    Board board;
    Card hand[2][2];
    Card extra_card;
    Color turn;
};

#endif