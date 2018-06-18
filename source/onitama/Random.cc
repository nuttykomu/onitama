#include <chrono>
#include "Random.h"

// If globals are evil, then so are
// random number generators. 😈
std::mt19937 RNG;

void seed_rng() {
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    RNG = std::mt19937(seed);
}

std::uniform_int_distribution<int> int_generator(int min, int max) {
    return std::uniform_int_distribution<int>(min, max);
}