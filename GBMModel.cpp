#include "GBMModel.h"
#include "rv.h"

GBMModel::GBMModel(PseudoFactory& factory) : S0_(factory.GetS0()),
                                             r_(factory.GetRiskFreeRate()),
                                             sigma_(factory.GetVolatility()),
                                             N_(factory.GetNumberTotalSteps()),
	                                         T_(factory.GetExpiry()),
									         dt_(factory.GetExpiry() / factory.GetNumberTotalSteps()),
											 sqrtdt_(std::sqrt(dt_)),
											 generator_(factory.CreateRandomBase()),
											 path_(factory.CreateBrownianMotionPath())
{
	drift_ = (r_ - 0.5 * sigma_ * sigma_) * dt_;
}


void GBMModel::simulate_paths(int start_idx, int end_idx, Eigen::MatrixXd& paths) const
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	generator_->SeedGenerator(seed);
	boost::mt19937 rng = generator_->GetGenerator();

	paths.col(0).setConstant(S0_);

	for (int i = start_idx; i < end_idx; ++i)
	{

		std::vector<double> variates(N_);

		path_->GeneratePath(variates,rng);

		for (int j = 0; j < N_; ++j)
		{
			//std::cout << "Variates: " << variates[j] << std::endl;
			paths(i, j + 1) = paths(i, j) * exp(drift_ + sigma_ * sqrtdt_ * variates[j]);
		}

		if ((i + 1) % 200000 == 0)
		{
			std::cout << "Paths simulated: " << i + 1 << std::endl;
		}
	}
}
