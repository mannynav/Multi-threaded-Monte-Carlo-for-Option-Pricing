#include "GBMModel.h"


GBMModel::GBMModel(double S0, double r, double sigma) : S0_(S0), r_(r), sigma_(sigma)
{
}

GBMModel::GBMModel(PseudoFactory& factory) : S0_(factory.GetS0()), r_(factory.Getr()), sigma_(factory.Getsig())
{
	dt_ = factory.GetT() / factory.GetN();
	drift_ = (r_ - 0.5 * sigma_ * sigma_) * dt_;
}


void GBMModel::simulate_paths(int start_idx, int end_idx, Eigen::MatrixXd& paths) const
{
	boost::random::mt19937 ngen(static_cast<unsigned int>(std::time(nullptr)));
	boost::random::normal_distribution<> norm_dist1(0.0, 1.0);
	boost::random::variate_generator<boost::mt19937&, boost::random::normal_distribution<>> normal_sampler(
		ngen, norm_dist1);

	// Simulate paths within the designated range
	for (int i = start_idx; i < end_idx; ++i)
	{
		paths(i, 0) = S0_; // Set initial price
		int num_paths_per_update = 100000;

		for (int j = 0; j < 100; ++j)
		{
			double random_number = normal_sampler();

			paths(i, j + 1) = paths(i, j) * exp(drift_ + sigma_ * sqrt(dt_) * random_number);
		}

		if ((i + 1) % num_paths_per_update == 0)
		{
			std::cout << "Paths simulated: " << i + 1 << std::endl;
		}
	}
}
