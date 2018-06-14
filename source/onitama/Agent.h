#ifndef AGENT_H
#define AGENT_H

#include <random>

#include "State.h"

struct Node {
    uint32_t childrenCount;
    uint32_t playouts;
    uint32_t wins;
    Node *parent;
    Node **children;
    Move move;
};

class Agent {
public:
    Agent(GameState state, int color);
    bool updateState(GameState state, Move move);
    Node **run(int iterations);
//private:
    std::default_random_engine generator;
    GameState state;
    Node *root;
    int color;
};

#endif