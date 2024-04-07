
#pragma once

#include <memory>

#include "RandomBase.h"
#include "Eigen/Dense"

#ifndef RandomMersenneTwisterH
#define RandomMersenneTwisterH


class PseudoFactory;

class  RandomMersenneTwister : public RandomBase
{

public:

	explicit RandomMersenneTwister(const PseudoFactory& factory);
	void SeedGenerator(unsigned int seed) override;
	boost::mt19937& GetGenerator() override { return rng; }


private:

	boost::mt19937 rng;
	boost::normal_distribution<> dist;

};


#endif // RandomMersenneTwisterH
