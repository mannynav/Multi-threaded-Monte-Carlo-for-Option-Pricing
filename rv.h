#pragma once

#include <vector>
#include <Boost/random.hpp>
#include <Boost/random/non_central_chi_squared_distribution.hpp>
#include <Eigen/Dense>
#include <numeric>
#include <random>

namespace RandomVariableStatisticalFunctions
{

	double normVariate();
	double rand_uniform();
	double inverseQNorm(double p,int err);


}

namespace rv = RandomVariableStatisticalFunctions;