#include "AntitheticPath.h"

AntitheticPath::AntitheticPath(const PseudoFactory& factory) : T_(factory.GetExpiry()), N_(factory.GetNumberTotalSteps()), dt_(T_ / N_), even_(true),standard_norm_distro_(0.0,1.0)
{
	drift_ = 0.0;
	sigma_ = 0.0;
	neg_path.resize(N_);
}

void AntitheticPath::GeneratePath(std::vector<double>& path, boost::mt19937& rng) 
{
	boost::random::variate_generator<boost::mt19937&, boost::normal_distribution<>> rnorm(rng, standard_norm_distro_);

	//if even we generate a normal path, if odd we generate the negative of the previous path (the even path)
	if (even_)
	{
		std::ranges::generate(path, rnorm);

		std::ranges::transform(path, neg_path.begin(),[](double x) { return -x; }); //we need to store the negative of this path for the next iteration

		even_ = false;
	}
	else
	{
		std::ranges::copy(neg_path, path.begin()); //we change the original path to neg_path

		even_ = true;
	}

}
