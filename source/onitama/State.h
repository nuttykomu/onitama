#ifndef STATE_H
#define STATE_H

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

GameState getNewGameState();
GameState applyMove(GameState state, int move);

int *getBluePositions(GameState state);
int *getRedPositions(GameState state);

bool blueWon(GameState state);
bool redWon(GameState state);

#endif