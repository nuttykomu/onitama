#ifndef RANDOM_H
#define RANDOM_H

#include <random>

void seed_rng();
auto get_distribution(int, int);

extern std::mt19937 RNG;

#endif