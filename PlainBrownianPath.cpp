

#include "PlainBrownianPath.h"
#include <boost/random/normal_distribution.hpp>
#include <boost/random/variate_generator.hpp>


void PlainBrownianPath::GeneratePath(std::vector<double>& path, boost::mt19937& rng)
{
	boost::normal_distribution<> nd(0.0, 1);
	boost::random::variate_generator<boost::mt19937&, boost::normal_distribution<>> rnorm(rng, nd);

	std::ranges::generate(path, rnorm);

}


