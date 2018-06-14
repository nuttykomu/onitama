#include <ctime>
#include <random>
#include <set>
#include <vector>

#include "Card.h"
#include "State.h"

const int BLUE = 0;
const int RED = 1;

GameState getNewGameState() {
    GameState state = {};

    // 1. Set up the pieces on the board.
    state.pieces |= 0b00010'0LL << (0 * 6);  // Position 02, Not Captured [BLUE MASTER]
    state.pieces |= 0b00000'0LL << (1 * 6);  // Position 00, Not Captured [BLUE PAWN]
    state.pieces |= 0b00001'0LL << (2 * 6);  // Position 01, Not Captured [BLUE PAWN]
    state.pieces |= 0b00011'0LL << (3 * 6);  // Position 03, Not Captured [BLUE PAWN]
    state.pieces |= 0b00100'0LL << (4 * 6);  // Position 04, Not Captured [BLUE PAWN]
    state.pieces |= 0b10110'0LL << (5 * 6);  // Position 22, Not Captured [RED MASTER]
    state.pieces |= 0b10100'0LL << (6 * 6);  // Position 20, Not Captured [RED PAWN]
    state.pieces |= 0b10101'0LL << (7 * 6);  // Position 21, Not Captured [RED PAWN]
    state.pieces |= 0b10111'0LL << (8 * 6);  // Position 23, Not Captured [RED PAWN]
    state.pieces |= 0b11000'0LL << (9 * 6);  // Position 24, Not Captured [RED PAWN]

    // 2. Draw five move cards randomly.
    std::default_random_engine rng((unsigned int)time(0));
    std::uniform_int_distribution<int> generateCard(0, 15);
    std::set<int> cardsDrawn;

    while (cardsDrawn.size() < 5) {
        cardsDrawn.insert(generateCard(rng));
    }

    int i = 0;
    for (int card : cardsDrawn) {
        state.cards |= card << (i++ * 4);
    }

    // 3. Determine who goes first.
    const int EXTRA_CARD_OFFSET = 16;
    int extraCardMask = 0b1111 << EXTRA_CARD_OFFSET;
    int extraCardIndex = (state.cards & extraCardMask) >> EXTRA_CARD_OFFSET;
    state.turn = CardList[extraCardIndex].color;

    return state;
}

GameState applyMove(GameState state, int move) {

    // ╔════════════════════════════════╗
    // ║ TODO: Implement this function. ║
    // ╚════════════════════════════════╝

}

Move *getMoves(GameState state) {

    // ╔════════════════════════════════╗
    // ║ TODO: Implement this function. ║
    // ╚════════════════════════════════╝

}

std::vector<int> getPawnPositions(GameState state, int color) {
    std::vector<int> positions;
    int colorOffset = (color == BLUE) ? 6 : 36;

    for (int i = 0; i < 4; i++) {
        bool isCaptured = state.pieces & (1 << colorOffset + i * 6);
        if (!isCaptured) {
            uint64_t positionMask = 0b11111LL << (colorOffset + i * 6 + 1);
            uint64_t position = (state.pieces & positionMask) >> (colorOffset + i * 6 + 1);
            positions.push_back(position);
        }
    }

    return positions;
}

int getMasterPosition(GameState state, int color) {
    int positionOffset = (color == BLUE) ? 1 : 31;
    uint64_t positionMask = 0b11111LL << positionOffset;
    return (state.pieces & positionMask) >> positionOffset;
}

std::vector<Card> getCards(GameState state, int color) {
    std::vector<Card> cards;
    int colorOffset = (color == BLUE) ? 0 : 8;
    for (int i = 0; i < 2; i++) {
        uint32_t cardMask = 0b1111 << (colorOffset + i * 4);
        uint32_t cardIndex = (state.cards & cardMask) >> (colorOffset + i * 4);
        cards.push_back(CardList[cardIndex]);
    }
    return cards;
}

Card getExtraCard(GameState state) {
    int offset = 16;
    uint32_t cardMask = 0b1111 << offset;
    uint32_t cardIndex = (state.cards & cardMask) >> offset;
    return CardList[cardIndex];
}

bool blueWon(GameState state) {
    bool blueMasterReachedTemple = getMasterPosition(state, BLUE) == 22;
    bool redMasterCaptured = state.pieces & (1 << 30);
    return blueMasterReachedTemple | redMasterCaptured;
}

bool redWon(GameState state) {
    bool redMasterReachedTemple = getMasterPosition(state, RED) == 2;
    bool blueMasterCaptured = state.pieces & 1;
    return redMasterReachedTemple | blueMasterCaptured;
}