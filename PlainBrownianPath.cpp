

#include "PlainBrownianPath.h"
#include <boost/random/variate_generator.hpp>


PlainBrownianPath::PlainBrownianPath() : standard_norm_distro_(0.0,1.0)
{}


void PlainBrownianPath::GeneratePath(std::vector<double>& path, boost::mt19937& rng)
{
	boost::random::variate_generator<boost::mt19937&, boost::normal_distribution<>> normal_variate(rng, standard_norm_distro_);
	std::ranges::generate(path, normal_variate);
}


