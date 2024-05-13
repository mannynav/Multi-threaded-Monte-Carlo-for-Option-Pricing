#include "GBMModel.h"
#include "rv.h"

GBMModel::GBMModel(PseudoFactory& factory) : S0_(factory.GetS0()), r_(factory.Getr()), sigma_(factory.Getsig()), N_(factory.GetN()), T_(factory.GetT()), M_(factory.GetM())
{
	dt_ = factory.GetT() / factory.GetN();

	double shift = factory.GetShift();

	drift_ = ((r_+shift) - 0.5 * sigma_ * sigma_) * dt_;

	generator_ = factory.CreateRandomBase();
	path_ = factory.CreateBrownianMotionPath();
}


Eigen::MatrixXd GBMModel::simulate_paths(int start_idx, int end_idx, Eigen::MatrixXd& paths) const
{

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	generator_->SeedGenerator(seed);
	boost::mt19937 rng = generator_->GetGenerator();

	double sqrtdt = std::sqrt(dt_);

	// Simulate paths within the designated range
	for (int i = start_idx; i < end_idx; ++i)
	{
		paths(i, 0) = S0_; // Set initial price

		std::vector<double> variates(N_);

		//Variates will be filled with sqrt(dt)*Z, Z is standard normal
		path_->GeneratePath(variates,rng);

		for (int j = 0; j < N_; ++j)
		{
			//std::cout << "Variates: " << variates[j] << std::endl;
			paths(i, j + 1) = paths(i, j) * exp(drift_ + sigma_ * sqrtdt * variates[j]);

		}

		if ((i + 1) % 200000 == 0)
		{
			std::cout << "Paths simulated: " << i + 1 << std::endl;
		}
	}

	return paths;
}

