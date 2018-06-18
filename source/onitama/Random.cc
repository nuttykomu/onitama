#include "Random.h"

// If globals are evil, then so are
// random number generators. 😈
std::mt19937 RNG;

void seed_rng() {
    std::random_device rd;
    RNG = std::mt19937(rd());
}

std::uniform_int_distribution<int> int_generator(int min, int max) {
    return std::uniform_int_distribution<int>(min, max);
}