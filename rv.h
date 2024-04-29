#pragma once

#include <Boost/random.hpp>
#include <numeric>
#include <random>

namespace RandomVariableStatisticalFunctions
{

	double normVariate();
	double normVariate(boost::mt19937& rng);
	double rand_uniform(boost::mt19937&);
	double inverseQNorm(double p,int err);

	double NonCentral_CS_Sample(boost::mt19937&, double delta, double lamba);


}

namespace rv = RandomVariableStatisticalFunctions;