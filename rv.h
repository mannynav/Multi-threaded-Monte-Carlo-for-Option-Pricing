#pragma once

#include <Boost/random.hpp>
#include <numeric>
#include <random>

namespace RandomVariableStatisticalFunctions
{

	double my_rand2();
	double GetNormalVariate();
	long Poisson_jumps(const double lambda);	//Simulates from a Poisson distribution, parameter lambda

	double normVariate();
	double normVariate(boost::mt19937& rng);
	double rand_uniform(boost::mt19937&);
	double NonCentral_CS_Sample(boost::mt19937&, double delta, double lamba);


	double inverseQNorm(double p,int err);
	double poisson_jumps(const double lambda);

	


}

namespace rv = RandomVariableStatisticalFunctions;