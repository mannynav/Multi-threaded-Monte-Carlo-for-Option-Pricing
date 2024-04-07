#include "GBMModel.h"
#include "rv.h"

GBMModel::GBMModel(double S0, double r, double sigma) : S0_(S0), r_(r), sigma_(sigma)
{
}

GBMModel::GBMModel(PseudoFactory& factory) : S0_(factory.GetS0()), r_(factory.Getr()), sigma_(factory.Getsig())
{
	dt_ = factory.GetT() / factory.GetN();
	drift_ = (r_ - 0.5 * sigma_ * sigma_) * dt_;

	generator_ = factory.CreateRandomBase();
}


GBMModel::~GBMModel()
{
	delete generator_;
}


void GBMModel::simulate_paths(int start_idx, int end_idx, Eigen::MatrixXd& paths) const
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 gen(seed);
	std::normal_distribution<double> nd(0, 1);



	double sqrtdt = std::sqrt(dt_);

	// Simulate paths within the designated range
	for (int i = start_idx; i < end_idx; ++i)
	{
		paths(i, 0) = S0_; // Set initial price
		int num_paths_per_update = 200000;

		for (int j = 0; j < 100; ++j)
		{
			double random_number = nd(gen);

			paths(i, j + 1) = paths(i, j) * exp(drift_ + sigma_ * sqrtdt * random_number);
		}

		if ((i + 1) % num_paths_per_update == 0)
		{
			std::cout << "Paths simulated: " << i + 1 << std::endl;
		}
	}
}
