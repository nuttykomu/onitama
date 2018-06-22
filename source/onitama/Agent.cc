#include <cmath>
#include <ctime>
#include <iostream>
#include <limits>

#include "Agent.h"
#include "Random.h"

Agent::Agent(State state, Color color)
    : root_state(state), color(color) {
    this->root_node = new Node;
    this->root_node->parent = nullptr;
    this->root_node->playouts = 0;
    this->root_node->wins = 0;
}

std::vector<Node *> Agent::run(int seconds) {
    int iterations = 0;
    std::clock_t start_time = std::clock();
    while ((std::clock() - start_time) / (double)CLOCKS_PER_SEC < seconds) {
        State state = this->root_state.clone();
        Node *expanded_node = tree_policy(this->root_node, state);
        Color winner = default_policy(state);
        backpropogate_rewards(expanded_node, winner);
        iterations++;
    }
    std::cout << iterations << " iterations completed..." << std::endl;
    return root_node->children;
}

Node *Agent::tree_policy(Node *node, State &state) {
    // walk the tree until a terminal node is reached
    while (node->children.size() != 0 || state.get_moves().size() != 0) {
        auto moves = state.get_moves();
        auto picker = get_generator(0, moves.size() - 1);
        // if the current node is expandable, expand it...
        if (node->children.size() < moves.size()) {
            while (true) {
                auto move = moves[picker(RNG)];
                // check if the child already exists
                for (auto child : node->children) {
                    if (child->move.card == move.card ||
                        child->move.start == move.start ||
                        child->move.end == move.end) {
                        continue;
                    }
                }
                Node *child = new Node;
                child->parent = node;
                child->playouts = 0;
                child->wins = 0;
                child->move = move;
                node->children.push_back(child);
                state.apply_move(move);
                return child;
            }
        }
        // ...otherwise, select the best child node.
        else {
            Node *best_child = nullptr;
            double max_score = 0;
            for (auto child : node->children) {
                Move move = child->move;
                double score = compute_ucb1(child);
                if (score >= max_score) {
                    best_child = child;
                    max_score = score;
                }
            }
            state.apply_move(best_child->move);
            node = best_child;
        }
    }
    return node;
}

Color Agent::default_policy(State state) {
    while (!state.has_victory(🔵) && !state.has_victory(🔴)) {
        auto moves = state.get_moves();
        auto picker = get_generator(0, moves.size() - 1);
        auto move = moves[picker(RNG)];
        state.apply_move(move);
    }
    return state.turn;
}

void Agent::backpropogate_rewards(Node *node, Color result) {
    do {
        node->playouts++;
        if (result == this->color) {
            node->wins++;
        }
        node = node->parent;
    } while (node != nullptr);
}

double Agent::compute_ucb1(Node *node) {
    const double infinity = std::numeric_limits<double>::infinity();
    double exploration = sqrt(2 * log(node->parent->playouts) / node->playouts);
    double exploitation = node->wins / node->playouts;
    return (node->playouts != 0) ? exploration + exploitation : infinity;
}