#include <ctime>
#include <iostream>

#include "Agent.h"
#include "Random.h"

/**
 * Driver program for playing a game against the AI agent.
 * This is just for testing purposes. Eventually, I will
 * create a web interface and run this code from a Node.js
 * server.
 */
int main() {
    precompute_moves();
    seed_rng();
    State state;
    state.initialize();
    Color agent_color = 🔵;
    Agent agent(state.clone(), agent_color);

    std::cout << std::endl << "  > Welcome to Onitama!" << std::endl
              << "  > Generating initial board state..." << std::endl
              << std::endl << state << std::endl;

    while (!state.has_victory(🔵) && !state.has_victory(🔴)) {
        if (state.turn == agent_color) {
            // get the best move
            std::cout << "  > Bot (AI) is making a move..." << std::endl;
            auto results = agent.run(45);
            double best_score = 0;
            Move best_move;
            for (auto child : results) {
                double move_score = child->wins / child->playouts;
                if (move_score > best_score) {
                    best_move = child->move;
                    best_score = move_score;
                }
            }
            // make the move
            state.apply_move(best_move);
            agent.update(best_move);
            // output new state
            std::cout << "  > Bot (AI) moved from " << best_move.start << " to " << best_move.end
                      << " using " << CARD_LIST[best_move.card].name << "..." << std::endl
                      << std::endl << state << std::endl;
        }
        else {
            // display possible moves
            std::cout << "  > Here are your available moves:\n" << std::endl;
            auto moves = state.get_moves();
            for (int i = 0; i < moves.size(); i++) {
                std::cout << "      Move " << i << ": " << moves[i].start << " to "
                          << moves[i].end << " [" << CARD_LIST[moves[i].card].name << "] " << std::endl;
            }
            // choose move
            std::cout << "\n  > Where would you like to move? ";
            int selected_move;
            std::cin >> selected_move;
            // apply move
            state.apply_move(moves[selected_move]);
            agent.update(moves[selected_move]);
            // output new state
            std::cout << std::endl << state << std::endl;
        }
    }

    return 0;
}