

#include "ImportanceSampledPath.h"

#include <boost/random/normal_distribution.hpp>
#include <boost/random/variate_generator.hpp>




ImportanceSampledPath::ImportanceSampledPath(const PseudoFactory& factory) : T_(factory.GetExpiry()), N_(factory.GetNumberTotalSteps()), dt_(T_/N_)
{
}

void ImportanceSampledPath::GeneratePath(std::vector<double>& path, boost::mt19937& rng) 
{
	double sqrtdt = std::sqrt(dt_);

	boost::normal_distribution<> nd(0.0, 1);
	boost::random::variate_generator<boost::mt19937&, boost::normal_distribution<>> rnorm(rng, nd);

	//for non IS paths
	//std::ranges::generate(path, rnorm);

	std::ranges::generate(path, [&rnorm, sqrtdt]() { return rnorm() * sqrtdt; });

	double path_sum = std::accumulate(path.begin(), path.end(), 0.0);

	W.push_back(path_sum);

}
