#include <algorithm>
#include <array>
#include <string>

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

std::ostream& operator<<(std::ostream& os, const State& state) {
    std::string lines[7];
    lines[0] = "  +---------------+";
    lines[1] = "  |";
    lines[2] = "  |";
    lines[3] = "  |";
    lines[4] = "  |";
    lines[5] = "  |";
    lines[6] = "  +---------------+";

    for (int i = 0; i < 25; i++) {
        int index = i / 5 + 1;
        if      (state.board.master[🔵] & (1 << i)) lines[index] += " M ";
        else if (state.board.master[🔴] & (1 << i)) lines[index] += " m ";
        else if (state.board.pawns[🔵] & (1 << i))  lines[index] += " P ";
        else if (state.board.pawns[🔴] & (1 << i))  lines[index] += " p ";
        else lines[index] += " . ";
    }

    lines[1] += "|  BLUE:  [" + state.hand[🔵][0].name + "][" + state.hand[🔵][1].name + "]";
    lines[2] += "|  RED:   [" + state.hand[🔴][0].name + "][" + state.hand[🔴][1].name + "]";
    lines[3] += "|  EXTRA: [" + state.extra_card.name + "]";
    lines[4] += "|";
    lines[5] += "|  It is ";
    lines[5] += (state.turn == 🔵 ? "BLUE" : "RED");
    lines[5] += "'s turn to move...";

    for (int i = 0; i < 7; i++) {
        os << lines[i] << std::endl;
    }

    return os;
}