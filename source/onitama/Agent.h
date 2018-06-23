#ifndef AGENT_H
#define AGENT_H

#include <vector>

#include "Color.h"
#include "Move.h"
#include "State.h"

#define NUMBER_OF_THREADS (16)

struct Node {
    double playouts;
    double wins;
    Move move;
    Node *parent;
    std::vector<Node *> children;
};

class Agent {
public:
    Agent(State state, Color color);
    std::vector<Node *> run(int seconds);
    void run_aux(int seconds, int id);
private:
    Node *tree_policy(Node *node, State &state);
    Color default_policy(State state);
    void backpropogate_rewards(Node *node, Color result);
    double compute_ucb1(Node *node);
    Color color;
    State root_state;
    Node *root_node[NUMBER_OF_THREADS];
    int iterations[NUMBER_OF_THREADS];
    std::clock_t start_time;
};

#endif