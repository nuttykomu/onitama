#include <ctime>
#include <random>

#include "State.h"

GameState getNewGameState() {
    GameState state = {};

    // 1. Set up the pieces on the board.
    state.pieces |= 0b00010'1LL << (0 * 6);  // Position 02, Not Captured [BLUE MASTER]
    state.pieces |= 0b00000'1LL << (1 * 6);  // Position 00, Not Captured [BLUE PAWN]
    state.pieces |= 0b00001'1LL << (2 * 6);  // Position 01, Not Captured [BLUE PAWN]
    state.pieces |= 0b00011'1LL << (3 * 6);  // Position 03, Not Captured [BLUE PAWN]
    state.pieces |= 0b00100'1LL << (4 * 6);  // Position 04, Not Captured [BLUE PAWN]
    state.pieces |= 0b10110'1LL << (5 * 6);  // Position 22, Not Captured [RED MASTER]
    state.pieces |= 0b10100'1LL << (6 * 6);  // Position 20, Not Captured [RED PAWN]
    state.pieces |= 0b10101'1LL << (7 * 6);  // Position 21, Not Captured [RED PAWN]
    state.pieces |= 0b10111'1LL << (8 * 6);  // Position 23, Not Captured [RED PAWN]
    state.pieces |= 0b11000'1LL << (9 * 6);  // Position 24, Not Captured [RED PAWN]

    // 2. Draw five move cards randomly.
    std::default_random_engine rng((unsigned int)time(0));
    std::uniform_int_distribution<int> draw(0, 15);

    for (int i = 0; i < 5; i++) {
        state.cards |= draw(rng) << (i * 4);
    }

    // 3. Determine who goes first.

    // ╔═════════════════════════════════════════════════════╗
    // ║ TODO: Implement this after implementing move cards. ║
    // ╚═════════════════════════════════════════════════════╝

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

    // ╔════════════════════════════════╗
    // ║ TODO: Implement this function. ║
    // ╚════════════════════════════════╝

}

bool redWon(GameState state) {

    // ╔════════════════════════════════╗
    // ║ TODO: Implement this function. ║
    // ╚════════════════════════════════╝

}