#pragma once

#include <Boost/random.hpp>
#include <numeric>
#include <random>

namespace RandomVariableStatisticalFunctions
{

	double normVariate();
	double rand_uniform();
	double inverseQNorm(double p,int err);


}

namespace rv = RandomVariableStatisticalFunctions;