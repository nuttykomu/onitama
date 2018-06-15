#include <algorithm>
#include <array>
#include <ctime>
#include <random>
#include <vector>

#include "Card.h"
#include "State.h"

const int BLUE = 0;
const int RED = 1;

GameState getNewGameState() {
    GameState state = {};

    // 1. Set up the pieces on the board.
    state.master[BLUE].push_back(2);
    state.pawns[BLUE].push_back(0);
    state.pawns[BLUE].push_back(1);
    state.pawns[BLUE].push_back(3);
    state.pawns[BLUE].push_back(4);
    state.master[RED].push_back(22);
    state.pawns[RED].push_back(20);
    state.pawns[RED].push_back(21);
    state.pawns[RED].push_back(23);
    state.pawns[RED].push_back(24);

    // 2. Draw five move cards randomly.
    std::array<int, 16> random { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    shuffle(random.begin(), random.end(), std::default_random_engine((unsigned int)time(0)));
    state.hand[BLUE].push_back(&CardList[random[0]]);
    state.hand[BLUE].push_back(&CardList[random[1]]);
    state.hand[RED].push_back(&CardList[random[2]]);
    state.hand[RED].push_back(&CardList[random[3]]);
    state.extraCard = &CardList[random[4]];

    // 3. Determine who goes first.
    state.turn = state.extraCard->color;

    return state;
}

bool hasVictory(GameState state, int color) {
    const int TEMPLE_ARCH_POSITION = (color == BLUE) ? 22 : 2;
    const int otherColor = (color == BLUE) ? RED : BLUE;
    bool reachedTemple = state.master[color].size() != 0 && state.master[color][0] == TEMPLE_ARCH_POSITION;
    bool capturedMaster = state.master[otherColor].size() == 0;
    return reachedTemple || capturedMaster;
}

std::vector<Move> getMoves(GameState state) {
    // Get all starting positions.
    std::vector<int> positions;
    positions.insert(positions.end(), state.master[state.turn].begin(), state.master[state.turn].end());
    positions.insert(positions.end(), state.pawns[state.turn].begin(), state.pawns[state.turn].end());
    
    std::vector<Move> moves;
    if (!hasVictory(state, BLUE) && !hasVictory(state, RED)) {
        // For each position, enumerate all possible candidate moves.
        for (int position : positions) {
            for (Card *card : state.hand[state.turn]) {
                for (M move : card->moves) {

                    // If RED turn, rotate the board.
                    int startPosition = position;
                    if (state.turn == RED) {
                        startPosition = 24 - position;
                    }

                    // Generate candidate move.
                    int shiftX = -move.x;
                    int shiftY = move.y * 5;
                    int endPosition = startPosition + shiftX + shiftY;

                    // Test candidate move for valid end position.
                    int startRow = startPosition / 5;
                    int endRow = (startPosition + shiftX) / 5;
                    bool validXShift = startRow == endRow;
                    bool validYShift = endPosition >= 0 && endPosition < 25;

                    // Rotate the board back to original orientation.
                    if (state.turn == RED) {
                        startPosition = 24 - startPosition;
                        endPosition = 24 - endPosition;
                    }

                    // Test candidate move for friendly fire.
                    auto iterator = std::find(positions.begin(), positions.end(), endPosition);
                    bool noFriendlyFire = iterator == positions.end();

                    if (validXShift && validYShift && noFriendlyFire) {
                        Move move = {
                            /* Card:  */ card,
                            /* Start: */ (unsigned)startPosition,
                            /* End:   */ (unsigned)endPosition
                        };
                        moves.push_back(move);
                    }
                }
            }
        }
    }
    return moves;
}

GameState applyMove(GameState state, Move move) {
    const int enemy = (state.turn == BLUE) ? RED : BLUE;

    // Update the piece position.
    std::replace(
        state.master[state.turn].begin(),
        state.master[state.turn].end(),
        move.start,
        move.end
    );
    
    std::replace(
        state.pawns[state.turn].begin(),
        state.pawns[state.turn].end(),
        move.start,
        move.end
    );

    // Capture the enemy piece (if applicable).
    state.master[enemy].erase(
        std::remove(
            state.master[enemy].begin(),
            state.master[enemy].end(),
            move.end),
        state.master[enemy].end()
    );

    state.pawns[enemy].erase(
        std::remove(
            state.pawns[enemy].begin(),
            state.pawns[enemy].end(),
            move.end),
        state.pawns[enemy].end()
    );

    // Swap the used card with the extra card.
    for (int i = 0; i < 2; i++) {
        if (state.hand[state.turn][i] == move.card) {
            std::swap(state.hand[state.turn][i], move.card);
        }
    }

    // Update the turn color.
    state.turn = (state.turn == BLUE) ? RED : BLUE;

    return state;
}
