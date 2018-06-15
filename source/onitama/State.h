#ifndef STATE_H
#define STATE_H

#include <vector>

#include "Card.h"

struct GameState {
    // 0 → Blue's turn to move.
    // 1 → Red's turn to move.
    uint32_t turn;

    // master[0] → Blue's master.
    // pawns[0]  → Blue's pawns.
    // master[1] → Red's master.
    // pawns[1]  → Red's pawns.
    std::vector<int> master[2];
    std::vector<int> pawns[2];

    // hand[0] → Blue's hand.
    // hand[1] → Red's hand.
    std::vector<Card *> hand[2];
    Card *extraCard;
};

struct Move {
    Card *card;
    uint32_t start;
    uint32_t end;
};

// Constants.
extern const int BLUE;
extern const int RED;

extern GameState getNewGameState();
extern bool hasVictory(GameState state, int color);

extern std::vector<Move> getMoves(GameState state);
extern GameState applyMove(GameState state, Move move);

extern std::vector<int> getPawnPositions(GameState state, int color);
extern int getMasterPosition(GameState state, int color);

extern std::vector<Card> getCards(GameState state, int color);
extern Card getExtraCard(GameState state);

#endif