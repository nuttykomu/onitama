#include <cmath>
#include <ctime>
#include <limits>
#include <iostream>

#include "Agent.h"
#include "Card.h"

Agent::Agent(GameState state, int color)
    : rootState(state), color(color), generator((unsigned int)time(0)) {

    this->root = new Node;
    this->root->parent = nullptr;
    this->root->playouts = 0;
    this->root->wins = 0;

    int index = 0;
    for (auto move : getMoves(this->rootState)) {
        Node *child = new Node;
        child->parent = this->root;
        child->playouts = 0;
        child->wins = 0;
        child->move = move;
        this->root->children.push_back(child);
    }
}

bool Agent::updateState(GameState state, Move move) {

    // ╔════════════════════════════════╗
    // ║ TODO: Implement this function. ║
    // ╚════════════════════════════════╝

}

std::vector<Node *> Agent::run(int iterations) {
    for (int i = 0; i < iterations; i++) {
        this->state = this->rootState;
        this->currentNode = this->root;
        this->selection();
        this->expansion();
        this->simulation();
        this->backpropagation();

        if (i % 500 == 0) {
            std::cout << i << " iterations completed." << std::endl;
        }
    }
    return this->root->children;
}

void Agent::selection() {
    if (this->currentNode->children.size() != 0) {
        double maxScore = 0;
        for (Node *child : this->currentNode->children) {
            double nodeScore = computeUCT(child);
            if (nodeScore >= maxScore) {
                maxScore = nodeScore;
                this->currentNode = child;
            }
        }
        this->state = applyMove(this->state, this->currentNode->move);
        this->selection();
    }
}

void Agent::expansion() {
    auto moves = getMoves(this->state);
    std::uniform_int_distribution<int> selectMove(0, moves.size() - 1);
    bool nodeAlreadyExists = false;
    Move move;

    do {
        move = moves[selectMove(this->generator)];
        for (auto child : this->currentNode->children) {
            if (child->move.card == move.card &&
                child->move.start == move.start &&
                child->move.end == move.end) {
                nodeAlreadyExists == true;
            }
        }
    } while (nodeAlreadyExists);

    Node *child = new Node;
    child->parent = this->currentNode;
    child->playouts = 0;
    child->wins = 0;
    child->move = move;
    this->currentNode->children.push_back(child);

    this->state = applyMove(this->state, move);
    this->currentNode = child;
}

void Agent::simulation() {
    while (!hasVictory(this->state, BLUE) && !hasVictory(this->state, RED)) {
        auto moves = getMoves(this->state);
        std::uniform_int_distribution<int> selectMove(0, moves.size() - 1);
        auto move = moves[selectMove(this->generator)];
        this->state = applyMove(this->state, move);
    }
}

void Agent::backpropagation() {
    do {
        this->currentNode->playouts++;
        if (this->state.turn == this->color) {
            this->currentNode->wins++;
        }
        this->currentNode = this->currentNode->parent;
    } while (this->currentNode != nullptr);
}

double Agent::computeUCT(Node *node) {
    double n_i = node->playouts;
    double N_i = node->parent->playouts;
    if (n_i != 0) {
        double exploitation = (double)node->wins / node->playouts;
        double exploration = sqrt(2) * sqrt(log(N_i) / n_i);
        return exploitation + exploration;
    }
    else {
        return std::numeric_limits<double>::max();
    }
}
