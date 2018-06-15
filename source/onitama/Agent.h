#ifndef AGENT_H
#define AGENT_H

#include <random>

#include "State.h"

struct Node {
    uint32_t playouts;
    uint32_t wins;
    Move move;
    Node *parent;
    std::vector<Node *> children;
};

class Agent {
public:
    Agent(GameState state, int color);
    bool updateState(GameState state, Move move);
    std::vector<Node *> run(int iterations);

//private:
    std::default_random_engine generator;
    GameState rootState;
    Node *root;
    int color;

    // Monte Carlo Tree Search.
    void selection();
    void expansion();
    void simulation();
    void backpropagation();
    double computeUCT(Node *node);
    Node *currentNode;
    GameState state;
};

#endif