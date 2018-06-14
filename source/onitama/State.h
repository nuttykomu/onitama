#ifndef STATE_H
#define STATE_H

#include <vector>

#include "Card.h"

struct GameState {
    // Each pawn and master is encoded in `pieces` using 6 bits each:
    // 1 bit to store their state (captured or not captured?), and
    // 5 bits to store their location on the board.
    //
    //  [00][01-05] Blue Master
    //  [06][07-10] Blue Pawn
    //  ...
    //  [26][27-30] Red Master
    //  [31][32-35] Red Pawn
    //  ...
    uint64_t pieces;

    // Each of the players cards and the extra card are encoded using
    // 4 bits each. There are 16 move cards in total. The integer
    // representation of each 4-bit section maps to an index of the
    // lexicographically-ordered move card list.
    //
    //  [00-03] Blue Card
    //  [04-07] Blue Card
    //  [08-11] Red Card
    //  [12-15] Red Card
    //  [16-19] Extra Card
    uint32_t cards;

    // 0 → Blue's turn to move.
    // 1 → Red's turn to move.
    uint32_t turn;
};

struct Move {
    uint32_t card;
    uint32_t start;
    uint32_t end;
};

// Search predicate for finding moves in containers.
// Intended to be used with std::find_if.
// https://stackoverflow.com/a/590005
struct findMove {
    uint32_t card;
    uint32_t start;
    uint32_t end;

    findMove(Move move) : 
        card(move.card),
        start(move.start), 
        end(move.end) {}

    bool operator() (const Move& move) const {
        return move.card == card &&
               move.start == start &&
               move.end == end;
    }
};

extern GameState getNewGameState();
extern bool hasVictory(GameState state, int color);

extern std::vector<Move> getMoves(GameState state);
extern GameState applyMove(GameState state, Move move);

extern std::vector<int> getPawnPositions(GameState state, int color);
extern int getMasterPosition(GameState state, int color);

extern std::vector<Card> getCards(GameState state, int color);
extern Card getExtraCard(GameState state);

#endif