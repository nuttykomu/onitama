#include <ctime>
#include <random>

#include "Card.h"
#include "State.h"

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
    std::uniform_int_distribution<int> draw(0, 15);

    for (int i = 0; i < 5; i++) {
        state.cards |= draw(rng) << (i * 4);
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

int *getBluePositions(GameState state) {

    // ╔════════════════════════════════╗
    // ║ TODO: Implement this function. ║
    // ╚════════════════════════════════╝

}

int *getRedPositions(GameState state) {

    // ╔════════════════════════════════╗
    // ║ TODO: Implement this function. ║
    // ╚════════════════════════════════╝

}

bool blueWon(GameState state) {
    const int RED_TEMPLE_ARCH_POSITION = 22;
    const int BLUE_MASTER_POSITION = 1;
    const int RED_MASTER_STATUS = 30;

    // 🌊 Way of the Stream.
    uint64_t blueMasterPositionMask = 0b11111 << BLUE_MASTER_POSITION;
    uint64_t blueMasterPosition = (state.pieces & blueMasterPositionMask) >> BLUE_MASTER_POSITION;
    bool blueMasterReachedTemple = blueMasterPosition == RED_TEMPLE_ARCH_POSITION;

    // 🗻 Way of the Stone.
    bool redMasterCaptured = state.pieces & (1 << RED_MASTER_STATUS);
    return blueMasterReachedTemple | redMasterCaptured;
}

bool redWon(GameState state) {
    const int BLUE_TEMPLE_ARCH_POSITION = 2;
    const int RED_MASTER_POSITION = 31;

    // 🌊 Way of the Stream.
    uint64_t redMasterPositionMask = 0b11111LL << RED_MASTER_POSITION;
    uint64_t redMasterPosition = (state.pieces & redMasterPositionMask) >> RED_MASTER_POSITION;
    bool redMasterReachedTemple = redMasterPosition == BLUE_TEMPLE_ARCH_POSITION;

    // 🗻 Way of the Stone.
    bool blueMasterCaptured = state.pieces & 1;
    return redMasterReachedTemple | blueMasterCaptured;
}