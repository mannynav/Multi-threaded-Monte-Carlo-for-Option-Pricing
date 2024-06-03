

#include "RandomMersenneTwister.h"



RandomMersenneTwister::RandomMersenneTwister(const PseudoFactory& factory) :  rng(factory.GetSeed()), dist(0.0, 1.0)
{}

void RandomMersenneTwister::SeedGenerator(unsigned int seed)
{
	rng.seed(seed);
}