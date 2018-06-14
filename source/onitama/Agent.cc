#include <ctime>

#include "Agent.h"

Agent::Agent(GameState state, int color)
    : state(state), color(color), generator((unsigned int)time(0)) {

    this->root = new Node;
    this->root->parent = nullptr;
    this->root->playouts = 0;
    this->root->wins = 0;

    auto moves = getMoves(this->state);
    this->root->childrenCount = moves.size();
    this->root->children = new Node*[this->root->childrenCount + 1];
    this->root->children[this->root->childrenCount] = nullptr;

    int index = 0;
    for (auto move : getMoves(this->state)) {
        Node *child = new Node;
        child->parent = this->root;
        child->children = nullptr;
        child->childrenCount = 0;
        child->playouts = 0;
        child->wins = 0;
        child->move = move;
        this->root->children[index++] = child;
    }
}

bool Agent::updateState(GameState state, Move move) {

    // ╔════════════════════════════════╗
    // ║ TODO: Implement this function. ║
    // ╚════════════════════════════════╝

}

Node **Agent::run(int iterations) {

    // ╔════════════════════════════════╗
    // ║ TODO: Implement this function. ║
    // ╚════════════════════════════════╝

}