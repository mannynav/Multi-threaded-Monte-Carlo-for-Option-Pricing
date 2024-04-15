#include "GBMModel.h"
#include "rv.h"

GBMModel::GBMModel(double S0, double r, double sigma) : S0_(S0), r_(r), sigma_(sigma)
{
}

GBMModel::GBMModel(PseudoFactory& factory) : S0_(factory.GetS0()), r_(factory.Getr()), sigma_(factory.Getsig()), N_(factory.GetN()), T_(factory.GetT())
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
	generator_->SeedGenerator(seed);
	boost::mt19937 rng = generator_->GetGenerator();
	boost::normal_distribution<> nd1(0.0, 1.0);
	boost::variate_generator<boost::mt19937&, boost::normal_distribution<> > rnorm(rng, nd1);

	double sqrtdt = std::sqrt(dt_);

	// Simulate paths within the designated range
	for (int i = start_idx; i < end_idx; ++i)
	{
		paths(i, 0) = S0_; // Set initial price
		int num_paths_per_update = 200000;

		std::vector<double> variates(N_);
		std::generate(variates.begin(), variates.end(), rnorm);

		for (int j = 0; j < N_; ++j)
		{
			paths(i, j + 1) = paths(i, j) * exp(drift_ + sigma_ * sqrtdt * variates[j]);
		}

		if ((i + 1) % num_paths_per_update == 0)
		{
			std::cout << "Paths simulated: " << i + 1 << std::endl;
		}
	}
}
