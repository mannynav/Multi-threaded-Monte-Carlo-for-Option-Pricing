#include "AntitheticPath.h"

AntitheticPath::AntitheticPath(const PseudoFactory& factory) : T_(factory.GetExpiry()), N_(factory.GetNumberTotalSteps()), dt_(T_ / N_), even_(true)
{
	drift_ = 0.0;
	sigma_ = 0.0;
	neg_path.resize(N_);
}

void AntitheticPath::GeneratePath(std::vector<double>& path, boost::mt19937& rng) 
{
	boost::normal_distribution<> nd(0.0, 1);
	boost::random::variate_generator<boost::mt19937&, boost::normal_distribution<>> rnorm(rng, nd);


	//if even we generate a normal path, if odd we generate the negative of the previous path (the even path)
	if (even_)
	{

		std::ranges::generate(path, rnorm);

		//we need to store the negative of this path for the next iteration
		std::ranges::transform(path, neg_path.begin(),[](double x) { return -x; });

		even_ = false;
		
	}
	else
	{
		//we change the original path to neg_path
		std::ranges::copy(neg_path, path.begin());

		even_ = true;
	}

}
