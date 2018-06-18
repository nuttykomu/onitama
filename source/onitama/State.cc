#include <algorithm>
#include <array>

#include "Card.h"
#include "Color.h"
#include "Random.h"
#include "State.h"

void State::initialize() {
    std::array<int, 16> deck {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    std::shuffle(deck.begin(), deck.end(), RNG);
    this->hand[🔵][0] = CARD_LIST[deck[0]];
    this->hand[🔵][1] = CARD_LIST[deck[1]];
    this->hand[🔴][0] = CARD_LIST[deck[2]];
    this->hand[🔴][1] = CARD_LIST[deck[3]];
    this->extra_card = CARD_LIST[deck[4]];
    this->turn = this->extra_card.color;
}

State State::clone() {
    State clone;
    clone.board = this->board.clone();
    clone.hand[🔵][0] = this->hand[🔵][0];
    clone.hand[🔵][1] = this->hand[🔵][1];
    clone.hand[🔴][0] = this->hand[🔴][0];
    clone.hand[🔴][1] = this->hand[🔴][1];
    clone.extra_card = this->extra_card;
    return clone;
}