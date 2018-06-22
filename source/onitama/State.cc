#include <algorithm>
#include <array>
#include <iostream>
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
    clone.turn = this->turn;
    return clone;
}

std::vector<Move> State::get_moves() {
    const int INVALID_POSITION = 25;
    std::vector<Move> moves;
    moves.reserve(20);
    auto start = this->board.get_positions(this->turn);
    while (*start != INVALID_POSITION) {
        for (int i = 0; i < 2; i++) {
            Card &card = this->hand[this->turn][i];
            auto move_bitboard = MOVES[this->turn][card.index][*start];
            auto allies = this->board.master[this->turn] | this->board.pawns[this->turn];
            auto end = get_bit_indices(move_bitboard & ~allies);
            while (*end != INVALID_POSITION) {
                moves.push_back({card.index, *start, *end});
                end++;
            }
        }
        start++;
    }
    /**
     * "It is possible that you will find that you cannot use any of your cards
     * to make a legal move. If this happens — and only then — you must pass your
     * turn. None of your pawns will move. But like the river that constantly
     * flows, you cannot remain unchanged: you must still choose one of the two
     * cards in front of you, place it to the left of the playmat and rotate it,
     * then take the card from the right side of the board." — Rulebook
     */
    if (moves.size() == 0) {
        const int INVALID_POSITION = 25;
        moves.push_back({this->hand[this->turn][0].index, INVALID_POSITION, INVALID_POSITION});
        moves.push_back({this->hand[this->turn][1].index, INVALID_POSITION, INVALID_POSITION});
    }
    return moves;
}

void State::apply_move(Move move) {
    if (this->board.master[this->turn] & (1 << move.start)) {
        this->board.master[this->turn] &= ~(1 << move.start);
        this->board.master[this->turn] |= 1 << move.end;
    }
    else if (this->board.pawns[this->turn] & (1 << move.start)) {
        this->board.pawns[this->turn] &= ~(1 << move.start);
        this->board.pawns[this->turn] |= 1 << move.end;
    }
    for (int i = 0; i < 2; i++) {
        if (this->hand[this->turn][i].index == move.card) {
            std::swap(this->hand[this->turn][i], this->extra_card);
        }
    }
    this->turn = (this->turn == 🔵) ? 🔴 : 🔵;
}

bool State::has_victory(Color color) {
    // Way of the Stream...
    bool temple_reached =
        this->board.master[color] ==
        (color == 🔵 ? 1 << 22 : 1 << 2);

    // Way of the Stone...
    bool master_captured =
        (color == 🔵) ?
        (this->board.master[🔴] == 0) :
        (this->board.master[🔵] == 0);

    return temple_reached || master_captured;
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