#include <iostream>
#include <ctime>

#include "Agent.h"
#include "Random.h"

int main() {
    precompute_moves();
    seed_rng();
    State state;
    state.initialize();
    Agent agent(state, state.turn);
    auto results = agent.run(30);
    for (auto child : results) {
        std::cout << "Move " << child->move.start << "-" << child->move.end << ": "
                  << child->wins / child->playouts * 100 << "%" << std::endl;
    }
    return 0;
}