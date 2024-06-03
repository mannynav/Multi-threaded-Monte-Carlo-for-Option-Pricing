
#include "DisplacedDiffusionModel.h"
#include "rv.h"

DisplacedDiffusionModel::DisplacedDiffusionModel(PseudoFactory& factory) : S0_(factory.GetS0()),
																		   r_(factory.GetRiskFreeRate()),
																		   a_(factory.GetAdjustment()),
																		   sigmaDD_(factory.GetVolatilityDD()),
																		   M_(factory.GetNumberOfPaths()),
																		   N_(factory.GetNumberTotalSteps()),
																		   T_(factory.GetExpiry()),
																           dt_(factory.GetExpiry() / factory.GetNumberTotalSteps()),
                                                                           sqrtdt_(std::sqrt(dt_))
{
	drift_ = (r_  - 0.5 * sigmaDD_ * sigmaDD_) * dt_;
	generator_ = factory.CreateRandomBase();
	path_ = factory.CreateBrownianMotionPath();
}


void DisplacedDiffusionModel::simulate_paths(int start_idx, int end_idx, Eigen::MatrixXd& paths) const
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	generator_->SeedGenerator(seed);
	boost::mt19937 rng = generator_->GetGenerator();

	paths.col(0).setConstant(S0_ + a_);

	for (int i = start_idx; i < end_idx; ++i)
	{
		//paths(i, 0) = S0_ + a_; // Set initial price with displacement parameter

		std::vector<double> variates(N_);

		path_->GeneratePath(variates, rng);

		for (int j = 0; j < N_; ++j)
		{
			paths(i, j + 1) = (paths(i, j) - a_) * exp(drift_ + sigmaDD_ * sqrtdt_ * variates[j]) + a_;
		}

		if ((i + 1) % 200000 == 0)
		{
			std::cout << "Paths simulated: " << i + 1 << std::endl;
		}
	}
}