#include "rv.h"

double RandomVariableStatisticalFunctions::normVariate()
{

    std::random_device rd;  // Seed for random number engine
    std::mt19937 gen(rd()); // Mersenne Twister 19937 generator
    std::normal_distribution<> dist(0.0, 1.0); // Standard normal distribution

    return dist(gen);
}