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
}

bool Agent::updateState(GameState state, Move move) {

    // ╔════════════════════════════════╗
    // ║ TODO: Implement this function. ║
    // ╚════════════════════════════════╝

}

std::vector<Node *> Agent::run(int iterations) {
    while (this->root->playouts < 10000) {
        this->aborted = false;
        this->state = this->rootState;
        this->currentNode = this->root;
        this->selection();
        this->expansion();
        this->simulation();
        this->backpropagation();

        if (this->root->playouts % 500 == 0) {
            std::cout << this->root->playouts << " playouts. " << std::endl;
        }
    }
    return this->root->children;
}

void Agent::selection() {
    // Proceed until you reach a point where not all of the
    // child positions have statistics recorded.
    int childrenCount = this->currentNode->children.size();
    int possibleMoves = getMoves(this->state).size();
    bool allChildrenVisited = childrenCount == possibleMoves;
    bool childrenExist = childrenCount != 0;

    if (childrenExist && allChildrenVisited) {
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
        if (moves.size() == 0) {
            // This leaf node results in a win/loss for one of the players.
            // No more possible moves... ABORT MISSION!!!
            std::cout << this->state.pawns[BLUE][0] << std::endl;
            this->aborted = true;
            return;
        }

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
    if (!this->aborted) {
        do {
            this->currentNode->playouts++;
            if (this->state.turn == this->color) {
                this->currentNode->wins++;
            }
            this->currentNode = this->currentNode->parent;
        } while (this->currentNode != nullptr);
    }
}

double Agent::computeUCT(Node *node) {
    double n_i = node->playouts;
    double N_i = node->parent->playouts;
    double exploitation = (double)node->wins / node->playouts;
    double exploration = sqrt(2) * sqrt(log(N_i) / n_i);
    return exploitation + exploration;
}
