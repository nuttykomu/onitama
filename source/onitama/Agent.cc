#include <cmath>
#include <ctime>
#include <iostream>
#include <limits>
#include <thread>

#include "Agent.h"
#include "Random.h"

Agent::Agent(State state, Color color)
    : root_state(state), color(color) {
    for (int i = 0; i < NUMBER_OF_THREADS; i++) {
        this->root_node[i] = new Node;
        this->root_node[i]->parent = nullptr;
        this->root_node[i]->playouts = 0;
        this->root_node[i]->wins = 0;
    }
}

std::vector<Node *> Agent::run(int seconds) {
    this->start_time = std::clock();
    // construct multiple MCTS trees in parallel
    std::thread mcts_agents[NUMBER_OF_THREADS];
    for (int id = 0; id < NUMBER_OF_THREADS; id++) {
        mcts_agents[id] = std::thread(&Agent::run_aux, this, seconds, id);
    }
    // synchronize the threads
    for (int id = 0; id < NUMBER_OF_THREADS; id++) {
        mcts_agents[id].join();
    }
    // merge the root children together
    std::vector<Node *> merged_children = this->root_node[0]->children;
    for (int id = 1; id < NUMBER_OF_THREADS; id++) {
        for (auto thread_child : this->root_node[id]->children) {
            for (auto merged_child : merged_children) {
                if (merged_child->move.card == thread_child->move.card &&
                    merged_child->move.start == thread_child->move.start &&
                    merged_child->move.end == thread_child->move.end) {
                    merged_child->playouts += thread_child->playouts;
                    merged_child->wins += thread_child->wins;
                }
            }
        }
    }
    // compute how many total iterations were completed
    int iterations = 0;
    for (int id = 0; id < NUMBER_OF_THREADS; id++) {
        iterations += this->iterations[id];
    }
    std::cout << iterations << " iterations completed..." << std::endl;
    return merged_children;
}

void Agent::run_aux(int seconds, int id) {
    this->iterations[id] = 0;
    while ((std::clock() - this->start_time) / (double)CLOCKS_PER_SEC < seconds) {
        State state = this->root_state.clone();
        Node *expanded_node = tree_policy(this->root_node[id], state);
        Color winner = default_policy(state);
        backpropogate_rewards(expanded_node, winner);
        this->iterations[id]++;
    }
}

Node *Agent::tree_policy(Node *node, State &state) {
    // walk the tree until a terminal node is reached
    while (node->children.size() != 0 || state.get_moves().size() != 0) {
        auto moves = state.get_moves();
        auto picker = get_generator(0, moves.size() - 1);
        // if the current node is expandable, expand it...
        if (node->children.size() < moves.size()) {
            Move move;
            bool child_exists = true;
            while (child_exists) {
                child_exists = false;
                move = moves[picker(RNG)];
                // check if the child already exists
                for (auto child : node->children) {
                    if (child->move.card == move.card &&
                        child->move.start == move.start &&
                        child->move.end == move.end) {
                        child_exists = true;
                    }
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